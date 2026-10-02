# One-key candidate boundary reconstruction, 2026-10-02

Parent commits: alpha 94b7f57e and 35677806, neutral Chinese ABI 105f3b45.
This pass changes only `libs/RVLMiddleware/eZiText/src/clib/zi81key.c`.
Alpha source/logs and Chinese source/log are unchanged.

## Retained target-defined boundaries

- `Zi8IsMatch1Key` consumes a halfword key. Six candidate calls narrow that
  argument after Zi8GetPCode: target +0x0B0C, +0x0F30, +0x16C0, +0x1BA4,
  +0x1F4C and +0x22A8. Restored the ziU16 formal and removed its three
  redundant key masks. The helper itself remains 97/97 instructions,
  objdiff 100%, ctxdiff diffs 0. All source call sites are in this same unit.
- Each of the six duplicate-bit checks consumes a byte result in the target.
  Made the byte conversion explicit at these call boundaries rather than
  changing the already-exact full-width duplicate helper.
- The user-dictionary availability result is narrowed to a byte at target
  +0x1E00. The existing full-width declaration remains; the caller now
  performs the demonstrated conversion explicitly.
- User ordinal decoding narrows the masked high byte to a halfword before
  its shift at target +0x1E44. Recovered that type boundary.
- Final output termination stores through the current output index and then
  increments that index without reloading it (+0x2524..+0x2534). Recovered
  the ordinary postfix-index store. Its right-hand side is constant zero,
  so there is no unsequenced index read/write.

These are source/ABI shape reconstructions with demonstrated target
conversions; no callee-saved-register or declaration-order sweep was used.

## Isolated source trials

Each trial used the exact 43U Ninja compiler command in `/tmp/ezi-onekey-pass`,
without modifying the worktree until the final candidate was selected.
Below: candidate-function fuzzy / unit fuzzy / matched data / exact functions.

- Halfword formal retaining old masks: 95.26784 / 97.65741 / 1232 / 4; rejected
- Byte duplicate-helper return: 94.73383 / 97.4822 / 1232 / 5; rejected
- Explicit duplicate-result bytes alone: same as preceding; not retained alone
- User-dictionary result byte alone: 95.240715 / 97.708664 / 1280 / 5
- User ordinal halfword alone: 95.30121 / 97.735695 / 1280 / 5
- Combined count-limit increments: 95.106384 / 97.64865 / 1232 / 5; rejected
- Terminal postfix index alone: 95.4368 / 97.79627 / 1280 / 5
- Halfword formal/old masks + duplicate bytes + limits:
  95.984566 / 97.97763 / 1232 / 4; rejected
- Halfword formal with ordinary typed uses:
  95.26784 / 97.72078 / 1232 / 5; restores the exact helper
- Typed key + duplicate bytes: 95.83312 / 97.97334 / 1280 / 5
- Typed key + duplicate bytes + count limits:
  95.984566 / 98.04101 / 1232 / 5; excluded for data regression
- Preceding plus terminal postfix: 96.01794 / 98.055916 / 1232 / 5; excluded
- Preceding plus user-dictionary/ordinal conversions:
  95.926155 / 98.01491 / 1232 / 5; excluded
- Typed key + duplicate bytes + terminal postfix:
  95.858154 / 97.98453 / 1280 / 5
- Typed key + duplicate bytes + user-dictionary byte:
  95.87484 / 97.99198 / 1280 / 5
- Typed key + duplicate bytes + ordinal halfword:
  95.93533 / 98.01901 / 1280 / 5
- Typed key + duplicate bytes + terminal postfix + user-dictionary byte:
  95.86858 / 97.98919 / 1280 / 5
- Typed key + duplicate bytes + terminal postfix + ordinal halfword:
  95.98957 / 98.04324 / 1280 / 5
- Final complete boundary subset: 96.41927 / 98.23523 / 1280 / 5

After selecting that subset, the three count-limit blocks were tested
individually against it. OEM: 96.17564 / 98.12637 / 1280 / 5; PUD:
95.725075 / 97.92507 / 1232 / 5; phrase: 95.93575 / 98.019196 / 1280 / 5.
All three were rejected. No count-limit rewrite remains in the candidate.

## Full validation and exact data disclosure

Fresh report `/tmp/ezi-onekey-boundary.json`; full-build log
`/tmp/ezi-onekey-boundary-build.log`.

Unit fuzzy 97.778564% -> 98.23523%. Candidate-function fuzzy
95.39716% -> 96.41927%, about 98 fewer weighted deficit bytes.
Exact functions remain 5/9; exact code remains 3952/21460;
matched data remains 1280/1388. All five baseline exact functions have
ctxdiff diffs 0 and identical instruction counts.

Candidate instructions: 2387 -> 2405 versus target 2397; size
0x254C -> 0x2594 versus target 0x2574. Frame remains 0x140.
It is not exact, and no new exact function is claimed.

The spelling tables remain 1152 byte-identical bytes. .sdata2 and extab
remain byte-identical at 8 and 72 bytes. The switch table's source is 44
bytes versus target 48, the pre-existing four-byte section-alignment tail;
all 44 bytes and all eleven canonical relocation targets/addends match.
No real data object was resized or renamed and no padding was added.

The already-unmatched 108-byte extabindex still has two differing bytes at
0x4F and 0x5B, with the same 98.14815% section score. They are the function
extent words: spelling remains 0x1A94 versus target 0x1A90; candidate extent
changes from 0x254C to 0x2594 versus target 0x2574. This is changed unmatched
metadata, not a claim that all data bytes are unchanged.

Pool check: identical (no narrow strings). Advisory branch mapping: all 351
pairs preserve their destination and all 71 helper calls correspond. A
register-value-aware linear audit pairs 621 observable store/call/branch
effects. The seven missing byte-boundary differences are resolved; its
remaining three differences are the unchanged count-limit reloads, not a
formal proof or an exactness claim.

Full 43U build succeeds with the approved wrapper and
WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
`git diff --check` succeeds. No remote, linking, shared-header, assembly,
volatile, register-forcing, dummy-storage or undefined-value changes.
