# clean3-c5 cleanup attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/clean3-c5`, branch `agent/w1009/clean3-c5`, baseline `8a67b68cf`.
Read clean3-head.md, cleanup-common.md, AGENTS.md, unslop, writing-for-agents, and the prior cleanup logs for the owned files. Queried the existing nup graph. Baseline completion checker returned DECOMPLETE_OK; DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. Source and object snapshots are in `/tmp/clean3-c5-baseline`.

Acceptance: every retained trial preserves every allocated section, layout, exported symbol, and resolved relocation against the exact initial object. Compiler local label names resolve to section and offset. Reject and rebuild any trial that changes bytes. Gate all touched units at the end, regenerate the report, require DECOMPLETE_OK and the DOL SHA1, and commit each changed source separately.

Prior evidence rules out repeating plain AxManager IRO deletion, pointer/local/scoped/positive-guard/do-while variants; plain FAT32-builder IRO deletion and combined media/direct-write variants; WDScan constant/definition-level volatile substitutions and section deletion; NUP no-inline deletion, null-check deletion, unreachable-status simplification and tag-assignment hoisting; HTTP header-loop assignment hoisting and pointer-switch simplification; NWC24 conversion dispatch and success-guard alternatives; VI switch/nested-region rewrites; OSPlayTime result self-copy deletion; ARC moving the search bounds into its inner loop. Common error, cleanup and unlock exits stay. Wave 3 experiments require a different source hypothesis.

## Trials
- KEEP `libs/RevoEX/src/nhttp/NHTTP_request` remove volatile from the two request-queue locals: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nand/NANDOpenClose` remove export force-active scope, retaining the ordinary function definition: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/arc/arc` remove export force-active scope, retaining the ordinary function definition: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/NW4R/src/snd/snd_AxManager` remove IRO scope with a typed inline free-voice initialization helper: section .text; relocations .text; exported symbols. Init__Q44nw4r3snd6detail9AxManagerFv: 51 raw instruction words differ, 62/63 instructions
- REVERT `libs/RVL_SDK/src/fa/driver/sd_drv` remove builder IRO scope with branch-local reserved-sector helper returns: section .text; relocations .text; exported symbols. pfd_sddrv_build_fat32_mbr_bpb: 104 raw instruction words differ, 228/222 instructions
- KEEP `libs/RVL_SDK/src/nand/NANDOpenClose` remove obsolete force-link comment: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RevoEX/src/nhttp/NHTTP_thread` remove file-wide auto-inline prohibition: section .text; relocations .text; exported symbols. NHTTPi_CheckHeaderEnd: function removed or added; NHTTPi_CommThreadProcMain: 108 raw instruction words differ, 156/129 instructions; NHTTPi_SendData: function removed or added; NHTTPi_SendHeaderList: 59 raw instruction words differ, 158/62 instructions; NHTTPi_SendProcPostDataAscii: 135 raw instruction words differ, 385/177 instructions
- REVERT `libs/RevoEX/src/wd/WDScan` replace OUI volatile macros with plain extern const declarations before the definitions: section .sdata; section .sdata2; section .text; relocations .text; exported symbols. WDGetPrivacyMode: 113 raw instruction words differ, 117/115 instructions
- REVERT `libs/NW4R/src/snd/snd_AxManager` remove IRO scope using a named end iterator for the list insertion: section .text; relocations .text; exported symbols. Init__Q44nw4r3snd6detail9AxManagerFv: 51 raw instruction words differ, 62/63 instructions
- KEEP `libs/RVL_SDK/src/nup/nup` replace two dont-inline scopes with the existing NO_INLINE declaration convention: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nup/nup` use the named progress type size in status copy: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nup/nup` use the existing audit types for allocation, signature and certificate sizes: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RevoEX/src/nwc24/NWC24MsgSubject` NWC24ReadMsgSubjectPublic use switch break for the immediate shared return: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RevoEX/src/nwc24/NWC24MsgSubject` NWC24ReadMsgTextPublic use switch break for the immediate shared return: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RevoEX/src/nwc24/NWC24MsgCommit` keep successful message finalization inside its success branch: section .text; relocations .text. NWC24CommitMsgInternal: 75 raw instruction words differ, 826/827 instructions
- KEEP `libs/RevoEX/src/nwc24/NWC24MsgCommit` format the scoped plain-text status conversion as ordinary statements: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/vi/vi3in1` remove the jump immediately before the shared transmit label: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/vi/vi3in1` name YUV dispatch labels by their video regions: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RVL_SDK/src/os/OSPlayTime` remove unused interrupt local and overwritten fade-loop initializations: compile failure, MWCC 10140 at enabled = OSDisableInterrupts(). The interrupt local is used later in this function. Restored immediately; the corrected initialization-only trial follows.
- KEEP `libs/RVL_SDK/src/os/OSPlayTime` name remaining audio bytes and the last non-permanent ticket-limit index: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/os/OSPlayTime` remove only the overwritten fade-loop initializations, keeping the used interrupt state: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RVL_SDK/src/wpad/WPAD` remove unused-parameter pragmas from the allocation callbacks: exported symbols. FORCEACTIVEWPAD_c789: function removed or added; FORCEACTIVEWPAD_c791: function removed or added
- KEEP `libs/RVL_SDK/src/card/CARDMount` remove the unreachable break after the rejected-card return: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/sdi/sdi_api` name the callback-owned command buffer and use the existing command/response sizes: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/sdi/sdi_api` use the existing IPC invalid-argument constant: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RevoEX/src/nhttp/NHTTP_thread` replace the one-field token-match struct with a boolean: section .text; relocations .text. NHTTPi_ThreadParseHeaderProc: 20 raw instruction words differ, 191/191 instructions
- KEEP `libs/RevoEX/src/nhttp/NHTTP_thread` use the existing HTTP method and encoding enum names: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RevoEX/src/nhttp/NHTTP_thread` document the required out-of-line HTTP helper calls: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nup/nup_nhttp` expand the dense cleanup branches into ordinary multiline statements: all allocated sections, layout, exported symbols and resolved relocations identical.

WPAD comparator correction: removing two directives shifts the line-derived FORCEACTIVEWPAD_c791 symbol to FORCEACTIVEWPAD_c789. All allocated bytes and resolved relocations were already identical. The existing DECOMP_FORCE_ACTIVE macro derives this dead helper's name from __LINE__; its address, size and binding are unchanged. Normalize only that generated suffix when comparing exported symbols, then retest. Ordinary export names remain strict.
- KEEP `libs/RVL_SDK/src/wpad/WPAD` remove unused-parameter pragmas with the generated line-number symbol normalized: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RVL_SDK/src/wpad/WPAD` remove the unused alignment array and its activation stub: section .bss; section .text; relocations .data; relocations .text; exported symbols. FORCEACTIVEWPAD_c791: function removed or added; WPADiInitSub: 1 raw instruction words differ, 132/132 instructions
- KEEP `libs/RVL_SDK/src/nup/nup` remove the redundant boot-update jump before the if/else cleanup join: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nup/nup` use the ticket type size for response splitting: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RevoEX/src/nhttp/NHTTP_thread` document the token-match object needed by the keep-alive branch: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RevoEX/src/nwc24/NWC24MsgCommit` remove the status overwrite already excluded by the failure branch: section .text; relocations .text. NWC24CommitMsgInternal: 35 raw instruction words differ, 824/827 instructions
- REVERT `libs/RevoEX/src/nwc24/NWC24MsgCommit` use ordinary null-text status handling without the scoped result local: section .text. NWC24CommitMsgInternal: 4 raw instruction words differ, 827/827 instructions
- KEEP `libs/RVL_SDK/src/nup/nup` use the audit-record pointer type and remove its repeated casts: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/vi/vi3in1` use named video regions and the existing boot-video-format address: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/wpad/WPAD` replace the alignment TODO with the measured compiler requirement: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RevoEX/src/nwc24/NWC24MsgCommit` explain the retained scoped result and final status guard: all allocated sections, layout, exported symbols and resolved relocations identical.

## Full gate correction

The first full gate failed the DOL checksum, cf9aab55069c8ddadf2b06cd321acfe51e894155, despite all 308 owned functions remaining instruction-exact, every reported section at 100%, and zero regressions. ARCEntrynumIsDir and NANDSafeOpen lose the 0x00080000 flag in MWCC's non-allocated .comment linker metadata when their force-active scopes are removed. Their code and ordinary ELF symbol records remain identical, but the linker drops the unreferenced exports. The early KEEP results for these two scopes are superseded by REVERT. Restore both scopes; retain a one-line compiler requirement beside each.

Strengthened the trial comparator to include the complete MWCC .comment metadata. It was unchanged in every other owned unit, including NUP's NO_INLINE conversion and WPAD's generated helper rename. The final DOL gate remains the acceptance authority. NANDOpenClose's extra raw string is inherited: both baseline and candidate have the same fourth trailing source string, while the retail extracted object has three. Reported data and every section are 100%; this cleanup does not change that pool.
- KEEP `libs/RVL_SDK/src/arc/arc` explain why ARCEntrynumIsDir retains force-active metadata: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nand/NANDOpenClose` explain why NANDSafeOpen retains force-active metadata: all allocated sections, layout, exported symbols and resolved relocations identical.
- REVERT `libs/RVL_SDK/src/nand/NANDOpenClose` remove the unreferenced aligned trailing string object: section .comment; section .data; exported symbols.
- KEEP `libs/RVL_SDK/src/nand/NANDOpenClose` explain the retained trailing object alignment: all allocated sections, layout, exported symbols and resolved relocations identical.
- KEEP `libs/RVL_SDK/src/nand/NANDOpenClose` state the measured data-layout requirement precisely: all allocated sections, layout, exported symbols and resolved relocations identical.

## Final source decisions

- nup.cpp: four dont-inline directives become two existing NO_INLINE declarations, so the helpers still stay out of line. Removed the redundant boot-update cleanup jump and label. Uses sizeof for progress, audit, ticket and certificate types, plus a typed audit-record pointer instead of repeated casts. The other 46 gotos are common return/error/cleanup exits. Keep the proven short-circuit tag searches, redundant title guard and negative-status alternatives.
- nup_nhttp.cpp: expanded dense error/cleanup branches into normal multiline statements. Keep the 23 common cleanup exits, allocation switch, header-condition assignments and no-inline helper declaration already proven necessary by wave 2.
- NWC24MsgSubject.c: removed the two immediate-return switch gotos and unused labels. Keeps the 32 common return/error exits, short-circuit encoding setup and success-only switches already measured in wave 2.
- NWC24MsgCommit.c: formatted the scoped plain-text status conversion and explained it. Rewriting it as ordinary null-status handling changes four instruction words. Removing the final status guard drops three instructions; folding finalization into the success branch drops one. Keep its shared report and file-cancellation exits and the measured status guard.
- NHTTP_thread.c: uses existing HTTP method and encoding enums. No unk/local/field/var/temp placeholders remain in this baseline. Removing auto_inline off changes multiple helper bodies and call sequences; flattening TokenMatch to BOOL changes 20 instruction words. Both retained forms now have compiler notes. Reserved fields with no proven role stay.
- NHTTP_request.c: removed both volatile request-queue local qualifiers. The header's volatile request pointer still supplies the same reloads; code, data, relocations and linker metadata remain identical. Shared error cleanup stays.
- WDScan.c: unchanged. Moving OUI definitions after plain extern declarations fails to reproduce the existing loads and storage. Existing volatile-access and .sdata notes stay; the prior constant and definition-level volatile trials are not repeated.
- sdi_api.c: renamed the callback's SDSectorSize pointer to commandBuffer because it owns the allocated SD command packet and frees it on completion. Uses SD_CMD_SIZE, sizeof(resp) and IPC_RESULT_INVALID; removed the speculative typo comment. Common error/return exits stay. The unused SDDevRca callback field has no proven role and stays.
- OSPlayTime.c: named remaining DMA bytes and the non-permanent ticket-limit index. Removed fade-loop initializations overwritten before their first reads. Kept the interrupt local actually used later in the function; the mistaken deletion was restored immediately. Existing result self-copies and common exits stay under prior instruction evidence.
- vi3in1.c: removed the final immediate transmit jump. Dispatch labels name NTSC, PAL and MPAL, comparisons use existing VI enum names, and the boot video-format load uses OS_ADDR_TV_VIDEO_FORMAT. Keep the separate region-store blocks under the existing compiler note.
- WPAD.c: removed the two unused-parameter pragmas. Normalized only the line-derived activation helper name for comparison; every byte and link flag stays identical. Removing FAKE_ALIGNMENT and its existing helper changes data and one instruction in WPADiInitSub, so both stay with the measured layout note. Common callback/error exits stay.
- CARDMount.c: removed the unreachable break after the invalid-card return. Common unmount/unlock error exits stay.
- sd_drv.c: unchanged. Branch-local reserved-sector helper returns without the builder IRO scope change the builder from 222 to 228 instructions. Keep the IRO 0 scope and its existing compiler note; earlier media/direct-write variants are not repeated.
- NANDOpenClose.c: retained the restored force-active scope with its linker requirement explained. Deleting canYouAlignMe changes data and MWCC metadata, so its existing object stays with a layout note. The inherited extra raw pool string remains unchanged.
- arc.c: retained the restored export force-active scope with its linker requirement explained. The documented hierarchy-search join remains under the prior failed structured-loop evidence.
- snd_AxManager.cpp: unchanged. A typed inline free-voice helper and a named insertion end iterator at default IRO each remove one instruction. Keep IRO 0 and the existing voice-address note; prior pointer/scope/guard/do-while variants are not repeated.

Retained changes remove four gotos, six pragma directives and two local volatile qualifiers. Both force-active scopes remain. All 16 units, including the three unchanged optimizer cases, are included in the final gate. No header, configuration, upstream, other-worktree, push, PR, merge, rebase or subagent work was performed.

## Source commits

- `87283f41637bd58c1541d0db66e7a9b1d697db86`: `libs/RVL_SDK/src/nup/nup.cpp`.
- `1c1adc4545f18d4619642508c116309f48a86955`: `libs/RVL_SDK/src/nup/nup_nhttp.cpp`.
- `8654252e8d0fd5d2bb4fca5cb359cc0f92594cb5`: `libs/RevoEX/src/nwc24/NWC24MsgSubject.c`.
- `fa89f0cda62c44db3040eb7721d6ddae73d46277`: `libs/RevoEX/src/nwc24/NWC24MsgCommit.c`.
- `60d468a6cf34caa25f750095fc541cf234f1e65d`: `libs/RevoEX/src/nhttp/NHTTP_thread.c`.
- `682ec84e8f7552ab0ca6aa0b814d2bf814099d90`: `libs/RevoEX/src/nhttp/NHTTP_request.c`.
- `b192d817ef510c4938065c5ae4f747fc12b943cf`: `libs/RVL_SDK/src/sdi/sdi_api.c`.
- `37cc96285e744209175c28040ca6b6744bfb8c23`: `libs/RVL_SDK/src/os/OSPlayTime.c`.
- `eabe15c8774d5d6c1afa024c05eba5dd3546becd`: `libs/RVL_SDK/src/vi/vi3in1.c`.
- `20bb756172f3f73857bf64c503c857c79779f38d`: `libs/RVL_SDK/src/wpad/WPAD.c`.
- `cabdc7a09a49096ddc1554b2221b5364c9e75ae6`: `libs/RVL_SDK/src/card/CARDMount.c`.
- `db1249c7b9f2858104530920229a96158e497166`: `libs/RVL_SDK/src/nand/NANDOpenClose.c`.
- `83931f879c191defd054e6b0a86959ea08a13d10`: `libs/RVL_SDK/src/arc/arc.c`.

## Final verification

Final committed-source gate: GATE PASS. Full 43U build and build/43U/ok pass; all 308 owned functions are instruction-exact and every reported code/data section is 100%. Zero regressions, forbidden-pattern additions or readability warnings. All 16 complete baseline objects, including MWCC linker metadata, remain identical after normalizing only WPAD's generated line-number helper name.

Fresh report: DECOMPLETE_OK; all 1028 units and 12563 functions remain exact and linked. Fresh unit measures and all code/data/function entries equal the initial complete baseline. ASM INVENTORY PASS retains 162 original functions, 164 bodies/blocks, zero placeholders. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. git diff --check passes.

All 16 raw pools match the baseline. Fifteen match retail directly; NANDOpenClose retains the unchanged trailing canYouAlignMe string at offset 64, beyond the retail-owned data. The final linked data and DOL match exactly. All 30 focused ctxdiff checks report diffs 0 and equal instruction counts.

| Unit | Exact functions before -> after | Code | Data |
| --- | --- | --- | --- |
| `libs/RVL_SDK/src/nup/nup` | 23/23 -> 23/23 | 10764/10764 | 1720/1720 |
| `libs/RVL_SDK/src/nup/nup_nhttp` | 9/9 -> 9/9 | 2588/2588 | 144/144 |
| `libs/RevoEX/src/nwc24/NWC24MsgSubject` | 12/12 -> 12/12 | 5352/5352 | 232/232 |
| `libs/RevoEX/src/nwc24/NWC24MsgCommit` | 18/18 -> 18/18 | 8532/8532 | 904/904 |
| `libs/RevoEX/src/nhttp/NHTTP_thread` | 26/26 -> 26/26 | 11292/11292 | 504/504 |
| `libs/RevoEX/src/nhttp/NHTTP_request` | 7/7 -> 7/7 | 2512/2512 | 48/48 |
| `libs/RevoEX/src/wd/WDScan` | 5/5 -> 5/5 | 2180/2180 | 16/16 |
| `libs/RVL_SDK/src/sdi/sdi_api` | 22/22 -> 22/22 | 5948/5948 | 248/248 |
| `libs/RVL_SDK/src/os/OSPlayTime` | 7/7 -> 7/7 | 2176/2176 | 160/160 |
| `libs/RVL_SDK/src/vi/vi3in1` | 18/18 -> 18/18 | 6976/6976 | 1512/1512 |
| `libs/RVL_SDK/src/wpad/WPAD` | 67/67 -> 67/67 | 31040/31040 | 15096/15096 |
| `libs/RVL_SDK/src/card/CARDMount` | 7/7 -> 7/7 | 2380/2380 | 64/64 |
| `libs/RVL_SDK/src/fa/driver/sd_drv` | 26/26 -> 26/26 | 11760/11760 | 3592/3592 |
| `libs/RVL_SDK/src/nand/NANDOpenClose` | 22/22 -> 22/22 | 5056/5056 | 88/88 |
| `libs/RVL_SDK/src/arc/arc` | 14/14 -> 14/14 | 2464/2464 | 120/120 |
| `libs/NW4R/src/snd/snd_AxManager` | 25/25 -> 25/25 | 6364/6364 | 42040/42040 |

Evidence: `/tmp/clean3-c5-final-gate-committed.log`, `/tmp/clean3-c5-final-checks.log`, `/tmp/clean3-c5-final-pools.log`, `/tmp/clean3-c5-final-ctxdiff.log`, `/tmp/clean3-c5-source-commits.json`.

GATE PASS
