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
