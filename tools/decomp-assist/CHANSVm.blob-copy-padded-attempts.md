# VmBlobPackCommon copy/padding lifetime boundary

43U only. Base `4508f455dbd44de4f512618e91692a9b6115d6e8`, tree
`28f9b61d3f0bed89a5086a4a813ee52a462b1504`. One fixed candidate; no permutations.

The existing blob copy, bounded overlap-safe `memmove`, optional zero-fill and
offset commit now have a small inline helper. This is an independently
reconstructed candidate, not recovery of the historical helper in
`a5h.attempts.md:47–48`. The historical source hashes could not be recovered.

## Actual measurements

- Fresh baseline default build reproduced all 1,027 source objects and the
  complete official report byte-for-byte
- One candidate compile: `VmBlobPackCommon` **97.949104 → 97.97156%**;
  2,672 bytes / 668 instructions unchanged; target instruction differences 244 → 242
- Selected-source recompile through full default Ninja reproduced the candidate
  source, object and full report; explicit `build/43U/ok` passes
- Only CHANSVm.o changes. All 232 sibling function bytes/scores and all other
  1,026 units unchanged; 224 exact functions preserved
- Unit fuzzy **99.45986 → 99.46098%**; exact code 39,908/53,564 and data
  6,904/6,904 unchanged; link classifications unchanged
- Pool 125/125 identical; literal audit 233 functions/40 arguments, zero errors,
  candidates or skips; `git diff --check` passes
- DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`

Candidate source SHA256:
`d52e12d7c154c61dc49ffb0ef125764fb8714a7d6f71631e810fd3a57d88d536`

Candidate object SHA256:
`a60ea527623793184e6e3edd0584e0e335c534248a5a9902dfe217cefdf39999`

This remains a fuzzy improvement, not an exact match or a completed linked unit.

## Semantics and metadata

Source and destination may share a header or contained overlapping payloads.
The existing declaration-level volatile offset reads retain their order,
including the fresh destination-offset reload after copy/padding. Const adds
no restrict/disjointness promise. Parser, allocation, conversion, callback,
validation and error paths stay in place. Removed locals belonged only to the
copied block. No compiler option, layout or link setting changed.

49 instructions differ from baseline, all register allocation. Raw ELF symbol
entries and relocation sections are identical. Every nontext section except
`.strtab` is identical; exactly 79 local `@number` object-name replacements
reconstruct that section. No helper body or extra function symbol is emitted.

## Standalone verification

`verify_vm_blob_copy_padded.py` needs preinstalled pyelftools and capstone.
It reads caller-supplied files and writes only a fresh output directory:

```sh
python tools/decomp-assist/verify_vm_blob_copy_padded.py \
  --baseline-object /path/to/baseline-CHANSVm.o \
  --candidate-object build/43U/src/src/channelScript/CHANSVm.o \
  --original-object build/43U/obj/src/channelScript/CHANSVm.o \
  --dol /path/to/authorized-original-43U.dol \
  --symbols config/43U/symbols.txt \
  --output-dir /path/to/new-verification-output
```

The checker compares corresponding CFG edges with a must-equality relation,
intersecting predecessor states at branch and loop joins. Both baseline versus
candidate and baseline versus original pass 944 explicit/implicit uses. CR0,
XER.CA, CTR, LR, memory, stack addressing and SDA21 bases are accounted for.
Ordinary calls kill equality for undocumented caller-saved scratch registers;
only documented results and coupled memory effects are retained.

The callee contracts follow the actual CHANSVm.c definitions: word/pointer
arguments occupy their listed r3..r9 registers and all results use r3 except
the u64 MakeU64 result in r3:r4. BlobHasSpace's signed64 argument is aligned in
r5:r6, skipping r4. There are no stack-passed arguments. VmBoolInt is BOOL/int,
not byte-sized vmBool (VmTypes.h and revolution/types.h). MSL string.h declares
the pointer results and size_t arguments of memcpy/memmove/memset. The original
save/restore helper tails are independently decoded from the DOL.

The original DOL copy slice at +0x4BC..+0x518 is exactly 23 instructions. There
are 5,456 bounded cases, each compared across baseline/candidate/direct-DOL
instructions: 16,368 complete-memory and ordered-trace comparisons. Coverage
includes 136 same-header, 2,352 padding, 1,508 zero-copy, 395 forward-overlap and 429
backward-overlap cases. Negative controls reject a missing volatile reload,
overlap-unsafe forward copying and undocumented scratch use after a call.

These are bounded custom instruction/source checks with opaque fixed callee
contracts and modeled libc operations, not general formal verification or
complete VM/Wii runtime testing. Malformed header-overwriting payload pointers
are not asserted valid. Full project/report gates remain separate requirements.

Harness-development failures were retained separately: the first metadata
assertion exposed local-name renumbering, and a DOL call loader restricted to
`.text` rejected memset at 0x81330334. Its exact `.init` symbol declaration fixed
the resolver; no name was guessed. An initial save-helper textual check also
rejected Capstone's decimal `-8` spelling; numeric operand checks replaced it.
These were verifier fixes, not additional source candidates or compiler trials.
