# Punctuation options receiver, 2026-10-03

Base: bf8ebfa3. Owned source: Zi8punct.c only. This is a source-contract
correction with unchanged generated code and no percentage gain.

## Actual call and receiver

All original-object references show exactly one executable caller,
Zi8GetCandidatesOrCount, plus the punctuation function's exception-index
reference. At that call the fixed ABI positions are:

- r3: the candidate request
- r4: the candidate options object
- r5: the workspace

The dispatcher preserves these three incoming pointers separately. Its
_GetCandidates/_CheckCandidates producers create the existing 24-byte
ZiCandidateOptions object, initialize capacity from the workspace, and pass
its address as the second argument. The dispatcher then writes maxCount
from the workspace before calling the punctuation helper.

The punctuation target reads a byte at options +0, a word at options +0x0C,
and a halfword at options +0x10. These are countOnly, maxCount and capacity.
It overwrites incoming r5 before reading it, so the third workspace formal
is present in the caller contract but unused by this implementation.

The reconstructed definition previously omitted that third formal and named
the second argument workspace. It consequently described options accesses
using unrelated workspace fields at coincidentally equal offsets.

## Minimal correction

Copy the existing private ZiCandidateOptions type verbatim from zi8getc2.c;
no shared header or producer is changed. Its complete layout is reused,
including its established fields, without introducing any object, extra
storage or invented padding. A fixed-target-width layout check confirms
size 24 and the three accessed offsets 0/0x0C/0x10.

The definition now takes request, opaque options and workspace, and accesses
the real options fields through the private view. Its ziU32 result agrees
with the sole caller's declaration. All locals, comparisons, loops, output
stores and branch directions remain unchanged. The unused workspace formal
recovers an argument already supplied by the target caller; it does not
manufacture state or instructions.

## Verification

Fresh configured 43U baseline and candidate full builds pass with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. Pool first: identical and empty.
All allocated payloads and canonical relocations are baseline-identical:
.text 300, .rodata 80, extab 8 and extabindex 12 bytes. The only complete-object
difference is two anonymous symbol-number characters in nonallocated .strtab.
All other 1,026 source objects are byte-identical to baseline.

Zi8Punctuation stays 75/75 instructions with ctxdiff zero differences. Unit
code 300/300, data 100/100, and 1/1 exact functions remain 100%. The entire
1,027-unit objdiff report is unchanged. Full 43U DOL SHA1 remains
26116613f624061ba99c8d1a299aaa6efa85670d. git diff --check passes.

Private evidence: /tmp/ezi-options-punct-{report.json,build.log,verification.txt},
/tmp/ezi-options-baseline.json and /tmp/ezi-new-receiver-refs.txt.
No remote changes, other-region builds, assembly, linking flags, forced
registers, volatile, dummy assignments or shared-header edits.

## Broader read-only ABI audit

The original-object call inventory covered 20 remaining nonexact functions,
excluding the already resolved one-key/PUD/conversion work: 337 direct calls
and one OEM callback. A symbolic-expression comparison pins each value to
its actual ABI argument register and outgoing stack slot; it does not apply
a global argument-register permutation. After applying only the previously
proven alpha scalar-frame offset mapping, all 338 call argument expressions
agree. The callback's four arguments and stored callback target also agree.
No external tail branch was found; indirect non-call branches are switches.
A separate incoming-register/stack-use audit found no additional live
argument beyond a callee's reconstructed parameter list. These are diagnostic
checks, not a formal whole-program equivalence proof.

The declaration/definition scan identified the separate missing workspace
formal on Zi8IsZicorpSignature. Three exact version-query helpers also have
old-style empty definitions despite receiving an unused workspace in their
exact caller; those are outside this candidate. No allocation experiments
were performed.
