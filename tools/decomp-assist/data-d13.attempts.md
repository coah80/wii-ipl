# data-d13 attempts

Scope: BS2Mach, zi8cgetc, zi8alpha, zi81key. Baseline HEAD 0c94076d; origin/main fetched and scoped diff empty before work. All four pools identical. Before gate PASS, no regressions, retail DOL SHA1 correct.

## zi8alpha
- Rename/extent proof: .text relocations 0x84A HA and 0x84E LO in Zi8_814659E8 load target lbl_81617EA4 and source FrenchExcludePairs, both .rodata offset 0x104. Seven ZiExclusionPair records are 10 bytes each, target/source first 70 bytes identical, trailing six target bytes zero alignment before next unit at 0x81617EF0. Rename to FrenchExcludePairs and correct 76 to 70 bytes; address and split totals unchanged.

## ELF audit src/BS2/BS2Mach
obj non-text sizes: .bss=155232, .data=3024, .sdata=32, .sbss=240
- obj jumptable_8164619C .data+0x3f4 size 52 loaded by CheckDVDCommandStatus+0x5a, CheckDVDCommandStatus+0x62; entries 13; target functions CheckDVDCommandStatus
- obj jumptable_81646338 .data+0x590 size 184 loaded by CheckBS2CommandStatus+0xda, CheckBS2CommandStatus+0xe2; entries 46; target functions CheckBS2CommandStatus
- obj jumptable_816467F4 .data+0xa4c size 92 loaded by BS2Tick+0x12c2, BS2Tick+0x12ca; entries 23; target functions BS2Tick
- obj jumptable_81646850 .data+0xaa8 size 292 loaded by BS2Tick+0x3e, BS2Tick+0x46; entries 73; target functions BS2Tick
src non-text sizes: .data=3020, .bss=155232, .sdata=32, .sbss=236
- src @3618 .data+0x3f4 size 52 loaded by CheckDVDCommandStatus+0x5a, CheckDVDCommandStatus+0x62; entries 13; target functions CheckDVDCommandStatus
- src @3695 .data+0x590 size 184 loaded by CheckBS2CommandStatus+0xda, CheckBS2CommandStatus+0xe2; entries 46; target functions CheckBS2CommandStatus
- src @3972 .data+0xaa8 size 292 loaded by BS2Tick+0x3e, BS2Tick+0x46; entries 73; target functions BS2Tick
- src @3973 .data+0xa4c size 92 loaded by BS2Tick+0x12ae, BS2Tick+0x12b6; entries 23; target functions BS2Tick

## ELF audit libs/RVLMiddleware/eZiText/src/clib/zi8cgetc
obj non-text sizes: extab=48, extabindex=72, .data=392, .sdata2=16, .sbss2=8
- obj jumptable_8166AA88 .data+0x0 size 44 loaded by zi8InternalGetZH+0x76d2, zi8InternalGetZH+0x76d6; entries 11; target functions zi8InternalGetZH
- obj jumptable_8166AAB4 .data+0x2c size 44 loaded by zi8InternalGetZH+0x5436, zi8InternalGetZH+0x543a; entries 11; target functions zi8InternalGetZH
- obj jumptable_8166AAE0 .data+0x58 size 160 loaded by zi8InternalGetZH+0x11be, zi8InternalGetZH+0x11c2; entries 40; target functions zi8InternalGetZH
- obj jumptable_8166AB80 .data+0xf8 size 144 loaded by zi8InternalGetZH+0x102e, zi8InternalGetZH+0x1032; entries 36; target functions zi8InternalGetZH
src non-text sizes: extab=48, extabindex=72, .data=392, .sdata2=16, .sbss2=8
- src @2792 .data+0xf8 size 144 loaded by zi8InternalGetZH+0x1032, zi8InternalGetZH+0x1036; entries 36; target functions zi8InternalGetZH
- src @2793 .data+0x58 size 160 loaded by zi8InternalGetZH+0x11c2, zi8InternalGetZH+0x11c6; entries 40; target functions zi8InternalGetZH
- src @2794 .data+0x2c size 44 loaded by zi8InternalGetZH+0x543e, zi8InternalGetZH+0x5442; entries 11; target functions zi8InternalGetZH
- src @2795 .data+0x0 size 44 loaded by zi8InternalGetZH+0x76d6, zi8InternalGetZH+0x76da; entries 11; target functions zi8InternalGetZH

## ELF audit libs/RVLMiddleware/eZiText/src/clib/zi8alpha
obj non-text sizes: extab=72, extabindex=108, .rodata=336, .data=48
- obj jumptable_8166AA58 .data+0x0 size 48 loaded by Zi8AlphaGetCandidates+0x18b2, Zi8AlphaGetCandidates+0x18b6; entries 12; target functions Zi8AlphaGetCandidates
src non-text sizes: extab=72, extabindex=108, .rodata=330, .data=48
- src @1527 .data+0x0 size 48 loaded by Zi8AlphaGetCandidates+0x18ae, Zi8AlphaGetCandidates+0x18b2; entries 12; target functions Zi8AlphaGetCandidates

## ELF audit libs/RVLMiddleware/eZiText/src/clib/zi81key
obj non-text sizes: extab=72, extabindex=108, .rodata=1152, .data=48, .sdata2=8
- obj jumptable_8166AA28 .data+0x0 size 44 loaded by Zi8Get1KeyPressCandidates+0x3aa, Zi8Get1KeyPressCandidates+0x3ae; entries 11; target functions Zi8Get1KeyPressCandidates
- obj extabindex function extents [492, 628, 388, 1364, 200, 324, 6800, 9588, 1676]
src non-text sizes: extab=72, extabindex=108, .rodata=1152, .data=44, .sdata2=8
- src @1359 .data+0x0 size 44 loaded by Zi8Get1KeyPressCandidates+0x3aa, Zi8Get1KeyPressCandidates+0x3ae; entries 11; target functions Zi8Get1KeyPressCandidates
- src extabindex function extents [492, 628, 388, 1364, 200, 324, 6796, 9548, 1676]

Rename-only control, original 76-byte extent: {"fuzzy_match_percent": 94.17153, "total_code": "21664", "matched_code": "5704", "matched_code_percent": 26.329395, "total_data": "564", "matched_data": "180", "matched_data_percent": 31.914892, "total_functions": 12, "matched_functions": 10, "matched_functions_percent": 83.33333, "total_units": 1}; [{"name": ".data", "size": "48", "metadata": {}}, {"name": ".rodata", "size": "336", "fuzzy_match_percent": 99.0991, "metadata": {}}, {"name": ".text", "size": "21664", "fuzzy_match_percent": 94.17153, "metadata": {}}, {"name": "extab", "size": "72", "fuzzy_match_percent": 100.0, "metadata": {}}, {"name": "extabindex", "size": "108", "fuzzy_match_percent": 100.0, "metadata": {}}]

Extent-only control, extracted name: {"fuzzy_match_percent": 94.17153, "total_code": "21664", "matched_code": "5704", "matched_code_percent": 26.329395, "total_data": "564", "matched_data": "516", "matched_data_percent": 91.489365, "total_functions": 12, "matched_functions": 10, "matched_functions_percent": 83.33333, "total_units": 1}; [{"name": ".data", "size": "48", "metadata": {}}, {"name": ".rodata", "size": "336", "fuzzy_match_percent": 100.0, "metadata": {}}, {"name": ".text", "size": "21664", "fuzzy_match_percent": 94.17153, "metadata": {}}, {"name": "extab", "size": "72", "fuzzy_match_percent": 100.0, "metadata": {}}, {"name": "extabindex", "size": "108", "fuzzy_match_percent": 100.0, "metadata": {}}]

## Classification and scope boundary

BS2Mach: .bss/.sdata/.sbss already 100%. Target .data string objects at offsets 0x0, 0x22, 0x3C, 0x428, 0x452, 0x648, 0x669 are anonymous compiler string-pool ranges, several containing multiple literals. All 91 ordinary literal contents and offsets agree. Source symbols are compiler-generated @ identifiers, not real typed object names. Do not rename these extracted objects to unstable compiler identifiers or shrink aggregate pool extents. Four jump tables are compiler-generated switch data. The CheckDVDCommandStatus table has an exact owning function; remaining tables have code-relative relocations into non-exact CheckBS2CommandStatus and BS2Tick. No safe real-name correction exists for any remaining .data symbol. Four trailing .data bytes and four trailing .sbss bytes are split alignment, not missing objects.

zi8cgetc: .sdata2/.sbss2/extab/extabindex already 100%. All four .data objects are switch tables whose entries relocate into non-exact zi8InternalGetZH; same table offsets/sizes, displaced basic blocks. Matching these requires code work. No real named object or initializer is missing. Compiler @ names are not authorized rename targets.

zi8alpha: .rodata now 100%, extab/extabindex already 100%. Remaining 48-byte .data object is a 12-entry switch table owned by non-exact Zi8AlphaGetCandidates. Its code-relative relocation destinations require code matching, not a data extent change. No ordinary initializer difference remains.

zi81key: .rodata/.data/.sdata2/extab already 100%. Only extabindex differs, exactly at function-size fields for Zi8Get1KeyPressSpelling (source 6796, target 6800) and Zi8Get1KeyPressCandidates (source 9548, target 9588). These are genuine generated code-length fields. Never edit function extents or unwind data to disguise missing instructions. Source tables and type names already agree. No data edit can resolve these lengths.

Control results: extent correction alone restores .rodata 100% and matched_data 180 -> 516; name-only correction does not. Both are retained because the HA/LO relocation proof identifies the actual FrenchExcludePairs object. No source change is required. Data total remains 564, split endpoints remain unchanged, and the six alignment bytes remain unowned by the corrected symbol.

## Open-function attempt coverage inherited from tracked logs

No source tuning is undertaken in this data assignment. All open functions already have at least three measured, distinct source attempts recorded in tracked logs; the summaries below preserve that coverage without repeating rejected experiments.

BS2Mach.attempts.md, Remaining-function attempt coverage:
- Run: per-block do/while cache calls; counted for loop; bulk cache zero/flush. Register-clearing trampoline remains outside portable C.
- BS2StartGame: target-shaped nested error branches; switch result dispatch; nested polling via DVD status APIs. Calls/reloads/scheduling remain.
- BS2StartGCGame: config/SRAM/MIOS implementation; reversed multiply operands with 64-bit MIOS vararg; separate timer locals and DVD polling. Reload/scheduling remains.
- CheckBS2CommandStatus: per-state paths/shared exit; direct returns; precompute chunk length. Reload/scheduling remains.
- BS2Tick: object-order state switch; typed disk/partition scan; region switch plus forward ticket scan. State branch/register scheduling remains.

zi8cgetc.current.attempts.md:
- ZiMatchZHSpelling: unsigned candidate character length; long spelling match result; long candidate character length; 18 measured trials, register-only plateau.
- zi8InternalGetZH: initialize all engine locals at declaration; charset-only declaration initialization; phase/output-index declaration initialization; 19 initial measured trials plus relocation-aware g20-g22 fixes. Engine register choices/call-result moves remain.
- Zi8GetElementCount: explicit remaining-character condition; direct separator local; compound count increments; 12 measured trials, register-only plateau.

zi8alpha.attempts.md:
- Zi8ChangeWordCase: integer case flag; byte case flag; separate flag declaration/assignment. Register-only plateau.
- Zi8AlphaGetCandidates: reverse declarations; five byte state flags; explicit phonetic separator switch. Many subsequent complete-body improvements landed; current branch/register differences remain.

zi81key.attempts.md:
- Zi8SpellingZY: flat row indexing; typed row pointer; generic output formal. Six register differences remain.
- Zi8SpellingPY: initialize length before components; signed tone; decode tone after spelling rows. Later work improved it, current register allocation remains.
- Zi8Get1KeyPressSpelling: compound cursor postincrement; constant-first language tests; index increment in for header. One missing instruction and fallback-call scheduling remain.
- Zi8Get1KeyPressCandidates: halfword key/byte length formals; explicit PCode halfword casts/masks; preincrement capacity comparisons. Ten missing instructions and scheduling remain.

Data goal is not complete. No prohibited symbol renames, guessed objects, padding, forced sections, code-size changes, or assembly were used. This candidate is a focused 336-byte data-measure gain and leaves every instruction-exact count unchanged.

## Final fresh validation

BS2Mach pool contents AND offsets identical for all 91 strings. French table reader Zi8_814659E8: ctxdiff 51/51 instructions, diffs 0.

- main/src/BS2/BS2Mach: exact functions 24 -> 24, code 4940 -> 4940, data 155504 -> 155504 / 158528.
  - Open Run 16.744186%; prior distinct source-attempt coverage listed above.
  - Open BS2StartGame 95.496185%; prior distinct source-attempt coverage listed above.
  - Open BS2StartGCGame 99.5614%; prior distinct source-attempt coverage listed above.
  - Open CheckBS2CommandStatus 99.50739%; prior distinct source-attempt coverage listed above.
  - Open BS2Tick 98.15876%; prior distinct source-attempt coverage listed above.
- main/libs/RVLMiddleware/eZiText/src/clib/zi81key: exact functions 5 -> 5, code 3952 -> 3952, data 1280 -> 1280 / 1388.
  - Open Zi8SpellingZY 99.756096%; prior distinct source-attempt coverage listed above.
  - Open Zi8SpellingPY 99.36306%; prior distinct source-attempt coverage listed above.
  - Open Zi8Get1KeyPressSpelling 97.92647%; prior distinct source-attempt coverage listed above.
  - Open Zi8Get1KeyPressCandidates 95.39716%; prior distinct source-attempt coverage listed above.
- main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha: exact functions 10 -> 10, code 5704 -> 5704, data 180 -> 516 / 564.
  - Open Zi8ChangeWordCase 99.09091%; prior distinct source-attempt coverage listed above.
  - Open Zi8AlphaGetCandidates 92.01039%; prior distinct source-attempt coverage listed above.
- main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc: exact functions 5 -> 5, code 4168 -> 4168, data 144 -> 144 / 536.
  - Open ZiMatchZHSpelling 98.80165%; prior distinct source-attempt coverage listed above.
  - Open zi8InternalGetZH 95.99054%; prior distinct source-attempt coverage listed above.
  - Open Zi8GetElementCount 99.347824%; prior distinct source-attempt coverage listed above.

Final non-quick gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4940/16980 data 155504/158528 functions 24/29 fuzzy 97.8276 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 24/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 97.82756
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 95.496185
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 98.15876
[src/BS2/BS2Mach] baseline: code 4940/16980 data 155504 functions 24 fuzzy 97.8276
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.4008 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 96.40079
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 95.99054
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.4008
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] objdiff: code 5704/21664 data 516/564 functions 10/12 fuzzy 94.1715 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] instruction-exact functions: 10/12
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .rodata size 336 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .text size 21664 match 94.17153
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extabindex size 108 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   below 100: Zi8ChangeWordCase 99.09091
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   below 100: Zi8AlphaGetCandidates 92.01039
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] baseline: code 5704/21664 data 180 functions 10 fuzzy 94.1715
[libs/RVLMiddleware/eZiText/src/clib/zi81key] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi81key] objdiff: code 3952/21460 data 1280/1388 functions 5/9 fuzzy 97.2622 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi81key] instruction-exact functions: 5/9
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .data size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .rodata size 1152 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .text size 21460 match 97.26225
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extabindex size 108 match 98.14815
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingZY 99.756096
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingPY 99.36306
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressSpelling 97.92647
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressCandidates 95.39716
[libs/RVLMiddleware/eZiText/src/clib/zi81key] baseline: code 3952/21460 data 1280 functions 5 fuzzy 97.2622
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.18649 -> 98.20482
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
