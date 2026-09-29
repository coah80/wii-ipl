# MyTiInputForm attempts

Unit: `src/keyboard/MyTiInputForm`, 4.3U only.

Implemented all 84 target functions, including the compiler-generated inheritance thunks, in object order. The original `ghidra_decomp.txt` contains no functions from this unit; implementation followed the extracted assembly and sibling headers.

The initial source had 42 instruction-exact functions. Correcting the guarded base layout with the existing font and six repeat counters brought objdiff to 73 functions. Ordinary string literals and the original animation records produced identical 29-string pools from the first build.

## Functions that required iteration

- `onCommandOnDispMode`: initially 143/130 instructions. Keeping the cursor line in a separate scalar until constructing the relation argument, qualifying the candidate calls, and passing command 14 directly reduced this to 130/130. Assigning the edit point fields individually removed the final floating-point scheduling differences. Exact.
- `InputForm::create`: initially 229/220 instructions. Removing redundant checks around placement new reduced this to 220/220. Correcting the GUI call to `setTriggerTarget(false)` fixed the last virtual-slot difference. Exact.
- `createAnimation`: initially 129/124 instructions with a cached animation pointer. Ordinary placement new reduced this to 123/124. Reloading the animation record through its table entry restored 124/124 with 22 differences. Moving the count variable outside the loop worsened allocation to 49 differences. Keeping the loop bound as `entry.count` and initializing each concrete pane's key type in its constructor produced zero differences. The base constructor is protected; both concrete constructors initialize the key type before use. Exact.
- `ScrollButton::create`: initially 160/154 instructions. Ordinary placement new and a signed animation ID corrected allocation checks and comparison instructions. Exact.
- `init`: initial fields were at wrong guarded layout offsets. After restoring the repeat fields, separate boolean and float assignments corrected store order; `updateCandidateState_()` corrected the virtual slot. Exact.
- `setScroll`: initially 9/10 instructions. Reading the stored scroll field when negating it preserved the original float rounding instruction. Exact.
- `calcCursorPos`: initially 69/68 instructions. Computing line height before the adjusted cursor Y removed the extra saved floating-point move. Exact.
- `open`: separate scroll-from and scroll-to stores fixed the last two differences. Exact.
- `setEditMode`: initially 57/51 instructions. Qualified candidate calls removed the extra virtual dispatch. Exact.
- `doAutoScroll`: initially 153/152 instructions. Casting the quotient to int before adding one restored the original conversion order and 152/152 instructions. Multiplication operand reversal and a named half-line value left one difference. Multiplying the line-height temporary in place removed it. Exact.
- `calc`: initial 624/629 instructions and a different frame layout. Explicit draw-size/position temporaries and VEC3 construction gave 626/629. A helper returning the transformed origin, with separate coordinate assignments, restored the packed VEC2 return and 629/629. Computing draw Y before setting pane size and expressing half-height separately reduced this to 14 differences. Guarding the rectangle member with its NW4R type and assigning the returned rectangle directly corrected ten stack offsets. Several half-height multiplication temporaries altered allocation without reaching exactness. Dividing the centered height differences by 2 and computing the lower edge in a named scalar removed every remaining difference. Exact: 629/629 instructions, diffs 0.

## Validation scope

The unit remains `NonMatching`. All original code functions match; data has separate unresolved differences and no linking claim is made. All shared-header changes are guarded by `MYTIINPUTFORM_IMPLEMENTATION`, defined only in this source file.

The default gate merge-base is `112e4e1a`, for which the supplied tools have no baseline report. Gates use the available parent snapshot explicitly: `--base 0aca3c76`. No supplied baseline or tool was edited. Regression checks against that snapshot remain zero.
