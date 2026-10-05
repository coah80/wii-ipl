# da4b de-asm attempts

Base f8957ca95be0ca4b35a281fa9a5d59f7f1787a41, branch agent/w1005/da4b, worktree data-d3. Parent prepared the fresh branch before this turn. Read AGENTS.md, deasm-round.md, common.md, levers.md, prior da4 log, and original Gekko Ghidra exports.

Scope: init_buff_thumbnail, parse_dht, make_huffdec, decode_iquant_rc, scan_varinit, restart_interval, parse_sof, err_restart. Previous three conversions are present in #1172. Preserve exact bytes, section data, symbols and DOL SHA1; commit each new exact C conversion separately.

Lever 19 audit: TMC_JPEG contains no OSThread creation or polling loop. The read callback is called synchronously by buffer_system.c. The owned register differences involve addresses, Huffman counters, coefficient values and scan geometry, not a demonstrated shared completion flag. No field is made volatile without target and call-site evidence.

Lever 18a: record the first differing definition in assignment order, then move that variable across a helper boundary, name a compiler temporary, share one local for non-overlapping values, or use a one-field struct. Use the allocator ordering model as a hypothesis, and compare emitted instructions after every trial.

TMCJPEGDEC_init_buff_thumbnail / get-baseline: 18a first diff at instruction 24: current address result r6, target r5; next length load target r6. The address and length live ranges interfere.; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-start-0: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-start-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-start-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-end-0: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-end-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-end-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-src-0: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-src-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-src-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-named-current-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-named-current-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-struct-current-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-struct-current-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-named-offset-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-named-offset-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-named-length-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-named-length-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-offset-1: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 8.
TMCJPEGDEC_init_buff_thumbnail / get-reuse-offset-2: 18a named address, one-field aggregate, or value reuse adjusts current-address numbering/interference; instructions 34/34, aligned differences 8.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-0: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-1: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-2: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-3: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-4: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-5: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-6: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u32-7: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-0: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-1: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-2: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-3: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-4: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-5: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-6: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-helper-u8p-7: 18a current-address computation across inline boundary with named return/const scalar arguments; instructions 34/34, aligned differences 3.
TMCJPEGDEC_parse_dht / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 120/120, aligned differences 6.
TMCJPEGDEC_make_huffdec / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 198/200, aligned differences 133.
TMCJPEGDEC_decode_iquant_rc / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 167/167, aligned differences 7.
TMCJPEGDEC_scan_varinit / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 129/129, aligned differences 9.
TMCJPEGDEC_restart_interval / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 93/93, aligned differences 17.
TMCJPEGDEC_parse_sof / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 222/223, aligned differences 129.
TMCJPEGDEC_err_restart / baseline: First-difference evidence before lever 18a; Ghidra export read; instructions 115/115, aligned differences 39.
TMCJPEGDEC_parse_dht / dht-start: 18a first differing definition tblID: r28 instead of r26; count walker r26 instead of r28. tblClass r27 and idx/totalCodes r25 already correct.; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-0: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-number-1: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-2: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-3: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-4: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-5: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-6: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-number-7: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-number-8: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-9: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-number-10: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-number-11: 18a move ID/walker declaration, aggregate or type to swap their relative vreg priority; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-walker-inline-0: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 75.
TMCJPEGDEC_parse_dht / dht-walker-inline-1: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 68.
TMCJPEGDEC_parse_dht / dht-walker-inline-2: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 75.
TMCJPEGDEC_parse_dht / dht-walker-inline-3: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 68.
TMCJPEGDEC_parse_dht / dht-walker-inline-4: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 75.
TMCJPEGDEC_parse_dht / dht-walker-inline-5: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 68.
TMCJPEGDEC_parse_dht / dht-walker-inline-6: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 75.
TMCJPEGDEC_parse_dht / dht-walker-inline-7: 18a put count walker and loop index in inline helper to shift their virtual numbers; instructions 124/120, aligned differences 68.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bas-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bas-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bas-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bas-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bsa-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bsa-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bsa-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-bsa-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-lived-abs-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-abs-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-abs-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-abs-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-lived-asb-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-asb-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-asb-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-asb-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sba-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sba-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sba-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sba-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sab-0: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sab-1: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sab-2: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-lived-sab-3: 18a name both add inputs and reuse dead base for length to alter neighbor counts; instructions 34/34, aligned differences 6.
TMCJPEGDEC_init_buff_thumbnail / get-range-0: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-1: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-2: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-range-3: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-range-4: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-5: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-6: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-range-7: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-range-8: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-9: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-range-10: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-range-11: 18a current/end range variables move across one inline boundary; instructions 34/34, aligned differences 4.
TMCJPEGDEC_init_buff_thumbnail / get-diagnostic-opt_propagation: 18e diagnostic only, not retained; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-diagnostic-opt_common_subs: 18e diagnostic only, not retained; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-diagnostic-scheduling: 18e diagnostic only, not retained; instructions 34/34, aligned differences 23.
TMCJPEGDEC_init_buff_thumbnail / get-diagnostic-opt_dead_assignments: 18e diagnostic only, not retained; instructions 34/34, aligned differences 3.
TMCJPEGDEC_parse_dht / dht-priority-0-1: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-0-2: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-0-3: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-0-4: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-0-5: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-1-0: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-1-2: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-1-3: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-1-4: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-1-5: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-2-0: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-2-1: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-priority-2-3: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-2-4: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-2-5: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-3-0: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-3-1: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-3-2: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-priority-3-4: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-3-5: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-4-0: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-4-1: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-4-2: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-4-3: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-4-5: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-5-0: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-5-1: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-5-2: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-5-3: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-priority-5-4: 18a hold other declarations fixed and move only differing tblID/count-walker numbers; instructions 120/120, aligned differences 27.
TMCJPEGDEC_parse_dht / dht-interference-0: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-1: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-2: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-3: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-4: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-5: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-6: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-interference-7: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 123/120, aligned differences 105.
TMCJPEGDEC_parse_dht / dht-interference-8: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 119/120, aligned differences 75.
TMCJPEGDEC_parse_dht / dht-interference-9: 18a aggregate field numbering or extend/reuse actual walker over summation; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-inline-params-0-0-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-0-0-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-0-1-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-0-1-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-0-2-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-0-2-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 16.
TMCJPEGDEC_parse_dht / dht-inline-params-1-0-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-inline-params-1-0-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-inline-params-1-1-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-inline-params-1-1-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-inline-params-1-2-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-inline-params-1-2-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-inline-params-2-0-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-inline-params-2-0-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 13.
TMCJPEGDEC_parse_dht / dht-inline-params-2-1-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-inline-params-2-1-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 9.
TMCJPEGDEC_parse_dht / dht-inline-params-2-2-0: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-inline-params-2-2-1: 18a/18c ID or class creation in caller/helper with const primitive parameter; instructions 120/120, aligned differences 9.
TMCJPEGDEC_make_huffdec / mkh-alias-count-0: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-1: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-2: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-3: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-4: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-5: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-6: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-7: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-8: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-9: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-10: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-11: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-12: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-13: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-alias-count-14: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-alias-count-15: 18a first bits walker r6 versus target r3; first restore countdown fast-table loop and character-alias reloads to recover target interference; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-0: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 186.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-1: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-2: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 186.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-3: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-4: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-5: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-6: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_make_huffdec / mkh-sizes-inline-7: 18a shift the first bits walker and count local into one inline boundary; instructions 204/200, aligned differences 187.
TMCJPEGDEC_decode_iquant_rc / iquant-reuse-position-0-0: 18a first coefficient value definition should reuse dead bit-position r4 instead of bit-buffer r3; instructions 167/167, aligned differences 0.

TMCJPEGDEC_decode_iquant_rc / iquant-exact: 18a exact: reuse the bit-position local for the coefficient value, changing its virtual register neighbours. Both DC and AC use the same readable helper.
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x29c base 0x29c insns 167/167; diffs 0: []; objdiff 100.0. Evidence: /tmp/da4b/iquant-exact.
TMCJPEGDEC_scan_varinit / scan-input-boundary-0: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-1: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-2: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-3: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-4: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-5: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-6: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-7: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-8: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-9: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-10: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-input-boundary-11: 18a first differing hSamp load target r6, source r4; move sampling inputs and scaled result across inline boundary; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-0: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-1: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 13.
TMCJPEGDEC_scan_varinit / scan-live-range-2: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-3: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 13.
TMCJPEGDEC_scan_varinit / scan-live-range-4: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-5: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-6: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-7: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 10.
TMCJPEGDEC_scan_varinit / scan-live-range-8: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-live-range-9: 18a reuse dead sampling/scale/divisor locals or name component preheader address; instructions 129/129, aligned differences 9.

## Accepted decode_iquant_rc C conversion

First differing assignment was AC coefficient value: source and r3, target and r4. The previous bit position occupied r4 and died at the store. Reusing the same local for the consumed bit position and decoded coefficient changed its interference/coalescing; both DC and AC now match. Removed unused bit_data. Exact-name objdiff 100.0, ctxdiff 167/167 instructions and diffs 0, empty pool identical.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] objdiff: code 908/908 data None/None functions 2/2 fuzzy 100.0000 linked code 908
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] instruction-exact functions: 2/2
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3]   section .text size 908 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3] baseline: code 908/908 data None functions 2 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 77.20428 -> 77.20428
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
TMCJPEGDEC_restart_interval / restart-marker-reuse-0: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-1: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-2: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-3: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-4: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-5: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-6: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 22.
TMCJPEGDEC_restart_interval / restart-marker-reuse-7: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 22.
TMCJPEGDEC_restart_interval / restart-marker-reuse-8: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-9: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-10: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-marker-reuse-11: 18a first mismatch is zero constant r5 vs r0 because marker result takes r0; reuse marker result in later position/divisor local; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-boundary-0: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-boundary-1: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 22.
TMCJPEGDEC_restart_interval / restart-boundary-2: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 32.
TMCJPEGDEC_restart_interval / restart-boundary-3: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 35.
TMCJPEGDEC_restart_interval / restart-boundary-4: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-boundary-5: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-boundary-6: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / restart-boundary-7: 18a marker value local numbering and range initialization inside the same helper; instructions 93/93, aligned differences 17.
TMCJPEGDEC_err_restart / err-marker-reuse-0: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-1: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-2: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-3: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-4: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-5: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-6: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-7: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-marker-reuse-8: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 70.
TMCJPEGDEC_err_restart / err-marker-reuse-9: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 70.
TMCJPEGDEC_err_restart / err-marker-reuse-10: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-marker-reuse-11: 18a first marker byte target r6 versus r5; name/reuse marker and MCU position. Remove unnecessary assignment back into address-taken input byte per Ghidra.; instructions 114/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-handler-scope-0: Ghidra successful marker path nested in reader loop; preserve target double exit branch; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-handler-scope-1: Ghidra successful marker path nested in reader loop; preserve target double exit branch; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-handler-scope-2: Ghidra successful marker path nested in reader loop; preserve target double exit branch; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-handler-scope-3: Ghidra successful marker path nested in reader loop; preserve target double exit branch; instructions 114/115, aligned differences 72.
TMCJPEGDEC_parse_sof / sof-unsized-extern: Incomplete extern diagnostic, actual array definition remains 6 bytes; missing instruction is lis for SampleComps. Header changes remain temporary.; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-0: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-1: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-2: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-hsample-3: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-4: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-hsample-5: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-6: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-7: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 84.
TMCJPEGDEC_parse_sof / sof-hsample-8: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 224/223, aligned differences 154.
TMCJPEGDEC_parse_sof / sof-hsample-9: 18a first differing named value hSamp source r4 target r3, opposite frame component address; reuse call result or move value creation boundary; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-unpack-inline-0: 18a component address and decoded horizontal value formed inside inline store helper; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-unpack-inline-1: 18a component address and decoded horizontal value formed inside inline store helper; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-unpack-inline-2: 18a component address and decoded horizontal value formed inside inline store helper; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-unpack-inline-3: 18a component address and decoded horizontal value formed inside inline store helper; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_dht / dht-count-degree-0: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-count-degree-1: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 24.
TMCJPEGDEC_parse_dht / dht-count-degree-2: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 38.
TMCJPEGDEC_parse_dht / dht-count-degree-3: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 35.
TMCJPEGDEC_parse_dht / dht-count-degree-4: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 97/120, aligned differences 85.
TMCJPEGDEC_parse_dht / dht-count-degree-5: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 97/120, aligned differences 85.
TMCJPEGDEC_parse_dht / dht-count-degree-6: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 35.
TMCJPEGDEC_parse_dht / dht-count-degree-7: 18a reduce tblID interference degree: reuse one count local for 16-byte reader index and total symbol count instead of two coalesced vregs; instructions 120/120, aligned differences 35.
TMCJPEGDEC_parse_dht / dht-walker-number-0: 18a local walker in pointer-returning inline; combine with count-local degree reduction; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-walker-number-1: 18a local walker in pointer-returning inline; combine with count-local degree reduction; instructions 121/120, aligned differences 108.
TMCJPEGDEC_parse_dht / dht-walker-number-2: 18a local walker in pointer-returning inline; combine with count-local degree reduction; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / dht-walker-number-4: 18a local walker in pointer-returning inline; combine with count-local degree reduction; instructions 120/120, aligned differences 35.
TMCJPEGDEC_parse_dht / dht-walker-number-5: 18a local walker in pointer-returning inline; combine with count-local degree reduction; instructions 121/120, aligned differences 108.

Queued searches receive refreshed best C before lock acquisition. SOF: incomplete-extern diagnostic plus inline sampling unpack gives 223 instructions and 77 differences, fixing the first hSamp/component-address swap. No shared header edit retained. Restart recovery: prior 85% search candidate preserved in /tmp/da4b/err-best.c, next MCU value is bounded by 255*65535+255+65535 = 16777215, so its unsigned temporary changes compiler division selection without changing defined arithmetic for nonzero pitch; this remains a non-exact trial.
TMCJPEGDEC_make_huffdec / mkh-param-walker-0: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-param-walker-1: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 198/200, aligned differences 142.
TMCJPEGDEC_make_huffdec / mkh-param-walker-2: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-param-walker-3: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 196/200, aligned differences 140.
TMCJPEGDEC_make_huffdec / mkh-param-walker-4: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 195/200, aligned differences 171.
TMCJPEGDEC_make_huffdec / mkh-param-walker-5: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 195/200, aligned differences 176.
TMCJPEGDEC_make_huffdec / mkh-param-walker-6: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 193/200, aligned differences 174.
TMCJPEGDEC_make_huffdec / mkh-param-walker-7: 18a use original dht parameter for first walk, retaining original pointer for table phase; target walker r3 rather than r6; instructions 193/200, aligned differences 179.
TMCJPEGDEC_err_restart / err-full-quotient-0: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 72.
TMCJPEGDEC_make_huffdec / mkh-fill-walker-1: 18a named parameter walker plus natural countdown/index endpoints matching target Ghidra remaining counter; instructions 196/200, aligned differences 140.
TMCJPEGDEC_err_restart / err-full-quotient-1: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 71.
TMCJPEGDEC_make_huffdec / mkh-fill-walker-2: 18a named parameter walker plus natural countdown/index endpoints matching target Ghidra remaining counter; instructions 208/200, aligned differences 147.
TMCJPEGDEC_err_restart / err-full-quotient-2: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 67.
TMCJPEGDEC_make_huffdec / mkh-fill-walker-3: 18a named parameter walker plus natural countdown/index endpoints matching target Ghidra remaining counter; instructions 158/200, aligned differences 98.
TMCJPEGDEC_err_restart / err-full-quotient-3: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 66.
TMCJPEGDEC_make_huffdec / mkh-fill-walker-4: 18a named parameter walker plus natural countdown/index endpoints matching target Ghidra remaining counter; instructions 216/200, aligned differences 144.
TMCJPEGDEC_err_restart / err-full-quotient-4: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 72.
TMCJPEGDEC_make_huffdec / mkh-fill-walker-5: 18a named parameter walker plus natural countdown/index endpoints matching target Ghidra remaining counter; instructions 159/200, aligned differences 99.
TMCJPEGDEC_err_restart / err-full-quotient-5: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-full-quotient-6: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 67.
TMCJPEGDEC_err_restart / err-full-quotient-7: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 66.
TMCJPEGDEC_err_restart / err-full-quotient-8: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 72.
TMCJPEGDEC_err_restart / err-full-quotient-9: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 71.
TMCJPEGDEC_err_restart / err-full-quotient-10: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 114/115, aligned differences 67.
TMCJPEGDEC_err_restart / err-full-quotient-11: Target computes remainder with full signed quotient before narrowing; moving restart-span product before position store follows Ghidra; instructions 113/115, aligned differences 66.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-0: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-1: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-2: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-3: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-4: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-5: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-6: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-7: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-8: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-9: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-10: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-copy-value-11: 18a extend existing copied input word lifetime into thumbnail offset/current pointer; target reuses r5 from final context copy; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-0: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-1: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-2: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-3: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-4: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-5: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-6: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_init_buff_thumbnail / get-offset-helper-7: 18a first offset local across helper, reuse dead source/start parameter for thumbnail base; instructions 34/34, aligned differences 5.
TMCJPEGDEC_parse_sof / sof-table-locals-0: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-1: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-2: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 78.
TMCJPEGDEC_parse_sof / sof-table-locals-3: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 78.
TMCJPEGDEC_parse_sof / sof-table-locals-4: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-5: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-6: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-7: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / sof-table-locals-8: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 73.
TMCJPEGDEC_parse_sof / sof-table-locals-9: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 73.
TMCJPEGDEC_parse_sof / sof-table-locals-10: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 74.
TMCJPEGDEC_parse_sof / sof-table-locals-11: 18a next first difference counts base r5 vs target r6: name loop count or move walkers into inline selector to change temporary numbering; instructions 223/223, aligned differences 74.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-0: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 223/223, aligned differences 54.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-1: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 221/223, aligned differences 106.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-2: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 223/223, aligned differences 58.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-3: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 221/223, aligned differences 106.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-4: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 223/223, aligned differences 54.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-5: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 221/223, aligned differences 106.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-6: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 223/223, aligned differences 58.
TMCJPEGDEC_parse_sof / sof-geometry-boundary-7: 18a geometry names cross inline boundary; full-width quotient reused for remainder before narrowing; instructions 221/223, aligned differences 106.
TMCJPEGDEC_make_huffdec / mkh-character-char-0: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-character-char-1: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-character-char-2: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-character-char-3: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-character-signed-char-0: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-character-signed-char-1: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-character-signed-char-2: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-character-signed-char-3: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_parse_sof / sof-validation-priority-0: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 54.
TMCJPEGDEC_make_huffdec / mkh-character-unsigned-char-0: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-1: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 50.
TMCJPEGDEC_make_huffdec / mkh-character-unsigned-char-1: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_parse_sof / sof-validation-priority-2: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 49.
TMCJPEGDEC_make_huffdec / mkh-character-unsigned-char-2: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-3: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 45.
TMCJPEGDEC_make_huffdec / mkh-character-unsigned-char-3: 19 excluded: reloads follow table writes, so test actual alias types, not volatile; target has 8 symbol loads in unrolled body, current CSE has 1; instructions 196/200, aligned differences 131.
TMCJPEGDEC_parse_sof / sof-validation-priority-4: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 54.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-0: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-5: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 50.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-1: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-6: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 49.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-2: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-7: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 45.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-3: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 198/200, aligned differences 133.
TMCJPEGDEC_parse_sof / sof-validation-priority-8: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 49.
TMCJPEGDEC_parse_sof / sof-validation-priority-9: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 45.
TMCJPEGDEC_parse_sof / sof-validation-priority-10: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 49.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-4: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 196/200, aligned differences 131.
TMCJPEGDEC_parse_sof / sof-validation-priority-11: 18a target validation frame base r3 and index r4; reverse only these local numbers, preserve geometry helper and no volatile; instructions 223/223, aligned differences 45.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-5: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-6: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-entry-inline-7: 18a/19 alias audit: move table and source-byte access through entry helper without volatile or extra stores; instructions 196/200, aligned differences 131.
TMCJPEGDEC_parse_sof / sof-match-boundary-0: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-1: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-2: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-3: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-4: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-5: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-6: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-7: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-8: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-9: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-10: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-match-boundary-11: 18a target inner table pointers in r4/r3 look like inline helper parameters; isolate validation with void early return so no artificial result branch; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / sof-walker-order-chv: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 49.
TMCJPEGDEC_parse_sof / sof-walker-order-cvh: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 48.
TMCJPEGDEC_parse_sof / sof-walker-order-hcv: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 46.
TMCJPEGDEC_parse_sof / sof-walker-order-hvc: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 50.
TMCJPEGDEC_parse_sof / sof-walker-order-vch: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 45.
TMCJPEGDEC_parse_sof / sof-walker-order-vhc: 18a reverse declaration number of first differing count pointer; preserve target global relocation order; instructions 223/223, aligned differences 50.
TMCJPEGDEC_make_huffdec / mkh-diagnostic-opt_common_subs: 18e diagnostic only: identify whether source symbol reload difference is CSE or copy propagation; instructions 199/200, aligned differences 158.
TMCJPEGDEC_make_huffdec / mkh-diagnostic-opt_propagation: 18e diagnostic only: identify whether source symbol reload difference is CSE or copy propagation; instructions 193/200, aligned differences 137.
TMCJPEGDEC_make_huffdec / mkh-pair-table-0: Typed halfword pair array and explicit symbol index width as target alias/CSE diagnostic; no volatile; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / mkh-pair-table-1: Typed halfword pair array and explicit symbol index width as target alias/CSE diagnostic; no volatile; instructions 196/200, aligned differences 131.
TMCJPEGDEC_make_huffdec / mkh-pair-table-2: Typed halfword pair array and explicit symbol index width as target alias/CSE diagnostic; no volatile; instructions 198/200, aligned differences 143.
TMCJPEGDEC_make_huffdec / mkh-pair-table-3: Typed halfword pair array and explicit symbol index width as target alias/CSE diagnostic; no volatile; instructions 196/200, aligned differences 141.

Source-search slot starvation: three later searches completed, but four older jobs had empty logs and no held slot. Stopped only own still-waiting jobs after verifying /proc cwd and command. In the local /tmp copy, changed fixed 5-second retries to random 0.1-0.6-second retries, keeping SLOTS=24 and flock acquisition unchanged. No other worker or shared tool/limiter was modified. Restart from refreshed best C.
/tmp/da4b/get-search-18: requeued after 1651 seconds without a trial.
/tmp/da4b/mkh-search-18: requeued after 1488 seconds without a trial.
/tmp/da4b/sof-search-18: requeued after 802 seconds without a trial.
/tmp/da4b/err-search-18: requeued after 801 seconds without a trial.
TMCJPEGDEC_parse_sof / score-sof-unpack-inline-0: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 77.
TMCJPEGDEC_parse_sof / score-sof-unpack-inline-0: objdiff 96.260086; instruction delta 0, aligned differences 77; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-unpack-inline-0.c.
TMCJPEGDEC_parse_sof / score-sof-geometry-boundary-0: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 54.
TMCJPEGDEC_parse_sof / score-sof-geometry-boundary-0: objdiff 97.44843; instruction delta 0, aligned differences 54; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-geometry-boundary-0.c.
TMCJPEGDEC_parse_sof / score-sof-validation-priority-2: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 49.
TMCJPEGDEC_parse_sof / score-sof-validation-priority-2: objdiff 97.605385; instruction delta 0, aligned differences 49; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-validation-priority-2.c.
TMCJPEGDEC_parse_sof / score-sof-validation-priority-3: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 45.
TMCJPEGDEC_parse_sof / score-sof-validation-priority-3: objdiff 97.739914; instruction delta 0, aligned differences 45; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-validation-priority-3.c.
TMCJPEGDEC_parse_sof / score-sof-walker-order-vch: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 45.
TMCJPEGDEC_parse_sof / score-sof-walker-order-vch: objdiff 97.69507; instruction delta 0, aligned differences 45; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-walker-order-vch.c.
TMCJPEGDEC_parse_sof / score-sof-match-boundary-0: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 223/223, aligned differences 51.
TMCJPEGDEC_parse_sof / score-sof-match-boundary-0: objdiff 97.53812; instruction delta 0, aligned differences 51; source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-match-boundary-0.c.
TMCJPEGDEC_init_buff_thumbnail / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 34/34, aligned differences 3.
TMCJPEGDEC_init_buff_thumbnail / handoff-measure: objdiff 99.55882; instruction delta 0, aligned differences 3; source /tmp/da4b/TMCJPEGDEC_init_buff_thumbnail-variants/get-baseline.c.
TMCJPEGDEC_parse_dht / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 120/120, aligned differences 6.
TMCJPEGDEC_parse_dht / handoff-measure: objdiff 99.708336; instruction delta 0, aligned differences 6; source /tmp/da4/TMCJPEGDEC_parse_dht-variants/dht-types-0.c.
TMCJPEGDEC_make_huffdec / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 198/200, aligned differences 133.
TMCJPEGDEC_make_huffdec / handoff-measure: objdiff 78.43; instruction delta -2, aligned differences 133; source /tmp/da4/TMCJPEGDEC_make_huffdec-variants/mkhdec-final-0.c.
TMCJPEGDEC_scan_varinit / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / handoff-measure: objdiff 99.496124; instruction delta 0, aligned differences 9; source /tmp/da4/TMCJPEGDEC_scan_varinit-variants/scan-decls-0.c.
TMCJPEGDEC_restart_interval / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 93/93, aligned differences 17.
TMCJPEGDEC_restart_interval / handoff-measure: objdiff 96.77419; instruction delta 0, aligned differences 17; source /tmp/da4/TMCJPEGDEC_restart_interval-variants/restart-more-4.c.
TMCJPEGDEC_err_restart / handoff-measure: Fresh source/object and exact-name objdiff measurement of rejected C; no tracked source edit; instructions 115/115, aligned differences 39.
TMCJPEGDEC_err_restart / handoff-measure: objdiff 85.13043; instruction delta 0, aligned differences 39; source /tmp/da4b/err-best.c.

Further source audit: src/utility/iplJpegDecoder.cpp calls TMCCJPEGDecodeRGB565 synchronously and checks its return before setting its own mStatus to STATUS_DECODED. decapi.c reads/writes the JPEG state within that call, and buffer_system.c invokes its read callback synchronously. No inspected caller polls an owned JPEG buffer/Huffman/MCU field across threads. Lever 19 has no supporting evidence here, so all declarations retain their original qualifiers.
Rejected semantic trial: dht-count-degree-4 and -5 accidentally used idx for both the summation iterator and accumulator. They were never installed or accepted and do not count toward distinct valid attempts. The other DHT numbering/lifetime variants exceed the required three valid trials.
make_huffdec evidence: target unrolled fill reloads tb[index] after each halfword pair. C currently caches the symbol byte and produces a different loop remainder. Plain/signed/unsigned character access, a halfword pair array, mutable pointer view and inline writer did not restore the target. Temporary opt_common_subs/opt_propagation diagnostics did not become exact; neither pragma was installed.
SOF progress remains advisory: instruction alignment alone does not establish matching global relocations. Fresh exact-name objdiff scores the 223-instruction best C at 97.739914, with the incomplete extern confined to /tmp/da4b/sof-headers. All seven remaining asm bodies remain in tracked source.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-0: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-1: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-2: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-3: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-4: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-5: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 9.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-6: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-7: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-8: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 15.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-9: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 15.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-10: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-11: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-12: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 15.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-13: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 15.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-14: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.
TMCJPEGDEC_scan_varinit / scan-reuse-dimensions-15: 18a target hSamp r6 later holds frameWidth; qTblH r4 later holds frameHeight. Reuse those non-overlapping scalar lifetimes to alter neighbor count.; instructions 129/129, aligned differences 16.

## Round coverage and remaining C candidates

One converted function: TMCJPEGDEC_decode_iquant_rc, committed as c0611243 after the full clean gate. Seven asm bodies remain unresolved. Their arithmetic/control flow is expressible in C; no architectural need for retained assembly was found. Unaccepted sources and temporary diagnostics are confined to /tmp/da4b. The only changed project source is iqdec_resolution_change_a3.c.

Logged compile measurements by function, including baseline/repeated evidence checks: TMCJPEGDEC_decode_iquant_rc=2, TMCJPEGDEC_err_restart=30, TMCJPEGDEC_init_buff_thumbnail=97, TMCJPEGDEC_make_huffdec=65, TMCJPEGDEC_parse_dht=94, TMCJPEGDEC_parse_sof=72, TMCJPEGDEC_restart_interval=22, TMCJPEGDEC_scan_varinit=40. Every remaining function has more than three distinct valid source-level trials. The two invalid DHT accumulator rewrites are excluded from acceptance and coverage.

- TMCJPEGDEC_init_buff_thumbnail: rejected C objdiff 99.55882, instruction delta 0, aligned instruction differences 3. Source /tmp/da4b/TMCJPEGDEC_init_buff_thumbnail-variants/get-baseline.c. Report /tmp/da4b/TMCJPEGDEC_init_buff_thumbnail-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_parse_dht: rejected C objdiff 99.708336, instruction delta 0, aligned instruction differences 6. Source /tmp/da4/TMCJPEGDEC_parse_dht-variants/dht-types-0.c. Report /tmp/da4b/TMCJPEGDEC_parse_dht-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_make_huffdec: rejected C objdiff 78.43, instruction delta -2, aligned instruction differences 133. Source /tmp/da4/TMCJPEGDEC_make_huffdec-variants/mkhdec-final-0.c. Report /tmp/da4b/TMCJPEGDEC_make_huffdec-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_scan_varinit: rejected C objdiff 99.496124, instruction delta 0, aligned instruction differences 9. Source /tmp/da4/TMCJPEGDEC_scan_varinit-variants/scan-decls-0.c. Report /tmp/da4b/TMCJPEGDEC_scan_varinit-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_restart_interval: rejected C objdiff 96.77419, instruction delta 0, aligned instruction differences 17. Source /tmp/da4/TMCJPEGDEC_restart_interval-variants/restart-more-4.c. Report /tmp/da4b/TMCJPEGDEC_restart_interval-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_err_restart: rejected C objdiff 85.13043, instruction delta 0, aligned instruction differences 39. Source /tmp/da4b/err-best.c. Report /tmp/da4b/TMCJPEGDEC_err_restart-variants/handoff-measure-report/report.json.
- TMCJPEGDEC_parse_sof: rejected C objdiff 97.739914, instruction delta 0, aligned instruction differences 45. Source /tmp/da4b/TMCJPEGDEC_parse_sof-variants/sof-validation-priority-3.c. Report /tmp/da4b/TMCJPEGDEC_parse_sof-variants/score-sof-validation-priority-3-report/report.json. Requires temporary incomplete-extern header for measurement only.

SOF search include fix: POSIX absolute and parent-relative include directives were rejected by MWCC. The local srcsearch copy now accepts --include and prepends its path to the real compiler command. The original source include stays unchanged. Verified source search starts at 223 instructions / 97.739914 with /tmp/da4b/sof-headers; shared headers are untouched.

## Completed source searches

dht-search-18:
```
target counts {'TMCJPEGDEC_parse_dht': 120} start {'TMCJPEGDEC_parse_dht': 120} {'TMCJPEGDEC_parse_dht': 99.708336}
done 165 trials; best-nodrop energy -99.7083
```
scan-search-18:
```
target counts {'TMCJPEGDEC_scan_varinit': 129} start {'TMCJPEGDEC_scan_varinit': 129} {'TMCJPEGDEC_scan_varinit': 99.496124}
done 85 trials; best-nodrop energy -99.4961
```
restart-search-18:
```
target counts {'TMCJPEGDEC_restart_interval': 93} start {'TMCJPEGDEC_restart_interval': 93} {'TMCJPEGDEC_restart_interval': 96.77419}
done 341 trials; best-nodrop energy -96.7742
```
err-search-resumed:
```
target counts {'TMCJPEGDEC_err_restart': 115} start {'TMCJPEGDEC_err_restart': 115} {'TMCJPEGDEC_err_restart': 85.13043}
done 536 trials; best-nodrop energy -85.1304
```
get-search-resumed:
```
target counts {'TMCJPEGDEC_init_buff_thumbnail': 34} start {'TMCJPEGDEC_init_buff_thumbnail': 34} {'TMCJPEGDEC_init_buff_thumbnail': 99.55882}
done 450 trials; best-nodrop energy -99.5588
```
mkh-search-resumed:
```
target counts {'TMCJPEGDEC_make_huffdec': 200} start {'TMCJPEGDEC_make_huffdec': 198} {'TMCJPEGDEC_make_huffdec': 78.43}
done 442 trials; best-nodrop energy -74.43
```
sof-search-include:
```
target counts {'TMCJPEGDEC_parse_sof': 223} start {'TMCJPEGDEC_parse_sof': 223} {'TMCJPEGDEC_parse_sof': 97.739914}
done 481 trials; best-nodrop energy -97.7399
```
All seven remaining functions completed srcsearch from their best available C. Total 2500 source-search trials. None reached exactness; no search mutation was installed. All own search processes have ended before the final full clean gate.
origin/main advanced by two commits while this worker ran. The leaf remains based on the requested f8957ca9 plus c0611243; no merge or rebase was performed.

## Final clean validation

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] objdiff: code 316/316 data None/None functions 3/3 fuzzy 100.0000 linked code 316
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] instruction-exact functions: 3/3
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode]   section .text size 316 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode] baseline: code 316/316 data None functions 3 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] objdiff: code 5604/5604 data 256/256 functions 13/13 fuzzy 100.0000 linked code 5604
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] instruction-exact functions: 13/13
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .rodata size 256 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .text size 5604 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] baseline: code 5604/5604 data 256 functions 13 fuzzy 100.0000
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
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 77.20428 -> 77.20428
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
After the clean gate, ninja -C . build/43U/ok reported no work. Fresh ctxdiff for TMCJPEGDEC_decode_iquant_rc: 167/167 instructions, diffs 0. SHA1 independently read as 26116613f624061ba99c8d1a299aaa6efa85670d.

Before -> after across owned units: instruction-exact functions 20 -> 20; matched code 8056 -> 8056 bytes; matched data 256 -> 256 bytes; retained asm bodies 8 -> 7. Gated source conversion: c0611243. All seven source searches completed, 2500 trials. Only iqdec_resolution_change_a3.c and this attempts log changed. No push, PR, merge, rebase, shared-header edit or other-worktree edit occurred.
