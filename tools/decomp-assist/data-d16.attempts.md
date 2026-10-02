# Data d16 attempts

HEAD and fetched origin/main are 6f49df32. Both owned units are unchanged on origin/main. Scope is data symbols only inside the two assigned split ranges; no source/code/configure/split changes.

Baseline: MyTiManager instruction-exact 91/91, code 20196/20196, data 148/1132; fa/pf_path instruction-exact 27/27, code 11872/11872, data 8/56. Pools identical, 7 and 0 strings. Initial pool commands with unit paths failed because this version of pool_diff accepts object paths; corrected commands passed before any mutation.

Fresh ELF audit: MyTiManager source .data now contains a genuine 36-byte weak Animation vtable at +0x3b0. Target +0x3b0..0x3d8 remains zero without outgoing relocations. Canonical retained Animation vtable is 0x8165D258, with seven real virtual slots. This improves the earlier evidence in data-d4, whose source ended at +0x3b0. The current source ends at +0x3d4; the last four target bytes are zero section alignment. Tail ownership will be tested only with this type/relocation evidence.

fa/pf_path: both .sdata byte arrays are identical for all 48 bytes. The target null literal at +4 is recorded as four bytes, compiler char[2] is two bytes. The target initializer at +40 is split into two single bytes, compiler emits one two-byte const array, used by lbz with addends 0 and 1. The final target space literal is recorded as two bytes, compiler emits a four-byte narrow char string with explicit trailing zero bytes. .sdata2 has two identical two-byte arrays similarly split into individual byte symbols; trailing two bytes are zero alignment. No initializer difference or non-exact function exists.

## pf_path literal extent proof

lbl_81698394 at unchanged .sdata:0x81698394 is char[4] literal `"\x20\0\0"`, not char[2]: PFPATH_CheckExtShortName loads it at .text+0x2b78 and +0x2bcc and passes it to PFSTR_StrNCmp; the compiled @2271 has size 4 and bytes 20000000 at the identical +0x2c offset. Extent 2 -> 4 recovers the complete real string including its explicit two zeros and implicit terminator. No address, section size, source object or total_data changes.

Minimal correction selected: other pf_path aliases and initializer sublabels already compare correctly through exact section bytes. Leave all names and other extents alone.

## MyTiManager tail extent proof

lbl_816681E8 at unchanged .data:0x816681E8 covers the discarded weak Animation vtable footprint, size 0x24 rather than 0x28: the compiler emits __vt__Q39textinput4util9Animation at identical .data+0x3b0 with two ABI header words and seven virtual slots, ending +0x3d4; include/keyboard/tiUtil.h declares exactly those seven methods, and the retained retail Animation vtable at 0x8165D258 also has size 0x24 and precisely the same seven relocation targets. Target createMemoInputForm .text+0x9de/+0x9fe and createLetterInputForm +0xb06/+0xb26 refer to the retained canonical table, while source equivalents refer to this weak copy; this demonstrates linker deduplication. The four unrelocated zero bytes at 0x8166820c..0x81668210 align the next unit to eight bytes and are not an eighth virtual method. Correct only the extent, keep the existing label, all addresses, all 984 section bytes and total_data 1132. No source vtable suppressed and no weak-pointer bytes fabricated.

The old log could not infer the tail when its source emitted no Animation table. The current source now supplies independent table-layout evidence. Every source tail relocation is an extra linker-discarded weak entry; no target relocation is removed or altered. The goal depends on correcting true object versus section-alignment ownership, not inventing a name for zero bytes.

## Iteration measurements

After pf_path extent correction, fresh objdiff report: matched_data 8 -> 56/56, .sdata and .sdata2 both 100%, code 11872/11872, functions 27/27. After MyTiManager correction, fresh objdiff report: matched_data 148 -> 1132/1132, all six non-text sections 100%, code 20196/20196, functions 91/91. Correct source-only Ninja targets subsequently report no work to do. Extracted object paths are outputs of SPLIT, not explicit Ninja targets; the two commands naming them reported unknown targets after the required split succeeded, and were corrected to source-only targets before final verification.

Objdiff v3.4.5 source inspection confirms diff_data_section uses the greatest owned-symbol endpoint, excluding physical section-end alignment, and accepts exact raw section bytes when every target relocation matches; extra source weak relocations do not veto this route. Both corrections describe actual object extents and preserve every physical section byte. Names need no correction for these units.

No open function exists in either unit: all 118 functions were exact before this data task. No compiler experiments, code changes, dummy objects, fake virtual slots, forced placement, symbol renames, configure changes, split changes, or remote mutations. The earlier broad requirement for new exact functions does not apply to these explicitly assigned already-code-100% units; preserve exact counts instead.

## Final clean gate and audit

Full non-quick two-unit gate rebuilt 43U from scratch and passed. Fresh post-build pool comparisons remain identical. All 91 MyTiManager and 27 pf_path functions were checked individually with ctxdiff.py: every one reports diffs 0 and identical instruction counts. Output is /tmp/data-d16.ctxdiff-all.txt.

Live progress and build/43U/report.json regenerated after the gate. Both units matched_data == unchanged total_data, code == unchanged total_code, and every section reports 100%. Source bodies and every symbol name/address/section are unchanged; an automated line-by-line config audit confirms exactly the two extent corrections proved above. No remaining non-exact functions or unresolved non-text sections.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/MyTiManager] pool: IDENTICAL
[src/keyboard/MyTiManager] objdiff: code 20196/20196 data 1132/1132 functions 91/91 fuzzy 100.0000 linked code 20196
[src/keyboard/MyTiManager] instruction-exact functions: 91/91
[src/keyboard/MyTiManager]   section .bss size 72 match 100.0
[src/keyboard/MyTiManager]   section .ctors size 4 match 100.0
[src/keyboard/MyTiManager]   section .data size 984 match 100.0
[src/keyboard/MyTiManager]   section .sbss size 16 match 100.0
[src/keyboard/MyTiManager]   section .sdata size 24 match 100.0
[src/keyboard/MyTiManager]   section .sdata2 size 32 match 100.0
[src/keyboard/MyTiManager]   section .text size 20196 match 100.0
[src/keyboard/MyTiManager] baseline: code 20196/20196 data 148 functions 91 fuzzy 100.0000
[libs/RVL_SDK/src/fa/pf_path] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_path] objdiff: code 11872/11872 data 56/56 functions 27/27 fuzzy 100.0000 linked code 11872
[libs/RVL_SDK/src/fa/pf_path] instruction-exact functions: 27/27
[libs/RVL_SDK/src/fa/pf_path]   section .sdata size 48 match 100.0
[libs/RVL_SDK/src/fa/pf_path]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_path]   section .text size 11872 match 100.0
[libs/RVL_SDK/src/fa/pf_path] baseline: code 11872/11872 data 8 functions 27 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 90.94304 -> 90.94304
global fuzzy_match_percent: 99.58742 -> 99.58742
global complete_code_percent: 73.73083 -> 73.73083
global matched_data_percent: 99.36639 -> 99.42271
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
