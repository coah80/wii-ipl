# Planar converter translation gates

## 411 normal

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 2192/15948 data None/None functions 4/13 fuzzy 63.9556 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 63.955605
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.7398
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 91.36236
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 57.682865
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 45.19579
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 57.682865
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 44.407173
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 52.16751
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 52.587765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2B50 55.795338
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.69363
global fuzzy_match_percent: 98.04096 -> 98.05914
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Complete loop ports, quick gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 2192/15948 data None/None functions 4/13 fuzzy 88.1116 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 88.11161
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.7398
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 92.89326
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 85.13043
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 79.60842
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 85.13043
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 80.681435
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 88.033
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 90.28723
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2B50 88.06218
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.69363
global fuzzy_match_percent: 98.04096 -> 98.18778
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Complete pixel address expressions, quick gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 2192/15948 data None/None functions 4/13 fuzzy 94.7775 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 94.77753
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.7398
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.255615
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 93.65729
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 95.073685
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 91.79028
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 88.48734
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 92.59644
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 93.723404
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2B50 99.04145
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.69363
global fuzzy_match_percent: 98.04096 -> 98.22327
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

211 edge exact, quick gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 94.8703 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 94.87033
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.7398
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.255615
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 93.65729
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 95.073685
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 91.79028
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 88.48734
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 92.59644
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 93.723404
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.74518
global fuzzy_match_percent: 98.04096 -> 98.22376
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Port the exact 211 edge shape, quick gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 3736/15948 data None/None functions 5/13 fuzzy 99.1402 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.140205
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.7398
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 99.7191
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 98.54737
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 99.4757
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 98.99789
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 99.55584
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 99.58777
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.74518
global fuzzy_match_percent: 98.04096 -> 98.24650
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Final translated setup and chroma headers (quick)

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
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.74518
global fuzzy_match_percent: 98.04096 -> 98.24680
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Final full gate (clean build, non-quick)

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
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 2192/15948 data None functions 4 fuzzy 60.5393
regressions vs baseline: 0
global matched_code_percent: 84.69363 -> 84.74518
global fuzzy_match_percent: 98.04096 -> 98.24680
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.34007 -> 90.34007
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Source commits: 75b91040 align remaining planar setup blocks; 4f97418f port exact planar edge loop shape; 79662a9e match planar 211 edge conversion; 33360af8 align planar tile address expressions; ef73aa9e retranslate planar subsampling loops; f52ddef8 retranslate planar 411 tile addressing;
