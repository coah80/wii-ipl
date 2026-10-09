# opus-candbox attempts

Worktree `sol-high`, branch `agent/w1009/o-candbox`, base `72e9c8d6`. Unit `src/keyboard/tiCandidateBox`, last open function `LayoutByNW4R::createAnmPane_` (6/216, count r23 and slot r31 swapped). Read opus-common.md, levers.md, effort-policy entries, sol-x9 log, sol-m4 log (branch `agent/w1009/candbox-max`), saved sol-r12/sol-y11 diffs.

Baseline: full build OK, DOL `26116613...`, odiff 6/216, pool identical 57/57. combosweep (single and pairwise pragmas): `base 6 -> 6`, no hit.

## Root cause

`tiPredictLang::create` is already exact and has the same inner loop with the same struct (`char paneName[20]`, `count`, `forceAddName`, `pAnims[8]`). Its target has count r31 and slot r23, which is what createAnmPane_ needs.

A private mwdbg trace of `tiPredictLang::create` (port 19931 copy of the launcher, shared tool unchanged) shows why. The slot base `p + j*4` is IRO CSE temp `@7026` (vreg r45) and forceAddName is IRO temp `@7028` (r44). Both are numbered after the named locals and before the hoisted constructor constants, so they simplify before the constants and color after them (slot r23). Count is a late anonymous load hoisted out of the loop condition (r131), so it colors first (r31).

The same natural loop inside tiCandidateBox (`j < paneAnimations.count`, `paneAnimations.pAnims[j]->` three times) gives 220 insns. No IRO temps are created, the slot is recomputed in each branch, and constant `2` survives pass-1 spilling.

Table declaration trials with that loop:

| trial | table | result |
| --- | --- | --- |
| 01 | `extern "C" const CandidatePaneData scCandidatePaneData` (struct wrapper, aligned(8)) | 158/220 |
| 02 | `static const CandidatePaneData` (struct wrapper) | 158/220 |
| 03 | `extern "C" const PaneToAnimation[]` (plain array) | 158/220 |
| 04 | `static const PaneToAnimation[]` (plain array, no aligned) | **0/216** |

IRO only CSEs the table loads and addresses when the table is a static plain array, which is how every sibling unit declares it (`csPaneToAnimation`). The `CandidatePaneData` wrapper and `extern "C"` were decomp scaffolding. Without `aligned(8)` the table still lands at .data 0x28, size 0x680.

## Source changes

- Table: `static const PaneToAnimation csPaneToAnimation[]`, same name as tiToolBar/tiPredictLang/pctype. Removed the unused `CandidatePaneData` struct.
- `createAnmPane_`: the tiPredictLang/tiToolBar loop form, with no count/forceAddName/animation locals.
- symbols.txt: `scCandidatePaneData` -> `csPaneToAnimation__Q29textinput12candidatebox` (scope:local). Same address and size. Only tiCandidateBox referenced the old name.

Unit after this: 112/112 functions, code 100%, data 100%, all sections 100%, pool identical.

## Link (Matching flip)

First flip: DOL `8d444a7b...`. Two causes, both checked against the original objects:

1. Thunk order. Target `@36@__dt__` comes before `@36@setRootPaneScaleFor4x3..init`; ours put it last (already true on the old baseline). This is the "move to end on touch" thunk list (eggAudioExpMgr, lever 12). tiPredictLang/tiToolBar/tiCellPhone fix it with a header `Sample : public LayoutByNW4R` behind a `*_SAMPLE_CLASS` macro, and `__vt__Q39textinput12candidatebox6Sample` exists in the DOL. A Sample with only `virtual ~Sample() {}` does not move the thunks. It needs the inline constructor, so the Base/EventHandler/LayoutByNW4R constructor guards also accept `TI_CANDIDATEBOX_SAMPLE_CLASS`, as tiPredictLang.h does. After that, all 112 common functions are in target order. Proof it is required: removing it leaves the wrong thunk order and DOL `5507fb9e...`.
2. Weak vtable hole. The target has 0x40 zero bytes between `__vt__...AnmObserver` (0xd48) and `__vt__Q39textinput4util12AnimObserver` (0xd94). Ours left only the deduplicated gui::EventHandler copy (0x18), so everything after shifted by -0x20/-0x24. util::Animation methods were inline in the original: they sit as scattered weak functions in tiInputForm's .text, and MyTiManager.cpp already defines them `inline`. UITextArea has a `util::Animation` member, so the original object also emitted a weak `__vt__Q39textinput4util9Animation` (0x24, kept from tiInputForm). EventHandler 0x18 at 0xd58 + Animation 0x24 at 0xd70 ends at 0xd94. I added the same inline definitions as MyTiManager.cpp at the end of tiCandidateBox.cpp, with startAnm in this TU's declared parameter order. Only virtual calls exist, so no code changes. .data is now 0xda0, the target size.

Flip with both: full build OK, `build/43U/main.dol` SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

Trial snapshots: `/tmp/opus-candbox/trials/`. Captures: `/tmp/opus-candbox-cap-predictlang`, `/tmp/opus-candbox-cap-f01`.

## Gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiCandidateBox] pool: IDENTICAL
[src/keyboard/tiCandidateBox] objdiff: code 24000/24000 data 4652/4652 functions 112/112 fuzzy 100.0000 linked code 24000
[src/keyboard/tiCandidateBox] instruction-exact functions: 112/112
regressions vs baseline: 0
global matched_code_percent: 98.14728 -> 98.17613
global complete_code_percent: 91.22256 -> 92.02384
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

origin/main moved to `82783c6e` during the run (BS2Update lines in configure.py/symbols.txt only, no overlap). Not rebased.
