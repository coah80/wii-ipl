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

## Follow-up matching attempts, 2026-09-30

Starting this continuation: 4/9 instruction-exact, code 2588/21460, data 1160/1388. Configuration stayed NonMatching throughout these attempts. All experiments were scoped to the named function, built as 43U and measured with ctxdiff. Rejected variants were restored.

- Zi8SpellingZY: reversed scalar declarations (123/123, ten differences); expressed the final-row access with pointer arithmetic (123/123, six differences); used a typed four-byte row structure (123/123, six differences). Retained the six-difference baseline.
- Zi8SpellingPY: moved tone declaration first (158/157); used a signed tone (159/157); changed the spelling scans to postfix increments (158/157). None removed the register-held tone or restored the target stack slot.
- MatchAltSound1Key: reversed scalar declarations (339/341); made the signed midpoint sum explicit (339/341); changed backward-search decrement to assignment (339/341). None fixed table-load/search ordering.
- Zi8Get1KeyPressSpelling: unsigned terminator equality (1571/1700, 59.628235%); reverse local declarations (1572/1700, 59.968235%); integer expansion count and integer boolean conversions (1536/1700, 59.57353%). All scored below the starting 59.97%; retained the baseline.
- Zi8Get1KeyPressCandidates: reverse local declarations (2775/2397, 53.831455%); while-form terminator trimming (2773/2397, 53.523155%); explicit unsigned charset result (2775/2397, 53.775135%). Retained the small fuzzy-score improvement from reversing the candidate function declarations; instruction count and the target stack-layout mismatch remain unchanged. This is a partial improvement, not an exact match. No additional exact function was found.

## Complete-body continuation, 2026-09-30

Starting from f20fc7b8: spelling 59.97%, candidates 53.831455%; unit 4/9 exact. Spelling target frame is 0x90; the prior source used 0xb0. Recovered byte/halfword/pointer declaration order from stack accesses, separated the input-conversion flag from the pinyin flag, and reused the target's character and scan variables across their successive roles. Restored mode-selection address order, postfix expansion/output writes, and missing spelling-call result narrowing. Frame now 0x90, 1577/1700 instructions, 79.560585%; first exact divergence +0x1c is a register choice. Quick gate PASS, zero regressions, identical pool.

Spelling address-order pass: restored a separate condition for every phonetic expansion store, including the target's fourth EFF5 expansion F316. Corrected increment forms, language-support branch direction, early returns, spelling length's shared stack slot, explicit comparison breaks, and the exact/extended table passes through the final return. Every target basic-block region is represented; there is no stub or omitted tail. 1697/1700 instructions, 96.225296%; first exact divergence +0x20 is register allocation. Remaining structural differences are a few result moves, output scan scheduling and the remaining-skip branch. Quick gate PASS, zero regressions.

Spelling final scan attempt: restored highlighted-output increment scheduling, workspace length comparison operand order and the final remaining-candidate branch direction. 1696/1700, 96.82353%; first exact divergence +0x20. Kept the gain after quick gate PASS. The remaining four-instruction difference consists mainly of compiler-generated copies after calls and postfix stores; all table passes and exits are present.

Candidates frame pass: recovered separate key-value/key-mask arrays, byte declaration order and the original shared scan index. Removed decompiler-only call-result locals and added typed OEM/PUD arguments. Recovered switch dispatches and sequential phrase cursor operations. 2451/2397 instructions, frame 0x160 versus target 0x140, 68.29662%. The remaining extra frame words are compiler-generated Boolean temporaries from comma expressions. Quick gate PASS; every previously exact function remains exact.

Candidates prefix pass: expanded comma-expression Boolean tests into sequential table loads and checks, removing five compiler temporaries; frame now exactly 0x140. Restored charset switches and branches, key-value/mask writes, division, call-result narrowing and output operand order. 2390/2397 instructions, 72.67042%; first exact divergence +0x28 is a register choice. Quick gate PASS. Continuing through OEM, PUD, phrase, sorted ordinal, user ordinal and ordinary ordinal paths.

Candidates OEM/PUD address-order pass: recovered typed byte-return dictionary calls, corrected key-mask activation, replaced reconstructed output labels with the original skip/word/character branches and postfix output indexing. Restored the OEM and PUD scan loops through their exhaustion paths. Frame remains 0x140; candidates 80.75636% versus 53.831455% at entry. Quick gate PASS, zero regressions, identical pool.

Candidates phrase/sorted-ordinal passes: restored the context-count decrement after comparison, first phrase-ordinal consumption and charset scan from the saved entry cursor. Rebuilt each group before continuing. Recovered character-first duplicate filtering, word output, table-filter narrowing and sorted ordinal explicit loop breaks/output increments. Candidate score 82.131%, then 84.724236%, then 88.3033%; frame 0x140 throughout. Quick gate PASS, no regressions.

Candidates final body pass: restored user-ordinal and ordinary-ordinal duplicate branches, byte/word emission, capacity exits and cursor increment order through the final return. Measured after each pass: 91.54819%, then 94.64998%. Both huge bodies now cover every target basic-block region; candidates frame 0x140 and first exact divergence +0x28 (register choice). Quick gate PASS, zero regressions.

Near-match continuation: candidate byte narrowing/branch inversion combined scored 94.54735% and regressed the previously exact matcher to 98.96907%; restoring its tone parameter recovered the matcher but candidates remained 94.56404%. Isolated duplicate-result casts plus final postfix store scored 94.335%; both rejected, restoring 94.64998%. MatchAltSound1Key recovered address-order search labels and halfword table indices (98.2698%, 345/341), then correct integer offset and low-byte expression (99.80939%, 341/341); restored the search restart assignment. Quick gate PASS, zero regressions.

Additional near-match trials after the complete-body pass: MatchAltSound1Key with a generic context argument and typed local alias retained 341/341 instructions and the same twelve register differences; reversing declarations produced fifty differences; postfix backward-search decrement retained the same twelve. Restored the best readable source: 99.82404%, 341/341, context and phonetic table base exchange r25/r26. All bodies remain complete.

Additional near-match source trials in this continuation:

- Zi8SpellingZY: decoded components as signed halfwords; 94.10569%, src 0x1f8 base 0x1ec insns 126/123. --- replace mine 8:10 base 8:9.
- Zi8SpellingZY: initialize length at declaration; 99.756096%, src 0x1ec base 0x1ec insns 123/123. diffs 6: [27, 28, 35, 36, 37, 38].
- Zi8SpellingZY: explicit scan for loop; 99.756096%, src 0x1ec base 0x1ec insns 123/123. diffs 6: [27, 28, 35, 36, 37, 38].
- Zi8SpellingPY: constant tone at declaration; 94.968155%, src 0x278 base 0x274 insns 158/157. --- delete mine 4:7 base 4:4.
- Zi8SpellingPY: decode all components in declaration order; 97.54777%, src 0x278 base 0x274 insns 158/157. --- replace mine 4:5 base 4:5.
- Zi8SpellingPY: explicit scan for loops; 97.038216%, src 0x278 base 0x274 insns 158/157. --- delete mine 4:5 base 4:4.

Retained PY component initialization in declaration order: 97.54777% versus 97.038216% at entry, 158/157 instructions. Initializing length first restored the lower baseline score; constant tone worsened it. Quick gate PASS, zero regressions. ZY retains six table-base register differences; no rejected source variant remains.

Final full gate over zi81key and zi8alpha: PASS, original DOL hash, identical pools, zero regressions, zero net forbidden patterns and readability warnings. zi81key remains 4/9 instruction-exact; exact code 2588/21460, exact data 1208/1388, weighted fuzzy 96.51463%. Entry exact data was 1160/1388. Final function scores: ZY 99.756096%, PY 97.54777%, alternate sound 99.82404%, spelling 96.82353%, candidates 94.64998%; the four exact functions remain exact. Both large bodies cover all original block regions. Remaining differences and rejected source variants are recorded above; no new exact function is claimed.

## Exactness continuation from a3b04ad9, 2026-09-30

Entry 4/9 instruction-exact. MatchAltSound1Key had 341/341 instructions, twelve differences exchanging the workspace and phonetic-table registers r25/r26. Recovered the shared generic workspace formal and cast only its field accesses to the local workspace structure. This preserves the API's original workspace type, with no extra pointer local. Result: objdiff 100.0%, 341/341 instructions, ctxdiff diffs 0. All other function scores unchanged. Quick gate PASS, identical pool, zero regressions.

Further exactness variants in this continuation (rejected unless explicitly retained):

- Zi8SpellingZY: unsigned long length; 99.756096%, src 0x1ec base 0x1ec insns 123/123.
- Zi8SpellingZY: index before table pointer in address expression; 99.756096%, src 0x1ec base 0x1ec insns 123/123.
- Zi8SpellingZY: signed length counter; 99.756096%, src 0x1ec base 0x1ec insns 123/123.
- Zi8SpellingPY: full-width tone switch expression; 97.54777%, src 0x278 base 0x274 insns 158/157.
- Zi8SpellingPY: repeated halfword normalization at tone switch; 97.54777%, src 0x278 base 0x274 insns 158/157.
- Zi8SpellingPY: full-width include-tone formal with byte test; 97.54777%, src 0x278 base 0x274 insns 158/157.
- Zi8SpellingPY: halfword key formal; 93.598724%, src 0x280 base 0x274 insns 160/157.
- Zi8SpellingPY: unsigned long tone temporary; 97.19745%, src 0x274 base 0x274 insns 157/157.
- Zi8SpellingPY: signed tone temporary; 97.19745%, src 0x274 base 0x274 insns 157/157.
- Zi8Get1KeyPressSpelling: generic workspace parameter with typed field access; 96.82353%, src 0x1a80 base 0x1a90 insns 1696/1700.
- Zi8Get1KeyPressSpelling: restore phonetic output candidate-loop increment; 96.882355%, src 0x1a84 base 0x1a90 insns 1697/1700.

ZY additionally tried generic output formal, unsigned-long and signed length counters, reversed index/table address operands and a typed final-spelling row structure: all retained 123/123 instructions and the same six differences, 99.756096%. Restored the ordinary two-dimensional table.

Retained the missing tableIndex increment after each converted phonetic candidate. The target increments this index before advancing past the string terminator; without it the source loop could fail to terminate. Spelling now 96.882355%, 1697/1700 instructions, frame 0x90. Quick gate PASS, zero regressions, identical pool.

Spelling follow-up variants: combined terminator-trimming while condition fell to 96.16765%; unsigned-long total counter and const phonetic-table pointer retained 96.882355%. Separating the two phonetic conversion stores from their pointer increments raised the score to 97.74117%, 1701/1700 instructions; first strict divergence moved from +0x20 to +0xa0 (branch displacement). Retained after quick gate PASS with zero regressions and identical pool.

Candidate workspace generic-formal variant retained 94.64998%, 2381/2397. Recovered Zi8IsDupWordW's three-argument prototype from its matched definition in zi8getc2.c: ziBool return, wide-string pointer, byte length and generic workspace. This supplies the original byte-argument narrowing at length-one calls and removes old-style-call promotion. Candidates rose to 94.779305%; spelling rose to 97.867645%, with all five exact functions preserved. Quick gate PASS, zero regressions.

Spelling postfix-compound-store retry fell to 96.805885%; capturing an element pointer before advancing fell to 95.17765% and enlarged the frame. Both rejected.

Candidate prefix-filter branch now emits the matching case before the failing case, as in the target. 94.87901%, 2384/2397 instructions, frame 0x140. Quick gate PASS, zero regressions; retained.

Candidate endian decoding: shift the explicitly narrowed high byte before adding the low byte, replacing multiplication by 0x100 in the sorted ordinal and ordinary character paths. This restores two target narrowing instructions and high-byte-first evaluation. 95.355446%, 2386/2397 instructions. Explicit duplicate-return byte casts did not change the prior score. Quick gate PASS, zero regressions; shift expressions retained.

Final rejected variants (restored the committed higher score after each):

- Zi8Get1KeyPressCandidates: prefix total candidate increment inside capacity comparison; 95.06467%, src 0x253c base 0x2574 insns 2383/2397.
- Zi8Get1KeyPressSpelling: merge nested language fallback conditions into else if; 97.867645%, src 0x1a90 base 0x1a90 insns 1700/1700.

Final retained scores: alternate sound 100%, ZY 99.756096%, PY 97.54777%, spelling 97.867645%, candidates 95.355446%. All large bodies are complete. ZY retains six table-address register differences; PY retains a register-held tone rather than the target halfword stack slot; spelling retains helper-result copies and output-cursor scheduling differences; candidates retain helper-result copies, matcher argument narrowing and counter/output scheduling. Each remaining function has more than three distinct source-level attempts recorded. Five of nine functions are instruction-exact.

Final full gate over both owned units: GATE PASS, full build ok, original DOL hash 26116613f624061ba99c8d1a299aaa6efa85670d, both pools identical, zero regressions, zero added forbidden patterns and zero readability warnings. zi81key exact functions 4/9 -> 5/9, exact code 2588 -> 3952 of 21460 bytes, exact data 1208/1388 unchanged, weighted fuzzy 96.5146% -> 97.1719%. zi8alpha exact functions 10/12 unchanged, exact code 5704/21664 and exact data 72/564 unchanged, weighted fuzzy 86.7764% -> 88.8508%. These are partial matching improvements; the remaining functions are not claimed exact.

## Address-order continuation from 131d8f74, 2026-09-30

Entry open functions, largest first:

- Zi8Get1KeyPressCandidates: 9588 bytes, 95.355446%, 2386/2397 instructions.
- Zi8Get1KeyPressSpelling: 6800 bytes, 97.867645%, 1700/1700 instructions.
- Zi8SpellingPY: 628 bytes, 97.54777%, 158/157 instructions.
- Zi8SpellingZY: 492 bytes, 99.756096%, 123/123 and six register differences.

Entry unit: 5/9 instruction-exact, exact code 3952/21460, data 1208/1388.
The two large frames already agree, 0x140 and 0x90 respectively. Pools are
identical. All rejected variants below were restored before final validation.

Candidate call and output audit:

1. Recovered the byte sixth argument of Zi8IsMatch1Key from the target's literal
   argument narrowing. The initial formal change alone added a redundant byte
   normalization in the matcher. Replaced its masked zero test with the typed
   byte zero test: matcher again 97/97, diffs 0, objdiff 100%. Candidates improve
   to 95.39716%, 2387/2397. Retained; quick gate PASS, zero regressions.
2. Halfword key and byte length matcher formals with ordinary typed uses:
   matcher stays exact, candidates 95.26784%, 2398/2397. Halfword key alone gives
   the same result. Rejected; byte sixth argument remains.
3. Explicit halfword casts of nested Zi8GetPCode results: unchanged 95.39716%.
   Explicit halfword masks: 94.456406%, 2391/2397. Rejected.
4. Preincrement total count inside OEM/PUD/phrase capacity comparisons:
   95.106384%, 2384/2397. Removes target-redundant reloads but perturbs other
   call-result copies; rejected.
5. Byte duplicate-bit result and return in Zi8SetFindCand: helper remains
   50/50, diffs 0, 100%; candidates 94.73383%, 2395/2397. Explicit byte casts at
   the callers produce the same candidate code. Rejected in favor of the
   higher candidate score; original helper remains exact and unchanged.

Spelling call and cursor audit:

1. Postincrement compound store for non-apostrophe conversion: 96.723526%,
   1697/1700. The target pointer scheduling is closer, but new helper copies
   and register differences lower the score. Rejected.
2. Constant-first language-support comparisons: unchanged 97.867645%,
   1700/1700, with the same two missing fallback-call result copies.
3. Put the converted-candidate index increment in the for header: 97.75%,
   1700/1700, eight structural groups instead of six. Rejected.
4. Explicit converted-character OR assignment: unchanged 97.867645%.
5. Postincrement only the apostrophe replacement, as at 814620C8..814620D4:
   97.92647%, 1699/1700, five structural groups. Retained. The remaining gaps
   are fallback-call copies and non-apostrophe cursor scheduling.

ZY register-only attempts: flattened row indexing 125/123, rejected;
row pointer dereference 123/123 and the same six register differences; generic
output formal 123/123 with 115 differences, rejected. Full-width initial/final
indices with explicit halfword normalization separately and together each
retain 99.756096%, 123/123 and the same six table-address register differences.
No variant was retained.

PY attempts: initialize length before decoded components, 97.038216%, 158/157;
signed tone, 94.55414%, 158/157; decode tone after spelling rows, 94.968155%,
158/157; for-loop scans, unchanged 97.54777%, 158/157. No variant recovers the
original halfword tone slot at stack 0x8 without a register-backed tone.
No artificial tone-storage object or volatile qualifier was introduced.

All four open functions have at least three distinct measured source-level
attempts in this run. Only ZY is registers-only. No new exact function is
claimed; both units remain NonMatching. The existing complete function bodies
remain present, and no shared header or other unit was edited.

Final full gate over both units: GATE PASS. Full clean 43U build passes, DOL
SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, both pools identical, zero
regressions, zero forbidden patterns and zero readability warnings. One-key
unit remains 5/9 instruction-exact, code 3952/21460 and data 1208/1388;
weighted fuzzy 97.17185% -> 97.20914%. Exact-count completion is not achieved.
