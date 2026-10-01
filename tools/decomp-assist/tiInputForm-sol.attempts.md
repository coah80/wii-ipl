# tiInputForm matching attempts

Baseline objdiff 209/221; raw instruction check 207/221; code 30712/50656; data 908/3772; six asm bodies.
Each discarded trial restores the source; only exact candidates are retained.
Shared header helper trial was restored completely. No shared header changes remain.

onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv | command-mode-declaration-order | structural 0 positional 7 insns 2053/2053 objdiff 99.98295 | POOL IDENTICAL up to 20 (mine=20 base=20) | d75cc54817fe
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-boolean-guard | structural 4 positional 172 insns 263/264 objdiff 99.583336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 9abe3d595151
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-boolean-guard | structural 4 positional 183 insns 274/275 objdiff 99.6 | POOL IDENTICAL up to 20 (mine=20 base=20) | 7a3c965a3965
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-multiply-operands | structural 0 positional 5 insns 473/473 objdiff 99.915436 | POOL IDENTICAL up to 20 (mine=20 base=20) | 6e582ddce1a8
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-space-width-locals | structural 0 positional 4 insns 473/473 objdiff 99.93658 | POOL IDENTICAL up to 20 (mine=20 base=20) | 978f300afffd
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-offset-local-first | structural 0 positional 5 insns 473/473 objdiff 99.915436 | POOL IDENTICAL up to 20 (mine=20 base=20) | d0d4a84c46ad
onPressUp__Q39textinput9inputform4BaseFv | pressUp-switch-false | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | 6d33e7106da1
onPressDown__Q39textinput9inputform4BaseFv | pressDown-switch-false | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | 7b46b351d366
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-switch-false | structural 4 positional 173 insns 265/264 objdiff 99.56439 | POOL IDENTICAL up to 20 (mine=20 base=20) | 92b5c1ec5c4e
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-switch-false | structural 4 positional 184 insns 276/275 objdiff 99.58182 | POOL IDENTICAL up to 20 (mine=20 base=20) | c89d25fed981
onPressDownHWKB__Q39textinput9inputform4BaseFv | hwDown-switch-and-zi-branch | structural 15 positional 168 insns 268/270 objdiff 98.333336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 898a595ff3e4
onPressDownHWKB__Q39textinput9inputform4BaseFv | hwDown-scoped-selection | structural 15 positional 168 insns 268/270 objdiff 98.333336 | POOL IDENTICAL up to 20 (mine=20 base=20) | a2ba02ff4f55
onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv | command-mode-unfix-pointer | structural 0 positional 7 insns 2053/2053 objdiff 99.98295 | POOL IDENTICAL up to 20 (mine=20 base=20) | a6b28507b819
onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv | command-mode-signed-values | structural 0 positional 0 insns 2053/2053 objdiff 100.0 | POOL IDENTICAL up to 20 (mine=20 base=20) | 984336fd7638
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-separate-pane-name | structural 12 positional 22 insns 237/237 objdiff 96.44726 | POOL IDENTICAL up to 20 (mine=20 base=20) | 0416736fc39f
onPressUp__Q39textinput9inputform4BaseFv | pressUp-true-switch | structural 2 positional 2 insns 246/246 objdiff 99.97561 | POOL IDENTICAL up to 20 (mine=20 base=20) | 9c9dccc15fc8
onPressUp__Q39textinput9inputform4BaseFv | pressUp-positive-nested | structural 9 positional 53 insns 245/246 objdiff 99.55285 | POOL IDENTICAL up to 20 (mine=20 base=20) | a07574e011c3
onPressDown__Q39textinput9inputform4BaseFv | pressDown-true-switch | structural 2 positional 2 insns 246/246 objdiff 99.97561 | POOL IDENTICAL up to 20 (mine=20 base=20) | 0765e6acf20b
onPressDown__Q39textinput9inputform4BaseFv | pressDown-positive-nested | structural 9 positional 53 insns 245/246 objdiff 99.55285 | POOL IDENTICAL up to 20 (mine=20 base=20) | 692b741821d3
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-integer-zero-case | structural 7 positional 171 insns 268/264 objdiff 98.46212 | POOL IDENTICAL up to 20 (mine=20 base=20) | a8c7bbc6118c
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-positive-nested | structural 5 positional 41 insns 264/264 objdiff 99.204544 | POOL IDENTICAL up to 20 (mine=20 base=20) | d0ceb5604173
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-integer-zero-case | structural 7 positional 182 insns 279/275 objdiff 98.523636 | POOL IDENTICAL up to 20 (mine=20 base=20) | 3c64fdb5df5b
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-positive-nested | INVALID HARNESS: prior failed edit was not restored; restored all source from accepted commit; excluded from attempts
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-branch-name | INVALID HARNESS: prior failed edit was not restored; restored all source from accepted commit; excluded from attempts
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-inverted-name-branch | INVALID HARNESS: prior failed edit was not restored; restored all source from accepted commit; excluded from attempts
onPressUp__Q39textinput9inputform4BaseFv | pressUp-switch-body | structural 9 positional 53 insns 245/246 objdiff 99.55285 | POOL IDENTICAL up to 20 (mine=20 base=20) | 7354ddbfd6e3
onPressDown__Q39textinput9inputform4BaseFv | pressDown-switch-body | structural 9 positional 53 insns 245/246 objdiff 99.55285 | POOL IDENTICAL up to 20 (mine=20 base=20) | dcc9b7d4b55f
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-switch-body | structural 4 positional 173 insns 265/264 objdiff 99.56439 | POOL IDENTICAL up to 20 (mine=20 base=20) | 932a87b84b7e
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-switch-body | build failed; restored
calcCursorPos__Q39textinput9inputform4BaseFff | calc-cursor-scale-components | structural 80 positional 235 insns 317/326 objdiff 86.54601 | POOL IDENTICAL up to 20 (mine=20 base=20) | 9ba6717476d8
calcCursorPos__Q39textinput9inputform4BaseFff | calc-cursor-height-temporaries | structural 34 positional 45 insns 326/326 objdiff 91.622696 | POOL IDENTICAL up to 20 (mine=20 base=20) | e02d1e3b0f98
calcCursorPos__Q39textinput9inputform4BaseFff | calc-cursor-width-first-declarations | structural 42 positional 65 insns 326/326 objdiff 91.269936 | POOL IDENTICAL up to 20 (mine=20 base=20) | a10cbdfc0919
onPressUp__Q39textinput9inputform4BaseFv | pressUp-negative-switch | structural 12 positional 101 insns 247/246 objdiff 97.439026 | POOL IDENTICAL up to 20 (mine=20 base=20) | 3b7efb6bad83
onPressDown__Q39textinput9inputform4BaseFv | pressDown-negative-switch | structural 12 positional 101 insns 247/246 objdiff 97.439026 | POOL IDENTICAL up to 20 (mine=20 base=20) | c21d9f059975
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-negative-switch | structural 7 positional 198 insns 265/264 objdiff 97.5 | POOL IDENTICAL up to 20 (mine=20 base=20) | 179355ecfda8
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-negative-switch | structural 5 positional 185 insns 276/275 objdiff 99.4 | POOL IDENTICAL up to 20 (mine=20 base=20) | 3c81716eaf9b
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-split-offset | structural 10 positional 17 insns 473/473 objdiff 97.97463 | POOL IDENTICAL up to 20 (mine=20 base=20) | c16585407d68
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-double-scale-expression | structural 0 positional 4 insns 473/473 objdiff 99.93658 | POOL IDENTICAL up to 20 (mine=20 base=20) | 651274cad027
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-reuse-layout-data | structural 23 positional 190 insns 252/237 objdiff 91.818565 | POOL IDENTICAL up to 20 (mine=20 base=20) | d0baa013fa7c
onPressUp__Q39textinput9inputform4BaseFv | pressUp-default-first | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | 2fc2fb852a90
onPressDown__Q39textinput9inputform4BaseFv | pressDown-default-first | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | 8319afbfcc60
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-default-first | structural 4 positional 173 insns 265/264 objdiff 99.56439 | POOL IDENTICAL up to 20 (mine=20 base=20) | 05d9bc50ee69
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-default-first | structural 4 positional 184 insns 276/275 objdiff 99.58182 | POOL IDENTICAL up to 20 (mine=20 base=20) | 1d7a33f1c796
onPressDownHWKB__Q39textinput9inputform4BaseFv | hwDown-default-first | structural 15 positional 168 insns 268/270 objdiff 98.333336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 2689db88dd9d
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layout-create-root-pane-search | structural 15 positional 178 insns 354/356 objdiff 95.80618 | POOL IDENTICAL up to 20 (mine=20 base=20) | 69ead8b11801
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layout-create-animation-file-reload | structural 11 positional 225 insns 354/356 objdiff 95.97472 | POOL IDENTICAL up to 20 (mine=20 base=20) | 75a40753bb59
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layout-create-loop-declarations | structural 20 positional 229 insns 352/356 objdiff 95.02809 | POOL IDENTICAL up to 20 (mine=20 base=20) | b4df3e032fef
isOverRowLimit__Q39textinput9inputform4BaseFUlPCw | row-limit-retain-scale-vector | structural 1 positional 54 insns 238/238 objdiff 98.61345 | POOL IDENTICAL up to 20 (mine=20 base=20) | 6e323fc2e8cb
isOverRowLimit__Q39textinput9inputform4BaseFUlPCw | row-limit-leading-declarations | structural 17 positional 136 insns 235/238 objdiff 97.35294 | POOL IDENTICAL up to 20 (mine=20 base=20) | a006fa65fa61
isOverRowLimit__Q39textinput9inputform4BaseFUlPCw | row-limit-inner-width-recalculation | structural 8 positional 167 insns 239/238 objdiff 98.17227 | POOL IDENTICAL up to 20 (mine=20 base=20) | 35a561a80470
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-loop | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-row-reference | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-short-index | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-locals | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 0eb7dc26059f
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-declare-index-first | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 62cf6b694b1a
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-reuse-rows | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | a82cc97841ef
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-declsearch | 38 declaration permutations; best structural 0 positional 19; restored
onPressLeft__Q39textinput9inputform4BaseFv | asm-pressLeft-cpp-early-return | structural 4 positional 66 insns 153/154 objdiff 99.28571 | POOL IDENTICAL up to 20 (mine=20 base=20) | 607eb261877c
onPressLeft__Q39textinput9inputform4BaseFv | asm-pressLeft-cpp-switch-true | structural 2 positional 2 insns 154/154 objdiff 99.96104 | POOL IDENTICAL up to 20 (mine=20 base=20) | 976a6153f21d
onPressLeft__Q39textinput9inputform4BaseFv | asm-pressLeft-cpp-switch-false | structural 4 positional 67 insns 155/154 objdiff 99.25325 | POOL IDENTICAL up to 20 (mine=20 base=20) | dfe9e3c3d383
onPressRight__Q39textinput9inputform4BaseFv | asm-pressRight-cpp-early-return | structural 34 positional 153 insns 194/185 objdiff 91.33514 | POOL IDENTICAL up to 20 (mine=20 base=20) | f04543734c7e
onPressRight__Q39textinput9inputform4BaseFv | asm-pressRight-cpp-switch-true | structural 34 positional 190 insns 195/185 objdiff 91.8973 | POOL IDENTICAL up to 20 (mine=20 base=20) | eb835b78de0d
onPressRight__Q39textinput9inputform4BaseFv | asm-pressRight-cpp-switch-false | structural 35 positional 193 insns 196/185 objdiff 91.308105 | POOL IDENTICAL up to 20 (mine=20 base=20) | 1186ce86d3d8
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-color-members | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-integral-color-conversions | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-sustain-color-order | INVALID HARNESS: declaration matched instead of definition; restored; excluded from attempts
onPressUp__Q39textinput9inputform4BaseFv | pressUp-zero-case-only | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | 180beccdcd88
onPressDown__Q39textinput9inputform4BaseFv | pressDown-zero-case-only | structural 9 positional 54 insns 247/246 objdiff 99.532524 | POOL IDENTICAL up to 20 (mine=20 base=20) | a5de099a7701
onPressLeftHWKB__Q39textinput9inputform4BaseFv | hwLeft-zero-case-only | structural 4 positional 173 insns 265/264 objdiff 99.56439 | POOL IDENTICAL up to 20 (mine=20 base=20) | f8039bc8c5ac
onPressRightHWKB__Q39textinput9inputform4BaseFv | hwRight-zero-case-only | structural 4 positional 184 insns 276/275 objdiff 99.58182 | POOL IDENTICAL up to 20 (mine=20 base=20) | 9c77e36da31b
onPressDownHWKB__Q39textinput9inputform4BaseFv | hwDown-zero-case-only | structural 15 positional 168 insns 268/270 objdiff 98.333336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 38ead171e991
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-loop | structural 20 positional 31 insns 47/39 objdiff 58.589745 | POOL IDENTICAL up to 20 (mine=20 base=20) | 37f330b49d1e
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-row-reference | structural 20 positional 31 insns 47/39 objdiff 58.589745 | POOL IDENTICAL up to 20 (mine=20 base=20) | a36c8df331ab
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-short-index | structural 20 positional 31 insns 47/39 objdiff 58.589745 | POOL IDENTICAL up to 20 (mine=20 base=20) | b8d509644b6d
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-locals | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 0eb7dc26059f
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-declare-index-first | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 62cf6b694b1a
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | base-create-cpp-reuse-rows | structural 0 positional 26 insns 72/72 objdiff 97.708336 | POOL IDENTICAL up to 20 (mine=20 base=20) | a82cc97841ef
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-color-members | structural 6 positional 13 insns 165/165 objdiff 96.15151 | POOL IDENTICAL up to 20 (mine=20 base=20) | 822d6248d14c
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-integral-color-conversions | structural 6 positional 13 insns 165/165 objdiff 96.15151 | POOL IDENTICAL up to 20 (mine=20 base=20) | 1f321e3e07d7
calc__Q39textinput9inputform4BaseFv | asm-calc-cpp-sustain-color-order | structural 10 positional 17 insns 165/165 objdiff 96.12727 | POOL IDENTICAL up to 20 (mine=20 base=20) | 480cbca6c766
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-rect | build failed; actual pane field at 0xCD uses GetAlpha; restored; retried below
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-scale-local | build failed; actual pane field at 0xCD uses GetAlpha; restored; retried below
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-rect-construct | build failed; actual pane field at 0xCD uses GetAlpha; restored; retried below
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-rect | structural 12 positional 12 insns 114/114 objdiff 99.89474 | POOL IDENTICAL up to 20 (mine=20 base=20) | 0f32a2388795
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-scale-local | structural 14 positional 14 insns 114/114 objdiff 98.14035 | POOL IDENTICAL up to 20 (mine=20 base=20) | 9e0c10784f78
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-cpp-rect-construct | structural 12 positional 12 insns 114/114 objdiff 99.89474 | POOL IDENTICAL up to 20 (mine=20 base=20) | a688e8db5e54
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-position-first | structural 16 positional 14 insns 114/114 objdiff 96.833336 | POOL IDENTICAL up to 20 (mine=20 base=20) | 209adef28e0d
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-vectors-leading | structural 21 positional 66 insns 116/114 objdiff 90.54386 | POOL IDENTICAL up to 20 (mine=20 base=20) | 53d4dc4b9bf8
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-scale-assignment | structural 17 positional 66 insns 116/114 objdiff 93.60526 | POOL IDENTICAL up to 20 (mine=20 base=20) | fdbe90516347
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-head-pointers | structural 7 positional 24 insns 38/39 objdiff 81.02564 | POOL IDENTICAL up to 20 (mine=20 base=20) | d784982b5ddb
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-head-declarations | structural 7 positional 24 insns 38/39 objdiff 81.02564 | POOL IDENTICAL up to 20 (mine=20 base=20) | df89867b9a97
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-head-index | structural 15 positional 27 insns 41/39 objdiff 73.46154 | POOL IDENTICAL up to 20 (mine=20 base=20) | f242af921e84
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-name-inline-boundary | structural 12 positional 22 insns 237/237 objdiff 96.44726 | FIRST DIVERGENCE at index 18    16 mine=0x418    base=0x418          M 'N_separateBarAll'       B 'N_separateBarAll'    17 mine=0x42c    base=0x42c          M 'T_title_text'       B 'T_title_text' *  18 mine=0xbb4    base=0xa5c          M 'T_2l_TextBox'       B 'OutOfLength\n' *  19 mine=0xbc4    base=0xa6c          M 'OutOfLength\n'       B 'Error#004\nAn error has occurred.\nThe system files are corrupted.'  mine has 21 strings, base has 20 | 310e507c1ba6
draw__Q39textinput9inputform12LayoutByNW4RFv | asm-draw-base-boundary | structural 0 positional 0 insns 114/114 objdiff 100.0 | POOL IDENTICAL up to 20 (mine=20 base=20) | 809714fa4eb8
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-head-before-last | structural 6 positional 24 insns 38/39 objdiff 84.48718 | POOL IDENTICAL up to 20 (mine=20 base=20) | 275024d1ac01
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-assignment-head | structural 7 positional 24 insns 38/39 objdiff 81.02564 | POOL IDENTICAL up to 20 (mine=20 base=20) | ff64ac7e4d9f
init__Q49textinput9inputform4Base14RowInfoManagerFv | rowinfo-cpp-head-first-direct-back | structural 9 positional 12 insns 39/39 objdiff 82.5641 | POOL IDENTICAL up to 20 (mine=20 base=20) | dc54453e7984
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-const-widths-scale-local | structural 0 positional 7 insns 473/473 objdiff 99.87315 | POOL IDENTICAL up to 20 (mine=20 base=20) | 204be0b3619d
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-scale-offset-reuse | structural 0 positional 7 insns 473/473 objdiff 99.87315 | POOL IDENTICAL up to 20 (mine=20 base=20) | 53556a72c25d
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-vector-scale-local | structural 78 positional 248 insns 475/473 objdiff 98.67865 | POOL IDENTICAL up to 20 (mine=20 base=20) | 65003abb2099

## Final open-function audit

onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | 8 distinct built source variants | all non-exact trials restored
calcCursorPos__Q39textinput9inputform4BaseFff | 3 distinct built source variants | all non-exact trials restored
onPressUp__Q39textinput9inputform4BaseFv | 7 distinct built source variants | all non-exact trials restored
onPressDown__Q39textinput9inputform4BaseFv | 7 distinct built source variants | all non-exact trials restored
onPressDownHWKB__Q39textinput9inputform4BaseFv | 4 distinct built source variants | all non-exact trials restored
onPressLeftHWKB__Q39textinput9inputform4BaseFv | 8 distinct built source variants | all non-exact trials restored
onPressRightHWKB__Q39textinput9inputform4BaseFv | 6 distinct built source variants | all non-exact trials restored
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | 3 distinct built source variants | all non-exact trials restored
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | 3 distinct built source variants | all non-exact trials restored
isOverRowLimit__Q39textinput9inputform4BaseFUlPCw | 3 distinct built source variants | all non-exact trials restored
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | 3 distinct built source variants | all non-exact trials restored
onPressLeft__Q39textinput9inputform4BaseFv | 3 distinct built source variants | all non-exact trials restored
onPressRight__Q39textinput9inputform4BaseFv | 3 distinct built source variants | all non-exact trials restored
calc__Q39textinput9inputform4BaseFv | 3 distinct built source variants | all non-exact trials restored
init__Q49textinput9inputform4Base14RowInfoManagerFv | 9 distinct built source variants | all non-exact trials restored

Two gate raw instruction mismatches are normalization artifacts. Animation::calc instructions 7/16 are byte-identical 41860054/41860028; confirmInputting_ instructions 211/227 are byte-identical 40860028/41860024. Both are objdiff 100%. No offset or symbol changes were made to change the count.
The concatenated isEnableCursorCache/getStartPos target symbol has no corresponding source function and no fuzzy score. It was not renamed, removed, or resized.
Remaining asm bodies are still present at objdiff 100%; conversion trials were restored because they did not stay instruction-exact.
