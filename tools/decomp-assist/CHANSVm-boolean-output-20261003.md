# CHANSVm boolean output contract

Base: `fc114afd44065fb99f9ff2fe2969f393a504fe03` (43U).
Leaf: `agent/bittle/chans-scalar-contracts`.

## Correction and evidence

`CHANSVmGetBoolean` writes an optional four-byte `vmBoolInt` result, but its
source formal described a `CHANSVmObjHdr*`. All three callers cast addresses
of scalar locals to that object pointer. The original helper's only output
write is a word store at `0x8144C664`. Its Step call destinations at
`0x81456B08`, `0x81457584`, and `0x814575B0` were verified directly in the
original DOL, as were 48 nonrelocated helper words and its direct callees.

The actual MWCC layout probe confirms object alignment/size 8/16 and scalar
alignment/size 4/4. Step's two conditional-branch callers pass sp+0x0C, which
has scalar alignment but not object alignment. Declaring a whole object at
that address is an incorrect source contract even though the generated
helper only performs one word store.

Use `vmBoolInt*` as the output formal, assign through `*ret`, make both
receiving locals `vmBoolInt`, and remove all three casts. No shared header
contains a declaration, and no header changed. A repository-wide source
search found exactly this definition and these three calls. A complete
original-object relocation scan found only those calls plus ten labels in
the helper's own switch table; no additional callback was found.

## Tests and gates

- Source-extracted baseline reproduces a UBSan misaligned-object access when
  passed a four-byte-aligned, non-eight-byte-aligned scalar destination.
- Candidate passes 1,283 typed-output cases, corresponding null-output calls,
  and surrounding-byte canaries. Coverage includes all 256 discriminator
  values, signed integer boundaries, zero/nonzero string lengths, finite
  floating values, signed zero, infinities, NaN, and error/no-write paths.
- This is a focused host helper harness with a modeled object layout and
  `isnan` shim, not full VM or Wii runtime execution. Target layout was
  independently checked with the configured MWCC compiler.
- Entire compiled object is byte-identical, including code, data, symbols
  and relocations. SHA256:
  `5bf3f4a0a404e2a574287c16de81d702a1402d9fca416455e84dc1df67c9eb76`.
- All 1,027 report units unchanged. Exact CHANS functions 222/233; exact code
  38,136/53,564; data 6,904/6,904. GetBoolean remains 100%; Step 96.98723%.
- Pool: 125/125 identical. `git diff --check` passes.
- Full 43U `all_source`, report, and `ok` gates pass with the existing cached
  tools selected through documented configure overrides. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Artifacts: `/tmp/chans-step-abi/`, including `test_boolean.py`, the MWCC
alignment probe, `check_boolean_original.py`, and build/test results.
No original binary or disassembly is committed.

GATE: coherent scalar-output source correction; no fuzzy/exact/data/link gain.
