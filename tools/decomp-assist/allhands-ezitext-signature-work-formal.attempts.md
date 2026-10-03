# Signature-check workspace formal, 2026-10-03

Parent: 8a0aa7ce; its punctuation-options correction is preserved unchanged.
Owned source: zi8initd.c / Zi8IsZicorpSignature only.

The local declaration in zi8alpha.c takes word, halfword length and workspace.
An original-object reference scan finds exactly one caller and no function
pointer or other address escape. The target AlphaGetCandidates call puts the
word in r3, narrows the length into r4, and moves its preserved workspace into
r5 immediately before calling Zi8IsZicorpSignature.

The callee's current definition omitted the third formal. Its target reads
only r3/r4; r5 never appears anywhere in its 48 instructions. It has no calls
or tail target. Add the existing ZI_NEED_WORK formal to align the definition
with the actual caller and its declaration. The argument is genuinely passed
but unused. No local, assignment, storage, volatility or forced spill is added.
The body and all other declarations remain unchanged.

Validation after this separate change:
- The complete zi8initd object is byte-identical to the fresh baseline
- Zi8IsZicorpSignature remains 48/48 instructions, ctxdiff zero differences
- Zi8InitializeDynamic remains 128/128 instructions, ctxdiff zero differences
- Unit code 704/704, data 20/20 and 2/2 exact functions remain 100%
- The complete 1,027-unit report is identical to baseline and the preceding
  punctuation-only report; all source objects except punctuation's already
  documented nonallocated symbol-name difference are byte-identical
- Owned allocated sections and canonical relocations are unchanged
- Pool is identical and empty; full configured 43U build passes
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

This is contract reconstruction only, with no percentage gain. No shared
header, caller, linking flag, assembly, other-region build or remote change.
Private evidence: /tmp/ezi-options-signature-{report.json,build.log,verification.txt}
and /tmp/ezi-new-receiver-refs.txt.
