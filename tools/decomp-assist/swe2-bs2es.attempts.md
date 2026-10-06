# swe2-bs2es attempts — BS2ESGetTicketViews integrity (remove carrier)

Task: replace the 256-byte aligned carrier struct `{ESTitleId title[4]; u32 count[56];}`
with honest storage while keeping the function exact.

## Target layout (build/43U/obj/src/BS2/BS2Mach.o)

- vectors: sp+0x20 (4 x IOSIoVector)
- title:   sp+0x40 (8-byte ESTitleId at offset 0 of a 32-aligned block)
- count:   sp+0x60 (u32 at offset 0x20 of the same block)
- block:   sp+0x40..0x140 = 0x100 = 256 bytes

libs/RVL_SDK/src/es/es.c `ES_GetTicketViews` (already matched) uses
`DECLARE_ES_WORK` = `u8 __esWork[256] ALIGN32`, `pTitleId` at AT_ES_WORK(0x00),
`pNumTicketViews` at AT_ES_WORK(0x20). BS2ESGetTicketViews is the same request
adapted to a caller-supplied fd: the stack copy keeps the 256-byte work buffer
with identical +0x00/+0x20 offsets and declares the ioctl vectors separately.

## Attempts

1. `u8 work[256] ALIGN32` + existing `IOSIoVector vectors[4] ALIGN32`;
   `title = (ESTitleId *)work; ticketCount = (u32 *)(work + 0x20)`.
   -> differing: 0 / 71. Pool identical (91 = 91). Kept.
