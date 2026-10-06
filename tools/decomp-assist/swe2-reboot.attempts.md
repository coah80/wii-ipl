# swe2-reboot attempts — BS2Reboot (src/BS2/BS2Mach.c)

Integrity task: function already exact; replace dishonest
`struct { ESTitleId title[32]; } launchWork` carrier with honest storage.

Target disasm layout (0x280 frame):
- 0x20 ticketCount, 0x24 descriptor
- 0x40 vectors[4]
- 0x60 OSStateFlags flags (0x20)
- 0x80 title (ESTitleId, 8 bytes used of a 0x100 region)
- 0x180 ESTicketView ticket (0xD8)

The 0x100 title region matches the SDK ES work-buffer size. es.c uses
`u8 __esWork[256] ALIGN32` (DECLARE_ES_WORK) with the title at +0x00 for
ES_LaunchTitle; BS2ESGetTicketViews in the same file already uses the same
`u8 work[256] ALIGN32` idiom.

| # | Change | differing |
|---|--------|-----------|
| 1 | `u8 work[256] ALIGN32` in place of launchWork; `ESTitleId *title = (ESTitleId *)work` | 0 / 137 |

Exact on first attempt. pool_diff: no divergence.
