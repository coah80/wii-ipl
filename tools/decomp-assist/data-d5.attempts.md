# data-d5 data lane

Baseline 2026-10-02: HEAD and origin/main eecf16f0. All four owned sources equal origin/main before changes. Fresh object build and objdiff report saved in /tmp/data-d5-before.json; instruction-exact baseline in /tmp/data-d5-exact-before.json.

| Unit | matched data | total data | instruction exact |
| --- | ---: | ---: | ---: |
| SDChannelSelect | 224 | 2960 | 117/129 |
| ChannelSelect | 192 | 2336 | 101/102 |
| GCWindow | 248 | 2032 | 47/48 |
| SDMemory | 200 | 3344 | 63/66 |

Pool-first audit: SDChannelSelect 101/101, GCWindow 50/50 and SDMemory 90/90 strings identical. ChannelSelect first divergence index 91, offset 0x653, duplicates WSD_SELECT after its earlier ordinary literal at 0x524. Relocation audit found SDMemory title-pane table at .data+0xc targets A,B,C,D,B_BtnA; source instead uses A,B,B_BtnA,C,D. Correct the typed table initializer.

All raw shared .data bytes already equal for SDChannelSelect, GCWindow and SDMemory. Their unequal section scores also involve coarse extracted symbol boundaries and deduplicated weak data. A raw-byte comparison alone does not prove relocations match. No symbols or splits have been changed.

## SDMemory

Fetched origin before starting; no source changes on origin/main. Attempt 1: corrected the real five-entry title-pane table to A,B,C,D,B_BtnA. Target .data+0x14/+0x18/+0x1c relocations name the corresponding C,D,B_BtnA .sdata literals. Source and target now have identical literal bytes and table targets. Quick gate: data 200 -> 3344/3344, every data section 100%; instruction-exact 63/66 unchanged, objdiff-exact 64/66 unchanged, regressions 0, GATE PASS. No additional data objects or ownership edits needed.

## ChannelSelect

Fetched origin before starting; no source changes on origin/main. Attempt 1: moved the real scSE_WSD_SELECT definition before preparePageScrolling and referenced that object instead of producing another identical literal. Pool 99/98 -> 98/98 strings, identical; .data raw shared bytes now identical. .data objdiff 32.810795 -> 95.60976; instruction-exact 101/102 unchanged. Remaining semantic reloc differences are exclusively weak interpolation/gui vtables, not strings, arrays or live ChannelSelect/event-handler vtable entries. Source .data 2140 versus target 2144 is trailing linker alignment; source .sdata 73 versus target 80 and .sbss 4 versus 8 also contain only trailing zero alignment. No artificial objects added to fill these gaps.

Full clean gate over all four units: GATE PASS, full build ok, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, regressions 0, forbidden patterns 0, readability problems 0. SDMemory all non-text sections 100% and matched_data 3344/3344. Instruction-exact counts remain 117,101,47,63. Source review is three changed lines plus moving one existing definition.

## GCWindow

Fetched origin before starting; no source changes on origin/main. Target nm shows LinearIntp<VEC3> destructor and vtable undefined, while the source instantiated a weak LinearIntp vtable at .data+0x650 and Interporation vtable at +0x660, displacing the real MemCardEventHandler vtable from +0x650 to +0x670. These are explicit-specialization ownership differences rather than missing arrays. The existing LinearIntp constructor is instruction-exact, 4/4 instructions, diffs 0.

Attempt 1: declare the concrete LinearIntp<VEC3> specialization with an out-of-line destructor, preserving Interporation<VEC3> inheritance. First compilation exposed earlier include order, fixed by including math types under the same GCWindow-only macro. Real MemCardEventHandler vtable returned to +0x650; .data 16.997168 -> 99.55357. The remaining weak Interporation vtable moved to the end. All 47 baseline exact functions preserved.

Attempt 2: declare the corresponding concrete Interporation<VEC3> specialization with an out-of-line destructor, keeping its existing fields, initialization and accessors. Both interpolation vtables now have external ownership as the target's LinearIntp relocation proves; no fake zero tables, section attributes or forced references. .data 100%, data 248 -> 2032/2032; all other data sections remain 100%, instruction-exact 47/48 unchanged. Semantic relocations in .data, .rodata and .sdata now agree fully. Every shared-header change is under IPL_GC_WINDOW_CPP, defined only by the owned GCWindow.cpp.

## SDChannelSelect

Fetched origin before starting; no source changes on origin/main. Pool 101/101 identical. All raw shared bytes of .data, .rodata, .sdata and .sdata2 identical. All non-text semantic relocations before .data+0x960 identical, including every pane-name array, dialog page and compiler switch table. Live button/event/scene vtables start at target 0x980/0x99c/0x9b4 versus source 0x960/0x97c/0x994. Target .data+0x960..0x980 is all zero and has no relocation or symbol. Target trailing deduplicated GUI vtables have zero bytes and no relocations, while source emits real weak PaneManager/EventHandler/Interface vtables. No artificial gap object is permitted.

Attempt 1: HermiteIntp<VEC3> specialization inherited the existing Interporation<VEC3> and defined its destructor inline. Preserved all 117 exact functions but generated the two weak vtables at the end, not in the target's earlier anonymous 32-byte gap. .data stayed 35.06984, matched_data 224. Reverted.

Attempt 2: use the primary HermiteIntp template with a VEC3 member-init specialization declaration. Preserved 117 exact functions but instantiated init and weak vtables at the end. .data stayed 35.06984, matched_data 224. Reverted because ownership was less faithful to the target's undefined init symbol.

Attempt 3: retain concrete HermiteIntp<VEC3> destructor/init out of line but inherit Interporation<VEC3>. Preserved 117 exact functions; only the intermediate weak vtable was emitted at the end. .data stayed 35.06984, matched_data 224. Reverted.

Symbol investigation: renamed the two event-handler and scene vtable symbols without changing their extents, using their function-pointer relocations as evidence; .data reached 43.61462, no matched-data gain. Also experimentally split the BaseMask4/Picture_04/ClockPane2 literal-plus-array aggregates at their proven literal lengths and five-/three-pointer table boundaries, preserving section bytes, lengths and all relocations; .data reached 56.610638, no matched-data gain. Reverted all symbols changes. Do not confuse symbol-scoring improvements with exact bytes or acceptance. The anonymous zero gap's exact ownership is not proven, so it remains open rather than being filled with fabricated data.

## Data-lane completion audit

SDMemory and GCWindow have every non-text section at 100% and matched_data equal total_data. ChannelSelect has identical zero-extended raw non-text section bytes and identical live relocations; remaining .data score 95.60976 comes solely from linker-deduplicated weak interpolation/gui data. Per task step 4, record this extraction limitation instead of deleting correct weak tables or adding zeros. SDChannelSelect has three distinct typed-class attempts plus relocation-backed symbol experiments; its missing anonymous 32-byte zero range and shifted live vtable placement remain unresolved. The code-only non-matches are outside this data-lane assignment and have not been changed.

ChannelSelect attempt 2: preserved the Hermite primary template but inherited FrameController directly, with the existing start/end fields instead of the intermediate Interporation base. The intermediate weak vtable disappeared and shifted live event/scene vtables by 16 bytes; .data fell from 95.60976 to 32.810795 despite 101 instruction-exact functions remaining. Reverted.

ChannelSelect attempt 3: kept the VEC3 interpolation hierarchy and declared the concrete f32 Hermite specialization with its real fields/init/get and out-of-line destructor, matching the target's external f32 vtable ownership. .data rose to 96.36185, but compiler literal ordering changed .sdata2 to 88.63636 and instruction-exact functions fell 101 -> 100, objdiff code 24736 -> 24272, data 192 -> 104. Rejected and reverted immediately. No failing experiment was committed.

All three remaining-data source attempts are recorded for ChannelSelect and SDChannelSelect. GCWindow data is exact after two attempts; SDMemory data is exact after one initializer correction. No code decompilation was undertaken in this lane.

## Final clean gate

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 27108/33828 data 224/2960 functions 117/129 fuzzy 99.5051 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 117/129
[src/scene/channelSelect/iplChannelSelect] objdiff: code 24736/25668 data 192/2336 functions 101/102 fuzzy 99.7634 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 101/102
[src/scene/memoryCard/iplGCWindow] objdiff: code 9172/9964 data 2032/2032 functions 47/48 fuzzy 99.8398 linked code 0
[src/scene/memoryCard/iplGCWindow] instruction-exact functions: 47/48
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 98.9810 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

Fresh comparison confirms no baseline instruction-exact function disappeared. All four string pools identical. GCWindow and SDMemory semantic non-text relocations identical; GCWindow and SDMemory data are 100%. Extab/extabindex, .bss and .sbss are absent except ChannelSelect .sbss, which reports 100%. Config/splits/symbols unchanged in the final diff. Final clean gate log: /tmp/data-d5-final-gate.log. Symbol/relocation evidence: /tmp/data-d5-symbol-relocation-evidence.txt; final semantic relocation comparison: /tmp/data-d5-final-relocs.txt.

# data-d5 round 2

Fresh branch HEAD/origin/main f6fd2780, after #736. GCWindow and SDMemory are no longer owned. No initial source differences from origin/main for the four new leaves. Fresh baseline report /tmp/data-d5-r2-start.json and instruction-exact snapshot /tmp/data-d5-r2-before.json.

| Unit | matched data | total data | instruction exact |
| --- | ---: | ---: | ---: |
| SDChannelSelect | 224 | 2960 | 117/129 |
| ChannelSelect | 192 | 2336 | 101/102 |
| wad | 64 | 528 | 35/40 |
| NHTTP_thread | 88 | 504 | 25/26 |

Pool-first audit: all four pools identical, 101/101, 98/98, 18/18 and 8/8 strings respectively. Fresh fetches confirm owned SDK/RevoEX sources have not changed on origin/main.

wad .data raw bytes and semantic relocations are identical after zero extension; target length 464 versus source 458, source alignment 8. Target includes six trailing linker alignment bytes. No missing static or pointer table is apparent.

NHTTP_thread .data raw bytes and semantic relocations are identical after zero extension; target 200 versus source 194. .rodata target 216 versus source 213. Target STR_POST_TYPE_BIN symbol is incorrectly at +0x27, which points at the alignment zero before the actual string at +0x28. STR_POST_TYPE_MULTIPART is incorrectly at +0xa6, which points at two alignment zeros before the actual string at +0xa8. Source strings and target bytes agree completely. Investigate instruction relocation addends before correcting these symbols; preserve section ownership and total bytes.

NHTTP_thread symbol correction: NHTTPi_SendProcPostDataBinary materializes STR_POST_DISPOS at 0x81618C70 via .text relocations +0xdf2/+0xdfa. Its original instructions at 0x81499674 and 0x814997E4 add 0xa8 and 0x28 to that relocated base before calling NHTTPi_SendData. These prove MULTIPART begins at 0x81618D18 and BIN at 0x81618C98, not the previous misaligned 0x81618D16/0x81618C97. Corrected only the two symbol addresses; their true character-array sizes remain 0x2d and 0x4c. DTK now recognizes both as strings. All source bytes, section sizes, splits and total data 504 stay unchanged. .rodata 99.5283 -> 100%, matched_data 88 -> 304/504; instruction-exact 25/26 unchanged and objdiff code 10528 unchanged. Quick gate PASS, DOL correct, regressions 0, forbidden/readability 0. No source changes or data-placement tricks.

Round 2 SDK padding audit: nm/objdump symbols and section relocations on both objects are saved in /tmp/data-d5-r2-nm-objdump.txt. wad and NHTTP_thread .data sections both have sh_addralign=8. Their last literal ends at 0x1ca and 0xc2 respectively; target sections end at 0x1d0 and 0xc8, exactly the next 8-byte boundary. These are six zero linker-alignment bytes, not weak objects, static tables, or missing strings. The current compiled sections stop at the literal terminator. No semantic data relocation differs and no symbol/reference names an object in these tails. Shrinking the unit, attributing the zeros to its neighbor, or adding an oversized array solely to reach the boundary would hide/fabricate the mismatch, so none is permitted. This is recorded as a separate linker-padding limitation, not the task's weak-data exception.

Round 2 SDChannelSelect: fresh pool and symbol/relocation audit confirms the previous round's exact state and the three logged typed-class experiments remain applicable. Target .data+0x960..0x980 has no symbol or incoming relocation anywhere in the target object. Source uses that range for its first live button-event vtable; all three real vtable pointer sequences match by class but their section positions differ by 32. Do not invent ownership for the target's anonymous zero range. The trailing weak GUI tables are also still deduplicated.

Round 2 ChannelSelect: fresh bytes and semantic relocation comparison reproduces the first round's exact evidence and three logged attempts. All live string/table/vtable bytes agree, including the fixed WSD_SELECT pool. Remaining source relocations land only in target's deduplicated weak-table zeros. No new actionable data mismatch.

NHTTPi_ThreadParseHeaderProc code cross-check, no data changes: baseline 98.58639%, 191/191 instructions, 20 differences involving pool/request registers and scheduling of the keep-alive false value around the comparison call. Attempt 1 used an initialized BOOL result, updated it on success and stored once after the comparison. 189/191 instructions, 97.565445%, no new exact function; reverted. Attempt 2 retained separate stores but named the false value before the call. Compiler folded it back to the baseline, 191/191 instructions, 98.58639%; reverted. Attempt 3 stored the comparison's boolean result directly. Measurements are saved in /tmp/data-d5-r2-nhttp-parse3.ctx and /tmp/data-d5-r2-nhttp-parse3.json; no exact gain, reverted. These are distinct readable forms, with no volatile or register coercion. All three kept the data report 304/504; none was committed.

WAD_815C1288 attempt 1: initialize transfer before bufferIndex, following target load order. objdiff 96.803276%, source/target 61/61 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-1.ctx. No accepted exact gain, restored.

WAD_815C1288 attempt 2: express the producer loop as while with explicit index advance. objdiff 96.803276%, source/target 61/61 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-2.ctx. No accepted exact gain, restored.

WAD_815C1288 attempt 3: calculate chunk size with a conditional expression. objdiff 96.31148%, source/target 61/61 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-3.ctx. No accepted exact gain, restored.

WADImportGetBlocks attempt 1: express content-count and file-count loops with explicit advances. objdiff 94.24161%, source/target 286/298 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-4.ctx. No accepted exact gain, restored.

WADImportGetBlocks attempt 2: bind each content descriptor only after selecting its index. objdiff 91.72819%, source/target 281/298 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-5.ctx. No accepted exact gain, restored.

WADImportGetBlocks attempt 3: cache the file-count value for allocation and iteration. objdiff 92.66443%, source/target 284/298 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-6.ctx. No accepted exact gain, restored.

WADImportEx attempt 1: separate cleanup-state declarations from initialization before unpackInfo clear. objdiff 99.01571%, source/target 1146/1146 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-7.ctx. No accepted exact gain, restored.

WADImportEx attempt 2: declare the two transfer buffers together, retaining their initialization order. objdiff 99.02269%, source/target 1146/1146 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-8.ctx. No accepted exact gain, restored.

WADImportEx attempt 3: group content-installation cache declarations before the result state. objdiff 98.81676%, source/target 1146/1146 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-9.ctx. No accepted exact gain, restored.

WADBackupEx attempt 1: initialize stream/file cleanup states at declaration. objdiff 97.085686%, source/target 1057/1062 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-10.ctx. No accepted exact gain, restored.

WADBackupEx attempt 2: reorder independent metadata/cache zero initializations before validation. objdiff 97.37571%, source/target 1057/1062 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-11.ctx. No accepted exact gain, restored.

WADBackupEx attempt 3: initialize the thread-created state with other cleanup flags. objdiff 97.370995%, source/target 1057/1062 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-12.ctx. No accepted exact gain, restored.

WADImportDVDExForBS attempt 1: initialize the read-buffer pointer after cleanup state declaration. objdiff 97.49049%, source/target 261/263 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-13.ctx. No accepted exact gain, restored.

WADImportDVDExForBS attempt 2: check buffer then path in the initial independent validation. objdiff 97.45247%, source/target 261/263 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-14.ctx. No accepted exact gain, restored.

WADImportDVDExForBS attempt 3: group content-buffer and remaining-size calculations with a typed section-end pointer. Compile failed; rejected and restored. Evidence /tmp/data-d5-r2-wad-trial-15.build.

WADImportDVDExForBS attempt 3: group content-buffer and remaining-size calculations with a typed section-end pointer. objdiff 97.49049%, source/target 261/263 instructions, baseline exact functions preserved 35/35, data 64/528, pool 0. Evidence /tmp/data-d5-r2-wad-trial-15.ctx. No accepted exact gain, restored.

src/scene/sdChannelSelect/iplSDChannelSelect::create attempt 1: express the thumbnail heap addition as separate arithmetic. objdiff 96.64384%, instructions 146/146, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-1.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::create attempt 2: declare elapsed tick storage beside the starting tick. objdiff 97.73972%, instructions 145/146, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-2.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::create attempt 3: test a single next-page index temporary. objdiff 96.5274%, instructions 144/146, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-3.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::handleSDTitleListResult attempt 1: initialize added-title state before iteration indices. objdiff 98.91813%, instructions 170/171, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-4.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::handleSDTitleListResult attempt 2: use an explicit increment statement for the stored channel index. objdiff 99.15205%, instructions 170/171, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-5.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::handleSDTitleListResult attempt 3: initialize title count and adjust the hazard case explicitly. objdiff 96.666664%, instructions 168/171, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-6.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByUsage attempt 1: reverse independent usage accumulator declarations. objdiff 97.72277%, instructions 101/101, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-7.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByUsage attempt 2: declare the channel index before its page output. objdiff 97.77228%, instructions 101/101, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-8.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByUsage attempt 3: return the final first-usage comparison directly. objdiff 94.53465%, instructions 100/101, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-9.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesFromNandUsage attempt 1: reverse independent usage accumulator declarations. objdiff 97.745094%, instructions 102/102, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-10.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesFromNandUsage attempt 2: declare the channel index before its page output. objdiff 97.79412%, instructions 102/102, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-11.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesFromNandUsage attempt 3: return the final first-usage comparison directly. objdiff 94.588234%, instructions 101/102, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-12.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByChannelOrder attempt 1: reverse independent usage accumulator declarations. objdiff 97.22222%, instructions 126/126, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-13.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByChannelOrder attempt 3: return the final first-usage comparison directly. objdiff 94.666664%, instructions 125/126, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-15.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesBySpecialChannels attempt 1: reverse independent usage accumulator declarations. objdiff 97.484764%, instructions 361/361, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-16.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesBySpecialChannels attempt 2: declare the channel index before its page output. objdiff 97.54017%, instructions 361/361, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-17.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesBySpecialChannels attempt 3: return the final first-usage comparison directly. objdiff 96.634346%, instructions 360/361, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-18.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::flushSaveDataAndMountSD attempt 1: bind the pointer animation before resetting it. objdiff 99.65714%, instructions 35/35, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-19.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::flushSaveDataAndMountSD attempt 2: bind the save manager for its two operations. objdiff 99.65714%, instructions 35/35, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-20.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::flushSaveDataAndMountSD attempt 3: hold the flush result before storing it. objdiff 99.65714%, instructions 35/35, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-21.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::calcCommon attempt 3: simplify the independent right-arrow predicate. objdiff 98.888885%, instructions 109/108, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-24.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::initializeNormalPage attempt 1: assign the left arrow flag before conditional animation. objdiff 89.62766%, instructions 93/94, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-25.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::initializeNormalPage attempt 2: simplify the right-arrow range comparison. objdiff 98.723404%, instructions 95/94, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-26.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::initializeNormalPage attempt 3: isolate the first animation pointer. Compile failed, reverted; /tmp/data-d5-r2-scene-trial-27.build.

src/scene/sdChannelSelect/iplSDChannelSelect::selectChannel attempt 1: materialize the channel translation as a named vector. objdiff 93.72881%, instructions 60/59, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-28.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::selectChannel attempt 2: place the selected channel index assignment next to its lookup. objdiff 80.932205%, instructions 60/59, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-29.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::selectChannel attempt 3: separate the button declaration from initialization. objdiff 98.305084%, instructions 60/59, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-30.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::setChannelScissor attempt 1: declare clipping coordinates before extents. objdiff 92.67811%, instructions 233/233, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-31.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::setChannelScissor attempt 2: reverse independent vertical projection divisions. objdiff 93.48498%, instructions 233/233, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-32.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::setChannelScissor attempt 3: expand extents before subtracting the border coordinates. objdiff 93.343346%, instructions 233/233, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-33.ctx. No accepted exact gain, reverted.

src/scene/channelSelect/iplChannelSelect::setChannelScissor attempt 1: declare clipping coordinates before extents. objdiff 92.69099%, instructions 233/233, exact baseline preserved 101/101, data 192/2336, pool 0; /tmp/data-d5-r2-scene-trial-34.ctx. No accepted exact gain, reverted.

src/scene/channelSelect/iplChannelSelect::setChannelScissor attempt 2: reverse independent vertical projection divisions. objdiff 93.4721%, instructions 233/233, exact baseline preserved 101/101, data 192/2336, pool 0; /tmp/data-d5-r2-scene-trial-35.ctx. No accepted exact gain, reverted.

src/scene/channelSelect/iplChannelSelect::setChannelScissor attempt 3: expand extents before subtracting the border coordinates. objdiff 93.356224%, instructions 233/233, exact baseline preserved 101/101, data 192/2336, pool 0; /tmp/data-d5-r2-scene-trial-36.ctx. No accepted exact gain, reverted.

Runner selection error: the first button-handler trial accidentally measured the already-exact SDChannelSelect member overload. That measurement was invalid, no candidate was accepted or committed, and the source was restored. Subsequent trials use the full anonymous handler namespace and report its actual 98.541664% score.

src/scene/sdChannelSelect/iplSDChannelSelect::collectTitlesByChannelOrder attempt 2: declare a cached selected channel index as const. objdiff 97.29365%, instructions 126/126, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-14.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::calcCommon attempt 1: set the left arrow visibility with one boolean expression. objdiff 88.14815%, instructions 104/108, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-22.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::calcCommon attempt 2: bind the SD button through a separate scene pointer. objdiff 99.07407%, instructions 109/108, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-23.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::initializeNormalPage attempt 3: isolate the first animation pointer. objdiff 98.93617%, instructions 95/94, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-27.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::onEventDerived attempt 1: switch directly on the scene state. objdiff 98.541664%, instructions 144/144, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-37.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::onEventDerived attempt 2: bind the pane before getting its name. objdiff 98.541664%, instructions 144/144, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-38.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::onEventDerived attempt 3: use a typed boolean for the controller trigger. objdiff 98.541664%, instructions 144/144, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-39.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::onEventDerived attempt 4: handle nonzero events with an early return before normal-state processing. objdiff 98.541664%, instructions 144/144, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-40.ctx. No accepted exact gain, reverted.

src/scene/sdChannelSelect/iplSDChannelSelect::onEventDerived attempt 5: dispatch the event with a switch and explicit default return. objdiff 99.30556%, instructions 145/144, exact baseline preserved 117/117, data 224/2960, pool 0; /tmp/data-d5-r2-scene-trial-41.ctx. No accepted exact gain, reverted.

Final pre-gate remote check: fetched origin/main a1d6b7d9; none of the four owned source files changed since starting main f6fd2780. No new upstream match duplicates this work.

Button-handler fifth attempt uses the real event switch and reaches 99.30556%, 145/144 instructions. The remaining extra instruction is `li r5,0` before SDButton::setEventHandler(NULL). The original relocates to the two-pointer setter but does not initialize its ignored second argument. The current honest declaration supplies default NULL, and the setter implementation ignores that argument. Removed no argument, introduced no alias/prototype cast or uninitialized value; reverted the fuzzy-only candidate. This explains the unresolved call ABI difference rather than claiming a register-only tie-break.

## Round 2 final full gate and remaining functions

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 27108/33828 data 224/2960 functions 117/129 fuzzy 99.5051 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 117/129
[src/scene/channelSelect/iplChannelSelect] objdiff: code 24736/25668 data 192/2336 functions 101/102 fuzzy 99.7634 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 101/102
[libs/RVL_SDK/src/wad/wad] objdiff: code 13180/24500 data 64/528 functions 35/40 fuzzy 98.9416 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 35/40
[libs/RevoEX/src/nhttp/NHTTP_thread] objdiff: code 10528/11292 data 304/504 functions 25/26 fuzzy 99.9044 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_thread] instruction-exact functions: 25/26
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

src/scene/sdChannelSelect/iplSDChannelSelect: data 224 -> 224/2960; code 27108 -> 27108/33828; instruction-exact 117 -> 117/129.

- create__Q33ipl5scene15SDChannelSelectFv: 97.73972%; instructions 145/146; allocation and elapsed-tick scheduling; one instruction missing; 3 distinct compiled source attempts, all rejected and restored.
- handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv: 99.15205%; instructions 170/171; title-loop/state scheduling; one instruction missing; 3 distinct compiled source attempts, all rejected and restored.
- collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.81188%; instructions 101/101; loop register assignment and scheduling; 3 distinct compiled source attempts, all rejected and restored.
- collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.833336%; instructions 102/102; loop register assignment and scheduling; 3 distinct compiled source attempts, all rejected and restored.
- collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.29365%; instructions 126/126; loop register assignment and scheduling; 3 distinct compiled source attempts, all rejected and restored.
- collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.55125%; instructions 361/361; loop register assignment and scheduling; 3 distinct compiled source attempts, all rejected and restored.
- flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 99.65714%; instructions 35/35; heap/save-manager load order reversed, two instruction differences; 3 distinct compiled source attempts, all rejected and restored.
- calcCommon__Q33ipl5scene15SDChannelSelectFv: 99.07407%; instructions 109/108; extra default second-argument initialization at SDButton setter call; 3 distinct compiled source attempts, all rejected and restored.
- initializeNormalPage__Q33ipl5scene15SDChannelSelectFv: 98.93617%; instructions 95/94; extra default second-argument initialization at SDButton setter call; 3 distinct compiled source attempts, all rejected and restored.
- selectChannel__Q33ipl5scene15SDChannelSelectFii: 98.305084%; instructions 60/59; extra default second-argument initialization at SDButton setter call; 3 distinct compiled source attempts, all rejected and restored.
- setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: 93.4721%; instructions 233/233; floating-point registers and arithmetic scheduling; 3 distinct compiled source attempts, all rejected and restored.
- onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface: 98.541664%; instructions 144/144; event dispatch form and ignored second setter argument; 5 distinct compiled source attempts, all rejected and restored.

src/scene/channelSelect/iplChannelSelect: data 192 -> 192/2336; code 24736 -> 24736/25668; instruction-exact 101 -> 101/102.

- setChannelScissor__Q33ipl5scene13ChannelSelectCFPCQ33ipl5scene10ChannelObj: 93.48498%; instructions 233/233; floating-point registers and arithmetic scheduling; 3 distinct compiled source attempts, all rejected and restored.

libs/RVL_SDK/src/wad/wad: data 64 -> 64/528; code 13180 -> 13180/24500; instruction-exact 35 -> 35/40.

- WADImportGetBlocks: 94.24161%; instructions 286/298; metadata/content loop and initialization code, twelve instructions missing; 3 distinct compiled source attempts, all rejected and restored.
- WADImportEx: 99.02269%; instructions 1146/1146; register allocation across transfer/cleanup state, equal instruction count; 3 distinct compiled source attempts, all rejected and restored.
- WAD_815C1288: 96.803276%; instructions 61/61; transfer/index register allocation, equal instruction count; 3 distinct compiled source attempts, all rejected and restored.
- WADBackupEx: 97.370995%; instructions 1057/1062; export loops and cleanup code, five instructions missing; 3 distinct compiled source attempts, all rejected and restored.
- WADImportDVDExForBS: 97.49049%; instructions 261/263; section calculations, two instructions missing; 3 distinct compiled source attempts, all rejected and restored.

libs/RevoEX/src/nhttp/NHTTP_thread: data 88 -> 304/504; code 10528 -> 10528/11292; instruction-exact 25 -> 25/26.

- NHTTPi_ThreadParseHeaderProc: 98.58639%; instructions 191/191; pool/request registers and keep-alive false-value scheduling; 3 distinct compiled source attempts, all rejected and restored.

All 19 remaining functions have at least three compiled, distinct source-level attempts recorded above. No exact function disappeared. Final pools all identical, zero-extended section bytes and semantic relocations independently rechecked after the clean gate. Only NHTTP .rodata reaches a new 100% section; remaining .data scores are SDChannelSelect 35.06984, ChannelSelect 95.60976, wad 99.34924, NHTTP_thread 98.47716. The anonymous SD gap ownership and SDK final linker padding remain unresolved; the ChannelSelect weak-data exception is documented. No code, shared header, split or array-size changes survive round 2.

## High round: symbol pairing and typed extents

Starting HEAD 0c94076d, fetched origin/main 08923eda. No owned source differs on the remote. All pools are identical; fresh before report saved as /tmp/data-d5-r3-before-report.json. Correct the previous interpretation: source-only weak data does not itself prevent exact data scoring. Coarse target aggregates and misleading names paired the wrong objects; physical linker padding stays present when real typed extents are corrected. The following changes use original relocations, constant address calculations from relocated bases, literal terminators and real vtable slot layouts. No original addresses, splits, section totals or source definitions change.

### High-round libs/RVL_SDK/src/wad/wad symbol/type proofs

- 816904B0 lbl_816904B0 -> __func__$1718, extent 88 -> 12: .text+0x98E relocates lbl_816904B0+0x0; 12-byte NUL-terminated char literal b'WADImportEx\x00'. Address and physical section length unchanged.
- 816904BC new symbol @4498, extent 37 inside formerly aggregated lbl_816904B0: WADImportEx .text+0x1a60 `addi r3, r3, 0xc` via relocation-derived base register r3; 37-byte NUL-terminated char literal b'%s:%d Cancel importing the content.\n\x00'. Address and physical section length unchanged.
- 816904E4 new symbol @4499, extent 35 inside formerly aggregated lbl_816904B0: WADImportEx .text+0x1a94 `addi r3, r3, 0x34` via relocation-derived base register r3; 35-byte NUL-terminated char literal b'%s:%d Cancel importing the title.\n\x00'. Address and physical section length unchanged.
- 81690508 lbl_81690508 -> @4643, extent 13 -> 13: .text+0x217E relocates lbl_81690508+0x0; 13-byte NUL-terminated char literal b'/title/%x/%x\x00'. Address and physical section length unchanged.
- 81690518 lbl_81690518 -> __func__$2446, extent 13 -> 13: .text+0x2F16 relocates lbl_81690518+0x0; 13-byte NUL-terminated char literal b'_WADMemAlloc\x00'. Address and physical section length unchanged.
- 81690528 lbl_81690528 -> @4680, extent 56 -> 56: .text+0x2F12 relocates lbl_81690528+0x0; 56-byte NUL-terminated char literal b'%s: Memory Allocator must return 64B aligned memBlocks\n\x00'. Address and physical section length unchanged.
- 81690560 lbl_81690560 -> @4976, extent 32 -> 32: .text+0x41D2 relocates lbl_81690560+0x0; 32-byte NUL-terminated char literal b'/shared2/succession/transfer.id\x00'. Address and physical section length unchanged.
- 81690580 lbl_81690580 -> @4988, extent 11 -> 11: .text+0x4292 relocates lbl_81690580+0x0; 11-byte NUL-terminated char literal b'notransfer\x00'. Address and physical section length unchanged.
- 8169058C lbl_8169058C -> @5034, extent 9 -> 9: .text+0x442A relocates lbl_8169058C+0x0; 9-byte NUL-terminated char literal b'%s/%s/%s\x00'. Address and physical section length unchanged.
- 81690598 lbl_81690598 -> @5036, extent 11 -> 11: .text+0x442E relocates lbl_81690598+0x0; 11-byte NUL-terminated char literal b'banner.bin\x00'. Address and physical section length unchanged.
- 816905A4 lbl_816905A4 -> @5310, extent 12 -> 12: .text+0x560E relocates lbl_816905A4+0x0; 12-byte NUL-terminated char literal b'zeldaTp.dat\x00'. Address and physical section length unchanged.
- 816905B0 lbl_816905B0 -> __func__$3419, extent 16 -> 16: .text+0x5826 relocates lbl_816905B0+0x0; 16-byte NUL-terminated char literal b'_WADCleanTmpDir\x00'. Address and physical section length unchanged.
- 816905C0 lbl_816905C0 -> @5329, extent 192 -> 17: .text+0x5822 relocates lbl_816905C0+0x0; 17-byte NUL-terminated char literal b'%s:%d remove %s\n\x00'. Address and physical section length unchanged.
- 816905D4 new symbol __func__$3450, extent 18 inside formerly aggregated lbl_816905C0: WADImportDVDForBS .text+0x59cc `addi r4, r31, 0x124` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'WADImportDVDForBS\x00'. Address and physical section length unchanged.
- 816905E8 new symbol @5365, extent 39 inside formerly aggregated lbl_816905C0: WADImportDVDForBS .text+0x59c8 `addi r3, r31, 0x138` via relocation-derived base register r31; 39-byte NUL-terminated char literal b'%s:%d Format should be iRD format: %s\n\x00'. Address and physical section length unchanged.
- 81690610 new symbol @5366, extent 28 inside formerly aggregated lbl_816905C0: WADImportDVDForBS .text+0x5b10 `addi r3, r31, 0x160` via relocation-derived base register r31; 28-byte NUL-terminated char literal b'%s: Import Boot Failed: %d\n\x00'. Address and physical section length unchanged.
- 8169062C new symbol @5367, extent 28 inside formerly aggregated lbl_816905C0: WADImportDVDForBS .text+0x5b24 `addi r3, r31, 0x17c` via relocation-derived base register r31; 28-byte NUL-terminated char literal b'%s: Import Boot Successful\n\x00'. Address and physical section length unchanged.
- 81690648 new symbol @5368, extent 50 inside formerly aggregated lbl_816905C0: WADImportDVDForBS .text+0x5b38 `addi r3, r31, 0x198` via relocation-derived base register r31; 50-byte NUL-terminated char literal b'%s:%d This function only works for boot2 import.\n\x00'. Address and physical section length unchanged.

wad quick gate PASS: data 64 -> 528/528, all non-text sections 100%, instruction-exact 35/40 unchanged, code 13180/24500 unchanged, regressions/forbidden/readability 0. Correct literal extents remove the earlier false padding limitation; physical section remains 464 bytes.

### High-round libs/RevoEX/src/nhttp/NHTTP_thread symbol/type proofs

- 8166D1A8 lbl_8166D1A8 -> @2079, extent 92 -> 9: .text+0x6D2 relocates lbl_8166D1A8+0x0; 9-byte NUL-terminated char literal b'CONNECT \x00'. Address and physical section length unchanged.
- 8166D1B4 new symbol @2081, extent 12 inside formerly aggregated lbl_8166D1A8: NHTTPi_SendProxyConnectMethod .text+0x798 `addi r4, r28, 0xc` via relocation-derived base register r28; 12-byte NUL-terminated char literal b' HTTP/1.1\r\n\x00'. Address and physical section length unchanged.
- 8166D1C0 new symbol @2084, extent 38 inside formerly aggregated lbl_8166D1A8: NHTTPi_SendProxyConnectMethod .text+0x848 `addi r4, r28, 0x18` via relocation-derived base register r28; 38-byte NUL-terminated char literal b'Content-Length: 0\r\nPragma: no-cache\r\n\x00'. Address and physical section length unchanged.
- 8166D1E8 new symbol @2085, extent 28 inside formerly aggregated lbl_8166D1A8: NHTTPi_SendProxyConnectMethod .text+0x888 `addi r4, r28, 0x40` via relocation-derived base register r28; 28-byte NUL-terminated char literal b'Proxy-Authorization: Basic \x00'. Address and physical section length unchanged.
- 8166D204 lbl_8166D204 -> @2147, extent 108 -> 17: .text+0xCFA relocates lbl_8166D204+0x0; 17-byte NUL-terminated char literal b'Content-Length: \x00'. Address and physical section length unchanged.
- 8166D218 new symbol @2423, extent 22 inside formerly aggregated lbl_8166D204: NHTTPi_ThreadSendProc .text+0x1d78 `addi r4, r30, 0x70` via relocation-derived base register r30; 22-byte NUL-terminated char literal b'Authorization: Basic \x00'. Address and physical section length unchanged.
- 8166D230 new symbol @2483, extent 15 inside formerly aggregated lbl_8166D204: NHTTPi_ThreadParseHeaderProc .text+0x223c `addi r4, r28, 0x88` via relocation-derived base register r28; 15-byte NUL-terminated char literal b'Content-Length\x00'. Address and physical section length unchanged.
- 8166D240 new symbol @2484, extent 11 inside formerly aggregated lbl_8166D204: NHTTPi_ThreadParseHeaderProc .text+0x2300 `addi r4, r28, 0x98` via relocation-derived base register r28; 11-byte NUL-terminated char literal b'Connection\x00'. Address and physical section length unchanged.
- 8166D24C new symbol @2485, extent 11 inside formerly aggregated lbl_8166D204: NHTTPi_ThreadParseHeaderProc .text+0x2350 `addi r6, r28, 0xa4` via relocation-derived base register r28; 11-byte NUL-terminated char literal b'Keep-Alive\x00'. Address and physical section length unchanged.
- 8166D258 new symbol @2486, extent 18 inside formerly aggregated lbl_8166D204: NHTTPi_ThreadParseHeaderProc .text+0x238c `addi r4, r28, 0xb0` via relocation-derived base register r28; 18-byte NUL-terminated char literal b'Transfer-Encoding\x00'. Address and physical section length unchanged.

NHTTP_thread quick gate PASS: data 304 -> 504/504, all non-text sections 100%, instruction-exact 25/26 unchanged, code 10528/11292 unchanged, regressions/forbidden/readability 0. Fetched origin before this unit; no remote source fix. The final Transfer-Encoding string is 18 bytes; remaining six alignment bytes stay physically present and need no fabricated array.

### High-round src/scene/channelSelect/iplChannelSelect symbol/type proofs

- 8164DD14 jumptable_8164DD14 -> @23426, extent 108 -> 108: .text+0x9A6 relocates jumptable_8164DD14+0x0; 108-byte typed pointer/jump table; +0x0->calcNormal__Q33ipl5scene13ChannelSelectFv+0xD4, +0x4->calcNormal__Q33ipl5scene13ChannelSelectFv+0x4C, +0x8->calcNormal__Q33ipl5scene13ChannelSelectFv+0xD4. Address and physical section length unchanged.
- 8164D978 lbl_8164D978 -> @17260, extent 9 -> 9: .text+0x586 relocates lbl_8164D978+0x0; 9-byte NUL-terminated char literal b'N_Ch_a04\x00'. Address and physical section length unchanged.
- 8164D981 lbl_8164D981 -> @17261, extent 9 -> 9: .data+0x198 relocates lbl_8164D981+0x0; 9-byte NUL-terminated char literal b'N_Ch_a08\x00'. Address and physical section length unchanged.
- 8164D98A lbl_8164D98A -> @17262, extent 9 -> 9: .data+0x1A8 relocates lbl_8164D98A+0x0; 9-byte NUL-terminated char literal b'N_Ch_a12\x00'. Address and physical section length unchanged.
- 8164D993 lbl_8164D993 -> @17263, extent 9 -> 9: .data+0x1AC relocates lbl_8164D993+0x0; 9-byte NUL-terminated char literal b'N_Ch_b01\x00'. Address and physical section length unchanged.
- 8164D99C lbl_8164D99C -> @17264, extent 9 -> 9: .data+0x1B0 relocates lbl_8164D99C+0x0; 9-byte NUL-terminated char literal b'N_Ch_b02\x00'. Address and physical section length unchanged.
- 8164D9A5 lbl_8164D9A5 -> @17265, extent 9 -> 9: .data+0x1B4 relocates lbl_8164D9A5+0x0; 9-byte NUL-terminated char literal b'N_Ch_b03\x00'. Address and physical section length unchanged.
- 8164D9AE lbl_8164D9AE -> @17266, extent 9 -> 9: .data+0x1B8 relocates lbl_8164D9AE+0x0; 9-byte NUL-terminated char literal b'N_Ch_b04\x00'. Address and physical section length unchanged.
- 8164D9B7 lbl_8164D9B7 -> @17267, extent 9 -> 9: .data+0x1BC relocates lbl_8164D9B7+0x0; 9-byte NUL-terminated char literal b'N_Ch_b05\x00'. Address and physical section length unchanged.
- 8164D9C0 lbl_8164D9C0 -> @17268, extent 9 -> 9: .data+0x1C0 relocates lbl_8164D9C0+0x0; 9-byte NUL-terminated char literal b'N_Ch_b06\x00'. Address and physical section length unchanged.
- 8164D9C9 lbl_8164D9C9 -> @17269, extent 9 -> 9: .data+0x1C4 relocates lbl_8164D9C9+0x0; 9-byte NUL-terminated char literal b'N_Ch_b07\x00'. Address and physical section length unchanged.
- 8164D9D2 lbl_8164D9D2 -> @17270, extent 9 -> 9: .data+0x1C8 relocates lbl_8164D9D2+0x0; 9-byte NUL-terminated char literal b'N_Ch_b08\x00'. Address and physical section length unchanged.
- 8164D9DB lbl_8164D9DB -> @17271, extent 9 -> 9: .data+0x1CC relocates lbl_8164D9DB+0x0; 9-byte NUL-terminated char literal b'N_Ch_b09\x00'. Address and physical section length unchanged.
- 8164D9E4 lbl_8164D9E4 -> @17272, extent 9 -> 9: .data+0x1D0 relocates lbl_8164D9E4+0x0; 9-byte NUL-terminated char literal b'N_Ch_b10\x00'. Address and physical section length unchanged.
- 8164D9ED lbl_8164D9ED -> @17273, extent 9 -> 9: .data+0x1D4 relocates lbl_8164D9ED+0x0; 9-byte NUL-terminated char literal b'N_Ch_b11\x00'. Address and physical section length unchanged.
- 8164D9F6 lbl_8164D9F6 -> @17274, extent 9 -> 9: .data+0x1D8 relocates lbl_8164D9F6+0x0; 9-byte NUL-terminated char literal b'N_Ch_b12\x00'. Address and physical section length unchanged.
- 8164D9FF lbl_8164D9FF -> @17275, extent 9 -> 9: .data+0x1DC relocates lbl_8164D9FF+0x0; 9-byte NUL-terminated char literal b'N_Ch_c01\x00'. Address and physical section length unchanged.
- 8164DA08 lbl_8164DA08 -> @17276, extent 9 -> 9: .data+0x1E0 relocates lbl_8164DA08+0x0; 9-byte NUL-terminated char literal b'N_Ch_c02\x00'. Address and physical section length unchanged.
- 8164DA11 lbl_8164DA11 -> @17277, extent 9 -> 9: .data+0x1E4 relocates lbl_8164DA11+0x0; 9-byte NUL-terminated char literal b'N_Ch_c03\x00'. Address and physical section length unchanged.
- 8164DA1A lbl_8164DA1A -> @17278, extent 9 -> 9: .data+0x1E8 relocates lbl_8164DA1A+0x0; 9-byte NUL-terminated char literal b'N_Ch_c04\x00'. Address and physical section length unchanged.
- 8164DA23 lbl_8164DA23 -> @17279, extent 9 -> 9: .data+0x1EC relocates lbl_8164DA23+0x0; 9-byte NUL-terminated char literal b'N_Ch_c05\x00'. Address and physical section length unchanged.
- 8164DA2C lbl_8164DA2C -> @17280, extent 9 -> 9: .data+0x1F0 relocates lbl_8164DA2C+0x0; 9-byte NUL-terminated char literal b'N_Ch_c06\x00'. Address and physical section length unchanged.
- 8164DA35 lbl_8164DA35 -> @17281, extent 9 -> 9: .data+0x1F4 relocates lbl_8164DA35+0x0; 9-byte NUL-terminated char literal b'N_Ch_c07\x00'. Address and physical section length unchanged.
- 8164DA3E lbl_8164DA3E -> @17282, extent 9 -> 9: .data+0x1F8 relocates lbl_8164DA3E+0x0; 9-byte NUL-terminated char literal b'N_Ch_c08\x00'. Address and physical section length unchanged.
- 8164DA47 lbl_8164DA47 -> @17283, extent 9 -> 9: .data+0x1FC relocates lbl_8164DA47+0x0; 9-byte NUL-terminated char literal b'N_Ch_c09\x00'. Address and physical section length unchanged.
- 8164DA50 lbl_8164DA50 -> @17284, extent 9 -> 9: .data+0x200 relocates lbl_8164DA50+0x0; 9-byte NUL-terminated char literal b'N_Ch_c10\x00'. Address and physical section length unchanged.
- 8164DA59 lbl_8164DA59 -> @17285, extent 9 -> 9: .data+0x204 relocates lbl_8164DA59+0x0; 9-byte NUL-terminated char literal b'N_Ch_c11\x00'. Address and physical section length unchanged.
- 8164DA62 lbl_8164DA62 -> @17286, extent 9 -> 9: .data+0x208 relocates lbl_8164DA62+0x0; 9-byte NUL-terminated char literal b'N_Ch_c12\x00'. Address and physical section length unchanged.
- 8164DA6B lbl_8164DA6B -> @17287, extent 9 -> 9: .data+0x20C relocates lbl_8164DA6B+0x0; 9-byte NUL-terminated char literal b'N_Ch_d01\x00'. Address and physical section length unchanged.
- 8164DA74 lbl_8164DA74 -> @17288, extent 9 -> 9: .data+0x210 relocates lbl_8164DA74+0x0; 9-byte NUL-terminated char literal b'N_Ch_d02\x00'. Address and physical section length unchanged.
- 8164DA7D lbl_8164DA7D -> @17289, extent 9 -> 9: .data+0x214 relocates lbl_8164DA7D+0x0; 9-byte NUL-terminated char literal b'N_Ch_d03\x00'. Address and physical section length unchanged.
- 8164DA86 lbl_8164DA86 -> @17290, extent 9 -> 9: .data+0x218 relocates lbl_8164DA86+0x0; 9-byte NUL-terminated char literal b'N_Ch_d04\x00'. Address and physical section length unchanged.
- 8164DA8F lbl_8164DA8F -> @17291, extent 9 -> 9: .data+0x21C relocates lbl_8164DA8F+0x0; 9-byte NUL-terminated char literal b'N_Ch_d05\x00'. Address and physical section length unchanged.
- 8164DA98 lbl_8164DA98 -> @17292, extent 9 -> 9: .data+0x220 relocates lbl_8164DA98+0x0; 9-byte NUL-terminated char literal b'N_Ch_d06\x00'. Address and physical section length unchanged.
- 8164DAA1 lbl_8164DAA1 -> @17293, extent 9 -> 9: .data+0x224 relocates lbl_8164DAA1+0x0; 9-byte NUL-terminated char literal b'N_Ch_d07\x00'. Address and physical section length unchanged.
- 8164DAAA lbl_8164DAAA -> @17294, extent 9 -> 9: .data+0x228 relocates lbl_8164DAAA+0x0; 9-byte NUL-terminated char literal b'N_Ch_d08\x00'. Address and physical section length unchanged.
- 8164DAB3 lbl_8164DAB3 -> @17295, extent 9 -> 9: .data+0x22C relocates lbl_8164DAB3+0x0; 9-byte NUL-terminated char literal b'N_Ch_d09\x00'. Address and physical section length unchanged.
- 8164DABC lbl_8164DABC -> @17296, extent 9 -> 9: .data+0x230 relocates lbl_8164DABC+0x0; 9-byte NUL-terminated char literal b'N_Ch_d10\x00'. Address and physical section length unchanged.
- 8164DAC5 lbl_8164DAC5 -> @17297, extent 9 -> 9: .data+0x234 relocates lbl_8164DAC5+0x0; 9-byte NUL-terminated char literal b'N_Ch_d11\x00'. Address and physical section length unchanged.
- 8164DACE lbl_8164DACE -> @17298, extent 9 -> 9: .data+0x238 relocates lbl_8164DACE+0x0; 9-byte NUL-terminated char literal b'N_Ch_d12\x00'. Address and physical section length unchanged.
- 8164DAD7 lbl_8164DAD7 -> @17299, extent 9 -> 9: .data+0x23C relocates lbl_8164DAD7+0x0; 9-byte NUL-terminated char literal b'N_Ch_e01\x00'. Address and physical section length unchanged.
- 8164DAE0 lbl_8164DAE0 -> @17300, extent 9 -> 9: .data+0x24C relocates lbl_8164DAE0+0x0; 9-byte NUL-terminated char literal b'N_Ch_e05\x00'. Address and physical section length unchanged.
- 8164DAE9 lbl_8164DAE9 -> @17301, extent 9 -> 9: .data+0x25C relocates lbl_8164DAE9+0x0; 9-byte NUL-terminated char literal b'N_Ch_e09\x00'. Address and physical section length unchanged.
- 8164DBE4 lbl_8164DBE4 -> @17302, extent 10 -> 10: .data+0x2A0 relocates lbl_8164DBE4+0x0; 10-byte NUL-terminated char literal b'BaseMask0\x00'. Address and physical section length unchanged.
- 8164DBEE lbl_8164DBEE -> @17303, extent 10 -> 10: .data+0x2A4 relocates lbl_8164DBEE+0x0; 10-byte NUL-terminated char literal b'BaseMask1\x00'. Address and physical section length unchanged.
- 8164DBF8 lbl_8164DBF8 -> @17304, extent 10 -> 10: .data+0x2A8 relocates lbl_8164DBF8+0x0; 10-byte NUL-terminated char literal b'BaseMask2\x00'. Address and physical section length unchanged.
- 8164DC02 lbl_8164DC02 -> @17305, extent 10 -> 10: .data+0x2AC relocates lbl_8164DC02+0x0; 10-byte NUL-terminated char literal b'BaseMask3\x00'. Address and physical section length unchanged.
- 8164DC0C lbl_8164DC0C -> @17306, extent 10 -> 10: .data+0x2B0 relocates lbl_8164DC0C+0x0; 10-byte NUL-terminated char literal b'BaseMask4\x00'. Address and physical section length unchanged.
- 8164DC2C lbl_8164DC2C -> @17307, extent 11 -> 11: .data+0x2EC relocates lbl_8164DC2C+0x0; 11-byte NUL-terminated char literal b'Picture_00\x00'. Address and physical section length unchanged.
- 8164DC37 lbl_8164DC37 -> @17308, extent 11 -> 11: .data+0x2F0 relocates lbl_8164DC37+0x0; 11-byte NUL-terminated char literal b'Picture_01\x00'. Address and physical section length unchanged.
- 8164DC42 lbl_8164DC42 -> @17309, extent 11 -> 11: .data+0x2F4 relocates lbl_8164DC42+0x0; 11-byte NUL-terminated char literal b'Picture_02\x00'. Address and physical section length unchanged.
- 8164DC4D lbl_8164DC4D -> @17310, extent 11 -> 11: .data+0x2F8 relocates lbl_8164DC4D+0x0; 11-byte NUL-terminated char literal b'Picture_03\x00'. Address and physical section length unchanged.
- 8164DC58 lbl_8164DC58 -> @17311, extent 32 -> 11: .data+0x2FC relocates lbl_8164DC58+0x0; 11-byte NUL-terminated char literal b'Picture_04\x00'. Address and physical section length unchanged.
- 8164DC64 new symbol mscUnk0PaneNames__Q33ipl5scene13ChannelSelect, extent 20 inside formerly aggregated lbl_8164DC58: createBaseLayout__Q33ipl5scene13ChannelSelectFv .text+0x12c8 `addi r28, r27, 0x2ec` via relocation-derived base register r27; 20-byte typed pointer/jump table; +0x0->lbl_8164DC2C+0x0, +0x4->lbl_8164DC37+0x0, +0x8->lbl_8164DC42+0x0. Address and physical section length unchanged.
- 8164DC78 lbl_8164DC78 -> mscUnk1PaneNames__Q33ipl5scene13ChannelSelect, extent 20 -> 20: .text+0x2F1E relocates lbl_8164DC78+0x0; 20-byte typed pointer/jump table; +0x0->lbl_816968B1+0x0, +0x4->lbl_816968B7+0x0, +0x8->lbl_816968BD+0x0. Address and physical section length unchanged.
- 8164DC8C lbl_8164DC8C -> @17317, extent 9 -> 9: .data+0x330 relocates lbl_8164DC8C+0x0; 9-byte NUL-terminated char literal b'N_Clock0\x00'. Address and physical section length unchanged.
- 8164DC95 lbl_8164DC95 -> @17318, extent 9 -> 9: .data+0x334 relocates lbl_8164DC95+0x0; 9-byte NUL-terminated char literal b'N_Clock1\x00'. Address and physical section length unchanged.
- 8164DC9E lbl_8164DC9E -> @17319, extent 9 -> 9: .data+0x338 relocates lbl_8164DC9E+0x0; 9-byte NUL-terminated char literal b'N_Clock2\x00'. Address and physical section length unchanged.
- 8164DCA8 lbl_8164DCA8 -> mscClockPaneNames__Q33ipl5scene13ChannelSelect, extent 12 -> 12: .text+0xD72 relocates lbl_8164DCA8+0x0; 12-byte typed pointer/jump table; +0x0->lbl_8164DC8C+0x0, +0x4->lbl_8164DC95+0x0, +0x8->lbl_8164DC9E+0x0. Address and physical section length unchanged.
- 8164DCB4 lbl_8164DCB4 -> @23246, extent 12 -> 12: .text+0x362 relocates lbl_8164DCB4+0x0; 12-byte NUL-terminated char literal b'chanSel.ash\x00'. Address and physical section length unchanged.
- 8164DCC0 lbl_8164DCC0 -> @23247, extent 31 -> 13: .text+0x396 relocates lbl_8164DCC0+0x0; 13-byte NUL-terminated char literal b'diskThum.ash\x00'. Address and physical section length unchanged.
- 8164DCCD new symbol @23374, extent 18 inside formerly aggregated lbl_8164DCC0: calcCommon__Q33ipl5scene13ChannelSelectFv .text+0x684 `addi r4, r31, 0x355` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'WIPL_SE_WII_START\x00'. Address and physical section length unchanged.
- 8164DCDF lbl_8164DCDF -> @23375, extent 53 -> 14: .text+0x2416 relocates lbl_8164DCDF+0x0; 14-byte NUL-terminated char literal b'WIPL_BGM_MENU\x00'. Address and physical section length unchanged.
- 8164DCED new symbol @23376, extent 18 inside formerly aggregated lbl_8164DCDF: calcCommon__Q33ipl5scene13ChannelSelectFv .text+0x8e4 `addi r4, r31, 0x375` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'WIPL_SE_SDCARD_IN\x00'. Address and physical section length unchanged.
- 8164DCFF new symbol @23377, extent 19 inside formerly aggregated lbl_8164DCDF: calcCommon__Q33ipl5scene13ChannelSelectFv .text+0x918 `addi r4, r31, 0x387` via relocation-derived base register r31; 19-byte NUL-terminated char literal b'WIPL_SE_SDCARD_OUT\x00'. Address and physical section length unchanged.
- 8164DD80 lbl_8164DD80 -> @23551, extent 55 -> 23: .text+0x10A6 relocates lbl_8164DD80+0x0; 23-byte NUL-terminated char literal b'/title/%08x/%08x/data/\x00'. Address and physical section length unchanged.
- 8164DD97 new symbol @23653, extent 18 inside formerly aggregated lbl_8164DD80: createBaseLayout__Q33ipl5scene13ChannelSelectFv .text+0x122c `addi r7, r27, 0x41f` via relocation-derived base register r27; 18-byte NUL-terminated char literal b'my_IplTop_a.brlyt\x00'. Address and physical section length unchanged.
- 8164DDA9 new symbol @23654, extent 14 inside formerly aggregated lbl_8164DD80: createBaseLayout__Q33ipl5scene13ChannelSelectFv .text+0x1254 `addi r4, r27, 0x431` via relocation-derived base register r27; 14-byte NUL-terminated char literal b'ChangeTex16x9\x00'. Address and physical section length unchanged.
- 8164DDB7 lbl_8164DDB7 -> @23655, extent 173 -> 11: .text+0x3A16 relocates lbl_8164DDB7+0x0; 11-byte NUL-terminated char literal b'Picture_16\x00'. Address and physical section length unchanged.
- 8164DDC2 new symbol @23656, extent 18 inside formerly aggregated lbl_8164DDB7: createBaseLayout__Q33ipl5scene13ChannelSelectFv .text+0x1364 `addi r4, r27, 0x44a` via relocation-derived base register r27; 18-byte NUL-terminated char literal b'my_IplTop_a.brlan\x00'. Address and physical section length unchanged.
- 8164DDD4 new symbol @23731, extent 18 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x15c8 `addi r7, r31, 0x45c` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'my_DiskCh_b.brlyt\x00'. Address and physical section length unchanged.
- 8164DDE6 new symbol @23732, extent 18 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x15dc `addi r4, r31, 0x46e` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'my_DiskCh_b.brlan\x00'. Address and physical section length unchanged.
- 8164DDF8 new symbol @23734, extent 18 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x16bc `addi r7, r31, 0x480` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'my_GCIcon_a.brlyt\x00'. Address and physical section length unchanged.
- 8164DE0A new symbol @23735, extent 18 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x16d0 `addi r4, r31, 0x492` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'my_GCIcon_a.brlan\x00'. Address and physical section length unchanged.
- 8164DE1C new symbol @23736, extent 19 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x170c `addi r7, r31, 0x4a4` via relocation-derived base register r31; 19-byte NUL-terminated char literal b'my_DiskCh_In.brlyt\x00'. Address and physical section length unchanged.
- 8164DE2F new symbol @23739, extent 26 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x17ac `addi r4, r31, 0x4b7` via relocation-derived base register r31; 26-byte NUL-terminated char literal b'my_DiskCh_In_DiskIn.brlan\x00'. Address and physical section length unchanged.
- 8164DE49 new symbol @23740, extent 27 inside formerly aggregated lbl_8164DDB7: createDiskLayout__Q33ipl5scene13ChannelSelectFv .text+0x17c4 `addi r4, r31, 0x4d1` via relocation-derived base register r31; 27-byte NUL-terminated char literal b'my_DiskCh_In_DiskOut.brlan\x00'. Address and physical section length unchanged.
- 8164DEA7 lbl_8164DEA7 -> @24254, extent 16 -> 16: .text+0x369A relocates lbl_8164DEA7+0x0; 16-byte NUL-terminated char literal b'WIPL_SE_BT_PUSH\x00'. Address and physical section length unchanged.
- 8164DEB7 lbl_8164DEB7 -> @24282, extent 276 -> 18: .text+0x3792 relocates lbl_8164DEB7+0x0; 18-byte NUL-terminated char literal b'WIPL_SE_CH_SELECT\x00'. Address and physical section length unchanged.
- 8164DEC9 new symbol @24521, extent 18 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4690 `addi r7, r30, 0x551` via relocation-derived base register r30; 18-byte NUL-terminated char literal b'my_IplTop_b.brlyt\x00'. Address and physical section length unchanged.
- 8164DEDB new symbol @24522, extent 18 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x46a4 `addi r4, r30, 0x563` via relocation-derived base register r30; 18-byte NUL-terminated char literal b'my_IplTop_b.brlan\x00'. Address and physical section length unchanged.
- 8164DEED new symbol @24523, extent 18 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4724 `addi r7, r30, 0x575` via relocation-derived base register r30; 18-byte NUL-terminated char literal b'my_TVMask_a.brlyt\x00'. Address and physical section length unchanged.
- 8164DEFF new symbol @24524, extent 24 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4738 `addi r4, r30, 0x587` via relocation-derived base register r30; 24-byte NUL-terminated char literal b'my_TVMask_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 8164DF17 new symbol @24525, extent 11 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x473c `addi r5, r30, 0x59f` via relocation-derived base register r30; 11-byte NUL-terminated char literal b'Picture_00\x00'. Address and physical section length unchanged.
- 8164DF22 new symbol @24526, extent 23 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4750 `addi r4, r30, 0x5aa` via relocation-derived base register r30; 23-byte NUL-terminated char literal b'my_TVMask_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 8164DF39 new symbol @24527, extent 19 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4794 `addi r7, r30, 0x5c1` via relocation-derived base register r30; 19-byte NUL-terminated char literal b'my_TVShade_a.brlyt\x00'. Address and physical section length unchanged.
- 8164DF4C new symbol @24528, extent 25 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x47a8 `addi r4, r30, 0x5d4` via relocation-derived base register r30; 25-byte NUL-terminated char literal b'my_TVShade_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 8164DF65 new symbol @24530, extent 24 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x47c0 `addi r4, r30, 0x5ed` via relocation-derived base register r30; 24-byte NUL-terminated char literal b'my_TVShade_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 8164DF7D new symbol @24531, extent 10 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x4868 `addi r4, r30, 0x605` via relocation-derived base register r30; 10-byte NUL-terminated char literal b'4x3_dummy\x00'. Address and physical section length unchanged.
- 8164DF87 new symbol @24532, extent 19 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x48c8 `addi r7, r30, 0x60f` via relocation-derived base register r30; 19-byte NUL-terminated char literal b'my_TVApear_a.brlyt\x00'. Address and physical section length unchanged.
- 8164DF9A new symbol @24533, extent 25 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x48dc `addi r4, r30, 0x622` via relocation-derived base register r30; 25-byte NUL-terminated char literal b'my_TVApear_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 8164DFB3 new symbol @24534, extent 24 inside formerly aggregated lbl_8164DEB7: createChanMoveLayout__Q33ipl5scene13ChannelSelectFv .text+0x48f4 `addi r4, r30, 0x63b` via relocation-derived base register r30; 24-byte NUL-terminated char literal b'my_TVApear_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 8164E014 lbl_8164E014 -> @24865, extent 16 -> 16: .text+0x5CAE relocates lbl_8164E014+0x0; 16-byte NUL-terminated char literal b'WIPL_SE_CH_DRAG\x00'. Address and physical section length unchanged.
- 8164E048 __vt__Q33ipl4math29HermiteIntp<Q33ipl4math4VEC3> -> __vt__Q33ipl4math29HermiteIntp<Q33ipl4math4VEC3>, extent 32 -> 16: .text+0x1506 relocates __vt__Q33ipl4math29HermiteIntp<Q33ipl4math4VEC3>+0x0; 16-byte vtable (two header words and 2 virtual slots); +0x8->__dt__Q33ipl4math29HermiteIntp<Q33ipl4math4VEC3>Fv+0x0, +0xC->calc__Q33ipl7utility15FrameControllerFv+0x0. Address and physical section length unchanged.

ChannelSelect quick gate PASS: data 192 -> 2336/2336, every non-text section 100%, instruction-exact 101/102 unchanged, code 24736/25668 unchanged, regressions/forbidden/readability 0. Fetched origin before starting; no remote source changes. Hermite vtable has 16 real bytes, not the 32-byte aggregate with a deduplicated neighbor. Only symbol metadata changed.

### High-round src/scene/sdChannelSelect/iplSDChannelSelect symbol/type proofs

- 81654088 @16632 -> @16723, extent 9 -> 9: .text+0x384E relocates @16632+0x0; 9-byte NUL-terminated char literal b'N_Ch_a04\x00'. Address and physical section length unchanged.
- 81654091 @16633 -> @16724, extent 9 -> 9: .data+0x198 relocates @16633+0x0; 9-byte NUL-terminated char literal b'N_Ch_a08\x00'. Address and physical section length unchanged.
- 8165409A @16634 -> @16725, extent 9 -> 9: .data+0x1A8 relocates @16634+0x0; 9-byte NUL-terminated char literal b'N_Ch_a12\x00'. Address and physical section length unchanged.
- 816540A3 @16635 -> @16726, extent 9 -> 9: .data+0x1AC relocates @16635+0x0; 9-byte NUL-terminated char literal b'N_Ch_b01\x00'. Address and physical section length unchanged.
- 816540AC @16636 -> @16727, extent 9 -> 9: .data+0x1B0 relocates @16636+0x0; 9-byte NUL-terminated char literal b'N_Ch_b02\x00'. Address and physical section length unchanged.
- 816540B5 @16637 -> @16728, extent 9 -> 9: .data+0x1B4 relocates @16637+0x0; 9-byte NUL-terminated char literal b'N_Ch_b03\x00'. Address and physical section length unchanged.
- 816540BE @16638 -> @16729, extent 9 -> 9: .data+0x1B8 relocates @16638+0x0; 9-byte NUL-terminated char literal b'N_Ch_b04\x00'. Address and physical section length unchanged.
- 816540C7 @16639 -> @16730, extent 9 -> 9: .data+0x1BC relocates @16639+0x0; 9-byte NUL-terminated char literal b'N_Ch_b05\x00'. Address and physical section length unchanged.
- 816540D0 @16640 -> @16731, extent 9 -> 9: .data+0x1C0 relocates @16640+0x0; 9-byte NUL-terminated char literal b'N_Ch_b06\x00'. Address and physical section length unchanged.
- 816540D9 @16641 -> @16732, extent 9 -> 9: .data+0x1C4 relocates @16641+0x0; 9-byte NUL-terminated char literal b'N_Ch_b07\x00'. Address and physical section length unchanged.
- 816540E2 @16642 -> @16733, extent 9 -> 9: .data+0x1C8 relocates @16642+0x0; 9-byte NUL-terminated char literal b'N_Ch_b08\x00'. Address and physical section length unchanged.
- 816540EB @16643 -> @16734, extent 9 -> 9: .data+0x1CC relocates @16643+0x0; 9-byte NUL-terminated char literal b'N_Ch_b09\x00'. Address and physical section length unchanged.
- 816540F4 @16644 -> @16735, extent 9 -> 9: .data+0x1D0 relocates @16644+0x0; 9-byte NUL-terminated char literal b'N_Ch_b10\x00'. Address and physical section length unchanged.
- 816540FD @16645 -> @16736, extent 9 -> 9: .data+0x1D4 relocates @16645+0x0; 9-byte NUL-terminated char literal b'N_Ch_b11\x00'. Address and physical section length unchanged.
- 81654106 @16646 -> @16737, extent 9 -> 9: .data+0x1D8 relocates @16646+0x0; 9-byte NUL-terminated char literal b'N_Ch_b12\x00'. Address and physical section length unchanged.
- 8165410F @16647 -> @16738, extent 9 -> 9: .data+0x1DC relocates @16647+0x0; 9-byte NUL-terminated char literal b'N_Ch_c01\x00'. Address and physical section length unchanged.
- 81654118 @16648 -> @16739, extent 9 -> 9: .data+0x1E0 relocates @16648+0x0; 9-byte NUL-terminated char literal b'N_Ch_c02\x00'. Address and physical section length unchanged.
- 81654121 @16649 -> @16740, extent 9 -> 9: .data+0x1E4 relocates @16649+0x0; 9-byte NUL-terminated char literal b'N_Ch_c03\x00'. Address and physical section length unchanged.
- 8165412A @16650 -> @16741, extent 9 -> 9: .data+0x1E8 relocates @16650+0x0; 9-byte NUL-terminated char literal b'N_Ch_c04\x00'. Address and physical section length unchanged.
- 81654133 @16651 -> @16742, extent 9 -> 9: .data+0x1EC relocates @16651+0x0; 9-byte NUL-terminated char literal b'N_Ch_c05\x00'. Address and physical section length unchanged.
- 8165413C @16652 -> @16743, extent 9 -> 9: .data+0x1F0 relocates @16652+0x0; 9-byte NUL-terminated char literal b'N_Ch_c06\x00'. Address and physical section length unchanged.
- 81654145 @16653 -> @16744, extent 9 -> 9: .data+0x1F4 relocates @16653+0x0; 9-byte NUL-terminated char literal b'N_Ch_c07\x00'. Address and physical section length unchanged.
- 8165414E @16654 -> @16745, extent 9 -> 9: .data+0x1F8 relocates @16654+0x0; 9-byte NUL-terminated char literal b'N_Ch_c08\x00'. Address and physical section length unchanged.
- 81654157 @16655 -> @16746, extent 9 -> 9: .data+0x1FC relocates @16655+0x0; 9-byte NUL-terminated char literal b'N_Ch_c09\x00'. Address and physical section length unchanged.
- 81654160 @16656 -> @16747, extent 9 -> 9: .data+0x200 relocates @16656+0x0; 9-byte NUL-terminated char literal b'N_Ch_c10\x00'. Address and physical section length unchanged.
- 81654169 @16657 -> @16748, extent 9 -> 9: .data+0x204 relocates @16657+0x0; 9-byte NUL-terminated char literal b'N_Ch_c11\x00'. Address and physical section length unchanged.
- 81654172 @16658 -> @16749, extent 9 -> 9: .data+0x208 relocates @16658+0x0; 9-byte NUL-terminated char literal b'N_Ch_c12\x00'. Address and physical section length unchanged.
- 8165417B @16659 -> @16750, extent 9 -> 9: .data+0x20C relocates @16659+0x0; 9-byte NUL-terminated char literal b'N_Ch_d01\x00'. Address and physical section length unchanged.
- 81654184 @16660 -> @16751, extent 9 -> 9: .data+0x210 relocates @16660+0x0; 9-byte NUL-terminated char literal b'N_Ch_d02\x00'. Address and physical section length unchanged.
- 8165418D @16661 -> @16752, extent 9 -> 9: .data+0x214 relocates @16661+0x0; 9-byte NUL-terminated char literal b'N_Ch_d03\x00'. Address and physical section length unchanged.
- 81654196 @16662 -> @16753, extent 9 -> 9: .data+0x218 relocates @16662+0x0; 9-byte NUL-terminated char literal b'N_Ch_d04\x00'. Address and physical section length unchanged.
- 8165419F @16663 -> @16754, extent 9 -> 9: .data+0x21C relocates @16663+0x0; 9-byte NUL-terminated char literal b'N_Ch_d05\x00'. Address and physical section length unchanged.
- 816541A8 @16664 -> @16755, extent 9 -> 9: .data+0x220 relocates @16664+0x0; 9-byte NUL-terminated char literal b'N_Ch_d06\x00'. Address and physical section length unchanged.
- 816541B1 @16665 -> @16756, extent 9 -> 9: .data+0x224 relocates @16665+0x0; 9-byte NUL-terminated char literal b'N_Ch_d07\x00'. Address and physical section length unchanged.
- 816541BA @16666 -> @16757, extent 9 -> 9: .data+0x228 relocates @16666+0x0; 9-byte NUL-terminated char literal b'N_Ch_d08\x00'. Address and physical section length unchanged.
- 816541C3 @16667 -> @16758, extent 9 -> 9: .data+0x22C relocates @16667+0x0; 9-byte NUL-terminated char literal b'N_Ch_d09\x00'. Address and physical section length unchanged.
- 816541CC @16668 -> @16759, extent 9 -> 9: .data+0x230 relocates @16668+0x0; 9-byte NUL-terminated char literal b'N_Ch_d10\x00'. Address and physical section length unchanged.
- 816541D5 @16669 -> @16760, extent 9 -> 9: .data+0x234 relocates @16669+0x0; 9-byte NUL-terminated char literal b'N_Ch_d11\x00'. Address and physical section length unchanged.
- 816541DE @16670 -> @16761, extent 9 -> 9: .data+0x238 relocates @16670+0x0; 9-byte NUL-terminated char literal b'N_Ch_d12\x00'. Address and physical section length unchanged.
- 816541E7 @16671 -> @16762, extent 9 -> 9: .data+0x23C relocates @16671+0x0; 9-byte NUL-terminated char literal b'N_Ch_e01\x00'. Address and physical section length unchanged.
- 816541F0 @16672 -> @16763, extent 9 -> 9: .data+0x24C relocates @16672+0x0; 9-byte NUL-terminated char literal b'N_Ch_e05\x00'. Address and physical section length unchanged.
- 816541F9 @16673 -> @16764, extent 9 -> 9: .data+0x25C relocates @16673+0x0; 9-byte NUL-terminated char literal b'N_Ch_e09\x00'. Address and physical section length unchanged.
- 816542F4 @16674 -> @16765, extent 10 -> 10: .data+0x2A0 relocates @16674+0x0; 10-byte NUL-terminated char literal b'BaseMask0\x00'. Address and physical section length unchanged.
- 816542FE @16675 -> @16766, extent 10 -> 10: .data+0x2A4 relocates @16675+0x0; 10-byte NUL-terminated char literal b'BaseMask1\x00'. Address and physical section length unchanged.
- 81654308 @16676 -> @16767, extent 10 -> 10: .data+0x2A8 relocates @16676+0x0; 10-byte NUL-terminated char literal b'BaseMask2\x00'. Address and physical section length unchanged.
- 81654312 @16677 -> @16768, extent 10 -> 10: .data+0x2AC relocates @16677+0x0; 10-byte NUL-terminated char literal b'BaseMask3\x00'. Address and physical section length unchanged.
- 8165433C @16679 -> @16770, extent 11 -> 11: .data+0x2EC relocates @16679+0x0; 11-byte NUL-terminated char literal b'Picture_00\x00'. Address and physical section length unchanged.
- 81654347 @16680 -> @16771, extent 11 -> 11: .data+0x2F0 relocates @16680+0x0; 11-byte NUL-terminated char literal b'Picture_01\x00'. Address and physical section length unchanged.
- 81654352 @16681 -> @16772, extent 11 -> 11: .data+0x2F4 relocates @16681+0x0; 11-byte NUL-terminated char literal b'Picture_02\x00'. Address and physical section length unchanged.
- 8165435D @16682 -> @16773, extent 11 -> 11: .data+0x2F8 relocates @16682+0x0; 11-byte NUL-terminated char literal b'Picture_03\x00'. Address and physical section length unchanged.
- 81654460 @16689 -> @16780, extent 9 -> 9: .data+0x3F4 relocates @16689+0x0; 9-byte NUL-terminated char literal b'N_Clock0\x00'. Address and physical section length unchanged.
- 81654469 @16690 -> @16781, extent 9 -> 9: .data+0x3F8 relocates @16690+0x0; 9-byte NUL-terminated char literal b'N_Clock1\x00'. Address and physical section length unchanged.
- 81654488 @24438 -> @24582, extent 14 -> 14: .text+0x3FA relocates @24438+0x0; 14-byte NUL-terminated char literal b'sdChanSel.ash\x00'. Address and physical section length unchanged.
- 81654496 @24439 -> @24583, extent 17 -> 17: .text+0x416 relocates @24439+0x0; 17-byte NUL-terminated char literal b'corrupt_icon.ash\x00'. Address and physical section length unchanged.
- 816544A7 @24489 -> @24633, extent 25 -> 25: .text+0x626 relocates @24489+0x0; 25-byte NUL-terminated char literal b' ... wait for bs2 abord\n\x00'. Address and physical section length unchanged.
- 816544C0 @24490 -> @24634, extent 27 -> 27: .text+0x66A relocates @24490+0x0; 27-byte NUL-terminated char literal b'*** BS2 abort costs: %dms\n\x00'. Address and physical section length unchanged.
- 816544DC jumptable_816544DC -> @24741, extent 56 -> 56: .text+0xDCA relocates jumptable_816544DC+0x0; 56-byte typed pointer/jump table; +0x0->processWorkerCommands__Q33ipl5scene15SDChannelSelectFv+0x408, +0x4->processWorkerCommands__Q33ipl5scene15SDChannelSelectFv+0x21C, +0x8->processWorkerCommands__Q33ipl5scene15SDChannelSelectFv+0x234. Address and physical section length unchanged.
- 81654514 jumptable_81654514 -> @24981, extent 64 -> 64: .text+0x1EAE relocates jumptable_81654514+0x0; 64-byte typed pointer/jump table; +0x0->processWorkerState__Q33ipl5scene15SDChannelSelectFv+0xA0, +0x4->processWorkerState__Q33ipl5scene15SDChannelSelectFv+0x94, +0x8->processWorkerState__Q33ipl5scene15SDChannelSelectFv+0xAC. Address and physical section length unchanged.
- 81654554 @24961 -> @25087, extent 11 -> 11: .text+0x2266 relocates @24961+0x0; 11-byte NUL-terminated char literal b'T_TimerMes\x00'. Address and physical section length unchanged.
- 8165455F @24962 -> @25088, extent 14 -> 14: .text+0x22F2 relocates @24962+0x0; 14-byte NUL-terminated char literal b'T_TimerMes_01\x00'. Address and physical section length unchanged.
- 81654570 jumptable_81654570 -> @25094, extent 60 -> 60: .text+0x224A relocates jumptable_81654570+0x0; 60-byte typed pointer/jump table; +0x0->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x3E8, +0x4->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x3E8, +0x8->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x2A4. Address and physical section length unchanged.
- 816545AC jumptable_816545AC -> @25093, extent 64 -> 64: .text+0x21F2 relocates jumptable_816545AC+0x0; 64-byte typed pointer/jump table; +0x0->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x24C, +0x4->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x24C, +0x8->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x24C. Address and physical section length unchanged.
- 816545EC jumptable_816545EC -> @25092, extent 64 -> 64: .text+0x2166 relocates jumptable_816545EC+0x0; 64-byte typed pointer/jump table; +0x0->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x1C0, +0x4->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x1C0, +0x8->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x27C. Address and physical section length unchanged.
- 8165462C jumptable_8165462C -> @25091, extent 64 -> 64: .text+0x20DA relocates jumptable_8165462C+0x0; 64-byte typed pointer/jump table; +0x0->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x134, +0x4->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x134, +0x8->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x148. Address and physical section length unchanged.
- 8165466C jumptable_8165466C -> @25090, extent 40 -> 40: .text+0x200E relocates jumptable_8165466C+0x0; 40-byte typed pointer/jump table; +0x0->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0x68, +0x4->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0xAC, +0x8->updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv+0xAC. Address and physical section length unchanged.
- 81654694 jumptable_81654694 -> @25466, extent 120 -> 120: .text+0x359E relocates jumptable_81654694+0x0; 120-byte typed pointer/jump table; +0x0->calcNormal__Q33ipl5scene15SDChannelSelectFv+0x10C, +0x4->calcNormal__Q33ipl5scene15SDChannelSelectFv+0x4C, +0x8->calcNormal__Q33ipl5scene15SDChannelSelectFv+0x10C. Address and physical section length unchanged.
- 8165480F @26032 -> @25863, extent 14 -> 14: .text+0x4B2E relocates @26032+0x0; 14-byte NUL-terminated char literal b'WIPL_BGM_MENU\x00'. Address and physical section length unchanged.
- 8165481D @26047 -> @26098, extent 11 -> 11: .text+0x589A relocates @26047+0x0; 11-byte NUL-terminated char literal b'WSD_SELECT\x00'. Address and physical section length unchanged.
- 81654828 @26062 -> @26120, extent 16 -> 16: .text+0x59FA relocates @26062+0x0; 16-byte NUL-terminated char literal b'WIPL_SE_BT_PUSH\x00'. Address and physical section length unchanged.
- 8165497E @26231 -> @26552, extent 22 -> 22: .text+0x75F2 relocates @26231+0x0; 22-byte NUL-terminated char literal b'WIPL_SE_CH_TARGETTING\x00'. Address and physical section length unchanged.
- 81654994 @26266 -> @26600, extent 16 -> 16: .text+0x799E relocates @26266+0x0; 16-byte NUL-terminated char literal b'WIPL_SE_CH_HOLD\x00'. Address and physical section length unchanged.
- 816549A4 @26311 -> @26645, extent 15 -> 15: .text+0x7ABA relocates @26311+0x0; 15-byte NUL-terminated char literal b'WIPL_SE_CH_SET\x00'. Address and physical section length unchanged.
- 816549B3 @26312 -> @26646, extent 20 -> 20: .text+0x7AFA relocates @26312+0x0; 20-byte NUL-terminated char literal b'WIPL_SE_CH_NOT_MOVE\x00'. Address and physical section length unchanged.
- 816549C7 @26336 -> @26677, extent 16 -> 16: .text+0x7D6E relocates @26336+0x0; 16-byte NUL-terminated char literal b'WIPL_SE_CH_DRAG\x00'. Address and physical section length unchanged.
- 816549D7 @26559 -> @26753, extent 15 -> 15: .text+0x8192 relocates @26559+0x0; 15-byte NUL-terminated char literal b'WIPL_SE_DECIDE\x00'. Address and physical section length unchanged.
- 81654204 lbl_81654204 -> mscChannelPaneNames__Q33ipl5scene15SDChannelSelect, extent 240 -> 240: .text+0x574A relocates lbl_81654204+0x0; 240-byte typed pointer/jump table; +0x0->@16631+0x0, +0x4->@16631+0x0, +0x8->@16631+0x0. Address and physical section length unchanged.
- 8165431C lbl_8165431C -> @16769, extent 32 -> 10: .data+0x2B0 relocates lbl_8165431C+0x0; 10-byte NUL-terminated char literal b'BaseMask4\x00'. Address and physical section length unchanged.
- 81654328 new symbol mscBasePaneNames__Q33ipl5scene15SDChannelSelect, extent 20 inside formerly aggregated lbl_8165431C: draw__Q33ipl5scene15SDChannelSelectFv .text+0x38b8 `addi r25, r26, 0x2a0` via relocation-derived base register r26; 20-byte typed pointer/jump table; +0x0->@16674+0x0, +0x4->@16675+0x0, +0x8->@16676+0x0. Address and physical section length unchanged.
- 81654368 lbl_81654368 -> @16774, extent 32 -> 11: .data+0x2FC relocates lbl_81654368+0x0; 11-byte NUL-terminated char literal b'Picture_04\x00'. Address and physical section length unchanged.
- 81654374 new symbol mscPicturePaneNames__Q33ipl5scene15SDChannelSelect, extent 20 inside formerly aggregated lbl_81654368: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x3fc4 `addi r28, r27, 0x2ec` via relocation-derived base register r27; 20-byte typed pointer/jump table; +0x0->@16679+0x0, +0x4->@16680+0x0, +0x8->@16681+0x0. Address and physical section length unchanged.
- 81654388 lbl_81654388 -> mscEdgePaneNames__Q33ipl5scene15SDChannelSelect, extent 20 -> 20: .text+0x5472 relocates lbl_81654388+0x0; 20-byte typed pointer/jump table; +0x0->@16684+0x0, +0x4->@16685+0x0, +0x8->@16686+0x0. Address and physical section length unchanged.
- 81654472 lbl_81654472 -> @16782, extent 22 -> 9: .data+0x3FC relocates lbl_81654472+0x0; 9-byte NUL-terminated char literal b'N_Clock2\x00'. Address and physical section length unchanged.
- 8165447C new symbol mscClockPaneNames__Q33ipl5scene15SDChannelSelect, extent 12 inside formerly aggregated lbl_81654472: draw__Q33ipl5scene15SDChannelSelectFv .text+0x39f0 `addi r26, r26, 0x3f4` via relocation-derived base register r26; 12-byte typed pointer/jump table; +0x0->@16689+0x0, +0x4->@16690+0x0, +0x8->lbl_81654472+0x0. Address and physical section length unchanged.
- 8165473B lbl_8165473B -> @25703, extent 212 -> 11: .text+0x5C46 relocates lbl_8165473B+0x0; 11-byte NUL-terminated char literal b'Picture_16\x00'. Address and physical section length unchanged.
- 81654746 new symbol @25704, extent 22 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x4060 `addi r4, r27, 0x6be` via relocation-derived base register r27; 22-byte NUL-terminated char literal b'mn_SdcardMenu_a.brlan\x00'. Address and physical section length unchanged.
- 8165475C new symbol @25705, extent 25 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x4088 `addi r7, r27, 0x6d4` via relocation-derived base register r27; 25-byte NUL-terminated char literal b'mn_SdcardMenu_Page.brlyt\x00'. Address and physical section length unchanged.
- 81654775 new symbol @25706, extent 16 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40b0 `addi r7, r27, 0x6ed` via relocation-derived base register r27; 16-byte NUL-terminated char literal b'mn_Nocard.brlyt\x00'. Address and physical section length unchanged.
- 81654785 new symbol @25707, extent 19 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40c4 `addi r4, r27, 0x6fd` via relocation-derived base register r27; 19-byte NUL-terminated char literal b'mn_Nocard_IN.brlan\x00'. Address and physical section length unchanged.
- 81654798 new symbol @25708, extent 9 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40c8 `addi r5, r27, 0x710` via relocation-derived base register r27; 9-byte NUL-terminated char literal b'Group_00\x00'. Address and physical section length unchanged.
- 816547A1 new symbol @25709, extent 20 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40dc `addi r4, r27, 0x719` via relocation-derived base register r27; 20-byte NUL-terminated char literal b'mn_Nocard_Out.brlan\x00'. Address and physical section length unchanged.
- 816547B5 new symbol @25710, extent 22 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40f4 `addi r4, r27, 0x72d` via relocation-derived base register r27; 22-byte NUL-terminated char literal b'mn_Nocard_IN_02.brlan\x00'. Address and physical section length unchanged.
- 816547CB new symbol @25711, extent 9 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x40f8 `addi r5, r27, 0x743` via relocation-derived base register r27; 9-byte NUL-terminated char literal b'Group_01\x00'. Address and physical section length unchanged.
- 816547D4 new symbol @25712, extent 23 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x410c `addi r4, r27, 0x74c` via relocation-derived base register r27; 23-byte NUL-terminated char literal b'mn_Nocard_Out_02.brlan\x00'. Address and physical section length unchanged.
- 816547EB new symbol @25713, extent 21 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x4124 `addi r4, r27, 0x763` via relocation-derived base register r27; 21-byte NUL-terminated char literal b'mn_Nocard_Wait.brlan\x00'. Address and physical section length unchanged.
- 81654800 new symbol @25715, extent 15 inside formerly aggregated lbl_8165473B: createBaseLayout__Q33ipl5scene15SDChannelSelectFv .text+0x4180 `addi r7, r27, 0x778` via relocation-derived base register r27; 15-byte NUL-terminated char literal b'help_Btn.brlyt\x00'. Address and physical section length unchanged.
- 81654838 lbl_81654838 -> @26130, extent 326 -> 18: .text+0x5A8A relocates lbl_81654838+0x0; 18-byte NUL-terminated char literal b'WIPL_SE_CH_SELECT\x00'. Address and physical section length unchanged.
- 8165484A new symbol @26333, extent 22 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x66f8 `addi r7, r31, 0x7c2` via relocation-derived base register r31; 22-byte NUL-terminated char literal b'mn_SdcardMenu_d.brlyt\x00'. Address and physical section length unchanged.
- 81654860 new symbol @26334, extent 22 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x670c `addi r4, r31, 0x7d8` via relocation-derived base register r31; 22-byte NUL-terminated char literal b'mn_SdcardMenu_d.brlan\x00'. Address and physical section length unchanged.
- 81654876 new symbol @26335, extent 18 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x678c `addi r7, r31, 0x7ee` via relocation-derived base register r31; 18-byte NUL-terminated char literal b'my_TVMask_a.brlyt\x00'. Address and physical section length unchanged.
- 81654888 new symbol @26336, extent 24 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x67a0 `addi r4, r31, 0x800` via relocation-derived base register r31; 24-byte NUL-terminated char literal b'my_TVMask_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 816548A0 new symbol @26337, extent 11 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x67a4 `addi r5, r31, 0x818` via relocation-derived base register r31; 11-byte NUL-terminated char literal b'Picture_00\x00'. Address and physical section length unchanged.
- 816548AB new symbol @26338, extent 23 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x67b8 `addi r4, r31, 0x823` via relocation-derived base register r31; 23-byte NUL-terminated char literal b'my_TVMask_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 816548C2 new symbol @26339, extent 19 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x67fc `addi r7, r31, 0x83a` via relocation-derived base register r31; 19-byte NUL-terminated char literal b'my_TVShade_a.brlyt\x00'. Address and physical section length unchanged.
- 816548D5 new symbol @26340, extent 25 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x6810 `addi r4, r31, 0x84d` via relocation-derived base register r31; 25-byte NUL-terminated char literal b'my_TVShade_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 816548EE new symbol @26342, extent 24 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x6828 `addi r4, r31, 0x866` via relocation-derived base register r31; 24-byte NUL-terminated char literal b'my_TVShade_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 81654906 new symbol @26344, extent 10 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x68d0 `addi r4, r31, 0x87e` via relocation-derived base register r31; 10-byte NUL-terminated char literal b'4x3_dummy\x00'. Address and physical section length unchanged.
- 81654910 new symbol @26345, extent 19 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x6930 `addi r7, r31, 0x888` via relocation-derived base register r31; 19-byte NUL-terminated char literal b'my_TVApear_a.brlyt\x00'. Address and physical section length unchanged.
- 81654923 new symbol @26346, extent 25 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x6944 `addi r4, r31, 0x89b` via relocation-derived base register r31; 25-byte NUL-terminated char literal b'my_TVApear_a_Apear.brlan\x00'. Address and physical section length unchanged.
- 8165493C new symbol @26347, extent 24 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x695c `addi r4, r31, 0x8b4` via relocation-derived base register r31; 24-byte NUL-terminated char literal b'my_TVApear_a_Lost.brlan\x00'. Address and physical section length unchanged.
- 81654954 new symbol @26348, extent 16 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x69e4 `addi r7, r31, 0x8cc` via relocation-derived base register r31; 16-byte NUL-terminated char literal b'wait_icon.brlyt\x00'. Address and physical section length unchanged.
- 81654964 new symbol @26349, extent 26 inside formerly aggregated lbl_81654838: createSceneLayouts__Q33ipl5scene15SDChannelSelectFv .text+0x69f8 `addi r4, r31, 0x8dc` via relocation-derived base register r31; 26-byte NUL-terminated char literal b'wait_icon_wait_loop.brlan\x00'. Address and physical section length unchanged.
- 81654A08 lbl_81654A08 -> __vt__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandler, extent 28 -> 28: .text+0x52 relocates lbl_81654A08+0x0; 28-byte vtable (two header words and 5 virtual slots); +0x8->onEvent__Q33ipl5scene24SDButtonEventHandlerBaseFUlUlPv+0x0, +0xC->setManager__Q23gui12EventHandlerFPQ23gui7Manager+0x0, +0x10->setLatestEventCtrlNo__Q23gui12EventHandlerFi+0x0. Address and physical section length unchanged.
- 81654A24 lbl_81654A24 -> __vt__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@27SDChannelSelectEventHandler, extent 24 -> 24: .text+0x41BA relocates lbl_81654A24+0x0; 24-byte vtable (two header words and 4 virtual slots); +0x8->onEvent__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@27SDChannelSelectEventHandlerFUlUlPv+0x0, +0xC->setManager__Q23gui12EventHandlerFPQ23gui7Manager+0x0, +0x10->setLatestEventCtrlNo__Q23gui12EventHandlerFi+0x0. Address and physical section length unchanged.
- 81654A3C lbl_81654A3C -> __vt__Q33ipl5scene15SDChannelSelect, extent 252 -> 104: .text+0x2A relocates lbl_81654A3C+0x0; 104-byte vtable (two header words and 24 virtual slots); +0x8->__dt__Q33ipl5scene15SDChannelSelectFv+0x0, +0xC->getParent__Q33ipl5scene4BaseFv+0x0, +0x10->getChild__Q33ipl5scene4BaseFv+0x0. Address and physical section length unchanged.

SDChannelSelect: fetched origin before starting; no remote source fix. All data now 2960/2960 with every non-text section 100%. The three live vtables pair by their proven class names despite source offsets being 32 bytes earlier. The scene vtable is 104 bytes (two header words and 24 slots, including null ABI slots); its old 252-byte extent absorbed 148 bytes of deduplicated GUI tables. The anonymous target .data+0x960..0x980 remains unowned, unchanged and unfabricated; it does not prevent exact per-object data comparison. Source weak tables are also unchanged. Final full gate follows.

## High-round final full gate

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 27108/33828 data 2960/2960 functions 117/129 fuzzy 99.5051 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 117/129
[src/scene/channelSelect/iplChannelSelect] objdiff: code 24736/25668 data 2336/2336 functions 101/102 fuzzy 99.7634 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 101/102
[libs/RVL_SDK/src/wad/wad] objdiff: code 13180/24500 data 528/528 functions 35/40 fuzzy 98.9416 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 35/40
[libs/RevoEX/src/nhttp/NHTTP_thread] objdiff: code 10528/11292 data 504/504 functions 25/26 fuzzy 99.9044 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_thread] instruction-exact functions: 25/26
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

src/scene/sdChannelSelect/iplSDChannelSelect: matched_data 224 -> 2960/2960; instruction-exact 117 -> 117/129; code bytes 27108 -> 27108/33828.
src/scene/channelSelect/iplChannelSelect: matched_data 192 -> 2336/2336; instruction-exact 101 -> 101/102; code bytes 24736 -> 24736/25668.
libs/RVL_SDK/src/wad/wad: matched_data 64 -> 528/528; instruction-exact 35 -> 35/40; code bytes 13180 -> 13180/24500.
libs/RevoEX/src/nhttp/NHTTP_thread: matched_data 304 -> 504/504; instruction-exact 25 -> 25/26; code bytes 10528 -> 10528/11292.

Fresh independent audit confirms all four units have every non-text section at 100%, matched_data equals total_data, and every baseline instruction-exact function is preserved. The physical section byte totals and all symbol addresses stay unchanged. Config diff audit checked all 401 changed symbol lines are inside the four owned .data ranges; no source file, shared header, function symbol, other unit symbol or split changed. The 32-byte SD zero range and all alignment/deduplicated storage remain in the extraction. They need no source padding. Final gate log /tmp/data-d5-r3-final-gate.log; independent section/relocation audit /tmp/data-d5-r3-final-audit.txt.

Remaining code-only functions (19), outside the achieved non-text-data goal; each retains at least three logged source attempts:

- create__Q33ipl5scene15SDChannelSelectFv: 97.73972%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv: 99.15205%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.81188%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.833336%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.29365%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.55125%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 99.65714%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- calcCommon__Q33ipl5scene15SDChannelSelectFv: 99.07407%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- initializeNormalPage__Q33ipl5scene15SDChannelSelectFv: 98.93617%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- selectChannel__Q33ipl5scene15SDChannelSelectFii: 98.305084%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: 93.4721%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface: 98.541664%; 5 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- setChannelScissor__Q33ipl5scene13ChannelSelectCFPCQ33ipl5scene10ChannelObj: 93.48498%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- WADImportGetBlocks: 94.24161%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- WADImportEx: 99.02269%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- WAD_815C1288: 96.803276%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- WADBackupEx: 97.370995%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- WADImportDVDExForBS: 97.49049%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
- NHTTPi_ThreadParseHeaderProc: 98.58639%; 3 prior distinct compiled source attempts, with instruction-level reasons recorded in the round-2 manifest. Code unchanged this round.
