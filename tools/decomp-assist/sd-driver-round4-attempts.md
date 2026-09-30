# SD driver round 4 attempts

Baseline c7958e9f: 19/26 exact, code 8284/11752, data 408/3592, fuzzy 98.5769. Every trial builds only the SD object; restored trials do not remain in source. Readonly accessors use ordinary pointers, without volatile.

- pfd_sddrv_get_disk_info: validate disk and output record in separate early returns. 100/96 instructions, 90 differing positions, objdiff 95.729164%, pool offsets identical.
- pfd_sddrv_get_disk_info: clear output geometry through typed helper. 98/96 instructions, 2 differing positions, objdiff 97.916664%, pool offsets identical.
- pfd_sddrv_get_disk_info: derive media attributes in named temporary. 96/96 instructions, 46 differing positions, objdiff 88.479164%, pool offsets identical.
- pfd_sddrv_get_total_sectors: form sector multiplier with compound shift. 80/80 instructions, 6 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: subtract base exponent from clamped multiplier in place. 80/80 instructions, 10 differing positions, objdiff 96.9875%, pool offsets identical.
- pfd_sddrv_get_total_sectors: calculate block product after exponent clamping. 80/80 instructions, 23 differing positions, objdiff 91.7375%, pool offsets identical.
- pfd_sddrv_get_total_sectors: reduce clamped exponent before compound power shift. 80/80 instructions, 6 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: form multiplier through typed power-of-two helper. 80/80 instructions, 7 differing positions, objdiff 99.375%, pool offsets identical.
- pfd_sddrv_get_total_sectors: name the clamped relative exponent before multiplier shift. 80/80 instructions, 6 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: hold shift calculation in a word and narrow its product operand. 80/80 instructions, 5 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: use signed word for shift calculation with narrowed factor. 80/80 instructions, 5 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: narrow unsigned word multiplier after compound shift. 80/80 instructions, 5 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_st_removal_callback: transition removal state and return current device. 65/66 instructions, 53 differing positions, objdiff 95.07576%, pool offsets identical.
- pfd_st_removal_callback: transition removal state and report device presence. 65/66 instructions, 53 differing positions, objdiff 95.07576%, pool offsets identical.
- pfd_st_removal_callback: read current device through a pointer to its record field. 66/66 instructions, 3 differing positions, objdiff 96.818184%, pool offsets identical.
- pfd_sddrv_get_total_sectors: reuse decoded block-size temporary for sector scaling. 80/80 instructions, 6 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: keep sector factor within relative-exponent temporary. 80/80 instructions, 5 differing positions, objdiff 99.5%, pool offsets identical.
- pfd_sddrv_get_total_sectors: reuse decoded minimum for the power-of-two factor. 80/80 instructions, 7 differing positions, objdiff 99.375%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: calculate each CHS tuple in matching FAT32 writer order. 202/202 instructions, 9 differing positions, objdiff 99.75247%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: compute ending CHS tuple before starting tuple. 202/202 instructions, 16 differing positions, objdiff 99.57921%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: decode cylinder coordinates with sector quotient and head remainder. 202/202 instructions, 83 differing positions, objdiff 90.60396%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: cache starting LBA before tuple arithmetic. 202/202 instructions, 13 differing positions, objdiff 99.628716%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: cache both partition endpoint LBAs before tuple arithmetic. 202/202 instructions, 31 differing positions, objdiff 96.73267%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: hold starting LBA in a signed sector cursor. 202/202 instructions, 13 differing positions, objdiff 99.628716%, pool offsets identical.
- pfd_sddrv_get_total_sectors: derive relative power in typed sector-scaling helper. 80/80 instructions, 10 differing positions, objdiff 96.9875%, pool offsets identical.
- pfd_sddrv_get_total_sectors: derive relative exponent before an inline compound power shift. 80/80 instructions, 7 differing positions, objdiff 99.375%, pool offsets identical.
- pfd_sddrv_get_total_sectors: clamp and derive scale in one typed helper. 80/80 instructions, 7 differing positions, objdiff 99.375%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: read starting LBA through readonly format accessor. 202/202 instructions, 9 differing positions, objdiff 99.75247%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: read starting cylinder numerator through readonly accessor. 204/202 instructions, 144 differing positions, objdiff 97.49505%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: convert LBA coordinates through typed geometry helper. 202/202 instructions, 18 differing positions, objdiff 99.430695%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: derive cylinder span from signed geometry values. 202/202 instructions, 9 differing positions, objdiff 99.75247%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: compute heads before corresponding cylinder divisions. 202/202 instructions, 9 differing positions, objdiff 99.75247%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: multiply sectors-per-track before head count in cylinder span. 202/202 instructions, 9 differing positions, objdiff 99.70297%, pool offsets identical.
- pfd_sddrv_build_fat32_mbr_bpb: write the internal reserved-sector buffer without redundant null guard. 216/222 instructions, 100 differing positions, objdiff 97.20721%, pool offsets differ.
- pfd_sddrv_build_fat32_mbr_bpb: validate reserved sector through typed presence predicate. 230/222 instructions, 122 differing positions, objdiff 94.75225%, pool offsets identical.
- pfd_sddrv_build_fat32_mbr_bpb: validate reserved-sector buffer after obtaining its typed view. 230/222 instructions, 122 differing positions, objdiff 94.75225%, pool offsets identical.
- pfd_sddrv_finalize: clear insertion and drive state with chained scalar assignment. 57/57 instructions, 6 differing positions, objdiff 82.45614%, pool offsets identical.
- pfd_sddrv_finalize: clear insertion state through a signed SDK boolean view. 57/57 instructions, 4 differing positions, objdiff 92.63158%, pool offsets identical.
- pfd_sddrv_finalize: place initialized-state cleanup in its positive lifecycle branch. 57/57 instructions, 12 differing positions, objdiff 88.947365%, pool offsets identical.
- pfd_sddrv_init: dispatch all driver statuses through common return label. 146/144 instructions, 139 differing positions, objdiff 90.03472%, pool offsets identical.
- pfd_sddrv_init: put new initialization in the uninitialized branch. 141/144 instructions, 142 differing positions, objdiff 93.125%, pool offsets identical.
- pfd_sddrv_init: read driver lifecycle through its record pointer. 139/144 instructions, 101 differing positions, objdiff 82.076385%, pool offsets identical.
- pfd_sddrv_full_format: initialize interrupt event explicitly. 117/117 instructions, 0 differing positions, objdiff 100.0%, pool offsets identical.
  Data result: {'.rodata': 368, '.data': 2574, '.bss': 608, '.sbss': 12}; {'g_attach_func': (0, 4), 'g_detach_func': (4, 4), 'g_event': (8, 4), 'g_pfd_sddrv_info': (0, 28), 'g_pfd_sddev': (32, 64), 'g_pfd_sddrv_buf': (96, 512)}.
- pfd_sddrv_full_format: initialize existing device and sector storage explicitly. 117/117 instructions, 0 differing positions, objdiff 100.0%, pool offsets identical.
  Data result: {'.rodata': 368, '.data': 2574, '.bss': 604, '.sbss': 12}; {'g_attach_func': (0, 4), 'g_detach_func': (4, 4), 'g_pfd_sddev': (0, 64), 'g_pfd_sddrv_buf': (64, 512), 'g_pfd_sddrv_info': (576, 28), 'g_event': (8, 4)}.
- pfd_sddrv_full_format: initialize driver context explicitly. 117/117 instructions, 0 differing positions, objdiff 100.0%, pool offsets identical.
  Data result: {'.rodata': 368, '.data': 2574, '.bss': 608, '.sbss': 12}; {'g_attach_func': (0, 4), 'g_detach_func': (4, 4), 'g_pfd_sddrv_info': (0, 28), 'g_event': (8, 4), 'g_pfd_sddev': (32, 64), 'g_pfd_sddrv_buf': (96, 512)}.
- pfd_sddrv_init: validate disk through an inline status-returning helper. 147/144 instructions, 142 differing positions, objdiff 87.43056%, pool offsets identical.
- pfd_sddrv_init: validate generic disk argument through status helper. 147/144 instructions, 142 differing positions, objdiff 87.43056%, pool offsets identical.
- pfd_sddrv_init: preserve separate identity status in initialized branch. 147/144 instructions, 142 differing positions, objdiff 87.43056%, pool offsets identical.

## Geometry full gate

CHS arithmetic now follows the matching FAT32 writer in this unit: cylinder, head, sector for each endpoint. This cuts the 20 positional differences to nine, all a swap of temporary registers 8 and 9. Compound multiplier shifting cuts capacity differences from ten to six. Both instruction counts already equal the target. All 19 exact functions are preserved; no new function is exact yet. The full gate passes with zero regressions.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8284/11752 data 408/3592 functions 19/26 fuzzy 98.9142 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 19/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.91423
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 96.818184
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8284/11752 data 408 functions 19 fuzzy 98.5769
regressions vs baseline: 0
global matched_code_percent: 85.95139 -> 85.95139
global fuzzy_match_percent: 98.69584 -> 98.69716
global complete_code_percent: 59.99415 -> 59.99415
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_store_mbr_buf: reuse sector lookup temporary for starting coordinate. 202/202 instructions, 13 differing positions, objdiff 99.628716%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: reuse sector lookup temporary for ending coordinate. 202/202 instructions, 9 differing positions, objdiff 99.75247%, pool offsets identical.
- pfd_sddrv_store_mbr_buf: name the head and track geometry used in both coordinates. 202/202 instructions, 15 differing positions, objdiff 99.55446%, pool offsets identical.
- pfd_sddrv_get_total_sectors: represent encoded read-length exponent as an unsigned byte. 81/80 instructions, 39 differing positions, objdiff 96.75%, pool offsets identical.
- pfd_sddrv_get_total_sectors: represent encoded read-length exponent as a halfword. 81/80 instructions, 39 differing positions, objdiff 96.75%, pool offsets identical.
- pfd_sddrv_get_total_sectors: represent decoded card size within its twelve-bit field width. 81/80 instructions, 43 differing positions, objdiff 90.5625%, pool offsets identical.

## Final audit

Every remaining function received at least three new distinct compiled source attempts this round. Rejected trials were restored. No new instruction-exact function was found; the unit remains open at 19/26. The only retained source changes are the compound sector-multiplier shift and the CHS expression order taken from the matching FAT32 writer in this same source file. Code and data exact-byte counts remain unchanged, while fuzzy improves from 98.5769 to 98.9142.

New attempts per remaining function:
- pfd_sddrv_get_disk_info: 3.
- pfd_sddrv_get_total_sectors: 18.
- pfd_st_removal_callback: 3.
- pfd_sddrv_store_mbr_buf: 15.
- pfd_sddrv_build_fat32_mbr_bpb: 3.
- pfd_sddrv_finalize: 3.
- pfd_sddrv_init: 6.

Remaining differences:
- get_disk_info: 98/96 instructions. The first 96 match exactly. The extracted target symbol ends at `mtlr r0`, before the stack-pointer restoration and `blr`. Separate argument checks, typed geometry clearing, and temporary attributes did not repair this boundary. No symbol-size changes were made.
- get_total_sectors: 80/80 instructions. Six differences are only temporary registers in the final power-of-two factor and multiply. Compound shift improves 96.9875% to 99.5%. Width changes, typed helper forms, local reuse, and operation order did not reach 100%.
- removal_callback: 66/66 instructions. Three differences are the initial device load moving before insertion-state clearing and its zero register. Typed state transitions and a pointer-to-device-field accessor did not improve the retained form.
- store_mbr_buf: 202/202 instructions. Nine differences are solely the interchange of registers 8 and 9 for cylinder span and starting LBA. Matching FAT32 CHS order improves 95.84158% to 99.75247%. Endpoint caching, scalar accessors, geometry helpers, operand order, and local reuse did not resolve the register choice.
- build_fat32_mbr_bpb: 230/222 instructions. Calculation, primary/backup BPB writes, FSInfo writes, reserved writes, final MBR write, and return were checked against target blocks. The extra instructions remain in the inlined reserved-sector validation and report dispatch. Removing internal null validation produced 216 instructions and lost two pooled report strings, so it was rejected. Presence validation and the typed sector view kept all strings but did not shorten the helper. No synthetic dead block was inserted.
- finalize: 57/57 instructions. Four differences remain in final flag-mask registers and state-store scheduling. Chained resets, an SDK boolean view, and moving initialization-bit clearing into the initialized branch were rejected.
- init: 144/144 instructions. Null comparison, branchless existing-disk result selection, and global store/load scheduling differ. Common-return control flow, positive initialization branching, a record pointer, and status-returning argument helpers did not match. The higher-scoring 141-instruction positive branch was rejected because its instruction count and target flow diverged.

Data audit:
- All 46 string payloads and offsets are identical, and both immutable tables match the original `.rodata` bytes.
- The common bytes of `.data`, `.bss`, and `.sbss` are identical. `.data` is missing two terminal alignment zeros; `.bss` has the same total size but the extracted driver-context symbol is 32 bytes while source is 28. `.sbss` places the event at offset 8 rather than 32 and omits the extracted zero alignment interval.
- Three ordinary explicit-initializer variants were built. Context and event initializers kept the existing sizes. Initializing device and buffer storage changed BSS declaration order and was rejected. All initializer trials were restored.
- No additional context field or buffer padding is supported by observed accesses. Alignment and the extracted context symbol boundary remain uncertain; no filler members, artificial data, packed strings, or forced alignment were added.

```text
.data: compiled 2574, original 2576, common payload differences 0, original suffix 0000.
.bss: compiled 608, original 608, common payload differences 0, original suffix .
.rodata: compiled 368, original 368, common payload differences 0, original suffix .
.sbss: compiled 12, original 40, common payload differences 0, original suffix 00000000000000000000000000000000000000000000000000000000.
g_pfd_sddrv_info: compiled offset/size (0, 28), original (0, 32).
g_pfd_sddev: compiled offset/size (32, 64), original (32, 64).
g_pfd_sddrv_buf: compiled offset/size (96, 512), original (96, 512).
g_attach_func: compiled offset/size (0, 4), original (0, 4).
g_detach_func: compiled offset/size (4, 4), original (4, 4).
g_event: compiled offset/size (8, 4), original (32, 4).
String payloads and offsets identical: 46/46.
Remaining functions:
pfd_st_removal_callback: 96.818184%; src 0x108 base 0x108 insns 66/66; diffs 3: [10, 12, 13]
pfd_sddrv_init: 92.326385%; src 0x240 base 0x240 insns 144/144; diffs 31: [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
pfd_sddrv_finalize: 92.63158%; src 0xe4 base 0xe4 insns 57/57; diffs 4: [45, 47, 49, 50]
pfd_sddrv_get_disk_info: 97.916664%; src 0x188 base 0x180 insns 98/96; --- delete mine 96:98 base 96:96
pfd_sddrv_get_total_sectors: 99.5%; src 0x140 base 0x140 insns 80/80; diffs 6: [57, 58, 59, 60, 61, 62]
pfd_sddrv_store_mbr_buf: 99.75247%; src 0x328 base 0x328 insns 202/202; diffs 9: [59, 60, 64, 65, 67, 69, 72, 74, 80]
pfd_sddrv_build_fat32_mbr_bpb: 94.75225%; src 0x398 base 0x378 insns 230/222; --- replace mine 24:25 base 24:25
```

Final full gate rebuilt all four original leaf units from scratch. It passes with zero baseline regressions, forbidden additions, and readability additions. sd-driver-round4-gates.txt contains every gate block from this round verbatim.

Before -> after:
- pfd_cmn: instruction-exact 1/1 -> 1/1, code 280/280 -> 280/280, data None -> None, fuzzy 100.0000 -> 100.0000.
- nand_drv: instruction-exact 18/18 -> 18/18, code 6952/6952 -> 6952/6952, data 5696/5696 -> 5696/5696, fuzzy 100.0000 -> 100.0000.
- msc_drv: instruction-exact 2/2 -> 2/2, code 20/20 -> 20/20, data 8/8 -> 8/8, fuzzy 100.0000 -> 100.0000.
- sd_drv: instruction-exact 19/26 -> 19/26, code 8284/11752 -> 8284/11752, data 408/3592 -> 408/3592, fuzzy 98.5769 -> 98.9142.
