# Card icon and move/copy reconstruction

Base: `13881c99`; branch `agent/bittle/card-icon-reconstruction`.
Owned source: `src/scene/cardSequence/iplCardSequence.cpp` only.
No headers, linking configuration, assembly, forced registers, volatile casts,
undefined values, or dummy storage were introduced.

## Retained: reset the temporary name on every move rename attempt

The target's rename-collision loop returns to the filename clearing call before
formatting the next temporary name. The reconstruction returned directly to the
formatting call, clearing the filename only on the first attempt.

Moved the existing filename `memset` into the `do` loop. This changes exactly one
compiled branch instruction word; every other allocated byte in the object is
unchanged from the baseline. It restores the target's per-attempt reset boundary.
It is not a claim that ordinary fixed-width temporary names previously produced
incorrect filenames; the SDK status routine also normalizes trailing name bytes.

- `runCardMoveOrCopy`: 97.804276 -> 97.8125 fuzzy
- Instructions: 608/608; ctxdiff differences: 186 -> 185
- Unit fuzzy: 97.198944 -> 97.20097
- Exact functions remain 27/30; matched code remains 4168/9852 bytes
- All 30 function scores preserved or improved
- All 27 exact functions checked individually: objdiff 100, ctxdiff zero
- Data remains 1496/1496 bytes exact

## Validation

- Full 43U build: PASS
- Pool before and after: identical, 43 strings
- Literal-reference advisory: 45 arguments in 29 functions; no candidates or
  errors. The unequal-sized icon loader was skipped; it was not changed
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Base-relative `git diff --check 13881c99`: PASS

A focused compiled-PPC loop audit passed 192 cases covering both slots, file
numbers 0/63/126, collision counts 0/1/2/7/63/126/127/128, and final results
0/-3/-7/-10. Candidate instruction execution produced the target's memory state
and call trace in every case. The baseline omitted the repeated clear in 174
cases. `memset`, `sprintf`, and status results were modeled, so this is bounded
loop evidence, not execution of the complete copy/move operation or Wii runtime.

## Icon-loader audit and deferred boundary

The loader was inspected against the target and tested with a bounded integer
PPC interpreter using modeled CARD, memory-copy and cache-store calls.

- 841 valid-format, bounds and error cases agreed on return values, modeled
  call traces and non-stack memory, including guard regions
- Both slots and file-table endpoints, banner modes, icon formats 0/1/2,
  animation speeds, sector errors, image/comment read failures, close failures,
  and offset boundaries were exercised
- Valid-case instruction coverage was 506/508 source and 511/512 target; this is
  instruction-address coverage, not exhaustive inputs or paths
- All interpreted calls checked SP, LR and nonvolatile GPR restoration

Six reserved-format examples exposed a separate difference: after a preceding
valid icon, format 3 retains the preceding icon's byte size in the target, while
the current source resets it to zero. This affects later offsets and modeled
image-read lengths. Format 3 is not among the SDK's supported icon formats.
When the first icon has format 3, the target has no uniquely established initial
size; that unspecified boundary must not be reconstructed with an invented
initial value or an uninitialized C local.

An explicitly initialized carry trial agreed with the six later-format-3 cases
and all 841 earlier cases, but reduced loader fuzzy from 90.34375 to 90.14844.
It was restored. Its patch and bounded evidence are preserved privately for
possible later review. The retained source does not claim to correct this
reserved-input boundary or to establish general runtime correctness.

## Existing external branch

Read-only inspection of the already fetched `origin/agent/w1008/card2` at
`14b921b3` found a restructuring of the image-read success/error join. It has the
same effective error propagation as the current source. It was not copied,
merged, or used as a replacement implementation; no remote action was taken.
