# fa/driver/sd_drv

Baseline 9/26. Matching vf/develop/sd_drv.c exists, but uses VFSys handles rather than this driver's single media state. Its API and error handling cannot be ported directly.

Explicit adaptations: combined physical-I/O success exits and positive partial-completion tests (127/127, two argument register differences); reordered sector/counter locals (twelve differences reduced to two); extracted aligned single/multi helpers (141/127, rejected) and separate call helpers (127/127, unchanged, rejected). Added the missing unregister diagnostic argument. Corrected full-format reset/eject state, status diagnostic and success/error return boundaries (105/117 to 117/117, seven stack offsets remain).

Three-source-variation sweep, source/target instruction counts and positional differences:

pfd_sddrv_get_disk_info:
- rotate independent local declarations: 98/96, 0 positional differences.
- normal path first, validation failure last: 98/96, 80 positional differences.
- common operation status exit: 98/96, 29 positional differences.

pfd_sddrv_physical_write:
- rotate independent local declarations: 127/127, 2 positional differences.
- normal path first, validation failure last: 127/127, 99 positional differences.
- common operation status exit: 127/127, 2 positional differences.

pfd_sddrv_physical_read:
- rotate independent local declarations: 127/127, 2 positional differences.
- normal path first, validation failure last: 127/127, 99 positional differences.
- common operation status exit: 127/127, 2 positional differences.

pfd_sddrv_full_format:
- rotate independent local declarations: 117/117, 7 positional differences.
- normal path first, validation failure last: 117/117, 78 positional differences.
- common operation status exit: 116/117, 62 positional differences.

pfd_sddrv_init:
- rotate independent local declarations: 143/144, 137 positional differences.
- normal path first, validation failure last: 143/144, 141 positional differences.
- common operation status exit: 142/144, 138 positional differences.

pfd_sddrv_finalize:
- normal path first, validation failure last: 57/57, 49 positional differences.
- common operation status exit: 57/57, 43 positional differences.
- Prior explicit helper extraction in this function: instruction stream unchanged; see adaptations above.

pfd_st_inter_callback:
- normal path first, validation failure last: 65/69, 59 positional differences.
- common operation status exit: 65/69, 51 positional differences.
- Prior explicit helper extraction in this function: instruction stream unchanged; see adaptations above.

pfd_st_removal_callback:
- normal path first, validation failure last: 62/66, 56 positional differences.
- common operation status exit: 62/66, 49 positional differences.
- Prior explicit helper extraction in this function: instruction stream unchanged; see adaptations above.

pfd_sddrv_get_total_sectors:
- rotate independent local declarations: 79/80, 42 positional differences.
- normal path first, validation failure last: 79/80, 67 positional differences.
- common operation status exit: 79/80, 42 positional differences.

pfd_sddrv_calc_fat32_mbr_bpb:
- rotate independent local declarations: 131/133, 94 positional differences.
- normal path first, validation failure last: 131/133, 122 positional differences.
- common operation status exit: 131/133, 98 positional differences.

pfd_sddrv_store_fat32_bpb_buf:
- rotate independent local declarations: 296/370, 272 positional differences.
- normal path first, validation failure last: 296/370, 282 positional differences.
- common operation status exit: 296/370, 272 positional differences.

pfd_sddrv_unmount:
- normal path first, validation failure last: 12/13, 11 positional differences.
- common operation status exit: 12/13, 8 positional differences.
- Prior explicit helper extraction in this function: instruction stream unchanged; see adaptations above.

pfd_sddrv_store_fat32_mbr_buf:
- rotate independent local declarations: 187/207, 150 positional differences.
- normal path first, validation failure last: 187/207, 176 positional differences.
- common operation status exit: 187/207, 150 positional differences.

pfd_sddrv_store_bpb_buf:
- rotate independent local declarations: 244/327, 233 positional differences.
- normal path first, validation failure last: 244/327, 233 positional differences.
- common operation status exit: 244/327, 233 positional differences.

pfd_sddrv_build_fat32_mbr_bpb:
- rotate independent local declarations: 222/222, 211 positional differences.
- normal path first, validation failure last: 222/222, 181 positional differences.
- common operation status exit: 218/222, 204 positional differences.

pfd_sddrv_store_mbr_buf:
- rotate independent local declarations: 155/202, 149 positional differences.
- normal path first, validation failure last: 155/202, 148 positional differences.
- common operation status exit: 155/202, 149 positional differences.

pfd_sddrv_calc_mbr_bpb:
- rotate independent local declarations: 239/173, 171 positional differences.
- normal path first, validation failure last: 239/173, 171 positional differences.
- common operation status exit: 239/173, 171 positional differences.

Retained targeted changes rather than generic common-return reshaping. Remaining format serializers differ in inline endian/copy expansion; calculators differ in arithmetic widths and iteration. Callback/global flag reload scheduling differs. get_disk_info has an identical 96-instruction prefix but two additional epilogue instructions. No symbol sizes changed.
