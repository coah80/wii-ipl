# da4 de-asm attempts

Scope: jdec_main, getcode, mkhdec3, iqdec_resolution_change_a3 in this worktree only.
Baseline: 7aa71d2930ed6d903fa00eff756f97f75a11a82d; origin/main 7aa71d2930ed6d903fa00eff756f97f75a11a82d.
Acceptance: readable C, exact-name objdiff 100%, ctxdiff zero differences, identical pool, full gate and retail DOL SHA1. Each converted function gets a separate commit.
Prior trials: tools/decomp-assist/asm-conversions.attempts.md, lines 450-538.


TMCJPEGDEC_init_buff_thumbnail / getcode1: Existing array C baseline, compare to Ghidra before rewriting typed input.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x88 base 0x88 insns 34/34; diffs 3: [24, 25, 26]; objdiff 99.55882. Evidence: /tmp/da4/getcode1.

TMCJPEGDEC_init_buff_thumbnail / getcode2: Typed input buffer, destination work and EXIF fields. Ghidra stores remaining before end and mark.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x88 base 0x88 insns 34/34; diffs 4: [24, 25, 26, 28]; objdiff 99.26471. Evidence: /tmp/da4/getcode2.

TMCJPEGDEC_init_buff_thumbnail / getcode3: Separate current pointer, preserving buffer assignment and subsequent pointer lifetime.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x88 base 0x88 insns 34/34; diffs 4: [24, 25, 26, 28]; objdiff 99.26471. Evidence: /tmp/da4/getcode3.

TMCJPEGDEC_imagestart / imagestart1: Natural 64-element zigzag loop with shared result exit matching Ghidra branches.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x18c base 0x190 insns 99/100; --- replace mine 2:3 base 2:3; objdiff 93.3. Evidence: /tmp/da4/imagestart1.

TMCJPEGDEC_imagestart / imagestart2: Named zigzag walker and explicit else branches as in matched buffer_system.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x188 base 0x190 insns 98/100; --- replace mine 2:3 base 2:3; objdiff 95.5. Evidence: /tmp/da4/imagestart2.

TMCJPEGDEC_init_buff_thumbnail / getcode4: Reuse pointer for thumbnail start and end, allocator lever 18b.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x88 base 0x88 insns 34/34; diffs 6: [24, 25, 26, 28, 30, 31]; objdiff 98.82353. Evidence: /tmp/da4/getcode4.

TMCJPEGDEC_imagestart / imagestart3: Ghidra nested successful parse paths; named walker before index declaration.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x18c base 0x190 insns 99/100; --- replace mine 7:8 base 7:8; objdiff 94.35. Evidence: /tmp/da4/imagestart3.

TMCJPEGDEC_init_buff_thumbnail / getcode5: Commuted thumbnail offset/length addition.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x88 base 0x88 insns 34/34; diffs 4: [24, 25, 26, 28]; objdiff 99.26471. Evidence: /tmp/da4/getcode5.
TMCJPEGDEC_imagestart / image-l0-f0: Named/indexed zigzag loop; error exit form 0; instructions 100/100, aligned differences 40.
TMCJPEGDEC_init_buff_thumbnail / get-False-0-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-l0-f1: Named/indexed zigzag loop; error exit form 1; instructions 98/100, aligned differences 67.
TMCJPEGDEC_imagestart / image-l0-f2: Named/indexed zigzag loop; error exit form 2; instructions 98/100, aligned differences 67.
TMCJPEGDEC_init_buff_thumbnail / get-False-0-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-l0-f3: Named/indexed zigzag loop; error exit form 3; instructions 100/100, aligned differences 40.
TMCJPEGDEC_init_buff_thumbnail / get-False-1-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 6.
TMCJPEGDEC_imagestart / image-l1-f0: Named/indexed zigzag loop; error exit form 0; instructions 100/100, aligned differences 40.
TMCJPEGDEC_init_buff_thumbnail / get-False-1-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 6.
TMCJPEGDEC_imagestart / image-l1-f1: Named/indexed zigzag loop; error exit form 1; instructions 98/100, aligned differences 67.
TMCJPEGDEC_init_buff_thumbnail / get-False-2-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-l1-f2: Named/indexed zigzag loop; error exit form 2; instructions 98/100, aligned differences 67.
TMCJPEGDEC_init_buff_thumbnail / get-False-2-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-False-3-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 3.
TMCJPEGDEC_imagestart / image-l1-f3: Named/indexed zigzag loop; error exit form 3; instructions 100/100, aligned differences 40.
TMCJPEGDEC_imagestart / image-l2-f0: Named/indexed zigzag loop; error exit form 0; instructions 100/100, aligned differences 21.
TMCJPEGDEC_imagestart / image-l2-f1: Named/indexed zigzag loop; error exit form 1; instructions 98/100, aligned differences 48.
TMCJPEGDEC_init_buff_thumbnail / get-False-3-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 3.
TMCJPEGDEC_imagestart / image-l2-f2: Named/indexed zigzag loop; error exit form 2; instructions 98/100, aligned differences 48.
TMCJPEGDEC_init_buff_thumbnail / get-False-4-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-l2-f3: Named/indexed zigzag loop; error exit form 3; instructions 100/100, aligned differences 21.
TMCJPEGDEC_init_buff_thumbnail / get-False-4-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-True-0-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-l3-f0: Named/indexed zigzag loop; error exit form 0; instructions 100/100, aligned differences 40.
TMCJPEGDEC_init_buff_thumbnail / get-True-0-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-True-1-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 6.
TMCJPEGDEC_imagestart / image-l3-f1: Named/indexed zigzag loop; error exit form 1; instructions 98/100, aligned differences 67.
TMCJPEGDEC_init_buff_thumbnail / get-True-1-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 6.
TMCJPEGDEC_imagestart / image-l3-f2: Named/indexed zigzag loop; error exit form 2; instructions 98/100, aligned differences 67.
TMCJPEGDEC_imagestart / image-l3-f3: Named/indexed zigzag loop; error exit form 3; instructions 100/100, aligned differences 40.
TMCJPEGDEC_init_buff_thumbnail / get-True-2-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-True-2-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-True-3-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-True-3-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-True-4-False: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-True-4-True: Typed pointer/integer source arithmetic and named length; instructions 34/34, aligned differences 4.

TMCJPEGDEC_scan_varinit / scan1: Frame member view and direct sampling array access, lever 16.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x204 base 0x204 insns 129/129; diffs 9: [8, 9, 10, 11, 12, 13, 15, 20, 21]; objdiff 99.496124. Evidence: /tmp/da4/scan1.
TMCJPEGDEC_scan_varinit / scan-decls-0: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-1: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-2: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-3: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-4: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-5: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-6: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-decls-7: Sample/scale/table/index role declaration order; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-inline: Inline boundary for single-component geometry; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-direct-0: Remove sample temporaries and test arithmetic width; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-direct-1: Remove sample temporaries and test arithmetic width; instructions 129/129, aligned differences 9.

TMCJPEGDEC_imagestart / imagestart4: Minimal named walker loop with direct error returns.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x190 base 0x190 insns 100/100; diffs 21: [7, 14, 16, 19, 23, 26, 29, 32, 35, 38, 41, 42, 45, 46, 49, 52, 55, 58, 61, 64]; objdiff 98.75. Evidence: /tmp/da4/imagestart4.
TMCJPEGDEC_scan_varinit / scan-direct-2: Remove sample temporaries and test arithmetic width; instructions 129/129, aligned differences 9.
TMCJPEGDEC_init_buff_thumbnail / get-offset-0: Named offset reused as thumbnail address; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-offset-1: Named offset reused as thumbnail address; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-offset-2: Named offset reused as thumbnail address; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-offset-3: Named offset reused as thumbnail address; instructions 34/34, aligned differences 8.
TMCJPEGDEC_init_buff_thumbnail / get-offset-4: Named offset reused as thumbnail address; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-offset-5: Named offset reused as thumbnail address; instructions 34/34, aligned differences 8.
TMCJPEGDEC_init_buff_thumbnail / get-inline: Inline EXIF start calculation; instructions 34/34, aligned differences 4.
TMCJPEGDEC_imagestart / image-inline-0: Inline zigzag initialization; instructions 100/100, aligned differences 0.
TMCJPEGDEC_restart_interval / restart-0: Direct error returns, Ghidra integer-width truncation and coordinate order; instructions 93/93, aligned differences 26.
TMCJPEGDEC_restart_interval / restart-1: Direct error returns, Ghidra integer-width truncation and coordinate order; instructions 93/93, aligned differences 26.
TMCJPEGDEC_restart_interval / restart-2: Direct error returns, Ghidra integer-width truncation and coordinate order; instructions 94/93, aligned differences 44.
TMCJPEGDEC_restart_interval / restart-3: Direct error returns, Ghidra integer-width truncation and coordinate order; instructions 94/93, aligned differences 45.

Accepted TMCJPEGDEC_imagestart: inline initialization of zigzag bytes removes the iterator/base register swap; plain C loop, no forced instructions. ctxdiff 100/100 instructions, diffs 0; exact-name objdiff 100.0; .text 5604/5604, .rodata 256/256, functions 13/13. Full clean gate passed, 0 regressions, 0 forbidden patterns, 0 readability warnings. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Gate evidence /tmp/da4/imagestart-gate.log.
TMCJPEGDEC_parse_para / para-nested: Nested underflow/EOI error paths as target; instructions 178/183, aligned differences 116.
TMCJPEGDEC_parse_para / para-helpers-0: Inline segment parsers, nested successful byte-reader returns; instructions 184/183, aligned differences 165.
TMCJPEGDEC_parse_para / para-helpers-1: Inline segment parsers, nested successful byte-reader returns; instructions 184/183, aligned differences 165.
TMCJPEGDEC_parse_para / para-helpers-2: Inline segment parsers, nested successful byte-reader returns; instructions 184/183, aligned differences 165.
TMCJPEGDEC_parse_para / para-helpers-3: Inline segment parsers, nested successful byte-reader returns; instructions 184/183, aligned differences 165.
TMCJPEGDEC_parse_dht / dht-0: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-1: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-2: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-3: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-4: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-5: Count loop, typed header fields, or inline symbol-count helper; instructions 120/120, aligned differences 34.

TMCJPEGDEC_parse_para / para-current: Inline segment-parser candidate after nested error checks.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x2e0 base 0x2dc insns 184/183; --- replace mine 14:15 base 14:15; objdiff 99.45355. Evidence: /tmp/da4/para-current.

TMCJPEGDEC_decode_iquant_rc / iquant1: Typed coefficient/Huffman indexing follows target Ghidra data flow.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x29c base 0x29c insns 167/167; diffs 15: [51, 52, 53, 54, 55, 56, 76, 78, 79, 132, 134, 136, 139, 142, 147]; objdiff 99.461075. Evidence: /tmp/da4/iquant1.

TMCJPEGDEC_parse_para / para2: Inline segment parsers with combined underflow and EOI exception.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x2dc base 0x2dc insns 183/183; diffs 0: []; objdiff 100.0. Evidence: /tmp/da4/para2.
TMCJPEGDEC_decode_iquant_rc / iquant-0: Direct zigzag access, pointer declaration lifetime, bit-position width or shift type; instructions 167/167, aligned differences 73.
TMCJPEGDEC_decode_iquant_rc / iquant-1: Direct zigzag access, pointer declaration lifetime, bit-position width or shift type; instructions 167/167, aligned differences 36.
TMCJPEGDEC_decode_iquant_rc / iquant-2: Direct zigzag access, pointer declaration lifetime, bit-position width or shift type; instructions 167/167, aligned differences 15.
TMCJPEGDEC_decode_iquant_rc / iquant-3: Direct zigzag access, pointer declaration lifetime, bit-position width or shift type; instructions 167/167, aligned differences 15.
TMCJPEGDEC_decode_iquant_rc / iquant-inline-0: Inline coefficient sign-extension helper; instructions 167/167, aligned differences 77.
TMCJPEGDEC_decode_iquant_rc / iquant-inline-1: Inline coefficient sign-extension helper; instructions 167/167, aligned differences 7.
TMCJPEGDEC_parse_sos / sos-0: Typed component view, mapping stored after successful search and early scan count store; instructions 114/112, aligned differences 90.
TMCJPEGDEC_parse_sos / sos-1: Typed component view, mapping stored after successful search and early scan count store; instructions 114/112, aligned differences 90.
TMCJPEGDEC_parse_sos / sos-2: Typed component view, mapping stored after successful search and early scan count store; instructions 114/112, aligned differences 90.
TMCJPEGDEC_parse_sos / sos-3: Typed component view, mapping stored after successful search and early scan count store; instructions 112/112, aligned differences 56.
TMCJPEGDEC_scan_varinit / scan-more-0: Sampling pair aggregate, arithmetic inline boundary, or coefficient row view; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-more-1: Sampling pair aggregate, arithmetic inline boundary, or coefficient row view; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-more-2: Sampling pair aggregate, arithmetic inline boundary, or coefficient row view; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-more-3: Sampling pair aggregate, arithmetic inline boundary, or coefficient row view; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-more-4: Sampling pair aggregate, arithmetic inline boundary, or coefficient row view; instructions 129/129, aligned differences 9.
TMCJPEGDEC_err_restart / err-0: Unsigned next-position division and target final posX subtraction; coordinate arithmetic forms; instructions 113/115, aligned differences 71.
TMCJPEGDEC_make_huffdec / mkhdec-0: Ghidra canonical Huffman sizes/codes, typed halfword entries, signed counter loop forms; instructions 193/200, aligned differences 177.
TMCJPEGDEC_err_restart / err-1: Unsigned next-position division and target final posX subtraction; coordinate arithmetic forms; instructions 113/115, aligned differences 71.
TMCJPEGDEC_make_huffdec / mkhdec-1: Ghidra canonical Huffman sizes/codes, typed halfword entries, signed counter loop forms; instructions 195/200, aligned differences 174.
TMCJPEGDEC_make_huffdec / mkhdec-2: Ghidra canonical Huffman sizes/codes, typed halfword entries, signed counter loop forms; instructions 193/200, aligned differences 177.
TMCJPEGDEC_err_restart / err-2: Unsigned next-position division and target final posX subtraction; coordinate arithmetic forms; instructions 113/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-3: Unsigned next-position division and target final posX subtraction; coordinate arithmetic forms; instructions 113/115, aligned differences 71.
TMCJPEGDEC_make_huffdec / mkhdec-3: Ghidra canonical Huffman sizes/codes, typed halfword entries, signed counter loop forms; instructions 193/200, aligned differences 177.
TMCJPEGDEC_err_restart / err-4: Unsigned next-position division and target final posX subtraction; coordinate arithmetic forms; instructions 113/115, aligned differences 71.
TMCJPEGDEC_make_huffdec / mkhdec-4: Ghidra canonical Huffman sizes/codes, typed halfword entries, signed counter loop forms; instructions 193/200, aligned differences 177.
TMCJPEGDEC_parse_sos / sos-corrected-0: Correct target component-found branch and re-read stored scan count; instructions 112/112, aligned differences 0.

Accepted TMCJPEGDEC_parse_para: inline helpers for APP, DRI, DNL and COM parsing recreate separate stack locals and error-return paths. Segment-skip helper provides the two nested success clamps without bitwise result tricks. Combined underflow/EOI exception matches the final branch. Exact-name objdiff 100.0; ctxdiff 183/183, diffs 0. Full clean GATE PASS, 0 regressions/patterns/readability warnings, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Evidence /tmp/da4/para-gate.log.

TMCJPEGDEC_parse_sos / sos-exact: Matched typed component table and component-found control flow.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x1c0 base 0x1c0 insns 112/112; diffs 0: []; objdiff 100.0. Evidence: /tmp/da4/sos-exact.
TMCJPEGDEC_decode_iquant_rc / iquant-more-0: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-more-1: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-more-2: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-more-3: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-more-4: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-more-5: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_err_restart / err-corrected-0: Marker loop exits before recovery; 16-bit position locals and target grouped sum; instructions 114/115, aligned differences 72.
TMCJPEGDEC_decode_iquant_rc / iquant-more-6: Independent AC value lifetime, signedness, inline parameter const or indexed product form; instructions 167/167, aligned differences 7.
TMCJPEGDEC_err_restart / err-corrected-1: Marker loop exits before recovery; 16-bit position locals and target grouped sum; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-corrected-2: Marker loop exits before recovery; 16-bit position locals and target grouped sum; instructions 113/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-corrected-3: Marker loop exits before recovery; 16-bit position locals and target grouped sum; instructions 114/115, aligned differences 72.
TMCJPEGDEC_parse_sof / sof-0: Ghidra reused byte/word inputs, full sampling search, and inferred coordinate widths; instructions 219/223, aligned differences 203.
TMCJPEGDEC_parse_sof / sof-1: Ghidra reused byte/word inputs, full sampling search, and inferred coordinate widths; instructions 219/223, aligned differences 203.
TMCJPEGDEC_parse_sof / sof-2: Ghidra reused byte/word inputs, full sampling search, and inferred coordinate widths; instructions 221/223, aligned differences 205.
TMCJPEGDEC_parse_sof / sof-3: Ghidra reused byte/word inputs, full sampling search, and inferred coordinate widths; instructions 219/223, aligned differences 203.
TMCJPEGDEC_decode_iquant_rc / iquant-final-0: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-final-1: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-final-2: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 8.
TMCJPEGDEC_decode_iquant_rc / iquant-final-3: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-final-4: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 7.
TMCJPEGDEC_decode_iquant_rc / iquant-final-5: AC store inline, output-reference value, reused coefficient, mask width or explicit AC block; instructions 167/167, aligned differences 71.
TMCJPEGDEC_parse_dht / dht-more-0: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-more-1: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-more-2: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-more-3: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-more-4: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-more-5: Header-local lifetime, narrowed table ID or inline nibble extraction; instructions 120/120, aligned differences 9.
TMCJPEGDEC_restart_interval / restart-more-0: Natural marker local and inline position update; instructions 93/93, aligned differences 23.
TMCJPEGDEC_restart_interval / restart-more-1: Natural marker local and inline position update; instructions 93/93, aligned differences 26.
TMCJPEGDEC_restart_interval / restart-more-2: Natural marker local and inline position update; instructions 93/93, aligned differences 26.
TMCJPEGDEC_restart_interval / restart-more-3: Natural marker local and inline position update; instructions 93/93, aligned differences 20.
TMCJPEGDEC_restart_interval / restart-more-4: Natural marker local and inline position update; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-more-5: Natural marker local and inline position update; instructions 93/93, aligned differences 20.

Accepted TMCJPEGDEC_parse_sos: reused stored scan count, typed component-table view, and explicit component-found error path. Ghidra mapping loop checks were verified against original instructions. Exact-name objdiff 100.0, ctxdiff 112/112 diffs 0. Full clean GATE PASS; 0 regressions/patterns/readability warnings; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Evidence /tmp/da4/sos-gate.log.
TMCJPEGDEC_parse_dht / dht-final-0: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 30.
TMCJPEGDEC_parse_dht / dht-final-1: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-final-2: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-final-3: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.
TMCJPEGDEC_make_huffdec / mkhdec-scopes-0: Independent locals per Huffman sizes, codes, valptr and lookup phases; instructions 195/200, aligned differences 174.
TMCJPEGDEC_make_huffdec / mkhdec-scopes-1: Independent locals per Huffman sizes, codes, valptr and lookup phases; instructions 198/200, aligned differences 136.
TMCJPEGDEC_parse_dht / dht-final-4: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.
TMCJPEGDEC_make_huffdec / mkhdec-scopes-2: Independent locals per Huffman sizes, codes, valptr and lookup phases; instructions 195/200, aligned differences 171.
TMCJPEGDEC_parse_dht / dht-final-5: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.
TMCJPEGDEC_make_huffdec / mkhdec-scopes-3: Independent locals per Huffman sizes, codes, valptr and lookup phases; instructions 195/200, aligned differences 174.
TMCJPEGDEC_parse_dht / dht-final-6: Header scalar versus walker lifetime and grouped decoded table fields; instructions 121/120, aligned differences 107.
TMCJPEGDEC_parse_dht / dht-final-7: Header scalar versus walker lifetime and grouped decoded table fields; instructions 120/120, aligned differences 9.

TMCJPEGDEC_parse_sof / sof-current: Shared byte/word temporaries and 16-bit MCU counts, full sampling search.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x374 base 0x37c insns 221/223; --- replace mine 3:6 base 3:7; objdiff 82.28251. Evidence: /tmp/da4/sof-current.
TMCJPEGDEC_init_buff_thumbnail / get-final-0: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-final-1: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-final-2: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-final-3: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-final-4: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-final-5: Reuse source/start pointer parameter or group thumbnail pointers; instructions 34/34, aligned differences 4.
TMCJPEGDEC_parse_sof / sof-corrected-0: Typed component base, 16-bit maximum sampling, shared scalar input, inline validation; instructions 220/223, aligned differences 140.
TMCJPEGDEC_parse_sof / sof-corrected-1: Typed component base, 16-bit maximum sampling, shared scalar input, inline validation; instructions 222/223, aligned differences 142.
TMCJPEGDEC_parse_sof / sof-corrected-2: Typed component base, 16-bit maximum sampling, shared scalar input, inline validation; instructions 222/223, aligned differences 142.
TMCJPEGDEC_parse_sof / sof-corrected-3: Typed component base, 16-bit maximum sampling, shared scalar input, inline validation; instructions 222/223, aligned differences 142.
TMCJPEGDEC_make_huffdec / mkhdec-final-0: Huffman phase declaration order and indexed versus walking table entries; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkhdec-final-1: Huffman phase declaration order and indexed versus walking table entries; instructions 198/200, aligned differences 136.
TMCJPEGDEC_make_huffdec / mkhdec-final-2: Huffman phase declaration order and indexed versus walking table entries; instructions 175/200, aligned differences 115.
TMCJPEGDEC_make_huffdec / mkhdec-final-3: Huffman phase declaration order and indexed versus walking table entries; instructions 196/200, aligned differences 134.
TMCJPEGDEC_make_huffdec / mkhdec-final-4: Huffman phase declaration order and indexed versus walking table entries; instructions 196/200, aligned differences 134.
TMCJPEGDEC_init_buff_thumbnail / get-helper-0: Inline input copy/validation or thumbnail-buffer initialization; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-helper-1: Inline input copy/validation or thumbnail-buffer initialization; instructions 39/34, aligned differences 25.
TMCJPEGDEC_init_buff_thumbnail / get-helper-2: Inline input copy/validation or thumbnail-buffer initialization; instructions 34/34, aligned differences 4.
TMCJPEGDEC_parse_sof / sof-last-0: Explicit quotient arithmetic or inline sampling-layout search; instructions 222/223, aligned differences 142.
TMCJPEGDEC_parse_sof / sof-last-1: Explicit quotient arithmetic or inline sampling-layout search; instructions 222/223, aligned differences 143.
TMCJPEGDEC_parse_sof / sof-last-2: Explicit quotient arithmetic or inline sampling-layout search; instructions 222/223, aligned differences 143.
TMCJPEGDEC_parse_sof / sof-last-3: Explicit quotient arithmetic or inline sampling-layout search; instructions 222/223, aligned differences 143.
TMCJPEGDEC_scan_varinit / scan-pair-0: Named promoted horizontal/vertical scales, direct coefficient access; instructions 129/129, aligned differences 11.
TMCJPEGDEC_scan_varinit / scan-pair-1: Named promoted horizontal/vertical scales, direct coefficient access; instructions 129/129, aligned differences 14.
TMCJPEGDEC_scan_varinit / scan-width-0: Sampling scale width or direct component index; instructions 129/129, aligned differences 14.
TMCJPEGDEC_scan_varinit / scan-width-1: Sampling scale width or direct component index; instructions 131/129, aligned differences 122.

TMCJPEGDEC_parse_sof / sof2-current: Typed component base, constrained sampling maxima, and inline validation.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x378 base 0x37c insns 222/223; --- replace mine 5:7 base 5:7; objdiff 93.34529. Evidence: /tmp/da4/sof2-current.
TMCJPEGDEC_scan_varinit / scan-width-2: Sampling scale width or direct component index; instructions 129/129, aligned differences 11.
TMCJPEGDEC_make_huffdec / mkhdec-helper-0: Halfword arrays, countdown condition, or size-table inline helper; instructions 198/200, aligned differences 136.
TMCJPEGDEC_make_huffdec / mkhdec-helper-1: Halfword arrays, countdown condition, or size-table inline helper; instructions 196/200, aligned differences 134.
TMCJPEGDEC_make_huffdec / mkhdec-helper-2: Halfword arrays, countdown condition, or size-table inline helper; instructions 158/200, aligned differences 98.
TMCJPEGDEC_make_huffdec / mkhdec-helper-3: Halfword arrays, countdown condition, or size-table inline helper; instructions 204/200, aligned differences 177.
TMCJPEGDEC_init_buff_thumbnail / get-typed-0: Typed EXIF/input buffer helper behind existing public ABI; instructions 35/34, aligned differences 25.
TMCJPEGDEC_init_buff_thumbnail / get-typed-1: Typed EXIF/input buffer helper behind existing public ABI; instructions 35/34, aligned differences 25.
TMCJPEGDEC_init_buff_thumbnail / get-typed-2: Typed EXIF/input buffer helper behind existing public ABI; instructions 35/34, aligned differences 25.
TMCJPEGDEC_init_buff_thumbnail / get-typed-3: Typed EXIF/input buffer helper behind existing public ABI; instructions 35/34, aligned differences 25.
TMCJPEGDEC_init_buff_thumbnail / get-typed-4: Typed EXIF/input buffer helper behind existing public ABI; instructions 35/34, aligned differences 25.
TMCJPEGDEC_parse_dht / dht-boundary-0: Count-read inline boundary, decoded header outputs or typed internal table parser; instructions 124/120, aligned differences 79.
TMCJPEGDEC_parse_dht / dht-boundary-1: Count-read inline boundary, decoded header outputs or typed internal table parser; instructions 120/120, aligned differences 16.
TMCJPEGDEC_err_restart / err-final-0: Independent full-width division/remainder and narrowed restart-step/position lifetimes; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-final-1: Independent full-width division/remainder and narrowed restart-step/position lifetimes; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-final-2: Independent full-width division/remainder and narrowed restart-step/position lifetimes; instructions 115/115, aligned differences 39.
TMCJPEGDEC_err_restart / err-final-3: Independent full-width division/remainder and narrowed restart-step/position lifetimes; instructions 114/115, aligned differences 72.
TMCJPEGDEC_init_buff_thumbnail / get-arith-0: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-arith-1: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 8.
TMCJPEGDEC_init_buff_thumbnail / get-arith-2: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-arith-3: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-arith-4: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-arith-5: Address assignment expression or independent length/current/end values; instructions 34/34, aligned differences 4.
TMCJPEGDEC_parse_dht / dht-walker-0: Narrowed inline return, count-array start inline or direct indexing; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-walker-1: Narrowed inline return, count-array start inline or direct indexing; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-walker-2: Narrowed inline return, count-array start inline or direct indexing; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-walker-3: Narrowed inline return, count-array start inline or direct indexing; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-walker-4: Narrowed inline return, count-array start inline or direct indexing; instructions 120/120, aligned differences 9.
TMCJPEGDEC_init_buff_thumbnail / get-view-0: EXIF triple array view or explicit current address with existing word-buffer representation; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-view-1: EXIF triple array view or explicit current address with existing word-buffer representation; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-view-2: EXIF triple array view or explicit current address with existing word-buffer representation; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-view-3: EXIF triple array view or explicit current address with existing word-buffer representation; instructions 34/34, aligned differences 3.
TMCJPEGDEC_restart_interval / restart-final-0: Original block-scoped marker reset and field loads with corrected truncation points; instructions 94/93, aligned differences 42.
TMCJPEGDEC_restart_interval / restart-final-1: Original block-scoped marker reset and field loads with corrected truncation points; instructions 93/93, aligned differences 23.

Search tooling: copied srcsearch.py to /tmp/da4/srcsearch.py with definition-only function discovery. Stock finder could select a forward declaration or call before the definition. Shared source-search concurrency limit retained. Initial thumbnail search completed 154 trials with no gain; scan_varinit search completed 239 trials with no gain. Later searches queued behind all 24 shared slots, rather than increasing the limiter.
TMCJPEGDEC_restart_interval / restart-final-2: Original block-scoped marker reset and field loads with corrected truncation points; instructions 93/93, aligned differences 23.
TMCJPEGDEC_restart_interval / restart-final-3: Original block-scoped marker reset and field loads with corrected truncation points; instructions 94/93, aligned differences 53.
TMCJPEGDEC_parse_sof / sof-types-0: Sampling maxima declared before persistent pointers; zero checks narrow as target proves; instructions 222/223, aligned differences 129.
TMCJPEGDEC_parse_sof / sof-types-1: Sampling maxima declared before persistent pointers; zero checks narrow as target proves; instructions 222/223, aligned differences 135.
TMCJPEGDEC_parse_sof / sof-types-2: Sampling maxima declared before persistent pointers; zero checks narrow as target proves; instructions 222/223, aligned differences 143.
TMCJPEGDEC_parse_dht / dht-types-0: Decoded class/ID order and walker lifetime around count summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_sof / sof-types-3: Sampling maxima declared before persistent pointers; zero checks narrow as target proves; instructions 222/223, aligned differences 129.
TMCJPEGDEC_parse_dht / dht-types-1: Decoded class/ID order and walker lifetime around count summation; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-types-2: Decoded class/ID order and walker lifetime around count summation; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-types-3: Decoded class/ID order and walker lifetime around count summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-types-4: Decoded class/ID order and walker lifetime around count summation; instructions 120/120, aligned differences 6.

TMCJPEGDEC_parse_sof / sof-unsized: Unsized local extern declaration, target materializes sample-count table with lis/addi.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x378 base 0x37c insns 222/223; --- replace mine 12:13 base 12:13; objdiff 94.37668. Evidence: /tmp/da4/sof-unsized.
TMCJPEGDEC_init_buff_thumbnail / get-fields-0: Explicit current/end pointer fields or indexed thumbnail offset; instructions 35/34, aligned differences 11.
TMCJPEGDEC_init_buff_thumbnail / get-fields-1: Explicit current/end pointer fields or indexed thumbnail offset; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-fields-2: Explicit current/end pointer fields or indexed thumbnail offset; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-fields-3: Explicit current/end pointer fields or indexed thumbnail offset; instructions 35/34, aligned differences 12.

Restored all unaccepted worktree C candidates to the last validated commits while searches continue from isolated snapshots. No source change is being kept at a fuzzy-only score. The failed whole-parser inline trial removed the static parse_dht symbol and was rejected immediately.
TMCJPEGDEC_parse_sof / sof-incomplete-array: Diagnostic: incomplete SampleComps extern declaration matches target lis/addi instead of SDA reference; isolated temporary header; instructions 223/223, aligned differences 84.
TMCJPEGDEC_init_buff_thumbnail / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 34/34, aligned differences 3.
TMCJPEGDEC_scan_varinit / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 129/129, aligned differences 9.
TMCJPEGDEC_restart_interval / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 93/93, aligned differences 17.
TMCJPEGDEC_parse_dht / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_sof / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 222/223, aligned differences 129.
TMCJPEGDEC_err_restart / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 115/115, aligned differences 39.
TMCJPEGDEC_make_huffdec / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 198/200, aligned differences 133.
TMCJPEGDEC_decode_iquant_rc / handoff-evidence: Representative rejected C candidate for persistent-worker handoff; instructions 167/167, aligned differences 7.

Unconverted function handoff evidence, all candidates rejected and original asm retained:
- TMCJPEGDEC_init_buff_thumbnail: C objdiff 99.55882; instruction delta 0, aligned differences 3; source /tmp/da4/TMCJPEGDEC_init_buff_thumbnail-variants/get-view-0.c.
- TMCJPEGDEC_scan_varinit: C objdiff 99.496124; instruction delta 0, aligned differences 9; source /tmp/da4/TMCJPEGDEC_scan_varinit-variants/scan-decls-0.c.
- TMCJPEGDEC_restart_interval: C objdiff 96.77419; instruction delta 0, aligned differences 17; source /tmp/da4/TMCJPEGDEC_restart_interval-variants/restart-more-4.c.
- TMCJPEGDEC_parse_dht: C objdiff 99.708336; instruction delta 0, aligned differences 6; source /tmp/da4/TMCJPEGDEC_parse_dht-variants/dht-types-0.c.
- TMCJPEGDEC_parse_sof: C objdiff 94.37668; instruction delta -1, aligned differences 129; source /tmp/da4/TMCJPEGDEC_parse_sof-variants/sof-types-0.c.
- TMCJPEGDEC_err_restart: C objdiff 78.33044; instruction delta 0, aligned differences 39; source /tmp/da4/TMCJPEGDEC_err_restart-variants/err-final-2.c.
- TMCJPEGDEC_make_huffdec: C objdiff 78.43; instruction delta -2, aligned differences 133; source /tmp/da4/TMCJPEGDEC_make_huffdec-variants/mkhdec-final-0.c.
- TMCJPEGDEC_decode_iquant_rc: C objdiff 99.76048; instruction delta 0, aligned differences 7; source /tmp/da4/TMCJPEGDEC_decode_iquant_rc-variants/iquant-inline-1.c.

Final retained state

Converted: TMCJPEGDEC_imagestart (014a5167), TMCJPEGDEC_parse_para (f518779c), TMCJPEGDEC_parse_sos (a6b74133). Each received an independent clean gate before its separate commit.
Every other assigned function remains original assembly, unresolved rather than classified as legitimate vendor assembly. No target instruction requires retaining assembly; the remaining problem is reproducing compiler output in C.
Compiled source trials by function: TMCJPEGDEC_init_buff_thumbnail=61, TMCJPEGDEC_imagestart=21, TMCJPEGDEC_scan_varinit=24, TMCJPEGDEC_restart_interval=15, TMCJPEGDEC_parse_para=7, TMCJPEGDEC_parse_dht=33, TMCJPEGDEC_decode_iquant_rc=21, TMCJPEGDEC_parse_sos=6, TMCJPEGDEC_err_restart=14, TMCJPEGDEC_make_huffdec=19, TMCJPEGDEC_parse_sof=21. All eight unconverted functions have at least three distinct compiled source attempts.
Useful continuation findings: init_buff_thumbnail receives EXIF data through its legacy work pointer. make_huffdec valptr contains 16-bit code/index pairs; its fallback byte stores are wrong. parse_sof reuses one byte and one word input variable, scans all sample layouts, and materializes SampleComps with lis/addi. An isolated unsized-extern header diagnostic restores 223 instructions but leaves 84 register/order differences, so no header change was retained. err_restart final subtraction reads posX, not posY, and original division is signed despite Ghidra guessing unsigned.
Applicable levers covered: inline helpers; signedness and widths; const pointers/parameters; separate or reused locals; declaration order; block scopes; counted loops; source search; direct array access; Ghidra and allocator/copy-lifetime hypotheses. eZiText-only spellings, thunk ordering and aggregate/global section boundaries do not apply to these functions. Prior-art gh search was excluded by the worker no-gh contract. No compiler/version flag sweep, new asm, use-site volatile, register keyword, pinned label or shared-layout trick was retained.

Final clean verification

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] objdiff: code 5604/5604 data 256/256 functions 13/13 fuzzy 100.0000 linked code 5604
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] instruction-exact functions: 13/13
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .rodata size 256 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .text size 5604 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] baseline: code 5604/5604 data 256 functions 13 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] objdiff: code 316/316 data None/None functions 3/3 fuzzy 100.0000 linked code 316
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] instruction-exact functions: 3/3
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode]   section .text size 316 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] baseline: code 316/316 data None functions 3 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3] objdiff: code 1228/1228 data None/None functions 2/2 fuzzy 100.0000 linked code 1228
[libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3] instruction-exact functions: 2/2
[libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3]   section .text size 1228 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3] baseline: code 1228/1228 data None functions 2 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] objdiff: code 908/908 data None/None functions 2/2 fuzzy 100.0000 linked code 908
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] instruction-exact functions: 2/2
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3]   section .text size 908 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] baseline: code 908/908 data None functions 2 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Search completion and resource limit

getcode-search:
```
target counts {'TMCJPEGDEC_init_buff_thumbnail': 34} start {'TMCJPEGDEC_init_buff_thumbnail': 34} {'TMCJPEGDEC_init_buff_thumbnail': 99.26471}
done 154 trials; best-nodrop energy -99.2647
```
scan-search:
```
target counts {'TMCJPEGDEC_scan_varinit': 129} start {'TMCJPEGDEC_scan_varinit': 129} {'TMCJPEGDEC_scan_varinit': 99.496124}
done 239 trials; best-nodrop energy -99.4961
```
getcode-search2:
```
target counts {'TMCJPEGDEC_init_buff_thumbnail': 34} start {'TMCJPEGDEC_init_buff_thumbnail': 34} {'TMCJPEGDEC_init_buff_thumbnail': 99.55882}
done 57 trials; best-nodrop energy -99.5588
```
iquant-search:
```
target counts {'TMCJPEGDEC_decode_iquant_rc': 167} start {'TMCJPEGDEC_decode_iquant_rc': 167} {'TMCJPEGDEC_decode_iquant_rc': 99.76048}
done 70 trials; best-nodrop energy -99.7605
```
sof-search:
```
target counts {'TMCJPEGDEC_parse_sof': 223} start {'TMCJPEGDEC_parse_sof': 222} {'TMCJPEGDEC_parse_sof': 93.34529}
done 79 trials; best-nodrop energy -91.3453
```
err-search:
```
target counts {'TMCJPEGDEC_err_restart': 115} start {'TMCJPEGDEC_err_restart': 115} {'TMCJPEGDEC_err_restart': 78.33044}
it 10 best-nodrop -78.4174 cnt {'TMCJPEGDEC_err_restart': 115} score [78.41739]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [78.41739]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [78.41739]
it 26 best-nodrop -79.6957 cnt {'TMCJPEGDEC_err_restart': 115} score [79.695656]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.695656]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.695656]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.695656]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.695656]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [79.608696]
it 39 best-nodrop -85.0435 cnt {'TMCJPEGDEC_err_restart': 115} score [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.95652]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [84.91304]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
it 80 best-nodrop -85.1304 cnt {'TMCJPEGDEC_err_restart': 115} score [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.13043]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
SOLUTION {'TMCJPEGDEC_err_restart': 115} [85.04348]
done 106 trials; best-nodrop energy -85.1304
```
restart-search: cancelled own queued process after 1093 seconds without acquiring a shared search slot; zero trials ran.
dht-search: cancelled own queued process after 948 seconds without acquiring a shared search slot; zero trials ran.
mkhdec-search: cancelled own queued process after 828 seconds without acquiring a shared search slot; zero trials ran.
dht-search2: cancelled own queued process after 383 seconds without acquiring a shared search slot; zero trials ran.
The stopped jobs wrote only temporary search snapshots. No other worker process or shared limiter was changed. Source search completed on thumbnail initialization, scan geometry, coefficient decoding, frame-header parsing and restart error recovery. Huffman-table building, Huffman-header parsing and restart-interval search remained resource-blocked after their manual C trials.

Final audit: 11 assigned functions, 242 logged compiled trials. Every unconverted function has at least three distinct source-level trials. Retained exact count 20 -> 20, matched code 8056 -> 8056 bytes, matched data 256 -> 256 bytes; asm bodies 11 -> 8. Eight conversions remain unresolved. No push, PR, merge, rebase, worktree switch or outside-worktree edit occurred.
