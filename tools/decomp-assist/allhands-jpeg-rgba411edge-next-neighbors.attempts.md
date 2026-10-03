# RGBA411 edge: next fixed official-fuzzy neighborhood

Base `1701b591a6d1e32c0c58f211734778101bb4983b` (merged #1123), 43U only.
Branch `agent/bittle/jpeg-rgba411edge-next-neighbors`. The retained source
exchanges only `chromaSkip` and `greenOffset` declarations at lines 305/307,
improving **94.24107% -> 94.28571%**.

## Frozen scope and coherent baseline

Only the same 23 existing uninitialized declarations at lines 288–310 were
eligible. Their types, including s8 crValue, and every source byte outside the
block are unchanged. No initializer, assignment, expression, scope, helper,
production flag or other converter changes. The block has no shadowing or local
address escape. All locals remain assigned before use under the existing
x % 4 == 0 contract. Signed chroma, the unsigned luminance read into blue, cached
four-pixel chroma groups, partial groups and sequential live-input/store alias
behavior are preserved; `scope-proof.json` records the unchanged proof.

The isolated leaf's fresh default build, full report and all 1,027 objects
matched the frozen parent `wii-rgba411edge-review`, HEAD
`719046fb76f7915514e612cd001390dd334339fa`, tree
`dbdd6d252a5f6f36c42cea66f16efe129382de1d`, identical to merged 1701b591.
No baseline comparison used moving main.

Baseline SHA256 pins:

- Source: `803568b7331b6f129b679e49c38cde33141ccfa78acd4e141cc8d1e845cbb2c7`
- Function: `e59b6f386311d19613f5eb11609de1e5cad8a4df34fd1710464a5647a04d575a`
- Declarations: `9767aa396109225cd85c7fb136c052f1b04ee9dcf65180d20af6e49d94b41d51`
- Body: `7df5621114f8d4d34256326ef5b0288961ac319645758707c7f77c015620cf8f`
- Object: `68dc16e83ae3e1edf47f975a80fc360eb74bcc0a101862cd2693490f4b0577d0`

## One fixed neighborhood, all official scores

The unchanged official declsearch generators enumerate 253 swaps + 484 distinct
moves - 22 shared orders = 715 unique neighbors, plus baseline. The center was
fixed throughout. All **716** distinct orders really compiled using ordinary
Ninja/MWCC, with immutable exact source/object snapshots, hashes, compiler output,
argv/timestamps and changed object mtimes. There were **347** distinct objects,
zero failed/no-work calls and zero source instability.

The current center was prior official snapshot 0017. Exact overlap with that
preceding 716-order manifest occurs at current indices `[0,17,268,269,595,596]`:
six orders including baseline, five neighbors. The other 710 neighbors were
absent from that manifest. Additional older structural-search overlap is unknown;
this is not a global novelty claim.

Official objdiff scored every immutable object under a private copy of the actual
configuration, retaining settings, metadata and mappings, using a frozen original
object and unique snapshot names. No deduplication, live-object swapping, proxy
filtering or aggregate-score ranking. Private-baseline function/section/measures
equal the full baseline report. Every snapshot passes raw bytes outside the
target, section headers, relocation vectors, sibling bodies/reports/exacts,
allocated non-code and exact/code/data/link gates.

Results among neighbors: **1 gain, 156 ties, 558 losses**. Snapshot **0240** is
the unique highest admissible result at **94.28571%**. Baseline and selected
object both retain proxy `(4,51)` and ctxdiff 51. Stop reason: the authorized
baseline plus all 715 neighbors completed. Only **5/715** neighbors of the new
winner are present in this set; 710 remain unobserved here. No new-winner fixed
point, plateau/global optimum, restart or adaptive continuation is claimed.

## Fresh full gates and behavior

The selected exact source was freshly built by default Ninja, reproducing its
saved whole-object snapshot. Fresh progress/report/43U-ok, full official report,
all 1,027-object/report comparisons, source review and diff checks pass. Only the
target body/fuzzy changes; all sibling and other-unit improvements are preserved.

- Target 94.24107% -> 94.28571%; 112/112 instructions, ctxdiff 51 unchanged
- RGBA unit 90.69921% -> 90.70224%
- Global fuzzy is 99.73204% before and after at reported precision
- Exact remains 2/13 functions and 660/6596 code bytes
- All twelve sibling bodies/reports and both raw-exact YUV400 functions preserved
- Raw non-target object bytes, section headers and relocation vectors identical
- No allocated non-code; empty pools identical
- Literal audit: 12 functions, zero candidates/errors, unchanged setter-size skip
- All 186 shared immutable tool files and actual objdiff config unchanged
- DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`
- Overall completion remains the expected `DECOMPLETE_FAIL`

The unchanged accepted scalar corpus passes **11,451 vectors / 34,353 executions**
against this actual candidate, original and fresh baseline, with **112/112**
instructions covered in each. Coverage includes 1,257 complete edge-size cases,
256 dimension-branch cases, 64 tiled/residue cases, 6,400 saturation vectors and
3,474 halfword-aligned overlaps wholly within the actual 0x184-byte convBuf.
All x origins satisfy four-pixel alignment. State/descriptors remain separate;
chroma is cached within each group while later input reads observe prior writes.
All non-stack bytes/guards, preserved GPRs, SP and LR pass. The repository JPEG
suite independently passes **9,456 cases across 28 functions**. These finite
integer-interpreter tests are not formal equivalence or Wii hardware validation;
additional alias/residue checks do not expand public API guarantees.

Retained SHA256 values:

- Source: `75e33386739273752329ebd7f48e4882d4a8b4f3f6282a88e3f1d59ba735bbb8`
- Function: `c882e0182c7df3091cbe827c1f9ba7d8ec428d60fc3f15b6853d7d128c0a5231`
- Declarations: `34da96226f3f0c217f7cd32c632ccc58090130ad5fd52874d76d4fb95459eaae`
- Object: `9f1c539c06a7b017a215c41317d40861572e97407aa738791b14bb0f9e4bcdd8`
- Full report: `778c8ddcdcd988f4bf9be22420fcbd25af648b6b7cb59601df0dee78c8a984e1`

## Evidence and reproduction

Leaf: `/workspace/scratch/0128b1ed02cc/wii-jpeg-rgba411edge-next-neighbors`.
Evidence: `/workspace/scratch/0128b1ed02cc/jpeg-evidence/rgba411edge-next-neighbors/`.

The directory preserves immutable snapshots, official reports/config, manifests,
source/context/scope hashes, full baseline/final reports and 1,027-object hashes,
all compiler/scoring/gate logs, model results and `differential.log`. Shared tools
were reused read-only and new evidence stayed in workspace storage. A 1.1 GB
precompile free-space guard was checked every order; minimum observed free space
was 4,512,989,184 bytes. No prior evidence/branches, main, remote or linking changes.

From the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-next-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-next-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba411edge-next-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

The enumeration driver refuses a restart after recorded calls exist.
