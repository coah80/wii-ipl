# rx51b: eZiText expression and allocator investigation

Worktree: `data-d3`, branch `agent/w1005/rx51b`, baseline `73139514`.
The fetched `origin/main` equals this baseline. GC/3.0a5 is selected by the
existing build. Private sources, reports, searches and debugger captures go
under `/tmp/rx51b`; the validated private a5 debugger from `/tmp/rx51/mwdbg`
is reused. No shared tools, other worktrees, configure.py or zkokeyp.c are
edited. The earlier user-word result is already linked by PR #1229.

Acceptance requires readable equivalent C, identical pools, exact-name
objdiff 100%, zero ctxdiff differences, no unit regressions and the full
43U gate with DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
Use member access for structures. Do not invent carriers or byte-offset
accesses to influence allocation.

## Baseline and prior work

Fresh report: Spelling 99.555885%, Candidates 96.419270%, ZH 98.336266%,
Alpha 95.648506%, Prepare 96.994680%. The four units have 25/30 exact
functions, 16064/94700 matched code bytes and 2448/2556 matched data bytes.
The only source changes since the prior investigation are corrected ZH
function declarations, which leave its generated code unchanged.
All four freshly measured string pools are empty and identical.

The prior log `rx51.attempts.md` records 74 compiled manual trials and 15
1200-second searches. This continuation keeps those rejected hypotheses
and validated allocator captures as evidence; it does not rerun the same
search seeds against the same source.

Spelling still has three structural discrepancies: one extra byte narrowing
on the first candidate increment, an omitted support-0x7c result copy, and
an extra support-0x7d result copy. Its named saved registers match retail.
The prior increment fix removes narrowing but changes recycled temporary
slots and three other call-result copies. The next trials test type and
expression lifetimes at those uses, with fresh debugger validation for
promising shapes.

## Return-value contract: the missing temporary

Mapping every target GPR use onto the validated baseline PCode exposed a
specific boundary, rather than a general allocator tie. After changing the
first candidate increment to `++candidateCount`, Spelling's target colors
agree with a one-slot shift through B206, including the saved work fields.
From B207 (immediately after Zi8Memset) onward, they require the old slot
numbers. Zi8Memset was declared void, so it allocated no discarded return
temporary. A pointer-return declaration supplies precisely that missing slot.

With both corrections, Spelling is 1700/1700, ctxdiff zero, objdiff 100%.
The validated a5 capture has 207 GPR priority nodes and 21 accepted coalesces,
matching the baseline counts. v57 changes r6 to r4 at degree 11, priority
182. The 0x7c result becomes v73, r4, degree 9, priority 167; the 0x7d
result becomes v83 and coalesces into r3. v92 remains r0, degree 7,
priority 154, preserving the required table-count copy. Independent wibo
object identity, 2977 GPR rewrites and 2584 machine register operands pass.
Capture: `/tmp/rx51/captures/rx51b-spelling-memset-return`.

This cannot be retained as an incompatible caller-only declaration.
Zi8Memset's target is 12 instructions and leaves its destination in r3 on
all paths. Adding `return destination` with a pointer return type compiles
to the same 12 instructions, with all 17 functions of zi8getc2 still exact.
Zi8Memcpy has the same destination-return behavior; its explicit return
also preserves all 17 exact functions. The contract correction must include
the definitions and every declaration, with the full gate covering each
changed caller unit. These private tests edit no other worktree.

Candidates with the corrected memset return and all three count-only
increments merged into their comparisons is 2397/2397, 99.99583%, one
ADD operand-order difference. `phraseEntries += offset + 1` computes the
integer displacement before pointer addition and fixes that ADD. Both
zi81key functions and all nine unit functions are then exact; data rises
from 1280/1388 to 1388/1388. The equivalent grouped-pointer expression and
array-address spelling also match; compound assignment is the clearest.
The source remains a genuine packed phrase-record cursor, without invented
offsets or carrier types.

The discarded-return correction also changes Prepare's previously tested
structural form from 943 instructions to 940 and removes its three unwanted
call-result copies. Its four remaining differences are the order of the
independent best/previous phonetic zero stores. They are being corrected
against the target stack offsets before validation.

## Reboot recovery

The machine reboot erased `/tmp/rx51` and `/tmp/rx51b`, including the old
trial sources and validated captures. At recovery, the source worktree was
unchanged and only this attempts log was untracked. The branch and HEAD
remain `agent/w1005/rx51b` and `73139514`. The numbers above describe the
pre-reboot captures, which no longer exist; new validation is required.

Reconstructed all four exact candidates from the recorded expression
changes and recompiled against the surviving target objects. Spelling and
Candidates again give 1700/1700 and 2397/2397, zi81key 9/9 and 1388/1388
data. ZH gives 10676/10676 with zero differences, zi8cgetc 8/8 and 536/536
data. Prepare gives 940/940, zero differences and 68/68 data. All seven
units touched so far by the common memory-function contract are fully exact
in private objdiff reports; Alpha's declaration is also updated before any
commit so there is no incompatible void declaration left behind.

ZH's three final differences were ADD operand order in computing an ordinal:
`firstOrdinal + (remainingOrdinals - candidateCount - 1)` fixes all three.
The other required changes are separate component pointer/count assignments,
three postincrement space stores, the equivalent unsigned count-underflow
test and the ordinal increment spelling. Prepare's final four differences
were fixed by initializing bestInitial before bestFinal, then previousInitial
before previousFinal. Neither change adds a new field, wrapper or raw offset.

Rebuilt the private a5 debugger from the supplied patch under `/tmp/rx51b`.
The supplied patch uses port 19035; the private emulator uses 19051. The first
recovery capture found this mismatch and failed before capturing; the private
driver's connection port is corrected. No shared debugger files were edited.

## Alpha continuation after the contract correction

Canonical memory declarations preserve all 11 already exact Alpha functions
and all 564 data bytes. The open function moves 95.648506% to 95.637100%,
3946/3946; this small fuzzy decrease accompanies a necessary declaration
correction and is not being called a matching gain. Explicitly discarding
the return with `(void)` does not change allocation.

Fresh structural trials remove the proven dead dictionaryIndex initialization
(the for-loop initializer is retained), put the terminator after the preceding
character, and replace two dictionary-kind ranges with their target switch
shapes. This gives 3949/3946 at 95.963000%, with 408 data bytes. Adding the
two target halfword/byte normalization casts gives 3951/3946 at 95.959200%.
Replacing six test-only assignments to index with direct predicate calls gives
3951/3946 at 95.799545%. All remain private because they lose data.

The highlighted-word final character store remains a sequencing problem:
retail loads the RHS, stores through the old output index, and increments
that index without reloading it. A comma-separated store/increment,
independent scalar temporary, const scalar temporary and reuse of index
were compiled; they add copies, spills or reloads and do not match. No
expression reads and modifies elementIndex without sequencing. The four
increment spellings were also checked in both separate and comma forms.
A fresh Alpha allocator capture is running to locate the remaining reused
slot conflicts before any candidate is retained.

## Recovery acceptance checkpoint

The clean full eight-unit gate passes after reconstruction. It reports zero
regressions, forbidden patterns and readability warnings; the 43U DOL hash
remains correct. Global matched data is now 100%. The four target functions
are instruction exact; Alpha stays open. No configure.py flags are changed.

```text
[libs/RVLMiddleware/eZiText/src/clib/zi81key] objdiff: code 21460/21460 data 1388/1388 functions 9/9 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi81key] instruction-exact functions: 9/9
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 47816/47816 data 536/536 functions 8/8 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 8/8
[libs/RVLMiddleware/eZiText/src/clib/zprepare] objdiff: code 3760/3760 data 68/68 functions 1/1 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zprepare] instruction-exact functions: 1/1
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] objdiff: code 5880/21664 data 564/564 functions 11/12 fuzzy 96.8213 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] instruction-exact functions: 11/12
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] objdiff: code 6888/6888 data 332/332 functions 17/17 fuzzy 100.0000 linked code 6888
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] instruction-exact functions: 17/17
[libs/RVLMiddleware/eZiText/src/clib/zi8initd] objdiff: code 704/704 data 20/20 functions 2/2 fuzzy 100.0000 linked code 704
[libs/RVLMiddleware/eZiText/src/clib/zi8initd] instruction-exact functions: 2/2
[libs/RVLMiddleware/eZiText/src/clib/zi8is] objdiff: code 1136/1136 data 40/40 functions 3/3 fuzzy 100.0000 linked code 1136
[libs/RVLMiddleware/eZiText/src/clib/zi8is] instruction-exact functions: 3/3
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] objdiff: code 2656/2656 data 80/80 functions 4/4 fuzzy 100.0000 linked code 2656
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] instruction-exact functions: 4/4
GATE PASS
```

## Fresh debugger confirmations and Alpha argument lifetimes

Committed the recovered, fully gated source as `3f03dab6`. The remote ref
later moved to `8fd7e1ce`; no fetch, merge or rebase was performed after that.
The acceptance checkpoint above uses the recorded `73139514` baseline.

Fresh a5 captures under `/tmp/rx51b/captures` replace the erased evidence.
Spelling: 207 priority nodes, 21 accepted coalesces, 2977 GPR rewrites and
2584 machine operands. Candidates: 180 nodes, 47 coalesces, 4483 rewrites,
3626 machine operands. Prepare: 204 nodes, 21 coalesces, 1667 rewrites,
1429 machine operands. ZH: 206 nodes, 31 coalesces and 18821 rewrites. Its
three out-of-range conditional branches were independently checked as
inverted skips plus far branches; 8604 straight instructions and 16379
register operands then agree. Every independent wibo object is identical.
These large captures use graph snapshots, not assignment-event validation.

All three newly exact units have identical text symbol order. The .sbss2
and .sdata2 symbols also agree. Symorder's raw warnings concern anonymous
jump-table/exception names; their offsets and sizes agree. Their complete
code/data objdiff measures are already 100%. No Matching flag was changed.

Two additional defined comma/compound forms of the highlighted-character
store gave 95.555244% (3952 instructions) and 95.519770% (3951). Neither
was kept. The original separate store still reloads elementIndex; the target
keeps the old index through its increment. Unsequenced variants remain
excluded.

The fresh Alpha structural capture has 173 priority nodes and 54 coalesces;
index stays r29 while its weight falls 208 to 187. Mapping target operands
to recycled virtual slots establishes a stronger result: the first four
temporary banks agree on desired colors through B378. The first persistent
numbering divergence begins at B379, the first variable-length ROM match
call. Explicit masks on already narrow function arguments allocate extra
virtual values even when they produce the same machine narrowing. Removing
only ROM-call masks reaches 96.377340%; all matching-call masks reach
97.658390%. The masks are redundant with the declared parameter conversions.

The first broader trial incorrectly treated DeTokenization's length as a
halfword parameter. It is declared ziU32; that private trial was corrected
to an explicit ziU16 cast before further use. Restoring that narrowing,
using the target's unsigned byte comparison and removing only the final
redundant prefixMode cast gives 98.170296%, 3948/3946. Data is 408/564,
so this remains a private diagnostic candidate. Three new source searches
use seeds 1051/1151/1251; they respect the shared slot limiter.

The 98.17% capture confirms the argument-mask hypothesis: all mapped
operands agree with the first-bank target colors through B546, except the
known highlighted-character store. B547 then adds one unnecessary virtual
value for DeTokenization's explicit length cast. Testing the definition and
its declaration together establishes that both its length parameter and
return type can be ziU16 while preserving its exact machine body. Changing
only the parameter loses that helper's match; changing both restores all
11 exact helpers and yields Alpha 98.717690%, 3946/3946, data 516/564.
The accepted workspace is unchanged; no fuzzy-only trial is retained.

Eight fresh defined forms of the highlighted-character store were compiled
against this new basis: scoped const/mutable ziU16 and ziU32 values, a
compound count assignment, a comma expression, and separate input/output
address locals. Their scores range 97.394830% to 97.830460%, with extra
spills/copies and lost data. Six void/comma variants either reproduce the
938-difference private baseline or add instructions. These failures do not
establish a pure allocator tie: target instructions 637-646 and 3672-3683
still require two different store/increment shapes.

The first new searches were superseded by this better manual basis: seed
1051 was still queued, and 1151/1251 had not improved their starts. They
were stopped cleanly, then seeds 2051/2151/2251 were launched for the full
1200 seconds from the 98.717690% candidate, retaining the shared limiter.

Candidates' fresh baseline graph has 188 priority nodes and 39 coalesces;
the exact graph has 180 and 47. Its initial ordinalTable zero is v32: the
old graph merged it into r3, while the new degree-6 node interferes with
r3 and colors last (priority 179) to target r0. The named saved registers
and their weights are unchanged. The count comparisons and memory-return
slot change the reused temporary graph; the packed-record compound advance
also puts the ADD operands in target order.

Prepare's graph changes 217/8 to 204/21 (priority nodes/coalesces). The
contextMask literal v33 has degree 8, priority 215, r3 before; it has
degree 6, priority 202, target r0 afterward. Its new r3 interference comes
from another use of the same recycled slot. The new discarded-memory-return
v34 coalesces with r3 and emits no move. Match/request/index/nibbles/work
remain r31/r30/r29/r28/r27 with weights 147/53/42/29/9.

ZH's baseline and exact graphs both have 206 priority nodes and 31 accepted
coalesces. The reused v152, first the narrowed `getOptions & ~0x20` byte,
keeps degree 18 but moves priority 101 to 100 and color r10 to target r8.
Its early definition is unchanged; the later count/pointer expression fixes
change which values reuse those slots. v32/v33 retain r8/r7 and degrees
10/11. The three ordinal ADD operand fixes change operand construction,
not those saved-register assignments.

Adding the target's explicit byte normalization to the prefix destination
index reaches Alpha 99.803600%, 3946/3946, 69 raw instruction differences
and all 564 data bytes. This supplies the extra virtual slot at B855 and
restores every later bank's desired colors. Only the two previously noted
store/increment sequences remain structurally different; their other uses
account for the residual register differences. Compound, comma, discarded
comma and scalar-character prefix forms were compiled; none is exact.
The pending 2051/2151/2251 searches were moved to this new start while they
were still queued, so their full run budgets remain 1200 seconds each.

The full-local capture of the scalar-character alternative confirms weight
2 for its character value; it is not selected for a saved register. Existing
parameters/work/index/wordCursor/options retain weights 390/328/187/183/45
and r31/r30/r29/r28/r27. Thus the extra scalar introduces a stack slot and
store/load instructions under these flags, rather than the desired temporary
register value. No forced-register keyword, fake use, carrier or unsequenced
index mutation was introduced to evade that result.

## Reconstructing the rejected Alpha candidate after another reboot

This patch is recorded as experiment evidence only. It is not an accepted
source change: Alpha is still 69 instructions away from exactness. It applies
to the canonical memory-return declaration in commit `3f03dab6`. All helper
functions stay exact, all data matches, and the instruction counts agree.

```diff
--- accepted/zi8alpha.c
+++ private-alpha-99.8036/zi8alpha.c
@@ -296,5 +296,5 @@
 }

-ziU32 Zi8DeTokenization(ziWChar* word, ziU32 length, ziU16 capacity, ziU16 language);
+ziU16 Zi8DeTokenization(ziWChar* word, ziU16 length, ziU16 capacity, ziU16 language);
 ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
 ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
@@ -551,5 +551,4 @@
   }
   Zi8InitDupWordBuf(workData);
-  dictionaryIndex = 0;
   if ((((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
      ((((parameters->getOptions & 0xfd) != 0x80 && (parameters->elementCount != 0)) &&
@@ -655,5 +654,5 @@
   goto prepareDictionaryOrder;
 preparePrefix:
-  prefixMode = ((ZiAlphaWork*)workData)->suffixMode;
+  prefixMode = (ziU8)((ZiAlphaWork*)workData)->suffixMode;
   prefixTableFlags = Zi8GetTableCount(language,0x1f,workData);
   prefixVowelFlags = prefixTableFlags & 0x10;
@@ -901,17 +900,17 @@
               else {
                 if (alternateSingleCharacter != 2) {
-                  wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,language,wordCursor,
-                                               wordCapacity & 0xffff,matchMode,
-                                               dictionaryStatus[dictionaryKind] & 0xff,0,exactLengthOnly,workData);
+                  wordLength = Zi8MatchROMdata(elements,elementCount,language,wordCursor,
+                                               wordCapacity,matchMode,
+                                               dictionaryStatus[dictionaryKind],0,exactLengthOnly,workData);
                   }
                 if ((alternateSingleCharacter != 0) && ((wordLength == 0 || (*wordCursor == *elements)))) {
                   if (alternateSingleCharacter == 1) {
                     alternateSingleCharacter = 2;
-                    wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,parameters->subLanguage,wordCursor,
-                                                 wordCapacity & 0xffff,1,0,0,exactLengthOnly,workData);
+                    wordLength = Zi8MatchROMdata(elements,elementCount,parameters->subLanguage,wordCursor,
+                                                 wordCapacity,1,0,0,exactLengthOnly,workData);
                       }
                   else {
-                    wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,parameters->subLanguage,wordCursor,
-                                                 wordCapacity & 0xffff,1,1,0,exactLengthOnly,workData);
+                    wordLength = Zi8MatchROMdata(elements,elementCount,parameters->subLanguage,wordCursor,
+                                                 wordCapacity,1,1,0,exactLengthOnly,workData);
                       }
                 }
@@ -923,25 +922,22 @@
                  ((((ZiAlphaWork*)workData)->singleCharacter != 0 && (parameters->elementCount == 2)))) {
                 *wordCursor = ((ZiAlphaWork*)workData)->singleCharacter;
+                wordCursor[1] = *punctuationCursor++;
                 wordCursor[2] = 0;
-                wordCursor[1] = *punctuationCursor++;
                 wordLength = 2;
               }
               if (((apostropheIndex != 0) && (wordLength != 0)) && (elementCount == parameters->elementCount)) {
                 if (language == 0x2f) {
-                  index = Zi8ITspecialExclusion
-                                     (wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex);
-                  if (index != '\0') {
+                  if (Zi8ITspecialExclusion
+                                     (wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex) != 0) {
                     wordLength = 0;
                   }
                 }
                 else if (language == 0x58) {
-                  index = Zi8_814659E8(wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex);
-                  if (index != '\0') {
+                  if (Zi8_814659E8(wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex) != 0) {
                     wordLength = 0;
                   }
                 }
                 else {
-                  index = Zi8IsVowel(language,wordCursor[apostropheIndex]);
-                  if (index == '\0') {
+                  if (Zi8IsVowel(language,wordCursor[apostropheIndex]) == 0) {
                     wordLength = 0;
                   }
@@ -962,18 +958,15 @@
                   }
                   if (language == 0x2f) {
-                    index = Zi8ITspecialExclusion(wordCursor,prefixCount,wordLength);
-                    if (index != '\0') {
+                    if (Zi8ITspecialExclusion(wordCursor,prefixCount,wordLength) != 0) {
                       wordLength = 0;
                     }
                   }
                   else if (language == 0x58) {
-                    index = Zi8_814659E8(wordCursor,prefixCount,wordLength);
-                    if (index != '\0') {
+                    if (Zi8_814659E8(wordCursor,prefixCount,wordLength) != 0) {
                       wordLength = 0;
                     }
                   }
                   else {
-                    index = Zi8IsVowel(language,*wordCursor);
-                    if (index == '\0') {
+                    if (Zi8IsVowel(language,*wordCursor) == 0) {
                       wordLength = 0;
                     }
@@ -999,7 +992,7 @@
             case 6:
               if (elementCount != 0) {
-                wordLength = Zi8MatchPUDdata(elements,elementCount & 0xff,language,wordCursor,
-                                             wordCapacity & 0xffff,dictionaryExact,
-                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
+                wordLength = Zi8MatchPUDdata(elements,elementCount,language,wordCursor,
+                                             wordCapacity,dictionaryExact,
+                                             dictionaryStatus[dictionaryKind],workData);
               }
               break;
@@ -1009,6 +1002,6 @@
                 wordLength = Zi8MatchUWDdata(elements,elementCount,
                                              parameters->currentWord,parameters->wordCharCount,
-                                             language,wordCursor,wordCapacity & 0xffff,dictionaryExact,
-                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
+                                             language,wordCursor,wordCapacity,dictionaryExact,
+                                             dictionaryStatus[dictionaryKind],workData);
                 if (((elementCount != 0) || (wordLength != 1)) || (*wordCursor != 0x20)) break;
                 dictionaryStatus[dictionaryKind] = 1;
@@ -1020,5 +1013,5 @@
                 wordLength = Zi8MatchOEMdata(elements,elementCount,language,wordCursor,
                                              wordCapacity,dictionaryExact,
-                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
+                                             dictionaryStatus[dictionaryKind],workData);
               }
               break;
@@ -1075,6 +1068,10 @@
                             (((ZiAlphaWork*)workData)->dictionaries[language] == 0)))))) {
                 if (language != ((ZiAlphaWork*)workData)->language) break;
-                index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
-                if (index == 0xc || (index < 9 && index >= 5)) {
+                switch (((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1]) {
+                case 5:
+                case 6:
+                case 7:
+                case 8:
+                case 12:
                   if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
                     punctuationBuffer[0] = 0;
@@ -1095,6 +1092,15 @@
                      (((ZiAlphaWork*)workData)->dictionaries[language] != 0)))))) ||
                   (languagePassCount == 2)))) break;
-              index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
-              if ((index != 0xc) && (((0xb < index || (8 < index)) || (index < 5)))) break;
+              switch (((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1]) {
+              case 5:
+              case 6:
+              case 7:
+              case 8:
+              case 12:
+                goto prepareRememberedPunctuation;
+              default:
+                goto finishDictionaryPass;
+              }
+prepareRememberedPunctuation:
               if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
                 punctuationBuffer[0] = 0;
@@ -1128,6 +1134,6 @@
                   wordCursor[wordLength] = 0;
                 }
-                wordLength = (ziU16)Zi8DeTokenization(wordCursor,wordLength & 0xffff,wordCapacity & 0xffff,language);
-                if (((phoneticInput) && ((unsigned int)parameters->elementCount < (wordLength & 0xff))) &&
+                wordLength = Zi8DeTokenization(wordCursor,wordLength,wordCapacity,language);
+                if (((phoneticInput) && ((ziU8)parameters->elementCount < (wordLength & 0xffU))) &&
                    ((wordCursor[wordLength - 1] == 0xf360 || (wordCursor[wordLength - 1] == 0x27)))) {
                   wordLength = wordLength - 1;
@@ -1146,5 +1152,5 @@
                   }
                   if (((int)((ZiAlphaOptions*)optionData)->maxWordLength < (int)(wordLength + prefixCount)) ||
-                     ((Zi8IsDupWordW(wordCursor - prefixCount,wordLength + prefixCount & 0xff,
+                     ((Zi8IsDupWordW(wordCursor - prefixCount,wordLength + prefixCount,
                                                workData)) != '\0')) {
                     if ((prefixCount != 0) && (((ZiAlphaOptions*)optionData)->maxWordLength <= prefixCount)) break;
@@ -1542,5 +1548,5 @@
         }
         if (elements[((ZiAlphaWork*)workData)->prefixCount] != 0xEFF1 && Zi8IsAlphaPunct(elements[((ZiAlphaWork*)workData)->prefixCount]) != 0) {
-          ((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount] = elements[((ZiAlphaWork*)workData)->prefixCount];
+          ((ZiAlphaWork*)workData)->prefix[(ziU8)((ZiAlphaWork*)workData)->prefixCount] = elements[((ZiAlphaWork*)workData)->prefixCount];
           ((ZiAlphaWork*)workData)->prefixCount++;
         } else {
@@ -1638,5 +1644,5 @@


-ziU32 Zi8DeTokenization(ziWChar* word, ziU32 length, ziU16 capacity, ziU16 language) {
+ziU16 Zi8DeTokenization(ziWChar* word, ziU16 length, ziU16 capacity, ziU16 language) {
     ziU16 index;
     ziBool changed = ZI8_FALSE;
```

## Alpha's remaining graph conflict

The 99.803600% capture independently validates 6541 GPR operand rewrites
and 5472 machine operands. Its graph has 181 priority nodes and 46 accepted
coalesces. The target requires the highlighted character in r4 at instruction
640. Our character v92 has degree 9 and priority 128 and colors r3: its
interference neighbors include v93/r6 and v94/r5, leaving r3 available.
The separate increment defines v96 only after that character has died.
The target instead keeps the old index through the store and uses the slot
corresponding to v96 for the scaled destination address while the character
is still live. That missing overlap explains why r4 is needed.

This cannot be fixed by declaration priority alone. Mapping target operands
onto the current PCode requires v94 to be r3 in B129 but r5 in its other
seven lifetimes, and requires v96 to be r4 there but r3 elsewhere. At the
prefix store, the old-count v145 dies before address formation, has degree 7
and priority 86, and selects r0; retail keeps that count in r5 through the
increment. The current narrow-index v146 is coalesced into r3. These are
different live ranges and temporary roles, not arbitrary interchangeable
colors. The two obvious indexed-postincrement spellings would read and
modify the same index without sequencing, so they were not compiled.

One independent packed-record ADD discrepancy also remained at instruction
2490. `keyLayoutCursor += *keyLayoutCursor + 1` fixes it without changing
counts or data. The final private manual score is 99.806130%, 3946/3946,
68 differences and 564/564 data. Commuting the addition or writing an array
address did not fix that operand order. The patch above needs this additional
compound assignment to reconstruct the best manual source.

## Compiled recovery trial index

Only the four exact functions in commit `3f03dab6` are retained. Alpha rows
below are rejected trials. Data denotes the unit matched-data byte count.

| Trial | Function score | Instructions | Matched data |
| --- | ---: | ---: | ---: |
| restored-zi81key | 100.000000 | 2397/2397 | 1388 |
| restored-zi8cgetc | 100.000000 | 10676/10676 | 536 |
| restored-zprepare | 100.000000 | 940/940 | 68 |
| restored-zi8getc2 | 100.000000 | 12/12 | 332 |
| restored-zi8initd | 100.000000 | 128/128 | 20 |
| restored-zi8uwd | 100.000000 | 116/116 | 80 |
| restored-zi8alpha | 95.637100 | 3946/3946 | 564 |
| restored-alpha-discard | 95.637100 | 3946/3946 | 564 |
| alpha-new-structural | 95.963000 | 3949/3946 | 408 |
| alpha-new-casts | 95.959200 | 3951/3946 | 408 |
| alpha-new-predicates | 95.799545 | 3951/3946 | 408 |
| alpha-new-comma | 95.522300 | 3951/3946 | 408 |
| alpha-new-index | 95.824880 | 3952/3946 | 408 |
| alpha-sequence-0 | 95.585655 | 3952/3946 | 408 |
| alpha-sequence-1 | 95.585655 | 3952/3946 | 408 |
| alpha-sequence-2 | 95.585655 | 3952/3946 | 408 |
| alpha-sequence-3 | 95.799545 | 3951/3946 | 408 |
| alpha-sequence-4 | 95.799545 | 3951/3946 | 408 |
| alpha-sequence-5 | 95.799545 | 3951/3946 | 408 |
| alpha-sequenced-store-0 | 95.555244 | 3952/3946 | 408 |
| alpha-sequenced-store-1 | 95.519770 | 3951/3946 | 408 |
| alpha-arguments-rom | 96.377340 | 3955/3946 | 408 |
| alpha-arguments-matches | 97.658390 | 3954/3946 | 408 |
| alpha-arguments-all | 97.709076 | 3950/3946 | 408 |
| alpha-arguments-fixed | 98.170296 | 3948/3946 | 408 |
| alpha-detoken-param | 98.717690 | 3946/3946 | 516 |
| alpha-detoken-16 | 98.717690 | 3946/3946 | 516 |
| alpha-fresh-sequence-const-u16 | 97.639130 | 3954/3946 | 408 |
| alpha-fresh-sequence-const-u32 | 97.405220 | 3955/3946 | 408 |
| alpha-fresh-sequence-scalar-u16 | 97.830460 | 3948/3946 | 408 |
| alpha-fresh-sequence-scalar-u32 | 97.405220 | 3955/3946 | 408 |
| alpha-fresh-sequence-count-compound | 97.473640 | 3954/3946 | 408 |
| alpha-fresh-sequence-comma | 97.538270 | 3949/3946 | 408 |
| alpha-fresh-sequence-output-address | 97.394830 | 3953/3946 | 408 |
| alpha-fresh-sequence-input-address | 97.438160 | 3954/3946 | 408 |
| alpha-comma-void-store | 97.538270 | 3949/3946 | 408 |
| alpha-comma-void-both | 98.717690 | 3946/3946 | 516 |
| alpha-comma-comma-void | 98.717690 | 3946/3946 | 516 |
| alpha-comma-compound-void | 97.473640 | 3954/3946 | 408 |
| alpha-comma-preincrement-void | 98.503800 | 3947/3946 | 408 |
| alpha-comma-value-sequenced | 97.596550 | 3948/3946 | 408 |
| alpha-prefix-index-cast | 99.803600 | 3946/3946 | 564 |
| alpha-prefix-compound | 98.662190 | 3950/3946 | 408 |
| alpha-prefix-compound-void | 98.662190 | 3950/3946 | 408 |
| alpha-prefix-comma | 99.673840 | 3947/3946 | 456 |
| alpha-prefix-comma-discard | 98.717690 | 3946/3946 | 516 |
| alpha-prefix-char-local | 98.736440 | 3948/3946 | 408 |
| alpha-add-commuted | 99.803600 | 3946/3946 | 564 |
| alpha-add-address | 99.803600 | 3946/3946 | 564 |
| alpha-add-grouped | 99.806130 | 3946/3946 | 564 |
| alpha-index-lifetime-old-const | 98.402176 | 3947/3946 | 408 |
| alpha-index-lifetime-old-mutable | 98.402176 | 3947/3946 | 408 |
| alpha-index-lifetime-copied-post | 98.222500 | 3947/3946 | 408 |
| alpha-index-lifetime-copy-after | 98.357834 | 3947/3946 | 408 |

The grouped-pointer trial also passed a fresh debugger capture and independent
wibo comparison. Four old-index lifetime variants add one instruction and
lose data. A normal `static inline` append helper was then tried to sequence
the source-character read before the index mutation. Under the required
`-inline off`, the call remains; it scores 95.866700% and loses data. This
helper is rejected and compiler flags are unchanged. Its target instruction
count happens to agree because other copies move, which is not exactness.

| Additional trial | Function score | Instructions | Matched data |
| --- | ---: | ---: | ---: |
| alpha-inline-sequence | 95.866700 | 3946/3946 | 516 |

Final checks on the accepted source still give identical empty pools and
ctxdiff zero at 1700, 2397, 10676 and 940 instructions. The DOL SHA1 remains
`26116613f624061ba99c8d1a299aaa6efa85670d`. The only uncommitted tracked file
is this attempts log. The three final searches are still queued behind the
shared 24-slot limiter as of 2026-10-05 17:46 UTC.

### Additional sequenced arithmetic trials

Three defined C expressions tried to retain the old `elementIndex` while
copying the character: adding the store/comma expression to the index in
either operand order, and subtracting the store/comma expression's `-1`.
All three compiled to 3955/3946 instructions, scored 98.241510%, and matched
408/564 data bytes. They add nine instructions and change stack placement;
none reproduces retail's copied old index followed by the indexed store.
All are rejected. The accepted source and four exact functions are unchanged.

The final three 1200-second searches remain queued as of 18:03 UTC. The
shared limiter has 24 active owners; its time budget begins only after a
slot is acquired. No limiter change or other worker process was made.

The arithmetic trial's fresh mwdbg capture confirms the frontend difference.
B129 emits `li v95,1; stw v95,@1531; lwz v96,elementIndex; lwz v97,@1531;
add v98,v96,v97`. The compiler-generated comma-result object is the extra
stack temporary; this is not an allocator choice that declaration order can
remove. Character v92 retains degree 9, priority 134 and r3, while v93/v94
still color r6/r5. The hidden literal v95 has degree 10, priority 131 and r4.
There are 42 successful coalesces. Debugger validation passes, including
6559 GPR operand rewrites, 5490 emitted register operands, and byte-identical
output against the independent wibo compilation.

A standard two-byte `memcpy` was also tested for the highlighted character,
followed by the separate index increment. This is a defined copy, but GC/a5
with the required flags retains `bl memcpy` and fixes its arguments in r3-r5;
it does not expand the call into the target's indexed halfword load/store.
The result is 99.534720%, 3950/3946 instructions and 408/564 data, so it is
rejected. Together with the ordinary inline-helper trial, this rules out
these two natural call boundaries under the actual compiler flags.

## Completed final Alpha searches

These searches use GC/3.0a5, the actual unit command, `--mode anneal`, the
shared 24-slot limiter, and the 99.803600% `prefix-index-cast.c` manual seed.
Each requested 1200 seconds after acquiring a slot. They do not edit the
worktree. Any returned candidate still requires a source review and exact
ctxdiff; none is accepted solely on its fuzzy score.

| Seed | Completed trials | Best no-drop score | Candidate files |
| --- | ---: | ---: | --- |
| 2251 | 1299 | 99.803600% | no best.c or solution.c |
| 2051 | 1172 | 99.803600% | no best.c or solution.c |
| 2151 | 1169 | 99.803600% | no best.c or solution.c |

All three runs completed their full budgets: 3640 trials total, with no
improvement and no candidate file to promote. The best manual Alpha trial
remains 99.806130% with 68 differences; it is rejected. The unresolved
constraint is the two indexed stores' old-index lifetimes and resulting
PCode, not a demonstrated arbitrary allocator tie. No unsequenced index
read/modification, carrier, forced register, or compiler-flag change was used.

## Recovery handoff

The accepted source is still commit `3f03dab6`; subsequent changes are this
attempts log. The full clean eight-unit gate passed with zero regressions,
zero forbidden-pattern additions, and zero readability warnings. Current
report values remain Spelling 100%, Candidates 100%, ZH 100%, Prepare 100%,
and Alpha 95.637100%. Alpha retains only the consistent memory-helper
prototype correction, with its slight fuzzy decrease already included in
the passing gate. No rejected Alpha implementation is in the worktree.

The exact units remain zi81key 9/9, zi8cgetc 8/8, and zprepare 1/1. Their
code and data measures are 100%; the other four edited helper caller units
remain fully exact and linked. The zi81key gain is 108 matched data bytes,
bringing matched project data to 100%. Configure/link flags were not edited;
linking the three newly exact units remains the orchestrator's step.

A final report read and SHA1 check confirm
`26116613f624061ba99c8d1a299aaa6efa85670d`. The shared `origin/main` ref advanced
to `f18082e8` while this run was active; none of its three intervening commits
changes an eZiText clib source file. This branch was not rebased. All search
and debugger processes launched for these final trials have completed.
