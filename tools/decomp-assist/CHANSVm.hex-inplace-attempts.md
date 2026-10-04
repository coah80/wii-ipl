# VmBlobPackCommon in-place hexadecimal decoding

43U only, base `631f31b7f814516abfdfcd763db376ea50a02a13`.
Exactly one source form: remove the separate u32 nibble temporary and decode
into the existing u32 ch value. No declaration permutations or other variants.

## Fresh build results

- Fresh baseline default build reproduces all 1,027 objects and complete report
- Candidate: function **97.97156 → 98.0988%**, unit **99.46098 → 99.46733%**
- Size remains 2,672 bytes / 668 instructions; strict target differences 242 → 230
- Only 13 instructions change, within +0x9A8..+0xA08, reproducing the target's
  in-place r7 decoding. Its source-pointer base remains different
- Selected actual recompile reproduces candidate source/object/report exactly
- All 232 sibling bytes/scores, 224 exact functions, other 1,026 units, matched
  code 39,908/53,564, data 6,904/6,904 and link classifications preserved
- Full default 43U, explicit ok, pool 125/125, literal audit 233 functions /
  40 arguments (no skips/errors/candidates), and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Only baseline, candidate and selected compiler invocations were used.
This remains a fuzzy gain, not an exact match or completed linked unit.

Source SHA256:
`2a4903c930eed51968ef99d018dc46256807cb59bb4f69287e3065b883591faf`

Object SHA256:
`7325c84d335b08f2fb58405e87ca76fc0245fcd8549bb640ec4ef7911893b053`

## Contracts and reproducible checks

The original code unit is unused after decoding. Each iteration overwrites ch
before use; no ch occurrence remains outside this loop except its declaration.
It cannot escape to another format case or later branch. Count-zero paths do
not read it. Decoded values are 0..15, optionally shifted to at most 240.
Input/output accesses, zero-fill, pointer/count induction and volatile offset
commits retain their order, including contained overlapping payload views.

Every raw symbol entry and relocation section is unchanged. All nontext
sections except `.strtab` are unchanged; exactly 79 local object-name changes
exhaustively reconstruct `.strtab`. No helper body or function symbol is added.

The accepted copy/pad slice +0x4BC..+0x518 is raw-byte identical. The published
common verifier is hash-pinned and replayed automatically: 944 must-equality
uses pass for each baseline/candidate and baseline/original comparison, with
branch/loop predecessor intersections and explicit GPR/CR0/CA/CTR/LR/memory
effects. Undocumented call-clobber equality is killed. The original call ABI,
save/restore tails, metadata/name accounting, unchanged copy slice and its
16,368 bounded comparisons are freshly checked, not assumed from an old run.

Fresh hex checks interpret direct original-DOL instructions +0x978..+0xA38,
including pre-decode memset and post-loop offset reload/store:

- All 65,536 code units and both parities: **131,072 scalar cases**, each run
  on baseline/candidate/original instructions, **393,216 comparisons**
- **640 bounded strings**, lengths 0..64, run on all three streams:
  **1,920 comparisons**, including **330 contained-overlap cases**
- Complete memory, ordered access/call traces, scalar cursor and CTR results
  are checked against an independent lookup-table reference
- Negative controls reject an incorrect digit base, missing high-nibble shift,
  omitted volatile copy-offset reload, overlap-unsafe copying and undocumented
  scratch use after a call

Use preinstalled pyelftools/capstone; no compilation or downloads occur:

```sh
python tools/decomp-assist/verify_vm_blob_hex_inplace.py \
  --baseline-object /path/to/accepted-baseline-CHANSVm.o \
  --candidate-object build/43U/src/src/channelScript/CHANSVm.o \
  --original-object build/43U/obj/src/channelScript/CHANSVm.o \
  --dol /path/to/authorized-original-43U.dol \
  --symbols config/43U/symbols.txt --source src/channelScript/CHANSVm.c \
  --output-dir /path/to/new-verification-output
```

The default common verifier is the already-published sibling
`verify_vm_blob_copy_padded.py`; an explicit path is also accepted. Both reports
are saved in the new output directory. Input source/object and common-verifier
hashes pin this exact trial. Full project/report gates remain separate.

These are bounded custom instruction/source checks with modeled libc and fixed
opaque callee contracts, not general formal verification or full VM/Wii runtime
testing. Only valid allocated spans are covered; malformed or out-of-bounds
input behavior is not claimed. Earlier evidence and diagnostics are preserved.
