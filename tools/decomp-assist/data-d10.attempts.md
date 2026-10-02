# data-d10 rework

The prior candidate was rejected for edits outside assigned ownership. This replacement starts from origin/main and resolves symbols by section plus absolute address within splits.txt ranges, never by generated name alone.

## RFL_MiddleDatabase

POOL IDENTICAL up to 0 (mine=0 base=0)
Ownership: extab 0x81330bc0-0x81330c10, extabindex 0x81331b30-0x81331ba8
- extab:0x81330bc0 @2294 -> @2302; 8 bytes unchanged; index relocation identifies updateHDBcallback_, paired length 488, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b30 @2295 -> @2303; 12 bytes unchanged; index relocation identifies updateHDBcallback_, paired length 488, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330bc8 @2312 -> @2320; 8 bytes unchanged; index relocation identifies loadHiddenDataSync_, paired length 372, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b3c @2313 -> @2321; 12 bytes unchanged; index relocation identifies loadHiddenDataSync_, paired length 372, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330bd0 @2327 -> @2335; 8 bytes unchanged; index relocation identifies updateHiddenOld_, paired length 340, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b48 @2328 -> @2336; 12 bytes unchanged; index relocation identifies updateHiddenOld_, paired length 340, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330bd8 @2347 -> @2355; 8 bytes unchanged; index relocation identifies loadHiddenRandomSync_, paired length 316, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b54 @2348 -> @2356; 12 bytes unchanged; index relocation identifies loadHiddenRandomSync_, paired length 316, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330be0 @2373 -> @2381; 8 bytes unchanged; index relocation identifies updateHDBRandcallback_, paired length 404, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b60 @2374 -> @2382; 12 bytes unchanged; index relocation identifies updateHDBRandcallback_, paired length 404, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330be8 @2434 -> @2442; 8 bytes unchanged; index relocation identifies updateHiddenRandom_, paired length 732, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b6c @2435 -> @2443; 12 bytes unchanged; index relocation identifies updateHiddenRandom_, paired length 732, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330bf0 @2447 -> @2455; 8 bytes unchanged; index relocation identifies updateRandom_, paired length 248, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b78 @2448 -> @2456; 12 bytes unchanged; index relocation identifies updateRandom_, paired length 248, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330bf8 @2464 -> @2472; 8 bytes unchanged; index relocation identifies RFLUpdateMiddleDBAsync, paired length 92, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b84 @2465 -> @2473; 12 bytes unchanged; index relocation identifies RFLUpdateMiddleDBAsync, paired length 92, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330c00 @2482 -> @2490; 8 bytes unchanged; index relocation identifies RFLiUpdateMiddleDBAsync, paired length 312, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b90 @2483 -> @2491; 12 bytes unchanged; index relocation identifies RFLiUpdateMiddleDBAsync, paired length 312, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
- extab:0x81330c08 @2497 -> @2505; 8 bytes unchanged; index relocation identifies RFLiGetCharInfoMiddleDB, paired length 156, unwind bytes identical; owned range 0x81330bc0-0x81330c10.
- extabindex:0x81331b9c @2498 -> @2506; 12 bytes unchanged; index relocation identifies RFLiGetCharInfoMiddleDB, paired length 156, unwind bytes identical; owned range 0x81331b30-0x81331ba8.
## RFL_MakeTex

POOL IDENTICAL up to 0 (mine=0 base=0)
Ownership: extab 0x813309c0-0x81330a00, extabindex 0x81331830-0x81331890, .rodata 0x8161d358-0x8161d418, .sdata2 0x816950b0-0x81695170
- extab:0x813309c0 @2834 -> @2842; 8 bytes unchanged; index relocation identifies RFLiSetupCopyTex, paired length 304, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331830 @2835 -> @2843; 12 bytes unchanged; index relocation identifies RFLiSetupCopyTex, paired length 304, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309c8 @3102 -> @3110; 8 bytes unchanged; index relocation identifies RFLiMakeTexture, paired length 4232, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x8133183c @3103 -> @3111; 12 bytes unchanged; index relocation identifies RFLiMakeTexture, paired length 4232, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309d0 @3139 -> @3147; 8 bytes unchanged; index relocation identifies RFLiSetup2DCameraAndParam, paired length 472, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331848 @3140 -> @3148; 12 bytes unchanged; index relocation identifies RFLiSetup2DCameraAndParam, paired length 472, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309d8 @3153 -> @3161; 8 bytes unchanged; index relocation identifies RFLiSetTev4Mouth, paired length 584, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331854 @3154 -> @3162; 12 bytes unchanged; index relocation identifies RFLiSetTev4Mouth, paired length 584, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309e0 @3179 -> @3187; 8 bytes unchanged; index relocation identifies RFLiSetTev4Eye, paired length 688, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331860 @3180 -> @3188; 12 bytes unchanged; index relocation identifies RFLiSetTev4Eye, paired length 688, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309e8 @3227 -> @3235; 8 bytes unchanged; index relocation identifies RFLiSetFaceParts, paired length 1288, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x8133186c @3228 -> @3236; 12 bytes unchanged; index relocation identifies RFLiSetFaceParts, paired length 1288, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309f0 @3251 -> @3259; 8 bytes unchanged; index relocation identifies RFLiCapture, paired length 2156, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331878 @3252 -> @3260; 12 bytes unchanged; index relocation identifies RFLiCapture, paired length 2156, unwind bytes identical; owned range 0x81331830-0x81331890.
- extab:0x813309f8 @3267 -> @3275; 8 bytes unchanged; index relocation identifies RFLiDrawQuad, paired length 504, unwind bytes identical; owned range 0x813309c0-0x81330a00.
- extabindex:0x81331884 @3268 -> @3276; 12 bytes unchanged; index relocation identifies RFLiDrawQuad, paired length 504, unwind bytes identical; owned range 0x81331830-0x81331890.
## RFL_DataUtility

POOL IDENTICAL up to 0 (mine=0 base=0)
Ownership: extab 0x81330c30-0x81330c58, extabindex 0x81331bd8-0x81331c14, .rodata 0x8161e070-0x8161e080
- extab:0x81330c30 @2175 -> @2183; 8 bytes unchanged; index relocation identifies RFLiCheckValidInfo, paired length 1124, unwind bytes identical; owned range 0x81330c30-0x81330c58.
- extabindex:0x81331bd8 @2176 -> @2184; 12 bytes unchanged; index relocation identifies RFLiCheckValidInfo, paired length 1124, unwind bytes identical; owned range 0x81331bd8-0x81331c14.
- extab:0x81330c38 @2237 -> @2245; 8 bytes unchanged; index relocation identifies RFLiIsValidOnNAND, paired length 44, unwind bytes identical; owned range 0x81330c30-0x81330c58.
- extabindex:0x81331be4 @2238 -> @2246; 12 bytes unchanged; index relocation identifies RFLiIsValidOnNAND, paired length 44, unwind bytes identical; owned range 0x81331bd8-0x81331c14.
- extab:0x81330c40 @2281 -> @2289; 8 bytes unchanged; index relocation identifies RFLiPickupCharInfo, paired length 320, unwind bytes identical; owned range 0x81330c30-0x81330c58.
- extabindex:0x81331bf0 @2282 -> @2290; 12 bytes unchanged; index relocation identifies RFLiPickupCharInfo, paired length 320, unwind bytes identical; owned range 0x81331bd8-0x81331c14.
- extab:0x81330c48 @2298 -> @2306; 8 bytes unchanged; index relocation identifies copyChar2Additional_, paired length 400, unwind bytes identical; owned range 0x81330c30-0x81330c58.
- extabindex:0x81331bfc @2299 -> @2307; 12 bytes unchanged; index relocation identifies copyChar2Additional_, paired length 400, unwind bytes identical; owned range 0x81331bd8-0x81331c14.
- extab:0x81330c50 @2304 -> @2312; 8 bytes unchanged; index relocation identifies RFLGetAdditionalInfo, paired length 84, unwind bytes identical; owned range 0x81330c30-0x81330c58.
- extabindex:0x81331c08 @2305 -> @2313; 12 bytes unchanged; index relocation identifies RFLGetAdditionalInfo, paired length 84, unwind bytes identical; owned range 0x81331bd8-0x81331c14.
## RFL_NWC24

POOL IDENTICAL up to 15 (mine=15 base=15)
Ownership: extab 0x81330c58-0x81330c78, extabindex 0x81331c14-0x81331c44, .data 0x8166f0f0-0x8166f2c8
- extab:0x81330c58 @1981 -> @1986; 8 bytes unchanged; index relocation identifies RFLiNWC24Msg2CharData, paired length 120, unwind bytes identical; owned range 0x81330c58-0x81330c78.
- extabindex:0x81331c14 @1982 -> @1987; 12 bytes unchanged; index relocation identifies RFLiNWC24Msg2CharData, paired length 120, unwind bytes identical; owned range 0x81331c14-0x81331c44.
- extab:0x81330c60 @1990 -> @1995; 8 bytes unchanged; index relocation identifies RFLiSetOfficial2NWC24Msg, paired length 216, unwind bytes identical; owned range 0x81330c58-0x81330c78.
- extabindex:0x81331c20 @1991 -> @1996; 12 bytes unchanged; index relocation identifies RFLiSetOfficial2NWC24Msg, paired length 216, unwind bytes identical; owned range 0x81331c14-0x81331c44.
- extab:0x81330c68 @2044 -> @2049; 8 bytes unchanged; index relocation identifies RFLiNWC24Msg2HiddenAsync, paired length 392, unwind bytes identical; owned range 0x81330c58-0x81330c78.
- extabindex:0x81331c2c @2045 -> @2050; 12 bytes unchanged; index relocation identifies RFLiNWC24Msg2HiddenAsync, paired length 392, unwind bytes identical; owned range 0x81331c14-0x81331c44.
- extab:0x81330c70 @2129 -> @2134; 8 bytes unchanged; index relocation identifies makeNWC24MsgforExchange_, paired length 2256, unwind bytes identical; owned range 0x81330c58-0x81330c78.
- extabindex:0x81331c38 @2130 -> @2135; 12 bytes unchanged; index relocation identifies makeNWC24MsgforExchange_, paired length 2256, unwind bytes identical; owned range 0x81331c14-0x81331c44.

Ownership audit: 54 name-only changes; every changed absolute address is inside exactly one assigned unit range. Addresses, extents, attributes and section totals unchanged. RFL_Model, RFL_Database, RFL_HiddenDatabase and RFL_NANDLoader have no configuration edits.

## Baseline gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLFaceLib/src/RFL_MiddleDatabase] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_MiddleDatabase] objdiff: code 3648/3648 data 80/200 functions 13/13 fuzzy 100.0000 linked code 3648
[libs/RVLFaceLib/src/RFL_MiddleDatabase] instruction-exact functions: 13/13
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section .text size 3648 match 100.0
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section extab size 80 match 100.0
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section extabindex size 120 match 95.5
[libs/RVLFaceLib/src/RFL_MiddleDatabase] baseline: code 3648/3648 data 80 functions 13 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_MakeTex] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_MakeTex] objdiff: code 10396/10396 data 448/544 functions 10/10 fuzzy 100.0000 linked code 10396
[libs/RVLFaceLib/src/RFL_MakeTex] instruction-exact functions: 10/10
[libs/RVLFaceLib/src/RFL_MakeTex]   section .rodata size 192 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section .sdata2 size 192 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section .text size 10396 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section extab size 64 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section extabindex size 96 match 86.25
[libs/RVLFaceLib/src/RFL_MakeTex] baseline: code 10396/10396 data 448 functions 10 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_DataUtility] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_DataUtility] objdiff: code 2244/2244 data 56/116 functions 6/6 fuzzy 100.0000 linked code 2244
[libs/RVLFaceLib/src/RFL_DataUtility] instruction-exact functions: 6/6
[libs/RVLFaceLib/src/RFL_DataUtility]   section .rodata size 16 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section .text size 2244 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section extab size 40 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section extabindex size 60 match 86.0
[libs/RVLFaceLib/src/RFL_DataUtility] baseline: code 2244/2244 data 56 functions 6 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_NWC24] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_NWC24] objdiff: code 2992/2992 data 504/552 functions 5/5 fuzzy 100.0000 linked code 2992
[libs/RVLFaceLib/src/RFL_NWC24] instruction-exact functions: 5/5
[libs/RVLFaceLib/src/RFL_NWC24]   section .data size 472 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section .text size 2992 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section extab size 32 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section extabindex size 48 match 92.5
[libs/RVLFaceLib/src/RFL_NWC24] baseline: code 2992/2992 data 504 functions 5 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_Model] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Model] objdiff: code 7788/7788 data 552/552 functions 15/15 fuzzy 100.0000 linked code 7788
[libs/RVLFaceLib/src/RFL_Model] instruction-exact functions: 15/15
[libs/RVLFaceLib/src/RFL_Model]   section .data size 16 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .rodata size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .sdata2 size 64 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .text size 7788 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extab size 80 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extabindex size 120 match 100.0
[libs/RVLFaceLib/src/RFL_Model] baseline: code 7788/7788 data 552 functions 15 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_Database] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Database] objdiff: code 7508/7508 data 688/688 functions 39/39 fuzzy 100.0000 linked code 7508
[libs/RVLFaceLib/src/RFL_Database] instruction-exact functions: 38/39
[libs/RVLFaceLib/src/RFL_Database]   section .sdata2 size 8 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section .text size 7508 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extab size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extabindex size 408 match 100.0
[libs/RVLFaceLib/src/RFL_Database] baseline: code 7508/7508 data 688 functions 39 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.07103 -> 63.07103
global matched_data_percent: 97.78074 -> 97.78074
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Independent address audit passed on the actual git diff. The RFL_Model range beginning 0x81330970 and all neighboring unowned ranges retain origin/main names exactly. MakeTex was checked before edits and still had 448/544 matched data, so its eight unwind entries required pairing.

## Fresh report and instruction audit

All 1023 unowned units have identical measures, function results and section results before/after, including Model, Database, HiddenDatabase and NANDLoader. All owned sections are 100%.
- RFL_MiddleDatabase updateHDBcallback_: src 0x1e8 base 0x1e8 insns 122/122; diffs 0: []
- RFL_MiddleDatabase loadHiddenDataSync_: src 0x174 base 0x174 insns 93/93; diffs 0: []
- RFL_MiddleDatabase updateHiddenOld_: src 0x154 base 0x154 insns 85/85; diffs 0: []
- RFL_MiddleDatabase loadHiddenRandomSync_: src 0x13c base 0x13c insns 79/79; diffs 0: []
- RFL_MiddleDatabase updateHDBRandcallback_: src 0x194 base 0x194 insns 101/101; diffs 0: []
- RFL_MiddleDatabase updateHiddenRandom_: src 0x2dc base 0x2dc insns 183/183; diffs 0: []
- RFL_MiddleDatabase updateRandom_: src 0xf8 base 0xf8 insns 62/62; diffs 0: []
- RFL_MiddleDatabase RFLGetMiddleDBBufferSize: src 0x8 base 0x8 insns 2/2; diffs 0: []
- RFL_MiddleDatabase RFLInitMiddleDB: src 0xac base 0xac insns 43/43; diffs 0: []
- RFL_MiddleDatabase RFLUpdateMiddleDBAsync: src 0x5c base 0x5c insns 23/23; diffs 0: []
- RFL_MiddleDatabase RFLiUpdateMiddleDBAsync: src 0x138 base 0x138 insns 78/78; diffs 0: []
- RFL_MiddleDatabase RFLGetMiddleDBStoredSize: src 0x8 base 0x8 insns 2/2; diffs 0: []
- RFL_MiddleDatabase RFLiGetCharInfoMiddleDB: src 0x9c base 0x9c insns 39/39; diffs 0: []
libs/RVLFaceLib/src/RFL_MiddleDatabase: data 80 -> 200/200; instruction-exact 13 -> 13; code 3648 -> 3648/3648.
- RFL_MakeTex RFLiSetupCopyTex: src 0x130 base 0x130 insns 76/76; diffs 0: []
- RFL_MakeTex RFLiMakeTexture: src 0x1088 base 0x1088 insns 1058/1058; diffs 0: []
- RFL_MakeTex RFLiSetup2DCameraAndParam: src 0x1d8 base 0x1d8 insns 118/118; diffs 0: []
- RFL_MakeTex RFLiSetTev4Mouth: src 0x248 base 0x248 insns 146/146; diffs 0: []
- RFL_MakeTex RFLiSetTev4Eye: src 0x2b0 base 0x2b0 insns 172/172; diffs 0: []
- RFL_MakeTex RFLiSetFaceParts: src 0x508 base 0x508 insns 322/322; diffs 0: []
- RFL_MakeTex RFLiCapture: src 0x86c base 0x86c insns 539/539; diffs 0: []
- RFL_MakeTex RFLiDrawQuad: src 0x1f8 base 0x1f8 insns 126/126; diffs 0: []
- RFL_MakeTex RFLiGetMaxMaskRsl: src 0x68 base 0x68 insns 26/26; diffs 0: []
- RFL_MakeTex RFLiGetMaskBufSize: src 0x40 base 0x40 insns 16/16; diffs 0: []
libs/RVLFaceLib/src/RFL_MakeTex: data 448 -> 544/544; instruction-exact 10 -> 10; code 10396 -> 10396/10396.
- RFL_DataUtility copyChar2Additional_: src 0x190 base 0x190 insns 100/100; diffs 0: []
- RFL_DataUtility RFLiCheckValidInfo: src 0x464 base 0x464 insns 281/281; diffs 0: []
- RFL_DataUtility RFLiIsValidOnNAND: src 0x2c base 0x2c insns 11/11; diffs 0: []
- RFL_DataUtility RFLiIsSameFaceCore: src 0x110 base 0x110 insns 68/68; diffs 0: []
- RFL_DataUtility RFLiPickupCharInfo: src 0x140 base 0x140 insns 80/80; diffs 0: []
- RFL_DataUtility RFLGetAdditionalInfo: src 0x54 base 0x54 insns 21/21; diffs 0: []
libs/RVLFaceLib/src/RFL_DataUtility: data 56 -> 116/116; instruction-exact 6 -> 6; code 2244 -> 2244/2244.
- RFL_NWC24 RFLiNWC24Msg2CharData: src 0x78 base 0x78 insns 30/30; diffs 0: []
- RFL_NWC24 RFLiSetOfficial2NWC24Msg: src 0xd8 base 0xd8 insns 54/54; diffs 0: []
- RFL_NWC24 RFLiNWC24Msg2HiddenAsync: src 0x188 base 0x188 insns 98/98; diffs 0: []
- RFL_NWC24 makeNWC24MsgforExchange_: src 0x8d0 base 0x8d0 insns 564/564; diffs 0: []
- RFL_NWC24 RFLiMakeNWC24MsgforExchange: src 0x8 base 0x8 insns 2/2; diffs 0: []
libs/RVLFaceLib/src/RFL_NWC24: data 504 -> 552/552; instruction-exact 5 -> 5; code 2992 -> 2992/2992.

Remaining owned target nonmatching functions: none. Uncertain mappings: none.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLFaceLib/src/RFL_MiddleDatabase] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_MiddleDatabase] objdiff: code 3648/3648 data 200/200 functions 13/13 fuzzy 100.0000 linked code 3648
[libs/RVLFaceLib/src/RFL_MiddleDatabase] instruction-exact functions: 13/13
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section .text size 3648 match 100.0
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section extab size 80 match 100.0
[libs/RVLFaceLib/src/RFL_MiddleDatabase]   section extabindex size 120 match 100.0
[libs/RVLFaceLib/src/RFL_MiddleDatabase] baseline: code 3648/3648 data 80 functions 13 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_MakeTex] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_MakeTex] objdiff: code 10396/10396 data 544/544 functions 10/10 fuzzy 100.0000 linked code 10396
[libs/RVLFaceLib/src/RFL_MakeTex] instruction-exact functions: 10/10
[libs/RVLFaceLib/src/RFL_MakeTex]   section .rodata size 192 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section .sdata2 size 192 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section .text size 10396 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section extab size 64 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex]   section extabindex size 96 match 100.0
[libs/RVLFaceLib/src/RFL_MakeTex] baseline: code 10396/10396 data 448 functions 10 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_DataUtility] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_DataUtility] objdiff: code 2244/2244 data 116/116 functions 6/6 fuzzy 100.0000 linked code 2244
[libs/RVLFaceLib/src/RFL_DataUtility] instruction-exact functions: 6/6
[libs/RVLFaceLib/src/RFL_DataUtility]   section .rodata size 16 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section .text size 2244 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section extab size 40 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility]   section extabindex size 60 match 100.0
[libs/RVLFaceLib/src/RFL_DataUtility] baseline: code 2244/2244 data 56 functions 6 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_NWC24] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_NWC24] objdiff: code 2992/2992 data 552/552 functions 5/5 fuzzy 100.0000 linked code 2992
[libs/RVLFaceLib/src/RFL_NWC24] instruction-exact functions: 5/5
[libs/RVLFaceLib/src/RFL_NWC24]   section .data size 472 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section .text size 2992 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section extab size 32 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24]   section extabindex size 48 match 100.0
[libs/RVLFaceLib/src/RFL_NWC24] baseline: code 2992/2992 data 504 functions 5 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_Model] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Model] objdiff: code 7788/7788 data 552/552 functions 15/15 fuzzy 100.0000 linked code 7788
[libs/RVLFaceLib/src/RFL_Model] instruction-exact functions: 15/15
[libs/RVLFaceLib/src/RFL_Model]   section .data size 16 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .rodata size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .sdata2 size 64 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section .text size 7788 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extab size 80 match 100.0
[libs/RVLFaceLib/src/RFL_Model]   section extabindex size 120 match 100.0
[libs/RVLFaceLib/src/RFL_Model] baseline: code 7788/7788 data 552 functions 15 fuzzy 100.0000
[libs/RVLFaceLib/src/RFL_Database] pool: IDENTICAL
[libs/RVLFaceLib/src/RFL_Database] objdiff: code 7508/7508 data 688/688 functions 39/39 fuzzy 100.0000 linked code 7508
[libs/RVLFaceLib/src/RFL_Database] instruction-exact functions: 38/39
[libs/RVLFaceLib/src/RFL_Database]   section .sdata2 size 8 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section .text size 7508 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extab size 272 match 100.0
[libs/RVLFaceLib/src/RFL_Database]   section extabindex size 408 match 100.0
[libs/RVLFaceLib/src/RFL_Database] baseline: code 7508/7508 data 688 functions 39 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.07103 -> 63.07103
global matched_data_percent: 97.78074 -> 97.79842
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
