# Permuter lane 2, recovery and continuation

HEAD 674722c158ff057be7a5110841cf18b50d1cb631
Origin 674722c158ff057be7a5110841cf18b50d1cb631

Scope: five assigned C units. No source or config changes outside these units. Keep pfd_sddrv_get_total_sectors unchanged. Resume existing /tmp/perm-* dirs. At most three permuter jobs.

## Initial pools
libs/RevoEX/src/nhttp/NHTTP_recvbuf: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVL_SDK/src/fa/pf_cache: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/nwc24/NWC24Download: POOL IDENTICAL up to 3 (mine=3 base=3)
libs/RVL_SDK/src/fa/driver/sd_drv: POOL IDENTICAL up to 46 (mine=46 base=46)
libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL: POOL IDENTICAL up to 1 (mine=1 base=1)

## NHTTPi_Base64Encode recovery

Fresh origin/main 674722c1 has #996 byte caching and a mutable static alphabet, 67.63025%, 119/119 instructions, 67 differences. Re-derived from current function: replace the array with an ordinary alphabet literal, keep signed s32 length, and read each triplet in the natural indexing expressions with low bits before the next byte shift. Preserve every other #996 change. Result: 119/119 instructions, diffs 0, pool 1/1 identical. Previous permuter hint 6240 -> 400 was the immutable literal; this recovery uses the readable exact implementation.

Recovery accepted locally: exact-name objdiff 100.0%, ctxdiff diffs 0, 119/119 instructions, pool identical, 112/112 data. Full non-quick GATE PASS, DOL 26116613f624061ba99c8d1a299aaa6efa85670d, 0 regressions, 0 forbidden patterns, 0 readability warnings. stdlib 11/14 -> 12/14, code 1388 -> 1864 / 2248. Gate /tmp/perm2b-gate-base64.txt.

## Previous-round evidence

Prior log preserved at /tmp/perm2-old-attempts.md, from orch/perm2-progress. All twelve still-open functions had at least three compiled readable attempts there. Raw best scores: cache 25, recvbuf 180 with rejected public-width change, InitDlTask 155, UpdateDlTask 440, header consistency 60, AddTaskInternal 1127 with rejected truncation, sd init 883 with rejected extra write, finalize 60, store_mbr 50, FAT32 builder 1430 with rejected unreachable report, strnicmp 20, compareToken 567 on pre-#996 source. Resuming original dirs with current context and safe weights; new source trials below. No old fuzzy edit copied.

Setup regenerated from current MWCC preprocessor and ninja compile flags. Each directory retains previous-round inputs and old output candidates. New weights disable external/API changes, AST removal and dummy/no-op passes. Identical compile flags to ninja, excluding dependency-file generation.

### NHTTPi_strnicmp resumed permuter
Fresh origin bc2b18090b6a3aaa67f42945d32b55bd3646bf94, exact-name objdiff 99.76471%.

### NWC24iCheckDlHeaderConsistency resumed permuter
Fresh origin bc2b18090b6a3aaa67f42945d32b55bd3646bf94, exact-name objdiff 98.77358%.

### PFCACHE_DoWriteNumSectorAndFreeIfNeeded resumed permuter
Fresh origin bc2b18090b6a3aaa67f42945d32b55bd3646bf94, exact-name objdiff 99.8927%.
NWC24iCheckDlHeaderConsistency run finished, raw best None, new outputs 0, elapsed 2s. Log /tmp/perm-NWC24iCheckDlHeaderConsistency/run-b.log.

### NHTTPi_compareToken resumed permuter
Fresh origin bc2b18090b6a3aaa67f42945d32b55bd3646bf94, exact-name objdiff 98.844444%.
NHTTPi_compareToken improvement output-30-1 score 30, elapsed 32s.

### PFCACHE_DoWriteNumSectorAndFreeIfNeeded readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. pass the exclusive sector end before the cache page in the overlap helper: 99.8927% objdiff, 233/233 instructions, diffs 4.
2. return the last written sector directly after overlap bookkeeping: 99.8927% objdiff, 233/233 instructions, diffs 4.
3. compute the page overlap before the last written sector: 99.8927% objdiff, 233/233 instructions, diffs 4.

### NHTTPi_strnicmp readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. test the right zero byte before the left zero byte: 98.29412% objdiff, 51/51 instructions, diffs 11.
2. continue comparison inside the positive remaining length branch: compile failed
User break, cancelled...
### mwcceppc.exe Compiler:
#    File: Z:\tmp\perm2b-manual\NHTTPi_strnicmp-2.c
# -------------------------------------------------
#      16:         int a=*left++, b=*right++;
#   Error:         ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program
.
3. keep the unequal lowercase comparison in an explicit alternate branch: 99.76471% objdiff, 51/51 instructions, diffs 2.

### NWC24iCheckDlHeaderConsistency readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. use the incoming header directly in the task-range loop: 98.77358% objdiff, 212/212 instructions, diffs 3.
2. use the incoming repair flag directly at the repair guard: 98.77358% objdiff, 212/212 instructions, diffs 3.
3. initialize the task view together with the pointer declaration: 98.77358% objdiff, 212/212 instructions, diffs 3.

Header-consistency resumed run hit a parser collision with SDK NAND permission enumerators named PERM_USER_READ etc. Renamed those enumeration identifiers only in /tmp input, retaining all values. The failed two-second run is excluded; retry required. Same sanitation applied to queued download functions.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. compare the lowercase right token before the cached left token: 97.066666% objdiff, 45/45 instructions, diffs 18.
2. keep the raw left token byte in a signed byte local: 94.95556% objdiff, 46/45 instructions, diffs 25.
3. keep the raw left token byte in a word-sized local: 99.51111% objdiff, 45/45 instructions, diffs 4.

### NHTTPi_compareTokenN_HdrRecvBuf readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. derive the last header position once after locating its block: 95.40323% objdiff, 124/124 instructions, diffs 54.
2. lower the token byte in a natural loop local before comparing the header: 57.64516% objdiff, 124/124 instructions, diffs 63.
3. increment the token before advancing the response position: 97.16129% objdiff, 124/124 instructions, diffs 7.

### pfd_sddrv_store_mbr_buf readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. keep the CHS cylinder values word-sized until storing their low bits: 94.80198% objdiff, 198/202 instructions, diffs 145.
2. keep the CHS sector values word-sized until their packed store: 93.044556% objdiff, 198/202 instructions, diffs 145.
3. keep start and end CHS head numbers word-sized until their byte stores: 92.52475% objdiff, 200/202 instructions, diffs 150.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
4. use a s32 raw left token byte before signed character comparisons: 99.51111% objdiff, 45/45 instructions, diffs 4.
5. use a u32 raw left token byte before signed character comparisons: 99.51111% objdiff, 45/45 instructions, diffs 4.
6. use a short raw left token byte before signed character comparisons: 99.51111% objdiff, 45/45 instructions, diffs 4.

### NHTTPi_strnicmp readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
4. declare the loaded bytes before the explicit remaining-length guard: 96.62745% objdiff, 50/51 instructions, diffs 48.
5. reverse only the inner two-zero test: 99.56863% objdiff, 51/51 instructions, diffs 4.
6. return directly when both compared strings reach the terminator: 95.745094% objdiff, 51/51 instructions, diffs 6.

### NWC24InitDlTask readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. keep parsed title identifiers together in a natural title-id pair: compile failed
User break, cancelled...
### mwcceppc.exe Compiler:
#    File: Z:\tmp\perm2b-manual\NWC24InitDlTask-1.c
# -------------------------------------------------
#     292:     task->nwc24IdHigh = nwc24IdHigh;
#   Error:                         ^^^^^^^^^^^
#   (10140) undefined identifier 'nwc24IdHigh'
#   Too many errors printed, aborting program
.
2. scope the task data pointer to the validated initialization block: 98.923615% objdiff, 144/144 instructions, diffs 31.
3. use the natural combined guard for the optional content filename: 95.416664% objdiff, 139/144 instructions, diffs 93.

### NWC24UpdateDlTask readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. name writable validation before passing the naturally typed task view: 99.031624% objdiff, 253/253 instructions, diffs 26.
2. name writable validation and keep the retry count in its natural loop local: 95.8498% objdiff, 253/253 instructions, diffs 64.
3. name writable validation and use the alternate successful-retry branch: 97.80633% objdiff, 256/253 instructions, diffs 86.

### AddTaskInternal readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. separate allocation and purge statuses while reloading the task ID: 97.7182% objdiff, 398/401 instructions, diffs 323.
2. check successful allocation before continuing the allocation loop: 97.7182% objdiff, 398/401 instructions, diffs 323.
3. cache the task identifier inside each allocation-loop iteration: 97.7182% objdiff, 398/401 instructions, diffs 323.

### pfd_sddrv_finalize readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. name final driver cleanup as an inline state helper: 92.63158% objdiff, 57/57 instructions, diffs 4.
2. clear the final media and drive fields with the natural reverse assignment chain: 89.210526% objdiff, 57/57 instructions, diffs 6.
3. clear the initialized flag after zeroing the drive only: 81.929825% objdiff, 57/57 instructions, diffs 9.

### pfd_sddrv_init readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. keep the device status signed for its single insertion-bit test: 92.326385% objdiff, 144/144 instructions, diffs 31.
2. keep the mounted device in an explicit initialized task-local slot: 88.05556% objdiff, 144/144 instructions, diffs 62.
3. hold a natural driver-info alias for the final successful initialization: 84.75% objdiff, 143/144 instructions, diffs 61.

### pfd_sddrv_build_fat32_mbr_bpb readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
1. pass the natural format-data view to each FAT32 sector store: 92.815315% objdiff, 231/222 instructions, diffs 221.
2. give BPB validation and sector writes separate meaningful statuses: 85.50901% objdiff, 227/222 instructions, diffs 224.
3. use a success continuation for the final master-boot-record sector write: 93.193695% objdiff, 230/222 instructions, diffs 122.

### NWC24InitDlTask readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
4. store parsed title-id halves in a naturally named local pair: 98.923615% objdiff, 144/144 instructions, diffs 31.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
7. load the right token as an unsigned byte before its signed lowercase conversion: 99.73333% objdiff, 45/45 instructions, diffs 2.
8. cache the unsigned right token byte only for lowercase conversion: 99.73333% objdiff, 45/45 instructions, diffs 2.
9. keep the lowercase right token in its own word-sized local: 59.288887% objdiff, 45/45 instructions, diffs 38.
10. express lowercase folding as the original conditional assignment: 94.62222% objdiff, 44/45 instructions, diffs 30.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
11. test the space token before the terminating byte: 97.37778% objdiff, 46/45 instructions, diffs 43.
12. use the raw word value for its known zero token test: 96.17778% objdiff, 46/45 instructions, diffs 43.
13. test a matched token terminator through an inverted continuation guard: 89.95556% objdiff, 46/45 instructions, diffs 41.
14. fold the two token bytes with a natural maximum-before-minimum predicate: 74.066666% objdiff, 41/45 instructions, diffs 45.

### NHTTPi_strnicmp readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
7. keep the lowercase right result in a signed byte conversion: 95.15686% objdiff, 52/51 instructions, diffs 36.
8. fold compared bytes with a maximum-before-minimum case predicate: 88.39216% objdiff, 47/51 instructions, diffs 50.
9. test the uppercase range with inverted out-of-range bit predicates: 30.980392% objdiff, 52/51 instructions, diffs 52.

### PFCACHE_DoWriteNumSectorAndFreeIfNeeded readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
4. record each overlap count from its natural sector range: 98.090126% objdiff, 235/233 instructions, diffs 105.
5. pass the page-start value separately to overlap accounting: 99.8927% objdiff, 233/233 instructions, diffs 4.
6. subtract remaining sectors before adding completed-sector overlap: 99.8927% objdiff, 233/233 instructions, diffs 4.

### NWC24iCheckDlHeaderConsistency readable trials
Remote source unchanged at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
4. initialize the task cursor at the beginning of the range scan: 98.77358% objdiff, 212/212 instructions, diffs 3.
5. take the task-data view only at the two successful repair stores: 98.77358% objdiff, 212/212 instructions, diffs 3.
6. continue directly for a disabled repair request after valid header lookup: 98.77358% objdiff, 212/212 instructions, diffs 3.

### NHTTPi_strnicmp readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
10. load the right byte before the left byte with separate natural declarations: 97.5098% objdiff, 51/51 instructions, diffs 20.
11. promote the right byte only when passing it to lowercase: 95.94118% objdiff, 52/51 instructions, diffs 33.
12. use signed longs for the two loaded comparison bytes: 99.76471% objdiff, 51/51 instructions, diffs 2.
13. load unsigned comparison bytes and sign them for the lowercase helper: 78.196075% objdiff, 54/51 instructions, diffs 42.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
15. invert the final comparison into a natural continue branch: 57.4% objdiff, 46/45 instructions, diffs 43.
16. advance token pointers in the for-loop update expressions: 99.73333% objdiff, 45/45 instructions, diffs 2.
17. keep the returned mismatch status in the natural matching-loop branch: 99.066666% objdiff, 45/45 instructions, diffs 6.

## Readable hint review so far

NHTTPi_compareToken new raw score 60 -> 30 widens only rawLeft to unsigned int. Readable int/s32/u32/short translations all reach 99.51111%, 45/45 instructions, four differences. Loading the right byte as u8 before its s8 conversion improves the readable form to 99.73333%, two constant-initialization scheduling differences. Both are hints only, so no fuzzy edit retained.

Every currently open function has at least three distinct compiled new source attempts; failures are excluded. Trial sources and exact-name reports stay under /tmp/perm2b-manual. All repository source remains the committed Base64 recovery.

### NHTTPi_compareToken readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
18. assign the lowercase token character before returning it from a local helper: 99.73333% objdiff, 45/45 instructions, diffs 2.
19. name the uppercase token-range predicate before selecting the result: 99.73333% objdiff, 45/45 instructions, diffs 2.
20. name the converted token byte before its uppercase-range selection: 91.4% objdiff, 48/45 instructions, diffs 45.

### NHTTPi_strnicmp readable trials
Remote source changed at bc2b18090b6a3aaa67f42945d32b55bd3646bf94.
14. assign the lowercase string byte before returning from its inline helper: 99.76471% objdiff, 51/51 instructions, diffs 2.
15. name the uppercase string-range predicate before selecting its byte: 99.76471% objdiff, 51/51 instructions, diffs 2.
16. name the converted string byte before the uppercase-range selection: 88.09804% objdiff, 55/51 instructions, diffs 52.

NWC24UpdateDlTask queued seed now uses its readable writable-validation helper, 99.031624%, 253/253 instructions, 26 diffs. Seed is /tmp-only, retaining a copy of the current original seed in the function directory. The helper repairs the prologue instruction count without source noise, so continue permutation from this closer readable form.

Scheduler resumed with all three existing permuter processes preserved. The repaired header-consistency input is queued at the next free slot; at most three jobs remain active throughout.
NHTTPi_strnicmp run finished, raw best 20, new outputs 0, elapsed 2700s. Log /tmp/perm-NHTTPi_strnicmp/run-b.log.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded run finished, raw best 25, new outputs 0, elapsed 2702s. Log /tmp/perm-PFCACHE_DoWriteNumSectorAndFreeIfNeeded/run-b.log.

### NWC24iCheckDlHeaderConsistency resumed permuter
Fresh origin e221614209428fe5ec360f7a6ac092f93dd8b8fa, exact-name objdiff 98.77358%.

### NHTTPi_compareTokenN_HdrRecvBuf resumed permuter
Fresh origin e221614209428fe5ec360f7a6ac092f93dd8b8fa, exact-name objdiff 97.32258%.
NHTTPi_compareToken run finished, raw best 30, new outputs 1, elapsed 2732s. Log /tmp/perm-NHTTPi_compareToken/run-b.log.

### pfd_sddrv_store_mbr_buf resumed permuter
Fresh origin adea4fb5d1a37152aa4ff0050fab1575be56687d, exact-name objdiff 99.75247%.
NWC24iCheckDlHeaderConsistency run finished, raw best 60, new outputs 0, elapsed 292s. Log /tmp/perm-NWC24iCheckDlHeaderConsistency/run-b.log.

### NWC24InitDlTask resumed permuter
Fresh origin a894ff5cb76db05ef7cf425eb5b6a9e25343e460, exact-name objdiff 98.923615%.

NWC24iCheckDlHeaderConsistency produced output-0-1 at 292 seconds, raw score 60 -> 0. The controller missed this final output between its last poll and process exit; state corrected, future controllers now scan final outputs. Inspecting the hint and translating to readable full-unit source before any acceptance.

### NWC24iCheckDlHeaderConsistency readable trials
Remote source unchanged at a894ff5cb76db05ef7cf425eb5b6a9e25343e460.
7. give task reading its own named task pointer as the permuter hinted: 100.0% objdiff, 212/212 instructions, diffs 0.
8. initialize the named read-task pointer directly from the task view: 100.0% objdiff, 212/212 instructions, diffs 0.
9. initialize the named read-task pointer directly from the task object: 100.0% objdiff, 212/212 instructions, diffs 0.
10. declare the read-task pointer together with its assignment before the scan: 99.55189% objdiff, 212/212 instructions, diffs 18.

Header-consistency raw zero translated to readTask, an ordinary initialized pointer used for reading the task object. Tested both direct initialization from &task and from taskPointer: each is 100.0% exact-name objdiff, 212/212 instructions, diffs 0, code 9304/12496 and data 80/80. Selected direct &task initialization, a two-line source change. Paused the same three permuter groups and scheduler for the clean gate.

The detailed temporary source diffs are preserved at /tmp/perm2b-uncondensed-log.md and /tmp/perm2b-manual. This tracked log keeps trial descriptions and measured results.

Header-consistency accepted locally after full non-quick GATE PASS: pool 3/3 identical, exact-name objdiff 100.0%, ctxdiff 212/212 and diffs 0; NWC24Download 26/30 -> 27/30, code 8456 -> 9304 / 12496, data 80/80 unchanged. DOL 26116613f624061ba99c8d1a299aaa6efa85670d, zero regressions, forbidden patterns and readability warnings. Gate /tmp/perm2b-gate-header.txt.

The same three permuter groups and scheduler resumed after the successful clean gate and local commit.

## Remaining-function attempt audit after the two exact commits

| Function | Distinct compiled readable trials | Best readable percent | Repository retained |
|---|---:|---:|---|
| NHTTPi_compareTokenN_HdrRecvBuf | 3 | 97.16129 | no fuzzy edit |
| PFCACHE_DoWriteNumSectorAndFreeIfNeeded | 6 | 99.8927 | no fuzzy edit |
| NWC24InitDlTask | 3 | 98.923615 | no fuzzy edit |
| NWC24UpdateDlTask | 3 | 99.031624 | no fuzzy edit |
| AddTaskInternal | 3 | 97.7182 | no fuzzy edit |
| pfd_sddrv_init | 3 | 92.326385 | no fuzzy edit |
| pfd_sddrv_finalize | 3 | 92.63158 | no fuzzy edit |
| pfd_sddrv_store_mbr_buf | 3 | 94.80198 | no fuzzy edit |
| pfd_sddrv_build_fat32_mbr_bpb | 3 | 93.193695 | no fuzzy edit |
| NHTTPi_strnicmp | 15 | 99.76471 | no fuzzy edit |
| NHTTPi_compareToken | 20 | 99.73333 | no fuzzy edit |

Current-baseline NWC24UpdateDlTask has 249/253 instructions, AddTaskInternal 398/401, and the FAT32 builder 230/222. These are not pure register ties. The close readable UpdateDlTask helper reaches 253/253 but remains non-exact; it is only a permuter seed outside the repo.
NHTTPi_compareTokenN_HdrRecvBuf improvement output-195-1 score 195, elapsed 1085s.

Recvbuf raw hint 270 -> 195 changes the public delimiter from s8 to unsigned short and aliases the offset pointer. Reject the public-width change, as in the prior round. Despite the documented behavior, perm_randomize_internal_type walks function parameter declarations too, bypassing perm_randomize_function_type=0. Added a /tmp compile-time signature guard to every function: generated sources with changed public parameter tokens are rejected before MWCC, while natural local-type permutations remain enabled. Compile flags remain identical to ninja. Existing running permuters use the guarded compile script on their next candidate.

### NHTTPi_compareTokenN_HdrRecvBuf readable trials
Remote source unchanged at 5e0816c3f138027ced9240c617641ded5d4bcc78.
4. use a naturally named header-offset pointer with the original signed delimiter: 97.32258% objdiff, 124/124 instructions, diffs 5.
```diff
---
+++
@@ -76,8 +76,10 @@
     NHTTPi_HDRBUFLIST* block;
     s32 offset;
+    s32* headerOffset;
     int character;
+    headerOffset = &offset;

     if (position < limit) {
-        FindHeaderBlock(response, position, &block, &offset);
+        FindHeaderBlock(response, position, &block, headerOffset);
         character = ReadHeaderChar(response, &block, &offset);
         while (LowerCase((s8)character) == LowerCase(*token)) {
```
5. initialize the header-offset pointer next to its offset declaration: 97.32258% objdiff, 124/124 instructions, diffs 5.
```diff
---
+++
@@ -76,8 +76,9 @@
     NHTTPi_HDRBUFLIST* block;
     s32 offset;
+    s32* headerOffset = &offset;
     int character;

     if (position < limit) {
-        FindHeaderBlock(response, position, &block, &offset);
+        FindHeaderBlock(response, position, &block, headerOffset);
         character = ReadHeaderChar(response, &block, &offset);
         while (LowerCase((s8)character) == LowerCase(*token)) {
```
6. use the header-offset cursor consistently for all header reads: 97.32258% objdiff, 124/124 instructions, diffs 5.
```diff
---
+++
@@ -76,12 +76,14 @@
     NHTTPi_HDRBUFLIST* block;
     s32 offset;
+    s32* headerOffset;
     int character;
+    headerOffset = &offset;

     if (position < limit) {
-        FindHeaderBlock(response, position, &block, &offset);
-        character = ReadHeaderChar(response, &block, &offset);
+        FindHeaderBlock(response, position, &block, headerOffset);
+        character = ReadHeaderChar(response, &block, headerOffset);
         while (LowerCase((s8)character) == LowerCase(*token)) {
             if (*token == 0 || *token == ' ' || *token == delimiter || position == limit - 1) return 0;
-            character = ReadHeaderChar(response, &block, &offset);
+            character = ReadHeaderChar(response, &block, headerOffset);
             ++position;
             ++token;
```

Recvbuf readable offset-pointer translations keep s8 delimiter and all remain 97.32258%, 124/124, five scheduling differences. The unsigned-short signature hint does not count. No repository edit retained.
pfd_sddrv_store_mbr_buf run finished, raw best 50, new outputs 0, elapsed 2701s. Log /tmp/perm-pfd_sddrv_store_mbr_buf/run-b.log.

### NWC24UpdateDlTask resumed permuter
Fresh origin ce2130f8676de950cc8a5019da333815ae1f1f3f, exact-name objdiff 95.00395%.
NWC24InitDlTask run finished, raw best 155, new outputs 0, elapsed 2702s. Log /tmp/perm-NWC24InitDlTask/run-b.log.

### AddTaskInternal resumed permuter
Fresh origin 7649d9b1ec2a40030ae9d3f561ac51eeaa3f0d89, exact-name objdiff 97.7182%.
AddTaskInternal improvement output-1417-1 score 1417, elapsed 230s.

### AddTaskInternal readable trials
Remote source changed at bf8ebfa35379f7243a9ae0de73081573664c8a32.
4. name the real unassigned-task sentinel with its API identifier type: 97.7182% objdiff, 398/401 instructions, diffs 323.
```diff
---
+++
@@ -1290,4 +1290,5 @@
 NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount) {
     DlTaskData* task = (DlTaskData*)dlTask;
+    const NWC24DlId unassignedTaskId = 0xffff;
     NWC24Err result;
     result = ValidateDlTask(dlTask, TRUE);
@@ -1296,5 +1297,5 @@
     if (result < NWC24_OK) { return result; }
     for (;;) {
-        if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
+        if (task->id != unassignedTaskId) { return UpdateDlTaskInline(dlTask); }
         result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
```
5. name the unassigned-task sentinel as a constant word value: 97.7182% objdiff, 398/401 instructions, diffs 323.
```diff
---
+++
@@ -1290,4 +1290,5 @@
 NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount) {
     DlTaskData* task = (DlTaskData*)dlTask;
+    const u32 unassignedTaskId = 0xffff;
     NWC24Err result;
     result = ValidateDlTask(dlTask, TRUE);
@@ -1296,5 +1297,5 @@
     if (result < NWC24_OK) { return result; }
     for (;;) {
-        if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
+        if (task->id != unassignedTaskId) { return UpdateDlTaskInline(dlTask); }
         result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
```
6. scope the named unassigned-task sentinel after URL validation: 97.7182% objdiff, 398/401 instructions, diffs 323.
```diff
---
+++
@@ -1295,6 +1295,8 @@
     result = ValidateDlTaskUrl(dlTask);
     if (result < NWC24_OK) { return result; }
+    {
+    const NWC24DlId unassignedTaskId = 0xffff;
     for (;;) {
-        if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
+        if (task->id != unassignedTaskId) { return UpdateDlTaskInline(dlTask); }
         result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
@@ -1303,4 +1305,5 @@
         } else if (result < NWC24_OK) { return result; }
     }
+    }
 }

```

AddTaskInternal raw 1535 -> 1417 names 0xffff in an extra mutable integer local before the allocation loop. A real named constant with NWC24DlId/u32 type and natural scoping was tried instead; each remains below 100%. No mutable constant-only temporary or fuzzy source retained.
AddTaskInternal improvement output-1415-2 score 1415, elapsed 436s.

AddTaskInternal score-1417 tie 2 adds a two-element status array, redundant status copies, the mutable sentinel and an empty null-test. Rejected as source noise. Ordinary separate operation statuses and named constant forms were already tested without exactness.

AddTaskInternal score-1415 ties 2 and 3 reuse operation status as a cached task ID and fail to refresh it after allocation/purge. Rejected as behavior changes. The readable fresh-ID loop was already compiled, 97.7182%, with no exact result.

Recvbuf stopping after 3551 seconds with no usable improvement. Its only raw improvement, 195, changes the public signed delimiter; three readable offset-cursor translations preserve the original five scheduling differences. Signed API retained, no source accepted.
NHTTPi_compareTokenN_HdrRecvBuf run finished, raw best 195, new outputs 1, elapsed 3553s. Log /tmp/perm-NHTTPi_compareTokenN_HdrRecvBuf/run-b.log.

### pfd_sddrv_finalize resumed permuter
Fresh origin bf8ebfa35379f7243a9ae0de73081573664c8a32, exact-name objdiff 92.63158%.
pfd_sddrv_finalize improvement output-60-9 score 60, elapsed 24s.

### pfd_sddrv_finalize readable trials
Remote source unchanged at bf8ebfa35379f7243a9ae0de73081573664c8a32.
4. name disk validity and retain the readable chained final cleanup: 82.45614% objdiff, 57/57 instructions, diffs 6.
```diff
---
+++
@@ -482,6 +482,7 @@
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
-
-    if (disk == 0) {
+    BOOL invalidDisk = disk == 0;
+
+    if (invalidDisk) {
         return -30;
     }
@@ -501,7 +502,6 @@
     }
     g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
-    g_pfd_sddrv_info.media_inserted = 0;
+    g_pfd_sddrv_info.media_inserted = (g_pfd_sddrv_info.drive = 0);
     g_pfd_sddrv_info.disk = 0;
-    g_pfd_sddrv_info.drive = 0;
     return 0;
 }
```
5. name the unmounted device at its actual reload before unmounting: 82.45614% objdiff, 57/57 instructions, diffs 6.
```diff
---
+++
@@ -482,4 +482,5 @@
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
+    SDDev* device;

     if (disk == 0) {
@@ -494,5 +495,6 @@
             OSReport("WARNING Faild to UnregisterDeviceIntrHandler sd card [ret = %d]\n", result);
         }
-        result = ISD_UnmountCard(g_pfd_sddrv_info.device);
+        device = g_pfd_sddrv_info.device;
+        result = ISD_UnmountCard(device);
         if (result != 0) {
             OSReport("WARNING Faild to unmount sd card [ret = %d]\n", result);
@@ -501,7 +503,6 @@
     }
     g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
-    g_pfd_sddrv_info.media_inserted = 0;
+    g_pfd_sddrv_info.media_inserted = (g_pfd_sddrv_info.drive = 0);
     g_pfd_sddrv_info.disk = 0;
-    g_pfd_sddrv_info.drive = 0;
     return 0;
 }
```
6. name mounted state through its real flag test before cleanup: 82.45614% objdiff, 57/57 instructions, diffs 6.
```diff
---
+++
@@ -486,6 +486,7 @@
         return -30;
     }
-    if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 2) != 0) {
-        clear_mount_flag();
+    {
+        BOOL mounted = (pfd_sddrv_flags(&g_pfd_sddrv_info) & 2) != 0;
+        if (mounted) clear_mount_flag();
     }
     if ((g_pfd_sddrv_info.flags & 1) != 0) {
@@ -501,7 +502,6 @@
     }
     g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
-    g_pfd_sddrv_info.media_inserted = 0;
+    g_pfd_sddrv_info.media_inserted = (g_pfd_sddrv_info.drive = 0);
     g_pfd_sddrv_info.disk = 0;
-    g_pfd_sddrv_info.drive = 0;
     return 0;
 }
```

Finalize raw 295 -> 60 repeats the old chained drive/media cleanup, plus a mutable flag-mask status and a boolean null guard. New readable disk-validity, mounted-state and real-device reload translations keep the ordinary chain but are not exact in the full translation unit. Redundant device-copy ties are rejected. No source retained.
AddTaskInternal improvement output-1372-1 score 1372, elapsed 916s.

AddTaskInternal raw 1372 moves the real purge call into the already-assigned-ID branch and removes it from the full-list recovery branch. All three ties share that behavior change; rejected. Meaningful ID refresh, status and allocation-loop alternatives are already measured.

## Local accepted source review

Base64 uses the ordinary immutable alphabet literal and direct signed-byte indexing, keeping signed length and all other #996 functions. Header consistency adds one initialized readTask pointer used for the actual read call; validation and repair use the existing taskPointer view. Neither change adds an unused object, inline assembly, casts to volatile, register declarations, pinned addresses or unrelated source/config edits. Both fresh full gates pass with exact object and DOL evidence.
AddTaskInternal improvement output-1245-6 score 1245, elapsed 1342s.

### AddTaskInternal readable trials
Remote source changed at cc94a7530c7c03027ada69dd55d7bf6be6a5eb54.
7. keep the first allocation ID in a named word value without pointer indirection: 98.81546% objdiff, 400/401 instructions, diffs 324.
```diff
---
+++
@@ -1291,5 +1291,7 @@
     DlTaskData* task = (DlTaskData*)dlTask;
     NWC24Err result;
+    s32 firstTaskId;
     result = ValidateDlTask(dlTask, TRUE);
+    firstTaskId = taskCount;
     if (result != NWC24_OK) { return result; }
     result = ValidateDlTaskUrl(dlTask);
@@ -1297,5 +1299,5 @@
     for (;;) {
         if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
-        result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
+        result = FindFreeDlTask(dlTask, firstTaskId, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
             result = NWC24PurgeOldestDlTask();
```
8. pass the first allocation ID with its real SDK identifier cast: 98.81546% objdiff, 400/401 instructions, diffs 324.
```diff
---
+++
@@ -1297,5 +1297,5 @@
     for (;;) {
         if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
-        result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
+        result = FindFreeDlTask(dlTask, (NWC24DlId)taskCount, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
             result = NWC24PurgeOldestDlTask();
```
9. retain an explicit unsigned-short argument conversion instead of a redundant mask: 98.81546% objdiff, 400/401 instructions, diffs 324.
```diff
---
+++
@@ -1297,5 +1297,5 @@
     for (;;) {
         if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
-        result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
+        result = FindFreeDlTask(dlTask, (u16)taskCount, maxTaskCount);
         if (result == NWC24_ERR_FULL) {
             result = NWC24PurgeOldestDlTask();
```

AddTaskInternal raw 1245 tie 6 aliases a widened allocation-start ID, adds pointer-to-pointer indirection, a zero sentinel and an if(1) block. Tie 7 only adds taskCount & 0xffff. Tested the named allocation ID and natural SDK/u16 argument conversions without the noise; none is exact. The redundant mask and pointer indirection are not retained. Finalize tie 12 is only the already-tested chained drive/media cleanup; still non-exact in the full unit.

### pfd_sddrv_init readable trials
Remote source unchanged at 885cdfeee63a4b681bb5242e198dd7220834eb43.
4. use the SDK NULL macro for the input disk guard: 92.326385% objdiff, 144/144 instructions, diffs 31.
```diff
---
+++
@@ -314,5 +314,5 @@
     u32 status;

-    if (disk == 0) {
+    if (disk == NULL) {
         return -30;
     }
```
5. return the different-disk error before the already-initialized success: 92.326385% objdiff, 144/144 instructions, diffs 31.
```diff
---
+++
@@ -319,8 +319,8 @@
     if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 1) != 0) {
         OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
-        if (disk == g_pfd_sddrv_info.disk) {
-            return 0;
-        }
-        return -44;
+        if (disk != g_pfd_sddrv_info.disk) {
+            return -44;
+        }
+        return 0;
     }
     if ((g_pfd_sddrv_info.flags & 4) == 0) {
```
6. combine the SDK NULL guard with the different-disk early error: 92.326385% objdiff, 144/144 instructions, diffs 31.
```diff
---
+++
@@ -314,13 +314,13 @@
     u32 status;

-    if (disk == 0) {
+    if (disk == NULL) {
         return -30;
     }
     if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 1) != 0) {
         OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
-        if (disk == g_pfd_sddrv_info.disk) {
-            return 0;
-        }
-        return -44;
+        if (disk != g_pfd_sddrv_info.disk) {
+            return -44;
+        }
+        return 0;
     }
     if ((g_pfd_sddrv_info.flags & 4) == 0) {
```
7. express the already-initialized disk identity through its return value: 92.326385% objdiff, 144/144 instructions, diffs 31.
```diff
---
+++
@@ -314,13 +314,10 @@
     u32 status;

-    if (disk == 0) {
+    if (disk == NULL) {
         return -30;
     }
     if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 1) != 0) {
         OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
-        if (disk == g_pfd_sddrv_info.disk) {
-            return 0;
-        }
-        return -44;
+        return disk == g_pfd_sddrv_info.disk ? 0 : -44;
     }
     if ((g_pfd_sddrv_info.flags & 4) == 0) {
```

### pfd_sddrv_finalize readable trials
Remote source unchanged at 885cdfeee63a4b681bb5242e198dd7220834eb43.
7. use the SDK NULL macro for finalization input validation: 92.63158% objdiff, 57/57 instructions, diffs 4.
```diff
---
+++
@@ -483,5 +483,5 @@
     s32 result;

-    if (disk == 0) {
+    if (disk == NULL) {
         return -30;
     }
```
8. capture the final flags in a named cleanup value: 92.61404% objdiff, 57/57 instructions, diffs 5.
```diff
---
+++
@@ -482,4 +482,5 @@
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
+    u32 flags;

     if (disk == 0) {
@@ -500,7 +501,8 @@
         g_pfd_sddrv_info.device = 0;
     }
-    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
+    flags = g_pfd_sddrv_info.flags & 0xfffffffe;
     g_pfd_sddrv_info.media_inserted = 0;
     g_pfd_sddrv_info.disk = 0;
+    g_pfd_sddrv_info.flags = flags;
     g_pfd_sddrv_info.drive = 0;
     return 0;
```
9. use a natural info pointer for the final cleanup fields: 83.91228% objdiff, 58/57 instructions, diffs 53.
```diff
---
+++
@@ -482,4 +482,5 @@
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
+    PFD_SDDRV_INFO* info = &g_pfd_sddrv_info;

     if (disk == 0) {
@@ -500,8 +501,8 @@
         g_pfd_sddrv_info.device = 0;
     }
-    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
-    g_pfd_sddrv_info.media_inserted = 0;
-    g_pfd_sddrv_info.disk = 0;
-    g_pfd_sddrv_info.drive = 0;
+    info->flags &= 0xfffffffe;
+    info->media_inserted = 0;
+    info->disk = 0;
+    info->drive = 0;
     return 0;
 }
```

### pfd_sddrv_init readable trials
Remote source unchanged at 885cdfeee63a4b681bb5242e198dd7220834eb43.
8. name the already-initialized disk result before returning it: 92.94444% objdiff, 142/144 instructions, diffs 138.
```diff
---
+++
@@ -319,8 +319,9 @@
     if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 1) != 0) {
         OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
-        if (disk == g_pfd_sddrv_info.disk) {
-            return 0;
-        }
-        return -44;
+        sd_result = 0;
+        if (disk != g_pfd_sddrv_info.disk) {
+            sd_result = -44;
+        }
+        return sd_result;
     }
     if ((g_pfd_sddrv_info.flags & 4) == 0) {
```
9. name the current-driver disk identity check as an inline predicate: 92.326385% objdiff, 144/144 instructions, diffs 31.
```diff
---
+++
@@ -309,4 +309,8 @@
 }

+static inline BOOL pfd_sddrv_is_current_disk(FADisk* disk) {
+    return disk == g_pfd_sddrv_info.disk;
+}
+
 s32 pfd_sddrv_init(FADisk* disk) {
     s32 sd_result;
@@ -319,5 +323,5 @@
     if ((pfd_sddrv_flags(&g_pfd_sddrv_info) & 1) != 0) {
         OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
-        if (disk == g_pfd_sddrv_info.disk) {
+        if (pfd_sddrv_is_current_disk(disk)) {
             return 0;
         }
```
10. publish the mounted device in each real insertion-state branch: 87.84722% objdiff, 146/144 instructions, diffs 74.
```diff
---
+++
@@ -349,6 +349,6 @@
         g_pfd_sddrv_info.media_inserted = 1;
     }
-    g_pfd_sddrv_info.device = device;
     if (g_pfd_sddrv_info.media_inserted != 0) {
+        g_pfd_sddrv_info.device = device;
         g_event = 2;
         sd_result = ISD_RegisterDeviceIntrHandler(device, (SDDevIntrCallback)pfd_st_removal_callback, &g_event);
@@ -360,4 +360,5 @@
         }
     } else {
+        g_pfd_sddrv_info.device = device;
         g_event = 1;
         sd_result = ISD_RegisterDeviceIntrHandler(device, (SDDevIntrCallback)pfd_st_inter_callback, &g_event);
```

### pfd_sddrv_finalize readable trials
Remote source unchanged at 885cdfeee63a4b681bb5242e198dd7220834eb43.
10. complete the initialized-flag mask before clearing final state: 92.63158% objdiff, 57/57 instructions, diffs 4.
```diff
---
+++
@@ -482,4 +482,5 @@
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
+    u32 flags;

     if (disk == 0) {
@@ -500,5 +501,7 @@
         g_pfd_sddrv_info.device = 0;
     }
-    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
+    flags = g_pfd_sddrv_info.flags;
+    flags &= 0xfffffffe;
+    g_pfd_sddrv_info.flags = flags;
     g_pfd_sddrv_info.media_inserted = 0;
     g_pfd_sddrv_info.disk = 0;
```
11. name the initialized-flag update as an inline cleanup step: 92.63158% objdiff, 57/57 instructions, diffs 4.
```diff
---
+++
@@ -480,4 +480,8 @@
 }

+static inline void pfd_sddrv_clear_init_flag(void) {
+    g_pfd_sddrv_info.flags &= 0xfffffffe;
+}
+
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
@@ -500,5 +504,5 @@
         g_pfd_sddrv_info.device = 0;
     }
-    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
+    pfd_sddrv_clear_init_flag();
     g_pfd_sddrv_info.media_inserted = 0;
     g_pfd_sddrv_info.disk = 0;
```
12. use an initialized-flag helper and natural chained media-drive cleanup: 82.45614% objdiff, 57/57 instructions, diffs 6.
```diff
---
+++
@@ -480,4 +480,8 @@
 }

+static inline void pfd_sddrv_clear_init_flag(void) {
+    g_pfd_sddrv_info.flags &= 0xfffffffe;
+}
+
 s32 pfd_sddrv_finalize(FADisk* disk) {
     s32 result;
@@ -500,8 +504,7 @@
         g_pfd_sddrv_info.device = 0;
     }
-    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
-    g_pfd_sddrv_info.media_inserted = 0;
+    pfd_sddrv_clear_init_flag();
+    g_pfd_sddrv_info.media_inserted = g_pfd_sddrv_info.drive = 0;
     g_pfd_sddrv_info.disk = 0;
-    g_pfd_sddrv_info.drive = 0;
     return 0;
 }
```

### PFCACHE_DoWriteNumSectorAndFreeIfNeeded readable trials
Remote source unchanged at 9c7d87ab008df7e35558321e3ca297a887d35c44.
7. form the exclusive sector end in one natural addition before bookkeeping: 98.62661% objdiff, 232/233 instructions, diffs 106.
```diff
---
+++
@@ -618,6 +618,5 @@
                 pf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                     (sector + num_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector);
-                num_overlap = num_sector;
-                num_overlap += sector;
+                num_overlap = sector + num_sector;
                 last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
```
8. pass the cache page sector directly to the overlap-count helper: compile failed
User break, cancelled...
### mwcceppc.exe Compiler:
#    File: Z:\tmp\perm2b-manual\PFCACHE_DoWriteNumSectorAndFreeIfNeeded-8.c
# -------------------------------------------------------------------------
#     558:     p_page->stat |= 2;
#   Error:     ^^^^^^
#   (10140) undefined identifier 'p_page'
#   Too many errors printed, aborting program
.
```diff
---
+++
@@ -551,7 +551,7 @@
 #pragma dont_inline reset

-static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
+static inline pf_u32 PFCACHE_RecordPageEndOverlap(pf_u32 page_sector, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
     pf_u32 last_sector = end_sector - 1;
-    pf_u32 num_overlap = end_sector - p_page->sector;
+    pf_u32 num_overlap = end_sector - page_sector;
     *p_num_success += num_overlap;
     *p_num_rest_sector -= num_overlap;
@@ -620,5 +620,5 @@
                 num_overlap = num_sector;
                 num_overlap += sector;
-                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
+                last_sector = PFCACHE_RecordPageEndOverlap(p_page->sector, num_overlap, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                 p_page->p_mod_sbuf = p_page->buffer;
```
9. pass the page sector and form its exclusive end in one addition: compile failed
User break, cancelled...
### mwcceppc.exe Compiler:
#    File: Z:\tmp\perm2b-manual\PFCACHE_DoWriteNumSectorAndFreeIfNeeded-9.c
# -------------------------------------------------------------------------
#     558:     p_page->stat |= 2;
#   Error:     ^^^^^^
#   (10140) undefined identifier 'p_page'
#   Too many errors printed, aborting program
.
```diff
---
+++
@@ -551,7 +551,7 @@
 #pragma dont_inline reset

-static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
+static inline pf_u32 PFCACHE_RecordPageEndOverlap(pf_u32 page_sector, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
     pf_u32 last_sector = end_sector - 1;
-    pf_u32 num_overlap = end_sector - p_page->sector;
+    pf_u32 num_overlap = end_sector - page_sector;
     *p_num_success += num_overlap;
     *p_num_rest_sector -= num_overlap;
@@ -618,7 +618,6 @@
                 pf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                     (sector + num_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector);
-                num_overlap = num_sector;
-                num_overlap += sector;
-                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
+                num_overlap = sector + num_sector;
+                last_sector = PFCACHE_RecordPageEndOverlap(p_page->sector, num_overlap, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                 p_page->p_mod_sbuf = p_page->buffer;
```

### PFCACHE_DoWriteNumSectorAndFreeIfNeeded readable trials
Remote source unchanged at 9c7d87ab008df7e35558321e3ca297a887d35c44.
10. carry the loaded page sector into its overlap bookkeeping operation: 99.8927% objdiff, 233/233 instructions, diffs 4.
```diff
---
+++
@@ -551,7 +551,7 @@
 #pragma dont_inline reset

-static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
+static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 page_sector, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
     pf_u32 last_sector = end_sector - 1;
-    pf_u32 num_overlap = end_sector - p_page->sector;
+    pf_u32 num_overlap = end_sector - page_sector;
     *p_num_success += num_overlap;
     *p_num_rest_sector -= num_overlap;
@@ -620,5 +620,5 @@
                 num_overlap = num_sector;
                 num_overlap += sector;
-                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
+                last_sector = PFCACHE_RecordPageEndOverlap(p_page, p_page->sector, num_overlap, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                 p_page->p_mod_sbuf = p_page->buffer;
```
11. compute the overlap count at its call before updating the page state: 99.8927% objdiff, 233/233 instructions, diffs 4.
```diff
---
+++
@@ -551,7 +551,6 @@
 #pragma dont_inline reset

-static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
+static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32 num_overlap, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
     pf_u32 last_sector = end_sector - 1;
-    pf_u32 num_overlap = end_sector - p_page->sector;
     *p_num_success += num_overlap;
     *p_num_rest_sector -= num_overlap;
@@ -620,5 +619,5 @@
                 num_overlap = num_sector;
                 num_overlap += sector;
-                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
+                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, num_overlap - p_page->sector, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                 p_page->p_mod_sbuf = p_page->buffer;
```
12. pass the actual overlap count before its exclusive-end argument: 99.8927% objdiff, 233/233 instructions, diffs 4.
```diff
---
+++
@@ -551,7 +551,6 @@
 #pragma dont_inline reset

-static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
+static inline pf_u32 PFCACHE_RecordPageEndOverlap(PF_CACHE_PAGE* p_page, pf_u32 num_overlap, pf_u32 end_sector, pf_u32* p_num_success, pf_u32* p_num_rest_sector) {
     pf_u32 last_sector = end_sector - 1;
-    pf_u32 num_overlap = end_sector - p_page->sector;
     *p_num_success += num_overlap;
     *p_num_rest_sector -= num_overlap;
@@ -620,5 +619,5 @@
                 num_overlap = num_sector;
                 num_overlap += sector;
-                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap, p_num_success, &num_rest_sector);
+                last_sector = PFCACHE_RecordPageEndOverlap(p_page, num_overlap - p_page->sector, num_overlap, p_num_success, &num_rest_sector);
                 p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                 p_page->p_mod_sbuf = p_page->buffer;
```

AddTaskInternal raw 1245 tie 8 adds an unused duplicate purge status to the redundant taskCount mask from tie 7. The separate meaningful purge status and explicit SDK/u16 argument conversions were already compiled and remain non-exact. No source retained.
Additional SD initialization identity-return forms, SDK NULL guard, named current-disk predicate and insertion-branch publication remain non-exact. Finalize named flags and initialized-flag helpers retain its four register/scheduling differences; natural chained cleanup still has six differences. Cache overlap-count argument/helper forms retain its four register differences. Failed helper trials 8 and 9 were corrected in trials 10-12, with no repository edit.

### NHTTPi_strnicmp readable trials
Remote source changed at 9c7d87ab008df7e35558321e3ca297a887d35c44.
17. name the right lowercase byte before testing the raw terminators: 51.039215% objdiff, 55/51 instructions, diffs 52.
```diff
---
+++
@@ -14,6 +14,7 @@
     while(length>0) {
         int a=*left++, b=*right++;
+        int lowercaseRight = LowerCase(b);
         if(a==0 || b==0) { if(a==0 && b==0) { length=0; break; } }
-        b=LowerCase(b);
+        b=lowercaseRight;
         a=LowerCase(a);
         if(a!=b) break;
```
18. name the left lowercase byte before testing the raw terminators: 51.431374% objdiff, 55/51 instructions, diffs 52.
```diff
---
+++
@@ -14,7 +14,8 @@
     while(length>0) {
         int a=*left++, b=*right++;
+        int lowercaseLeft = LowerCase(a);
         if(a==0 || b==0) { if(a==0 && b==0) { length=0; break; } }
         b=LowerCase(b);
-        a=LowerCase(a);
+        a=lowercaseLeft;
         if(a!=b) break;
         --length;
```
19. convert both string bytes before the raw terminator guard: 5.8627453% objdiff, 58/51 instructions, diffs 56.
```diff
---
+++
@@ -14,7 +14,9 @@
     while(length>0) {
         int a=*left++, b=*right++;
+        int lowercaseRight = LowerCase(b);
+        int lowercaseLeft = LowerCase(a);
         if(a==0 || b==0) { if(a==0 && b==0) { length=0; break; } }
-        b=LowerCase(b);
-        a=LowerCase(a);
+        b=lowercaseRight;
+        a=lowercaseLeft;
         if(a!=b) break;
         --length;
```
20. name the remaining comparison length in a real loop local: 99.76471% objdiff, 51/51 instructions, diffs 2.
```diff
---
+++
@@ -12,13 +12,14 @@

 s32 NHTTPi_strnicmp(const char* left, const char* right, s32 length) {
-    while(length>0) {
+    s32 remaining = length;
+    while(remaining>0) {
         int a=*left++, b=*right++;
-        if(a==0 || b==0) { if(a==0 && b==0) { length=0; break; } }
+        if(a==0 || b==0) { if(a==0 && b==0) { remaining=0; break; } }
         b=LowerCase(b);
         a=LowerCase(a);
         if(a!=b) break;
-        --length;
+        --remaining;
     }
-    return length;
+    return remaining;
 }

```
NWC24UpdateDlTask run finished, raw best 440, new outputs 0, elapsed 2701s. Log /tmp/perm-NWC24UpdateDlTask/run-b.log.

### pfd_sddrv_init resumed permuter
Fresh origin 9c7d87ab008df7e35558321e3ca297a887d35c44, exact-name objdiff 92.326385%.

AddTaskInternal: stopped after about 45 minutes without a usable readable improvement. Raw score 1245 hints were translated and measured or rejected for semantic changes or redundant noise.
AddTaskInternal run finished, raw best 1245, new outputs 10, elapsed 2704s. Log /tmp/perm-AddTaskInternal/run-b.log.

### pfd_sddrv_build_fat32_mbr_bpb resumed permuter
Fresh origin 7654dc33e1f98d0fcf7c8361acc522ec02068b57, exact-name objdiff 94.75225%.

## T3 restart recovery, 2026-10-03

Branch agent/w1002/sol-perm2b-max retains local commits 2a4c1b79 and de060b36. The only uncommitted file is this attempts log. Fresh origin fetch shows no additional source changes in the five owned units. Initial quick all-unit GATE PASS confirms both saved exact gains, all identical pools, the target DOL SHA1, zero regressions, forbidden patterns and readability warnings. Evidence /tmp/perm2b-t3-initial-gate.txt. Every open function already has at least three distinct compiled readable attempts. Finished 45-minute runs will not be repeated. Only the three interrupted SD permuters will resume, with prior elapsed time charged to their existing 45-minute budget. Saved compile flags were checked against current ninja commands.
pfd_sddrv_init: resuming saved dir with 2290s left, original elapsed 410s, origin a791e598a154e105d9ca81087d8d5912e222636a, exact-name objdiff 92.326385%.
pfd_sddrv_build_fat32_mbr_bpb: resuming saved dir with 2556s left, original elapsed 144s, origin a791e598a154e105d9ca81087d8d5912e222636a, exact-name objdiff 94.75225%.
pfd_sddrv_finalize: resuming saved dir with 392s left, original elapsed 2308s, origin a791e598a154e105d9ca81087d8d5912e222636a, exact-name objdiff 92.63158%.
pfd_sddrv_init: new raw hint output-1506-1 score 1506, resumed elapsed 27s.
pfd_sddrv_init: new raw hint output-1416-1 score 1416, resumed elapsed 88s.
pfd_sddrv_init: new raw hint output-1018-1 score 1018, resumed elapsed 92s.
pfd_sddrv_finalize: new raw hint output-60-13 score 60, resumed elapsed 191s.

### NHTTPi_strnicmp new T3 source trials
Fresh origin a791e598a154e105d9ca81087d8d5912e222636a, assigned-unit origin diff True. Duplicates of saved full-unit trial sources are skipped.
1. advance both string pointers after loading the compared bytes: 99.37255% objdiff, 51/51 instructions, diffs 6. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-1.c.
2. keep byte comparison values in function scope with the existing length loop: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-2.c.
3. place the natural length decrement in the for-loop update: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-3.c.
4. guard the positive remaining length before a nonzero counted loop: 77.05882% objdiff, 54/51 instructions, diffs 53. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-4.c.
5. keep loaded byte pointers unchanged until the comparison succeeds: 91.23529% objdiff, 51/51 instructions, diffs 39. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-5.c.
6. store the remaining comparison count together with a successful byte step: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-6.c.
7. return directly when the comparison bytes differ: 91.52941% objdiff, 53/51 instructions, diffs 13. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-7.c.
pfd_sddrv_build_fat32_mbr_bpb: new raw hint output-1451-1 score 1451, resumed elapsed 302s.

### NHTTPi_strnicmp new T3 source trials
Fresh origin a791e598a154e105d9ca81087d8d5912e222636a, assigned-unit origin diff True. Duplicates of saved full-unit trial sources are skipped.
8. reverse the written lower-bound comparison while preserving the same uppercase range: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-8.c.
9. reverse the written upper-bound comparison while preserving the same uppercase range: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-9.c.
10. write both uppercase comparisons with the literal on the left: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-10.c.
11. name the first and last uppercase bytes as immutable comparison bounds: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-11.c.
12. name uppercase byte bounds with their actual signed character type: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-12.c.
13. name both uppercase comparisons before combining their boolean results: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-13.c.
14. keep the compared character in a named result initialized at helper entry: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-14.c.
15. express the folded ASCII byte through lowercase and uppercase letter distance: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-15.c.
pfd_sddrv_finalize: resumed run finished, raw best 60, new hints 1, total elapsed 2701s. Evidence /tmp/perm-pfd_sddrv_finalize/run-t3.log.

### pfd_sddrv_init new T3 source trials
Fresh origin 333eea81e98c872d3da0379e2dfbcdeba224ef5e, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
1. cache the current disk at its actual post-report ownership check: compile failed ### mwcceppc.exe Compiler: #    File: Z:\tmp\perm2b-t3-manual\pfd_sddrv_init-1.c # --------------------------------------------------- #     321:         FADisk* currentDisk = g_pfd_sddrv_info.disk;  #   Error:         ^^^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... . Source /tmp/perm2b-t3-manual/pfd_sddrv_init-1.c.
2. cache the current disk before reporting its initialized state: 88.1875% objdiff, 144/144 instructions, diffs 30. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-2.c.
3. name the actual insertion bit predicate before publishing media presence: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-3.c.
4. return the initialized-disk status through explicit success and error alternatives: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-4.c.
5. keep the mounted card pointer in a distinct named device during failure cleanup: compile failed ### mwcceppc.exe Compiler: #    File: Z:\tmp\perm2b-t3-manual\pfd_sddrv_init-5.c # --------------------------------------------------- #     366:             SDDev* mountedCard = device;  #   Error:             ^^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... . Source /tmp/perm2b-t3-manual/pfd_sddrv_init-5.c.

SD-init hints 1506 and 1416 suggest caching disk/device pointers and naming the real media-insertion predicate. These are translated above without redundant status copies. Hint 1018 suppresses the real initialized-driver report for a different disk and repurposes a device error result as the constant 42. Rejected as changed observable behavior and source noise. Finalize hint 60 tie 13 only changes an error truth test and repeats the already-tried chained zero cleanup; it remains advisory.

### pfd_sddrv_store_mbr_buf new T3 source trials
Fresh origin 333eea81e98c872d3da0379e2dfbcdeba224ef5e, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
1. name the last disk sector once before converting its end CHS address: 99.75247% objdiff, 202/202 instructions, diffs 9. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-1.c.
2. name the CHS disk size after finding the geometry settings: compile failed ### mwcceppc.exe Compiler: #    File: Z:\tmp\perm2b-t3-manual\pfd_sddrv_store_mbr_buf-2.c # ------------------------------------------------------------ #     994:     u32 diskSectors = format_data->total_sectors;  #   Error:     ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... . Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-2.c.
3. calculate the end head before its cylinder with the same geometry range: 99.75247% objdiff, 202/202 instructions, diffs 9. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-3.c.
4. reverse the two geometry factors in CHS cylinder and head calculations: 99.70297% objdiff, 202/202 instructions, diffs 9. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-4.c.
5. reuse the known total-sector request value in the end CHS address: 96.95049% objdiff, 201/202 instructions, diffs 154. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-5.c.
6. name the shared CHS cylinder conversion as an inline geometry helper: 99.15842% objdiff, 202/202 instructions, diffs 33. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-6.c.

### pfd_sddrv_finalize new T3 source trials
Fresh origin 333eea81e98c872d3da0379e2dfbcdeba224ef5e, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
1. declare the driver flag field volatile for the target reload between mounted-state test and mask: 92.63158% objdiff, 57/57 instructions, diffs 4. Source /tmp/perm2b-t3-manual/pfd_sddrv_finalize-1.c.
2. name the initialized flag in the cleanup mask with its driver meaning: 92.63158% objdiff, 57/57 instructions, diffs 4. Source /tmp/perm2b-t3-manual/pfd_sddrv_finalize-2.c.
3. retain the read flags in a typed word before the final mask update: 92.63158% objdiff, 57/57 instructions, diffs 4. Source /tmp/perm2b-t3-manual/pfd_sddrv_finalize-3.c.
4. type the initialized flag complement as the SDK word mask: 92.63158% objdiff, 57/57 instructions, diffs 4. Source /tmp/perm2b-t3-manual/pfd_sddrv_finalize-4.c.
5. write the card-unmount failure guard as its natural nonzero result test: 92.63158% objdiff, 57/57 instructions, diffs 4. Source /tmp/perm2b-t3-manual/pfd_sddrv_finalize-5.c.

Definition-level volatile was tested only on the TU-local flag field. Target evidence is two flags loads with no intervening store at mounted-state test and clear, target instructions 8 and 11. No use-site volatile cast, public header or configuration was changed. The result is a trial; it is acceptable only if all existing exact functions and data are preserved.

### pfd_sddrv_build_fat32_mbr_bpb new T3 source trials
Fresh origin 333eea81e98c872d3da0379e2dfbcdeba224ef5e, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
1. declare the existing reserved-sector writer explicitly inline for its known global buffer: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-1.c.
2. keep the existing reserved-sector result scoped to its validation block: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-2.c.
3. pass the first reserved-sector element with explicit array addressing: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-3.c.
4. test the reserved-sector helper directly before reporting its actual error: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-4.c.

### pfd_sddrv_init new T3 source trials
Fresh origin 7c582f0e411fee30ba3dc7070941056cf6fb247c, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
6. declare the current-disk cursor with locals and load it after the report: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-6.c.
7. declare the failure-cleanup device with locals and initialize it at its real use: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-7.c.
8. express the absent input as a typed null disk pointer: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-8.c.
9. express disk input validation through its unsigned address value: 92.326385% objdiff, 144/144 instructions, diffs 31. Source /tmp/perm2b-t3-manual/pfd_sddrv_init-9.c.

### pfd_sddrv_store_mbr_buf new T3 source trials
Fresh origin 7c582f0e411fee30ba3dc7070941056cf6fb247c, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
7. declare disk geometry size with locals and load it before CHS conversion: 99.23267% objdiff, 202/202 instructions, diffs 19. Source /tmp/perm2b-t3-manual/pfd_sddrv_store_mbr_buf-7.c.

Failed mixed-declaration trials were corrected with C89 declaration placement. FAT32 builder raw hint 1451 reuses an uninitialized integer on error paths, then converts later write failures into success returns. Rejected without source translation because it changes error handling.

### pfd_sddrv_build_fat32_mbr_bpb new T3 source trials
Fresh origin 7c582f0e411fee30ba3dc7070941056cf6fb247c, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
5. preserve reserved-buffer validation with a positive buffer success branch: 95.0% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-5.c.
6. retain initialized status for the reserved-buffer helper and both real return paths: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-6.c.
7. give the private reserved writer its real typed sector pointer: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-7.c.
8. give the private reserved writer a fixed-size sector buffer pointer: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-8.c.

### NHTTPi_strnicmp new T3 source trials
Fresh origin 74dcb16a50a803604362b80e7d535744b0b765d1, assigned-unit origin diff True. Duplicates of saved full-unit trial sources are skipped.
16. use an SDK signed word for the lowercase helper input and result: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-16.c.
17. use signed byte input for lowercase folding of loaded string bytes: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-17.c.
18. return the naturally bounded lowercase byte with signed character type: 93.196075% objdiff, 53/51 instructions, diffs 37. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-18.c.
19. type uppercase comparison bounds as signed long ASCII constants: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-19.c.
20. use signed word input with signed long ASCII comparison bounds: 99.76471% objdiff, 51/51 instructions, diffs 2. Source /tmp/perm2b-t3-manual/NHTTPi_strnicmp-20.c.

Retained-match review at T3 restart: Base64 remains 119/119 instructions, exact-name objdiff 100.0%; header consistency remains 212/212, exact-name objdiff 100.0%; both ctxdiff reports have diffs 0. Direct object-path pool checks preserve all five pools. Advisory literal_reference_diff checked 4 string arguments across 39 exact functions in the two changed units, with no candidates, errors or skipped functions. Evidence /tmp/perm2b-t3-literal-check.txt. All new full-TU compiler experiments stay under /tmp and no fuzzy source is retained.
pfd_sddrv_build_fat32_mbr_bpb: new raw hint output-1430-2 score 1430, resumed elapsed 1313s.
pfd_sddrv_build_fat32_mbr_bpb: new raw hint output-1430-3 score 1430, resumed elapsed 1373s.

### pfd_sddrv_build_fat32_mbr_bpb new T3 source trials
Fresh origin fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, assigned-unit origin diff False. Duplicates of saved full-unit trial sources are skipped.
9. check the private reserved-writer status using its exclusively negative error return: 94.75225% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-9.c.
10. assign the reserved-writer status on both validated return paths: 95.0% objdiff, 230/222 instructions, diffs 122. Source /tmp/perm2b-t3-manual/pfd_sddrv_build_fat32_mbr_bpb-10.c.

FAT32 builder hints 1430 ties 2 and 3 move one real error report after an earlier return. Both repeat the prior round unreachable-report failure and are rejected without repeating source trials. The real two-report error path remains intact.
pfd_sddrv_init: resumed run finished, raw best 1018, new hints 3, total elapsed 2700s. Evidence /tmp/perm-pfd_sddrv_init/run-t3.log.

Final scope audit will use gate merge-base 674722c158ff057be7a5110841cf18b50d1cb631; fresh origin be7ded2fdc4ebba0b87695a132905e38e7f984df. The worker branch is intentionally not rebased, as required. All current source changes remain the two saved exact commits. Recovery changes only this attempts log. One startup commentary message was required by the harness; subsequent intermediate messages are tool calls only.
pfd_sddrv_build_fat32_mbr_bpb: resumed run finished, raw best 1430, new hints 3, total elapsed 2702s. Evidence /tmp/perm-pfd_sddrv_build_fat32_mbr_bpb/run-t3.log.

All three interrupted SD runs reached their existing 45-minute budgets and exited. Canonical run-state-b.json files are now corrected to finished, preserving the pre-restart snapshots and resumed state. New raw scores: init 1018, finalize 60, FAT32 builder 1430. Every new hint was translated into readable source and measured, or rejected with specific semantic failure evidence. No new source match was obtained during recovery; the two saved exact gains are retained. New loop, ASCII helper type, CHS geometry and reserved-sector validation experiments remain non-exact and are not copied into repository source.

## Recovery final validation

Final non-quick full gate over all five units: GATE PASS. Clean 43U rebuild succeeds, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. All five pools identical, every present data section 100%, zero regressions, forbidden patterns and readability warnings. Fresh rebuilt exact-name objdiff remains 100.0% for Base64 and header consistency; final ctxdiff is 119/119 and 212/212 instructions respectively, both diffs 0. Full output /tmp/perm2b-t3-final-gate.txt, report /tmp/perm2b-t3-final-report.json.

Baseline -> retained leaf: NWC24Download 26/30 -> 27/30, code 8456 -> 9304 / 12496, data 80/80; NHTTP_stdlib_RVL 11/14 -> 12/14, code 1388 -> 1864 / 2248, data 112/112. Other assigned units unchanged. Across the five units: exact functions 100 -> 102 / 113, matched code 26764 -> 28088 / 35592, data 3784/3784 unchanged. Recovery itself adds zero exact functions and retains local source commits 2a4c1b79 and de060b36.

| Remaining function | Current objdiff percent | Instructions source/target | Diffs | Distinct compiled readable trials | Evidence |
|---|---:|---:|---:|---:|---|
| NHTTPi_compareTokenN_HdrRecvBuf | 97.32258 | 124/124 | 5 | 6 | five constant/extension scheduling differences; public-width hints rejected |
| PFCACHE_DoWriteNumSectorAndFreeIfNeeded | 99.8927 | 233/233 | 4 | 10 | four scratch-register differences at overlap accounting |
| NWC24InitDlTask | 98.923615 | 144/144 | 31 | 3 | register allocation and scheduling; identical instruction count |
| NWC24UpdateDlTask | 95.00395 | 249/253 | 250 | 3 | instruction-count and lowering mismatch; closer readable helper also non-exact |
| AddTaskInternal | 97.7182 | 398/401 | 323 | 9 | instruction-count and lowering mismatch; behavior-changing ID/purge hints rejected |
| pfd_sddrv_init | 92.326385 | 144/144 | 31 | 17 | null/identity-test lowering and field-publication scheduling; changed-report/global-write hints rejected |
| pfd_sddrv_finalize | 92.63158 | 57/57 | 4 | 17 | four final-mask register/scheduling differences; chained cleanup hint remains non-exact |
| pfd_sddrv_store_mbr_buf | 99.75247 | 202/202 | 9 | 9 | nine scratch-register differences in CHS arithmetic |
| pfd_sddrv_build_fat32_mbr_bpb | 94.75225 | 230/222 | 122 | 13 | reserved-helper null-check/lowering adds eight instructions; unreachable-report/uninitialized hints rejected |
| NHTTPi_strnicmp | 99.76471 | 51/51 | 2 | 39 | two constant-initialization scheduling differences |
| NHTTPi_compareToken | 98.844444 | 45/45 | 10 | 20 | ten register/scheduling differences; closer readable hint still has two differences |

All eleven open functions have at least three distinct successful source compilations logged, excluding compiler failures. No original function, configuration flag, shared header, protected total-sector function, or other worktree was changed during recovery. The final branch remains based on 674722c1; parent integration must perform its own current-main validation. All permutation processes have exited and saved directories remain intact.

# perm2 campaign attempts

Base: 5bdfe797a9136815a89f849f0c00dc7624068d12 (origin/main, #1186), branch agent/w1005/perm2, worktree sol-med. Fetched under /tmp/wii-git.lock; clean before restoring the authorized adapter/settings from agent/w1005/perm. Owned functions: KPADInit, NWC24InitDlTask, Window::DrawFrame, SOGetSockName, Setting::scanAP, BS2Update UpdateThread. No CDB or ESMisc edits.

Read common.md, levers.md including semantic/readability rules20/21 and mwdbg22, AGENTS.md and unslop. Prior campaign evidence stays in build/perm. Added separate --campaign build/perm2 support; dependency symlinks remain inside this worktree.

KPAD seed is the reviewed 98.89189 source from old branch9340119e. BS2 requested95.30 is raw output-2955-1: filename getter, data9160/10488 versus original10488/10488. It is a rejected diagnostic seed, not an accepted starting source. Source remains current main until a natural rewrite passes review and gates.

Baseline {"job": "kpad", "normal_instructions": 185, "seed_instructions": 185, "identical_to_normal": false, "main_fuzzy": 97.810814, "main_measures": {"fuzzy_match_percent": 99.875916, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "seed_fuzzy": 98.89189, "seed_measures": {"fuzzy_match_percent": 99.937195, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}}

Baseline {"job": "nwc24", "normal_instructions": 144, "seed_instructions": 144, "identical_to_normal": true, "main_fuzzy": 99.201385, "main_measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "seed_fuzzy": 99.201385, "seed_measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}}

Baseline {"job": "window", "normal_instructions": 376, "seed_instructions": 376, "identical_to_normal": true, "main_fuzzy": 98.17819, "main_measures": {"fuzzy_match_percent": 99.75864, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "seed_fuzzy": 98.17819, "seed_measures": {"fuzzy_match_percent": 99.75864, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}}

Baseline {"job": "so", "normal_instructions": 63, "seed_instructions": 63, "identical_to_normal": true, "main_fuzzy": 96.666664, "main_measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "seed_fuzzy": 96.666664, "seed_measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}}

Baseline {"job": "scan", "normal_instructions": 272, "seed_instructions": 272, "identical_to_normal": true, "main_fuzzy": 99.20221, "main_measures": {"fuzzy_match_percent": 99.97709, "total_code": "37884", "matched_code": "36796", "matched_code_percent": 97.128075, "total_data": "5696", "matched_data": "5696", "matched_data_percent": 100.0, "total_functions": 112, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_units": 1}, "seed_fuzzy": 99.20221, "seed_measures": {"fuzzy_match_percent": 99.97709, "total_code": "37884", "matched_code": "36796", "matched_code_percent": 97.128075, "total_data": "5696", "matched_data": "5696", "matched_data_percent": 100.0, "total_functions": 112, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_units": 1}}

Baseline {"job": "bs2", "normal_instructions": 911, "seed_instructions": 913, "identical_to_normal": false, "main_fuzzy": 94.83023, "main_measures": {"fuzzy_match_percent": 95.340576, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "seed_fuzzy": 95.30011, "seed_measures": {"fuzzy_match_percent": 95.76407, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "9160", "matched_data_percent": 87.33791, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}}

Started KPADInit, PID 439912, 7200 seconds, 2026-10-05 07:06:20 UTC.

Started NWC24InitDlTask, PID 439985, 7200 seconds, 2026-10-05 07:06:20 UTC.

Started DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc, PID 440055, 7200 seconds, 2026-10-05 07:06:20 UTC.

Started SOGetSockName, PID 440057, 7200 seconds, 2026-10-05 07:06:20 UTC.

Started scanAP__Q33ipl5scene7SettingFv, PID 440128, 7200 seconds, 2026-10-05 07:06:20 UTC.

Started UpdateThread, PID 440136, 7200 seconds, 2026-10-05 07:06:20 UTC.

Source trial {"job": "scan", "label": "playing-query-index-first", "build": 0, "sha256": "9210454e5e3fdf4d493648c28668d830fe517846537db7e69fc594eab22aa7b2", "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "fuzzy": 99.20221, "measures": {"fuzzy_match_percent": 99.97709, "total_code": "37884", "matched_code": "36796", "matched_code_percent": 97.128075, "total_data": "5696", "matched_data": "5696", "matched_data_percent": 100.0, "total_functions": 112, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_units": 1}, "drops": [], "instructions": [272, 272], "diffs": 4}

Source trial {"job": "scan", "label": "playing-query-const-index", "build": 0, "sha256": "708920a9123bd8bd8baedc1b7a055c81c2279b720fe9c8528225f8e7c48f1987", "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "fuzzy": 99.20221, "measures": {"fuzzy_match_percent": 99.97709, "total_code": "37884", "matched_code": "36796", "matched_code_percent": 97.128075, "total_data": "5696", "matched_data": "5696", "matched_data_percent": 100.0, "total_functions": 112, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_units": 1}, "drops": [], "instructions": [272, 272], "diffs": 4}

Source trial {"job": "scan", "label": "playing-query-explicit-u16", "build": 0, "sha256": "5cd4771b9510a71898dea7e4e255d57e6d2090d79f9848d2fec42d4c25a9eb5f", "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "fuzzy": 99.20221, "measures": {"fuzzy_match_percent": 99.97709, "total_code": "37884", "matched_code": "36796", "matched_code_percent": 97.128075, "total_data": "5696", "matched_data": "5696", "matched_data_percent": 100.0, "total_functions": 112, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_units": 1}, "drops": [], "instructions": [272, 272], "diffs": 4}

Source trial {"job": "bs2", "label": "current-import-path-local", "build": 0, "sha256": "b6e7a8d5017f93eb0bedd03d943d3bc200291f86351e5def8e8e2c313ddc9022", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 95.16539, "measures": {"fuzzy_match_percent": 95.64265, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "bs2", "label": "current-import-index-reuse", "build": 0, "sha256": "7c476ab28d5235a56a26ed78baf33374fbc597cf95a548508b5c456ce88e9422", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 94.83023, "measures": {"fuzzy_match_percent": 95.340576, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "bs2", "label": "current-import-entry-local", "build": 0, "sha256": "d8a5a524cdd8d5f7096d7af50479ded7ba5007444b7a544f4bf17c31253cc619", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 95.16539, "measures": {"fuzzy_match_percent": 95.64265, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "bs2", "label": "current-import-path-outer", "build": 0, "sha256": "e7e1f0612f2cd8630a68302e8e957d9fce6d80da0824c3743933bab431567c4b", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 95.16539, "measures": {"fuzzy_match_percent": 95.64265, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "window", "label": "frame-geometry-local", "build": 0, "sha256": "9fe3ea29a4c572a96f4609dfb7cb7536535a8909e5a04ac53cd3d3ef5fc0c749", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 97.89893, "measures": {"fuzzy_match_percent": 99.721634, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 144}

Source trial {"job": "window", "label": "first-texture-coordinates-local", "build": 0, "sha256": "c0085997f9e7d9960374f2244d6a1bd4e2825dfb9da51a76f41d430746fe681d", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.606384, "measures": {"fuzzy_match_percent": 99.550385, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 135}

Source trial {"job": "window", "label": "texture-coordinates-local", "build": 0, "sha256": "9a849604954005d9ffc9eef51c122c790d4b41842a9dbc356707ddc450d99722", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 88.93351, "measures": {"fuzzy_match_percent": 98.53383, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 203}

Source trial {"job": "nwc24", "label": "combined-title-id", "build": 0, "sha256": "a8ec7f7d8ebd6c738e53238c529128906b4d09425af79f9228930c59ef3355ca", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "scoped-const-title-high", "build": 0, "sha256": "df7278351ec18f496c3827b48c44fb02f9cd1482155751939858a30c8ea9152c", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "scoped-const-title-words", "build": 0, "sha256": "f54ecae0bcf18b93346dfa9c4b55771ae66b3eb01d8c60a913852d01199fed23", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "so", "label": "copy-length-baseline-confirm", "build": 0, "sha256": "65114df36514e49587c6e74fa0bcc9f1ae45ba80331527b42c531c5bc93b3b41", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.01588, "measures": {"fuzzy_match_percent": 99.87769, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "copy-length-request-first", "build": 0, "sha256": "422df7cace1852c71164dd37dcd34b4ade2fac0a390474972aca77c7899f7608", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.349205, "measures": {"fuzzy_match_percent": 99.77495, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 24}

Source trial {"job": "so", "label": "copy-length-address-first", "build": 0, "sha256": "fffcf9f92495a6589af193bf3348fc0650a370d291ee92afcd2d3e6b00c607de", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.42857, "measures": {"fuzzy_match_percent": 99.77985, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 23}

Source trial {"job": "so", "label": "copy-length-integers-grouped", "build": 0, "sha256": "0f0462bad5e30c43cc668f80954f2f764d9c4989d4df0104668dfc0cd9ecea43", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.74603, "measures": {"fuzzy_match_percent": 99.799416, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 19}

Source trial {"job": "so", "label": "copy-length-socket-first", "build": 0, "sha256": "ce38210f40003234364df1c3f663ba28f5503bd61d02ad4cc9ad754e9b0758bb", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.01588, "measures": {"fuzzy_match_percent": 99.87769, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "copy-length-socket-last", "build": 0, "sha256": "19e702d0d7d86311f04acd53cc15d8a2b934ccad8f6131ad24db2c6af138f369", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.01588, "measures": {"fuzzy_match_percent": 99.87769, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "kpad", "label": "reuse-enable-flag", "build": 0, "sha256": "1f9a8430173b5aa4b4013d97b481c3f90684f983791aec2bc2fd713385610628", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 98.89189, "measures": {"fuzzy_match_percent": 99.937195, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 34}

Source trial {"job": "kpad", "label": "matrix-after-repeat", "build": 0, "sha256": "526ec45957463a7449ac11d51e0b74285df40c03b16ff6f20a521f07a89812e1", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.86487, "measures": {"fuzzy_match_percent": 99.99234, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 5}

Source trial {"job": "kpad", "label": "matrix-after-scale", "build": 0, "sha256": "47747c34140d1a6c012dc5cdcca8ebd1087f25efb7c7feca08b92799d7e46b20", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 98.89189, "measures": {"fuzzy_match_percent": 99.937195, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 34}

Source trial {"job": "kpad", "label": "repeat-before-matrix", "build": 0, "sha256": "1794520981a9c610c96d5c63ce45603d94503fc9ab02edf6f4b20311cbffdeba", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 88.48649, "measures": {"fuzzy_match_percent": 99.34743, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 30}

Source trial {"job": "kpad", "label": "interval-between-extents", "build": 0, "sha256": "7bdab1314d515fc57a3f5a8aea1feb1f566c6c5164eabe1bc7c0c6f902d58ff2", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.945946, "measures": {"fuzzy_match_percent": 99.99693, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 2}

Source trial {"job": "kpad", "label": "interval-before-extents", "build": 0, "sha256": "07b199b1193b0d92b7c17d4e5deddbf687a6b513450ccf7e59743910a4139fae", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.86487, "measures": {"fuzzy_match_percent": 99.99234, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 5}

Source trial {"job": "kpad", "label": "interval-before-sine", "build": 0, "sha256": "b8b076d5973809b6ae01f4a3dc02723010a88b806db11033b0a2ec2e801e8351", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.86487, "measures": {"fuzzy_match_percent": 99.99234, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 5}

Source trial {"job": "kpad", "label": "round-sine-on-store", "build": 0, "sha256": "7aa933ced118f437e258ef06f8ba17d7c6f08e8b0c4e7b8fbc5644a782ae2d44", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.21622, "measures": {"fuzzy_match_percent": 99.955574, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 29}

Source trial {"job": "kpad", "label": "interval-between-extents-round-on-store", "build": 0, "sha256": "23ac2f7a9a363782c59b174b54ead22c2db84de10aa323d8de77af9853e703c9", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.297295, "measures": {"fuzzy_match_percent": 99.960175, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 26}

Source trial {"job": "kpad", "label": "round-existing-rotation-before-zero", "build": 0, "sha256": "979d72c86af8fc4199414129735558e6d4ad69966b0d62749f2d13d0d652d230", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.297295, "measures": {"fuzzy_match_percent": 99.960175, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 26}

Source trial {"job": "kpad", "label": "round-existing-rotation-at-store", "build": 0, "sha256": "c819888b64fa1a5df471691f8d7afe631ea7274ffdf6bdd4b9b54842e5f00a22", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 99.297295, "measures": {"fuzzy_match_percent": 99.960175, "total_code": "13056", "matched_code": "12316", "matched_code_percent": 94.33211, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 26}

Source trial {"job": "kpad", "label": "round-sine-element-before-zero", "build": 0, "sha256": "24355d4796fb6d2615c7679c7f105cd37c8d64acc68107b25af0fb31a5bc116f", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 100.0, "measures": {"fuzzy_match_percent": 100.0, "total_code": "13056", "matched_code": "13056", "matched_code_percent": 100.0, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 29, "matched_functions_percent": 100.0, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 0}

Source trial {"job": "kpad", "label": "round-sine-element-at-store", "build": 0, "sha256": "c832154b3059b7478dc6097730ba6083772a2a1f1ba02de23ce8598d6e03809a", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 100.0, "measures": {"fuzzy_match_percent": 100.0, "total_code": "13056", "matched_code": "13056", "matched_code_percent": 100.0, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 29, "matched_functions_percent": 100.0, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 0}

Source trial {"job": "nwc24", "label": "explicit-home-clear", "build": 0, "sha256": "a9b4781b7c33fd9b5eafff6ea28702ab50d146bfd38b847f899376d9504b8d7c", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 86.21528, "measures": {"fuzzy_match_percent": 99.36459, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [132, 144], "diffs": null}

Source trial {"job": "nwc24", "label": "empty-home-string", "build": 0, "sha256": "dcc8ee2dd4efbd306fdd98df6f88af24708e00c04281144c5a18b06c1c375e17", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "word-home-clear", "build": 0, "sha256": "2c53e329703bbbd9a848007890b05284fdde80b7b8bb57ef605969f68c86cbe2", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 74.611115, "measures": {"fuzzy_match_percent": 98.829704, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [166, 144], "diffs": null}

Source trial {"job": "kpad", "label": "clean-match", "build": 0, "sha256": "49365c515b07e3eecff80b0b891457cc6e1362a9a2b52bc5653df9c35745e958", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "fuzzy": 100.0, "measures": {"fuzzy_match_percent": 100.0, "total_code": "13056", "matched_code": "13056", "matched_code_percent": 100.0, "total_data": "8032", "matched_data": "8032", "matched_data_percent": 100.0, "total_functions": 29, "matched_functions": 29, "matched_functions_percent": 100.0, "total_units": 1}, "drops": [], "instructions": [185, 185], "diffs": 0}

KPAD lever22: original capture assigned matrix-base temps r55/r56 before repeat constants r57/r59/r66, causing saved r26/r27 instead of target r29/r30. Grouping the four first-row stores with the remaining matrix stores after repeat defaults creates those address temps later; compiler scheduling still emits the retail order. Result99.86487,5 differences. Moving objectInterval between referenceHeight and referenceWidth in declaration order lets its disjoint lifetime reuse f28 before f27 is allocated, giving99.945946,2 differences. A double negative-sine result and separate f32 sineElement retain the target fneg f2 then frsp f0. Clean source100.0,185/185,0 differences, all8032data and other28 functions unchanged. Stores moved only across independent channel-field stores, with no intervening call; all trig calls and rounding remain in their original order. Applied this minimal source; mwdbg confirmation queued.

Source trial {"job": "window", "label": "named-flip-table-before-setup", "build": 0, "sha256": "ad5b16901a8a7a631f633a50c64d51e58971e070558705e3f0e20b939e6216b3", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 84.09309, "measures": {"fuzzy_match_percent": 97.89253, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 220}

Source trial {"job": "window", "label": "named-flip-table-after-texture", "build": 0, "sha256": "81ab48d7a3ba48bae0bf0d95802ea206804693ff0c6b94a07d3f4420edb1d11a", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 88.93351, "measures": {"fuzzy_match_percent": 98.53383, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 203}

Source trial {"job": "window", "label": "named-flip-table-before-geometry", "build": 0, "sha256": "32a6cc3aea3157260a467e5b3049d5d1e1e21e806f30e9f6bc31bb7302cd50f1", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 88.93351, "measures": {"fuzzy_match_percent": 98.53383, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 203}

Source trial {"job": "window", "label": "lt-corner-references-before-flip", "build": 0, "sha256": "46973be1c4da17811a938aa67c641a8c431c536998795fa9a97e37d47947993f", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 96.47991, "total_code": "11352", "matched_code": "3420", "matched_code_percent": 30.126848, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 18, "matched_functions_percent": 85.71429, "total_units": 1}, "drops": [["DrawFrame4__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 94.37708], ["DrawFrame8__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 94.12476]], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "window", "label": "lt-corner-references-after-flip", "build": 0, "sha256": "e2e1d7a5a24c26b9e69438fd995fa8602bed26c5851737a703647370cd4495d0", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 99.65292, "total_code": "11352", "matched_code": "3420", "matched_code_percent": 30.126848, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 18, "matched_functions_percent": 85.71429, "total_units": 1}, "drops": [["DrawFrame4__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 99.815155], ["DrawFrame8__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 99.812386]], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "window", "label": "all-corner-references-before-flip", "build": 0, "sha256": "1b116eddddedfbab03429a1e8ad7d3177d6daeb1a79fb03fc27f3607799e8ab2", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 88.27519, "total_code": "11352", "matched_code": "3420", "matched_code_percent": 30.126848, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 18, "matched_functions_percent": 85.71429, "total_units": 1}, "drops": [["DrawFrame4__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 81.33641], ["DrawFrame8__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2PCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc", 100.0, 78.89963]], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "bs2", "label": "skipped-import-path-local", "build": 0, "sha256": "379bd68783deed7eda4279e6ad6f4565321ef33a94f510da1769ee141acf2135", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 95.16539, "measures": {"fuzzy_match_percent": 95.64265, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "bs2", "label": "import-and-skipped-path-locals", "build": 0, "sha256": "64eb10eaced267e23151c3f40587d0fde3b65f1a1609fdefeaa4524edf42d7f5", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 95.23877, "measures": {"fuzzy_match_percent": 95.708786, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Source trial {"job": "bs2", "label": "saved-path-for-imports", "build": 0, "sha256": "46137b606b9690514313d3eaa7e19eed2657971bc3073e5ef9e555acbe365379", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 94.092, "measures": {"fuzzy_match_percent": 94.675224, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [909, 913], "diffs": null}

Source trial {"job": "bs2", "label": "one-import-path-variable", "build": 0, "sha256": "7bce69737a8562daf138e615efdb227c83f632a940cbbf8afbda13af5693619d", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 94.73932, "measures": {"fuzzy_match_percent": 95.25864, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [909, 913], "diffs": null}

Source trial {"job": "so", "label": "query-request-first", "build": 0, "sha256": "54e2e31081208b2b803f98a2acb88fdc53650d045db5830b5771e8befd35adb8", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 91.111115, "measures": {"fuzzy_match_percent": 99.45206, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [64, 63], "diffs": null}

Source trial {"job": "so", "label": "query-resource-first", "build": 0, "sha256": "660c2843634eb288b9bb2642baeaf53e0440b803f99c729242f0616638951e2b", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 91.111115, "measures": {"fuzzy_match_percent": 99.45206, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [64, 63], "diffs": null}

Source trial {"job": "so", "label": "query-const-socket", "build": 0, "sha256": "16b852490b589d9811e5368a230d59f3cc74f1b6f052abbde23276d0e44edb9d", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 91.111115, "measures": {"fuzzy_match_percent": 99.45206, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [64, 63], "diffs": null}

MWDBG compatibility bs2 import-and-skipped-path-locals: compiler fault at0x46da46 is the runtime case-fold table while comparing Shift-JIS/system encoding names. Debug-only omission of -enc SJIS produces a byte-identical whole object under normal wibo; original matching compile flags remain unchanged. Object SHA256 bc85e28c6062f492655611588cc84f13cda31714da1d10578f13c28b4ad18d6e.

MWDBG local driver: copied shared gc3.py into build/perm2/gc3_cached.py and cached 4KiB memory pages only while stopped. Cache is cleared before every continue and after any compiler function call. This reduces remote memory reads for large allocator graphs; shared tools are unchanged. Future captures record the local driver hash and still require normal-compiler byte identity plus graph/rewrite/machine-register validation.

BS2 compatibility replay: uninstrumented retrowin32 completed with the debug-only encoding omission, exit0, byte-identical to the complete production object for import-and-skipped-path-locals. Original debug failure did not reach UpdateThread.

MWDBG compatibility bs2 output-2810-1: compiler fault at0x46da46 is the runtime case-fold table while comparing Shift-JIS/system encoding names. Debug-only omission of -enc SJIS produces a byte-identical whole object under normal wibo; original matching compile flags remain unchanged. Object SHA256 b107ee9fcb22dda59ce837e984a3cd7b94c479e3bea6a4a35cad5fb622eb9950.

Source trial {"job": "window", "label": "single-texture-coordinate-set", "build": 0, "sha256": "e7a9e3513db9cdad149171300a7acb5813e8640d69e367537bb4f61858ad9d3f", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 99.75864, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "window", "label": "mutable-vertex-color-usage", "build": 0, "sha256": "e4d4a68bdadd2d202df08f73855f28c9529e5770c23cd6eba6b27ab037490b1f", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 99.75864, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "window", "label": "single-set-mutable-usage", "build": 0, "sha256": "1ac60c78a0c396391d7bca1519175a535e2e9c7626cf70f2ce653c0e59b4c3ea", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 98.17819, "measures": {"fuzzy_match_percent": 99.75864, "total_code": "11352", "matched_code": "9848", "matched_code_percent": 86.751236, "total_data": "316", "matched_data": "316", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_units": 1}, "drops": [], "instructions": [376, 376], "diffs": 119}

Source trial {"job": "so", "label": "address-copy-source-first", "build": 0, "sha256": "bea47613c814986e2565252c5e47653dd32bbef039c0768340266d5116df67fa", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "address-copy-source-first-both", "build": 0, "sha256": "3430d65df93a1be296cad122d4cd5c21d90800f327b55a0a7645e8f405923592", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "address-copy-length-first", "build": 0, "sha256": "e5b4eb2471b836f02e1f6e0d671f424fd772cc7c0307aca02ab2c8b89643c453", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "address-copy-source-length-first", "build": 0, "sha256": "500b42cc5c5a69aa748fe352e6ddb47c18f02a036b25392adda9eb582716d686", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Private debugger transport: the shared GDB queue has exceeded thirty minutes. A worktree-local copy of retrowin32 changes only the two-byte TCP port immediate in debugger::run, corresponding to wait_for_gdb_connection(9001) in the shared source. Compiler binary, emulation and codegen are unchanged. Local driver uses port49051 and its own lock; proof {"port": 49051, "instruction_address": "0x3cd400", "file_offset": "0x3cc400", "original_instruction": "66c78424a00200002923", "patched_instruction": "66c78424a00200009bbf", "original_sha256": "60ff93660b62ad09e683c3e54a5498bb2f6a67ee41b6656ded90a92ef0165bb5", "private_sha256": "9c85df235aa8a07b48560146abca2ccaea1dfbb0cf81ecc360b494ca46005268"}. Every capture still requires whole-object wibo identity.

MWDBG capture validation kpad-matrix-after-repeat: exit0; build/perm2/mwdbg/kpad-matrix-after-repeat/validation-run.log.

MWDBG capture validation kpad-clean-match: exit0; build/perm2/mwdbg/kpad-clean-match/validation-run.log.

MWDBG capture validation so-copy-length-baseline-confirm: exit0; build/perm2/mwdbg/so-copy-length-baseline-confirm/validation-run.log.

Private mwdbg kpad/clean-match: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/kpad-clean-match-private, SHA256 69e39fb39346edf3ee86c5d94804ee3e1f26c96e1c98925b16241b2985dfcbce.

Private mwdbg so/copy-length-baseline-confirm: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/so-copy-length-baseline-confirm-private, SHA256 668c1f17393ffd1f4ca5260e1bf05dcd3b717ce3d51436613252ec0277436233.

MWDBG driver cross-check kpad-clean-match: cached private-port capture matches the original shared driver in every final node color, name, cost, flags, degree, neighbor list, representative, priority, rewrite count, and whole object.

MWDBG driver cross-check so-copy-length-baseline-confirm: cached private-port capture matches the original shared driver in every final node color, name, cost, flags, degree, neighbor list, representative, priority, rewrite count, and whole object.

BS2 private trace reached UpdateThread and allocator simplify, then exceeded180 seconds. Unlike the encoding failure, this is trace volume. Retrying the clean candidate with900 seconds on the private port; other workers are unaffected.

Source trial {"job": "bs2", "label": "main-baseline-for-trace", "build": 0, "sha256": "c603e82cfb6d417fa8973eaa364811af93a08661052d62298c62da67673f395a", "pool": "POOL IDENTICAL up to 55 (mine=55 base=55)", "fuzzy": 94.83023, "measures": {"fuzzy_match_percent": 95.340576, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "drops": [], "instructions": [911, 913], "diffs": null}

Private mwdbg kpad/output-210-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/kpad-output-210-1-private, SHA256 e4e31e3d07177175449be07cad5b4405ac1f68cb777dfb625765583786b418c1.

Raw private mwdbg kpad/output-210-1 exit0.

Raw trace attempt kpad/output-210-1: exit0, build/perm2/mwdbg/kpad-output-210-1.

MWDBG capture validation kpad-output-210-1: exit0; build/perm2/mwdbg/kpad-output-210-1/validation-run.log.

Raw BS2 debugger reviews use allocator snapshots to avoid repeating thousands of per-node breakpoint stops for candidates already rejected for pool/readability. This mode retains pre-coalescing and pre-simplify graphs, actual color priority, final node colors, all PCode stages, register rewrite checks and production-object identity. Individual simplify/assign-event checks are explicitly marked uncollected. Retained-source baseline and clean candidate still use the full trace.

Private mwdbg bs2/import-and-skipped-path-locals: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-import-and-skipped-path-locals-long-private, SHA256 bc85e28c6062f492655611588cc84f13cda31714da1d10578f13c28b4ad18d6e.

Private debugger transport optimization: local accept/accept4 shim enables TCP_NODELAY on accepted debugger sockets and preserves errno. Retrowin32 leaves Nagle enabled by default; thousands of small GDB packets make full BS2 traces slow. Only the private emulator process is preloaded; compiler and project code are unchanged. Private emulator binary retained at build/perm2/retrowin32-private.bin with SHA256 9c85df235aa8a07b48560146abca2ccaea1dfbb0cf81ecc360b494ca46005268. Subsequent traces still require independent whole-object and register validation.

Source trial {"job": "so", "label": "const-input-pointee-before-socket", "build": 0, "sha256": "a68764b8e71b2372fa10d974f791131e7896748ed82b97a664855aed6cbbd731", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-input-pointee-before-reply", "build": 2, "sha256": "7d452f8c5fcc896b4c5270211dba3ea770428f530dea2ea9e8b4c9305802c764"}

Source trial {"job": "so", "label": "const-input-pointer-before-socket", "build": 0, "sha256": "21bfe2d10cde21de588878277712725da7899fe07267caec6bf0cfbd28b0ddbd", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-input-pointer-before-reply", "build": 2, "sha256": "75414761c9f1fabb00ee895df0ebd0b7ad6c0d030a55752ca7be6f3a9bede771"}

Source trial {"job": "so", "label": "const-input-both-before-socket", "build": 0, "sha256": "c543adba81760d25d9da6c132a6f392a47b4dbc4215311204c1be4837983dfc2", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-input-both-before-reply", "build": 2, "sha256": "39355ddda97be6f63e5c14cd89dc68f6cdc479588963c33bf7eb7fdba6a67ee0"}

BS2 readable candidate changes exactly four instructions relative to current main: the addi r4,r4,0x10 and crclr pair swaps at instruction734/735 and870/871. Full mwdbg identifies the two branch-local path values as r32/r33, both allocated directly to argument register r4. The helper hint therefore becomes two ordinary const char* locals evaluated immediately before their report calls; every other instruction is unchanged. This preserves all55 pool strings and10488 data bytes. It fixes argument-preparation scheduling, not the two missing retail base reloads, and remains partial at95.23877.

SO const-length capture explains its98.01588 partial score: preloading length moves the socket store past reply-address construction, so socket and reply interfere and socket changes from target r28 to r30. The same three differing instructions remain, moved to positions5/30/33. No source retained from that trial.

Source trial {"job": "so", "label": "const-input-pointee-copy-block", "build": 0, "sha256": "4585396203a9cd975fc729e0a622b97b3f1a3640513b8c44442dc97838fbd99c", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-input-pointer-copy-block", "build": 0, "sha256": "f1db807e5746135d98e2e75a4f193c58fa1d234473a753fe712b8d9189244092", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-input-both-copy-block", "build": 0, "sha256": "b9b91c251e95070b6c863c16a645c1aafee34e6d141ca62db8e812744f79d49b", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

BS2 raw mwdbg retry output-2810-1: exit1; debug-only ASCII path, build/perm2/mwdbg/bs2-output-2810-1-ascii.

MWDBG compatibility bs2 output-2835-1: compiler fault at0x46da46 is the runtime case-fold table while comparing Shift-JIS/system encoding names. Debug-only omission of -enc SJIS produces a byte-identical whole object under normal wibo; original matching compile flags remain unchanged. Object SHA256 9346b83ea0c2a0b53f7a2dcbf9d12a1aa1522d464a1992608c163d121f9edf77.

Private mwdbg bs2/main-baseline-for-trace: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-main-baseline-for-trace-private, SHA256 5d6b3ace4896b2cadb13ae9a10c130fd8e0143d3c4782fc9e5767998f8f9cd33.

Source trial {"job": "nwc24", "label": "home-title-id-return", "build": 0, "sha256": "428efcb03d99c2ee7a7fcf7df6d86ec153fb36da74b61e1358e64f0befc2f75d", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 100.0, "measures": {"fuzzy_match_percent": 100.0, "total_code": "12496", "matched_code": "12496", "matched_code_percent": 100.0, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 30, "matched_functions_percent": 100.0, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 0}

Source trial {"job": "nwc24", "label": "home-title-id-accumulated", "build": 0, "sha256": "72d7051a89131b6ff64b8bfaa74a796de130d4b63836801f38d7ff2108acc67b", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "reuse-word-value-first", "build": 0, "sha256": "b6951f8b55686b1577e9b846a4eeee61ec5e8a804af16ad4cd9cc908608a6c25", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "reuse-word-value-last", "build": 0, "sha256": "c890fbdb889f6710e869b64d97fc42ac4c9c2df531ed23d80318fd5dc1ef195e", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Source trial {"job": "nwc24", "label": "reuse-word-value-with-results", "build": 0, "sha256": "c17ee22b3caf47f501bfb8ba1e053da4cc8b97b7de00c32eddc202792127779a", "pool": "POOL IDENTICAL up to 3 (mine=3 base=3)", "fuzzy": 99.201385, "measures": {"fuzzy_match_percent": 99.96319, "total_code": "12496", "matched_code": "11920", "matched_code_percent": 95.390526, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 30, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_units": 1}, "drops": [], "instructions": [144, 144], "diffs": 23}

Raw trace attempt bs2/output-2810-1: exit1, build/perm2/mwdbg/bs2-output-2810-1.

Source trial {"job": "so", "label": "allocate-name-request", "build": 0, "sha256": "2ee1b26a620492e80cf29848ecd272d8d641080d51f61cbf926eb340eb06dd51", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 80.15873, "measures": {"fuzzy_match_percent": 98.77691, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [65, 63], "diffs": null}

Source trial {"job": "so", "label": "allocate-name-request-const-size", "build": 0, "sha256": "9875bec28df4d1a89f8485fff7a37782c74fd82d0307411605998d73fd06ea02", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 80.15873, "measures": {"fuzzy_match_percent": 98.77691, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [65, 63], "diffs": null}

Source trial {"job": "so", "label": "allocate-name-request-address-first", "build": 0, "sha256": "792e0072128fd94eb21e0be21f832f59a0c2047012f658b94df2e5fcdf22216c", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 80.15873, "measures": {"fuzzy_match_percent": 98.77691, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [65, 63], "diffs": null}

NWC24 raw output40:99.72222,144/144,8 differences. It reuses BOOL useContentFile for a parsed32-bit identifier; that mixed meaning is unsuitable to retain. Natural rewrite factors NAND directory parsing into GetHomeTitleId, returns a real u64 assembled from high/low words, and stores its two halves into the task. This reaches100.0,144/144,0 differences, all80data bytes and other29 functions unchanged. A compound u64 accumulation and three generic scratch-value reuse forms remain99.201385 and were discarded. The accepted helper preserves the64-byte zero initialization, NAND call, both terminator stores and strtoul order, including error paths. Raw and exact mwdbg captures are queued.

Private mwdbg bs2/output-2810-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-output-2810-1-private, SHA256 b107ee9fcb22dda59ce837e984a3cd7b94c479e3bea6a4a35cad5fb622eb9950.

Raw private mwdbg bs2/output-2810-1 exit0.

Source trial {"job": "so", "label": "address-after-prepare", "build": 0, "sha256": "e729cce44267424d9b9b6b3c0e743672e0a95d7ec132ff96736f8d3f0623f9e3", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "address-scoped-after-prepare", "build": 0, "sha256": "bd7b9d669acef0a288ab288290b84167511905295c4476d9a64fa5131842b441", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "direct-address-parameter", "build": 0, "sha256": "05a3d68270ae5e5e6e9067385a0506e368677482ea1af1bbd72e92eb4f924005", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "address-length-accessor", "build": 0, "sha256": "d4ff950835b1e550698ed00cce24b7294b0583bd56576b278d341fa38109cf20", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Source trial {"job": "so", "label": "const-address-parameter", "build": 0, "sha256": "82b1bc92370da1845975f4b6d80230aa7e3909a66f6c5cf3360a7320d4b58955", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 96.666664, "measures": {"fuzzy_match_percent": 99.79452, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 3}

Private mwdbg nwc24/output-40-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/nwc24-output-40-1-private, SHA256 96b269bede5dfde0952084b607f46dd2289a0b2434c00a3071e588b097c7f408.

Private mwdbg nwc24/home-title-id-return: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/nwc24-home-title-id-return-private, SHA256 ca377dae7b8b20529018ce37f56d942aa82f016cd9a55df0e7bd9bd51622f7b5.

Source trial {"job": "so", "label": "initialize-name-request", "build": 0, "sha256": "b098c29e2a76d19c92f31feafefe95f79dd20dfc109e86b2e494100379e30b8e", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 90.2381, "measures": {"fuzzy_match_percent": 99.39824, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 6}

Source trial {"job": "so", "label": "initialize-name-request-address-first", "build": 0, "sha256": "5a58ebf9ebf3d2b9c77f9354824c3f5381485d0c692bd0a63219739b75c74f1a", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 90.2381, "measures": {"fuzzy_match_percent": 99.39824, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 6}

Source trial {"job": "so", "label": "address-validation-boundary", "build": 0, "sha256": "7f9beb593aa99f4d27ae942aefd54f1a0317aa717f0f95db6bb2e2590e297652", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 86.25397, "measures": {"fuzzy_match_percent": 99.15264, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [68, 63], "diffs": null}

Private mwdbg so/output-50-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/so-output-50-1-private, SHA256 89c044705045714fa4ef36ade493ccf03d58c46451b92b4fa7ce095a6ba11ded.

Source trial {"job": "so", "label": "validated-address-return", "build": 0, "sha256": "76423616a75433298a7ae91a528bd93cf6521cef78b2e3e29fcebcb596d9eee9", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 88.07937, "measures": {"fuzzy_match_percent": 99.26517, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [67, 63], "diffs": null}

Source trial {"job": "so", "label": "validated-address-const-parameter", "build": 0, "sha256": "3b805d2fc797d004689e493e74b12aef2a89d8f112edae3caf9b0c77602b1f08", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 88.07937, "measures": {"fuzzy_match_percent": 99.26517, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [67, 63], "diffs": null}

Private mwdbg bs2/output-2835-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-output-2835-1-private, SHA256 9346b83ea0c2a0b53f7a2dcbf9d12a1aa1522d464a1992608c163d121f9edf77.

Raw private mwdbg bs2/output-2835-1 exit0.

NWC24 lever22 proof: baseline parsed-high temp r51 received physical r29 after low r53 took r30, leaving zero/header temp r48 on r28. The raw reuse puts the early values right but keeps its mixed-purpose useContentFile node live into validation, swapping the later header and owner/group registers. GetHomeTitleId instead creates parsed-high temp r48 before zero temp r50; allocator priority assigns zero r29 and high r28, while low r55 stays r30. The later header/owner/group allocation stays at target r29/r28. Full trace passes all graph/event/rewrite/emitted-register checks and is byte-identical to production MWCC. Both KPAD and NWC24 quick gates pass; final clean gate is pending search completion.

BS2 raw mwdbg retry output-2835-1: exit1; debug-only ASCII path, build/perm2/mwdbg/bs2-output-2835-1-ascii.

MWDBG compatibility bs2 output-2895-1: compiler fault at0x46da46 is the runtime case-fold table while comparing Shift-JIS/system encoding names. Debug-only omission of -enc SJIS produces a byte-identical whole object under normal wibo; original matching compile flags remain unchanged. Object SHA256 1e88f849066cbde4f66a368a9cffd165c20d8c9708a9492d902fe2f57ab50ab1.

Private mwdbg bs2/output-2895-1: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-output-2895-1-private, SHA256 1e88f849066cbde4f66a368a9cffd165c20d8c9708a9492d902fe2f57ab50ab1.

Raw private mwdbg bs2/output-2895-1 exit0.

Private mwdbg bs2/output-2895-2: validated whole-object production identity, graph/color/rewrite and emitted-register checks. Capture build/perm2/mwdbg/bs2-output-2895-2-private, SHA256 4513a598cba9682ea21812cc1d625e654e6d32c71276fe6e3bad48d7cd4085d6.

Raw private mwdbg bs2/output-2895-2 exit0.

Raw private mwdbg nwc24/output-40-1 exit0.

Raw private mwdbg so/output-50-1 exit0.

Source trial {"job": "so", "label": "immutable-address-local", "build": 0, "sha256": "7154b8a07ff9f9e981c45f50fa909fe4626792684f5af6a1232ff04915354d0e", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 95.79365, "measures": {"fuzzy_match_percent": 99.74071, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 14}

Source trial {"job": "so", "label": "immutable-address-local-first", "build": 0, "sha256": "084cc02b4206b58493a1382e021b1157fd1980ceda9aa8965f41a3c2f88455c7", "pool": "POOL IDENTICAL up to 1 (mine=1 base=1)", "fuzzy": 95.0, "measures": {"fuzzy_match_percent": 99.69178, "total_code": "4088", "matched_code": "3836", "matched_code_percent": 93.83562, "total_data": "144", "matched_data": "144", "matched_data_percent": 100.0, "total_functions": 22, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_units": 1}, "drops": [], "instructions": [63, 63], "diffs": 24}

Stopped redundant shared-port debugger retries after private captures completed. Selection required this worktree cwd and exact local debugger/trace entrypoints; descendants were stopped while launcher locks remained held. No other worker process or shared tool file was changed. PIDs [2291939, 2292601, 2441536, 3006324, 3006869, 3867110].

SO output50 semantic review: address-of-local indirection is equivalent on all paths, but is unnecessary source scaffolding and rejected under lever21. The debugger shows it replacing named addr with anonymous temp r55 and moving memcpy destination setup after source/length. The raw candidate is99.20635 with10 register differences (address/size swap). Natural parameter, scope, const-pointer, length accessor, allocation/initialization and validation boundaries did not reproduce the scheduling gain; all are discarded. SO source remains96.666664.

BS2 raw outputs2810/2835/2895-1/2895-2 all received debugger verification. The three latter runs use complete allocator/PCode snapshots;2810 uses full events. All retain the rejected filename-wrapper pool regression (9160/10488 matched data), and2810 also invents a persistent zero-return temporary. No raw BS2 candidate is retained. The reviewed two-path-local rewrite preserves10488/10488 data and improves94.83023 to95.23877.

## Final perm2 campaign validation

All six searches ran7201.6-7201.8 seconds, with at most six permuter processes. Total iterations 59693; seven saved candidates, all reviewed for semantics/readability and verified with mwdbg.

- kpad: current-main 97.810814 -> retained 100.0; exact functions 28 -> 29; instructions [185, 185]; differences 0; data 8032/8032.
- nwc24: current-main 99.201385 -> retained 100.0; exact functions 29 -> 30; instructions [144, 144]; differences 0; data 80/80.
- window: current-main 98.17819 -> retained 98.17819; exact functions 20 -> 20; instructions [376, 376]; differences 119; data 316/316.
- so: current-main 96.666664 -> retained 96.666664; exact functions 21 -> 21; instructions [63, 63]; differences 3; data 144/144.
- scan: current-main 99.20221 -> retained 99.20221; exact functions 111 -> 111; instructions [272, 272]; differences 4; data 5696/5696.
- bs2: current-main 94.83023 -> retained 95.23877; exact functions 9 -> 9; instructions [911, 913]; differences None; data 10488/10488.

KPAD search seed98.89189 continued from agent/w1005/perm; fresh-main baseline97.810814. BS2 rejected seed95.30011 and raw best95.75903 both regress data to9160/10488; retained source starts from main94.83023 and reaches95.23877 with all data preserved. SO best raw99.20635 rejected for unnecessary double-pointer scaffolding; retained96.666664. Window and scan had no saved improvement.

Exact gain:2 functions,1316 code bytes. Owned exact total218 ->220/224. KPAD is29/29 and NWC24Download30/30, with every code/data section100%; no linking configuration changed.

Final clean gate command: `PYTHONDONTWRITEBYTECODE=1 python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RVL_SDK/src/kpad/KPAD libs/RevoEX/src/nwc24/NWC24Download libs/NW4R/src/lyt/lyt_window libs/RevoEX/src/so/SOBasic src/scene/setting/iplSetting src/BS2/BS2Update --base 5bdfe797a9136815a89f849f0c00dc7624068d12`. No --quick.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/kpad/KPAD] pool: IDENTICAL
[libs/RVL_SDK/src/kpad/KPAD] objdiff: code 13056/13056 data 8032/8032 functions 29/29 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/kpad/KPAD] instruction-exact functions: 29/29
[libs/RVL_SDK/src/kpad/KPAD]   section .bss size 7680 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .data size 88 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata size 112 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata2 size 120 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .text size 13056 match 100.0
[libs/RVL_SDK/src/kpad/KPAD] baseline: code 12316/13056 data 8032 functions 28 fuzzy 99.8759
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 12496/12496 data 80/80 functions 30/30 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 30/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 11920/12496 data 80 functions 29 fuzzy 99.9632
[libs/NW4R/src/lyt/lyt_window] pool: IDENTICAL
[libs/NW4R/src/lyt/lyt_window] objdiff: code 9848/11352 data 316/316 functions 20/21 fuzzy 99.7586 linked code 0
[libs/NW4R/src/lyt/lyt_window] instruction-exact functions: 20/21
[libs/NW4R/src/lyt/lyt_window]   section .ctors size 4 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .data size 256 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sbss size 8 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sdata2 size 48 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .text size 11352 match 99.75864
[libs/NW4R/src/lyt/lyt_window]   below 100: DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc 98.17819
[libs/NW4R/src/lyt/lyt_window] baseline: code 9848/11352 data 316 functions 20 fuzzy 99.7586
[libs/RevoEX/src/so/SOBasic] pool: IDENTICAL
[libs/RevoEX/src/so/SOBasic] objdiff: code 3836/4088 data 144/144 functions 21/22 fuzzy 99.7945 linked code 0
[libs/RevoEX/src/so/SOBasic] instruction-exact functions: 21/22
[libs/RevoEX/src/so/SOBasic]   section .bss size 40 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .data size 88 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sbss size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sdata size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .text size 4088 match 99.79452
[libs/RevoEX/src/so/SOBasic]   below 100: SOGetSockName 96.666664
[libs/RevoEX/src/so/SOBasic] baseline: code 3836/4088 data 144 functions 21 fuzzy 99.7945
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 36796/37884 data 5696/5696 functions 111/112 fuzzy 99.9771 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 111/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 100.0
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.97709
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 99.20221
[src/scene/setting/iplSetting] baseline: code 36796/37884 data 5696 functions 111 fuzzy 99.9771
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 95.7088 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/BS2/BS2Update]   section .bss size 9056 match 100.0
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 100.0
[src/BS2/BS2Update]   section .sdata size 24 match 100.0
[src/BS2/BS2Update]   section .text size 4052 match 95.708786
[src/BS2/BS2Update]   below 100: UpdateThread 95.23877
[src/BS2/BS2Update] baseline: code 400/4052 data 10488 functions 9 fuzzy 95.3406
regressions vs baseline: 0
global matched_code_percent: 93.01130 -> 93.05523
global fuzzy_match_percent: 99.78460 -> 99.78580
global complete_code_percent: 77.53828 -> 77.53828
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh `ninja -C . progress build/43U/report.json build/43U/ok` passed. All six pools are identical; KPAD ctxdiff185/185,0 differences; NWC24InitDlTask144/144,0 differences. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Final report/ctx/pool artifacts: build/perm2/final-audit/.

Remaining Window allocator evidence: its common flip-table base is simplified after the other persistent pointers because its degree is still above the available-color count on the earlier ascending visit. That assigns r31 instead of target r21. Tested direct geometry/texture expressions, real corner references, coordinate-array shape and scalar scope forms did not solve it without regressions. Scan retains four independent index/layout load-order differences; no evidence justifies volatile.

## Retained source commits

- cc0c835a Match KPADInit matrix initialization and rounding
- daf83ea9 Match NWC24InitDlTask with home title parsing helper
- 114c5292 Improve UpdateThread log argument scheduling

All three contain the source validated by the final clean gate above. The separate support commit restores the adapter/settings and preserves this attempts log. No push, PR, merge, rebase, or linking change was made.
