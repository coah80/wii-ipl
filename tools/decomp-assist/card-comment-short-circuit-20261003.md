# Card loader: one lazy short-circuit base-rejection form

## Result and finite scope

The single pinned form improves `loadCardFileIcons` **90.37305 → 90.7832**
(+0.41015) and its unit **97.225334 → 97.3106**. This is a partial fuzzy gain,
not an exact match or a linked-source claim. Exact measures remain 27/30
functions, 4,168/9,852 code bytes and 1,496/1,496 data bytes.

Actual ELF counts: baseline **508 / 2,032 bytes**, candidate/selected
**506 / 2,024 bytes**, original **512 / 2,048 bytes**. The report's 2,048-byte
function extent refers to the target. Exactly three ordinary target compiles
completed: one fresh baseline, one candidate, one selected build. The candidate
was scored individually with the real objdiff configuration; no proxy, extra
form, flag change, enumeration, deduplication or adaptive search.

Authorized patch SHA256:
`87455536f789f577bd8edf47cc140c3fc6d3b9a8d55693e56e32415892ba3cde`.
Selected source SHA256:
`03e01f38b652547d881d85c63a5b9a39715ae23cad2a1cc0bebd513b88f2c6f2`.
Selected whole-object SHA256:
`58992542a70254d76f10d7933d15920d88bb9bc9277e120d42df0a99038bc6bf`.

Base main was `db6157b693be9cbd8daa01693e5334d1bc5c2657`, tree
`e9db756f46131b1168ba5d9f03a110b84dacd555`. Per explicit authorization, the
clean restored `wii-card-comment-base-join` cache was reused at docs-only
commit `46598c06416e1d60364b63e75ba5727732122869`. The previous losing goto
form/docs and all old immutable evidence are preserved; it was not used as a
seed. A new reference snapshot verified unchanged main/leaf source, original
DOL, all 1,027 source objects, full raw report, 394 headers and actual tools/
compiler/config pins. Fresh baseline compilation reproduced the complete
1,027-object manifest and raw report byte-for-byte.

## Source-definedness and exact scheduling proof

Only the comment base rejection structure changes. A real `u32 fileSize` is
scoped around the bounds block. Built-in short-circuit OR combines negative
base with `base > (fileSize = original length * sector expression)`. Both base
failures set result zero before the unchanged endOffset else block.

No fileSize read can occur without assignment: entering else proves the
nonnegative second operand executed. Negative base skips assignment, descriptor
length and sector loads; it never reads fileSize. Labels remain outside the
new block, so no goto enters it or bypasses an initialization needed by a use.
The scalar's address does not escape. This is meaningful later-used state,
not dummy storage or an undefined incoming-register trick.

All casts, primitive arithmetic, unsigned multiplication/wrap, masks and
endOffset signed/unsigned tests remain unchanged. CARDGetSectorSize precedes
the lazy metadata loads as before. Negative sector/read results still bypass
the zero assignment and preserve their negative result. Every call, pointer
increment and memory operation keeps its source order, including valid
contained aliases and callbacks changing metadata or the valid sThread pointer.

A complete actual-body map verifies all **506** surviving nodes with exact
GPR operands and relocation identities. It removes precisely baseline +0x664
`li r24,0` and +0x668 branch, and changes +0x660 from `bge valid` to `blt` the
existing upper-base rejection. Every subsequent node maps by -8 bytes; earlier
branch destinations are adjusted exactly. No register allocation change is
hidden by operand/name erasure. Candidate now has shared zero at **+0x678**,
branch-to-clear +0x67C, then valid endOffset at +0x680. Target has the same early
shared-rejection shape at **+0x690/+0x694/+0x698**. This resolves the late-block
placement observed in the previous losing goto candidate.

## Exact metadata and all siblings

All 29 sibling raw bodies/extents and exact-name official function measures
remain unchanged; all 27 exact functions remain exact. Raw allocated nontext
bytes and sizes remain identical to the retained baseline. The entire symbol
and relocation tables were compared without broad compiler-name normalization.

- 50 symbol records change: 46 concrete local .data names, owned size -8, and
  exactly three later function addresses -8 (clearCardWritePending,
  checkCardFileDuplicate, runCardMoveOrCopy)
- Each of the 46 exact old/new name pairs retains symbol index, type, binding,
  section, address, extent and underlying bytes; nine pairs are relocation
  targets in seven sibling functions
- All relocation indices/types are unchanged; each text relocation offset
  and section-symbol text addend is mapped exactly by the two-node deletion
- All other nonowned symbol types/extents, section flags/types/alignments and
  raw nontext remain unchanged; every file-offset, header, string-table and
  other metadata difference is listed in the saved before/after accounting

The initial conservative name-based gate rejected those exact local-name
changes. Its original record is retained in `candidate-result.json` and is
not silently weakened. `candidate-admissibility.json` independently resolves
all changes through explicit per-record proofs, with no blanket @ stripping.
Original/baseline raw .data/.sdata/.sbss differences predate this form; this
trial's retained-baseline raw data comparison passes.

Full final report/objects: only the owned object/unit changes. Exactly five
report fields change, all fuzzy improvements (loader, text section, unit,
global, main category). Every other unit/report field, exact/data/function/link
measure and configuration is unchanged. Baseline report SHA256
`c35f319907b5b93711e720ee5a0872e2cfc06e65d2eed871b46184c956412279`;
complete final hashes and changed paths are preserved in evidence.

## Fresh bounded PPC behavior evidence

The fresh actual-instruction comment/return slice and independent sequential
source reference passed **1,920 unique cases**, **5,760 actual executions per
run** (baseline/candidate/original), and 1,920 reference executions.
Coverage is **113/113 baseline, 111/111 candidate, 111/111 target** instructions
in this region. Source definition/use and whole-body mapping remain separate
from that bounded runtime coverage claim.

Cases cover signed/wrap/base/end bounds, negative/positive sector/read/close
results, both slots, file indices 0/63/126, and deterministic generated values.
Four valid allocation layouts include contained buffer destinations, descriptor
inside comment storage, and destination equal to a descriptor. All modeled
memcpy ranges are disjoint. Six callback profiles preserve or mutate descriptor
state at sector/read/close boundaries, or replace sThread with another valid
allocated state. Return values, complete call/read/write traces and final
non-stack memory agree across all four executions. Actual stack/LR and
nonvolatile-register restoration are checked using original DOL helper bytes.
All target nonrelocated words and all 13 original direct-call destinations are
independently verified against the protected original DOL.

The standalone repository proof script was also rerun with the selected object:
another 1,920 cases/5,760 actual executions, all result/trace/memory/coverage
fields identical. Total worker model execution across these two runs is 11,520;
this adds no source compilation or variant. Parent independently reproduced
1,920 cases/5,760 executions and the full review object/score/gates.

Limits: the model enters after the unchanged image prefix with established
live-ins and saved frame. CARD/copy routines are modeled, not full SDK code.
This is not Wii hardware, full-function input coverage or a formal proof.
Existing image-prefix zero-icon negative-shift and reserved-format-3 limitations
are unchanged and not exploited. Arbitrary sector bit patterns are bounded
arithmetic probes, not claims about physical cards.

## Final build and repeatable evidence

Default 43U build and explicitly forced ok pass with no additional source
compile. Original and compiled DOL remain byte-identical with SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`. Pool: 43/43 identical. Literal audit:
29 functions/45 arguments, zero candidates/errors, explicit loader size skip.
Parent's separate full review also reproduces exact object and all 27 exact
ctxdiff-zero siblings, pool/literals and DOL.

New workspace evidence: `card-comment-short-circuit-evidence/`, indexed and
immutable. Previous `card-sequence-comment-base-join-evidence/` stays intact.
Ordinary compile sources/objects/timestamps/argv/output and official configs/
reports, both 1,027-object manifests, exact metadata, case vectors and full
coverage/result digests are retained. Configure/tools/compiler/wrapper and
`WIBO_SJIS_MISSING_IMPORTS=1` are unchanged; no downloads/remotes/upstream.

Reusing the existing cache avoids the previously unaffordable fresh checkout.
Incremental evidence estimate was 28 MiB; phase checks preserve 1.1 GiB plus
100 MiB review reserve. The copied read-only pin file first needed its own new
copy made writable before preflight; no old evidence changed and no compile
was retried. Proof-script extraction first rejected a naïve substring check,
then used an identifier check before any standalone execution. Neither event
changed the authorized source or compile count.

Saved-only validation:

```
.venv/bin/python card-comment-short-circuit-evidence/validate_saved.py --live
```

Fresh bounded proof, using a new output directory:

```
.venv/bin/python wii-card-comment-base-join/tools/decomp-assist/card_comment_short_circuit_audit.py \
  --baseline card-comment-short-circuit-evidence/baseline.o \
  --candidate card-comment-short-circuit-evidence/final/selected.o \
  --original card-comment-short-circuit-evidence/original.o \
  --dol card-comment-short-circuit-evidence/original-main.app \
  --symbols wii-card-comment-base-join/config/43U/symbols.txt \
  --output-dir validation/card-comment-fresh-proof
```

No further source form or traversal is authorized. This one-candidate trial
is complete and awaits parent integration decision.
