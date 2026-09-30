# NWC24MsgRead matching attempts

Baseline: no source; 0/16 exact functions, 0/4660 code, 0/128 data.
All functions implemented in object order from target assembly and object-exported Ghidra.
Pool and .data are identical, using ordinary literals. The first implementation
used the older reference only for file-reading conventions; signatures and
behavior come from the target. Format errors use NWC24_ERR_FORMAT (-24).

## Source attempts

NWC24ReadMsgField | protection exit through common result label | (98.82353, -9999) | src 0x194 base 0x198 insns 101/102
NWC24ReadMsgField | mailbox helper reads public message view | (98.92157, -9999) | src 0x194 base 0x198 insns 101/102
NWC24ReadMsgField | protection test after type local snapshot | (98.92157, -9999) | src 0x194 base 0x198 insns 101/102
NWC24ReadMsgFaceData | field and decoder success switches | (100.0, 0) | src 0xd4 base 0xd4 insns 53/53
NWC24ReadMsgAltName | status switch and independent decoder result | (100.0, 0) | src 0xb8 base 0xb8 insns 46/46
NWC24ReadMsgMBRegDate | work cursor declared after counts and explicit scan progress | (98.257576, -19) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | status declaration before cursor and scan counts | (99.545456, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | advance byte cursor in hexadecimal conversion call | (95.22727, -24) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBDelay | work cursor declared after counts and explicit scan progress | (98.18965, -17) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | status declaration before cursor and scan counts | (99.48276, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | advance byte cursor in hexadecimal conversion call | (94.74138, -22) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgTextEx | unsigned bounded charset scan | (100.0, 0) | src 0xb8 base 0xb8 insns 46/46
NWC24ReadMsgMBRegDate | scan offset and input pointer in for increment | (99.69697, -2) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | scan offset and digit count in for increment | (99.545456, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | scan index uses remaining count condition | (99.69697, -2) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBDelay | scan offset and input pointer in for increment | (99.655174, -2) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | scan offset and digit count in for increment | (99.48276, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | scan index uses remaining count condition | (99.655174, -2) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBUpdateSW | initialize work buffer after flag validation and switch status | (95.53571, -14) | src 0xe0 base 0xe0 insns 56/56
NWC24ReadMsgMBUpdateSW | work buffer declaration after result | (90.71429, -9999) | src 0xdc base 0xe0 insns 55/56
NWC24ReadMsgMBUpdateSW | signed update digit | (89.01786, -9999) | src 0xdc base 0xe0 insns 55/56
NWC24ReadMsgMBOptOutFlag | cursor lifetime and explicit separator case | (92.14286, -9999) | src 0x138 base 0x134 insns 78/77
NWC24ReadMsgMBOptOutFlag | signed bounded hexadecimal scan counters | (90.58442, -9999) | src 0x138 base 0x134 insns 78/77
NWC24ReadMsgMBOptOutFlag | app id accumulated before cursor advance | (92.14286, -9999) | src 0x138 base 0x134 insns 78/77
NWC24ReadMsgFromAddr | preserve stream status when closing fails | (98.804344, -9999) | src 0x16c base 0x170 insns 91/92
NWC24ReadMsgFromAddr | mailbox selection status via positive body | (97.5, -56) | src 0x170 base 0x170 insns 92/92
NWC24ReadMsgFromAddr | close result declared before stream result | (97.5, -56) | src 0x170 base 0x170 insns 92/92
NWC24ReadMsgSubject | read length initialized before mailbox selection | (96.14634, -9999) | src 0x144 base 0x148 insns 81/82
NWC24ReadMsgSubject | signed file read length | (98.65854, -9999) | src 0x144 base 0x148 insns 81/82
NWC24ReadMsgSubject | protection error stored in result | (98.65854, -9999) | src 0x144 base 0x148 insns 81/82
NWC24ReadMsgMBRegDate | scan counter increments explicitly after shift temporary | (99.545456, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | input cursor advanced through next-pointer temporary | (99.545456, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | signed hex digit count | (98.78788, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBDelay | scan counter increments explicitly after shift temporary | (99.48276, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | input cursor advanced through next-pointer temporary | (99.48276, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | signed hex digit count | (98.62069, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBUpdateSW | result declared before working pointer | (97.41071, -7) | src 0xe0 base 0xe0 insns 56/56
NWC24ReadMsgMBUpdateSW | message alias introduced after local result | (95.53571, -14) | src 0xe0 base 0xe0 insns 56/56
NWC24ReadMsgMBUpdateSW | result first then digit then cursor | (100.0, 0) | src 0xe0 base 0xe0 insns 56/56
ReadMsgTextInternal | separate encoding string and charset capacities | (93.735954, -9999) | src 0x2c0 base 0x2c8 insns 176/178
ReadMsgTextInternal | decoded count declared before truncation status | (93.735954, -9999) | src 0x2c0 base 0x2c8 insns 176/178
ReadMsgTextInternal | error status switches before closing | (91.88202, -9999) | src 0x2cc base 0x2c8 insns 179/178
NWC24ReadMsgAttached | attachment index converted to signed array index | (96.04395, -9999) | src 0x164 base 0x16c insns 89/91
NWC24ReadMsgAttached | decoded status declared before attachment length | (96.04395, -9999) | src 0x164 base 0x16c insns 89/91
NWC24ReadMsgAttached | alias attachment descriptor with real data pointer | (93.17583, -9999) | src 0x164 base 0x16c insns 89/91
ReadBase64Data | output cursor copied to explicit working pointer | (99.55696, -7) | src 0x13c base 0x13c insns 79/79
ReadBase64Data | source scan index declared before cursor | (97.974686, -26) | src 0x13c base 0x13c insns 79/79
ReadBase64Data | completion flag declared before status | (98.03797, -26) | src 0x13c base 0x13c insns 79/79
ReadQPText | use actual read extent for partial escape check | (98.6375, -24) | src 0x140 base 0x140 insns 80/80
ReadQPText | swap consumed and decoded count declarations | (98.725, -17) | src 0x140 base 0x140 insns 80/80
ReadQPText | output cursor copied to explicit working pointer | (99.3875, -15) | src 0x140 base 0x140 insns 80/80
ReadBase64Data | scan cursor declared before integer index | (99.620255, -4) | src 0x13c base 0x13c insns 79/79
ReadBase64Data | initialize status before completion flag | (99.68355, -5) | src 0x13c base 0x13c insns 79/79
ReadBase64Data | cursor-first scan and status-first initialization | (99.74683, -2) | src 0x13c base 0x13c insns 79/79
ReadQPText | remaining and offset lifetimes declared in input order | (99.9125, -7) | src 0x140 base 0x140 insns 80/80
ReadQPText | swap byte count slots | (99.475, -8) | src 0x140 base 0x140 insns 80/80
ReadQPText | input-order offsets and byte count slots | (100.0, 0) | src 0x140 base 0x140 insns 80/80
ReadBase64Data | cursor increment before index increment | (100.0, 0) | src 0x13c base 0x13c insns 79/79
NWC24ReadMsgMBRegDate | digit count before cursor in for increment | (99.545456, -3) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBRegDate | digit count in condition after consuming character | (100.0, 0) | src 0x108 base 0x108 insns 66/66
NWC24ReadMsgMBDelay | digit count before cursor in for increment | (99.48276, -3) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBDelay | digit count in condition after consuming character | (100.0, 0) | src 0xe8 base 0xe8 insns 58/58
NWC24ReadMsgMBOptOutFlag | return absent app id before hexadecimal scan | (99.61039, -3) | src 0x134 base 0x134 insns 77/77
NWC24ReadMsgMBOptOutFlag | explicit hexadecimal progress after reading each digit | (92.14286, -9999) | src 0x138 base 0x134 insns 78/77
NWC24ReadMsgMBOptOutFlag | separator early exit plus scan progress | (99.61039, -3) | src 0x134 base 0x134 insns 77/77
SelectMBox | mailbox selector with local error status | (2172, 96.739914)
SelectMBox | mailbox selector direct switch on status flags | (2172, 94.90558)
NWC24ReadMsgMBOptOutFlag | digit count in loop increment and cursor in body | (100.0, 0) | src 0x134 base 0x134 insns 77/77

## Remaining functions

NWC24ReadMsgField, 98.92157%: 101/102 instructions; protected-type load is reused across inlined mailbox selection.
NWC24ReadMsgFromAddr, 98.804344%: 91/92 instructions; type-load reuse and close-result control flow differ.
NWC24ReadMsgSubject, 98.65854%: 81/82 instructions; inlined mailbox selection reuses the protected-type load.
NWC24ReadMsgAttached, 96.04395%: 89/91 instructions; attachment addressing and saved-register allocation differ.
ReadMsgTextInternal, 93.735954%: 176/178 instructions; type-load reuse, empty-length handling, and saved-register allocation differ.

Shared-header changes are guarded by NWC24_MSG_READ, defined only by this unit.
No other unit output changes.
