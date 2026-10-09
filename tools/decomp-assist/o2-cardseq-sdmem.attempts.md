# o2-cardseq-sdmem attempts

Branch `agent/w1009/o2-cardseq-sdmem` from `20cf9f9f`.

## iplSDMemory: SDMemory::drawTransferTitles (50 -> 0), unit linked

Start: 50/451 differing, register-only. Earlier Opus run (data-d9 `9b634499`) had brought it
363 -> 50 with the MSL `wcsstr` overload and `TextBox::SetTextColor`.

### Diagnosis with mwdbg + regsim

Target vs ours, GPRs only:

- alpha r31 / string-pool base r30 / bodyPane, titleSizePane r29; ours r29 / r31 / r30.
- line loop: lineCount r22, totalLines r23, `L"\n"` r24, messageLine r26, messageText r27,
  lineIndex r28; ours r19 / r19 / r23 / r20 / r26 / r24.

The capture shows vreg numbering = `this`, named locals (reverse declaration order), frontend
temps (reverse creation order), then codegen vregs (string base r70 first). Coloring is reverse
simplify order and picks the lowest free register, requesting saved registers from r31 down.
Replaying the capture with relabelled vregs (`/tmp` wrapper around `regsim.simulate/color`)
reproduced the whole target when:

1. alpha lives in a codegen vreg created after the string base (any number 71..150),
2. totalLines sits between the third wcsstr's `s2` temp (v62) and lineEnd (v106/107),
3. row and visibleRows are numbered below every line-loop local,
4. messageText is numbered above lineIndex.

### Source changes that produce it

1. `nw4r::lyt::Pane::GetAlpha()` is `const` in real NW4R. With the const member the inline's
   result is a codegen value, not a frontend temp, and alpha moves above the string base.
   (An explicit `static_cast<u8>` around the call did the same; the const accessor is the real
   declaration, so that is what landed.) 50 -> 20.
2. `visibleRows` / `row` declared in the title loop body (`s32 visibleRows = ...; for (s32 row = 0; ...)`). 20 -> 18.
3. `messageText` declared before `lineIndex`. With 2: 13.
4. No `totalLines` local: `for (lineIndex = 0; lineIndex < lineCount + 1; ++lineIndex)`.
   With 1-3: 0 differing.

Types of alpha tried first (u32, s32, int, u16): no change; s8/char: worse. A named
`memoPane` local: no change.

### Linking the unit (Matching flip)

Flipping the unit failed to link: the source called six SDChannelSelect members through
`extern "C" iplSDChannelSelect_813D....` placeholders. A temporary link with the existing
mangled names linked but changed the DOL: one weak function survived dedup,
`SDMemory::TitleRange::operator=`, because SDChannelTitle hand-wrote the same compiler-generated
function as `extern "C" iplSDChannelTitle_copyTitleRange`. Fixes (all byte-identical where noted):

- SDChannelTitle: `sdRange = scene->mTitleRange;` / `nandRange = sdRange = scene->mTitleRange;`
  instead of the hand-written copy; symbols.txt names 0x813E6FA0
  `__as__Q43ipl5scene8SDMemory10TitleRangeFRCQ43ipl5scene8SDMemory10TitleRange` (scope:weak).
  The compiler emits it at the same place. Unit stays 69/69.
- SDChannelSelect, real parameter types from the command dispatch and NandSDWorker:
  `enqueueMoveNotice(ESTitleId)` (type 6 -> copy_nand_app_to_sd_async), `enqueueDeleteNotice(ESTitleId)`
  (type 13), `enqueueErrorNotice(TitleIdList*, TitleIdList*)` (type 11 -> check_backup_fits_async),
  `enqueueCommandNotice(TitleIdList* x3)` (type 12; the worker casts paramA-C to TitleIdList*),
  collect* `titleNames` as `wchar_t (*)[21]`. Object bytes identical, only symbol names change
  (symbols.txt updated for the nine functions). `friend class SDMemory;` for the private members.
- SDMemory: `TitleListState` was three `NandSDWorker::TitleIdList`s; it is now
  `mTitleList / mNandTitleList / mSDTitleList`, and the calls are member calls. Still 66/66.

Full build: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d with iplSDMemory Matching.
gate.py (SDMemory, SDChannelSelect, SDChannelTitle) --quick: 0 regressions, GATE PASS.

## iplCardSequence: loadCardFileIcons (213 -> 135, equal size)

Kept (all functions of the unit otherwise unchanged, pool identical):

- Format-3 palette left uninitialized (lever 10). Asm proof: in the target icon loop r6 is
  paletteSize; its only writes are `li r6,0x400` (case 1), `li r6,0x800` (case 2) and `li r6,0`
  (case 0). Case 3 branches (`cmpwi r4,3; bge`) straight to the iconOffset update that reads r6
  (`add r22,r6,r22` / `add r21,r6,r21`) and `add r7,r7,r6`; no instruction writes r6 between
  function entry and the loop. Case 0 sets paletteSize to 0 itself. 213 -> 387 (511 insns) with
  the array form, -> 192 (512/512) with the existing `u8* iconPalette` pointer form.
- Image read as `static inline s32 readCardImages(...)`: the target's CARDRead failure is
  `bge +8; b <check>` into the shared `if (result < 0)` test, the shape of an inlined early
  `return` (a goto folds to `blt`, a top-level return branches to the epilogue).
- Comment read as `static inline s32 readCardComment(...)`: with only the image helper the two
  sector-size slots swapped (0x8/0xC); as a second inline its `sectorSize` gets 0x8 again, and
  its early `return 0` / final `return result` give the target's comment flow.
- Banner/icon setup + image read as `loadCardIconImages(...)`, and the block base/offset split
  as `getCardBlockAddress(address, &offset)`: 231 -> 135, slot/fileNo/dir get r24/r25/r26.

Allocator analysis (mwdbg + regsim, a want-map derived by aligning backend-01/04 PCode with the
target): remaining diffs are register-only. Target colors iconAddressBase r31, then the four
CSE multipliers (fileNo*64 r30, slot*8128 r29, fileNo*4 r28, slot*508 r27), dir r26, fileNo r25,
slot r24, iconAddressOffset r23; comment base r23 / offset r21 / readSize r22 / result r29.
In the current capture iconAddressOffset sits in the last simplify scan (colored first, r31)
and iconAddressBase leaves one scan earlier; no numbering of the existing temps fixes both.

### loadCardFileIcons 135 -> 126

- NONE case as `u8* previous = &...iconFmt[iconCount - 1]; ...iconFmt[iconCount] = *previous;`:
  gives the target's `add; lwz; addis; subi; add; lbz -1(p); stb 0(p)` shape (134). The array
  form and `p[-1]` forms keep the -0x6fb4 in the displacement instead.
- Animation setup written in place with the icon loop's own `iconCount`/`shift`/`icon`, initialized
  `shift, iconCount, hasTlut, iconImageSize` in that order, early exit by `goto animationDone`.
  PCode value numbering reuses the first `li 0` of the block for the two zero stores; the target
  reuses the animation shift (r3), which only happens when shift is the first zero in that block.
  With the old helper the stores reused hasTlut. Anim region instruction order now matches.
- Block base as the common subexpression `iconAddress & 0xFFFFFE00` (IRO CSE temp, numbered just
  above the CSE multipliers, as the simulator requires); offset `iconAddress - (iconAddress & ~0x1FF)`.
  Base, params and the four multipliers now get the target registers (126).

Tooling: private mwdbg copy on gdb port 9137 (/tmp/o2-cardseq-sdmem-mwdbg, retrowin32 rebuilt with
the port patched) because the shared port queue timed out; IRO log via the known 2-byte patch of a
/tmp copy of GC/3.0a5.2 (diagnosis only). Remaining in the simulator: transferSize must be numbered
below the image offset, the comment base/offset/readSize above every other temp, result low.
