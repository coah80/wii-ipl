# CHANSVm converter input types

Base: `20cf9f9f25b13b8cd6910e07cc5eb71558845d4e`, target 43U only.

## Change and source review

`CHANSVmConvertToFloatFromStr` took a pointer-to-const source header while
`VmConvertFunc` specified a mutable source header. The conversion table cast
hid that incompatible function-pointer type at the indirect call.

Give all 11 converters and the callback typedef the same pointer-to-const
source-header type, and remove the callback cast. All converters either read
source values, ignore the source, or pass it through the read-only array-join
path. They write only newly allocated result objects. Propagate the input type
through `VmArrayJoinCommon`, `VmArrayJoinEstimateStrSize`, `VmArrayJoinSub`, and
`VmArraySeekTop`, including the forward declaration. These helpers only read
the source header; the join routines write the destination string and local
state. `VmArraySeekTop` still returns a mutable chunk pointer because header
constness is shallow and other callers can mutate array elements. No cast is
needed at the array-join boundary.

The public `CHANSVmConvertObjectType` input remains mutable: its same-type fast
path returns the original mutable object. Passing it to a const-source
converter is valid. No executable expressions, flags, data or layout changed.

## Fresh leaf verification

Configured using the restored `wii-source-tools/build-43U.sh` tool paths and
flags, with commands run in the isolated leaf instead of that script's fixed
main directory. Baseline object was freshly compiled before editing.

- Entire CHANSVm object is byte-identical to that baseline, SHA256
  `11fa48261cd93668d133d5ef73efbf3c9109181730b21409153b78316189e063`.
  All 233 sibling function spans, allocated sections and relocations unchanged.
- All 15 emitted converter/dispatch/join functions: exact-name objdiff 100.0,
  raw target function bytes and normalized relocation targets identical
  (86 code relocations). VmArraySeekTop is inlined.
- All target data sections match including alignment padding: `.rodata` 1432,
  `.data` 4672, `.sdata2` 184, `.sdata` 600, `.sbss` 16 bytes;
  all 614 data relocations match by resolved section/function target.
- Pool: 125/125 strings identical. Dispatch ctxdiff: 47/47 instructions, 0 diffs.
  FloatFromStr: 83/83 instructions, one textual symbol-alias difference
  (`VmNaN` versus `lbl_81694F08`); raw bytes and resolved relocation target are
  identical. This is not represented as a literal ctxdiff-zero result.
- Fresh full 43U build, report and `build/43U/ok` pass. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- All 1028 unit measures/functions/sections and overall report measures are
  unchanged against the saved base report. All 22 workflow guards pass with
  no skips. `git diff --check` passes.

This is a binary-neutral type correction, not a new matching/linking gain.
CHANSVm remains 229/233 exact, 45284/53564 exact code bytes, 6904/6904 matching
data bytes, and unlinked. The completion assertion still fails on the existing
project-wide incomplete code/link totals; no full-completion claim is made.

Local evidence: `../vm-converter-const-evidence/` contains baseline/candidate
build logs, original baseline object/report, verification script/results,
full-build/report/ok logs, pool and ctxdiff results, guards and completion logs.
