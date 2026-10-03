# AOSS initialization source reconstruction, 2026-10-02

Baseline 3d3448e3. Only src/scene/setting/AOSS.c changed; ATERM, AOSSLink,
headers, metadata, and linking remain untouched. Read AGENTS and the AOSS,
round-five/six/seven, and fz1 attempt records before starting.

## Retained source boundaries

1. Restore the repeated initial-address status check and its cleanup block.
   In the target AOSS_Init_old object, the first address-setup error path ends
   at 0x6EC, followed by a second check and cleanup at 0x6F0-0x730 before the
   access-point allocation at 0x734. This check is redundant on the successful
   edge, but the original retains the complete branch and cleanup. A short
   source comment explains why it is not folded away in the reconstruction.
2. Give the send operation a local result separate from its socket descriptor.
   The target keeps the socket snapshot through send setup, but consumes each
   send return directly at the common result test. The previous source reused
   one long-lived variable for both roles and copied both call results into a
   saved register before testing them.
3. Restore two explicit zero/one/default timeout-error chains. Target error
   dispatch tests state zero first, then one, rather than using the previous
   switch's range dispatch.
4. Publish the next protocol state at the common reconnection join. The target
   carries the returned state through reconnect processing, then assigns the
   protocol-state local once. The old source assigned it before reconnect and
   repeated the assignment afterward.
5. Traverse the three request records with one actual array index. Both the
   six-byte address copy and the transaction-ID conversion use the same record.
   The previous source maintained an independent byte offset as well as the
   array index, producing a redundant second induction variable.
6. Restore retry and cleanup boundaries: one conditional-argument sleep call,
   no unused pre-sleep delay assignment, consistent large-delay-first update,
   and the target's nonnegative socket-cleanup test.

All changes are ordinary initialized C. No new qualifiers, helpers, assembly,
register declarations, data padding, or source/metadata pins were used.

## Measurements

| Cumulative source form | Init fuzzy | Instructions / 1584 |
| --- | ---: | ---: |
| Baseline | 93.78725% | 1575 |
| Timeout error chains | 94.41288% | 1571 |
| Also scoped send result | 94.454544% | 1569 |
| Also repeated address guard | 95.45013% | 1586 |
| Also receive-state join | 95.51326% | 1585 |
| Also request-record array traversal | 95.78409% | 1583 |
| Also retry/cleanup boundaries | 96.18624% | 1581 |

The instruction count need not monotonically approach the target: several
changes remove extra source instructions while the guard restores an omitted
block. Final Init remains nonexact. Unit fuzzy improves 96.777916% -> 97.71665%.
Exact functions remain 16/21, exact code 6436/16192, and data 3928/3928.
Every other AOSS function and every other unit's report remains unchanged.

Rejected experiments, all restored:

- Moving the receive-state join alone regressed the original baseline; it
  improved the retained scope/guard reconstruction when retested there.
- Grouping timeout/receive/descriptors into one real polling context regressed
  Init 95.51326 -> 95.29293. No stack-layout aggregate was retained.
- Deriving the current request record from an explicit byte cursor regressed
  95.51326 -> 95.423615; the final ordinary array traversal improved it.
- Original extracted BSS symbols have global binding, but making the actual
  CRC table global changed no instructions. Global packet-state/runtime
  definitions changed no instructions and regressed data; all restored.

## Hello and remaining limits

AOSSSendHelloRequest stays at 92.190475%, 271/273 instructions. Its target
materializes separate runtime/CRC/key-state bases; the source hoists a shared
BSS base. The fresh audit found no omitted packet, CRC, key-schedule, or socket
operation. Prior loop/temporary/register permutations were not repeated.

Init still differs in default-option object boundaries, redundant target
link-result branches, polling scratch lifetimes/stack slots, and register and
instruction scheduling. The preexisting initialized result fallback remains:
no undefined read was introduced to imitate the target's uncertain early
register use. No full-function, unit, or project-completion claim is made.

## Verification

- Configured only 43U with ../toolchain/wibo-build/wibo
- WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source build/43U/report.json build/43U/ok
- Pool identical (one ordinary .data string); every allocated data section is
  byte-identical to the fresh baseline and all five report 100%
- All 16 exact functions freshly verified with ctxdiff, zero differences
- Literal audit: 10 arguments across 16 exact functions; no skipped functions,
  candidates, or errors
- Complete reports: only AOSS changes; its only improved function is Init;
  no per-function, code, data, or cross-unit regression
- Focused native C harness passes 65536 retry spans, 20003 timeout-error states,
  and 65536 three-record initializations with boundary canaries. These check
  the rewritten local algorithms; they do not simulate network initialization
- Harness source/executable: /tmp/aoss-reconstruction-harness.c and the same
  path without .c in the current executor
- git diff --check passes
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d

GATE: nonregression, exact-function preservation, complete data, pool, focused
native tests, full 43U build, and DOL checks pass. Frozen for independent parent
review; this is partial source reconstruction only.
