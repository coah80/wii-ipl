# sol-audit integrity audit

Worktree `data-d12`, branch `agent/w1009/data-d12-audit`, baseline `c723136f`.
The first full 43U build passed. DOL SHA1 was
`26116613f624061ba99c8d1a299aaa6efa85670d`.

Each retained edit must preserve every allocated section and resolved relocation
against the starting object, exact-name objdiff scores, instruction comparisons,
string pools, the full DOL hash, and the final gate. Existing non-exact functions
in BS2Mach and CHANSVm must preserve their starting bytes.

Audited 21 variables: 11 carriers and 10 legitimate aggregates. Removed seven
carriers and expressed two legitimate FAT-hint snapshots with their existing
type. Four carriers remain unchanged after unsuccessful trials: Board, FAT12,
WAD import and PUD matching. Their remaining compiler differences are recorded
below. No excluded function range was edited.

## Candidate verdicts

Locations refer to the starting source scan. Each function-local aggregate is
judged by its actual uses and receiving interfaces.

| Location and variable | Verdict | Action | Result |
| --- | --- | --- | --- |
| `src/scene/board/iplBoard.cpp:432 state` | carrier | Restore after 40 declaration orders and allocator capture | Blocked: ordinary interrupt states become r24 instead of SP+8/+0x10/+0x14; frame 0x90 instead of 0xA0 |
| `libs/RVLMiddleware/eZiText/src/clib/zikorean.c:30 state` | carrier | Replace with reverse-order ordinary locals | Exact 619/619 instructions, diffs 0; whole object unchanged |
| `libs/RVLMiddleware/eZiText/src/clib/zi8match.c:116 state` | carrier | Replace with reverse-order ordinary locals | Exact 311/311 instructions, diffs 0; whole object unchanged |
| `libs/RVLMiddleware/eZiText/src/clib/zi8match.c:293 traversal` | carrier | Replace with reverse-order ordinary locals | Exact 363/363 instructions, diffs 0; whole object unchanged |
| `libs/RVLMiddleware/eZiText/src/clib/zi8pud2.c:60 match` | carrier | Restore after rejecting an exact but unread local copy | Blocked: SP+0x24 is a dead workspace-pointer store; honest removal produces 353/354 instructions |
| `libs/RVL_SDK/src/fa/pf_fat12.c:178 state` | carrier | Restore after 49 compiled trials and allocator capture | Blocked: target offset=r31/error=r28, ordinary locals offset=r28/error=r31; best 23 differences in 155/155 instructions |
| `libs/RVL_SDK/src/fa/pf_path.c:421 work` | carrier | Use actual 13-byte SFN buffer and separate matched_end | Exact 87/87 instructions, diffs 0; whole object unchanged |
| `libs/RVL_SDK/src/fa/pf_file.c:1876 saved_hint` | legit | Use existing three-word PFFILE_FAT_HINT | Real state passed to PFFAT APIs; exact fadjust 115/115 instructions, diffs 0 |
| `libs/RVL_SDK/src/fa/pf_file.c:1926 saved_hint` | legit | Use existing three-word PFFILE_FAT_HINT | Same real hint state; exact finfo 91/91 instructions, diffs 0 |
| `libs/RVL_SDK/src/fa/pf_file.c:101 last_access_data` | legit | Retain | Nested member of the real file type, shared FAT-hint/error-state storage |
| `libs/RVL_SDK/src/fa/pf_dir.c:104 volume_state` | legit | Retain | Nested member of global volume state, typed current-volume array view |
| `src/BS2/BS2Mach.c:1331 loaderRead` | carrier | Separate address/length/offset before titleCode | Whole object unchanged; BS2Tick retains its pre-existing 71 instruction differences, 1940/1940 instructions |
| `src/keyboard/tiCandidateBox.cpp:296 predictionState` | legit | Retain | Actual mode/enabled command record; tiInputForm commands 29 and 31 consume and populate both fields |
| `src/system/iplSystem.cpp:530 blankNameStorage` | carrier | Use ordinary SCOwnerNickname | Exact init 689/689 instructions, diffs 0; whole object unchanged |
| `libs/RVL_SDK/src/kpad/KPAD.c:72 dpdState` | legit | Retain | Nested member of KPADInside holding actual sensor objects and candidate pairs |
| `libs/RVL_SDK/src/fs/fs.c:64 args` | legit | Retain | Nested tagged callback payload union used by asynchronous FS operations |
| `libs/RVL_SDK/src/wad/wad.c:3499 parts` | carrier | Restore after 40 declaration orders | Blocked: target clears 0x28 bytes at SP+0x40; independent scalar objects cannot reproduce that contiguous clear safely |
| `libs/RVL_SDK/src/wad/wad.c:1937 fields` | legit | Retain | Nested file-info view overlaying actual FAFileInfo storage |
| `src/channelScript/CHANSVm.c:5503 unpackBuf` | legit | Retain | Single 64-bit value viewed as two words during blob decoding |
| `src/channelScript/CHANSVm.c:347 u` | carrier | Separate chunk offset and result pointer | CHANSVmNewObjData exact 96/96 instructions, diffs 0; every caller and partial function unchanged |
| `src/system/TVRC.cpp:38 commands` | legit | Retain | Nested command-offset table in the real TVRC database file format |

## Prior evidence

Read sol-common.md, brief-v2.md and all levers. Consulted existing attempts for
the affected units before editing. The current integrity rule overrides older
logs that accepted carriers as search state.

Board: rx65 and grok-board already tested both flat declaration directions,
reference aliases, invented one-field wrappers, inline out-parameter guards,
real interrupt guards and single-interrupt-state reuse. These do not reproduce
the three target stack homes. Do not repeat them as new ideas. grok-board's
volatile diagnostic matched but was rejected because the target has no repeated
volatile read.

PUD: allhands-ezitext-pud-packed-header established that the incoming work
pointer store at SP+0x24 is never read or passed onward. Plain reverse-order
locals also reproduce that store, but the resulting workspace local is unread.
That initial exact edit was rejected and reverted under sol-common.md rule 4.

FAT12: fz3 had exhaustively tested the five flat-local permutations, callback
scopes, offset typing and a FAT-flush helper. Its current carrier matched a
register-allocation tie; new trials must explore additional source shapes.

## Retained source and type evidence

eZiText scalar declarations in reverse field order reproduce the target stack
homes without aggregate storage. Korean, secondary character and phonetic
matching retain all instruction bytes and data. The PUD exception is discussed
below and is not part of the retained changes.

PFPATH_cmpName uses a genuine SFN buffer. PF_DIR_ENT.short_name is declared as
13 bytes in libs/RevoEX/include/private/vf/PrFILE2/fatfs/pf_entry.h:15, and
pf_entry/pf_dir callers pass that field. An 8.3 name contains at most 12 bytes
plus its terminator. Appending a dot to a name without one also fits; the longest
volume-label name is 11 bytes. A standalone 16-byte buffer lands at SP+0x10,
three instruction operands away from the target SP+0xC. The actual 13-byte
capacity puts the buffer at SP+0xC and matched_end at SP+8, without alignment
attributes or padding.

The two saved_hint variables are snapshots of one real FAT-hint value. The
existing PFFILE_FAT_HINT at pf_file.c:9 and PFFAT_HINT at pf_fat.c:80 both have
chain_index, cluster and previous_cluster. PFFAT_InitHint at pf_fat.c:1907 clears
all three words; PFFAT_InitFFD consumes previous_cluster. pf_file.c passes
&file->hint to these APIs and places it in ffd.p_hint. The imported PF_FAT_HINT
view declares only two words, so its third word is viewed through
last_access_data.last_access.chain_index. Using the already-defined
PFFILE_FAT_HINT makes this single three-word API state explicit. fadjust keeps
the hint at SP+0xC/+0x10/+0x14 and cursor at SP+0x18 through SP+0x24 in a 0x30
frame; finfo keeps its hint at SP+8/+0xC/+0x10 and cursor at SP+0x18 through
SP+0x24 in a 0x40 frame. No shared type or field layout changed.

BS2Tick's address, length and offset are separate Apploader output parameters.
Moving the reverse-order declarations immediately after interruptsEnabled
preserves their starting offsets and the entire original source object. BS2Tick
was already partial and remains partial; this audit does not claim a new match.

VmReserveChunkEntry's offset and returned ChunkEntry pointer have independent
lifetimes. Their old union was storage reuse, not type punning of one value.
Separate chunkOffset and entry locals, with entry declared after chunkIdx,
preserve every inline expansion. The exhaustion path now assigns vmNull to
entry directly instead of constructing it by writing the integer union member.

blankNameStorage wraps a single SCOwnerNickname without a separate interface or
meaning. The ordinary SCOwnerNickname local gives identical init code.

## Carriers retained after failed removal

### Board::appendRecord

Forty compiled declaration orders and a fresh confirmation produced a best
44 differing instructions, with 283/283 instructions. The ordinary-local frame
is 0x90; the target is 0xA0. The target stores recordInterrupts at SP+8,
waitInterrupts at SP+0x10 and slotInterrupts at SP+0x14. Other target homes are
dataSize SP+0xC, times SP+0x18/+0x1C/+0x20, gameCode SP+0x24, id SP+0x28,
type SP+0x30, date SP+0x38 and key SP+0x48.

The best ordinary-local allocator capture assigns all three non-overlapping
interrupt states to r24: virtual r38 slotInterrupts (18 neighbors), r39
recordInterrupts (23 neighbors), and r40 waitInterrupts (19 neighbors). Each is
simplified and colored without spilling. Declaration permutations do not force
their three target stack homes. Prior scoped/reference/guard variants were
already unsuccessful or forbidden. Restored the original source and object.

Diagnostic diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-audit.iplBoard.diff.
Capture: /tmp/sol-audit-board-capture; its emitted allocated sections agree with
the ordinary compiler build of the captured source.

### PFFAT12_ReadFATEntryWithBuf

Forty-nine compiled trials covered separate locals, real FAT-sector and
read-sector helpers, scoped copy-loop counters, 31 combinations of named actual
mask/sector/callback values, and error-value lifetime/type variants. The best
has 23 differences in 155/155 instructions and the correct 0x30 frame. The
remaining problem is register ordering, not stack offsets: target offset=r31,
err=r28, current_fat=r29, sector=r30; flat offset=r28, err=r31, with the latter
two unchanged.

The captured graph maps virtual r37 offset to r28, r38 err to r31, r39
current_fat to r29 and r40 sector to r30. Compiler-created @692/r41 and
@690/r42 also use r31 at other lifetimes. Regsim reproduces all 84 captured
assignments. A search constrained to the five source locals reaches only two
of four desired colors; a nominal four-of-four search requires permuting
parameters and compiler-created temporaries, which source declaration order
cannot do. Real source-shape changes either retain the 23 differences or add
instructions. Restored the carrier rather than use volatile casts, register
keywords or artificial storage.

Diagnostic diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-audit.pf_fat12.diff.
Capture: /tmp/sol-audit-fat12-capture; constrained simulator:
/tmp/sol-audit-regsim.py.

### WADImportDVDExForBS

Forty successfully compiled declaration orders and a fresh confirmation have
262/263 instructions, 223 differences and a 0xE0 frame instead of target 0x100.
An initial batch failed because of a field-prefix substitution error; those
failures do not count as compiled effort.

The target clears a contiguous 0x28-byte region at SP+0x40. Its field homes are
type 0x40, cidxMode 0x44, version 0x46, certSize 0x48, certificates 0x4C,
crlSize 0x50, crls 0x54, ticketSize 0x58, ticket 0x5C, tmdSize 0x60 and tmd
0x64. Header is at SP+0x20 and fileInfo at SP+0x68. Flat metadata values
become registers r31/r30/r29/r28/r27/r26/r22; type is at SP+0x20, header at
SP+0x40 and fileInfo at SP+0x60. Their independent object sizes cannot safely
support the target's one 40-byte memset. Per-object initialization also exposes
cidxMode=0 and folds the target's conditional mask branches. A diagnostic
memset through &type cannot justify a retained change because it writes past
that scalar object. Restored the entire original WAD source and object.

Diagnostic diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-audit.wad.diff.

### Zi8MatchPUDdata_ZHS

The target instruction at function offset 0x3C is stw r31,0x24(r1). SP+0x24
is never read or passed out; the working pointer remains r31, and fallback is
at SP+0x20. Reverse-order plain locals reproduce all 354 instructions only
by retaining an unread workspace copy. That candidate was initially committed
as 80d7290c, then rejected and reverted in 5b0f57b6.

Four subsequent compiled trials removed the dead copy, used a live void-pointer
alias throughout, used a live typed alias throughout, or scoped a live typed
alias to the language-table lookup. Removing the copy gives 353/354 instructions
and omits the required store. Live aliases give 385/354 or 366/354 instructions
because they change the actual workspace loads and stack homes. No acceptable
use was found for the target's unread SP+0x24 word. Restored the carrier and
every original object byte; no replacement dead local is retained.

Best source without the dead copy:
/mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-audit.zi8pud2.diff.

## Compiled trials

Counts below are differing instructions against the target, with equal size
required for exactness. An additional comparison covers every allocated section
and resolved relocation against the starting object.

| Trial | Change or reason | Measurement |
| --- | --- | --- |
| PFPATH_cmpName-flat-reverse | Separate ordinary locals; reverse declaration order | PFPATH_cmpName: 3/87, insns 87/87; baseline sections and relocations different |
| PFPATH_cmpName-flat-field | Separate ordinary locals; original field order | PFPATH_cmpName: 3/87, insns 87/87; baseline sections and relocations different |
| BS2Tick-flat-reverse | Separate ordinary locals; reverse declaration order | BS2Tick: 105/1940, insns 1940/1940; baseline sections and relocations different |
| BS2Tick-flat-field | Separate ordinary locals; original field order | BS2Tick: 105/1940, insns 1940/1940; baseline sections and relocations different |
| init__Q23ipl6SystemFiPPc-flat-reverse | Separate ordinary locals; reverse declaration order | init__Q23ipl6SystemFiPPc: 0/689, insns 689/689; baseline sections and relocations identical |
| PFFILE_fadjust-flat-reverse | Separate ordinary locals; reverse declaration order | PFFILE_fadjust: 87/115, insns 115/115; baseline sections and relocations different |
| PFFILE_fadjust-flat-field | Separate ordinary locals; original field order | PFFILE_fadjust: 87/115, insns 115/115; baseline sections and relocations different |
| PFFILE_finfo-flat-reverse | Separate ordinary locals; reverse declaration order | PFFILE_finfo: 58/91, insns 89/91; baseline sections and relocations different |
| PFFILE_finfo-flat-field | Separate ordinary locals; original field order | PFFILE_finfo: 58/91, insns 89/91; baseline sections and relocations different |
| Zi8GetKoreanCandidates-flat-reverse | Flat scalar confirmation; existing target has memory-backed aggregate members | Zi8GetKoreanCandidates: 0/619, insns 619/619; baseline sections and relocations identical |
| Zi8SecMatchChar-flat-reverse | Flat scalar confirmation; existing target has memory-backed aggregate members | Zi8SecMatchChar: 0/311, insns 311/311; baseline sections and relocations identical |
| Zi8MatchPhonetic-flat-reverse | Flat scalar confirmation; existing target has memory-backed aggregate members | Zi8MatchPhonetic: 0/363, insns 363/363; baseline sections and relocations identical |
| Zi8MatchPUDdata_ZHS-flat-reverse | Flat scalar confirmation; existing target has memory-backed aggregate members | Zi8MatchPUDdata_ZHS: 0/354, insns 354/354; baseline sections and relocations identical |
| PFFAT12_ReadFATEntryWithBuf-flat-reverse | Flat scalar confirmation; existing target has memory-backed aggregate members | PFFAT12_ReadFATEntryWithBuf: 30/155, insns 155/155; baseline sections and relocations different |
| PFFAT12_ReadFATEntryWithBuf-flat-field | Flat scalar confirmation; existing target has memory-backed aggregate members | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155; baseline sections and relocations different |
| VmReserveChunkEntry-separate | Use separate offset and result pointer, preserving the NULL return on exhaustion | CHANSVmNewObjData: 11/96, insns 96/96; baseline sections and relocations different |
| PFPATH_cmpName-array-align4 | Natural byte buffer layout without aggregate padding | BUILD FAIL |
| PFPATH_cmpName-array-align1 | Natural byte buffer layout without aggregate padding | BUILD FAIL |
| PFPATH_cmpName-array-align2 | Natural byte buffer layout without aggregate padding | BUILD FAIL |
| PFPATH_cmpName-array-near-copy | Natural byte buffer layout without aggregate padding | BUILD FAIL |
| PFPATH_cmpName-byte-array-align1 | Inspect target byte-array alignment and declaration scope | PFPATH_cmpName: 33/87, insns 88/87; baseline sections and relocations different |
| PFPATH_cmpName-byte-array-align2 | Inspect target byte-array alignment and declaration scope | PFPATH_cmpName: 33/87, insns 88/87; baseline sections and relocations different |
| PFPATH_cmpName-byte-array-align4 | Inspect target byte-array alignment and declaration scope | PFPATH_cmpName: 33/87, insns 88/87; baseline sections and relocations different |
| PFPATH_cmpName-byte-array-align8 | Inspect target byte-array alignment and declaration scope | PFPATH_cmpName: 33/87, insns 88/87; baseline sections and relocations different |
| PFPATH_cmpName-short-name-buffer13 | Inspect target byte-array alignment and declaration scope | PFPATH_cmpName: 0/87, insns 87/87; baseline sections and relocations identical |
| fat12-flat-for-mwdbg | Capture the actual flat scalar allocator tie before selecting source shapes | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155; baseline sections and relocations different |
| VmReserveChunkEntry-order-0 | Separate search offset and actual return pointer; declaration order u32 idx;,u32 chunkOffset;,ChunkEntry* entry;,ChunkEntry* chunk;,u32 chunkIdx; | CHANSVmNewObjData: 11/96, insns 96/96; baseline sections and relocations different |
| VmReserveChunkEntry-order-1 | Separate search offset and actual return pointer; declaration order u32 idx;,u32 chunkOffset;,ChunkEntry* entry;,u32 chunkIdx;,ChunkEntry* chunk; | CHANSVmNewObjData: 11/96, insns 96/96; baseline sections and relocations different |
| VmReserveChunkEntry-order-2 | Separate search offset and actual return pointer; declaration order u32 idx;,u32 chunkOffset;,ChunkEntry* chunk;,ChunkEntry* entry;,u32 chunkIdx; | CHANSVmNewObjData: 11/96, insns 96/96; baseline sections and relocations different |
| VmReserveChunkEntry-order-3 | Separate search offset and actual return pointer; declaration order u32 idx;,u32 chunkOffset;,ChunkEntry* chunk;,u32 chunkIdx;,ChunkEntry* entry; | CHANSVmNewObjData: 0/96, insns 96/96; baseline sections and relocations identical |
| PFFILE_fadjust-copy-chain | Ordinary state snapshots copied independently through standard memcpy | PFFILE_fadjust: 118/115, insns 122/115, baseline differences 118; baseline sections and relocations different |
| PFFILE_fadjust-copy-both | Ordinary state snapshots copied independently through standard memcpy | PFFILE_fadjust: 119/115, insns 122/115, baseline differences 119; baseline sections and relocations different |
| PFFILE_fadjust-copy-chain-save | Ordinary state snapshots copied independently through standard memcpy | PFFILE_fadjust: 81/115, insns 117/115, baseline differences 81; baseline sections and relocations different |
| PFFILE_fadjust-copy-chain-restore | Ordinary state snapshots copied independently through standard memcpy | PFFILE_fadjust: 116/115, insns 120/115, baseline differences 116; baseline sections and relocations different |
| PFFILE_finfo-copy-chain | Ordinary state snapshots copied independently through standard memcpy | PFFILE_finfo: 55/91, insns 97/91, baseline differences 55; baseline sections and relocations different |
| PFFILE_finfo-copy-both | Ordinary state snapshots copied independently through standard memcpy | PFFILE_finfo: 69/91, insns 97/91, baseline differences 69; baseline sections and relocations different |
| PFFILE_finfo-copy-chain-save | Ordinary state snapshots copied independently through standard memcpy | PFFILE_finfo: 51/91, insns 93/91, baseline differences 51; baseline sections and relocations different |
| PFFILE_finfo-copy-chain-restore | Ordinary state snapshots copied independently through standard memcpy | PFFILE_finfo: 40/91, insns 95/91, baseline differences 40; baseline sections and relocations different |
| BS2Tick-baseline-offsets | Measure changed stack offsets against starting bytes, independently of existing target mismatch | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-0 | Plain loader output order offset,length,address before u32 titleCode; | BS2Tick: 85/1940, insns 1940/1940, baseline differences 14; baseline sections and relocations different |
| BS2Tick-locals-1 | Plain loader output order offset,length,address before u8 titleCharacters[4]; | BS2Tick: 85/1940, insns 1940/1940, baseline differences 14; baseline sections and relocations different |
| BS2Tick-locals-2 | Plain loader output order offset,length,address before DVDFileInfo bannerFile; | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-3 | Plain loader output order offset,length,address before s32 status; | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-4 | Plain loader output order offset,length,address before switch (State) { | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-5 | Plain loader output order offset,address,length before u32 titleCode; | BS2Tick: 93/1940, insns 1940/1940, baseline differences 22; baseline sections and relocations different |
| BS2Tick-locals-6 | Plain loader output order offset,address,length before u8 titleCharacters[4]; | BS2Tick: 93/1940, insns 1940/1940, baseline differences 22; baseline sections and relocations different |
| BS2Tick-locals-7 | Plain loader output order offset,address,length before DVDFileInfo bannerFile; | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-8 | Plain loader output order offset,address,length before s32 status; | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-9 | Plain loader output order offset,address,length before switch (State) { | BS2Tick: 105/1940, insns 1940/1940, baseline differences 34; baseline sections and relocations different |
| BS2Tick-locals-10 | Plain loader output order length,offset,address before u32 titleCode; | BS2Tick: 93/1940, insns 1940/1940, baseline differences 22; baseline sections and relocations different |
| BS2Tick-locals-11 | Plain loader output order length,offset,address before u8 titleCharacters[4]; | BS2Tick: 93/1940, insns 1940/1940, baseline differences 22; baseline sections and relocations different |
| BS2Tick-locals-12 | Plain loader output order length,offset,address before DVDFileInfo bannerFile; | BS2Tick: 90/1940, insns 1940/1940, baseline differences 19; baseline sections and relocations different |
| BS2Tick-locals-13 | Plain loader output order length,offset,address before s32 status; | BS2Tick: 90/1940, insns 1940/1940, baseline differences 19; baseline sections and relocations different |
| BS2Tick-locals-14 | Plain loader output order length,offset,address before switch (State) { | BS2Tick: 90/1940, insns 1940/1940, baseline differences 19; baseline sections and relocations different |
| BS2Tick-locals-15 | Plain loader output order length,address,offset before u32 titleCode; | BS2Tick: 86/1940, insns 1940/1940, baseline differences 15; baseline sections and relocations different |
| BS2Tick-locals-16 | Plain loader output order length,address,offset before u8 titleCharacters[4]; | BS2Tick: 86/1940, insns 1940/1940, baseline differences 15; baseline sections and relocations different |
| BS2Tick-locals-17 | Plain loader output order length,address,offset before DVDFileInfo bannerFile; | BS2Tick: 97/1940, insns 1940/1940, baseline differences 26; baseline sections and relocations different |
| BS2Tick-locals-18 | Plain loader output order length,address,offset before s32 status; | BS2Tick: 97/1940, insns 1940/1940, baseline differences 26; baseline sections and relocations different |
| BS2Tick-locals-19 | Plain loader output order length,address,offset before switch (State) { | BS2Tick: 97/1940, insns 1940/1940, baseline differences 26; baseline sections and relocations different |
| BS2Tick-locals-20 | Plain loader output order address,offset,length before u32 titleCode; | BS2Tick: 86/1940, insns 1940/1940, baseline differences 15; baseline sections and relocations different |
| BS2Tick-locals-21 | Plain loader output order address,offset,length before u8 titleCharacters[4]; | BS2Tick: 86/1940, insns 1940/1940, baseline differences 15; baseline sections and relocations different |
| BS2Tick-locals-22 | Plain loader output order address,offset,length before DVDFileInfo bannerFile; | BS2Tick: 98/1940, insns 1940/1940, baseline differences 27; baseline sections and relocations different |
| BS2Tick-locals-23 | Plain loader output order address,offset,length before s32 status; | BS2Tick: 98/1940, insns 1940/1940, baseline differences 27; baseline sections and relocations different |
| BS2Tick-locals-24 | Plain loader output order address,offset,length before switch (State) { | BS2Tick: 98/1940, insns 1940/1940, baseline differences 27; baseline sections and relocations different |
| BS2Tick-locals-25 | Plain loader output order address,length,offset before u32 titleCode; | BS2Tick: 71/1940, insns 1940/1940, baseline differences 0; baseline sections and relocations identical |
| PFFILE_fadjust-real-fat-hint | The FAT implementation actually accepts a three-word chain_index/cluster/previous_cluster hint at &file->hint | PFFILE_fadjust: 0/115, insns 115/115, baseline differences 0; baseline sections and relocations identical |
| PFFILE_finfo-real-fat-hint | The FAT implementation actually accepts a three-word chain_index/cluster/previous_cluster hint at &file->hint | PFFILE_finfo: 0/91, insns 91/91, baseline differences 0; baseline sections and relocations identical |
| Board-flat-order-0 | Ordinary record and interrupt locals; declaration order recordInterrupts,recordDate,recordSecond,slotInterrupts,waitInterrupts,recordKey,recordGC,cdbId,recordMin,dataSize,recordType[8],recordHour | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 53/283, insns 283/283, baseline differences 53; baseline sections and relocations different |
| Board-flat-order-1 | Ordinary record and interrupt locals; declaration order recordInterrupts,recordDate,recordHour,recordGC,recordMin,recordKey,dataSize,recordSecond,recordType[8],cdbId,waitInterrupts,slotInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 54/283, insns 283/283, baseline differences 54; baseline sections and relocations different |
| Board-flat-order-2 | Ordinary record and interrupt locals; declaration order recordGC,recordKey,recordType[8],dataSize,slotInterrupts,recordDate,recordInterrupts,recordHour,recordSecond,recordMin,cdbId,waitInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-3 | Ordinary record and interrupt locals; declaration order recordType[8],recordInterrupts,waitInterrupts,recordMin,recordDate,recordHour,recordKey,cdbId,recordGC,slotInterrupts,dataSize,recordSecond | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 54/283, insns 283/283, baseline differences 54; baseline sections and relocations different |
| Board-flat-order-4 | Ordinary record and interrupt locals; declaration order recordGC,recordMin,waitInterrupts,dataSize,recordHour,recordDate,recordSecond,recordType[8],recordInterrupts,cdbId,recordKey,slotInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-5 | Ordinary record and interrupt locals; declaration order recordGC,recordSecond,cdbId,recordDate,recordType[8],recordKey,waitInterrupts,recordMin,recordHour,dataSize,recordInterrupts,slotInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-6 | Ordinary record and interrupt locals; declaration order dataSize,recordHour,recordSecond,recordGC,waitInterrupts,recordMin,recordDate,slotInterrupts,cdbId,recordKey,recordType[8],recordInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-7 | Ordinary record and interrupt locals; declaration order recordType[8],recordDate,recordMin,recordSecond,cdbId,recordInterrupts,waitInterrupts,recordKey,recordHour,dataSize,slotInterrupts,recordGC | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 54/283, insns 283/283, baseline differences 54; baseline sections and relocations different |
| Board-flat-order-8 | Ordinary record and interrupt locals; declaration order recordInterrupts,slotInterrupts,recordKey,cdbId,recordType[8],recordSecond,recordDate,waitInterrupts,recordMin,recordHour,recordGC,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 57/283, insns 283/283, baseline differences 57; baseline sections and relocations different |
| Board-flat-order-9 | Ordinary record and interrupt locals; declaration order dataSize,recordSecond,recordKey,recordMin,recordDate,recordInterrupts,recordHour,recordGC,slotInterrupts,recordType[8],waitInterrupts,cdbId | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-10 | Ordinary record and interrupt locals; declaration order recordGC,recordKey,recordMin,slotInterrupts,cdbId,recordDate,recordSecond,dataSize,waitInterrupts,recordHour,recordInterrupts,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 45/283, insns 283/283, baseline differences 45; baseline sections and relocations different |
| Board-flat-order-11 | Ordinary record and interrupt locals; declaration order recordKey,slotInterrupts,recordHour,recordDate,cdbId,dataSize,recordType[8],recordGC,recordInterrupts,recordSecond,recordMin,waitInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-12 | Ordinary record and interrupt locals; declaration order dataSize,recordSecond,cdbId,waitInterrupts,recordGC,recordHour,recordMin,slotInterrupts,recordDate,recordType[8],recordInterrupts,recordKey | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-13 | Ordinary record and interrupt locals; declaration order recordMin,recordKey,waitInterrupts,cdbId,recordHour,recordSecond,recordGC,recordType[8],slotInterrupts,recordInterrupts,recordDate,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-14 | Ordinary record and interrupt locals; declaration order recordMin,dataSize,recordSecond,recordType[8],recordKey,recordDate,cdbId,waitInterrupts,recordHour,recordGC,recordInterrupts,slotInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-15 | Ordinary record and interrupt locals; declaration order cdbId,recordGC,recordHour,dataSize,slotInterrupts,recordMin,recordDate,recordInterrupts,waitInterrupts,recordKey,recordSecond,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-16 | Ordinary record and interrupt locals; declaration order recordHour,recordType[8],waitInterrupts,recordDate,cdbId,recordMin,recordSecond,recordKey,recordGC,recordInterrupts,slotInterrupts,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-17 | Ordinary record and interrupt locals; declaration order waitInterrupts,slotInterrupts,recordHour,cdbId,recordSecond,recordGC,dataSize,recordInterrupts,recordDate,recordMin,recordKey,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 45/283, insns 283/283, baseline differences 45; baseline sections and relocations different |
| Board-flat-order-18 | Ordinary record and interrupt locals; declaration order recordDate,waitInterrupts,recordType[8],recordSecond,recordMin,recordInterrupts,recordHour,dataSize,recordGC,recordKey,cdbId,slotInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 44/283, insns 283/283, baseline differences 44; baseline sections and relocations different |
| Board-flat-order-19 | Ordinary record and interrupt locals; declaration order recordHour,recordSecond,slotInterrupts,recordType[8],recordInterrupts,recordDate,dataSize,recordKey,waitInterrupts,recordMin,cdbId,recordGC | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-20 | Ordinary record and interrupt locals; declaration order recordType[8],recordInterrupts,slotInterrupts,recordDate,recordGC,recordHour,waitInterrupts,recordMin,recordSecond,recordKey,cdbId,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-21 | Ordinary record and interrupt locals; declaration order recordDate,recordInterrupts,recordMin,dataSize,recordSecond,recordKey,recordHour,recordGC,cdbId,slotInterrupts,recordType[8],waitInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-22 | Ordinary record and interrupt locals; declaration order dataSize,recordGC,recordDate,recordType[8],slotInterrupts,cdbId,waitInterrupts,recordHour,recordKey,recordSecond,recordInterrupts,recordMin | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-23 | Ordinary record and interrupt locals; declaration order dataSize,recordGC,cdbId,recordMin,recordDate,recordInterrupts,recordSecond,recordKey,recordHour,waitInterrupts,slotInterrupts,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-24 | Ordinary record and interrupt locals; declaration order cdbId,slotInterrupts,recordType[8],recordDate,recordHour,recordSecond,waitInterrupts,dataSize,recordInterrupts,recordKey,recordGC,recordMin | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-25 | Ordinary record and interrupt locals; declaration order cdbId,recordGC,recordKey,slotInterrupts,dataSize,recordSecond,recordHour,recordDate,recordMin,recordType[8],waitInterrupts,recordInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-26 | Ordinary record and interrupt locals; declaration order dataSize,waitInterrupts,recordDate,recordInterrupts,recordType[8],recordGC,slotInterrupts,recordHour,recordSecond,recordMin,cdbId,recordKey | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-27 | Ordinary record and interrupt locals; declaration order recordMin,slotInterrupts,waitInterrupts,recordHour,recordType[8],recordKey,recordDate,dataSize,recordSecond,cdbId,recordGC,recordInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-28 | Ordinary record and interrupt locals; declaration order recordMin,recordType[8],cdbId,dataSize,recordHour,waitInterrupts,recordSecond,recordGC,recordDate,slotInterrupts,recordInterrupts,recordKey | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-29 | Ordinary record and interrupt locals; declaration order dataSize,cdbId,waitInterrupts,recordInterrupts,recordKey,recordDate,recordMin,recordGC,recordSecond,recordHour,slotInterrupts,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-30 | Ordinary record and interrupt locals; declaration order recordHour,waitInterrupts,cdbId,recordInterrupts,recordDate,recordSecond,recordGC,recordKey,slotInterrupts,recordType[8],recordMin,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-31 | Ordinary record and interrupt locals; declaration order recordKey,waitInterrupts,recordGC,dataSize,slotInterrupts,recordSecond,recordType[8],recordInterrupts,recordMin,recordHour,cdbId,recordDate | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| fat12-sector-helper-base | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-sector-helper-offset-initialized | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-sector-helper-sector-const | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-sector-helper-typed-sector | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 122/155, insns 156/155, baseline differences 122; baseline sections and relocations different |
| fat12-read-sector-helper-base | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 101/155, insns 159/155, baseline differences 101; baseline sections and relocations different |
| fat12-read-sector-helper-offset-initialized | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 101/155, insns 159/155, baseline differences 101; baseline sections and relocations different |
| fat12-read-sector-helper-sector-const | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 101/155, insns 159/155, baseline differences 101; baseline sections and relocations different |
| fat12-read-sector-helper-typed-sector | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 130/155, insns 160/155, baseline differences 130; baseline sections and relocations different |
| Board-flat-order-32 | Ordinary record and interrupt locals; declaration order slotInterrupts,recordKey,cdbId,waitInterrupts,recordMin,recordGC,recordType[8],dataSize,recordHour,recordDate,recordInterrupts,recordSecond | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| fat12-block-copy-counters-base | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 34/155, insns 155/155, baseline differences 34; baseline sections and relocations different |
| fat12-block-copy-counters-offset-initialized | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 34/155, insns 155/155, baseline differences 34; baseline sections and relocations different |
| fat12-block-copy-counters-sector-const | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 34/155, insns 155/155, baseline differences 34; baseline sections and relocations different |
| fat12-block-copy-counters-typed-sector | Natural FAT sector/flush operation and local scopes, without a carrier | PFFAT12_ReadFATEntryWithBuf: 127/155, insns 156/155, baseline differences 127; baseline sections and relocations different |
| Board-flat-order-33 | Ordinary record and interrupt locals; declaration order recordInterrupts,recordSecond,recordKey,cdbId,recordGC,recordDate,recordHour,waitInterrupts,slotInterrupts,recordType[8],recordMin,dataSize | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 57/283, insns 283/283, baseline differences 57; baseline sections and relocations different |
| Board-flat-order-34 | Ordinary record and interrupt locals; declaration order recordGC,slotInterrupts,recordHour,recordSecond,waitInterrupts,dataSize,recordInterrupts,recordMin,recordKey,cdbId,recordType[8],recordDate | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 45/283, insns 283/283, baseline differences 45; baseline sections and relocations different |
| Board-flat-order-35 | Ordinary record and interrupt locals; declaration order recordType[8],slotInterrupts,recordDate,recordHour,recordInterrupts,cdbId,waitInterrupts,recordMin,dataSize,recordKey,recordGC,recordSecond | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-36 | Ordinary record and interrupt locals; declaration order recordKey,waitInterrupts,recordHour,recordType[8],recordMin,slotInterrupts,dataSize,recordInterrupts,recordSecond,cdbId,recordDate,recordGC | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-37 | Ordinary record and interrupt locals; declaration order recordType[8],cdbId,recordMin,recordKey,waitInterrupts,recordGC,dataSize,recordHour,slotInterrupts,recordInterrupts,recordSecond,recordDate | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| Board-flat-order-38 | Ordinary record and interrupt locals; declaration order recordMin,cdbId,recordKey,recordDate,dataSize,recordSecond,recordType[8],slotInterrupts,recordGC,recordHour,recordInterrupts,waitInterrupts | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 58/283, insns 283/283, baseline differences 58; baseline sections and relocations different |
| Board-flat-order-39 | Ordinary record and interrupt locals; declaration order slotInterrupts,dataSize,waitInterrupts,recordSecond,recordMin,recordDate,recordHour,cdbId,recordInterrupts,recordGC,recordKey,recordType[8] | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 49/283, insns 283/283, baseline differences 49; baseline sections and relocations different |
| WADImportDVDExForBS-locals-0 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-1 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |

The initial WAD batch failed before code generation because the temporary field
rewriter replaced the prefix of `titleMetaSize`. All 40 failed variants were
restored and excluded from compiled-trial counts; the rewriter now matches whole
field names. Raw failure output remains in `/tmp/sol-audit-trials.jsonl`.

| WADImportDVDExForBS-locals-2 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-3 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-4 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-5 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-6 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-7 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-8 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-9 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-10 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-11 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-12 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-13 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-14 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-15 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-16 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-17 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-18 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-19 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-20 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-21 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-22 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-23 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-24 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-25 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-26 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-27 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-28 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-29 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-30 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-31 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-32 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-33 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-34 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-35 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-36 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-37 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-38 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| WADImportDVDExForBS-locals-39 | Ordinary initialized size/pointer locals; scalar mode makes the existing mask branch unreachable | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| fat12-values-1 | Name actual call/mask/sector values in their original evaluation order: offset-mask | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-2 | Name actual call/mask/sector values in their original evaluation order: next-sector | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-3 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-4 | Name actual call/mask/sector values in their original evaluation order: driver-error | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-5 | Name actual call/mask/sector values in their original evaluation order: offset-mask,driver-error | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-6 | Name actual call/mask/sector values in their original evaluation order: next-sector,driver-error | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-7 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,driver-error | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-8 | Name actual call/mask/sector values in their original evaluation order: callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-9 | Name actual call/mask/sector values in their original evaluation order: offset-mask,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-10 | Name actual call/mask/sector values in their original evaluation order: next-sector,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-11 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-12 | Name actual call/mask/sector values in their original evaluation order: driver-error,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-13 | Name actual call/mask/sector values in their original evaluation order: offset-mask,driver-error,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-14 | Name actual call/mask/sector values in their original evaluation order: next-sector,driver-error,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-15 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,driver-error,callback-pointer | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-16 | Name actual call/mask/sector values in their original evaluation order: fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-17 | Name actual call/mask/sector values in their original evaluation order: offset-mask,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-18 | Name actual call/mask/sector values in their original evaluation order: next-sector,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-19 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-20 | Name actual call/mask/sector values in their original evaluation order: driver-error,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-21 | Name actual call/mask/sector values in their original evaluation order: offset-mask,driver-error,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-22 | Name actual call/mask/sector values in their original evaluation order: next-sector,driver-error,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-23 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,driver-error,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-24 | Name actual call/mask/sector values in their original evaluation order: callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-25 | Name actual call/mask/sector values in their original evaluation order: offset-mask,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-26 | Name actual call/mask/sector values in their original evaluation order: next-sector,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-27 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-28 | Name actual call/mask/sector values in their original evaluation order: driver-error,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-29 | Name actual call/mask/sector values in their original evaluation order: offset-mask,driver-error,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-30 | Name actual call/mask/sector values in their original evaluation order: next-sector,driver-error,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-values-31 | Name actual call/mask/sector values in their original evaluation order: offset-mask,next-sector,driver-error,callback-pointer,fat-sector-base | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-final-unsigned-error | Actual status/value lifetime or representation; no forced storage | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-final-callback-result-init | Actual status/value lifetime or representation; no forced storage | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| fat12-final-error-block | Actual status/value lifetime or representation; no forced storage | BUILD FAIL |
| fat12-final-read-status-scope | Actual status/value lifetime or representation; no forced storage | PFFAT12_ReadFATEntryWithBuf: 23/155, insns 155/155, baseline differences 23; baseline sections and relocations different |
| Board-best-confirm | Fresh best flat-local confirmation before allocator capture | appendRecord__Q33ipl5scene5BoardFP10_CDBRecord: 44/283, insns 283/283, baseline differences 44; baseline sections and relocations different |
| WADImportDVDExForBS-offset-proof | Fresh ordinary-local code for stack-home and memset comparison | WADImportDVDExForBS: 223/263, insns 262/263, baseline differences 223; baseline sections and relocations different |
| pud-without-dead-copy | Remove the unread workspace snapshot; preserve only fallback and actual matching values | Zi8MatchPUDdata_ZHS: 339/354, insns 353/354, baseline differences 339; baseline sections and relocations different |
| pud-live-workspace-alias | Use the workspace alias for every actual workspace access and helper argument | Zi8MatchPUDdata_ZHS: 373/354, insns 385/354, baseline differences 373; baseline sections and relocations different |
| pud-live-typed-workspace | Use a typed working pointer for every actual workspace access and helper argument | Zi8MatchPUDdata_ZHS: 373/354, insns 385/354, baseline differences 373; baseline sections and relocations different |
| pud-scoped-table-workspace | Scope a live typed workspace alias to the language-table lookup rather than keeping an unread snapshot | Zi8MatchPUDdata_ZHS: 353/354, insns 366/354, baseline differences 353; baseline sections and relocations different |

## Final independent verification

Final allocated-section bytes and resolved relocation targets equal the starting
source objects for all 16 audited units. This covers .text, data, zero-initialized
sections, exception tables and inline callers, including the pre-existing
non-exact BS2Mach and CHANSVm code. The restored Board, FAT12, WAD and PUD
objects also equal their starting objects.

Fresh ctxdiff checks give diffs 0 and equal instruction counts for Korean
(619), secondary character matching (311), phonetic matching (363), cmpName
(87), fadjust (115), finfo (91), System::init (689) and CHANSVmNewObjData
(96). BS2Tick remains 1940/1940 instructions with its original 71 differences;
its source-object bytes are identical to the original local baseline.

| Changed unit | Exact functions before | Exact functions after | Code/data result |
| --- | --- | --- | --- |
| `libs/RVLMiddleware/eZiText/src/clib/zikorean` | 3/3 | 3/3 | 100%; every section unchanged |
| `libs/RVLMiddleware/eZiText/src/clib/zi8match` | 10/10 | 10/10 | 100%; every section unchanged |
| `libs/RVL_SDK/src/fa/pf_path` | 27/27 | 27/27 | 100%; every section unchanged |
| `libs/RVL_SDK/src/fa/pf_file` | 45/45 | 45/45 | 100%; every section unchanged |
| `src/BS2/BS2Mach` | 27/29 | 27/29 | Existing partial code unchanged; data 100% |
| `src/system/iplSystem` | 63/63 | 63/63 | 100%; every section unchanged |
| `src/channelScript/CHANSVm` | 227/233 | 227/233 | Existing partial code unchanged; data 100% |

Ran the requested final gate once over all seven changed units and the four
restored carrier units:

```sh
python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py \
    src/scene/board/iplBoard \
    libs/RVLMiddleware/eZiText/src/clib/zikorean \
    libs/RVLMiddleware/eZiText/src/clib/zi8match \
    libs/RVLMiddleware/eZiText/src/clib/zi8pud2 \
    libs/RVL_SDK/src/fa/pf_fat12 \
    libs/RVL_SDK/src/fa/pf_path \
    libs/RVL_SDK/src/fa/pf_file \
    src/BS2/BS2Mach src/system/iplSystem \
    libs/RVL_SDK/src/wad/wad src/channelScript/CHANSVm --quick
```

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

All 11 gate-unit pools are identical. Regenerated the live report with
`ninja progress build/43U/report.json build/43U/ok`. Compared every unit's
measures, function scores and section sizes/scores against the initial full
report: zero differences across all 1028 units. Global exact-function count
remains 12523/12563, matched code 2933788/2995176 and matched data
1832684/1832684. Linked code/data measures also remain unchanged.

Raw final outputs: /tmp/sol-audit-gate.log,
/tmp/sol-audit-final-ctxdiff.log and /tmp/sol-audit-final-evidence.json.
Focused source diff passes git diff --check. No build configuration, shared
header, assembly, pragma or source comment was added or changed.

## Retained per-file commits

| Commit | File |
| --- | --- |
| `f8a2e625` | `src/system/iplSystem.cpp` |
| `3118dc23` | `libs/RVLMiddleware/eZiText/src/clib/zikorean.c` |
| `60c64eef` | `libs/RVLMiddleware/eZiText/src/clib/zi8match.c` |
| `4bbe8e23` | `libs/RVL_SDK/src/fa/pf_path.c` |
| `69be5311` | `src/channelScript/CHANSVm.c` |
| `97ee91e9` | `src/BS2/BS2Mach.c` |
| `6c837a8c` | `libs/RVL_SDK/src/fa/pf_file.c` |

PUD trial commit `80d7290c` is canceled by `5b0f57b6`; the net PUD source diff
is empty. Land only the complete audited branch or its net diff, not the
rejected PUD commit alone.
