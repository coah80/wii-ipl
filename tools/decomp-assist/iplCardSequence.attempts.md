# iplCardSequence matching attempts

Baseline: absent source, 0/30 exact functions, 0/9852 exact code bytes.
Started from /tmp/iplCardSequence.candidate98.cpp and replaced all raw thread
field offsets with CardThreadState members and ordinary array indexing.
Reused FileInfo, CardState and IconState from iplMemoryCardLib.h. The inline
request helpers use the existing public signatures. Only this CPP defines
IPL_CARD_SEQUENCE_CPP; its guarded shutdown return declaration is BOOL.

CardThreadState models the actual queues, OS thread, stack, file handles,
allocated buffers, per-file arrays and completion state. The embedded comment
read buffer is aligned to 32 bytes for CARDRead, giving the original 0xDBE0
allocation size without dummy members or explicit filler bytes.

Initial typed reconstruction: 23/30 exact functions, 3248/9852 exact code bytes.
All 43 strings were identical on the first build. After subsequent ordinary
code restructuring, every data section scores 100%: .data 1464, .bss 16,
.sbss 8 and .sdata 8 bytes. No new address symbols or artificial data exist.

## sendCardCopyCmd / sendCardMoveCmd / sendCardDeleteCmd

Each experiment was applied to all three functions; they differ only in the
command byte. All retained versions have 21/21 instructions, two differences:
the ori into the message register and li r5,0 occur in the opposite order.

1. Initial packed high-byte message plus command at the send call: two differences.
2. Included command in the initial message expression: eight differences,
   different packing instruction order and registers.
3. Used the public void signature and a final send statement: two differences.
4. Factored a real sendFileCommand inline helper: compiler emitted an out-of-line
   helper, reducing wrappers to three instructions; reverted.
5. Packed file/slot/command with a union and bitfields: 22/21 instructions,
   rlwimi and a register copy instead of the original ori.
6. Used addition of the command byte: 21/21, twelve differences, addi instead
   of ori and different registers; reverted.
7. Separate final message |= command statement: same two differences.
   Retained this clear form. Each final function is 90.47619%.

## initCardThread

1. Typed arrays indexed by a signed byte index divided by four: 173/167
   instructions, 90.69461%; signed division introduced srawi/addze.
2. Native array element index: 167/167, 27 differences. All differences are
   in the two pointer-array initialization loops.
3. Ordinary ascending for loops and direct expressions in the second loop:
   167/167, 19 differences; second loop now matches.
4. Computed both buffer pointers before either store: 166/167; commoned loads
   unlike the original; reverted the hoisting.
5. Unsigned image offset, comment offset and array index: still 167/167,
   same 19 register differences in the first initialization loop.
Final: 98.952095%; first-loop register allocation remains open.

## CardSequence_813D2C8C

1. Typed fields and a command | (validState << 8) response: 300/301 instructions,
   98.106316%; compiler folded the response into ori rather than rlwimi.
2. Union response with an eight-bit validity field: 301/301, 78 differences.
   Remaining differences are saved registers and response assembly scheduling.
3. Extracted sendValidityResponse as a real inline helper: identical 301/301
   result and 78 differences. Retained this readable packing helper.
Final: 97.9402%; saved-register assignment and three response instructions differ.

## CardSequence_813D3424

1. Typed icon and pointer tables: 514/512 instructions, 87.08008%; signed
   conversion of the byte palette offset introduced extra arithmetic, plus
   different register allocation and image/comment error branches.
2. Inverted the comment-range boundary checks into a normal nested success
   path: 509/512, 86.47461%; changed branch layout and error joins.
3. Indexed iconOffset by the real iconCount rather than dividing a byte
   offset by four: 499/512, 87.23633%; removed the artificial signed-division
   work and retained direct struct fields. Original helper/error boundaries
   and register allocation still differ.
Final: 87.23633%; 499/512 instructions. Original code appears to retain
inlined helper return/error joins that this reconstruction optimizes away.

## CardSequence_813D3D14

1. Typed thread fields with the original nested stages: 608/608, 97.804276%;
   186 differences, mostly saved registers, plus metadata error joins,
   move-loop branch target and cleanup sign extensions.
2. Full-width destinationFileNo until API calls: 606/608, 97.458885%;
   removed two original instructions and changed allocation; reverted.
3. Structured nested sector-size checks instead of label-based checks:
   604/608, 96.43915%; eliminated additional original branches; reverted.
Final: retained the first 608/608 version, 97.804276%.

No remaining function lacks three distinct source-level attempts. No other
translation unit changes its output. Configure.py remains NonMatching.

## Continuation after the first merge

Baseline: 23/30 exact functions, 3248/9852 exact code bytes, all 1496 data
bytes exact. Pool remains identical (43 strings). Every experiment below was
built as the owned object and inspected with ctxdiff; discarded variants are
absent from the final diff. Shared headers are unchanged in this continuation.

### initCardThread

1. Integer address temporaries for the allocated image/comment buffers:
   167/167 instructions, unchanged 19 register differences. Reverted casts.
2. Descending remaining-count loop with a byte index divided by sizeof(pointer):
   168/167 instructions; added an index mask and changed allocation. Reverted.
3. Named typed destination-entry pointers and reversed pointer-addition operands:
   167/167, unchanged 19 register differences. Reverted.
4. Compute both buffer offsets directly from the native file index instead of
   maintaining two separate offset accumulators: 167/167, diffs 0. Retained.
   Both pointer-array loops now match and obsolete offset locals are removed.

### CardSequence_813D2C8C

1. Reused one file-index variable for the mount scan, listing and delete cases:
   301/301, 73 differences versus the baseline 78. Saved-register assignments
   and response assembly ordering still differ. Reverted for the focused diff.
2. With the unified index, changed thread validity and exit flags to bool:
   301/301, same 73 differences. Reverted.
3. Initialized the response union to zero, then assigned its command field:
   302/301, additional packing instruction. Reverted.

### CardSequence_813D3D14

1. Separate scoped result for the copy-metadata phase: 608/608, 185 differences
   versus baseline 186; still saved registers and branch destinations. Reverted.
2. Copy-metadata phase as a single-iteration loop with explicit failure breaks
   and a common result check: 608/608, 182 differences. Pool identical. Reverted.
3. Moved move-stage initialization after the CARDDir assignment in that variant:
   608/608, 189 differences. Reverted.

### sendCardCopyCmd / sendCardMoveCmd / sendCardDeleteCmd

All variants were applied to all three command functions.

1. Real inline makeFileRequest packing helper shared by the three wrappers:
   compiler kept it out of line; each wrapper became 29/21 instructions.
   Reverted. This helper is different from the earlier sendFileCommand helper:
   it only computes a packet and performs no shared-state writes or OS calls.
2. Separate OSMessage request and BOOL nonblocking flags locals: 21/21,
   unchanged two instruction-order differences. Reverted.
3. Union file/slot fields followed by OR into its value: 21/21, nine differences
   involving packing registers and the same ori/li ordering. Reverted.
4. Template packet encoder specialized by command: inlined, 21/21, four
   differences (two packing instructions and the same ori/li ordering). Reverted.

### CardSequence_813D3424

1. Named IconState reference spanning the whole function: 362/512 instructions;
   compiler cached its address and eliminated many original global reloads.
   Reverted.
2. Named IconState reference limited to the animation/format loops: 438/512;
   same address-caching issue within that region. Reverted.
3. Extracted a real single-use inline readComment helper with sector-size and
   range checks, read, copy and error clearing: inlined to 499/512, different
   allocation/error boundaries. Reverted.

Retained only the instruction-exact initCardThread change. Every remaining
function has three new distinct attempts in this continuation. All data
sections and the complete pool remain exact; no DOL link investigation.

## Continuation after the second merge

Baseline: 24/30 exact functions, 3916/9852 exact code bytes, 1496/1496 data
bytes. The pool is identical at 43 strings. The three long functions were
examined in decreasing baseline score; command packing experiments followed.
Every variant below was built as the owned object and inspected with ctxdiff.

### CardSequence_813D2C8C

1. Unified mount, listing and delete file indices and widened the slot local
   to u32: 301/301 instructions, 70 differences versus the baseline 78.
   Saved registers and validity-response scheduling still differ. Reverted.
2. Reused the slot and result locals for the free-space scan rather than
   separate outerSlot/freeBlocks locals: 301/301, 69 differences. Reverted.
3. Made the validity flag u8 and passed its value to the validity report:
   301/301, unchanged 78 differences. Reverted.

### CardSequence_813D3D14

1. Native bool flags for temporary creation, metadata completion and cancel:
   608/608 instructions, unchanged 186 differences. Reverted.
2. Scoped permissionResult for the initial permission check, independent of
   the transfer result: 608/608, 177 differences. Initial saved-register
   assignments, metadata joins and cleanup conversions remain different.
   Reverted for the focused final diff.
3. With the scoped permission result, used a full-width destination result,
   explicit s16 conversions when accepting the creation result and at file
   APIs: 608/608, same 177 differences. Reverted.

### sendCardCopyCmd / sendCardMoveCmd / sendCardDeleteCmd

Each variant was applied to all three commands. The final mask expression
was checked independently for each symbol: 21/21 instructions, diffs 0.

1. Packed the slot first in a union value, then assigned its file byte:
   21/21, 11 differences in packing registers and instruction ordering.
2. Shared inline sendFileRequest helper for the final OR and nonblocking
   queue send: inlined, 21/21, unchanged two scheduling differences.
3. Signed message temporary: 21/21, unchanged two differences.
4. Separate masked slot temporary: 21/21, eight packing/scheduling differences.
5. Explicit file-byte temporary: 21/21, unchanged two differences.
6. Separate initial slot assignment and OR of the shifted file byte:
   21/21, 11 differences. Reverted.
7. Explicit unsigned file mask before shifting, replacing the narrowing byte
   cast: 21/21, diffs 0 for Copy, Move and Delete. Retained. Both express the
   same file-byte truncation; the mask produces the original li/ori order.

### CardSequence_813D3424

1. Corrected the eighth-icon palette destination to icons[slot][fileNo].
   The original at 813D384C adds the selected icon offset before storing
   iconTlutOffset at 813D385C. The previous icons[0][0] destination was wrong.
   499/512 instructions; objdiff improves from 87.23633% to 87.92969%.
   Retained this behavior correction.
2. Moved iconCount and shift increments to the common bottom of the format
   loop: 499/512, objdiff improves further to 89.44531%. The source now
   expresses the shared loop continuation directly. Retained.
3. Extracted the sector-size checks, image read/copy and invalid-image clearing
   into a real inline readCardImages helper: inlined to 480/512 instructions.
   Pool identical; more original error-path instructions were optimized away.
   Reverted.

The final diff retains three exact command functions and the palette destination
correction and shared loop continuation. All remaining functions have at least
three new distinct attempts.
Shared headers and configure.py are unchanged. All data sections remain exact.

## w1011/struct2 probes
- cardThreadMain (301v301): pure reg-perms + one merge-order tie — base `mr r4,r19; rlwimi r4,r25,8` vs mine `rlwimi r23,r29,8; mr r4,r23`. Same count, ordering only.
- loadCardFileIcons (508v512, -4): base emits per-path `li r?,0; stb` zero-init pairs (dead zero-webs on each switch-case path — `bannerEnable=0` etc. re-materialize the zero instead of sharing), plus split `addis/addi` addr materialization + `lbz -1(r); stb 0(r)` adjacent-field copy where mine fuses. Structural decode incomplete.
- runCardMoveOrCopy (608v608?): not yet diffed.

## w1011/struct2 wave 2 (loadCardFileIcons 508->511/512)
- WIN: `s32 icon = 0` decl-init materializes a missing zero-web (+1).
- WIN: `u32* iconOffsets = &...iconOffset[0]` + `s32 nextIcon = iconCount + 1` → base's `slwi r,2; lwzx`/`stwx` indexed addressing (+2). Direct member index `iconOffset[iconCount+1]` folds to immediate-offset lwz/stw.
- Tried/reverted: `(u16)` index cast (513), `iconFmt[iconCount]=iconFmt[iconCount-1]` direct (510), u16* iconOffsets.
- Residual -1 + ~92 reg/order diffs: base materializes `&iconFmt[iconCount]` in one reg with `lbz -1(r); stb 0(r)` where every source form folds to `lbz -0x6fb5/stb -0x6fb4` field offsets (remat-vs-pin family).

## loadCardFileIcons residual -1 insn + coloring
- runCardMoveOrCopy (608v608): normalized-identical, pure coloring tie.
- loadCardFileIcons -1 = pinned-result phi: mine emits `mr r24,r3` (callee-pinned result web) after CARDGetSectorSize, base keeps result in r3-arrival and remats `li r3,0` in the error path. Same phi-coalescing tie family as attach_mount (pfrest) — no source lever found.

## w1011/struct2 wave-2 — web-birth decode (loadCardFileIcons SOLVED -1)

- `s32 iconCount; ... iconCount = 0;` — UNINIT DECL + SEPARATE ASSIGN
  splits the zero web's birth so MWCC rematerializes a second `li 0` for
  the icon-init stores (base's exact remat pattern). Applied in BOTH
  updateCardIconAnimation and loadCardFileIcons: 511 -> 512 insns,
  residual now 26 pure callee-renaming diffs (r31/r26 sThread,
  r7/r4+r10/r6 record ptrs — coloring family).
  NB: `static s32 iconCount` also produced 512 but emits dead object
  `iconCount$16368` (forbidden, PR #973) — the lever is web-birth
  timing, not storage class. Static variant rejected.
- cardThreadMain sendValidityResponse: `reply.value = command;
  reply.fields.valid = valid;` produces base's `mr` + `rlwimi @0xFF00`
  byte-insert order (vs `reply.value = valid<<8; fields.command=command`
  which folds to `li 0x100 + rlwimi`). Residual 2 lines: in-place
  `rlwimi r19` vs base `mr r4,r19; rlwimi r4` — same coalescer
  dst-operand wall as the or-chain. `|=` folds to ori; bitfield-order
  emits 2 rlwimi + stw.

## w1011/struct2 wave-3 — structural probes (icon-record intermediates)

- `IconState* rec = &sThread->icons[slot][fileNo]` + member accesses:
  collapses fn to 408 insns — MWCC pins the pointer, kills the
  per-use rematted add chains. The sThread->icons[slot][fileNo]
  spelled-out form is load-bearing for the remat structure.
- `IconState (*icons)[CARD_MAX_FILE] = sThread->icons` array pointer:
  collapses to 424 for the same reason. Named intermediates can't
  reproduce base's pinned-products + remat-adds split.
- The 26 residual diffs are a pure callee-window swap: base pins the
  icon-record PRODUCTS (slot*0x1FC0->r29, fileNo<<6->r30, masked addr
  ->r31) and params->r24-r26; mine pins params high. Chaitin color
  ordering — documented tie.
- cardThreadMain: `OSMessage msg` arg-coalescing local, packed
  `command | (valid<<8)` single expr (folds, 300), mask+or
  `(v & ~0xFF00)|(valid<<8)` (rlwinm+ori split) — the mr+rlwimi
  copy-vs-inplace residual (2 lines) is the coalescer dst-operand wall.

## w1011/struct2 wave-4 — mr+rlwimi mechanism PROVEN, no free source form

- `sThread->lastCommand = command;` after sendValidityResponse makes
  command's web survive the pack → emits base's EXACT `mr r4,r19;
  rlwimi r4,r25,8` (copy+insert, not in-place). Mechanism confirmed:
  the rlwimi dst binds to a surviving operand's copy — but the store
  costs +3 insns and base has no such store. Verified base's r19 dies
  at the same point (reborn at 0xd58 case-0 reassign).
- `command & 0xFF` extract: folds (command provably masked) → in-place.
- `command | (valid<<8)`: single-expr fold to li/ori (300, -1).
- `(reply.value & ~0xFF00)|(valid<<8)`: rlwinm+ori split.
- Residual 2 lines = coalescer dst-operand choice with no source
  lever that preserves insn count.
