# o-sections: linked units with .text section below 100%

Task: `check_decomp_complete.py` failed on three linked units whose functions were
all 100% but whose `.text` section score was not: iplSound 99.49785,
iplBoardObject 99.73868, iplButton 98.53095.

## Cause

objdiff 3.4.5 scores a code section as the size-weighted mean of the target
symbols' match percent, with an unpaired target symbol counted as 0
(`diff_generic_section` in objdiff-core/src/diff/data.rs). The per-function list
in the report hides this: for a `complete` unit, `report.rs` falls back to 100%
when a target symbol has no partner. Pairing is by exact name, plus
`name$<digits>` against `name$<digits>` (`symbol_name_matches`). The report
ignores objdiff.json `symbol_mappings` (it uses `MappingConfig::default()`).

Each unit had exactly one unpaired target function, equal to the missing bytes:

| unit | target symbol | built symbol | bytes |
|------|---------------|--------------|-------|
| iplSound | `__dt__Q33ipl3snd6UnkClsFv` | `__arraydtor$15981` | 0x1c |
| iplBoardObject | `init__Q43ipl5scene11BoardObject29@class$8157iplBoardObject_cppFv` | `...30@class$12470...` | 0x18 |
| iplButton | `push__Q33ipl7utility36Queue<Q43ipl5scene6Button7Command,8>FRCQ43ipl5scene6Button7Command` | `push_button_queue` | 0x70 |

Extra weak or dead-stripped functions in the built objects do not affect the
score (only target symbols count).

## Fixes

- iplSound: the target function is `__destroy_arr(_seBlk, ~tagSSeInfo, 0xc, 16)`,
  the compiler's array destructor for `tagSSeInfo _seBlk[16]`; `UnkCls` was a
  placeholder. Renamed in symbols.txt to `__arraydtor$15982`. The `$<digits>`
  rule pairs it with any number, so header churn cannot break it.
- iplBoardObject: the `@class$NNNN<file>` id is a TU-wide counter that moves
  with any earlier header change (30039 -> 8157 upstream, now 12470; my
  iplQueue.h change alone moved it to 12471). objdiff cannot pair it unless the
  number is exact, so a symbols.txt resync would go stale on the next header
  edit. Named the class `StandData` (identical code) and renamed the symbol to
  `init__Q43ipl5scene11BoardObject9StandDataFv`.
- iplButton: `push_button_queue` was an extern "C" stand-in (first asm, then C)
  for `mReservedCmd.push(command)`, added because the in-class `Queue::push`
  instance is emitted right after `reserveAnm` (DOL mismatch). In the target,
  `push` is the last function before the `@20@` dtor thunk, and in
  NandSDCardManager all Queue instances sit at the end of the TU in first-use
  order (push<Thumb,15>, pop<Thumb,15>, push<Command,4>), with single-caller
  pop<Command,4> inlined. That is deferred template instantiation: `push` and
  `pop` were defined outside the class. Moved both out of class in
  `utility/iplQueue.h` and restored `mReservedCmd.push(command)`.
- iplNandSDCardManager: its `#pragma sym on` ("actually needed to match") was
  the old workaround for the same placement. With out-of-class push/pop the
  pragma splits three ordinary functions into a second `.text`; without it the
  layout matches the target. Removed it. Same 72 functions, identical bytes.

## Results

- `.text`: iplSound 100, iplBoardObject 100, iplButton 100; NandSDCardManager,
  iplBoard and iplSceneManager still 100 in every section.
- Pools identical in all five touched units; DOL SHA1 unchanged.
- check_decomp_complete.py: only remaining failure is main/src/keyboard/tiString
  (`inputChar__Q39textinput8tistring9DecolatedFw` 93.55882, unit not linked).

## Tried and rejected

- Template `push` in-class (da7 queue-01): exact bytes but placed after
  reserveAnm, DOL changes.
- Out-of-class push with `#pragma sym on` kept in NandSDCardManager:
  on_get_thumbnail, clean_command_queue and getAsyncResult move into the
  second `.text`; layout breaks.
- Out-of-class push only (pop in-class), no sym pragma: push instances at the
  end but pop<Thumb,15> stays mid-file; target needs it between the pushes.
- symbols.txt resync to `@class$12470`: works now, breaks on the next header edit.
