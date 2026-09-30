# NWC24MBoxCtrl matching attempts

Baseline: no source, 0/25 exact functions, 0/10604 matched code bytes.
The implementation includes all 25 target functions and ordinary literals in target pool order.

## Remaining functions

- NWC24iIsMsgObjReadable: direct field checks, signed flags temporary, and explicit Boolean result each retain 57/57 instructions with five prologue scheduling differences. Nested validity checks produce ten differences. Best 92.98245%.
- NWC24GetMsgIdList: separate call errors from the scan result restores 153/153 instructions. Moving path before entry leaves 28 differences. Moving the result before counters yields 36 differences. Counter/result/cursor/entry declaration ordering reduces this to 21 register differences. Best 99.24837%.
- NWC24iMBoxCheck: switch to ordered if/else and precompute required capacity gives 68/68 instructions with 26 differences. A separate required-size temporary gives 66/68 instructions; the target retains an oldest-ID stack store and reload. Header/oldest declaration ordering and an output pointer temporary both retain the earlier 26 differences. Best 96.92647%.
- DeleteMsg: the initial scan has 297/296 instructions. Separating seek/read errors from the persistent search result gives 291/296 and 76.73987%. Moving the matching-ID branch before oldest-ID selection gives 297/296 and 91.5304%. Reordering count/oldest/offset declarations leaves the initial score unchanged. Remaining differences include scan error flow, ID comparison scheduling, stack allocation, and registers.
- DuplicationCheck: the initial predicate has 223/222 instructions and 88.95045%. Separating the application-ID predicate gives 220/222 and 90.32883%. A separate duplicate Boolean gives 251/222 and 75.38739%. Reordering counters retains the initial score. Remaining differences include candidate predicate branches and register allocation.

## Exact results

20/25 functions, 7420/10604 matched code bytes. Each exact function also has zero ctxdiff differences.
Scalar assignments with explicit packed-field temporaries match both conversion functions. Splitting user-ID accesses into high/low words fixes their register ordering. The corresponding shared-header view is guarded by NWC24_MBOX_CTRL, defined only in this source.
Cached-header lifetimes, file declaration order, explicit close-error returns, and separate send-file status resolve the control/header/open/close functions. Inline header-write and forced-unmount helpers reproduce the target lifetimes without assembly or uninitialized values.

The eight strings are identical in pool order. .data and .sdata are 100%; .sbss scores 50%. MountInfo is an eight-byte count/type structure, while the extracted target labels its first four bytes and leaves the second word unnamed. No symbol-size or placement edits were made.

## Continuation after the first merge

Starting point: 20/25 instruction-exact functions, 7420/10604 matched code bytes,
184/192 matched data bytes. All five previously open functions received at least
three distinct source-level attempts in this continuation.

### Newly exact functions

- NWC24GetMsgIdList: indexing the output by count replaces the explicit cursor
  and reduces register differences from 21 to 19. Separating offset/count
  declarations gives eight differences. Declaring the path before the errors
  gives four differences; putting it between the persistent result and the
  transient errors gives zero differences, 153/153 instructions, 100%.
  An inline open helper was also tried; it left five differences, including
  an error-branch destination, and was discarded.
- DeleteMsg: keeping seek/read/protection failures in the persistent scan result
  corrects the scan's exit paths. Using the existing inline header writer for
  both recovery and final flush gives 296/296 instructions. Result/counter/entry
  declaration order then reduces 41 register differences to 25, 16, and 12.
  Reusing the consumed protection/type arguments for completion status and
  ordering the scan declarations gives zero differences, 100%. Named completion
  helpers were tried as alternatives: a header-value helper gives 78 differences,
  a header-reference helper gives eight, and a clear/delete helper gives ten.
  Separate named completion errors give nine differences. None was retained.
- DuplicationCheck: explicit candidate initialization gives 94.27928%; separate
  tag/content duplicate branches give 91.927925%; putting the message-count
  limit inside the scan gives 93.07658%. Combining those changes gives
  98.62613%, 223/222 instructions. A positive final duplicate branch removes
  the extra instruction, giving 99.12162%, 222/222. Moving the error before
  counters and ordering offset/count/duplicate-ID/duplicate-offset/oldest/entry
  declarations then gives zero differences, 100%. Date comparisons use the
  signed comparison shown in the target.

### Functions still open

- NWC24iIsMsgObjReadable: an immutable message-pointer local, a separate
  private-message pointer view, and a copied entry parameter retain five
  prologue scheduling differences, 57/57 instructions, 92.98245%. A cached type
  scalar gives 58/57 instructions and 90.61404%. Combining type validity checks
  gives 55/57 and 89.29825%. A nested LED-validity body gives 57/57 but 41
  differences, 85.789474%. An inline readability helper retains the five
  differences. The target stores LR/r31 and copies the argument before loading
  type; MWCC schedules the load and mask among those prologue instructions.
- NWC24iMBoxCheck: an oldest-ID wrapper, a one-element output array, and a
  returned output pointer retain 66/68 instructions and 96.92647%. Grouping
  the cached header and oldest ID in a mailbox local gives 67/68 instructions,
  98.382355%; reversing the fields gives 98.30882%. A direct oldest-ID
  assignment gives 96.92647%. Copying the ID through memcpy or Mail_memcpy
  gives 70/68 instructions and 90.867645%. The retained mailbox local restores
  the target's oldest-ID store and header stack offset, but MWCC forwards the
  stored value into r4 rather than emitting the target's subsequent load.

### Data verification

The eight strings remain identical in pool order. .data and .sdata each score
100%. The compiler emits 166/12 bytes versus extracted 168/16 bytes respectively;
the target's additional trailing bytes are alignment zeros. The eight .sbss
bytes are byte-identical zeros. The sole MountInfo symbol has size eight in the
compiled object, whereas the extraction labels only the first four bytes.
Target instructions access the type using MountInfo plus its four-byte field
position. Its real count/type structure therefore remains eight bytes; the
extracted symbol boundary accounts for the 50% .sbss score. No symbol metadata,
placement directive, extra object, or other unit was changed.

Current result: 23/25 instruction-exact functions, 10104/10604 matched code
bytes, 184/192 matched data bytes. All 23 exact functions have zero ctxdiff
differences. The two open functions and extracted MountInfo extent remain
unresolved.
