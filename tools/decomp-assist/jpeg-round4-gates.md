# JPEG round 4 gates

## RGBA8 color arithmetic and clamp blocks

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 85.6762 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 85.67617
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 82.75
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 78.695946
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 82.66372
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 83.36601
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 80.13461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 85.55652
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 86.19091
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.49917
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## RGB565 color blocks ported from matching templates

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 85.6762 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 85.67617
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 82.75
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 78.695946
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 82.66372
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 83.36601
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 80.13461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 85.55652
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 86.19091
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 91.8984 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 91.898445
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 86.58986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 92.26415
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 86.463234
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 92.47664
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 86.77305
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 90.87719
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 90.39796
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 95.13761
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 96.86813
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 95.72115
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.51353
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## butterfly and entropy blocks

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 85.6107 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 85.61067
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 82.33036
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 78.60135
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 82.24779
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 83.36601
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 80.13461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 85.55652
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 86.19091
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 91.8984 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 91.898445
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 86.58986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 92.26415
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 86.463234
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 92.47664
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 86.77305
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 90.87719
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 90.39796
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 95.13761
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 96.86813
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 95.72115
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 83.8495 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 83.84951
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 77.78989
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 87.27974
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 97.9022 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 97.902176
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 97.902176
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.53204
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## pixel walks and Huffman storage

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 86.4348 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 86.43481
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 84.50893
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 83.060814
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 85.22124
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 83.36601
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 80.13461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 85.55652
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 87.27273
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 92.5809 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 92.58086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 89.00461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 92.26415
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 90.625
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 88.084114
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 88.12057
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 90.70175
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 93.10204
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 95.13761
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 96.86813
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 95.72115
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 83.8495 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 83.84951
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 77.78989
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 87.27974
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.53560
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## IDCT butterfly scheduling

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 86.4348 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 86.43481
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 84.50893
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 83.060814
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 85.22124
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 83.36601
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 80.13461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 85.55652
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 87.27273
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 92.5809 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 92.58086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.86471
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 89.00461
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 92.26415
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 90.625
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 88.084114
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 88.12057
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 90.70175
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 93.10204
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 95.13761
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 96.86813
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 95.72115
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.7159 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.7159
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 82.07393
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.54022
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## color packing and frames

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 88.3099 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 88.30988
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 84.50893
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 85.22124
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 84.73333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 94.5129 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 94.51294
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 92.26415
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 95.29412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 93.2243
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 90.70175
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 95.561226
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 96.60551
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 96.86813
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 97.25961
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.54800
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check7

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 88.7380 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 88.73802
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 85.45536
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 95.1210 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 95.12096
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.09434
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 95.29412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 96.02804
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.333336
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 95.561226
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 96.60551
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.30769
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 97.25961
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.55017
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check8

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 88.7975 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 88.797455
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 86.33036
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 612/6184 data None/None functions 2/13 fuzzy 95.1533 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 95.1533
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.09434
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 95.55147
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 96.02804
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.46491
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 95.561226
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 96.60551
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.30769
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 97.25961
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.41974
global fuzzy_match_percent: 98.48116 -> 98.55039
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check9: first new exact function

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 88.7975 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 88.797455
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 86.33036
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 95.3376 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 95.33765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.09434
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 95.55147
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 96.02804
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.46491
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 95.561226
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 96.60551
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.30769
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55077
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check10: sibling color temporaries

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.0922 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.09218
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.66964
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 95.4314 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 95.431435
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.09434
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 95.55147
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 96.72897
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.46491
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 95.96939
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 96.74312
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.47253
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55160
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check11: converter register declaration searches

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.0922 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.09218
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 79.81405
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.66964
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 87.22222
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.26087
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.43299
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.0589 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.05886
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.48387
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.09434
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.53271
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.46491
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.623856
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.91209
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55291
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## check12: sample types and shared 411 pixel locals

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.3699 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.36992
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 80.47108
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.69072
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.1365 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.13648
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.53271
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.72807
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55368
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## final full gate: clean rebuild of all four owned units

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.3699 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.36992
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 80.47108
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.69072
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.1365 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.13648
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.53271
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.72807
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55368
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## final full gate after dead-initializer cleanup

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.3699 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.36992
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 80.47108
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.69072
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 77.4967
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.1365 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.13648
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.89412
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.53271
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 93.72807
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 612/6184 data None functions 2 fuzzy 84.9515
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 68.2110
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 87.5761
regressions vs baseline: 0
global matched_code_percent: 85.41974 -> 85.43362
global fuzzy_match_percent: 98.48116 -> 98.55368
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.78117 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
