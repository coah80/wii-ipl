# Four-unit matching attempts

Baseline measured live, not copied from task estimates. Only instruction-exact improvements retained. Failed compiler experiments do not count toward the three-attempt requirement.

## getControlKey__Q49textinput8keyboard6pctype4BaseFPc
Origin 30e1ef09380cb59719dcfbd2c00c52ca16473946, source identical
Diagnosis: 36/36 instructions; counter and element offset exchange r30/r31, prologue initialization moves. No branch or frame difference.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (36, 36, 8)
1. bind the selected control by reference before comparison: (34, 36, 23) objdiff 88.02778 pool/regression/scan PASS reverted
2. declare the traversal index in function scope: (36, 36, 8) objdiff 93.333336 pool/regression/scan PASS reverted
3. use a do while traversal preserving 16 bit index: compile failed /src/keyboard/tiPcKeyboard.d
Final restored (36, 36, 8)
Origin 30e1ef09380cb59719dcfbd2c00c52ca16473946, source identical
Diagnosis: Counter and offset coloring remains; try loop induction form after scoped-index and reference trials.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (36, 36, 8)
1. do while with preincremented 16 bit traversal index: (37, 36, 20) objdiff 90.55556 pool/regression/scan PASS reverted
Final restored (36, 36, 8)
Origin edfb253724595e3a6487d03a669d4a521f781e1d, source identical
Diagnosis: Register-only result after three loop/reference experiments. Test genuine inline key-state lookup boundary then declaration ordering.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (36, 36, 8)
1. inline control lookup with explicit key-state argument: compile failed ---------------------
Final restored (36, 36, 8)
Origin 17407ed1cbfa5f7f43ebd141902ceea0c73a1e64, source identical
Diagnosis: Register-only induction/element offset mismatch; name the widened control index so its declaration participates in real allocation.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (36, 36, 8)
1. explicit widened control index before traversal counter: (36, 36, 8) objdiff 93.333336 pool/regression/scan PASS reverted
start (2, 8)
best (2, 8) after 2 builds; source restored; best order was:
Final restored (36, 36, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: Register-only result after three loop/reference experiments. Test genuine inline key-state lookup boundary then declaration ordering.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (36, 36, 8)
1. inline control lookup with explicit key-state argument: (36, 36, 0) objdiff 100 pool/regression/scan PASS retained for further trials
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
[agent/w1002/near7 21811470] match base::getcontrolkey

## setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode
Origin 30e1ef09380cb59719dcfbd2c00c52ca16473946, source identical
Diagnosis: 106/105; only extra mr r31,r30 initializes defined enum fallback. Target default-path value is not initialized. Keep defined behavior; test equivalent mappings.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (106, 105, 99)
1. select key mode with conditional expressions: (117, 105, 109) objdiff 88.46667 pool/regression/scan PASS reverted
2. reuse mode as direct numeric key mode: (88, 105, 100) objdiff 82.685715 pool/regression/scan FAIL reverted
3. signed intermediate enum mapping: (106, 105, 99) objdiff 99.04762 pool/regression/scan PASS reverted
Final restored (106, 105, 99)

## onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb
Origin 30e1ef09380cb59719dcfbd2c00c52ca16473946, source identical
Diagnosis: 49/49; inline setABCFlag owner and flags exchange r4/r6. Branches, stack and instruction schedule otherwise identical.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (49, 49, 8)
1. bind the key state pointer before querying flags: (49, 49, 8) objdiff 99.081635 pool/regression/scan PASS reverted
2. pass modifier combination directly into setter: (49, 49, 9) objdiff 99.081635 pool/regression/scan FAIL reverted
3. separate flags declaration and getter assignment: (49, 49, 8) objdiff 99.081635 pool/regression/scan PASS reverted
Final restored (49, 49, 8)
Origin edfb253724595e3a6487d03a669d4a521f781e1d, source identical
Diagnosis: Try actual setter owner load lifetime; standalone setter and every caller remain protected by gate regression check.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (49, 49, 8)
1. load owner after updating flags in real setter: (49, 49, 8) objdiff 99.081635 pool/regression/scan PASS reverted
Final restored (49, 49, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: After three structural/helper/lifetime attempts, expose state pointer and flags as separately assigned locals for safe declaration search. Every local assigned before use.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (49, 49, 8)
2. put final round key before substituted bytes: (249, 251, 244) objdiff 61.49004 pool/regression/scan PASS reverted
Final restored (249, 251, 244)
fewer than two leading declarations; pass --lines START END
Final restored (49, 49, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source differs; inspected below
Diagnosis: After three structural/helper/lifetime attempts, expose state pointer and flags as separately assigned locals for safe declaration search. Every local assigned before use.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (49, 49, 8)
start (0, 8)
best (0, 8) after 2 builds; source restored; best order was:
Final restored (49, 49, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source differs; inspected below
Diagnosis: Structural branches and instructions identical, inline helper boundary changed control lookup coloring exactly. Try real shared shift-modifier operation boundary for both pressed and released events.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (49, 49, 8)
1. inline shared shift modifier operation with state first: (49, 49, 11) objdiff 98.77551 pool/regression/scan PASS reverted
2. inline shared shift modifier operation with enable flag first: (49, 49, 11) objdiff 98.77551 pool/regression/scan PASS reverted
Final restored (49, 49, 8)

## onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv
Origin 30e1ef09380cb59719dcfbd2c00c52ca16473946, source identical
Diagnosis: 39/39; inline owner and flags exchange r4/r6 only.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (39, 39, 8)
1. bind the key state pointer before querying flags: (39, 39, 8) objdiff 98.84615 pool/regression/scan PASS reverted
2. pass modifier combination directly into setter: (39, 39, 13) objdiff 92.30769 pool/regression/scan FAIL reverted
3. separate flags declaration and getter assignment: (39, 39, 8) objdiff 98.84615 pool/regression/scan PASS reverted
Final restored (39, 39, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: After three structural/helper/lifetime attempts, expose state pointer and flags as separately assigned locals for safe declaration search. Every local assigned before use.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (39, 39, 8)
fewer than two leading declarations; pass --lines START END
Final restored (39, 39, 8)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source differs; inspected below
Diagnosis: After three structural/helper/lifetime attempts, expose state pointer and flags as separately assigned locals for safe declaration search. Every local assigned before use.
POOL IDENTICAL up to 204 (mine=204 base=204)
Initial (39, 39, 8)
start (0, 8)
best (0, 8) after 2 builds; source restored; best order was:
Final restored (39, 39, 8)

## AXFXChorusExpShutdown
Origin c1cccf1c2c9ef6531a5f914c1e67b7032dbbc273, source identical
Diagnosis: 36/36; fx and channel exchange r29/r30, identical frame/branches. Test helper boundary before declaration coloring.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (36, 36, 5)
1. declare channel before interrupt enabled: (36, 36, 0) objdiff 100 pool/regression/scan FAIL reverted
2. split enabled declaration and assignment: compile failed DK/src/axfx/AXFXChorusExp.d
3. use signed channel traversal: (36, 36, 5) objdiff 97.638885 pool/regression/scan FAIL reverted
Final restored (36, 36, 5)
Origin f095c9ea12ecefe57174107f9d1cb93ba6ebe1cf, source differs; inspected below
Diagnosis: Register-only loop mismatch after declaration/lifetime trials; use real delay-line freeing inline helper corresponding to allocation/bzero helpers.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (36, 36, 5)
1. inline delay line deallocation helper: (36, 36, 0) objdiff 100 pool/regression/scan PASS retained for further trials
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
[agent/w1002/near7 c10cacbe] match axfxchorusexpshutdown

## AXFXChorusExpCallback
Origin c1cccf1c2c9ef6531a5f914c1e67b7032dbbc273, source identical
Diagnosis: 216/216; input/output array stack offsets reversed, history induction updates and whole decrement scheduled differently, interpolation float accumulation differs. Fix structural operations before coloring.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (216, 216, 70)
1. declare input before output to match stack arrays: (216, 216, 74) objdiff 89.12037 pool/regression/scan PASS reverted
2. decrement remaining history samples before source wrap: (216, 216, 63) objdiff 89.15741 pool/regression/scan PASS retained for further trials
3. separate history increment from index masking: (216, 216, 11) objdiff 99.64352 pool/regression/scan PASS retained for further trials
Final restored (216, 216, 70)
Origin e5f4e0e1f4b38e8ac2f461523b2cb26ede5210f4, source identical
Diagnosis: Prior structural trials reduced 70 diffs to 11. Retain separate history increments and earlier whole decrement; then inspect arrays/induction coloring.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (216, 216, 70)
1. restore separate increments and decrement before wrap: (216, 216, 11) objdiff 99.64352 pool/regression/scan PASS retained for further trials
2. exchange input and output array declarations after loop repairs: (216, 216, 15) objdiff 99.625 pool/regression/scan PASS reverted
3. declare retained history index before fractional source indices: (216, 216, 11) objdiff 99.64352 pool/regression/scan PASS reverted
Final restored (216, 216, 70)
Origin fed31b69b6e31473842c24734915f62f8466a84f, source identical
Diagnosis: 11 remaining differences after loop fix are input/output expression operand order and stack pointer register allocation.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (216, 216, 70)
1. separate history increments and decrement before wrap: (216, 216, 11) objdiff 99.64352 pool/regression/scan PASS retained for further trials
2. read output before incremented bus input in dry addition: (216, 216, 0) objdiff 100 pool/regression/scan PASS retained for further trials
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
[agent/w1002/near7 6cc459c4] match axfxchorusexpcallback

## __InitParams
Origin c1cccf1c2c9ef6531a5f914c1e67b7032dbbc273, source identical
Diagnosis: 126/126; comparison reversed and independent integer resets, floating conversions and history stores reorder. Conversion locals needed before data stores; no inline helper boundary mismatch.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (126, 126, 56)
Origin c1cccf1c2c9ef6531a5f914c1e67b7032dbbc273, source identical
Diagnosis: 126/126; comparison reversed and independent integer resets, floating conversions and history stores reorder. Conversion locals needed before data stores; no inline helper boundary mismatch.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (126, 126, 56)
1. compare depth against delay in target operand order: (126, 126, 55) objdiff 69.992065 pool/regression/scan PASS retained for further trials
2. compute all signed LFO conversions in locals before state stores: (126, 126, 55) objdiff 69.75397 pool/regression/scan PASS reverted
3. multiply depth on left of fixed point scale: (126, 126, 55) objdiff 69.992065 pool/regression/scan PASS reverted
Final restored (126, 126, 56)
Origin 0d75b24a9634b51dd5a74eb4d7ce09dea02d681b, source differs; inspected below
Diagnosis: Move integer state initialization ahead of arithmetic conversions so history stores no longer interleave. Same constants and operation associations as original.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (126, 126, 56)
1. initialize integer LFO state before conversion stores: (126, 126, 55) objdiff 69.79365 pool/regression/scan PASS retained for further trials
2. depth on left in saturation comparison: (126, 126, 54) objdiff 69.87302 pool/regression/scan PASS retained for further trials
3. compute period step before phase and depth conversions: (126, 126, 55) objdiff 69.11905 pool/regression/scan FAIL reverted
Final restored (126, 126, 56)
Origin d17ab22bf0394165d00ce90513e36b576ee05d94, source differs; inspected below
Diagnosis: Try natural inline history clearing helper to establish arithmetic boundary matching target history stores after all conversion stores.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (126, 126, 56)
1. inline history clearing boundary after LFO conversion stores: (126, 126, 56) objdiff 69.9127 pool/regression/scan PASS reverted
Final restored (126, 126, 56)

## __CalcLFO
Origin c1cccf1c2c9ef6531a5f914c1e67b7032dbbc273, source identical
Diagnosis: 65 target; target retains signed 64 bit shifted sample and negation carry, ours manually assembles low word. Target unsigned sign >=1. Restore arithmetic width first.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 65, 65)
1. use signed 64 bit shifts and retained sample value: (54, 65, 65) objdiff 61.46154 pool/regression/scan PASS retained for further trials
2. test unsigned LFO sign against one: (54, 65, 65) objdiff 62.384617 pool/regression/scan PASS reverted
3. widen accumulated last sample before gradient addition: (54, 65, 65) objdiff 61.46154 pool/regression/scan PASS reverted
Final restored (51, 65, 65)
Origin 0d75b24a9634b51dd5a74eb4d7ce09dea02d681b, source differs; inspected below
Diagnosis: Target gradient multiply expands 64-bit difference operand, sample shift/negation remain 64-bit. Target uses fixed-count CTR loop.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 65, 65)
1. retain 64 bit gradient difference and signed sample with sign threshold: (54, 65, 65) objdiff 62.384617 pool/regression/scan PASS retained for further trials
2. fixed-count ascending for loop: (55, 65, 65) objdiff 72.0 pool/regression/scan PASS retained for further trials
3. name gradient product independently before shifted store: (55, 65, 65) objdiff 72.0 pool/regression/scan PASS reverted
Final restored (51, 65, 65)
Origin d17ab22bf0394165d00ce90513e36b576ee05d94, source differs; inspected below
Diagnosis: Try compound assignment preserving signed 64-bit multiplication intermediate instead of direct product expression, with fixed-count CTR loop.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 65, 65)
1. compound 64 bit gradient multiplication with signed output: (61, 65, 65) objdiff 62.29231 pool/regression/scan PASS retained for further trials
Final restored (51, 65, 65)

## pdm_part_is_master_boot_sector
Origin d9fbf88fb8fcce715fab661f1fe8be49f007efcd, source identical
Diagnosis: 86/84; frame 64 vs 48 saves extra r29 from endian load association. Target start/count pointers r6/r7 and index r8. Target high byte loaded before middle byte, addition pair layout remains meaningful.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (86, 84, 84)
1. evaluate high byte pair before low byte pair: (86, 84, 85) objdiff 82.27381 pool/regression/scan PASS reverted
2. group little endian words as independent low and high halves: (86, 84, 85) objdiff 86.38095 pool/regression/scan PASS reverted
3. initialize traversal pointers at declaration after signature validation: compile failed /pdm_partition.d
Final restored (86, 84, 84)
Origin c8bb9f44da1ea63d0dad0a388957bcb5a4150fab, source identical
Diagnosis: Third compiling structural trial: high/middle byte loads ordered by named scalar parts; target saves one fewer callee register.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (86, 84, 84)
1. name high and low byte pairs before stores: (83, 84, 76) objdiff 81.34524 pool/regression/scan PASS retained for further trials
Final restored (86, 84, 84)
Origin d17ab22bf0394165d00ce90513e36b576ee05d94, source identical
Diagnosis: Named endian halves reduced frame/instruction count; preliminary start store must precede remaining buffer reads to preserve target alias dependency.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (86, 84, 84)
1. retain preliminary start store before count byte loads: (84, 84, 36) objdiff 86.95238 pool/regression/scan PASS retained for further trials
2. evaluate low start half before high start half: (84, 84, 36) objdiff 86.75 pool/regression/scan PASS reverted
start (27, 36)
improved (27, 34)
improved (27, 33)
improved (27, 32)
improved (27, 26)
best (27, 26) after 33 builds; kept in source:
Final restored (86, 84, 84)

## pdm_part_get_start_sector
Origin d9fbf88fb8fcce715fab661f1fe8be49f007efcd, source identical
Diagnosis: 276/276; endian macro operand association and load scheduling differ, preserved frame and control flow. Target reads middle bytes of several partitions first; grouping words affects scheduler.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (276, 276, 146)
1. use grouped high and low half endian addition at call sites: (276, 276, 140) objdiff 83.10507 pool/regression/scan PASS retained for further trials
2. interleave start and length array initialization by partition: (276, 276, 145) objdiff 83.065216 pool/regression/scan PASS reverted
3. separate requested partition declaration from member load: (276, 276, 140) objdiff 83.10507 pool/regression/scan PASS reverted
Final restored (276, 276, 146)

## pdm_part_chg_ltop
Origin d9fbf88fb8fcce715fab661f1fe8be49f007efcd, source identical
Diagnosis: 51/51; ratio and adjusted start exchange r0/r3 only. No structural differences. Try ratio lifetime/width then declaration search.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 51, 16)
1. load media ratio before start sector: (51, 51, 16) objdiff 97.84314 pool/regression/scan PASS reverted
2. use separate logical and physical sector ratios: compile failed 
3. commute the final logical-sector addition: (51, 51, 16) objdiff 97.745094 pool/regression/scan PASS reverted
Final restored (51, 51, 16)
Origin c8bb9f44da1ea63d0dad0a388957bcb5a4150fab, source identical
Diagnosis: Third compiling variation separates logical ratio lifetime with leading C declarations.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 51, 16)
1. separate leading declaration for logical ratio: (51, 51, 16) objdiff 97.84314 pool/regression/scan PASS reverted
Register-only declaration search
Final restored (51, 51, 16)
Origin 17407ed1cbfa5f7f43ebd141902ceea0c73a1e64, source identical
Diagnosis: Structural source attempts exhausted; use declaration permutation search for remaining r0/r3 assignment.
POOL IDENTICAL up to 0 (mine=0 base=0)
Initial (51, 51, 16)
Register-only declaration search
start (0, 16)
best (0, 16) after 6 builds; source restored; best order was:
Final restored (51, 51, 16)

## AESiEncryptBlock
Origin 0d75b24a9634b51dd5a74eb4d7ce09dea02d681b, source identical
Diagnosis: 158/158; same 64-byte frame, four-word round and decrement branch. Target associates byte3/byte2 then byte1 then byte0 and round key; ours schedules final byte with byte1 separately. Operand association and local lifetime first.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (158, 158, 134)
1. combine each round key into its corresponding next-word temporary: (158, 158, 137) objdiff 52.829113 pool/regression/scan PASS reverted
2. group each round lookup into high and low byte pairs: (158, 158, 134) objdiff 60.348103 pool/regression/scan PASS reverted
3. declare all next state words before round expressions: (158, 158, 134) objdiff 60.348103 pool/regression/scan PASS reverted
Final restored (158, 158, 134)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: Round key first XOR association and final substitution key-first association follow target merge order. Prior structural variants unchanged or regressed; these move operand roots.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (158, 158, 134)
1. put round key at the XOR expression root: (158, 158, 137) objdiff 52.829113 pool/regression/scan PASS reverted
2. put final round key before substituted bytes: (158, 158, 134) objdiff 60.348103 pool/regression/scan PASS reverted
Final restored (158, 158, 134)

## AESiDecryptBlock
Origin 0d75b24a9634b51dd5a74eb4d7ce09dea02d681b, source identical
Diagnosis: 251 target; two-word unrolled key transform and same round frame. Target mix algebra uses successive xor-and-rotate stages; ours equivalent association changes scheduling. Round lookup differs as encryption.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (249, 251, 244)
1. combine each round key into its corresponding next-word temporary: (249, 251, 244) objdiff 62.063744 pool/regression/scan PASS reverted
2. group each round lookup into high and low byte pairs: (249, 251, 244) objdiff 61.49004 pool/regression/scan PASS reverted
3. declare all next state words before round expressions: (249, 251, 244) objdiff 61.49004 pool/regression/scan PASS reverted
Final restored (249, 251, 244)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: Round key first XOR association and final substitution key-first association follow target merge order. Prior structural variants unchanged or regressed; these move operand roots.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (249, 251, 244)
1. put round key at the XOR expression root: (249, 251, 244) objdiff 62.063744 pool/regression/scan PASS reverted

## NETAESCreateEx
Origin 0d75b24a9634b51dd5a74eb4d7ce09dea02d681b, source identical
Diagnosis: 107/108; target key word count recomputed after memcpy from saved keyLength; target rotate-substitute bytes associated in a different operand order. Independent declaration/operation lifetime first.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (107, 108, 81)
1. compute schedule word count after memcpy: (107, 108, 81) objdiff 88.98148 pool/regression/scan PASS reverted
2. substitute rotated key bytes explicitly in target operand order: (107, 108, 81) objdiff 90.18519 pool/regression/scan PASS reverted
3. declare schedule before key expansion scalars: (107, 108, 81) objdiff 88.98148 pool/regression/scan PASS reverted
Final restored (107, 108, 81)
Origin a81b7c36fe25993fac3ad2a3009f16839aed40ec, source identical
Diagnosis: Target round count truncates to 8-bit before context store, then separately computes untruncated word count after memcpy. Factor the derived round count into typed temporary to avoid reused division.
POOL IDENTICAL up to 4 (mine=4 base=4)
Initial (107, 108, 81)
1. use 8 bit round count before context store: (107, 108, 81) objdiff 88.98148 pool/regression/scan PASS reverted
2. initialize word count independently after retaining context round count: (114, 108, 111) objdiff 72.99074 pool/regression/scan PASS reverted
3. use signed key word count matching SDK length domain: (107, 108, 81) objdiff 88.47222 pool/regression/scan PASS reverted
Final restored (107, 108, 81)

## Final open-function audit
setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode: 99.04762%, 3 compiling source trials; one extra move initializes the defined fallback; target default path appears uninitialized, preserved defined behavior.
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb: 99.081635%, 7 compiling source trials; inline setter flags and owner registers r4/r6 exchanged after structural and declaration trials.
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 98.84615%, 3 compiling source trials; inline setter flags and owner registers r4/r6 exchanged after structural and declaration trials.
pdm_part_is_master_boot_sector: 86.5%, 5 compiling source trials; endian byte-load association changes frame and saved registers; staged loads can fix frame but not schedule.
pdm_part_get_start_sector: 82.56159%, 3 compiling source trials; endian extraction load schedule and scalar register allocation.
pdm_part_chg_ltop: 97.84314%, 3 compiling source trials; ratio/start r0/r3 exchange; declsearch six orders unchanged.
__InitParams: 69.9127%, 7 compiling source trials; floating scheduling, compare operand order and state-store scheduling; 126 instructions each.
__CalcLFO: 68.53846%, 7 compiling source trials; signed 64-bit gradient multiplication boundary, shifted sample lifetime and loop scheduling.
AESiEncryptBlock: 60.348103%, 5 compiling source trials; round lookup/XOR operand association and temporary lifetimes; 158 instructions each.
AESiDecryptBlock: 61.49004%, 4 compiling source trials; key-transform algebra scheduling and round lookup/XOR operand association; 249 versus 251 instructions.
NETAESCreateEx: 88.98148%, 6 compiling source trials; derived word-count lifetime and key-substitution operand scheduling; 107 versus 108 instructions.

## Accepted instruction-exact results
getControlKey__Q49textinput8keyboard6pctype4BaseFPc
src 0x90 base 0x90 insns 36/36
diffs 0: []
AXFXChorusExpCallback
src 0x360 base 0x360 insns 216/216
diffs 0: []
AXFXChorusExpShutdown
src 0x90 base 0x90 insns 36/36
diffs 0: []

## Before -> after, instruction exact / matched code bytes / matched data bytes
tiPcKeyboard: 137/141 -> 138/141; 27568 -> 27712; 18548 -> 18548
pdm_partition: 17/20 -> 17/20; 2072 -> 2072; no data section
AXFXChorusExp: 3/7 -> 5/7; 912 -> 1920; 48 -> 48
aes: 6/9 -> 6/9; 684 -> 684; 2800 -> 2800

## Final full gate, all four units
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiPcKeyboard] pool: IDENTICAL
[src/keyboard/tiPcKeyboard] objdiff: code 27712/28484 data 18548/18564 functions 138/141 fuzzy 99.9733 linked code 0
[src/keyboard/tiPcKeyboard] instruction-exact functions: 138/141
[src/keyboard/tiPcKeyboard]   section .bss size 16 match None
[src/keyboard/tiPcKeyboard]   section .ctors size 4 match 100.0
[src/keyboard/tiPcKeyboard]   section .data size 12576 match 100.0
[src/keyboard/tiPcKeyboard]   section .rodata size 5816 match 100.0
[src/keyboard/tiPcKeyboard]   section .sbss size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata size 136 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata2 size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .text size 28484 match 99.97332
[src/keyboard/tiPcKeyboard]   below 100: setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode 99.04762
[src/keyboard/tiPcKeyboard]   below 100: onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb 99.081635
[src/keyboard/tiPcKeyboard]   below 100: onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv 98.84615
[src/keyboard/tiPcKeyboard] baseline: code 27568/28484 data 18548 functions 137 fuzzy 99.9396
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2072/3716 data None/None functions 17/20 fuzzy 93.4801 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 17/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 93.48009
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_get_start_sector 82.56159
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_chg_ltop 97.84314
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 2072/3716 data None functions 17 fuzzy 93.4801
[libs/RVL_SDK/src/axfx/AXFXChorusExp] pool: IDENTICAL
[libs/RVL_SDK/src/axfx/AXFXChorusExp] objdiff: code 1920/2684 data 48/48 functions 5/7 fuzzy 91.3025 linked code 0
[libs/RVL_SDK/src/axfx/AXFXChorusExp] instruction-exact functions: 5/7
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   section .sdata2 size 48 match 100.0
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   section .text size 2684 match 91.302536
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   below 100: __InitParams 69.9127
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   below 100: __CalcLFO 68.53846
[libs/RVL_SDK/src/axfx/AXFXChorusExp] baseline: code 912/2684 data 48 functions 3 fuzzy 87.7615
[libs/RevoEX/src/net/aes] pool: IDENTICAL
[libs/RevoEX/src/net/aes] objdiff: code 684/2752 data 2800/2800 functions 6/9 fuzzy 75.1148 linked code 0
[libs/RevoEX/src/net/aes] instruction-exact functions: 6/9
[libs/RevoEX/src/net/aes]   section .data size 200 match 100.0
[libs/RevoEX/src/net/aes]   section .rodata size 2592 match 100.0
[libs/RevoEX/src/net/aes]   section .sdata2 size 8 match 100.0
[libs/RevoEX/src/net/aes]   section .text size 2752 match 75.11482
[libs/RevoEX/src/net/aes]   below 100: AESiEncryptBlock 60.348103
[libs/RevoEX/src/net/aes]   below 100: AESiDecryptBlock 61.49004
[libs/RevoEX/src/net/aes]   below 100: NETAESCreateEx 88.98148
[libs/RevoEX/src/net/aes] baseline: code 684/2752 data 2800 functions 6 fuzzy 75.1148
regressions vs baseline: 0
global matched_code_percent: 87.99755 -> 88.03601
global fuzzy_match_percent: 99.37608 -> 99.37956
global complete_code_percent: 62.37071 -> 62.37071
global matched_data_percent: 92.06847 -> 92.06847
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS


## Source commits
6cc459c4 match axfxchorusexpcallback
c10cacbe match axfxchorusexpshutdown
21811470 match base::getcontrolkey

## Uncertainty
The enum default path appears uninitialized in the target; no undefined fallback was introduced. The exact LFO source boundary responsible for its expanded 64-bit gradient multiplication remains unresolved.
