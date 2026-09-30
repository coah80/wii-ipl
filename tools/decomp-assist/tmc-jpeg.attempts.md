# TMC JPEG matching attempts

All work stayed in this worktree. No units were changed to Matching. Only the EXIF marker scan gained an exact function. The other five units are uncommitted partial implementations or cleanup experiments.

The quick gate accepts non-regressing partial code. A GATE PASS alone does not establish a new exact function or a complete unit.

All six units have no data bytes or string pools. pool_diff.py cannot read absent .data sections; the gate independently reported identical empty pools.

## texturecvtr/Texture_MCUtoRGB565

- rgb-inline-store: Reordered 444/400 switch cases and named the four 420 row pointers before assigning them.
- rgb-explicit-pixels: Expanded the pixel-store helper into scoped RGB channel calculations at each pixel.
- rgb-byte-samples: Changed signed sample pointers to byte pointers with signed sample casts; expressed texture rows through byte pointers.
- rgb-final-byte-setup: Final setup uses byte offsets into the actual conversion buffer; no address-pinning symbols or objects.
- rgb-initial-layouts: Literal MCU loops, signed chroma pointers, inlined pixel-store helper; corrected buffer layout and rounded texture bounds.
- rgb-self-saturation: Used explicit channel saturation statements and copied grayscale channels before saturation.
- rgb-ternary-saturation: Expressed channel saturation with ternaries and kept grayscale copies in their branch.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCJPEGDEC_set_converterRGB565 | rgb-inline-store | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-explicit-pixels | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-byte-samples | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-final-byte-setup | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-initial-layouts | 88.511765 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-self-saturation | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGB565 | rgb-ternary-saturation | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-inline-store | 74.502304 | 217/217 | 199 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-explicit-pixels | 72.820274 | 217/217 | 200 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-byte-samples | 72.797230 | 217/217 | 201 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-final-byte-setup | 72.797230 | 217/217 | 201 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-initial-layouts | 74.502304 | 217/217 | 199 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-self-saturation | 72.797230 | 217/217 | 201 |
| TMCJPEGDEC_converterYUV411toRGB565 | rgb-ternary-saturation | 72.797230 | 217/217 | 201 |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-inline-store | 75.311320 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-explicit-pixels | 80.783020 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-byte-samples | 80.924530 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-final-byte-setup | 80.924530 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-initial-layouts | 75.311320 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-self-saturation | 80.924530 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV411toRGB565edge | rgb-ternary-saturation | 80.924530 | 109/106 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-inline-store | 76.058820 | 136/136 | 121 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-explicit-pixels | 76.544120 | 136/136 | 122 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-byte-samples | 76.580880 | 136/136 | 122 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-final-byte-setup | 76.580880 | 136/136 | 122 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-initial-layouts | 76.058820 | 136/136 | 121 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-self-saturation | 76.580880 | 136/136 | 122 |
| TMCJPEGDEC_converterYUV422toRGB565 | rgb-ternary-saturation | 76.580880 | 136/136 | 122 |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-inline-store | 83.037384 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-explicit-pixels | 80.934580 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-byte-samples | 80.794395 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-final-byte-setup | 80.794395 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-initial-layouts | 83.037384 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-self-saturation | 80.794395 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV422toRGB565edge | rgb-ternary-saturation | 80.794395 | 110/107 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-inline-store | 75.531910 | 141/141 | 127 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-explicit-pixels | 77.340420 | 141/141 | 125 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-byte-samples | 77.375885 | 141/141 | 125 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-final-byte-setup | 77.375885 | 141/141 | 125 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-initial-layouts | 75.531910 | 141/141 | 127 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-self-saturation | 77.375885 | 141/141 | 125 |
| TMCJPEGDEC_converterYUV420toRGB565 | rgb-ternary-saturation | 77.375885 | 141/141 | 125 |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-inline-store | 81.842100 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-explicit-pixels | 83.552635 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-byte-samples | 83.289474 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-final-byte-setup | 83.289474 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-initial-layouts | 81.842100 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-self-saturation | 83.289474 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV420toRGB565edge | rgb-ternary-saturation | 83.289474 | 117/114 | different counts |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-inline-store | 76.816330 | 98/98 | 80 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-explicit-pixels | 73.000000 | 98/98 | 85 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-byte-samples | 73.051020 | 98/98 | 85 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-final-byte-setup | 73.051020 | 98/98 | 85 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-initial-layouts | 76.816330 | 98/98 | 80 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-self-saturation | 73.051020 | 98/98 | 85 |
| TMCJPEGDEC_converterYUV211toRGB565 | rgb-ternary-saturation | 73.051020 | 98/98 | 85 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-inline-store | 80.862390 | 109/109 | 82 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-explicit-pixels | 77.192660 | 109/109 | 91 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-byte-samples | 77.238530 | 109/109 | 91 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-final-byte-setup | 77.238530 | 109/109 | 91 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-initial-layouts | 80.862390 | 109/109 | 82 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-self-saturation | 77.238530 | 109/109 | 91 |
| TMCJPEGDEC_converterYUV211toRGB565edge | rgb-ternary-saturation | 77.238530 | 109/109 | 91 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-inline-store | 75.373630 | 91/91 | 75 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-explicit-pixels | 73.450550 | 91/91 | 80 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-byte-samples | 73.505490 | 91/91 | 80 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-final-byte-setup | 73.505490 | 91/91 | 80 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-initial-layouts | 75.373630 | 91/91 | 75 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-self-saturation | 73.505490 | 91/91 | 80 |
| TMCJPEGDEC_converterYUV444toRGB565 | rgb-ternary-saturation | 73.505490 | 91/91 | 80 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-inline-store | 80.182690 | 104/104 | 79 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-explicit-pixels | 76.432690 | 104/104 | 88 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-byte-samples | 76.480770 | 104/104 | 88 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-final-byte-setup | 76.480770 | 104/104 | 88 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-initial-layouts | 80.182690 | 104/104 | 79 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-self-saturation | 76.480770 | 104/104 | 88 |
| TMCJPEGDEC_converterYUV444toRGB565edge | rgb-ternary-saturation | 76.480770 | 104/104 | 88 |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-inline-store | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-explicit-pixels | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-byte-samples | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-final-byte-setup | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-initial-layouts | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-self-saturation | 79.571430 | 67/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565 | rgb-ternary-saturation | 82.571430 | 68/70 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-inline-store | 84.216866 | 81/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-explicit-pixels | 84.216866 | 81/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-byte-samples | 84.216866 | 81/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-final-byte-setup | 84.216866 | 81/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-initial-layouts | 84.216866 | 81/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-self-saturation | 81.686745 | 80/83 | different counts |
| TMCJPEGDEC_converterYUV400toRGB565edge | rgb-ternary-saturation | 84.216866 | 81/83 | different counts |

## texturecvtr/Texture_MCUtoRGBA8

- rgba-inline-pixels: Ported the RGB MCU loops to split AR/GB texture tiles; corrected chroma signs and tile offsets.
- rgba-green-first: Computed green before red and changed the order of the channel range expression.
- rgba-signed-stride-and-bounds: Used a signed tile stride, computed vertical bounds first, and made grayscale copies before saturation.
- rgba-final: Reviewed the final readable source and rebuilt it.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCJPEGDEC_set_converterRGBA8 | rgba-inline-pixels | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGBA8 | rgba-green-first | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGBA8 | rgba-signed-stride-and-bounds | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_set_converterRGBA8 | rgba-final | 93.635290 | 169/170 | different counts |
| TMCJPEGDEC_converterYUV411toRGBA8 | rgba-inline-pixels | 63.995870 | 242/242 | 220 |
| TMCJPEGDEC_converterYUV411toRGBA8 | rgba-green-first | 65.190090 | 242/242 | 218 |
| TMCJPEGDEC_converterYUV411toRGBA8 | rgba-signed-stride-and-bounds | 65.871900 | 242/242 | 221 |
| TMCJPEGDEC_converterYUV411toRGBA8 | rgba-final | 65.871900 | 242/242 | 221 |
| TMCJPEGDEC_converterYUV411toRGBA8edge | rgba-inline-pixels | 75.294640 | 115/112 | different counts |
| TMCJPEGDEC_converterYUV411toRGBA8edge | rgba-green-first | 71.544640 | 115/112 | different counts |
| TMCJPEGDEC_converterYUV411toRGBA8edge | rgba-signed-stride-and-bounds | 71.544640 | 115/112 | different counts |
| TMCJPEGDEC_converterYUV411toRGBA8edge | rgba-final | 71.544640 | 115/112 | different counts |
| TMCJPEGDEC_converterYUV422toRGBA8 | rgba-inline-pixels | 68.743240 | 148/148 | 132 |
| TMCJPEGDEC_converterYUV422toRGBA8 | rgba-green-first | 67.770270 | 148/148 | 137 |
| TMCJPEGDEC_converterYUV422toRGBA8 | rgba-signed-stride-and-bounds | 66.486490 | 148/148 | 137 |
| TMCJPEGDEC_converterYUV422toRGBA8 | rgba-final | 66.486490 | 148/148 | 137 |
| TMCJPEGDEC_converterYUV422toRGBA8edge | rgba-inline-pixels | 71.725660 | 116/113 | different counts |
| TMCJPEGDEC_converterYUV422toRGBA8edge | rgba-green-first | 68.610620 | 116/113 | different counts |
| TMCJPEGDEC_converterYUV422toRGBA8edge | rgba-signed-stride-and-bounds | 68.610620 | 116/113 | different counts |
| TMCJPEGDEC_converterYUV422toRGBA8edge | rgba-final | 68.610620 | 116/113 | different counts |
| TMCJPEGDEC_converterYUV420toRGBA8 | rgba-inline-pixels | 68.424835 | 153/153 | 132 |
| TMCJPEGDEC_converterYUV420toRGBA8 | rgba-green-first | 69.810455 | 153/153 | 136 |
| TMCJPEGDEC_converterYUV420toRGBA8 | rgba-signed-stride-and-bounds | 69.745094 | 153/153 | 136 |
| TMCJPEGDEC_converterYUV420toRGBA8 | rgba-final | 69.745094 | 153/153 | 136 |
| TMCJPEGDEC_converterYUV420toRGBA8edge | rgba-inline-pixels | 74.166664 | 123/120 | different counts |
| TMCJPEGDEC_converterYUV420toRGBA8edge | rgba-green-first | 74.191666 | 123/120 | different counts |
| TMCJPEGDEC_converterYUV420toRGBA8edge | rgba-signed-stride-and-bounds | 74.191666 | 123/120 | different counts |
| TMCJPEGDEC_converterYUV420toRGBA8edge | rgba-final | 74.191666 | 123/120 | different counts |
| TMCJPEGDEC_converterYUV211toRGBA8 | rgba-inline-pixels | 69.846150 | 104/104 | 89 |
| TMCJPEGDEC_converterYUV211toRGBA8 | rgba-green-first | 69.480770 | 104/104 | 93 |
| TMCJPEGDEC_converterYUV211toRGBA8 | rgba-signed-stride-and-bounds | 69.480770 | 104/104 | 93 |
| TMCJPEGDEC_converterYUV211toRGBA8 | rgba-final | 69.480770 | 104/104 | 93 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | rgba-inline-pixels | 74.295654 | 115/115 | 96 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | rgba-green-first | 73.965220 | 115/115 | 99 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | rgba-signed-stride-and-bounds | 73.965220 | 115/115 | 99 |
| TMCJPEGDEC_converterYUV211toRGBA8edge | rgba-final | 73.965220 | 115/115 | 99 |
| TMCJPEGDEC_converterYUV444toRGBA8 | rgba-inline-pixels | 70.453606 | 97/97 | 85 |
| TMCJPEGDEC_converterYUV444toRGBA8 | rgba-green-first | 70.082470 | 97/97 | 87 |
| TMCJPEGDEC_converterYUV444toRGBA8 | rgba-signed-stride-and-bounds | 70.082470 | 97/97 | 87 |
| TMCJPEGDEC_converterYUV444toRGBA8 | rgba-final | 70.082470 | 97/97 | 87 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | rgba-inline-pixels | 73.445460 | 110/110 | 93 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | rgba-green-first | 73.118180 | 110/110 | 94 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | rgba-signed-stride-and-bounds | 73.118180 | 110/110 | 94 |
| TMCJPEGDEC_converterYUV444toRGBA8edge | rgba-final | 73.118180 | 110/110 | 94 |
| TMCJPEGDEC_converterYUV400toRGBA8 | rgba-inline-pixels | 84.276310 | 74/76 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8 | rgba-green-first | 84.276310 | 74/76 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8 | rgba-signed-stride-and-bounds | 84.276310 | 74/76 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8 | rgba-final | 84.276310 | 74/76 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8edge | rgba-inline-pixels | 85.561800 | 87/89 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8edge | rgba-green-first | 85.561800 | 87/89 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8edge | rgba-signed-stride-and-bounds | 85.561800 | 87/89 | different counts |
| TMCJPEGDEC_converterYUV400toRGBA8edge | rgba-final | 85.561800 | 87/89 | different counts |

## texturecvtr/Texture_MCUtoY8U8V8

- planar-indexed-tiles: Implemented each original symbol using tiled luma and chroma output loops; width and height fields are guarded for this TU only.
- planar-tile-index-and-count: Expressed tile addresses with multiplication, tested a bounded decrementing 444 loop, and used border-selection ternaries.
- planar-shared-chroma-offset: Used signed tile strides, vertical bounds first, shared chroma offsets, and explicit sample temporaries.
- planar-final: Returned to direct indexed tile loops after the weaker shared-offset experiment.
- planar-guarded-counted-444: Tested a guarded do-loop for the combined 444 planes. It removed automatic unrolling but was still smaller than the target.
- planar-signed-chroma-pointers: Changed chroma pointers to signed bytes. The compiler eliminated sign extension before byte stores; measurements stayed unchanged.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCJPEGDEC_set_converterY8U8V8 | planar-indexed-tiles | 92.540820 | 195/196 | different counts |
| TMCJPEGDEC_set_converterY8U8V8 | planar-tile-index-and-count | 89.760200 | 195/196 | different counts |
| TMCJPEGDEC_set_converterY8U8V8 | planar-shared-chroma-offset | 84.530610 | 193/196 | different counts |
| TMCJPEGDEC_set_converterY8U8V8 | planar-final | 92.540820 | 195/196 | different counts |
| TMCJPEGDEC_set_converterY8U8V8 | planar-guarded-counted-444 | 92.540820 | 195/196 | different counts |
| TMCJPEGDEC_set_converterY8U8V8 | planar-signed-chroma-pointers | 92.540820 | 195/196 | different counts |
| TMCJPEG_814EFEAC | planar-indexed-tiles | 52.233147 | 338/356 | different counts |
| TMCJPEG_814EFEAC | planar-tile-index-and-count | 52.233147 | 338/356 | different counts |
| TMCJPEG_814EFEAC | planar-shared-chroma-offset | 45.828650 | 317/356 | different counts |
| TMCJPEG_814EFEAC | planar-final | 52.233147 | 338/356 | different counts |
| TMCJPEG_814EFEAC | planar-guarded-counted-444 | 52.233147 | 338/356 | different counts |
| TMCJPEG_814EFEAC | planar-signed-chroma-pointers | 52.233147 | 338/356 | different counts |
| TMCJPEG_814F043C | planar-indexed-tiles | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F043C | planar-tile-index-and-count | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F043C | planar-shared-chroma-offset | 44.304348 | 371/391 | different counts |
| TMCJPEG_814F043C | planar-final | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F043C | planar-guarded-counted-444 | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F043C | planar-signed-chroma-pointers | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F0A58 | planar-indexed-tiles | 43.534737 | 477/475 | different counts |
| TMCJPEG_814F0A58 | planar-tile-index-and-count | 43.534737 | 477/475 | different counts |
| TMCJPEG_814F0A58 | planar-shared-chroma-offset | 41.677895 | 456/475 | different counts |
| TMCJPEG_814F0A58 | planar-final | 43.534737 | 477/475 | different counts |
| TMCJPEG_814F0A58 | planar-guarded-counted-444 | 43.534737 | 477/475 | different counts |
| TMCJPEG_814F0A58 | planar-signed-chroma-pointers | 43.534737 | 477/475 | different counts |
| TMCJPEG_814F11C4 | planar-indexed-tiles | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F11C4 | planar-tile-index-and-count | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F11C4 | planar-shared-chroma-offset | 44.304348 | 371/391 | different counts |
| TMCJPEG_814F11C4 | planar-final | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F11C4 | planar-guarded-counted-444 | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F11C4 | planar-signed-chroma-pointers | 51.355500 | 391/391 | 387 |
| TMCJPEG_814F17E0 | planar-indexed-tiles | 41.890297 | 475/474 | different counts |
| TMCJPEG_814F17E0 | planar-tile-index-and-count | 41.890297 | 475/474 | different counts |
| TMCJPEG_814F17E0 | planar-shared-chroma-offset | 39.810127 | 454/474 | different counts |
| TMCJPEG_814F17E0 | planar-final | 41.890297 | 475/474 | different counts |
| TMCJPEG_814F17E0 | planar-guarded-counted-444 | 41.890297 | 475/474 | different counts |
| TMCJPEG_814F17E0 | planar-signed-chroma-pointers | 41.890297 | 475/474 | different counts |
| TMCJPEG_814F1F48 | planar-indexed-tiles | 46.809643 | 400/394 | different counts |
| TMCJPEG_814F1F48 | planar-tile-index-and-count | 46.809643 | 400/394 | different counts |
| TMCJPEG_814F1F48 | planar-shared-chroma-offset | 41.375633 | 379/394 | different counts |
| TMCJPEG_814F1F48 | planar-final | 46.809643 | 400/394 | different counts |
| TMCJPEG_814F1F48 | planar-guarded-counted-444 | 46.809643 | 400/394 | different counts |
| TMCJPEG_814F1F48 | planar-signed-chroma-pointers | 46.809643 | 400/394 | different counts |
| TMCJPEG_814F2570 | planar-indexed-tiles | 47.063830 | 376/376 | 370 |
| TMCJPEG_814F2570 | planar-tile-index-and-count | 47.063830 | 376/376 | 370 |
| TMCJPEG_814F2570 | planar-shared-chroma-offset | 42.981384 | 356/376 | different counts |
| TMCJPEG_814F2570 | planar-final | 47.063830 | 376/376 | 370 |
| TMCJPEG_814F2570 | planar-guarded-counted-444 | 47.063830 | 376/376 | 370 |
| TMCJPEG_814F2570 | planar-signed-chroma-pointers | 47.063830 | 376/376 | 370 |
| TMCJPEG_814F2B50 | planar-indexed-tiles | 52.950780 | 385/386 | different counts |
| TMCJPEG_814F2B50 | planar-tile-index-and-count | 52.950780 | 385/386 | different counts |
| TMCJPEG_814F2B50 | planar-shared-chroma-offset | 46.113990 | 365/386 | different counts |
| TMCJPEG_814F2B50 | planar-final | 52.950780 | 385/386 | different counts |
| TMCJPEG_814F2B50 | planar-guarded-counted-444 | 52.950780 | 385/386 | different counts |
| TMCJPEG_814F2B50 | planar-signed-chroma-pointers | 52.950780 | 385/386 | different counts |
| TMCJPEG_814F3158 | planar-indexed-tiles | unscored | 275/99 | different counts |
| TMCJPEG_814F3158 | planar-tile-index-and-count | unscored | 230/99 | different counts |
| TMCJPEG_814F3158 | planar-shared-chroma-offset | unscored | 215/99 | different counts |
| TMCJPEG_814F3158 | planar-final | unscored | 275/99 | different counts |
| TMCJPEG_814F3158 | planar-guarded-counted-444 | 37.404040 | 63/99 | different counts |
| TMCJPEG_814F3158 | planar-signed-chroma-pointers | unscored | 275/99 | different counts |
| TMCJPEG_814F32E4 | planar-indexed-tiles | unscored | 288/112 | different counts |
| TMCJPEG_814F32E4 | planar-tile-index-and-count | unscored | 243/112 | different counts |
| TMCJPEG_814F32E4 | planar-shared-chroma-offset | unscored | 228/112 | different counts |
| TMCJPEG_814F32E4 | planar-final | unscored | 288/112 | different counts |
| TMCJPEG_814F32E4 | planar-guarded-counted-444 | 45.651787 | 76/112 | different counts |
| TMCJPEG_814F32E4 | planar-signed-chroma-pointers | unscored | 288/112 | different counts |
| TMCJPEG_814F34A4 | planar-indexed-tiles | 60.037037 | 147/162 | different counts |
| TMCJPEG_814F34A4 | planar-tile-index-and-count | 60.037037 | 147/162 | different counts |
| TMCJPEG_814F34A4 | planar-shared-chroma-offset | 59.728394 | 147/162 | different counts |
| TMCJPEG_814F34A4 | planar-final | 60.037037 | 147/162 | different counts |
| TMCJPEG_814F34A4 | planar-guarded-counted-444 | 60.037037 | 147/162 | different counts |
| TMCJPEG_814F34A4 | planar-signed-chroma-pointers | 60.037037 | 147/162 | different counts |
| TMCJPEG_814F372C | planar-indexed-tiles | 62.891430 | 160/175 | different counts |
| TMCJPEG_814F372C | planar-tile-index-and-count | 62.891430 | 160/175 | different counts |
| TMCJPEG_814F372C | planar-shared-chroma-offset | 62.605713 | 160/175 | different counts |
| TMCJPEG_814F372C | planar-final | 62.891430 | 160/175 | different counts |
| TMCJPEG_814F372C | planar-guarded-counted-444 | 62.891430 | 160/175 | different counts |
| TMCJPEG_814F372C | planar-signed-chroma-pointers | 62.891430 | 160/175 | different counts |

## buffer/idct_block_var

- idct-output-and-saturation: Restored missing Lumi butterfly outputs, completed zero filling, fixed unsigned saturation, and restored the second-pass luma bias.
- idct-row-loop-and-butterfly-sums: Tested a row-count loop, sequential AC accumulation, and grouped butterfly sums in both functions.
- idct-butterfly-temporaries: Separated odd butterfly factors into temporaries and used a sign-mask clamp.
- idct-final-complete-butterfly-output: Also restored the three missing Col butterfly stores so no temporary output is left uninitialized.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCJPEGDEC_IdctBlock_Lumi | idct-output-and-saturation | 64.821014 | 259/257 | different counts |
| TMCJPEGDEC_IdctBlock_Lumi | idct-row-loop-and-butterfly-sums | 64.712060 | 258/257 | different counts |
| TMCJPEGDEC_IdctBlock_Lumi | idct-butterfly-temporaries | 63.077820 | 257/257 | 217 |
| TMCJPEGDEC_IdctBlock_Lumi | idct-final-complete-butterfly-output | 63.077820 | 257/257 | 217 |
| TMCJPEGDEC_IdctBlock_Col | idct-output-and-saturation | 70.601320 | 471/454 | different counts |
| TMCJPEGDEC_IdctBlock_Col | idct-row-loop-and-butterfly-sums | 70.055070 | 471/454 | different counts |
| TMCJPEGDEC_IdctBlock_Col | idct-butterfly-temporaries | 70.055070 | 471/454 | different counts |
| TMCJPEGDEC_IdctBlock_Col | idct-final-complete-butterfly-output | 69.085900 | 480/454 | different counts |

## b65/iqdec_b65_frv32

- iq-struct-return-helper: Removed all volatile coercions; represented fast Huffman entries with named fields and ordinary struct-value returns.
- iq-value-limit-helper: Used a local limit struct returned by value and reloaded the bit position after buffer loading.
- iq-shared-long-code-decoder: Factored long Huffman decoding into a shared C helper. The compiler did not inline it.
- iq-inline-long-code-decoder: Requested ordinary C inline expansion of the shared helper; branch layout and register allocation still differed.
- iq-final: Retained the value-copy experiment rather than the weaker shared-decoder experiment.
- iq-typed-limit-iteration: Removed redundant reads and byte-offset casts; iterated typed entries and reused the cached AC table.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCJPEGDEC_decode_iquant | iq-struct-return-helper | 83.829710 | 271/276 | different counts |
| TMCJPEGDEC_decode_iquant | iq-value-limit-helper | 85.333336 | 281/276 | different counts |
| TMCJPEGDEC_decode_iquant | iq-shared-long-code-decoder | 61.442028 | 196/276 | different counts |
| TMCJPEGDEC_decode_iquant | iq-inline-long-code-decoder | 71.557970 | 280/276 | different counts |
| TMCJPEGDEC_decode_iquant | iq-final | 85.333336 | 281/276 | different counts |
| TMCJPEGDEC_decode_iquant | iq-typed-limit-iteration | 84.641304 | 280/276 | different counts |

## exif/exif_parse

- exif-bounds-widths-and-entry-order: Corrected directory offset checks and remaining-byte widths; changed byte assembly order and bounded pointers against end minus field size.
- exif-pointer-lifetimes-and-switch-tags: Computed entry pointers before remaining counts, advanced pointers before checking entry space, and tested ignored EXIF tag cases.
- exif-switch-breaks-and-declarations: Tested break-based switch bodies and separate declarations for tag offsets and pointers.
- exif-scoped-directory-entries: Gave each directory its own pointer, remaining count, entry count, and loop index.
- exif-marker-switch-and-byte-copy: Used a marker switch, copied the 20 date-time bytes individually, and recomputed transfer-function pointers from offsets.
- exif-marker-local-order: Ordered marker and segment locals to match the target stack slots and swapped the two terminal-marker case bodies. GetOffsetEXIF reached exact.
- exif-separate-ignored-tag-blocks: Tested separate ignored-tag bodies. The dispatch grew and did not improve matching; discarded.
- exif-final: Restored the independently gated, committed EXIF result.

| Function | Attempt | Objdiff % | Instructions mine/target | Instruction differences |
| --- | --- | ---: | ---: | ---: |
| TMCCJPEGDecGetOffsetEXIF | exif-bounds-widths-and-entry-order | 77.129036 | 171/155 | different counts |
| TMCCJPEGDecGetOffsetEXIF | exif-pointer-lifetimes-and-switch-tags | 77.129036 | 171/155 | different counts |
| TMCCJPEGDecGetOffsetEXIF | exif-switch-breaks-and-declarations | 77.129036 | 171/155 | different counts |
| TMCCJPEGDecGetOffsetEXIF | exif-scoped-directory-entries | 77.129036 | 171/155 | different counts |
| TMCCJPEGDecGetOffsetEXIF | exif-marker-switch-and-byte-copy | 99.877420 | 155/155 | 11 |
| TMCCJPEGDecGetOffsetEXIF | exif-marker-local-order | 100.000000 | 155/155 | 0 |
| TMCCJPEGDecGetOffsetEXIF | exif-separate-ignored-tag-blocks | 100.000000 | 155/155 | 0 |
| TMCCJPEGDecGetOffsetEXIF | exif-final | 100.000000 | 155/155 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-bounds-widths-and-entry-order | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-pointer-lifetimes-and-switch-tags | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-switch-breaks-and-declarations | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-scoped-directory-entries | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-marker-switch-and-byte-copy | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-marker-local-order | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-separate-ignored-tag-blocks | 100.000000 | 132/132 | 0 |
| TMCCJPEGDecGetInfoEXIF | exif-final | 100.000000 | 132/132 | 0 |
| TMCJPEGDEC_exif_parse | exif-bounds-widths-and-entry-order | 85.528305 | 212/212 | 118 |
| TMCJPEGDEC_exif_parse | exif-pointer-lifetimes-and-switch-tags | 98.514150 | 212/212 | 52 |
| TMCJPEGDEC_exif_parse | exif-switch-breaks-and-declarations | 98.514150 | 212/212 | 52 |
| TMCJPEGDEC_exif_parse | exif-scoped-directory-entries | 98.113205 | 212/212 | 58 |
| TMCJPEGDEC_exif_parse | exif-marker-switch-and-byte-copy | 98.113205 | 212/212 | 58 |
| TMCJPEGDEC_exif_parse | exif-marker-local-order | 98.113205 | 212/212 | 58 |
| TMCJPEGDEC_exif_parse | exif-separate-ignored-tag-blocks | 98.113205 | 212/212 | 58 |
| TMCJPEGDEC_exif_parse | exif-final | 98.113205 | 212/212 | 58 |
| TMCJPEGDEC_IFD0_tag_parse | exif-bounds-widths-and-entry-order | 70.449066 | 446/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-pointer-lifetimes-and-switch-tags | 75.883575 | 446/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-switch-breaks-and-declarations | 75.883575 | 446/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-scoped-directory-entries | 75.883575 | 446/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-marker-switch-and-byte-copy | 85.507280 | 480/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-marker-local-order | 85.507280 | 480/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-separate-ignored-tag-blocks | 85.507280 | 480/481 | different counts |
| TMCJPEGDEC_IFD0_tag_parse | exif-final | 85.507280 | 480/481 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-bounds-widths-and-entry-order | 82.797520 | 243/242 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-pointer-lifetimes-and-switch-tags | 97.570250 | 244/242 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-switch-breaks-and-declarations | 91.566120 | 240/242 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-scoped-directory-entries | 91.566120 | 240/242 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-marker-switch-and-byte-copy | 92.107440 | 242/242 | 79 |
| TMCJPEGDEC_IFD1_tag_parse | exif-marker-local-order | 92.107440 | 242/242 | 79 |
| TMCJPEGDEC_IFD1_tag_parse | exif-separate-ignored-tag-blocks | 85.975204 | 260/242 | different counts |
| TMCJPEGDEC_IFD1_tag_parse | exif-final | 92.107440 | 242/242 | 79 |
| TMCJPEGDEC_ThumbnailCheck | exif-bounds-widths-and-entry-order | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-pointer-lifetimes-and-switch-tags | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-switch-breaks-and-declarations | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-scoped-directory-entries | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-marker-switch-and-byte-copy | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-marker-local-order | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-separate-ignored-tag-blocks | 100.000000 | 50/50 | 0 |
| TMCJPEGDEC_ThumbnailCheck | exif-final | 100.000000 | 50/50 | 0 |

## Remaining differences

The last full gate is the final authority. Each unmatched function is listed here with its final score and instruction evidence. Equal instruction counts do not establish a pure register tie-break; branch offsets and operand scheduling also remain.

- TMCJPEGDEC_set_converterRGB565: 93.635290%, 169/170 instructions, conversion-buffer address folding and scheduling.
- TMCJPEGDEC_converterYUV411toRGB565: 72.797230%, 217/217 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV411toRGB565edge: 80.924530%, 109/106 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV422toRGB565: 76.580880%, 136/136 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV422toRGB565edge: 80.794395%, 110/107 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV420toRGB565: 77.375885%, 141/141 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV420toRGB565edge: 83.289474%, 117/114 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV211toRGB565: 73.051020%, 98/98 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV211toRGB565edge: 77.238530%, 109/109 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV444toRGB565: 73.505490%, 91/91 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV444toRGB565edge: 76.480770%, 104/104 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV400toRGB565: 82.571430%, 68/70 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_converterYUV400toRGB565edge: 84.216866%, 81/83 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_set_converterRGBA8: 93.635290%, 169/170 instructions, conversion-buffer address folding and scheduling.
- TMCJPEGDEC_converterYUV411toRGBA8: 65.871900%, 242/242 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV411toRGBA8edge: 71.544640%, 115/112 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV422toRGBA8: 66.486490%, 148/148 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV422toRGBA8edge: 68.610620%, 116/113 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV420toRGBA8: 69.745094%, 153/153 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV420toRGBA8edge: 74.191666%, 123/120 instructions, three initialized chroma offsets remain; no uninitialized-value shortcut used.
- TMCJPEGDEC_converterYUV211toRGBA8: 69.480770%, 104/104 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV211toRGBA8edge: 73.965220%, 115/115 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV444toRGBA8: 70.082470%, 97/97 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV444toRGBA8edge: 73.118180%, 110/110 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_converterYUV400toRGBA8: 84.276310%, 74/76 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_converterYUV400toRGBA8edge: 85.561800%, 87/89 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_set_converterY8U8V8: 92.540820%, 195/196 instructions, conversion-buffer address folding and scheduling.
- TMCJPEG_814EFEAC: 52.233147%, 338/356 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F043C: 51.355500%, 391/391 instructions, operand/register allocation and scheduling.
- TMCJPEG_814F0A58: 43.534737%, 477/475 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F11C4: 51.355500%, 391/391 instructions, operand/register allocation and scheduling.
- TMCJPEG_814F17E0: 41.890297%, 475/474 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F1F48: 46.809643%, 400/394 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F2570: 47.063830%, 376/376 instructions, operand/register allocation and scheduling.
- TMCJPEG_814F2B50: 52.950780%, 385/386 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F3158: unscored, 275/99 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F32E4: unscored, 288/112 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F34A4: 60.037037%, 147/162 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEG_814F372C: 62.891430%, 160/175 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_IdctBlock_Lumi: 63.077820%, 257/257 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_IdctBlock_Col: 69.085900%, 480/454 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_decode_iquant: 84.641304%, 280/276 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_exif_parse: 98.113205%, 212/212 instructions, operand/register allocation and scheduling.
- TMCJPEGDEC_IFD0_tag_parse: 85.507280%, 480/481 instructions, instruction count and control-flow/code-generation structure.
- TMCJPEGDEC_IFD1_tag_parse: 92.107440%, 242/242 instructions, switch dispatch tree and operand/register allocation.

## Review limits

The planar 444 loops remain much larger than the targets and are unscored by objdiff. No converter unit reached exact. MCU converter behavior was reconstructed from the target assembly but has not been tested on decoded images. The instruction-level differences remain open.

Changed sources: the three texture converters, buffer/idct_block_var.c, b65/iqdec_b65_frv32.c, exif/exif_parse.c. The planar output fields in include/tmc_jpeg.h are guarded by TMC_JPEG_PLANAR_OUTPUT and enabled only by Texture_MCUtoY8U8V8.c.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code None/6184 data None/None functions 0/13 fuzzy 79.3978 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 79.397804
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.63529
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 72.79723
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 80.92453
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 76.58088
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 80.794395
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 77.375885
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 83.289474
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 73.05102
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 77.23853
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 73.50549
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 76.48077
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV400toRGB565 82.57143
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV400toRGB565edge 84.216866
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code None/6184 data None functions 0 fuzzy 9.2756
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code None/6596 data None/None functions 0/13 fuzzy 73.7611 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 73.76107
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.63529
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 65.8719
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 71.54464
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 66.48649
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 68.61062
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 69.745094
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 74.191666
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 69.48077
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 73.96522
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 70.08247
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 73.11818
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV400toRGBA8 84.27631
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV400toRGBA8edge 85.5618
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code None/6596 data None functions 0 fuzzy 76.5585
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code None/15948 data None/None functions 0/13 fuzzy 48.8432 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 48.84324
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.54082
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 52.233147
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 51.3555
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 43.534737
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 51.3555
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 41.890297
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 46.809643
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 47.06383
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2B50 52.95078
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F3158 None
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F32E4 None
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F34A4 60.037037
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F372C 62.89143
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code None/15948 data None functions 0 fuzzy 0.0351
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 66.9142 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 66.91421
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 63.07782
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 69.0859
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 69.6357
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 84.6413 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 84.641304
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 84.641304
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 85.7101
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 92.7036 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 92.70361
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 98.113205
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 85.50728
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 92.10744
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 728/5088 data None functions 2 fuzzy 77.1800
regressions vs baseline: 0
global matched_code_percent: 82.03095 -> 82.05164
global fuzzy_match_percent: 93.26352 -> 93.68542
global complete_code_percent: 57.20994 -> 57.20994
global matched_data_percent: 89.09599 -> 89.09599
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.c: possible pointer+offset into a blob (orchestrator reviews) (+2 net), e.g. work->pConvRowPtrs[6] = (void*)(ob + 0xc4);
review note: libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c: possible pointer+offset into a blob (orchestrator reviews) (+10 net), e.g. work->pConvRowPtrs[5] = (void*)(ob + 0x104);
review note: libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8.c: possible pointer+offset into a blob (orchestrator reviews) (+10 net), e.g. work->pConvRowPtrs[5] = (void*)(ob + 0x104);
GATE PASS
```

## Follow-up: smallest RGB565 converter

Baseline main: f34c0b3a. The requested first target was TMCJPEGDEC_converterYUV400toRGB565, 280 bytes. No other function or translation unit was changed while this target remained non-exact. The other functions retain the earlier logged attempts above.

The retained source reaches 99.21429% objdiff, 70/70 instructions, with nine register-only instruction differences. This is partial progress, not an exact function. Exact functions and exact code bytes do not increase.

| Attempt family | Observed result |
| --- | --- |
| Reuse the luminance value for red; explicit clamp branches | 68/70 instructions. High clamp assignments still preceded their branches. |
| Three-way saturation using negative-value ternaries | 70/70. The clamp branch directions and distances become exact. |
| Associate packing as blue plus the red/green sum | The compiler schedules the blue/red add first. All channel calculations and their registers become exact. |
| Hoist row variables; retain a separate row cursor | 70/70, nine remaining register-only differences. |
| Loop forms: while, body increment, preincrement | The same nine register differences remain. A guarded do loop grows to 77 instructions. |
| Pointer arithmetic versus indexed stores; typed 4x4 texture tiles | Direct pointer/index forms retain the register plateau. Typed tiles grow to 74 instructions. |
| Inline color/index/store helpers | All helpers inline away; the same nine differences remain. No helper is retained. |
| Local declaration scopes and initialization orders | Best remains nine differences. Hoisting additional declarations or metadata into structs worsens allocation. |
| Signed long/int choices, explicit scale/dimension temporaries | Best remains nine differences. Parameter int variants fail type checking and are discarded. |
| Separate packing temporaries and operand orders | Best remains nine differences. Separate red clamping changes the register allocation and scheduling. |

Successful built variants measured: 1152. Compile failures were discarded rather than measured against stale objects. Incorrect experimental self-sum of green was discarded. All experiments built only the RGB565 object.

Remaining instruction differences for the retained converter:

```text
9 srwi: tile stride r9 instead of r12
16 rlwinm: row offset r12 instead of r26
17 mullw: reads tile stride r9 instead of r12
18 mr: column r3 instead of r9
19 add: row output r12 instead of r3, offset r12 instead of r26
51 clrlwi: column r3 instead of r9
52 srawi: column r3 instead of r9
57 addi: column r3 instead of r9
61 sthx: row output r12 instead of r3
```

Follow-up data audit after building the retained source. All allocated non-code sections are absent in both target and source objects. There are no tables, strings, vtables, or data ordering changes to make.

```text
texturecvtr/Texture_MCUtoRGB565 allocated data sections target/source: [[], []]
texturecvtr/Texture_MCUtoRGBA8 allocated data sections target/source: [[], []]
texturecvtr/Texture_MCUtoY8U8V8 allocated data sections target/source: [[], []]
buffer/idct_block_var allocated data sections target/source: [[], []]
b65/iqdec_b65_frv32 allocated data sections target/source: [[], []]
exif/exif_parse allocated data sections target/source: [[], []]
```

Follow-up full gate, all six requested units, regressions 0. The retained converter improves from 82.57143% to 99.21429%; instruction-exact totals remain 3/48 and matched code remains 1348/37764 bytes. This gate pass does not satisfy the new-exact-function completion condition.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code None/6184 data None/None functions 0/13 fuzzy 80.1514 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 80.15136
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.63529
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 72.79723
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 80.92453
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 76.58088
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565edge 80.794395
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 77.375885
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 83.289474
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565 73.05102
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV211toRGB565edge 77.23853
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565 73.50549
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV444toRGB565edge 76.48077
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV400toRGB565 99.21429
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV400toRGB565edge 84.216866
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code None/6184 data None functions 0 fuzzy 79.3978
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code None/6596 data None/None functions 0/13 fuzzy 73.7611 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 73.76107
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.63529
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 65.8719
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 71.54464
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 66.48649
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 68.61062
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 69.745094
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 74.191666
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 69.48077
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 73.96522
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 70.08247
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 73.11818
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV400toRGBA8 84.27631
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV400toRGBA8edge 85.5618
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code None/6596 data None functions 0 fuzzy 73.7611
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code None/15948 data None/None functions 0/13 fuzzy 48.8432 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 0/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 48.84324
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.54082
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814EFEAC 52.233147
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F043C 51.3555
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F0A58 43.534737
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F11C4 51.3555
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F17E0 41.890297
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F1F48 46.809643
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2570 47.06383
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F2B50 52.95078
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F3158 None
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F32E4 None
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F34A4 60.037037
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEG_814F372C 62.89143
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code None/15948 data None functions 0 fuzzy 48.8432
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 66.9142 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] instruction-exact functions: 0/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   section .text size 2844 match 66.91421
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Lumi 63.07782
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var]   below 100: TMCJPEGDEC_IdctBlock_Col 69.0859
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] baseline: code None/2844 data None functions 0 fuzzy 66.9142
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 84.6413 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 84.641304
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 84.641304
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 84.6413
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 92.7036 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 92.70361
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 98.113205
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 85.50728
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 92.10744
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 92.7036
regressions vs baseline: 0
global matched_code_percent: 82.26412 -> 82.26412
global fuzzy_match_percent: 94.05748 -> 94.05904
global complete_code_percent: 57.93924 -> 57.93924
global matched_data_percent: 89.35397 -> 89.35397
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## IFD1 switch lowering — decoded model (verified)
Orig tree: root cmpwi 0x132; left {11a};{111};{103};{128};{11c-edge};{12d}; right cmpw 0x8769;{202};{201};{213};{9101};{9000};{a004-edge}.
- Node count = case labels; adjacent shared-fall-through labels merge into ONE counted node
  but emit as a range-check (upper-edge `cmpwi <last+1>; bgelr`).
- `case X: ;` (empty body, == else arm) counts as a node but emits NOTHING (folded into
  parent's range branch) — orig's {111} emits `beqlr;bgelr` covering the folded {112}.
- {a000,a001,a002,a003} shared empty labels = one range-node -> emits `cmpw 0xa004; bgelr`
  (orig's edge form). GNU `case a...b:` ranges compile but count differently — don't use.
- Split pivot = index floor(n/2) over sorted node list (n includes merged ranges as 1).
- Orig set: 14 real labels {103,111,11a,11b,128,12d,132,201,202,213,8769,9000,9101,a003}
  + folded {112} + range {a000..a003} -> 12 nodes + else -> root {132}.
- Residual (~6 insns): dead-blr cluster count, {103} leaf `bltlr` vs `blr`,
  body regalloc (r6 vs r8 homes in readU32-assemble bounds-checks).
