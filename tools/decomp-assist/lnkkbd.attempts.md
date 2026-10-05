# lnkkbd: link iplKeyboard

Worktree: data-d1. Branch: agent/w1005/lnkkbd. Base: a461786f.
Scope: src/system/iplKeyboard, its guarded declarations if needed, and its
configure.py entry. The assigned LINK task overrides common.md's matching-only
phase. Acceptance requires 32/32 instruction-exact functions, identical pools,
unchanged other objects, and a full gate with DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d.

## Baseline

Fetched origin/main and confirmed a461786f. Clean worktree. Rebuilt the object,
progress report, and build/43U/ok. The existing report was stale at 31/32; the
fresh baseline is 32/32, code 6024/6024, data 1184/1184, linked code 0.
The baseline DOL has the required SHA1. pool_diff reports 28/28 identical
strings. create has 318/318 instructions and getSaveData has 18/18, both diffs 0.
Saved the baseline report and SHA256 hashes for 1027 source objects under build/.

## Trial 1: restore getSaveData's definition order

The target object's final functions are doSave at 0x1544, memo::getSaveData at
0x1698, touchFormInDisp at 0x16e0, sendRelease at 0x173c, getZiSystemDic at
0x1768, getZiOemDic at 0x1774, and keyboard::getState at 0x1780.
The source placed the existing out-of-line memo::getSaveData definition after
keyboard::getState. Move that definition immediately after doSave by reopening
the ipl::keyboard namespaces around the following methods. Keep every function
body and header unchanged. Switch only iplKeyboard from Equivalent to Matching.
Additional weak NW4R destructors in the source object are linker deduplicated;
do not remove or replace their definitions.

Result: the first trial restores the required DOL SHA1 with Matching enabled.
pool_diff remains identical at 28/28. The final seven functions now follow the
target's order, with each source offset exactly 0xC0 above its target offset;
three existing 64-byte weak destructors account for that deduplicated space.
build/43U/ok passes. Proceed to the required full clean gate and compare every
other source object's hash against the fresh baseline.

## Final verification

Ran the required full gate without --quick. All 32 exact-name objdiff functions
remain 100.0%; every ctxdiff has equal instruction counts and diffs 0. Pools
remain identical at 28 strings. Code 6024/6024 and data 1184/1184 are now fully
linked, with both measures at 100%. No remaining functions in this leaf.

Compared SHA256 hashes of all 1027 freshly rebuilt source objects against the
baseline. Only src/system/iplKeyboard.o changed; all 1026 other objects are
byte-identical. Comparing complete per-unit report entries also finds only
main/src/system/iplKeyboard changed. No header edit was needed.

Full gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/iplKeyboard] pool: IDENTICAL
[src/system/iplKeyboard] objdiff: code 6024/6024 data 1184/1184 functions 32/32 fuzzy 100.0000 linked code 6024
[src/system/iplKeyboard] instruction-exact functions: 32/32
[src/system/iplKeyboard]   section .data size 1168 match 100.0
[src/system/iplKeyboard]   section .sdata size 8 match 100.0
[src/system/iplKeyboard]   section .sdata2 size 8 match 100.0
[src/system/iplKeyboard]   section .text size 6024 match 100.0
[src/system/iplKeyboard] baseline: code 6024/6024 data 1184 functions 32 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.69692 -> 92.69692
global fuzzy_match_percent: 99.77907 -> 99.77907
global complete_code_percent: 76.20227 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

Local build evidence: build/lnkkbd-baseline-report.json,
build/lnkkbd-baseline-object-hashes.json, build/lnkkbd-isolation.txt,
build/lnkkbd-ctxdiff.txt, and build/lnkkbd-full-gate.txt.

Changed source: src/system/iplKeyboard.cpp, configure.py. Function bodies are
unchanged. The only source change moves the existing out-of-line getSaveData
definition to the target's function order. No new assembly, forced placement,
padding, symbol metadata, or compiler options. Ready for parent verification.
