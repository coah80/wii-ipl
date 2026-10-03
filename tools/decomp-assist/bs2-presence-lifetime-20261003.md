# BS2Tick disk-presence read lifetime, 2026-10-03

Base: `84d0c74f0ae814354a805907299bb7ff79243ece`, 43U only.
The only source change is in `src/BS2/BS2Mach.c`, case 0 of `BS2Tick`.

## Source evidence

The original function begins at `0x8137D3B8`. Its case-zero initialization
reads `BS2NoDisk` at `+0xC8`, stores `AudioBufferUnconfigured` at `+0xCC`,
compares the captured disk flag at `+0xD0`, and clears `CoverBlock.state` at
`+0xD4`. The baseline clears the cover state before reading the disk flag.
The extracted object's relocations and all 29 instructions in this
initialization slice agree with the original linked DOL.

Capture `BS2NoDisk` in the existing `s32 status` before the audio and cover
resets, then test that captured value. `BS2NoDisk` is already declared
`vBOOL`; `CoverBlock.state` is already volatile in this translation unit.
Their distinct addresses are `0x816989E4` and `0x8108BF6C`. No qualifier,
storage, callback, initialization, or shared-header change is needed.

The assigned status is genuinely consumed by the zero/nonzero branch.
Case 0 always exits the switch, so it cannot carry this value into another
case. All later status consumers have their own preceding assignment;
the declaration and all their statements are unchanged. The function enters
with interrupts disabled. This reconstructs the target's access order; it
does not claim an observed runtime failure or asynchronous pointer replacement.

Historical lead: `big1.attempts.md:509` records the same disk-presence
snapshot within an earlier compound candidate, with a partial improvement
from 98.67783% to 98.77062% and no exact/code/data regression. That compound
was not present in this baseline. Its larger 99.106186% score includes other
changes and is not attributed to this isolated edit. No prior source artifact
was imported; the target instructions independently support this change.

## Single measured trial

| Measure | Baseline | Candidate |
| --- | ---: | ---: |
| BS2Tick fuzzy | 98.639175% | 98.73196% |
| BS2Tick instructions / original | 1937 / 1940 | 1937 / 1940 |
| Unit fuzzy | 99.09658% | 99.138985% |
| Exact functions | 25 / 29 | 25 / 29 |
| Matched code bytes | 5112 / 16980 | 5112 / 16980 |
| Matched data bytes | 155504 / 158528 | 155504 / 158528 |

The compiler changes eleven instructions, all between function offsets
`+0x9C` and `+0xD4`. Three relocation positions move inside the slice;
all 1461 relocation identities, their count, and every relocation elsewhere
are preserved. All text outside BS2Tick and every allocated nontext byte
remain identical. Each of the 25 exact functions remains instruction-exact.
All other 1026 unit reports are unchanged.

## Validation

- A bounded interpreter executes the actual baseline, candidate, and original
  initialization slices for 10036 flag combinations, including signed/unsigned
  boundaries, both zero/nonzero classes, and deterministic 32-bit samples.
  It reaches every one of the 29 instructions in each slice. Final memory
  and next-state choices agree; candidate disk/audio/cover/state access order
  agrees with the original. A wrong signed test is detected.
- The predicate is exactly word equality to zero, so its two equivalence
  classes cover the full 32-bit flag domain; this is not a claim of exhaustive
  execution of all 2^64 input pairs or the complete Wii runtime.
- All 201 original direct-call targets agree with raw DOL addresses. Candidate
  and baseline call sites and destinations are unchanged, including callbacks.
- `pool_diff.py`: 91/91 identical strings.
- Literal audit: 97 arguments across 28 functions, no candidates/errors;
  BS2Tick remains the existing unequal-extent skip.
- Full `all_source`, fresh report, and `build/43U/ok` pass.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passes. No linking/configuration or assembly changes.

Private local validation: `validation/bs2-presence-lifetime-20261003/check.py`
and `check.json` under the shared workspace. Baseline/candidate objects,
reports, and build/pool/literal/ctxdiff logs are retained in
`/tmp/bs2-presence-lifetime/`. Original binary/instruction material is not
included in this commit.
