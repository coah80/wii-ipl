# ATERM association formatting recovery

Base main `9aa4a0d88748808c5b1e3a9e62518641a5624a72`, tree
`125f757de23bda7b0b8cad78472508a5f94a0506`. One authorized recovered source
form in `src/scene/setting/ATERM.c`, function `ATERMBuildAssociationRequest`.
No discovery/protocol/AES, header, compiler/configuration or linking changes.

## Recovered provenance and reason for restoration

`h2b.attempts.md:240–353` preserves the complete trial61 diff. Applying it to
historical34858f3f reproduces whole-source SHA256
`6fa4cc5bdf9ec05f63b18be1e148ccdfa3b61438f40c3e87342ae09c33047998`,
exactly matching its logged compiled-source identifier6fa4cc5bdf9e at line88.
This is exact recovered source provenance, rather than an inferred spelling.
The old candidate object and raw sibling hashes are unavailable.

The log records official98.7594%,133/133 instructions,28 raw differences,
unchanged19 exact functions/11584 code/18584 data bytes, empty identical pool
and regressions[]. Lines144–174 explicitly restore every nonexact association
trial; only exact StartNetworkStack was retained. No separate source-quality
or data rejection is recorded for61. The nearby AOSS trial12's data loss and
uninitialized guard experiments were not imported. Its final clean gate did
not independently accept this discarded association candidate.

Current association body is byte-identical to the historical baseline. The
subsequent real network-global split and exact StartNetworkStack remain intact.
Only the archived61 helpers and two formatting uses are recovered. This is a
previously tested family, with no claim of new source-form novelty.

Canonical current patch SHA256:
`72757f427659688e0a58a05e6b2efd1e02e2341b1be7754b60bb6d0df85edd73`.
Selected whole source SHA256:
`e0eafa41540c9424bac5bad7cd0b5d2118473e14bc4830c6215e723d3e00dc12`.

## Actual target discrepancy and source contract

Original function814031DC has count6 at+0xC0 and+0x15C, mtctr at+0xD8 and
+0x174, and bdnz at+0x154 and+0x1F0. Baseline uses end-pointer cmplw/blt.
The recovered nested hex-byte/MAC encoders restore both counted-loop primitives.
All133 candidate/target mnemonics, immediates, branches and calls correspond.
Exactly28 remaining raw operand differences follow these independently checked
region dataflow maps:

- +0xC0..+0x158: candidate r9→target r5 and candidate r5→target r9
- +0x158..+0x1FC: candidate r9→r5, r5→r6, r4→r9 and r6→r4

Unlisted registers remain identical. These maps explain residual operands;
they do not change objects, compiler choices or official scoring. Both pre-
format call/control blocks and the epilogue retain identical raw words.
OriginalDOL independently verifies120 nonrelocated words and all9 direct-call
destinations. No register forcing is used; the function remains nonexact.

The two nibble entries are initialized and actually read by a bounded encoder
loop. No dummy/unused state, artificial guard or initializer bypass is added.
For every u8 input0..255, both nibbles are0..15 and produce ASCII48..57 or65..70.
Indices0..2/0..6, pointer difference2 and output length17 fit their signed types.
The two six-byte inputs remain inside the existing8-byte buffers; the maximum
formatted write index17 remains inside each existing32-byte text buffer.

Each byte load is followed by high digit, low digit and NUL stores. The first
five colons overwrite that NUL; the sixth leaves it, followed by finalNUL.
Both addresses and every existing pre-format call, argument, request store,
metadata read and global-flag guard keep their original order. The arrays
remain private; no helper introduces callbacks, escaped addresses or loads
from live caller state. The text arrays have no later C consumer, but both
already exist and the original actually performs their stores. No new dead
output storage is introduced to mimic those stores.

## Fresh independent build and official measurements

Reused a clean independent43U leaf/cache with only permitted prior documentation
commits differing from main. All1027 cached objects and full raw report were
verified against a newly frozen main reference before a fresh ordinary baseline
compile. The compile reproduced every object/report byte. Cached tool/wrapper,
compiler/configuration/header/source/log context639 pins were verified; tools
were not downloaded or modified.

Exactly3 actual ordinary source compiles: one baseline, one candidate and one
selected compile. There were no alternatives, proxy scores, deduplication or
adaptive searches. Every compile has immutable source/object bytes, hashes,
timestamps, full argv, output and actual compiler evidence.

- Function official:93.44361→98.7594, a strict+5.31579-point gain
- Unit official:97.42845→97.575714
- Global official:99.73871→99.73965
- Baseline/candidate/selected/target:133 instructions,532 bytes, frame0x60
- Exact functions20/26, code12200/19204, data18584/18864: unchanged
- The existing280-byte ATERMRun switch-table imperfection remains unchanged
- Selected whole object:
  `feacf87770e385fe70dca985be22c1b93bfd557dea6855d9d60977f506ad31c2`

OnlyATERM changes among all1027 source objects. Full-report changes are five
fuzzy increases; all other fields and1026 complete unit reports are identical.
All25 sibling bodies, addresses, extents and full function reports are identical.
All.text bytes outside the owned extent, including padding, are identical.
All20 existing exact functions retain zero strict instruction differences.

## Exact metadata and relocation accounting

ELF header, section order and every section header are identical. All145 raw
symbol-table entries retain their exact type, binding, section, value, size and
other fields. All raw relocation-table bytes are identical. Allocated nontext
bytes are identical. Only owned.text bytes and.strtab spelling bytes change.

Four concrete compiler-local object names change at fixed symbol indices:

- 22:@2600→@2652, .data+0, extent40
- 23:@2652→@2704, .data+40, extent132
- 24:@1043→@1036, .sdata+0, extent7
- 25:@2792→@2844, .data+172, extent44

Each entry and its entire allocated raw extent is independently byte-verified.
No blanket prefix stripping or broad name normalization is used. The initial
conservative name-sensitive relocation gate flagged three siblings; its failed
record remains preserved. Exact four-pair/stable-index/raw-table proof resolves
those descriptor-name warnings without weakening the actual relocation gate.

## Fresh bounded actual-PPC/reference proof

6656 distinct cases execute the whole actual baseline, candidate and original
functions:19968 actual executions per run, plus6656 independent sequential
source-reference executions. Worker initial and two fresh standalone-reproduction runs
all pass:59904 worker actual executions total. Parent separately reproduced
the whole proof from saved objects in its own validation outputs.

Coverage is133/133 instructions for each of the three objects. Return values,
call arguments/order, every memory read/write trace and complete allocated
memory state agree with the sequential reference. Stack/LR and all nonvolatile
registers are preserved. Candidate's high/low/NUL/colon store ordering agrees
exactly with original and baseline.

Cases include every raw input-byte value independently at every one of six
positions of both MAC arrays,64 structured MAC pairs and512 deterministic
random pairs. The selected BSSID's first-byte bit1 remains cleared as before.
Four valid request layouts cover disjoint storage and contained aliases with
addressBuffer, selectedBssid and the shared-address flag. Four NCD callback
profiles mutate valid request/global fields or flags after producing six valid
bytes. NCD return probes include-5,-1,0,1; all output bytes remain initialized.
All memcpy ranges are allocated and nonoverlapping.

Two preexisting original/source global spellings are explicitly paired at exact
relocation sites: gAtermProductName/lbl_81697248 at+8, .sdata+48, and
gAtermUseSharedAddress/lbl_81697244 at+0xB4, .sdata+44. Section/value/addend/type
and all other relocation properties agree. These are not new trial renames.

Limits: this is a bounded actual-instruction interpreter, not hardware or formal
proof. memcpy/memcmp/NCD are modeled to valid-buffer contracts, not full SDK
implementations. Concrete ELF relocations are rebased to private valid model
allocations. Four alias/callback layouts do not exhaust arbitrary callers or
2^96 MAC-pair inputs. An NCD failure leaving unwritten bytes is neither exploited
nor newly defined. No malformed pointer/out-of-bounds callback claim is made.

The first proof-loader assertion compared preexisting global spellings literally
and stopped before cases. It was replaced by the two exact site/type/section/
value pairs above. The failed initial script is preserved; no source compile
was repeated. This does not weaken baseline/candidate raw relocation identity.

## Final gates and repeatable proof

Selected ordinary compile reproduces the candidate whole object exactly.
Default43U build, forced build/43U/ok, all1027 report/object accounting and
originalDOL preservation pass. DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.
Pool0/0 identical. Literal advisory analyzes24 functions/7 arguments, with no
candidates/errors; only existing unequal-extent Discovery/RunConfig are skipped.
Source diff-check passes. No new exact or complete-linking claim is made.

Private workspace evidence is `aterm-association-recovery-evidence/`, including
`validate_saved.py`, actual compile records, saved reports/objects, exact
metadata accounting and bounded model inputs/results. Earlier card and IDCT/JPEG
trial evidence remains untouched. This one association recovery is closed with
a retained gain. Discovery is a separate reserved scope, not part of this trial.

Repeat the standalone proof against saved authorized local artifacts; output
directory must be fresh:

```sh
.venv/bin/python tools/decomp-assist/aterm_association_recovery_audit.py \
  --baseline /path/to/baseline.o --candidate /path/to/selected.o \
  --original /path/to/original.o --dol /path/to/original-main.app \
  --symbols config/43U/symbols.txt --output-dir /path/to/fresh-proof
```

The script only reads those inputs and writes its proof outputs. It does not
compile, score, modify a repository or include proprietary binary artifacts.
