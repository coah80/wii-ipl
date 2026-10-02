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
