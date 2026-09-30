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
