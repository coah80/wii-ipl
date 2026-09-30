# SD driver round 3 attempts

Baseline SD pool identical; starts at 15/26 exact functions. Each trial builds only its owned object. Failed experiments are restored.

- pfd_sddrv_unmount: ordinary static mounted-flag helper without explicit inline. 12/13 instructions; 9 differing positions.
- pfd_sddrv_unmount: read mounted bit through ordinary static accessor. 12/13 instructions; 9 differing positions.
- pfd_sddrv_unmount: read and clear flags through two ordinary static accessors. 12/13 instructions; 9 differing positions.
- pfd_sddrv_physical_read: marshal aligned transfer through buffer-first scalar accessor. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_read: use a signed sector cursor with unsigned SD API conversion. 127/127 instructions; 0 differing positions.
- pfd_sddrv_physical_read: represent sector and buffer as transfer cursor fields. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_write: marshal aligned transfer through buffer-first scalar accessor. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_write: use a signed sector cursor with unsigned SD API conversion. 127/127 instructions; 0 differing positions.
- pfd_sddrv_physical_write: represent sector and buffer as transfer cursor fields. 127/127 instructions; 2 differing positions.

## Signed transfer cursors full gate

Both 127-instruction transfer functions match with signed sector cursors. The SDK card size limits keep the cursor within its signed range. API sector parameters remain unsigned. No extra helper functions are retained.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 7956/11752 data 408/3592 functions 17/26 fuzzy 98.1464 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 17/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.146355
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.89474
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.84158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 6940/11752 data 408 functions 15 fuzzy 98.1395
regressions vs baseline: 0
global matched_code_percent: 85.68883 -> 85.72276
global fuzzy_match_percent: 98.59454 -> 98.59455
global complete_code_percent: 59.86180 -> 59.86180
global matched_data_percent: 90.85581 -> 90.85581
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_get_total_sectors: use signed intermediate block count. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: use signed decoded CSD card size. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: use signed shift count for read block length. 80/80 instructions; 10 differing positions.
- pfd_sddrv_store_mbr_buf: use signed cylinder span for CHS arithmetic. 202/202 instructions; 20 differing positions.
- pfd_sddrv_store_mbr_buf: use signed short cylinder coordinates. 202/202 instructions; 20 differing positions.
- pfd_sddrv_store_mbr_buf: use signed short ending cylinder coordinate. 202/202 instructions; 20 differing positions.
- pfd_sddrv_get_disk_info: derive write-protection attribute in one expression. 94/96 instructions; 46 differing positions.
- pfd_sddrv_get_disk_info: clear geometry only in positive total-sector result branch. 98/96 instructions; 14 differing positions.
- pfd_sddrv_get_disk_info: compare memory-type bit values before reporting invalid media. 102/96 instructions; 61 differing positions.
- pfd_sddrv_full_format: initialize callback pointers explicitly to null. 117/117 instructions; 0 differing positions.
  Data trial: [('.data', 2574), ('.bss', 608), ('.rodata', 368), ('.sbss', 12)]; [('g_attach_func', 0, 4), ('g_detach_func', 4, 4), ('g_pfd_sddrv_info', 0, 28), ('g_event', 8, 4)].
- pfd_sddrv_full_format: initialize driver state and interrupt event explicitly. 117/117 instructions; 0 differing positions.
  Data trial: [('.data', 2574), ('.bss', 608), ('.rodata', 368), ('.sbss', 12)]; [('g_attach_func', 8, 4), ('g_detach_func', 4, 4), ('g_pfd_sddrv_info', 0, 28), ('g_event', 0, 4)].
- pfd_sddrv_full_format: spell final report literal as adjacent readable fragments. 117/117 instructions; 0 differing positions.
  Data trial: [('.data', 2574), ('.bss', 608), ('.rodata', 368), ('.sbss', 12)]; [('g_attach_func', 8, 4), ('g_detach_func', 4, 4), ('g_pfd_sddrv_info', 0, 28), ('g_event', 0, 4)].
- pfd_sddrv_build_fat32_mbr_bpb: fixed-size sector buffer parameter in reserved-sector helper. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: validate signature field through small typed writer. 230/222 instructions; 117 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: validate signature member after clearing reserved-sector buffer. 230/222 instructions; 117 differing positions.
- pfd_st_inter_callback: scope readonly device state to registration block. 66/69 instructions; 39 differing positions.
- pfd_st_inter_callback: scope readonly disk state to notification block. 70/69 instructions; 24 differing positions.
- pfd_st_inter_callback: separate readonly registration and notification state pointers. 71/69 instructions; 65 differing positions.
- pfd_st_removal_callback: scope readonly device state to registration block. 63/66 instructions; 37 differing positions.
- pfd_st_removal_callback: scope readonly disk state to notification block. 67/66 instructions; 26 differing positions.
- pfd_st_removal_callback: separate readonly registration and notification state pointers. 68/66 instructions; 61 differing positions.
- pfd_st_inter_callback: device presence through readonly state accessor. 66/69 instructions; 39 differing positions.
- pfd_st_inter_callback: disk and drive presence through readonly state accessors. 68/69 instructions; 55 differing positions.
- pfd_st_inter_callback: all presence tests through readonly state accessors. 69/69 instructions; 0 differing positions.
- pfd_st_removal_callback: device presence through readonly state accessor. 63/66 instructions; 37 differing positions.
- pfd_st_removal_callback: disk and drive presence through readonly state accessors. 65/66 instructions; 53 differing positions.
- pfd_st_removal_callback: all presence tests through readonly state accessors. 66/66 instructions; 3 differing positions.
- pfd_st_removal_callback: update insertion state through mutable record pointer before readonly device access. 66/66 instructions; 3 differing positions.
- pfd_st_removal_callback: represent inserted and ejected state as SDK BOOL fields. 66/66 instructions; 3 differing positions.
- pfd_st_removal_callback: update insertion state through typed state setter. 66/66 instructions; 3 differing positions.
- pfd_sddrv_unmount: read mounted flag through readonly state accessor. 13/13 instructions; 0 differing positions.
- pfd_sddrv_finalize: read mounted flag through readonly state accessor. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: read both lifecycle flags through readonly accessors. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: read final initialized-state flags through readonly accessor. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: reset lifecycle fields through a driver record pointer. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: preserve initialized flags in a named mask temporary. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: reset media state before clearing initialized flag. 57/57 instructions; 9 differing positions.
- pfd_sddrv_finalize: clear initialized flag through typed record helper. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: reset lifecycle state through typed record helper. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: clear initialized flag through compound assignment. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: use signed local lifecycle flag word. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: reset drive before media and disk state. 57/57 instructions; 6 differing positions.
- pfd_sddrv_finalize: reset disk before media and drive state. 57/57 instructions; 5 differing positions.

## Callback and lifecycle full gate

Readonly record accessors preserve the target reloads without volatile. Insertion callback and unmount are exact. Finalize now clears insertion state without clearing the target-preserved ejection state; four scheduling differences remain. Removal retains three scheduling differences.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8284/11752 data 408/3592 functions 19/26 fuzzy 98.4765 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 19/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.47652
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 96.818184
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.84158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 6940/11752 data 408 functions 15 fuzzy 98.1395
regressions vs baseline: 0
global matched_code_percent: 85.68883 -> 85.73370
global fuzzy_match_percent: 98.59454 -> 98.59586
global complete_code_percent: 59.86180 -> 59.86180
global matched_data_percent: 90.85581 -> 90.85581
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_init: readonly flag access and truth tests for media bits. 144/144 instructions; 29 differing positions.
- pfd_sddrv_init: dispatch already-initialized disk mismatch first. 144/144 instructions; 29 differing positions.
- pfd_sddrv_init: share success return for an already initialized disk. 141/144 instructions; 134 differing positions.
- pfd_sddrv_init: use SDK null pointer constant and direct secondary flag read. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: compare registered disk through readonly state accessor. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: keep existing-disk result in small typed helper. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: validate disk using an unsigned address value. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: validate disk against a typed null disk pointer. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: validate disk against generic SDK null pointer. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: validate disk through typed presence predicate. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: compare initialized disk through typed predicate. 144/144 instructions; 31 differing positions.
- pfd_sddrv_init: use typed predicates for disk validation and identity. 144/144 instructions; 31 differing positions.
- pfd_st_removal_callback: clear inserted state through field pointer accessor. 66/66 instructions; 3 differing positions.
- pfd_sddrv_finalize: clear initialization bit through flag-word helper. 57/57 instructions; 4 differing positions.
- pfd_sddrv_finalize: clear initialization bit through field pointer accessor. 57/57 instructions; 4 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: check reserved buffer through unsigned address. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: write reserved sector in positive buffer branch. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: share reserved-sector status return across null validation. 229/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: declare reserved boot writer explicitly inline. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: accept generic sector storage in reserved boot writer. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: accept typed reserved boot-sector pointer. 230/222 instructions; 122 differing positions.

## Initialization and callback pointer data full gate

Initialization uses separate flag reads and tests insertion booleans for nonzero, as the target does. Explicit null callback initializers emit attach then detach in declaration order at small-data offsets 0 and 4. No objects or alignment directives were added. Exact count stays 19/26; initialization improves 90.27778 to 92.326385.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8284/11752 data 408/3592 functions 19/26 fuzzy 98.5769 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 19/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.57692
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 96.818184
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.84158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 6940/11752 data 408 functions 15 fuzzy 98.1395
regressions vs baseline: 0
global matched_code_percent: 85.68883 -> 85.73370
global fuzzy_match_percent: 98.59454 -> 98.59624
global complete_code_percent: 59.86180 -> 59.86180
global matched_data_percent: 90.85581 -> 90.85581
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_get_total_sectors: shift unsigned word for decoded read block size. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: shift unsigned word for sector multiplier factor. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: shift unsigned words for both capacity factors. 80/80 instructions; 10 differing positions.
- pfd_sddrv_store_mbr_buf: calculate ending cylinder before starting cylinder. 202/202 instructions; 20 differing positions.
- pfd_sddrv_store_mbr_buf: cache starting and ending LBA for CHS conversion. 202/202 instructions; 30 differing positions.
- pfd_sddrv_store_mbr_buf: calculate cylinder-relative heads before sector coordinates. 202/202 instructions; 22 differing positions.

## Final audit

Every initially open function has at least three distinct compiled source attempts in this log. Four functions became exact: physical read, physical write, insertion callback, and unmount. The remaining seven have 3 to 14 attempts each. Experiments outside the retained improvements were restored.

The FAT32 builder was checked against target blocks: calculation, BPB writes, FSInfo writes, inline reserved-sector writer, reserved writes, MBR write, and epilogue. Its eight extra instructions come from null validation and error-result dispatch in the reserved-sector helper. The target retains an unreachable report tail while omitting the validation and report argument setup. Positive branch, common status return, explicit inline, typed storage, field writer, and address validation variants did not reproduce that optimization. No artificial dead code or missing behavior was added.

Remaining evidence:
- pfd_st_removal_callback, 96.818184%: 66/66 instructions, three differences. Device presence load moves before the insertion-state store and takes a different zero register.
- pfd_sddrv_init, 92.326385%: 144/144 instructions, 31 positional differences. Null comparison and branchless existing-disk status selection differ; device/insertion and disk/flags store ordering also differs. Target media truth tests and distinct flags reads are retained.
- pfd_sddrv_finalize, 92.63158%: 57/57 instructions, four differences. Final flag-mask register and insertion-state store scheduling differ. Target preserves the ejection field; source now preserves it too.
- pfd_sddrv_get_disk_info, 97.916664%: all first 96 instructions match. Source has 98 instructions; the target symbol excludes stack restoration and return. Symbol configuration remains untouched; extracted symbol boundary is unresolved.
- pfd_sddrv_get_total_sectors, 96.9875%: 80/80 instructions, ten differences in CSD multiplier temporary registers and constant scheduling.
- pfd_sddrv_store_mbr_buf, 95.84158%: 202/202 instructions, twenty differences in CHS division scheduling and temporary registers.
- pfd_sddrv_build_fat32_mbr_bpb, 94.75225%: 230/222 instructions, inline reserved-sector validation and error tail differ.

Data payload and attribution audit follows. `.rodata` is completely identical, including the function table and fourteen size records. All 46 string payloads and offsets are identical. Explicit callback initialization fixes declaration order without adding storage. `.bss` raw zero payload is identical; the driver record symbol is four bytes shorter than the extracted original symbol. `.data` lacks two terminal alignment zeros. `.sbss` has a different event offset and lacks the extracted alignment interval, although objdiff normalizes it to 100%. The original alignment and rounded record boundary cannot be established from these accesses. No padding members, filler strings, artificial objects, or forced alignment were added.

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
pfd_sddrv_get_total_sectors: 96.9875%; src 0x140 base 0x140 insns 80/80; diffs 10: [48, 52, 54, 55, 56, 57, 58, 59, 60, 62]
pfd_sddrv_store_mbr_buf: 95.84158%; src 0x328 base 0x328 insns 202/202; diffs 20: [59, 61, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 82]
pfd_sddrv_build_fat32_mbr_bpb: 94.75225%; src 0x398 base 0x378 insns 230/222; --- replace mine 24:25 base 24:25
```

Full non-quick gate rebuilt all four owned units from scratch and passed with zero exact regressions, forbidden additions, and readability additions. All five gate blocks, including the initial quick baseline, are copied verbatim into sd-driver-round3-gates.txt.

Before -> after:
- pfd_cmn: instruction-exact 1/1 -> 1/1, code 280/280 -> 280/280, data None -> None, fuzzy 100.0000 -> 100.0000.
- nand_drv: instruction-exact 18/18 -> 18/18, code 6952/6952 -> 6952/6952, data 5696/5696 -> 5696/5696, fuzzy 100.0000 -> 100.0000.
- msc_drv: instruction-exact 2/2 -> 2/2, code 20/20 -> 20/20, data 8/8 -> 8/8, fuzzy 100.0000 -> 100.0000.
- sd_drv: instruction-exact 15/26 -> 19/26, code 6940/11752 -> 8284/11752, data 408/3592 -> 408/3592, fuzzy 98.1395 -> 98.5769.
