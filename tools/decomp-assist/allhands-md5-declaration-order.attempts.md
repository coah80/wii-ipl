# MD5 bounded declaration-order continuation, 2026-10-03

Base: `b7a06e9d`, after the accepted sequential cursor helper from `55ff13a2`.
Only `libs/RevoEX/src/net/md5.c` and this log change. The parent authorized one
bounded official declaration search after confirming this source had not been
searched. No remote operation, extra search or custom variant was performed.

## Authorized range and run

Original lines 93..97 contain only five existing uninitialized declarations:
word, constant, index, round, block. The initialized state words on line 92,
static arrays, all assignments, expressions, scopes and both helpers stay
byte-for-byte unchanged. These independent scalar/pointer declarations have
no initialization side effects; every value is still assigned before use.

The earlier four-leaves-r11 search used different rotation code and a larger
block containing initialized state declarations. The accepted grouping and
cursor-helper attempts explicitly did not search this exact source.

After a fresh 43U baseline build and pool check, ran exactly once:

    WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
      PYTHONPATH=../local-tools ../.venv/bin/python -u \
      tools/decomp-assist/declsearch.py libs/RevoEX/src/net/md5 ProcessBlock \
      --version 43U --lines 93 97 --max-evals 23

The official structural/positional score trajectory was:
(5,212) -> (5,209) -> (5,202) -> (5,197).
The selected order is index, block, constant, round, word.

The run stopped at its 23-unique-evaluation bound, not a proven local fixed
point. The final order has 22 distinct swap/move neighbors, and the original
order is outside that neighborhood. Covering the final order, its entire
neighborhood and the already-tested original would require at least 24
unique evaluations. A later separately authorized finite continuation could
therefore be useful; none was run here. The tool's final rebuild is additional
to its 23 evaluations. This is not an exhaustive search of all 120 orders.

## Fresh retention gates

- ProcessBlock: 94.98366 -> 95.55556% fuzzy, 306/306 instructions. Positional
  ctxdiff decreases 212 -> 197; the official structural score remains 5.
- Unit: 96.63377 -> 97.01755%. Exact functions 3/4, code 600/1824 and data
  456/456 remain unchanged. This is a partial matching gain; linking is unchanged.
- NETMD5Init 16/16, NETMD5Update 60/60 and NETMD5GetDigest 74/74 remain literally
  instruction-exact against original and unchanged from baseline.
- .data 448 bytes and the existing .sdata byte/extent are unchanged. Empty
  pools identical. Literal advisory analyzes all four functions without
  candidates, skips or errors; there are no string arguments to check.
- Full 1,027-unit reports show only MD5 improved, with no fuzzy, exact-function,
  exact-code or data regression. The final report equals the candidate report.
- A fresh symbolic PPC instruction audit reduces the compiled candidate and
  original to the same unsigned 64-step MD5 recurrence, with identical selected
  addresses for 128 LE message loads, 64 constants and 48 indices. Only the four
  state words are written; count and block remain untouched.
- Production C passes 3,088 known-answer/seeded digest and chunking checks.
  RFC1321 padding is supplied externally; GetDigest's platform-endian stores
  remain instruction-exact and outside little-endian host test coverage.
- Production ProcessBlock passes 20,000 arbitrary-state/block comparisons with
  ASan/UBSan, preserving count, input block and canaries. Leak detection is
  disabled for ptrace; address and undefined-behavior instrumentation is enabled.
- Full 43U build and build/43U/ok pass. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`. git diff --check passes.

Private evidence: `/tmp/md5-declaration-order/` contains the exact search log,
source/object snapshots, reports, symbolic/host/sanitizer checks, pool/ctxdiff/
literal output and build logs. The read-only eligibility screen is separately
preserved in `/tmp/md5-declaration-screen/`. Original assembly/objects stay private.

GATE: passing bounded five-declaration-only partial gain, frozen for independent
review. No initializer, expression, statement, type, scope or helper changed.

## Finite continuation: local fixed point

Prepared base `32be36cb` plus cherry-picked source candidate `31dffe1b`.
Fresh configure/build verified ProcessBlock 95.55556% before the continuation.
The parent authorized exactly one further official run over the same five
uninitialized declarations, with --lines 93 97 --max-evals 120. No source type,
initializer, assignment, expression, scope or helper was changed.

The run started and finished at (5,197), without any intermediate improvement.
It stopped after 23 unique evaluations: the selected order and all 22 distinct
swap/move neighbors. This is a local fixed point of the official tool's scoring
and neighborhood, not the 120-evaluation cap or an exhaustive global optimum.
No additional run is authorized or planned.

The tool restored its initial source byte-for-byte. The complete rebuilt MD5
object and full 1,027-unit before/after/final reports are also byte-identical.
ProcessBlock remains 95.55556%, 306/306 instructions, 197 positional differences;
unit 97.01755%, exact APIs 3/4, code 600/1824 and data 456/456 are preserved.
Pool remains identical and all three public APIs remain instruction-exact.
Fresh full 43U build and build/43U/ok pass, with DOL SHA1 unchanged at
`26116613f624061ba99c8d1a299aaa6efa85670d`.

No semantic harness was rerun for the neutral continuation: both the entire
source and compiled object are identical to its already-validated baseline.
The earlier symbolic, 3,088-vector and 20,000-sanitizer gates therefore remain
applicable without claiming new test runs. This continuation changes only this
log; the source candidate from `31dffe1b` is preserved for consolidated review.

Private continuation evidence: `/tmp/md5-order-finish/`, including search.log,
source/object baseline, identical reports, pool/ctxdiff results and full gates.
GATE: neutral finite continuation closed at local fixed point; prior source gain
preserved, no further declaration search performed.
