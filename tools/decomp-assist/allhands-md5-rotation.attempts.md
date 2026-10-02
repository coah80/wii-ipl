# MD5 rotation-expression reconstruction, 2026-10-02

Baseline: `449529d9`, 43U only. Owned source: `libs/RevoEX/src/net/md5.c`.
The current user priority permits validated structural/fuzzy improvements before
exact matching and linking. This is a partial matching candidate, not an exact
match or a linking change. AES experiments were saved outside the checkout and
AES was restored to the baseline before this candidate was validated.

## Source evidence

- Ground truth: `build/43U/obj/libs/RevoEX/src/net/md5.o`, `ProcessBlock`.
- The target is 0x4C8 bytes / 306 instructions, with a 0x20-byte stack frame.
- Each of the sixteen unrolled MD5 steps contains two byte-reversed word loads.
  The first pair is at function-relative offsets 0x3C and 0x40. The right-shift
  half consumes the first value, and the left-shift half consumes the second.
- The target retains four additions across the two rotation halves: the
  right-shift half adds the message word to (round constant + state), and the
  left-shift half adds the state to (message word + round constant). The state
  includes the round Boolean function. The first rotation uses right shift 25
  and left shift 7; the remaining shifts follow the existing MD5 round schedule.
- The index-table address is first materialized after the first sixteen steps,
  rather than before the sequential-word round.
- The inline helper expresses these real unsigned 32-bit operands and restores
  the target-sized body. It introduces no assembly, volatile qualifier,
  uninitialized value, fake storage, padding, or compiler-option change.
- All four round algorithms, all 64 constants, all 48 indices, and all public
  API bodies are otherwise unchanged. The old ROTATE macro became unused and
  was removed.

## Attempts

1. Direct pointer-form byte-reversed loads and alternate ordinary arithmetic
   groupings: 274-294 instructions, at best near the starting score. Rejected.
2. A typed inline endian-load wrapper: improved instruction similarity but
   retained 276 instructions and insufficient target operation boundaries.
3. Rotation-expression helpers without independent load results: 288-290
   instructions, approximately 41-44% ProcessBlock fuzzy. Rejected.
4. Explicitly named byte-reversed operands for the two rotation halves:
   306 instructions / 81.82026% fuzzy. Retained the target's first-read/right-
   shift ordering. Reversing those loads reached 82.0% but added two instructions
   and contradicted the target's operand ordering, so it was rejected.
5. Sequential partial-sum statements and equivalent regroupings did not
   improve the retained structural form. No register-only declaration sweep.

## Validation

Command setup:
`python3 configure.py --version 43U --wrapper ../toolchain/wibo-build/wibo`
`WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja`

- `pool_diff.py`: identical empty MD5 string pool, 0/0 strings.
- `.data`: all 448 bytes identical. The source `.sdata` is the one-byte
  end marker (0x80); the target has the same byte followed by seven alignment
  zeros. This existing section-size difference is unchanged, and objdiff
  reports `.sdata` and unit data at 100%. No padding was added.
- `NETMD5Init`: 16/16 instructions, ctxdiff diffs 0, objdiff 100%.
- `NETMD5Update`: 60/60 instructions, ctxdiff diffs 0, objdiff 100%.
- `NETMD5GetDigest`: 74/74 instructions, ctxdiff diffs 0, objdiff 100%.
- `ProcessBlock`: 294 -> 306 instructions against target 306;
  43.290848 -> 81.82026% fuzzy. Final ctxdiff has 255 positional differences,
  primarily allocation, scheduling and remaining arithmetic grouping. Not exact.
- MD5 unit: 61.945175 -> 87.80044% fuzzy; exact 3/4 -> 3/4;
  exact code 600/1824 unchanged; data 456/456 (100%) unchanged; unlinked unchanged.
- Full 1027-unit report: no unit regressed in exact functions, exact code,
  exact data or fuzzy score versus the baseline report. Overall fuzzy moved
  99.588615 -> 99.60437%; exact code and linking did not change.
- Full 43U build passed. `build/43U/ok` passed. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Host algorithm validation: `/tmp/crypto-remainder/validate_md5.py` compiles the
production source unchanged with host shims for PPC byte-reversed intrinsics.
It verifies ProcessBlock through NETMD5Update with externally supplied RFC1321
padding, comparing state words with Python hashlib. The host test deliberately
does not exercise GetDigest's platform-specific big-endian length stores.

Result: 3,088 successful digest/chunking comparisons, covering the seven RFC1321
example strings, one million `a` bytes, 1,500 seeded messages, lengths around
55/56/63/64/65 and larger block boundaries, and fixed/random chunk sizes.
Run: `python3 /tmp/crypto-remainder/validate_md5.py`.

Local evidence (not committed or uploaded): `/tmp/crypto-remainder/md5.target`,
`md5-final.ctx`, `md5-final.json`, `baseline.json`, `full-build.log`, and the
host test plus its header shim. Only source and this summary are committed.

GATE: partial decompilation candidate validated; no regressions; exact matching
and linking remain open. No claim of all-100% completion.
