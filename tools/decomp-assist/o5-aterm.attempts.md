# o5-aterm attempts (ATERMBuildEncryptedMessage, 2026-10-09)

Worktree data-d3, branch agent/w1009/o5-aterm at b275eb2d. Start: ATERM 25/26 exact,
ATERMBuildEncryptedMessage 2/96 differing (target `mr r3,r27; mr r29,r7`, ours swapped), NonMatching.
End: 26/26 exact, ATERM flipped to Matching, main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Scratch: /tmp/o5-aterm (sched.py = scheduler port, brute.py, t/ = standalone function + try.sh/dbg.sh).
mwdbg captures: _mwdbg/runs/o5-aterm-base, o5-v2, o5-v5, o5-v9 (3.0a5.2 gives the same code as 3.0a5
for this function; trace with `--sjiswrap on` and an explicit `--args` command).

## What the source change is

The function now writes the frame and element headers through typed header pointers, like
atermSetSingleElement and atermSetElementData already do in this file:

    AtermFrameHeader* header = (AtermFrameHeader*)messageBuffer;
    AtermElementHeader* element = (AtermElementHeader*)payload;
    memset(element, 0, sizeof(*element));
    element->length = SOHtoNs(payloadLength - sizeof(*element));
    ...
    memset(header, 0, sizeof(*header));
    header->command = SOHtoNs(sequence);
    header->length = SOHtoNs(payloadLength);
    end = (u8*)(header + 1);
    end += payloadLength;

Same values, same stores, same calls. `for (cursor = (u8*)header; ...)` breaks B1 again (4 diffs), so the
checksum still walks `messageBuffer`; `end = (u8*)(header + 1) + payloadLength` in one statement swaps
the add order (4 diffs).

## Why it works (from the backend dumps)

1. The cast copies are not IRO copy candidates (the right side is a cast, not a plain object ref), so
   `mr v41,v32` (header) and `mr v40,v34` (element) reach PCode in B1. With `element` used twice
   (memset, ->length) local expression propagation does not fold it either.
2. Pass-1 scheduling sees the chain p5 -> element copy -> memset arg -> bl and the header copy after
   p3, which gives the order p5, p3, element copy, p4, p6, p7, header copy, ...
3. The forward peephole folds the element copy into memset's argument move (`mr r3,r34` lands in the
   element copy's slot) and clears B1's scheduled flag (backend-01 B1 flags 0x4, not 0xc).
4. The allocator coalesces the header copy into msg (r30) and deletes it.
5. Pass 2 (after allocation, physical registers, no opcode-rank tie-break) reschedules B1 because its
   flag was cleared, and emits p5, p3, p4, p6, `mr r3,r27`, `mr r29,r7`, li, li, li, bl: the target.

General lesson (proposed lever 37): any copy the allocator or the forward peephole deletes from a block
clears that block's "scheduled" flag (0x8), and the block is scheduled again after register allocation
from its pass-1 order, with physical-register dependencies and ties broken by list order instead of
opcode rank. o4's model scheduled B1 only once, which is why it found no C shape. Seen in the captures:
v2 (inline helper with a modified length param: copy deleted, B1 flags 0xc -> 0x4 -> rescheduled) and v5.

## Scheduler port

/tmp/o5-aterm/sched.py ports schedule_block/select_ready_coloring_node (750 model). It reproduces pass 1
and pass 2 of base, v2 and v5 and pass 1 of v9. For v9's pass 2 it predicts `p4, arg, p6` where 3.0a5.2
emits `p4, p6, arg`, so the GC/3 pass-2 tie-break differs from the 1.x reference in at least that case.
brute.py (extra vanishing copies x RA outcomes x statement orders) found the payload/len/msg copy family
first; the struct-pointer style was the natural C for it.

## Attempts

| attempt | Encrypted diffs |
|---|---|
| goto/label boundary after param copies | 2 (folded away) |
| inline wrap helper (payload, length, key), modified length | 2 (length copy deleted, B1 rescheduled, same order) |
| inline helper with early return | 13 |
| AtermFrameHeader* header only (v5) | 2 (header copy reaches B1, deleted, B1 rescheduled) |
| header + element pointers, memset(element), element->length (v6/v7) | 0 |
| v7 + header->command/length, header + 1 (v9) | 0, kept |
| v9 with checksum over header | 4 |
| v9 with one-statement end | 4 |

## Link fix (AxAdpcmPlayer)

Flipping ATERM to Matching first gave main.dol 035744a9..., with 1104 runs of r13/.bss displacements
off by 0x10. ATERM's .bss objects match one for one (last object AtermThread ends at 0x810C0C70), but
the original AxAdpcmPlayer .bss starts at 0x810C0C80. The linker only pads before a section for its
alignment, so the original AxAdpcmPlayer.o .bss was 32-aligned; the built one was 8-aligned, which
the dtk ATERM object (size 0x1FE0 to the next unit) had been hiding. `u8 sZeroMem[0x100]` is the DSP
zero buffer (zeroBuffer -> convertDSPAddr), so it gets `ATTRIBUTE_ALIGN(32)`. AxAdpcmPlayer.o is
otherwise byte-identical (same .text/.data, .bss offsets and size), 13/13 exact.

## Result

ATERMBuildEncryptedMessage 2 -> 0 (96/96). ATERM 26/26 exact, all seven sections 100%, Matching.
Full build OK, main.dol 26116613f624061ba99c8d1a299aaa6efa85670d.
`gate.py src/scene/setting/ATERM src/bannerSound/AxAdpcmPlayer --quick`: GATE PASS, 0 regressions,
0 forbidden patterns, 0 readability warnings; complete code 96.55193 -> 97.19308.
