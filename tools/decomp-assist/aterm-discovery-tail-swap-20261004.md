# ATERM Discovery: one bounded tail-statement swap

Accepted base `f7a1067224fe9fb17b7aea9c4fe5d62e7d0ecb99`, tree
`3e85cdf166d71675478bb53422eeae57c3f71543`. Exactly one authorized candidate:
move existing `recordIndex++` immediately before the existing BSSID cursor
advance at the end of the descriptor-copy loop. All expressions, types,
scopes, helpers, neighboring reads/stores/calls and descriptor advance stay fixed.
No other statement order was tested or authorized.

Canonical patch SHA256:
`d2f2f29ecd1556ee5cd13c607de61c95e52fd40f0a54ff699931ffdcc6d1b1d8`.
Selected source SHA256:
`842ad263c2e5a65352e138f29343d3c4b7ad5aab0e00be9975dbf40d6eebdc31`.

## Target evidence and limited historical novelty

The original advances SSID, record-owner and BSSID at +0x1B0/+0x1B4/+0x1B8,
then shifts descriptor length at +0x1BC and advances the scalar index at +0x1C0.
The accepted source advances SSID, BSSID and record-owner at
+0x1A8/+0x1AC/+0x1B0, then shifts length and advances the index.
The record-owner induction is generated from the existing indexed record fields.
The proposal was an uncertain scheduling probe, not recovered source provenance.

Surviving ATERM/sol-med logs cover indexed/cursor record views, descriptor
lifetimes, positive scan branches and delayed iteration initialization.
fz20 covers entry declaration searches and broader scan-boundary forms;
h2/h2b cover formatter/helper families. None preserves an explicit trial of
this adjacent tail swap. Missing individual historical sources prevent a global
novelty claim. The two missing target instructions concern already-tried
initialization and negative-scan CFG families; they remain absent.
Association's 133-instruction residual remains register-only and was untouched.

## Exactly three actual ordinary compiles

The clean worker leaf/cache was reused, preserving all previous evidence.
A fresh snapshot verified accepted-main source, all 1,027 source-object hashes,
full raw report and 639 immutable compiler/header/tool/configuration pins.
The real baseline compile reproduced all objects and the full report exactly.
Each compile preserves complete source/object snapshots, hashes, timestamps,
actual command argv/output and compilation evidence. Cached tools and ordinary
43U flags were unchanged; `WIBO_SJIS_MISSING_IMPORTS=1` was used.

Baseline, one candidate and selected source were compiled once each: total3.
The candidate received one individual official score from a private copy of the
actual objdiff configuration. No proxy, deduplication, adaptive search or extra
source variant was used.

- Discovery official98.28897 → 98.31939, strict+0.03042 points
- Unit97.73922 → 97.74089; global99.74069 → 99.740715
- Baseline/candidate/selected261 instructions,1044 bytes; target263,1052
- Selected whole object,43576 bytes:
  `d29024892430ec1a464fe399dd4d6d04b2a175e3a435b7a9153a8610b19caff9`
- Association98.7594 and all25 siblings retain identical bodies and reports
- Exact20/26, code12200/19204, data18584/18864 and link measures stay fixed
- OnlyATERM differs among1,027 objects; the full report has five fuzzy increases
  and no other changed field. All other1,026 complete unit reports are identical

## Precise induction, lifetime and ELF accounting

Only three existing `addi` words change scheduling:

| Owned offset | Baseline | Candidate |
|---|---|---|
| +0x1AC | r15 = r15+48, BSSID | r27 = r27+48, record-owner |
| +0x1B0 | r27 = r27+48, record-owner | r24 = r24+1, scalar index |
| +0x1B8 | r24 = r24+1, scalar index | r15 = r15+48, BSSID |

Each operation reads/writes only its distinct register and does not change CR
or XER. The intervening fixed shift touches r0 alone; no load, store, call,
branch or consumer lies between them. Independent affine updates commute for
all32-bit register values;512 edge-value combinations additionally agree.
All other actual instructions and every raw relocation byte are identical.

The source assignments affect independent, initialized, nonescaping locals.
recordIndex starts0; a valid entered loop has nonnegative result and index
strictly below the checked count, so its increment does not wrap. Existing
pointer operations, addresses and later uses are identical on the established
valid allocated-buffer domain. No input/alias/callback access moves and no
initialization bypass, dummy state or arithmetic reassociation is introduced.

The candidate improves record-owner placement but advances the scalar index
earlier and BSSID later than the target. Complete target scheduling is not
reproduced; this remains a small partial fuzzy gain.

The entire ELF differs in exactly seven bytes at file offsets
2632,2633,2637,2639,2644,2645,2647, all within those three owned.text words.
Every other ELF byte, including headers, section/symbol names, all145 symbol
entries, extents/types/bindings, raw allocated nontext, relocation tables,
outside-owned instructions and padding, is identical. No name normalization
or relocation exception is needed. All20 exact functions have fresh strict
target instruction differences0.

## Fresh bounded actual-PPC/reference tests

2076 distinct cases execute baseline/candidate/original:6228 actual executions
per completed run plus2076 sequential references. Coverage is261/261,261/261
and263/263 instructions. The standalone reproduction makes a second completed
worker run, totaling12456 passing actual executions. No model failure or
interpreter/reference correction occurred during this trial.

The accepted Discovery model's2008 cases are supplemented by68 multi-record
cases with counts0,1,2,3,5,7, four allocation layouts, selection/wait paths and
five callback profiles. An initial preparation/status estimate said88 added
cases; the actual Cartesian products, saved inputs and proof correctly contain68.

Every return, call argument/order, caller nonstack memory read/write trace,
actual formatter store and complete allocated final memory state agrees.
Stack/LR/nonvolatile preservation uses the original DOL-verified helper bodies.
Cases also cover all256 bytes at each MAC position, descriptor/SSID boundaries,
first/second allocation errors, scan error/oversize, cancellation, deadlines,
release mutations and reachable iteration299/300. Values>300 are unreachable
under the checked loop/ABI and are explicitly untested.

The prior accepted reference correction is retained: the independent ordinary
deadline read is linearized before the ordinary state/progress stores, matching
verified target behavior. Its initial literal-source trace failure and precise
storage/call-order justification remain immutable in the prior evidence.
No event filtering or generalization is added here. Private frame accesses are
ABI/state checked; only actual formatter frame stores are treated as observable
trace events, as in the previously accepted model.

SDK/libc callbacks are modeled to the same valid-buffer contracts. Complete
SDK/hardware behavior, arbitrary callbacks, overlapping copies, malformed or
out-of-bounds descriptors, invalid effective-type aliases, unchecked third
allocation failure, all64-bit times and exhaustive MAC/count domains are outside
this bounded proof. No hardware or formal verification claim is made.

## Final gates, evidence and replay

The selected compile reproduces the candidate entire object. Default full43U,
explicit ok, all1,027 object/report gates, pool0/0 and literal advisory pass.
Literal analysis covers24 functions/7 arguments with no candidates/errors;
existing unequal-size Discovery/RunConfig skips remain disclosed.
Current and original DOL are unchanged, SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`. Diff-check passes.
Parent independently reproduced the object/full-build gates and the2076-case
model to separate outputs.

Immutable evidence: `aterm-discovery-tail-swap-evidence/`, including
`proposed.patch`, all compile records/snapshots, frozen1,027-object manifests,
full reports, exact ELF/induction proofs, fresh model inputs/results and saved
validator. All prior closed evidence remains unchanged. Evidence stayed in
workspace storage above the1.1GiB+100MiB reserve.

Run the repository proof with saved authorized artifacts and a fresh output path:

```sh
.venv/bin/python tools/decomp-assist/aterm_discovery_tail_swap_audit.py \
  --baseline /path/to/baseline.o --candidate /path/to/selected.o \
  --original /path/to/original.o --dol /path/to/original-main.app \
  --symbols config/43U/symbols.txt --output-dir /path/to/fresh-proof
```

It reads inputs and writes proof outputs only; it does not compile or score.
No proprietary binary artifacts are committed. This one-candidate scope is
closed; no other statement order or residual family is claimed exhausted.
