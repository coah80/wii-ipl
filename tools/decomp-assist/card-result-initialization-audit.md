# MemoryCardManager result initialization

Base: `f8957ca9`. Branch: `agent/fix/card-result-initialization`.
One bounded source trial: initialize `result` from the existing `file` value in
`isMoveEnable` and `isCopyEnable`. No conditions, shared reads, error priorities,
headers, compiler flags, or Matching classifications changed.

## Target evidence

Both original functions are 0x1D8 bytes / 118 instructions. At function offset
0x4C, `lwz r29,8(r5)` loads `mFile[slot][index].fileNo`. Each ordinary result
branch replaces r29 with its error/success code. If the initial eligibility test
fails but the second pass finds every condition favorable, the final test at
0x1A8 branches directly to the output check without replacing r29; the store at
0x1B8 writes that retained file number through `code`.

That path is relevant because card state is shared with the card thread. For
example, the first `isDistSlot` can observe a non-ready slot, and the second can
observe a ready slot with otherwise favorable conditions. The old C++ left
`result` uninitialized on this path. The target retained the file value.
`file` is `u32` (`unsigned long`); the output is `long`, both 32-bit for this
target. Valid directory indices are representable in both types. The retained
`long result = file;` expresses the target's existing value lifetime.

## Independent leaf verification

Configured 43U with explicit local compiler/tool paths. Rebuilt the unmodified
baseline in this leaf before editing and preserved its report, object, DOL,
all-source-object hashes, and original-function disassembly. The sole candidate
was then compiled and the full 43U build, report, and `build/43U/ok` rerun.

- The complete MemoryCardManager object is byte-identical to the fresh baseline
  (SHA256 `aa01d4ef861b2dd2e796ee3ffc1853de63dc0e7bed1245b46375aa51a3b62d4f`).
- All 1027 source-object SHA256 values are unchanged.
- Every report unit entry and all global measures are unchanged.
- Both edited functions remain objdiff 100%, 118/118 instructions, zero decoded
  instruction differences against the original objects.
- All 23 previously exact functions in the 26-function unit retain zero
  instruction differences. Code remains 4080/5396 bytes exact, with unchanged
  fuzzy score 98.22832%. The unit remains NonMatching and has no owned data.
- Pool audit passes (0/0 strings). Literal-reference audit analyzes all 23 exact
  functions with zero candidates, skips, or errors; there are no string
  arguments to compare.
- Full 43U build passes. DOL bytes equal the baseline and SHA1 is
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passes. No additional source trial was attempted.

Local evidence is preserved under `build/card-result-review/`: baseline and
candidate reports/objects/DOLs, object hashes, build logs, target disassembly,
`target-result-dataflow.json`, `pool.txt`, `literals.txt`, and `validation.json`.

GATE PASS: binary-neutral source-defined initialization; exact siblings,
code/data/link measures, all source-object bytes, and full-build/DOL preserved.
