# odh and AOSS matching attempts

Partial progress only. Full gate passes; instruction-exact counts and matched code bytes did not increase. No configure.py linking changes.

## src/system/odh

| Function | Target bytes | Before % | After % | Remaining difference |
|---|---:|---:|---:|---|
| cdj_c_setQuantizationTable | 280 | 93.97143 | 94.14286 | 70/70 instructions; remaining register choices. |
| cdj_c_colorConv | 308 | 97.40260 | 97.40260 | 77/77 instructions; remaining register choices. |
| LineConv11 | 584 | 80.74657 | 80.74657 | 146/146 instructions; float operation scheduling/register choices; constant-pool regression candidate rejected. |
| fdct_fast | 676 | 78.30769 | 89.78107 | 169/169 instructions; pair-load and butterfly scheduling. |
| huffmanCoder | 652 | 91.96319 | 96.50307 | 163/163 instructions; initial cursor addition scheduling and register choices. |
| cdj_d_decompressLoop | 3596 | 97.68409 | 97.45273 | 899/899 instructions; remaining register choices. |
| cdj_d_setDequantizationTable | 204 | 94.60784 | 94.84314 | 51/51 instructions; inner-loop increment scheduling. |
| LineDeconv21 | 560 | 92.61429 | 92.65000 | 145/140 instructions; larger frame and spilled green-table pointer. |
| LineDeconv12 | 584 | 83.47260 | 83.47260 | 146/146 instructions; component/output scheduling. |
| LineDeconv22 | 976 | 96.43443 | 96.43443 | 244/244 instructions; first pixel offset/blue shift scheduling. |
| huffmanDecoder | 1224 | 91.04902 | 94.93464 | 306/306 instructions; remaining register choices. |
| idct_fast | 948 | 70.49789 | 70.49789 | 236/237 instructions; frame/register pressure and butterfly scheduling. |

### Attempts

#### cdj_c_setQuantizationTable

- explicit output table index: 94.14286%; instructions 70/70; 0 differences after register-number normalization.
- increment input row first: 93.97143%; instructions 70/70; 2 differences after register-number normalization.
- unsigned inner scale index: 93.97143%; instructions 70/70; 2 differences after register-number normalization.
- separate output pass from scale pass: 94.14286%; instructions 70/70; 0 differences after register-number normalization.
- walk standard and scaled quantization pointers: 89.90000%; instructions 68/70; 54 differences after register-number normalization.
- use counted scale pass loop: 94.14286%; instructions 70/70; 0 differences after register-number normalization.

#### cdj_c_colorConv

- signed row loop: 97.40260%; instructions 77/77; 0 differences after register-number normalization.
- add source before row offset: 97.40260%; instructions 77/77; 0 differences after register-number normalization.
- signed padded width: 97.40260%; instructions 77/77; 0 differences after register-number normalization.
- name padded plane size: 97.40260%; instructions 77/77; 0 differences after register-number normalization.
- promote height before conversion loops: 97.40260%; instructions 77/77; 0 differences after register-number normalization.
- read conversion height after plane setup: 97.40260%; instructions 77/77; 0 differences after register-number normalization.

#### LineConv11

- read conversion constants at use: 80.88356%; instructions 146/146; 40 differences after register-number normalization.
- reuse output channel values across clamp: 80.47260%; instructions 146/146; 40 differences after register-number normalization.
- name input chroma planes: 80.47260%; instructions 146/146; 40 differences after register-number normalization.

#### fdct_fast

- canonical row butterflies: 77.27811%; instructions 169/169; 41 differences after register-number normalization.
- index quantization columns: 81.72189%; instructions 167/169; 38 differences after register-number normalization.
- canonical column butterflies: 85.30769%; instructions 167/169; 29 differences after register-number normalization.
- separate quantization column bases: 88.86391%; instructions 169/169; 14 differences after register-number normalization.
- differences before pair sums: 88.86391%; instructions 169/169; 14 differences after register-number normalization.
- compute odd sums before even outputs: 89.78107%; instructions 169/169; 15 differences after register-number normalization.

#### huffmanCoder

- index component predictors: 96.50307%; instructions 163/163; 3 differences after register-number normalization.
- single coefficient cursor through blocks: 96.25767%; instructions 163/163; 3 differences after register-number normalization.
- use typed initial coefficient cursor: 96.25767%; instructions 163/163; 3 differences after register-number normalization.
- signed huffman code words: 96.25767%; instructions 163/163; 3 differences after register-number normalization.

#### cdj_d_decompressLoop

- unsigned strides: 97.32814%; instructions 899/899; 8 differences after register-number normalization.
- promote block width: 97.68409%; instructions 899/899; 2 differences after register-number normalization.
- factor row bounds: 97.45273%; instructions 899/899; 0 differences after register-number normalization.

#### cdj_d_setDequantizationTable

- explicit dequantization table index: 94.84314%; instructions 51/51; 3 differences after register-number normalization.
- clamp unsigned coefficient directly: 94.84314%; instructions 51/51; 3 differences after register-number normalization.
- separate scale and output cursors: 81.64706%; instructions 51/51; 21 differences after register-number normalization.

#### LineDeconv21

- separate packed rgb565 value: 92.61429%; instructions 145/140; 108 differences after register-number normalization.
- indexed first rgb565 store: 92.65000%; instructions 145/140; 108 differences after register-number normalization.
- signed pixel loop index: 92.65000%; instructions 145/140; 108 differences after register-number normalization.
- load cr green before cb green: 92.61429%; instructions 145/140; 108 differences after register-number normalization.

#### LineDeconv12

- load cr green first: 83.47260%; instructions 146/146; 99 differences after register-number normalization.
- index first packed store: 83.47260%; instructions 146/146; 99 differences after register-number normalization.
- separate tiled offset sum: 83.47260%; instructions 146/146; 99 differences after register-number normalization.

#### LineDeconv22

- sum tiled offsets before destination: 96.43443%; instructions 244/244; 2 differences after register-number normalization.
- associate tiled offset: 96.43443%; instructions 244/244; 2 differences after register-number normalization.
- name rgb565 packed channels: 94.07787%; instructions 244/244; 7 differences after register-number normalization.
- separate tiled column: 96.31148%; instructions 244/244; 3 differences after register-number normalization.

#### huffmanDecoder

- index predictors and reload destination: 93.97385%; instructions 306/306; 11 differences after register-number normalization.
- name first right leaf index: 94.74183%; instructions 306/306; 8 differences after register-number normalization.
- advance bytes while remaining bits exceed byte: 94.93464%; instructions 306/306; 0 differences after register-number normalization.

#### idct_fast

- load even pair before odd pair: 70.49789%; instructions 236/237; 130 differences after register-number normalization.
- retranslate column products and butterflies: 66.42194%; instructions 236/237; 129 differences after register-number normalization.
- compute even rotation before odd products: 65.50211%; instructions 236/237; 135 differences after register-number normalization.
- signed transform workspace and sums: 70.49789%; instructions 236/237; 130 differences after register-number normalization.

## src/scene/setting/AOSS

| Function | Target bytes | Before % | After % | Remaining difference |
|---|---:|---:|---:|---|
| AOSS_Init_old | 6336 | 73.34911 | 73.34911 | 1494/1584 instructions; stack frame, poll records and omitted branch path; target r14 initialization unresolved. |
| AOSS_81400830 | 1284 | 93.84112 | 97.04050 | 321/321 instructions; register choices and two ctxdiff CR1 branch operand decoding discrepancies. |
| AOSS_81400E0C | 760 | 100.00000 | 100.00000 | 190/190 instructions; objdiff 100; ctxdiff CR1 branch decoding uses wrong operand and depends on preceding function sizes. |
| AOSS_814013AC | 456 | 98.77193 | 98.77193 | 114/114 instructions; remaining cursor/length register choices. |
| AOSS_81401778 | 1092 | 79.16483 | 80.16849 | 276/273 instructions; global base lifetime, initial checksum folding and encryption loop scheduling. |
| AOSS_81401E80 | 588 | 98.60545 | 98.60545 | 147/147 instructions; XOR result/base register choices and two ctxdiff CR1 branch decoding discrepancies. |

### Attempts

#### AOSS_Init_old

- retranslate poll descriptors and align request records: 69.44571%; instructions 1551/1584; 1412 differences after register-number normalization.
- retranslate signed wait arrays and timeout pair: 64.67929%; instructions 1603/1584; 1471 differences after register-number normalization.
- align bound socket address: 64.68056%; instructions 1603/1584; 1470 differences after register-number normalization.
- two complete descriptors and copied gateway: 72.99811%; instructions 1498/1584; 1438 differences after register-number normalization.
- align complete socket address: 69.45644%; instructions 1553/1584; 1403 differences after register-number normalization.

#### AOSS_81400830

- retain encrypted payload pointer: 93.84112%; instructions 326/321; 277 differences after register-number normalization.
- name rc4 state sum before swap: 93.84112%; instructions 326/321; 277 differences after register-number normalization.
- encrypted byte first xor operand: 93.84112%; instructions 326/321; 277 differences after register-number normalization.
- retain payload through final memcpy: 93.98131%; instructions 327/321; 204 differences after register-number normalization.
- hold rc4 state pointer during each swap: 96.28661%; instructions 321/321; 6 differences after register-number normalization.
- initialize crc before table call: 97.04050%; instructions 321/321; 2 differences after register-number normalization.

#### AOSS_81400E0C

Already objdiff-exact; no source change. Apparent ctxdiff disagreement is described below.


#### AOSS_814013AC

- reuse record cursor after outer option: 96.18421%; instructions 114/114; 2 differences after register-number normalization.
- delay remaining length initialization: 96.18421%; instructions 114/114; 2 differences after register-number normalization.
- initialize option flags after length guard: 94.47369%; instructions 114/114; 7 differences after register-number normalization.
- preserve state argument before copying response length: 94.38596%; instructions 114/114; 7 differences after register-number normalization.
- compute network record before config fields: 93.94737%; instructions 114/114; 7 differences after register-number normalization.
- reuse response length argument for inner record: 98.20175%; instructions 114/114; 0 differences after register-number normalization.
- reuse response argument and record cursor: 97.58772%; instructions 114/114; 0 differences after register-number normalization.
- compute network destination before config pointers: 95.48245%; instructions 114/114; 2 differences after register-number normalization.

#### AOSS_81401778

- initialize hello crc before table call: 79.16483%; instructions 275/273; 230 differences after register-number normalization.
- retain hello payload during header calls: 80.16849%; instructions 276/273; 245 differences after register-number normalization.
- share checksum accumulator and delay payload setup: 79.82051%; instructions 276/273; 245 differences after register-number normalization.
- compute hello checksum in eight byte loop: 79.82051%; instructions 276/273; 245 differences after register-number normalization.
- retain key schedule bytes within encryption round: 79.21612%; instructions 272/273; 184 differences after register-number normalization.
- use encrypted output cursor: 74.95971%; instructions 273/273; 232 differences after register-number normalization.

#### AOSS_81401E80

- xor directly into packet: 98.23129%; instructions 147/147; 2 differences after register-number normalization.
- read mask before packet: 97.99320%; instructions 147/147; 2 differences after register-number normalization.
- retain mask byte for xor: 97.99320%; instructions 147/147; 2 differences after register-number normalization.

## Uncertainties

- The gate uses odiff.dis, which interprets the first operand of conditional branches as an immediate. For CR1 branches that operand is a condition register, so its relative-target calculation changes with preceding function sizes. AOSS_81400E0C is already 100% in objdiff but fails that instruction-exact comparison. Tools were not changed.
- AOSS_Init_old target assembly reads r14 at 0x813FEC9C without a visible prior initialization in that function. Its source origin is unresolved. No uninitialized local was introduced.
- Register-number normalization is an iteration aid, not acceptance; it can hide register data-flow differences. Exact counts below come from the unchanged gate.

## Full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/odh] pool: IDENTICAL
[src/system/odh] objdiff: code 4092/14684 data 6360/6360 functions 16/28 fuzzy 94.2454 linked code 0
[src/system/odh] instruction-exact functions: 16/28
[src/system/odh]   section .data size 464 match 100.0
[src/system/odh]   section .rodata size 5856 match 100.0
[src/system/odh]   section .sdata2 size 40 match 100.0
[src/system/odh]   section .text size 14684 match 94.24544
[src/system/odh]   below 100: cdj_c_setQuantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl 94.14286
[src/system/odh]   below 100: cdj_c_colorConv__9CArGBAOdhFP16SArCDJ_OdhMasterPUci 97.402596
[src/system/odh]   below 100: LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli 80.746574
[src/system/odh]   below 100: fdct_fast__9CArGBAOdhFPUlPUcUlPUl 89.78107
[src/system/odh]   below 100: huffmanCoder__9CArGBAOdhFPUsP21SArCDJ_HuffmanRequest 96.50307
[src/system/odh]   below 100: cdj_d_decompressLoop__9CArGBAOdhFP16SArCDJ_OdhMasterii 97.45273
[src/system/odh]   below 100: cdj_d_setDequantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl 94.84314
[src/system/odh]   below 100: LineDeconv21__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli 92.65
[src/system/odh]   below 100: LineDeconv12__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli 83.4726
[src/system/odh]   below 100: LineDeconv22__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli 96.434425
[src/system/odh]   below 100: huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl 94.93464
[src/system/odh]   below 100: idct_fast__9CArGBAOdhFPCUcPUlPUlPUcUl 70.49789
[src/system/odh] baseline: code 4092/14684 data 6360 functions 16 fuzzy 93.2405
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3896/3928 functions 16/21 fuzzy 87.9140 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 87.91403
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 73.34911
[src/scene/setting/AOSS]   below 100: AOSS_81400830 97.0405
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 98.77193
[src/scene/setting/AOSS]   below 100: AOSS_81401778 80.168495
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3896 functions 16 fuzzy 87.5926
regressions vs baseline: 0
global matched_code_percent: 85.90652 -> 85.90652
global fuzzy_match_percent: 98.69413 -> 98.70080
global complete_code_percent: 59.99415 -> 59.99415
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Additional register attempts

- AOSS_81401E80, promote xor byte to word: 98.60545%; 147/147 instructions; 2 normalized differences. Rejected; committed source retained.
- AOSS_81401E80, promote xor mask to word: 98.57143%; 147/147 instructions; 2 normalized differences. Rejected; committed source retained.
- AOSS_81401E80, keep both xor operands as words: 98.57143%; 147/147 instructions; 2 normalized differences. Rejected; committed source retained.
- AOSS_814013AC, advance response argument as option cursor: 95.08772%; 114/114 instructions; 7 normalized differences. Rejected; committed source retained.
- AOSS_814013AC, reuse both response cursor and length arguments: 95.96491%; 114/114 instructions; 5 normalized differences. Rejected; committed source retained.
- AOSS_814013AC, name protocol state index before cursor length: 95.96491%; 114/114 instructions; 5 normalized differences. Rejected; committed source retained.
