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
