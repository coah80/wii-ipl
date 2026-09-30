# bs2 reload matching attempts

Baseline: 787aa9d3, fresh branch agent/w0930/bs2-reloads. Object builds, string pools, ctxdiff and objdiff accompany each candidate; rejected candidates restored. Detailed candidate source and diffs in /tmp/bs2r3-attempts.

main/src/BS2/BS2Mach

- Run: 172 bytes, 16.744186%.
- BS2StartGame: 1572 bytes, 95.496185%.
- BS2StartGCGame: 912 bytes, 99.5614%.
- BS2NANDDivideCallback: 512 bytes, 85.03906%.
- BS2NANDDivideReadAsync: 188 bytes, 60.31915%.
- BS2NANDDivideWriteAsync: 188 bytes, 60.31915%.
- CheckBS2CommandStatus: 1624 bytes, 83.23645%.
- BS2Tick: 7760 bytes, 98.25309%.
main/src/BS2/BS2Update

- BS2UpdateInit: 288 bytes, 79.875%.
- UpdateThread: 3652 bytes, 84.516975%.

| Unit | Function | Attempt | Change | Result |
| --- | --- | --- | --- | --- |

Initial quick gate: full build and DOL hash correct, both pools identical, no added forbidden/style patterns. Default gate lacks latest-main baseline 787aa9d3. Until the orchestrator supplies it, use gate --base 30809a5b, the immediately preceding checked-in main with an authoritative baseline, and independently compare both owned units to the fresh 787aa9d3 snapshot. No baseline reports edited.

| src/BS2/BS2Mach | BS2StartGCGame | 1 | Poll an explicit command-state snapshot read from CoverBlock each iteration; memcpy keeps the asynchronous read observable without qualifying the global | 99.56140 -> 96.71491; src 0x3a0 base 0x390 insns 232/228; restored |

| src/BS2/BS2Mach | BS2StartGCGame | 2 | RTC multiplication with frequency widened as the left operand, retaining the post-call RTC and bus-clock reads | 99.56140 -> 99.42982; src 0x390 base 0x390 insns 228/228; restored |

| src/BS2/BS2Mach | BS2StartGCGame | 3 | Use a 64-bit tick-frequency temporary and multiply by the explicitly unsigned RTC plus bias | 99.56140 -> 99.42982; src 0x390 base 0x390 insns 228/228; restored |

| src/BS2/BS2Mach | BS2StartGCGame | 4 | Inline the seconds addition into the tick conversion after the bias call, preserving global bus-clock read location | 99.56140 -> 99.42982; src 0x390 base 0x390 insns 228/228; restored |

| src/BS2/BS2Mach | BS2Tick | 1 | Remove cached partition pointer from both state-18 loops; each report and increment dereferences global PartitionCursor | 98.25309 -> 98.28918; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| src/BS2/BS2Mach | BS2Tick | 2 | Read data TOC partition count through the global pointer after reporting instead of the known GameTOCBuf address | 98.28918 -> 98.28505; src 0x1e34 base 0x1e50 insns 1933/1940; restored |

Correction: I read the wrong gate status before making local commit 9b58ef9a. The alternate-base gate actually FAILS due to changes already on main: nand_drv data decrease and sd_drv volatile additions in #400. I undid that local commit with git reset --soft HEAD~1, retaining source and logs. No gate-failing commit remains. Latest-main baseline 787aa9d3 is required; no restore-tools or baseline report edits are authorized. Tick improvement remains uncommitted until the default gate passes. Fuzzy 98.25309 -> 98.28918; 1933/1940 instructions.

| src/BS2/BS2Mach | BS2Tick | 3 | Positive GamePartition branch precedes the failed-partition branch; keep state-37 fallthrough into state 37 | 98.28918 -> 98.20515; src 0x1e38 base 0x1e50 insns 1934/1940; restored |

| src/BS2/BS2Mach | BS2StartGame | 1 | Remove local status snapshots; every error dispatch comparison reads global LowReadResult directly | 95.49618 -> 94.79644; src 0x644 base 0x624 insns 401/393; restored |

| src/BS2/BS2Mach | BS2StartGame | 2 | Read an explicit global completion snapshot at each polling iteration using ordinary memcpy, preserving asynchronous polling | 95.49618 -> 94.36132; src 0x65c base 0x624 insns 407/393; restored |

| src/BS2/BS2Mach | BS2StartGame | 3 | Remove drive-error caching; read and mask the hardware error register at each comparison | 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; restored |

| src/BS2/BS2Mach | BS2NANDDivideCallback | 1 | Use pointers to the real transfer counters and dereference them at every update, remaining-byte test, report and completion | 85.03906 -> 78.09375; src 0x1ec base 0x200 insns 123/128; restored |

| src/BS2/BS2Mach | BS2NANDDivideCallback | 2 | Keep cancellation and negative-result blocks as separate guards returning before updating the global transfer state | 85.03906 -> 85.03906; src 0x1dc base 0x200 insns 119/128; restored |

| src/BS2/BS2Mach | BS2NANDDivideCallback | 3 | Write counter and buffer updates explicitly, test completion by equality, and reload global completion callback on each call | 85.03906 -> 87.26562; src 0x1dc base 0x200 insns 119/128; kept |

| src/BS2/BS2Mach | CheckBS2CommandStatus | 1 | Remove cached dataToc pointer; both partition chunk calculations read global DataToc and its count directly | 83.23645 -> 83.27340; src 0x620 base 0x658 insns 392/406; kept |

| src/BS2/BS2Mach | CheckBS2CommandStatus | 2 | Dereference a pointer to the actual global CacheLength at every accumulation and limit comparison | 83.27340 -> 81.80788; src 0x624 base 0x658 insns 393/406; restored |

| src/BS2/BS2Mach | CheckBS2CommandStatus | 3 | Express cache capacity as failure guard then perform the write, maintaining literal order and direct global argument reads | 83.27340 -> 83.27340; src 0x620 base 0x658 insns 392/406; restored |

| src/BS2/BS2Mach | BS2NANDDivideReadAsync | 1 | Dereference pointer to the real global length at each limit test, report and async NAND argument | 60.31915 -> 52.44681; src 0xc0 base 0xbc insns 48/47; restored |

| src/BS2/BS2Mach | BS2NANDDivideReadAsync | 2 | Set global file and buffer before resetting the transferred count, keeping all later calls as direct global reads | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| src/BS2/BS2Mach | BS2NANDDivideReadAsync | 3 | Use a switch over the length comparison to retain the two explicit reporting and async-call blocks | 60.31915 -> 71.80851; src 0xd0 base 0xbc insns 52/47; kept |

| src/BS2/BS2Mach | BS2NANDDivideWriteAsync | 1 | Dereference pointer to the real global length at each limit test, report and async NAND argument | 60.31915 -> 52.44681; src 0xc0 base 0xbc insns 48/47; restored |

| src/BS2/BS2Mach | BS2NANDDivideWriteAsync | 2 | Set global file and buffer before resetting the transferred count, keeping all later calls as direct global reads | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| src/BS2/BS2Mach | BS2NANDDivideWriteAsync | 3 | Use a switch over the length comparison to retain the two explicit reporting and async-call blocks | 60.31915 -> 71.80851; src 0xd0 base 0xbc insns 52/47; kept |

| src/BS2/BS2Update | UpdateThread | 1 | Rebuild the target 0xf0 frame with a typed scratch structure: channel/block/inode outputs at sp8/c/10, ticket count14, area18, title20, paths28/48 and DVD file68 | compile failed |

| src/BS2/BS2Update | UpdateThread | 2 | Translate initial area switch to shared invalid-product block and valid-product join matching address-order basic blocks | 84.51698 -> 85.58051; src 0xd74 base 0xe44 insns 861/913; kept |

| src/BS2/BS2Update | UpdateThread | 3 | Read global UpdateProgress directly for each WAD suffix/import path; remove local index snapshots after report calls | 85.58051 -> 84.74699; src 0xd7c base 0xe44 insns 863/913; restored |

| src/BS2/BS2Update | UpdateThread | 4 | Correct the scratch-frame translation to qualify locals only, preserving BS2UpdateEntry.titleId fields and the target stack slots | 85.58051 -> 85.55203; src 0xd74 base 0xe44 insns 861/913; restored; regression matched_data |

| src/BS2/BS2Update | UpdateThread | 5 | Rebuild matching scratch stack layout with token-aware local replacements preserving string literals and entry fields | 85.58051 -> 85.61446; src 0xd74 base 0xe44 insns 861/913; kept |

| src/BS2/BS2Update | BS2UpdateInit | 1 | Explicitly initialize the existing seat flag array to zero to test declaration-order BSS emission and the target common Flags0 anchor | 79.87500 -> 79.87500; src 0x11c base 0x120 insns 71/72; restored |

| src/BS2/BS2Update | BS2UpdateInit | 2 | Give thread start an explicit local thread and stack-end pointer to match the original saved thread-base register and frame | 79.87500 -> 79.87500; src 0x11c base 0x120 insns 71/72; restored |

| src/BS2/BS2Update | BS2UpdateInit | 3 | Initialize the existing flag arrays, thread storage and update headers explicitly; test common BSS grouping without adding objects | 79.87500 -> 79.87500; src 0x11c base 0x120 insns 71/72; restored |

| src/BS2/BS2Update | UpdateThread | 6 | Translate every update-discovery failure in address order as report then selectedCount=0 then jump to the common count publication, avoiding a shared reset block | 85.61446 -> 86.59912; src 0xd9c base 0xe44 insns 871/913; kept |

All requested Mach functions now have at least three compiled source-level attempts in this round; real caching removals improved Tick and command-status, and callback equality changed register scheduling. GC and StartGame retain asynchronous-safe API polling: direct snapshots added calls instead of the target reloads. No volatile declarations or asm were added. UpdateThread stack layout now matches via typed scratch fields; proceeding through failure/basic-block joins. Latest-main baseline is still unavailable, so no commits are authorized by the gate yet.

| src/BS2/BS2Update | UpdateThread | 7 | Remove cached entry pointers in both discovery loops and listing; each statement re-indexes the disc/seat array, matching target repeated base-plus-index instructions | 86.59912 -> 89.73384; src 0xe08 base 0xe44 insns 898/913; kept |

UpdateThread: direct re-indexing of entries follows original address-order loads; cached base pointers retained where target keeps them across calls. All scratch fields are existing real outputs/paths/file info, with no padding.

| src/BS2/BS2Update | BS2UpdateInit | 4 | Extract actual seat-flag initialization and critical-attribute filtering into an inline helper before thread initialization, preserving executable operations and testing the original helper boundary/common BSS anchor | 79.87500 -> 79.87500; src 0x11c base 0x120 insns 71/72; restored |

| src/BS2/BS2Update | BS2UpdateInit | 5 | Group existing real flag arrays, thread and aligned DVD headers as typed update storage, preserving all sizes/required alignment and reading members directly; test the target shared-base addressing | 79.87500 -> 77.50000; src 0x11c base 0x120 insns 71/72; restored; regression matched_data |

| src/BS2/BS2Update | UpdateThread | 8 | Retain the literal disc-entry base as a typed local pointer while re-indexing every access, matching the target saved base register rather than folded addis accesses | 89.73384 -> 91.48083; src 0xe0c base 0xe44 insns 899/913; restored; regression matched_data |

| src/BS2/BS2Update | UpdateThread | 9 | Extract the low title code with the explicit 64-bit 0xffffffff mask used by the target Internet/BBC checks | 89.73384 -> 89.69003; src 0xe14 base 0xe44 insns 901/913; restored |

| src/BS2/BS2Update | UpdateThread | 10 | Restore the original global symbol binding of rc and hardware/version variables from target nm; external calls may modify rc, requiring the target repeated reads | 89.73384 -> 89.73384; src 0xe08 base 0xe44 insns 898/913; restored |

Update discovery stack and initial region/failure blocks now follow target order. Direct entry indexing improved UpdateThread 84.51698 -> 89.73384 and instruction count 860 -> 898 versus target 913. Rejected saved-base and 64-bit-mask candidates show further code gains but changed the matched jump-table data, so they remain restored. Target nm shows rc/version symbols global; restoring binding alone did not prevent -ipa file forwarding and was restored.

| src/BS2/BS2Update | UpdateThread | 11 | Re-translate first-loop copy cursor: original r30 advances only after an imported entry; type-zero entries increment selectedCount but not the selected-array write cursor | 89.73384 -> 89.63965; src 0xe04 base 0xe44 insns 897/913; restored |

| src/BS2/BS2Update | UpdateThread | 12 | Advance a typed selected-entry cursor in both type-zero and import-copy branches, reproducing the independent r30 cursor alongside selectedCount | 89.73384 -> 88.80614; src 0xe04 base 0xe44 insns 897/913; restored |

| src/BS2/BS2Mach | BS2NANDDivideReadAsync | 4 | Treat zero as the small-transfer case and use default for a full chunk, avoiding unreachable explicit-boolean switch alternatives | 71.80851 -> 82.55319; src 0xbc base 0xbc insns 47/47; kept |

| src/BS2/BS2Mach | BS2NANDDivideWriteAsync | 4 | Treat zero as the small-transfer case and use default for a full chunk, avoiding unreachable explicit-boolean switch alternatives | 71.80851 -> 82.55319; src 0xbc base 0xbc insns 47/47; kept |

| src/BS2/BS2Mach | BS2Tick | 4 | Use the disk-ID gameName field for the four system-disc comparisons, leaving the header pointer for magic and streaming reads | 98.28918 -> 98.28918; src 0x1e34 base 0x1e50 insns 1933/1940; restored |

| src/BS2/BS2Mach | BS2Tick | 5 | Keep an independently typed game-name pointer for the system-disc inline comparison block | 98.28918 -> 98.17680; src 0x1e38 base 0x1e50 insns 1934/1940; restored |

| src/BS2/BS2Mach | BS2Tick | 6 | Read the streaming flag into a byte temporary before preparing either audio-config call, matching the original field-load order | 98.28918 -> 98.28918; src 0x1e34 base 0x1e50 insns 1933/1940; restored |

| src/BS2/BS2Update | UpdateThread | 13 | Give discovery, listing and import phases separate typed disc-base pointer lifetimes, keeping repeated per-use indexing and original saved literal base registers | 89.73384 -> 91.29463; src 0xe14 base 0xe44 insns 901/913; kept |

| src/BS2/BS2Update | UpdateThread | 14 | Translate both import joins as local call result then one global rc store before the report, matching target stores outside the suffix branches | 91.29463 -> 91.45454; src 0xe0c base 0xe44 insns 899/913; kept |

| src/BS2/BS2Update | UpdateThread | 15 | Restore original global rc definition with explicit zero initialization before import-result joins; verify emitted reloads rather than assuming visibility fixes them | 91.45454 -> 91.45454; src 0xe0c base 0xe44 insns 899/913; restored |

| src/BS2/BS2Update | UpdateThread | 16 | Use the target 64-bit lower-word title mask in the seat restrictions after phase-specific disc-base lifetimes are rebuilt | 91.45454 -> 92.31435; src 0xe18 base 0xe44 insns 902/913; kept |

Current original global read limitations: NAND initializers target reloads at 8137CAE0/8137CB2C while direct global C reads are still store-forwarded. StartGame target polls CoverBlock.state and LowReadResult without API/barrier calls; all safe ordinary-C snapshot variants added calls and were rejected. Update rc report/error paths target reloads at 81380058/81380064/81380078; changing symbol binding did not stop compiler forwarding. No volatile/asm/codegen pragmas or hand-placed objects used.

Whitespace review: indented phase-local loops and failure jumps consistently; rebuilt Update object. Current retained Update discovery has the exact 0xf0 frame and named scratch slots; initial region switch, failure joins, both selection loops, restrictions, listing and import joins have been translated/reviewed in target address order. Residual data-anchor and rc/global forwarding are documented; no register-only or exact claim is made.

Final fresh-build measurements:

- BS2StartGCGame: 912 bytes, 99.56140 -> 99.56140; src 0x390 base 0x390 insns 228/228; 4 compiled attempts.
- BS2Tick: 7760 bytes, 98.25309 -> 98.28918; src 0x1e34 base 0x1e50 insns 1933/1940; 6 compiled attempts.
- BS2StartGame: 1572 bytes, 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; 3 compiled attempts.
- BS2NANDDivideCallback: 512 bytes, 85.03906 -> 87.26562; src 0x1dc base 0x200 insns 119/128; 3 compiled attempts.
- CheckBS2CommandStatus: 1624 bytes, 83.23645 -> 83.27340; src 0x620 base 0x658 insns 392/406; 3 compiled attempts.
- BS2NANDDivideReadAsync: 188 bytes, 60.31915 -> 82.55319; src 0xbc base 0xbc insns 47/47; 4 compiled attempts.
- BS2NANDDivideWriteAsync: 188 bytes, 60.31915 -> 82.55319; src 0xbc base 0xbc insns 47/47; 4 compiled attempts.
- UpdateThread: 3652 bytes, 84.51698 -> 92.31435; src 0xe18 base 0xe44 insns 902/913; 15 compiled attempts.
- BS2UpdateInit: 288 bytes, 79.87500 -> 79.87500; src 0x11c base 0x120 insns 71/72; 5 compiled attempts.

Final full gate, both touched units, default origin/main baseline.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4052/16980 data 155504/158528 functions 21/29 fuzzy 95.5642 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 21/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 95.56419
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 95.496185
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: BS2NANDDivideCallback 87.265625
[src/BS2/BS2Mach]   below 100: BS2NANDDivideReadAsync 82.55319
[src/BS2/BS2Mach]   below 100: BS2NANDDivideWriteAsync 82.55319
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 83.2734
[src/BS2/BS2Mach]   below 100: BS2Tick 98.28918
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 112/4052 data 1328/10488 functions 8/10 fuzzy 91.6427 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 8/10
[src/BS2/BS2Update]   section .bss size 9056 match 72.9682
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 78.947365
[src/BS2/BS2Update]   section .sdata size 24 match 94.117645
[src/BS2/BS2Update]   section .text size 4052 match 91.64265
[src/BS2/BS2Update]   below 100: BS2UpdateInit 79.875
[src/BS2/BS2Update]   below 100: UpdateThread 92.31435
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE FAIL: no baseline report for merge-base 787aa9d3; rebase onto origin/main
```

Full clean build and DOL hash pass; both pools identical, zero added forbidden patterns and readability warnings. The only final failure is absent authoritative baseline 787aa9d3. Latest main already is 787aa9d3, so rebasing cannot solve this; no baseline files or restore tools were modified. No gate-passing commit could be made. All improvements are preserved as uncommitted changes on agent/w0930/bs2-reloads for orchestrator baseline generation/review. Erroneous local commit 9b58ef9a was undone and is not on this branch. No functions reached instruction exactness; no claim of completion or register-only equivalence.

| src/BS2/BS2Mach | BS2StartGCGame | 5 | Inline typed command-state accessor at the original polling helper boundary | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

| src/BS2/BS2Mach | BS2StartGCGame | 6 | Inline global cover-state accessor; repeat the global member access through the helper on every iteration | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

| src/BS2/BS2Mach | BS2StartGCGame | 7 | Inline pending-command predicate, with the idle comparison inside the helper | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

Final additional helper boundary audit: GC attempts 5/6/7 all compiled at 228/228 instructions but 96.88596%, below the retained 99.56140%. Each hoists CoverBlock.state and branches bne -4, so it is also unsafe as asynchronous polling. All three restored. Seven compiled GC attempts total. No source differs from the full-gate candidate after these restorations.
