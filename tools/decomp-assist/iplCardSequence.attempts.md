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
