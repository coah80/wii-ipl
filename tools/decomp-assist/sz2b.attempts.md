# sz2b Chinese jump-table data round

Worktree data-d4, branch agent/w1004/sz2b, baseline 99ba99ee. Read AGENTS.md, sz2.attempts.md, common.md, levers.md and ezi-insight.md before trials. Existing untracked attempts logs remain untouched. Only zi8InternalGetZH is assigned for source work. The two other fuzzy functions are outside this data task and retain their earlier logged trials.

Acceptance: zi8cgetc matched data must increase without any function percentage or code/data/link regression. Keep 10676 instructions, readable C, empty matching pools and the retail DOL SHA1. No flags, shared headers, symbols, other source units or jump-table payloads may change.

Initial ninja passed. Fresh report: code 4168/47816, data 144/536, exact functions 5/8. zi8InternalGetZH 96.27482%, ZiMatchZHSpelling 98.80165%, Zi8GetElementCount 99.347824%. Case offsets 11/98. Tables at .data+0, +0x2c, +0x58, +0xf8 have respectively 0/11, 11/11, 0/40, 0/36 matching entries and shifts +8, 0, +4, +4 bytes.

Baseline ctxdiff has 9311 differing instructions with equal sizes 0xa6d0. A register-normalized alignment finds only 30 insertion/deletion sites, almost all return-copy moves. The first extra instruction is source +0x58c, mr r11,r3 after Zi8GetZHCharSet. Target +0x58c narrows r3 directly. This +4 persists through both phonetic tables. It balances at target +0x200c, a return-copy move after Zi8IsCharacter. The .data+0x2c table already aligns. Two extra return-copy moves after it, source +0x56d8 and +0x6ebc, account for the +8 in .data+0. Target/source context is saved in build/sz2b/alignment.txt and asm JSON files. No missing store is present in this alignment, so no never-read store is justified.

Lever review: this C unit uses -inline off -opt off, so static inline helpers would add calls and cannot preserve these switch offsets. Prior charset-switch, declaration-order and generic workspace trials are recorded in sz2.attempts.md and will not be repeated. This round starts with typed expressions, compound assignments and target-proven statement forms around the extra moves.

Expanded byte shift to reproduce the target narrowing without a compound assignment.
Trial: {"trial": "charset-expand-shift", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Expanded the three independent option-mask updates.
Trial: {"trial": "get-options-expand-masks", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Mark the read-only fuzzy-pair field views const.
Trial: {"trial": "work-const-fuzzy-views", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Make charset truncation explicit at its byte assignment.
Trial: {"trial": "charset-byte-shift", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use the library unsigned-long word type at the mismatched call result, distinct from the earlier native-int trial.
Trial: {"trial": "charset-long-return", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try a const options view for read-only request configuration; reject if downstream mutable helper parameters require it.
Trial: {"trial": "options-const-view", "error": "build failed"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-guard-break", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-separate-guards", "score": 95.899216, "insns": 10675, "data": "72", "tables": [[0, 0, 11, [4]], [44, 11, 11, [0]], [88, 0, 40, [12]], [248, 0, 36, [12]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.899216]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-nested-bit-guard", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-negated-ternary", "score": 95.78466, "insns": 10682, "data": "24", "tables": [[0, 0, 11, [24]], [44, 0, 11, [16]], [88, 0, 40, [28]], [248, 0, 36, [28]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.78466]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-logical-not", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Re-express the simplified-character charset guard with the same short-circuit calls and stores.
Trial: {"trial": "charset-subtract-bit", "score": 96.27426, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.27426]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Target proof: +0x8de0 and +0x8e9c narrow Zi8GetPCode to 16 bits before mask tests. Existing source lacks these two conversions. The masks are already halfwords, so narrowing preserves the result.
Trial: {"trial": "phonetic-code-halfword-0", "score": 96.23595, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [12]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.23595]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Target proof: +0x8de0 and +0x8e9c narrow Zi8GetPCode to 16 bits before mask tests. Existing source lacks these two conversions. The masks are already halfwords, so narrowing preserves the result.
Trial: {"trial": "phonetic-code-halfword-1", "score": 96.23642, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [12]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.23642]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Target proof: +0x8de0 and +0x8e9c narrow Zi8GetPCode to 16 bits before mask tests. Existing source lacks these two conversions. The masks are already halfwords, so narrowing preserves the result.
Trial: {"trial": "phonetic-code-halfword-01", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Target proof: +0x1cb8 stores the table result at 0xfc, +0x1cbc reloads 0xfc, +0x1cc0 stores 0xf8. Separate componentCursor initialization from the componentTable snapshot to reproduce that load.
Trial: {"trial": "component-cursor-separate-copy", "score": 95.99054, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [4]], [44, 0, 11, [8]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.99054]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Target proof: +0x1cb8 stores the table result at 0xfc, +0x1cbc reloads 0xfc, +0x1cc0 stores 0xf8. Separate componentCursor initialization from the componentTable snapshot to reproduce that load.
Trial: {"trial": "target-cursor-and-halfwords", "score": 96.090294, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [8]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.090294]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine adjacent resets of related flags with unchanged store order. These are live state fields, not padding or never-read additions. Measure with the target-proven phonetic halfword conversions.
Trial: {"trial": "charset-pair-reset", "score": 96.10472, "insns": 10675, "data": "24", "tables": [[0, 0, 11, [-12]], [44, 0, 11, [-16]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.10472]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine adjacent resets of related flags with unchanged store order. These are live state fields, not padding or never-read additions. Measure with the target-proven phonetic halfword conversions.
Trial: {"trial": "completion-pair-reset", "score": 96.42235, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine adjacent resets of related flags with unchanged store order. These are live state fields, not padding or never-read additions. Measure with the target-proven phonetic halfword conversions.
Trial: {"trial": "count-pair-reset", "score": 96.42329, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine adjacent resets of related flags with unchanged store order. These are live state fields, not padding or never-read additions. Measure with the target-proven phonetic halfword conversions.
Trial: {"trial": "phrase-flags-reset", "score": 95.0473, "insns": 10673, "data": "24", "tables": [[0, 0, 11, [-20]], [44, 0, 11, [-28]], [88, 0, 40, [-8]], [248, 0, 36, [-8]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.0473]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use explicit library types at the engine boundary. No shared header, function definition or other unit is changed.
Trial: {"trial": "phonetic-code-return-halfword", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use explicit library types at the engine boundary. No shared header, function definition or other unit is changed.
Trial: {"trial": "secondary-match-return-byte", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use explicit library types at the engine boundary. No shared header, function definition or other unit is changed.
Trial: {"trial": "secondary-match-return-native", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use explicit library types at the engine boundary. No shared header, function definition or other unit is changed.
Trial: {"trial": "workspace-typed-formal", "score": 96.27482, "insns": 10676, "data": "144", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine target halfword return type, response reset and separate table snapshot.
Trial: {"trial": "response-reset-cursor-copy", "score": 96.07531, "insns": 10677, "data": "72", "tables": [[0, 11, 11, [0]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.07531]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine the two related range-bound resets before the final component switch; preserve store order and live values.
Trial: {"trial": "cangjie-range-reset", "score": 96.04955, "insns": 10675, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-12]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.04955]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "index-library-signed", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "phase-library-signed", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "output-limit-library-signed", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "pattern-library-word", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "const-input-elements", "score": 95.74691, "insns": 10689, "data": "24", "tables": [[0, 0, 11, [36]], [44, 0, 11, [24]], [88, 0, 40, [12]], [248, 0, 36, [12]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.74691]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Use a library-width scalar or const read view where the target width and read-only use support it; keep the proved Zi8GetPCode halfword return.
Trial: {"trial": "const-phonetic-patterns", "score": 96.492134, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-separate-1297", "score": 96.41814, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-separate-1431", "score": 96.41766, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-postadvance-1532", "score": 96.234825, "insns": 10683, "data": "24", "tables": [[0, 0, 11, [20]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.234825]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-postadvance-1576", "score": 96.266205, "insns": 10682, "data": "24", "tables": [[0, 0, 11, [16]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.266205]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-postadvance-1637", "score": 96.15146, "insns": 10681, "data": "24", "tables": [[0, 0, 11, [12]], [44, 11, 11, [0]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.15146]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-postadvance-1817", "score": 95.96974, "insns": 10681, "data": "24", "tables": [[0, 0, 11, [12]], [44, 11, 11, [0]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.96974]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Try separate or postincrement ring advancement. For every byte value, preincrement then reset at 64 and postincrement then reset at 63 leave the same final index, including 255 wrapping to zero. No pointer or callback occurs between these operations.
Trial: {"trial": "ring-postadvance-1878", "score": 95.711784, "insns": 10680, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.711784]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep helper calls and live stores, varying whether the following test consumes the assigned value or reloads the local. No new local, call or store is introduced.
Trial: {"trial": "pud-separate-result", "score": 96.24906, "insns": 10679, "data": "72", "tables": [[0, 0, 11, [12]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.24906]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep helper calls and live stores, varying whether the following test consumes the assigned value or reloads the local. No new local, call or store is introduced.
Trial: {"trial": "user-character-test-assignment", "score": 96.41766, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep helper calls and live stores, varying whether the following test consumes the assigned value or reloads the local. No new local, call or store is introduced.
Trial: {"trial": "pud-and-user-character-assignment", "score": 96.24345, "insns": 10679, "data": "72", "tables": [[0, 0, 11, [12]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.24345]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Change the live component count update using ordinary compound/expanded arithmetic; preserve the resulting count and final index.
Trial: {"trial": "component-count-subtract", "score": 96.05751, "insns": 10677, "data": "72", "tables": [[0, 11, 11, [0]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.05751]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Change the live component count update using ordinary compound/expanded arithmetic; preserve the resulting count and final index.
Trial: {"trial": "component-count-expanded", "score": 96.05751, "insns": 10677, "data": "72", "tables": [[0, 11, 11, [0]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.05751]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Change the live component count update using ordinary compound/expanded arithmetic; preserve the resulting count and final index.
Trial: {"trial": "component-last-index", "score": 99.231735, "insns": 10680, "data": "72", "tables": [[0, 0, 11, [16]], [44, 0, 11, [12]], [88, 0, 40, [-4]], [248, 0, 36, [-4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1523", "score": 95.988945, "insns": 10677, "data": "24", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.988945]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1581", "score": 95.99888, "insns": 10676, "data": "96", "tables": [[0, 0, 11, [-8]], [44, 0, 11, [-8]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 95.99888]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1641", "score": 96.180595, "insns": 10678, "data": "24", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.180595]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1678", "score": 96.18612, "insns": 10679, "data": "24", "tables": [[0, 0, 11, [4]], [44, 11, 11, [0]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.18612]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1709", "score": 96.138535, "insns": 10675, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.138535]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1745", "score": 96.2855, "insns": 10674, "data": "72", "tables": [[0, 0, 11, [-8]], [44, 0, 11, [-8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1822", "score": 96.27754, "insns": 10675, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-12]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Store the separator, then test the preincremented output cursor. Same output bytes, cursor, and early-exit state; this is the proven eZiText increment-and-limit lever.
Trial: {"trial": "output-limit-increment-1882", "score": 96.07859, "insns": 10674, "data": "72", "tables": [[0, 0, 11, [-8]], [44, 0, 11, [-12]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.07859]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Reconstruct the component-table last index and remaining count. Both equal the original halfword count minus one. The prior calculate-index-before-decrement trial raised engine matching above 99%, so compare the readable ways to express this relationship.
Trial: {"trial": "component-index-predecrement", "score": 96.331024, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Reconstruct the component-table last index and remaining count. Both equal the original halfword count minus one. The prior calculate-index-before-decrement trial raised engine matching above 99%, so compare the readable ways to express this relationship.
Trial: {"trial": "component-index-postdecrement", "score": 99.28156, "insns": 10681, "data": "72", "tables": [[0, 0, 11, [20]], [44, 0, 11, [16]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Reconstruct the component-table last index and remaining count. Both equal the original halfword count minus one. The prior calculate-index-before-decrement trial raised engine matching above 99%, so compare the readable ways to express this relationship.
Trial: {"trial": "component-index-count-first", "score": 99.28653, "insns": 10681, "data": "72", "tables": [[0, 0, 11, [20]], [44, 0, 11, [16]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Reconstruct the component-table last index and remaining count. Both equal the original halfword count minus one. The prior calculate-index-before-decrement trial raised engine matching above 99%, so compare the readable ways to express this relationship.
Trial: {"trial": "component-index-assignment-first", "score": 96.07222, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [4]], [44, 0, 11, [8]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["zi8InternalGetZH", 96.27482, 96.07222]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Reconstruct the component-table last index and remaining count. Both equal the original halfword count minus one. The prior calculate-index-before-decrement trial raised engine matching above 99%, so compare the readable ways to express this relationship.
Trial: {"trial": "component-index-copy-first", "score": 96.46431, "insns": 10679, "data": "72", "tables": [[0, 0, 11, [12]], [44, 0, 11, [4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine the last-index expression with the target-proven separate table snapshot.
Trial: {"trial": "component-index-and-cursor-copy", "score": 98.931526, "insns": 10684, "data": "72", "tables": [[0, 0, 11, [24]], [44, 0, 11, [20]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Follow the 99.28% candidate through natural count/index update forms; preserve both halfword results.
Trial: {"trial": "component-index-postcombined", "score": 96.331024, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Follow the 99.28% candidate through natural count/index update forms; preserve both halfword results.
Trial: {"trial": "component-index-two-decrements", "score": 99.27716, "insns": 10682, "data": "72", "tables": [[0, 0, 11, [24]], [44, 0, 11, [20]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Follow the 99.28% candidate through natural count/index update forms; preserve both halfword results.
Trial: {"trial": "component-count-two-expressions", "score": 98.912796, "insns": 10684, "data": "72", "tables": [[0, 0, 11, [24]], [44, 0, 11, [20]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Follow the 99.28% candidate through natural count/index update forms; preserve both halfword results.
Trial: {"trial": "component-count-poststatement", "score": 99.28653, "insns": 10681, "data": "72", "tables": [[0, 0, 11, [20]], [44, 0, 11, [16]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-796", "score": 96.31669, "insns": 10685, "data": "24", "tables": [[0, 0, 11, [28]], [44, 0, 11, [24]], [88, 0, 40, [12]], [248, 0, 36, [12]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-930", "score": 98.137596, "insns": 10681, "data": "72", "tables": [[0, 0, 11, [20]], [44, 0, 11, [4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-1108", "score": 98.71834, "insns": 10682, "data": "72", "tables": [[0, 0, 11, [16]], [44, 0, 11, [16]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-1302", "score": 99.1183, "insns": 10679, "data": "72", "tables": [[0, 0, 11, [12]], [44, 0, 11, [8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-1360", "score": 98.52538, "insns": 10682, "data": "72", "tables": [[0, 0, 11, [24]], [44, 0, 11, [8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Apply the output cursor increment-and-limit form to the 99.28% candidate, before the middle switch. Preserve every output and early-exit value.
Trial: {"trial": "high-output-limit-1437", "score": 98.69267, "insns": 10677, "data": "72", "tables": [[0, 0, 11, [12]], [44, 0, 11, [8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Share the count-minus-one expression with both live halfword destinations and compare natural chain/compound assignment forms.
Trial: {"trial": "component-chained-subtraction", "score": 96.47387, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Share the count-minus-one expression with both live halfword destinations and compare natural chain/compound assignment forms.
Trial: {"trial": "component-compound-subtraction", "score": 96.47387, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Share the count-minus-one expression with both live halfword destinations and compare natural chain/compound assignment forms.
Trial: {"trial": "component-chained-last-index", "score": 96.47368, "insns": 10678, "data": "72", "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Share the count-minus-one expression with both live halfword destinations and compare natural chain/compound assignment forms.
Trial: {"trial": "component-counter-update-after", "score": 98.912796, "insns": 10684, "data": "72", "tables": [[0, 0, 11, [24]], [44, 0, 11, [20]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Both pre-middle-switch output-limit trials shortened that interval by two instructions each. Combine the two independent cursor updates and remeasure the whole function.
Trial: {"trial": "context-and-range-output-limits", "score": 98.531006, "insns": 10675, "data": "72", "tables": [[0, 0, 11, [4]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1524", "score": 97.253746, "insns": 10674, "data": "72", "tables": [[0, 0, 11, [-8]], [44, 0, 11, [-4]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1582", "score": 97.66223, "insns": 10679, "data": "24", "tables": [[0, 0, 11, [4]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1642", "score": 98.30096, "insns": 10673, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1679", "score": 98.37645, "insns": 10674, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1710", "score": 97.85041, "insns": 10673, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1746", "score": 98.15305, "insns": 10672, "data": "72", "tables": [[0, 0, 11, [-8]], [44, 0, 11, [-4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1823", "score": 98.549835, "insns": 10671, "data": "72", "tables": [[0, 0, 11, [-12]], [44, 0, 11, [-8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The current candidate aligns 87/98 cases, with only the last table one instruction late. Apply one more independent output-cursor limit form between the middle and last switches.
Trial: {"trial": "last-table-output-1883", "score": 97.95476, "insns": 10678, "data": "24", "tables": [[0, 0, 11, [4]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Expand two live-state resets after all switches into individual assignments, keeping store order. Measure their effect on the instruction deficit and case offsets; no new fields or stores are added.
Trial: {"trial": "tail-explicit-state-resets", "score": 96.82671, "insns": 10674, "data": "72", "tables": [[0, 11, 11, [0]], [44, 0, 11, [-8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-range-reset", "score": 96.69886, "insns": 10675, "data": "72", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-group-reset", "score": 97.40352, "insns": 10680, "data": "24", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-empty-count-predecrement", "score": 97.299736, "insns": 10679, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-empty-count-compound", "score": 98.36109, "insns": 10675, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-empty-count-separate", "score": 97.294586, "insns": 10679, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Tail-only live-state expression after all jump tables. Empty-count forms use the equivalent 16-bit underflow test. Separate assignments preserve all writes and exit states; no padding or extra state is introduced.
Trial: {"trial": "tail-byte-count-expanded", "score": 96.55358, "insns": 10682, "data": "72", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Combine the two live-state reset statements after the final switch, retaining the 98 aligned case offsets if register allocation permits.
Trial: {"trial": "tail-two-explicit-resets", "score": 96.72368, "insns": 10673, "data": "72", "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-8]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep the exhausted-counter condition and its decrement, checking explicit old-value types and the equivalent halfword underflow form.
Trial: {"trial": "tail-count-zero-left", "score": 98.37645, "insns": 10674, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep the exhausted-counter condition and its decrement, checking explicit old-value types and the equivalent halfword underflow form.
Trial: {"trial": "tail-count-unsigned-old", "score": 98.37645, "insns": 10674, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep the exhausted-counter condition and its decrement, checking explicit old-value types and the equivalent halfword underflow form.
Trial: {"trial": "tail-count-library-word-old", "score": 98.37645, "insns": 10674, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep the exhausted-counter condition and its decrement, checking explicit old-value types and the equivalent halfword underflow form.
Trial: {"trial": "tail-count-explicit-halfword-old", "score": 98.37645, "insns": 10674, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

Keep the exhausted-counter condition and its decrement, checking explicit old-value types and the equivalent halfword underflow form.
Trial: {"trial": "tail-count-expanded-underflow", "score": 98.36109, "insns": 10675, "data": "464", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The compound empty-count candidate has all 98 cases aligned and needs one instruction in the tail. Test one ordinary live-state update without any added state or no-op.
Trial: {"trial": "tail-candidate-count-compound", "score": 97.39416, "insns": 10681, "data": "24", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [8]], [248, 0, 36, [8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The compound empty-count candidate has all 98 cases aligned and needs one instruction in the tail. Test one ordinary live-state update without any added state or no-op.
Trial: {"trial": "tail-group-ordinal-compound", "score": 98.336266, "insns": 10676, "data": "536", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The compound empty-count candidate has all 98 cases aligned and needs one instruction in the tail. Test one ordinary live-state update without any added state or no-op.
Trial: {"trial": "tail-spelling-snapshot-separate", "score": 96.34854, "insns": 10681, "data": "72", "tables": [[0, 0, 11, [8]], [44, 0, 11, [4]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

The compound empty-count candidate has all 98 cases aligned and needs one instruction in the tail. Test one ordinary live-state update without any added state or no-op.
Trial: {"trial": "tail-pair-output-count-compound", "score": 98.32877, "insns": 10676, "data": "536", "tables": [[0, 11, 11, [0]], [44, 11, 11, [0]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}.

## Candidate selected for clean validation

The component last-index expression, the actual Zi8GetPCode halfword return type, and three output cursor increment-and-limit expressions align all 98 cases. That precursor has 10674 instructions and only 464 matched data bytes because its exception index has the wrong function size. Two live counter expressions in the tail restore the two instructions: halfword exhaustion uses `(candidateCount -= 1) == 0xFFFF`, and the phonetic-group ordinal uses `ordinalIndex += 1`. Trial tail-group-ordinal-compound reaches data 536/536, 10676 instructions, 98/98 aligned case entries and engine 98.336266%, with every other function percentage unchanged. Trial tail-pair-output-count-compound also passes these preliminary measurements but scores 98.32877%; it is not selected.

The retained source has seven focused edits, no new local, field, store, data definition, pragma, assembler, label or comment. The earlier response-field reset experiments are absent. The existing two smaller fuzzy functions and all other units are untouched.

Semantic review: Zi8GetPCode is defined with return type ziU16 in zi8match.c:886, and its eight existing call sites in this unit are within the owned engine. Computing componentIndex before decrementing componentCount yields the same two halfword values for all 65536 inputs, including zero. Each separator store uses the same old output index, then advances it before the same capacity check; output points to the caller buffer or the separate local countOutput array. For every 16-bit candidateCount value, decrement-and-test-0xFFFF takes the same exhaustion path as testing the predecrement value for zero and leaves the same count. The group ordinal compound addition is the same halfword increment. No never-read or uninitialized-value allowance is used.

These are readable source changes that improve table layout. They are not claimed to reproduce every instruction: the engine remains non-exact, and all five previously exact functions must pass again from the clean build.

## Final validation

99 compiled source trials and 1 rejected build trial are recorded above. Failed scratch-script assertions are not counted as compiled trials. Rejected variants remain only under build/sz2b. The source contains only the selected data-gain candidate.

The final non-quick gate rebuilt the entire 43U target from a deleted build/43U directory and passed. A separate strict audit against the freshly built 99ba99ee baseline checked all 1027 units, all five code/data/link/exact metrics, every existing function name, and every function percentage. Zero regressions. The only changes are zi8cgetc matched data 144 -> 536 and zi8InternalGetZH 96.27482% -> 98.336266%.

Independent ELF checks: .data 392 bytes and all 98 resolved relocations exactly equal the target; .sbss2 8 bytes, .sdata2 16 bytes, extab 48 bytes, and extabindex 72 bytes with 12 resolved relocations also exactly equal. All 98 case offsets, first basic-block lengths and case spans match. Function size is 10676 instructions, unchanged. The five previously exact functions have identical instruction counts and zero ctxdiff-equivalent differences. The engine remains non-exact with 5971 direct ctxdiff differences. ZiMatchZHSpelling remains 121 instructions with 29 register differences; Zi8GetElementCount remains 115 instructions with 13 register differences.

Exhaustively checked the two halfword arithmetic identities for all 65536 inputs. Regenerated progress and build/43U/report.json; explicit build/43U/ok passed. Retail DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d. The final object is byte-identical to the selected trial object after the clean rebuild.

Scope: only libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c and this new log are retained. The existing a4h, a4m, h4 and u6 logs remain untracked. No shared header, build flag, symbol, data payload or mapping-tool edit. No push, PR, merge, rebase or other-worktree edit. origin/main advanced externally while this worker ran; this branch remains based on the assigned 99ba99ee. Parent verification and integration remain required.

Final full gate output:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 536/536 functions 5/8 fuzzy 98.4957 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 98.495735
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 98.336266
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.6547
regressions vs baseline: 0
global matched_code_percent: 92.59315 -> 92.59315
global fuzzy_match_percent: 99.74304 -> 99.77242
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94958 -> 99.97097
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
