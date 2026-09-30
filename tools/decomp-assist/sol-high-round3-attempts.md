# Matching round 3

Baseline 91e65d76. Data already 100% in the three priority units; preserve all pools. Closest functions first within NWC24Download, then tiCellPhone, then pf_dir.

libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 1-wide-entry-index | objdiff 99.523810% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 2-late-task-view | objdiff 99.727890% | insns 147/147 | positional diffs 8 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 3-distinct-entry-id | objdiff 99.897960% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 1-independent-reload-result | objdiff 99.051094% | insns 138/137 | positional diffs 18 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 2-split-write-result | objdiff 96.934300% | insns 141/137 | positional diffs 20 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 3-loop-countdown-condition | objdiff 98.905110% | insns 138/137 | positional diffs 20 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 1-read-operation-scope | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 2-independent-close-status | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 3-task-id-wide-seek-view | objdiff 99.130430% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 1-typed-size-and-clear-cursor | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 2-countdown-loop | objdiff 95.781950% | insns 136/133 | positional diffs 130 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 3-inner-header-initialization | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 1-id-pair-array | objdiff 98.923615% | insns 144/144 | positional diffs 31 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 2-type-flag-before-fields | objdiff 89.090280% | insns 144/144 | positional diffs 61 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 3-direct-typed-task-lifetime | objdiff 98.923615% | insns 144/144 | positional diffs 31 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 1-task-view-before-parameter-aliases | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 2-task-storage-lifetime-nested | objdiff 98.679245% | insns 212/212 | positional diffs 7 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 3-unsigned-repair-cursor | objdiff 94.830185% | insns 206/212 | positional diffs 204 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 1-reversed-comparison-operands | objdiff 98.034485% | insns 145/145 | positional diffs 17 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 2-found-before-entry-output | objdiff 98.034485% | insns 145/145 | positional diffs 17 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 3-signed-sort-direction | objdiff 98.034485% | insns 145/145 | positional diffs 17 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 1-cached-entry-limits | objdiff 97.552444% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 2-universal-time-success-scope | objdiff 96.783220% | insns 145/143 | positional diffs 139 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 3-header-check-expanded-with-status | objdiff 96.538460% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 1-top-tested-entry-loop | objdiff 93.544304% | insns 79/79 | positional diffs 20 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 2-loop-check-helper-header-reload | objdiff 93.544304% | insns 79/79 | positional diffs 20 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 3-increment-loop-condition | objdiff 92.531650% | insns 78/79 | positional diffs 50 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 1-read-task-unaliased-removal | objdiff 96.743420% | insns 150/152 | positional diffs 36 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 2-positive-read-status-scope | objdiff 89.486840% | insns 150/152 | positional diffs 147 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 3-max-count-load-expanded | objdiff 94.736840% | insns 151/152 | positional diffs 137 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 1-retry-status-before-loop | objdiff 74.865616% | insns 295/253 | positional diffs 291 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 2-separate-access-status-after-time | objdiff 93.877470% | insns 249/253 | positional diffs 249 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 3-retry-result-do-loop | objdiff 91.090910% | insns 248/253 | positional diffs 250 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 1-retry-allocation-until-task-assigned | objdiff 71.753120% | insns 398/401 | positional diffs 319 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 2-find-status-success-or-full | objdiff 93.578550% | insns 397/401 | positional diffs 328 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 3-explicit-task-null-validation | objdiff 70.316710% | insns 401/401 | positional diffs 383 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 1-candidate-check-with-in-loop-call | objdiff 84.312500% | insns 167/176 | positional diffs 86 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 2-read-positive-result-branch | objdiff 85.204544% | insns 170/176 | positional diffs 166 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 3-initialize-bounds-before-flags | objdiff 84.363640% | insns 171/176 | positional diffs 166 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 4-entry-pointer-spans-division | objdiff 96.122450% | insns 142/147 | positional diffs 33 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 1-pane-record-pointer | objdiff 99.819820% | insns 333/333 | positional diffs 11 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 2-pane-record-before-construction | objdiff 91.141140% | insns 329/333 | positional diffs 281 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 3-inner-animation-record | BUILD FAILED; see saved build output
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 1-retain-event-record-through-trigger | objdiff 99.670090% | insns 682/682 | positional diffs 37 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 2-trigger-state-before-name | objdiff 99.384160% | insns 682/682 | positional diffs 38 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 3-scoped-keyset-pointer | objdiff 99.670090% | insns 682/682 | positional diffs 37 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 1-label-before-name-lifetime | objdiff 98.526120% | insns 536/536 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 2-retain-current-keyset-for-label | objdiff 97.460820% | insns 533/536 | positional diffs 411 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3-toggle-name-loop-cursor | objdiff 98.522385% | insns 536/536 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 3-inner-animation-record | objdiff 97.897896% | insns 333/333 | positional diffs 18 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 1-index-advance-before-countdown | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 2-next-entry-lifetime | objdiff 99.681160% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 3-two-typed-cursors | objdiff 88.608696% | insns 64/69 | positional diffs 67 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 1-scope-cluster-write-index | objdiff 99.649470% | insns 562/562 | positional diffs 36 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 2-dot-record-fields-explicit | objdiff 99.455510% | insns 562/562 | positional diffs 58 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 3-separate-long-name-count-value | objdiff 98.108540% | insns 564/562 | positional diffs 220 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 1-shared-update-return | objdiff 98.336000% | insns 625/625 | positional diffs 264 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 2-narrow-entry-offset-arithmetic | objdiff 97.808000% | insns 628/625 | positional diffs 540 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 3-directory-open-loop-field-cursor | objdiff 97.476800% | insns 628/625 | positional diffs 539 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 1-ancestry-top-check-and-shared-stop | objdiff 97.218704% | insns 629/631 | positional diffs 558 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 2-byte-long-name-offset | objdiff 97.226620% | insns 639/631 | positional diffs 563 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 3-directory-record-pointer-for-ancestry | objdiff 96.890650% | insns 629/631 | positional diffs 558 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 4-parameter-order-and-post-repair-success | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 4-count-conversion-scoped-around-legacy-header | objdiff 95.454544% | insns 145/143 | positional diffs 84 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 4-positive-allocation-status-first | objdiff 93.024940% | insns 397/401 | positional diffs 328 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 4-ancestry-shared-bottom-test | objdiff 96.973060% | insns 636/631 | positional diffs 563 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 5-ancestry-loop-with-explicit-top-exit | BUILD FAILED; see saved build output
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 6-restore-ancestry-to-top-loop-with-byte-offset | objdiff 96.973060% | insns 636/631 | positional diffs 563 | regressions 0

Audit: PFDIR_p_move trials 1 and 3 removed the initial root check and are excluded from the attempt count. Only equivalent ancestry variants retained; trial 2 restores the root check. Revisited functions now measure the current source before selecting a better result.
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 7-explicit-root-exit-before-search | objdiff 98.510300% | insns 635/631 | positional diffs 562 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 8-cached-ancestry-next-cluster | objdiff 97.028530% | insns 635/631 | positional diffs 563 | regressions 0

Priority-unit review: pools and every data section remain 100%; all twenty open functions have at least three successful body variants (failed builds and non-equivalent ancestry trials excluded). Changes retained: iterator tie comparison, unaliased menu removal, shared rename return, equivalent move root-exit loop. Next: MsgCommit pool first.
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | 1-board-flags-local-lifetimes | objdiff 99.891174% | insns 827/827 | positional diffs 18 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | 2-plain-text-error-positive-scope | objdiff 99.891174% | insns 827/827 | positional diffs 18 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | 3-separate-body-result-and-board-values | objdiff 99.915360% | insns 827/827 | positional diffs 14 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | WriteMIMEAttachHeader | 1-order-capacity-sum-left-to-right | objdiff 94.673910% | insns 92/92 | positional diffs 14 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | WriteMIMEAttachHeader | 2-separate-header-capacity-local | objdiff 97.500000% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | WriteMIMEAttachHeader | 3-balanced-length-sum | objdiff 97.282610% | insns 92/92 | positional diffs 8 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | CheckMsgBoxSpace | 1-combine-base64-size-increment-last | objdiff 85.573990% | insns 223/223 | positional diffs 73 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | CheckMsgBoxSpace | 2-retain-attachment-base64-and-lines | objdiff 79.372200% | insns 223/223 | positional diffs 103 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | CheckMsgBoxSpace | 3-unsigned-attachment-cursor | objdiff 78.573990% | insns 214/223 | positional diffs 213 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | data1-global-loopback-definition-after-functions | objdiff 99.915360% | insns 827/827 | positional diffs 14 | regressions 0
data1-global-loopback-definition-after-functions sections: [{'name': '.bss', 'size': '64', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '680', 'metadata': {}}, {'name': '.sbss', 'size': '8', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '152', 'fuzzy_match_percent': 18.765432, 'metadata': {}}, {'name': '.text', 'size': '8532', 'fuzzy_match_percent': 98.442566, 'metadata': {}}]
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | data2-content-format-definitions-after-writers | objdiff 99.915360% | insns 827/827 | positional diffs 14 | regressions 0
data2-content-format-definitions-after-writers sections: [{'name': '.bss', 'size': '64', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '680', 'metadata': {}}, {'name': '.sbss', 'size': '8', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '152', 'fuzzy_match_percent': 11.358025, 'metadata': {}}, {'name': '.text', 'size': '8532', 'fuzzy_match_percent': 98.442566, 'metadata': {}}]
libs/RevoEX/src/nwc24/NWC24MsgCommit | NWC24CommitMsgInternal | data3-subject-field-owned-line-ending | objdiff 99.915360% | insns 827/827 | positional diffs 14 | regressions 0
data3-subject-field-owned-line-ending sections: [{'name': '.bss', 'size': '64', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '680', 'metadata': {}}, {'name': '.sbss', 'size': '8', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '152', 'fuzzy_match_percent': 18.765432, 'metadata': {}}, {'name': '.text', 'size': '8532', 'fuzzy_match_percent': 98.442566, 'metadata': {}}]
libs/RevoEX/src/nwc24/NWC24Mime | CopyWithoutLinearWhiteSpaces | 1-hoist-capacity-limit | objdiff 100.000000% | insns 73/73 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | CopyWithoutLinearWhiteSpaces | 2-loop-character-with-output-length-scope | objdiff 99.109590% | insns 73/73 | positional diffs 13 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | CopyWithoutLinearWhiteSpaces | 3-signed-output-offset | objdiff 98.561646% | insns 73/73 | positional diffs 17 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 1-split-null-guards-and-consumed-pointer-check | objdiff 94.296295% | insns 134/135 | positional diffs 102 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 2-preserve-leading-marker-pointer | objdiff 94.148150% | insns 133/135 | positional diffs 102 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 3-second-marker-index-result | objdiff 86.703705% | insns 137/135 | positional diffs 104 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 1-signed-remaining-size-and-byte-terminator | objdiff 88.423910% | insns 95/92 | positional diffs 89 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 2-retain-input-and-output-size-values | objdiff 92.500000% | insns 95/92 | positional diffs 74 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 3-removed-redundant-null-check-with-signed-remaining | objdiff 91.576090% | insns 92/92 | positional diffs 59 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | QDecode | 1-byte-result-and-independent-hex-validity | objdiff 92.609590% | insns 147/146 | positional diffs 113 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | QDecode | 2-whitespace-next-byte-cursor | objdiff 94.130135% | insns 146/146 | positional diffs 59 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | QDecode | 3-advance-main-input-during-decode | objdiff 92.609590% | insns 147/146 | positional diffs 113 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 1-leading-marker-kept-through-second-scan | objdiff 81.190475% | insns 81/84 | positional diffs 61 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 2-second-marker-pointer-advancing-loop | objdiff 79.095240% | insns 85/84 | positional diffs 59 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 3-copy-positive-size-branch | objdiff 92.380950% | insns 83/84 | positional diffs 56 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 1-use-real-marker-pointer | objdiff 79.188890% | insns 178/180 | positional diffs 168 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 2-delimiter-derived-from-offset | objdiff 79.661110% | insns 179/180 | positional diffs 168 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 3-signed-whitespace-prefix-capacity | BUILD FAILED; see saved build output
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 1-charset-length-before-capacity-test | objdiff 71.681816% | insns 176/198 | positional diffs 168 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 2-delimiter-character-lived-through-word | objdiff 71.681816% | insns 176/198 | positional diffs 168 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 3-overflow-result-restore-at-end | objdiff 69.363640% | insns 176/198 | positional diffs 156 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 4-native-int-whitespace-capacity | objdiff 79.661110% | insns 179/180 | positional diffs 168 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectQP | 1-signed-second-buffer-capacity | objdiff 99.548615% | insns 144/144 | positional diffs 12 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectQP | 2-scope-source-offset-after-encoding | BUILD FAILED; see saved build output
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectQP | 3-loop-offset-increment-after-length | objdiff 98.020836% | insns 144/144 | positional diffs 16 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24SetMsgSubjectAndTextPublic | 1-scoped-private-message-for-protection | objdiff 97.210526% | insns 190/190 | positional diffs 65 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24SetMsgSubjectAndTextPublic | 2-char-work-address-view | objdiff 98.236840% | insns 190/190 | positional diffs 65 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24SetMsgSubjectAndTextPublic | 3-output-subject-allocation-size-lived-after-conversion | objdiff 97.210526% | insns 190/190 | positional diffs 65 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 1-read-result-switch | objdiff 94.142860% | insns 70/70 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 2-scoped-read-result-switch | objdiff 94.142860% | insns 70/70 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 3-switch-and-original-capacity-after-charset-load | objdiff 93.857140% | insns 70/70 | positional diffs 9 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 1-two-read-result-switches | objdiff 92.115390% | insns 104/104 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 2-switched-read-results-and-signed-text-loop | objdiff 92.115390% | insns 104/104 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 3-switched-read-results-and-positive-conversion-status | BUILD FAILED; see saved build output
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 1-explicit-conversion-and-encode-switches | objdiff 84.257355% | insns 137/136 | positional diffs 121 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 2-signed-total-excluding-terminator | objdiff 93.433820% | insns 139/136 | positional diffs 130 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 3-output-capacity-scoped-per-conversion | objdiff 93.455880% | insns 139/136 | positional diffs 130 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectQP | 4-offset-only-in-encoded-word-case | objdiff 98.715280% | insns 144/144 | positional diffs 29 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 4-single-case-switch-with-overflow-in-default | objdiff 97.142860% | insns 68/70 | positional diffs 28 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 4-read-overflow-tests-in-default-switch-arms | objdiff 96.153850% | insns 100/104 | positional diffs 64 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 5-switch-results-and-signed-source-loop | objdiff 96.153850% | insns 100/104 | positional diffs 64 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgField | 1-scope-mailbox-selection-after-protection | objdiff 98.921570% | insns 101/102 | positional diffs 84 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgField | 2-result-qualified-protection-check | objdiff 97.843140% | insns 102/102 | positional diffs 6 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgField | 3-selector-expanded-with-status-return | objdiff 96.892160% | insns 101/102 | positional diffs 81 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgFromAddr | 1-scoped-selector-view | objdiff 98.804344% | insns 91/92 | positional diffs 66 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgFromAddr | 2-sender-address-typed-flags-local | objdiff 97.500000% | insns 92/92 | positional diffs 56 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgFromAddr | 3-supported-type-switch | objdiff 97.608696% | insns 92/92 | positional diffs 6 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgSubject | 1-private-message-view-before-read-only-loads | objdiff 98.658540% | insns 81/82 | positional diffs 65 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgSubject | 2-protection-status-switch | objdiff 97.317070% | insns 82/82 | positional diffs 6 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgSubject | 3-close-result-separate-scope | objdiff 97.195120% | insns 80/82 | positional diffs 65 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgAttached | 1-decoded-size-success-switch | objdiff 96.373630% | insns 90/91 | positional diffs 75 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgAttached | 2-attachment-record-after-mailbox-open | objdiff 96.043950% | insns 89/91 | positional diffs 75 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | NWC24ReadMsgAttached | 3-independent-read-and-close-lifetimes | objdiff 94.890110% | insns 88/91 | positional diffs 75 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | ReadMsgTextInternal | 1-success-switch-in-header-reads | objdiff 91.516850% | insns 180/178 | positional diffs 158 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | ReadMsgTextInternal | 2-capacity-limit-and-overflow-scope | objdiff 91.516850% | insns 175/178 | positional diffs 163 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgRead | ReadMsgTextInternal | 3-output-encoding-initialize-before-buffer | objdiff 93.089890% | insns 178/178 | positional diffs 152 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 5-nested-single-status-switches | objdiff 95.571430% | insns 69/70 | positional diffs 29 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 6-nested-single-status-switches | objdiff 94.038460% | insns 102/104 | positional diffs 64 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgTextPublic | 6-overflow-if-else-inside-default | objdiff 97.142860% | insns 68/70 | positional diffs 28 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24ReadMsgSubjectPublic | 7-overflow-if-else-inside-default | objdiff 96.153850% | insns 100/104 | positional diffs 64 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 4-only-zero-case-with-overflow-default | objdiff 93.308820% | insns 135/136 | positional diffs 77 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 5-overflow-before-default-switch | objdiff 93.308820% | insns 135/136 | positional diffs 77 | regressions 0
libs/RevoEX/src/nwc24/NWC24MsgSubject | NWC24iSetMsgSubjectBase64 | 6-distinct-available-and-encoded-lengths | objdiff 93.286766% | insns 135/136 | positional diffs 79 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 4-read-helper-inlined-at-public-entry | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 4-header-at-initialization-block-only | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 4-wide-index-for-entry-clearing | objdiff 99.087590% | insns 136/137 | positional diffs 48 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 4-rederive-all-concatenation-and-failure-blocks | objdiff 95.626260% | insns 192/198 | positional diffs 155 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 5-failure-return-with-scoped-character | objdiff 95.626260% | insns 192/198 | positional diffs 155 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 6-final-success-test-through-switch | objdiff 95.626260% | insns 192/198 | positional diffs 155 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 7-real-concatenation-helpers-with-status-returns | objdiff 95.126260% | insns 202/198 | positional diffs 184 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 8-encoding-helper-inline-character-validity | objdiff 95.126260% | insns 202/198 | positional diffs 184 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 9-spell-out-final-overflow-precedence | objdiff 95.126260% | insns 202/198 | positional diffs 184 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | EncodeWord | 10-format-specific-prefix-separator-suffix-helpers | objdiff 100.000000% | insns 198/198 | positional diffs 0 | regressions 0

EncodeWord control-flow evidence: rederived the prefix, charset, separator, encoding, text, suffix, and final overflow blocks from build/43U/asm/libs/RevoEX/src/nwc24/NWC24Mime.s. Each append helper has independent success/overflow returns. Generic literal arguments survived strlen in a saved register, adding four pointer moves; format-specific helpers emit the same ordinary literals at their uses and remove those moves. Attempt 10 is 198/198 instructions, zero ctxdiff differences, objdiff 100%; data remains 88/88. The target unconditionally writes decodedSizeOut on the final text/suffix errors and encodedSize on final success; preserved those target operations. Quick gate: /tmp/sol-high-round3-encode-gate.txt, GATE PASS, regressions/forbidden/readability all zero.
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 4-remove-duplicate-validation-and-use-signed-input-bytes | objdiff 99.130430% | insns 92/92 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 5-signed-input-with-input-size-before-capacity-in-loop | objdiff 99.456520% | insns 92/92 | positional diffs 8 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 6-signed-char-input-output-and-result-type | objdiff 99.130430% | insns 92/92 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 4-second-marker-cursor-with-prefix-preserved | objdiff 90.833336% | insns 83/84 | positional diffs 62 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 5-second-marker-cursor-with-prefix-preserved | objdiff 91.071430% | insns 83/84 | positional diffs 61 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 6-second-marker-cursor-with-prefix-preserved | objdiff 90.833336% | insns 83/84 | positional diffs 62 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 4-second-marker-search-with-recomputed-found-position | objdiff 93.925930% | insns 134/135 | positional diffs 99 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 5-second-marker-search-with-recomputed-found-position | objdiff 94.000000% | insns 134/135 | positional diffs 98 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 6-second-marker-search-with-recomputed-found-position | objdiff 94.370370% | insns 134/135 | positional diffs 100 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 7-output-initialized-before-input-and-length | objdiff 99.293480% | insns 92/92 | positional diffs 9 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 8-output-char-view-before-input-length | objdiff 99.293480% | insns 92/92 | positional diffs 9 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | NWC24DecodeMIMEHeaderFieldBody | 9-capacity-before-input-length | objdiff 99.239130% | insns 92/92 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 7-marker-helper-with-prefix-and-separate-success-return | objdiff 97.261900% | insns 84/84 | positional diffs 35 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 8-caller-increments-prefix-after-marker-helper | objdiff 97.261900% | insns 84/84 | positional diffs 35 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractCharset | 9-copy-output-length-reuse-after-scan | objdiff 94.404760% | insns 85/84 | positional diffs 47 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | ExtractEncodedText | 7-marker-offset-helper-with-independent-success-return | objdiff 98.148150% | insns 135/135 | positional diffs 44 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 4-rederive-marker-encoding-and-success-output-blocks | objdiff 97.694440% | insns 180/180 | positional diffs 67 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 5-decode-lengths-before-marker-local | objdiff 97.694440% | insns 180/180 | positional diffs 67 | regressions 0
libs/RevoEX/src/nwc24/NWC24Mime | DecodeWord | 6-unsigned-consumed-and-prefix-length | objdiff 97.694440% | insns 180/180 | positional diffs 67 | regressions 0

DecodeWord control-flow evidence: target marker search retains the marker literal across strlen/strncmp, returns NULL only after exhausting the inclusive bound, and uses an encoding extraction helper with explicit invalid/success status. Replaced the integer pointer representation with char*, separated that helper, preserved output initialization and unconditional final decodedSize store from the target. The plain prefix branch calculates length before initializing its copy capacity. Current DecodeWord: 180/180, register-normalized instruction sequence identical, 67 register differences. ExtractCharset and ExtractEncodedText now reproduce the second search's recomputed found position and separate exhaustion return through real marker helpers; instruction counts 84/84 and 135/135, normalized sequences identical. Header body now has the single target NULL guard and signed char input; 92/92, only eight saved-register differences. Quick MIME gate /tmp/sol-high-round3-decode-gate.txt: GATE PASS; exact code 3576/6124, fuzzy 98.82299, data 88/88, regressions/forbidden/readability zero.
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 4-load-animation-key-from-table-at-attachment | objdiff 99.789790% | insns 333/333 | positional diffs 12 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 5-retain-animation-presence-as-bool | objdiff 95.240240% | insns 339/333 | positional diffs 277 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 6-inner-animation-type-enum-before-resource-creation | objdiff 96.396390% | insns 335/333 | positional diffs 209 | regressions 0

Final audit excludes failed builds, PFDIR_p_move ancestry trials 1/3, data-only trials, and three source bodies already tried in round 2 (keyboard create trial 3, AddDlTask trial 2, AddTaskInternal trial 1). New keyboard create trials 4/5/6 cover that duplicate. Every one of the forty initially open functions has at least three distinct successful NEW body variants, measured from saved sources with whitespace normalized; none remains untried. Keyboard source and all shared-header guard sides are unchanged this round. Matching sibling libs/RevoEX/src/vf/fatfs/pf_dir.c was diffed again against the owned file; its later traversal/layout differences do not resolve the four remaining bodies. Six units retain 100% data; MsgCommit data remains open with raw CRLF and alignment differences recorded above, without added padding or storage-size tricks.

Final full (non-quick) gate over all seven units: /tmp/sol-high-round3-final-gate.txt, GATE PASS. Fresh clean build and expected DOL SHA1; no regressions, forbidden additions or readability warnings. MIME gained two instruction-exact functions, 9/16 -> 11/16, exact code 2492 -> 3576/6124, fuzzy 90.243630 -> 98.822990. Priority exact counts remain 17/30, 83/86, 34/38; Download and pf_dir fuzzy improved. Every gate block, before/after metrics, all 38 remaining functions with measured counts/causes, data uncertainty, files and code commits are preserved in sol-high-round3-report.md. Post-build ctxdiff verified both new exact functions at zero differences. ReadMsgTextInternal's final clean-build count is 176/178, superseding the earlier positional-count note.
