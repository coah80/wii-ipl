# Data lane d1

Base eecf16f0, fetched origin before inspection. Owned sources agree with origin/main. Initial full quick gate PASS, SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, zero regressions.

| Unit | Initial matched data / total | Initial exact functions | Initial matched code |
|---|---|---|---|
| OSUtf | 0 / 48704 | 4 / 4 | 568 / 568 |
| iplKeyboard | 8 / 1184 | 30 / 32 | 4680 / 6024 |
| iplController | 80 / 696 | 84 / 84 | 5708 / 5708 |
| d_nhttp | 16 / 720 | 22 / 22 | 3180 / 3180 |

All four pool_diff checks identical. Inspected both ELF symbol tables, all owned non-text section bytes, and relocation records with pyelftools.

## OSUtf

The 93 typed u16 lookup pages exactly match. The only 372 differing bytes are the 93 non-null pointers in UcsSjisTable. Original extraction retained absolute DOL addresses without relocation records because symbols.txt marks the pointer table noreloc. Built C table has 93 R_PPC_ADDR32 relocations to the correct UcsXX pages. First original values at offsets 0xba40, 0xba4c, 0xba50 are 0x81674228, 0x81674428, 0x81674628, precisely Ucs00, Ucs03, Ucs04 in symbols.txt. Remove noreloc only from the pointer table and describe data:4byte. Keep the u16 pages noreloc. No symbol address, size, section boundary, source object, or total byte count changes. Regenerated extraction now reports .data 100%, matched_data 48704/48704.

## iplController

All 616 original .data bytes and all 133 relocation records match built prefix exactly. All other sections match. Built .data is 752 bytes: Base vtable is 140 bytes instead of original extraction's 144, followed by a 140-byte weak Interface vtable at 0x264. Original trailing four bytes are zero without relocations, not a virtual slot. Existing original vtables and member-pointer objects have identical typed source and relocations. Extra weak abstract-base vtable is linker discarded in the already Matching unit, and current DOL hash proves linked data. No dummy padding, forced placement, or removing real virtual functions is justified.

## d_nhttp

Built .data 701 bytes is identical to original 704-byte prefix; last three extraction bytes are zero linker alignment. Built .sdata 6 bytes is identical to original 8-byte prefix; last two bytes zero alignment, and this section already scores 100%. The only relocation is __NHTTPVersion to first version string at offset zero on both sides. .sbss 8 bytes exact. No missing table or object. Changing array counts or adding padding would violate task policy. Already Matching DOL proves these linked bytes.

## iplKeyboard

Built .data 1161 bytes is byte-identical to original 1168-byte prefix. Last seven extraction bytes are zero alignment. Built .sdata 6 bytes is identical to original 8-byte prefix, with two zero alignment bytes. .sdata2 exact. All 85 .data relocation offsets and target names match; twelve create switch-table addends differ by exactly four bytes because create has 317 versus 318 instructions. Other data discrepancy is coarse original string symbols versus individual compiler literals. Do not shrink symbols or alter ownership to hide that. Investigate create source variations for switch-table instruction addresses.

Clean full four-unit gate PASS after OSUtf metadata correction; zero regressions, exact counts 4/30/84/22 unchanged, global matched data 93.05085 -> 95.70837. DOL hash correct.

Keyboard create attempt 1: separate ArcResourceLink declaration/assignment and omit value-initialization parentheses. Output unchanged, 317/318 instructions, objdiff 94.18239%. Reverted.

Keyboard create attempt 2: obtain the archive buffer directly at ArcResourceLink::Set instead of extending its lifetime across allocation. 317/318 instructions, 93.03459% objdiff, exact counts unchanged. Reverted.

Keyboard create attempt 3: separate allocator declaration/assignment and declare OEM dictionary before system dictionary. 317/318 instructions, 94.22956% objdiff, exact counts unchanged. Changed loop register assignment but did not recover the missing instruction or switch-table addends. Reverted; fuzzy gain alone is not accepted. Remaining create is 94.18239%, with allocation register lifetimes, loop registers, and one-instruction size discrepancy. Three distinct source attempts complete.

Keyboard getSaveData attempt 1: under a macro defined only by iplKeyboard.cpp, declare the existing virtual getter out of line, then implement the real member as `return mMemoSetting`. This emits the real function already present in the original object, without forcing references or changing any vtable slot. ctxdiff 18/18 instructions, diffs 0; exact-name objdiff 100%. Unit exact functions 30 -> 31 and matched code 4680 -> 4752. No new assembly. Other header consumers retain their existing inline definition. Stop iteration on this function because it is exact.

Final upstream check: origin/main advanced to 9eb08c48 while this leaf was running. None of the four owned units or the guarded getter header changed between eecf16f0 and current origin/main. No rebase or cross-worktree operations performed.

Data-lane audit: OSUtf has no unresolved section; all functions exact. Controller has no unresolved function, no byte or relocation difference in original section ranges, and only the linker-discarded weak Interface table beyond them. NHTTP has no unresolved function and only final zero alignment bytes in .data. Keyboard has exactly one open function, create, with three distinct source attempts above; getter is now exact. No additional non-text sections, missing statics, initializer differences, or pointer-table differences were found in these four original objects. Section ownership and symbol sizes remain unchanged throughout.

## Final verification

Clean non-quick four-unit gate PASS. Full build ok; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; regressions 0; forbidden patterns 0; readability warnings 0. Fresh pool_diff checks all identical. Fresh getter ctxdiff 18/18 instructions, diffs 0. Final exact counts OSUtf 4/4, keyboard 31/32, controller 84/84, NHTTP 22/22. Final matched data OSUtf 48704/48704, keyboard 8/1184, controller 80/696, NHTTP 16/720. Final matched code OSUtf 568/568, keyboard 4752/6024, controller 5708/5708, NHTTP 3180/3180. The gate passes but the all-data-100% objective is not met for the latter three units; no claim of completion for those sections. All remaining genuine unmatched functions have three distinct attempts recorded. Final full gate output is /tmp/data-d1.final-gate.txt.

# Round 2, after #730

Fresh leaf HEAD bcb2ac0e equals fetched origin/main at start. Initial quick three-unit gate PASS, DOL SHA1 correct, zero regressions. Keyboard data 8/1184, exact 31/32, code 4752/6024; controller data 80/696, exact 84/84, code 5708/5708; NHTTP data 16/720, exact 22/22, code 3180/3180. All three pool_diff checks identical. Rechecked ELF bytes, nm, objdump symbol tables and relocations. Prior round's byte/relocation findings remain reproducible.

Inspect the installed objdiff 3.4.5 data comparison algorithm to distinguish relocation mismatches from legal linker tail alignment; do not alter comparison settings or tool code to hide mismatches. Investigate source changes and extraction metadata only when supported by byte/relocation evidence.

Round 2 keyboard create attempt 1: replace the second loop's parallel OEM induction variable with the meaningful expression `i + EZTX_LANG_MAX`. Objdiff create 94.50944%, 313/318 instructions, no exact function loss. Compiler strength-reduces both indices into one byte offset and removes five instructions instead of recovering the target's independently maintained OEM index. Not accepted.

Objdiff 3.4.5 diff_data_section compares bytes up to maximum data symbol extent and only uses raw byte match percentage when every original relocation matches. This explains keyboard .data's 25% despite identical bytes: create jump-table relocations fail. The final keyboard data string ends at 1161 on both sides, so those seven section tail bytes do not obstruct .data matching. NHTTP original last coarse blob includes tail alignment and extends to 704 while built last literal ends at 701, so its 99.786476% score is the byte ratio 2*701/(704+701). Controller's extra weak Interface table extends built symbol extent to 752 against original 616. These are specific measured causes, not guessed missing objects. Do not change symbol sizes or suppress the real extra source vtable to fake matching.

Round 2 keyboard create attempt 2: express both OEM indices as `i + EZTX_LANG_MAX`, removing parallel induction variables. 309/318 instructions, create 92.28616%, no exact function loss. Both loops strength-reduce OEM addressing to the system byte offset plus 40, unlike target's separate index addition and shift. Reverted.

Round 2 keyboard create attempt 4, memo_declaration_order: src 0x4f4 base 0x4f8 insns 317/318; create 94.157234%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 5, memo_copy_initialization: src 0x4b8 base 0x4f8 insns 302/318; create 87.8522%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 6, dictionary_fallback_order: src 0x4f4 base 0x4f8 insns 317/318; create 93.83648%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 7, dictionary_ternary_fallback: src 0x4fc base 0x4f8 insns 319/318; create 93.93082%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 8, oem_load_after_system_fallback: src 0x4f4 base 0x4f8 insns 317/318; create 94.57861%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 9, signed_counter_unsigned_oem: src 0x4f4 base 0x4f8 insns 317/318; create 94.18239%; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 3: use unsigned loop induction variables for both dictionaries, retaining parallel OEM indices. Output unchanged at 317/318 instructions and 94.18239%; exact functions remain 31. Reverted.

Round 2 controller vtable attempt 1: make the abstract Interface destructor an inline non-pure destructor under a source-only header guard. Abstractness remains enforced by decide and setForceInvalid; this tests whether the pure destructor caused unwanted table emission. All 84 original functions remain 100%, but extra Interface table remains and .data stays 92.03601%. Reverted both source and header; no justification for changing destructor semantics without a match.

Round 2 keyboard create attempt 10, system_ternary_fallback: src 0x4f8 base 0x4f8 insns 318/318; create 94.00944% ; code 4752, data 1176, exact-name functions 31.

Round 2 keyboard create attempt 11, oem_ternary_fallback: src 0x4f8 base 0x4f8 insns 318/318; create 94.00944% ; code 4752, data 1176, exact-name functions 31.

Round 2 keyboard create attempt 12, system_inverted_ternary: src 0x4f4 base 0x4f8 insns 317/318; create 94.35535% ; code 4752, data 8, exact-name functions 31.

Round 2 keyboard create attempt 13, oem_inverted_ternary: src 0x4f4 base 0x4f8 insns 317/318; create 94.35535% ; code 4752, data 8, exact-name functions 31.

Round 2 candidate: retain attempt 10's ordinary system dictionary fallback selection `usedSystemDict != NULL ? usedSystemDict : systemDict`. OEM selection remains unchanged. The resulting create has 318 instructions, and all twelve destination switch-table relocation addends now exactly match the original object. Both .data byte extents are 1161, and every one of the 85 original .data relocation records matches; objdiff .data is 100%, raising matched_data from 8 to 1176 of 1184. No string, symbol, section ownership, source object, or data byte is altered; no padding or assembly is introduced. This is a genuine relocation-data match from a readable conditional expression, even though create remains instruction-nonexact at 94.00944%. Instruction-exact count remains 31/32. Attempts 11 through 13 are not retained. The data-lane task permits improvements with unchanged exact counts; the generic worker count-growth criterion is not met.

Candidate quick three-unit gate PASS, zero regressions, zero forbidden patterns, zero readability warnings, correct DOL SHA1. Keyboard .data 100%; .sdata remains 85.71429%, .sdata2 100%. Controller .data 92.03601%; other data sections 100%. NHTTP .data 99.786476%; .sdata and .sbss 100%. No original extab/extabindex, .bss, or additional small-data sections are present in the owned objects.

Remaining keyboard .sdata contains `arc\0` at offset 0, followed by empty 16-bit wchar string at offset 4. Source literal is 2 bytes, extraction labels it as a 4-byte object including two alignment zeros. All instructions using it still match exactly. Changing L"" to an artificially longer null literal or enlarging its symbol would fabricate storage; neither is accepted. NHTTP and controller residual section differences remain exactly the extraction alignment/weak-vtable findings above. They contain no unmatched functions. All failed experimental source and header changes were restored before the candidate gate.

Attempts 4-9 detail: 4 reverses the two MemoSetting declarations; 5 uses direct initialization for the loaded setting and copied setting; 6 reverses system/OEM fallback statement order; 7 expresses both fallback selections as ternaries; 8 postpones the OEM pointer load until after system fallback selection; 9 moves OEM induction initialization outside the first loop and uses an unsigned system index. Each was independently compiled, measured, and reverted. Attempts 10/12 use respectively non-null/null-first system ternaries; 11/13 use respectively non-null/null-first OEM ternaries. Only 10 is retained. The single remaining unmatched function, keyboard create, has thirteen distinct source-level experiments in this round, in addition to the three original attempts. Controller and NHTTP have zero remaining unmatched original functions.

Final fetch during verification reached f6fd2780; owned three sources do not differ between this branch's base and fetched origin/main. The worktree remains on its assigned leaf branch.

## Round 2 final clean gate

Final non-quick gate over all three units PASS. Full 43U build succeeds and DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. Regressions 0; forbidden additions 0; readability warnings 0; all pools identical. Keyboard exact functions 31 -> 31, matched code 4752 -> 4752, matched data 8 -> 1176 of 1184; .data 100%. Controller exact 84 -> 84, code 5708 -> 5708, data 80 -> 80 of 696. NHTTP exact 22 -> 22, code 3180 -> 3180, data 16 -> 16 of 720. No instruction-exact function count dropped. Fresh relocation comparison confirms every original keyboard .data relocation matches. Final gate output /tmp/data-d1-r2.final-gate.txt.

Incomplete data sections: keyboard .sdata 85.71429% from extracted empty-string extent; controller .data 92.03601% from linker-discarded weak Interface vtable and unit-boundary alignment; NHTTP .data 99.786476% from last extraction blob covering three tail alignment zeros. No symbol size or section boundary has been changed to improve the score. The all-data-100% goal remains incomplete. Remaining function create is 94.00944%, 318/318 instructions with 210 instruction differences; register allocation, dictionary-loop instruction scheduling, and MemoSetting temporary stack placement still differ. Every remaining function has at least three distinct logged attempts; all thirteen are retained as evidence, with only the data-exact candidate in the source diff.

# Round 3, after #739

Base 775167f4 fetched origin/main before starting. Initial quick gate PASS, DOL SHA1 correct, instruction-exact functions controller 84/84, NHTTP 22/22, keyboard 31/32. Matched data respectively 80/696, 16/720, 1176/1184; matched code respectively 5708/5708, 3180/3180, 4752/6024. All string pools identical. The human explicitly authorizes proven symbol extent corrections that exclude alignment or neighbour bytes while keeping addresses and section totals unchanged. This supersedes earlier rounds' interpretation that every extent correction was forbidden.

Controller proof: lbl_816346A8 -> kDownMember__Q23ipl10controller, same address 0x816346A8 and size 12; Master::down relocations at .text+0xcb6/+0xcc2 load it, and member-pointer words {0,0x14,0} encode Interface::down's vtable offset, byte-identical to the typed source member pointer.
Controller proof: lbl_816346B4 -> kDownTrgMember__Q23ipl10controller, same address 0x816346B4 and size 12; Master::downTrg relocations at .text+0xcf6/+0xd02 load it, and words {0,0x18,0} encode Interface::downTrg, matching the source member pointer.
Controller proof: lbl_816346C0 -> kUpTrgMember__Q23ipl10controller, same address 0x816346C0 and size 12; Master::upTrg relocations at .text+0xd36/+0xd42 load it, and words {0,0x1c,0} encode Interface::upTrg, matching the source member pointer.
Controller proof: lbl_816346CC -> kRepeatMember__Q23ipl10controller, same address 0x816346CC and size 12; Master::repeat relocations at .text+0xd7e/+0xd8a load it, and words {0,0x30,0} encode Interface::repeat, matching the source member pointer.
Controller extent proof: __vt__Q33ipl10controller4Base at unchanged 0x81634880 is 0x8c, not 0x90: the real class has two header words plus 33 virtual entries, with 33 target relocations from +0x08 through final Base::read at +0x88; the compiler emits exactly 140 bytes, and the final unrelocated zero word at +0x8c is alignment before neighbour FreeStyle at 0x81634910. Leave that word unowned, keep .data section size 616 and all addresses unchanged. Extra emitted weak Interface table is ignored, not suppressed.

Controller measurement after proven four renames and Base extent correction: every non-text section 100%, matched_data 696/696. No source or section boundary change.

NHTTP extent proof: lbl_8166D328 stays at 0x8166D328 and spans the real emitted diagnostic string pool from compiler literal @1000 at unit .data+0xb8 through @1126 at +0x29c, a char[33] holding NHTTPDisableVerifyOptionForDebug and its final NUL at +0x2bc; its real pool extent is 0x205, not 0x208. Both objects agree on all 517 bytes in that span and every literal's internal offset; the three bytes +0x2bd..+0x2bf are unreferenced trailing alignment. NHTTPAddHeaderField's .text+0x452/+0x45a relocations reference the pool start; the source's last function references the final ordinary literal. Leave those three alignment bytes unowned, with .data size still 704 and all addresses unchanged. No symbol rename is needed because .data has no relocations and its byte comparison then spans the same emitted pool extent.

NHTTP measurement after proven string-pool extent correction: .data, .sdata, .sbss all 100%, matched_data 720/720; all 22 original functions remain exact in objdiff.

Keyboard extent proof: lbl_816961FC stays at 0x816961FC, with size 2 instead of 4: start's .text+0xf84 and +0xfe4 SDA relocations load the same ordinary empty wchar_t literal for setWCString and setTitleText; wchar_t[1] is 2 bytes in the target ABI, the compiled symbol @17447 is size 2 at identical .sdata+4 with bytes 0000, and the following two zero bytes are section alignment. Leave them unowned; .sdata stays 8 bytes and the entire unit stays 1184 data bytes. The other .sdata object, "arc", already has matching address and four-byte extent; do not rename it or any unrelated compiler literal.

Keyboard measurement after the proven empty-wide-string extent correction: .data, .sdata and .sdata2 all 100%, matched_data 1184/1184; exact-name functions remain 31/32. Controller and NHTTP also retain every non-text section at 100%. All seven metadata edits are backed by the one-line proofs above. No source files, build configuration, split boundaries, addresses, section totals, bytes, or weak-table emission are changed. Remaining keyboard create is code work and is outside this completed data-only lane; prior rounds logged thirteen distinct attempts without reducing its exact function count.

## Round 3 final verification

Clean non-quick gate over controller, NHTTP and keyboard PASS. Full 43U build passes; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Regressions 0, forbidden patterns 0, readability warnings 0, all pools identical. Controller data 80 -> 696/696, instruction-exact 84 -> 84, matched code 5708 -> 5708. NHTTP data 16 -> 720/720, instruction-exact 22 -> 22, matched code 3180 -> 3180. Keyboard data 1176 -> 1184/1184, instruction-exact 31 -> 31, matched code 4752 -> 4752. Fresh report asserts every owned non-text section is 100%, matched_data equals unchanged total_data, and original section sizes are unchanged. Data-lane goal achieved. Remaining keyboard create stays 94.00944%; its instruction differences are outside data scope and its prior thirteen attempts are logged. No new source experiment is needed for this metadata-only lane. Final full gate output /tmp/data-d1-r3.final-gate.txt, final report /tmp/data-d1-r3.final-report.json.
