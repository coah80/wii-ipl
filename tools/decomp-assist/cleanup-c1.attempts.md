# cleanup-c1 source cleanup

Baseline: f1db6b656e386063a8bc263fb75a299f36ae4803, equal to origin/main.
Assigned units: CHANSVm, AOSS, iplCardSequence. Existing rx67c.attempts.md is unrelated and left untouched.
Initial full ninja build passed. All 1028 units and 12563 functions matched and linked at 100%.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. Completion checker: DECOMPLETE_OK.

Acceptance: preserve every allocated object section, relocation, unit match/link measure, and the DOL hash.
Restore any trial that changes bytes. Finish with the three-unit gate and a fresh completion check.

## Trials
- src/channelScript/CHANSVm: remove function-scoped #pragma opt_lifetimes off. RESTORED; .rela.text; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/scene/setting/AOSS: remove function-scoped #pragma optimization_level 3. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/cardSequence/iplCardSequence: remove function-scoped #pragma opt_propagation off. RESTORED; .rela.data; .rela.text; .text: 9852 -> 9848 bytes, 5438 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma with immutable index bound. RESTORED; .rela.text; .sdata2: 184 -> 192 bytes, 8 differing bytes; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with response-table declaration before cursor. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/cardSequence/iplCardSequence: remove propagation pragma with byte-sized command. RESTORED; .rela.data; .rela.text; .text: 9852 -> 9848 bytes, 5441 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with cursor initialization before response table. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma using response parameter as the option cursor. RESTORED; .rela.text; .text: 16192 -> 16192 bytes, 34 differing bytes.
- src/scene/cardSequence/iplCardSequence: remove propagation pragma with command-scoped response local. RESTORED; .rela.data; .rela.text; .text: 9852 -> 9848 bytes, 5438 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma with array accumulator declared after stack top. RESTORED; .rela.text; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/scene/setting/AOSS: replace checksum carrier with expected and actual checksum scalars. RESTORED; .rela.text; .text: 16192 -> 16192 bytes, 16 differing bytes.
- src/scene/setting/AOSS: remove unused poll-time carrier and dead field stores. RESTORED; .rela.data; .rela.text; .text: 16192 -> 16184 bytes, 9327 differing bytes.
- src/scene/cardSequence/iplCardSequence: replace pollCardSlot exit goto with return. RESTORED; .rela.text.
- src/scene/cardSequence/iplCardSequence: replace probeCard dispatch gotos with a structured command test. RESTORED; .rela.text; .text: 9852 -> 9852 bytes, 14 differing bytes.
- src/scene/cardSequence/iplCardSequence: move clearAllCardFileEntries out of comma expression into its conditional block. RESTORED; .rela.text.
- src/scene/cardSequence/iplCardSequence: split chained icon-counter assignment into ordered initializations. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: replace source-line and object-header size literals with sizeof. RESTORED; .text: 53564 -> 53564 bytes, 2 differing bytes.
- src/scene/setting/AOSS: replace socket cleanup goto with a structured status result. RESTORED; .rela.data; .rela.text; .text: 16192 -> 16184 bytes, 12282 differing bytes.

Relocation comparison now resolves defined symbols to section plus address and undefined symbols to external name. Compiler-generated local names and symbol-size metadata do not affect linked bytes. Recheck the two text-identical control-flow trials with this normalization.

- src/scene/cardSequence/iplCardSequence: replace pollCardSlot exit goto with return, checking resolved relocations. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: remove comma expression from reportCardThreadError, checking resolved relocations. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: replace line-table entry size with sizeof(SrcLineEntry). KEPT; all allocated sections and relocations identical.
- src/scene/setting/AOSS: replace checksum carrier with reversed scalar declaration order. RESTORED; .text: 16192 -> 16192 bytes, 16 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after AOSSKeySchedule schedule;. RESTORED; .text: 16192 -> 16192 bytes, 16 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after u32 firstValue;. RESTORED; .text: 16192 -> 16192 bytes, 22 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after u8* state;. RESTORED; .text: 16192 -> 16192 bytes, 22 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after u32 controlFlags;. RESTORED; .text: 16192 -> 16192 bytes, 34 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after u32 dataLength;. RESTORED; .text: 16192 -> 16192 bytes, 56 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier after int result;. RESTORED; .text: 16192 -> 16192 bytes, 56 differing bytes.
- src/scene/setting/AOSS: flatten checksum carrier into a block around decryption and CRC validation. RESTORED; .text: 16192 -> 16192 bytes, 56 differing bytes.
- src/channelScript/CHANSVm: replace object free sizes with the aligned object-header size used for allocation. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: use CARD_ICON_MAX for the final icon boundary. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with accumulatorGetPropertyName. RESTORED; .text: 53564 -> 53564 bytes, 58 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with pAccLoadStringConst. RESTORED; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with pAccLogNot. RESTORED; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with pAccLoadIndirect. RESTORED; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with accumulatorGetPropertyName, pAccLoadStringConst. RESTORED; .text: 53564 -> 53564 bytes, 58 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma while sharing accumulator pointer with pAccLogNot, pAccLoadStringConst, pAccLoadIndirect, pAccStoreIndirect, accumulatorGetPropertyName, accumulatorSetIndex, accumulatorDeleteIndirect. RESTORED; .text: 53564 -> 53564 bytes, 58 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma with case-local u32 propertyIndex;, u32 foundEntry;. RESTORED; .text: 53564 -> 53564 bytes, 72 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma with case-local u32 arraySize;. RESTORED; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/channelScript/CHANSVm: remove lifetime pragma with case-local u32 propertyIndex;, u32 foundEntry;, CHANSVmErr propertyResult;. RESTORED; .text: 53564 -> 53564 bytes, 209 differing bytes.
- src/scene/setting/AOSS: replace six printable-key/SSID scan gotos with loop breaks. RESTORED; .text: 16192 -> 16192 bytes, 256 differing bytes.
- src/channelScript/CHANSVm: move binary operand deletion results out of condition assignments. KEPT; all allocated sections and relocations identical.
- src/scene/setting/AOSS: replace request-record buffer initialization size with sizeof. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: replace mount-result label dispatch with nested conditions. RESTORED; compile failed.
- src/scene/cardSequence/iplCardSequence: replace mount-result gotos with nested conditions, selecting the definition rather than its prototype. RESTORED; .rela.text; .text: 9852 -> 9848 bytes, 4394 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after u32 flags = 0;. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after AOSSConfigRecord* configRecord;. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after AOSSStoredConfig* wep40Config;. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after AOSSStoredConfig* wep104Config;. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after AOSSStoredConfig* tkipConfig;. RESTORED; .text: 16192 -> 16192 bytes, 12 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after AOSSStoredConfig* aesConfig;. RESTORED; .text: 16192 -> 16192 bytes, 14 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after u8* networkSettings;. RESTORED; .text: 16192 -> 16192 bytes, 23 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after u32 length;. RESTORED; .text: 16192 -> 16192 bytes, 23 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after int result;. RESTORED; .text: 16192 -> 16192 bytes, 23 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with option cursor declared after s32 optionRemaining;. RESTORED; .text: 16192 -> 16192 bytes, 15 differing bytes.
- src/scene/setting/AOSS: remove optimizer pragma with direct response-type table access. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/cardSequence/iplCardSequence: replace command-message bitfield union with explicit field masks. RESTORED; .text: 9852 -> 9852 bytes, 6 differing bytes.
- src/channelScript/CHANSVm: replace string conversion failure goto with return in CHANSVmConvertToStrFromInt. RESTORED; .text: 53564 -> 53564 bytes, 10 differing bytes.
- src/channelScript/CHANSVm: replace string conversion failure goto with return in CHANSVmConvertToStrFromFloat. RESTORED; .text: 53564 -> 53564 bytes, 10 differing bytes.
- src/scene/setting/AOSS: replace reply payload byte offset with its typed payload field. KEPT; all allocated sections and relocations identical.
- src/scene/setting/AOSS: express reply option header length with offsetof instead of summing field sizes. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: replace reused class-size variable with named source-line count and table end. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: use a while loop for separately initialized icon counters. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: remove unreachable break after the symbol-opcode error return. KEPT; all allocated sections and relocations identical.
- src/scene/setting/AOSS: expand compact protocol jump conditions into normal blocks. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: name per-frame icon bytes separately from the texture palette size. KEPT; all allocated sections and relocations identical.
- src/channelScript/CHANSVm: retest pragma removal on the retained cleanups using resolved relocation destinations. RESTORED; .text: 53564 -> 53564 bytes, 41 differing bytes.
- src/scene/setting/AOSS: retest pragma removal on the retained cleanups using resolved relocation destinations. RESTORED; .text: 16192 -> 16192 bytes, 8 differing bytes.
- src/scene/cardSequence/iplCardSequence: retest pragma removal on the retained cleanups using resolved relocation destinations. RESTORED; .rela.data; .rela.text; .text: 9852 -> 9848 bytes, 5438 differing bytes.
- src/channelScript/CHANSVm: document retained compiler requirements. KEPT; all allocated sections and relocations identical.
- src/scene/setting/AOSS: document retained compiler requirements and keep two-space protocol indentation. KEPT; all allocated sections and relocations identical.
- src/scene/cardSequence/iplCardSequence: document retained compiler requirements. KEPT; all allocated sections and relocations identical.

## Retained result

72 recorded compiler trials: 18 retained, 54 restored, including one failed compilation. Trials include cumulative improvements and final documentation checks.

CHANSVm: source-line table size uses sizeof(SrcLineEntry), with separate lineBlockCount and lineTableEnd. Object free sizes use the same VM_ALIGN(sizeof(CHANSVmObjHdr)) as allocation. Operand deletion assignments are normal statements. Removed three obsolete size TODOs and an unreachable break.

AOSS: request initialization uses sizeof(requestRecords). Option headers use offsetof(AOSSReplyOption, fields.payload), and the payload cursor uses the typed field. Expanded four compact protocol jump conditions.

iplCardSequence: replaced the polling exit goto with return; removed the error-path comma expression; split icon counter initialization into a normal while loop; named iconFrameSize for frame bytes; replaced the last-frame literal with CARD_ICON_MAX - 1.

All three function pragmas remain. CHANSVm default lifetime splitting changes 24 instructions; AOSS default optimization swaps the search cursor and table-base registers in eight instructions; cardThreadMain constant propagation folds the response into ori and removes the target register insert. Declaration, scope, pointer-sharing and response-local alternatives failed exact comparison. Each pragma now has one compiler-requirement comment.

AOSS checksum fields remain grouped: scalar replacements change the checksum/key-state register allocation, even at equal instruction count. Legacy select descriptor and timeout stores remain; deleting the unused timeout removes two target stores. Both requirements have one-line comments. Remaining shared card-state placeholder fields were not renamed because their header has consumers outside this assignment. Structured mount-result, validation and conversion rewrites changed code and were restored. No new workaround was introduced.

The first mount-result trial selected a forward declaration and failed compilation; the corrected definition-only trial compiled but removed one target instruction. Both were restored. The initial checksum-placement harness assertion happened before any source write and was corrected before running those trials.

## Final verification

Ran the requested gate once over all three units with --quick. Full 43U build passed. Pools identical: CHANSVm 125/125, AOSS 1/1, iplCardSequence 43/43.

Instruction-exact counts unchanged: CHANSVm 233/233; AOSS 21/21; iplCardSequence 30/30. Code/data: 53564/6904, 16192/2800, 9852/1496 bytes respectively, all matched and fully linked. Every owned section is 100%. No configure.py or header changes.

Fresh focused ctxdiff checks all have identical counts and diffs 0: CHANSVmAddExe, CHANSVmStep, AOSS_Init_old, AOSSApplyAuthOptions, AOSSDecryptMessage, pollCardSlot, reportCardThreadError, cardThreadMain, loadCardFileIcons.

Every allocated object section and resolved relocation is identical to the initial source-object snapshot. Global report measures are identical to the initial complete report. Report regeneration and completion checker passed: DECOMPLETE_OK. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.

GATE PASS: 0 regressions, 0 forbidden patterns, 0 readability warnings. Git diff --check passed. Gate transcript: /tmp/cleanup-c1-gate.log. Trial utility and initial snapshots: /tmp/cleanup-c1-*.

origin/main advanced two commits through another session during this work. This worker did not fetch, merge or rebase; the branch remains based on f1db6b65 for parent integration.

Source commits: cb31c2d7 CHANSVm; ee720b82 AOSS; 673e11b5 iplCardSequence. Each source file was committed separately after verification.
