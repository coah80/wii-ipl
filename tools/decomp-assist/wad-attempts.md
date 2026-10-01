# WAD matching attempts, round 2

Baseline: merged main f1590c83, 27/40 instruction-exact, code 8392/24500, data 64/528.

| Function | Target bytes | Objdiff before -> after | Source/target instructions | Positional nonregister differences |
| --- | ---: | --- | --- | ---: |
| WADImportGetBlocks | 1192 | 94.24161 -> 94.22147 | 286/298 | 260 |
| WAD_815BFFA8 | 248 | 97.17742 -> 99.35484 | 62/62 | 0 |
| WADImportEx | 4584 | 79.80366 -> 91.91536 | 1157/1146 | 1045 |
| WAD_815C1288 | 244 | 96.39344 -> 96.39344 | 61/61 | 0 |
| WADBackupEx | 4248 | 82.28342 -> 93.37382 | 1044/1062 | 994 |
| WADOpenStream | 812 | 98.89162 -> 99.50739 | 202/203 | 47 |
| _WADUnpackBackup | 452 | 97.34513 -> 99.02655 | 114/113 | 73 |
| _WADBackupGetFiles | 1268 | 97.19243 -> 100.00000 | 317/317 | 0 |
| _WADBackupGetSize | 620 | 99.90323 -> 99.90323 | 155/155 | 0 |
| _WADRandPad | 364 | 93.78022 -> 100.00000 | 91/91 | 0 |
| WAD_815C43E0 | 248 | 97.17742 -> 99.35484 | 62/62 | 0 |
| _WADHash | 776 | 98.53093 -> 98.55670 | 194/194 | 0 |
| WADImportDVDExForBS | 1052 | 96.04562 -> 96.17871 | 260/263 | 233 |

String pools: identical, 18 entries. All 458 emitted .data bytes equal the target prefix; the target section has six trailing zero bytes. Both sections have alignment 8. .sdata is identical at 64 bytes. No padding or forced data placement added.

Repeated null-validation branches were translated directly from target assembly: files 815C3B08/815C3B14; backup 815C1504/815C1514, 815C162C/815C163C, 815C170C/815C171C, 815C1868/815C1878, 815C1A48/815C1A58, 815C1A84/815C1A94.

Positional difference counts include shifted instructions. Five remaining functions have equal instruction counts and zero nonregister differences. Seven instruction-count discrepancies were investigated; _WADRandPad is now exact after recomputing its byte-source view inside the tail loop. Six functions still differ beyond registers. Every initially open function has at least three fresh distinct logged attempts.

Positional difference counts include shifted instructions. Five remaining functions have equal instruction counts and zero nonregister differences. Seven instruction-count discrepancies were investigated; _WADRandPad is now exact after recomputing its byte-source view inside the tail loop. Six functions still differ beyond registers. Every initially open function has at least three fresh distinct logged attempts.

Positional difference counts include shifted instructions. Five remaining functions have equal instruction counts and zero nonregister differences. Seven instruction-count discrepancies were investigated; _WADRandPad is now exact after recomputing its byte-source view inside the tail loop. Six functions still differ beyond registers. Every initially open function has at least three fresh distinct logged attempts.

Attempts:
```text
_WADBackupGetSize: r2 final backup size has its own lifetime rather than updating metadata header size; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
r2 baseline: 27/40 exact, code 8392/24500, data 64/528, fuzzy 92.233955; merged source clean. Data audit pending; remaining function attempts start fresh.
_WADBackupGetSize: r2 lifetime: declare file byte count after selected content count; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 2, 0); objdiff 99.90323; retained True
_WADBackupGetSize: r2 write total through the output expression without overwriting header size; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 10, 9); objdiff 97.3871; retained False
_WADUnpackBackup: r2 retranslate success reset before metadata load and move shared success to entry; insns/diffs/nonregister (113, 113, 12, 4) -> (114, 113, 78, 73); objdiff 99.02655; retained True
WADOpenStream: r2 translate NAND-read success as switch break; reverse extent and SD seek operand order; insns/diffs/nonregister (203, 203, 30, 28) -> (204, 203, 51, 48); objdiff 98.349754; retained False
WADOpenStream: r2 translate nested SD seek failure with explicit seek result; insns/diffs/nonregister (203, 203, 30, 28) -> (203, 203, 30, 28); objdiff 98.891624; retained True
WADOpenStream: r2 translate NAND cases into structured write/read switch branches; compilation failed; restored
_WADUnpackBackup: r2 assign success once after either metadata branch; no early extra reset; insns/diffs/nonregister (114, 113, 78, 73) -> (113, 113, 12, 4); objdiff 97.34513; retained False
_WADUnpackBackup: r2 load metadata size before header alignment into its longer-lived temporary; insns/diffs/nonregister (114, 113, 78, 73) -> (114, 113, 78, 73); objdiff 99.02655; retained True
_WADUnpackBackup: r2 reset success in metadata-read and skip-read branches with no extra prologue instruction; insns/diffs/nonregister (114, 113, 78, 73) -> (115, 113, 54, 45); objdiff 97.831856; retained False
_WADUnpackBackup: r2 original branch direction: skip read before metadata allocation arm; insns/diffs/nonregister (114, 113, 78, 73) -> (115, 113, 75, 67); objdiff 97.30089; retained False
_WADRandPad: r2 do not hold the tail source address across random calls; insns/diffs/nonregister (89, 91, 52, 35) -> (89, 91, 26, 25); objdiff 94.60439; retained True
_WADRandPad: r2 index the random source bytes with the copied-byte counter; insns/diffs/nonregister (89, 91, 26, 25) -> (84, 91, 80, 80); objdiff 75.48351; retained False
_WADRandPad: r2 one byte cursor for word output and remaining tail; insns/diffs/nonregister (89, 91, 26, 25) -> (89, 91, 26, 25); objdiff 94.60439; retained True
data audit .data: source 458, target 464, overlapping differences 0, target remainder 000000000000
data audit .sdata: source 64, target 64, overlapping differences 0, target remainder 
_WADRandPad: r2 inline copy helper caused original function to disappear through automatic inlining; restored immediately; candidate rejected.
WADImportEx: r2 stack/prologue: result declaration and zero initialization before all ownership locals; insns/diffs/nonregister (1155, 1146, 1130, 1105) -> (1155, 1146, 1121, 1096); objdiff 79.70506; retained False
WADImportEx: r2 stack/prologue: parsed metadata local before progress and owned allocations; insns/diffs/nonregister (1155, 1146, 1130, 1105) -> (1155, 1146, 1130, 1105); objdiff 79.803665; retained True
WADImportEx: r2 opening block: reuse boot size for initial header read length as target r25; insns/diffs/nonregister (1155, 1146, 1130, 1105) -> (1156, 1146, 1129, 1101); objdiff 79.373474; retained False
WADImportEx: unlock current mutex on transfer failure; recompute aligned read comparison; insns/diffs/nonregister (1155, 1146, 1130, 1105) -> (1160, 1146, 1126, 1104); objdiff 80.374344; retained True
WADImportEx: unconditional join after successful create; return failed join immediately; insns/diffs/nonregister (1160, 1146, 1126, 1104) -> (1155, 1146, 1126, 1100); objdiff 80.92234; retained True
WADImportEx: remove transfer reset and postjoin error test absent from target; insns/diffs/nonregister (1155, 1146, 1126, 1100) -> (1150, 1146, 1126, 1095); objdiff 81.25305; retained True
_WADBackupGetSize: sum title and content through local before files-first final addition; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
WAD_815BFFA8: move result initialization after transfer pointer load; insns/diffs/nonregister (62, 62, 30, 0) -> (62, 62, 36, 0); objdiff 96.29032; retained False
WAD_815BFFA8: use direct mutex expressions across wait and unlock; insns/diffs/nonregister (62, 62, 30, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained True
WAD_815BFFA8: make transfer loop a for loop with index advance; insns/diffs/nonregister (62, 62, 19, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained True
WAD_815C1288: move result initialization after transfer pointer load; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WAD_815C1288: use direct mutex expressions across wait and unlock; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: make transfer loop a for loop with index advance; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WAD_815C43E0: move result initialization after transfer pointer load; insns/diffs/nonregister (62, 62, 30, 0) -> (62, 62, 36, 0); objdiff 96.29032; retained False
WAD_815C43E0: use direct mutex expressions across wait and unlock; insns/diffs/nonregister (62, 62, 30, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained True
WAD_815C43E0: make transfer loop a for loop with index advance; insns/diffs/nonregister (62, 62, 19, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained True
WAD_815BFFA8: declare chunk size with loop state; assign at each iteration; insns/diffs/nonregister (62, 62, 19, 0) -> (62, 62, 14, 0); objdiff 98.79032; retained True
WAD_815BFFA8: declare transfer pointer before index but initialize in target order; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815C1288: declare chunk size with loop state; assign at each iteration; compilation failed; restored
WAD_815C1288: declare transfer pointer before index but initialize in target order; compilation failed; restored
WAD_815C43E0: declare chunk size with loop state; assign at each iteration; insns/diffs/nonregister (62, 62, 19, 0) -> (62, 62, 14, 0); objdiff 98.79032; retained True
WAD_815C43E0: declare transfer pointer before index but initialize in target order; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815BFFA8: declare chunk after transfer state; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815BFFA8: declare chunk before result but load input state first; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 17, 0); objdiff 98.30645; retained False
WAD_815BFFA8: assign transfer before zero index initialization; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815C43E0: declare chunk after transfer state; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815C43E0: declare chunk before result but load input state first; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 17, 0); objdiff 98.30645; retained False
WAD_815C43E0: assign transfer before zero index initialization; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 19, 0); objdiff 98.30645; retained False
WAD_815C1288: loop chunk declaration before its assignment; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WAD_815C1288: direct mutex use with outer chunk local; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
_WADBackupGetFiles: translate allocation status before validating the name-list pointer; insns/diffs/nonregister (314, 317, 266, 257) -> (321, 317, 274, 265); objdiff 96.8265; retained False
_WADBackupGetFiles: allocation failure flows to shared status test before directory read; insns/diffs/nonregister (314, 317, 266, 257) -> (315, 317, 272, 264); objdiff 97.28706; retained True
_WADBackupGetFiles: load output iterator immediately before traversal; insns/diffs/nonregister (315, 317, 272, 264) -> (315, 317, 272, 264); objdiff 96.6877; retained False
_WADHash: keep read status in the result local before length comparison; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 44, 0); objdiff 98.5567; retained True
_WADHash: declare completed count before read pointer; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 44, 0); objdiff 98.5567; retained True
_WADHash: declare chunk length inside each transfer arm; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 62, 0); objdiff 97.78351; retained False
WADImportEx: reset status after argument validation as in target opening block; insns/diffs/nonregister (1150, 1146, 1126, 1095) -> (1152, 1146, 1123, 1095); objdiff 81.24869; retained False
WADImportEx: load parsed metadata before setting progress cursor; insns/diffs/nonregister (1150, 1146, 1126, 1095) -> (1150, 1146, 1126, 1095); objdiff 81.25305; retained True
WADImportEx: reuse aligned boot length expression after stream read; insns/diffs/nonregister (1150, 1146, 1126, 1095) -> (1152, 1146, 1123, 1094); objdiff 81.53054; retained True
WADBackupEx: retranslate stack: reverse declaration order; NAND file has natural alignment; insns/diffs/nonregister (996, 1062, 970, 950) -> (996, 1062, 968, 948); objdiff 82.33804; retained True
WADBackupEx: retranslate content listing: reset status after only missing-title error; insns/diffs/nonregister (996, 1062, 968, 948) -> (995, 1062, 975, 953); objdiff 82.43126; retained True
WADBackupEx: retranslate metadata view: reset status after selecting allocated view; insns/diffs/nonregister (995, 1062, 975, 953) -> (997, 1062, 971, 949); objdiff 83.12429; retained True
WADImportGetBlocks: load file-header pointer once at traversal entry; insns/diffs/nonregister (286, 298, 274, 259) -> (284, 298, 271, 251); objdiff 93.067116; retained False
WADImportGetBlocks: give file-list entry a pointer during field population; insns/diffs/nonregister (286, 298, 274, 259) -> (272, 298, 260, 246); objdiff 88.06376; retained False
WADImportGetBlocks: load parsed metadata before clearing block counters; insns/diffs/nonregister (286, 298, 274, 259) -> (286, 298, 274, 260); objdiff 93.58725; retained False
WADImportDVDExForBS: load title metadata after ticket import into a narrower block lifetime; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.00761; retained False
WADImportDVDExForBS: declare section cursor before content pointer; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.08365; retained True
WADImportDVDExForBS: express chunk minimum with target compare branch direction; insns/diffs/nonregister (260, 263, 243, 233) -> (259, 263, 238, 224); objdiff 95.39924; retained False
WADImportEx: correct stream type natural size; keep local/member alignment; (1152, 1146, 1123, 1094); objdiff 81.53054
WADBackupEx: correct stream type natural size; keep local/member alignment; (997, 1062, 971, 949); objdiff 83.12429
WADImportGetBlocks: correct stream type natural size; keep local/member alignment; (286, 298, 275, 260); objdiff 94.22147
WADImportEx: align enclosing frame while stream local keeps natural extent; insns/diffs/nonregister (1152, 1146, 1123, 1094) -> (1152, 1146, 1123, 1094); objdiff 81.53839; retained True
WADBackupEx: align enclosing frame while stream local keeps natural extent; insns/diffs/nonregister (997, 1062, 971, 949) -> (997, 1062, 970, 948); objdiff 83.13936; retained True
WADImportEx: initialize status immediately after report name; insns/diffs/nonregister (1152, 1146, 1123, 1094) -> (1152, 1146, 1113, 1084); objdiff 82.50175; retained True
WADImportEx: declare metadata after owned buffers to shorten allocation pressure; insns/diffs/nonregister (1152, 1146, 1113, 1084) -> (1152, 1146, 1113, 1084); objdiff 82.50175; retained True
WADImportEx: defer status initialization until all frame and ownership declarations; insns/diffs/nonregister (1152, 1146, 1113, 1084) -> (1152, 1146, 1121, 1092); objdiff 81.363; retained False
_WADBackupGetSize: use signed header accumulator before total-size output; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 2, 0); objdiff 99.90323; retained True
_WADBackupGetSize: compute file-inclusive size before updating metadata accumulator; insns/diffs/nonregister (155, 155, 2, 0) -> (158, 155, 18, 14); objdiff 96.67742; retained False
_WADBackupGetSize: preserve header-plus-content subtotal through content output; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 6, 4); objdiff 98.645164; retained False
WADBackupEx: form certificate addresses from their struct fields and align each API buffer; insns/diffs/nonregister (997, 1062, 970, 948) -> (999, 1062, 973, 952); objdiff 83.17609; retained True
WADBackupEx: retranslate writes: validate byte count then set successful status; insns/diffs/nonregister (999, 1062, 973, 952) -> (1003, 1062, 979, 959); objdiff 85.32957; retained True
WADBackupEx: retranslate closing size checks: failed seek is backup write error; clear status before digest; insns/diffs/nonregister (1003, 1062, 979, 959) -> (1006, 1062, 985, 965); objdiff 85.70904; retained True
_WADBackupGetSize: single left-associated total expression; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
_WADBackupGetSize: single sum with file total as first operand; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
WADOpenStream: nested SD offset and seek-status branches with explicit result; write extent compare order; insns/diffs/nonregister (203, 203, 30, 28) -> (203, 203, 30, 28); objdiff 98.94089; retained True
WADOpenStream: structured NAND write/read arms without goto label; insns/diffs/nonregister (203, 203, 30, 28) -> (203, 203, 30, 28); objdiff 98.94089; retained True
WADOpenStream: NAND write arm returns before independent read path; insns/diffs/nonregister (203, 203, 30, 28) -> (203, 203, 30, 28); objdiff 98.94089; retained True
WADOpenStream: SD seek guards write arm directly with short-circuit test; insns/diffs/nonregister (203, 203, 30, 28) -> (203, 203, 30, 28); objdiff 98.891624; retained False
WADOpenStream: NAND read status mapped to return expression; insns/diffs/nonregister (203, 203, 30, 28) -> (202, 203, 48, 47); objdiff 99.45813; retained True
WADOpenStream: join successful seek with common SD handle validation; insns/diffs/nonregister (202, 203, 48, 47) -> (202, 203, 48, 47); objdiff 99.45813; retained True
WADOpenStream: seek success branches directly to handle validation; failure has explicit else; insns/diffs/nonregister (202, 203, 48, 47) -> (202, 203, 48, 47); objdiff 99.45813; retained True
WADOpenStream: validate NAND write count through explicit status local; insns/diffs/nonregister (202, 203, 48, 47) -> (202, 203, 47, 47); objdiff 99.50739; retained True
WADOpenStream: SD write arm returns validated handle; read arm shares validation expression; insns/diffs/nonregister (202, 203, 47, 47) -> (213, 203, 49, 49); objdiff 92.38916; retained False
WADOpenStream: map SD seek byte offset to an error status before shared handle check; insns/diffs/nonregister (202, 203, 47, 47) -> (206, 203, 48, 48); objdiff 98.44827; retained False
_WADBackupGetFiles: translate both allocation-result validation branches present at 815C3B08 and 815C3B14; insns/diffs/nonregister (315, 317, 272, 264) -> (317, 317, 41, 11); objdiff 98.1388; retained True
_WADBackupGetFiles: advance traversal index before name-length call and cleanup; insns/diffs/nonregister (317, 317, 41, 11) -> (317, 317, 36, 3); objdiff 98.73817; retained True
_WADBackupGetFiles: initialize recursive count before selecting child output pointer; insns/diffs/nonregister (317, 317, 36, 3) -> (317, 317, 33, 0); objdiff 99.38486; retained True
WADBackupEx: translate the six repeated allocation checks and success resets visible in target blocks; insns/diffs/nonregister (1006, 1062, 985, 965) -> (1038, 1062, 1018, 997); objdiff 88.28719; retained True
WADBackupEx: reset status before path-size query and progress callback; insns/diffs/nonregister (1038, 1062, 1018, 997) -> (1038, 1062, 1017, 997); objdiff 88.75612; retained True
_WADBackupGetFiles: declare total file count before output iterator; insns/diffs/nonregister (317, 317, 33, 0) -> (317, 317, 30, 0); objdiff 99.46372; retained True
_WADBackupGetFiles: declare name cursor after loop index state; insns/diffs/nonregister (317, 317, 30, 0) -> (317, 317, 19, 0); objdiff 99.63722; retained True
_WADBackupGetFiles: use signed directory traversal index like NAND count comparisons; insns/diffs/nonregister (317, 317, 19, 0) -> (317, 317, 19, 0); objdiff 99.63722; retained True
WADBackupEx: separate TMD view length from exported TMD length; correct output-size stack declaration order; insns/diffs/nonregister (1038, 1062, 1017, 997) -> (1038, 1062, 1013, 986); objdiff 88.859695; retained True
WADBackupEx: translate empty file list branch with explicit null output owner; insns/diffs/nonregister (1038, 1062, 1013, 986) -> (1041, 1062, 1002, 969); objdiff 89.0951; retained True
WADBackupEx: initialize owned buffers and size outputs in target prologue order after declarations; insns/diffs/nonregister (1041, 1062, 1002, 969) -> (1042, 1062, 967, 931); objdiff 88.86441; retained False
WADImportEx: align the 32-bit content length rather than the 64-bit metadata member; insns/diffs/nonregister (1152, 1146, 1113, 1084) -> (1142, 1146, 1113, 1089); objdiff 82.56806; retained True
WADBackupEx: align the 32-bit content length rather than the 64-bit metadata member; insns/diffs/nonregister (1041, 1062, 1002, 969) -> (1039, 1062, 1011, 985); objdiff 89.391716; retained True
WADBackupEx: use export consumer condition queues from target wait and signal blocks; insns/diffs/nonregister (1039, 1062, 1011, 985) -> (1039, 1062, 1011, 985); objdiff 89.3936; retained True
WADBackupEx: keep export stream write count in joined-thread status slot as target does; insns/diffs/nonregister (1039, 1062, 1011, 985) -> (1040, 1062, 1015, 987); objdiff 89.49247; retained True
_WADBackupGetFiles: declare output iterator before directory owner and file count; insns/diffs/nonregister (317, 317, 19, 0) -> (317, 317, 0, 0); objdiff 100.0; retained True
_WADBackupGetFiles: initialize directory owner and counter before optional output iterator; insns/diffs/nonregister (317, 317, 0, 0) -> (317, 317, 4, 0); objdiff 99.936905; retained False
_WADRandPad: copy remaining random bytes with standard memcpy; insns/diffs/nonregister (89, 91, 26, 25) -> (52, 91, 22, 14); objdiff 52.307693; retained False
_WADRandPad: index source and destination bytes from their original cursors; insns/diffs/nonregister (89, 91, 26, 25) -> (85, 91, 82, 80); objdiff 68.73627; retained False
_WADRandPad: use immutable source pointer with an indexed read and advancing destination; insns/diffs/nonregister (89, 91, 26, 25) -> (84, 91, 80, 80); objdiff 75.48351; retained False
WADImportEx: declare report-name pointer after transfer state to reduce its register priority; insns/diffs/nonregister (1142, 1146, 1113, 1089) -> (1142, 1146, 1113, 1089); objdiff 82.56806; retained True
WADImportEx: place metadata pointer after all owner declarations; insns/diffs/nonregister (1142, 1146, 1113, 1089) -> (1142, 1146, 1113, 1089); objdiff 82.56806; retained True
WADImportEx: keep progress cursor declaration before status state; insns/diffs/nonregister (1142, 1146, 1113, 1089) -> (1141, 1146, 1053, 1013); objdiff 83.095116; retained True
WAD_815BFFA8: declare transfer, index, then chunk in register-lifetime order; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815C43E0: declare transfer, index, then chunk in register-lifetime order; insns/diffs/nonregister (62, 62, 14, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WADImportEx: choose transfer chunk in target greater-than branch order; insns/diffs/nonregister (1141, 1146, 1053, 1013) -> (1141, 1146, 1053, 1013); objdiff 83.25131; retained True
WADBackupEx: choose transfer chunk in target greater-than branch order; insns/diffs/nonregister (1040, 1062, 1015, 987) -> (1040, 1062, 1015, 987); objdiff 89.69021; retained True
WADBackupEx: clear successful file-read status before encryption API block; insns/diffs/nonregister (1040, 1062, 1015, 987) -> (1043, 1062, 1012, 985); objdiff 90.01224; retained True
WAD_815BFFA8: name ready and failure status constants before the chunk local; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815C43E0: name ready and failure status constants before the chunk local; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WADOpenStream: join SD handle validation with a labelled seek failure block; insns/diffs/nonregister (202, 203, 47, 47) -> (202, 203, 47, 47); objdiff 99.50739; retained True
WADBackupEx: declare size outputs before ownership locals to match target zero stores; insns/diffs/nonregister (1043, 1062, 1012, 985) -> (1044, 1062, 972, 933); objdiff 89.77683; retained False
WADBackupEx: free file descriptors before export thread stack in target cleanup order; insns/diffs/nonregister (1043, 1062, 1012, 985) -> (1043, 1062, 1012, 985); objdiff 90.01224; retained True
WADBackupEx: guard final backup-size output pointer as target does; insns/diffs/nonregister (1043, 1062, 1012, 985) -> (1046, 1062, 1009, 983); objdiff 90.33616; retained True
WADBackupEx: limit saved-file closing to file_done; target cleanup has no second NANDClose; insns/diffs/nonregister (1046, 1062, 1009, 983) -> (1031, 1062, 1001, 978); objdiff 89.44633; retained False
WADBackupEx: retranslate signature seek and fixed-size writes with target signed status comparisons; insns/diffs/nonregister (1046, 1062, 1009, 983) -> (1046, 1062, 1008, 982); objdiff 91.4162; retained True
WADBackupEx: retain target-faithful cleanup without second NANDClose despite lower fuzzy score; original cleanup 815C232C-815C23F4 has no NANDClose; (1031, 1062, 1001, 978); objdiff 90.23258
WADBackupEx: keep file-header pointer across file export calls as in target loop; insns/diffs/nonregister (1031, 1062, 1001, 978) -> (1033, 1062, 1010, 989); objdiff 91.35123; retained True
WADImportEx: initialize parsed metadata pointer to null in the target prologue; insns/diffs/nonregister (1141, 1146, 1053, 1013) -> (1141, 1146, 1053, 1013); objdiff 83.25131; retained True
WADImportEx: initialize metadata pointer before ownership and progress state; insns/diffs/nonregister (1141, 1146, 1053, 1013) -> (1144, 1146, 1118, 1097); objdiff 82.42583; retained False
WADImportEx: defer content descriptor assignment until content import begins; cancellation is guarded; insns/diffs/nonregister (1141, 1146, 1053, 1013) -> (1139, 1146, 1083, 1045); objdiff 83.356895; retained True
WADImportEx: reset import status after validation before initial progress callback; insns/diffs/nonregister (1139, 1146, 1083, 1045) -> (1141, 1146, 1038, 992); objdiff 83.35253; retained False
_WADRandPad: inline byte copier with indexed source; move existing non-inlining boundary past real padding function to preserve it; (52, 91, 22, 14); objdiff 52.307693
_WADRandPad: helper candidate rejected; not instruction-exact or registers-only
_WADRandPad: form indexed byte view through the SDK 32-bit address representation; insns/diffs/nonregister (89, 91, 26, 25) -> (84, 91, 80, 80); objdiff 75.48351; retained False
Final remaining audit: WADImportGetBlocks 286/298; target initializes two unused zero owners and conditionally frees them; no dummy owners added. WADImportEx 1139/1146: frame 0x760 matches; metadata spill and branch/status ordering remain. WADBackupEx 1033/1062: frame 0x8c0 matches; genuine transfer/size/signature/cleanup blocks retranslated; remaining prologue, metadata addressing, and branch layout. WADOpenStream 202/203: target has an unreachable branch after SD seek failure. _WADUnpackBackup 114/113: defined success initialization adds one instruction on skipped-metadata path. _WADRandPad 89/91: scalar tail source address reused rather than recomputed. WADImportDVDExForBS 260/263: target retains empty content-size comparison and null/status setup. All open functions have at least three fresh distinct source attempts. Five open functions have equal counts and only register differences.
Cleanup: remove consecutive duplicate success assignment; restore equal-scoring structured SD seek block rather than retaining extra labels.
_WADRandPad: tail byte source recomputed inside each iteration; insns/diffs/nonregister (89, 91, 26, 25) -> (91, 91, 0, 0); objdiff 100.0; retained True
_WADRandPad: tail source uses void byte view with loop index; insns/diffs/nonregister (91, 91, 0, 0) -> (91, 91, 35, 32); objdiff 96.15385; retained False
_WADRandPad: tail count and byte cursor established before random word assignment; insns/diffs/nonregister (91, 91, 0, 0) -> (89, 91, 43, 35); objdiff 93.72527; retained False
WADImportEx: metadata owner declared first before progress and status; insns/diffs/nonregister (1139, 1146, 1083, 1045) -> (1142, 1146, 1123, 1099); objdiff 82.47819; retained False
WADImportEx: metadata owner and function report declared before progress state; insns/diffs/nonregister (1139, 1146, 1083, 1045) -> (1142, 1146, 1123, 1099); objdiff 82.47819; retained False
WADImportEx: report name then metadata owner precede status and progress; insns/diffs/nonregister (1139, 1146, 1083, 1045) -> (1142, 1146, 1123, 1099); objdiff 82.47819; retained False
WADImportDVDExForBS: keep allocation buffer null validation as pointer comparison; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.08365; retained True
WADImportDVDExForBS: chunk minimum uses remaining-size greater-than branch with destination retained; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.12167; retained True
WADImportDVDExForBS: declare remaining buffer length after content count to match pointer lifetime; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.17871; retained True
WADImportEx: stack first: place transfer before saved file header to match target 0x120 and 0xa0; insns/diffs/nonregister (1139, 1146, 1083, 1045) -> (1139, 1146, 1082, 1044); objdiff 83.37086; retained True
WADImportEx: retranslate shared hash allocation failure exactly, including zero-count allocation result; insns/diffs/nonregister (1139, 1146, 1082, 1044) -> (1136, 1146, 1095, 1063); objdiff 83.84032; retained True
WADImportEx: retranslate indexed content lookup: unsigned mode threshold, record pointer in each branch, successful status clear; insns/diffs/nonregister (1136, 1146, 1095, 1063) -> (1148, 1146, 1083, 1042); objdiff 85.16143; retained True
WADImportEx: clear import status before beginning content and after obtaining a valid descriptor; insns/diffs/nonregister (1148, 1146, 1083, 1042) -> (1152, 1146, 1103, 1068); objdiff 85.3089; retained True
WADImportEx: use unsigned traversal count for metadata array indices; insns/diffs/nonregister (1152, 1146, 1103, 1068) -> (1152, 1146, 1103, 1068); objdiff 85.34468; retained True
WADImportEx: emit missing-content import before matched-content skip as target address order; insns/diffs/nonregister (1152, 1146, 1103, 1068) -> (1152, 1146, 1097, 1059); objdiff 88.05061; retained True
WADImportEx: retranslate final callback: file list size and count select backup progress; zero progress last; insns/diffs/nonregister (1152, 1146, 1097, 1059) -> (1153, 1146, 1096, 1058); objdiff 89.56806; retained True
WADBackupEx: validate system-title prefix with explicit title ID mask as target; insns/diffs/nonregister (1033, 1062, 1010, 989) -> (1035, 1062, 1016, 993); objdiff 91.14595; retained False
WADBackupEx: preserve flags mask comparison width in title import validation; insns/diffs/nonregister (1033, 1062, 1010, 989) -> (1034, 1062, 1014, 985); objdiff 91.25047; retained False
WADBackupEx: initialize size accumulators immediately before title metadata query; insns/diffs/nonregister (1033, 1062, 1010, 989) -> (1033, 1062, 1010, 989); objdiff 91.35123; retained True
WADImportEx: selected content pointer declared with metadata state rather than inside loop; insns/diffs/nonregister (1153, 1146, 1096, 1058) -> (1153, 1146, 1096, 1058); objdiff 89.53316; retained False
WADImportEx: loop cursor initialization occurs at traversal entry rather than function entry; insns/diffs/nonregister (1153, 1146, 1096, 1058) -> (1153, 1146, 1096, 1058); objdiff 89.56806; retained True
WADImportEx: assign successful argument-validation status through progress cursor before callback; insns/diffs/nonregister (1153, 1146, 1096, 1058) -> (1154, 1146, 1062, 1012); objdiff 89.74084; retained True
WADBackupEx: mask the 32-bit title prefix before comparing to system title class; insns/diffs/nonregister (1033, 1062, 1010, 989) -> (1032, 1062, 999, 980); objdiff 91.14877; retained False
WADBackupEx: initialize parsed title components after successful encryption-buffer allocation; insns/diffs/nonregister (1033, 1062, 1010, 989) -> (1033, 1062, 1010, 988); objdiff 91.53484; retained True
WADBackupEx: keep header block address through initial write and explicit count local; insns/diffs/nonregister (1033, 1062, 1010, 988) -> (1035, 1062, 1010, 980); objdiff 91.32768; retained False
WADBackupEx: restore size initialization at declaration to preserve argument spill offsets; insns/diffs/nonregister (1033, 1062, 1010, 988) -> (1033, 1062, 1010, 988); objdiff 91.53484; retained True
WADBackupEx: declare saved-file descriptor owner before other function locals; insns/diffs/nonregister (1033, 1062, 1010, 988) -> (1044, 1062, 1022, 994); objdiff 93.373825; retained True
WADBackupEx: normalize backup option flags through a local with argument lifetime ending at initialization; insns/diffs/nonregister (1044, 1062, 1022, 994) -> (1045, 1062, 1018, 994); objdiff 92.80038; retained False
WADImportEx: keep parsed metadata owner alongside stream arguments at function entry; insns/diffs/nonregister (1154, 1146, 1062, 1012) -> (1154, 1146, 1062, 1012); objdiff 89.74084; retained True
WADImportEx: remove unused scalar declarations left by earlier translations; insns/diffs/nonregister (1154, 1146, 1062, 1012) -> (1154, 1146, 1062, 1012); objdiff 89.74084; retained True
WADBackupEx: remove unused scalar declarations left by earlier translations; insns/diffs/nonregister (1044, 1062, 1022, 994) -> (1044, 1062, 1022, 994); objdiff 93.373825; retained True
WADImportEx: initial header read keeps requested byte count for returned-count comparison; insns/diffs/nonregister (1154, 1146, 1062, 1012) -> (1156, 1146, 1063, 1023); objdiff 89.47557; retained False
WADImportEx: boot read validates byte count without storing it as import status, then resets successful status; insns/diffs/nonregister (1154, 1146, 1062, 1012) -> (1155, 1146, 1078, 1045); objdiff 90.37522; retained True
WADBackupEx: reuse backup header byte count across initial and per-file hash/write checks; insns/diffs/nonregister (1044, 1062, 1022, 994) -> (1051, 1062, 1013, 980); objdiff 92.655365; retained False
WADImportEx: retranslate first savedata traversal: reset writable header pointer each read and clear successful read status; insns/diffs/nonregister (1155, 1146, 1078, 1045) -> (1156, 1146, 1072, 1034); objdiff 90.59773; retained True
WADImportEx: retranslate final permissions pass with explicit status branches and per-read header reset; insns/diffs/nonregister (1156, 1146, 1072, 1034) -> (1156, 1146, 1071, 1034); objdiff 91.15968; retained True
WADImportEx: clear successful file read/write status and compute file progress relative to its section first; insns/diffs/nonregister (1156, 1146, 1071, 1034) -> (1156, 1146, 1072, 1036); objdiff 92.03316; retained True
Progress after additional block translations: _WADRandPad now 91/91 with ctxdiff zero; WADImportEx 92.03316 after savedata pointer/status/permissions and callback corrections; WADBackupEx 93.373825 after moving the real file owner before other locals. Full gate running before committing these changes. Six instruction-count discrepancies remain; no artificial zero owners, unreachable branch padding, or undefined return values introduced.
WADImportEx: declare first buffer owner before progress and parsed metadata state; insns/diffs/nonregister (1156, 1146, 1072, 1036) -> (1156, 1146, 1072, 1036); objdiff 92.03316; retained True
WADImportEx: declare both buffer owners before progress and parsed metadata state; insns/diffs/nonregister (1156, 1146, 1072, 1036) -> (1156, 1146, 1072, 1036); objdiff 92.1815; retained True
WADBackupEx: initialize saved-file owner after declarations while preserving its early variable lifetime; insns/diffs/nonregister (1044, 1062, 1022, 994) -> (1033, 1062, 1011, 989); objdiff 91.53484; retained False
WADImportEx: represent successful validation directly as zero status; insns/diffs/nonregister (1156, 1146, 1072, 1036) -> (1157, 1146, 1083, 1045); objdiff 91.91536; retained False
WADImportEx: retain direct zero success status despite 92.1815 -> 91.91536 fuzzy change; assigning status from a progress counter obscures its purpose. No matching functions regressed.
WADImportEx: metadata declaration between first and second buffer owners; insns/diffs/nonregister (1157, 1146, 1083, 1045) -> (1157, 1146, 1083, 1045); objdiff 91.91536; retained True
WADImportEx: status declared before progress with buffer owners already first; insns/diffs/nonregister (1157, 1146, 1083, 1045) -> (1157, 1146, 1083, 1045); objdiff 91.91536; retained True
WADImportEx: report-name declaration first followed by both buffer owners; insns/diffs/nonregister (1157, 1146, 1083, 1045) -> (1157, 1146, 1083, 1045); objdiff 91.91536; retained True
Final attempt-count audit:
WADImportGetBlocks: 4 logged attempts; 1192 B; 94.24161 -> 94.22147; source/target 286/298; positional nonregister 260
WAD_815BFFA8: 10 logged attempts; 248 B; 97.17742 -> 99.354836; source/target 62/62; positional nonregister 0
WADImportEx: 50 logged attempts; 4584 B; 79.803665 -> 91.91536; source/target 1157/1146; positional nonregister 1045
WAD_815C1288: 7 logged attempts; 244 B; 96.39344 -> 96.39344; source/target 61/61; positional nonregister 0
WADBackupEx: 37 logged attempts; 4248 B; 82.283424 -> 93.373825; source/target 1044/1062; positional nonregister 994
WADOpenStream: 14 logged attempts; 812 B; 98.891624 -> 99.50739; source/target 202/203; positional nonregister 47
_WADUnpackBackup: 5 logged attempts; 452 B; 97.34513 -> 99.02655; source/target 114/113; positional nonregister 73
_WADBackupGetFiles: 11 logged attempts; 1268 B; 97.19243 -> 100.0; source/target 317/317; positional nonregister 0
_WADBackupGetSize: 9 logged attempts; 620 B; 99.90323 -> 99.90323; source/target 155/155; positional nonregister 0
_WADRandPad: 13 logged attempts; 364 B; 93.78022 -> 100.0; source/target 91/91; positional nonregister 0
WAD_815C43E0: 10 logged attempts; 248 B; 97.17742 -> 99.354836; source/target 62/62; positional nonregister 0
_WADHash: 3 logged attempts; 776 B; 98.53093 -> 98.5567; source/target 194/194; positional nonregister 0
WADImportDVDExForBS: 6 logged attempts; 1052 B; 96.04562 -> 96.17871; source/target 260/263; positional nonregister 233
data final audit .data: source 458, target 464, overlapping differences 0, target remainder 000000000000; alignments 8/8
data final audit .sdata: source 64, target 64, overlapping differences 0, target remainder ; alignments 8/8
Final limitations: WADImportEx 1157/1146 retains metadata and pool-pointer spill differences plus success-store scheduling; WADBackupEx 1044/1062 retains prologue zero ordering, scalar offsets, header address folding and branch shape. WADImportGetBlocks 286/298 lacks two target-only unused allocation owners; WADOpenStream 202/203 lacks target unreachable SD branch; _WADUnpackBackup 114/113 keeps defined success initialization for skipped metadata; WADImportDVDExForBS 260/263 lacks target empty comparison and null/status setup. Remaining five functions are registers-only. Both newly exact functions have ctxdiff zero. Data tail gap remains uncertain; no dummy padding added.
```

Full gate:
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/wad/wad] pool: IDENTICAL
[libs/RVL_SDK/src/wad/wad] objdiff: code 10024/24500 data 64/528 functions 29/40 fuzzy 96.7618 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 29/40
[libs/RVL_SDK/src/wad/wad]   section .data size 464 match 99.34924
[libs/RVL_SDK/src/wad/wad]   section .sdata size 64 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .text size 24500 match 96.761795
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportGetBlocks 94.22147
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815BFFA8 99.354836
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportEx 91.91536
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C1288 96.39344
[libs/RVL_SDK/src/wad/wad]   below 100: WADBackupEx 93.373825
[libs/RVL_SDK/src/wad/wad]   below 100: WADOpenStream 99.50739
[libs/RVL_SDK/src/wad/wad]   below 100: _WADUnpackBackup 99.02655
[libs/RVL_SDK/src/wad/wad]   below 100: _WADBackupGetSize 99.90323
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C43E0 99.354836
[libs/RVL_SDK/src/wad/wad]   below 100: _WADHash 98.5567
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportDVDExForBS 96.17871
[libs/RVL_SDK/src/wad/wad] baseline: code 8392/24500 data 64 functions 27 fuzzy 92.2340
regressions vs baseline: 0
global matched_code_percent: 85.63862 -> 85.69311
global fuzzy_match_percent: 98.59054 -> 98.62757
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85581 -> 90.85581
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: libs/RVL_SDK/src/wad/wad.c: possible pointer+offset into a blob (orchestrator reviews) (+4 net), e.g. if ((u32)WADReadStream(&stream, &readBuffer, (bootSize + 0x1F) & ~0x1F,
GATE PASS
```

# WAD matching attempts, round 3

Baseline main 23067a34: 29/40 exact, code 10024/24500, data 64/528.

| Function | Bytes | Objdiff before -> after | Instructions source/target | Positional diffs / nonregister |
|---|---:|---|---|---|
| WADImportGetBlocks | 1192 | 94.22147 -> 94.22147 | 286/298 | 275 / 260 |
| WAD_815BFFA8 | 248 | 99.354836 -> 99.354836 | 62/62 | 8 / 0 |
| WADImportEx | 4584 | 91.91536 -> 97.835075 | 1144/1146 | 327 / 79 |
| WAD_815C1288 | 244 | 96.39344 -> 96.39344 | 61/61 | 34 / 0 |
| WADBackupEx | 4248 | 93.373825 -> 96.98493 | 1059/1062 | 816 / 748 |
| WADOpenStream | 812 | 99.50739 -> 100.0 | 203/203 | 0 / 0 |
| _WADUnpackBackup | 452 | 99.02655 -> 100.0 | 113/113 | 0 / 0 |
| _WADBackupGetSize | 620 | 99.90323 -> 100.0 | 155/155 | 0 / 0 |
| WAD_815C43E0 | 248 | 99.354836 -> 99.354836 | 62/62 | 8 / 0 |
| _WADHash | 776 | 98.5567 -> 98.5567 | 194/194 | 44 / 0 |
| WADImportDVDExForBS | 1052 | 96.17871 -> 96.17871 | 260/263 | 243 / 233 |

Fresh attempts (rejected variants were restored):

```text
Round 3 baseline main 23067a34: 29/40 exact, code 10024/24500, data 64/528. Pool and section audit first, closest functions next; all open functions receive fresh logged source attempts. Applying the unslop skill for authored reporting.
_WADBackupGetSize: separate metadata/content subtotal from file-inclusive total; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
_WADBackupGetSize: compute aggregate only at total-size output after separate content/file outputs; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 10, 9); objdiff 97.3871; retained False
_WADBackupGetSize: keep distinct total-size local rather than reassigning metadata accumulator; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
WADOpenStream: SD seek uses structured failure branch before the common handle check; insns/diffs/nonregister (202, 203, 47, 47) -> (202, 203, 47, 47); objdiff 99.50739; retained True
WADOpenStream: SD write/read selection ends seek guard with an explicit empty success arm; insns/diffs/nonregister (202, 203, 47, 47) -> (203, 203, 0, 0); objdiff 100.0; retained True
WADOpenStream: move SD seek return into a single outer write guard without a success goto; insns/diffs/nonregister (203, 203, 0, 0) -> (203, 203, 0, 0); objdiff 100.0; retained True
.data: source 458, target 464, overlap mismatches 0; trailing target 000000000000
.sdata: source 64, target 64, overlap mismatches 0; trailing target 
WAD_815BFFA8: chunk byte count declared before descriptor/context state; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 24, 0); objdiff 97.66129; retained False
WAD_815BFFA8: successful transfer status initialized before input descriptor/context load; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815BFFA8: signed API byte-count temporary with unsigned remaining-size arithmetic; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815C43E0: chunk byte count declared before descriptor/context state; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 24, 0); objdiff 97.66129; retained False
WAD_815C43E0: successful transfer status initialized before input descriptor/context load; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815C43E0: signed API byte-count temporary with unsigned remaining-size arithmetic; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
_WADUnpackBackup: translate skipped-metadata return as defined incoming header-address status held in r3; insns/diffs/nonregister (114, 113, 78, 73) -> (117, 113, 100, 97); objdiff 96.0177; retained False
_WADUnpackBackup: initialize defined incoming status after header checks before optional device query; insns/diffs/nonregister (114, 113, 78, 73) -> (113, 113, 0, 0); objdiff 100.0; retained True
_WADUnpackBackup: return success directly on metadata-only completion rather than preserving a mutable status; insns/diffs/nonregister (113, 113, 0, 0) -> (114, 113, 55, 45); objdiff 96.814156; retained False
_WADUnpackBackup: target 815C360C-815C36F8 keeps incoming r3 on contentSize==0, nonzero tmdSize, and flags bits 4/2 both set. Explicitly initializing result from header after validation models that defined machine return without uninitialized C. Source 113/113, ctxdiff zero, 100%.
Threads: all three fresh register-only variants reverted because no instruction improvement; original unsigned byte counts retained.
_WADHash: declare read length before progress cursor and mutable read buffer; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 44, 0); objdiff 98.5567; retained True
_WADHash: separate read length for synchronous chunks from thread-consumer chunks; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 44, 0); objdiff 98.5567; retained True
_WADHash: use loop-header buffer swap for threaded producer traversal; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 44, 0); objdiff 98.5567; retained True
WAD_815C1288: size local first in export consumer state; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WAD_815C1288: export result initialized before descriptor and loop input loads; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: chunk count local scoped to each transfer iteration; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WADImportEx: stack-first: declare content count before stream ownership flags; insns/diffs/nonregister (1157, 1146, 1083, 1045) -> (1157, 1146, 1079, 1041); objdiff 91.927574; retained True
WADImportEx: stack-first: declare thread stack owner before content descriptor and import flags; insns/diffs/nonregister (1157, 1146, 1079, 1041) -> (1157, 1146, 1078, 1040); objdiff 91.94067; retained True
WADImportEx: report label uses mutable C string pointer type as SDK C convention; insns/diffs/nonregister (1157, 1146, 1078, 1040) -> (1157, 1146, 1078, 1040); objdiff 91.94067; retained True
Round 3 progress: WADOpenStream and _WADUnpackBackup now instruction-exact and locally committed after quick gates. Five remaining register-only functions received three fresh variants each. Initial data audit still finds identical strings and all .sdata, with six terminal .data bytes absent. Work continues on the four instruction-count discrepancies.
WADImportEx: inline helper for the two cancellation reports; (1157, 1146, 1078, 1040) -> (1157, 1146, 1078, 1040); 91.94067 -> 91.94067; outlined False; pool POOL IDENTICAL up to 18 (mine=18 base=18); retained False
WADImportDVDExForBS: use adjusted read-buffer pointer for post-open allocation check; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.17871; retained True
WADImportDVDExForBS: scope and compute aligned read size before the DVD call; insns/diffs/nonregister (260, 263, 243, 233) -> (259, 263, 238, 225); objdiff 94.277565; retained False
WADImportDVDExForBS: iterate content descriptors with a for loop; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.17871; retained True
WADImportGetBlocks: declare file-list ownership first to extend the actual allocation lifetime; insns/diffs/nonregister (286, 298, 275, 260) -> (286, 298, 276, 260); objdiff 93.93624; retained False
WADImportGetBlocks: count content indices with an explicit while loop; insns/diffs/nonregister (286, 298, 275, 260) -> (286, 298, 275, 260); objdiff 94.22147; retained True
WADImportGetBlocks: scope title metadata and the current content descriptor to their actual traversal; compilation failed; restored
WADImportGetBlocks: scope metadata and content descriptors at the starts of traversal blocks; insns/diffs/nonregister (286, 298, 275, 260) -> (286, 298, 275, 260); objdiff 94.22147; retained True
WADBackupEx: compute the metadata padding delta before random fill and recompute the write extent; insns/diffs/nonregister (1044, 1062, 1022, 994) -> (1047, 1062, 1026, 995); objdiff 94.089455; retained True
WADBackupEx: select NAND transfer size with explicit greater-than if/else arms; insns/diffs/nonregister (1047, 1062, 1026, 995) -> (1048, 1062, 1030, 1002); objdiff 94.32957; retained True
WADBackupEx: extract the low title-id word with its explicit unsigned mask for the random seed; insns/diffs/nonregister (1048, 1062, 1030, 1002) -> (1051, 1062, 1017, 985); objdiff 94.414314; retained True
WADBackupEx: route file-header hash failure directly to global cleanup as target does; insns/diffs/nonregister (1051, 1062, 1017, 985) -> (1051, 1062, 1017, 985); objdiff 94.41902; retained True
Restored equal-code hash, export loop, DVD import, and block-count variants; retained only instruction/fuzzy improvements.
WADImportEx: initialize optional parsed title metadata alongside the import buffer owners; insns/diffs/nonregister (1157, 1146, 1078, 1040) -> (1157, 1146, 1078, 1040); objdiff 91.94067; retained True
WADImportEx: declare parsed title metadata before the diagnostic name and other owners; insns/diffs/nonregister (1157, 1146, 1078, 1040) -> (1160, 1146, 1126, 1097); objdiff 90.84206; retained False
WADImportEx: declare diagnostic function name after all actual import owner state; insns/diffs/nonregister (1157, 1146, 1078, 1040) -> (1157, 1146, 1078, 1040); objdiff 91.94067; retained True
WADImportEx: use a signed header read-size local across the read and returned-size check; insns/diffs/nonregister (1157, 1146, 1078, 1040) -> (1158, 1146, 1098, 1063); objdiff 92.20768; retained True
WADImportGetBlocks: inline shared import-buffer cleanup used by both actual import and block counting; (290, 298, 278, 263); objdiff 94.2047
WADImportEx: inline shared import-buffer cleanup used by both actual import and block counting; (1158, 1146, 1098, 1063); objdiff 92.20768
Shared cleanup helper trial restored pending instruction improvement and pool review.
WADBackupEx: group backup-header construction and device-id query in a typed inline helper; (1051, 1062, 1017, 985); objdiff 94.33616
WADImportEx: derive diagnostic function name from compiler function-name identifier; insns/diffs/nonregister (1158, 1146, 1098, 1063) -> (1158, 1146, 1098, 1063); objdiff 92.20768; retained True
WADImportEx: retain a declaration for matched title metadata next to unpack workspace; insns/diffs/nonregister (1158, 1146, 1098, 1063) -> (1158, 1146, 1098, 1063); objdiff 92.20768; retained True
WADImportEx: choose decrypted file chunks with explicit size limit branches; insns/diffs/nonregister (1158, 1146, 1098, 1063) -> (1159, 1146, 1088, 1046); objdiff 92.33857; retained True
WADImportEx: compare decoded content index against metadata count in target less-than direction; insns/diffs/nonregister (1159, 1146, 1088, 1046) -> (1159, 1146, 1088, 1046); objdiff 92.364746; retained True
WADBackupEx: hold the initialized header extent in the shared padded-size temporary for its write check; insns/diffs/nonregister (1051, 1062, 1017, 985) -> (1052, 1062, 1011, 980); objdiff 94.607346; retained True
WADBackupEx: hold file-header write extent in padded-size temporary after the hash update; insns/diffs/nonregister (1052, 1062, 1011, 980) -> (1053, 1062, 1019, 990); objdiff 94.55085; retained False
WADBackupEx: store regular-file classification before optional file-data export; insns/diffs/nonregister (1052, 1062, 1011, 980) -> (1054, 1062, 1023, 995); objdiff 94.39077; retained False
WADImportEx: preserve the successful ES content descriptor status until the next real API result; insns/diffs/nonregister (1159, 1146, 1088, 1046) -> (1157, 1146, 1100, 1059); objdiff 92.00349; retained False
WADImportEx: defer first file-header pointer initialization until transfer-id resolution succeeds; insns/diffs/nonregister (1159, 1146, 1088, 1046) -> (1159, 1146, 1088, 1046); objdiff 91.9555; retained False
WADBackupEx: express the high title-id word as an unsigned masked extraction; insns/diffs/nonregister (1052, 1062, 1011, 980) -> (1054, 1062, 921, 890); objdiff 94.66384; retained True
WADBackupEx: declare initialized size outputs before pointer owners and local work buffers; insns/diffs/nonregister (1054, 1062, 921, 890) -> (1044, 1062, 1004, 981); objdiff 92.659134; retained False
WADBackupEx: keep the trailing path fill length including its terminator as one local; insns/diffs/nonregister (1054, 1062, 921, 890) -> (1054, 1062, 921, 890); objdiff 94.89548; retained True
WADImportEx: give each cancellation diagnostic a real typed inline wrapper with local function-name lifetime; (1140, 1146, 910, 824); objdiff 95.26614
Cancellation diagnostic wrappers retained: metadata now stays in a register; source shrinks 1159 to 1140 against target 1146; fuzzy 95.26614. Both wrappers inline; no new public functions or artificial code.
WADImportEx: cast the unsigned stream byte count to signed for the signed header-size comparison; insns/diffs/nonregister (1140, 1146, 910, 824) -> (1140, 1146, 910, 823); objdiff 95.06283; retained False
WADImportEx: assign an ES content descriptor to result only on failure before the common success reset; insns/diffs/nonregister (1140, 1146, 910, 824) -> (1141, 1146, 749, 613); objdiff 95.279236; retained True
WADImportEx: write directory creation error as a nested success/error branch before existing-directory recovery; insns/diffs/nonregister (1141, 1146, 749, 613) -> (1141, 1146, 762, 626); objdiff 95.63264; retained True
WADImportEx: pass function name to cancellation wrappers defined later in source-token order; (1160, 1146, 1096, 1063); objdiff 93.0
WADImportEx: declare returned status before buffer ownership so it is the first initialized scalar; insns/diffs/nonregister (1141, 1146, 762, 626) -> (1141, 1146, 740, 603); objdiff 95.72513; retained True
WADImportEx: place parsed title metadata first among local declarations after status; insns/diffs/nonregister (1141, 1146, 740, 603) -> (1141, 1146, 740, 603); objdiff 95.72513; retained True
WADImportEx: give the fixed header extent unsigned storage while both read operands use signed comparison; insns/diffs/nonregister (1141, 1146, 740, 603) -> (1141, 1146, 740, 602); objdiff 95.77487; retained True
WADImportEx: extend file-header buffer lifetime with its declaration next to the concrete file header; insns/diffs/nonregister (1141, 1146, 740, 602) -> (1143, 1146, 1095, 1058); objdiff 95.635254; retained False
_WADBackupGetSize: add file bytes to the parenthesized metadata/content subtotal; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
_WADBackupGetSize: add file bytes to content plus metadata in the final aggregate expression; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.870964; retained False
_WADBackupGetSize: add content bytes to file plus metadata in the final aggregate expression; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 3, 0); objdiff 99.83871; retained False
WAD_815BFFA8: scope the current chunk byte count inside the transfer iteration; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815BFFA8: clear buffer readiness after recording the real ES error flag; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 12, 4); objdiff 95.96774; retained False
WAD_815C43E0: scope the current chunk byte count inside the transfer iteration; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 8, 0); objdiff 99.354836; retained True
WAD_815C43E0: clear buffer readiness after recording the real ES error flag; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 12, 4); objdiff 95.96774; retained False
WAD_815BFFA8: share typed inline readiness/error completion after ES transfer; (62, 62, 8, 0); objdiff 99.354836
WAD_815C43E0: share typed inline readiness/error completion after ES transfer; (62, 62, 8, 0); objdiff 99.354836
_WADBackupGetSize: combine content and file contributions in one compound addition; insns/diffs/nonregister (155, 155, 2, 0) -> (155, 155, 0, 0); objdiff 100.0; retained True
WADImportEx: initialize the real file-header pointer before allocating the second file-transfer buffer; insns/diffs/nonregister (1141, 1146, 740, 602) -> (1142, 1146, 638, 474); objdiff 95.858635; retained True
WADImportEx: initialize the current header pointer in the file-import loop scope; insns/diffs/nonregister (1142, 1146, 638, 474) -> (1140, 1146, 797, 688); objdiff 95.92496; retained True
_WADBackupGetSize: combined compound update titleSize += contentSize + filesSize is instruction-exact (155/155, zero diffs); stopped further register attempts. Extra equal-code thread scope variants restored.
WADImportEx: rejected separate per-loop header-pointer scope despite higher fuzzy score; retained outer pointer initialized before second file buffer, which preserves target slot and advances instruction count to 1142/1146.
WADImportEx: join directory creation and existing-directory recovery at their common status check; insns/diffs/nonregister (1142, 1146, 638, 474) -> (1143, 1146, 900, 810); objdiff 97.23124; retained True
WADImportEx: retain the size-query status when reading installed title metadata; insns/diffs/nonregister (1143, 1146, 900, 810) -> (1144, 1146, 509, 299); objdiff 97.3185; retained True
WADImportEx: read each indexed installed-content field directly across the hash comparison call; insns/diffs/nonregister (1144, 1146, 509, 299) -> (1145, 1146, 989, 928); objdiff 97.680626; retained True
WADImportEx: initialize the matched-content output index before allocating its actual metadata array; insns/diffs/nonregister (1145, 1146, 989, 928) -> (1145, 1146, 992, 935); objdiff 97.850784; retained True
WADImportEx: pass the decoded header ticket type held in target r8 to ES_ImportTicket; insns/diffs/nonregister (1145, 1146, 992, 935) -> (1144, 1146, 327, 79); objdiff 97.835075; retained False
WADImportEx: return diagnostics to direct reports after installed-content pointer lifetime and status corrections; (1164, 1146, 1101, 1067); objdiff 94.6178
WADImportEx: retained decoded ES_ImportTicket type despite 0.016 fuzzy decrease. Target 815C02E0 loads headerInfo into r8 and 815C03BC passes it unchanged; literal zero was a real translation error. Source 1144/1146 now differs mainly in report pointer reloads and scheduling.
WADImportEx: cancellation diagnostic message lifetime variant; (1144, 1146, 327, 79); objdiff 97.835075
WADImportEx: cancellation diagnostic namehelper lifetime variant; (1144, 1146, 327, 79); objdiff 97.835075
WADImportDVDExForBS: move buffer availability and alignment into typed inline preparation with real size output; (262, 263, 246, 236); objdiff 94.44867
WADImportEx/data: use one actual named immutable diagnostic string shared by the two report wrappers; (1141, 1146, 1094, 1058); objdiff 96.5445; sections [{'name': '.data', 'size': '464', 'fuzzy_match_percent': 97.592995, 'metadata': {}}, {'name': '.sdata', 'size': '64', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.text', 'size': '24500', 'fuzzy_match_percent': 97.92686, 'metadata': {}}]
WADBackupEx: order real ownership flags and thread-stack pointer by target stack slots; insns/diffs/nonregister (1054, 1062, 921, 890) -> (1054, 1062, 920, 889); objdiff 94.90866; retained True
WADBackupEx: compare the masked high title-id word as an unsigned 32-bit field; insns/diffs/nonregister (1054, 1062, 920, 889) -> (1053, 1062, 1026, 1000); objdiff 95.06403; retained True
WADBackupEx: encode installed-content availability with an explicit successful else arm; insns/diffs/nonregister (1053, 1062, 1026, 1000) -> (1053, 1062, 1026, 1000); objdiff 95.06403; retained True
WADBackupEx: clear export status before validating the selected content descriptor; insns/diffs/nonregister (1053, 1062, 1026, 1000) -> (1054, 1062, 1032, 1007); objdiff 95.158195; retained True
WADBackupEx: keep backup file header extent across hashing and stream write as one actual transfer size; insns/diffs/nonregister (1054, 1062, 1032, 1007) -> (1055, 1062, 1034, 1007); objdiff 95.29944; retained True
WADBackupEx: write backup metadata size fields before file size/count in target address order; insns/diffs/nonregister (1055, 1062, 1034, 1007) -> (1055, 1062, 1034, 1009); objdiff 95.30697; retained True
WADBackupEx: place the parsed title words in target scalar slots and initialize only while parsing a title path; insns/diffs/nonregister (1055, 1062, 1034, 1009) -> (1055, 1062, 1035, 1010); objdiff 95.70056; retained True
WADBackupEx: compare selected title content index against the metadata bound in target direction; insns/diffs/nonregister (1055, 1062, 1035, 1010) -> (1055, 1062, 1034, 1009); objdiff 95.71469; retained True
WADBackupEx: reset completed signing status before querying the second certificate; insns/diffs/nonregister (1055, 1062, 1034, 1009) -> (1056, 1062, 1032, 1006); objdiff 95.62053; retained False
WADBackupEx: reset successful seek status before rewriting the finalized backup header; insns/diffs/nonregister (1055, 1062, 1034, 1009) -> (1056, 1062, 1032, 1006); objdiff 95.804146; retained True
WADBackupEx: use the actual indexed backup-file record directly across path fill and copy calls; insns/diffs/nonregister (1056, 1062, 1032, 1006) -> (1057, 1062, 1022, 987); objdiff 96.10546; retained True
WADBackupEx: initialize genuine backup owners and size outputs in target order without moving their stack declarations; insns/diffs/nonregister (1057, 1062, 1022, 987) -> (1058, 1062, 814, 751); objdiff 97.079094; retained True
WADBackupEx: represent the serialized header as its real 128-byte buffer and a typed header view; insns/diffs/nonregister (1058, 1062, 814, 751) -> (1058, 1062, 814, 751); objdiff 97.079094; retained True
WADBackupEx: restored equal-code header union and implicit availability fallthrough; retained target signing-status reset despite small fuzzy decrease. Final source/target (1059, 1062, 816, 748); objdiff 96.98493.
Final audit: every initially open function has at least three fresh distinct compiled source trials; failed builds and no-change trials are additional, not counted as successful trials. Three new functions have identical instruction counts and ctxdiff zero. Four remaining functions are register-only. WADImportEx 1144/1146 retains two duplicated target pool-pointer reloads and scheduling differences; decoded ES_ImportTicket type and ES_GetTmd query status now follow target. WADBackupEx 1059/1062 retains header member-address folding, zero-status stores and dead file-type comparison scheduling. WADImportDVDExForBS 260/263 lacks target dead content-size load/compare and materialized null comparison. WADImportGetBlocks 286/298 lacks two unused target null owners and their dead cleanup guards; no dummy owner variables added.
Data: normal literal pool remains identical (18 strings); all 458 overlapping .data bytes and all 64 .sdata bytes are identical. Target .data is 464 bytes with six additional terminal zero bytes; both objects have alignment 8. No .rodata/.sdata2/tables/vtables are present. Named immutable diagnostic string trial broke pool ordering and was restored. No padding, dummy data, section changes or forced retention added; tail origin remains uncertain. Gate pointer/blob review note is an integer padding-length calculation, not an address or string-blob offset.
```

Gate evidence:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/wad/wad] pool: IDENTICAL
[libs/RVL_SDK/src/wad/wad] objdiff: code 11908/24500 data 64/528 functions 32/40 fuzzy 98.5322 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 32/40
[libs/RVL_SDK/src/wad/wad]   section .data size 464 match 99.34924
[libs/RVL_SDK/src/wad/wad]   section .sdata size 64 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .text size 24500 match 98.53224
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportGetBlocks 94.22147
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815BFFA8 99.354836
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportEx 97.835075
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C1288 96.39344
[libs/RVL_SDK/src/wad/wad]   below 100: WADBackupEx 96.98493
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C43E0 99.354836
[libs/RVL_SDK/src/wad/wad]   below 100: _WADHash 98.5567
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportDVDExForBS 96.17871
[libs/RVL_SDK/src/wad/wad] baseline: code 10024/24500 data 64 functions 29 fuzzy 96.7618
regressions vs baseline: 0
global matched_code_percent: 86.00588 -> 86.06878
global fuzzy_match_percent: 98.73286 -> 98.74735
global complete_code_percent: 59.99415 -> 59.99415
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: libs/RVL_SDK/src/wad/wad.c: possible pointer+offset into a blob (orchestrator reviews) (+1 net), e.g. paddedSize = ((titleMetaSize + 0x3F) & ~0x3F) - titleMetaSize;
GATE PASS
```

# WAD matching attempts, round 4

Baseline main 5c1794ef: 32/40 exact, code 11908/24500, data 64/528. Final: 34/40 exact, code 12404/24500, data 64/528.

| Function | Bytes | Objdiff before -> after | Instructions source/target | Positional diffs / nonregister | Disposition |
|---|---:|---|---|---|---|
| WADImportGetBlocks | 1192 | 94.22147 -> 94.24161 | 286/298 | 274 / 259 | instruction differences remain |
| WAD_815BFFA8 | 248 | 99.354836 -> 100.0 | 62/62 | 0 / 0 | exact |
| WADImportEx | 4584 | 97.835075 -> 98.76091 | 1146/1146 | 254 / 0 | registers only |
| WAD_815C1288 | 244 | 96.39344 -> 96.39344 | 61/61 | 34 / 0 | registers only |
| WADBackupEx | 4248 | 96.98493 -> 97.370995 | 1057/1062 | 874 / 832 | instruction differences remain |
| WAD_815C43E0 | 248 | 99.354836 -> 100.0 | 62/62 | 0 / 0 | exact |
| _WADHash | 776 | 98.5567 -> 99.25258 | 194/194 | 24 / 0 | registers only |
| WADImportDVDExForBS | 1052 | 96.17871 -> 96.17871 | 260/263 | 243 / 233 | instruction differences remain |

Fresh attempts; all rejected and equal-code variants restored except the reported improvements. Nonregister counts are positional and become inflated after an inserted/deleted instruction; LCS block audit isolates the actual gaps. The three instruction-count mismatches remain open despite multiple distinct trials.

```text
Round 4: read AGENTS.md and applied unslop. Restart audit: clean source, GATE PASS baseline 32/40, code 11908/24500, data 64/528, identical pool. Fresh trials follow.
WAD_815BFFA8: express actual chunk selection as a conditional value; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 0, 0); objdiff 100.0; retained True
WAD_815C43E0: express actual chunk selection as a conditional value; insns/diffs/nonregister (62, 62, 8, 0) -> (62, 62, 0, 0); objdiff 100.0; retained True
WAD_815BFFA8 and WAD_815C43E0: conditional chunk expressions are instruction-exact, 62/62 and zero differences. Further attempts stopped at exact matches.
_WADHash: select read extents with conditional expressions in both transfer loops; insns/diffs/nonregister (194, 194, 44, 0) -> (194, 194, 24, 0); objdiff 99.25258; retained True
WAD_815C1288: select actual export chunk with conditional expression; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: order export state as fd, result, remaining, transfer, buffer index and chunk; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: use explicit export chunk branches with separate real assignments; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
_WADHash: initialize completed count at the first actual stream read after argument checks; insns/diffs/nonregister (194, 194, 24, 0) -> (193, 194, 179, 171); objdiff 98.453606; retained False
_WADHash: declare synchronous read extent within its loop and threaded extent within the producer loop; insns/diffs/nonregister (194, 194, 24, 0) -> (194, 194, 24, 0); objdiff 99.25258; retained True
_WADHash: declare and initialize thread producer index before the transfer setup; insns/diffs/nonregister (194, 194, 24, 0) -> (194, 194, 46, 22); objdiff 98.24742; retained False
_WADHash: update completed byte offset with one assignment rather than compound update; insns/diffs/nonregister (194, 194, 24, 0) -> (194, 194, 24, 0); objdiff 99.25258; retained True
_WADHash: keep read-buffer pointer local to each synchronous or producer read; compilation failed; restored
WAD_815C1288: keep the acquired mutex pointer in the outer transfer scope; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WADImportEx: translate cancellation diagnostics with builtin-name; (1144, 1146, 327, 79) -> (1146, 1146, 269, 19); objdiff 98.03927; pool POOL IDENTICAL up to 18 (mine=18 base=18); retained True
WADImportEx: load unpacked content offset before the title metadata pointer in the first decoded block; insns/diffs/nonregister (1146, 1146, 269, 19) -> (1146, 1146, 268, 17); objdiff 98.04537; retained True
WADImportEx: calculate transfer read extent directly at the stream call instead of preserving a redundant local; insns/diffs/nonregister (1146, 1146, 268, 17) -> (1146, 1146, 263, 14); objdiff 98.411865; retained True
WADImportEx: initialize the actual file-header read pointer before either file-transfer allocation; insns/diffs/nonregister (1146, 1146, 263, 14) -> (1146, 1146, 254, 0); objdiff 98.76091; retained True
WADImportEx: address-order translation now 1146/1146, all 254 surviving differences are register operands (normalized nonregister differences zero). Builtin __func__ gives the two target reloads; inline wrappers removed. _WADHash: kept conditional extents, restored equal-code declaration/assignment trials to minimize source diff. Export thread: restored equal-code local scope/explicit chunk trial.
WAD_815C1288: read the indexed mutex directly at each synchronization call; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WADBackupEx: use a typed view of the serialized header for metadata fields and ES device arguments; insns/diffs/nonregister (1059, 1062, 816, 748) -> (1059, 1062, 816, 748); objdiff 96.98493; retained True
WADBackupEx: encode installed-content success and missing-content failure with explicit arms; insns/diffs/nonregister (1059, 1062, 816, 748) -> (1060, 1062, 794, 731); objdiff 96.74953; retained False
WADBackupEx: select the producer content chunk with a conditional expression; insns/diffs/nonregister (1059, 1062, 816, 748) -> (1059, 1062, 816, 748); objdiff 96.98493; retained True
WADImportGetBlocks: evaluate metadata skip flag directly at the decoded metadata use; insns/diffs/nonregister (286, 298, 275, 260) -> (285, 298, 274, 258); objdiff 93.50336; retained False
WADImportGetBlocks: use explicit indexed metadata addresses in both selected-content arms; insns/diffs/nonregister (286, 298, 275, 260) -> (286, 298, 275, 260); objdiff 94.22147; retained True
WADImportGetBlocks: declare the real read file-header pointer only in the file-list block; insns/diffs/nonregister (286, 298, 275, 260) -> (286, 298, 275, 260); objdiff 94.22147; retained True
WADImportDVDExForBS: materialize the real content buffer as the initial nullable read-buffer owner; insns/diffs/nonregister (260, 263, 243, 233) -> (261, 263, 200, 175); objdiff 95.28137; retained False
WADImportDVDExForBS: assign read buffer from the incoming buffer at the post-open availability check; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.17871; retained True
WADImportDVDExForBS: retain the decoded content metadata pointer only inside its import loop; insns/diffs/nonregister (260, 263, 243, 233) -> (260, 263, 243, 233); objdiff 96.17871; retained True
WADBackupEx: use a typed inline device-id query on the actual serialized backup header; (1059, 1062, 816, 748) -> (1059, 1062, 816, 748); objdiff 96.98493; pool POOL IDENTICAL up to 18 (mine=18 base=18); retained True
Restored all equal-code GetBlocks, DVD and Backup trials to reduce source noise. Export, Hash and Import register-only conditions met; three valid trials logged for each remaining function. Continued stack and block audit, not stopping at those counts.
WADImportGetBlocks: keep workspace aligned while giving the stream its natural field alignment at target 0x1d0; (286, 298, 275, 260) -> (286, 298, 274, 259); objdiff 94.24161; pool POOL IDENTICAL up to 18 (mine=18 base=18); retained True
WADBackupEx: address device and mask fields through the serialized header byte view; insns/diffs/nonregister (1059, 1062, 816, 748) -> (1059, 1062, 816, 748); objdiff 96.98493; retained True
WADBackupEx: retain the transfer write status until the worker supplies its joined result; insns/diffs/nonregister (1059, 1062, 816, 748) -> (1058, 1062, 897, 857); objdiff 97.079094; retained True
WADBackupEx: derive validation status from the installed content count before the common status check; insns/diffs/nonregister (1058, 1062, 897, 857) -> (1061, 1062, 928, 897); objdiff 96.64501; retained False
WADBackupEx: include the standard srand prototype so the seed occupies the target 32-bit r3 argument; (1058, 1062, 897, 857) -> (1057, 1062, 874, 832); objdiff 97.187386; pool POOL IDENTICAL up to 18 (mine=18 base=18); retained True
WADBackupEx: keep successful size-only backup status from the preceding validation; insns/diffs/nonregister (1057, 1062, 874, 832) -> (1056, 1062, 928, 895); objdiff 97.14972; retained False
WADBackupEx: retain signing status until the certificate result and clear it after the signature seek; insns/diffs/nonregister (1057, 1062, 874, 832) -> (1057, 1062, 874, 832); objdiff 97.370995; retained True
WAD_815C1288: export register lifetime combination scoped-conditional; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: export register lifetime combination direct-conditional; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
WAD_815C1288: export register lifetime combination separate-condition-status; insns/diffs/nonregister (61, 61, 34, 0) -> (63, 61, 48, 20); objdiff 92.85246; retained False
WAD_815C1288: export register lifetime combination while-loop; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 34, 0); objdiff 96.39344; retained True
WAD_815C1288: export register lifetime combination hoisted-mutex; insns/diffs/nonregister (61, 61, 34, 0) -> (61, 61, 35, 0); objdiff 96.31148; retained False
Final fresh-attempt audit: initially open threads 815BFFA8 and 815C43E0 reached exact on the first conditional-chunk trial. All six remaining functions have at least three distinct compiled source trials this round; failed builds and unchanged replacements are not counted. Export equal-code while-loop trial restored.
WADImportEx: all address-order basic blocks now align; 1146/1146 instructions and normalized nonregister differences zero. The builtin function name removes the inline reporting wrappers and emits both target pool reloads.
WADImportGetBlocks: corrected stream field alignment: baseline frame was actually 0x2c0 and stream 0x1e0 (previous-round claim of matching frame was incorrect); current frame 0x2a0 and stream 0x1d0 match target. LCS differences consist only of two target zero-valued unused owners and their ten cleanup instructions, twelve target instructions total. No dummy owners introduced.
WADBackupEx: corrected actual srand ABI by including stdlib.h; the previous implicit declaration passed the masked 64-bit seed in r3/r4 rather than the target 32-bit seed in r3. Removed target-absent status reset after content write and moved signing-status reset to the successful signature seek. Previous-round evidence claiming a reset before ES_GetDeviceCert was incorrect: target 815C2200-815C2208 contains none, target 815C223C does reset. Residual 1057/1062 includes member-address folding, duplicated count-validation status writes, file-loop zero lifetimes and a dead file-type comparison; no artificial empty branch added.
WADImportDVDExForBS: 260/263 instructions; three real lifetime/null-check translations did not improve accepted code. Target adds an otherwise unused header-content-size load/compare and materializes the null comparator. Nullable real content-buffer trial 261/263 worsened registers and scheduling and was restored.
Data audit .data: source 458, target 464, alignment 8/8, overlapping bytes 458, differing overlapping bytes 0, additional target bytes 000000000000.
Data audit .sdata: source 64, target 64, alignment 8/8, overlapping bytes 64, differing overlapping bytes 0, additional target bytes .
Data audit .rodata: absent in both objects.
Data audit .sdata2: absent in both objects.
Data audit: all eighteen strings and all overlapping data bytes identical. Target .data has six final zero bytes, with no missing strings, data symbols, tables or vtables. Origin of terminal extent remains uncertain; no padding, extra string bytes, dummy objects or forced section retention added.
```

Final full gate evidence:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/wad/wad] pool: IDENTICAL
[libs/RVL_SDK/src/wad/wad] objdiff: code 12404/24500 data 64/528 functions 34/40 fuzzy 98.8085 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 34/40
[libs/RVL_SDK/src/wad/wad]   section .data size 464 match 99.34924
[libs/RVL_SDK/src/wad/wad]   section .sdata size 64 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .text size 24500 match 98.80849
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportGetBlocks 94.24161
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportEx 98.76091
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C1288 96.39344
[libs/RVL_SDK/src/wad/wad]   below 100: WADBackupEx 97.370995
[libs/RVL_SDK/src/wad/wad]   below 100: _WADHash 99.25258
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportDVDExForBS 96.17871
[libs/RVL_SDK/src/wad/wad] baseline: code 11908/24500 data 64 functions 32 fuzzy 98.5322
regressions vs baseline: 0
global matched_code_percent: 86.10818 -> 86.12473
global fuzzy_match_percent: 98.85413 -> 98.85639
global complete_code_percent: 60.24602 -> 60.24602
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
