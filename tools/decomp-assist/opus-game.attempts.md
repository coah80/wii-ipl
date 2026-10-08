# opus-game attempts (worktree sol-high, base origin/main 77cf3598)

Units: iplCardSequence, odh, tiInputForm, tiCandidateBox. Diff counts are odiff.py (differing / total).

## tiCandidateBox

### create (278/356, size 0x590 vs 0x580) -> EXACT 0/352
Evidence: target addresses every pane-name string directly off the .data base
(r30+0x6a8, +0x6b4, +0x6c0, ...). Ours CSE'd `scPaneNameTable` and
`&scCandidatePaneData` into sub-bases (+0x28, +0x6b4). In the inlined
UIButton::Create the target holds both name args in saved registers instead of
rematerializing the address, which is how MWCC treats string-literal args.
1. Pass scroll/window names directly, no paneNames locals: 268/353.
2. Split scPaneNameTable into separate char arrays: 278/352 (equal size, sub-bases remain).
3. Names as string literals (B_OffBtn ... P_prdc_scrl_Rght): literals emitted after the
   named globals, in the target's order; 287/354.
4. Also W_predictWindow, N_predictInput, W_OnOff_Area, N_prdc_Texts and the
   "P_OffBtn" tail of scCandidatePaneData as literals: 0/352, .data bytes identical.
   symbols.txt: scCandidatePaneData size 0x68C -> 0x680; scPaneNameTable and the four
   named strings replaced by local literal labels at the same addresses. Total data
   unchanged; unit data 100%; DOL SHA1 unchanged.

### createAnmPane_ (64/216)
mwdbg trace + regsim (127/127 reproduced). Named locals colored in reverse
declaration order; `animationCount` cannot reach r31 by order (regsim 0/1).
1. Loop bound `j < p.count` (count becomes a compiler temp -> r31): 86/216 but count now r31.
2. Declare forceAddName, i at top; p, pane in loop; j in for: 41/216. All named locals match;
   left: animation-address temp r30 vs r23 and the hoisted constant temps shifted by one.
3. `p.pAnims[j]` at each use instead of the reference: 149/220 (reloads). Reverted.
4. forceAddName declared in the loop: 82/216. Reverted.
5. Pointer to slot `const AnimationFile* const* animation = &p.pAnims[j]`: 41 (no change). Reverted.
6. `animations = p.pAnims` hoisted, `animations[j]`: 86. Reverted.
Retrace after step 2: named locals all match; the only mismatch is the unnamed
animation-address temp (ours r30, target r23), numbered after the LICM constant temps.
Declaration order cannot move it. Kept steps 1-2 (64 -> 41) in the create commit.

## tiInputForm (best: opus-game.best.tiInputForm.diff, apply with patch -p0)

### create (153/356)
Register-blind diff showed one structural spot: target evaluates the
`getLanguageTextPane() ? textBox : "T_2l_TextBox"` name before loading mpLayout.
1. Name hoisted into a local before FindPaneByName: 153 (MWCC still loads mpLayout first).
2. Use the existing `selectInputTextName(*this, mpLanguageData)` helper (moved above create):
   146/356, now register-only (register-blind diff identical). Unit still 219/221, data 100%.
3. Drop `count` local (loop bound `button.count`): 179, count not hoisted here. Reverted.
mwdbg + regsim on step 2: reproduces 138/138; best 7/10 wanted registers with named
locals only and 7/10 even with temps. Structural: target puts LICM constants (li 0, lis
vtable) in r20/r21/r31 between named locals. Not fixable by declaration order.

### calcCursorPos (43/326)
FPR tie plus scheduling. scale.x/scale.y FPRs swapped (ours x=f31, target x=f30); the
SRA'd fields are numbered by first use.
1. GetHeight() instead of bottom-top: 43 (no change).
2. Compute `right` before `lineBottom`: 41, scale FPRs match, but schedule order flips
   (target computes the height product first) and fuzzy drops 93.05 -> 93.03. Not kept.
3. Named scaleX/scaleY locals: 235. Reverted.

## iplCardSequence (best: opus-game.best.iplCardSequence.diff, apply with patch -p0)

### loadCardFileIcons (436/512, 0x7f4 vs 0x800) -> best 406/512 (91.34% -> 93.34%)
Register-blind structural diff lines 41 -> 28.
1. `hasTlut = FALSE` initialized with the other counters before the speed loop: 419.
2. No-icon branch: store unk_0x01 before `iconImageSize = 0`: 408.
3. iconCount declared after the unk_0x02 store: 408 (struct 36).
4. `goto closeFile` -> `return result` (target's `bge; b epilogue` pairs, result stays in r3): 406, struct 28.
5. Tail `if (result < 0) return result;` instead of closeFile/closeFileSuccess labels: 406 (same, cleaner).
Tried without gain: iconCount u32/int, icon u32, `iconOffset[icon + 1]` (worse),
NONE-case spellings (array copy with [iconCount - 1], `(&...)[-1]`, `+ iconCount`, paletteSize after pointer).
Evidence for the rest: the target never sets paletteSize on the switch default path (r6 is
not initialized before the loop; default jumps straight to the iconCount < 7 test), so the
original read a stale paletteSize for format 3. Dropping the default assignment gives 404
and size 508, but that is an uninitialized read, so not kept. Remaining structure: NONE case
pointer formed as sThread + (iconCount + slot/file offset + 0x10000 - 0x6fb4), and
iconOffset[iconCount + 1] computed as ((iconCount + 1) << 2) without folding into +4.

### cardThreadMain (78/301)
mwdbg + regsim: reproduces 109/109; 9/9 wanted only with @-temps interleaved, 7/9 with
named locals only. One structural spot: the validity reply. Target copies command (mr r4, r19)
then rlwimi from validState (r25); ours coalesces the reply with command and inserts the
hoisted constant 1 (r29). PCode: `mr r72, r40; rlwimi r72, r71` with r71 the hoisted const;
r40 -> r72 coalesced because command dies there.
Tried: OR-expression reply (const-folds to ori 0x100: 261), mask-and-or (77), named
OSMessage local (78), validState BOOL/u8 (79/78), helper param u8/BOOL, command u8 (78).

## odh

### LineConv11 (12/146)
mwdbg + regsim: 77/77 reproduced; best 6/10 wanted (pixelSource r29, hi byte r8,
pixel r25, RGBA8 pointer r30) -> structural register tie. Plus lfs f7 / lis 0x4330 order.
Tried: split pointer add (15), &source[...] (12), operand order of the pointer sum (12),
pixel assembled from [0] first (12).

### huffmanDecoder (171/306)
Traced only. Target keeps sourceCursor in a volatile reg (r12) and bitOffset in r31; ours
the reverse, from the decomp's reuse of bitIndex/tableIndex/bitCountAndMask for several
values. Not attempted further this round.
