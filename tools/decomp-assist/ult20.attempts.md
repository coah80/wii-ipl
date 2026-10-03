# ult20, 2026-10-03

Worktree data-d5; branch agent/w1003/sol-ult20-ultra. Read ult20.md, AGENTS.md, unslop, coah-voice, previous unit attempts, effort policy and reference index. No prior-art entries for these units. Required harness commentary conflicts with requested silence; recorded here. All experiments and edits stay in this leaf or /tmp.

Baseline: NWC24Download 27/30 instruction-exact, code 9304/12496, data 80/80. exif_parse 3/6, code 1348/5088, no data bytes, data 100%. Both pools identical. Target and source disassemblies are saved in /tmp/ult20.

BEGIN AddTaskInternal: origin/main e3095dfb979ded66d2b6a71228563066c5445f5a, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT AddTaskInternal | word-width task-count arguments, short directory iterator proven by validation then clrlwi | 70a2fc06a47c | objdiff 97.14464% | metric (24, 323), insns 398/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main e3095dfb979ded66d2b6a71228563066c5445f5a, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate strip exit and signed TIFF rational offset | e339dc5d3b10 | objdiff 95.05372% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate strip exit and mutable rational cursor | 22e3fb716b46 | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit with rational numerator cursor and denominator cursor separately scoped | f68321801d20 | BUILD FAIL leware/TMC_JPEG/src/exif/exif_parse.d
### mwcceppc.exe Compiler:
#    File: libs\RVLMiddleware\TMC_JPEG\src\exif\exif_parse.c
# ----------------------------------------------------------
#     524:             const u8* denominator = pInfo->thumbnailData + (offset + 4); 
#   Error:             ^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit with const offset local initialized at definition | 1479d936b28f | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit with signed pointer-distance bounds preserving unsigned TIFF offset | 218e3f18ea4e | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit after ignored block, offset read through typed output helper | c7c561702aa4 | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit after ignored block, output helper and cursor declared before offset | e2d5cc8fbf84 | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip exit after ignored block, distinct numerator and denominator cursors | a8f9ea250b83 | objdiff 95.54958% | metric (17, 228), insns 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273] break; with group break; | f4080a18dd2f | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273] break; with group return; | 33e400696d2a | objdiff 95.91736% | metric (20, 233), insns 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273, 274] break; with group break; | 2fec20ff7b05 | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273, 284] break; with group break; | e71ece923559 | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273, 274, 284] break; with group break; | d0d93d9026ac | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273, 306] break; with group break; | 3a9616220dae | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual ignored cases [273, 284] return; with group break; | c2cbcc9abcc4 | objdiff 97.38843% | metric (16, 231), insns 245/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []

Prior-art correction from parent: read-only gh search/API used with explicit authorization. Retrieved hotlandsoftware/wii-news-channel at ce95adf7a3a57345f5250cd296aed7656ceb886e, src/revolution/NWC24/NWC24Download.c and its internal header. URL: https://github.com/hotlandsoftware/wii-news-channel/blob/ce95adf7a3a57345f5250cd296aed7656ceb886e/src/revolution/NWC24/NWC24Download.c . Their Init uses an immediately initialized implementation pointer before homeDir, octet-stream predicate helper, direct final Check result; Update uses typed last-access/error-clear helpers and const retry task; Add uses typed implementation arguments, CheckDlUrl as a separate inline boundary, and calls public Update. Read-only search found only declarations in the Asu-chan source. No other repository contacted for writes.
ATTEMPT AddTaskInternal | News Channel string validation nested in task-parameter validation helper | a64136937080 | objdiff 96.38404% | metric (23, 328), insns 398/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | News Channel nested URL boundary and word-width allocation bounds | a87399b275b6 | objdiff 97.4813% | metric (11, 329), insns 400/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | News Channel directory-entry inline helper preserves narrowing boundary | 0f28c151b286 | objdiff 97.4813% | metric (11, 329), insns 400/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN NWC24InitDlTask: origin/main b7d9c4fb65392cdb115b4004c28b4dc8a34e1d34, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT NWC24InitDlTask | News Channel implementation pointer initialized before home buffer declaration | 09023515b4ea | objdiff 98.923615% | metric (0, 31), insns 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | News Channel implementation-first initializer and octet-stream helper boundary | a9fea9d57a10 | objdiff 98.923615% | metric (0, 31), insns 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | News Channel typed memset and direct validation return | 54049e23f477 | objdiff 98.923615% | metric (0, 31), insns 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN NWC24UpdateDlTask: origin/main b7d9c4fb65392cdb115b4004c28b4dc8a34e1d34, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT NWC24UpdateDlTask | News Channel typed retry validation and conditional mask result | d55e5f60aa38 | objdiff 99.40711% | metric (0, 30), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | current writable validation at both nested update sites with typed retry helper | e40dd3ffc8e2 | objdiff 97.69327% | metric (6, 329), insns 400/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | News Channel error reset helper status scoped separately from update status | e5ca2b7016f1 | objdiff 99.40711% | metric (0, 30), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | News Channel last-access helpers use read-only task views with scoped reset | aef0c2197814 | objdiff 99.565216% | metric (0, 22), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group predicate owns boolean, flags and groupId outside validation helper | 589edb2c2007 | objdiff 99.80237% | metric (0, 10), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group predicate receives identifier and flags with explicit allowed return | 30370f31820f | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group predicate receives flags before identifier with explicit allowed return | a4689e34c018 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | ownership result scoped as group-writable boolean after flags-first predicate | 33403a6ffbbd | objdiff 99.80237% | metric (0, 10), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | separate group predicate materializes default result after identifier local | e07ec63f1232 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | separate group predicate copies identifier after default result | a85d349565e2 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | separate group predicate uses one return expression for flag and identifier match | b1832b534300 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

## Target basic blocks and source statements


NWC24InitDlTask call sequence: _savegpr_27, NANDGetHomeDir, strtoul, strtoul, memset, NWC24GetAppId, NWC24GetGroupId, strcpy, NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, _restgpr_27.
BB 0x0..0x10: initialize homePath, save task/type; terminator bl 0x10   ; _savegpr_27.
BB 0x14..0x64: initialize homePath, save task/type; terminator bl 0x64   ; NANDGetHomeDir.
BB 0x68..0x78: NANDGetHomeDir; terminate and parse high/low IDs; terminator bl 0x78   ; strtoul.
BB 0x7c..0x90: NANDGetHomeDir; terminate and parse high/low IDs; terminator bl 0x90   ; strtoul.
BB 0x94..0xa0: acquire header; require open library/task/type; terminator beq 0xa8.
BB 0xa4..0xa4: acquire header; require open library/task/type; terminator addi r29, r4, 0x3600.
BB 0xa8..0xac: acquire header; require open library/task/type; terminator bne 0xb8.
BB 0xb0..0xb4: acquire header; require open library/task/type; terminator b 0x228.
BB 0xb8..0xbc: acquire header; require open library/task/type; terminator bne 0xc8.
BB 0xc0..0xc4: acquire header; require open library/task/type; terminator b 0x228.
BB 0xc8..0xcc: acquire header; require open library/task/type; terminator blt 0xd8.
BB 0xd0..0xd4: acquire header; require open library/task/type; terminator b 0x228.
BB 0xd8..0xe4: memset task; assign type, priority, appId/groupId/IDs and defaults; terminator bl 0xe4   ; memset.
BB 0xe8..0xf4: memset task; assign type, priority, appId/groupId/IDs and defaults; terminator bl 0xf4   ; NWC24GetAppId.
BB 0xf8..0xfc: memset task; assign type, priority, appId/groupId/IDs and defaults; terminator bl 0xfc   ; NWC24GetGroupId.
BB 0x100..0x134: memset task; assign type, priority, appId/groupId/IDs and defaults; terminator beq 0x140.
BB 0x138..0x13c: octet-stream predicate; strcpy content.bin; terminator bne 0x148.
BB 0x140..0x144: octet-stream predicate; strcpy content.bin; terminator b 0x14c.
BB 0x148..0x148: octet-stream predicate; strcpy content.bin; terminator li r0, 0.
BB 0x14c..0x150: octet-stream predicate; strcpy content.bin; terminator beq 0x164.
BB 0x154..0x160: octet-stream predicate; strcpy content.bin; terminator bl 0x160   ; strcpy.
BB 0x164..0x16c: ValidateDlTask: header/task null guards; terminator beq 0x178.
BB 0x170..0x174: ValidateDlTask: header/task null guards; terminator b 0x17c.
BB 0x178..0x178: ValidateDlTask: header/task null guards; terminator li r29, 0.
BB 0x17c..0x180: ValidateDlTask: header/task null guards; terminator bne 0x18c.
BB 0x184..0x188: ValidateDlTask: header/task null guards; terminator b 0x224.
BB 0x18c..0x190: ValidateDlTask: header/task null guards; terminator bne 0x19c.
BB 0x194..0x198: ValidateDlTask: header/task null guards; terminator b 0x224.
BB 0x19c..0x19c: tool exemption and app owner predicate; terminator bl 0x19c   ; NWC24IsMsgLibOpenedByTool.
BB 0x1a0..0x1a4: tool exemption and app owner predicate; terminator bne 0x200.
BB 0x1a8..0x1ac: tool exemption and app owner predicate; terminator bl 0x1ac   ; NWC24GetAppId.
BB 0x1b0..0x1c4: tool exemption and app owner predicate; terminator bne 0x200.
BB 0x1c8..0x1d8: group writable flag and groupId predicate; terminator beq 0x1f0.
BB 0x1dc..0x1dc: group writable flag and groupId predicate; terminator bl 0x1dc   ; NWC24GetGroupId.
BB 0x1e0..0x1e8: group writable flag and groupId predicate; terminator bne 0x1f0.
BB 0x1ec..0x1ec: group writable flag and groupId predicate; terminator li r30, 1.
BB 0x1f0..0x1f4: group writable flag and groupId predicate; terminator bne 0x200.
BB 0x1f8..0x1fc: group writable flag and groupId predicate; terminator b 0x224.
BB 0x200..0x208: id bounds validation; terminator beq 0x220.
BB 0x20c..0x214: id bounds validation; terminator blt 0x220.
BB 0x218..0x21c: id bounds validation; terminator b 0x224.
BB 0x220..0x220: id bounds validation; terminator li r0, 0.
BB 0x224..0x224: return sign of validation status; restore frame; terminator srawi r3, r0, 0x1f.
BB 0x228..0x22c: return sign of validation status; restore frame; terminator bl 0x22c   ; _restgpr_27.
BB 0x230..0x23c: return sign of validation status; restore frame; terminator blr .

NWC24UpdateDlTask call sequence: NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, NWC24iGetUniversalTime, __div2i, NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, StoreDlTask.
BB 0xdd0..0xdf8: save task and four saved registers; terminator beq 0xe04.
BB 0xdfc..0xe00: writable validation: cached header/task null guards; terminator b 0xe08.
BB 0xe04..0xe04: writable validation: cached header/task null guards; terminator li r28, 0.
BB 0xe08..0xe0c: writable validation: cached header/task null guards; terminator bne 0xe18.
BB 0xe10..0xe14: writable validation: cached header/task null guards; terminator b 0xeb0.
BB 0xe18..0xe1c: writable validation: cached header/task null guards; terminator bne 0xe28.
BB 0xe20..0xe24: writable validation: cached header/task null guards; terminator b 0xeb0.
BB 0xe28..0xe28: tool exemption and owner predicate; terminator bl 0xe28   ; NWC24IsMsgLibOpenedByTool.
BB 0xe2c..0xe30: tool exemption and owner predicate; terminator bne 0xe8c.
BB 0xe34..0xe38: tool exemption and owner predicate; terminator bl 0xe38   ; NWC24GetAppId.
BB 0xe3c..0xe50: tool exemption and owner predicate; terminator bne 0xe8c.
BB 0xe54..0xe64: group write predicate with independent BOOL; terminator beq 0xe7c.
BB 0xe68..0xe68: group write predicate with independent BOOL; terminator bl 0xe68   ; NWC24GetGroupId.
BB 0xe6c..0xe74: group write predicate with independent BOOL; terminator bne 0xe7c.
BB 0xe78..0xe78: group write predicate with independent BOOL; terminator li r30, 1.
BB 0xe7c..0xe80: group write predicate with independent BOOL; terminator bne 0xe8c.
BB 0xe84..0xe88: group write predicate with independent BOOL; terminator b 0xeb0.
BB 0xe8c..0xe94: id bounds; return validation error; terminator beq 0xeac.
BB 0xe98..0xea0: id bounds; return validation error; terminator blt 0xeac.
BB 0xea4..0xea8: id bounds; return validation error; terminator b 0xeb0.
BB 0xeac..0xeac: id bounds; return validation error; terminator li r3, 0.
BB 0xeb0..0xeb4: id bounds; return validation error; terminator beq 0xebc.
BB 0xeb8..0xeb8: id bounds; return validation error; terminator b 0x11a4.
BB 0xebc..0xec4: existing task id required; terminator beq 0xeec.
BB 0xec8..0xed0: existing task id required; terminator beq 0xedc.
BB 0xed4..0xed8: existing task id required; terminator b 0xee0.
BB 0xedc..0xedc: existing task id required; terminator li r3, 0.
BB 0xee0..0xee8: existing task id required; terminator blt 0xef4.
BB 0xeec..0xef0: existing task id required; terminator b 0x11a4.
BB 0xef4..0xef8: GetUniversalTime; handle error; terminator bl 0xef8   ; NWC24iGetUniversalTime.
BB 0xefc..0xf00: GetUniversalTime; handle error; terminator blt 0xfc8.
BB 0xf04..0xf14: read-only access-time validation using cached work; terminator beq 0xf20.
BB 0xf18..0xf1c: read-only access-time validation using cached work; terminator b 0xf24.
BB 0xf20..0xf20: read-only access-time validation using cached work; terminator li r5, 0.
BB 0xf24..0xf28: read-only access-time validation using cached work; terminator bne 0xf34.
BB 0xf2c..0xf30: read-only access-time validation using cached work; terminator b 0xf68.
BB 0xf34..0xf38: read-only access-time validation using cached work; terminator bne 0xf44.
BB 0xf3c..0xf40: read-only access-time validation using cached work; terminator b 0xf68.
BB 0xf44..0xf4c: read-only access-time validation using cached work; terminator beq 0xf64.
BB 0xf50..0xf58: read-only access-time validation using cached work; terminator blt 0xf64.
BB 0xf5c..0xf60: read-only access-time validation using cached work; terminator b 0xf68.
BB 0xf64..0xf64: read-only access-time validation using cached work; terminator li r5, 0.
BB 0xf68..0xf6c: read-only access-time validation using cached work; terminator beq 0xf74.
BB 0xf70..0xf70: read-only access-time validation using cached work; terminator b 0xfb8.
BB 0xf74..0xf7c: require assigned id; divide OSTime by sixty; terminator bne 0xf88.
BB 0xf80..0xf84: require assigned id; divide OSTime by sixty; terminator b 0xfb8.
BB 0xf88..0xf90: require assigned id; divide OSTime by sixty; terminator bl 0xf90   ; __div2i.
BB 0xf94..0xf98: store directory lastAccess and join access status; terminator beq 0xfa4.
BB 0xf9c..0xfa0: store directory lastAccess and join access status; terminator b 0xfa8.
BB 0xfa4..0xfa4: store directory lastAccess and join access status; terminator li r3, 0.
BB 0xfa8..0xfb4: store directory lastAccess and join access status; terminator stw r4, 0x88(r3).
BB 0xfb8..0xfc0: store directory lastAccess and join access status; terminator bge 0xfc8.
BB 0xfc4..0xfc4: store directory lastAccess and join access status; terminator b 0xfcc.
BB 0xfc8..0xfc8: store directory lastAccess and join access status; terminator mr r5, r3.
BB 0xfcc..0xfd0: store directory lastAccess and join access status; terminator bge 0xfdc.
BB 0xfd4..0xfd8: store directory lastAccess and join access status; terminator b 0x11a4.
BB 0xfdc..0xfe4: clear error helper: header/task null guards; terminator beq 0xff0.
BB 0xfe8..0xfec: clear error helper: header/task null guards; terminator b 0xff4.
BB 0xff0..0xff0: clear error helper: header/task null guards; terminator li r28, 0.
BB 0xff4..0xff8: clear error helper: header/task null guards; terminator bne 0x1004.
BB 0xffc..0x1000: clear error helper: header/task null guards; terminator b 0x109c.
BB 0x1004..0x1008: clear error helper: header/task null guards; terminator bne 0x1014.
BB 0x100c..0x1010: clear error helper: header/task null guards; terminator b 0x109c.
BB 0x1014..0x1014: clear helper tool/owner predicate; terminator bl 0x1014   ; NWC24IsMsgLibOpenedByTool.
BB 0x1018..0x101c: clear helper tool/owner predicate; terminator bne 0x1078.
BB 0x1020..0x1024: clear helper tool/owner predicate; terminator bl 0x1024   ; NWC24GetAppId.
BB 0x1028..0x103c: clear helper tool/owner predicate; terminator bne 0x1078.
BB 0x1040..0x1050: clear helper group predicate; terminator beq 0x1068.
BB 0x1054..0x1054: clear helper group predicate; terminator bl 0x1054   ; NWC24GetGroupId.
BB 0x1058..0x1060: clear helper group predicate; terminator bne 0x1068.
BB 0x1064..0x1064: clear helper group predicate; terminator li r30, 1.
BB 0x1068..0x106c: clear helper group predicate; terminator bne 0x1078.
BB 0x1070..0x1074: clear helper group predicate; terminator b 0x109c.
BB 0x1078..0x1080: clear helper id bounds; clear fields on success; terminator beq 0x1098.
BB 0x1084..0x108c: clear helper id bounds; clear fields on success; terminator blt 0x1098.
BB 0x1090..0x1094: clear helper id bounds; clear fields on success; terminator b 0x109c.
BB 0x1098..0x1098: clear helper id bounds; clear fields on success; terminator li r0, 0.
BB 0x109c..0x10a0: clear helper id bounds; clear fields on success; terminator bne 0x10b0.
BB 0x10a4..0x10ac: clear helper id bounds; clear fields on success; terminator sth r0, 0x1a(r31).
BB 0x10b0..0x10b8: retry-enabled predicate; loop counter update; terminator bne 0x119c.
BB 0x10bc..0x10c0: retry-enabled predicate; loop counter update; terminator b 0x10d0.
BB 0x10c4..0x10cc: retry-enabled predicate; loop counter update; terminator stb r0, 0x24(r31).
BB 0x10d0..0x10dc: retry read-validation: acquire header and id bounds; terminator beq 0x10e8.
BB 0x10e0..0x10e4: retry read-validation: acquire header and id bounds; terminator b 0x10ec.
BB 0x10e8..0x10e8: retry read-validation: acquire header and id bounds; terminator li r3, 0.
BB 0x10ec..0x10f0: retry read-validation: acquire header and id bounds; terminator bne 0x10fc.
BB 0x10f4..0x10f8: retry read-validation: acquire header and id bounds; terminator b 0x1130.
BB 0x10fc..0x1100: retry read-validation: acquire header and id bounds; terminator bne 0x110c.
BB 0x1104..0x1108: retry read-validation: acquire header and id bounds; terminator b 0x1130.
BB 0x110c..0x1114: retry read-validation: acquire header and id bounds; terminator beq 0x112c.
BB 0x1118..0x1120: retry read-validation: acquire header and id bounds; terminator blt 0x112c.
BB 0x1124..0x1128: retry read-validation: acquire header and id bounds; terminator b 0x1130.
BB 0x112c..0x112c: retry read-validation: acquire header and id bounds; terminator li r3, 0.
BB 0x1130..0x1134: retry read-validation: acquire header and id bounds; terminator beq 0x113c.
BB 0x1138..0x1138: retry read-validation: acquire header and id bounds; terminator b 0x1188.
BB 0x113c..0x1144: check retryEnabled, retryMask and counter bounds; terminator bne 0x1150.
BB 0x1148..0x114c: check retryEnabled, retryMask and counter bounds; terminator b 0x1188.
BB 0x1150..0x1158: check retryEnabled, retryMask and counter bounds; terminator bne 0x1164.
BB 0x115c..0x1160: check retryEnabled, retryMask and counter bounds; terminator b 0x1188.
BB 0x1164..0x1168: check retryEnabled, retryMask and counter bounds; terminator ble 0x1174.
BB 0x116c..0x1170: check retryEnabled, retryMask and counter bounds; terminator b 0x1188.
BB 0x1174..0x1180: shift retry bit, test mask, propagate disabled/error; terminator bne 0x1188.
BB 0x1184..0x1184: shift retry bit, test mask, propagate disabled/error; terminator li r3, -0x27.
BB 0x1188..0x118c: shift retry bit, test mask, propagate disabled/error; terminator beq 0x10c4.
BB 0x1190..0x1194: shift retry bit, test mask, propagate disabled/error; terminator bge 0x119c.
BB 0x1198..0x1198: shift retry bit, test mask, propagate disabled/error; terminator b 0x11a4.
BB 0x119c..0x11a0: StoreDlTask; restore frame; terminator bl 0x11a0   ; StoreDlTask.
BB 0x11a4..0x11c0: StoreDlTask; restore frame; terminator blr .

AddTaskInternal call sequence: _savegpr_26, NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, NWC24iCheckStringLength, strncmp, strncmp, NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, NWC24iGetUniversalTime, __div2i, NWC24IsMsgLibOpenedByTool, NWC24GetAppId, NWC24GetGroupId, StoreDlTask, NWC24PurgeOldestDlTask, _restgpr_26.
BB 0x2850..0x2860: save task and bounds; writable validation header/task guards; terminator bl 0x2860   ; _savegpr_26.
BB 0x2864..0x2878: save task and bounds; writable validation header/task guards; terminator beq 0x2884.
BB 0x287c..0x2880: save task and bounds; writable validation header/task guards; terminator b 0x2888.
BB 0x2884..0x2884: save task and bounds; writable validation header/task guards; terminator li r26, 0.
BB 0x2888..0x288c: save task and bounds; writable validation header/task guards; terminator bne 0x2898.
BB 0x2890..0x2894: save task and bounds; writable validation header/task guards; terminator b 0x2930.
BB 0x2898..0x289c: save task and bounds; writable validation header/task guards; terminator bne 0x28a8.
BB 0x28a0..0x28a4: save task and bounds; writable validation header/task guards; terminator b 0x2930.
BB 0x28a8..0x28a8: tool exemption and owner predicate; terminator bl 0x28a8   ; NWC24IsMsgLibOpenedByTool.
BB 0x28ac..0x28b0: tool exemption and owner predicate; terminator bne 0x290c.
BB 0x28b4..0x28b8: tool exemption and owner predicate; terminator bl 0x28b8   ; NWC24GetAppId.
BB 0x28bc..0x28d0: tool exemption and owner predicate; terminator bne 0x290c.
BB 0x28d4..0x28e4: group write predicate; terminator beq 0x28fc.
BB 0x28e8..0x28e8: group write predicate; terminator bl 0x28e8   ; NWC24GetGroupId.
BB 0x28ec..0x28f4: group write predicate; terminator bne 0x28fc.
BB 0x28f8..0x28f8: group write predicate; terminator li r28, 1.
BB 0x28fc..0x2900: group write predicate; terminator bne 0x290c.
BB 0x2904..0x2908: group write predicate; terminator b 0x2930.
BB 0x290c..0x2914: id bounds; propagate validation error; terminator beq 0x292c.
BB 0x2918..0x2920: id bounds; propagate validation error; terminator blt 0x292c.
BB 0x2924..0x2928: id bounds; propagate validation error; terminator b 0x2930.
BB 0x292c..0x292c: id bounds; propagate validation error; terminator li r3, 0.
BB 0x2930..0x2934: id bounds; propagate validation error; terminator beq 0x293c.
BB 0x2938..0x2938: id bounds; propagate validation error; terminator b 0x2e7c.
BB 0x293c..0x2944: parameter validation: acquire header, id bounds; terminator beq 0x2950.
BB 0x2948..0x294c: parameter validation: acquire header, id bounds; terminator b 0x2954.
BB 0x2950..0x2950: parameter validation: acquire header, id bounds; terminator li r3, 0.
BB 0x2954..0x2960: parameter validation: acquire header, id bounds; terminator blt 0x2974.
BB 0x2964..0x2968: parameter validation: acquire header, id bounds; terminator beq 0x2974.
BB 0x296c..0x2970: parameter validation: acquire header, id bounds; terminator b 0x29e4.
BB 0x2974..0x2984: nested URL helper: length guard and http/https prefix; terminator bl 0x2984   ; NWC24iCheckStringLength.
BB 0x2988..0x298c: nested URL helper: length guard and http/https prefix; terminator bge 0x2994.
BB 0x2990..0x2990: nested URL helper: length guard and http/https prefix; terminator b 0x29d4.
BB 0x2994..0x29a0: nested URL helper: length guard and http/https prefix; terminator bl 0x29a0   ; strncmp.
BB 0x29a4..0x29a8: nested URL helper: length guard and http/https prefix; terminator beq 0x29d0.
BB 0x29ac..0x29bc: nested URL helper: length guard and http/https prefix; terminator bl 0x29bc   ; strncmp.
BB 0x29c0..0x29c4: nested URL helper: length guard and http/https prefix; terminator beq 0x29d0.
BB 0x29c8..0x29cc: nested URL helper: length guard and http/https prefix; terminator b 0x29d4.
BB 0x29d0..0x29d0: nested URL helper: length guard and http/https prefix; terminator li r3, 0.
BB 0x29d4..0x29dc: join URL status and propagate negative error; terminator bge 0x29e4.
BB 0x29e0..0x29e0: join URL status and propagate negative error; terminator mr r0, r3.
BB 0x29e4..0x29e8: join URL status and propagate negative error; terminator bge 0x29f4.
BB 0x29ec..0x29f0: join URL status and propagate negative error; terminator b 0x2e7c.
BB 0x29f4..0x29fc: assigned id chooses nested update; otherwise allocate; terminator beq 0x2dbc.
BB 0x2a00..0x2a08: nested update writable header/task guards; terminator beq 0x2a14.
BB 0x2a0c..0x2a10: nested update writable header/task guards; terminator b 0x2a18.
BB 0x2a14..0x2a14: nested update writable header/task guards; terminator li r26, 0.
BB 0x2a18..0x2a1c: nested update writable header/task guards; terminator bne 0x2a28.
BB 0x2a20..0x2a24: nested update writable header/task guards; terminator b 0x2ac0.
BB 0x2a28..0x2a2c: nested update writable header/task guards; terminator bne 0x2a38.
BB 0x2a30..0x2a34: nested update writable header/task guards; terminator b 0x2ac0.
BB 0x2a38..0x2a38: nested update tool and owner predicates; terminator bl 0x2a38   ; NWC24IsMsgLibOpenedByTool.
BB 0x2a3c..0x2a40: nested update tool and owner predicates; terminator bne 0x2a9c.
BB 0x2a44..0x2a48: nested update tool and owner predicates; terminator bl 0x2a48   ; NWC24GetAppId.
BB 0x2a4c..0x2a60: nested update tool and owner predicates; terminator bne 0x2a9c.
BB 0x2a64..0x2a74: nested update group write predicate; terminator beq 0x2a8c.
BB 0x2a78..0x2a78: nested update group write predicate; terminator bl 0x2a78   ; NWC24GetGroupId.
BB 0x2a7c..0x2a84: nested update group write predicate; terminator bne 0x2a8c.
BB 0x2a88..0x2a88: nested update group write predicate; terminator li r30, 1.
BB 0x2a8c..0x2a90: nested update group write predicate; terminator bne 0x2a9c.
BB 0x2a94..0x2a98: nested update group write predicate; terminator b 0x2ac0.
BB 0x2a9c..0x2aa4: nested update id bounds; propagate status; terminator beq 0x2abc.
BB 0x2aa8..0x2ab0: nested update id bounds; propagate status; terminator blt 0x2abc.
BB 0x2ab4..0x2ab8: nested update id bounds; propagate status; terminator b 0x2ac0.
BB 0x2abc..0x2abc: nested update id bounds; propagate status; terminator li r5, 0.
BB 0x2ac0..0x2ac4: nested update id bounds; propagate status; terminator beq 0x2acc.
BB 0x2ac8..0x2ac8: nested update id bounds; propagate status; terminator b 0x2db4.
BB 0x2acc..0x2ad4: require assigned task id; terminator beq 0x2afc.
BB 0x2ad8..0x2ae0: require assigned task id; terminator beq 0x2aec.
BB 0x2ae4..0x2ae8: require assigned task id; terminator b 0x2af0.
BB 0x2aec..0x2aec: require assigned task id; terminator li r3, 0.
BB 0x2af0..0x2af8: require assigned task id; terminator blt 0x2b04.
BB 0x2afc..0x2b00: require assigned task id; terminator b 0x2db4.
BB 0x2b04..0x2b08: GetUniversalTime and read-only access-time validation; terminator bl 0x2b08   ; NWC24iGetUniversalTime.
BB 0x2b0c..0x2b10: GetUniversalTime and read-only access-time validation; terminator blt 0x2bd8.
BB 0x2b14..0x2b24: GetUniversalTime and read-only access-time validation; terminator beq 0x2b30.
BB 0x2b28..0x2b2c: GetUniversalTime and read-only access-time validation; terminator b 0x2b34.
BB 0x2b30..0x2b30: GetUniversalTime and read-only access-time validation; terminator li r5, 0.
BB 0x2b34..0x2b38: GetUniversalTime and read-only access-time validation; terminator bne 0x2b44.
BB 0x2b3c..0x2b40: GetUniversalTime and read-only access-time validation; terminator b 0x2b78.
BB 0x2b44..0x2b48: GetUniversalTime and read-only access-time validation; terminator bne 0x2b54.
BB 0x2b4c..0x2b50: GetUniversalTime and read-only access-time validation; terminator b 0x2b78.
BB 0x2b54..0x2b5c: GetUniversalTime and read-only access-time validation; terminator beq 0x2b74.
BB 0x2b60..0x2b68: GetUniversalTime and read-only access-time validation; terminator blt 0x2b74.
BB 0x2b6c..0x2b70: GetUniversalTime and read-only access-time validation; terminator b 0x2b78.
BB 0x2b74..0x2b74: GetUniversalTime and read-only access-time validation; terminator li r5, 0.
BB 0x2b78..0x2b7c: GetUniversalTime and read-only access-time validation; terminator beq 0x2b84.
BB 0x2b80..0x2b80: GetUniversalTime and read-only access-time validation; terminator b 0x2bc8.
BB 0x2b84..0x2b8c: require assigned id and divide time; terminator bne 0x2b98.
BB 0x2b90..0x2b94: require assigned id and divide time; terminator b 0x2bc8.
BB 0x2b98..0x2ba0: require assigned id and divide time; terminator bl 0x2ba0   ; __div2i.
BB 0x2ba4..0x2ba8: store directory lastAccess; join status; terminator beq 0x2bb4.
BB 0x2bac..0x2bb0: store directory lastAccess; join status; terminator b 0x2bb8.
BB 0x2bb4..0x2bb4: store directory lastAccess; join status; terminator li r3, 0.
BB 0x2bb8..0x2bc4: store directory lastAccess; join status; terminator stw r4, 0x88(r3).
BB 0x2bc8..0x2bd0: store directory lastAccess; join status; terminator bge 0x2bd8.
BB 0x2bd4..0x2bd4: store directory lastAccess; join status; terminator b 0x2bdc.
BB 0x2bd8..0x2bd8: store directory lastAccess; join status; terminator mr r5, r3.
BB 0x2bdc..0x2be0: store directory lastAccess; join status; terminator bge 0x2be8.
BB 0x2be4..0x2be4: store directory lastAccess; join status; terminator b 0x2db4.
BB 0x2be8..0x2bf0: clear error writable header/task guards; terminator beq 0x2bfc.
BB 0x2bf4..0x2bf8: clear error writable header/task guards; terminator b 0x2c00.
BB 0x2bfc..0x2bfc: clear error writable header/task guards; terminator li r27, 0.
BB 0x2c00..0x2c04: clear error writable header/task guards; terminator bne 0x2c10.
BB 0x2c08..0x2c0c: clear error writable header/task guards; terminator b 0x2ca8.
BB 0x2c10..0x2c14: clear error writable header/task guards; terminator bne 0x2c20.
BB 0x2c18..0x2c1c: clear error writable header/task guards; terminator b 0x2ca8.
BB 0x2c20..0x2c20: clear error tool/owner predicates; terminator bl 0x2c20   ; NWC24IsMsgLibOpenedByTool.
BB 0x2c24..0x2c28: clear error tool/owner predicates; terminator bne 0x2c84.
BB 0x2c2c..0x2c30: clear error tool/owner predicates; terminator bl 0x2c30   ; NWC24GetAppId.
BB 0x2c34..0x2c48: clear error tool/owner predicates; terminator bne 0x2c84.
BB 0x2c4c..0x2c5c: clear error group predicate; terminator beq 0x2c74.
BB 0x2c60..0x2c60: clear error group predicate; terminator bl 0x2c60   ; NWC24GetGroupId.
BB 0x2c64..0x2c6c: clear error group predicate; terminator bne 0x2c74.
BB 0x2c70..0x2c70: clear error group predicate; terminator li r30, 1.
BB 0x2c74..0x2c78: clear error group predicate; terminator bne 0x2c84.
BB 0x2c7c..0x2c80: clear error group predicate; terminator b 0x2ca8.
BB 0x2c84..0x2c8c: clear error id bounds and successful stores; terminator beq 0x2ca4.
BB 0x2c90..0x2c98: clear error id bounds and successful stores; terminator blt 0x2ca4.
BB 0x2c9c..0x2ca0: clear error id bounds and successful stores; terminator b 0x2ca8.
BB 0x2ca4..0x2ca4: clear error id bounds and successful stores; terminator li r0, 0.
BB 0x2ca8..0x2cac: clear error id bounds and successful stores; terminator bne 0x2cbc.
BB 0x2cb0..0x2cb8: clear error id bounds and successful stores; terminator sth r0, 0x1a(r29).
BB 0x2cbc..0x2cc4: retry-enabled guard and loop; terminator bne 0x2da8.
BB 0x2cc8..0x2ccc: retry-enabled guard and loop; terminator b 0x2cdc.
BB 0x2cd0..0x2cd8: increment retryCount modulo32; terminator stb r0, 0x24(r29).
BB 0x2cdc..0x2ce8: retry read-validation header/task/id guards; terminator beq 0x2cf4.
BB 0x2cec..0x2cf0: retry read-validation header/task/id guards; terminator b 0x2cf8.
BB 0x2cf4..0x2cf4: retry read-validation header/task/id guards; terminator li r3, 0.
BB 0x2cf8..0x2cfc: retry read-validation header/task/id guards; terminator bne 0x2d08.
BB 0x2d00..0x2d04: retry read-validation header/task/id guards; terminator b 0x2d3c.
BB 0x2d08..0x2d0c: retry read-validation header/task/id guards; terminator bne 0x2d18.
BB 0x2d10..0x2d14: retry read-validation header/task/id guards; terminator b 0x2d3c.
BB 0x2d18..0x2d20: retry read-validation header/task/id guards; terminator beq 0x2d38.
BB 0x2d24..0x2d2c: retry enabled/mask/count/bit tests; join retry result; terminator blt 0x2d38.
BB 0x2d30..0x2d34: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2d3c.
BB 0x2d38..0x2d38: retry enabled/mask/count/bit tests; join retry result; terminator li r3, 0.
BB 0x2d3c..0x2d40: retry enabled/mask/count/bit tests; join retry result; terminator beq 0x2d48.
BB 0x2d44..0x2d44: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2d94.
BB 0x2d48..0x2d50: retry enabled/mask/count/bit tests; join retry result; terminator bne 0x2d5c.
BB 0x2d54..0x2d58: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2d94.
BB 0x2d5c..0x2d64: retry enabled/mask/count/bit tests; join retry result; terminator bne 0x2d70.
BB 0x2d68..0x2d6c: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2d94.
BB 0x2d70..0x2d74: retry enabled/mask/count/bit tests; join retry result; terminator ble 0x2d80.
BB 0x2d78..0x2d7c: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2d94.
BB 0x2d80..0x2d8c: retry enabled/mask/count/bit tests; join retry result; terminator bne 0x2d94.
BB 0x2d90..0x2d90: retry enabled/mask/count/bit tests; join retry result; terminator li r3, -0x27.
BB 0x2d94..0x2d98: retry enabled/mask/count/bit tests; join retry result; terminator beq 0x2cd0.
BB 0x2d9c..0x2da0: retry enabled/mask/count/bit tests; join retry result; terminator bge 0x2da8.
BB 0x2da4..0x2da4: retry enabled/mask/count/bit tests; join retry result; terminator b 0x2db0.
BB 0x2da8..0x2dac: StoreDlTask; join nested update result; terminator bl 0x2dac   ; StoreDlTask.
BB 0x2db0..0x2db0: StoreDlTask; join nested update result; terminator mr r5, r3.
BB 0x2db4..0x2db8: StoreDlTask; join nested update result; terminator b 0x2e7c.
BB 0x2dbc..0x2dc4: allocation helper cached header and validated bounds; terminator beq 0x2dd0.
BB 0x2dc8..0x2dcc: allocation helper cached header and validated bounds; terminator b 0x2dd4.
BB 0x2dd0..0x2dd0: allocation helper cached header and validated bounds; terminator li r3, 0.
BB 0x2dd4..0x2dd8: allocation helper cached header and validated bounds; terminator beq 0x2df8.
BB 0x2ddc..0x2de0: allocation helper cached header and validated bounds; terminator bgt 0x2df8.
BB 0x2de4..0x2dec: allocation helper cached header and validated bounds; terminator bge 0x2df8.
BB 0x2df0..0x2df4: allocation helper cached header and validated bounds; terminator ble 0x2e00.
BB 0x2df8..0x2dfc: allocation helper cached header and validated bounds; terminator b 0x2e5c.
BB 0x2e00..0x2e18: narrow initial directory iterator to u16; loop; terminator bge 0x2e58.
BB 0x2e1c..0x2e20: directory entry lookup; write free id and return success; terminator beq 0x2e2c.
BB 0x2e24..0x2e28: directory entry lookup; write free id and return success; terminator b 0x2e30.
BB 0x2e2c..0x2e2c: directory entry lookup; write free id and return success; terminator li r3, 0.
BB 0x2e30..0x2e40: directory entry lookup; write free id and return success; terminator bne 0x2e50.
BB 0x2e44..0x2e4c: directory entry lookup; write free id and return success; terminator b 0x2e5c.
BB 0x2e50..0x2e54: increment iterator; report full list; terminator bdnz 0x2e1c.
BB 0x2e58..0x2e58: increment iterator; report full list; terminator li r3, -6.
BB 0x2e5c..0x2e60: full list calls purge, retry successful allocation; propagate negative errors; terminator bne 0x2e74.
BB 0x2e64..0x2e64: full list calls purge, retry successful allocation; propagate negative errors; terminator bl 0x2e64   ; NWC24PurgeOldestDlTask.
BB 0x2e68..0x2e6c: full list calls purge, retry successful allocation; propagate negative errors; terminator bge 0x29f4.
BB 0x2e70..0x2e70: full list calls purge, retry successful allocation; propagate negative errors; terminator b 0x2e7c.
BB 0x2e74..0x2e78: full list calls purge, retry successful allocation; propagate negative errors; terminator bge 0x29f4.
BB 0x2e7c..0x2e80: restore frame and return; terminator bl 0x2e80   ; _restgpr_26.
BB 0x2e84..0x2e90: restore frame and return; terminator blr .

TMCJPEGDEC_exif_parse call sequence: TMCJPEGDEC_IFD0_tag_parse, TMCJPEGDEC_IFD1_tag_parse, TMCJPEGDEC_IFD0_tag_parse.
BB 0x47c..0x4b0: initialize bounds and nextIfdOffset; validate header size; terminator bge 0x4bc.
BB 0x4b4..0x4b8: initialize bounds and nextIfdOffset; validate header size; terminator b 0x7b8.
BB 0x4bc..0x4cc: decode and validate byte order; terminator beq 0x4e4.
BB 0x4d0..0x4d8: decode and validate byte order; terminator beq 0x4e4.
BB 0x4dc..0x4e0: decode and validate byte order; terminator b 0x7b8.
BB 0x4e4..0x500: decode TIFF magic and validate42; terminator bne 0x508.
BB 0x504..0x504: decode TIFF magic and validate42; terminator clrlwi r0, r5, 0x10.
BB 0x508..0x510: decode TIFF magic and validate42; terminator beq 0x51c.
BB 0x514..0x518: decode TIFF magic and validate42; terminator b 0x7b8.
BB 0x51c..0x540: decode initial IFD offset and check size; terminator bne 0x54c.
BB 0x544..0x548: decode initial IFD offset and check size; terminator b 0x55c.
BB 0x54c..0x558: decode initial IFD offset and check size; terminator rlwimi r5, r7, 0x18, 0, 7.
BB 0x55c..0x560: decode initial IFD offset and check size; terminator bge 0x56c.
BB 0x564..0x568: decode initial IFD offset and check size; terminator b 0x7b8.
BB 0x56c..0x580: IFD0 cursor/remaining bounds and count decode; terminator bge 0x58c.
BB 0x584..0x588: IFD0 cursor/remaining bounds and count decode; terminator b 0x7b8.
BB 0x58c..0x5a8: IFD0 cursor/remaining bounds and count decode; terminator bne 0x5b0.
BB 0x5ac..0x5ac: IFD0 cursor/remaining bounds and count decode; terminator clrlwi r0, r3, 0x10.
BB 0x5b0..0x5c8: IFD0 entry byte extent check; terminator bge 0x5d4.
BB 0x5cc..0x5d0: IFD0 entry byte extent check; terminator b 0x7b8.
BB 0x5d4..0x5d8: IFD0 entry loop invoking IFD0_tag_parse; terminator b 0x5f4.
BB 0x5dc..0x5e8: IFD0 entry loop invoking IFD0_tag_parse; terminator bl 0x5e8   ; TMCJPEGDEC_IFD0_tag_parse.
BB 0x5ec..0x5f0: IFD0 entry loop invoking IFD0_tag_parse; terminator addi r24, r24, 1.
BB 0x5f4..0x5fc: IFD0 entry loop invoking IFD0_tag_parse; terminator blt 0x5dc.
BB 0x600..0x60c: require next-IFD word and decode; terminator bge 0x618.
BB 0x610..0x614: require next-IFD word and decode; terminator b 0x7b8.
BB 0x618..0x63c: require next-IFD word and decode; terminator bne 0x648.
BB 0x640..0x644: require next-IFD word and decode; terminator b 0x658.
BB 0x648..0x654: require next-IFD word and decode; terminator rlwimi r3, r5, 0x18, 0, 7.
BB 0x658..0x65c: zero next IFD returns success; validate offset; terminator bne 0x668.
BB 0x660..0x664: zero next IFD returns success; validate offset; terminator b 0x7b8.
BB 0x668..0x66c: zero next IFD returns success; validate offset; terminator bge 0x678.
BB 0x670..0x674: zero next IFD returns success; validate offset; terminator b 0x7b8.
BB 0x678..0x68c: IFD1 cursor and count decode with bounds; terminator bge 0x698.
BB 0x690..0x694: IFD1 cursor and count decode with bounds; terminator b 0x7b8.
BB 0x698..0x6b4: IFD1 cursor and count decode with bounds; terminator bne 0x6bc.
BB 0x6b8..0x6b8: IFD1 cursor and count decode with bounds; terminator clrlwi r0, r3, 0x10.
BB 0x6bc..0x6d4: IFD1 extent check and entry loop; terminator bge 0x6e0.
BB 0x6d8..0x6dc: IFD1 extent check and entry loop; terminator b 0x7b8.
BB 0x6e0..0x6e4: IFD1 extent check and entry loop; terminator b 0x700.
BB 0x6e8..0x6f4: IFD1 extent check and entry loop; terminator bl 0x6f4   ; TMCJPEGDEC_IFD1_tag_parse.
BB 0x6f8..0x6fc: IFD1 extent check and entry loop; terminator addi r25, r25, 1.
BB 0x700..0x708: IFD1 extent check and entry loop; terminator blt 0x6e8.
BB 0x70c..0x714: load EXIF sub-IFD offset and validate; terminator bge 0x720.
BB 0x718..0x71c: load EXIF sub-IFD offset and validate; terminator b 0x7b8.
BB 0x720..0x734: sub-IFD cursor/count decode and bounds; terminator bge 0x740.
BB 0x738..0x73c: sub-IFD cursor/count decode and bounds; terminator b 0x7b8.
BB 0x740..0x75c: sub-IFD cursor/count decode and bounds; terminator bne 0x764.
BB 0x760..0x760: sub-IFD cursor/count decode and bounds; terminator clrlwi r0, r3, 0x10.
BB 0x764..0x77c: sub-IFD entry extent check and IFD0_tag_parse loop; terminator bge 0x788.
BB 0x780..0x784: sub-IFD entry extent check and IFD0_tag_parse loop; terminator b 0x7b8.
BB 0x788..0x78c: sub-IFD entry extent check and IFD0_tag_parse loop; terminator b 0x7a8.
BB 0x790..0x79c: sub-IFD entry extent check and IFD0_tag_parse loop; terminator bl 0x79c   ; TMCJPEGDEC_IFD0_tag_parse.
BB 0x7a0..0x7a4: sub-IFD entry extent check and IFD0_tag_parse loop; terminator addi r28, r28, 1.
BB 0x7a8..0x7b0: sub-IFD entry extent check and IFD0_tag_parse loop; terminator blt 0x790.
BB 0x7b4..0x7b4: success return and saved-register restore; terminator li r3, 0.
BB 0x7b8..0x7c8: success return and saved-register restore; terminator blr .

TMCJPEGDEC_IFD0_tag_parse call sequence: .
BB 0x7cc..0x7e4: decode tag and type with TIFF endian helper; terminator bne 0x7ec.
BB 0x7e8..0x7e8: decode tag and type with TIFF endian helper; terminator clrlwi r7, r0, 0x10.
BB 0x7ec..0x808: decode tag and type with TIFF endian helper; terminator bne 0x810.
BB 0x80c..0x80c: decode tag and type with TIFF endian helper; terminator clrlwi r0, r6, 0x10.
BB 0x810..0x818: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x87c.
BB 0x81c..0x820: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xa20.
BB 0x824..0x824: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x858.
BB 0x828..0x82c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beqlr .
BB 0x830..0x830: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x844.
BB 0x834..0x838: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beqlr .
BB 0x83c..0x83c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bltlr .
BB 0x840..0x840: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x844..0x848: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x91c.
BB 0x84c..0x850: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bgelr .
BB 0x854..0x854: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator b 0x8f4.
BB 0x858..0x85c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xb4c.
BB 0x860..0x860: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x870.
BB 0x864..0x868: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xb24.
BB 0x86c..0x86c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x870..0x874: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xc50.
BB 0x878..0x878: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x87c..0x888: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xde0.
BB 0x88c..0x88c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x8c0.
BB 0x890..0x898: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xd78.
BB 0x89c..0x89c: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x8b0.
BB 0x8a0..0x8a4: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xd50.
BB 0x8a8..0x8a8: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bgelr .
BB 0x8ac..0x8ac: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x8b0..0x8b8: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xdbc.
BB 0x8bc..0x8bc: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x8c0..0x8c8: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xe50.
BB 0x8cc..0x8cc: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0x8e4.
BB 0x8d0..0x8d8: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator beq 0xe04.
BB 0x8dc..0x8dc: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bge 0xe28.
BB 0x8e0..0x8e0: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator blr .
BB 0x8e4..0x8ec: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator bgelr .
BB 0x8f0..0x8f0: switch tag dispatch; ignored compression/strip/JPEG tags exit; terminator b 0xed0.
BB 0x8f4..0x90c: orientation SHORT decode/store; terminator bne 0x914.
BB 0x910..0x910: orientation SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0x914..0x918: orientation SHORT decode/store; terminator blr .
BB 0x91c..0x93c: X resolution offset decode; bounds; numerator; denominator; terminator bne 0x948.
BB 0x940..0x944: X resolution offset decode; bounds; numerator; denominator; terminator b 0x958.
BB 0x948..0x954: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r8, r7, 0x18, 0, 7.
BB 0x958..0x964: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x968..0x974: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x978..0x998: X resolution offset decode; bounds; numerator; denominator; terminator bne 0x9a4.
BB 0x99c..0x9a0: X resolution offset decode; bounds; numerator; denominator; terminator b 0x9b4.
BB 0x9a4..0x9b0: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r7, 0x18, 0, 7.
BB 0x9b4..0x9c8: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x9cc..0x9d8: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x9dc..0x9fc: X resolution offset decode; bounds; numerator; denominator; terminator bne 0xa08.
BB 0xa00..0xa04: X resolution offset decode; bounds; numerator; denominator; terminator b 0xa18.
BB 0xa08..0xa14: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r5, 0x18, 0, 7.
BB 0xa18..0xa1c: X resolution offset decode; bounds; numerator; denominator; terminator blr .
BB 0xa20..0xa40: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0xa4c.
BB 0xa44..0xa48: Y resolution offset decode; bounds; numerator; denominator; terminator b 0xa5c.
BB 0xa4c..0xa58: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r8, r7, 0x18, 0, 7.
BB 0xa5c..0xa68: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0xa6c..0xa78: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0xa7c..0xa9c: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0xaa8.
BB 0xaa0..0xaa4: Y resolution offset decode; bounds; numerator; denominator; terminator b 0xab8.
BB 0xaa8..0xab4: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r7, 0x18, 0, 7.
BB 0xab8..0xacc: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0xad0..0xadc: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0xae0..0xb00: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0xb0c.
BB 0xb04..0xb08: Y resolution offset decode; bounds; numerator; denominator; terminator b 0xb1c.
BB 0xb0c..0xb18: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r5, 0x18, 0, 7.
BB 0xb1c..0xb20: Y resolution offset decode; bounds; numerator; denominator; terminator blr .
BB 0xb24..0xb3c: resolution-unit SHORT decode/store; terminator bne 0xb44.
BB 0xb40..0xb40: resolution-unit SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0xb44..0xb48: resolution-unit SHORT decode/store; terminator blr .
BB 0xb4c..0xb6c: transfer function offset; channel/index loops, bounds and SHORT store; terminator bne 0xb78.
BB 0xb70..0xb74: transfer function offset; channel/index loops, bounds and SHORT store; terminator b 0xb88.
BB 0xb78..0xb84: transfer function offset; channel/index loops, bounds and SHORT store; terminator rlwimi r9, r7, 0x18, 0, 7.
BB 0xb88..0xb90: transfer function offset; channel/index loops, bounds and SHORT store; terminator li r0, 0x80.
BB 0xb94..0xb9c: transfer function offset; channel/index loops, bounds and SHORT store; terminator mtctr r0.
BB 0xba0..0xbac: transfer function offset; channel/index loops, bounds and SHORT store; terminator bgt 0xc3c.
BB 0xbb0..0xbbc: transfer function offset; channel/index loops, bounds and SHORT store; terminator bgt 0xc3c.
BB 0xbc0..0xbd8: transfer function offset; channel/index loops, bounds and SHORT store; terminator bne 0xbe0.
BB 0xbdc..0xbdc: transfer function offset; channel/index loops, bounds and SHORT store; terminator clrlwi r5, r6, 0x10.
BB 0xbe0..0xbf4: transfer function offset; channel/index loops, bounds and SHORT store; terminator bgt 0xc3c.
BB 0xbf8..0xc04: transfer function offset; channel/index loops, bounds and SHORT store; terminator bgt 0xc3c.
BB 0xc08..0xc20: transfer function offset; channel/index loops, bounds and SHORT store; terminator bne 0xc28.
BB 0xc24..0xc24: transfer function offset; channel/index loops, bounds and SHORT store; terminator clrlwi r5, r6, 0x10.
BB 0xc28..0xc38: transfer function offset; channel/index loops, bounds and SHORT store; terminator bdnz 0xba0.
BB 0xc3c..0xc48: transfer function offset; channel/index loops, bounds and SHORT store; terminator blt 0xb94.
BB 0xc4c..0xc4c: transfer function offset; channel/index loops, bounds and SHORT store; terminator blr .
BB 0xc50..0xc70: date-time offset decode; bounds; copy twenty bytes; terminator bne 0xc7c.
BB 0xc74..0xc78: date-time offset decode; bounds; copy twenty bytes; terminator b 0xc8c.
BB 0xc7c..0xc88: date-time offset decode; bounds; copy twenty bytes; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0xc8c..0xc98: date-time offset decode; bounds; copy twenty bytes; terminator bgtlr .
BB 0xc9c..0xca8: date-time offset decode; bounds; copy twenty bytes; terminator bgtlr .
BB 0xcac..0xd4c: date-time offset decode; bounds; copy twenty bytes; terminator blr .
BB 0xd50..0xd68: YCbCr position SHORT decode/store; terminator bne 0xd70.
BB 0xd6c..0xd6c: YCbCr position SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0xd70..0xd74: YCbCr position SHORT decode/store; terminator blr .
BB 0xd78..0xd98: EXIF subdirectory offset LONG decode/store; terminator bne 0xda4.
BB 0xd9c..0xda0: EXIF subdirectory offset LONG decode/store; terminator b 0xdb4.
BB 0xda4..0xdb0: EXIF subdirectory offset LONG decode/store; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0xdb4..0xdb8: EXIF subdirectory offset LONG decode/store; terminator blr .
BB 0xdbc..0xddc: EXIF version four-byte copy; terminator blr .
BB 0xde0..0xe00: flash version four-byte copy; terminator blr .
BB 0xe04..0xe24: FlashPix version four-byte copy; terminator blr .
BB 0xe28..0xe40: color space SHORT decode/store; terminator bne 0xe48.
BB 0xe44..0xe44: color space SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0xe48..0xe4c: color space SHORT decode/store; terminator blr .
BB 0xe50..0xe54: pixelXDimension SHORT or LONG according to type; terminator bne 0xe84.
BB 0xe58..0xe70: pixelXDimension SHORT or LONG according to type; terminator bne 0xe78.
BB 0xe74..0xe74: pixelXDimension SHORT or LONG according to type; terminator clrlwi r0, r4, 0x10.
BB 0xe78..0xe80: pixelXDimension SHORT or LONG according to type; terminator blr .
BB 0xe84..0xe88: pixelXDimension SHORT or LONG according to type; terminator bnelr .
BB 0xe8c..0xeac: pixelXDimension SHORT or LONG according to type; terminator bne 0xeb8.
BB 0xeb0..0xeb4: pixelXDimension SHORT or LONG according to type; terminator b 0xec8.
BB 0xeb8..0xec4: pixelXDimension SHORT or LONG according to type; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0xec8..0xecc: pixelXDimension SHORT or LONG according to type; terminator blr .
BB 0xed0..0xed4: pixelYDimension SHORT or LONG according to type; terminator bne 0xf04.
BB 0xed8..0xef0: pixelYDimension SHORT or LONG according to type; terminator bne 0xef8.
BB 0xef4..0xef4: pixelYDimension SHORT or LONG according to type; terminator clrlwi r0, r4, 0x10.
BB 0xef8..0xf00: pixelYDimension SHORT or LONG according to type; terminator blr .
BB 0xf04..0xf08: pixelYDimension SHORT or LONG according to type; terminator bnelr .
BB 0xf0c..0xf2c: pixelYDimension SHORT or LONG according to type; terminator bne 0xf38.
BB 0xf30..0xf34: pixelYDimension SHORT or LONG according to type; terminator b 0xf48.
BB 0xf38..0xf44: pixelYDimension SHORT or LONG according to type; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0xf48..0xf4c: pixelYDimension SHORT or LONG according to type; terminator blr .

TMCJPEGDEC_IFD1_tag_parse call sequence: .
BB 0xf50..0xf68: decode TIFF tag; terminator bne 0xf70.
BB 0xf6c..0xf6c: decode TIFF tag; terminator clrlwi r0, r6, 0x10.
BB 0xf70..0xf78: decode TIFF tag; terminator beqlr .
BB 0xf7c..0xf7c: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0xfd0.
BB 0xf80..0xf84: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beq 0x1038.
BB 0xf88..0xf88: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0xfac.
BB 0xf8c..0xf90: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0xf94..0xf94: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bgelr .
BB 0xf98..0xf9c: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beq 0x1268.
BB 0xfa0..0xfa0: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bltlr .
BB 0xfa4..0xfa4: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0xfa8..0xfa8: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0xfac..0xfb0: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beq 0x1240.
BB 0xfb4..0xfb4: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0xfc4.
BB 0xfb8..0xfbc: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bgelr .
BB 0xfc0..0xfc0: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator b 0x113c.
BB 0xfc4..0xfc8: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0xfcc..0xfcc: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0xfd0..0xfdc: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0xfe0..0xfe0: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0x1008.
BB 0xfe4..0xfe8: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beq 0x12d4.
BB 0xfec..0xfec: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0xffc.
BB 0xff0..0xff4: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0x1290.
BB 0xff8..0xff8: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0xffc..0x1000: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0x1004..0x1004: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0x1008..0x1010: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0x1014..0x1014: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bge 0x1028.
BB 0x1018..0x1020: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator beqlr .
BB 0x1024..0x1024: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0x1028..0x1030: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator bgelr .
BB 0x1034..0x1034: switch dispatch; strip/orientation/date/transfer/metadata ignored; terminator blr .
BB 0x1038..0x1058: X resolution offset decode; bounds; numerator; denominator; terminator bne 0x1064.
BB 0x105c..0x1060: X resolution offset decode; bounds; numerator; denominator; terminator b 0x1074.
BB 0x1064..0x1070: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r8, r7, 0x18, 0, 7.
BB 0x1074..0x1080: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x1084..0x1090: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x1094..0x10b4: X resolution offset decode; bounds; numerator; denominator; terminator bne 0x10c0.
BB 0x10b8..0x10bc: X resolution offset decode; bounds; numerator; denominator; terminator b 0x10d0.
BB 0x10c0..0x10cc: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r7, 0x18, 0, 7.
BB 0x10d0..0x10e4: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x10e8..0x10f4: X resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x10f8..0x1118: X resolution offset decode; bounds; numerator; denominator; terminator bne 0x1124.
BB 0x111c..0x1120: X resolution offset decode; bounds; numerator; denominator; terminator b 0x1134.
BB 0x1124..0x1130: X resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r5, 0x18, 0, 7.
BB 0x1134..0x1138: X resolution offset decode; bounds; numerator; denominator; terminator blr .
BB 0x113c..0x115c: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0x1168.
BB 0x1160..0x1164: Y resolution offset decode; bounds; numerator; denominator; terminator b 0x1178.
BB 0x1168..0x1174: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r8, r7, 0x18, 0, 7.
BB 0x1178..0x1184: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x1188..0x1194: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x1198..0x11b8: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0x11c4.
BB 0x11bc..0x11c0: Y resolution offset decode; bounds; numerator; denominator; terminator b 0x11d4.
BB 0x11c4..0x11d0: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r7, 0x18, 0, 7.
BB 0x11d4..0x11e8: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x11ec..0x11f8: Y resolution offset decode; bounds; numerator; denominator; terminator bgtlr .
BB 0x11fc..0x121c: Y resolution offset decode; bounds; numerator; denominator; terminator bne 0x1228.
BB 0x1220..0x1224: Y resolution offset decode; bounds; numerator; denominator; terminator b 0x1238.
BB 0x1228..0x1234: Y resolution offset decode; bounds; numerator; denominator; terminator rlwimi r0, r5, 0x18, 0, 7.
BB 0x1238..0x123c: Y resolution offset decode; bounds; numerator; denominator; terminator blr .
BB 0x1240..0x1258: resolution-unit SHORT decode/store; terminator bne 0x1260.
BB 0x125c..0x125c: resolution-unit SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0x1260..0x1264: resolution-unit SHORT decode/store; terminator blr .
BB 0x1268..0x1280: compression SHORT decode/store; terminator bne 0x1288.
BB 0x1284..0x1284: compression SHORT decode/store; terminator clrlwi r0, r4, 0x10.
BB 0x1288..0x128c: compression SHORT decode/store; terminator blr .
BB 0x1290..0x12b0: thumbnail-offset LONG decode/store; terminator bne 0x12bc.
BB 0x12b4..0x12b8: thumbnail-offset LONG decode/store; terminator b 0x12cc.
BB 0x12bc..0x12c8: thumbnail-offset LONG decode/store; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0x12cc..0x12d0: thumbnail-offset LONG decode/store; terminator blr .
BB 0x12d4..0x12f4: thumbnail-length LONG decode/store; terminator bne 0x1300.
BB 0x12f8..0x12fc: thumbnail-length LONG decode/store; terminator b 0x1310.
BB 0x1300..0x130c: thumbnail-length LONG decode/store; terminator rlwimi r0, r6, 0x18, 0, 7.
BB 0x1310..0x1314: thumbnail-length LONG decode/store; terminator blr .

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main b7a06e9d82e35cda3de92a6135db491000722791, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | explicit switch default exits function | 89d68ecc76f7 | objdiff 96.08264% | metric (21, 236), insns 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | explicit switch default breaks dispatch | cfcd828cb192 | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored low tag retains own block with explicit default return | e8f0c0510faa | objdiff 96.08264% | metric (21, 236), insns 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []

BEGIN TMCJPEGDEC_IFD0_tag_parse: origin/main b7a06e9d82e35cda3de92a6135db491000722791, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | explicit switch default exits function | 35aef4f8c04d | objdiff 98.86694% | metric (18, 459), insns 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | explicit switch default breaks dispatch | 7d63f285ef7f | objdiff 99.49065% | metric (5, 457), insns 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored low tag retains own block with explicit default return | f3293547b07c | objdiff 98.86694% | metric (18, 459), insns 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT NWC24UpdateDlTask | writable validator consumes const implementation pointer like SDK helper | 5eb765437776 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | News Channel minimal update locals with direct task-id checks and const implementation validation | ee443f8faa2c | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | const implementation and read-only cached-header view for writable permissions | 5fb835ecdec4 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | access-time identifier declared before cached work | 5a1e48edb42d | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | access-time status and identifier before cached work | 347988e7f246 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | News Channel timestamp setter uses shared validation and typed directory entry helper | 8522e62c0df1 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN TMCJPEGDEC_exif_parse: origin/main b7a06e9d82e35cda3de92a6135db491000722791, remote source differs=False. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT TMCJPEGDEC_exif_parse | named TIFF base separate from input view across all directory walks | ed746f06d1e9 | objdiff 99.43396% | metric (0, 21), insns 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | mutable TIFF byte view matches writable IFD0 entry helper boundary | 39e7677748ab | objdiff 99.43396% | metric (0, 21), insns 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | decoded 16-bit entry count widened in traversal local while loop index remains u16 | 6822e526c892 | objdiff 98.86793% | metric (0, 38), insns 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | unsigned byte extent for decoded directory size comparison | 51c247756b6b | objdiff 98.60849% | metric (3, 23), insns 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission early guard returns | 4b3e17b4e00c | objdiff 93.162056% | metric (27, 146), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission nested success and default-failure returns | dbf4d1610991 | objdiff 96.264824% | metric (23, 148), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission equality retained in explicit bool local | 76767a698351 | objdiff 95.38735% | metric (27, 148), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | direct permission predicate in validator with no duplicate boolean local | 36006c862f96 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | TIFF LONG reader with separate endian result local | bee2cdd92548 | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | TIFF LONG reader with result local declared after raw | 467c34299922 | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | TIFF LONG reader with conditional endian result expression | acec98ff2697 | objdiff 95.65289% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | TIFF LONG reader swaps raw in place before one return | 5d5c727c2694 | objdiff 80.57025% | metric (64, 225), insns 231/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission identifier uses widened unsigned value | 0ce34a2bbe8d | objdiff 100.0% | metric (0, 0), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | EXACT CANDIDATE
ATTEMPT NWC24UpdateDlTask | group permission byte boolean return with proven zero/one assignments | e753abaf0787 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission unsigned boolean return with zero/one assignments | 0ea2c0d01fcb | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | group permission group comparison uses full-width SDK result masked to16 | 9957153222b4 | objdiff 99.841896% | metric (0, 8), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24UpdateDlTask | minimal exact candidate restores allocation and URL helpers outside public update | d23f8d8d8906 | objdiff 100.0% | metric (0, 0), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | EXACT CANDIDATE
ATTEMPT NWC24UpdateDlTask | final source cleanup uses unsigned retry shift, drops unused update declarations and extra blank lines | 951aa8570e31 | objdiff 100.0% | metric (0, 0), insns 253/253 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | EXACT CANDIDATE

NWC24UpdateDlTask accepted locally: 100.0%, 253/253 instructions, ctxdiff diffs0. News Channel typed retry boundary, const access-time task and independent writable group helper reproduce the target. The group predicate accepts a full-width u32 groupId, matching cmplw without an input narrowing operation; this changes virtual-register interference versus a u16 parameter and fixes the last eight differences. Final unsigned retry-bit shift preserves defined behavior. Quick full build passes, DOL 26116613f624061ba99c8d1a299aaa6efa85670d, pools identical, regressions0, forbidden0, readability0. NWC24Download28/30, code10316/12496, data80/80. Final nonquick gate remains required.

BEGIN NWC24InitDlTask: origin/main b7a06e9d82e35cda3de92a6135db491000722791, remote source differs=True. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT NWC24InitDlTask | initializer uses proven full-width writable group predicate at final validation | c7a2e3e2d88c | objdiff 99.201385% | metric (0, 23), insns 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN AddTaskInternal: origin/main b7a06e9d82e35cda3de92a6135db491000722791, remote source differs=True. Existing live baseline remains nonexact; no new source for this unit on remote.
ATTEMPT AddTaskInternal | nested update uses independently exact public writable validation boundary | 59e3e0307784 | objdiff 98.12968% | metric (17, 323), insns 398/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested update also uses independently exact error-clear helper | cc4f9391fff0 | objdiff 98.22942% | metric (17, 323), insns 398/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | exact update boundaries with News Channel word-width directory allocation helper | 0a43c366db29 | objdiff 99.32668% | metric (5, 324), insns 400/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | rational offset declared signed LONG | 2fce48cd0817 | objdiff 99.241165% | metric (5, 457), insns 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | rational offset expressed as pointer-width integer | 5dd3474f935e | objdiff 99.49065% | metric (5, 457), insns 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | rational bytes decoded via read-only local entry field view | 59b0afa0d502 | objdiff 99.49065% | metric (5, 457), insns 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | rational offset declared signed LONG | 02c2f730d6ca | objdiff 95.65289% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | rational offset expressed as pointer-width integer | 2a1190b9a93a | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | rational bytes decoded via read-only local entry field view | dbfb1d5e6dde | objdiff 96.14876% | metric (14, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT NWC24InitDlTask | declaration-search result for exact writable-helper initializer | c7a2e3e2d88c | objdiff 99.201385% | metric (0, 23), insns 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | full exact-update and word-count seed retains URL local before nested string helper | 0bd44f6cbc65 | objdiff 98.453865% | metric (6, 46), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested URL helper takes mutable string view | b6e4db31f8f2 | objdiff 98.453865% | metric (6, 46), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested URL helper clips successful string check through explicit result join | 33ef72aa9c91 | objdiff 98.31422% | metric (9, 339), insns 400/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested URL helper receives whole task and owns field cursor | 4959c07064a2 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [274] | 14af27b5859a | objdiff 95.96281% | metric (14, 228), insns 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [273] | f52216370593 | objdiff 95.95868% | metric (15, 229), insns 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [284] | dc6b589558ec | objdiff 91.900826% | metric (57, 219), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [274, 284] | d6bf95f7c93d | objdiff 91.77273% | metric (58, 230), insns 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [274, 273] | bb9b54d11ed2 | objdiff 92.10744% | metric (57, 223), insns 238/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [274, 301] | b97449a49f3c | objdiff 91.54958% | metric (49, 230), insns 237/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit ignored tags absent from target dispatch [40960, 40961, 40962, 40963] | e4c765e07b8b | objdiff 96.12397% | metric (16, 226), insns 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT AddTaskInternal | nested retry status has independent lexical lifetime | bcf61ab43fe0 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested store status shares explicit operation result join | c08ee3da551b | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | initial nested validation has scoped status assignment | 9a1fea2e8141 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | retry helper counter widened to word at typed boundary | fd74b07a52f5 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | caller owns dedicated status for nested update result | 1aff3d20cd48 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | caller reuses its operation status for nested update result | 0a34b38d3eff | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | nested update takes implementation pointer at inline API boundary | bc94db9ad634 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | SDK nested update only keeps implementation pointer and status locals | 7a496d28d77d | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | SDK retry helper takes implementation pointer directly with minimal nested update locals | ea7bdb8c9608 | objdiff 99.601% | metric (1, 30), insns 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

## Remaining-function audit

NWC24InitDlTask: 4 distinct compiled source trials in this round. All still-fuzzy source restored.
AddTaskInternal: 21 distinct compiled source trials in this round. All still-fuzzy source restored.
TMCJPEGDEC_exif_parse: 4 distinct compiled source trials in this round. All still-fuzzy source restored.
TMCJPEGDEC_IFD0_tag_parse: 6 distinct compiled source trials in this round. All still-fuzzy source restored.
TMCJPEGDEC_IFD1_tag_parse: 31 distinct compiled source trials in this round. All still-fuzzy source restored.
Declaration search: exact-helper Init seed used 71 builds, structural0/exact23 unchanged. Updated public Update seed used23 builds at0/8 before the full-width group argument solved it. The five remaining functions have at least three new, compiled source attempts. No data edits: both owned units are already data100%; same symbol names, extents and section totals.
Retained only the locally gated NWC24UpdateDlTask exact change; additional Init, Add and JPEG candidates remain /tmp-only. Add whole-task URL helper and word-width directory bounds yielded401/401, structural1/exact30 at99.601%, but no exact result after status/inline-boundary variants. Shared retry/access helper improvement raises the committed Add score without altering any matched function.

## Final clean gate

Nonquick gate rebuilt build/43U from scratch. Original function extents and configuration unchanged. One new instruction-exact function: NWC24UpdateDlTask. Five functions remain open after the audited trials above. Final pools checked independently after the clean build; exact Update ctxdiff253/253, diffs0. Live build/43U/report.json regenerated after the gate. No push, PR, merge, rebase, branch/worktree operations or edits to other worktrees.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 10316/12496 data 80/80 functions 28/30 fuzzy 99.7071 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 28/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.70711
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 98.10474
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 9304/12496 data 80 functions 27 fuzzy 99.5519
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 98.9804 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 98.98035
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
regressions vs baseline: 0
global matched_code_percent: 91.93089 -> 91.96468
global fuzzy_match_percent: 99.71777 -> 99.71841
global complete_code_percent: 74.84181 -> 74.84181
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
