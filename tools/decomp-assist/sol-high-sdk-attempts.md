# SDK matching attempts

Baseline commit: c4f51491. Last matching source commit: 4c68814c629631198beb515e9747a8622f5145bd.

All four units remain NonMatching. This is partial matching progress, not a completion or linking claim.
All target function bodies are present in target address order. The NUP boot-version mangled-name discrepancy remains open. Both pool_diff.py and the gate report identical string sequences for every unit. A stricter offset audit finds all seven VI literals 184 bytes earlier than the target; the other three units match offsets too. VI pool placement therefore remains open.
The final full gate rebuilt 43U from scratch, checked the target DOL hash, found zero baseline-exact regressions and zero forbidden/readability additions. The full captured output is in sol-high-sdk-gate.txt.

Instruction-exact counts use the gate normalized instruction comparison; code/data bytes and fuzzy percentages use exact-name objdiff. Missing matched_data measures are displayed as zero.

## libs/RVL_SDK/src/fa/driver/sd_drv

sd_drv: exact 10 -> 10; code 2100 -> 2100/11752; data 408 -> 408/3592; fuzzy 70.5225 -> 94.6276.

### pfd_st_inter_callback

pfd_st_inter_callback: 93.840576%; instructions 65/69, diffs 55; inlined drive lookup and callback register assignment.
Compiled source-level attempts: 3.

1. explicit driver retrieval in callback rather than shared helper: objdiff 93.840576 -> 93.840576; instructions [65, 69] -> [65, 69]; diffs 55 -> 55; restored.
2. device presence tested as unsigned pointer: objdiff 93.840576 -> 93.840576; instructions [65, 69] -> [65, 69]; diffs 55 -> 55; restored.
3. split drive-present and callback-present checks: objdiff 93.840576 -> 93.840576; instructions [65, 69] -> [65, 69]; diffs 55 -> 55; restored.

### pfd_st_removal_callback

pfd_st_removal_callback: 90.303030%; instructions 62/66, diffs 53; inlined drive lookup and callback scheduling.
Compiled source-level attempts: 3.

1. explicit driver retrieval in callback rather than shared helper: objdiff 90.303030 -> 90.303030; instructions [62, 66] -> [62, 66]; diffs 53 -> 53; restored.
2. device presence tested as unsigned pointer: objdiff 90.303030 -> 90.303030; instructions [62, 66] -> [62, 66]; diffs 53 -> 53; restored.
3. split drive-present and callback-present checks: objdiff 90.303030 -> 90.303030; instructions [62, 66] -> [62, 66]; diffs 53 -> 53; restored.

### pfd_sddrv_init

pfd_sddrv_init: 86.104164%; instructions 143/144, diffs 138; mount-status branches and callback registration register allocation.
Compiled source-level attempts: 3.

1. unsigned pointer comparisons and inverted already-initialized disk branch from asm: objdiff 86.104164 -> 86.104164; instructions [143, 144] -> [143, 144]; diffs 138 -> 138; restored.
2. exact flag equality instead of nonzero mask: objdiff 86.104164 -> 84.993060; instructions [143, 144] -> [145, 144]; diffs 138 -> 137; restored.
3. store mounted device before insertion flag test as target order: objdiff 86.104164 -> 81.909720; instructions [143, 144] -> [143, 144]; diffs 138 -> 138; restored.

### pfd_sddrv_unmount

pfd_sddrv_unmount: 90.000000%; instructions 12/13, diffs 9; mount-bit helper load and mask allocation.
Compiled source-level attempts: 3.

1. explicit flag equals mount bit: objdiff 90.000000 -> 81.538460; instructions [12, 13] -> [13, 13]; diffs 9 -> 7; restored.
2. inline mount bit clear expanded: objdiff 90.000000 -> 90.000000; instructions [12, 13] -> [12, 13]; diffs 9 -> 9; restored.
3. conditional mount-bit clear through local driver pointer: compile rejected; compile failed, restored.
4. separate inline mounted-flag query from bit update: objdiff 90.000000 -> 90.000000; instructions [12, 13] -> [12, 13]; diffs 9 -> 9; restored.

### pfd_sddrv_finalize

pfd_sddrv_finalize: 92.877190%; instructions 58/57, diffs 19; inlined mount-bit clearing and error-return scheduling.
Compiled source-level attempts: 3.

1. explicit flag equals mount bit: objdiff 92.263160 -> 92.877190; instructions [57, 57] -> [58, 57]; diffs 43 -> 19; kept.
2. inline mount bit clear expanded: objdiff 92.877190 -> 92.877190; instructions [58, 57] -> [58, 57]; diffs 19 -> 19; restored.
3. finalize preserves ejected flag as target and uses bit-equal initialized test: objdiff 92.877190 -> 91.491230; instructions [58, 57] -> [58, 57]; diffs 19 -> 50; restored.

### pfd_sddrv_get_disk_info

pfd_sddrv_get_disk_info: 97.916664%; instructions 98/96, diffs 2; original symbol ends before final two epilogue instructions; config unchanged.
Compiled source-level attempts: 3.

1. combine mounted/ejected checks; metadata ends original symbol before final two epilogue instructions: objdiff 97.916664 -> 95.104164; instructions [98, 96] -> [96, 96]; diffs 2 -> 79; restored.
2. explicit return result after geometry success; metadata ends original symbol before final two epilogue instructions: objdiff 97.916664 -> 96.875000; instructions [98, 96] -> [97, 96]; diffs 2 -> 20; restored.
3. geometry zero assignments in chained expression; metadata ends original symbol before final two epilogue instructions: objdiff 97.916664 -> 97.895836; instructions [98, 96] -> [98, 96]; diffs 2 -> 4; restored.

### pfd_sddrv_physical_read

pfd_sddrv_physical_read: 99.921260%; instructions 127/127, diffs 2; two register-allocation differences in aligned read arguments.
Compiled source-level attempts: 3.

1. aligned path uses input sector, current sector initialized only for unaligned loop: objdiff 99.921260 -> 98.346460; instructions [127, 127] -> [127, 127]; diffs 2 -> 43; restored.
2. aligned single-block call uses literal block count: objdiff 99.921260 -> 99.448820; instructions [127, 127] -> [127, 127]; diffs 2 -> 3; restored.
3. unaligned loop explicitly advances sector before buffer: objdiff 99.921260 -> 99.763780; instructions [127, 127] -> [127, 127]; diffs 2 -> 4; restored.

### pfd_sddrv_physical_write

pfd_sddrv_physical_write: 99.921260%; instructions 127/127, diffs 2; two register-allocation differences in aligned write arguments.
Compiled source-level attempts: 3.

1. aligned path uses input sector, current sector initialized only for unaligned loop: objdiff 99.921260 -> 98.346460; instructions [127, 127] -> [127, 127]; diffs 2 -> 43; restored.
2. aligned single-block call uses literal block count: objdiff 99.921260 -> 99.448820; instructions [127, 127] -> [127, 127]; diffs 2 -> 3; restored.
3. unaligned loop explicitly advances sector before buffer: objdiff 99.921260 -> 99.763780; instructions [127, 127] -> [127, 127]; diffs 2 -> 4; restored.

### pfd_sddrv_get_total_sectors

pfd_sddrv_get_total_sectors: 90.937500%; instructions 79/80, diffs 43; CSD multiplier truncation and min/max scheduling.
Compiled source-level attempts: 3.

1. CSD read-block multiplier held in u32 until min/max truncation: objdiff 90.937500 -> 90.937500; instructions [79, 80] -> [79, 80]; diffs 43 -> 43; restored.
2. explicit casts on each min/max intermediate: objdiff 90.937500 -> 90.437500; instructions [79, 80] -> [79, 80]; diffs 43 -> 46; restored.
3. CSD size assembly uses high bits as first operand: objdiff 90.937500 -> 87.375000; instructions [79, 80] -> [79, 80]; diffs 43 -> 42; restored.

### pfd_sddrv_calc_mbr_bpb

pfd_sddrv_calc_mbr_bpb: 91.768780%; instructions 171/173, diffs 85; nested reserved-sector convergence loops and register lifetimes.
Compiled source-level attempts: 3.

1. re-derived 32-bit arithmetic, FAT classification before rounding, skip forbidden cluster interval: objdiff 20.606936 -> 91.433525; instructions [239, 173] -> [172, 173]; diffs 237 -> 126; kept.
2. reverse bounds comparison and pointer increment order; cache cluster size: objdiff 91.433525 -> 91.768780; instructions [172, 173] -> [171, 173]; diffs 126 -> 85; kept.
3. explicit outer-loop continuation and partition sector temporary: objdiff 91.768780 -> 90.265900; instructions [171, 173] -> [169, 173]; diffs 85 -> 85; restored.

### pfd_sddrv_store_bpb_buf

pfd_sddrv_store_bpb_buf: 99.342510%; instructions 327/327, diffs 8; serial-field aligned store instruction selection and literal-copy scheduling.
Compiled source-level attempts: 3.

1. re-derived copy-before-fields control flow, guarded inline copies, endian macros preserve source reloads: objdiff 37.935780 -> 94.217125; instructions [244, 327] -> [327, 327]; diffs 316 -> 72; kept.
2. endian expression instead of intrinsic gives constant stores and byte-swap recognition: objdiff 94.217125 -> 97.088684; instructions [327, 327] -> [327, 327]; diffs 72 -> 27; kept.
3. initialize table pointer after memset and reverse comparison/increment order: objdiff 97.088684 -> 98.654434; instructions [327, 327] -> [327, 327]; diffs 27 -> 14; kept.

### pfd_sddrv_store_mbr_buf

pfd_sddrv_store_mbr_buf: 94.366330%; instructions 202/202, diffs 42; CHS arithmetic scheduling and byte-store grouping.
Compiled source-level attempts: 3.

1. re-derived lookup error, typed CHS and partition type before memset, endian CHS stores: objdiff 51.099010 -> 94.183170; instructions [163, 202] -> [202, 202]; diffs 196 -> 46; kept.
2. pointer-first table iteration and reverse upper comparison: objdiff 94.183170 -> 94.366330; instructions [202, 202] -> [202, 202]; diffs 46 -> 42; kept.
3. compute CHS heads before sectors as target block: objdiff 94.366330 -> 94.366330; instructions [202, 202] -> [202, 202]; diffs 42 -> 44; restored.

### pfd_sddrv_calc_fat32_mbr_bpb

pfd_sddrv_calc_fat32_mbr_bpb: 89.909775%; instructions 132/133, diffs 55; FAT convergence loop countdown and sector reload scheduling.
Compiled source-level attempts: 3.

1. reload total sectors after table helper and multiply cluster bits for remainder test: objdiff 85.571430 -> 89.909775; instructions [131, 133] -> [132, 133]; diffs 96 -> 55; kept.
2. load sectors after size lookup instead of before: objdiff 89.909775 -> 88.360900; instructions [132, 133] -> [132, 133]; diffs 55 -> 58; restored.
3. fat-sector countdown uses calculated count rather than separate attempts: objdiff 89.909775 -> 89.909775; instructions [132, 133] -> [132, 133]; diffs 55 -> 55; restored.

### pfd_sddrv_store_fat32_mbr_buf

pfd_sddrv_store_fat32_mbr_buf: 77.507250%; instructions 208/207, diffs 196; CHS widths and endian-store scheduling.
Compiled source-level attempts: 3.

1. typed CHS cylinder/sector/head widths from clrlwi and fixed lookup status: objdiff 64.159424 -> 67.280190; instructions [193, 207] -> [202, 207]; diffs 167 -> 197; kept.
2. reverse range comparison and remove premature u16 truncation on CHS encoding: objdiff 67.280190 -> 77.507250; instructions [202, 207] -> [208, 207]; diffs 197 -> 196; kept.
3. end-of-partition local separate from type initialization: objdiff 77.507250 -> 77.507250; instructions [208, 207] -> [208, 207]; diffs 196 -> 196; restored.

### pfd_sddrv_store_fat32_bpb_buf

pfd_sddrv_store_fat32_bpb_buf: 96.494600%; instructions 374/370, diffs 353; four excess instructions in endian and literal-copy blocks.
Compiled source-level attempts: 3.

1. re-derived FAT32 BPB flow: copy literals first, inline source-value stores and lookup error: objdiff 69.167564 -> 95.583786; instructions [311, 370] -> [374, 370]; diffs 347 -> 353; kept.
2. table upper bound first operand and pointer-first increment: objdiff 95.583786 -> 95.683784; instructions [374, 370] -> [374, 370]; diffs 353 -> 353; kept.
3. 32-bit endian expression high byte before third byte: objdiff 95.683784 -> 96.494600; instructions [374, 370] -> [374, 370]; diffs 353 -> 353; kept.

### pfd_sddrv_build_fat32_mbr_bpb

pfd_sddrv_build_fat32_mbr_bpb: 94.752250%; instructions 230/222, diffs 122; media-state checks and inlined reserved-sector helper branches.
Compiled source-level attempts: 4.

1. reload partition start after calls as original block flow: objdiff 75.148650 -> 90.490990; instructions [222, 222] -> [230, 222]; diffs 211 -> 122; kept.
2. reserved boot buffer error moved into positive return branch: objdiff 90.490990 -> 90.490990; instructions [230, 222] -> [230, 222]; diffs 122 -> 122; restored.
3. reserved buffer writes unaligned branch first: objdiff 90.490990 -> 94.752250; instructions [230, 222] -> [230, 222]; diffs 122 -> 122; kept.
4. combine media-present and ejected failure blocks at each completed formatting stage: objdiff 94.752250 -> 90.968470; instructions [230, 222] -> [222, 222]; diffs 122 -> 149; restored.

## libs/RVL_SDK/src/wad/wad

wad: exact 21 -> 23; code 6680 -> 7080/24500; data 0 -> 0/528; fuzzy 77.3980 -> 80.8216.

### WADImportGetBlocks

WADImportGetBlocks: 76.553690%; instructions 263/298, diffs 288; inlined mask traversal, block arithmetic and stack-local layout.
Compiled source-level attempts: 3.

1. separate real workspace locals in target order instead of aligned wrapper: objdiff 76.553690 -> 76.486580; instructions [263, 298] -> [263, 298]; diffs 288 -> 289; restored.
2. preserve 64-bit content rounding until final block-count conversion: objdiff 76.553690 -> 72.657715; instructions [263, 298] -> [275, 298]; diffs 288 -> 287; restored.
3. selected content pointer recalculated from incremented index: objdiff 76.553690 -> 75.795300; instructions [263, 298] -> [266, 298]; diffs 288 -> 287; restored.

### WAD_815BFFA8

WAD_815BFFA8: 97.177420%; instructions 62/62, diffs 30; thread-loop callee-saved register allocation.
Compiled source-level attempts: 3.

1. declare thread-loop locals in target lifetime order: compile rejected; compile failed, restored.
2. loop exits test result before remaining bytes: compile rejected; compile failed, restored.
3. conditional minimum declared in one expression: compile rejected; compile failed, restored.
4. declare thread-loop locals in target lifetime order: objdiff 97.177420 -> 96.290320; instructions [62, 62] -> [62, 62]; diffs 30 -> 36; restored.
5. loop exits test result before remaining bytes: objdiff 97.177420 -> 97.016130; instructions [62, 62] -> [62, 62]; diffs 30 -> 32; restored.
6. conditional minimum declared in one expression: objdiff 97.177420 -> 96.854836; instructions [62, 62] -> [62, 62]; diffs 30 -> 33; restored.

### WADImportEx

WADImportEx: 71.913610%; instructions 1147/1146, diffs 1121; stream/unpack stack offsets, inlined mask traversal and cleanup scheduling.
Compiled source-level attempts: 3.

1. re-derived prologue workspace: separate stream and unpack info, remove duplicate transfer initialization: objdiff 70.807150 -> 71.912740; instructions [1151, 1146] -> [1147, 1146]; diffs 1119 -> 1120; kept.
2. separate stream/unpack local declaration order: objdiff 71.912740 -> 71.912740; instructions [1147, 1146] -> [1147, 1146]; diffs 1120 -> 1120; restored.
3. initial cleanup flags assigned after input buffers instead of grouped declarations: objdiff 71.912740 -> 71.913610; instructions [1147, 1146] -> [1147, 1146]; diffs 1120 -> 1121; kept.

### WAD_815C1288

WAD_815C1288: 96.393440%; instructions 61/61, diffs 34; thread-loop register allocation and result scheduling.
Compiled source-level attempts: 3.

1. declare thread-loop locals in target lifetime order: compile rejected; compile failed, restored.
2. loop exits test result before remaining bytes: compile rejected; compile failed, restored.
3. conditional minimum declared in one expression: compile rejected; compile failed, restored.
4. declare thread-loop locals in target lifetime order: objdiff 96.311480 -> 96.393440; instructions [61, 61] -> [61, 61]; diffs 35 -> 34; kept.
5. loop exits test result before remaining bytes: objdiff 96.393440 -> 96.229510; instructions [61, 61] -> [61, 61]; diffs 34 -> 36; restored.
6. conditional minimum declared in one expression: objdiff 96.393440 -> 96.311480; instructions [61, 61] -> [61, 61]; diffs 34 -> 35; restored.

### WADBackupEx

WADBackupEx: 59.089455%; instructions 909/1062, diffs 1049; export stack layout and nested content/file control flow.
Compiled source-level attempts: 3.

1. re-derived export prologue and call sequence; _WADCheckContents owns content-ID enumeration: objdiff 55.484936 -> 59.645950; instructions [933, 1062] -> [906, 1062]; diffs 1040 -> 1041; kept.
2. SHA1 context correct storage size and 64-byte DMA alignment: objdiff 59.645950 -> 59.669490; instructions [906, 1062] -> [906, 1062]; diffs 1041 -> 1040; kept.
3. file encryption IV initialized from file header for each encrypted file: objdiff 59.669490 -> 59.669490; instructions [906, 1062] -> [906, 1062]; diffs 1040 -> 1040; restored.

### _WADCheckContents

_WADCheckContents: 96.705880%; instructions 85/85, diffs 19; nested content search register assignment.
Compiled source-level attempts: 3.

1. cache per-content metadata pointer for nested search: compile rejected; compile failed, restored.
2. compare installed content ID with metadata operand first: compile rejected; compile failed, restored.
3. signed content counter preserves target comparisons: compile rejected; compile failed, restored.
4. cache per-content metadata pointer for nested search: compile rejected; compile failed, restored.
5. compare installed content ID with metadata operand first: objdiff 96.705880 -> 94.294120; instructions [85, 85] -> [85, 85]; diffs 19 -> 21; restored.
6. signed content counter preserves target comparisons: objdiff 96.705880 -> 95.294120; instructions [85, 85] -> [85, 85]; diffs 19 -> 21; restored.
7. target result reset only at end of each private-content search: objdiff 96.705880 -> 96.647060; instructions [85, 85] -> [85, 85]; diffs 19 -> 20; restored.

### WADOpenStream

WADOpenStream: 87.354680%; instructions 200/203, diffs 173; NAND extension loop, return scheduling and handle addressing.
Compiled source-level attempts: 3.

1. re-derived NAND extension branch rejects existing length at or beyond requested offset: objdiff 85.310350 -> 85.334980; instructions [200, 203] -> [200, 203]; diffs 173 -> 173; kept.
2. NAND read-open explicit error return instead of conditional expression: objdiff 85.334980 -> 85.802956; instructions [200, 203] -> [199, 203]; diffs 173 -> 173; kept.
3. NAND extension chunk selected from constant-first branch: objdiff 85.802956 -> 87.354680; instructions [199, 203] -> [200, 203]; diffs 173 -> 173; kept.

### WADWriteStream

100.000000%; instructions 47/47, diffs 0.

1. re-derived sparse switch dispatch retaining shared result register: compile rejected; compile failed, restored.
2. re-derived sparse switch dispatch retaining shared result register: objdiff 62.936170 -> 95.723404; instructions [43, 47] -> [45, 47]; diffs 35 -> 33; kept.
3. explicit unsupported stream cases preserve source switch decision tree: objdiff 95.723404 -> 100.000000; instructions [45, 47] -> [47, 47]; diffs 33 -> 0; kept.
4. stream dispatch returns early on invalid arguments before shared switch result: objdiff 100.000000 -> 100.000000; instructions [47, 47] -> [47, 47]; diffs 0 -> 0; restored.

### WADSeekStream

100.000000%; instructions 53/53, diffs 0.

1. re-derived switch dispatch and FAFinfo failure return: compile rejected; compile failed, restored.
2. re-derived switch dispatch and FAFinfo failure return: objdiff 51.226414 -> 94.113205; instructions [56, 53] -> [54, 53]; diffs 51 -> 40; kept.
3. explicit unsupported stream cases preserve source switch decision tree: objdiff 94.113205 -> 100.000000; instructions [54, 53] -> [53, 53]; diffs 40 -> 0; kept.
4. stream dispatch returns early on invalid arguments before shared switch result: objdiff 100.000000 -> 100.000000; instructions [53, 53] -> [53, 53]; diffs 0 -> 0; restored.

### _WADUnpackBackup

_WADUnpackBackup: 94.867256%; instructions 116/113, diffs 89; section-size reloads and allocation ordering.
Compiled source-level attempts: 3.

1. cache TMD size before flags branch for original source load order: compile rejected; compile failed, restored.
2. set size and aligned temporary before recording section offset: compile rejected; compile failed, restored.
3. backup content-index availability uses copied version field: compile rejected; compile failed, restored.
4. cache TMD size before flags branch for original source load order: objdiff 87.831856 -> 92.212390; instructions [118, 113] -> [117, 113]; diffs 91 -> 92; kept.
5. set size and aligned temporary before recording section offset: objdiff 92.212390 -> 92.212390; instructions [117, 113] -> [117, 113]; diffs 92 -> 92; restored.
6. backup content-index availability uses copied version field: objdiff 92.212390 -> 94.867256; instructions [117, 113] -> [116, 113]; diffs 92 -> 89; kept.

### _WADGetCidxCount

_WADGetCidxCount: 95.050000%; instructions 40/40, diffs 25; four-bit unrolled mask traversal register allocation; retained to preserve inlined consumers.
Compiled source-level attempts: 4.

1. ordinary bit loop permits compiler unrolling with cumulative index: compile rejected; compile failed, restored.
2. loop counter preincrement instead of postincrement: compile rejected; compile failed, restored.
3. mask first argument in bitwise test: compile rejected; compile failed, restored.
4. ordinary bit loop permits compiler unrolling with cumulative index: objdiff 95.050000 -> 96.625000; instructions [40, 40] -> [40, 40]; diffs 25 -> 19; kept.
5. loop counter preincrement instead of postincrement: objdiff 96.625000 -> 96.625000; instructions [40, 40] -> [40, 40]; diffs 19 -> 19; restored.
6. mask first argument in bitwise test: objdiff 96.625000 -> 96.625000; instructions [40, 40] -> [40, 40]; diffs 19 -> 19; restored.
7. restore four-bit unrolled mask traversal to preserve inlined consumers; compare whole-unit code score: unit fuzzy 78.282936 -> 80.821550; kept.

### _WADGetCidx

_WADGetCidx: 99.142860%; instructions 56/56, diffs 8; four-bit cumulative index register assignment.
Compiled source-level attempts: 4.

1. ordinary bit loop permits compiler unrolling with cumulative index: compile rejected; compile failed, restored.
2. loop counter preincrement instead of postincrement: compile rejected; compile failed, restored.
3. mask first argument in bitwise test: compile rejected; compile failed, restored.
4. ordinary bit loop permits compiler unrolling with cumulative index: objdiff 99.142860 -> 96.964290; instructions [56, 56] -> [56, 56]; diffs 8 -> 26; restored.
5. loop counter preincrement instead of postincrement: objdiff 99.142860 -> 99.142860; instructions [56, 56] -> [56, 56]; diffs 8 -> 8; restored.
6. mask first argument in bitwise test: objdiff 99.142860 -> 99.142860; instructions [56, 56] -> [56, 56]; diffs 8 -> 8; restored.
7. re-derived four-bit unroll uses one cumulative signed index as original blocks: objdiff 99.142860 -> 92.892860; instructions [56, 56] -> [56, 56]; diffs 8 -> 32; restored.

### _WADBackupGetFiles

_WADBackupGetFiles: 46.195583%; instructions 291/317, diffs 296; directory path buffers and deferred inline string comparisons.
Compiled source-level attempts: 3.

1. stack path arrays use ordinary NAND local alignment rather than DMA alignment: objdiff 46.195583 -> 43.823345; instructions [291, 317] -> [286, 317]; diffs 296 -> 310; restored.
2. single path buffer reused for nocopy and banner comparisons in object block order: objdiff 46.195583 -> 44.567820; instructions [291, 317] -> [291, 317]; diffs 296 -> 295; restored.
3. file enumeration advances fixed-size NAND name slots: objdiff 46.195583 -> 44.274450; instructions [291, 317] -> [288, 317]; diffs 296 -> 296; restored.

### _WADBackupGetSize

_WADBackupGetSize: 86.774190%; instructions 161/155, diffs 155; content loop arithmetic and output-pointer scheduling.
Compiled source-level attempts: 3.

1. re-derived TMD content size uses view contents and low 32-bit size: objdiff 68.554840 -> 86.774190; instructions [166, 155] -> [161, 155]; diffs 162 -> 155; kept.
2. selected count and output title pointer retained separately across contents loop: objdiff 86.774190 -> 86.774190; instructions [161, 155] -> [161, 155]; diffs 155 -> 155; restored.
3. pointer traversal for backup-file size accumulation: objdiff 86.774190 -> 84.419360; instructions [161, 155] -> [158, 155]; diffs 155 -> 147; restored.

### _WADRandPad

_WADRandPad: 87.307690%; instructions 89/91, diffs 62; partial-word byte-copy loop and random-expression scheduling.
Compiled source-level attempts: 5.

1. re-derived advancing word and byte pointers with original random call ordering: compile rejected; compile failed, restored.
2. assign random partial word to same wordCount storage as target: compile rejected; compile failed, restored.
3. explicit random OR accumulation before low two bits: compile rejected; compile failed, restored.
4. re-derived advancing word and byte pointers with original random call ordering: objdiff 62.461540 -> 78.802200; instructions [88, 91] -> [83, 91]; diffs 82 -> 88; kept.
5. assign random partial word to same wordCount storage as target: compile rejected; compile failed, restored.
6. explicit random OR accumulation before low two bits: objdiff 78.802200 -> 79.021980; instructions [83, 91] -> [83, 91]; diffs 88 -> 88; kept.
7. restore sequential random calls with low-bit shift first: objdiff 79.021980 -> 78.802200; instructions [83, 91] -> [83, 91]; diffs 88 -> 88; restored.
8. reuse completed word count for partial random word after declarations: objdiff 79.021980 -> 83.780220; instructions [83, 91] -> [92, 91]; diffs 88 -> 75; kept.
9. consistent partial and complete random word expressions preserve observed call evaluation order: objdiff 83.780220 -> 83.890110; instructions [92, 91] -> [92, 91]; diffs 75 -> 75; kept.

### WAD_815C43E0

WAD_815C43E0: 97.177420%; instructions 62/62, diffs 30; thread-loop callee-saved register allocation.
Compiled source-level attempts: 3.

1. declare thread-loop locals in target lifetime order: compile rejected; compile failed, restored.
2. loop exits test result before remaining bytes: compile rejected; compile failed, restored.
3. conditional minimum declared in one expression: compile rejected; compile failed, restored.
4. declare thread-loop locals in target lifetime order: objdiff 97.177420 -> 96.290320; instructions [62, 62] -> [62, 62]; diffs 30 -> 36; restored.
5. loop exits test result before remaining bytes: objdiff 97.177420 -> 97.016130; instructions [62, 62] -> [62, 62]; diffs 30 -> 32; restored.
6. conditional minimum declared in one expression: objdiff 97.177420 -> 96.854836; instructions [62, 62] -> [62, 62]; diffs 30 -> 33; restored.

### _WADHash

_WADHash: 71.103096%; instructions 205/194, diffs 193; threaded/sequential hash control flow and cleanup locals.
Compiled source-level attempts: 3.

1. re-derived shared result and read buffer; cancel path directly reaches common return: compile rejected; compile failed, restored.
2. byte completion variable shared across threaded and sequential paths: compile rejected; compile failed, restored.
3. choose chunk from remaining-first comparison: objdiff 71.000000 -> 71.103096; instructions [205, 194] -> [205, 194]; diffs 193 -> 193; kept.
4. sequential completion offset declared at function scope: objdiff 71.103096 -> 69.654640; instructions [205, 194] -> [204, 194]; diffs 193 -> 194; restored.
5. sequential read pointer retained across repeated reads: objdiff 71.103096 -> 69.731960; instructions [205, 194] -> [204, 194]; diffs 193 -> 193; restored.

### WADVerify

WADVerify: 86.863945%; instructions 133/147, diffs 131; hash/digest workspace offsets and original dormant cleanup blocks.
Compiled source-level attempts: 3.

1. re-derived workspace: DMA-aligned pointer, digest and real SHA1 context locals: objdiff 51.312923 -> 52.068027; instructions [130, 147] -> [131, 147]; diffs 136 -> 131; kept.
2. certificate source pointer reloaded after each memcpy: objdiff 52.068027 -> 56.027210; instructions [131, 147] -> [132, 147]; diffs 131 -> 128; kept.
3. signature stream offset computed before hashing as target local: objdiff 56.027210 -> 86.863945; instructions [132, 147] -> [133, 147]; diffs 128 -> 131; kept.

### WADImportDVDExForBS

WADImportDVDExForBS: 89.330795%; instructions 259/263, diffs 245; inlined mask traversal and boot-import workspace offsets.
Compiled source-level attempts: 6.

1. DVD read length unsigned comparison following cmplwi target: objdiff 75.908745 -> 75.908745; instructions [295, 263] -> [295, 263]; diffs 280 -> 280; restored.
2. DVD section offset initialized before result writes: objdiff 75.908745 -> 75.908745; instructions [295, 263] -> [295, 263]; diffs 280 -> 280; restored.
3. boot-import header and DVD info declaration order: objdiff 75.908745 -> 75.908745; instructions [295, 263] -> [295, 263]; diffs 280 -> 280; restored.
4. header parser workspace declared before file handle as original stack blocks: objdiff 75.908745 -> 75.806080; instructions [295, 263] -> [295, 263]; diffs 280 -> 281; restored.
5. re-derived constant-first content chunk selection: objdiff 75.908745 -> 75.889730; instructions [295, 263] -> [295, 263]; diffs 280 -> 280; restored.
6. content count iteration ordinary for-loop and explicit result initialization after open: objdiff 75.908745 -> 75.908745; instructions [295, 263] -> [295, 263]; diffs 280 -> 280; restored.

## libs/RVL_SDK/src/vi/vi

vi: exact 18 -> 18; code 2084 -> 2084/11296; data 400 -> 400/1944; fuzzy 83.3782 -> 85.1516.

### OnShutdown

OnShutdown: 81.039604%; instructions 97/101, diffs 44; four missing instructions in leading-zero/mask loop and return scheduling.
Compiled source-level attempts: 7.

1. re-derived leading-zero helper keeps low mask as 64-bit intermediate: objdiff 80.633670 -> 80.633670; instructions [96, 101] -> [96, 101]; diffs 84 -> 84; restored.
2. explicit else in leading-zero helper preserves original block boundary: objdiff 80.633670 -> 79.544556; instructions [96, 101] -> [95, 101]; diffs 84 -> 86; restored.
3. natural 64-bit shift for clearing transferred register bit: objdiff 80.633670 -> 68.148510; instructions [96, 101] -> [90, 101]; diffs 84 -> 89; restored.
4. re-derived shutdown event switch: only events one through three begin shutdown: objdiff 80.633670 -> 72.366330; instructions [96, 101] -> [101, 101]; diffs 84 -> 86; restored.
5. re-derived signed event tree: event 4 through 6 succeeds; out-of-range returns unchanged false final argument: objdiff 80.633670 -> 80.841580; instructions [96, 101] -> [97, 101]; diffs 84 -> 48; kept.
6. separate immediate final-success return from ordinary event-success label: objdiff 80.841580 -> 79.643560; instructions [97, 101] -> [99, 101]; diffs 48 -> 90; restored.
7. capture retrace counter before first-shutdown state is stored: objdiff 80.841580 -> 81.039604; instructions [97, 101] -> [97, 101]; diffs 48 -> 44; kept.

### __VIRetraceHandler

__VIRetraceHandler: 88.813960%; instructions 501/516, diffs 407; interrupt context stack frame and vertical polling/acknowledgement scheduling.
Compiled source-level attempts: 3.

1. re-derived vertical stability loops and retrace phase error test from individual interrupt blocks: objdiff 87.544570 -> 88.813960; instructions [502, 516] -> [501, 516]; diffs 443 -> 407; kept.
2. interrupt flags updated before hardware acknowledgement stores: objdiff 88.813960 -> 88.813960; instructions [501, 516] -> [501, 516]; diffs 407 -> 407; restored.
3. exception context placed after output pixel locals in interrupt stack frame: objdiff 88.813960 -> 88.813960; instructions [501, 516] -> [501, 516]; diffs 407 -> 407; restored.

### __VIInit

__VIInit: 87.469696%; instructions 121/132, diffs 122; original stack-backed TV initialization loop and scan register scheduling.
Compiled source-level attempts: 3.

1. re-derived standard encoder TV reset by explicit enum switch: objdiff 86.446970 -> 87.431816; instructions [119, 132] -> [121, 132]; diffs 122 -> 122; kept.
2. re-derived progressive branch tests scan mode above one: objdiff 87.431816 -> 87.469696; instructions [121, 132] -> [121, 132]; diffs 122 -> 122; kept.
3. initial blanking register arithmetic grouped as original loads: objdiff 87.469696 -> 87.469696; instructions [121, 132] -> [121, 132]; diffs 122 -> 122; restored.

### VIInit

VIInit: 85.062130%; instructions 332/338, diffs 168; scan/field locals and hardware initialization scheduling.
Compiled source-level attempts: 3.

1. re-derived scan mode held locally until interrupt restore: objdiff 82.547340 -> 85.062130; instructions [333, 338] -> [332, 338]; diffs 229 -> 168; kept.
2. framebuffer and pan heights reload current timing after adjusting display: objdiff 85.062130 -> 85.062130; instructions [332, 338] -> [332, 338]; diffs 168 -> 168; restored.
3. getTiming TV-mode argument sums shifted TV type and scan code: objdiff 85.062130 -> 85.062130; instructions [332, 338] -> [332, 338]; diffs 168 -> 168; restored.

### VIWaitForRetrace

VIWaitForRetrace: 90.476190%; instructions 21/21, diffs 2; two save/load instructions scheduled in the opposite order.
Compiled source-level attempts: 3.

1. declare saved interrupt state with initializer: objdiff 90.476190 -> 90.476190; instructions [21, 21] -> [21, 21]; diffs 2 -> 2; restored.
2. retrace wait expressed as do while: objdiff 90.476190 -> 90.476190; instructions [21, 21] -> [21, 21]; diffs 2 -> 2; restored.
3. inline wait helper gives interrupt state independent lifetime: objdiff 90.476190 -> 90.476190; instructions [21, 21] -> [21, 21]; diffs 2 -> 2; restored.

### setFbbRegs

setFbbRegs: 79.419540%; instructions 160/174, diffs 74; inlined framebuffer parity/address control flow and alias-dependent reloads.
Compiled source-level attempts: 3.

1. re-derived signed parity and explicit field-mode branches in framebuffer helper: objdiff 79.419540 -> 72.954025; instructions [160, 174] -> [164, 174]; diffs 74 -> 160; restored.
2. re-derived byte line stride computed before horizontal word offset: objdiff 79.419540 -> 79.419540; instructions [160, 174] -> [160, 174]; diffs 74 -> 74; restored.
3. top framebuffer sum grouped in target multiplication and address order: objdiff 79.419540 -> 71.942530; instructions [160, 174] -> [160, 174]; diffs 74 -> 98; restored.

### setHorizontalRegs

setHorizontalRegs: 62.232143%; instructions 49/56, diffs 55; compiler merges repeated changed-mask load/store pairs.
Compiled source-level attempts: 4.

1. inline changed-mask helper preserves independent register writes: objdiff 62.232143 -> 10.339286; instructions [49, 56] -> [61, 56]; diffs 55 -> 61; restored.
2. inline pointer-based changed mask handles register-write aliasing: objdiff 62.232143 -> 0.000000; instructions [49, 56] -> [65, 56]; diffs 55 -> 65; restored.
3. explicit assignment for changed mask: objdiff 62.232143 -> 62.232143; instructions [49, 56] -> [49, 56]; diffs 55 -> 55; restored.
4. inline mask OR helper instead of runtime-index shift: objdiff 62.232143 -> 1.607143; instructions [49, 56] -> [65, 56]; diffs 55 -> 65; restored.

### setVerticalRegs

setVerticalRegs: 57.950497%; instructions 81/101, diffs 89; compiler merges repeated changed-mask stores and blanking arithmetic.
Compiled source-level attempts: 3.

1. re-derived scan coefficients and signed display-position and size arithmetic: objdiff 48.237625 -> 57.900990; instructions [77, 101] -> [81, 101]; diffs 99 -> 89; kept.
2. re-derived changed-mark and vertical register source order: objdiff 57.900990 -> 57.950497; instructions [81, 101] -> [81, 101]; diffs 89 -> 89; kept.
3. cache shared blanking intervals within each parity branch: objdiff 57.950497 -> 53.049503; instructions [81, 101] -> [76, 101]; diffs 89 -> 92; restored.

### VIConfigure

VIConfigure: 74.807260%; instructions 423/441, diffs 367; inlined register helpers and scan/TV decision scheduling.
Compiled source-level attempts: 3.

1. re-derived boot TV compatibility test in original short-circuit branch order: objdiff 74.034010 -> 74.124720; instructions [430, 441] -> [430, 441]; diffs 384 -> 376; kept.
2. re-derived progressive scan register uses cached non-interlace mode: objdiff 74.124720 -> 74.807260; instructions [430, 441] -> [423, 441]; diffs 376 -> 367; kept.
3. store scan mode before changed-mode flag and use summed TV mode argument: objdiff 74.807260 -> 74.807260; instructions [423, 441] -> [423, 441]; diffs 367 -> 367; restored.

### VIConfigurePan

VIConfigurePan: 88.807510%; instructions 208/213, diffs 194; inlined register helpers and timing-pointer scheduling.
Compiled source-level attempts: 3.

1. re-derived single-field height branch using full original scan decision tree: objdiff 88.807510 -> 85.868546; instructions [208, 213] -> [211, 213]; diffs 194 -> 195; restored.
2. current timing retained before pan dimensions are written: objdiff 88.807510 -> 87.868546; instructions [208, 213] -> [208, 213]; diffs 194 -> 196; restored.
3. picture configuration updated before scaling registers: objdiff 88.807510 -> 46.004696; instructions [208, 213] -> [208, 213]; diffs 194 -> 192; restored.

### VIFlush

VIFlush: 78.913040%; instructions 69/69, diffs 20; leading-zero/mask-loop register allocation and initial state scheduling.
Compiled source-level attempts: 3.

1. re-derived leading-zero helper keeps low mask as 64-bit intermediate: objdiff 78.913040 -> 78.913040; instructions [69, 69] -> [69, 69]; diffs 20 -> 20; restored.
2. explicit else in leading-zero helper preserves original block boundary: objdiff 78.913040 -> 77.318840; instructions [69, 69] -> [68, 69]; diffs 20 -> 51; restored.
3. natural 64-bit shift for clearing transferred register bit: objdiff 78.913040 -> 62.362320; instructions [69, 69] -> [63, 69]; diffs 20 -> 62; restored.

### __VIDisplayPositionToXY

__VIDisplayPositionToXY: 82.624115%; instructions 140/141, diffs 109; one missing instruction plus half-line bound scheduling.
Compiled source-level attempts: 3.

1. re-derived each interlace and progressive bound block and pixel half-line masks: objdiff 68.404260 -> 82.517730; instructions [121, 141] -> [140, 141]; diffs 128 -> 112; kept.
2. single-scan branch reloads timing pointer after wrapping half-line: objdiff 82.517730 -> 81.780140; instructions [140, 141] -> [142, 141]; diffs 112 -> 125; restored.
3. express three equalization half-lines with shift and subtraction: objdiff 82.517730 -> 82.624115; instructions [140, 141] -> [140, 141]; diffs 112 -> 109; kept.

## libs/RVL_SDK/src/nup/nup

nup: exact 11 -> 13; code 2536 -> 2840/10764; data 128 -> 1720/1720; fuzzy 55.2887 -> 82.3081.

### __nupParseServerInfo__FP14NUPContextInfoPcPcUx

__nupParseServerInfo__FP14NUPContextInfoPcPcUx: 62.537610%; instructions 461/452, diffs 432; tag-helper inlining and parsed-title stack/register allocation.
Compiled source-level attempts: 3.

1. re-derived parser extraction blocks and both title passes through ordinary inline tag helper: objdiff 0.000000 -> 62.537610; instructions [431, 452] -> [461, 452]; diffs 442 -> 432; kept.
2. upload audit validation preserves separate value comparisons before storing state: objdiff 62.537610 -> 58.984512; instructions [461, 452] -> [468, 452]; diffs 432 -> 442; restored.
3. signed title counting loop counter mirrors target signed comparisons: objdiff 62.537610 -> 62.537610; instructions [461, 452] -> [461, 452]; diffs 432 -> 432; restored.

### __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc

__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc: 96.758620%; instructions 147/145, diffs 116; request-size arithmetic and response allocation scheduling.
Compiled source-level attempts: 3.

1. request allocation sum follows region country and message evaluation order: objdiff 95.200000 -> 95.131035; instructions [147, 145] -> [147, 145]; diffs 116 -> 116; restored.
2. response copy stored and reloaded through caller output: objdiff 95.200000 -> 96.758620; instructions [147, 145] -> [147, 145]; diffs 116 -> 116; kept.
3. endpoint declared before request pointer: objdiff 96.758620 -> 96.448270; instructions [147, 145] -> [147, 145]; diffs 116 -> 116; restored.

### __nupSetAuditState__FUc

100.000000%; instructions 31/31, diffs 0.

1. re-derived delete success bypasses error conversion; create existing-dir uses conditional expression: objdiff 53.838710 -> 78.548386; instructions [32, 31] -> [33, 31]; diffs 26 -> 24; kept.
2. share the ordinary audit pathname literal before branch dispatch: objdiff 78.548386 -> 100.000000; instructions [33, 31] -> [31, 31]; diffs 24 -> 0; kept.

### __nupBase64Encode__FPUcPUcUl

__nupBase64Encode__FPUcPUcUl: 71.619050%; instructions 59/63, diffs 41; alphabet reloads and partial-group output control flow.
Compiled source-level attempts: 3.

1. re-derived input step separated from bit accumulator update: objdiff 71.619050 -> 71.619050; instructions [59, 63] -> [59, 63]; diffs 41 -> 41; restored.
2. declare accumulator before alphabet lifetime: objdiff 71.619050 -> 70.111115; instructions [59, 63] -> [59, 63]; diffs 41 -> 51; restored.
3. advance individual output bytes through ordinary pointers: objdiff 71.619050 -> 71.619050; instructions [59, 63] -> [59, 63]; diffs 41 -> 41; restored.

### __nupGetAuditData__FP14NUPContextInfoPPc

__nupGetAuditData__FP14NUPContextInfoPPc: 91.741806%; instructions 236/244, diffs 160; encoded-length helper inlining and audit stack/register scheduling.
Compiled source-level attempts: 5.

1. re-derived audit format word, product code terminator and selected-title search order: objdiff 27.905737 -> 91.741806; instructions [243, 244] -> [236, 244]; diffs 223 -> 160; kept.
2. encoded audit size derived from complete signed-record bytes: objdiff 91.741806 -> 91.741806; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; restored.
3. typed record allocation and memcpy arguments preserve explicit field layout: objdiff 91.741806 -> 91.741806; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; restored.
4. re-derived failed serial-number fallback copies empty string at original sdata offset 0x10, not unknown status text: objdiff 91.741806 -> 91.741806; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; restored.
5. retain assembly-proven empty serial fallback: code unchanged, matched data improves 1688 to 1720 bytes: objdiff 91.741806 -> 91.741806; instructions [236, 244] -> [236, 244]; diffs 160 -> 160; kept.

### __nupGetTmdView__FUxPP9ESTmdView

100.000000%; instructions 45/45, diffs 0.

1. query-only ES_GetTmdView fills its size output before allocation: objdiff 95.555560 -> 0.000000; instructions [47, 45] -> [0, 0]; diffs 42 -> -1; restored.
2. successful size query tested before absent-title case: objdiff 95.555560 -> 95.288890; instructions [47, 45] -> [47, 45]; diffs 42 -> 42; restored.
3. allocated view pointer assigned through caller field: objdiff 95.555560 -> 95.555560; instructions [47, 45] -> [47, 45]; diffs 42 -> 42; restored.
4. retain original out-of-line query helper while using API-written size output: objdiff 95.555560 -> 100.000000; instructions [47, 45] -> [45, 45]; diffs 42 -> 0; kept.

### __nupGetBootVersion__FP14ESTitleVersion

__nupGetBootVersion__FP14ESTitleVersion: unscored; instructions 153/163, diffs 101; original mangled name says one argument but target uses two; ABI retained; content-search scheduling also differs.
Compiled source-level attempts: 3.

1. re-derived boot TMD guard and successful enumeration blocks; retains observed two-argument ABI: objdiff 0.000000 -> 0.000000; instructions [152, 163] -> [153, 163]; diffs 108 -> 101; kept.
2. boot version range check tests failure first as target: objdiff 0.000000 -> 0.000000; instructions [153, 163] -> [153, 163]; diffs 101 -> 101; restored.
3. content loop signed counter and installed count compared through unsigned lower bound: objdiff 0.000000 -> 0.000000; instructions [153, 163] -> [153, 163]; diffs 101 -> 101; restored.

### __nupGetTitleSize__FP12NUPTitleInfo

__nupGetTitleSize__FP12NUPTitleInfo: 73.942444%; instructions 133/139, diffs 114; inlined installed-content search and 64-bit block rounding scheduling.
Compiled source-level attempts: 3.

1. re-derived title storage allocation adds each real NAND block separately: objdiff 69.856120 -> 70.064750; instructions [123, 139] -> [132, 139]; diffs 133 -> 132; kept.
2. re-derived content loop signed counter and reloads TMD from title metadata: objdiff 70.064750 -> 73.942444; instructions [132, 139] -> [133, 139]; diffs 132 -> 114; kept.
3. progress step stored before rounded installed-content addition: objdiff 73.942444 -> 72.892090; instructions [133, 139] -> [133, 139]; diffs 114 -> 114; restored.

### __nupGetContentFull__FP14NUPContextInfoP12NUPTitleInfoPcUl

__nupGetContentFull__FP14NUPContextInfoP12NUPTitleInfoPcUl: 94.204544%; instructions 88/88, diffs 25; equal instruction count; register assignment and response-allocation scheduling.
Compiled source-level attempts: 3.

1. re-derived signed content-index search and full-width alignment addition: objdiff 86.318184 -> 93.193184; instructions [85, 88] -> [87, 88]; diffs 79 -> 80; kept.
2. response byte count recorded before returned allocation pointer: objdiff 93.193184 -> 93.238640; instructions [87, 88] -> [87, 88]; diffs 80 -> 80; kept.
3. response locals declared before URL pointer and index search: objdiff 93.238640 -> 94.204544; instructions [87, 88] -> [88, 88]; diffs 80 -> 25; kept.

### __nupGetContentIncr__FP14NUPContextInfoP12NUPTitleInfoPc

__nupGetContentIncr__FP14NUPContextInfoP12NUPTitleInfoPc: 90.421050%; instructions 109/114, diffs 105; installed-content helper inlining and import-error cleanup scheduling.
Compiled source-level attempts: 3.

1. re-derived shared installed-content search helper returns membership with pointer traversal: objdiff 80.026310 -> 87.307014; instructions [106, 114] -> [109, 114]; diffs 103 -> 105; kept.
2. incremental content loop signed count and 64-bit round before import begin: objdiff 87.307014 -> 78.894740; instructions [109, 114] -> [111, 114]; diffs 105 -> 80; restored.
3. import file result captured before begin-error cleanup call: objdiff 87.307014 -> 90.421050; instructions [109, 114] -> [109, 114]; diffs 105 -> 105; kept.

### __nupUpdateTitle__FP14NUPContextInfoP12NUPTitleInfoPcPc

__nupUpdateTitle__FP14NUPContextInfoP12NUPTitleInfoPcPc: 94.962960%; instructions 133/135, diffs 88; NAND free-block comparison and shared error-return scheduling.
Compiled source-level attempts: 3.

1. re-derived boot content fetch uses uncached content URL: objdiff 85.355550 -> 86.985180; instructions [135, 135] -> [135, 135]; diffs 100 -> 76; kept.
2. re-derived update-title control flow with common error return after every import block: objdiff 86.985180 -> 94.837036; instructions [135, 135] -> [133, 135]; diffs 76 -> 88; kept.
3. inode capacity condition places title progress operand first as original comparison: objdiff 94.837036 -> 94.962960; instructions [133, 135] -> [133, 135]; diffs 88 -> 88; kept.

### __nupOp

__nupOp: 90.413240%; instructions 422/438, diffs 391; boot/IOS/menu search and update loop scheduling; 16 target instructions remain unmatched.
Compiled source-level attempts: 3.

1. re-derived every operation block, server ABI values, boot/IOS/menu update order and shared cleanup from target assembly: objdiff 47.045662 -> 90.150690; instructions [332, 438] -> [423, 438]; diffs 428 -> 267; kept.
2. capture validated boot version in 16-bit local before server call: objdiff 90.150690 -> 90.641556; instructions [423, 438] -> [421, 438]; diffs 267 -> 414; kept.
3. unsigned offset loop for final update pass preserves pointer traversal and title reloads: objdiff 90.641556 -> 90.175800; instructions [421, 438] -> [421, 438]; diffs 414 -> 414; restored.

## Source-order audit

```json
[
  {
    "unit": "libs/RVL_SDK/src/fa/driver/sd_drv",
    "target_functions": 26,
    "source_functions_found": 26,
    "missing": [],
    "source_order_matches_object": true
  },
  {
    "unit": "libs/RVL_SDK/src/wad/wad",
    "target_functions": 40,
    "source_functions_found": 40,
    "missing": [],
    "source_order_matches_object": true
  },
  {
    "unit": "libs/RVL_SDK/src/vi/vi",
    "target_functions": 30,
    "source_functions_found": 30,
    "missing": [],
    "source_order_matches_object": true
  },
  {
    "unit": "libs/RVL_SDK/src/nup/nup",
    "target_functions": 23,
    "source_functions_found": 23,
    "missing": [],
    "source_order_matches_object": true
  }
]
```

## String offset audit

```json
[
  {
    "unit": "libs/RVL_SDK/src/fa/driver/sd_drv",
    "strings": 46,
    "sequence_matches": true,
    "offset_divergences": []
  },
  {
    "unit": "libs/RVL_SDK/src/wad/wad",
    "strings": 18,
    "sequence_matches": true,
    "offset_divergences": []
  },
  {
    "unit": "libs/RVL_SDK/src/vi/vi",
    "strings": 7,
    "sequence_matches": true,
    "offset_divergences": [
      {
        "string_index": 0,
        "source_offset": 772,
        "original_offset": 956
      },
      {
        "string_index": 1,
        "source_offset": 816,
        "original_offset": 1000
      },
      {
        "string_index": 2,
        "source_offset": 860,
        "original_offset": 1044
      },
      {
        "string_index": 3,
        "source_offset": 904,
        "original_offset": 1088
      },
      {
        "string_index": 4,
        "source_offset": 948,
        "original_offset": 1132
      },
      {
        "string_index": 5,
        "source_offset": 992,
        "original_offset": 1176
      },
      {
        "string_index": 6,
        "source_offset": 1036,
        "original_offset": 1220
      }
    ]
  },
  {
    "unit": "libs/RVL_SDK/src/nup/nup",
    "strings": 28,
    "sequence_matches": true,
    "offset_divergences": []
  }
]
```

## Review corrections

- WAD source blocks were reordered to original function address order while preserving effective inlining settings and all baseline exact functions.
- The partial random-word path draws one random word; an intermediate unused extra draw was removed during review.
- The original four-bit WAD count traversal was restored after whole-unit verification showed that the simple loop worsened its inlined consumers. The final whole-unit fuzzy score is higher.
- The NUP boot-version local passed to the server is initialized; size-output locals are consumed only after successful API queries.
- The NUP audit header stores a 32-bit format word. Its field name was corrected from titleId to format.
- The failed serial-number path copies the empty string identified at target small-data offset 0x10. Removing the duplicate unknown literal restores every NUP data section to 100 percent without changing instruction scores.
- VI shutdown event 4 through 6 returns success, and out-of-range events return the false final argument as observed in target assembly.

## Uncertainties

- pfd_sddrv_get_disk_info: original symbol size excludes the last addi/blr; no symbol metadata was changed.
- __nupGetBootVersion: original symbol name describes one argument, while target instructions and caller pass context in r3 and title in r4. The existing readable two-argument declaration was preserved, so exact-name objdiff cannot associate this function.
- Register allocation is an observed remaining difference in several functions, not proof that no source-level solution exists.
- WAD data remains zero matched bytes even with an identical string pool; no data placement tricks or linking changes were made.
- VI has 184 fewer bytes before its string pool. The original data after the 25 filter taps resembles three GX render-mode records, but no target reference proves their ownership or intended declarations. No unused objects were added merely to move the pool. pool_diff.py and gate.py compare string contents/order, not their offsets; the stricter audit above records this unresolved gap.
