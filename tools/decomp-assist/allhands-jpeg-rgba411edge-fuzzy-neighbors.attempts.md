# RGBA411 edge: recover an official-fuzzy declaration gain

Base `57c17ebe2a7b3788cbbbf54f7dc9a9fb35abaec8`, 43U only; branch
`agent/bittle/jpeg-rgba411edge-fuzzy-neighbors`. The retained source swaps only
`chromaSkip` and `output` declarations, improving the target from **94.10714% to
94.24107%**. No body, initializer, type, scope, helper, or production flag changes.

## Scope, source semantics and historical coverage

Only the 23 leading uninitialized declarations at lines 288–310 of
`Texture_MCUtoRGBA8.c` were eligible: 16 s32 scalars, six pointers, and `s8 crValue`.
All are genuinely used and share one existing scope, without shadowing, local
address escape or initializer dependencies. Every other source byte was frozen.

All locals are assigned before use under the existing x % 4 == 0 requirement.
State/input/output pointers, tile width, dimensions, endpoints, skips and loop
locals are initialized before their uses. Each nonempty row's first pixel assigns
chroma values and offsets, reused within its four-pixel group. The signed-byte
Cr variable and explicit signed Cb conversion remain unchanged. Blue initially
receives unsigned luminance, red/green consume that value, and blue then receives
its offset; all channels precede clamps and packing. Sequential AR/GB stores and
later live input reads remain unchanged, including contained input/output aliases.

Baseline SHA256 pins:

- Whole source: `6340fe5b79280f8429092aaa62b9ae7fc252c06af956fe6aa0eb884aceb8136b`
- Function: `a47aed8fea3a4cafeb4a5128698b610323977fa3aaa476f372c71da51f3c5e56`
- Declaration block: `ce3024ff4df05fcfd3d142923f0d32e37f3cc03ca279bc45060e194d2b9e9f1c`
- Body after declarations: `7df5621114f8d4d34256326ef5b0288961ac319645758707c7f77c015620cf8f`
- Whole object: `64dff303c3c0525eef81e5f1925fdf7e22733a43fe68a099b79f9163e7609eca`

The complete function is identical to #1082 (`7b324519`) through ten subsequent
RGBA source commits. `rgba411edge-declaration-context.attempts.md` records 1,227
ordinary evaluations, naturally stopping before its 1,600 cap at proxy `(4,51)`.
All 715 immediate neighbors were closed under that structural/positional score;
the log expressly excludes independent official-fuzzy closure. All 716 function
orders in this audit repeat historical compilation. The missing measurement is
official scoring, not new-order discovery. Historical per-order artifacts were
lost during the workspace reset; old coverage comes from the committed log.

## Fixed baseline, real compilation and official scoring

The new leaf's fresh default build, full report and all 1,027 object hashes
matched the frozen independently verified parent leaf `wii-rgb422-next-review`,
HEAD `8f1d13822b51509c354ab676d5e6c0097b7e0552`, tree
`1dde64c7318dc1cfdb4fd7e067931d495d56b02c`, identical to merged 57c17ebe.
No baseline comparison depended on moving main.

One fixed center used the unchanged official declsearch swap/pop-insert generators:
253 swaps + 484 distinct moves - 22 shared orders = 715 neighbors, plus baseline.
All 716 orders really compiled via ordinary Ninja/MWCC. Exact source/object hashes,
source stability, argv, timestamps, changed object mtimes and compiler output
were saved. There were 716 distinct orders, 347 distinct objects, and no failed,
no-work or unstable-source trial calls. No adaptive center, restart or continuation.

Every immutable snapshot received an official score under a private copy of the
actual objdiff configuration, preserving settings, metadata and mappings, with
frozen original object and unique snapshot names. No deduplication, live-object
swapping, proxy filter or batch-aggregate ranking. Private-baseline function,
section and measure results equal the full baseline report.

All 716 snapshots pass raw object bytes outside the target, section headers,
relocation vectors, sibling raw bodies/reports/exacts, allocated non-code and
exact/code/data/link gates. Two neighbors improve fuzzy, 157 tie baseline and
556 lose. Snapshot **0017** is the unique highest admissible result, **94.24107%**.
It exchanges `chromaSkip` at line 288 with `output` at line 305. Both baseline
and selected object remain proxy `(4,51)` and ctxdiff 51, explaining why the
historical strict-proxy run did not retain the official-fuzzy gain.

Stop reason: the authorized baseline plus all 715 neighbors completed. Only
5/715 immediate neighbors of the selected winner occur in this set; 710 were
not observed here. No winner fixed-point or global-optimum claim is made.

## Fresh retained-object and full gates

The exact selected source was freshly rebuilt by default Ninja, reproducing
saved snapshot 0017. Explicit progress/report/43U-ok, a fresh full report, source
checks and all 1,027-object/report comparisons pass. Only this target function's
code/fuzzy changes; every existing sibling and other unit remains preserved.

- Function: 94.10714% -> 94.24107%; 112/112 instructions, ctxdiff 51 unchanged
- RGBA unit: 90.69012% -> 90.69921%
- Frozen-base global: 99.73189% -> 99.73191%
- Exact functions remain 2/13; matched code remains 660/6596 bytes
- All twelve sibling bodies and both raw-exact YUV400 functions preserved
- Raw section headers/relocations/non-target bytes fixed; no allocated non-code
- Empty pools identical; literal audit has 12 functions, zero candidates/errors,
  and the unchanged unequal-size setter skip
- All 186 shared immutable compiler/tool files and actual objdiff config unchanged
- Full default build, explicit progress/report/43U-ok and diff check pass
- DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`
- Overall completion still returns expected `DECOMPLETE_FAIL`

Retained SHA256 values:

- Whole source: `803568b7331b6f129b679e49c38cde33141ccfa78acd4e141cc8d1e845cbb2c7`
- Function: `e59b6f386311d19613f5eb11609de1e5cad8a4df34fd1710464a5647a04d575a`
- Declaration block: `9767aa396109225cd85c7fb136c052f1b04ee9dcf65180d20af6e49d94b41d51`
- Whole object: `68dc16e83ae3e1edf47f975a80fc360eb74bcc0a101862cd2693490f4b0577d0`
- Full report: `93b8c741d5eaaee45f536e9bb943a5c35f8b15955e1bac9204387f9985d9cf20`

## Sequential pixels, contained aliases and suite

The independent scalar model passes **11,451 vectors / 34,353 object executions**
against retained candidate, original and baseline, covering all **112/112**
instructions in each. It models Y[8][32], Cb[8][8], Cr[8][8] at offsets 4/260/324,
with cached chroma per four horizontal pixels, source row strides 32/8/8,
partial final groups and sequential AR/GB writes. All x origins satisfy x % 4 == 0.

Coverage comprises 1,257 complete edge-size cases over scales 1/2/4/8 and three
origins, 256 independent dimension-branch cases, 64 tile/residue cases, 6,400
saturation vectors crossing all luminance bytes with signed Cb/Cr values
{-128,-1,0,1,127}, and 3,474 halfword-aligned contained input/output overlaps.
Descriptors/state remain separate and output lies wholly within the actual
0x184-byte convBuf for overlap cases. Later reads observe earlier aliased writes,
while current-group chroma stays cached. All non-stack bytes/guards and preserved
GPRs, SP and LR pass. The repository JPEG suite also passes **9,456 paired cases
across 28 functions**.

The oracle's first run passed geometry/saturation but stopped at its address
precondition: adaptation had mistakenly applied the x % 4 alignment to the
halfword texture address. No object/reference mismatch occurred. Its original
script/log are preserved. Only that test guard changed from tex % 4 to tex % 2,
then the unchanged complete vector set passed. Production source/object stayed
frozen. These finite interpreter tests are not formal equivalence or Wii hardware
validation; additional alias/residue cases do not expand public API guarantees.

## Reproduction and storage

Leaf: `/workspace/scratch/0128b1ed02cc/wii-jpeg-rgba411edge-fuzzy-neighbors`.
Evidence: `/workspace/scratch/0128b1ed02cc/jpeg-evidence/rgba411edge-fuzzy-neighbors/`.

The directory preserves all snapshots, official reports, manifests, source/context/
scope hashes, complete baseline/final reports and 1,027-object hashes, compiler/
scoring/gate logs, `audit.py`, audit results, the initial guard-failure evidence,
and `differential.log`. Workspace storage only; shared tools are reused read-only.
Each order checked a 1.1 GB free-space guard; minimum observed was 5,639,221,248
bytes. No other leaf/main/remote/linking changes or prior-evidence deletion.

From the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-fuzzy-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-fuzzy-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-fuzzy-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

The enumeration driver refuses a restart after recorded calls exist.
