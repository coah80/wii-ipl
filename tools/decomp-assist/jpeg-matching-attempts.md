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

## Continued matching after c923937c

Fresh baseline quick gate: PASS, zero regressions. All five original objects contain only code, with zero data bytes; their string pools are identical. No tables, vtables, or string literals require reconstruction in these units.

| Function | Distinct source attempt | Before percent | After percent | Evidence |
| --- | --- | --- | --- | --- |
| TMCJPEGDEC_set_converterRGB565 | converter stores before row stores | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGB565 | pointer to whole conversion buffer | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGB565 | signed conversion sample pointer | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGB565 | case scoped converter function pointers | 93.864710 | 93.864710 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGB565 | buffer initialized after state and component | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGBA8 | converter stores before row stores | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGBA8 | pointer to whole conversion buffer | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGBA8 | signed conversion sample pointer | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGBA8 | case scoped converter function pointers | 93.864710 | 93.864710 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterRGBA8 | buffer initialized after state and component | 93.864710 | 93.635290 | 169/170 instructions; 169 differences |
| TMCJPEGDEC_set_converterY8U8V8 | converter stores before row stores | 92.540820 | 92.540820 | 195/196 instructions; 195 differences |
| TMCJPEGDEC_set_converterY8U8V8 | pointer to whole conversion buffer | 92.540820 | 92.540820 | 195/196 instructions; 195 differences |
| TMCJPEGDEC_set_converterY8U8V8 | signed conversion sample pointer | 92.540820 | 92.540820 | 195/196 instructions; 195 differences |
| TMCJPEGDEC_set_converterY8U8V8 | case scoped converter function pointers | 92.540820 | 92.739800 | 195/196 instructions; 195 differences |
| TMCJPEGDEC_set_converterY8U8V8 | buffer initialized after state and component | 92.540820 | 92.540820 | 195/196 instructions; 195 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | reuse luminance temporary for blue | 88.241760 | 88.241760 | 91/91 instructions; 49 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | saturation low branch first | 88.241760 | 88.241760 | 91/91 instructions; 49 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | pixel arithmetic locals scoped to pixel loop | 88.241760 | 88.021980 | 91/91 instructions; 53 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | combined saturation mask | 88.241760 | 87.582420 | 91/91 instructions; 50 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | pack green after red and blue sum | 88.241760 | 88.241760 | 91/91 instructions; 49 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | reuse luminance temporary for blue | 88.076920 | 88.076920 | 104/104 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | saturation low branch first | 88.076920 | 88.076920 | 104/104 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | pixel arithmetic locals scoped to pixel loop | 88.076920 | 88.076920 | 104/104 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | combined saturation mask | 88.076920 | 87.500000 | 104/104 instructions; 73 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | pack green after red and blue sum | 88.076920 | 88.076920 | 104/104 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | reuse luminance temporary for blue | 72.381450 | 73.226810 | 97/97 instructions; 76 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | saturation low branch first | 72.381450 | 72.381450 | 97/97 instructions; 78 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | pixel arithmetic locals scoped to pixel loop | 72.381450 | 72.381450 | 97/97 instructions; 78 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | combined saturation mask | 72.381450 | 72.381450 | 97/97 instructions; 78 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | pack green after red and blue sum | 72.381450 | 72.381450 | 97/97 instructions; 78 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | reuse luminance temporary for blue | 77.600000 | 78.345450 | 110/110 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | saturation low branch first | 77.600000 | 77.600000 | 110/110 instructions; 74 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | pixel arithmetic locals scoped to pixel loop | 77.600000 | 77.600000 | 110/110 instructions; 74 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | combined saturation mask | 77.600000 | 77.600000 | 110/110 instructions; 74 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | pack green after red and blue sum | 77.600000 | 77.600000 | 110/110 instructions; 74 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | saturation block with early break | 88.241760 | 88.241760 | 91/91 instructions; 49 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | negative mask before saturation decision | 88.241760 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | unsigned upper bound following negative clamp | 88.241760 | 85.879120 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | saturation block with early break | 88.076920 | 88.076920 | 104/104 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | negative mask before saturation decision | 88.076920 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | unsigned upper bound following negative clamp | 88.076920 | 86.009610 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | saturation block with early break | 73.226810 | 73.226810 | 97/97 instructions; 76 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | negative mask before saturation decision | 73.226810 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | unsigned upper bound following negative clamp | 73.226810 | 73.690720 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | saturation block with early break | 78.345450 | 78.345450 | 110/110 instructions; 72 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | negative mask before saturation decision | 78.345450 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | unsigned upper bound following negative clamp | 78.345450 | 78.754550 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | row output pointer before tile product | 83.728070 | 83.640350 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | green pixel sum before red pixel sum | 83.728070 | 83.859650 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | explicit saturation branches in each pixel | 83.728070 | 83.728070 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | named output pixel offset before each store | 83.728070 | 83.728070 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | signed chroma source pointers | 83.728070 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | row output pointer before tile product | 82.858490 | 82.858490 | 109/106 instructions; 100 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | green pixel sum before red pixel sum | 82.858490 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | explicit saturation branches in each pixel | 82.858490 | 82.858490 | 109/106 instructions; 100 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | named output pixel offset before each store | 82.858490 | 82.858490 | 109/106 instructions; 100 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | signed chroma source pointers | 82.858490 | 82.716980 | 109/106 instructions; 100 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | row output pointer before tile product | 82.663550 | 82.663550 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | green pixel sum before red pixel sum | 82.663550 | 82.710280 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | explicit saturation branches in each pixel | 82.663550 | 82.663550 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | named output pixel offset before each store | 82.663550 | 82.663550 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | signed chroma source pointers | 82.663550 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | converter locals flattened like exact siblings | 79.165140 | 79.165140 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | row output pointer before tile product | 79.165140 | 79.165140 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | green pixel sum before red pixel sum | 79.165140 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | explicit saturation branches in each pixel | 79.165140 | 79.165140 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | named output pixel offset before each store | 79.165140 | 79.165140 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | signed chroma source pointers | 79.165140 | 79.119260 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | converter locals flattened like exact siblings | 78.117645 | 77.970590 | 136/136 instructions; 124 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | row output pointer before tile product | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | green pixel sum before red pixel sum | 78.117645 | 65.985290 | 136/136 instructions; 124 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | explicit saturation branches in each pixel | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | named output pixel offset before each store | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | signed chroma source pointers | 78.117645 | 78.080880 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | converter locals flattened like exact siblings | 77.375885 | 77.234040 | 141/141 instructions; 127 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | row output pointer before tile product | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | green pixel sum before red pixel sum | 77.375885 | 65.673760 | 141/141 instructions; 127 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | explicit saturation branches in each pixel | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | named output pixel offset before each store | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | signed chroma source pointers | 77.375885 | 77.340420 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | converter locals flattened like exact siblings | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | row output pointer before tile product | 75.921740 | 75.834785 | 115/115 instructions; 96 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | green pixel sum before red pixel sum | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | explicit saturation branches in each pixel | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | named output pixel offset before each store | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | signed chroma source pointers | 75.921740 | 75.791306 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | converter locals flattened like exact siblings | 75.336730 | 75.336730 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | row output pointer before tile product | 75.336730 | 75.336730 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | green pixel sum before red pixel sum | 75.336730 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | explicit saturation branches in each pixel | 75.336730 | 75.336730 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | named output pixel offset before each store | 75.336730 | 75.336730 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | signed chroma source pointers | 75.336730 | 75.285710 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | row output pointer before tile product | 74.608330 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | green pixel sum before red pixel sum | 74.608330 | 74.608330 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | explicit saturation branches in each pixel | 74.608330 | 74.608330 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | named output pixel offset before each store | 74.608330 | 74.608330 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | signed chroma source pointers | 74.608330 | 74.566666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | converter locals flattened like exact siblings | 74.239630 | 70.884796 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | row output pointer before tile product | 74.239630 | 74.009220 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | green pixel sum before red pixel sum | 74.239630 | 61.179720 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | explicit saturation branches in each pixel | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | named output pixel offset before each store | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | signed chroma source pointers | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | row output pointer before tile product | 71.901790 | 71.812500 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | green pixel sum before red pixel sum | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | explicit saturation branches in each pixel | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | named output pixel offset before each store | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | signed chroma source pointers | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | converter locals flattened like exact siblings | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | row output pointer before tile product | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | green pixel sum before red pixel sum | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | explicit saturation branches in each pixel | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | named output pixel offset before each store | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | signed chroma source pointers | 71.048080 | 70.903850 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | converter locals flattened like exact siblings | 71.032680 | 70.960785 | 153/153 instructions; 133 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | row output pointer before tile product | 71.032680 | 71.032680 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | green pixel sum before red pixel sum | 71.032680 | 71.032680 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | explicit saturation branches in each pixel | 71.032680 | 71.032680 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | named output pixel offset before each store | 71.032680 | 69.071890 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | signed chroma source pointers | 71.032680 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | row output pointer before tile product | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | green pixel sum before red pixel sum | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | explicit saturation branches in each pixel | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | named output pixel offset before each store | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | signed chroma source pointers | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | converter locals flattened like exact siblings | 69.442150 | 69.442150 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | row output pointer before tile product | 69.442150 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | green pixel sum before red pixel sum | 69.442150 | 69.442150 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | explicit saturation branches in each pixel | 69.442150 | 69.442150 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | named output pixel offset before each store | 69.442150 | 63.801650 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | signed chroma source pointers | 69.442150 | 69.442150 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | converter locals flattened like exact siblings | 67.770270 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | row output pointer before tile product | 67.770270 | 67.770270 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | green pixel sum before red pixel sum | 67.770270 | 67.770270 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | explicit saturation branches in each pixel | 67.770270 | 67.770270 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | named output pixel offset before each store | 67.770270 | 68.412160 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | signed chroma source pointers | 67.770270 | 67.770270 | 148/148 instructions; 136 differences |
| TMCJPEG_814F2B50 | exact sibling split tile and pixel addressing | 53.634716 | 53.634716 | 385/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | unsigned chroma samples with split addressing | 53.634716 | 53.634716 | 385/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | row output pointers before tile row arithmetic | 53.634716 | 53.634716 | 385/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | row arithmetic inside pixel loop as exact grayscale | 53.634716 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814EFEAC | exact sibling split tile and pixel addressing | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | unsigned chroma samples with split addressing | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | row output pointers before tile row arithmetic | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | row arithmetic inside pixel loop as exact grayscale | 53.101124 | 52.412920 | 339/356 instructions; 355 differences |
| TMCJPEG_814F043C | exact sibling split tile and pixel addressing | 52.511510 | 52.511510 | 391/391 instructions; 387 differences |
| TMCJPEG_814F043C | unsigned chroma samples with split addressing | 52.511510 | 52.511510 | 391/391 instructions; 387 differences |
| TMCJPEG_814F043C | row output pointers before tile row arithmetic | 52.511510 | 53.222507 | 391/391 instructions; 387 differences |
| TMCJPEG_814F043C | row arithmetic inside pixel loop as exact grayscale | 52.511510 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | exact sibling split tile and pixel addressing | 52.511510 | 52.511510 | 391/391 instructions; 387 differences |
| TMCJPEG_814F11C4 | unsigned chroma samples with split addressing | 52.511510 | 52.511510 | 391/391 instructions; 387 differences |
| TMCJPEG_814F11C4 | row output pointers before tile row arithmetic | 52.511510 | 53.222507 | 391/391 instructions; 387 differences |
| TMCJPEG_814F11C4 | row arithmetic inside pixel loop as exact grayscale | 52.511510 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F1F48 | exact sibling split tile and pixel addressing | 49.791878 | 49.791878 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | unsigned chroma samples with split addressing | 49.791878 | 49.791878 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | row output pointers before tile row arithmetic | 49.791878 | 48.713200 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | row arithmetic inside pixel loop as exact grayscale | 49.791878 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F2570 | exact sibling split tile and pixel addressing | 47.103720 | 47.103720 | 376/376 instructions; 370 differences |
| TMCJPEG_814F2570 | unsigned chroma samples with split addressing | 47.103720 | 47.103720 | 376/376 instructions; 370 differences |
| TMCJPEG_814F2570 | row output pointers before tile row arithmetic | 47.103720 | 49.789894 | 376/376 instructions; 371 differences |
| TMCJPEG_814F2570 | row arithmetic inside pixel loop as exact grayscale | 47.103720 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F0A58 | exact sibling split tile and pixel addressing | 43.555790 | 43.555790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | unsigned chroma samples with split addressing | 43.555790 | 43.555790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | row output pointers before tile row arithmetic | 43.555790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | row arithmetic inside pixel loop as exact grayscale | 43.555790 | 44.507370 | 478/475 instructions; 478 differences |
| TMCJPEG_814F17E0 | exact sibling split tile and pixel addressing | 41.890297 | 41.890297 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | unsigned chroma samples with split addressing | 41.890297 | 41.890297 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | row output pointers before tile row arithmetic | 41.890297 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | row arithmetic inside pixel loop as exact grayscale | 41.890297 | 41.890297 | 475/474 instructions; 472 differences |

Converter checkpoint: full clean gate PASS; zero regressions, forbidden patterns, and readability warnings. Global fuzzy 97.98290 -> 98.00015. Retained real source-shape gains in all three converters. Setup buffer base still folds; colored saturation and loop scheduling still differ. Data inventory from original ELF sections confirmed all five units have no data sections. Failed flattening experiments were reverted before the gate.
| TMCJPEGDEC_IdctBlock_Col | AC reduction from newly loaded coefficient | 69.112335 | 69.112335 | 480/454 instructions; 466 differences |
| TMCJPEGDEC_IdctBlock_Col | last butterfly sum uses target operand order | 69.112335 | 69.112335 | 480/454 instructions; 466 differences |
| TMCJPEGDEC_IdctBlock_Col | odd outer sum grouped before inner correction | 69.112335 | 69.112335 | 480/454 instructions; 466 differences |
| TMCJPEGDEC_IdctBlock_Col | column pass decrements pointer in loop update | 69.112335 | 69.085900 | 480/454 instructions; 466 differences |
| TMCJPEGDEC_IdctBlock_Col | row pass zero fill uses pointer bound | 69.112335 | 69.017624 | 480/454 instructions; 467 differences |
| TMCJPEGDEC_IdctBlock_Col | butterfly coefficients load odd terms before even terms | 69.112335 | 69.112335 | 480/454 instructions; 466 differences |
| TMCJPEGDEC_IdctBlock_Lumi | AC reduction from newly loaded coefficient | 66.618675 | 66.618675 | 257/257 instructions; 217 differences |
| TMCJPEGDEC_IdctBlock_Lumi | last butterfly sum uses target operand order | 66.618675 | 66.618675 | 257/257 instructions; 217 differences |
| TMCJPEGDEC_IdctBlock_Lumi | odd outer sum grouped before inner correction | 66.618675 | 66.618675 | 257/257 instructions; 217 differences |
| TMCJPEGDEC_IdctBlock_Lumi | column pass decrements pointer in loop update | 66.618675 | 66.610890 | 257/257 instructions; 217 differences |
| TMCJPEGDEC_IdctBlock_Lumi | row pass zero fill uses pointer bound | 66.618675 | 65.038910 | 257/257 instructions; 224 differences |
| TMCJPEGDEC_IdctBlock_Lumi | butterfly coefficients load odd terms before even terms | 66.618675 | 63.797665 | 257/257 instructions; 213 differences |
| TMCJPEGDEC_decode_iquant | sign extension subtracts amplitude mask | 85.112320 | 84.731890 | 280/276 instructions; 252 differences |
| TMCJPEGDEC_decode_iquant | AC entry lifetime begins after DC decoding | 85.112320 | 85.126810 | 282/276 instructions; 251 differences |
| TMCJPEGDEC_decode_iquant | DC entry declared before AC entry | 85.112320 | 85.119570 | 282/276 instructions; 253 differences |
| TMCJPEGDEC_decode_iquant | slow Huffman offset reads original entry symbol | 85.112320 | 85.293480 | 280/276 instructions; 245 differences |
| TMCJPEGDEC_decode_iquant | slow Huffman offsets added after code difference | 85.112320 | 85.039856 | 282/276 instructions; 254 differences |
| TMCJPEGDEC_decode_iquant | quantizer and predictor multiplication operands | 85.112320 | 85.094200 | 282/276 instructions; 254 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | unique converter locals at function scope | 89.450550 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | sample loads before pointer increments | 89.450550 | 82.087910 | 88/91 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | explicit addition for pixel counter updates | 89.450550 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | tile column multiply replaces tile shift | 89.450550 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | row traversal uses exact sibling row variable | 89.450550 | 87.252750 | 88/91 instructions; 68 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | output tile product cast to unsigned | 89.450550 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565 | prefix increment for row and column counters | 89.450550 | 89.450550 | 88/91 instructions; 65 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | unique converter locals at function scope | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | sample loads before pointer increments | 88.942310 | 88.365390 | 101/104 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | explicit addition for pixel counter updates | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | tile column multiply replaces tile shift | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | row traversal uses exact sibling row variable | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | output tile product cast to unsigned | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV444toRGB565edge | prefix increment for row and column counters | 88.942310 | 88.942310 | 101/104 instructions; 82 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | unique converter locals at function scope | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | explicit addition for pixel counter updates | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | tile column multiply replaces tile shift | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | row traversal uses exact sibling row variable | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | output tile product cast to unsigned | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGB565edge | prefix increment for row and column counters | 86.788994 | 86.788994 | 109/109 instructions; 87 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | explicit addition for pixel counter updates | 84.292450 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | tile column multiply replaces tile shift | 84.292450 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | row traversal uses exact sibling row variable | 84.292450 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | output tile product cast to unsigned | 84.292450 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV411toRGB565edge | prefix increment for row and column counters | 84.292450 | 84.292450 | 109/106 instructions; 99 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | explicit addition for pixel counter updates | 83.991230 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | tile column multiply replaces tile shift | 83.991230 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | row traversal uses exact sibling row variable | 83.991230 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | output tile product cast to unsigned | 83.991230 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV420toRGB565edge | prefix increment for row and column counters | 83.991230 | 83.991230 | 117/114 instructions; 110 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | unique converter locals at function scope | 83.816330 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | explicit addition for pixel counter updates | 83.816330 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | tile column multiply replaces tile shift | 83.816330 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | row traversal uses exact sibling row variable | 83.816330 | 83.602040 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | output tile product cast to unsigned | 83.816330 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV211toRGB565 | prefix increment for row and column counters | 83.816330 | 83.816330 | 98/98 instructions; 83 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | explicit addition for pixel counter updates | 82.803740 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | tile column multiply replaces tile shift | 82.803740 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | row traversal uses exact sibling row variable | 82.803740 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | output tile product cast to unsigned | 82.803740 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV422toRGB565edge | prefix increment for row and column counters | 82.803740 | 82.803740 | 110/107 instructions; 103 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | unique converter locals at function scope | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | sample loads before pointer increments | 80.981820 | 80.209090 | 107/110 instructions; 86 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | explicit addition for pixel counter updates | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | tile column multiply replaces tile shift | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | row traversal uses exact sibling row variable | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | output tile product cast to unsigned | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV444toRGBA8edge | prefix increment for row and column counters | 80.981820 | 80.981820 | 107/110 instructions; 83 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | unique converter locals at function scope | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | explicit addition for pixel counter updates | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | tile column multiply replaces tile shift | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | row traversal uses exact sibling row variable | 78.117645 | 78.110290 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | output tile product cast to unsigned | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV422toRGB565 | prefix increment for row and column counters | 78.117645 | 78.117645 | 136/136 instructions; 122 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | unique converter locals at function scope | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | explicit addition for pixel counter updates | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | tile column multiply replaces tile shift | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | row traversal uses exact sibling row variable | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | output tile product cast to unsigned | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV420toRGB565 | prefix increment for row and column counters | 77.375885 | 77.375885 | 141/141 instructions; 125 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | unique converter locals at function scope | 76.216490 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | sample loads before pointer increments | 76.216490 | 75.340210 | 94/97 instructions; 90 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | explicit addition for pixel counter updates | 76.216490 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | tile column multiply replaces tile shift | 76.216490 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | row traversal uses exact sibling row variable | 76.216490 | 76.257730 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | output tile product cast to unsigned | 76.216490 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV444toRGBA8 | prefix increment for row and column counters | 76.216490 | 76.216490 | 94/97 instructions; 87 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | unique converter locals at function scope | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | explicit addition for pixel counter updates | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | tile column multiply replaces tile shift | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | row traversal uses exact sibling row variable | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | output tile product cast to unsigned | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV211toRGBA8edge | prefix increment for row and column counters | 75.921740 | 75.921740 | 115/115 instructions; 95 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | explicit addition for pixel counter updates | 74.691666 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | tile column multiply replaces tile shift | 74.691666 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | row traversal uses exact sibling row variable | 74.691666 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | output tile product cast to unsigned | 74.691666 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV420toRGBA8edge | prefix increment for row and column counters | 74.691666 | 74.691666 | 123/120 instructions; 108 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | unique converter locals at function scope | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | explicit addition for pixel counter updates | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | tile column multiply replaces tile shift | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | row traversal uses exact sibling row variable | 74.239630 | 74.235020 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | output tile product cast to unsigned | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGB565 | prefix increment for row and column counters | 74.239630 | 74.239630 | 217/217 instructions; 201 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | explicit addition for pixel counter updates | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | tile column multiply replaces tile shift | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | row traversal uses exact sibling row variable | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | output tile product cast to unsigned | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV411toRGBA8edge | prefix increment for row and column counters | 71.901790 | 71.901790 | 115/112 instructions; 104 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | unique converter locals at function scope | 71.065360 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | explicit addition for pixel counter updates | 71.065360 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | tile column multiply replaces tile shift | 71.065360 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | row traversal uses exact sibling row variable | 71.065360 | 71.065360 | 153/153 instructions; 134 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | output tile product cast to unsigned | 71.065360 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV420toRGBA8 | prefix increment for row and column counters | 71.065360 | 71.065360 | 153/153 instructions; 135 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | unique converter locals at function scope | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | explicit addition for pixel counter updates | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | tile column multiply replaces tile shift | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | row traversal uses exact sibling row variable | 71.048080 | 69.269230 | 104/104 instructions; 90 differences |
| TMCJPEGDEC_converterYUV211toRGBA8 | output tile product cast to unsigned | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |

Additional sibling pass tests the exact grayscale declaration and row traversal shape against every remaining colored/planar sibling. Counter spelling and arithmetic casts can compile identically; these are recorded as source attempts, not as improvements. Failed variants are restored. No data has been added: the original ELF data inventory is empty for all five units.
| TMCJPEGDEC_converterYUV211toRGBA8 | prefix increment for row and column counters | 71.048080 | 71.048080 | 104/104 instructions; 91 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | explicit addition for pixel counter updates | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | tile column multiply replaces tile shift | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | row traversal uses exact sibling row variable | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | output tile product cast to unsigned | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV422toRGBA8edge | prefix increment for row and column counters | 70.424780 | 70.424780 | 116/113 instructions; 107 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | unique converter locals at function scope | 69.462810 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | explicit addition for pixel counter updates | 69.462810 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | tile column multiply replaces tile shift | 69.462810 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | row traversal uses exact sibling row variable | 69.462810 | 69.595040 | 242/242 instructions; 213 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | output tile product cast to unsigned | 69.462810 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV411toRGBA8 | prefix increment for row and column counters | 69.462810 | 69.462810 | 242/242 instructions; 216 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | unique converter locals at function scope | 69.060814 | 67.770270 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | sample loads before pointer increments | 69.060814 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | explicit addition for pixel counter updates | 69.060814 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | tile column multiply replaces tile shift | 69.060814 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | row traversal uses exact sibling row variable | 69.060814 | 67.675674 | 148/148 instructions; 137 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | output tile product cast to unsigned | 69.060814 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEGDEC_converterYUV422toRGBA8 | prefix increment for row and column counters | 69.060814 | 69.060814 | 148/148 instructions; 138 differences |
| TMCJPEG_814F043C | unique converter locals at function scope | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | sample loads before pointer increments | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | explicit addition for pixel counter updates | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | tile column multiply replaces tile shift | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | row traversal uses exact sibling row variable | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | output tile product cast to unsigned | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F043C | prefix increment for row and column counters | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | unique converter locals at function scope | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | sample loads before pointer increments | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | explicit addition for pixel counter updates | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | tile column multiply replaces tile shift | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | row traversal uses exact sibling row variable | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | output tile product cast to unsigned | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F11C4 | prefix increment for row and column counters | 57.682865 | 57.682865 | 391/391 instructions; 383 differences |
| TMCJPEG_814F2B50 | unique converter locals at function scope | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | sample loads before pointer increments | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | explicit addition for pixel counter updates | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | tile column multiply replaces tile shift | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | row traversal uses exact sibling row variable | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | output tile product cast to unsigned | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814F2B50 | prefix increment for row and column counters | 55.795338 | 55.795338 | 386/386 instructions; 382 differences |
| TMCJPEG_814EFEAC | unique converter locals at function scope | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | sample loads before pointer increments | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | explicit addition for pixel counter updates | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | tile column multiply replaces tile shift | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | row traversal uses exact sibling row variable | 53.101124 | 53.073032 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | output tile product cast to unsigned | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814EFEAC | prefix increment for row and column counters | 53.101124 | 53.101124 | 338/356 instructions; 356 differences |
| TMCJPEG_814F2570 | unique converter locals at function scope | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | sample loads before pointer increments | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | explicit addition for pixel counter updates | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | tile column multiply replaces tile shift | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | row traversal uses exact sibling row variable | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | output tile product cast to unsigned | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F2570 | prefix increment for row and column counters | 52.587765 | 52.587765 | 376/376 instructions; 373 differences |
| TMCJPEG_814F1F48 | unique converter locals at function scope | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | sample loads before pointer increments | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | explicit addition for pixel counter updates | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | tile column multiply replaces tile shift | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | row traversal uses exact sibling row variable | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | output tile product cast to unsigned | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F1F48 | prefix increment for row and column counters | 52.167510 | 52.167510 | 400/394 instructions; 395 differences |
| TMCJPEG_814F0A58 | sample loads before pointer increments | 45.195790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | explicit addition for pixel counter updates | 45.195790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | tile column multiply replaces tile shift | 45.195790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | row traversal uses exact sibling row variable | 45.195790 | 42.867367 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | output tile product cast to unsigned | 45.195790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F0A58 | prefix increment for row and column counters | 45.195790 | 45.195790 | 477/475 instructions; 475 differences |
| TMCJPEG_814F17E0 | sample loads before pointer increments | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | explicit addition for pixel counter updates | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | tile column multiply replaces tile shift | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | row traversal uses exact sibling row variable | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | output tile product cast to unsigned | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEG_814F17E0 | prefix increment for row and column counters | 44.407173 | 44.407173 | 475/474 instructions; 472 differences |
| TMCJPEGDEC_decode_iquant | slow DC result has separate lifetime | 85.293480 | 85.384056 | 280/276 instructions; 243 differences |
| TMCJPEGDEC_decode_iquant | DC sign extension and AC sign extension use mask temporary | 85.293480 | 86.634056 | 278/276 instructions; 225 differences |
| TMCJPEGDEC_decode_iquant | scoped AC entry following scoped slow DC result | 85.293480 | 85.398550 | 280/276 instructions; 240 differences |
| TMCJPEGDEC_decode_iquant | slow DC load errors flow through DC end | 85.293480 | 85.181160 | 279/276 instructions; 250 differences |
| TMCJPEGDEC_decode_iquant | DC and AC amplitudes subtract precomputed masks | 85.293480 | 86.739130 | 278/276 instructions; 219 differences |
| TMCJPEGDEC_decode_iquant | DC load and symbol errors share final assignment | 86.739130 | 87.576090 | 277/276 instructions; 256 differences |
| TMCJPEGDEC_decode_iquant | DC final assignment then signed result check | 86.739130 | 86.648550 | 278/276 instructions; 221 differences |
| TMCJPEGDEC_decode_iquant | Huffman code subtraction before symbol offset | 86.739130 | 87.576090 | 277/276 instructions; 256 differences |
| TMCJPEGDEC_decode_iquant | DC bit buffer and position load order | 86.739130 | 87.576090 | 277/276 instructions; 256 differences |
| TMCJPEGDEC_decode_iquant | amplitude bit position stored after extraction | 86.739130 | 87.123190 | 277/276 instructions; 256 differences |
| TMCJPEGDEC_decode_iquant | AC entry declared last among outer locals | 87.576090 | 87.561590 | 277/276 instructions; 257 differences |
| TMCJPEGDEC_decode_iquant | DC entry outer lifetime with AC declaration last | 87.576090 | 87.568840 | 277/276 instructions; 256 differences |
| TMCJPEGDEC_IdctBlock_Lumi | first IDCT butterfly translated in target block order | 66.618675 | 65.120620 | 257/257 instructions; 215 differences |
| TMCJPEGDEC_IdctBlock_Lumi | last odd rotation scheduled between target stores | 66.618675 | 65.120620 | 257/257 instructions; 215 differences |
| TMCJPEGDEC_IdctBlock_Lumi | outer odd sum added after corrected inner sum | 66.618675 | 65.120620 | 257/257 instructions; 215 differences |
| TMCJPEGDEC_IdctBlock_Lumi | sum and difference stores grouped by output pair | 66.618675 | 64.443580 | 257/257 instructions; 216 differences |
| TMCJPEGDEC_IdctBlock_Lumi | temporary array walk with remaining row count | 66.618675 | 64.354090 | 257/257 instructions; 221 differences |

Scalar block work: IDCT Lumi first butterfly was translated in target address order, then tried delayed odd rotation, alternate sum grouping, store order, and remaining-row loop. All five builds retained 257 instructions; none exceeded baseline, so all were reverted. Col retains 480 versus target 454 after six separately built arithmetic, store-loop and coefficient-load changes. IQ DC/AC lifetimes, common error path, Huffman symbol load and amplitude-mask subtraction reduced 282 to 277 instructions, improving 85.11232 -> 87.57609. No newly exact function has been obtained in this continuation.

## Continuation final remaining functions

Every remaining function has at least five logged source-level attempts across the two continued passes. Identical compiler output is reported without claiming a gain. Instruction difference counts are positional; one insertion shifts later comparisons. The two already exact CR1 grayscale functions still trigger the known ctxdiff branch normalization discrepancy.


libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8

TMCJPEGDEC_set_converterY8U8V8: 92.739800%; buffer base address folded; store scheduling and register allocation differ.
TMCJPEG_814EFEAC: 53.101124%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F043C: 57.682865%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F0A58: 45.195790%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F11C4: 57.682865%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F17E0: 44.407173%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F1F48: 52.167510%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F2570: 52.587765%; tile address loops, unrolling and register allocation differ.
TMCJPEG_814F2B50: 55.795338%; tile address loops, unrolling and register allocation differ.

libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565

TMCJPEGDEC_set_converterRGB565: 93.864710%; buffer base address folded; store scheduling and register allocation differ.
TMCJPEGDEC_converterYUV411toRGB565: 74.239630%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV411toRGB565edge: 84.292450%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV422toRGB565: 78.117645%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV422toRGB565edge: 82.803740%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV420toRGB565: 77.375885%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV420toRGB565edge: 83.991230%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV211toRGB565: 83.816330%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV211toRGB565edge: 86.788994%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV444toRGB565: 89.450550%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV444toRGB565edge: 88.942310%; chroma arithmetic, saturation branches and register scheduling differ.

libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8

TMCJPEGDEC_set_converterRGBA8: 93.864710%; buffer base address folded; store scheduling and register allocation differ.
TMCJPEGDEC_converterYUV411toRGBA8: 69.595040%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV411toRGBA8edge: 71.901790%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV422toRGBA8: 69.060814%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV422toRGBA8edge: 70.424780%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV420toRGBA8: 71.065360%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV420toRGBA8edge: 74.691666%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV211toRGBA8: 71.048080%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV211toRGBA8edge: 75.921740%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV444toRGBA8: 76.257730%; chroma arithmetic, saturation branches and register scheduling differ.
TMCJPEGDEC_converterYUV444toRGBA8edge: 80.981820%; chroma arithmetic, saturation branches and register scheduling differ.

libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var

TMCJPEGDEC_IdctBlock_Lumi: 66.618675%; IDCT butterflies, sparse path and register scheduling differ.
TMCJPEGDEC_IdctBlock_Col: 69.112335%; IDCT butterflies, sparse path and register scheduling differ.

libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32

TMCJPEGDEC_decode_iquant: 87.576090%; AC Huffman loop scheduling and register allocation; 277/276 instructions.

## Planar converter block translation after 99cfa80f

Only Texture_MCUtoY8U8V8 is owned this round. Original has 196, 356, 391, 475, 391, 474, 394, 376, 386 instructions for the nine open functions. Source starts at 195, 338, 391, 477, 391, 475, 400, 376, 385. Four previously exact loops are preserved. Original has no data sections; pool must remain empty. Tests start with the smallest setter and proceed through the converter functions by target size.
TMCJPEGDEC_set_converterY8U8V8, inline-buffer-base: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, structured-conversion-buffer: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, conversion-buffer-address-arithmetic: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setup-cases-address-order: 780/784 bytes, 92.540820 percent, 183 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
Setter block audit covers dispatch 0x000-0x048, six case blocks through 0x228, dimension rounding 0x230-0x304, and epilogue. All real stores and arithmetic are present. The first unresolved difference is the folded conversion-buffer base: source omits target addi at 0x004. Inline accessor, structured buffer view, integer buffer address and source-token store order do not retain it. Rejected variants restored; this is recorded as a structural mismatch, not a register tie-break.
TMCJPEG_814EFEAC, luma-and-chroma-address-blocks: 1120/1424 bytes, 52.044945 percent, 257 positional non-register differences, first [1, 2, 3, 5, 7, 8, 14, 15].
TMCJPEG_814EFEAC, luma-four-pixel-loop: 1412/1424 bytes, 57.643257 percent, 232 positional non-register differences, first [3, 5, 7, 8, 14, 15, 16, 24].
TMCJPEG_814EFEAC, frame-and-row-initialization: 1412/1424 bytes, 57.643257 percent, 232 positional non-register differences, first [3, 5, 7, 8, 14, 15, 16, 24].
TMCJPEG_814EFEAC, luma-stores-with-signed-tile-offsets: 1412/1424 bytes, 73.766850 percent, 154 positional non-register differences, first [3, 5, 7, 8, 14, 15, 16, 24].
TMCJPEG_814EFEAC, local-order-0: 1412/1424 bytes, 74.811800 percent, 151 positional non-register differences, first [3, 5, 7, 8, 24, 25, 26, 149].
TMCJPEG_814EFEAC, local-order-29: 1412/1424 bytes, 75.050560 percent, 149 positional non-register differences, first [7, 8, 24, 25, 26, 149, 153, 154].
TMCJPEG_814EFEAC, local-order-32: 1412/1424 bytes, 75.078650 percent, 149 positional non-register differences, first [7, 8, 24, 25, 26, 149, 153, 154].
TMCJPEG_814EFEAC, local-order-40: 1412/1424 bytes, 75.134834 percent, 149 positional non-register differences, first [7, 8, 24, 25, 26, 149, 153, 154].
TMCJPEG_814EFEAC, local-order-48: 1412/1424 bytes, 75.443820 percent, 149 positional non-register differences, first [7, 8, 24, 25, 26, 149, 153, 154].
TMCJPEG_814EFEAC, local-order-67: 1412/1424 bytes, 75.696630 percent, 149 positional non-register differences, first [7, 8, 24, 25, 26, 149, 153, 154].
TMCJPEG_814EFEAC, local-order-139: 1412/1424 bytes, 75.514046 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, local-order-149: 1412/1424 bytes, 75.570220 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, local-order-152: 1412/1424 bytes, 75.612360 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, local-order-167: 1412/1424 bytes, 75.823040 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, local-order-176: 1412/1424 bytes, 75.991570 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, local-order-retained: 1412/1424 bytes, 75.991570 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
411 normal was discarded because 338/356 instructions exceeded the five percent threshold. Fresh translation restores the signed tile-offset arithmetic and four-pixel luma loop. Source now has a 0x60-byte frame, 353/356 instructions; luma store blocks use the target opcodes. Early initializer scheduling is being aligned by real local declaration order before the chroma blocks are finalized.
TMCJPEG_814EFEAC, chroma-hoisted-address-blocks: 1416/1424 bytes, 75.831460 percent, 185 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 12].
TMCJPEG_814EFEAC, chroma-add-assignment-counter: 1412/1424 bytes, 75.991570 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-signed-row-product: 1324/1424 bytes, 59.615170 percent, 289 positional non-register differences, first [14, 15, 16, 20, 24, 25, 26, 27].
TMCJPEG_814EFEAC, chroma-signed-samples: 1412/1424 bytes, 75.991570 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-counter-retained: 1412/1424 bytes, 75.991570 percent, 146 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, separate-luma-and-chroma-row-products: 1416/1424 bytes, 77.174160 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, separate-chroma-offset-temporaries: 1416/1424 bytes, 77.174160 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-tile-offset-before-row-output: 1416/1424 bytes, 77.174160 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-exact-grayscale-address-shape: 1416/1424 bytes, 77.174160 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-byte-address-values: 1416/1424 bytes, 77.132020 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-width-signed-row-unsigned: 1416/1424 bytes, 77.174160 percent, 185 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-bounds-and-skip-own-lifetimes: 1416/1424 bytes, 76.441010 percent, 181 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, separate-chroma-bounds-retained: 1416/1424 bytes, 76.441010 percent, 181 positional non-register differences, first [7, 8, 149, 153, 154, 155, 157, 158].
TMCJPEG_814EFEAC, chroma-sample-load-temporaries: 1416/1424 bytes, 76.252810 percent, 192 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 12].
TMCJPEG_814EFEAC, chroma-load-store-pointer-walk: 1424/1424 bytes, 88.000000 percent, 30 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 12].
TMCJPEG_814EFEAC, chroma-direct-load-before-increment: 1424/1424 bytes, 88.000000 percent, 30 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 12].
TMCJPEG_814EFEAC, local-order-0: 1424/1424 bytes, 88.210670 percent, 30 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 12].
TMCJPEG_814EFEAC, local-order-1: 1424/1424 bytes, 88.252810 percent, 29 positional non-register differences, first [5, 6, 7, 8, 9, 10, 11, 13].
TMCJPEG_814EFEAC, local-order-17: 1424/1424 bytes, 89.606740 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-21: 1424/1424 bytes, 89.606740 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-22: 1424/1424 bytes, 89.901690 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-52: 1424/1424 bytes, 90.126400 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-55: 1424/1424 bytes, 90.168540 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-60: 1424/1424 bytes, 90.323040 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-72: 1424/1424 bytes, 90.603935 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-73: 1424/1424 bytes, 90.814606 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-85: 1424/1424 bytes, 90.898880 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-137: 1424/1424 bytes, 90.969100 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-207: 1424/1424 bytes, 91.221910 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-301: 1424/1424 bytes, 91.278090 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-302: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, local-order-retained: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
411 normal now has 356/356 instructions and the target 0x60 frame. The crucial correction is loading/storing each chroma byte before advancing its source pointer, instead of advancing inside the store expression. Initial dispatch/setup and luma blocks now differ only in register operands. Remaining work is two chroma setup schedules and the unrolled chroma address schedule around target instructions 236-268.
TMCJPEG_814EFEAC, chroma-cr-address-after-cb-store: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-skip-before-tile-width: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-both-input-walks-after-stores: 1424/1424 bytes, 91.300560 percent, 22 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, unsigned-chroma-pixel-offset: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, shared-chroma-row-offset: 1436/1424 bytes, 86.612360 percent, 193 positional non-register differences, first [152, 153, 154, 155, 156, 157, 158, 159].
TMCJPEG_814EFEAC, pixel-address-before-row-address: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, pixel-pointer-direct-byte-store: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, complete-411-translation-retained: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814F2570, 211-frame-and-luma-address-blocks: 1492/1504 bytes, 73.462770 percent, 223 positional non-register differences, first [9, 10, 11, 12, 13, 14, 15, 16].
TMCJPEG_814F2570, 211-luma-exact-grayscale-pointer-walk: 1492/1504 bytes, 73.462770 percent, 223 positional non-register differences, first [9, 10, 11, 12, 13, 14, 15, 16].
TMCJPEG_814F2570, 211-chroma-row-product-lifetime: 1504/1504 bytes, 80.691490 percent, 62 positional non-register differences, first [18, 20, 81, 83, 85, 88, 89, 90].
TMCJPEG_814F2570, local-order-8: 1504/1504 bytes, 80.710106 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2570, local-order-12: 1504/1504 bytes, 80.896280 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2570, local-order-30: 1504/1504 bytes, 80.936170 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2570, local-order-35: 1504/1504 bytes, 81.162230 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2570, local-order-115: 1504/1504 bytes, 81.135635 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2570, local-order-retained: 1504/1504 bytes, 81.135635 percent, 56 positional non-register differences, first [81, 83, 85, 88, 89, 90, 92, 93].
TMCJPEG_814F2B50, 211-edge-width-height-and-complete-loops: 1544/1544 bytes, 76.779790 percent, 65 positional non-register differences, first [36, 37, 94, 96, 98, 101, 102, 103].
TMCJPEG_814F043C, 411-edge-width-rounding-and-complete-loops: 1580/1564 bytes, 74.404090 percent, 359 positional non-register differences, first [13, 15, 16, 17, 18, 19, 20, 21].
TMCJPEG_814F2B50, local-order-0: 1544/1544 bytes, 77.038860 percent, 65 positional non-register differences, first [36, 37, 94, 96, 98, 101, 102, 103].
TMCJPEG_814F2B50, local-order-retained: 1544/1544 bytes, 77.038860 percent, 65 positional non-register differences, first [36, 37, 94, 96, 98, 101, 102, 103].
211 normal and edge have been translated through both luma and chroma loops. Both now have target sizes, 1504 and 1544 bytes, and 0x60-byte frames. The normal chroma loop retains the original luma width/bounds and reloads only its height; edge chroma height rounds upward. Separate luma/chroma tile products avoid incorrect hoisting. 411 edge has also been rewritten through its scalar luma and quarter-width chroma phases; its first build is four instructions long and is being aligned.
TMCJPEG_814F043C, local-order-6: 1580/1564 bytes, 74.595910 percent, 359 positional non-register differences, first [13, 15, 16, 17, 18, 19, 20, 21].
TMCJPEG_814F043C, local-order-104: 1580/1564 bytes, 74.800514 percent, 359 positional non-register differences, first [13, 15, 16, 17, 18, 19, 20, 21].
TMCJPEG_814F043C, local-order-retained: 1580/1564 bytes, 74.800514 percent, 359 positional non-register differences, first [13, 15, 16, 17, 18, 19, 20, 21].
TMCJPEG_814F043C, separate-chroma: 1564/1564 bytes, 85.130430 percent, 60 positional non-register differences, first [33, 35, 187, 188, 189, 190, 191, 192].
TMCJPEG_814F2570, separate-chroma-offset: 1504/1504 bytes, 90.287230 percent, 22 positional non-register differences, first [220, 221, 222, 224, 225, 226, 227, 242].
TMCJPEG_814F2B50, separate-chroma-offset: 1544/1544 bytes, 88.062180 percent, 30 positional non-register differences, first [36, 37, 246, 247, 248, 250, 252, 254].
TMCJPEG_814F0A58, 422-two-pixel-luma-and-chroma-blocks: 1888/1900 bytes, 85.631580 percent, 411 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814EFEAC, chroma-baseline: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chromaTileRow-s32: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chromaTileWidth-s32: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chromaTileOffset-u32: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-add-reversed: 1424/1424 bytes, 91.334270 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-postincrement-column: 980/1424 bytes, 44.064606 percent, 164 positional non-register differences, first [0, 4, 43, 44, 47, 48, 50, 51].
TMCJPEG_814EFEAC, chroma-bases-before-tile: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-pixel-first: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-signed-byte-source: 1424/1424 bytes, 91.362360 percent, 20 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-retained: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814F0A58, 422-two-offset-temporaries: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814EFEAC, chroma-order-baseline: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-0: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-1: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-2: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-3: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-4: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-5: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-6: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-7: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-8: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-9: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-10: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-11: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-12: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-13: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-14: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-15: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-16: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-17: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-18: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-19: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-20: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-21: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-22: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-23: 1424/1424 bytes, 91.300560 percent, 22 positional non-register differences, first [153, 155, 236, 238, 239, 242, 244, 245].
TMCJPEG_814EFEAC, chroma-dependency-order-24: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-25: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-26: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-27: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-28: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-29: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-30: 1424/1424 bytes, 92.143260 percent, 18 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-31: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-32: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-33: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-34: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-dependency-order-retained: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814F0A58, 422-luma-variants-baseline: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-recompute-row-for-second-byte: 1364/1900 bytes, 56.738950 percent, 325 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-inline-row-product: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-two-distinct-row-products: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-direct-signed-row-product: 1876/1900 bytes, 70.677895 percent, 424 positional non-register differences, first [0, 1, 2, 3, 4, 7, 8, 9].
TMCJPEG_814F0A58, 422-luma-variants-retained: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, luma-chroma-reuse-baseline: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, reuse-chromaTileRow: 1892/1900 bytes, 75.292630 percent, 402 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, reuse-chromaTileOffset: 1364/1900 bytes, 56.877895 percent, 320 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaPixelOffset: 1364/1900 bytes, 57.684210 percent, 326 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileWidth: 1896/1900 bytes, 79.082110 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaTileOffset: 1360/1900 bytes, 52.197895 percent, 321 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaPixelOffset: 1360/1900 bytes, 53.435790 percent, 325 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaTileWidth: 1892/1900 bytes, 75.292630 percent, 402 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, reuse-chromaTileOffset,chromaPixelOffset: 1364/1900 bytes, 54.513683 percent, 324 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileOffset,chromaTileWidth: 1364/1900 bytes, 57.360000 percent, 318 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaPixelOffset,chromaTileWidth: 1364/1900 bytes, 58.040000 percent, 325 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaTileOffset,chromaPixelOffset: 1360/1900 bytes, 51.671577 percent, 325 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaTileOffset,chromaTileWidth: 1360/1900 bytes, 52.197895 percent, 321 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileRow,chromaPixelOffset,chromaTileWidth: 1360/1900 bytes, 53.435790 percent, 325 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, reuse-chromaTileOffset,chromaPixelOffset,chromaTileWidth: 1364/1900 bytes, 55.069473 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, luma-chroma-reuse-retained: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814EFEAC, chroma-shape-baseline: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-row-pointer-and-indexed-pixel: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-unsigned-row-offset: 1436/1424 bytes, 87.595505 percent, 193 positional non-register differences, first [152, 153, 154, 155, 156, 157, 158, 159].
TMCJPEG_814EFEAC, chroma-signed-row-offset: 1436/1424 bytes, 87.595505 percent, 193 positional non-register differences, first [152, 153, 154, 155, 156, 157, 158, 159].
TMCJPEG_814EFEAC, chroma-row-plus-pixel-integer: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, chroma-offset-address-all-integer: 1424/1424 bytes, 85.002810 percent, 67 positional non-register differences, first [153, 155, 215, 216, 217, 218, 220, 221].
TMCJPEG_814EFEAC, chroma-shape-retained: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, lifetime-baseline: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaRowSkip: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, reuse-chromaXEnd: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, reuse-chromaYEnd: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaTileOffset: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaPixelOffset: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, inner-scope-chromaTileRow: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, lifetime-baseline: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaRowSkip: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, reuse-chromaXEnd: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, reuse-chromaYEnd: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaTileOffset: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, reuse-chromaPixelOffset: 1424/1424 bytes, 92.205055 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, lifetime-retained: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814F0A58, 422-pair-baseline: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-distinct-offset: 1908/1900 bytes, 69.225266 percent, 427 positional non-register differences, first [0, 1, 2, 3, 4, 5, 6, 7].
TMCJPEG_814F0A58, 422-distinct-pixel: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-distinct-output: 1896/1900 bytes, 74.730530 percent, 426 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-distinct-offset-pixel: 1908/1900 bytes, 69.225266 percent, 427 positional non-register differences, first [0, 1, 2, 3, 4, 5, 6, 7].
TMCJPEG_814F0A58, 422-distinct-offset-output: 1896/1900 bytes, 85.368420 percent, 422 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, 422-distinct-all: 1896/1900 bytes, 85.852630 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, 422-pair-retained: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-scoped-baseline: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-inner-tileRow: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-inner-tileOffset: 1896/1900 bytes, 79.282104 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-inner-tileRow,tileOffset,pixelOffset,output: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-inline-second-row-product: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-inline-first-row-product: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-scoped-retained: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F11C4, 422-edge-complete-scalar-loop-port: 1564/1564 bytes, 85.130430 percent, 60 positional non-register differences, first [33, 35, 187, 188, 189, 190, 191, 192].
TMCJPEG_814F17E0, 420-normal-complete-double-byte-loop-port: 1892/1896 bytes, 80.681435 percent, 419 positional non-register differences, first [11, 12, 13, 14, 15, 16, 17, 18].
TMCJPEG_814F1F48, 420-edge-complete-scalar-loop-port: 1576/1576 bytes, 88.033000 percent, 30 positional non-register differences, first [33, 35, 180, 182, 183, 184, 185, 188].
TMCJPEG_814EFEAC, remove-obsolete-luma-temporaries: 1424/1424 bytes, 92.893260 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, local-order-29: 1424/1424 bytes, 93.005615 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, local-order-111: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, local-order-retained: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEGDEC_set_converterY8U8V8, setup-type-baseline: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, conversion-buffer-array-decay: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, conversion-buffer-void-base: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, conversion-buffer-byte-zero-address: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, conversion-buffer-word-base: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setup-type-retained: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEG_814F043C, row-skip-baseline: 1564/1564 bytes, 85.130430 percent, 60 positional non-register differences, first [33, 35, 187, 188, 189, 190, 191, 192].
TMCJPEG_814F043C, inline-rowSkip: 1564/1564 bytes, 86.473145 percent, 58 positional non-register differences, first [187, 188, 189, 190, 191, 192, 260, 261].
TMCJPEG_814F043C, inline-chromaRowSkip: 1564/1564 bytes, 90.933500 percent, 20 positional non-register differences, first [33, 35, 272, 274, 275, 278, 280, 281].
TMCJPEG_814F043C, row-skip-retained: 1564/1564 bytes, 90.933500 percent, 20 positional non-register differences, first [33, 35, 272, 274, 275, 278, 280, 281].
TMCJPEG_814F2B50, row-skip-baseline: 1544/1544 bytes, 88.062180 percent, 30 positional non-register differences, first [36, 37, 246, 247, 248, 250, 252, 254].
TMCJPEG_814F2B50, row-skip-baseline: 1544/1544 bytes, 88.062180 percent, 30 positional non-register differences, first [36, 37, 246, 247, 248, 250, 252, 254].
TMCJPEG_814F2B50, inline-rowSkip: 1544/1544 bytes, 89.981865 percent, 24 positional non-register differences, first [246, 247, 248, 250, 252, 254, 256, 258].
TMCJPEG_814F2B50, row-skip-retained: 1544/1544 bytes, 89.981865 percent, 24 positional non-register differences, first [246, 247, 248, 250, 252, 254, 256, 258].
TMCJPEG_814EFEAC, row-skip-baseline: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, inline-rowSkip: 1424/1424 bytes, 92.500000 percent, 16 positional non-register differences, first [153, 155, 224, 226, 228, 229, 230, 234].
TMCJPEG_814EFEAC, row-skip-retained: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814F043C, row-skip-baseline: 1564/1564 bytes, 90.933500 percent, 20 positional non-register differences, first [33, 35, 272, 274, 275, 278, 280, 281].
TMCJPEG_814F043C, inline-rowSkip: 1564/1564 bytes, 91.790280 percent, 18 positional non-register differences, first [272, 274, 275, 278, 280, 281, 282, 284].
TMCJPEG_814F043C, row-skip-retained: 1564/1564 bytes, 91.790280 percent, 18 positional non-register differences, first [272, 274, 275, 278, 280, 281, 282, 284].
TMCJPEG_814EFEAC, 411-second-phase-baseline: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-chroma-height-from-width: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-chroma-direct-height-bound: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-skip-before-chroma-bounds: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-chroma-inline-row-skip: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-separate-chroma-width: 1424/1424 bytes, 93.342700 percent, 11 positional non-register differences, first [153, 155, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, 411-second-phase-retained: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, sample-temporary-baseline: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-u32-before-address: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-u32-before-store: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-u32-both-before-address: 1396/1424 bytes, 66.089890 percent, 190 positional non-register differences, first [0, 3, 4, 5, 6, 7, 8, 146].
TMCJPEG_814EFEAC, samples-s32-before-address: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-s32-before-store: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-s32-both-before-address: 1396/1424 bytes, 66.089890 percent, 190 positional non-register differences, first [0, 3, 4, 5, 6, 7, 8, 146].
TMCJPEG_814EFEAC, samples-u8-before-address: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-u8-before-store: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-u8-both-before-address: 1400/1424 bytes, 67.244385 percent, 190 positional non-register differences, first [0, 3, 4, 5, 6, 7, 8, 146].
TMCJPEG_814EFEAC, sample-temporary-retained: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, scoped-phase-baseline: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-phase-scope: 1424/1424 bytes, 93.539330 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, both-phase-scope: 1424/1424 bytes, 93.539330 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, initialized-chroma-phase-scope: 1420/1424 bytes, 86.460670 percent, 44 positional non-register differences, first [3, 5, 146, 147, 148, 149, 150, 151].
TMCJPEG_814EFEAC, row-unsigned-product-phase-scope: 1424/1424 bytes, 94.662920 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, scoped-phase-retained: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-order-baseline: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-0: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-1: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-2: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-3: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-4: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-5: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-6: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-7: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-8: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-9: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-10: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-11: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-12: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-13: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-14: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-15: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-16: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-17: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-18: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-19: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-20: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-21: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-22: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-23: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-24: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-25: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-26: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-27: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-28: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-29: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-30: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-31: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-32: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-33: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-34: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-35: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-36: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-37: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-38: 1424/1424 bytes, 94.699440 percent, 13 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-39: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-40: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-41: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-42: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-43: 1424/1424 bytes, 94.699440 percent, 13 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-44: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-45: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-46: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-47: 1424/1424 bytes, 94.699440 percent, 13 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-48: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-49: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-50: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-51: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-52: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-53: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-54: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-55: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-56: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-57: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-58: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-59: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-60: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-61: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-62: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-63: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-64: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-65: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-66: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-67: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-68: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-69: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-70: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-71: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-72: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-73: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-74: 1424/1424 bytes, 94.699440 percent, 13 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-75: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-76: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-77: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-78: 1424/1424 bytes, 94.609550 percent, 15 positional non-register differences, first [153, 156, 234, 235, 239, 242, 246, 248].
TMCJPEG_814EFEAC, chroma-dependency-order-79: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-80: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-81: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-82: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-83: 1424/1424 bytes, 94.587080 percent, 13 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-dependency-order-retained: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
Round 3 progress: all eight pixel converters have full luma and chroma translations; scalar luma phases now align except registers after separating luma/chroma offset lifetimes. Edge 411 luma setup and all luma blocks align except registers after moving row skips to their loop-end expressions. Chroma unroll scheduling remains structural, not a register-only match. Setter still lacks one common buffer-base instruction. No data sections exist in the original unit. Continuing the remaining structural differences.
TMCJPEG_814F0A58, 422-inline-tile_offset: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-inline-tile_offset: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-inline-pixel_address: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-inline-rejected-restored: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F11C4, 422-edge-411-aligned-luma-port: 1564/1564 bytes, 91.790280 percent, 18 positional non-register differences, first [272, 274, 275, 278, 280, 281, 282, 284].
TMCJPEG_814F1F48, 420-edge-411-aligned-luma-port: 1576/1576 bytes, 92.596440 percent, 21 positional non-register differences, first [180, 182, 183, 184, 185, 188, 189, 190].
TMCJPEG_814F0A58, 422-pair-rebuild-baseline: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-pair-indexed-signed-offsets: 1888/1900 bytes, 84.661050 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-pair-unsigned-output-row-temporary: 1888/1900 bytes, 84.661050 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-pair-duplicate-row-address: 1888/1900 bytes, 84.503160 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-pair-counter-before-pointer: 1888/1900 bytes, 84.661050 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-pair-row-in-for-initializer: 1888/1900 bytes, 84.661050 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-pair-index-pointer-bias: 1900/1900 bytes, 65.418945 percent, 252 positional non-register differences, first [0, 1, 2, 3, 8, 11, 12, 13].
TMCJPEG_814F0A58, 422-pair-rebuild-retained: 1900/1900 bytes, 65.418945 percent, 252 positional non-register differences, first [0, 1, 2, 3, 8, 11, 12, 13].
TMCJPEG_814F0A58, 422-combined-index-baseline: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-tile-index-before-byte-offset: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-signed-tile-index-before-byte-offset: 1360/1900 bytes, 55.757896 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-tile-offset-shift-assignment: 1360/1900 bytes, 58.524210 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-row-product-multiply-assignment: 1360/1900 bytes, 56.109474 percent, 322 positional non-register differences, first [3, 4, 5, 6, 7, 8, 9, 10].
TMCJPEG_814F0A58, 422-combined-index-retained: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-row-types-baseline: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-types-s32-s32-s32: 1876/1900 bytes, 70.778946 percent, 423 positional non-register differences, first [0, 1, 2, 3, 8, 9, 10, 11].
TMCJPEG_814F0A58, 422-types-s32-s32-u32: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-types-s32-u32-s32: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-types-s32-u32-u32: 1876/1900 bytes, 70.778946 percent, 423 positional non-register differences, first [0, 1, 2, 3, 8, 9, 10, 11].
TMCJPEG_814F0A58, 422-types-u32-s32-s32: 1876/1900 bytes, 70.778946 percent, 423 positional non-register differences, first [0, 1, 2, 3, 8, 9, 10, 11].
TMCJPEG_814F0A58, 422-types-u32-s32-u32: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-types-u32-u32-u32: 1876/1900 bytes, 70.778946 percent, 423 positional non-register differences, first [0, 1, 2, 3, 8, 9, 10, 11].
TMCJPEG_814F0A58, 422-row-types-retained: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-output-pair-baseline: 1896/1900 bytes, 79.608420 percent, 421 positional non-register differences, first [12, 13, 14, 15, 16, 17, 18, 19].
TMCJPEG_814F0A58, 422-second-output: 1896/1900 bytes, 84.313680 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-inner-second-output: 1896/1900 bytes, 84.313680 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-two-tile-offsets: 1888/1900 bytes, 84.661050 percent, 412 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-direct-tile-offset-and-next-output: 1896/1900 bytes, 84.313680 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, 422-output-pair-retained: 1896/1900 bytes, 84.313680 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, local-order-0: 1896/1900 bytes, 84.576840 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, local-order-27: 1896/1900 bytes, 84.534740 percent, 424 positional non-register differences, first [19, 20, 21, 22, 23, 24, 26, 27].
TMCJPEG_814F0A58, local-order-34: 1896/1900 bytes, 83.400000 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-38: 1896/1900 bytes, 83.547370 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-47: 1896/1900 bytes, 83.463160 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-53: 1896/1900 bytes, 84.568420 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-55: 1896/1900 bytes, 85.284210 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-68: 1896/1900 bytes, 85.673680 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-211: 1896/1900 bytes, 85.600000 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, local-order-retained: 1896/1900 bytes, 85.600000 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, row-skip-baseline: 1896/1900 bytes, 85.600000 percent, 423 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, inline-rowSkip: 1896/1900 bytes, 87.608420 percent, 413 positional non-register differences, first [33, 36, 37, 38, 39, 40, 41, 42].
TMCJPEG_814F0A58, inline-chromaRowSkip: 1896/1900 bytes, 86.351580 percent, 427 positional non-register differences, first [21, 22, 23, 24, 26, 27, 29, 30].
TMCJPEG_814F0A58, row-skip-retained: 1896/1900 bytes, 87.608420 percent, 413 positional non-register differences, first [33, 36, 37, 38, 39, 40, 41, 42].
TMCJPEG_814EFEAC, chroma-walk-baseline: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, for-preincrement: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, for-assignment: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, while: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, samples-postincrement: 1416/1424 bytes, 76.280900 percent, 183 positional non-register differences, first [3, 5, 149, 153, 154, 155, 156, 157].
TMCJPEG_814EFEAC, cb-row-walk: 1436/1424 bytes, 82.522470 percent, 173 positional non-register differences, first [149, 151, 153, 154, 156, 157, 158, 159].
TMCJPEG_814EFEAC, both-row-walks: 1420/1424 bytes, 75.707860 percent, 191 positional non-register differences, first [3, 5, 149, 153, 154, 155, 156, 157].
TMCJPEG_814EFEAC, chroma-walk-retained: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814F0A58, 422-full-expression-baseline: 1896/1900 bytes, 87.608420 percent, 413 positional non-register differences, first [33, 36, 37, 38, 39, 40, 41, 42].
TMCJPEG_814F0A58, 422-full-expression-pixel-pointer: 1900/1900 bytes, 90.250530 percent, 40 positional non-register differences, first [178, 179, 180, 181, 182, 183, 184, 185].
TMCJPEG_814F0A58, 422-full-expression-tile-pointer: 1912/1900 bytes, 66.654740 percent, 420 positional non-register differences, first [0, 1, 2, 3, 4, 5, 6, 7].
TMCJPEG_814F0A58, 422-full-expression-all-integer: 1900/1900 bytes, 90.250530 percent, 40 positional non-register differences, first [178, 179, 180, 181, 182, 183, 184, 185].
TMCJPEG_814F0A58, 422-full-expression-row-product-temp: 1896/1900 bytes, 87.776840 percent, 413 positional non-register differences, first [33, 36, 37, 38, 39, 40, 41, 42].
TMCJPEG_814F0A58, 422-full-expression-retained: 1900/1900 bytes, 90.250530 percent, 40 positional non-register differences, first [178, 179, 180, 181, 182, 183, 184, 185].
TMCJPEG_814F17E0, 420-complete-inline-pixel-addresses: 1896/1896 bytes, 88.487340 percent, 62 positional non-register differences, first [176, 177, 178, 179, 180, 181, 182, 183].
TMCJPEG_814F0A58, luma-source-walk-baseline: 1900/1900 bytes, 90.250530 percent, 40 positional non-register differences, first [178, 179, 180, 181, 182, 183, 184, 185].
TMCJPEG_814F0A58, luma-two-input-postincrements: 1900/1900 bytes, 93.852630 percent, 18 positional non-register differences, first [355, 357, 358, 361, 363, 364, 365, 367].
TMCJPEG_814F0A58, luma-two-input-separate-increments: 1900/1900 bytes, 90.250530 percent, 40 positional non-register differences, first [178, 179, 180, 181, 182, 183, 184, 185].
TMCJPEG_814F0A58, luma-second-input-preincrement: 1900/1900 bytes, 93.873690 percent, 18 positional non-register differences, first [355, 357, 358, 361, 363, 364, 365, 367].
TMCJPEG_814F0A58, luma-source-walk-retained: 1900/1900 bytes, 93.873690 percent, 18 positional non-register differences, first [355, 357, 358, 361, 363, 364, 365, 367].
TMCJPEG_814EFEAC, chroma-complete-expression-baseline: 1424/1424 bytes, 94.676960 percent, 11 positional non-register differences, first [153, 156, 234, 235, 236, 238, 239, 244].
TMCJPEG_814EFEAC, chroma-full-inline-postincrements: 1416/1424 bytes, 76.747190 percent, 177 positional non-register differences, first [149, 153, 154, 155, 156, 157, 158, 159].
TMCJPEG_814EFEAC, chroma-full-inline-separate-increments: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, chroma-full-inline-row-product-temp: 1420/1424 bytes, 94.115166 percent, 166 positional non-register differences, first [146, 147, 148, 149, 150, 151, 153, 154].
TMCJPEG_814EFEAC, chroma-complete-expression-retained: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814F0A58, chroma-complete-expression-baseline: 1900/1900 bytes, 93.873690 percent, 18 positional non-register differences, first [355, 357, 358, 361, 363, 364, 365, 367].
TMCJPEG_814F0A58, chroma-full-inline-postincrements: 1892/1900 bytes, 81.338950 percent, 175 positional non-register differences, first [268, 273, 274, 276, 277, 278, 279, 280].
TMCJPEG_814F0A58, chroma-full-inline-separate-increments: 1900/1900 bytes, 95.094734 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-full-inline-row-product-temp: 1896/1900 bytes, 90.947365 percent, 186 positional non-register differences, first [270, 271, 272, 274, 277, 280, 281, 282].
TMCJPEG_814F0A58, chroma-complete-expression-retained: 1900/1900 bytes, 95.094734 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, 422-inline-input-postincrements-and-chroma: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F043C, chroma-complete-expression-baseline: 1564/1564 bytes, 91.790280 percent, 18 positional non-register differences, first [272, 274, 275, 278, 280, 281, 282, 284].
TMCJPEG_814F043C, chroma-full-inline-postincrements: 1552/1564 bytes, 75.601020 percent, 187 positional non-register differences, first [178, 180, 182, 183, 184, 185, 186, 187].
TMCJPEG_814F043C, chroma-full-inline-separate-increments: 1564/1564 bytes, 93.657290 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, chroma-full-inline-row-product-temp: 1556/1564 bytes, 88.974430 percent, 98 positional non-register differences, first [183, 184, 185, 187, 188, 189, 191, 192].
TMCJPEG_814F043C, chroma-complete-expression-retained: 1564/1564 bytes, 93.657290 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F2570, chroma-complete-expression-baseline: 1504/1504 bytes, 90.287230 percent, 22 positional non-register differences, first [220, 221, 222, 224, 225, 226, 227, 242].
TMCJPEG_814F2570, chroma-full-inline-postincrements: 1492/1504 bytes, 75.986700 percent, 346 positional non-register differences, first [9, 10, 11, 12, 13, 14, 15, 16].
TMCJPEG_814F2570, chroma-full-inline-separate-increments: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, chroma-full-inline-row-product-temp: 1496/1504 bytes, 84.914894 percent, 333 positional non-register differences, first [20, 21, 22, 23, 24, 26, 27, 28].
TMCJPEG_814F2570, chroma-complete-expression-retained: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2B50, chroma-complete-expression-baseline: 1544/1544 bytes, 89.981865 percent, 24 positional non-register differences, first [246, 247, 248, 250, 252, 254, 256, 258].
TMCJPEG_814F2B50, chroma-full-inline-postincrements: 1532/1544 bytes, 71.722800 percent, 326 positional non-register differences, first [27, 28, 32, 33, 34, 35, 36, 37].
TMCJPEG_814F2B50, chroma-full-inline-separate-increments: 1544/1544 bytes, 99.041450 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, chroma-full-inline-row-product-temp: 1536/1544 bytes, 78.129530 percent, 241 positional non-register differences, first [27, 28, 33, 34, 35, 36, 37, 38].
TMCJPEG_814F2B50, chroma-complete-expression-retained: 1544/1544 bytes, 99.041450 percent, 0 positional non-register differences, first [].
Round 3 breakthrough: the grouped luma loops require the whole tile address expression in each byte store; extra address temporaries changed the compiler unroll and invariant-hoisting stages. Postincrementing the two luma inputs makes the complete 422 luma phase align except registers. Chroma similarly requires complete address expressions but separate source-pointer increments. This gives 211 edge 386/386 instructions with zero positional non-register differences, and 411 normal 356/356 with only two setup schedules still open.
TMCJPEG_814F2B50, local-order-5: 1544/1544 bytes, 99.093260 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-13: 1544/1544 bytes, 99.183940 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-25: 1544/1544 bytes, 99.404144 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-51: 1544/1544 bytes, 99.443010 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-83: 1544/1544 bytes, 99.481865 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-117: 1544/1544 bytes, 99.689120 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-614: 1544/1544 bytes, 99.922280 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, local-order-retained: 1544/1544 bytes, 99.922280 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, 411-skip-shape-baseline: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-new-s32-chroma-skip: 1424/1424 bytes, 92.387640 percent, 13 positional non-register differences, first [153, 155, 224, 225, 226, 228, 229, 230].
TMCJPEG_814EFEAC, 411-new-u32-chroma-skip: 1424/1424 bytes, 92.387640 percent, 13 positional non-register differences, first [153, 155, 224, 225, 226, 228, 229, 230].
TMCJPEG_814EFEAC, 411-reused-skip-after-address-simplification: 1424/1424 bytes, 93.286514 percent, 13 positional non-register differences, first [153, 155, 224, 225, 226, 228, 229, 230].
TMCJPEG_814EFEAC, 411-reused-skip-at-row-end: 1436/1424 bytes, 89.356740 percent, 195 positional non-register differences, first [146, 147, 148, 149, 150, 152, 153, 154].
TMCJPEG_814EFEAC, 411-width-becomes-row-skip: 1424/1424 bytes, 93.286514 percent, 13 positional non-register differences, first [153, 155, 224, 225, 226, 228, 229, 230].
TMCJPEG_814EFEAC, 411-unsigned-shared-skip: 1424/1424 bytes, 93.258430 percent, 13 positional non-register differences, first [153, 155, 224, 225, 226, 228, 229, 230].
TMCJPEG_814EFEAC, 411-skip-shape-retained: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814F2B50, 211-edge-height-register-baseline: 1544/1544 bytes, 99.922280 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, 211-edge-height-in-bound: 1544/1544 bytes, 100.000000 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, 211-edge-new-chroma-height: 1544/1544 bytes, 100.000000 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, 211-edge-width-read-before-height: 1544/1544 bytes, 100.000000 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, 211-edge-height-two-statements: 1544/1544 bytes, 100.000000 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2B50, 211-edge-height-register-retained: 1544/1544 bytes, 100.000000 percent, 0 positional non-register differences, first [].
TMCJPEG_814F043C, lifetime-baseline: 1564/1564 bytes, 93.657290 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, reuse-chromaXEnd: 1564/1564 bytes, 94.539640 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, lifetime-retained: 1564/1564 bytes, 94.539640 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F2570, lifetime-baseline: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, lifetime-retained: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F0A58, lifetime-baseline: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, reuse-chromaXEnd: 1900/1900 bytes, 94.989470 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, reuse-chromaYEnd: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, lifetime-retained: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-column-baseline: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, new-chroma-column: 1900/1900 bytes, 93.673680 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, scoped-chroma-column: 1900/1900 bytes, 93.673680 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-column-retained: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F043C, chroma-column-baseline: 1564/1564 bytes, 94.539640 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, new-chroma-column: 1564/1564 bytes, 93.657290 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, scoped-chroma-column: 1564/1564 bytes, 93.657290 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, chroma-column-retained: 1564/1564 bytes, 94.539640 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F2570, chroma-column-baseline: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, new-chroma-column: 1504/1504 bytes, 93.164894 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, scoped-chroma-column: 1504/1504 bytes, 93.164894 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, chroma-column-retained: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814EFEAC, 411-second-phase-baseline: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-height-from-width: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-direct-height-bound: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-skip-before-chroma-bounds: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-inline-row-skip: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-separate-chroma-width: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-second-phase-retained: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-height-stride-baseline: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-stride-from-height: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-one-dimension: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-new-height: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-only-width: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-height-stride-retained: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-width-read-order-baseline: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-width-read-before-x: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, 411-chroma-width-read-before-width: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, 411-chroma-width-read-before-height: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-width-read-before-chromaXEnd: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-chroma-width-read-before-chromaYEnd: 1424/1424 bytes, 99.255615 percent, 2 positional non-register differences, first [153, 156].
TMCJPEG_814EFEAC, 411-width-read-order-retained: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, pairwise-declaration-baseline: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, pairwise-declaration-retained: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, chroma-column-baseline: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, new-chroma-column: 1424/1424 bytes, 98.820220 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, scoped-chroma-column: 1424/1424 bytes, 98.820220 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, chroma-column-retained: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814F043C, exact-template-baseline: 1564/1564 bytes, 94.539640 percent, 11 positional non-register differences, first [260, 261, 262, 264, 265, 266, 268, 271].
TMCJPEG_814F043C, exact-211-edge-shape-port: 1564/1564 bytes, 99.475700 percent, 0 positional non-register differences, first [].
TMCJPEG_814F11C4, exact-template-baseline: 1564/1564 bytes, 91.790280 percent, 18 positional non-register differences, first [272, 274, 275, 278, 280, 281, 282, 284].
TMCJPEG_814F11C4, exact-211-edge-shape-port: 1564/1564 bytes, 99.475700 percent, 0 positional non-register differences, first [].
TMCJPEG_814F1F48, exact-template-baseline: 1576/1576 bytes, 92.596440 percent, 21 positional non-register differences, first [180, 182, 183, 184, 185, 188, 189, 190].
TMCJPEG_814F1F48, exact-211-edge-shape-port: 1576/1576 bytes, 99.555840 percent, 0 positional non-register differences, first [].
TMCJPEG_814F2570, exact-template-baseline: 1504/1504 bytes, 93.723404 percent, 11 positional non-register differences, first [242, 243, 244, 246, 247, 248, 250, 253].
TMCJPEG_814F2570, exact-211-edge-shape-port: 1504/1504 bytes, 99.587770 percent, 0 positional non-register differences, first [].
TMCJPEG_814F17E0, 420-complete-422-luma-and-chroma-port: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F0A58, chroma-read-order-baseline: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-width-read-before-x: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-width-read-before-width: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-width-read-before-height: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-width-read-before-chromaXEnd: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-width-read-before-chromaYEnd: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, chroma-read-order-retained: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F17E0, chroma-read-order-baseline: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-x: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-y: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-width: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-height: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-chromaXEnd: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-width-read-before-chromaYEnd: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, chroma-read-order-retained: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F0A58, row-skip-baseline: 1900/1900 bytes, 95.073685 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, inline-chromaRowSkip: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, row-skip-retained: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F17E0, row-skip-baseline: 1896/1896 bytes, 93.424050 percent, 17 positional non-register differences, first [353, 354, 358, 360, 362, 364, 366, 367].
TMCJPEG_814F17E0, inline-chromaRowSkip: 1896/1896 bytes, 98.997890 percent, 0 positional non-register differences, first [].
TMCJPEG_814F17E0, row-skip-retained: 1896/1896 bytes, 98.997890 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, chroma-read-order-baseline: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-read-before-x: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-read-before-width: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-read-before-height: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-read-before-chromaXEnd: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-read-before-chromaYEnd: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-read-order-retained: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, stride-expression-baseline: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-stride-8 + (-width): 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-stride-(-width) + 8: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-stride-(u32)(8 - width): 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-stride-(s32)(8 - width): 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-pointer-subtract-width-minus-eight: 1900/1900 bytes, 93.073685 percent, 15 positional non-register differences, first [274, 275, 343, 344, 345, 347, 348, 349].
TMCJPEG_814F0A58, chroma-next-row-index: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, stride-expression-retained: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEGDEC_set_converterY8U8V8, setter-pointer-form-baseline: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-void-pointer-arithmetic: compiler rejected the pointer expression. Reverted.
TMCJPEGDEC_set_converterY8U8V8, setter-signed-byte-base: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-conversion-buffer-array-pointer: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-pointer-form-retained: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEG_814F0A58, 422-chroma-header-baseline: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-direct-chroma-height-bound: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-chroma-only-width-value: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-separate-chroma-width: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-separate-chroma-height: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-unsigned-chroma-width: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-reverse-bound-definition-order: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, 422-chroma-header-retained: 1900/1900 bytes, 98.547370 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-8: 1900/1900 bytes, 98.578950 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-10: 1900/1900 bytes, 98.610530 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-27: 1900/1900 bytes, 98.884210 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-46: 1900/1900 bytes, 98.915790 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-67: 1900/1900 bytes, 98.936844 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-76: 1900/1900 bytes, 99.200000 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-87: 1900/1900 bytes, 99.231580 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-280: 1900/1900 bytes, 99.263160 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-361: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, local-order-retained: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
Round 3 progress: TMCJPEG_814F2B50 is now objdiff 100.0 percent; its remaining five scratch-register differences disappeared when chroma height was calculated directly in the bound. Porting that exact source to 411 edge, 422 edge, 420 edge and 211 normal makes all four instruction counts match with only register operands remaining. Normal 411 is also down to only register operands; normal 420 now has 474/474 instructions and only register operands. Normal 422 has 475/475 with two chroma-setup instruction schedules still open. Setter retains the known buffer-address folding and store-order barrier.
TMCJPEGDEC_set_converterY8U8V8, setter-inline-buffer-argument: 780/784 bytes, 92.765305 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-inline-buffer-argument-rejected: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEG_814EFEAC, tile-width-form-baseline: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, reuse-luma-tile-width: 1424/1424 bytes, 99.648880 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, signed-chroma-tile-width: 1436/1424 bytes, 74.404495 percent, 314 positional non-register differences, first [0, 4, 12, 13, 15, 16, 17, 18].
TMCJPEG_814EFEAC, chroma-width-load-and-shift: 1424/1424 bytes, 99.691010 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, chroma-width-byte-count-temporary: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, chroma-width-load-unsigned-division: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, tile-width-form-retained: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, tile-width-form-baseline: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, reuse-luma-tile-width: 1900/1900 bytes, 99.326320 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, signed-chroma-tile-width: 1900/1900 bytes, 63.692630 percent, 300 positional non-register differences, first [0, 1, 2, 3, 4, 5, 6, 7].
TMCJPEG_814F0A58, chroma-width-load-and-shift: 1900/1900 bytes, 98.894740 percent, 2 positional non-register differences, first [272, 274].
TMCJPEG_814F0A58, chroma-width-byte-count-temporary: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-width-load-unsigned-division: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, tile-width-form-retained: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, inline-stride-baseline: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, inline-row-skip-at-row-end: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, inline-row-skip-before-loop: 1900/1900 bytes, 94.494736 percent, 11 positional non-register differences, first [343, 344, 345, 347, 348, 349, 351, 354].
TMCJPEG_814F0A58, inline-stride-retained: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-header-skip-baseline: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, scoped-const-skip: 1912/1900 bytes, 91.098946 percent, 194 positional non-register differences, first [265, 266, 267, 268, 269, 271, 272, 273].
TMCJPEG_814F0A58, scoped-skip: 1912/1900 bytes, 91.098946 percent, 194 positional non-register differences, first [265, 266, 267, 268, 269, 271, 272, 273].
TMCJPEG_814F0A58, outer-skip: 1912/1900 bytes, 91.098946 percent, 194 positional non-register differences, first [265, 266, 267, 268, 269, 271, 272, 273].
TMCJPEG_814F0A58, chroma-header-skip-retained: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814EFEAC, chroma-constant-width-baseline: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, scoped-const-u32-chroma-tile-width: 1424/1424 bytes, 98.932590 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, scoped-u32-chroma-tile-width: 1424/1424 bytes, 98.932590 percent, 0 positional non-register differences, first [].
TMCJPEG_814EFEAC, chroma-constant-width-retained: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, chroma-constant-width-baseline: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, scoped-const-u32-chroma-tile-width: 1900/1900 bytes, 98.052635 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, scoped-u32-chroma-tile-width: 1900/1900 bytes, 98.052635 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, chroma-constant-width-retained: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEGDEC_set_converterY8U8V8, setter-case-translation-baseline: 780/784 bytes, 92.739800 percent, 175 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-cases-through-1: 780/784 bytes, 92.744896 percent, 177 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-cases-through-3: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-cases-through-5: 780/784 bytes, 92.540820 percent, 183 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-case-translation-retained: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-temporary-case-baseline: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-order-temporaries-through-1: 780/784 bytes, 92.734695 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-order-temporaries-through-3: 780/784 bytes, 92.683670 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-order-temporaries-through-5: 780/784 bytes, 92.438774 percent, 183 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-order-temporaries-retained: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-dispatch-baseline: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-address-ordered-branch-blocks: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEG_814F0A58, one-plane-skip-baseline: 1900/1900 bytes, 99.368420 percent, 2 positional non-register differences, first [274, 275].
TMCJPEG_814F0A58, one-plane-cb-skip-8 - width: 1900/1900 bytes, 99.010530 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, one-plane-cb-skip-8 - height: 1912/1900 bytes, 97.741050 percent, 193 positional non-register differences, first [0, 3, 268, 270, 271, 272, 273, 274].
TMCJPEG_814F0A58, one-plane-cr-skip-8 - width: 1900/1900 bytes, 99.010530 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, one-plane-cr-skip-8 - height: 1912/1900 bytes, 97.698944 percent, 193 positional non-register differences, first [0, 3, 268, 270, 271, 272, 273, 274].
TMCJPEG_814F0A58, one-plane-skip-retained: 1900/1900 bytes, 99.010530 percent, 0 positional non-register differences, first [].
TMCJPEGDEC_set_converterY8U8V8, setter-initializer-baseline: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-buffer-initializer: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-all-initializers: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-const buffer-initializer: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-const all-initializers: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEGDEC_set_converterY8U8V8, setter-initializer-retained: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
Byte audit: [('TMCJPEG_814F2B50', 1544, '90cafddeb6c5e9cc7a1697de26afc992a99a15b2dd43c77827e4ba2c74416b6f'), ('TMCJPEG_814F3158', 396, 'ebff8cfa476f8b73a0e25774de6ed1894610b7bfeb01dba893d52ec77630be24'), ('TMCJPEG_814F32E4', 448, '0285055cc73aa0c067bf01d154c35507e4b7d5e15b415513ab79574b4942553c'), ('TMCJPEG_814F34A4', 648, '2d24887255337ced3949a4cd8df4d806620a7ab69e61a4c2b3c882037c044f2c'), ('TMCJPEG_814F372C', 700, '2ae15e8409df7cc2ca3ed0b394c7850dc30209078f3888253095c969b5463a8c')]. The external ctxdiff normalization misreads the first operand of CR-qualified branches as an immediate; its branch displacement differences are spurious when raw bytes are equal. Tools and baseline reports were not changed.
TMCJPEGDEC_set_converterY8U8V8, final-readable-pointer-stores: 780/784 bytes, 92.785710 percent, 179 positional non-register differences, first [1, 2, 3, 4, 5, 6, 7, 8].
TMCJPEG_814EFEAC, final-readable-four-pixel-expression: 1424/1424 bytes, 99.719100 percent, 0 positional non-register differences, first [].
TMCJPEG_814F0A58, final-aligned-chroma-header: 1900/1900 bytes, 99.010530 percent, 0 positional non-register differences, first [].
Round 3 current result: all eight converter bodies were translated through their epilogues and now have target instruction counts. Seven differ only in registers and 211 edge is byte-identical. Setter was translated/reviewed through all six cases, dimension rounding and epilogue, but remains 195/196 instructions because the compiler folds its buffer-base address into individual case addresses; its store scheduling also differs. Forty-plus ordinary source variations were logged for that barrier; no artificial address preservation was used.

## Round 3 final source and instruction audit

Before sizes were rebuilt from the starting source, then current source was restored and rebuilt. Register-normalized comparisons use actual relative branch destinations; byte-exact results compare complete function byte ranges with original ELF sections. Original allocated data sections: {}.

| Function | Source bytes before -> after (target) | Fuzzy before -> after | Remaining |
|---|---|---|---|
| TMCJPEGDEC_set_converterY8U8V8 | 780 -> 780 (784) | 92.739800 -> 92.785710 | buffer-base folding and case store scheduling; 195/196 instructions |
| TMCJPEG_814EFEAC | 1352 -> 1424 (1424) | 53.101124 -> 99.719100 | register allocation only |
| TMCJPEG_814F043C | 1564 -> 1564 (1564) | 57.682865 -> 99.475700 | register allocation only |
| TMCJPEG_814F0A58 | 1908 -> 1900 (1900) | 45.195790 -> 99.010530 | register allocation only |
| TMCJPEG_814F11C4 | 1564 -> 1564 (1564) | 57.682865 -> 99.475700 | register allocation only |
| TMCJPEG_814F17E0 | 1900 -> 1896 (1896) | 44.407173 -> 98.997890 | register allocation only |
| TMCJPEG_814F1F48 | 1600 -> 1576 (1576) | 52.167510 -> 99.555840 | register allocation only |
| TMCJPEG_814F2570 | 1504 -> 1504 (1504) | 52.587765 -> 99.587770 | register allocation only |
| TMCJPEG_814F2B50 | 1544 -> 1544 (1544) | 55.795338 -> 100.000000 | byte-identical |
| TMCJPEG_814F3158 | 396 -> 396 (396) | 100.000000 -> 100.000000 | byte-identical |
| TMCJPEG_814F32E4 | 448 -> 448 (448) | 100.000000 -> 100.000000 | byte-identical |
| TMCJPEG_814F34A4 | 648 -> 648 (648) | 100.000000 -> 100.000000 | byte-identical |
| TMCJPEG_814F372C | 700 -> 700 (700) | 100.000000 -> 100.000000 | byte-identical |

Raw byte-identical functions: 5/13; exact code bytes 2192 -> 3736; allocated data bytes 0 -> 0. Seven open converters now match instruction counts and normalized operations throughout. The setter remains open with the recorded folding/scheduling barrier.
Baseline-count correction: rebuilding the exact starting commit source confirms 211 edge started at 386 instructions (1544 bytes), rather than the 385 written in the initial round note. The before/after table above uses that verified build.

Final non-quick gate: PASS; clean full build, original DOL hash, identical empty pool, zero regressions, zero added forbidden patterns, zero readability warnings. Fresh clean-build byte comparison confirms 5/13 exact; register-normalized complete instruction sequences match 12/13, with setter the only structural remainder. External instruction-exact 2/13 is the previously logged branch-normalization issue; full raw byte evidence and objdiff agree on 5/13.
