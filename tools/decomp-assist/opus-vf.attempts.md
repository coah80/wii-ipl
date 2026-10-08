# opus-vf attempts (lead: yannicksuter/mscharged-decomp)

Refs saved to /mnt/drive2/projects/wii-ipl-workers/_refs/prior/yannicksuter_mscharged-decomp__{sd_drv.c,sd_drv.h,pdm_partition.c,pdm_partition.h,lyt_window.cpp}.

## libs/NW4R/src/lyt/lyt_window (20/21, DrawFrame 119/376 differing, Equivalent)
1. Ported their HBM DrawFrame shape: LT quad expanded with GetTexutreFlipInfo(NONE) + inline SetFrameTexOrigin/SetFrameTexExtent (kept our GetTextureNum early-out). DrawFrame 0/376; all 21 functions exact, no mw_version change needed.
2. Flipped to Matching: DOL wrong. .data order flipInfos/scLytFatalMsg swapped -> moved scLytFatalMsg definition below the anonymous namespace (extern decl at top). Order fixed.
3. DOL still off by 4 bytes: Get/SetVtxColorElement inlines (lyt/common.h) used the local NW4R_ASSERT redefinition (scLytFatalMsg) instead of the header's own weak @STRING@ literal. Moved the lyt includes above the macro redefinition. DOL 26116613... OK.

## libs/RVL_SDK/src/fa/driver/sd_drv (23/26)
- Their src/RVL_SDK/vf/sd_drv.c is a 5-line stub (VFi_InitSDWrok only). No prior art for pfd_sddrv_init/finalize/build_fat32_mbr_bpb.
- mw_version="GC/3.0a5": object byte-identical to 3.0a5.2 (md5 ccd9f660...). No change. Not pursued further (no lead).

## libs/RVL_SDK/src/fa/pdm_partition (19/20, pdm_part_is_master_boot_sector 84/86)
- Their pdm_partition.c is the newer VF version (VFipdm_mbr_get_mbr_part_table); no pdm_part_is_master_boot_sector. Dead lead.
- mw_version="GC/3.0a5": object byte-identical (md5 a1dd0b38...). No change.
- Hand attempts on the function:
  1. read_partition_u32 = b0 + b1<<8 + b2<<16 + b3<<24 (plain sum): 25/84 (size now right).
  2. loop 2 pointer order swapped: 25. `*p_count + *p_start`: 23. p_count++ first: 27. for-header increments: 25.
  3. loop 2 as start[index] + count[index]: 21/84 (best).
  4. sum trees ((b2<<16)+b0)+((b3<<24)+(b1<<8)): 84/86; reversed sum: 85/86; casts / unsigned int / no casts / b0+b2+b1+b3: 21; OR form: 78-82.
  5. pointer p=buf+offset, MBR_WORD macro, buf+4 for count, &buf[454]: all 21. Accumulating local: 43.
  6. store count before start: 88. int index: 28. all 120 local declaration orders: best 21.
  7. loop 1 with arrays: 24. inverted if/else: 60.
  Remaining: 21 instructions in the inlined byte-assembly schedule (target loads b3,b2,b0 then b1; ours b3,b2,b1,b0). Best copy: tools/decomp-assist/opus-vf.best.pdm_partition.c.

## Step 3
All other fa/ (RVLSDKLib "fa") and vf/ Objects are Matching; nothing else to try.
