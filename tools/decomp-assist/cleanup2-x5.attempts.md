# cleanup2-x5 attempts

Baseline d83fa089e2d7d256ad9295e803a9484f042a5bfa. Assigned libs/RevoEX except NWC24MsgSubject.c and WDScan.c. Initial full 43U build passed, all 1028 units exact and linked, DECOMPLETE_OK, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Existing unrelated untracked files preserved.

Each function trial builds its object and compares every byte with the initial exact object. Failed trials restore the prior source and rebuild it. No function-scoped optimization pragmas or comma conditions appeared in the initial owned-source scan.

## Trials
- REVERTED libs/RevoEX/src/vf/fatfs/pf_fat.c: VFiPFFAT_ReadFATSector: replace retry gotos with continue; changed sections .text,.rela.text,.symtab; instructions 75/76, differences 13.
- REVERTED libs/RevoEX/src/vf/fatfs/pf_fat.c: VFiPFFAT_FindClusterLinkPage: replace exit labels with structured return and fallthrough; changed sections .text,.rela.text,.symtab; instructions 106/107, differences 86.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat.c: VFiPFFAT_GetClusterAllocatedInChain: replace loop exit goto with break; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat.c: file: rename saved free-cluster search start; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat.c: VFiPFFAT_ReadFATSector: express retry loop as do/while; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat.c: VFiPFFAT_FindClusterLinkPage: use sibling-style guarded cluster lookup with separate empty result; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_file.c: VFiPFFILE_p_fopen: replace file-open join gotos with if/else; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpen_: replace SD-decrypt entry and result gotos with if/else; changed sections .text,.strtab; instructions 109/109, differences 0.
- REVERTED libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpenReadOnly_: replace SD-decrypt entry and result gotos with if/else; changed sections .text,.strtab; instructions 93/93, differences 0.
- REVERTED libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordGetId: replace result switch and exit gotos with guarded ID extraction; changed sections .text,.rela.text,.symtab,.strtab; instructions 65/66, differences 16.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat.c: file: remove extra blank line at guarded lookup join; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c: VFiPFENT_ITER_DoAllocateEntry: replace emulated entry scan loop and middle-block jumps with while/break; changed sections .strtab; instructions 259/259, differences 0.
- KEPT libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c: VFiPFENT_ITER_DoGetEntryOfPath: replace directory-resolution join goto with if/else; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c: file: remove obsolete decompiler note; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c: VFiPFENT_ITER_DoAllocateEntry: replace emulated entry scan loop with while/break; check removed local labels separately; changed sections .strtab; instructions 259/259, differences 0.
- KEPT libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c: VFiPFENT_ITER_DoAllocateEntry: replace emulated entry scan loop with while/break; check removed local labels separately; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- REVERTED libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpen_: structure SD-decrypt branches; separate phases while preserving later OSPanic line; changed sections .text,.strtab; instructions 109/109, differences 0.
- REVERTED libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpenReadOnly_: structure SD-decrypt branches; separate phases while preserving later OSPanic line; changed sections .text,.strtab; instructions 93/93, differences 0.
- KEPT libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpen_: structure SD-decrypt branches with phase spacing; later native panic remains at line 772; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordOpenReadOnly_: structure SD-decrypt branches with phase spacing; later native panic remains at line 772; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat16.c: VFiPFFAT16_ReadFATEntryPage: replace FAT page retry labels with guarded callback and continue; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat16.c: VFiPFFAT16_WriteFATEntryPage: replace FAT page retry labels with guarded callback and continue; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat32.c: VFiPFFAT32_ReadFATEntryPage: replace FAT page retry labels with guarded callback and continue; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat32.c: VFiPFFAT32_WriteFATEntryPage: replace FAT page retry labels with guarded callback and continue; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat12.c: VFiPFFAT12_WriteFATEntryPage: structure repeated FAT page retry macro and remove generated-label concatenation macros; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_entry.c: VFiPFENT_RemoveEntry: replace optional cache-flush goto with guarded flush; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/vf/fatfs/pf_volume.c: VFiPFVOL_attach: remove redundant final goto and unreachable return; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/vf/dskmng/pdm_partition.c: VFipdm_part_get_permission: replace status-check and success gotos with direct control flow; changed sections .text,.rela.text; instructions 118/118, differences 43.
- REVERTED libs/RevoEX/src/vf/driver/pf_driver.c: VFiPFDRV_lerase: replace successful erase goto with direct return; changed sections .text,.rela.text; instructions 32/32, differences 13.
- KEPT libs/RevoEX/src/so/SOCommon.c: SOStartupEx: replace emulated startup retry loop with for/continue; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/so/SOCommon.c: file: name retained allocated socket work buffer address; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/cdb/CDBRecord.c: CDBRecordGetId: remove redundant default-case cleanup jump; keep shared unlock exit; code, data, relocations and symbol-table bytes identical; only compiler-generated local literal names changed in .strtab.
- KEPT libs/RevoEX/src/vf/driver/pf_driver.c: VFiPFDRV_lerase: guard erase error path and retain shared success return; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/dskmng/pdm_partition.c: VFipdm_part_get_permission: structure partition permission guard with terminal error else; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/dskmng/pdm_partition.c: VFipdm_part_get_start_sector: replace primary and extended partition success jumps with structured branches and break; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/dskmng/pdm_mbr.c: VFipdm_mbr_get_mbr_part_table: replace MBR success goto with validation else; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/dskmng/pdm_mbr.c: VFipdm_mbr_get_epbr_part_table: remove extended partition success join label; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/nhttp/NHTTP_recvbuf.c: NHTTPi_compareTokenN_HdrRecvBuf: replace goto-based character reads with existing ReadHeaderChar helper; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/nwc24/NWC24System.c: NWC24iPrepareShutdown: replace fatal-status goto with break and guarded LED setup; changed sections .text,.rela.text,.symtab,.strtab; instructions 50/48, differences 18.
- REVERTED libs/RevoEX/src/nwc24/NWC24System.c: NWC24iPrepareShutdown: structure status polling loop with fatal exit, busy retry and LED setup; changed sections .strtab; instructions 48/48, differences 0.
- REVERTED libs/RevoEX/src/nwc24/NWC24DateParser.c: ConvertDateToDays: replace leap-February validation goto with explicit date cases; changed sections .text,.rela.text,.symtab; instructions 123/113, differences 72.
- REVERTED libs/RevoEX/src/nwc24/NWC24System.c: NWC24iPrepareShutdown: check symbol-only changes in structured status polling loop; changed sections .strtab; instructions 48/48, differences 0.
- KEPT libs/RevoEX/src/nwc24/NWC24System.c: NWC24iPrepareShutdown: structure shutdown status loop; verify generated static suffix names only; code, data, relocations and symbol-table bytes identical; only compiler-generated local symbol suffixes changed in .strtab.
- KEPT libs/RevoEX/src/so/SOCommon.c: file: refine buffer name from same-offset HostReply field in SOInformation.c; code, data, relocations and symbol-table bytes identical; only compiler-generated local symbol suffixes changed in .strtab.
- REVERTED libs/RevoEX/src/nwc24/NWC24Download.c: file: try removing scoped dont_inline directives; changed sections .text,.rela.text,.symtab,.strtab.
- REVERTED libs/RevoEX/src/vf/develop/d_vf_sys.c: file: try removing scoped dont_inline directives; changed sections .text,.rela.text,.rela.sdata,.symtab,.strtab,.comment.
- REVERTED libs/RevoEX/src/cdb/CDBRecordKey.c: file: try removing scoped dont_inline directives; changed sections .text,.rela.text,.symtab,.strtab,.comment.
- REVERTED libs/RevoEX/src/cdb/CDBIntArray.c: file: try removing scoped dont_inline directives; changed sections .text,.rela.text,.symtab.
- REVERTED libs/RevoEX/src/so/SOCommon.c: file: try removing scoped dont_inline directives; changed sections .text,.rela.text,.symtab,.strtab.
- KEPT libs/RevoEX/src/net/neterrorcode.c: file: try removing connection-type prototype inline control; whole built object byte-identical to initial exact object.
- REVERTED libs/RevoEX/src/net/neterrorcode.c: file: try removing startup-error scoped inline control; changed sections .text,.rela.text,.symtab,.strtab.
- KEPT libs/RevoEX/src/nwc24/NWC24Download.c: file: document retained inline control after byte-changing removal trial; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/develop/d_vf_sys.c: file: document retained inline control after byte-changing removal trial; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/cdb/CDBRecordKey.c: file: document retained inline control after byte-changing removal trial; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/cdb/CDBIntArray.c: file: document retained inline control after byte-changing removal trial; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/so/SOCommon.c: file: document retained inline control after byte-changing removal trial; code, data, relocations and symbol-table bytes identical; only compiler-generated local symbol suffixes changed in .strtab.
- KEPT libs/RevoEX/src/net/neterrorcode.c: file: document retained inline control after byte-changing removal trial; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/nwc24/NWC24DateParser.c: ConvertDateToDays: document retained leap-day join after structured validation changed instructions; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/fatfs/pf_fat12.c: VFiPFFAT12_WriteFATEntryPage: align macro continuation spacing after label removal; whole built object byte-identical to initial exact object.
- KEPT libs/RevoEX/src/vf/dskmng/pdm_partition.c: VFipdm_part_get_permission: remove excess blank line at permission branch join; whole built object byte-identical to initial exact object.

## Audit decisions

- Largest files CDBDatabase.c and NHTTP_thread.c contain function-call argument commas, not comma operators in conditions. The balanced condition scan found no comma-expression conditions in the owned files.
- Retained common cleanup exits in NHTTP_request.c, NWC24MsgCommit.c, NWC24MsgRead.c, NWC24FriendList.c, NWC24MBoxCtrl.c, NWC24Download.c, d_vf.c, sd_drv.c, SOInit/SOStartupEx and CDBRecordGetId. They share close, unlock, error-reporting or state-restoration paths, as permitted by wave-2 guidance.
- Retained ConvertDateToDays leap-day join, documented inline. Its structured validation trial grew 113 instructions to 123 and changed 72 instruction positions.
- Retained scoped dont_inline controls in NWC24Download.c, d_vf_sys.c, CDBRecordKey.c, CDBIntArray.c, SOCommon.c and NETGetStartupErrorCode, documented at the directives. Removal changed object code or call relocations. The redundant NETiGetConnectionTypeFromConfigList prototype controls were removed exactly.
- Kept arg1 in the user-ID generation interface because the fourth ioctl result word has no demonstrated meaning in this checkout. SOCommon.unk10 was identified as the HostReply allocation by SOInformation.c and renamed hostReplyAddr.
- Native CDBRecordDuplicate OSPanic stays at source line 772. Spacing between open phases preserves its existing __LINE__ value without changing the assertion or adding a directive.
- Object comparisons allow only generated local symbol-name suffix changes when every other ELF section, including code, data, relocations and raw symbol-table entries, is byte-identical. No compiled byte or relocation change was retained.


## Final validation

GATE PASS over all 21 modified units using gate.py --quick with fixed baseline d83fa089e2d7d256ad9295e803a9484f042a5bfa. Full build passed, all 357 owned functions remain instruction-exact, 0 regressions, 0 added forbidden patterns, 0 readability warnings. Regenerated live report passed DECOMPLETE_OK. Code and data remain 100% matched and linked across all 1028 units. Global fuzzy measure remains at the unchanged baseline value 99.999886. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

Removed 43 goto statements in the modified files, two generated-label concatenation macros, two redundant dont_inline directives and one unreachable return. Renamed initial_search_cluster and hostReplyAddr. NWC24MsgSubject.c and WDScan.c are unchanged.

| File | Exact functions before/after | Commit |
|---|---:|---|
| libs/RevoEX/src/cdb/CDBIntArray.c | 13/13 -> 13/13 | ed8b5a31 |
| libs/RevoEX/src/cdb/CDBRecord.c | 29/29 -> 29/29 | aff3c409 |
| libs/RevoEX/src/cdb/CDBRecordKey.c | 20/20 -> 20/20 | daedc017 |
| libs/RevoEX/src/net/neterrorcode.c | 4/4 -> 4/4 | 32abb56c |
| libs/RevoEX/src/nhttp/NHTTP_recvbuf.c | 7/7 -> 7/7 | 36e3ec8b |
| libs/RevoEX/src/nwc24/NWC24DateParser.c | 8/8 -> 8/8 | 8334af1d |
| libs/RevoEX/src/nwc24/NWC24Download.c | 30/30 -> 30/30 | b6b3cb09 |
| libs/RevoEX/src/nwc24/NWC24System.c | 4/4 -> 4/4 | 64bdf6d5 |
| libs/RevoEX/src/so/SOCommon.c | 16/16 -> 16/16 | ed490fc1 |
| libs/RevoEX/src/vf/develop/d_vf_sys.c | 59/59 -> 59/59 | 4f0d05ca |
| libs/RevoEX/src/vf/driver/pf_driver.c | 14/14 -> 14/14 | 23f7f02a |
| libs/RevoEX/src/vf/dskmng/pdm_mbr.c | 4/4 -> 4/4 | 78cdd465 |
| libs/RevoEX/src/vf/dskmng/pdm_partition.c | 19/19 -> 19/19 | 43a893b3 |
| libs/RevoEX/src/vf/fatfs/pf_entry.c | 22/22 -> 22/22 | 09c3e5aa |
| libs/RevoEX/src/vf/fatfs/pf_entry_iterator.c | 15/15 -> 15/15 | 3a78906a |
| libs/RevoEX/src/vf/fatfs/pf_fat.c | 37/37 -> 37/37 | cf96cfa7 |
| libs/RevoEX/src/vf/fatfs/pf_fat12.c | 4/4 -> 4/4 | fbf6e428 |
| libs/RevoEX/src/vf/fatfs/pf_fat16.c | 4/4 -> 4/4 | cb8d66ab |
| libs/RevoEX/src/vf/fatfs/pf_fat32.c | 4/4 -> 4/4 | 2cc38bb7 |
| libs/RevoEX/src/vf/fatfs/pf_file.c | 24/24 -> 24/24 | a5bfb7c5 |
| libs/RevoEX/src/vf/fatfs/pf_volume.c | 20/20 -> 20/20 | e5e37ae0 |
