# NWC24Download attempts

Baseline 7/30 instruction-exact, 472/12496 code bytes, 80/80 data bytes.

Pool checked before code tuning: identical (3 strings). Header, title ownership and group permission checks were reconstructed as readable inline helpers; SetDlId, SetDlPriority and GetDlAppId now match. The initializer retains its observed task-list calls. Seek/write/clear helpers restore task and header normalization, close-result propagation, and entry ownership metadata (application ID, not task flags). StoreDlTask and DeleteDlTask now match, with original explicit call boundaries preserved by the repository NO_INLINE macro.

Closest functions were tried first. Each remaining function has at least three distinct compiled source attempts below. Header-helper extraction, declaration lifetime and keeping call boundaries were measured independently, with only improvements retained. Register-only survivors were left after additional scoped-local and branch-form attempts.

NWC24GetDlTask | named destination alias | (99.728264, -5) | src 0x170 base 0x170 insns 92/92
NWC24GetDlTask | task identifier alias before destination | (99.728264, -5) | src 0x170 base 0x170 insns 92/92
NWC24GetDlTask | operation status before read status | (99.728264, -5) | src 0x170 base 0x170 insns 92/92
NWC24GetDlAppId | taskId local declared after header | (99.0, -7) | src 0x8c base 0x8c insns 35/35
NWC24GetDlAppId | task pointer declared after header | (99.0, -7) | src 0x8c base 0x8c insns 35/35
NWC24GetDlAppId | common exit after output | (99.0, -7) | src 0x8c base 0x8c insns 35/35
NWC24SetDlId | work declaration before header | (98.875, -8) | src 0xa0 base 0xa0 insns 40/40
NWC24SetDlId | reuse initial work in refreshed header | (98.875, -8) | src 0xa0 base 0xa0 insns 40/40
NWC24SetDlId | header declared before task identifier | (98.5, -11) | src 0xa0 base 0xa0 insns 40/40
NWC24iLoadDlHeader | scoped write header pointer | (97.9, -4) | src 0x190 base 0x190 insns 100/100
NWC24iLoadDlHeader | seek and read shared operation result | (96.15, -9999) | src 0x194 base 0x190 insns 101/100
NWC24iLoadDlHeader | read status conditional branch | (95.05, -9999) | src 0x198 base 0x190 insns 102/100
NWC24iInitDlTaskList | separate success and version checks | (51.29032, -9999) | src 0xb8 base 0x7c insns 46/31
NWC24iInitDlTaskList | success test nested before version | (51.29032, -9999) | src 0xb8 base 0x7c insns 46/31
NWC24iInitDlTaskList | common final result | (51.129032, -9999) | src 0xb8 base 0x7c insns 46/31
NWC24iInitDlTaskList | preserve task list calls | (100.0, 0) | src 0x7c base 0x7c insns 31/31
NWC24iLoadDlHeader | shared seek-read status with scoped write pointer | (97.25, -16) | src 0x190 base 0x190 insns 100/100
NWC24iLoadDlHeader | seek-read operation local | (97.25, -16) | src 0x190 base 0x190 insns 100/100
NWC24iLoadDlHeader | inline seek-read operation | (96.25, -9999) | src 0x194 base 0x190 insns 101/100
NWC24SetDlPriority | shared inline validation with owner and group predicates | (100.0, 0) | src 0x108 base 0x108 insns 66/66
NWC24SetDlInterval | shared inline validation with owner and group predicates | (99.89796, -3) | src 0x24c base 0x24c insns 147/147
NWC24SetDlUrl | shared inline validation with owner and group predicates | (99.95413, -1) | src 0x1b4 base 0x1b4 insns 109/109
NWC24SetDlFlags | shared inline validation with owner and group predicates | (98.9011, -9999) | src 0x168 base 0x16c insns 90/91
NWC24GetDlAppId | shared inline validation with owner and group predicates | (100.0, 0) | src 0x8c base 0x8c insns 35/35
NWC24SetDlId | shared inline validation with owner and group predicates | (100.0, 0) | src 0xa0 base 0xa0 insns 40/40
NWC24SetDlInterval | separate final identifier lifetime | (99.89796, -3) | src 0x24c base 0x24c insns 147/147
NWC24SetDlInterval | refresh validation helper | (99.89796, -3) | src 0x24c base 0x24c insns 147/147
NWC24SetDlInterval | timestamp temporary declaration first | (99.89796, -3) | src 0x24c base 0x24c insns 147/147
NWC24SetDlFlags | separate reserved flag categories | (95.43956, -4) | src 0x16c base 0x16c insns 91/91
NWC24SetDlFlags | type checks with two cases | (94.83517, -9999) | src 0x15c base 0x16c insns 87/91
NWC24SetDlFlags | write flags from common exit | (93.95605, -9999) | src 0x178 base 0x16c insns 94/91
NWC24SetDlUrl | length error to common URL check | (98.99083, -9999) | src 0x1b0 base 0x1b4 insns 108/109
NWC24SetDlUrl | length guard around schemes | (98.99083, -9999) | src 0x1b0 base 0x1b4 insns 108/109
NWC24SetDlUrl | ownership pointer after result variable | (99.95413, -1) | src 0x1b4 base 0x1b4 insns 109/109
NWC24InitDlTask | cached-header inline helper lifetime | (89.36806, -9999) | src 0x234 base 0x240 insns 141/144
NWC24InitDlTask | scalar and pointer declaration order | (89.36806, -9999) | src 0x234 base 0x240 insns 141/144
NWC24InitDlTask | preserve calls to earlier functions | (89.36806, -9999) | src 0x234 base 0x240 insns 141/144
NWC24DeleteDlTask | cached-header inline helper lifetime | (85.75238, -9999) | src 0x18c base 0x1a4 insns 99/105
NWC24DeleteDlTask | scalar and pointer declaration order | (85.419044, -9999) | src 0x18c base 0x1a4 insns 99/105
NWC24DeleteDlTask | preserve calls to earlier functions | (85.419044, -9999) | src 0x18c base 0x1a4 insns 99/105
NWC24IterateDlTaskEx | scalar and pointer declaration order | (85.06896, -9999) | src 0x234 base 0x244 insns 141/145
NWC24IterateDlTaskEx | preserve calls to earlier functions | (85.06896, -9999) | src 0x234 base 0x244 insns 141/145
NWC24IterateDlTask | cached-header inline helper lifetime | (80.79747, -9999) | src 0x128 base 0x13c insns 74/79
NWC24IterateDlTask | scalar and pointer declaration order | (81.177216, -9999) | src 0x128 base 0x13c insns 74/79
NWC24IterateDlTask | preserve calls to earlier functions | (80.79747, -9999) | src 0x128 base 0x13c insns 74/79
NWC24ManageDlTaskListForMenu | cached-header inline helper lifetime | (73.45395, -9999) | src 0x20c base 0x260 insns 131/152
NWC24ManageDlTaskListForMenu | scalar and pointer declaration order | (73.585526, -9999) | src 0x20c base 0x260 insns 131/152
NWC24ManageDlTaskListForMenu | preserve calls to earlier functions | (73.585526, -9999) | src 0x20c base 0x260 insns 131/152
NWC24PurgeOldestDlTask | cached-header inline helper lifetime | (72.3125, -9999) | src 0x25c base 0x2c0 insns 151/176
NWC24PurgeOldestDlTask | scalar and pointer declaration order | (72.22727, -9999) | src 0x25c base 0x2c0 insns 151/176
NWC24PurgeOldestDlTask | preserve calls to earlier functions | (72.22727, -9999) | src 0x25c base 0x2c0 insns 151/176
DeleteDlTask | scalar and pointer declaration order | (69.92921, -9999) | src 0x16c base 0x1c4 insns 91/113
DeleteDlTask | preserve calls to earlier functions | (69.92921, -9999) | src 0x16c base 0x1c4 insns 91/113
NWC24iCreateDlTaskList | cached-header inline helper lifetime | (69.01504, -9999) | src 0x1e0 base 0x214 insns 120/133
NWC24iCreateDlTaskList | scalar and pointer declaration order | (69.2406, -9999) | src 0x1e0 base 0x214 insns 120/133
NWC24iCreateDlTaskList | preserve calls to earlier functions | (69.01504, -9999) | src 0x1e0 base 0x214 insns 120/133
StoreDlTask | cached-header inline helper lifetime | (68.196075, -9999) | src 0x154 base 0x198 insns 85/102
StoreDlTask | scalar and pointer declaration order | (68.245094, -9999) | src 0x154 base 0x198 insns 85/102
StoreDlTask | preserve calls to earlier functions | (68.245094, -9999) | src 0x154 base 0x198 insns 85/102
NWC24AddDlTask | cached-header inline helper lifetime | (67.14685, -9999) | src 0x1c4 base 0x23c insns 113/143
NWC24AddDlTask | scalar and pointer declaration order | (65.44056, -9999) | src 0x1cc base 0x23c insns 115/143
NWC24AddDlTask | preserve calls to earlier functions | (67.46154, -9999) | src 0x1c4 base 0x23c insns 113/143
AddTaskInternal | cached-header inline helper lifetime | (63.670822, -9999) | src 0x5d0 base 0x644 insns 372/401
AddTaskInternal | scalar and pointer declaration order | (63.658356, -9999) | src 0x5d0 base 0x644 insns 372/401
AddTaskInternal | preserve calls to earlier functions | (63.658356, -9999) | src 0x5d0 base 0x644 insns 372/401
NWC24UpdateDlTask | cached-header inline helper lifetime | (62.225296, -9999) | src 0x408 base 0x3f4 insns 258/253
NWC24UpdateDlTask | scalar and pointer declaration order | (62.343872, -9999) | src 0x408 base 0x3f4 insns 258/253
NWC24UpdateDlTask | preserve calls to earlier functions | (62.225296, -9999) | src 0x408 base 0x3f4 insns 258/253
NWC24ExtendDlTaskList | cached-header inline helper lifetime | (61.992702, -9999) | src 0x1e4 base 0x224 insns 121/137
NWC24ExtendDlTaskList | scalar and pointer declaration order | (61.91971, -9999) | src 0x1e4 base 0x224 insns 121/137
NWC24ExtendDlTaskList | preserve calls to earlier functions | (61.992702, -9999) | src 0x1e4 base 0x224 insns 121/137
NWC24iCheckDlHeaderConsistency | cached-header inline helper lifetime | (53.9717, -9999) | src 0x270 base 0x350 insns 156/212
NWC24iCheckDlHeaderConsistency | scalar and pointer declaration order | (53.853775, -9999) | src 0x270 base 0x350 insns 156/212
NWC24iCheckDlHeaderConsistency | preserve calls to earlier functions | (53.853775, -9999) | src 0x270 base 0x350 insns 156/212
StoreDlTask | full-width cached count in seek helper | (99.70588, -5) | src 0x198 base 0x198 insns 102/102
StoreDlTask | direct count fields in seek helper | (100.0, 0) | src 0x198 base 0x198 insns 102/102
StoreDlTask | id comparison first in seek helper | (95.78432, -7) | src 0x198 base 0x198 insns 102/102
DeleteDlTask | identifier before cached task declaration | (99.823006, -4) | src 0x1c4 base 0x1c4 insns 113/113
DeleteDlTask | result before cached task declaration | (99.42478, -12) | src 0x1c4 base 0x1c4 insns 113/113
DeleteDlTask | separate header reset identifier | (99.42478, -12) | src 0x1c4 base 0x1c4 insns 113/113
NWC24IterateDlTaskEx | descending expression signed sort mode | (85.06896, -9999) | src 0x234 base 0x244 insns 141/145
NWC24IterateDlTaskEx | iteration result next step in for clause | (85.06896, -9999) | src 0x234 base 0x244 insns 141/145
NWC24IterateDlTaskEx | callback value before candidate booleans | (85.06896, -9999) | src 0x234 base 0x244 insns 141/145
DeleteDlTask | clear helper scopes for task and identifier | (100.0, 0) | src 0x1c4 base 0x1c4 insns 113/113
NWC24iCreateDlTaskList | shared clear/write helpers and original close-result propagation | (99.62406, -10) | src 0x214 base 0x214 insns 133/133
NWC24ExtendDlTaskList | shared clear/write helpers and original close-result propagation | (97.62774, -9999) | src 0x230 base 0x224 insns 140/137
NWC24iCreateDlTaskList | header lifetime scoped to initialization | (99.62406, -10) | src 0x214 base 0x214 insns 133/133
NWC24iCreateDlTaskList | header declaration after task id | (99.62406, -10) | src 0x214 base 0x214 insns 133/133
NWC24iCreateDlTaskList | header after error result | (99.62406, -10) | src 0x214 base 0x214 insns 133/133
NWC24ExtendDlTaskList | iteration failure to close block | (99.85401, -4) | src 0x224 base 0x224 insns 137/137
NWC24ExtendDlTaskList | close status declaration before open status | (91.30657, -9999) | src 0x220 base 0x224 insns 136/137
NWC24ExtendDlTaskList | open result scoped away from iteration | (96.86131, -9999) | src 0x234 base 0x224 insns 141/137
NWC24iCreateDlTaskList | header-format initializer helper | (99.62406, -10) | src 0x214 base 0x214 insns 133/133
NWC24ExtendDlTaskList | separate final return status | (91.277374, -9999) | src 0x1f8 base 0x224 insns 126/137
NWC24ExtendDlTaskList | loop identifier separate scope | (99.85401, -4) | src 0x224 base 0x224 insns 137/137
NWC24ExtendDlTaskList | header pointer declaration after close status | (99.85401, -4) | src 0x224 base 0x224 insns 137/137
NWC24UpdateDlTask | shared ownership and validation helpers | (68.19763, -9999) | src 0x420 base 0x3f4 insns 264/253
NWC24DeleteDlTask | shared ownership and validation helpers | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.o
AddTaskInternal | shared ownership and validation helpers | (66.2394, -9999) | src 0x5e4 base 0x644 insns 377/401

Additional Store/Delete trials: reconstructed file helpers (91.27451%, 105/102; 91.28319%,109/113), captured entry pointer and reloaded original identifier (99.70588%,102/102;99.159294%,113/113), widened seek count (Store100%), scoped clear helper (Delete100%). Explicit NO_INLINE declarations prevent these functions from being auto-inlined into Update/AddTaskInternal; all 30 functions were remeasured after these changes.

Remaining:

NWC24InitDlTask 89.36806%: validation, branch shape and instruction count; src 0x234 base 0x240 insns 141/144.
NWC24SetDlInterval 99.89796%: register allocation; src 0x24c base 0x24c insns 147/147.
NWC24SetDlUrl 99.95413%: one error branch destination; src 0x1b4 base 0x1b4 insns 109/109.
NWC24SetDlFlags 98.9011%: validation, branch shape and instruction count; src 0x168 base 0x16c insns 90/91.
NWC24IterateDlTask 81.177216%: validation, branch shape and instruction count; src 0x128 base 0x13c insns 74/79.
NWC24IterateDlTaskEx 85.06896%: validation, branch shape and instruction count; src 0x234 base 0x244 insns 141/145.
NWC24UpdateDlTask 68.19763%: validation, branch shape and instruction count; src 0x420 base 0x3f4 insns 264/253.
NWC24DeleteDlTask 85.75238%: validation, branch shape and instruction count; src 0x18c base 0x1a4 insns 99/105.
NWC24AddDlTask 67.46154%: validation, branch shape and instruction count; src 0x1c4 base 0x23c insns 113/143.
NWC24GetDlTask 99.728264%: register allocation; src 0x170 base 0x170 insns 92/92.
NWC24PurgeOldestDlTask 72.3125%: validation, branch shape and instruction count; src 0x25c base 0x2c0 insns 151/176.
NWC24ManageDlTaskListForMenu 73.585526%: validation, branch shape and instruction count; src 0x20c base 0x260 insns 131/152.
NWC24ExtendDlTaskList 99.85401%: register allocation; src 0x224 base 0x224 insns 137/137.
NWC24iCheckDlHeaderConsistency 53.9717%: validation, branch shape and instruction count; src 0x270 base 0x350 insns 156/212.
NWC24iCreateDlTaskList 99.62406%: register allocation; src 0x214 base 0x214 insns 133/133.
NWC24iLoadDlHeader 97.9%: seek/read error join (four instructions differ); src 0x190 base 0x190 insns 100/100.
AddTaskInternal 66.2394%: validation, branch shape and instruction count; src 0x5e4 base 0x644 insns 377/401.

Final object: {'fuzzy_match_percent': 83.35883, 'total_code': '12496', 'matched_code': '2020', 'matched_code_percent': 16.165173, 'total_data': '80', 'matched_data': '80', 'matched_data_percent': 100.0, 'total_functions': 30, 'matched_functions': 13, 'matched_functions_percent': 43.333332, 'total_units': 1}
