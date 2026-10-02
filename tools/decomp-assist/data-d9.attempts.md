# data-d9 attempts

All four pools are identical. Initial report saved to /tmp/data-d9-before.json. Every target function is objdiff 100%; no code work is needed.

Attempt 1: rename index symbols by their function relocations. No metric gain. Reverted all index renames. objdiff 3.4.5 pairs compiler-generated index objects by bytes and relocations; differing unwind record names prevent relocation equality.

Attempt 2: rename the referenced unwind records to compiler-emitted names, proven by extabindex function relocations and identical unwind bytes. No addresses, extents or section totals changed.

## RFL_Database
- 0x81330AA0: @3211 -> @3220. Target and compiler extabindex +0 both relocate to RFLiInitDatabase; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AA8: @3216 -> @3225. Target and compiler extabindex +0 both relocate to bootloadCheckCRCCb_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AB0: @3230 -> @3239. Target and compiler extabindex +0 both relocate to bootloadDBcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AB8: @3248 -> @3257. Target and compiler extabindex +0 both relocate to bootloadDBopencallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AC0: @3259 -> @3268. Target and compiler extabindex +0 both relocate to RFLiBootLoadDatabaseAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AC8: @3262 -> @3271. Target and compiler extabindex +0 both relocate to saveDBcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AD0: @3274 -> @3283. Target and compiler extabindex +0 both relocate to saveDBopencallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AD8: @3282 -> @3291. Target and compiler extabindex +0 both relocate to saveDBmultiopencallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AE0: @3291 -> @3300. Target and compiler extabindex +0 both relocate to createCRCForSaveDBCallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AE8: @3306 -> @3315. Target and compiler extabindex +0 both relocate to RFLiSaveDatabaseAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AF0: @3321 -> @3330. Target and compiler extabindex +0 both relocate to RFLiSaveOpenedDatabaseAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330AF8: @3360 -> @3369. Target and compiler extabindex +0 both relocate to RFLiGetCharData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B00: @3438 -> @3447. Target and compiler extabindex +0 both relocate to convertRaw2InfoCore_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B08: @3443 -> @3452. Target and compiler extabindex +0 both relocate to RFLiConvertRaw2Info; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B10: @3448 -> @3457. Target and compiler extabindex +0 both relocate to RFLiConvertHRaw2Info; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B18: @3453 -> @3462. Target and compiler extabindex +0 both relocate to convertInfo2RawCore_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B20: @3458 -> @3467. Target and compiler extabindex +0 both relocate to RFLiConvertInfo2Raw; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B28: @3463 -> @3472. Target and compiler extabindex +0 both relocate to RFLiConvertInfo2HRaw; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B30: @3468 -> @3477. Target and compiler extabindex +0 both relocate to RFLiConvertHRaw2Raw; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B38: @3473 -> @3482. Target and compiler extabindex +0 both relocate to RFLiConvertRaw2HRaw; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B40: @3480 -> @3489. Target and compiler extabindex +0 both relocate to RFLiGetCharRawData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B48: @3488 -> @3497. Target and compiler extabindex +0 both relocate to RFLiGetCharInfo; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B50: @3571 -> @3580. Target and compiler extabindex +0 both relocate to RFLIsAvailableOfficialData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B58: @3590 -> @3599. Target and compiler extabindex +0 both relocate to RFLGetAvailableOfficialDataNum; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B60: @3617 -> @3626. Target and compiler extabindex +0 both relocate to createLowAddr_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B68: @3725 -> @3734. Target and compiler extabindex +0 both relocate to RFLiIsMyHomeID; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B70: @3821 -> @3830. Target and compiler extabindex +0 both relocate to RFLSearchOfficialData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B78: @3839 -> @3848. Target and compiler extabindex +0 both relocate to RFLiIsValidName2; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B80: @3853 -> @3862. Target and compiler extabindex +0 both relocate to RFLiGetIsolation; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B88: @3877 -> @3886. Target and compiler extabindex +0 both relocate to RFLiGetHiddenHeader; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B90: @3885 -> @3894. Target and compiler extabindex +0 both relocate to RFLiDBIsLoaded; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330B98: @3908 -> @3917. Target and compiler extabindex +0 both relocate to alarmCreateCb_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330BA0: @3913 -> @3922. Target and compiler extabindex +0 both relocate to RFLiCreateHeaderCRCAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330BA8: @3931 -> @3940. Target and compiler extabindex +0 both relocate to alarmCheckCb_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.

## RFL_HiddenDatabase
- 0x81330A18: @2533 -> @2543. Target and compiler extabindex +0 both relocate to RFLiInitHiddenDatabase; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A20: @2542 -> @2552. Target and compiler extabindex +0 both relocate to loadclosecallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A28: @2549 -> @2559. Target and compiler extabindex +0 both relocate to loadcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A30: @2556 -> @2566. Target and compiler extabindex +0 both relocate to loadopencallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A38: @2565 -> @2575. Target and compiler extabindex +0 both relocate to RFLiLoadHiddenDataAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A40: @2583 -> @2593. Target and compiler extabindex +0 both relocate to RFLiLoadCachedHiddenData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A48: @2684 -> @2694. Target and compiler extabindex +0 both relocate to overwrite_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A50: @2694 -> @2704. Target and compiler extabindex +0 both relocate to create_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A58: @2710 -> @2720. Target and compiler extabindex +0 both relocate to writeCallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A60: @2733 -> @2743. Target and compiler extabindex +0 both relocate to writeData_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A68: @2738 -> @2748. Target and compiler extabindex +0 both relocate to openForWriteCallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A70: @2776 -> @2786. Target and compiler extabindex +0 both relocate to RFLiOneDataToHiddenDB; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A78: @2804 -> @2814. Target and compiler extabindex +0 both relocate to RFLiCountupHiddenDataNum; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A80: @2810 -> @2820. Target and compiler extabindex +0 both relocate to RFLiGetHiddenNext; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A88: @2816 -> @2826. Target and compiler extabindex +0 both relocate to RFLiGetHiddenPrev; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A90: @2830 -> @2840. Target and compiler extabindex +0 both relocate to RFLiIsValidHiddenData; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330A98: @2880 -> @2890. Target and compiler extabindex +0 both relocate to RFLiIsCachedHDB; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.

## RFL_NANDLoader
- 0x81330818: @2144 -> @2374. Target and compiler extabindex +0 both relocate to RFLiInitLoader; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330820: @2193 -> @2423. Target and compiler extabindex +0 both relocate to parseOnmemoryRes_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330828: @2205 -> @2435. Target and compiler extabindex +0 both relocate to loadResRead2ndcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330830: @2217 -> @2447. Target and compiler extabindex +0 both relocate to loadResRead1stcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330838: @2223 -> @2453. Target and compiler extabindex +0 both relocate to loadResGetlengthcallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330840: @2229 -> @2459. Target and compiler extabindex +0 both relocate to loadResOpencallback_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330848: @2237 -> @2467. Target and compiler extabindex +0 both relocate to RFLiLoadResourceHeaderAsync; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330850: @2254 -> @2484. Target and compiler extabindex +0 both relocate to getNANDFile_; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330858: @2272 -> @2502. Target and compiler extabindex +0 both relocate to RFLiGetTexSize; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330860: @2298 -> @2528. Target and compiler extabindex +0 both relocate to RFLiLoadTexture; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330868: @2316 -> @2546. Target and compiler extabindex +0 both relocate to RFLiGetShpTexSize; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330870: @2342 -> @2572. Target and compiler extabindex +0 both relocate to RFLiLoadShpTexture; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330878: @2360 -> @2590. Target and compiler extabindex +0 both relocate to RFLiGetShapeSize; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330880: @2386 -> @2616. Target and compiler extabindex +0 both relocate to RFLiLoadShape; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330888: @2400 -> @2630. Target and compiler extabindex +0 both relocate to RFLFreeCachedResource; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330890: @2405 -> @2635. Target and compiler extabindex +0 both relocate to RFLIsResourceCached; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.

## RFL_Model
- 0x81330970: @2787 -> @2794. Target and compiler extabindex +0 both relocate to RFLGetModelBufferSize; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330978: @2836 -> @2843. Target and compiler extabindex +0 both relocate to RFLiInitCharModel; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330980: @2841 -> @2848. Target and compiler extabindex +0 both relocate to RFLSetMtx; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330988: @2871 -> @2878. Target and compiler extabindex +0 both relocate to RFLLoadDrawSetting; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330990: @2883 -> @2890. Target and compiler extabindex +0 both relocate to RFLLoadMaterialSetting; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x81330998: @2921 -> @2928. Target and compiler extabindex +0 both relocate to RFLDrawOpaCore; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x813309A0: @2936 -> @2943. Target and compiler extabindex +0 both relocate to RFLDrawXluCore; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x813309A8: @2956 -> @2959. Target and compiler extabindex +0 both relocate to RFLiInitCharModelRes; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x813309B0: @3092 -> @3095. Target and compiler extabindex +0 both relocate to RFLiInitShapeRes; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.
- 0x813309B8: @3105 -> @3108. Target and compiler extabindex +0 both relocate to RFLiInitTexRes; +8 relocates to this 8-byte unwind record, whose bytes are identical. Address and extent unchanged.

## Instruction verification

- RFL_Database: instruction-exact 38/39; no source or text symbols changed, so no instruction count dropped.
- Existing raw instruction difference: RFLiIsSameID; objdiff 100%, not altered by data-symbol changes.
- RFL_HiddenDatabase: instruction-exact 20/20; no source or text symbols changed, so no instruction count dropped.
- RFL_NANDLoader: instruction-exact 17/17; no source or text symbols changed, so no instruction count dropped.
- RFL_Model: instruction-exact 15/15; no source or text symbols changed, so no instruction count dropped.

## Final full gate

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLFaceLib/src/RFL_Database] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Database] objdiff: code 7508/7508 data 688/688 functions 39/39 fuzzy 100.0000 linked code 7508
[libs/RVLFaceLib/src/RFL_Database] instruction-exact functions: 38/39
[libs/RVLFaceLib/src/RFL_Database]   section .sdata2 size 8 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section .text size 7508 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extab size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extabindex size 408 match 100.0
[libs/RVLFaceLib/src/RFL_Database] baseline: code 7508/7508 data 280 functions 39 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_HiddenDatabase] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_HiddenDatabase] objdiff: code 3356/3356 data 340/340 functions 20/20 fuzzy 100.0000 linked code 3356
[libs/RVLFaceLib/src/RFL_HiddenDatabase] instruction-exact functions: 20/20
[libs/RVLFaceLib/src/RFL_HiddenDatabase]   section .text size 3356 match 100.0
[libs/RVLFaceLib/src/RFL_HiddenDatabase]   section extab size 136 match 100.0
[libs/RVLFaceLib/src/RFL_HiddenDatabase]   section extabindex size 204 match 100.0
[libs/RVLFaceLib/src/RFL_HiddenDatabase] baseline: code 3356/3356 data 136 functions 20 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_NANDLoader] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_NANDLoader] objdiff: code 4140/4140 data 504/504 functions 17/17 fuzzy 100.0000 linked code 4140
[libs/RVLFaceLib/src/RFL_NANDLoader] instruction-exact functions: 17/17
[libs/RVLFaceLib/src/RFL_NANDLoader]   section .data size 32 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader]   section .rodata size 144 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader]   section .sdata size 8 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader]   section .text size 4140 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader]   section extab size 128 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader]   section extabindex size 192 match 100.0
[libs/RVLFaceLib/src/RFL_NANDLoader] baseline: code 4140/4140 data 312 functions 17 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_Model] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Model] objdiff: code 7788/7788 data 552/552 functions 15/15 fuzzy 100.0000 linked code 7788
[libs/RVLFaceLib/src/RFL_Model] instruction-exact functions: 15/15
[libs/RVLFaceLib/src/RFL_Model]   section .data size 16 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .rodata size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .sdata2 size 64 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .text size 7788 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extab size 80 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extabindex size 120 match 100.0
[libs/RVLFaceLib/src/RFL_Model] baseline: code 7788/7788 data 432 functions 15 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.07103 -> 63.07103
global matched_data_percent: 97.64782 -> 97.69824
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

All non-text sections reach 100%; matched_data equals total_data in all four units. No remaining non-matching functions in objdiff. No code changes, no section total or symbol extent changes.

Existing RFLiIsSameID raw ctxdiff: 101/101 instructions, diffs 2 at indices 1 and 8. Both are bne displacement differences caused by its different object placement. Objdiff remains 100%. Source and code-symbol configuration are unchanged; data-lane instruction-exact count stays 38/39.
