# sz1 data layout attempts

Scope: zi81key, zkokeyp, zprepare, only the five assigned functions. Branch agent/w1004/sz1, starting commit f598e410. Existing untracked h8.attempts.md is left untouched and untracked. Read AGENTS.md, common.md, levers.md lever 14, ezi-insight.md, prior per-unit attempts, and unslop. No subagents or upstream actions.

Initial ninja build passes with DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. All three pools are identical with no strings. The differing function size words are in extabindex, not extab. All three extab sections already score 100%.

Baseline live report saved to /tmp/sz1/baseline.json. zi81key: matched code 3952/21460, data 1280/1388, exact functions 5/9. zkokeyp: 332/5200, data 96/180, exact 1/7. zprepare: 0/3760, data 8/68, exact 0/1. Counts: Spelling 1701/1700; Candidates 2405/2397; 814834AC 344/343; KOcandidates 671/669; PrepareMatch 936/940. No function percentage may fall from this baseline. The new success criterion is whole-section data gain with zero regressions.

## zi81key | Spelling preliminary trial: test compound candidateCount increment at target instruction 956

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

Checked the focused diff: the first compound increment was already in the correct function. Repeated scoped build confirmed it has no codegen effect; count it as one source attempt.

## zi81key | Spelling attempt 1: scoped compound increment for emitted spelling count

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 2: prefix candidate count increment

Zi8Get1KeyPressSpelling: 99.555885 -> 96.8%; instructions 1697/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 3: postfix candidate count increment

Zi8Get1KeyPressSpelling: 99.555885 -> 96.8%; instructions 1697/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 4: count increment with literal first

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 1: fold three count-only increments into capacity tests as in target

Zi8Get1KeyPressCandidates: 96.41927 -> 95.926155%; instructions 2394/2397; diffs unequal counts | unit data 1232/1388, exact 5/9 | section .data: 48 bytes, 0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 2: signed library-width total count matches maxCount type

Zi8Get1KeyPressCandidates: 96.41927 -> 96.41927%; instructions 2405/2397; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 3: signed library-width total with target compound capacity tests

Zi8Get1KeyPressCandidates: 96.41927 -> 95.926155%; instructions 2394/2397; diffs unequal counts | unit data 1232/1388, exact 5/9 | section .data: 48 bytes, 0% | section extabindex: 108 bytes, 98.14815%

## zkokeyp | 814834AC attempt 1: word and tail clears in a single comma expression

Zi8_814834AC: 99.3586 -> 98.9621%; instructions 345/343; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

## zkokeyp | 814834AC attempt 2: clear tail from initialized first byte

Zi8_814834AC: 99.3586 -> 99.3586%; instructions 344/343; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

## zkokeyp | 814834AC attempt 3: explicit byte conversion in chained clear

Zi8_814834AC: 99.3586 -> 99.3586%; instructions 344/343; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

Prior fz1 found 343 instructions when clearing from the actual zero loop index, but rejected it under the exact-code goal. Re-evaluate that source form for this round's whole-section data criterion and all-function percentage floor. This is an intentional change of acceptance criterion, not another exact-code search.

## zkokeyp | 814834AC attempt 4: evaluate prior zero scan-index initialization under data criterion

Zi8_814834AC: 99.3586 -> 99.052475%; instructions 343/343; diffs 23 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | KOcandidates attempt 1: chained packed-prefix and tail initialization

Zi8GetKOcandidates: 98.146484 -> 98.146484%; instructions 671/669; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

## zkokeyp | KOcandidates attempt 2: read-only word-table traversal pointers

Zi8GetKOcandidates: 98.146484 -> 98.146484%; instructions 671/669; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

## zkokeyp | KOcandidates attempt 3: packed-key clearing as one comma expression

Zi8GetKOcandidates: 98.146484 -> 97.74888%; instructions 672/669; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

Zi8PrepareMatch dead-store proof: target instructions 17-18 are li r0,0; stb r0,0xf(r1), immediately after Zi8Memset(match). Instructions 72-73 are li r0,1; stb r0,0xf(r1), inside the successful Zi8IsComponent arm immediately after elementIndex increments. No target instruction loads 0xf(r1). The byte is a plausible hasComponent flag, initially false and set only when a component is recognized. Restore these stores under the explicit -opt off never-read-store policy. No other object uses this local.

## zprepare | PrepareMatch attempt 1: restore target-proven component flag stores

Zi8PrepareMatch: 96.802124 -> 96.92021%; instructions 941/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 2: restore stroke-loop break and immediate success return

Zi8PrepareMatch: 96.802124 -> 97.15426%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 3: advance element index before phonetic length as in target

Zi8PrepareMatch: 96.802124 -> 97.24468%; instructions 944/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 4: body-local index then phonetic-length increments preserve the frame

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 5: typed workspace parameter for all call conversions

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 6: expanded component-index pointer update

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 7: naturally promoted component record stride

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 8: const lookup-table contents

Zi8PrepareMatch: 96.802124 -> 97.17021%; instructions 944/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 9: const componentIndex table contents alone

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 10: const component table contents alone

Zi8PrepareMatch: 96.802124 -> 97.17021%; instructions 944/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 11: const phoneticTable table contents alone

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 12: group adjacent byte input state in target stack order

Zi8PrepareMatch: 96.802124 -> 95.29149%; instructions 932/940; diffs unequal counts | unit data 0/68, exact 0/1 | section .data: 48 bytes, 0% | section extab: 8 bytes, 87.5% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 13: typed two-byte component-index records

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 14: split_component_assignment

Zi8PrepareMatch: 96.802124 -> 97.34042%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 15: component_assignment_outer_local

Zi8PrepareMatch: 96.802124 -> 97.354256%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 16: byte_nibble_assignment

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 17: phonetic_while_loop

Zi8PrepareMatch: 96.802124 -> 97.36702%; instructions 943/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 18: initialize each phonetic pair together in target store order

Zi8PrepareMatch: 96.802124 -> 97.106384%; instructions 940/940; diffs 709 | unit data 20/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 100.0%

## zprepare | PrepareMatch attempt 19: remove redundant halfword narrowing before six-bit index mask

Zi8PrepareMatch: 96.802124 -> 97.25%; instructions 938/940; diffs unequal counts | unit data 8/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 20: widen the masked high component-offset byte

Zi8PrepareMatch: 96.802124 -> 97.09574%; instructions 940/940; diffs 709 | unit data 20/68, exact 0/1 | section .data: 48 bytes, 0% | section extabindex: 12 bytes, 100.0%

## zprepare | PrepareMatch attempt 21: explicit component assignment with direct masked high byte

Zi8PrepareMatch: 96.802124 -> 96.99468%; instructions 939/940; diffs unequal counts | unit data 56/68, exact 0/1 | section .data: 48 bytes, 100.0% | section extabindex: 12 bytes, 91.66667%

## zprepare | PrepareMatch attempt 22: separate current phonetic initialization, paired best and previous state

Zi8PrepareMatch: 96.802124 -> 96.99468%; instructions 940/940; diffs 405 | unit data 68/68, exact 0/1 | section .data: 48 bytes, 100.0% | section extabindex: 12 bytes, 100.0%

Retained zprepare candidate: 68/68 matched data, all data sections 100%, instruction count 940/940, function 96.802124 -> 96.99468%. The code is not instruction-exact. Target-proven component stores, explicit element assignment, natural high-byte mask, stroke-loop break/return, index-before-length update, and paired best/previous initialization preserve behavior. Preserve /tmp/sz1/zprepare.gain60.c while other units continue.

## zkokeyp | 814834AC attempt 5: initialize matched count with packed-key tail

Zi8_814834AC: 99.3586 -> 99.02332%; instructions 343/343; diffs 25 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 6: natural_high_character_byte

Zi8_814834AC: 99.3586 -> 99.02332%; instructions 343/343; diffs 205 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 7: natural_low_character_byte

Zi8_814834AC: 99.3586 -> 99.067055%; instructions 343/343; diffs 211 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 8: compound_remaining_subtraction

Zi8_814834AC: 99.3586 -> 99.067055%; instructions 343/343; diffs 318 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 9: five-byte key array initialized at function entry

Zi8_814834AC: 99.3586 -> 98.74344%; instructions 343/343; diffs 60 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 10: five-byte array initialization after counters with original enclosing state

Build failed; rejected. #   Error:     ^^^^ #   (10141) expression syntax error

## zkokeyp | KOcandidates attempt 4: initialize paired word and prefix scan counters together

Zi8GetKOcandidates: 98.146484 -> 97.95216%; instructions 668/669; diffs unequal counts | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 97.61904%

## zkokeyp | KOcandidates attempt 5: initialize word_scan_pair together

Zi8GetKOcandidates: 98.146484 -> 98.87145%; instructions 669/669; diffs 83 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | KOcandidates attempt 6: initialize prefix_scan_pair together

Zi8GetKOcandidates: 98.146484 -> 98.8565%; instructions 669/669; diffs 93 | unit data 96/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 98.809525%

## zkokeyp | 814834AC attempt 11: declare initialized keys before filter state to preserve stack layout

Zi8_814834AC: 99.3586 -> 98.74344%; instructions 343/343; diffs 60 | unit data 180/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 100.0%

## zkokeyp | 814834AC attempt 12: flat real locals initialized in target order, followed by initialized key array

Zi8_814834AC: 99.3586 -> 99.65015%; instructions 343/343; diffs 21 | unit data 180/180, exact 1/7 | section .data: 40 bytes, 100.0% | section extabindex: 84 bytes, 100.0%

## zi81key | Spelling attempt 5: flatten phonetic-language conjunctions without changing evaluation order

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 6: initialize_counters_at_declaration

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 7: first_total_prefix

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 8: all_total_prefix

Zi8Get1KeyPressSpelling: 99.555885 -> 99.555885%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 9: generic_workspace_view

Zi8Get1KeyPressSpelling: 99.555885 -> 99.30294%; instructions 1702/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 10: paired_output_reset

Zi8Get1KeyPressSpelling: 99.555885 -> 95.747055%; instructions 1699/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 11: save_flags_before_count

Zi8Get1KeyPressSpelling: 99.555885 -> 99.55353%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 12: prefix_count_compound_spelling_index

Zi8Get1KeyPressSpelling: 99.555885 -> 99.67941%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 13: prefix_count_separate_terminator_advance

Zi8Get1KeyPressSpelling: 99.555885 -> 96.73235%; instructions 1698/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 14: prefix count and compound index with masked_phonetic_index_byte

Zi8Get1KeyPressSpelling: 99.555885 -> 98.14412%; instructions 1698/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 15: prefix count and compound index with natural_phonetic_high_byte

Zi8Get1KeyPressSpelling: 99.555885 -> 98.43235%; instructions 1699/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 16: prefix count and compound index with natural_element_index

Zi8Get1KeyPressSpelling: 99.555885 -> 99.67941%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 17: prefix count and compound index with natural_spelling_compare

Zi8Get1KeyPressSpelling: 99.555885 -> 99.67941%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 18: compound_first_phonetic_compare_index

Zi8Get1KeyPressSpelling: 99.555885 -> 98.67647%; instructions 1702/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 19: compound_second_phonetic_compare_index

Zi8Get1KeyPressSpelling: 99.555885 -> 99.03236%; instructions 1703/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 20: compound_trim_count

Zi8Get1KeyPressSpelling: 99.555885 -> 97.28236%; instructions 1703/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 21: compound_dictionary_candidate_count

Zi8Get1KeyPressSpelling: 99.555885 -> 99.50588%; instructions 1702/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 22: joint_count_initialization

Zi8Get1KeyPressSpelling: 99.555885 -> 99.64412%; instructions 1701/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Spelling attempt 23: dictionary_increment_natural_high_byte

Build failed; rejected. #   Error: ^^^^^ #   (10141) expression syntax error

## zi81key | Spelling attempt 24: dictionary_increment_natural_masked_index

Build failed; rejected. #   Error: ^^^^^ #   (10141) expression syntax error

## zi81key | Spelling attempt 23 corrected function boundary: dictionary_increment_natural_high_byte

Zi8Get1KeyPressSpelling: 99.555885 -> 98.47647%; instructions 1700/1700; diffs 1080 | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 99.07407%

## zi81key | Spelling attempt 24 corrected function boundary: dictionary_increment_natural_masked_index

Zi8Get1KeyPressSpelling: 99.555885 -> 98.18823%; instructions 1699/1700; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 4: fold only OEM count-only capacity test

Zi8Get1KeyPressCandidates: 96.41927 -> 96.17564%; instructions 2401/2397; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 5: fold only PUD count-only capacity test

Zi8Get1KeyPressCandidates: 96.41927 -> 95.725075%; instructions 2401/2397; diffs unequal counts | unit data 1232/1388, exact 5/9 | section .data: 48 bytes, 0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 6: fold only phrase count-only capacity test

Zi8Get1KeyPressCandidates: 96.41927 -> 95.93575%; instructions 2399/2397; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 7: null_optional_tables

Zi8Get1KeyPressCandidates: 96.41927 -> 95.64539%; instructions 2401/2397; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 8: zero_language_filters

Zi8Get1KeyPressCandidates: 96.41927 -> 95.65165%; instructions 2401/2397; diffs unequal counts | unit data 1280/1388, exact 5/9 | section .data: 48 bytes, 100.0% | section extabindex: 108 bytes, 98.14815%

## zi81key | Candidates attempt 9: paired_result_reset

Zi8Get1KeyPressCandidates: 96.41927 -> 95.74343%; instructions 2399/2397; diffs unequal counts | unit data 1232/1388, exact 5/9 | section .data: 48 bytes, 0% | section extabindex: 108 bytes, 98.14815%

## Final selection and open-function audit

zi81key restored completely. Spelling has 24 numbered source attempts, including two corrected build-script boundary errors; Candidates has 9 numbered attempts. Counts reached 1700 in Spelling but its score fell to 98.47647%, below the 99.555885% floor. The best nonregressing shape remained 1701 instructions and produced no whole-section data gain. Candidate counter, initialization and type trials also regressed percentage or existing .data matching. No zi81key changes are retained.

zkokeyp retains only 814834AC attempt 12 and KOcandidates attempt 5. The first function has 343/343 instructions, 99.65015%, with initialization stores and stack offsets identical to the target. Flattening real locals permits ordinary five-byte array initialization; no fabricated state or initialized padding was added. The second has 669/669 instructions, 98.87145%, after pairing the two word-scan counter initializations. The 84-byte extabindex is now 100%, raising matched data from 96 to 180. Other functions are unchanged.

zprepare retains attempt 22. Count 940/940, 96.99468%, .data 48 bytes, extab 8 bytes and extabindex 12 bytes all 100%. Every jump-table relocation now has the target function-relative case offset. Matched data rises 8 -> 68.

Assigned functions remaining open for the data goal: Spelling and Candidates only, both with at least three distinct compiled attempts. The three other assigned functions meet their data/layout goal but remain non-exact in code. Full matching of all five requested instruction counts was not achieved.

Behavior review: zero-initialized key bytes are identical to the previous word/tail initialization; only real local variables replace the filter aggregate. Paired zero assignments preserve both counter and phonetic values before any use. The component flag stores have target evidence above. The masked high byte is already 0..255, so removing its halfword cast changes no value. Splitting the component assignment preserves both destinations. Both phonetic-loop increments still occur after the same body paths; swapping independent increments changes no values. The stroke-loop break immediately returns the same value as the old common return. No shared headers, metadata, non-43U files, asm or linking configuration change.

## Final independent audit

Full live-report comparison against starting f598e410: 1027 units, zero per-function percentage regressions, zero exact/code/data/link regressions.
Changed report units: main/libs/RVLMiddleware/eZiText/src/clib/zkokeyp, main/libs/RVLMiddleware/eZiText/src/clib/zprepare
Global matched_data: 1831712 -> 1831856 bytes.
zkokeyp .data: 40 raw bytes identical; 10 canonical relocations identical.
zkokeyp extab: 56 raw bytes identical; 0 canonical relocations identical.
zkokeyp extabindex: 84 raw bytes identical; 14 canonical relocations identical.
zprepare .data: 48 raw bytes identical; 12 canonical relocations identical.
zprepare extab: 8 raw bytes identical; 0 canonical relocations identical.
zprepare extabindex: 12 raw bytes identical; 2 canonical relocations identical.
Zi8Get1KeyPressSpelling: src 0x1a94 base 0x1a90 insns 1701/1700
Zi8Get1KeyPressCandidates: src 0x2594 base 0x2574 insns 2405/2397
Zi8_814834AC: src 0x55c base 0x55c insns 343/343 diffs 21: [9, 19, 35, 56, 97, 103, 111, 120, 128, 204, 211, 249, 252, 258, 271, 274, 278, 281, 290, 292]
Zi8GetKOcandidates: src 0xa74 base 0xa74 insns 669/669 diffs 83: [15, 16, 17, 18, 93, 94, 96, 97, 98, 99, 100, 105, 106, 107, 108, 109, 110, 112, 113, 114]
Zi8PrepareMatch: src 0xeb0 base 0xeb0 insns 940/940 diffs 405: [11, 12, 17, 18, 20, 21, 22, 23, 25, 27, 28, 29, 30, 32, 33, 34, 48, 49, 52, 53]
zprepare src component-flag slot accesses: [(18, ('stb', 'r4, 0xf(r1)')), (74, ('stb', 'r0, 0xf(r1)'))]
zprepare obj component-flag slot accesses: [(18, ('stb', 'r0, 0xf(r1)')), (73, ('stb', 'r0, 0xf(r1)'))]

## Final clean gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi81key] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi81key] objdiff: code 3952/21460 data 1280/1388 functions 5/9 fuzzy 98.2352 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi81key] instruction-exact functions: 5/9
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .data size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .rodata size 1152 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .text size 21460 match 98.23523
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extabindex size 108 match 98.14815
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingZY 99.756096
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingPY 99.36306
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressSpelling 99.555885
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressCandidates 96.41927
[libs/RVLMiddleware/eZiText/src/clib/zi81key] baseline: code 3952/21460 data 1280 functions 5 fuzzy 98.2352
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] objdiff: code 332/5200 data 180/180 functions 1/7 fuzzy 99.1962 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] instruction-exact functions: 1/7
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .data size 40 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .text size 5200 match 99.19615
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extab size 56 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extabindex size 84 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_8148302C 99.49152
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483264 98.902435
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483308 99.13793
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814833F0 99.04256
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814834AC 99.65015
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8GetKOcandidates 98.87145
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] baseline: code 332/5200 data 96 functions 1 fuzzy 98.7462
[libs/RVLMiddleware/eZiText/src/clib/zprepare] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zprepare] objdiff: code None/3760 data 68/68 functions 0/1 fuzzy 96.9947 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zprepare] instruction-exact functions: 0/1
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .data size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .text size 3760 match 96.99468
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extab size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extabindex size 12 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   below 100: Zi8PrepareMatch 96.99468
[libs/RVLMiddleware/eZiText/src/clib/zprepare] baseline: code None/3760 data 8 functions 0 fuzzy 96.8021
regressions vs baseline: 0
global matched_code_percent: 92.59315 -> 92.59315
global fuzzy_match_percent: 99.74084 -> 99.74187
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.95482
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
