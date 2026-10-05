# lnkaddr: link iplAddress

Worktree data-d5, branch agent/w1005/lnkaddr, base b276099f.
The assigned LINK task overrides common.md's matching-only phase.
Acceptance requires 101/101 exact functions, unchanged code/data credit and
other source objects, Matching enabled, and the full gate with DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d.

## Baseline

Fetched origin/main under the shared Git lock. The remote advanced to ca031bd8;
its changes affect iplMemoryCardLib.h and lv19 logs, not this leaf. Address
remains NonMatching. Kept the assigned branch without merging or rebasing.
Fresh 43U build and report: 101/101 exact-name functions, code 23988/23988,
data 1964/1964, linked code 0. Pool strings identical, 81/81. Saved report and
all source object SHA256 hashes under build/lnkaddr-baseline-*.

The target object emits draw, VEC2::operator*(f32), Pane::SetTranslate(VEC3),
destroy. Target offsets are 0xc7c, 0x1028, 0x1070, 0x108c respectively.
Our object emits draw, SetTranslate(VEC2), SetTranslate(VEC3), VEC2::operator*,
VEC2 constructor, destroy. After linker deduplication this reverses the two
retained inline functions. The target draw calls SetTranslate(VEC2), while
add_translate calls SetTranslate(VEC3); function code already matches.

## Trial 1: reproduce the link failure

Change only the configure.py entry to Matching and map the rebuilt DOL.

Result: 103 differing bytes, unchanged DOL size. Differences cover the two
reversed functions and calls in BoardObject, ChannelObj, SDChannelObj,
SDMemory, and Address. Both functions still have ctxdiff diffs 0.

## Trial 2: delay the VEC3 setter definition

Use the existing IPL_ADDRESS_MATCHING macro to declare SetTranslate(VEC3)
in the header and define it inline immediately after Address::draw.
Keep its body unchanged. This allows draw's VEC2 multiplication to emit first,
then the setter at its original position before Address::destroy. The inline
definition should preserve weak binding. No math operator or caller edit.
The exported target decompilation confirms ordinary mTranslate assignment.

The rebuilt object retains STB_WEAK binding. Its order is SetTranslate(VEC2)
at 0x1108, VEC2::operator* at 0x1144, the deduplicated VEC2 constructor at
0x118c, SetTranslate(VEC3) at 0x1198, and destroy at 0x11b4. Filtering source
functions to the 101 target names now reproduces the complete target order.
Pool 81/81 remains identical; SetTranslate(VEC3) is 7/7 instructions, diffs 0.
IPL_ADDRESS_MATCHING is defined only by iplAddress.cpp.

Result: full incremental build passes with Matching enabled. DOL SHA1 is
26116613f624061ba99c8d1a299aaa6efa85670d; doldiff reports zero differing bytes
and equal 3867904-byte files. All 101 exact-name objdiff functions remain 100%,
and all 101 ctxdiff runs have equal instruction counts and diffs 0.
Code 23988/23988 and data 1964/1964 are now fully linked.
Proceed to the required clean full gate and all-object isolation check.

## Final verification

The required full gate ran without --quick and passed from a clean 43U build.
All 101 functions remain exact. Code 23988/23988 and data 1964/1964 are 100%
matched and linked. The final pool is identical at 81/81 strings, and doldiff
reports zero differing bytes with the required DOL SHA1.

Compared SHA256 hashes of all 1027 rebuilt source objects against the fresh
baseline. Only src/scene/address/iplAddress.o changed; all 1026 other objects
are byte-identical. Comparing complete unit entries in the two live reports
also finds only main/src/scene/address/iplAddress changed. No units or objects
were added or removed. There are no remaining open functions in this leaf.

Source changes are confined to the Matching entry, the existing Address-only
header guard, and the unchanged setter body at its target emission position.
All target function names occur in target order. No new assembly, labels,
padding, linker directives, compiler options, or symbol metadata were added.

Full gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 23988/23988 data 1964/1964 functions 101/101 fuzzy 100.0000 linked code 23988
[src/scene/address/iplAddress] instruction-exact functions: 101/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 100.0
[src/scene/address/iplAddress] baseline: code 23988/23988 data 1964 functions 101 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.77331 -> 92.77331
global fuzzy_match_percent: 99.78063 -> 99.78063
global complete_code_percent: 76.40339 -> 77.20428
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

Local evidence: build/lnkaddr-baseline-report.json,
build/lnkaddr-baseline-object-hashes.json, build/lnkaddr-trial1-doldiff.txt,
build/lnkaddr-function-order.txt, build/lnkaddr-ctxdiff.txt,
build/lnkaddr-full-gate.txt, and build/lnkaddr-isolation.json.
Ready for independent parent validation.
