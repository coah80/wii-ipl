# NWC24MsgCommit matching attempts

Baseline: no source, 0/18 functions, 0/8532 code bytes, 0/904 data bytes.
All 18 functions are implemented in target object order. The private header's
additional mailbox/message views are guarded by NWC24_MSG_COMMIT, defined only
in this source. NWC24_MBOX_CTRL retains its existing view.

## Remaining functions

- NWC24CommitMsgInternal: the initial implementation has 781/827 instructions,
  82.8549%. A signed initialization index, swapping subject/text declarations,
  and inclusive file-error bounds were tested separately. Separating the overall
  result from each write's status gives 812/827 instructions, 88.46554%. Generic
  optional field writers give 826/827, 90.1052%; individual command/tag/DWC/icon
  inline writers give 817/827, 92.53204%. Moving cancellation before object
  publication gives 818/827, 94.54534%. Combining unsigned attachment iteration,
  partial-write byte accounting, subject/text declaration order, and inclusive
  status bounds gives 94.71463%. A separate inline message-ID writer gives
  94.72672%, 818/827. Remaining differences involve write/error control flow,
  formatting temporaries, and register allocation.
- CheckMsgBoxSpace: the initial estimate gives 223/223 instructions, 85.57399%.
  Splitting the base64 estimate into three accumulation statements gives
  78.098656%, 109 differences. Signed accumulation counters give 86.13453%,
  76 differences, but change the final unsigned capacity comparison. Moving
  the per-attachment size temporary outside the scan gives 85.57399%,
  75 differences. The final source keeps unsigned counters and the original
  unsigned overflow comparison. Remaining differences are chiefly scheduling
  and allocation in the compiler's eight-way unrolled attachment estimate.
- WriteToField: deferring field-counter initialization gives 99.71111%,
  90/90 instructions, six differences. An inclusive capacity check reduces this
  to four differences, 99.77778%. Moving the cursor before the buffer, moving
  the buffer after the counters/length/error, and separating initialization
  from declaration retain those four differences. An explicit recipient
  pointer gives 98.977776%, 14 differences; moving the cursor declaration after
  the length gives 97.5%, 36 differences. The remaining four differences select
  r24 instead of r25 for the initial scratch buffer, before recipient iteration.
- WriteMIMEAttachHeader: the initial form gives 92/92 instructions, 86.815216%,
  53 differences. Reloading the work buffer after clearing gives 92.41304%,
  25 differences. Nonpositive format-count checks give 87.01087%. Computing
  the first two formatted counts before the final format gives 91/92
  instructions. Advancing the cursor before that sum restores 92/92 and gives
  97.33696%, eight differences. Combining template lengths before reading the
  MIME-name length gives 99.45652%; grouping the final template sum gives
  99.51087%, seven differences. Reusing template-length temporaries for
  formatted lengths and reordering those declarations do not resolve them.
  Remaining differences are the template-sum schedule and register choices.
- WriteQPData: the initial form gives 60/60 instructions, 98.333336%,
  19 differences. Signed total and reversed encoded/consumed-count declarations
  give 98.5%, 13 differences. An input cursor declared before the total gives
  98.833336%, ten differences. Separating the remaining-byte count gives 99%,
  nine differences. Moving the error/counters/output pointer and trying cursor
  declarations before/after those locals were also tested. The remaining nine
  differences are callee-saved register choices; instruction count matches.

## Exact objdiff results

13/18 functions, 3364/8532 code bytes. The exact functions are NWC24CommitMsg,
CheckMsgObject, SynthesizeAddrStr, WriteSMTP_MAILFROM, WriteSMTP_RCPTTO,
WriteFromField, WriteDateField, WriteXWiiAppIdField, WriteXWiiFaceField,
WriteXWiiAltNameField, WriteContentTypeField, WritePlainText, and WriteBase64Data.

Declaration/lifetime changes resolve loopback, address synthesis, recipient
iteration, application flags, folded base64 headers, and content headers.
Advancing the synthesized-address cursor and caching the complete field length
resolve the SMTP sender and From header. A while loop with explicit cursor and
remaining-byte updates resolves the base64 writer. Inclusive validation bounds
resolve message validation and the Date header.

The gate counts 11 instruction-exact functions. Its disassembler and ctxdiff
misnormalize the two cr1 branches in each of WriteSMTP_MAILFROM and
WriteFromField: odiff.dis reads operands[0].imm as the target even when the first
operand is the condition-register field. These functions are at different unit
positions while the preceding commit function remains short. Direct .text byte
comparison confirms all 232/256 bytes respectively are identical to the target;
objdiff reports both at 100%. No tool or target metadata was edited to bypass
that count. All other eleven exact functions have zero ctxdiff differences.

## Data

pool_diff and the gate report identical pools. Every long string occupies its
target .data offset, and the twelve-month table is at 0x140 in source order.
The unrelocated .data bytes match the complete 678-byte source prefix of the
680-byte target; the remaining target bytes are alignment zeros. The twelve
month-pointer relocations are present in both objects. The target extraction
combines the first thirteen strings into one 296-byte symbol, whereas MWCC
emits individual literal symbols. The table's small-string destinations also
retain the .sdata offset differences below. Objdiff does not score .data as
matched despite the identical raw prefix; its relocations/symbol grouping
remain open.

.bss MultiPartDivider is 64 bytes and matches 100%. .sbss m_pFile matches 100%.
.sdata scores 18.765432%. Its first difference is byte four: the target's
LoopBackEnable symbol includes a trailing zero word, whereas the source's
ordinary BOOL definition is four bytes. The target also contains separate
subject and multipart CRLF literals; MWCC pools the source literals together.
The source .sdata is 140 bytes versus the target's 152 bytes, including trailing
section alignment. No extra object, packed string blob, alignment directive,
symbol-size change, or placement trick was introduced to cover these gaps.
Total matched data is 72/904 bytes. These data-layout differences remain open.
