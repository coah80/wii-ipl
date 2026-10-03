# AOSS sleep return-type contract

Base: `7b324519`, 43U. One local declaration changes from `int` to `void`.
No function body, shared header, countdown, callback, data or linking change.

`AOSS.c` declared `AOSSi_Sleep(u32)` as returning `int`, while its definition
in `AOSSLink.c` returns `void`. The correction makes those function types
compatible. It is source-type correctness, with no matching percentage gain.

## Original evidence

- The SHA1-verified original DOL has a single tail branch at `0x813FD998`
  to `AOSSi_SleepMs` at `0x813FD18C`; both existing source functions return
  `void`, and both already match their original bodies
- A raw-DOL scan of all recorded text functions finds exactly six calls to
  `AOSSi_Sleep`, all within `AOSS_Init_old`
- Every source call is an expression statement. A control-flow walk from each
  original call proves that return register r3 is overwritten before any read,
  subsequent call or return on every reachable path through that local region
- The argument remains the same unsigned 32-bit millisecond count; all sleep,
  cancellation, countdown and callback timing is unchanged

## Verification

- Fresh baseline and candidate AOSS objects are byte-identical as entire files,
  including all sections, symbols and relocations
- Full default 43U rebuild passes; all 1,027 source objects are byte-identical
  to the pinned main baseline
- Fresh complete progress/report is exactly equal to baseline
- All 16 previously exact AOSS functions retain identical instruction streams
- AOSS remains 16/21 exact, 6,436/16,192 exact code bytes, 3,928/3,928 data
  bytes and 97.71665% fuzzy
- Pool: 1/1 identical. Literal audit: 12 arguments across 19 functions,
  no candidates or errors; Init and Hello retain their existing unequal-size
  skips
- Default build, explicit progress/report and `build/43U/ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

No live network or Wii execution was performed. Behavioral neutrality follows
from unchanged emitted objects and the independently checked call contract.
Original binary/disassembly evidence remains private and is not included.
