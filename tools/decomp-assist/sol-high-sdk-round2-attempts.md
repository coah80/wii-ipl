# SDK round 2 matching attempts

Baseline: bc6d67e3. Source remains NonMatching. Full gate output is in sol-high-sdk-round2-gates.txt.

## VI data

Target filter payload contains 25 u16 taps and three complete 60-byte PAL progressive GXRenderModeObj records. The records were missing, moving all seven later strings 184 bytes earlier.

1. Separate static GX mode records: compiler discarded unreferenced records; restored.
2. Separate public GX mode records: compiler emitted them after private data; pool offsets unchanged; restored.
3. Typed filter/mode aggregate: string offsets corrected; standalone aggregate alignment moved taps four bytes; superseded.
4. Array of filter/mode configurations: same aggregate alignment; superseded.
5. Hardware configuration groups the eleven timing records with the filter/mode aggregate. Natural member alignment matches all target payload bytes and pool offsets, without explicit padding or forced retention. Retained. VIInit objdiff 85.06213 -> 86.2929; exact count 18/30 unchanged. Raw .data is identical (1368 bytes); objdiff .data symbol association remains below 100%. Other raw VI data sections match their common bytes; source small sections omit natural trailing zero alignment.

## WAD small-data pool and file enumeration

WADOpenStream now visits the write branch first, pooling r+ before r. _WADBackupGetFiles was rebuilt block by block from its 317 target instructions: path construction uses strcmp against dot, absolute/relative branches pool %s/%s before %s, filters precede file opening, failures take per-name cleanup, and recursion advances a real header cursor. Instructions now 317/317; objdiff 46.195583 -> 96.01893. _WADCleanTmpDir target extension is app, not tmp. Raw .data/.sdata bytes now match, with only natural .data trailing alignment shorter in source. The full gate preserves all 23 exact functions and raises WAD fuzzy 80.82155 -> 83.43771.

VIFlush retains an explicit local register mask (78.91304 -> 81.23189); setHorizontalRegs caches the pending mask (62.232143 -> 67.14286). SD finalize chained media-state clearing improves 92.87719 -> 92.89474. Full three-unit gate passes with zero regressions; exact counts unchanged. Detailed per-function trials are recorded below when the round finishes.

SD CSD multiplier selection uses conditional expressions (90.9375 -> 96.9875, instructions 80/80). VI shutdown uses the same explicit shift-mask temporary as the flush path (81.039604 -> 82.623764). Full two-unit gate passes; no exact regression.

NUP reuses the existing installed-content helper for size calculation, initializes response outputs before loading the TMD view, accumulates request lengths in target call order, uses a signed content index, and checks boot import errors before common cleanup. Full NUP gate passes, fuzzy 82.30807 -> 82.932365; data remains 1720/1720 and exact remains 13/23.

SD format lookup blocks retain cached requested sector counts where they improve the target load schedule. Initialization compares the stored insertion boolean to one, matching the target branch. Full gate raises SD fuzzy 94.79272 -> 95.27297, exact remains 10/26.

WADBackupEx header and final signature blocks now follow the target: write a placeholder header, fill savedata identity and transfer MAC, call export with real metadata arguments, use aligned typed heap certificate records, validate stream size and seek before signing output. Target out-of-line transfer initializer boundary is preserved. Full WAD gate passes; fuzzy 83.43771 -> 85.42286. The gate review note at backupAreaLen != totalSize + 0x340 is integer size arithmetic, not a pointer offset. Copied-file-header/encryption-buffer reconstruction was compiled but restored after a fuzzy decrease and remains open.

NUP __nupGetContentFull reaches instruction-exact 100%, 88/88 instructions, diffs 0, after declaring the persistent URL before response outputs and separating URL/alignment declarations from assignments. __nupGetServerInfo reaches 99.793106%, 145/145, four call-scheduling/register differences; XML title arguments now match boot/system-menu/current-title order. Full NUP gate: 13 -> 14 exact, code 2840 -> 3192, data 1720/1720.

## Final round verification

Final full gate rebuilt all four units from scratch: PASS, zero baseline-exact regressions, zero forbidden additions, zero readability additions. All four units remain NonMatching; code/data are still partial. Every original function body exists in object order (26 SD, 40 WAD, 30 VI, 23 NUP); no order inversions.

Strict pool audit includes both string contents and offsets: SD 46/46, WAD 18/18, VI 7/7, NUP 28/28 identical. VI no longer has the 184-byte offset gap. NUP __nupGetContentFull is objdiff 100%, ctxdiff instructions 88/88 and diffs 0.

Final changes also advance WAD file offsets past the real WADFileHeader, use the target signed content index, converge unpack/hash errors on the target return blocks, and separate the NUP version parse-end/range branches. Transfer-ID helper reads 32 bytes, so its actual stack buffer is 32 bytes and only the six-byte MAC field is copied. This correctness fix compiled to the same aligned stack layout; it is retained despite no score change.

179 compiled trials are preserved below, including data experiments; three build failures are recorded separately. Every one of the 55 baseline nonmatching functions has at least three distinct compiled source-level attempts in this round. One is now exact; 54 remain open. Restored trials do not appear in the source diff. Scores are objdiff percentages; instruction counts/diffs are relocation-resolved normalized comparisons.

## Data audit and limits

| Unit | Section | Source / original bytes | Common byte differences | Remaining issue |
| --- | --- | ---: | ---: | --- |
| SD | .data | 2574 / 2576 | 0 | Trailing alignment and symbol association; objdiff 99.96117% |
| SD | .rodata | 368 / 368 | 0 | Objdiff 100% |
| SD | .bss | 608 / 608 | 0 | Driver-info symbol 28 vs 32 bytes, following globals already at target offsets; objdiff 97.36842% |
| SD | .sbss | 12 / 40 | 0 | Zero storage/order/gaps differ; objdiff 100% |
| WAD | .data | 458 / 464 | 0 | Natural trailing alignment and symbol association; objdiff 99.34924% |
| WAD | .sdata | 64 / 64 | 0 | Objdiff 100% |
| VI | .data | 1368 / 1368 | 0 | Raw payload exact; aggregate/original-label association gives objdiff 3.5053554% |
| VI | .sdata | 29 / 32 | 0 | Trailing zero alignment; objdiff 100% |
| VI | .sbss | 168 / 176 | 0 | Zero-storage symbol order/gaps differ; objdiff 90.243904% |
| VI | .bss | 368 / 368 | 0 | Objdiff 100% |
| NUP | .data | 1592 / 1592 | 0 | Objdiff 100% |
| NUP | .rodata | 86 / 88 | 0 | Trailing zero alignment; objdiff 100% |
| NUP | .sdata | 25 / 32 | 0 | Trailing zero alignment; objdiff 100% |
| NUP | .sbss | 4 / 8 | 0 | Trailing zero storage; objdiff 100% |

Raw common-byte comparisons are an additional check, not a claim that every section is instruction/data-exact in objdiff. No padding, force-active entry, new address label, symbol-size/config change, or shared-header change was added.

VI target bytes decode as three complete PAL progressive GX render modes. The hardware aggregate is a source-level reconstruction with natural field alignment, not proof of the original declaration grouping. Individual unreferenced static definitions were discarded and separate public definitions landed later; those experiments were restored. Original declaration ownership/grouping and small-zero-storage ordering remain uncertain.

Gate review note at backupAreaLen != totalSize + 0x340 refers to integer lengths; it is not pointer arithmetic into a blob. Certificate access uses a typed record after the runtime alignment present in the target, then named fields.

## Unit results

libs/RVL_SDK/src/fa/driver/sd_drv: exact 10 -> 10; code 2100 -> 2100/11752; data 408 -> 408/3592; fuzzy 94.627640 -> 95.272970.
libs/RVL_SDK/src/wad/wad: exact 23 -> 23; code 7080 -> 7080/24500; data 0 -> 64/528; fuzzy 80.821550 -> 85.703674.
libs/RVL_SDK/src/vi/vi: exact 18 -> 18; code 2084 -> 2084/11296; data 400 -> 400/1944; fuzzy 85.151560 -> 85.512390.
libs/RVL_SDK/src/nup/nup: exact 13 -> 14; code 2840 -> 3192/10764; data 1720 -> 1720/1720; fuzzy 82.308070 -> 83.114456.

## Remaining functions

pfd_st_inter_callback: 93.840576%; instructions 65/69, diffs 55; inlined drive lookup and callback register assignment.
pfd_st_removal_callback: 90.303030%; instructions 62/66, diffs 53; inlined drive lookup and callback scheduling.
pfd_sddrv_init: 90.277780%; instructions 144/144, diffs 86; callback argument registers and media-status branch scheduling.
pfd_sddrv_unmount: 90.000000%; instructions 12/13, diffs 9; mount-bit helper load and mask allocation.
pfd_sddrv_finalize: 92.894740%; instructions 58/57, diffs 19; inlined mount-bit clearing and error-return scheduling.
pfd_sddrv_get_disk_info: 97.916664%; instructions 98/96, diffs 2; original symbol ends before final two epilogue instructions; config unchanged.
pfd_sddrv_physical_read: 99.921260%; instructions 127/127, diffs 2; two register-allocation differences in aligned read arguments.
pfd_sddrv_physical_write: 99.921260%; instructions 127/127, diffs 2; two register-allocation differences in aligned write arguments.
pfd_sddrv_get_total_sectors: 96.987500%; instructions 80/80, diffs 10; CSD multiplier min/max registers and conditional selection scheduling.
pfd_sddrv_calc_mbr_bpb: 92.699425%; instructions 171/173, diffs 89; nested reserved-sector convergence loops and register lifetimes.
pfd_sddrv_store_bpb_buf: 99.834860%; instructions 327/327, diffs 12; serial-field aligned store instruction selection and literal-copy scheduling.
pfd_sddrv_store_mbr_buf: 95.163370%; instructions 202/202, diffs 46; CHS arithmetic scheduling and byte-store grouping.
pfd_sddrv_calc_fat32_mbr_bpb: 89.947365%; instructions 132/133, diffs 54; FAT convergence loop countdown and sector reload scheduling.
pfd_sddrv_store_fat32_mbr_buf: 78.285030%; instructions 208/207, diffs 197; CHS widths and endian-store scheduling.
pfd_sddrv_store_fat32_bpb_buf: 96.929730%; instructions 374/370, diffs 354; endian and literal-copy blocks still emit excess instructions.
pfd_sddrv_build_fat32_mbr_bpb: 94.752250%; instructions 230/222, diffs 122; media-state checks and inlined reserved-sector helper branches.
WADImportGetBlocks: 76.889260%; instructions 262/298, diffs 288; inlined mask traversal, block arithmetic and stack-local layout.
WAD_815BFFA8: 97.177420%; instructions 62/62, diffs 30; thread-loop callee-saved register allocation.
WADImportEx: 72.739970%; instructions 1131/1146, diffs 1110; stream/unpack stack offsets, inlined mask traversal and cleanup scheduling.
WAD_815C1288: 96.393440%; instructions 61/61, diffs 34; thread-loop register allocation and result scheduling.
WADBackupEx: 67.812614%; instructions 896/1062, diffs 1042; copied-file-header/encryption blocks, export stack layout and cleanup paths remain different.
_WADCheckContents: 96.705880%; instructions 85/85, diffs 19; nested content search register assignment.
WADOpenStream: 88.522170%; instructions 199/203, diffs 173; NAND extension loop, return scheduling and handle addressing.
_WADUnpackBackup: 95.840706%; instructions 115/113, diffs 57; section-size reloads and allocation ordering.
_WADGetCidxCount: 95.050000%; instructions 40/40, diffs 25; four-bit unrolled mask traversal register allocation; retained to preserve inlined consumers.
_WADGetCidx: 99.142860%; instructions 56/56, diffs 8; four-bit cumulative index register assignment.
_WADBackupGetFiles: 96.018930%; instructions 317/317, diffs 99; same target instruction count; directory cursor, frame locals and callee-saved registers differ.
_WADBackupGetSize: 86.774190%; instructions 161/155, diffs 155; content loop arithmetic and output-pointer scheduling.
_WADRandPad: 87.307690%; instructions 89/91, diffs 62; partial-word byte-copy loop and random-expression scheduling.
WAD_815C43E0: 97.177420%; instructions 62/62, diffs 30; thread-loop callee-saved register allocation.
_WADHash: 88.891754%; instructions 193/194, diffs 166; one missing instruction; threaded buffer ownership and result-join register lifetimes differ.
WADVerify: 86.863945%; instructions 133/147, diffs 131; hash/digest workspace offsets and original dormant cleanup blocks.
WADImportDVDExForBS: 89.330795%; instructions 259/263, diffs 245; inlined mask traversal and boot-import workspace offsets.
OnShutdown: 82.623764%; instructions 97/101, diffs 48; shift-mask loop and shutdown-return scheduling still differ.
__VIRetraceHandler: 88.813960%; instructions 501/516, diffs 407; interrupt context stack frame and vertical polling/acknowledgement scheduling.
__VIInit: 87.469696%; instructions 121/132, diffs 122; original stack-backed TV initialization loop and scan register scheduling.
VIInit: 86.292900%; instructions 332/338, diffs 193; hardware payload now correct; scan/field locals and hardware initialization scheduling differ.
VIWaitForRetrace: 90.476190%; instructions 21/21, diffs 2; two save/load instructions scheduled in the opposite order.
setFbbRegs: 79.419540%; instructions 160/174, diffs 74; inlined framebuffer parity/address control flow and alias-dependent reloads.
setHorizontalRegs: 67.142860%; instructions 47/56, diffs 55; compiler merges repeated changed-mask load/store pairs.
setVerticalRegs: 57.950497%; instructions 81/101, diffs 89; compiler merges repeated changed-mask stores and blanking arithmetic.
VIConfigure: 74.825390%; instructions 423/441, diffs 367; inlined register helpers and scan/TV decision scheduling.
VIConfigurePan: 88.807510%; instructions 208/213, diffs 194; inlined register helpers and timing-pointer scheduling.
VIFlush: 81.231890%; instructions 69/69, diffs 24; leading-zero/mask-loop register allocation and initial state scheduling.
__VIDisplayPositionToXY: 82.624115%; instructions 140/141, diffs 109; one missing instruction plus half-line bound scheduling.
__nupParseServerInfo__FP14NUPContextInfoPcPcUx: 62.991150%; instructions 463/452, diffs 434; tag-helper inlining and parsed-title stack/register allocation.
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc: 99.793106%; instructions 145/145, diffs 4; four register/call scheduling differences; instruction count and title arguments match.
__nupBase64Encode__FPUcPUcUl: 71.619050%; instructions 59/63, diffs 41; alphabet reloads and partial-group output control flow.
__nupGetAuditData__FP14NUPContextInfoPPc: 91.741806%; instructions 236/244, diffs 160; encoded-length helper inlining and audit stack/register scheduling.
__nupGetBootVersion__FP14ESTitleVersion: unscored; instructions 153/163, diffs 101; unscored original one-argument symbol metadata versus observed two-argument ABI; content-search instructions also differ.
__nupGetTitleSize__FP12NUPTitleInfo: 79.410070%; instructions 134/139, diffs 114; installed-content search and 64-bit block rounding scheduling.
__nupGetContentIncr__FP14NUPContextInfoP12NUPTitleInfoPc: 90.903510%; instructions 109/114, diffs 105; installed-content helper inlining and import-error cleanup scheduling.
__nupUpdateTitle__FP14NUPContextInfoP12NUPTitleInfoPcPc: 96.444440%; instructions 135/135, diffs 23; NAND free-block comparison and shared error-return scheduling.
__nupOp: 90.413240%; instructions 422/438, diffs 391; boot/IOS/menu search and update loop scheduling; 16 target instructions remain unmatched.

## Per-function attempts

### pfd_st_inter_callback

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 93.840576; instructions 65/69, diffs 55. inlined drive lookup and callback register assignment.

1. take positive status branch and let callback fall through common zero return: objdiff 93.840576 -> 85.91304; instructions [65, 69] -> [62, 69]; diffs 55 -> 66; restored.
2. save media notification disk locally after drive update: objdiff 93.840576 -> 93.840576; instructions [65, 69] -> [65, 69]; diffs 55 -> 55; restored.
3. callback drive char widened to signed int before user callback: objdiff 93.840576 -> 93.840576; instructions [65, 69] -> [65, 69]; diffs 55 -> 55; restored.

### pfd_st_removal_callback

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 90.30303; instructions 62/66, diffs 53. inlined drive lookup and callback scheduling.

1. take positive status branch and let callback fall through common zero return: objdiff 90.30303 -> 82.257576; instructions [62, 66] -> [59, 66]; diffs 53 -> 63; restored.
2. save media notification disk locally after drive update: objdiff 90.30303 -> 90.30303; instructions [62, 66] -> [62, 66]; diffs 53 -> 53; restored.
3. callback drive char widened to signed int before user callback: objdiff 90.30303 -> 90.30303; instructions [62, 66] -> [62, 66]; diffs 53 -> 53; restored.

### pfd_sddrv_init

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 90.27778; instructions 144/144, diffs 86. callback argument registers and media-status branch scheduling.

1. mounted device local is reloaded from driver before handler registration: objdiff 86.104164 -> 86.104164; instructions [143, 144] -> [143, 144]; diffs 138 -> 138; restored.
2. already-initialized disk result is selected by conditional expression: objdiff 86.104164 -> 86.104164; instructions [143, 144] -> [143, 144]; diffs 138 -> 138; restored.
3. test insertion flag explicitly equals one after device status read: objdiff 86.104164 -> 90.27778; instructions [143, 144] -> [144, 144]; diffs 138 -> 86; retained at that checkpoint.

### pfd_sddrv_unmount

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 90.0; instructions 12/13, diffs 9. mount-bit helper load and mask allocation.

1. test mount bit after right shift as target condition block: objdiff 90.0 -> 85.76923; instructions [12, 13] -> [12, 13]; diffs 9 -> 9; restored.
2. clear mounted state through explicit flag subtraction on mounted path: objdiff 90.0 -> 85.76923; instructions [12, 13] -> [12, 13]; diffs 9 -> 9; restored.
3. unsigned flag shift comparison in early no-mount return: objdiff 90.0 -> 65.0; instructions [12, 13] -> [14, 13]; diffs 9 -> 9; restored.

### pfd_sddrv_finalize

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 92.89474; instructions 58/57, diffs 19. inlined mount-bit clearing and error-return scheduling.

1. clear mount flag by decrement within mounted branch: objdiff 92.87719 -> 91.91228; instructions [58, 57] -> [58, 57]; diffs 19 -> 19; restored.
2. zero initialization expressed as chained media and disk state assignments: objdiff 92.87719 -> 92.89474; instructions [58, 57] -> [58, 57]; diffs 19 -> 19; retained at that checkpoint.
3. initialized flag explicitly equals one rather than truthy bit test: objdiff 92.89474 -> 90.96491; instructions [58, 57] -> [59, 57]; diffs 19 -> 51; restored.

### pfd_sddrv_get_disk_info

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 97.916664; instructions 98/96, diffs 2. original symbol ends before final two epilogue instructions; config unchanged.

1. return successful geometry helper result instead of new zero constant: objdiff 97.916664 -> 96.875; instructions [98, 96] -> [97, 96]; diffs 2 -> 20; restored.
2. group geometry halfword zeros separately from format pointer: objdiff 97.916664 -> 93.75; instructions [98, 96] -> [98, 96]; diffs 2 -> 4; restored.
3. media type check factors both memory-card status bits into one mask: objdiff 97.916664 -> 95.208336; instructions [98, 96] -> [96, 96]; diffs 2 -> 45; restored.

### pfd_sddrv_physical_read

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 99.92126; instructions 127/127, diffs 2. two register-allocation differences in aligned read arguments.

1. initialize current sector with loop variables and use original sector for aligned calls: objdiff 99.92126 -> 98.34646; instructions [127, 127] -> [127, 127]; diffs 2 -> 43; restored.
2. use additive sector advance with independent completion index: objdiff 99.92126 -> 99.92126; instructions [127, 127] -> [127, 127]; diffs 2 -> 2; restored.
3. descending outstanding-block loop preserves current-sector call argument lifetime: objdiff 99.92126 -> 95.90551; instructions [127, 127] -> [129, 127]; diffs 2 -> 84; restored.

### pfd_sddrv_physical_write

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 99.92126; instructions 127/127, diffs 2. two register-allocation differences in aligned write arguments.

1. initialize current sector with loop variables and use original sector for aligned calls: objdiff 99.92126 -> 98.34646; instructions [127, 127] -> [127, 127]; diffs 2 -> 43; restored.
2. use additive sector advance with independent completion index: objdiff 99.92126 -> 99.92126; instructions [127, 127] -> [127, 127]; diffs 2 -> 2; restored.
3. descending outstanding-block loop preserves current-sector call argument lifetime: objdiff 99.92126 -> 95.90551; instructions [127, 127] -> [129, 127]; diffs 2 -> 84; restored.

### pfd_sddrv_get_total_sectors

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 96.9875; instructions 80/80, diffs 10. CSD multiplier min/max registers and conditional selection scheduling.

1. conditional maximum/minimum expressions mirror two multiplier selection blocks: objdiff 90.9375 -> 96.9875; instructions [79, 80] -> [80, 80]; diffs 43 -> 10; retained at that checkpoint.
2. store shifted CSD block length as unsigned halfword before multiplying: objdiff 96.9875 -> 94.2375; instructions [80, 80] -> [81, 80]; diffs 10 -> 39; restored.
3. compute final CSD multiplier by shift instead of multiplication: objdiff 96.9875 -> 95.25; instructions [80, 80] -> [77, 80]; diffs 10 -> 26; restored.

### pfd_sddrv_calc_mbr_bpb

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 92.699425; instructions 171/173, diffs 89. nested reserved-sector convergence loops and register lifetimes.

1. target lookup block caches total sector count before loop initialization: objdiff 91.76878 -> 92.699425; instructions [171, 173] -> [171, 173]; diffs 85 -> 89; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 92.699425 -> 90.47399; instructions [171, 173] -> [167, 173]; diffs 89 -> 151; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 92.699425 -> 87.93642; instructions [171, 173] -> [164, 173]; diffs 89 -> 165; restored.

### pfd_sddrv_store_bpb_buf

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 99.83486; instructions 327/327, diffs 12. serial-field aligned store instruction selection and literal-copy scheduling.

1. target lookup block caches total sector count before loop initialization: objdiff 99.34251 -> 99.83486; instructions [327, 327] -> [327, 327]; diffs 8 -> 12; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 99.83486 -> 98.65749; instructions [327, 327] -> [323, 327]; diffs 12 -> 304; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 99.83486 -> 97.923546; instructions [327, 327] -> [322, 327]; diffs 12 -> 289; restored.

### pfd_sddrv_store_mbr_buf

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 95.16337; instructions 202/202, diffs 46. CHS arithmetic scheduling and byte-store grouping.

1. target lookup block caches total sector count before loop initialization: objdiff 94.36633 -> 95.16337; instructions [202, 202] -> [202, 202]; diffs 42 -> 46; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 95.16337 -> 93.25742; instructions [202, 202] -> [198, 202]; diffs 46 -> 181; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 95.16337 -> 91.40099; instructions [202, 202] -> [197, 202]; diffs 46 -> 166; restored.

### pfd_sddrv_calc_fat32_mbr_bpb

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 89.947365; instructions 132/133, diffs 54. FAT convergence loop countdown and sector reload scheduling.

1. target lookup block caches total sector count before loop initialization: objdiff 89.909775 -> 89.947365; instructions [132, 133] -> [132, 133]; diffs 55 -> 54; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 89.947365 -> 86.33835; instructions [132, 133] -> [128, 133]; diffs 54 -> 113; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 89.947365 -> 83.827065; instructions [132, 133] -> [125, 133]; diffs 54 -> 125; restored.

### pfd_sddrv_store_fat32_mbr_buf

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 78.28503; instructions 208/207, diffs 197. CHS widths and endian-store scheduling.

1. target lookup block caches total sector count before loop initialization: objdiff 77.50725 -> 78.28503; instructions [208, 207] -> [208, 207]; diffs 196 -> 197; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 78.28503 -> 76.42512; instructions [208, 207] -> [204, 207]; diffs 197 -> 199; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 78.28503 -> 73.85507; instructions [208, 207] -> [203, 207]; diffs 197 -> 199; restored.

### pfd_sddrv_store_fat32_bpb_buf

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 96.92973; instructions 374/370, diffs 354. endian and literal-copy blocks still emit excess instructions.

1. target lookup block caches total sector count before loop initialization: objdiff 96.4946 -> 96.92973; instructions [374, 370] -> [374, 370]; diffs 353 -> 354; retained at that checkpoint.
2. copy settings from selected table record pointer rather than recalculated array index: objdiff 96.92973 -> 95.88919; instructions [374, 370] -> [370, 370]; diffs 354 -> 345; restored.
3. lookup error dispatch returns literal failure directly as target status block: objdiff 96.92973 -> 94.9973; instructions [374, 370] -> [367, 370]; diffs 354 -> 355; restored.

### pfd_sddrv_build_fat32_mbr_bpb

Unit: libs/RVL_SDK/src/fa/driver/sd_drv. Final objdiff: 94.75225; instructions 230/222, diffs 122. media-state checks and inlined reserved-sector helper branches.

1. format workspace initialized by its actual typed size: objdiff 94.75225 -> 94.75225; instructions [230, 222] -> [230, 222]; diffs 122 -> 122; restored.
2. boot and duplicate sector writes compute sector through one advancing local: objdiff 94.75225 -> 94.75225; instructions [230, 222] -> [230, 222]; diffs 122 -> 122; restored.
3. inverted ejected state branch returns failure before missing-media test: objdiff 94.75225 -> 94.53603; instructions [230, 222] -> [230, 222]; diffs 122 -> 130; restored.

### WADImportGetBlocks

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 76.88926; instructions 262/298, diffs 288. inlined mask traversal, block arithmetic and stack-local layout.

1. selected content pointer indexed through real metadata array member: objdiff 76.55369 -> 76.55369; instructions [263, 298] -> [263, 298]; diffs 288 -> 288; restored.
2. file offset advances over actual 128-byte file header before aligned payload: objdiff 76.55369 -> 76.88926; instructions [263, 298] -> [262, 298]; diffs 288 -> 288; retained at that checkpoint.
3. header reader initializes buffer pointer immediately before stream use: objdiff 76.88926 -> 75.85235; instructions [262, 298] -> [262, 298]; diffs 288 -> 290; restored.

### WAD_815BFFA8

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 97.17742; instructions 62/62, diffs 30. thread-loop callee-saved register allocation.

1. increment ring index with modulo two instead of xor: objdiff 97.17742 -> 94.91936; instructions [62, 62] -> [63, 62]; diffs 30 -> 40; restored.
2. decrement remaining transfer bytes before condition signal: objdiff 97.17742 -> 90.72581; instructions [62, 62] -> [62, 62]; diffs 30 -> 32; restored.
3. outer loop explicit breaks retain producer-consumer wait blocks: compiler rejected; restored.
4. explicit break after loop locals retains transfer producer-consumer blocks: objdiff 97.17742 -> 82.5; instructions [62, 62] -> [62, 62]; diffs 30 -> 47; restored.

### WADImportEx

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 72.73997; instructions 1131/1146, diffs 1110. stream/unpack stack offsets, inlined mask traversal and cleanup scheduling.

1. use signed metadata content count for per-title content traversal: objdiff 72.73386 -> 72.73997; instructions [1131, 1146] -> [1131, 1146]; diffs 1110 -> 1110; retained at that checkpoint.
2. installed-content count declaration zeroed after import workspace setup: objdiff 72.73997 -> 72.71466; instructions [1131, 1146] -> [1132, 1146]; diffs 1110 -> 1124; restored.
3. chunk upper bound initializes to available transfer chunk then caps by remaining data: objdiff 72.73997 -> 72.534904; instructions [1131, 1146] -> [1130, 1146]; diffs 1110 -> 1116; restored.

### WAD_815C1288

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 96.39344; instructions 61/61, diffs 34. thread-loop register allocation and result scheduling.

1. increment ring index with modulo two instead of xor: objdiff 96.39344 -> 93.85246; instructions [61, 61] -> [62, 61]; diffs 34 -> 45; restored.
2. decrement remaining transfer bytes before condition signal: objdiff 96.39344 -> 89.83607; instructions [61, 61] -> [61, 61]; diffs 34 -> 36; restored.
3. outer loop explicit breaks retain producer-consumer wait blocks: compiler rejected; restored.
4. explicit break after loop locals retains transfer producer-consumer blocks: objdiff 96.39344 -> 81.55738; instructions [61, 61] -> [61, 61]; diffs 34 -> 48; restored.

### WADBackupEx

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 67.812614; instructions 896/1062, diffs 1042. copied-file-header/encryption blocks, export stack layout and cleanup paths remain different.

1. re-derived placeholder/header blocks 2050-22ec: transfer MAC and savedata title, export ABI, random seed and metadata padding: objdiff 59.089455 -> 66.38795; instructions [909, 1062] -> [896, 1062]; diffs 1049 -> 1043; retained at that checkpoint.
2. re-derived file blocks 2708-2890: real copied file header, header IV and source/destination encryption buffers: objdiff 66.38795 -> 66.0951; instructions [896, 1062] -> [900, 1062]; diffs 1043 -> 1042; restored.
3. re-derived final blocks 2a3c-2bf4: heap certificate records aligned to 64 bytes, size validation, signature seek and output size: objdiff 66.38795 -> 66.801315; instructions [896, 1062] -> [910, 1062]; diffs 1043 -> 1043; retained at that checkpoint.
4. retain target out-of-line transfer initializer boundary instead of six inlined OS initializer calls: objdiff 66.801315 -> 67.812614; instructions [910, 1062] -> [896, 1062]; diffs 1043 -> 1042; retained at that checkpoint.
5. transfer-ID buffer uses the 32-byte size read by the real helper; copy only six MAC bytes into header: objdiff 67.812614 -> 67.812614; instructions [896, 1062] -> [896, 1062]; diffs 1042 -> 1042; restored.

### _WADCheckContents

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 96.70588; instructions 85/85, diffs 19. nested content search register assignment.

1. count installed IDs down while pointer advances in each private-content search: objdiff 96.70588 -> 91.29412; instructions [85, 85] -> [84, 85]; diffs 19 -> 60; restored.
2. separate missing required-content condition into nested type check: objdiff 96.70588 -> 96.70588; instructions [85, 85] -> [85, 85]; diffs 19 -> 19; restored.
3. explicit content-mask byte pointer for selected private contents: objdiff 96.70588 -> 96.70588; instructions [85, 85] -> [85, 85]; diffs 19 -> 19; restored.

### WADOpenStream

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 88.52217; instructions 199/203, diffs 173. NAND extension loop, return scheduling and handle addressing.

1. write branch first as target; r+ before r in small-data pool: objdiff 87.35468 -> 88.487686; instructions [200, 203] -> [199, 203]; diffs 173 -> 173; retained at that checkpoint.
2. NAND seek completion selects failure on inequality before zero success: objdiff 88.487686 -> 88.52217; instructions [199, 203] -> [199, 203]; diffs 173 -> 173; retained at that checkpoint.
3. SD stream open returns through explicit null-handle validation: objdiff 88.52217 -> 88.52217; instructions [199, 203] -> [199, 203]; diffs 173 -> 173; restored.

### _WADUnpackBackup

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 95.840706; instructions 115/113, diffs 57. section-size reloads and allocation ordering.

1. backup header version and size failure checks share validation branch: objdiff 94.867256 -> 93.00885; instructions [116, 113] -> [114, 113]; diffs 89 -> 79; restored.
2. nonzero device-read status branches directly to shared return label: objdiff 94.867256 -> 95.840706; instructions [116, 113] -> [115, 113]; diffs 89 -> 57; retained at that checkpoint.
3. initialize successful verification status before final file-section branch: objdiff 95.840706 -> 95.840706; instructions [115, 113] -> [115, 113]; diffs 57 -> 57; restored.

### _WADGetCidxCount

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 95.05; instructions 40/40, diffs 25. four-bit unrolled mask traversal register allocation; retained to preserve inlined consumers.

1. single-bit count loop tests natural compiler four-way unrolling: objdiff 95.05 -> 96.625; instructions [40, 40] -> [40, 40]; diffs 25 -> 19; restored.
2. signed bit counter gives target arithmetic right shift in count blocks: objdiff 95.05 -> 89.175; instructions [40, 40] -> [40, 40]; diffs 25 -> 28; restored.
3. count each selected bit with unsigned mask inequality rather than truth test: objdiff 95.05 -> 95.05; instructions [40, 40] -> [40, 40]; diffs 25 -> 25; restored.

### _WADGetCidx

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 99.14286; instructions 56/56, diffs 8. four-bit cumulative index register assignment.

1. constant-first remaining counter tests in each unrolled bit block: objdiff 99.14286 -> 99.14286; instructions [56, 56] -> [56, 56]; diffs 8 -> 8; restored.
2. signed remaining count follows target zero-only termination: objdiff 99.14286 -> 99.14286; instructions [56, 56] -> [56, 56]; diffs 8 -> 8; restored.
3. return explicit base-relative bit index at unrolled early returns: objdiff 99.14286 -> 99.14286; instructions [56, 56] -> [56, 56]; diffs 8 -> 8; restored.
4. natural single-bit loop lets compiler unroll increments exactly as target: objdiff 99.14286 -> 96.96429; instructions [56, 56] -> [56, 56]; diffs 8 -> 26; restored.
5. four target bit blocks increment a single bit index between tests rather than separate base offsets: objdiff 99.14286 -> 92.89286; instructions [56, 56] -> [56, 56]; diffs 8 -> 32; restored.

### _WADBackupGetFiles

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 96.01893; instructions 317/317, diffs 99. same target instruction count; directory cursor, frame locals and callee-saved registers differ.

1. re-derived all 317 target instructions: absolute/relative path blocks, filters before open, continuation cleanup, recursive paths and output cursor: objdiff 46.195583 -> 96.01893; instructions [291, 317] -> [317, 317]; diffs 296 -> 99; retained at that checkpoint.
2. declare path workspace in ascending target stack order: objdiff 96.01893 -> 95.943214; instructions [317, 317] -> [317, 317]; diffs 99 -> 122; restored.
3. initialize relative/absolute selection directly from flags after directory read: objdiff 96.01893 -> 94.37855; instructions [317, 317] -> [315, 317]; diffs 99 -> 309; restored.

### _WADBackupGetSize

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 86.77419; instructions 161/155, diffs 155. content loop arithmetic and output-pointer scheduling.

1. content alignment performed at full metadata size width before byte-count conversion: objdiff 86.77419 -> 84.69678; instructions [161, 155] -> [163, 155]; diffs 155 -> 157; restored.
2. signed selected-content loop bound uses content-mask count return type: objdiff 86.77419 -> 86.451614; instructions [161, 155] -> [161, 155]; diffs 155 -> 155; restored.
3. real file-header pointer advances with file count traversal: objdiff 86.77419 -> 84.41936; instructions [161, 155] -> [158, 155]; diffs 155 -> 147; restored.

### _WADRandPad

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 87.30769; instructions 89/91, diffs 62. partial-word byte-copy loop and random-expression scheduling.

1. combine random word through xor of disjoint bit ranges: objdiff 87.30769 -> 85.0; instructions [89, 91] -> [89, 91]; diffs 62 -> 62; restored.
2. count complete-word loop down to zero following target mtctr block: objdiff 87.30769 -> 85.57143; instructions [89, 91] -> [87, 91]; diffs 62 -> 86; restored.
3. advance destination word pointer separately after complete random word store: objdiff 87.30769 -> 87.30769; instructions [89, 91] -> [89, 91]; diffs 62 -> 62; restored.

### WAD_815C43E0

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 97.17742; instructions 62/62, diffs 30. thread-loop callee-saved register allocation.

1. increment ring index with modulo two instead of xor: objdiff 97.17742 -> 94.91936; instructions [62, 62] -> [63, 62]; diffs 30 -> 40; restored.
2. decrement remaining transfer bytes before condition signal: objdiff 97.17742 -> 90.72581; instructions [62, 62] -> [62, 62]; diffs 30 -> 32; restored.
3. outer loop explicit breaks retain producer-consumer wait blocks: compiler rejected; restored.
4. explicit break after loop locals retains transfer producer-consumer blocks: objdiff 97.17742 -> 82.5; instructions [62, 62] -> [62, 62]; diffs 30 -> 47; restored.

### _WADHash

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 88.891754; instructions 193/194, diffs 166. one missing instruction; threaded buffer ownership and result-join register lifetimes differ.

1. re-derived all 194 target instructions: shared read pointer/result slots, synchronous cleanup and threaded cancellation/join returns: objdiff 81.18041 -> 88.891754; instructions [192, 194] -> [193, 194]; diffs 185 -> 166; retained at that checkpoint.
2. advance stream offset directly after each hash chunk rather than extra completed counter: objdiff 88.891754 -> 87.04124; instructions [193, 194] -> [192, 194]; diffs 166 -> 183; restored.
3. alignment validity compares rounded size with input in target operand order: objdiff 88.891754 -> 88.78866; instructions [193, 194] -> [193, 194]; diffs 166 -> 166; restored.

### WADVerify

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 86.863945; instructions 133/147, diffs 131. hash/digest workspace offsets and original dormant cleanup blocks.

1. use selected backup signature record for both certificate copy sources: objdiff 86.863945 -> 82.37415; instructions [133, 147] -> [132, 147]; diffs 131 -> 122; restored.
2. hash input and digest completion result tested through separate blocks: objdiff 86.863945 -> 86.863945; instructions [133, 147] -> [133, 147]; diffs 131 -> 131; restored.
3. minimum signature size validated before aligned total length: objdiff 86.863945 -> 72.9864; instructions [133, 147] -> [133, 147]; diffs 131 -> 137; restored.

### WADImportDVDExForBS

Unit: libs/RVL_SDK/src/wad/wad. Final objdiff: 89.330795; instructions 259/263, diffs 245. inlined mask traversal and boot-import workspace offsets.

1. content selection pointer held before chosen content-ID branch: objdiff 89.330795 -> 88.57034; instructions [259, 263] -> [259, 263]; diffs 245 -> 245; restored.
2. content transfer size retains metadata 64-bit rounding until DVD count conversion: objdiff 89.330795 -> 87.6616; instructions [259, 263] -> [261, 263]; diffs 245 -> 231; restored.
3. minimum transfer chunk chooses available buffer first with explicit branch: objdiff 89.330795 -> 89.31179; instructions [259, 263] -> [259, 263]; diffs 245 -> 245; restored.

### OnShutdown

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 82.623764; instructions 97/101, diffs 48. shift-mask loop and shutdown-return scheduling still differ.

1. shutdown event switch re-derived from target signed event dispatch blocks: objdiff 81.039604 -> 80.88119; instructions [97, 101] -> [98, 101]; diffs 44 -> 84; restored.
2. local shift mask follows each changed-register copy in shutdown flush: objdiff 81.039604 -> 82.623764; instructions [97, 101] -> [97, 101]; diffs 44 -> 48; retained at that checkpoint.
3. last shutdown stage returns explicit retrace counter inequality: objdiff 82.623764 -> 81.28713; instructions [97, 101] -> [98, 101]; diffs 48 -> 52; restored.

### __VIRetraceHandler

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 88.81396; instructions 501/516, diffs 407. interrupt context stack frame and vertical polling/acknowledgement scheduling.

1. position interrupt bits share one dispatch to target position callback block: objdiff 88.81396 -> 88.14535; instructions [501, 516] -> [498, 516]; diffs 407 -> 476; restored.
2. signed dimming-device loop index follows target counter comparisons: objdiff 88.81396 -> 88.81396; instructions [501, 516] -> [501, 516]; diffs 407 -> 407; restored.
3. position callback outputs share top-level workspace declaration before context: objdiff 88.81396 -> 88.81396; instructions [501, 516] -> [501, 516]; diffs 407 -> 407; restored.

### __VIInit

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 87.469696; instructions 121/132, diffs 122. original stack-backed TV initialization loop and scan register scheduling.

1. while-loop spin count follows reset-to-release delay block: objdiff 87.469696 -> 87.469696; instructions [121, 132] -> [121, 132]; diffs 122 -> 122; restored.
2. countdown spin count tests compiler retention of original delay: objdiff 87.469696 -> 87.469696; instructions [121, 132] -> [121, 132]; diffs 122 -> 122; restored.
3. spin exits on equality after prefix counter increment: objdiff 87.469696 -> 87.469696; instructions [121, 132] -> [121, 132]; diffs 122 -> 122; restored.

### VIInit

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 86.2929; instructions 332/338, diffs 193. hardware payload now correct; scan/field locals and hardware initialization scheduling differ.

1. local filter-tap pointer addresses actual hardware configuration member: objdiff 86.2929 -> 82.49113; instructions [332, 338] -> [335, 338]; diffs 193 -> 303; restored.
2. scan-mode bit directly converted from current display configuration: objdiff 86.2929 -> 85.40533; instructions [332, 338] -> [329, 338]; diffs 193 -> 256; restored.
3. framebuffer and pan heights double active lines using natural halfword assignment truncation: objdiff 86.2929 -> 86.2929; instructions [332, 338] -> [332, 338]; diffs 193 -> 193; restored.

### VIWaitForRetrace

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 90.47619; instructions 21/21, diffs 2. two save/load instructions scheduled in the opposite order.

1. do-while retrace wait follows target sleep-before-counter-test block: objdiff 90.47619 -> 90.47619; instructions [21, 21] -> [21, 21]; diffs 2 -> 2; restored.
2. interrupt state declaration initialized by call before counter declaration: objdiff 90.47619 -> 90.47619; instructions [21, 21] -> [21, 21]; diffs 2 -> 2; restored.
3. compare unsigned retrace delta to zero in wait termination: objdiff 90.47619 -> 87.61905; instructions [21, 21] -> [21, 21]; diffs 2 -> 3; restored.

### setFbbRegs

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 79.41954; instructions 160/174, diffs 74. inlined framebuffer parity/address control flow and alias-dependent reloads.

1. shifted framebuffer indicator uses Boolean hardware enable type: objdiff 79.41954 -> 79.41954; instructions [160, 174] -> [160, 174]; diffs 74 -> 74; restored.
2. cache top framebuffer word before low and high register packing: objdiff 79.41954 -> 75.51724; instructions [160, 174] -> [159, 174]; diffs 74 -> 75; restored.
3. hardware high-address decision tests each framebuffer word by shifted high byte: objdiff 79.41954 -> 76.545975; instructions [160, 174] -> [159, 174]; diffs 74 -> 103; restored.

### setHorizontalRegs

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 67.14286; instructions 47/56, diffs 55. compiler merges repeated changed-mask load/store pairs.

1. re-derived register-mask boundaries with local changes committed after each register pair: objdiff 62.232143 -> 67.14286; instructions [49, 56] -> [47, 56]; diffs 55 -> 55; retained at that checkpoint.
2. precompute horizontal offset before PAL special-mode split: objdiff 67.14286 -> 59.464287; instructions [47, 56] -> [47, 56]; diffs 55 -> 55; restored.
3. hold split horizontal blanking values in 16-bit hardware widths: objdiff 67.14286 -> 66.42857; instructions [47, 56] -> [47, 56]; diffs 55 -> 55; restored.

### setVerticalRegs

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 57.950497; instructions 81/101, diffs 89. compiler merges repeated changed-mask stores and blanking arithmetic.

1. re-derived parity blocks 16d8-1744: compute trailing blanking before leading blanking and assign hardware widths: objdiff 57.950497 -> 53.396038; instructions [81, 101] -> [76, 101]; diffs 89 -> 92; restored.
2. scan-mode range comparison follows target subtract-two and unsigned bound: objdiff 57.950497 -> 57.950497; instructions [81, 101] -> [81, 101]; diffs 89 -> 89; restored.
3. black-screen extension shared between odd and even fields: objdiff 57.950497 -> 57.950497; instructions [81, 101] -> [81, 101]; diffs 89 -> 89; restored.

### VIConfigure

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 74.82539; instructions 423/441, diffs 367. inlined register helpers and scan/TV decision scheduling.

1. pan height selected by explicit single-field framebuffer branch before scan check: objdiff 74.82539 -> 74.78685; instructions [423, 441] -> [421, 441]; diffs 367 -> 359; restored.
2. display Y origin uses explicit non-interlaced branch and hardware truncation: objdiff 74.82539 -> 74.433105; instructions [423, 441] -> [424, 441]; diffs 367 -> 373; restored.
3. three-dimensional enable uses direct scan-mode equality: objdiff 74.82539 -> 74.82539; instructions [423, 441] -> [423, 441]; diffs 367 -> 367; restored.

### VIConfigurePan

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 88.80751; instructions 208/213, diffs 194. inlined register helpers and timing-pointer scheduling.

1. framebuffer mode checked before scan mode in height-doubling decision: objdiff 88.80751 -> 87.95305; instructions [208, 213] -> [208, 213]; diffs 194 -> 196; restored.
2. local VI mode pointer groups panning member assignments: objdiff 88.80751 -> 72.22535; instructions [208, 213] -> [204, 213]; diffs 194 -> 210; restored.
3. height calculation stores doubled value directly before position adjustment: objdiff 88.80751 -> 85.66197; instructions [208, 213] -> [212, 213]; diffs 194 -> 192; restored.

### VIFlush

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 81.23189; instructions 69/69, diffs 24. leading-zero/mask-loop register allocation and initial state scheduling.

1. compound shadow assignments preserve target separate changed-mask update blocks: objdiff 78.91304 -> 78.91304; instructions [69, 69] -> [69, 69]; diffs 20 -> 20; restored.
2. changed-register mask computed in local after copying register: objdiff 78.91304 -> 81.23189; instructions [69, 69] -> [69, 69]; diffs 20 -> 24; retained at that checkpoint.
3. changed loop exits explicitly before selecting count-leading-zero register: objdiff 81.23189 -> 70.49275; instructions [69, 69] -> [67, 69]; diffs 24 -> 57; restored.

### __VIDisplayPositionToXY

Unit: libs/RVL_SDK/src/vi/vi. Final objdiff: 82.624115; instructions 140/141, diffs 109. one missing instruction plus half-line bound scheduling.

1. equatorial half-line start expressed as three times equalization lines: objdiff 82.624115 -> 82.51773; instructions [140, 141] -> [140, 141]; diffs 109 -> 112; restored.
2. combine lower and upper active-field rejection tests in each field block: objdiff 82.624115 -> 71.6312; instructions [140, 141] -> [125, 141]; diffs 109 -> 129; restored.
3. explicit signed output conversion at horizontal pixel assignment: objdiff 82.624115 -> 82.624115; instructions [140, 141] -> [140, 141]; diffs 109 -> 109; restored.

### __nupParseServerInfo__FP14NUPContextInfoPcPcUx

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 62.99115; instructions 463/452, diffs 434. tag-helper inlining and parsed-title stack/register allocation.

1. separate version parse-end and halfword range checks as target validation blocks: objdiff 62.53761 -> 62.99115; instructions [461, 452] -> [463, 452]; diffs 432 -> 434; retained at that checkpoint.
2. explicit unsigned-halfword maximum check follows numeric version conversion: objdiff 62.99115 -> 0; instructions [463, 452] -> [462, 452]; diffs 434 -> 433; restored.
3. selected title record pointer groups parsed identity and version stores: objdiff 62.99115 -> 62.457966; instructions [463, 452] -> [459, 452]; diffs 434 -> 430; restored.

### __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 99.793106; instructions 145/145, diffs 4. four register/call scheduling differences; instruction count and title arguments match.

1. request size accumulated by sequential argument string lengths: objdiff 96.75862 -> 98.86207; instructions [147, 145] -> [146, 145]; diffs 116 -> 115; retained at that checkpoint.
2. initialize endpoint pointer from allocator call after computing endpoint size: objdiff 98.86207 -> 98.86207; instructions [146, 145] -> [146, 145]; diffs 115 -> 115; restored.
3. use explicit response copy destination before allocating reply: objdiff 98.86207 -> 98.86207; instructions [146, 145] -> [146, 145]; diffs 115 -> 115; restored.
4. declare persistent request cleanup pointer before response output initializers: objdiff 98.86207 -> 99.655174; instructions [146, 145] -> [145, 145]; diffs 115 -> 8; retained at that checkpoint.
5. restore XML title argument order from target: boot, system menu, current requested title: objdiff 99.655174 -> 99.793106; instructions [145, 145] -> [145, 145]; diffs 8 -> 4; retained at that checkpoint.
6. request size uses product area before message ID and constant as first final operand: objdiff 99.793106 -> 99.13793; instructions [145, 145] -> [145, 145]; diffs 4 -> 22; restored.

### __nupBase64Encode__FPUcPUcUl

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 71.61905; instructions 59/63, diffs 41. alphabet reloads and partial-group output control flow.

1. countdown of input bytes derives mtctr/bdnz traversal from target blocks: objdiff 71.61905 -> 67.4127; instructions [59, 63] -> [57, 63]; diffs 41 -> 62; restored.
2. for-loop input advancement after encoding as target loop-tail block: objdiff 71.61905 -> 69.52381; instructions [59, 63] -> [59, 63]; diffs 41 -> 49; restored.
3. explicit index temporaries separate alphabet loads before output stores: objdiff 71.61905 -> 67.06349; instructions [59, 63] -> [59, 63]; diffs 41 -> 48; restored.

### __nupGetAuditData__FP14NUPContextInfoPPc

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 91.741806; instructions 236/244, diffs 160. encoded-length helper inlining and audit stack/register scheduling.

1. unsigned loop counter compares owned-title count before selected flag: objdiff 91.741806 -> 90.06148; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; restored.
2. type audit record pointer as its actual record throughout signing and copies: objdiff 91.741806 -> 91.741806; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; restored.
3. audit format copied by ordinary typed field assignment before record assembly: objdiff 91.741806 -> 89.909836; instructions [236, 244] -> [234, 244]; diffs 160 -> 187; restored.

### __nupGetBootVersion__FP14ESTitleVersion

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: unscored; instructions 153/163, diffs 101. unscored original one-argument symbol metadata versus observed two-argument ABI; content-search instructions also differ.

1. boot version uses explicit unsigned-halfword upper limit comparison: objdiff 0 -> 0; instructions [153, 163] -> [152, 163]; diffs 101 -> 143; restored.
2. installed-title ID search compares source title before saved ID: objdiff 0 -> 0; instructions [153, 163] -> [153, 163]; diffs 101 -> 101; restored.
3. early null TMD guard joins shared cleanup before content enumeration: objdiff 0 -> 0; instructions [153, 163] -> [153, 163]; diffs 101 -> 101; restored.

### __nupGetTitleSize__FP12NUPTitleInfo

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 79.41007; instructions 134/139, diffs 114. installed-content search and 64-bit block rounding scheduling.

1. re-derived installed-content membership block shares existing pointer-traversal helper in definition order: objdiff 73.942444 -> 79.41007; instructions [133, 139] -> [134, 139]; diffs 114 -> 114; retained at that checkpoint.
2. schedule progress-step increment before final installed-block addition as target: objdiff 79.41007 -> 78.28777; instructions [134, 139] -> [134, 139]; diffs 114 -> 112; restored.
3. reload selected content size after updating title progress as target storage block: objdiff 79.41007 -> 75.258995; instructions [134, 139] -> [136, 139]; diffs 114 -> 113; restored.

### __nupGetContentFull__FP14NUPContextInfoP12NUPTitleInfoPcUl

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 100.0; instructions 88/88, diffs 0. instruction-exact, no remaining differences.

1. initialize response buffers before loading TMD pointer as target entry block: objdiff 94.204544 -> 96.59091; instructions [88, 88] -> [88, 88]; diffs 25 -> 22; retained at that checkpoint.
2. content ID search uses base-relative content indexing as target search block: objdiff 96.59091 -> 98.295456; instructions [88, 88] -> [89, 88]; diffs 22 -> 80; retained at that checkpoint.
3. declare URL length before aligned content transfer length: objdiff 98.295456 -> 89.943184; instructions [89, 88] -> [89, 88]; diffs 80 -> 80; restored.
4. declare persistent URL cleanup pointer before zero-initialized response outputs: objdiff 98.295456 -> 99.71591; instructions [89, 88] -> [88, 88]; diffs 80 -> 5; retained at that checkpoint.
5. declare URL and alignment lengths together before their target-order assignments: objdiff 99.71591 -> 100.0; instructions [88, 88] -> [88, 88]; diffs 5 -> 0; retained at that checkpoint.
6. use 32-bit selected content length for HTTP transfer alignment: objdiff 100.0 -> 93.52273; instructions [88, 88] -> [86, 88]; diffs 0 -> 72; restored.

### __nupGetContentIncr__FP14NUPContextInfoP12NUPTitleInfoPc

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 90.90351; instructions 109/114, diffs 105. installed-content helper inlining and import-error cleanup scheduling.

1. signed metadata content index follows target signed numContents loop comparison: objdiff 90.42105 -> 90.90351; instructions [109, 114] -> [109, 114]; diffs 105 -> 105; retained at that checkpoint.
2. content alignment remains full 64-bit addition until HTTP length conversion: objdiff 90.90351 -> 78.89474; instructions [109, 114] -> [111, 114]; diffs 105 -> 81; restored.
3. one content error cleanup block handles begin and download failures: objdiff 90.90351 -> 89.0614; instructions [109, 114] -> [107, 114]; diffs 105 -> 106; restored.

### __nupUpdateTitle__FP14NUPContextInfoP12NUPTitleInfoPcPc

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 96.44444; instructions 135/135, diffs 23. NAND free-block comparison and shared error-return scheduling.

1. import boot result tested before shared successful cleanup as target branch: objdiff 94.96296 -> 96.44444; instructions [133, 135] -> [135, 135]; diffs 88 -> 23; retained at that checkpoint.
2. stats success block computes storage fit separately before import path: objdiff 96.44444 -> 94.85185; instructions [135, 135] -> [135, 135]; diffs 23 -> 66; restored.
3. inverted zero result branch separates successful title cleanup: objdiff 96.44444 -> 96.44444; instructions [135, 135] -> [135, 135]; diffs 23 -> 23; restored.

### __nupOp

Unit: libs/RVL_SDK/src/nup/nup. Final objdiff: 90.41324; instructions 422/438, diffs 391. boot/IOS/menu search and update loop scheduling; 16 target instructions remain unmatched.

1. boot version validated before storing the halfword service version: objdiff 90.41324 -> 89.69406; instructions [422, 438] -> [424, 438]; diffs 391 -> 422; restored.
2. progress total copied from context inside the mutex-protected update block: objdiff 90.41324 -> 89.24429; instructions [422, 438] -> [422, 438]; diffs 391 -> 391; restored.
3. cache per-title required flag before checking update status: objdiff 90.41324 -> 90.401825; instructions [422, 438] -> [422, 438]; diffs 391 -> 392; restored.

## Source commits

2dc3c119 restore vi hardware mode tables and string offsets
f4c2b966 match wad path traversal and small data literals
92989130 improve vi register masks and sd finalization
bfdde76d improve sd capacity selection and vi shutdown mask
c4fab96b improve nup content searches and request sizing
80e9873f improve sd format table loads and insertion branch
a533b150 restore wad export header and signature flow
ff9cce21 match nup full content fetch and server title arguments

The final commit contains the last WAD/NUP improvements and the complete round log/gate capture.
