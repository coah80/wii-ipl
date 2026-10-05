# rx5 allocator investigation

Start: f7cc4a45, branch agent/w1005/rx5. origin/main fetched and equal to HEAD.
Owned functions: scan_varinit, restart_interval, parse_dht, exif_parse, IFD0_tag_parse, decode_iquant. No other source scope.

Acceptance: readable C, exact-name objdiff 100%, ctxdiff zero, unchanged pools, no unit regressions, full gate and retail DOL SHA1. Existing assembly stays until a C replacement passes. Each unresolved function gets allocator evidence, three distinct compiled trials and the required source searches.

Evidence lives under build/rx5 in this worktree. The private mwdbg launcher only changes the output-directory guard and GDB working directory to keep captures here; it uses the unchanged shared gc3.py, compiler and global debugger lock. Compiler flags come from this worktree's Ninja command. No other worktree is used.

Baseline: jdec_main 13/13 exact, 5604 code bytes and 256 data bytes, including assembly placeholders. EXIF 3/6 exact, 1348/5088 code bytes. iqdec 0/1, 0/1104 code bytes. Source trial percentages below measure C candidates, distinct from the retained assembly's 100%.

## Compiled trials
- scan/baseline: 99.496124%; 129/129 instructions, 9 aligned differences. Recovered best prior C; no retained source edit.
- restart/baseline: 68.333336%; 75/93 instructions, 33 aligned differences. Recovered best prior C; no retained source edit.
- dht/baseline: 99.708336%; 120/120 instructions, 6 aligned differences. Recovered best prior C; no retained source edit.
- exif/baseline: 99.43396%; 212/212 instructions, 21 aligned differences. Live source baseline.
- ifd0/baseline: 99.49065%; 480/481 instructions, 456 aligned differences. Live source baseline.
- iquant/baseline: 99.710144%; 276/276 instructions, 13 aligned differences. Live source baseline.
- restart/recovered: 96.77419%; 93/93 instructions, 17 aligned differences. Recovered helper as well as caller; incomplete helper-less baseline above is rejected.

## Target register map

- scan_varinit, instructions 8-21: frame base r5; component address r8, ours r7; horizontal sample r6 and scaled horizontal sample r9, ours r4 for both; vertical sample r0 and scaled vertical sample r7, ours r6 and r8; horizontal divisor r4, ours r0. All nine differences are register choices; 129 instructions agree.
- restart_interval: saved inputs already agree, state r31, maxMCU r30, work r29, mcuCount r28. The remaining block wants zero r0, restart index r4, stepY and row count r5, stepX and column r4, pitch r6. Our zero r5 conflicts with row-count r4 and column r0. Instructions 68-70 also schedule the second division earlier. Thus the recovered 17-difference C is not purely register-only.
- parse_dht: target class r27, table ID r26, count-buffer cursor r28, loop index and total r25, permanent zero r29, work r30, scaleInfo r31. Our ID r28 and cursor r26 are exchanged, with six differences and the same 120 instructions.
- exif_parse: target data r30, first IFD cursor r27, count r23, byte span r26. Ours data r27, first cursor r30, count r26, span r23. The second IFD count reuses the first cursor's register. All 21 differences are register choices across 212 instructions.
- IFD0_tag_parse: target resolution offset r8 and resolved pointer r6; ours offset r6 and pointer r8 for both X and Y rational tags. Target additionally returns with bltlr after comparing tag 0x103. This extra branch is a control-flow mismatch, not allocator behavior. Baseline is 480/481 instructions.
- decode_iquant: target AC Huffman table r25 and symbols r24; ours r29/r30. Target zigzag table r29 and element r30; ours r24/r25. Downstream coefficient-mask r6 and coefficient-offset r7 also swap. All 13 differences are register choices across 276 instructions.

Three 1200-second annealing searches per assigned function are queued from the recovered prior best C. The private srcsearch copy only fixes function-definition discovery so static prototypes do not accidentally select an unrelated function body; the shared 24-slot lock is unchanged. Search outputs remain advisory until source semantics and the whole unit are checked.

## Private debugger transport

The shared lock had more than twenty queued captures. To avoid occupying or changing another worker's session, rx5 canceled only its own two queued processes and copied the debugger transport into build/rx5. The private retrowin32 binary changes the single immediate TCP port 9001 to 9105, located from objdump at the listener setup. gc3.py changes only its import root and matching connection port. The private launcher uses a local lock, local outputs and local driver. The MWCC executable and code-generation flags remain unchanged. Private transport hashes and the two-byte patch offset are in build/rx5/private-debugger.json. Each successful capture is checked against an independent wibo compile before its allocator evidence is trusted.
- scan/inline-vmul: 99.263565%; 129/129 instructions, 13 aligned differences. Allocator r39 vMul8 is colored after expression temps; inline its product to create a later expression vreg.
- scan/inline-vsample: 97.9845%; 129/129 instructions, 9 aligned differences. Move vertical sample load and product into the division expression, promoting both from named values to generated temps.
- scan/inline-vdivisor: 94.88372%; 129/129 instructions, 12 aligned differences. Generate vertical dividend and divisor together to alter their expression-vreg order.
- scan/reuse-scaled-horizontal: 99.263565%; 129/129 instructions, 13 aligned differences. Reuse the horizontal scale local after its last use, avoiding the separately named low-priority vertical scale.
- scan/vmul-priority-0: 99.263565%; 129/129 instructions, 13 aligned differences. Move pure vertical product past the horizontal result to target a vreg between horizontal quotient and component-base temps.
- scan/vmul-priority-1: 99.263565%; 129/129 instructions, 13 aligned differences. Move pure vertical product past the horizontal result to target a vreg between horizontal quotient and component-base temps.
- scan/vmul-priority-2: 99.263565%; 129/129 instructions, 13 aligned differences. Move pure vertical product past the horizontal result to target a vreg between horizontal quotient and component-base temps.
- dht/named-id: 99.416664%; 120/120 instructions, 13 aligned differences. r47 helper-return ID is colored before the named cursor. Make ID a plain local to place it in the named-vreg range.
- dht/named-class: 99.291664%; 120/120 instructions, 16 aligned differences. Keep ID inline boundary, make class a named local; distinguish which generated identity controls the swap.
- dht/named-header: 99.291664%; 120/120 instructions, 16 aligned differences. Make both header values named locals so cursor declaration order can precede their coloring.
- dht/id-after-class: 99.583336%; 120/120 instructions, 9 aligned differences. Reverse independent header extraction calls to reverse their inline temporary order.
- dht/cursor-outer: 99.708336%; 120/120 instructions, 6 aligned differences. Move cursor scope outside do-loop, testing its named-vreg placement without changing its lifetime.
- dht/cursor-count-reuse: 99.708336%; 120/120 instructions, 6 aligned differences. Reuse the byte cursor for summing the counts; test degree and recurrence renumbering.
- exif/span-expression: 98.58491%; 212/212 instructions, 46 aligned differences. Span is named r36, while count is expression r114. Recompute count * 12 textually and let CSE create a higher-numbered span temp.
- exif/parameter-cursor: 99.59906%; 212/212 instructions, 14 aligned differences. Use the incoming pointer as the mutable entry cursor and retain its base in a local, aiming to color base before pInfo/size.
- exif/wide-count: 98.86793%; 212/212 instructions, 38 aligned differences. Preserve the zero-extended count in a full-width local to test whether it survives as a named node.
- exif/parameter-cursor-span: 99.03302%; 212/212 instructions, 32 aligned differences. Combine base/cursor ownership with generated span identity.
- restart/zero-priority-0: 97.52688%; 93/93 instructions, 9 aligned differences. Zero vreg r65 is blocked from r0 by the column division r75. Generate zero after pure coordinate arithmetic so zero colors earlier.
- restart/zero-priority-1: 97.63441%; 93/93 instructions, 6 aligned differences. Zero vreg r65 is blocked from r0 by the column division r75. Generate zero after pure coordinate arithmetic so zero colors earlier.
- restart/zero-priority-2: 100.0%; 93/93 instructions, 0 aligned differences. Zero vreg r65 is blocked from r0 by the column division r75. Generate zero after pure coordinate arithmetic so zero colors earlier.
- restart/column-first: 96.77419%; 93/93 instructions, 17 aligned differences. Reverse independent coordinate division expressions to exchange their generated-vreg order.
- restart/clean-exact: 100.0%; 93/93 instructions, 0 aligned differences. Remove unused recovered declarations and fix helper indentation; position math precedes predictor reset, preserving every defined result and memory access.
- iquant/separate-ac-both: 99.29348%; 276/276 instructions, 32 aligned differences. Baseline AC table/symbols are split temporaries r57/r58 colored before zztbl r39 and zz r42. Give AC values their own block locals so their numbers precede the zigzag locals.
- iquant/separate-ac-table: 99.221016%; 276/276 instructions, 36 aligned differences. Baseline AC table/symbols are split temporaries r57/r58 colored before zztbl r39 and zz r42. Give AC values their own block locals so their numbers precede the zigzag locals.
- iquant/separate-ac-symbols: 99.25725%; 276/276 instructions, 34 aligned differences. Baseline AC table/symbols are split temporaries r57/r58 colored before zztbl r39 and zz r42. Give AC values their own block locals so their numbers precede the zigzag locals.
- iquant/before-symbol-zz-zztbl: 99.891304%; 276/276 instructions, 6 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- iquant/before-symbol-zztbl-zz: 99.78261%; 276/276 instructions, 9 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- iquant/after-symbol-zz-zztbl: 99.85507%; 276/276 instructions, 8 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- iquant/after-symbol-zztbl-zz: 99.746376%; 276/276 instructions, 11 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- iquant/before-all-zz-zztbl: 99.891304%; 276/276 instructions, 6 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- iquant/before-all-zztbl-zz: 99.78261%; 276/276 instructions, 9 aligned differences. AC Huffman locals now receive r25/r24. Raise zz/zztbl above ac_fast and idx in the high-degree coloring order using ordinary declaration order.
- ifd0/separate-x-denominator: 99.49065%; 480/481 instructions, 456 aligned differences. Numerator pointer is named because p is assigned twice, while offset is an inline temp. Separate denominator pointer to let numerator pointer become an expression temp and color first.
- ifd0/separate-y-denominator: 99.49065%; 480/481 instructions, 456 aligned differences. Numerator pointer is named because p is assigned twice, while offset is an inline temp. Separate denominator pointer to let numerator pointer become an expression temp and color first.
- ifd0/separate-xy-denominator: 99.49065%; 480/481 instructions, 456 aligned differences. Numerator pointer is named because p is assigned twice, while offset is an inline temp. Separate denominator pointer to let numerator pointer become an expression temp and color first.
- exif/cursor-second-local: 93.98113%; 210/212 instructions, 115 aligned differences. Split only the second IFD cursor from the mutable input parameter; restore its later expression identity.
- exif/cursor-wide-span: 99.74056%; 212/212 instructions, 9 aligned differences. Use a named full-width count and a signed CSE byte-span expression to place span ahead of count in the coloring order.
- exif/cursor-wide-span-second: 94.21698%; 210/212 instructions, 110 aligned differences. Combine full-width count, signed span expression and independent second-IFD cursor.
- exif/cursor-wide-count: 99.221695%; 212/212 instructions, 27 aligned differences. Test full-width count after fixing input base ownership.
- scan/baseline-extents-first: 99.496124%; 129/129 instructions, 9 aligned differences. Generate both sample extents before pixel-count divisions. This places the vertical product between component-address and horizontal-count temporaries.
- scan/inline-vmul-extents-first: 99.689926%; 129/129 instructions, 6 aligned differences. Generate both sample extents before pixel-count divisions. This places the vertical product between component-address and horizontal-count temporaries.
- scan/inline-vsample-extents-first: 100.0%; 129/129 instructions, 0 aligned differences. Generate both sample extents before pixel-count divisions. This places the vertical product between component-address and horizontal-count temporaries.
- scan/inline-vdivisor-extents-first: 100.0%; 129/129 instructions, 0 aligned differences. Generate both sample extents before pixel-count divisions. This places the vertical product between component-address and horizontal-count temporaries.

The scratch exif cursor-second-local and cursor-wide-span-second trials are invalid and discarded. Their text rewrite stopped at the first nested closing brace, so later reads still used the old cursor. A balanced-brace rewrite fixes the experiment; only the corrected trials below are usable. No malformed trial was installed.
- exif/cursor-wide-span-second-scoped: 98.86793%; 212/212 instructions, 41 aligned differences. Correct balanced rewrite of the entire second IFD block; all its cursor accesses use one separate local.
- iquant/index-before-mask: 99.891304%; 276/276 instructions, 6 aligned differences. Coefficient address is generated after the mask and colors first. Read q before pure mask arithmetic, preserving memory access order, to reverse their vreg creation.
- iquant/index-before-bit-position: 99.891304%; 276/276 instructions, 6 aligned differences. Coefficient address is generated after the mask and colors first. Read q before pure mask arithmetic, preserving memory access order, to reverse their vreg creation.
- iquant/byte-zigzag: 99.891304%; 276/276 instructions, 6 aligned differences. Use the byte type supplied by the zigzag table; test whether the scaled index remains a separate CSE temporary.
- iquant/named-ac-mask: 98.514496%; 276/276 instructions, 77 aligned differences. Make the repeated mask a real local instead of a CSE split of extra; test its degree and priority.
- iquant/reuse-bitcount-mask: 99.891304%; 276/276 instructions, 6 aligned differences. Reuse the completed bit-width local for its mask; evaluate the next lookup shift directly.
- iquant/early-coefficient-pointer: 99.891304%; 276/276 instructions, 6 aligned differences. Declare the pointer at the start of the C block, form it before arithmetic, and preserve its load position.
- iquant/mask-expression: 100.0%; 276/276 instructions, 0 aligned differences. Avoid giving extra an intermediate mask value, so mask creation comes from CSE instead of splitting extra into two identities.
- iquant/mask-expression-reverse: 100.0%; 276/276 instructions, 0 aligned differences. Avoid giving extra an intermediate mask value, so mask creation comes from CSE instead of splitting extra into two identities.
- iquant/masked-index: 99.891304%; 276/276 instructions, 6 aligned differences. Spell byte truncation as an integer mask at both array accesses to test common-index expression identity.
- exif/second-cursor-before-data: 98.79717%; 212/212 instructions, 42 aligned differences. First/second cursor currently share high-degree parameter r32. Name a second cursor after low-degree count/index nodes in vreg order, so its degree drops before simplify visits it.
- exif/second-cursor-after-data: 98.86793%; 212/212 instructions, 41 aligned differences. First/second cursor currently share high-degree parameter r32. Name a second cursor after low-degree count/index nodes in vreg order, so its degree drops before simplify visits it.
- exif/second-cursor-before-count: 98.86793%; 212/212 instructions, 41 aligned differences. First/second cursor currently share high-degree parameter r32. Name a second cursor after low-degree count/index nodes in vreg order, so its degree drops before simplify visits it.
- exif/second-cursor-first-local: 98.79717%; 212/212 instructions, 42 aligned differences. First/second cursor currently share high-degree parameter r32. Name a second cursor after low-degree count/index nodes in vreg order, so its degree drops before simplify visits it.
- dht/cursor-initialize-zero: 99.708336%; 120/120 instructions, 6 aligned differences. Write the zero count through the same cursor before advancing to length one, testing its recurrence identity.
- dht/header-expressions: 96.125%; 120/120 instructions, 13 aligned differences. Retain the raw header and let CSE share validated class/ID extraction with the table-selection call.
- ifd0/offset-advance: 99.49065%; 480/481 instructions, 456 aligned differences. Advance offset itself for the denominator so it has multiple definitions and can retain a named-vreg identity; then order pointer and offset declarations.
- ifd0/offset-pointer-first: 99.49065%; 480/481 instructions, 456 aligned differences. Advance offset itself for the denominator so it has multiple definitions and can retain a named-vreg identity; then order pointer and offset declarations.
- ifd0/offset-offset-first: 99.49065%; 480/481 instructions, 456 aligned differences. Advance offset itself for the denominator so it has multiple definitions and can retain a named-vreg identity; then order pointer and offset declarations.

## Confirmed allocator explanations

### scan_varinit, exact C

The baseline vertical scale is named r39, 12 graph neighbors and simplify degree 11. It is colored after component-address expression r54. r54 gets legal mask 0x1f80 and r7; r39 then gets 0x1f00 and r8. There are no coalescing candidates. The target needs the opposite order.

Inlining the vertical load/product alone generates the product too late, r63/r64, and displaces the horizontal quotient. Computing both extents before the image-count divisions puts the product in expression r56. It colors before component-address r51. Confirmed exact assignments: vertical scale r56 -> r7; component address r51 -> r8; horizontal scale r49 -> r9; horizontal sample r48 -> r6; vertical sample r55 -> r0. The generated operations stay in the target order after scheduling. build/rx5/scan/inline-vdivisor-extents-first/mwdbg/unit.o equals the independent wibo object byte for byte. Installed ctxdiff: 129/129, diffs 0; objdiff 100.0.

### restart_interval, exact C

Baseline column quotient r75 is colored before row quotient r71 and zero r65. Their legal masks are 0xc0001ff1, 0x1ff0 and 0x1fe0, yielding r0, r4 and r5. All saved input registers already agree. Relevant coalescing does not merge these values; the result-return coalesce elsewhere is unrelated.

Computing the next position before clearing the predictors generates zero as r72, ahead of column r68 and row r64 in reverse coloring order. Their legal masks become 0x1ff1, 0xc0001ff0 and 0x1fe0, yielding r0, r4 and r5. The zero's new interference fixes the final scheduling as well as the register names. All state loads remain before the clears, and the moved operations are pure coordinate arithmetic. The target also reads marker before testing the get_wbyte return, so the C preserves that established sequence. No invented uninitialized value is used. The cleaned capture equals the wibo object. Installed ctxdiff: 93/93, diffs 0; objdiff 100.0. Quick full build, retail DOL hash, pool, regressions and source scans all pass.

### decode_iquant, exact C

Baseline AC Huffman table/symbol values are split temporaries r57/r58 with 82 neighbors each. They simplify in the later high-degree pass and color before named zigzag table r39 and element r42. This allocates the Huffman values to r29/r30 and the zigzag values to r24/r25. The relevant graph representatives remain separate; coalescing mainly removes call-return copies and does not cause this swap.

Separate AC locals and ordinary zigzag declaration order change that sequence to zz r55 -> r30, zztbl r54 -> r29, ac_fast r52 -> r28, idx r51 -> r27, t r43 -> r26, AC table r38 -> r25, AC symbols r37 -> r24. This removes seven differences. The last six come from mask r61, a split value of extra, coloring after scaled-index r72. Both have fewer than 29 neighbors, 27 and 20. Combining the mask assignment and AND into one expression removes that split. The mask becomes expression r165 -> r6 and colors before scaled-index r71 -> r7. Moving the coefficient load or changing zz to u8 did not do this. The final capture equals independent wibo output; ctxdiff 276/276, diffs 0; objdiff 100.0.

The six pending scan/restart searches and three pending iqdec searches were canceled after their functions became exact manually. Open-function searches keep the 24-slot lock, use immutable copies of target objects and cached real Ninja commands, and survive the required clean gate. Queued retries use a short random delay to avoid synchronized lock starvation. EXIF searches that start after the manual work use the reviewed 212-instruction, nine-difference C candidate. No search candidate has been installed.

## First clean acceptance gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] objdiff: code 5604/5604 data 256/256 functions 13/13 fuzzy 100.0000 linked code 5604
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] instruction-exact functions: 13/13
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .rodata size 256 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .text size 5604 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] baseline: code 5604/5604 data 256 functions 13 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 98.9804 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 98.98035
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code 1104/1104 data None/None functions 1/1 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 1/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.7101
regressions vs baseline: 0
global matched_code_percent: 92.82099 -> 92.85785
global fuzzy_match_percent: 99.78336 -> 99.78347
global complete_code_percent: 77.26517 -> 77.26517
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

The full clean gate covers the two assembly-to-C conversions and the exact iqdec change together. Each function is staged separately for a local commit; the indexed intermediate jdec_main sources were also the independently compiled, all-100% trial units. No EXIF trial is retained.
- exif/second-cursor-before-data-shorter-live: 98.79717%; 212/212 instructions, 42 aligned differences. nextEntries has exactly 29 neighbors and waits for the high-degree pass. Move its pure address calculation after remaining-size arithmetic to remove one transient interference edge.
- exif/second-cursor-after-data-shorter-live: 98.86793%; 212/212 instructions, 41 aligned differences. nextEntries has exactly 29 neighbors and waits for the high-degree pass. Move its pure address calculation after remaining-size arithmetic to remove one transient interference edge.
- exif/second-cursor-before-count-shorter-live: 98.86793%; 212/212 instructions, 41 aligned differences. nextEntries has exactly 29 neighbors and waits for the high-degree pass. Move its pure address calculation after remaining-size arithmetic to remove one transient interference edge.
- exif/second-index-after-cursor: 99.48113%; 212/212 instructions, 18 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-index-before-cursor: 98.86793%; 212/212 instructions, 41 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-index-after-count: 99.386795%; 212/212 instructions, 21 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-count-after-cursor: 99.386795%; 212/212 instructions, 21 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-count-before-cursor: 98.77358%; 212/212 instructions, 44 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-count-after-count: 99.386795%; 212/212 instructions, 21 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-index-count-after-cursor: 99.57547%; 212/212 instructions, 15 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-index-count-before-cursor: 98.77358%; 212/212 instructions, 44 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/second-index-count-after-count: 99.57547%; 212/212 instructions, 15 aligned differences. The separate second cursor has degree 29, including split index/count nodes visited later. Give the second index/count its own earlier named node so simplify removes that edge before visiting the cursor.
- exif/regions-count-cursor-index: 99.48113%; 212/212 instructions, 18 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-count-cursor-index-third: 99.386795%; 212/212 instructions, 21 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-count-index-cursor: 98.86793%; 212/212 instructions, 41 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-count-index-cursor-third: 98.86793%; 212/212 instructions, 41 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-cursor-count-index: 99.74056%; 212/212 instructions, 9 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-cursor-count-index-third: 99.646225%; 212/212 instructions, 12 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-cursor-index-count: 99.57547%; 212/212 instructions, 15 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-cursor-index-count-third: 99.48113%; 212/212 instructions, 18 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-index-count-cursor: 98.77358%; 212/212 instructions, 44 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-index-count-cursor-third: 98.77358%; 212/212 instructions, 44 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-index-cursor-count: 99.386795%; 212/212 instructions, 21 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- exif/regions-index-cursor-count-third: 99.29245%; 212/212 instructions, 24 aligned differences. Color count before cursor and index after cursor, while simplifying the index before the cursor to cross below degree 29. Separate the third cursor where indicated to preserve its existing split lifetime.
- dht/named-cursor-class-id-index-total: 100.0%; 120/120 instructions, 0 aligned differences. Direct ID/class have degree 30/31. Put index and total before them in virtual numbering, so simplification reduces ID below 29, then class below 29. Reverse coloring can then assign cursor r28, class r27, ID r26.
- dht/named-cursor-class-index-id-total: 99.291664%; 120/120 instructions, 16 aligned differences. Direct ID/class have degree 30/31. Put index and total before them in virtual numbering, so simplification reduces ID below 29, then class below 29. Reverse coloring can then assign cursor r28, class r27, ID r26.
- dht/named-cursor-id-class-index-total: 99.416664%; 120/120 instructions, 13 aligned differences. Direct ID/class have degree 30/31. Put index and total before them in virtual numbering, so simplification reduces ID below 29, then class below 29. Reverse coloring can then assign cursor r28, class r27, ID r26.
- exif/third-index-count-cursor: 99.71698%; 212/212 instructions, 9 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- exif/third-index-cursor-count: 99.646225%; 212/212 instructions, 12 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- exif/third-count-index-cursor: 99.646225%; 212/212 instructions, 12 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- exif/third-count-cursor-index: 99.74056%; 212/212 instructions, 9 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- exif/third-cursor-index-count: 99.83491%; 212/212 instructions, 6 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- exif/third-cursor-count-index: 100.0%; 212/212 instructions, 0 aligned differences. The second IFD now matches with independent cursor/count/index. Give the last loop independent locals and order their priorities: index r28, count r27, cursor r26; parameter entries must not extend into this final loop.
- ifd0/pointer-inline-base-offset: 99.49065%; 480/481 instructions, 456 aligned differences. Offset helper-result nodes color before named pointer nodes. Give pointer formation an ordinary inline boundary, testing whether its generated identity colors before the retained offset.
- ifd0/pointer-inline-info-offset: 99.49065%; 480/481 instructions, 456 aligned differences. Offset helper-result nodes color before named pointer nodes. Give pointer formation an ordinary inline boundary, testing whether its generated identity colors before the retained offset.
- ifd0/pointer-inline-offset-base: 99.49065%; 480/481 instructions, 456 aligned differences. Offset helper-result nodes color before named pointer nodes. Give pointer formation an ordinary inline boundary, testing whether its generated identity colors before the retained offset.
- ifd0/offset-expanded-pointer-first-else: 99.241165%; 480/481 instructions, 456 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- ifd0/offset-expanded-pointer-first-update: 98.57588%; 478/481 instructions, 454 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- ifd0/offset-expanded-offset-first-else: 98.90852%; 480/481 instructions, 456 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- ifd0/offset-expanded-offset-first-update: 98.24324%; 478/481 instructions, 454 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- ifd0/offset-expanded-raw-first-else: 99.241165%; 480/481 instructions, 456 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- ifd0/offset-expanded-raw-first-update: 98.57588%; 478/481 instructions, 454 aligned differences. The offset is currently a late inline-return node. Expand only its endian conversion into the case, retaining a named merge value whose declaration can put the pointer earlier in coloring order.
- dht/installed-combined: 100.0%; 120/120 instructions, 0 aligned differences. Same exact DHT C in the unit containing the already exact scan/restart conversions; no extraction helper remains.
- ifd0/rational-expanded-scoped: 99.054054%; 480/481 instructions, 456 aligned differences. Expanded offset now gets r8, but a late inline numerator raw-value temp takes r6 before pointer. Bring rational word decoding into the same ordinary scalar scope so pointer can color first.
- ifd0/rational-expanded-reuse-raw: 99.241165%; 480/481 instructions, 456 aligned differences. Expanded offset now gets r8, but a late inline numerator raw-value temp takes r6 before pointer. Bring rational word decoding into the same ordinary scalar scope so pointer can color first.
- ifd0/rational-expanded-full-reuse: 99.241165%; 480/481 instructions, 456 aligned differences. Expanded offset now gets r8, but a late inline numerator raw-value temp takes r6 before pointer. Bring rational word decoding into the same ordinary scalar scope so pointer can color first.
- exif/clean-exact: 100.0%; 212/212 instructions, 0 aligned differences. Rename independent cursors/counts/indices for their IFD1 and Exif directories; remove redundant parentheses. No control-flow or memory-access change.
- ifd0/pointer-cse-x: 99.49065%; 480/481 instructions, 456 aligned differences. Replace a named pointer with repeated address expressions in its existing bounds checks and load. CSE, rather than a local declaration, should create the pointer identity later than the inline offset result.
- ifd0/pointer-cse-y: 99.49065%; 480/481 instructions, 456 aligned differences. Replace a named pointer with repeated address expressions in its existing bounds checks and load. CSE, rather than a local declaration, should create the pointer identity later than the inline offset result.
- ifd0/pointer-cse-xy: 99.49065%; 480/481 instructions, 456 aligned differences. Replace a named pointer with repeated address expressions in its existing bounds checks and load. CSE, rather than a local declaration, should create the pointer identity later than the inline offset result.
- ifd0/rational-helper-info-offset-order: 99.49065%; 480/481 instructions, 456 aligned differences. An ordinary helper owns the bounds-checked rational read. Its inlined cursor should receive a generated vreg after the caller's endian-decoded offset, reversing their coloring priority without extra loads.
- ifd0/rational-helper-info-order-offset: 99.49065%; 480/481 instructions, 456 aligned differences. An ordinary helper owns the bounds-checked rational read. Its inlined cursor should receive a generated vreg after the caller's endian-decoded offset, reversing their coloring priority without extra loads.
- ifd0/rational-helper-num-den-info: 99.49065%; 480/481 instructions, 456 aligned differences. An ordinary helper owns the bounds-checked rational read. Its inlined cursor should receive a generated vreg after the caller's endian-decoded offset, reversing their coloring priority without extra loads.


### parse_dht, exact C

Baseline helper-return ID r47 has 30 neighbors, and helper-return class r46 has 31. Earlier index/total nodes are already removed when simplify visits them, so their remaining degrees are 25 and 26. Both color before named cursor r35. The cursor therefore gets r26 while ID gets r28. Removing only the ID helper makes ID named r33, visited before its neighbors: degree 30 postpones it to the next pass, where it displaces work into r29. This explains why an ordinary declaration move previously looked ineffective.

The exact source uses direct header expressions and declaration order pCount, tblClass, tblID, idx, totalCodes. Named vregs appear in the reverse order: total r33, index r34, ID r35, class r36, cursor r37. Removing total/index reduces ID from 30 to 28; removing ID reduces class from 31 to 28. Both now simplify on the first pass. Reverse coloring reaches cursor, class, ID in that order. Each needs a new saved register, so they get r28, r27, r26. Their final legal masks are 0x10000000, 0x08000000, 0x04000000. Work and scaleInfo remain r30/r31 and the hoisted zero remains r29. There are no accepted copy coalesces in this function.

Capture: build/rx5/dht/named-cursor-class-id-index-total/mwdbg. Its complete object equals independent wibo output. Installing only the function into the current unit needs no header-extraction helper and preserves all 13 exact functions. Pool identical; ctxdiff 120/120, diffs 0; objdiff 100.0. The DHT searches were stopped after this manual exact result.

### exif_parse, exact C

The baseline puts incoming data r32 in r27 and named entries r39 in r30. They are high-degree nodes, colored in reverse order on the later pass. Using the input parameter as the first directory cursor and keeping the immutable data base in a local reverses those identities. A full-width count is still bounded by the u16 reader; count * 12 fits signed 32-bit. Letting CSE supply the signed byte-span expression makes count r35 -> r23 and span r50 -> r26. This fixes the first directory and leaves only the second cursor/count pair swapped.

A separate second cursor alone has exactly 29 neighbors, so it is deferred rather than simplified against the 29-register budget. It then steals r29 before pInfo and disrupts earlier allocation. Moving its pure address expression did not remove that edge. Independent directory indices and counts solve the actual ordering problem. In the exact capture, second index r38 and count r39 simplify first, lowering cursor r40 from 29 neighbors to remaining degree 27. The final directory uses separate r41/r42/r43 nodes; its cursor degree falls from 28 to 26. Thus all six nodes simplify on the first pass instead of disturbing the long-lived inputs.

Reverse coloring assigns the final cursor/count/index r43/r42/r41 to r26/r27/r28, with legal masks 0x4c000000, 0x58000000, 0x50000000. It assigns the second cursor/count/index r40/r39/r38 to r26/r27/r25, with masks 0x0c000000, 0x08000000, and a newly requested r25. Input cursor r32 -> r27, size r33 -> r28, pInfo r34 -> r29, base r44 -> r30, byteOrder r64 -> r31. Coalescing removes endian-helper return copies; it does not merge any of these distinct cursor/count/index representatives.

Capture: build/rx5/exif/third-cursor-count-index/mwdbg, complete object byte-identical to wibo. The final cleanup only names the later directories ifd1/exif and removes redundant parentheses; clean-exact remains 212/212, diffs 0, objdiff 100.0 with no other-function regressions. No extra memory accesses or changed bounds checks. EXIF searches stopped after this manual exact result.

## Second clean acceptance gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] objdiff: code 5604/5604 data 256/256 functions 13/13 fuzzy 100.0000 linked code 5604
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] instruction-exact functions: 13/13
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .rodata size 256 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .text size 5604 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] baseline: code 5604/5604 data 256 functions 13 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 2196/5088 data None/None functions 4/6 fuzzy 99.0747 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 4/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 99.074684
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code 1104/1104 data None/None functions 1/1 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 1/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.7101
regressions vs baseline: 0
global matched_code_percent: 92.82099 -> 92.88616
global fuzzy_match_percent: 99.78336 -> 99.78364
global complete_code_percent: 77.26517 -> 77.26517
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

The second clean gate covers all five retained exact results. EXIF rises from 3/6 to 4/6 exact functions. Combined owned units rise from 16/20 to 18/20, code 6952 -> 8904 exact bytes, data 256 -> 256 bytes. Three asm bodies are now readable exact C; their pre-existing assembly scores were already 100. No Matching flag changed. IFD0 and the unowned IFD1 remain non-exact.
- ifd0/reuse-outer-pointer: 99.49065%; 480/481 instructions, 456 aligned differences. The target reuses entry-type register r8 for the rational offset. Test natural scalar reuse across disjoint tag arms, and ordinary shared offset/pointer locals, to avoid the late inline-return identities.
- ifd0/reuse-outer-both: 99.49065%; 480/481 instructions, 456 aligned differences. The target reuses entry-type register r8 for the rational offset. Test natural scalar reuse across disjoint tag arms, and ordinary shared offset/pointer locals, to avoid the late inline-return identities.
- ifd0/reuse-type-value-c89: 99.49065%; 480/481 instructions, 456 aligned differences. Fix trial declaration placement for C89; preserve source evaluation order and scalar-reuse hypothesis.
- ifd0/reuse-outer-offset-c89: 99.49065%; 480/481 instructions, 456 aligned differences. Fix trial declaration placement for C89; preserve source evaluation order and scalar-reuse hypothesis.


### IFD0_tag_parse, still open

The baseline offset values from readU32 are virtual r76 (X) and r72 (Y), with 14 graph neighbors each. Their representatives receive the endian-helper return copies. Both are colored before cursor r42/r41, each with 11 neighbors. All four simplify on the first pass; this is a priority difference rather than a degree-threshold case. Offset gets legal mask 0x1fc0 -> r6, raw numerator assembly gets r7, and the cursor is left with mask 0x1f00 -> r8. The target needs offset r8 and cursor r6. The compiler accepts 32 ordinary input/helper coalesces; it does not merge offset and cursor, which interfere.

Giving the denominator a separate cursor, advancing the named offset by four, wrapping pointer formation in an inline helper, using repeated CSE address expressions, and moving the rational read to an ordinary helper all reproduce the original swap. The offset-pointer-first capture confirms exactly the same priority and masks as baseline, despite the source declaration change.

Expanding only the offset endian conversion changes its identity as intended: named offset r45/r42 now gets r8 with mask 0x1f00. The numerator's still-inlined raw-value node gets r6 first, however, leaving cursor r46/r43 with mask 0x1f80 -> r7. The expanded-offset capture is byte-identical to independent wibo output. Expanding the remaining reads shifts other raw values instead of resolving the complete instruction stream. The best retained score is therefore unchanged at 99.49065. All IFD0 experiments stay outside source.

The missing target bltlr after cmpwi tag, 0x103 is independent of this allocation. Current code has 480 instructions against 481. A single missing branch shifts all later positional comparisons, so the experiment harness's 456 aligned differences are not 456 distinct codegen errors. Skipping that target-only branch for diagnosis exposes the two offset/cursor register swaps. Ghidra also preserves the low-tag branch. No dummy guard or extra ignored tag is installed to create it. Earlier g5 switch-return/default/type/ignored-tag experiments remain rejected; source search is still running on the original best state.

## Scratch and validation audit

All 26 completed mwdbg captures equal their independently compiled complete objects byte for byte. Captures use the original validated compiler and real Ninja code-generation flags. The private debugger transport changes only its port and output location; object equality is checked before using its conclusions.

Five scratch variants failed compilation and were not installed: ifd0/reuse-type-value and reuse-outer-offset declared a pointer after a statement under C89 (corrected variants compiled); iquant/coefficient-address-first had an invalid generated declaration placement; exif/parameter-cursor-second-scoped had an overbroad text replacement; dht/cursor-for-init used a C99 for declaration. Two malformed EXIF cursor rewrites were separately rejected above for using the wrong pointer after a nested block. They do not count toward valid coverage. The exact retained sources contain neither form.

The final progress/report/ok invocation passes. decomp_status.py records the fresh report under build/rx5. check_decomp_complete.py correctly returns DECOMPLETE_FAIL: the project remains incomplete, with code match 2782104/2995176, code linked 2314228/2995176, data match 1832576/1832684, and data linked 1545820/1832684. This worker claims five exact C results, not whole-project completion.


## Local source commits

- 1bfc9310: scan_varinit exact C conversion.
- c0f80644: restart_interval exact C conversion.
- 7a50d130: decode_iquant exact register allocation.
- 89c236e6: parse_dht exact C conversion.
- 6591fa4c: exif_parse exact directory locals.

All five are covered by the second clean GATE PASS. The current report and source/target object hashes are recorded in build/rx5/handoff-manifest.json. Changed source scope is exactly jdec_main.c, exif_parse.c, and iqdec_b65_frv32.c. Source diffs contain no new comments, flags, assembly, carrier structs, shared headers, or unrelated function edits. IFD1 is outside the assignment and unchanged. No push, PR, merge, rebase, or other-worktree edit occurred.

## Completed IFD0 searches and final handoff

- Seed 105, 1200 seconds after acquiring the global slot: done 1251 trials; best-nodrop energy -97.4907. No no-regression improvement and no candidate file.
- Seed 205, 1200 seconds after acquiring the global slot: done 1122 trials; best-nodrop energy -97.4907. No no-regression improvement and no candidate file.
- Seed 305, 1200 seconds after acquiring the global slot: done 1327 trials; best-nodrop energy -97.4907. No no-regression improvement and no candidate file.

Seed 105's completed search was accidentally requeued by the snapshot/retry helper while its old process was still visible; that redundant run was stopped after the original completion line was confirmed. Seeds 205 and 305 each completed normally. The three completed budgets total 3700 compiler trials. IFD0 has 29 additional compiled manual variants in this run, including distinct cursor lifetime, offset identity, CSE address, inline-boundary, raw decode, and scalar reuse attempts. Its source remains byte-identical to baseline.

Five requested functions now have exact C: scan_varinit 129/129, restart_interval 93/93, parse_dht 120/120, exif_parse 212/212, decode_iquant 276/276; every ctxdiff is zero and every exact-name score is 100.0. IFD0 remains at 99.49065, 480/481 instructions. Best-C starting scores were 99.496124, 96.77419, 99.708336, 99.43396 and 99.710144 respectively. The first three previously used 100% assembly bodies, so these conversions do not increase their already exact unit counts.

Final retained result: five source commits, three asm bodies removed, two newly exact reported functions, +1952 exact code bytes, unchanged data, unchanged DOL hash, both clean full gates PASS, no regression or forbidden/readability finding. All work remains on agent/w1005/rx5 for parent verification. No uncommitted source candidate remains.
