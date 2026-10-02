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
