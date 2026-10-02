# pk2 max parked retry

Applied unslop and coah-voice writing passes to the required report. Worker scope is four assigned units, config data proofs, and this log. No orchestration.
Start HEAD and origin/main: e3457d11. Clean working tree. Origin fetched under /tmp/wii-git.lock.
Memory startup check: commands run successfully; historical bubblewrap failure is absent in this environment.

libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL: initial pool check: POOL IDENTICAL up to 1 (mine=1 base=1)
libs/RevoEX/src/nwc24/NWC24Download: initial pool check: POOL IDENTICAL up to 3 (mine=3 base=3)
libs/RVL_SDK/src/fa/driver/sd_drv: initial pool check: POOL IDENTICAL up to 46 (mine=46 base=46)
libs/RVL_SDK/src/fa/pf_cache: initial pool check: POOL IDENTICAL up to 0 (mine=0 base=0)
DATA AUDIT: all four assigned units already have 100% matched data in the live report; target/source data names, extents, and section scores agree. No config rename or extent change needed. pf_cache has no data sections.
BEGIN NHTTPi_strnicmp: fetched origin/main=e3457d11a22a9f0d8300daed615914fb230bea7d; owned source differs from HEAD on remote=False; diagnosis metric=((2, 2), 51, 51)
DIAGNOSIS NHTTPi_strnicmp: Same 0x10 frame, 51/51 instructions; only hoisted Z and zero constants exchange instruction order. No stack store/reload evidence supports volatile. Pointees already const. No extent overlap. Prior declaration permutations excluded.
ATTEMPT NHTTPi_strnicmp: read-only scalar pointer helper makes character values immutable views; source dc64c9a66cda; objdiff=99.76471%; metric=((2, 2), 51, 51); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_strnicmp: conditional-expression helper instead of argument mutation; source 3dbaa1148791; objdiff=99.76471%; metric=((2, 2), 51, 51); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_strnicmp: strict uppercase bounds preserve ASCII interval with different comparison lowering; source 6b4412f9238d; objdiff=49.117645%; metric=((36, 50), 50, 51); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
BEGIN NHTTPi_compareToken: fetched origin/main=e3457d11a22a9f0d8300daed615914fb230bea7d; owned source differs from HEAD on remote=False; diagnosis metric=((24, 42), 44, 45)
DIAGNOSIS NHTTPi_compareToken: Target has condition-entry loop with equality at bottom, right folding keeps shifted candidate then selects original on false; ours body-entry loop adds one branch and lacks that right selection. Target raw left byte survives in r31 for terminator check, same 0x10 frame.
ATTEMPT NHTTPi_compareToken: condition-entry loop compares inlined folds directly; source 0e30c24d2a81; objdiff=94.62222%; metric=((7, 30), 44, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_compareToken: fold helper takes read-only byte pointer and preserves raw input alias; source 4cc0b6297c87; objdiff=94.62222%; metric=((7, 30), 44, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_compareToken: signed-byte read-only view with conditional fold in loop predicate; source 9466120301dc; objdiff=84.62222%; metric=((9, 44), 42, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
BEGIN NHTTPi_Base64Encode: fetched origin/main=e3457d11a22a9f0d8300daed615914fb230bea7d; owned source differs from HEAD on remote=False; diagnosis metric=((71, 58), 119, 119)
DIAGNOSIS NHTTPi_Base64Encode: 119/119 instructions, same 0x20 frame and triplet unrolling. Target signed padding compare; ours unsigned. Most differences are dependent byte loads, alphabet index fragments, and stores under char aliasing; target keeps source[1] in r10, source[2] in r7 and early first fragment live.
ATTEMPT NHTTPi_Base64Encode: signed length and signed-byte input view tighten source alias type; source eb7a0c5a67ab; objdiff=62.42857%; metric=((69, 56), 119, 119); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_Base64Encode: signed-byte snapshots with explicit triplet and signed padding arithmetic; source e89377650b53; objdiff=62.781513%; metric=((47, 63), 119, 119); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_Base64Encode: read-only typed triplet passed to inline encoder; high fragment added before low; source cc15a48005fd; objdiff=64.35294%; metric=((43, 57), 119, 119); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
BEGIN NHTTPi_compareToken: fetched origin/main=e3457d11a22a9f0d8300daed615914fb230bea7d; owned source differs from HEAD on remote=False; diagnosis metric=((24, 42), 44, 45)
ATTEMPT NHTTPi_compareToken: right immutable value fold and left mutating fold keep distinct inline lifetimes; source 470960bd5c07; objdiff=94.62222%; metric=((7, 30), 44, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_compareToken: raw signed-byte terminator survives left fold; right const-value return helper; source f90da98d79f2; objdiff=69.28889%; metric=((6, 20), 45, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
ATTEMPT NHTTPi_compareToken: raw unsigned left byte widens at the fold boundary and signed stop check; source cffa6f49daf0; objdiff=94.62222%; metric=((7, 30), 44, 45); unit code/data/functions=1388/112/11; pool=POOL IDENTICAL up to 1 (mine=1 base=1); regressions=[]; restored
BEGIN NWC24InitDlTask: fetched origin/main=d78210528f882407ff363d4a112114670a216ce3; owned source differs from HEAD on remote=False; diagnosis metric=((0, 31), 144, 144)
DIAGNOSIS NWC24InitDlTask: 0x60 frame and 144/144 instructions; structural score zero. Zero/home ID/header/title/group values cycle saved registers. No volatile store-reload proof. Headers and task permission views are read-only candidates; validate alias assumptions before register search.
ATTEMPT NWC24InitDlTask: permission boundary receives const task and cached header explicitly; source ff1390188311; objdiff=98.854164%; metric=((0, 33), 144, 144); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24InitDlTask: owner components use const parse views and read-only initial header; source dadcc1f11b6b; BUILD FAILED m int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     268:     const char* ownerHighText = homePath + 7;
#   Error:     ^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

BEGIN NWC24UpdateDlTask: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((19, 250), 249, 253)
DIAGNOSIS NWC24UpdateDlTask: Target frame 0x20, explicit r28..r31 saves; source 0x30, five-register save helper. Target group check keeps allowed boolean and groupId in different saved lifetimes; retry branch uses positive cached-work view and shifted bit first. No store/reload volatile evidence. Reducing helper live values is structural priority.
ATTEMPT NWC24UpdateDlTask: read-only permission helper and nested group boolean control saved-value lifetime; source 63d243827abe; objdiff=98.695656%; metric=((5, 43), 253, 253); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24UpdateDlTask: read-only cached-work retry helper and shifted retry mask operand first; source 3c443ac7ae56; objdiff=98.715416%; metric=((5, 43), 253, 253); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24UpdateDlTask: caller-owned universal time object bounds access-time helper lifetime with const permissions; source 5d281c43af14; objdiff=97.885376%; metric=((11, 148), 251, 253); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
BEGIN NWC24InitDlTask: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 31), 144, 144)
DIAGNOSIS NWC24InitDlTask: 0x60 frame and 144/144 instructions; structural score zero. Zero/home ID/header/title/group values cycle saved registers. No volatile store-reload proof. Headers and task permission views are read-only candidates; validate alias assumptions before register search.
ATTEMPT NWC24InitDlTask: permission boundary receives const task and cached header explicitly; source ff1390188311; objdiff=98.854164%; metric=((0, 33), 144, 144); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24InitDlTask: owner components use const parse views and read-only initial header; source cd6db78c6535; objdiff=98.923615%; metric=((0, 31), 144, 144); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24InitDlTask: post-initialization read-only task/header views localize final validation lifetime; source fe5fbec0434b; objdiff=98.854164%; metric=((0, 33), 144, 144); unit code/data/functions=8140/80/25; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
BEGIN NWC24IterateDlTask: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 10), 79, 79)
DIAGNOSIS NWC24IterateDlTask: Leaf 79/79 instructions, structural score zero. Only work and derived header registers r6/r7 exchange. Target and source extents equal. Use read-only work/header views and lookup boundary without declaration-order permutations.
ATTEMPT NWC24IterateDlTask: const work pointer narrows iteration input alias view; source 487b19d2bdfc; objdiff=100.0%; metric=((0, 0), 79, 79); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; RETAINED exact, awaiting full gate
BEGIN NWC24iCheckDlHeaderConsistency: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((2, 3), 212, 212)
DIAGNOSIS NWC24iCheckDlHeaderConsistency: Same 0x2c0 frame, 212/212 instructions. Only task address creation moves after parameter copies. No forced stack spill or volatile evidence. Task object extent and neighbours equal; inspect read-only list view and helper boundaries instead of prior declaration permutations.
ATTEMPT NWC24iCheckDlHeaderConsistency: header parameter and both cached header views are const; source f6279354e003; objdiff=98.77358%; metric=((2, 3), 212, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24iCheckDlHeaderConsistency: constant task pointer, repair flag, and read-only list bound preserve immutable input lifetimes; source 4a24bba4583f; objdiff=98.77358%; metric=((2, 3), 212, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24iCheckDlHeaderConsistency: repair read boundary takes task pointer and read-only identifier address; source 39cb60543b0b; objdiff=96.69811%; metric=((15, 170), 210, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
CHECKPOINT NWC24IterateDlTask: const NWC24Work input view fixes r6/r7 alias allocation. Objdiff 100.0%, 79/79 instructions, ctxdiff diffs 0, code 8140 -> 8456, data 80/80 unchanged. Fresh quick full gate: GATE PASS, regressions 0, forbidden/readability 0, correct DOL SHA1. Final clean full gate still required.
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8456/12496 data 80/80 functions 26/30 fuzzy 99.1697 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 26/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.169655
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8140/12496 data 80 functions 25 fuzzy 99.1521
regressions vs baseline: 0
global matched_code_percent: 91.02223 -> 91.03278
global fuzzy_match_percent: 99.58757 -> 99.58764
global complete_code_percent: 73.73083 -> 73.73083
global matched_data_percent: 99.42271 -> 99.42271
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
BEGIN AddTaskInternal: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=True; diagnosis metric=((22, 323), 398, 401)
DIAGNOSIS AddTaskInternal: Target/source frames 0x30; 398/401 instructions. URL helper branch lacks target explicit jump; target free-slot counter wider then narrowed when indexed, and retry helper null/non-null branch direction differs. Current template also carries one extra saved register in update inner lifetime. Inspect const validation/URL views and widened search bounds first.
ATTEMPT AddTaskInternal: URL validation reads task and header through const views; source a9c8ec831220; objdiff=97.7182%; metric=((22, 323), 398, 401); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT AddTaskInternal: free-slot loop uses wide counter and explicit 16-bit entry view with read-only URL validation; source 6ae43c6b3f02; objdiff=97.7182%; metric=((22, 323), 398, 401); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT AddTaskInternal: free-slot status uses positive success branch; const URL task/header alias view; source 6eb9e944c574; objdiff=97.7182%; metric=((22, 323), 398, 401); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
BEGIN pfd_sddrv_init: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((18, 31), 144, 144)
DIAGNOSIS pfd_sddrv_init: 144/144 instructions, same 0x20 frame. Target unsigned register null test and branchful identity return; source cmpwi and branchless return, compensated size. Device store precedes media load in target, and final disk store precedes flag load. No same-field immediate store/reload warrants volatile. Try const views and real init helper boundaries.
ATTEMPT pfd_sddrv_init: const disk identity view and explicit mismatch return branch; source 905b3c7fadf5; objdiff=92.326385%; metric=((18, 31), 144, 144); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored

EXTENT AUDIT: all assigned open code symbol extents checked against sorted next symbols. No overlap; no function size edits authorized or needed.
NHTTPi_strnicmp: start 0x81497ec4, size 0xcc, next NHTTPi_getUrlEncodedSize 0x81497f90, no extent overlap.
NHTTPi_compareToken: start 0x81498454, size 0xb4, next NHTTPi_strtonum 0x81498508, no extent overlap.
NHTTPi_Base64Encode: start 0x81498598, size 0x1dc, next NHTTPi_InitThreadInfo 0x81498774, no extent overlap.
NWC24InitDlTask: start 0x814ae9b8, size 0x240, next NWC24SetDlId 0x814aebf8, no extent overlap.
NWC24IterateDlTask: start 0x814af408, size 0x13c, next NWC24IterateDlTaskEx 0x814af544, no extent overlap.
NWC24UpdateDlTask: start 0x814af788, size 0x3f4, next NWC24DeleteDlTask 0x814afb7c, no extent overlap.
NWC24iCheckDlHeaderConsistency: start 0x814b0874, size 0x350, next NWC24iCreateDlTaskList 0x814b0bc4, no extent overlap.
AddTaskInternal: start 0x814b1208, size 0x644, next DeleteDlTask 0x814b184c, no extent overlap.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: start 0x815c9f54, size 0x3a4, next PFCACHE_DoFlushCache 0x815ca2f8, no extent overlap.
pfd_sddrv_init: start 0x815ea638, size 0x240, next pfd_sddrv_mount 0x815ea878, no extent overlap.
pfd_sddrv_finalize: start 0x815eab80, size 0xe4, next pfd_sddrv_get_disk_info 0x815eac64, no extent overlap.
pfd_sddrv_get_total_sectors: start 0x815eb2a4, size 0x140, next pfd_sddrv_calc_mbr_bpb 0x815eb3e4, no extent overlap.
pfd_sddrv_store_mbr_buf: start 0x815ebbb4, size 0x328, next pfd_sddrv_build_mbr_bpb 0x815ebedc, no extent overlap.
pfd_sddrv_build_fat32_mbr_bpb: start 0x815eccc0, size 0x378, next pfd_sddrv_full_format 0x815ed038, no extent overlap.
ATTEMPT pfd_sddrv_init: media presence follows device assignment through read-only info helper; source 3d1f9324ee5f; objdiff=92.326385%; metric=((18, 31), 144, 144); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_init: init completion helper owns disk assignment and flags in target store order; source c149ecc642dd; objdiff=92.326385%; metric=((18, 31), 144, 144); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
BEGIN pfd_sddrv_finalize: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((6, 4), 57, 57)
DIAGNOSIS pfd_sddrv_finalize: Same 0x10 frame, 57/57 instructions. Four mismatches: final flag load target r3 versus r5, target masks/stores flags before media reset; ours hoists media reset ahead of mask. Record-level return helper can shorten final value lifetime. No proven volatile reload in target.
ATTEMPT pfd_sddrv_finalize: completion helper returns success after clearing real record fields; source 0cf2049687eb; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_finalize: const flag field input view in record completion helper; source 5361f291b228; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_finalize: separate read-only record view and mutable record completion boundary; source fe2bf402a758; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
BEGIN pfd_sddrv_get_total_sectors: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 6), 80, 80)
DIAGNOSIS pfd_sddrv_get_total_sectors: 80/80 instructions and frame unchanged. Six mismatches in final 16-bit multiplier shift/product: target reuses selected exponent r3 and constant r0, source uses r0/r5. Need true narrow shift lifetime before register-only permutations; no reload/spill or extent proof for other levers.
ATTEMPT pfd_sddrv_get_total_sectors: const exponent input at 16-bit block multiplier inline boundary; source cbcb2b194abc; objdiff=96.9875%; metric=((3, 10), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_get_total_sectors: reduce selected 16-bit exponent in place before multiplier shift; source ba2dc2fb501c; objdiff=99.5%; metric=((0, 6), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_get_total_sectors: sector count helper combines narrow factor and product with const exponent; source 21d00041dc62; objdiff=96.9875%; metric=((3, 10), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
BEGIN pfd_sddrv_store_mbr_buf: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 9), 202, 202)
DIAGNOSIS pfd_sddrv_store_mbr_buf: 202/202 instructions, frame identical. Only track-size product and partition start sector exchange r8/r9 within CHS arithmetic. Read-only formatting input and CHS helper boundaries can change alias assumptions; no volatile reload or symbol overlap.
ATTEMPT pfd_sddrv_store_mbr_buf: const formatting input parameter isolates CHS reads from output sector stores; source 1a720184cd4f; objdiff=99.75247%; metric=((0, 9), 202, 202); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_store_mbr_buf: local read-only formatting view spans table lookup and CHS calculation; source 017e7858eba2; objdiff=99.75247%; metric=((0, 9), 202, 202); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_store_mbr_buf: track-size multiplication in read-only settings helper with const format parameter; source 73df2e161b68; objdiff=99.09406%; metric=((5, 146), 203, 202); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
BEGIN pfd_sddrv_build_fat32_mbr_bpb: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((24, 122), 230, 222)
DIAGNOSIS pfd_sddrv_build_fat32_mbr_bpb: 230/222 instructions; same frame. Target reserved sector builder has no null-buffer failure because sole caller passes static 512-byte buffer. Ours inlining keeps null/error path. First block write argument load order also differs. Fix helper type/known object input before scheduling; no extent overlap.
ATTEMPT pfd_sddrv_build_fat32_mbr_bpb: reserved sector helper takes real typed sector object instead of byte-pointer alias; source c29717b898f6; objdiff=94.74324%; metric=((26, 122), 230, 222); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
pfd_sddrv_build_fat32_mbr_bpb dead-check proof: private reserved-sector helper has one call site, always g_pfd_sddrv_buf[512], a defined object whose address is nonnull. Removing its unreachable null failure preserves every call and payload store; target inlined block likewise omits it.
ATTEMPT pfd_sddrv_build_fat32_mbr_bpb: remove unreachable null guard from single-caller private reserved-sector builder; source 05e9e530517e; objdiff=97.20721%; metric=((18, 100), 216, 222); unit code/data/functions=8472/1016/20; pool=FIRST DIVERGENCE at index 41
   39 mine=0x850    base=0x850
      M 'ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()'
      B 'ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()'
   40 mine=0x898    base=0x898
      M 'ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_bu'
      B 'ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_bu'
*  41 mine=0x8e4    base=0x8e4
      M 'ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n'
      B 'ERR Failed to store reserved for boot sector values to buf. '
*  42 mine=0x930    base=0x924
      M 'ERR Failed to get total sectors. pfd_sddrv_get_total_sectors()\n'
      B 'pfd_sddrv_store_fat32_reserved_buf()\n'
*  43 mine=0x970    base=0x94c
      M 'ERR Failed to build up and write MBR and BPB fields.\n'
      B 'ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n'

mine has 44 strings, base has 46; regressions=['main/libs/RVL_SDK/src/fa/driver/sd_drv matched_code', 'main/libs/RVL_SDK/src/fa/driver/sd_drv matched_data', 'main/libs/RVL_SDK/src/fa/driver/sd_drv matched_functions', 'main/libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_full_format']; restored
ATTEMPT pfd_sddrv_build_fat32_mbr_bpb: reserved-sector helper owns its sole static destination object directly; source 79b89e963e83; objdiff=97.20721%; metric=((18, 100), 216, 222); unit code/data/functions=8472/1016/20; pool=FIRST DIVERGENCE at index 41
   39 mine=0x850    base=0x850
      M 'ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()'
      B 'ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()'
   40 mine=0x898    base=0x898
      M 'ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_bu'
      B 'ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_bu'
*  41 mine=0x8e4    base=0x8e4
      M 'ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n'
      B 'ERR Failed to store reserved for boot sector values to buf. '
*  42 mine=0x930    base=0x924
      M 'ERR Failed to get total sectors. pfd_sddrv_get_total_sectors()\n'
      B 'pfd_sddrv_store_fat32_reserved_buf()\n'
*  43 mine=0x970    base=0x94c
      M 'ERR Failed to build up and write MBR and BPB fields.\n'
      B 'ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n'

mine has 44 strings, base has 46; regressions=['main/libs/RVL_SDK/src/fa/driver/sd_drv matched_code', 'main/libs/RVL_SDK/src/fa/driver/sd_drv matched_data', 'main/libs/RVL_SDK/src/fa/driver/sd_drv matched_functions', 'main/libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_full_format']; restored
BEGIN PFCACHE_DoWriteNumSectorAndFreeIfNeeded: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 4), 233, 233)
DIAGNOSIS PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 233/233 instructions and same frame. Four register operand differences only in right overlap block, page sector versus recomputed end occupy r4/r5 oppositely. Last-sector subtraction scheduled identically. Data/strings absent, no volatile store-reload evidence or extent overlap. Change read-only overlap input boundaries, no declaration permutations.
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap helper reads request end through const scalar pointer; source 606706d65afa; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap helper uses separate const page view for sector input; source d5f6e06ac285; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: typed read-only request-end record across overlap update boundary; source 9a7956d662f5; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
BEGIN NWC24iCheckDlHeaderConsistency: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=True; diagnosis metric=((2, 3), 212, 212)
NWC24iCheckDlHeaderConsistency local type proof: DlTaskData ends with url[0xec], fileName[0x5c], optOut byte and 3 reserved bytes, total 0x200; matches opaque NWC24DlTask 0x200. Stack object replacement represents the same task, with no padding added or extent change.
ATTEMPT NWC24iCheckDlHeaderConsistency: real structured task stack object cast at the opaque API boundary; source fcd54af0851f; objdiff=98.77358%; metric=((2, 3), 212, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24iCheckDlHeaderConsistency: structured task receives opaque view through typed inline boundary; source 301ca3eb1edc; objdiff=98.77358%; metric=((2, 3), 212, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
ATTEMPT NWC24iCheckDlHeaderConsistency: typed task pointer stays structured until each opaque read/delete boundary; source 1bc6e69d54e9; objdiff=98.77358%; metric=((2, 3), 212, 212); unit code/data/functions=8456/80/26; pool=POOL IDENTICAL up to 3 (mine=3 base=3); regressions=[]; restored
BEGIN PFCACHE_DoWriteNumSectorAndFreeIfNeeded: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 4), 233, 233)
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: request-end formal is reduced in place to overlap count after deriving last sector; source b10773207f13; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap count starts from end and subtracts page before computing last sector; source 85f5d01a2a49; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
ATTEMPT PFCACHE_DoWriteNumSectorAndFreeIfNeeded: const source-sector lifetime retained for both overlap updates without separate overlap object; source f643ee71364a; objdiff=99.8927%; metric=((0, 4), 233, 233); unit code/data/functions=6464/0/35; pool=POOL IDENTICAL up to 0 (mine=0 base=0); regressions=[]; restored
BEGIN pfd_sddrv_finalize: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((6, 4), 57, 57)
PFD_SDDRV_INFO type trial proof: media_inserted/media_ejected are 32-bit truth values. Target init and callbacks write 0/1; lifecycle code tests against zero, and offsets remain 0x10/0x14. BOOL preserves width and layout and adds no volatile.
ATTEMPT pfd_sddrv_finalize: media insertion field models target truth value as SDK BOOL; source b5214114691d; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_finalize: both lifecycle truth fields model SDK BOOL with unchanged offsets; source f4736e296197; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_finalize: signed word mask expression preserves only the initialized-bit clearing; source e483acc64c10; objdiff=92.63158%; metric=((6, 4), 57, 57); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
BEGIN pfd_sddrv_get_total_sectors: fetched origin/main=26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source differs from HEAD on remote=False; diagnosis metric=((0, 6), 80, 80)
ATTEMPT pfd_sddrv_get_total_sectors: wide unsigned shift factor is narrowed at final sector multiplication; source eef542901c40; objdiff=99.5%; metric=((0, 5), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_get_total_sectors: signed arithmetic shift factor narrowed at product, exponent constrained to zero through two; source 7322e282bd0f; objdiff=99.5%; metric=((0, 5), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored
ATTEMPT pfd_sddrv_get_total_sectors: factor uses explicit unsigned shift expression and single 16-bit conversion; source 8666142025c4; objdiff=96.9875%; metric=((3, 10), 80, 80); unit code/data/functions=8940/3592/21; pool=POOL IDENTICAL up to 46 (mine=46 base=46); regressions=[]; restored

## Final open-function audit before clean gate
Every open symbol was checked after fresh origin fetch. Data and strings stayed identical; all failed variants restored. No declaration permutations used. All 13 open functions have at least three distinct source-level attempts with successful object builds.

OPEN NHTTPi_strnicmp: 99.76471%; 51/51 instructions; Z and zero initialization order exchanged, every later instruction identical; 3 distinct successful source attempts; all reverted.
OPEN NHTTPi_compareToken: 54.622223%; 44/45 instructions; loop entry and right-fold conditional value lifetime differ; 6 distinct successful source attempts; all reverted.
OPEN NHTTPi_Base64Encode: 60.285713%; 119/119 instructions; source byte/table lookup scheduling and signed padding comparisons differ; 3 distinct successful source attempts; all reverted.
OPEN NWC24InitDlTask: 98.923615%; 144/144 instructions; saved registers for zeros, owner ID, header and permission lifetimes differ; 3 distinct successful source attempts; all reverted.
OPEN NWC24UpdateDlTask: 95.00395%; 249/253 instructions; additional saved register/frame and permission/access/retry helper boundaries differ; 3 distinct successful source attempts; all reverted.
OPEN NWC24iCheckDlHeaderConsistency: 98.77358%; 212/212 instructions; stack task address materialization scheduled after saved argument copies; 6 distinct successful source attempts; all reverted.
OPEN AddTaskInternal: 97.7182%; 398/401 instructions; URL/free-slot/retry branch boundaries and saved register lifetimes differ; 3 distinct successful source attempts; all reverted.
OPEN pfd_sddrv_init: 92.326385%; 144/144 instructions; null/identity branch lowering and device/media/flag store-load scheduling differ; 3 distinct successful source attempts; all reverted.
OPEN pfd_sddrv_finalize: 92.63158%; 57/57 instructions; final flag-mask register and media-reset scheduling differ; 6 distinct successful source attempts; all reverted.
OPEN pfd_sddrv_get_total_sectors: 99.5%; 80/80 instructions; six register differences in narrow multiplier shift and product; 6 distinct successful source attempts; all reverted.
OPEN pfd_sddrv_store_mbr_buf: 99.75247%; 202/202 instructions; nine register differences for CHS track product and partition start; 3 distinct successful source attempts; all reverted.
OPEN pfd_sddrv_build_fat32_mbr_bpb: 94.75225%; 230/222 instructions; reserved-sector inline null/error path and block-write arguments differ; 3 distinct successful source attempts; all reverted.
OPEN PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 99.8927%; 233/233 instructions; request end and page sector exchange r4/r5 in right-overlap arithmetic; 6 distinct successful source attempts; all reverted.

Source-quality audit: only accepted source change is const NWC24Work* in NWC24IterateDlTask. No comments, new asm, volatile, register keyword, label pins, dummy objects, function renames, symbol/config changes, shared headers, other units, link flags, or remote writes. Data totals remain 112/80/3592/0, all 100%. Local accepted source commit f9c79662.

## Final full clean gate over all four units

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL libs/RevoEX/src/nwc24/NWC24Download libs/RVL_SDK/src/fa/driver/sd_drv libs/RVL_SDK/src/fa/pf_cache

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1388/2248 data 112/112 functions 11/14 fuzzy 87.9359 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] instruction-exact functions: 11/14
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .data size 72 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .text size 2248 match 87.93594
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_strnicmp 99.76471
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_compareToken 54.622223
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_Base64Encode 60.285713
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] baseline: code 1388/2248 data 112 functions 11 fuzzy 87.9359
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8456/12496 data 80/80 functions 26/30 fuzzy 99.1697 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 26/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.169655
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8140/12496 data 80 functions 25 fuzzy 99.1521
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 3592/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 3592 functions 21 fuzzy 99.0544
[libs/RVL_SDK/src/fa/pf_cache] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_cache] objdiff: code 6464/7396 data None/None functions 35/36 fuzzy 99.9865 linked code 0
[libs/RVL_SDK/src/fa/pf_cache] instruction-exact functions: 35/36
[libs/RVL_SDK/src/fa/pf_cache]   section .text size 7396 match 99.98648
[libs/RVL_SDK/src/fa/pf_cache]   below 100: PFCACHE_DoWriteNumSectorAndFreeIfNeeded 99.8927
[libs/RVL_SDK/src/fa/pf_cache] baseline: code 6464/7396 data None functions 35 fuzzy 99.9865
regressions vs baseline: 0
global matched_code_percent: 91.02223 -> 91.03278
global fuzzy_match_percent: 99.58757 -> 99.58764
global complete_code_percent: 73.73083 -> 73.73083
global matched_data_percent: 99.42271 -> 99.42271
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after instruction-exact/code/data:
NHTTP_stdlib_RVL: 11/14 -> 11/14; 1388/2248 -> 1388/2248; 112/112 -> 112/112.
NWC24Download: 25/30 -> 26/30; 8140/12496 -> 8456/12496; 80/80 -> 80/80.
sd_drv: 21/26 -> 21/26; 8940/11760 -> 8940/11760; 3592/3592 -> 3592/3592.
pf_cache: 35/36 -> 35/36; 6464/7396 -> 6464/7396; 0/0 -> 0/0.

Only NWC24IterateDlTask gained exact bytes. Const work view is proven by objdiff 100%, 79/79 identical instructions, and the final clean gate. All other trials are reverted. Remaining functions and reasons are in the OPEN audit above. No uncertainty about measured gains; source-level causes for the parked compiler differences remain unresolved.

Official declsearch scoring only after structural/source trials. No permutations and no source mutations.
NHTTPi_strnicmp: structural 2 exact 2.
NHTTPi_compareToken: structural 24 exact 42.
NHTTPi_Base64Encode: structural 71 exact 58.
NWC24InitDlTask: structural 0 exact 31.
NWC24UpdateDlTask: structural 19 exact 250.
NWC24iCheckDlHeaderConsistency: structural 2 exact 3.
AddTaskInternal: structural 20 exact 323.
pfd_sddrv_init: structural 18 exact 31.
pfd_sddrv_finalize: structural 6 exact 4.
pfd_sddrv_get_total_sectors: structural 0 exact 6.
pfd_sddrv_store_mbr_buf: structural 0 exact 9.
pfd_sddrv_build_fat32_mbr_bpb: structural 24 exact 122.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: structural 0 exact 4.

Accepted symbol final fresh ctxdiff:
```text
src 0x13c base 0x13c insns 79/79
diffs 0: []
```
Final progress/report.json and build/43U/ok targets pass. The full clean gate remains GATE PASS. Source change and all non-text scores are unchanged after scoring.
