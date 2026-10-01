# JPEG round 5 gates

## First improvement, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1976 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.19764
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 99.01053
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 3736/15948 data None functions 5 fuzzy 99.1976
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.4864 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.48636
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 81.24793
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.69072
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 89.3699
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.2037 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.20375
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.53271
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.60526
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.3460 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.34599
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 81.05058
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 88.3460
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.02564
global fuzzy_match_percent: 98.81924 -> 98.81962
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Restart recovery, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1976 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.19764
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 99.01053
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 3736/15948 data None functions 5 fuzzy 99.1976
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.4864 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.48636
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 81.24793
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.69072
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 89.3699
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.2232 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.22316
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.81309
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.60526
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 98.72449
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.8031 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.80309
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 82.31518
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 88.3460
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.02564
global fuzzy_match_percent: 98.81924 -> 98.82009
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Further converter declaration improvements, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1976 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.19764
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 99.01053
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 3736/15948 data None functions 5 fuzzy 99.1976
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.4985 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.49848
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 81.24793
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.87838
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.4902
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.896904
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 89.3699
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.2555 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.2555
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.81309
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.60526
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 99.234695
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.8031 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.80309
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 82.31518
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 88.3460
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.02564
global fuzzy_match_percent: 98.81924 -> 98.82020
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## RGB211 four-variable order, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1028/6184 data None/None functions 3/13 fuzzy 96.2911 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 3/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.29108
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 99.81309
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.60526
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 99.79592
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.02564
global fuzzy_match_percent: 98.81924 -> 98.82026
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Two new exact converter functions, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1848/6184 data None/None functions 5/13 fuzzy 96.3170 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 5/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.31695
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.60526
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.05302
global fuzzy_match_percent: 98.81924 -> 98.82033
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Port exact row addressing to sibling converters, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1976 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.19764
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 99.01053
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 3736/15948 data None functions 5 fuzzy 99.1976
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.5106 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.51061
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 81.24793
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.945946
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.55556
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.896904
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 89.3699
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 1848/6184 data None/None functions 5/13 fuzzy 96.3234 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 5/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.32342
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.692986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 98.899086
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.05302
global fuzzy_match_percent: 98.81924 -> 98.82037
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## RGB211 edge exact, quick gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 2284/6184 data None/None functions 6/13 fuzzy 96.4010 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 6/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.40103
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.692986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.06757
global fuzzy_match_percent: 98.81924 -> 98.82052
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Final clean full gate, all five units

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1976 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.19764
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 99.01053
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 3736/15948 data None functions 5 fuzzy 99.1976
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 89.5106 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 89.51061
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 81.24793
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 90.80357
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 86.945946
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 87.87611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 88.55556
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.23333
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 90.67308
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 91.82609
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 89.896904
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 89.3699
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 2284/6184 data None/None functions 6/13 fuzzy 96.4010 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 6/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.40103
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.692986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 97.96703
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 1028/6184 data None functions 3 fuzzy 96.1365
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.8031 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 88.80309
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 82.31518
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 92.47577
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 88.3460
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.8333 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.833336
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 86.02564 -> 86.06757
global fuzzy_match_percent: 98.81924 -> 98.82052
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Source commits and changed files

```text
06befa1f match rgb211 edge converter
771e314b port exact jpeg converter row addressing
ed33143a match rgb211 and rgb422 edge converters
8b4b6daa align rgb211 loop register allocation
026be0e8 align jpeg converter local declarations
35d0e3af refine jpeg idct and edge register lifetimes
cdb8a8f0 refine jpeg converter packing and selection
```

```text
libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var.c
libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.c
libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c
libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8.c
tools/decomp-assist/jpeg-round5-attempts.md
tools/decomp-assist/jpeg-round5-gates.md
```

All five allocated data totals are zero. Three new RGB565 functions are instruction-exact, verified by official objdiff 100% and ctxdiff diffs 0. Remaining per-function scores and evidence are in jpeg-round5-attempts.md. The Y8 CR-qualified-branch parser discrepancy is documented there with byte-identical function evidence; objdiff counts five exact functions while the gate counts two. No oracle tool was edited.
