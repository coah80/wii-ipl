# Structural round 10

Starting HEAD 21c9b95b; baseline gate passes, target DOL SHA1 confirmed. All edits owned by this single worker.

## Diagnosis before source trials
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | objdiff 98.923615 | structural/exact score, instructions ((0, 31), 144, 144); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | objdiff 99.303795 | structural/exact score, instructions ((0, 10), 79, 79); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | objdiff 95.00395 | structural/exact score, instructions ((19, 250), 249, 253); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | objdiff 87.11364 | structural/exact score, instructions ((29, 95), 167, 176); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | objdiff 96.74342 | structural/exact score, instructions ((12, 36), 150, 152); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | objdiff 98.77358 | structural/exact score, instructions ((2, 3), 212, 212); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | objdiff 97.7182 | structural/exact score, instructions ((20, 323), 398, 401); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RVL_SDK/src/nup/nup | __nupParseServerInfo__FP14NUPContextInfoPcPcUx | objdiff 98.108406 | structural/exact score, instructions ((0, 148), 452, 452); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RVL_SDK/src/nup/nup | __nupBase64Encode__FPUcPUcUl | objdiff 94.20635 | structural/exact score, instructions ((9, 21), 63, 63); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RVL_SDK/src/nup/nup | __nupGetBootVersion__FP14ESTitleVersion | objdiff None | structural/exact score, instructions ((0, 17), 163, 163); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RVL_SDK/src/nup/nup | __nupGetTitleSize__FP12NUPTitleInfo | objdiff 99.100716 | structural/exact score, instructions ((0, 22), 139, 139); full asm and diffs /tmp/sol-med-round10/diffs.txt
libs/RVL_SDK/src/nup/nup | __nupOp | objdiff 99.25799 | structural/exact score, instructions ((4, 47), 438, 438); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | createBrowser__Q33ipl5scene7SettingFv | objdiff 98.8505 | structural/exact score, instructions ((15, 114), 299, 301); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | draw__Q33ipl5scene7SettingFv | objdiff 91.525314 | structural/exact score, instructions ((82, 570), 595, 632); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | initKeyboard__Q33ipl5scene7SettingFPCc | objdiff 98.38498 | structural/exact score, instructions ((4, 195), 215, 213); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | calcKeyboard__Q33ipl5scene7SettingFv | objdiff 98.0 | structural/exact score, instructions ((15, 258), 292, 290); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | convertRevIP__Q33ipl5scene7SettingFPUcPCc | objdiff 98.69863 | structural/exact score, instructions ((0, 16), 73, 73); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | scanAP__Q33ipl5scene7SettingFv | objdiff 95.39338 | structural/exact score, instructions ((53, 160), 266, 272); full asm and diffs /tmp/sol-med-round10/diffs.txt
src/scene/setting/iplSetting | setUSBAP__Q33ipl5scene7SettingFv | objdiff 98.070175 | structural/exact score, instructions ((7, 21), 56, 57); full asm and diffs /tmp/sol-med-round10/diffs.txt
NWC24InitDlTask | home-directory parser inline boundary with named high/low outputs | ((0, 31), 144, 144) -> ((0, 31), 144, 144) | objdiff 98.923615 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24InitDlTask | combine parsed identity into native 64-bit title value | ((0, 31), 144, 144) -> ((0, 31), 144, 144) | objdiff 98.923615 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24InitDlTask | initializer-specific ownership helper argument order | ((0, 31), 144, 144) -> ((0, 31), 144, 144) | objdiff 98.923615 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24IterateDlTask | cache header getter directly at every loop validation | ((0, 10), 79, 79) -> ((5, 3), 79, 79) | objdiff 94.81013 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24IterateDlTask | header recomputation through work dlHead field each use | ((0, 10), 79, 79) -> ((6, 52), 83, 79) | objdiff 92.21519 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24IterateDlTask | iterator search isolated from begin handling in inline helper | ((0, 10), 79, 79) -> ((0, 18), 79, 79) | objdiff 98.73418 | gain [] loss ['NWC24IterateDlTaskEx'] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored
NWC24UpdateDlTask | materialized group ownership at update-only inline boundary | ((19, 250), 249, 253) -> ((5, 37), 253, 253) | objdiff 98.81423 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | retry predicate shifts before mask with explicit nonnull header branch | ((5, 37), 253, 253) -> ((5, 37), 253, 253) | objdiff 98.83399 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | access identifier copied through named inline output reader | ((5, 37), 253, 253) -> ((5, 29), 253, 253) | objdiff 98.992096 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | retry checker count parameter precedes task pointer | ((5, 29), 253, 253) -> ((5, 29), 253, 253) | objdiff 98.992096 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | group ownership accepts flags before group identifier | ((5, 29), 253, 253) -> ((19, 250), 249, 253) | objdiff 95.02371 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | retry uses explicit read-validation inline boundary | BUILD FAIL /src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     725:     u32 retryMask;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
NWC24UpdateDlTask | restore task-view group boundary after flags-first frame regression | ((19, 250), 249, 253) -> ((5, 29), 253, 253) | objdiff 98.992096 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24UpdateDlTask | retry read-validation expanded with declarations before statements | ((5, 29), 253, 253) -> ((5, 29), 253, 253) | objdiff 98.992096 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24UpdateDlTask | group identifier declared before result boolean | ((5, 29), 253, 253) -> ((19, 250), 249, 253) | objdiff 95.02371 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24UpdateDlTask | owner comparison materialized inside update validator | ((5, 29), 253, 253) -> ((5, 29), 253, 253) | objdiff 98.992096 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24iCheckDlHeaderConsistency | repair loop inline parameters task,header,repair with target-required out-of-line API call | ((2, 3), 212, 212) -> ((5, 6), 212, 212) | objdiff 96.95283 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24iCheckDlHeaderConsistency | repair loop inline parameters header,task,repair with target-required out-of-line API call | ((2, 3), 212, 212) -> ((5, 6), 212, 212) | objdiff 96.95283 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24iCheckDlHeaderConsistency | repair loop inline parameters header,repair,task with target-required out-of-line API call | ((2, 3), 212, 212) -> ((5, 6), 212, 212) | objdiff 96.95283 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
__nupBase64Encode__FPUcPUcUl | direct quartet stores in encoding order | ((9, 21), 63, 63) -> ((8, 17), 63, 63) | objdiff 86.53968 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupBase64Encode__FPUcPUcUl | counter reset after first direct output assignment | ((8, 17), 63, 63) -> ((8, 17), 63, 63) | objdiff 86.53968 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupBase64Encode__FPUcPUcUl | load every quartet character before writing output and resetting counter | ((8, 17), 63, 63) -> ((17, 30), 63, 63) | objdiff 79.7619 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupBase64Encode__FPUcPUcUl | byte count initialized before value accumulator | ((8, 17), 63, 63) -> ((8, 30), 63, 63) | objdiff 85.190475 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
NWC24ManageDlTaskListForMenu | deletion propagates result through caller output pointer | ((12, 36), 150, 152) -> ((12, 36), 148, 152) | objdiff 96.2829 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24ManageDlTaskListForMenu | validation and successful deletion use separate inline lifetimes | ((12, 36), 150, 152) -> ((12, 36), 150, 152) | objdiff 96.74342 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24ManageDlTaskListForMenu | common deletion result assigned after validation success branch | ((12, 36), 150, 152) -> ((12, 36), 148, 152) | objdiff 96.2829 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24PurgeOldestDlTask | inline iterator initializer with checked status at API boundary | ((29, 95), 167, 176) -> ((21, 134), 171, 176) | objdiff 90.53977 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24PurgeOldestDlTask | read and delete guarded by success with iterator failure conversion at end | ((21, 134), 171, 176) -> ((64, 167), 150, 176) | objdiff 76.47159 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24PurgeOldestDlTask | read task inline returns status into explicit outer result output | ((21, 134), 171, 176) -> ((21, 134), 171, 176) | objdiff 90.59659 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
AddTaskInternal | free-slot iterator uses unsigned word with explicit validated short id | ((20, 323), 398, 401) -> ((20, 323), 398, 401) | objdiff 97.75561 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
AddTaskInternal | URL failure returned through inline string-check boundary | ((20, 323), 398, 401) -> ((17, 88), 399, 401) | objdiff 98.02992 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
AddTaskInternal | free-slot count validation uses sequential guards without shared condition register | ((17, 88), 399, 401) -> ((26, 101), 405, 401) | objdiff 96.12219 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24PurgeOldestDlTask | preserve initializer then defer iterator error conversion after read/delete branch | ((21, 134), 171, 176) -> ((10, 49), 174, 176) | objdiff 96.98864 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | kept
NWC24PurgeOldestDlTask | selected deletion retains status separately from validation result | ((10, 49), 174, 176) -> ((10, 49), 174, 176) | objdiff 96.98864 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24PurgeOldestDlTask | selected read parameters id before pointer across inline call | ((10, 49), 174, 176) -> ((10, 49), 174, 176) | objdiff 96.98864 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
__nupBase64Encode__FPUcPUcUl | direct-store and cache trials reverted to starting source after no exact gain
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | tag parser output length parameter before value pointer | BUILD FAIL    319:                                      &titleStart, &titleLength)) != 0 &&
#   Error:                                                               ^
#   (10248) function call '__nupFindTag({lval} char *, {lval} const char *,
#   {lval} const char *, char **, unsigned long *)' does not match
#   '__nupFindTag(char *, const char *, const char *, unsigned long *, char
#   **)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
__nupBase64Encode__FPUcPUcUl | direct-store and cache trials reverted to starting source after no exact gain
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | tag parser output length parameter before value pointer | BUILD FAIL 21:                                    &versionStart, &versionLength)) != 0) {
#   Error:                                                                 ^
#   (10248) function call '__nupFindTag({lval} char *, {lval} const char *,
#   {lval} const char *, char **, unsigned long *)' does not match
#   '__nupFindTag(char *, const char *, const char *, unsigned long *, char
#   **)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | tag parser tests end tag through nested success branch | ((0, 148), 452, 452) -> ((69, 431), 470, 452) | objdiff 86.891594 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | tag values returned as named range at inline boundary | ((0, 148), 452, 452) -> ((0, 148), 452, 452) | objdiff 98.108406 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetTitleSize__FP12NUPTitleInfo | size-specific content helper takes content id before title | ((0, 22), 139, 139) -> ((0, 22), 139, 139) | objdiff 99.100716 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetTitleSize__FP12NUPTitleInfo | installed-content count passed explicitly at size-helper boundary | ((0, 22), 139, 139) -> ((0, 26), 139, 139) | objdiff 98.84892 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetTitleSize__FP12NUPTitleInfo | reserve size computed in separate native-wide total | ((0, 22), 139, 139) -> ((0, 22), 139, 139) | objdiff 99.100716 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetBootVersion__FP14ESTitleVersion | installed-content count acquired before allocating list | ((0, 17), 163, 163) -> ((0, 17), 163, 163) | objdiff None | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetBootVersion__FP14ESTitleVersion | title-id equality tests candidate before owned-title value | ((0, 17), 163, 163) -> ((0, 17), 163, 163) | objdiff None | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupGetBootVersion__FP14ESTitleVersion | boot-version conversion moves into title-version function scope | ((0, 17), 163, 163) -> ((4, 26), 163, 163) | objdiff None | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupOp | boot-version output initialized only on successful output query | ((4, 47), 438, 438) -> ((3, 404), 437, 438) | objdiff 99.520546 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupOp | boot-version output conversion stores only validated word | ((3, 404), 437, 438) -> ((0, 19), 438, 438) | objdiff 99.748856 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupOp | title selection loop acquires title id through helper output boundary | ((0, 19), 438, 438) -> ((0, 18), 438, 438) | objdiff 99.76028 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | tag helper length-before-value outputs with every call updated | ((0, 148), 452, 452) -> ((0, 148), 452, 452) | objdiff 98.108406 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored
__nupOp | title selection compares current title id before array entry | ((0, 18), 438, 438) -> ((0, 18), 438, 438) | objdiff 99.783104 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | title selection caches count after download-progress work | ((0, 18), 438, 438) -> ((0, 12), 438, 438) | objdiff 99.84018 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupOp | title id acquired via semantic inline output reader | ((0, 12), 438, 438) -> ((0, 19), 438, 438) | objdiff 99.748856 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | declsearch after structural trials | ((0, 12), 438, 438) -> ((0, 12), 438, 438)
declaration block:
      u8* response = 0;
      ESTmdView* tmdView = 0;
      u32 currentDeviceId;
      u32 needsAudit;
      char* auditData = 0;
      s32 result;
      u16 serverBootVersion;
      u16 bootTitleVersion;
      u16 systemMenuVersion;
      ESTitleId currentTitleId;
      NUPTitleInfo* bootTitle = 0;
      NUPTitleInfo* menuTitle = 0;
      NUPTitleInfo* systemTitle = 0;
      NUPContextInfo* context = (NUPContextInfo*)argument;
      u32 deviceId;
      char messageId[0x15];
      NANDStatus auditStatus;
      u32 i;
start (0, 12)
best (0, 12) after 180 builds; source restored; best order was:
    u8* response = 0;
    ESTmdView* tmdView = 0;
    u32 currentDeviceId;
    u32 needsAudit;
    char* auditData = 0;
    s32 result;
    u16 serverBootVersion;
    u16 bootTitleVersion;
    u16 systemMenuVersion;
    ESTitleId currentTitleId;
    NUPTitleInfo* bootTitle = 0;
    NUPTitleInfo* menuTitle = 0;
    NUPTitleInfo* systemTitle = 0;
    NUPContextInfo* context = (NUPContextInfo*)argument;
    u32 deviceId;
    char messageId[0x15];
    NANDStatus auditStatus;
    u32 i;
createBrowser__Q33ipl5scene7SettingFv | explicit case seven with invalid direct page returning safely | ((15, 114), 299, 301) -> ((15, 111), 303, 301) | objdiff 98.75083 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
createBrowser__Q33ipl5scene7SettingFv | projection dimensions calculated through rectangle accessors | ((15, 114), 299, 301) -> ((15, 114), 299, 301) | objdiff 98.8505 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
createBrowser__Q33ipl5scene7SettingFv | initialize default direct path before explicit seven-case switch | ((15, 114), 299, 301) -> ((9, 116), 302, 301) | objdiff 99.19933 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
draw__Q33ipl5scene7SettingFv | copy GX mode by scalar fields and sample-pattern pairs | ((82, 570), 595, 632) -> ((76, 537), 632, 632) | objdiff 91.01899 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
draw__Q33ipl5scene7SettingFv | window-null default branch and separate scroll direction stores | ((76, 537), 632, 632) -> ((71, 550), 632, 632) | objdiff 91.34335 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
draw__Q33ipl5scene7SettingFv | side rectangles calculate each float boundary at construction | ((71, 550), 632, 632) -> ((111, 601), 628, 632) | objdiff 85.54588 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
initKeyboard__Q33ipl5scene7SettingFPCc | keyboard defaults initialized in setting structure then copied to locals | ((4, 195), 215, 213) -> ((14, 202), 219, 213) | objdiff 96.478874 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
initKeyboard__Q33ipl5scene7SettingFPCc | keyboard type stored after string and row limits in setting object | ((4, 195), 215, 213) -> ((7, 195), 215, 213) | objdiff 98.38028 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
initKeyboard__Q33ipl5scene7SettingFPCc | unknown keyboard forms return before initialized limits are consumed | ((4, 195), 215, 213) -> ((18, 155), 215, 213) | objdiff 98.3615 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
__nupOp | current system title precedes candidate in 64-bit comparison after count lifetime fix | ((0, 12), 438, 438) -> ((0, 11), 438, 438) | objdiff 99.87443 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | kept
__nupOp | selection count materialized at semantic inline output boundary | ((0, 11), 438, 438) -> ((0, 11), 438, 438) | objdiff 99.87443 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | selection counter declared with thread locals but assigned at selection phase | ((0, 11), 438, 438) -> ((0, 11), 438, 438) | objdiff 99.87443 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | separate selection loop indices after download phase | ((0, 11), 438, 438) -> ((0, 18), 438, 438) | objdiff 99.783104 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
calcKeyboard__Q33ipl5scene7SettingFv | asterisk assignment precedes explicit index increment | ((15, 258), 292, 290) -> ((9, 274), 291, 290) | objdiff 98.63793 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
calcKeyboard__Q33ipl5scene7SettingFv | form text uses existing nickname as initialized fallback | ((9, 274), 291, 290) -> ((114, 271), 253, 290) | objdiff 84.82758 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
calcKeyboard__Q33ipl5scene7SettingFv | cancellation form text has its own scoped lifetime | ((9, 274), 291, 290) -> ((9, 274), 291, 290) | objdiff 98.63793 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | IPv4 parsing inline boundary takes source text before destination | ((0, 16), 73, 73) -> ((0, 10), 73, 73) | objdiff 99.178085 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | IPv4 parsing inline boundary takes destination before source text | ((0, 16), 73, 73) -> ((0, 10), 73, 73) | objdiff 99.178085 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | decimal parser takes named component pointer before conversion | ((0, 16), 73, 73) -> ((0, 16), 73, 73) | objdiff 98.69863 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored
scanAP__Q33ipl5scene7SettingFv | animation boolean accumulated through inline query | ((53, 160), 266, 272) -> ((36, 165), 257, 272) | objdiff 93.25 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
scanAP__Q33ipl5scene7SettingFv | animation boolean converted through SDK BOOL return boundary | BUILD FAIL Setting.cpp:3)
### mwcceppc.exe Compiler:
#    File: src\scene\setting\iplSetting.cpp
# -----------------------------------------
#    2707: ol IsSettingAnimationPlaying(layout::Object* object, int index) {
#   Error:                                                                 ^
#   (10333) object 'ipl::scene::IsSettingAnimationPlaying(ipl::layout::Object
#   *, int)' redefined
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
scanAP__Q33ipl5scene7SettingFv | animation query separates animator acquisition from state read | BUILD FAIL Setting.cpp:3)
### mwcceppc.exe Compiler:
#    File: src\scene\setting\iplSetting.cpp
# -----------------------------------------
#    2707: ol IsSettingAnimationPlaying(layout::Object* object, int index) {
#   Error:                                                                 ^
#   (10333) object 'ipl::scene::IsSettingAnimationPlaying(ipl::layout::Object
#   *, int)' redefined
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
__nupOp | special-title selection inline parameters required,titles,count | ((0, 11), 438, 438) -> ((23, 187), 436, 438) | objdiff 98.6484 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | special-title selection inline parameters count,titles,required | ((0, 11), 438, 438) -> ((23, 187), 436, 438) | objdiff 98.6484 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
setUSBAP__Q33ipl5scene7SettingFv | completion byte dispatches through switch before status argument reload | ((7, 21), 56, 57) -> ((7, 21), 56, 57) | objdiff 98.070175 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
__nupOp | special-title selection inline parameters titles,required,count | ((0, 11), 438, 438) -> ((23, 187), 436, 438) | objdiff 98.6484 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
scanAP__Q33ipl5scene7SettingFv | restore starting animation body after whole-query helper stayed out of line
scanAP__Q33ipl5scene7SettingFv | leaf animation state query variant 1 | ((53, 160), 266, 272) -> ((54, 160), 266, 272) | objdiff 93.757355 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
scanAP__Q33ipl5scene7SettingFv | leaf animation state query variant 2 | ((53, 160), 266, 272) -> ((53, 160), 266, 272) | objdiff 95.39338 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
scanAP__Q33ipl5scene7SettingFv | leaf animation state query variant 3 | ((53, 160), 266, 272) -> ((53, 160), 266, 272) | objdiff 95.39338 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
setUSBAP__Q33ipl5scene7SettingFv | completion byte handled by one-iteration loop with explicit break | ((7, 21), 56, 57) -> ((9, 12), 57, 57) | objdiff 85.87719 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
setUSBAP__Q33ipl5scene7SettingFv | completion guard uses semantic result-byte inline predicate | ((7, 21), 56, 57) -> ((0, 0), 57, 57) | objdiff 100.0 | gain ['setUSBAP__Q33ipl5scene7SettingFv'] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
__nupOp | candidate identifier loaded before candidate pointer declaration | ((0, 11), 438, 438) -> ((0, 11), 438, 438) | objdiff 99.87443 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | selection count acquired after array pointer in loop scope | ((0, 11), 438, 438) -> ((26, 185), 435, 438) | objdiff 98.3379 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep
__nupOp | two title scans share an explicit pointer cursor instead of recomputing candidate | ((0, 11), 438, 438) -> ((0, 19), 438, 438) | objdiff 99.77169 | gain [] loss [] | POOL IDENTICAL up to 28 (mine=28 base=28) | restored despite requested keep

## First exact candidate
setUSBAP: inline result-byte predicate preserves both target loads without volatile. 57/57 instructions, ctxdiff diffs 0, objdiff 100.0. All unrelated provisional code restored before full gate.

## Structural findings
NWC24InitDlTask | 144/144 instructions; only local and nested ownership-helper register colors differ. | completed source trials 3
NWC24IterateDlTask | 79/79 instructions; cached work/header r6 and r7 colors reversed. | completed source trials 3
NWC24UpdateDlTask | timestamp and ownership inline boundaries force 0x30 rather than 0x20 frame; update-only task-view group helper reaches correct frame; retry branch and coloring still differ. | completed source trials 9
NWC24PurgeOldestDlTask | initializer inline return and late iterator-error conversion explain most structural mismatch; reaches 174/176 instructions; removal result boundary remains different. | completed source trials 6
NWC24ManageDlTaskListForMenu | delete-validation/result boundary produces 150/152 instructions with r3/r5 status allocation differences. | completed source trials 3
NWC24iCheckDlHeaderConsistency | 212/212 instructions; task address scheduled after saved parameter copies instead of before. | completed source trials 3
AddTaskInternal | URL failure branch, free-slot counter conversion, timestamp and retry helper boundaries. | completed source trials 3
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | 452/452 instructions; repeated tag-helper local colors differ. | completed source trials 3
__nupBase64Encode__FPUcPUcUl | 63/63 instructions; quartet reads must be scheduled before stores, counter color differs. | completed source trials 4
__nupGetBootVersion__FP14ESTitleVersion | target symbol omits context but asm uses both parameters; actual emitted two-parameter body has 163/163 instructions and 17 color differences. | completed source trials 3
__nupGetTitleSize__FP12NUPTitleInfo | 139/139 instructions; reserve high-word temporary and installed-content helper colors differ. | completed source trials 3
__nupOp | boot output initialization and conversion branch resolved structurally; count lifetime removes 7 differences; remaining 11 differences swap count and low title-id register r7/r8. | completed source trials 16
createBrowser__Q33ipl5scene7SettingFv | 0x200/0x210 frame; explicit seventh case and invalid-page default shape; target default retains uninitialized path, which will not be reproduced. | completed source trials 3
draw__Q33ipl5scene7SettingFv | scalar GX mode copy explains most instruction-count gap; rectangle floating-point schedules and texture lifetimes differ. | completed source trials 3
initKeyboard__Q33ipl5scene7SettingFPCc | safe row/string defaults add two instructions; keyboard settings stores and local colors differ. | completed source trials 3
calcKeyboard__Q33ipl5scene7SettingFv | safe form defaults add instructions; asterisk update ordering improves 292 to 291 against 290. | completed source trials 3
convertRevIP__Q33ipl5scene7SettingFPUcPCc | 73/73 instructions; pointer/count/index colors differ; semantic wrapper reduces 16 to 10 differences. | completed source trials 3
scanAP__Q33ipl5scene7SettingFv | target materializes animation boolean; state/index store order differs; whole-query helper remains out of line and is rejected. | completed source trials 4
setUSBAP__Q33ipl5scene7SettingFv | target reloads result byte; inline byte predicate reproduces both loads, 57/57 instructions and diffs 0. | completed source trials 3

setUSBAP clean full gate PASS; instruction-exact 104 -> 105, objdiff exact 105 -> 106, code 30532 -> 30760, data unchanged, regressions/forbidden/readability 0; committed 31cd9401
NWC24InitDlTask | initial cached-header helper replaces open-coded acquisition | ((0, 31), 144, 144) -> ((0, 31), 144, 144) | objdiff 98.923615 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24InitDlTask | initial header acquired through named output parameter | ((0, 31), 144, 144) -> ((0, 31), 144, 144) | objdiff 98.923615 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24IterateDlTask | work cache acquired through semantic inline output reader | ((0, 10), 79, 79) -> ((0, 10), 79, 79) | objdiff 99.303795 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24IterateDlTask | reuse the validated cached header for later entry iteration | ((0, 10), 79, 79) -> ((2, 51), 78, 79) | objdiff 97.91139 | gain [] loss [] | POOL IDENTICAL up to 3 (mine=3 base=3) | restored despite requested keep
NWC24InitDlTask | declsearch after structural trials | ((0, 31), 144, 144) -> ((0, 31), 144, 144)
declaration block:
      char homePath[64] = {0};
      u32 nwc24IdHigh;
      u32 nwc24IdLow;
      DlTaskData* task;
      DlTaskListHeader* header;
      NWC24Err result;
      BOOL allowed;
      BOOL useContentFile;
start (0, 31)
best (0, 31) after 71 builds; source restored; best order was:
    char homePath[64] = {0};
    u32 nwc24IdHigh;
    u32 nwc24IdLow;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    BOOL allowed;
    BOOL useContentFile;
NWC24IterateDlTask | declsearch after structural trials | ((0, 10), 79, 79) -> ((0, 10), 79, 79)
declaration block:
      DlTaskListHeader* entriesHeader;
      NWC24Work* work;
      u16 taskId;
      u16 maxTaskCount;
      DlTaskListHeader* header;
      NWC24Err result;
start (0, 10)
best (0, 10) after 36 builds; source restored; best order was:
    DlTaskListHeader* entriesHeader;
    NWC24Work* work;
    u16 taskId;
    u16 maxTaskCount;
    DlTaskListHeader* header;
    NWC24Err result;

## Rejected provisional work
NWC24 update timestamp/ownership, purge initializer/error flow, AddTask URL helper, nupOp boot/title selection, Setting draw/calcKeyboard changes all restored. They improved structural or fuzzy scores but never achieved a new exact function. Saved snapshots under /tmp/sol-med-round10 are evidence only and will not be committed.
No configuration, symbols, shared headers, original data placement, link flags, or other translation units edited.
Readability: no new comments, asm, padding, volatile, uninitialized reads, raw pointer offsets, auto-named identifiers, or function deletion.
NWC24iCheckDlHeaderConsistency | declsearch after structural trials | ((2, 3), 212, 212) -> ((2, 3), 212, 212)
declaration block:
      NWC24DlTask task;
      NWC24DlTask* taskPointer = &task;
      NWC24DlId taskId;
      NWC24Err result;
      DlTaskListHeader* currentHeader;
      DlTaskListHeader* listHeader = header;
      BOOL shouldRepair = repair;
start (2, 3)
best (2, 3) after 52 builds; source restored; best order was:
    NWC24DlTask task;
    NWC24DlTask* taskPointer = &task;
    NWC24DlId taskId;
    NWC24Err result;
    DlTaskListHeader* currentHeader;
    DlTaskListHeader* listHeader = header;
    BOOL shouldRepair = repair;
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | declsearch after structural trials | ((0, 148), 452, 452) -> ((0, 148), 452, 452)
definition of __nupParseServerInfo__FP14NUPContextInfoPcPcUx not found
__nupGetTitleSize__FP12NUPTitleInfo | declsearch after structural trials | ((0, 22), 139, 139) -> ((0, 22), 139, 139)
definition of __nupGetTitleSize__FP12NUPTitleInfo not found
convertRevIP__Q33ipl5scene7SettingFPUcPCc | declsearch after structural trials | ((0, 16), 73, 73) -> ((0, 16), 73, 73)
declaration block:
              char ascii[20];
              int count = 0;
              int index;
start (0, 16)
best (0, 16) after 6 builds; source restored; best order was:
            char ascii[20];
            int count = 0;
            int index;
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | declsearch explicit lines after mangled-name parser failure | ((0, 148), 452, 452) -> ((0, 148), 452, 452)
declaration block:
      s32 result = 0;
      char* start;
      char* afterEnd;
      char* cursor;
      size_t valueLength;
      size_t titleCount;
start (0, 148)
best (0, 148) after 36 builds; source restored; best order was:
    s32 result = 0;
    char* start;
    char* afterEnd;
    char* cursor;
    size_t valueLength;
    size_t titleCount;
__nupGetTitleSize__FP12NUPTitleInfo | declsearch explicit lines after mangled-name parser failure | ((0, 22), 139, 139) -> ((0, 22), 139, 139)
declaration block:
      s32 result = 0;
      s32 contentIndex;
start (0, 22)
best (0, 22) after 2 builds; source restored; best order was:
    s32 result = 0;
    s32 contentIndex;
__nupBase64Encode__FPUcPUcUl | declsearch explicit lines after mangled-name parser failure | ((9, 21), 63, 63) -> ((9, 21), 63, 63)
declaration block:
      u8* end = input + length;
      u32 value = 0;
      u32 count = 0;
start (9, 21)
best (9, 21) after 6 builds; source restored; best order was:
    u8* end = input + length;
    u32 value = 0;
    u32 count = 0;
__nupGetBootVersion__FP14ESTitleVersion | declsearch actual body against target with explicit name mapping, no source symbol rename | ((0, 17), 163, 163) -> ((0, 17), 163, 163)
declaration block:
      s32 result;
      ESTmdView* tmdView = 0;
start (0, 17)
best (0, 17) after 2 builds; source restored; best order was:
    s32 result;
    ESTmdView* tmdView = 0;
convertRevIP__Q33ipl5scene7SettingFPUcPCc | retain source-before-destination IPv4 helper for final declaration search | ((0, 16), 73, 73) -> ((0, 10), 73, 73) | objdiff 99.178085 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | kept
convertRevIP__Q33ipl5scene7SettingFPUcPCc | IPv4 helper leading declaration block includes start and destination cursor | ((0, 10), 73, 73) -> ((0, 10), 73, 73) | objdiff 99.178085 | gain [] loss [] | POOL IDENTICAL up to 108 (mine=108 base=108) | restored despite requested keep
convertRevIP__Q33ipl5scene7SettingFPUcPCc | declaration search on semantic parsing helper after source trials | ((0, 10), 73, 73) -> ((0, 10), 73, 73)
declaration block:
              char ascii[20];
              int count = 0;
              int index;
start (0, 10)
best (0, 10) after 6 builds; source restored; best order was:
            char ascii[20];
            int count = 0;
            int index;

## Final open-function audit
NWC24InitDlTask | objdiff 98.923615 | distinct successful-build source attempts 5
NWC24IterateDlTask | objdiff 99.303795 | distinct successful-build source attempts 5
NWC24UpdateDlTask | objdiff 95.00395 | distinct successful-build source attempts 9
NWC24PurgeOldestDlTask | objdiff 87.11364 | distinct successful-build source attempts 5
NWC24ManageDlTaskListForMenu | objdiff 96.74342 | distinct successful-build source attempts 3
NWC24iCheckDlHeaderConsistency | objdiff 98.77358 | distinct successful-build source attempts 3
AddTaskInternal | objdiff 97.7182 | distinct successful-build source attempts 3
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | objdiff 98.108406 | distinct successful-build source attempts 3
__nupBase64Encode__FPUcPUcUl | objdiff 94.20635 | distinct successful-build source attempts 4
__nupGetBootVersion__FP14ESTitleVersion | objdiff None | distinct successful-build source attempts 3
__nupGetTitleSize__FP12NUPTitleInfo | objdiff 99.100716 | distinct successful-build source attempts 3
__nupOp | objdiff 99.25799 | distinct successful-build source attempts 16
createBrowser__Q33ipl5scene7SettingFv | objdiff 98.8505 | distinct successful-build source attempts 3
draw__Q33ipl5scene7SettingFv | objdiff 91.525314 | distinct successful-build source attempts 3
initKeyboard__Q33ipl5scene7SettingFPCc | objdiff 98.38498 | distinct successful-build source attempts 3
calcKeyboard__Q33ipl5scene7SettingFv | objdiff 98.0 | distinct successful-build source attempts 3
convertRevIP__Q33ipl5scene7SettingFPUcPCc | objdiff 98.69863 | distinct successful-build source attempts 5
scanAP__Q33ipl5scene7SettingFv | objdiff 95.39338 | distinct successful-build source attempts 4
All 18 open functions have at least three distinct source attempts. Declaration-order searches followed structural trials. Purge trial with accidental early source slicing was rejected and excluded from this audit. All source changes outside the committed result-byte predicate restored.

Final clean full gate over all three: GATE PASS; DOL target SHA1, all pools identical, regressions/forbidden/readability 0. Only Setting unit changed among 1027 reports. setUSBAP: objdiff 100.0, 57/57 instructions, ctxdiff diffs 0.
Fresh comparator caveat: setUpdate_NoUpdateDialog_ raw 120-byte bodies are identical and corrected disassembler score is (0,0). ctxdiff misreads blt cr1 first operand as branch target; two apparent differences depend on function offset. Prior round NaN explanation not supported by current output. Tooling left unchanged.
