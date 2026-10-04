# ATERM Discovery recovery after Association

Base accepted main `c5e1fe9cca350e658bf99aa50efd59ad16481f62`, tested tree
`84acfe394de296e3ed9d45b0b3cc9f828654da96`. One authorized source form in
`src/scene/setting/ATERM.c`; no compiler/header/configuration/linking changes.

## Exact recovered source and current-context reconciliation

`h2b.attempts.md:355–466` preserves the full081 patch. Applied to historical
34858f3f it reproduces SHA256
`9f59e4faaf4b304fff6c417a9e69bdb0657c39397ac290f0480ebfe448b1647d`,
exactly matching the logged compiled source identifier9f59e4faaf4b at line108.
Historical official98.28897%,261/263 instructions, unchanged exact/code/data,
empty identical pool and regressions[] were recorded. Lines144–172 restore all
nonexact Discovery trials; no separate source-quality/data rejection is recorded.
The old candidate object and complete compiler/header/config context were absent,
so this trial independently verified current context and behavior.

Association's accepted source already defined the identical hex-byte and MAC
helpers. This patch moves that single pair intact before Discovery, replaces
only Discovery's repeated formatting block with its recovered helper use, and
applies the archived shared-timeout join. No duplicate definition or new helper
form is introduced. Every Association body byte and all other function bodies,
globals, declarations and strings stay unchanged; the shared helpers only move.
Their two-caller/compiler-context risk was measured rather than assumed safe.

Canonical patch SHA256:
`e3d0833effdc722e8da188fa9de6570b9092ba8ab92042619b8fdf4e907bd074`.
Selected whole source SHA256:
`4e423db1558b85c81fd73e7434448cfdbf9ab73cefd08119188bc560532642f7`.
This is deliberate recovery of a previously tested family, not a novelty claim.

## Actual target primitives and source definedness

Original Discovery81402A24 has263 instructions/1052 bytes/frame0x90. Its MAC
formatting initializes6 at+0x228, sets the actual private output to stack+0x18,
establishes CTR at+0x240 and uses bdnz at+0x2BC. Baseline instead exits on the
sixth-byte equality test and uses an unconditional backedge. The real encoder
boundary restores the target counted-loop shape with identical byte operations.

Original iteration>=300 and final elapsed-time failure share result=-3 at+0x398.
Baseline duplicates it at+0x388/+0x3A8. The recovered timed_out label joins the
same two real failure paths. iteration>=300 still skips final OSGetTime/division;
on other paths the live deadline is still read after those calls. Equality is
still final success (now>deadline rejects); the unchanged loop-head >= test
still breaks. Cancel is only read on nonexpired final success. The direct jump
bypasses both now's assignment and all now reads, then assigns result=-3; no
uninitialized value or initialization-bypass mechanism is introduced.

The six live BSSID bytes are still read after the same selected-record copies.
Each produces high digit, low digit and NUL; the first five colons overwrite the
NUL, and finalNUL follows the sixth. u8 inputs0..255 yield initialized nibbles
0..15 and ASCII48..57/65..70. Both nibble entries are used; counters, pointer
difference2 and total length17 are in range. Existing32-byte output has maximum
write index17. No callback interposes within either formatting form.
selectedMacText has no later C consumer but already existed, and the target
actually performs these stores; no new dummy output storage is added.

All unchanged scan/record, allocation/clear, progress/error, global access and
release stages remain intact. Actual baseline/candidate scan prefix instructions
are identical except five necessary +8 branch destinations. The progress/loop
block moves by8 with exact opcode/operand/relocation correspondence and fixed
earlier backedges. Cleanup words are identical. No broader trace normalization
or source-form change is used.

All41 instructions in candidate MAC+0x220..+0x2C4 correspond to target+8 using
only the exact r9↔r5 dataflow exchange. All22 final-timeout instructions at
+0x354..+0x3AC correspond to target+8 using r26→r22. Immediates, operations,
branches and calls agree. These audit maps do not affect official scoring.
Two other target instructions remain absent; no exact-function claim is made.
Original DOL verifies221 nonrelocated words,17 direct-call destinations, and the
actual save/restore helper instructions used by the bounded model.

## Fresh ordinary compiles and official measurements

The clean independent leaf/cache was reused without another170MiB allocation.
Fresh accepted-main source/original/full report and all1027 object hashes were
frozen. The one ordinary baseline compile reproduced all1027 objects/full raw
report exactly. Immutable compiler/tool/config/header/log inputs639 pins were
checked throughout. No cached tool was modified, updated or downloaded.

Exactly3 actual ordinary source compiles: baseline, one candidate, selected.
No alternative, proxy filter, object deduplication, adaptive search or extra
source traversal occurred. Source/object bytes, hashes, timestamps, argv/output
and actual compiler evidence are preserved for each compile.

- Discovery official95.304184→98.28897, strict+2.984786 points
- Unit97.575714→97.73922; global99.73965→99.74069
- Baseline/candidate/selected261 instructions/1044 bytes; target263/1052
- Association remains98.7594 with its entire133-instruction body unchanged
- All25 sibling bodies/addresses/extents/full function reports are unchanged
- All20 existing exact functions retain strict instruction equality
- Exact20/26, code12200/19204, data18584/18864 and link measures are unchanged
- Existing280-byte RunConfig switch-table imperfection is unchanged
- Selected whole object:
  `5498cfc85de5aa41eec67d461c8d287aa62f2a3932414c83a6967d852fc8f813`

OnlyATERM changes among all1027 objects. Full-report changes are five fuzzy
increases; all other fields and1026 complete unit reports are byte-identical.

## Exact metadata and relocation accounting

ELF header, section order and every section header are identical. All145 raw
symbol entries retain exact type/binding/section/value/size/other fields. All
allocated nontext bytes and every text byte outside the owned extent are equal.
Four fixed-index local names change, each with identical entry and full extent:

- 22:@2652→@2680, .data+0, extent40
- 23:@2704→@2732, .data+40, extent132
- 24:@1036→@1018, .sdata2+0, extent7
- 25:@2844→@2872, .data+172, extent44

Exactly14 .rela.text entries shift their owned offsets: the BSSID pointer at
+0x224→+0x228, and thirteen progress/final-time entries by8. Every type, symbol
index, information word and addend is identical. All other relocation entries
and tables are unchanged. No broad name normalization is used. The conservative
initial descriptor-name warnings remain saved; exact per-record proof resolves
them without weakening relocation semantics.

Documentation correction: the prior Association prose mislabeled symbol24's
section as.sdata. Its frozen machine metadata and proof correctly say.sdata2.
The authorized one-line correction is included as a fourth changed path.
That typo never affected the four-pair proof or gates; prior evidence is intact.

## Fresh bounded whole-function PPC/reference proof

2008 distinct cases execute actual baseline/candidate/original functions:
6024 actual executions per completed run plus2008 sequential references.
Coverage is261/261,261/261 and263/263 instructions. Two completed worker runs
(initial corrected model and standalone reproduction) total12048 passing actual
executions. Parent independently reproduced2008/6024 with full coverage.

Return values, every call argument/order, all caller nonstack memory read/write
traces, actual private MAC stores and complete allocated memory state agree.
Stack/LR and all nonvolatile registers are preserved using the checked original
DOL save/restore helper bodies. Other private frame accesses are ABI/state-
checked rather than treated as externally observable order; that trace boundary
was fixed before the first execution and was not changed to hide a failure.

Cases cover all256 raw bytes independently at each of six MAC positions;
initialized variable descriptors/SSID bounds, counts0..2, first/second allocation
failures, scan error/oversize, cancellation before/after scan, selected-record
exits, progress callbacks and release ordering. Four valid allocation/alignment
layouts and five callback profiles modify legitimate globals or release targets.
Positive nonzero timer divisors and unsigned deadline equality/wrap boundaries
are tested. Reachable iteration299/300 paths verify late selection, cancellation
and iteration-limit laziness. Values>300 are unreachable under the checked
loop/ABI and are explicitly untested, not inferred covered.

Callees and callbacks are modeled to valid-buffer contracts, including libc,
scan/find, time/division, allocation/progress/release. Full SDK internals,
arbitrary callback programs, malformed/out-of-bounds descriptors, overlapping
copies, unchecked third-allocation failure and all64-bit clock combinations are
excluded. All concrete ELF relocations are rebased to private valid allocations.
No invalid effective-type alias, new undefined behavior, hardware or formal
proof is claimed. The unchecked third allocation may have other defined error
paths; this model requires a valid raw scan buffer and makes no blanket claim.

### Preserved failures and precise reference correction

Three pre-execution loader assertions were corrected: five shifted branch
destinations, moved unrelocated bl placeholder self-addresses, and Capstone's
numeric spelling of-8/-4 helper displacements. Exact decoded operands and raw
relocation semantics remain checked. Failed script versions are retained.

The first actual run passed all1536 MAC cases in all three objects, then its
first wait case failed against the literal-source reference trace on BASELINE:
actual read of deadline preceded the state2 store, while the reference reversed
these independent ordinary globals. It executed4609 actual function executions before failure;
that partial run is preserved separately and is not counted as a passing proof.

Concrete evidence verifies gAtermDeadline is ordinaryu32 in.sdata+0 and
state is ordinarys32 in.sbss+0. Original+0x2DC/+0x2E0, baseline+0x2CC/+0x2D0
and candidate+0x2D4/+0x2D8 are adjacent read/store instructions, with distinct
storage and no intervening call/volatile access. The reference now captures that
same ordinary deadline before the independent state/progress stores, aligned
to verified target behavior. No event was removed or generalized/filtered.
The first literal-source trace did not pass. Every corrected case then passed
exact trace/state comparison, including the standalone and parent reproductions.

## Final gates and repeatable proof

Selected compile reproduces the candidate whole object exactly. Default43U,
forced build/43U/ok, all1027 report/object gates and originalDOL preservation pass.
DOL SHA1:`26116613f624061ba99c8d1a299aaa6efa85670d`.
Empty0/0 pool is identical. Literal advisory analyzes24 functions/7 arguments,
no candidates/errors; existing unequal-extent Discovery/RunConfig are skipped.
Source diff-check passes. This remains a partial fuzzy gain, not complete matching.

Private evidence:`aterm-discovery-recovery-evidence/`, including saved validator,
three compile records, frozen reports/objects, precise metadata, model cases/
results, failed versions and the specific reference-linearization evidence.
All previous closed evidence is unchanged. This one fixed recovery is closed;
no further source form is authorized.

Run the standalone proof with authorized saved artifacts and a fresh output path:

```sh
.venv/bin/python tools/decomp-assist/aterm_discovery_recovery_audit.py \
  --baseline /path/to/baseline.o --candidate /path/to/selected.o \
  --original /path/to/original.o --dol /path/to/original-main.app \
  --symbols config/43U/symbols.txt --output-dir /path/to/fresh-proof
```

It reads those inputs and writes proof outputs only. It does not compile, score,
mutate a repository or include proprietary binary artifacts.
