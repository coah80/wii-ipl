# zi81key attempts

43U only. Baseline source absent; 0 of 9 exact functions, 0 of 21460 code bytes, 0 of 1388 data bytes.

Created the source from target assembly, the shared eZiText types, and prior decompiler scratch under /tmp. Removed the scratch source's volatile tone and parameter-storage padding. Replaced raw parameter/work offsets with local ABI structs, recovered readable local names, and retained all nine real functions in object order. Shared headers and other translation units were unchanged.

The local parameter ABI has result bytes at 0x20, 0x21, 0x22, scratch at 0x24, and a final workspace slot at 0x28. Unobserved work/options fields remain opaque. The shared ziGetParam differs from this observed ABI, so this unit uses its own struct.

Pool checked before compiler experiments: zero strings on either side, identical. All spelling tables and the search-order constant match their target data.

## Exact functions

Zi8IsMatch1Key: 97/97 instructions, diffs 0.
Zi8SetFindCand: 50/50 instructions, diffs 0.
ZiIsSupportedPhonetic: 81/81 instructions, diffs 0.
Zi8ZHCheckSpelling: initially 419/419 instructions with six frame-size differences. Restored the target's 64-character conversion buffer instead of the scratch source's 72-character array. Final 419/419 instructions, diffs 0.

## Remaining functions

Zi8SpellingZY | row pointer | src 0x1dc base 0x1ec insns 119/123 | --- replace mine 1:5 base 1:5
Zi8SpellingZY | reorder decoded components | src 0x1ec base 0x1ec insns 123/123 | diffs 6: [27, 28, 35, 36, 37, 38]
Zi8SpellingZY | typed length and key | src 0x21c base 0x1ec insns 135/123 | --- delete mine 7:8 base 7:7
Zi8SpellingPY | decode tone at use | src 0x268 base 0x274 insns 154/157 | --- insert mine 11:11 base 11:14
Zi8SpellingPY | byte length | src 0x2ac base 0x274 insns 171/157 | --- delete mine 4:5 base 4:4
Zi8SpellingPY | for spelling scans | src 0x278 base 0x274 insns 158/157 | --- delete mine 4:5 base 4:4
MatchAltSound1Key | short phonetic offset | src 0x564 base 0x554 insns 345/341 | --- replace mine 10:11 base 10:11
MatchAltSound1Key | unsigned record positions | src 0x53c base 0x554 insns 335/341 | --- replace mine 10:11 base 10:11
MatchAltSound1Key | signed key byte decode | src 0x54c base 0x554 insns 339/341 | --- replace mine 10:11 base 10:11
Zi8Get1KeyPressSpelling | reverse charset branch nesting | src 0x18bc base 0x1a90 insns 1583/1700 | --- replace mine 0:1 base 0:1
Zi8Get1KeyPressSpelling | return immediately on zero spelling limit | src 0x18e0 base 0x1a90 insns 1592/1700 | --- replace mine 0:1 base 0:1
Zi8Get1KeyPressSpelling | declare scan index before flags | src 0x18dc base 0x1a90 insns 1591/1700 | --- replace mine 0:1 base 0:1
Zi8Get1KeyPressCandidates | declare index before flags | src 0x2b7c base 0x2574 insns 2783/2397 | --- replace mine 0:1 base 0:1
Zi8Get1KeyPressCandidates | preserve signed character temporaries | src 0x2bac base 0x2574 insns 2795/2397 | --- replace mine 0:1 base 0:1
Zi8Get1KeyPressCandidates | postincrement initial input index | src 0x2b78 base 0x2574 insns 2782/2397 | --- replace mine 0:1 base 0:1

Zi8SpellingZY retains six register-choice differences at instructions 27, 28, 35, 36, 37, 38; its 123 instruction count is correct.
Zi8SpellingPY retains a register-held tone rather than the original stack tone, an extra saved register, and table-address register differences. Retained the ordinary non-volatile scalar rather than forcing a spill.
MatchAltSound1Key retains search/register and table-load ordering differences, 339/341 instructions. All three variants were rejected and the readable baseline was restored.
Zi8Get1KeyPressSpelling still differs in branch structure, automatic-variable allocation, and table access sequences. Fixed signedness of expansion count, subtype constants, and result byte offset after inspecting assembly. Final 1572/1700 instructions. No artificial register or stack constraints were used.
Zi8Get1KeyPressCandidates still differs in branch structure, automatic-variable allocation, and record access sequences. Recovered explicit includeTone/matchFull variables and the key-index decrement from assembly, corrected unsigned key comparisons, restored the target's 64-character word buffer, removed pointer/integer round trips, and retained the initial index postincrement variant. Final 2775/2397 instructions.

## Linking investigation

Temporarily switched only zi81key to Matching and built main.dol. It linked successfully but failed the required SHA1. Ran unitaudit.py, nm -n on both objects, and a full byte comparison with orig/43U/00000008.app.

Original/linked bytes: 3867904/3867904.
Linked SHA1: 003260ba28d079e13eab29ec2fce03bfd2c7d810.
First differing DOL byte: 0x5ba. Differing bytes: 2042540.
build/43U/obj/libs/RVLMiddleware/eZiText/src/clib/zi81key.o: text 0x53d4
Zi8IsMatch1Key: offset 0x460, size 0x184.
Zi8Get1KeyPressSpelling: offset 0xd44, size 0x1a90.
Zi8Get1KeyPressCandidates: offset 0x27d4, size 0x2574.
Zi8ZHCheckSpelling: offset 0x4d48, size 0x68c.
build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi81key.o: text 0x57b8
Zi8IsMatch1Key: offset 0x464, size 0x184.
Zi8Get1KeyPressSpelling: offset 0xd40, size 0x1890.
Zi8Get1KeyPressCandidates: offset 0x25d0, size 0x2b5c.
Zi8ZHCheckSpelling: offset 0x512c, size 0x68c.
Next unit Zi8SetParentalControls linked at 0x814655b0; target 0x814651cc; displacement +0x3e4.
INTERNAL     .text    0x8145fdf8 libs/RVLMiddleware/eZiText/src/clib/zi81key.c  {0: 2, 4: 2, -4: 2, -516: 1}
STEP     .text    0x814651cc libs/RVLMiddleware/eZiText/src/clib/zi8alpha.c  +0x0->+0x3e4  (prev unit libs/RVLMiddleware/eZiText/src/clib/zi81key.c)

The four exact functions do not make the whole unit linkable. Restored NonMatching in configure.py. The final full gate rebuilds the unlinked object and checks the original DOL hash, zero regressions, pool, forbidden patterns, and readability.

The meanings of opaque work/options members and the final workspace slot are not fully recovered. The large candidate/spelling routines remain a partial reconstruction; their fuzzy scores are not acceptance evidence.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi81key] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi81key] objdiff: code 2588/21460 data 1160/1388 functions 4/9 fuzzy 66.2913 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi81key] instruction-exact functions: 4/9
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .rodata size 1152 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .text size 21460 match 66.291336
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extab size 72 match 97.22222
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extabindex size 108 match 95.37037
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingZY 99.756096
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingPY 97.038216
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: MatchAltSound1Key 95.60117
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressSpelling 59.97
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressCandidates 53.775135
[libs/RVLMiddleware/eZiText/src/clib/zi81key] baseline: code None/21460 data None functions 0 fuzzy 0.0000
regressions vs baseline: 0
global matched_code_percent: 69.56702 -> 69.65343
global fuzzy_match_percent: 77.05006 -> 77.52503
global complete_code_percent: 56.50306 -> 56.50306
global matched_data_percent: 85.57046 -> 85.63375
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
