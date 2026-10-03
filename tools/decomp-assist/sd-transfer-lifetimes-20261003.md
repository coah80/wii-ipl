# SD transfer-title local lifetimes

Base: `fc114afd44065fb99f9ff2fe2969f393a504fe03`.
Owned source: `src/scene/sdChannelMemory/iplSDMemory.cpp`.
Only two existing local declarations move; no new objects or operations.

## Target evidence and retained source

`drawTransferTitles` starts at original DOL address `0x813EEFB8`, size 1804.
The original acquires memo Y into f31 at function `+0x90`, then writes the same
value into its local vector snapshot at `+0xA4`. Two subsequent pane lookups at
`+0xB4` and `+0xD4` leave that scalar live in f31. The previous source initialized
`bodyY` from the vector after those calls, causing an additional stack reload.
Initialize `bodyY` immediately after capturing the vector components instead.

This reconstructs the scalar lifetime, not changed callback behavior. Both
versions read the pane's translation before the later pane lookups. The private
`memoPosition` snapshot is never passed to a callee or otherwise exposed, so
those calls cannot legitimately mutate it. Capturing a reference to the live
pane or rereading `translation.y` after callbacks would have a different alias
contract; neither is introduced here.

The original initializes its newline count at `+0x180`, immediately after the
message fetch at `+0x17C`. Limit `lineCount` to that actual message-count stage,
inside the existing nonempty NAND-title branch and after obtaining the message.
Its uses, loop condition, arithmetic, and initialization value are unchanged.
No duplicate entry guard or extra separator local is added.

A raw original-object/DOL audit checked 387 nonrelocated words and all 38 direct
calls. The 50 ordered direct/indirect call sites remain the same in baseline,
candidate and original. All 24 floating arithmetic/comparison instructions are
identical between baseline and candidate. Pane/title fields, alpha propagation,
title-ID comparisons, native row counts and existing clipping expressions are
unchanged.

## Separate measurements

| Variant | Function fuzzy | Instructions / target |
| --- | ---: | ---: |
| Baseline | 92.7694% | 439/451 |
| Memo scalar captured with its snapshot | 93.02439% | 438/451 |
| Newline count initialized at message-count stage | 93.21286% | 439/451 |
| Both retained | 93.456764% | 438/451 |

These are source-grounded partial gains. The shorter extent removes an extra
reload; it does not mean a target operation was deleted. Remaining color-copy
and loop-entry differences are untouched. The function is still nonexact.

Earlier fz7 attempts retained a narrower count lifetime before later color
experiments caused the whole function to be restored. The already-fetched
external `07a3c7b3` also described the early memo scalar acquisition, but its
broader changes add dead color-copy storage and duplicate loop guards. Those
parts, and its register/frame experiments, were not imported or repeated.

## Final gates

- Unit fuzzy: 99.20353% -> 99.26294%
- Exact functions: preserved 64/66; matched code: preserved 14812/20872 bytes
- Matched data: preserved 3344/3344 bytes
- All allocated non-text bytes identical: `.data` 3144, `.sdata` 152,
  `.sdata2` 48 bytes, including sizes and alignment
- Complete reports for the other 1026 units unchanged; no function regresses
- All 64 objdiff-exact functions are instruction-identical to their baseline
- 57 of those have literal zero ctxdiff differences against original. Seven
  retain 12 pre-existing call-name differences for TitleRange assignment and
  SDChannelSelect collection/notice declarations. The original branch addresses
  were checked directly against the DOL; the local TitleRange copy helper is
  instruction-identical to the original five-instruction callee. This candidate
  does not resolve or change those existing external declaration/linking names
- Pool: 90/90 identical before and after
- Literal advisory: 157 arguments across 65 functions; no candidates/errors.
  The unequal-extent draw routine is the only skip
- Full 43U all_source/report/DOL build passes
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check`: pass

No runtime rendering or complete floating-domain proof is claimed. Verification
combines the unchanged source semantics, instruction-level preservation and
original-machine evidence. No shared headers, color storage, linking flags,
volatile qualifiers, assembly or unrelated functions changed.
