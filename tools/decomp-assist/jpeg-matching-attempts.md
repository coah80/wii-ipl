# JPEG matching attempts

Baseline full gate passes. All five units start with zero instruction-exact functions and zero objdiff matched code/data bytes.

## Texture_MCUtoY8U8V8

TMCJPEGDEC_set_converterY8U8V8: five distinct attempts, word-sized buffer indexing, pointer stores before function stores, state load before component load, local declaration order, remainder/division operand order. All retained 195 instructions versus 196 target; buffer base folding and register allocation remain. Reverted.

TMCJPEG_814F3158: shared tile/pixel offsets with column postincrement reduced 275 instructions to the target 99. Moving loop declarations to function scope reduced 76 differences to 66. Declaration-order experiments reduced this to 18. Swapping luminance and Cr texture declarations left 11 differences; swapping row skip and Cr row output declarations produced zero. Objdiff 100 percent; clean full gate passes.

## Texture_MCUtoRGB565

TMCJPEGDEC_converterYUV400toRGB565: target and source have 70 instructions. Advancing the y parameter instead of a row local increased differences from 9 to 10. Reordering pointer initialization and moving column/tile row declarations to loop scope increased differences to 23. Explicit row offsets, alternate pointer arithmetic and scoped declarations did not improve the original. Flat declaration order reduced 9 differences to 4. Explicit tileY and rowOffset locals made no further change and were reverted. Remaining differences are srawi/row-offset register allocation at instructions 15, 16, 17 and 19. Objdiff 99.71429 percent.

TMCJPEG_814F32E4: porting the exact YUV444 declaration order and shared offset loop, retaining the edge width/height branches, produced 112/112 instructions and zero differences on the first attempt. Objdiff 100 percent; gate passes.

Grayscale sibling port: RGB565 normal and edge loops each retained four register differences after copying the declaration/loop shape. Computing the row output pointer before the tile-row product removed all four, yielding 70/70 and 83/83 instructions with zero differences. RGBA8 initially had 16 differences after the port; the same statement order plus cycling blue, yEnd and tileWidth declarations produced 76/76 and 89/89 instructions with zero differences. The full gate over all three converters passes with zero regressions, no forbidden patterns, no readability warnings and the target DOL hash.

## Remaining-function sweeps

Each row records a separately built source variant and its fresh exact-name objdiff score. The ctxdiff instruction counts are included. Rejected variants were restored; only increases were retained.

### Texture_MCUtoY8U8V8

| Function | Attempt | Before percent | After percent | Instructions |
| --- | --- | --- | --- | --- |
| TMCJPEG_814EFEAC | source pointer walks | 52.233147 | 52.233147 | src 0x548 base 0x590 insns 338/356 |
| TMCJPEG_814EFEAC | column declared at function scope | 52.233147 | 52.373596 | src 0x548 base 0x590 insns 338/356 |
| TMCJPEG_814EFEAC | x/y bound initialization order | 52.233147 | 52.233147 | src 0x548 base 0x590 insns 338/356 |
| TMCJPEG_814EFEAC | arithmetic operand order | 52.233147 | 52.233147 | src 0x548 base 0x590 insns 338/356 |
| TMCJPEG_814EFEAC | texture and tile width declaration order | 52.233147 | 52.261234 | src 0x548 base 0x590 insns 338/356 |
| TMCJPEG_814F043C | source pointer walks | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F043C | column declared at function scope | 51.3555 | 52.51151 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F043C | x/y bound initialization order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F043C | arithmetic operand order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F043C | texture and tile width declaration order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F0A58 | source pointer walks | 43.534737 | 43.534737 | src 0x774 base 0x76c insns 477/475 |
| TMCJPEG_814F0A58 | column declared at function scope | 43.534737 | 43.55579 | src 0x774 base 0x76c insns 477/475 |
| TMCJPEG_814F0A58 | x/y bound initialization order | 43.534737 | 43.534737 | src 0x774 base 0x76c insns 477/475 |
| TMCJPEG_814F0A58 | arithmetic operand order | 43.534737 | 43.534737 | src 0x774 base 0x76c insns 477/475 |
| TMCJPEG_814F0A58 | texture and tile width declaration order | 43.534737 | 43.534737 | src 0x774 base 0x76c insns 477/475 |
| TMCJPEG_814F11C4 | source pointer walks | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F11C4 | column declared at function scope | 51.3555 | 52.51151 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F11C4 | x/y bound initialization order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F11C4 | arithmetic operand order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F11C4 | texture and tile width declaration order | 51.3555 | 51.3555 | src 0x61c base 0x61c insns 391/391 |
| TMCJPEG_814F17E0 | source pointer walks | 41.890297 | 41.890297 | src 0x76c base 0x768 insns 475/474 |
| TMCJPEG_814F17E0 | column declared at function scope | 41.890297 | 41.890297 | src 0x76c base 0x768 insns 475/474 |
| TMCJPEG_814F17E0 | x/y bound initialization order | 41.890297 | 41.890297 | src 0x76c base 0x768 insns 475/474 |
| TMCJPEG_814F17E0 | arithmetic operand order | 41.890297 | 41.890297 | src 0x76c base 0x768 insns 475/474 |
| TMCJPEG_814F17E0 | texture and tile width declaration order | 41.890297 | 41.890297 | src 0x76c base 0x768 insns 475/474 |
| TMCJPEG_814F1F48 | source pointer walks | 46.809643 | 46.809643 | src 0x640 base 0x628 insns 400/394 |
| TMCJPEG_814F1F48 | column declared at function scope | 46.809643 | 49.791878 | src 0x640 base 0x628 insns 400/394 |
| TMCJPEG_814F1F48 | x/y bound initialization order | 46.809643 | 46.809643 | src 0x640 base 0x628 insns 400/394 |
| TMCJPEG_814F1F48 | arithmetic operand order | 46.809643 | 46.809643 | src 0x640 base 0x628 insns 400/394 |
| TMCJPEG_814F1F48 | texture and tile width declaration order | 46.809643 | 46.588833 | src 0x640 base 0x628 insns 400/394 |
| TMCJPEG_814F2570 | source pointer walks | 47.06383 | 47.06383 | src 0x5e0 base 0x5e0 insns 376/376 |
| TMCJPEG_814F2570 | column declared at function scope | 47.06383 | 47.10372 | src 0x5e0 base 0x5e0 insns 376/376 |
| TMCJPEG_814F2570 | x/y bound initialization order | 47.06383 | 47.06383 | src 0x5e0 base 0x5e0 insns 376/376 |
| TMCJPEG_814F2570 | arithmetic operand order | 47.06383 | 47.06383 | src 0x5e0 base 0x5e0 insns 376/376 |
| TMCJPEG_814F2570 | texture and tile width declaration order | 47.06383 | 47.06383 | src 0x5e0 base 0x5e0 insns 376/376 |
| TMCJPEG_814F2B50 | source pointer walks | 52.95078 | 52.95078 | src 0x604 base 0x608 insns 385/386 |
| TMCJPEG_814F2B50 | column declared at function scope | 52.95078 | 53.634716 | src 0x604 base 0x608 insns 385/386 |
| TMCJPEG_814F2B50 | x/y bound initialization order | 52.95078 | 52.95078 | src 0x604 base 0x608 insns 385/386 |
| TMCJPEG_814F2B50 | arithmetic operand order | 52.95078 | 52.95078 | src 0x604 base 0x608 insns 385/386 |
| TMCJPEG_814F2B50 | texture and tile width declaration order | 52.95078 | 52.95078 | src 0x604 base 0x608 insns 385/386 |
| TMCJPEG_814F34A4 | source pointer walks | 60.037037 | 60.098766 | src 0x24c base 0x288 insns 147/162 |
| TMCJPEG_814F34A4 | column declared at function scope | 60.037037 | 59.512344 | src 0x24c base 0x288 insns 147/162 |
| TMCJPEG_814F34A4 | x/y bound initialization order | 60.037037 | 59.728394 | src 0x24c base 0x288 insns 147/162 |
| TMCJPEG_814F34A4 | arithmetic operand order | 60.037037 | 60.037037 | src 0x24c base 0x288 insns 147/162 |
| TMCJPEG_814F34A4 | texture and tile width declaration order | 60.037037 | 60.037037 | src 0x24c base 0x288 insns 147/162 |
| TMCJPEG_814F372C | source pointer walks | 62.89143 | 62.89143 | src 0x280 base 0x2bc insns 160/175 |
| TMCJPEG_814F372C | column declared at function scope | 62.89143 | 62.92 | src 0x280 base 0x2bc insns 160/175 |
| TMCJPEG_814F372C | x/y bound initialization order | 62.89143 | 62.605713 | src 0x280 base 0x2bc insns 160/175 |
| TMCJPEG_814F372C | arithmetic operand order | 62.89143 | 62.89143 | src 0x280 base 0x2bc insns 160/175 |
| TMCJPEG_814F372C | texture and tile width declaration order | 62.89143 | 62.89143 | src 0x280 base 0x2bc insns 160/175 |

### Texture_MCUtoRGB565

| Function | Attempt | Before percent | After percent | Instructions |
| --- | --- | --- | --- | --- |
| TMCJPEGDEC_set_converterRGB565 | state load before component | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGB565 | pointer stores before converter stores | 93.63529 | 93.86471 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGB565 | dimension operand order | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGB565 | base local declaration order | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_converterYUV411toRGB565 | source pointer walks | 72.79723 | 72.46083 | src 0x364 base 0x364 insns 217/217 |
| TMCJPEGDEC_converterYUV411toRGB565 | column declared at function scope | 72.79723 | 72.77419 | src 0x364 base 0x364 insns 217/217 |
| TMCJPEGDEC_converterYUV411toRGB565 | x/y bound initialization order | 72.79723 | 72.79723 | src 0x364 base 0x364 insns 217/217 |
| TMCJPEGDEC_converterYUV411toRGB565 | arithmetic operand order | 72.79723 | 74.23963 | src 0x364 base 0x364 insns 217/217 |
| TMCJPEGDEC_converterYUV411toRGB565 | texture and tile width declaration order | 72.79723 | 72.79723 | src 0x364 base 0x364 insns 217/217 |
| TMCJPEGDEC_converterYUV411toRGB565edge | source pointer walks | 80.92453 | 81.396225 | src 0x1b4 base 0x1a8 insns 109/106 |
| TMCJPEGDEC_converterYUV411toRGB565edge | column declared at function scope | 80.92453 | 82.85849 | src 0x1b4 base 0x1a8 insns 109/106 |
| TMCJPEGDEC_converterYUV411toRGB565edge | x/y bound initialization order | 80.92453 | 80.92453 | src 0x1b4 base 0x1a8 insns 109/106 |
| TMCJPEGDEC_converterYUV411toRGB565edge | arithmetic operand order | 80.92453 | 79.20755 | src 0x1b4 base 0x1a8 insns 109/106 |
| TMCJPEGDEC_converterYUV411toRGB565edge | texture and tile width declaration order | 80.92453 | 80.830185 | src 0x1b4 base 0x1a8 insns 109/106 |
| TMCJPEGDEC_converterYUV422toRGB565 | source pointer walks | 76.58088 | 75.33088 | src 0x220 base 0x220 insns 136/136 |
| TMCJPEGDEC_converterYUV422toRGB565 | column declared at function scope | 76.58088 | 78.117645 | src 0x220 base 0x220 insns 136/136 |
| TMCJPEGDEC_converterYUV422toRGB565 | x/y bound initialization order | 76.58088 | 76.58088 | src 0x220 base 0x220 insns 136/136 |
| TMCJPEGDEC_converterYUV422toRGB565 | arithmetic operand order | 76.58088 | 75.68382 | src 0x220 base 0x220 insns 136/136 |
| TMCJPEGDEC_converterYUV422toRGB565 | texture and tile width declaration order | 76.58088 | 76.58088 | src 0x220 base 0x220 insns 136/136 |
| TMCJPEGDEC_converterYUV422toRGB565edge | source pointer walks | 80.794395 | 74.53271 | src 0x1b8 base 0x1ac insns 110/107 |
| TMCJPEGDEC_converterYUV422toRGB565edge | column declared at function scope | 80.794395 | 82.66355 | src 0x1b8 base 0x1ac insns 110/107 |
| TMCJPEGDEC_converterYUV422toRGB565edge | x/y bound initialization order | 80.794395 | 80.794395 | src 0x1b8 base 0x1ac insns 110/107 |
| TMCJPEGDEC_converterYUV422toRGB565edge | arithmetic operand order | 80.794395 | 78.76636 | src 0x1b8 base 0x1ac insns 110/107 |
| TMCJPEGDEC_converterYUV422toRGB565edge | texture and tile width declaration order | 80.794395 | 80.700935 | src 0x1b8 base 0x1ac insns 110/107 |
| TMCJPEGDEC_converterYUV420toRGB565 | source pointer walks | 77.375885 | 75.992905 | src 0x234 base 0x234 insns 141/141 |
| TMCJPEGDEC_converterYUV420toRGB565 | column declared at function scope | 77.375885 | 77.23404 | src 0x234 base 0x234 insns 141/141 |
| TMCJPEGDEC_converterYUV420toRGB565 | x/y bound initialization order | 77.375885 | 77.30496 | src 0x234 base 0x234 insns 141/141 |
| TMCJPEGDEC_converterYUV420toRGB565 | arithmetic operand order | 77.375885 | 76.510635 | src 0x234 base 0x234 insns 141/141 |
| TMCJPEGDEC_converterYUV420toRGB565 | texture and tile width declaration order | 77.375885 | 77.23404 | src 0x234 base 0x234 insns 141/141 |
| TMCJPEGDEC_converterYUV420toRGB565edge | source pointer walks | 83.289474 | 83.72807 | src 0x1d4 base 0x1c8 insns 117/114 |
| TMCJPEGDEC_converterYUV420toRGB565edge | column declared at function scope | 83.289474 | 83.42105 | src 0x1d4 base 0x1c8 insns 117/114 |
| TMCJPEGDEC_converterYUV420toRGB565edge | x/y bound initialization order | 83.289474 | 83.289474 | src 0x1d4 base 0x1c8 insns 117/114 |
| TMCJPEGDEC_converterYUV420toRGB565edge | arithmetic operand order | 83.289474 | 81.51755 | src 0x1d4 base 0x1c8 insns 117/114 |
| TMCJPEGDEC_converterYUV420toRGB565edge | texture and tile width declaration order | 83.289474 | 83.20175 | src 0x1d4 base 0x1c8 insns 117/114 |
| TMCJPEGDEC_converterYUV211toRGB565 | source pointer walks | 73.05102 | 73.765305 | src 0x188 base 0x188 insns 98/98 |
| TMCJPEGDEC_converterYUV211toRGB565 | column declared at function scope | 73.05102 | 75.33673 | src 0x188 base 0x188 insns 98/98 |
| TMCJPEGDEC_converterYUV211toRGB565 | x/y bound initialization order | 73.05102 | 73.05102 | src 0x188 base 0x188 insns 98/98 |
| TMCJPEGDEC_converterYUV211toRGB565 | arithmetic operand order | 73.05102 | 69.66327 | src 0x188 base 0x188 insns 98/98 |
| TMCJPEGDEC_converterYUV211toRGB565 | texture and tile width declaration order | 73.05102 | 72.94898 | src 0x188 base 0x188 insns 98/98 |
| TMCJPEGDEC_converterYUV211toRGB565edge | source pointer walks | 77.23853 | 77.88074 | src 0x1b4 base 0x1b4 insns 109/109 |
| TMCJPEGDEC_converterYUV211toRGB565edge | column declared at function scope | 77.23853 | 79.16514 | src 0x1b4 base 0x1b4 insns 109/109 |
| TMCJPEGDEC_converterYUV211toRGB565edge | x/y bound initialization order | 77.23853 | 77.23853 | src 0x1b4 base 0x1b4 insns 109/109 |
| TMCJPEGDEC_converterYUV211toRGB565edge | arithmetic operand order | 77.23853 | 74.19266 | src 0x1b4 base 0x1b4 insns 109/109 |
| TMCJPEGDEC_converterYUV211toRGB565edge | texture and tile width declaration order | 77.23853 | 77.23853 | src 0x1b4 base 0x1b4 insns 109/109 |
| TMCJPEGDEC_converterYUV444toRGB565 | source pointer walks | 73.50549 | 74.27473 | src 0x16c base 0x16c insns 91/91 |
| TMCJPEGDEC_converterYUV444toRGB565 | column declared at function scope | 73.50549 | 73.61539 | src 0x16c base 0x16c insns 91/91 |
| TMCJPEGDEC_converterYUV444toRGB565 | x/y bound initialization order | 73.50549 | 73.50549 | src 0x16c base 0x16c insns 91/91 |
| TMCJPEGDEC_converterYUV444toRGB565 | arithmetic operand order | 73.50549 | 69.85714 | src 0x16c base 0x16c insns 91/91 |
| TMCJPEGDEC_converterYUV444toRGB565 | texture and tile width declaration order | 73.50549 | 73.50549 | src 0x16c base 0x16c insns 91/91 |
| TMCJPEGDEC_converterYUV444toRGB565edge | source pointer walks | 76.48077 | 77.15385 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV444toRGB565edge | column declared at function scope | 76.48077 | 78.45192 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV444toRGB565edge | x/y bound initialization order | 76.48077 | 76.48077 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV444toRGB565edge | arithmetic operand order | 76.48077 | 73.28846 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV444toRGB565edge | texture and tile width declaration order | 76.48077 | 76.48077 | src 0x1a0 base 0x1a0 insns 104/104 |

### Texture_MCUtoRGBA8

| Function | Attempt | Before percent | After percent | Instructions |
| --- | --- | --- | --- | --- |
| TMCJPEGDEC_set_converterRGBA8 | state load before component | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGBA8 | pointer stores before converter stores | 93.63529 | 93.86471 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGBA8 | dimension operand order | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_set_converterRGBA8 | base local declaration order | 93.63529 | 93.63529 | src 0x2a4 base 0x2a8 insns 169/170 |
| TMCJPEGDEC_converterYUV411toRGBA8 | source pointer walks | 65.8719 | 69.44215 | src 0x3c8 base 0x3c8 insns 242/242 |
| TMCJPEGDEC_converterYUV411toRGBA8 | column declared at function scope | 65.8719 | 64.921486 | src 0x3c8 base 0x3c8 insns 242/242 |
| TMCJPEGDEC_converterYUV411toRGBA8 | x/y bound initialization order | 65.8719 | 65.19009 | src 0x3c8 base 0x3c8 insns 242/242 |
| TMCJPEGDEC_converterYUV411toRGBA8 | arithmetic operand order | 65.8719 | 65.86777 | src 0x3c8 base 0x3c8 insns 242/242 |
| TMCJPEGDEC_converterYUV411toRGBA8 | texture and tile width declaration order | 65.8719 | 65.14876 | src 0x3c8 base 0x3c8 insns 242/242 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | source pointer walks | 71.54464 | 67.97321 | src 0x1cc base 0x1c0 insns 115/112 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | column declared at function scope | 71.54464 | 71.90179 | src 0x1cc base 0x1c0 insns 115/112 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | x/y bound initialization order | 71.54464 | 71.54464 | src 0x1cc base 0x1c0 insns 115/112 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | arithmetic operand order | 71.54464 | 71.48214 | src 0x1cc base 0x1c0 insns 115/112 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | texture and tile width declaration order | 71.54464 | 71.54464 | src 0x1cc base 0x1c0 insns 115/112 |
| TMCJPEGDEC_converterYUV422toRGBA8 | source pointer walks | 66.48649 | 67.58108 | src 0x250 base 0x250 insns 148/148 |
| TMCJPEGDEC_converterYUV422toRGBA8 | column declared at function scope | 66.48649 | 66.28378 | src 0x250 base 0x250 insns 148/148 |
| TMCJPEGDEC_converterYUV422toRGBA8 | x/y bound initialization order | 66.48649 | 67.77027 | src 0x250 base 0x250 insns 148/148 |
| TMCJPEGDEC_converterYUV422toRGBA8 | arithmetic operand order | 66.48649 | 66.3446 | src 0x250 base 0x250 insns 148/148 |
| TMCJPEGDEC_converterYUV422toRGBA8 | texture and tile width declaration order | 66.48649 | 66.28378 | src 0x250 base 0x250 insns 148/148 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | source pointer walks | 68.61062 | 67.530975 | src 0x1d0 base 0x1c4 insns 116/113 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | column declared at function scope | 68.61062 | 70.42478 | src 0x1d0 base 0x1c4 insns 116/113 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | x/y bound initialization order | 68.61062 | 68.61062 | src 0x1d0 base 0x1c4 insns 116/113 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | arithmetic operand order | 68.61062 | 68.59292 | src 0x1d0 base 0x1c4 insns 116/113 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | texture and tile width declaration order | 68.61062 | 68.522125 | src 0x1d0 base 0x1c4 insns 116/113 |
| TMCJPEGDEC_converterYUV420toRGBA8 | source pointer walks | 69.745094 | 71.03268 | src 0x264 base 0x264 insns 153/153 |
| TMCJPEGDEC_converterYUV420toRGBA8 | column declared at function scope | 69.745094 | 70.00654 | src 0x264 base 0x264 insns 153/153 |
| TMCJPEGDEC_converterYUV420toRGBA8 | x/y bound initialization order | 69.745094 | 69.810455 | src 0x264 base 0x264 insns 153/153 |
| TMCJPEGDEC_converterYUV420toRGBA8 | arithmetic operand order | 69.745094 | 69.77124 | src 0x264 base 0x264 insns 153/153 |
| TMCJPEGDEC_converterYUV420toRGBA8 | texture and tile width declaration order | 69.745094 | 69.87582 | src 0x264 base 0x264 insns 153/153 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | source pointer walks | 74.191666 | 74.60833 | src 0x1ec base 0x1e0 insns 123/120 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | column declared at function scope | 74.191666 | 74.191666 | src 0x1ec base 0x1e0 insns 123/120 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | x/y bound initialization order | 74.191666 | 74.191666 | src 0x1ec base 0x1e0 insns 123/120 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | arithmetic operand order | 74.191666 | 74.175 | src 0x1ec base 0x1e0 insns 123/120 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | texture and tile width declaration order | 74.191666 | 74.275 | src 0x1ec base 0x1e0 insns 123/120 |
| TMCJPEGDEC_converterYUV211toRGBA8 | source pointer walks | 69.48077 | 71.04808 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV211toRGBA8 | column declared at function scope | 69.48077 | 69.91346 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV211toRGBA8 | x/y bound initialization order | 69.48077 | 69.48077 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV211toRGBA8 | arithmetic operand order | 69.48077 | 66.09615 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV211toRGBA8 | texture and tile width declaration order | 69.48077 | 69.76923 | src 0x1a0 base 0x1a0 insns 104/104 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | source pointer walks | 73.96522 | 75.38261 | src 0x1cc base 0x1cc insns 115/115 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | column declared at function scope | 73.96522 | 75.92174 | src 0x1cc base 0x1cc insns 115/115 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | x/y bound initialization order | 73.96522 | 73.96522 | src 0x1cc base 0x1cc insns 115/115 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | arithmetic operand order | 73.96522 | 70.90435 | src 0x1cc base 0x1cc insns 115/115 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | texture and tile width declaration order | 73.96522 | 74.05218 | src 0x1cc base 0x1cc insns 115/115 |
| TMCJPEGDEC_converterYUV444toRGBA8 | source pointer walks | 70.08247 | 71.762886 | src 0x184 base 0x184 insns 97/97 |
| TMCJPEGDEC_converterYUV444toRGBA8 | column declared at function scope | 70.08247 | 70.18557 | src 0x184 base 0x184 insns 97/97 |
| TMCJPEGDEC_converterYUV444toRGBA8 | x/y bound initialization order | 70.08247 | 70.08247 | src 0x184 base 0x184 insns 97/97 |
| TMCJPEGDEC_converterYUV444toRGBA8 | arithmetic operand order | 70.08247 | 66.453606 | src 0x184 base 0x184 insns 97/97 |
| TMCJPEGDEC_converterYUV444toRGBA8 | texture and tile width declaration order | 70.08247 | 70.18557 | src 0x184 base 0x184 insns 97/97 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | source pointer walks | 73.11818 | 74.6 | src 0x1b8 base 0x1b8 insns 110/110 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | column declared at function scope | 73.11818 | 75.163635 | src 0x1b8 base 0x1b8 insns 110/110 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | x/y bound initialization order | 73.11818 | 73.11818 | src 0x1b8 base 0x1b8 insns 110/110 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | arithmetic operand order | 73.11818 | 69.91818 | src 0x1b8 base 0x1b8 insns 110/110 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | texture and tile width declaration order | 73.11818 | 73.20909 | src 0x1b8 base 0x1b8 insns 110/110 |

### idct_block_var

| Function | Attempt | Before percent | After percent | Instructions |
| --- | --- | --- | --- | --- |
| TMCJPEGDEC_IdctBlock_Lumi | ac operand order | 63.07782 | 63.07782 | src 0x404 base 0x404 insns 257/257 |
| TMCJPEGDEC_IdctBlock_Lumi | butterfly operand grouping | 63.07782 | 66.618675 | src 0x404 base 0x404 insns 257/257 |
| TMCJPEGDEC_IdctBlock_Lumi | first pass row counter form | 63.07782 | 62.55642 | src 0x404 base 0x404 insns 257/257 |
| TMCJPEGDEC_IdctBlock_Lumi | second pass pointer before counter | 63.07782 | 65.33463 | src 0x404 base 0x404 insns 257/257 |
| TMCJPEGDEC_IdctBlock_Lumi | clamp arithmetic sign tests | 63.07782 | 63.07782 | src 0x404 base 0x404 insns 257/257 |
| TMCJPEGDEC_IdctBlock_Col | ac operand order | 69.0859 | 69.0859 | src 0x780 base 0x718 insns 480/454 |
| TMCJPEGDEC_IdctBlock_Col | butterfly operand grouping | 69.0859 | 69.0859 | src 0x780 base 0x718 insns 480/454 |
| TMCJPEGDEC_IdctBlock_Col | first pass row counter form | 69.0859 | 68.90969 | src 0x780 base 0x718 insns 480/454 |
| TMCJPEGDEC_IdctBlock_Col | second pass pointer before counter | 69.0859 | 69.0859 | src 0x780 base 0x718 insns 480/454 |
| TMCJPEGDEC_IdctBlock_Col | clamp arithmetic sign tests | 69.0859 | 69.112335 | src 0x780 base 0x718 insns 480/454 |

### iqdec_b65_frv32

| Function | Attempt | Before percent | After percent | Instructions |
| --- | --- | --- | --- | --- |
| TMCJPEGDEC_decode_iquant | huffman code uses decoded threshold | 84.641304 | 84.641304 | src 0x460 base 0x450 insns 280/276 |
| TMCJPEGDEC_decode_iquant | dc load failure through common return | 84.641304 | 84.71377 | src 0x460 base 0x450 insns 280/276 |
| TMCJPEGDEC_decode_iquant | sign-extension subtraction operand grouping | 84.641304 | 85.11232 | src 0x468 base 0x450 insns 282/276 |
| TMCJPEGDEC_decode_iquant | dc lookup shift temporary combined | 84.641304 | 84.822464 | src 0x460 base 0x450 insns 280/276 |
| TMCJPEGDEC_decode_iquant | dc predictor load before quantizer | 84.641304 | 84.60507 | src 0x460 base 0x450 insns 280/276 |

## Further block translations

Planar grayscale: moving tile row and output row calculations inside the pixel loop changed 147 instructions to 150; explicit tile/pixel offsets kept 150. Making tile-row arithmetic unsigned reproduced the target 162/162 and 175/175 instructions, instead of compiler strength reduction. This is the unsigned product of the tile-row index and the existing unsigned tile width. Remaining differences were register allocation.

Planar 411 chroma: moving row calculations inside the pixel loop still produced 338/356 instructions, so structural differences remain.

RGB565/RGBA8 YUV444: ported the flat local declarations, pointer walking, row output before tile-row calculation, and per-pixel green/red/blue arithmetic in assembly order. Both normal and edge instruction counts agree with their targets. Register/saturation branch choices remain. Explicit clamp branches compiled identically to the ternaries.

Planar grayscale follow-up: declaration order brought both normal and edge functions to 100 percent objdiff, with identical complete raw .text byte slices of 648 and 700 bytes. Existing ctxdiff/gate disassembly reports two false differences for each because odiff.dis reads operand zero of a conditional branch as an immediate; for CR1 branches operand zero is a register, not the branch destination. Their differing source/target object positions leak into the displayed differences. Neither the gate nor its dependencies were modified. The gate's instruction-exact count therefore remains 2/13 for this unit while objdiff correctly reports 4/13.

All remaining functions received at least three separately built source variants, with five attempts for ordinary converters and both IDCT functions and the entropy decoder. Exact functions were kept. This is a partial matching result, not full unit completion or a linking change.

## Final remaining functions

### libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var

TMCJPEGDEC_IdctBlock_Lumi, 66.61867%, 257/257 instructions; 119 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_IdctBlock_Col, 69.11234%, instruction count 480/454; loop/control-flow shape and scheduling remain


### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8

TMCJPEGDEC_set_converterY8U8V8, 92.54082%, instruction count 195/196; loop/control-flow shape and scheduling remain

TMCJPEG_814EFEAC, 53.10112%, instruction count 338/356; loop/control-flow shape and scheduling remain

TMCJPEG_814F043C, 52.51151%, 391/391 instructions; 308 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEG_814F0A58, 43.55579%, instruction count 477/475; loop/control-flow shape and scheduling remain

TMCJPEG_814F11C4, 52.51151%, 391/391 instructions; 308 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEG_814F17E0, 41.89030%, instruction count 475/474; loop/control-flow shape and scheduling remain

TMCJPEG_814F1F48, 49.79188%, instruction count 400/394; loop/control-flow shape and scheduling remain

TMCJPEG_814F2570, 47.10372%, 376/376 instructions; 318 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEG_814F2B50, 53.63472%, instruction count 385/386; loop/control-flow shape and scheduling remain


### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565

TMCJPEGDEC_set_converterRGB565, 93.86471%, instruction count 169/170; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV411toRGB565, 74.23963%, 217/217 instructions; 104 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV411toRGB565edge, 82.85849%, instruction count 109/106; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV422toRGB565, 78.11764%, 136/136 instructions; 59 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV422toRGB565edge, 82.66355%, instruction count 110/107; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV420toRGB565, 77.37588%, 141/141 instructions; 57 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV420toRGB565edge, 83.72807%, instruction count 117/114; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV211toRGB565, 75.33673%, 98/98 instructions; 50 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV211toRGB565edge, 79.16514%, 109/109 instructions; 44 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV444toRGB565, 88.24176%, 91/91 instructions; 17 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV444toRGB565edge, 88.07692%, 104/104 instructions; 17 opcode positions differ, arithmetic/saturation scheduling and register allocation


### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8

TMCJPEGDEC_set_converterRGBA8, 93.86471%, instruction count 169/170; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV411toRGBA8, 69.44215%, 242/242 instructions; 119 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV411toRGBA8edge, 71.90179%, instruction count 115/112; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV422toRGBA8, 67.77027%, 148/148 instructions; 74 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV422toRGBA8edge, 70.42478%, instruction count 116/113; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV420toRGBA8, 71.03268%, 153/153 instructions; 69 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV420toRGBA8edge, 74.60833%, instruction count 123/120; loop/control-flow shape and scheduling remain

TMCJPEGDEC_converterYUV211toRGBA8, 71.04808%, 104/104 instructions; 34 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV211toRGBA8edge, 75.92174%, 115/115 instructions; 50 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV444toRGBA8, 72.38145%, 97/97 instructions; 34 opcode positions differ, arithmetic/saturation scheduling and register allocation

TMCJPEGDEC_converterYUV444toRGBA8edge, 77.60000%, 110/110 instructions; 28 opcode positions differ, arithmetic/saturation scheduling and register allocation


### libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32

TMCJPEGDEC_decode_iquant, 85.11232%, instruction count 282/276; loop/control-flow shape and scheduling remain
