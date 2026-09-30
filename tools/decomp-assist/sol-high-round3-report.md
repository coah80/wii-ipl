# Matching round 3

Baseline: 91e65d76. Final source: e26ea8f1. Seven owned units; no Matching flags or shared headers changed.

| Unit | Instruction-exact functions | Fuzzy % | Exact code bytes | Exact data bytes |
|---|---:|---:|---:|---:|
| libs/RevoEX/src/nwc24/NWC24Download | 17 -> 17/30 | 97.146930 -> 97.249360 | 3640 -> 3640/12496 | 80 -> 80/80 |
| src/keyboard/tiCellPhone | 83 -> 83/86 | 99.774020 -> 99.774020 | 12824 -> 12824/19028 | 3860 -> 3860/3860 |
| libs/RVL_SDK/src/fa/pf_dir | 34 -> 34/38 | 99.262856 -> 99.536890 | 11428 -> 11428/18976 | 40 -> 40/40 |
| libs/RevoEX/src/nwc24/NWC24MsgCommit | 15 -> 15/18 | 98.433190 -> 98.442566 | 3964 -> 3964/8532 | 72 -> 72/904 |
| libs/RevoEX/src/nwc24/NWC24Mime | 9 -> 11/16 | 90.243630 -> 98.822990 | 2492 -> 3576/6124 | 88 -> 88/88 |
| libs/RevoEX/src/nwc24/NWC24MsgSubject | 7 -> 7/12 | 97.417786 -> 98.587440 | 2776 -> 2776/5352 | 232 -> 232/232 |
| libs/RevoEX/src/nwc24/NWC24MsgRead | 11 -> 11/16 | 98.450645 -> 98.476395 | 2480 -> 2480/4660 | 128 -> 128/128 |

Two new exact functions: CopyWithoutLinearWhiteSpaces (73/73 instructions, ctxdiff 0) and EncodeWord (198/198, ctxdiff 0). MIME gained 1084 exact code bytes. The three priority units have no new exact functions this round; their remaining bodies received the required new attempts. Six units retain 100% data. This is partial matching progress; 38 functions and MsgCommit data remain open.

## Remaining functions

NWC24InitDlTask | 98.923615% | 144/144 instructions | saved-register allocation only (31 differences)
NWC24SetDlInterval | 99.897960% | 147/147 instructions | final task-ID saved register only (3 differences)
NWC24IterateDlTask | 95.000000% | 78/79 instructions | one missing loop-entry branch; induction increment scheduling
NWC24IterateDlTaskEx | 98.034485% | 145/145 instructions | task-ID load scheduled across the flag store and saved registers
NWC24UpdateDlTask | 94.173910% | 247/253 instructions | retry/validation blocks and saved-register frame; six instructions missing
NWC24AddDlTask | 97.552444% | 146/143 instructions | extra saved-register pair and time-validation status branch; three extra instructions
NWC24GetDlTask | 99.728264% | 92/92 instructions | destination/task-ID saved registers only (5 differences)
NWC24PurgeOldestDlTask | 85.829544% | 171/176 instructions | iterator initialization, candidate deletion/error blocks; five instructions missing
NWC24ManageDlTaskListForMenu | 96.743420% | 150/152 instructions | inlined removal-result copies and task-pointer lifetime; two instructions missing
NWC24ExtendDlTaskList | 99.854010% | 137/137 instructions | final reload-result saved register only (4 differences)
NWC24iCheckDlHeaderConsistency | 98.773580% | 212/212 instructions | task-pointer prologue initialization scheduled before parameter moves
NWC24iCreateDlTaskList | 99.624060% | 133/133 instructions | header-pointer saved register only (10 differences)
AddTaskInternal | 93.578550% | 397/401 instructions | URL checks and slot/purge/update status blocks; four instructions missing
onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 99.670090% | 682/682 instructions | saved-register allocation only (37 differences)
create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 99.819820% | 333/333 instructions | pane-record/animation-key and animation-table saved registers only (11 differences)
init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 98.526120% | 536/536 instructions | saved-register allocation only (155 differences)
PFDIR_GetSDD | 99.710144% | 69/69 instructions | two induction-register assignments differ (2 differences)
PFDIR_p_mkdir | 99.649470% | 562/562 instructions | dot-entry constant ordering and saved-register allocation (36 differences)
PFDIR_p_rename | 98.336000% | 625/625 instructions | current-directory traversal loads, zero-cluster branch, long-name masking, and final return; instruction counts agree
PFDIR_p_move | 98.510300% | 635/631 instructions | current-directory traversal loads, ancestry tests and long-name masking; four extra instructions
NWC24CommitMsgInternal | 99.915360% | 827/827 instructions | saved-register allocation only (14 differences)
CheckMsgBoxSpace | 85.573990% | 223/223 instructions | attachment-size arithmetic operand/load scheduling and saved-register allocation (73 differences)
WriteMIMEAttachHeader | 99.619570% | 92/92 instructions | capacity-sum operand registers only (5 differences)
QDecode | 94.130135% | 146/146 instructions | input cursor lifetime/update addressing, decode-bound branch direction and saved registers (59 differences)
DecodeWord | 97.694440% | 180/180 instructions | saved-register allocation only (67 differences)
NWC24DecodeMIMEHeaderFieldBody | 99.456520% | 92/92 instructions | working input/output saved registers swapped (8 differences)
ExtractCharset | 97.261900% | 84/84 instructions | saved-register allocation only (35 differences)
ExtractEncodedText | 98.148150% | 135/135 instructions | saved-register allocation only (44 differences)
NWC24ReadMsgSubjectPublic | 96.153850% | 100/104 instructions | four missing status-dispatch branches
NWC24ReadMsgTextPublic | 97.142860% | 68/70 instructions | two missing status-dispatch branches
NWC24SetMsgSubjectAndTextPublic | 98.236840% | 190/190 instructions | saved-register allocation only (65 differences)
NWC24iSetMsgSubjectQP | 99.548615% | 144/144 instructions | source-offset/output-buffer saved registers only (12 differences)
NWC24iSetMsgSubjectBase64 | 93.455880% | 139/136 instructions | two extra switch-dispatch branches, initial stack-store lifetime and loop arithmetic scheduling; three extra instructions
NWC24ReadMsgField | 98.921570% | 101/102 instructions | one missing mailbox-type reload after protection validation
NWC24ReadMsgFromAddr | 98.804344% | 91/92 instructions | one missing mailbox-type reload after supported-type validation
NWC24ReadMsgSubject | 98.658540% | 81/82 instructions | one missing mailbox-type reload after protection validation
ReadMsgTextInternal | 93.735954% | 176/178 instructions | type/encoding initialization, status branches and close-result precedence; two instructions missing
NWC24ReadMsgAttached | 96.373630% | 90/91 instructions | one missing type reload plus decoded-size error branch/address ordering

## Data and uncertainty

All owned .data/.rodata/.sdata/.sdata2/.ctors sections are exact in the six units other than MsgCommit. Keyboard source and shared headers are unchanged. Every existing keyboard guard side is intact.

MsgCommit remains 72/904 exact data bytes. Raw ELF sections: .data 678/680 bytes, .sdata 140/152, .sbss 4/8 (objdiff treats .sbss as 100%). The 24 ordinary .data literals have the same offsets; the target section includes two additional trailing bytes and different symbol grouping. The .sdata differences include spacing after LoopBackEnable, a separately emitted CRLF, and trailing alignment. The gate pool extractor ignores short/control-only strings, so its IDENTICAL result does not prove these CRLF sections identical. Declaration-order and literal-ownership trials were reverted after no data improvement. No padding, storage-size changes, packed string blobs or address shims were added. The original source forms behind the spacing and duplicate literal remain unresolved.

Compiler allocation remains unresolved where register-normalized streams agree. Purge iterator-initialization status branches and public subject/text status-dispatch branches remain uncertain; no known-false or unreachable dummy branches were inserted.

## Attempts and assembly evidence

Successful new body variants only. Failed builds, non-equivalent move ancestry trials 1/3, data-only trials, and source bodies already tested in round 2 are excluded. Saved sources were compared with whitespace normalized. Every one of the 40 initially open functions has at least three new distinct attempts; no initially open function was skipped.

onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 3 distinct successful new source bodies
create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 5 distinct successful new source bodies
init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3 distinct successful new source bodies
QDecode | 3 distinct successful new source bodies
EncodeWord | 10 distinct successful new source bodies
CopyWithoutLinearWhiteSpaces | 3 distinct successful new source bodies
DecodeWord | 6 distinct successful new source bodies
NWC24DecodeMIMEHeaderFieldBody | 9 distinct successful new source bodies
ExtractCharset | 9 distinct successful new source bodies
ExtractEncodedText | 7 distinct successful new source bodies
NWC24CommitMsgInternal | 3 distinct successful new source bodies
CheckMsgBoxSpace | 3 distinct successful new source bodies
WriteMIMEAttachHeader | 3 distinct successful new source bodies
NWC24ReadMsgField | 3 distinct successful new source bodies
NWC24ReadMsgFromAddr | 3 distinct successful new source bodies
NWC24ReadMsgSubject | 3 distinct successful new source bodies
ReadMsgTextInternal | 3 distinct successful new source bodies
NWC24ReadMsgAttached | 3 distinct successful new source bodies
NWC24ReadMsgSubjectPublic | 6 distinct successful new source bodies
NWC24ReadMsgTextPublic | 6 distinct successful new source bodies
NWC24SetMsgSubjectAndTextPublic | 3 distinct successful new source bodies
NWC24iSetMsgSubjectQP | 3 distinct successful new source bodies
NWC24iSetMsgSubjectBase64 | 6 distinct successful new source bodies
NWC24InitDlTask | 3 distinct successful new source bodies
NWC24SetDlInterval | 4 distinct successful new source bodies
NWC24IterateDlTask | 3 distinct successful new source bodies
NWC24IterateDlTaskEx | 3 distinct successful new source bodies
NWC24UpdateDlTask | 3 distinct successful new source bodies
NWC24AddDlTask | 3 distinct successful new source bodies
NWC24GetDlTask | 4 distinct successful new source bodies
NWC24PurgeOldestDlTask | 3 distinct successful new source bodies
NWC24ManageDlTaskListForMenu | 3 distinct successful new source bodies
NWC24ExtendDlTaskList | 4 distinct successful new source bodies
NWC24iCheckDlHeaderConsistency | 4 distinct successful new source bodies
NWC24iCreateDlTaskList | 4 distinct successful new source bodies
AddTaskInternal | 3 distinct successful new source bodies
PFDIR_GetSDD | 3 distinct successful new source bodies
PFDIR_p_mkdir | 3 distinct successful new source bodies
PFDIR_p_rename | 3 distinct successful new source bodies
PFDIR_p_move | 5 distinct successful new source bodies

The attempt log records each source change, resulting objdiff percentage, instruction counts and positional differences. Data trials are logged separately.

For instruction-count differences, target control-flow comparisons cover: Download iterator entry/increment; update retry checks; add time validation; purge initialization and candidate removal; menu removal status; AddTaskInternal URL and slot/purge/update stages; pf_dir ancestry and rollback; public subject/text status dispatch; Base64 conversion/encoding and CRLF folding; mailbox selection/type reloads, text decoding and close-result precedence. The final per-function ctxdiff and register-normalized differences were reread after the full clean build. Equal instruction counts do not imply an exact function. MIME construction and decoding were rederived through marker/append helper blocks; remaining MIME search/DecodeWord/header streams agree after register normalization.

The Matching pf_dir sibling at libs/RevoEX/src/vf/fatfs/pf_dir.c was diffed against the owned unit again. Its source remains unchanged.

## Files and commits

Changed source: libs/RVL_SDK/src/fa/pf_dir.c; libs/RevoEX/src/nwc24/NWC24Download.c; libs/RevoEX/src/nwc24/NWC24Mime.c; libs/RevoEX/src/nwc24/NWC24MsgCommit.c; libs/RevoEX/src/nwc24/NWC24MsgRead.c; libs/RevoEX/src/nwc24/NWC24MsgSubject.c.

Changed evidence: tools/decomp-assist/sol-high-round3-attempts.md; tools/decomp-assist/sol-high-round3-report.md.

3746c42d refine download and directory control flow
c1f5e02f match mime whitespace copying and refine message handling
632d1ebf match mime encoded word construction
e26ea8f1 rederive mime decoding and marker searches

Every source commit followed a passing gate with zero regressions, forbidden additions and readability warnings. Final non-quick gate rebuilt all seven units together and the complete 43U build; expected DOL SHA1 remained 26116613f624061ba99c8d1a299aaa6efa85670d. No link investigation, upstream interaction or unit status changes were performed.

## Every gate block

### sol-high-round3-before-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1469 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.14693
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3640/12496 data 80 functions 17 fuzzy 97.1469
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 12824/19028 data 3860 functions 83 fuzzy 99.7740
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.2629 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.262856
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 40 functions 34 fuzzy 99.2629
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.71820
global fuzzy_match_percent: 97.60807 -> 97.60807
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-priority-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.2494 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.24936
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 98.034485
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 96.74342
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3640/12496 data 80 functions 17 fuzzy 97.1469
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 12824/19028 data 3860 functions 83 fuzzy 99.7740
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.3324 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.33242
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 98.336
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 40 functions 34 fuzzy 99.2629
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.71820
global fuzzy_match_percent: 97.60807 -> 97.60895
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-priority-improved-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.2494 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.24936
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 98.034485
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 96.74342
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3640/12496 data 80 functions 17 fuzzy 97.1469
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 12824/19028 data 3860 functions 83 fuzzy 99.7740
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.5369 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.53689
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 98.336
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 98.5103
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 40 functions 34 fuzzy 99.2629
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.71820
global fuzzy_match_percent: 97.60807 -> 97.61025
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-mime-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgCommit] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgCommit] objdiff: code 3964/8532 data 72/904 functions 15/18 fuzzy 98.4426 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgCommit] instruction-exact functions: 15/18
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .bss size 64 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .data size 680 match None
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sdata size 152 match 18.765432
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .text size 8532 match 98.442566
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: NWC24CommitMsgInternal 99.91536
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: CheckMsgBoxSpace 85.57399
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: WriteMIMEAttachHeader 99.61957
[libs/RevoEX/src/nwc24/NWC24MsgCommit] baseline: code 3964/8532 data 72 functions 15 fuzzy 98.4332
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 2784/6124 data 88/88 functions 10/16 fuzzy 92.0150 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 10/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 92.01502
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: QDecode 94.130135
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: EncodeWord 71.681816
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 79.66111
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: NWC24DecodeMIMEHeaderFieldBody 92.5
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 92.38095
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 94.296295
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 2492/6124 data 88 functions 9 fuzzy 90.2436
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.72794
global fuzzy_match_percent: 97.60807 -> 97.61391
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-extras-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgCommit] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgCommit] objdiff: code 3964/8532 data 72/904 functions 15/18 fuzzy 98.4426 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgCommit] instruction-exact functions: 15/18
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .bss size 64 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .data size 680 match None
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sdata size 152 match 18.765432
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .text size 8532 match 98.442566
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: NWC24CommitMsgInternal 99.91536
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: CheckMsgBoxSpace 85.57399
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: WriteMIMEAttachHeader 99.61957
[libs/RevoEX/src/nwc24/NWC24MsgCommit] baseline: code 3964/8532 data 72 functions 15 fuzzy 98.4332
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 2784/6124 data 88/88 functions 10/16 fuzzy 92.0150 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 10/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 92.01502
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: QDecode 94.130135
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: EncodeWord 71.681816
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 79.66111
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: NWC24DecodeMIMEHeaderFieldBody 92.5
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 92.38095
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 94.296295
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 2492/6124 data 88 functions 9 fuzzy 90.2436
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 2776/5352 data 232/232 functions 7/12 fuzzy 98.5874 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 7/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 98.58744
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectQP 99.548615
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 93.45588
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 2776/5352 data 232 functions 7 fuzzy 97.4178
[libs/RevoEX/src/nwc24/NWC24MsgRead] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 2480/4660 data 128/128 functions 11/16 fuzzy 98.4764 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .data size 128 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .text size 4660 match 98.476395
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgField 98.92157
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgFromAddr 98.804344
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgSubject 98.65854
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: ReadMsgTextInternal 93.735954
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgAttached 96.37363
[libs/RevoEX/src/nwc24/NWC24MsgRead] baseline: code 2480/4660 data 128 functions 11 fuzzy 98.4506
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.72794
global fuzzy_match_percent: 97.60807 -> 97.61602
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-encode-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 3576/6124 data 88/88 functions 11/16 fuzzy 95.6773 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 95.67734
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: QDecode 94.130135
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 79.66111
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: NWC24DecodeMIMEHeaderFieldBody 92.5
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 92.38095
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 94.296295
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 2492/6124 data 88 functions 9 fuzzy 90.2436
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.75439
global fuzzy_match_percent: 97.60807 -> 97.62350
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-decode-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 3576/6124 data 88/88 functions 11/16 fuzzy 98.8230 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 98.82299
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: QDecode 94.130135
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 97.69444
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: NWC24DecodeMIMEHeaderFieldBody 99.45652
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 97.2619
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 98.14815
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 2492/6124 data 88 functions 9 fuzzy 90.2436
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.75439
global fuzzy_match_percent: 97.60807 -> 97.62993
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round3-final-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.2494 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.24936
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 98.034485
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 96.74342
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3640/12496 data 80 functions 17 fuzzy 97.1469
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 12824/19028 data 3860 functions 83 fuzzy 99.7740
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.5369 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.53689
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 98.336
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 98.5103
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 40 functions 34 fuzzy 99.2629
[libs/RevoEX/src/nwc24/NWC24MsgCommit] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgCommit] objdiff: code 3964/8532 data 72/904 functions 15/18 fuzzy 98.4426 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgCommit] instruction-exact functions: 15/18
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .bss size 64 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .data size 680 match None
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .sdata size 152 match 18.765432
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   section .text size 8532 match 98.442566
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: NWC24CommitMsgInternal 99.91536
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: CheckMsgBoxSpace 85.57399
[libs/RevoEX/src/nwc24/NWC24MsgCommit]   below 100: WriteMIMEAttachHeader 99.61957
[libs/RevoEX/src/nwc24/NWC24MsgCommit] baseline: code 3964/8532 data 72 functions 15 fuzzy 98.4332
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 3576/6124 data 88/88 functions 11/16 fuzzy 98.8230 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 98.82299
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: QDecode 94.130135
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 97.69444
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: NWC24DecodeMIMEHeaderFieldBody 99.45652
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 97.2619
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 98.14815
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 2492/6124 data 88 functions 9 fuzzy 90.2436
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 2776/5352 data 232/232 functions 7/12 fuzzy 98.5874 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 7/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 98.58744
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectQP 99.548615
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 93.45588
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 2776/5352 data 232 functions 7 fuzzy 97.4178
[libs/RevoEX/src/nwc24/NWC24MsgRead] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 2480/4660 data 128/128 functions 11/16 fuzzy 98.4764 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .data size 128 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .text size 4660 match 98.476395
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgField 98.92157
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgFromAddr 98.804344
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgSubject 98.65854
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: ReadMsgTextInternal 93.735954
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgAttached 96.37363
[libs/RevoEX/src/nwc24/NWC24MsgRead] baseline: code 2480/4660 data 128 functions 11 fuzzy 98.4506
regressions vs baseline: 0
global matched_code_percent: 83.71820 -> 83.75439
global fuzzy_match_percent: 97.60807 -> 97.62993
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

