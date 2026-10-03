# SD channel-order title declaration

Base: `e3095dfb979ded66d2b6a71228563066c5445f5a`.
Owned source: `src/scene/sdChannelSelect/iplSDChannelSelect.cpp` only.

## One retained declaration move

Move the existing uninitialized `ESTitleId titleId` declaration from the inner
order loop to immediately before the outer page loop. All assignments, reads,
conditions, calls and side effects stay at their original source positions.
No variable, initializer, cast, guard or operation is added.

This deliberately broadens the lexical lifetime of a genuinely used trivial
scalar. It is not a same-block declaration permutation or a behavior fix.
`ESTitleId` is `u64`, with no constructor or destructor. On every iteration,
the loaded-banner branch assigns the complete title type/code pair and the
unloaded branch assigns zero before either the exclusion checks or NAND-table
comparison can read it. The address never escapes. The previous iteration's
value cannot reach a use, and the scalar is not used outside the traversal.
Removing only its declaration from both versions leaves identical source text.
There is no newly observable lifetime effect.

The original function starts at `0x813DD3D8`, size 504 bytes. The candidate now
has the exact original assignment/exclusion sequence at offsets `+0x78..+0xAC`:
loaded entries overwrite both title words, unloaded entries zero both words,
then the first title tests occur. The original's 117 nonrelocated words and all
five direct calls were independently verified against the DOL. Candidate calls
at those same sites resolve to the same original destinations.

The prior lead is recorded in `fz16.attempts.md` lines 1570-1576 and repeated at
1795-1800 and 2176-2182: 126/126 instructions, 22 -> 7 positional differences,
restored while still nonexact. No prior isolated fuzzy score was recorded.
This run tested only the documented declaration location, not a new search or
an alternative within-loop ordering. The repository's `declsearch.py` was used
in `--score-only` mode before and after.

## Fresh results

- `collectTitlesByChannelOrder`: 97.29365% -> 98.007935%
- Instructions: unchanged 126/126; ctxdiff differences: 22 -> 7
- `declsearch.py --score-only`: structural/exact 2/22 -> 2/7
- Unit fuzzy: 99.76244% -> 99.77309%
- Exact functions: unchanged 123/129; matched code: unchanged 30344/33828 bytes
- Matched data: unchanged 2960/2960 bytes
- Every text byte outside the target function is identical to baseline
- All allocated non-text bytes, sizes and alignment are identical to baseline
- All 1561 relocation records are byte-identical
- The other 1026 unit reports are unchanged; no function regresses
- Pool: 101/101 identical before and after
- Literal audit: 73 arguments across 128 functions, no candidates/errors;
  the unchanged unequal-extent `create` function is the only skip
- Full 43U all_source/report/DOL gates pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check`: pass

The remaining seven differences are three channel-address register/operand
choices and four post-copy count/threshold scheduling instructions. They were
not modified or compensated for. This is a partial source-order gain, not an
exact-function or linking claim. Shared headers and all other source remain
unchanged.
