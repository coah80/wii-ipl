# Candidate-box window-name lifetime, 2026-10-03

Base: `57c17ebe2a7b3788cbbbf54f7dc9a9fb35abaec8`. 43U only.
Branch: `agent/bittle/candidatebox-window-name`.

## One bounded hypothesis

Immediately before the existing `mTextWindow.Create` call, capture the fixed
array address in `const char* windowName`, and pass that value to the unchanged
helper. No other production statement, helper body, type, scope or metadata was
changed. Exactly one candidate form was compiled.

`scW_predictWindow` is a mutable `char[16]` array defined at source line 220, not
a mutable pointer variable. Its object has size 16 at `.data+0x738` in both
objects, corresponding to target address 0x8165DA08, and contains
`W_predictWindow` followed by NUL. All named source references were inspected;
no writes beyond its initializer were found. The proof does not assume that
callbacks cannot change its characters: only the storage address is captured,
and every character read remains at its existing call site. The local pointer
is initialized before its sole source use, is not address-taken, has no shadow
or name collision, and crosses no branch or label.

`UITextWindow::Create` remains unchanged: obtain the pane manager, search for
the pane component, then search for the animation pane. Argument evaluation,
constructors, virtual calls and observable memory operations keep their order.

## Historical evidence and limits

`partial-oct2f.attempts.md:803` records the same window-name-capture hypothesis
at 93.67614%, 352/352 instructions and zero reported regressions. It was restored
in that older exact-only run. The historical variant tag is `d9cd56dc516f`; its
actual source snapshot and complete data/relocation gates are unavailable.

The current create body is byte-identical to the historical baseline body in
`c4857800df46ae3edfd824198fa09a31c4f6ce0f`, SHA256:
`c3e7e73cb75cef1cb36b2af59257e20e77b6afdc1c0db23da7b2e4f8a23d9824`.
The result below reproduces the old score numerically, but is a current-context
hypothesis replay, not a claimed identical historical source reproduction.

Other prior allocation, typed receiver, scoped buffer, pane-array traversal and
helper-lifetime experiments in tiCandidateBox, data-d15, rt8, partial-oct2d and
sol-high-structural-round4 attempt logs were read. No additional variant or
declaration sweep was run.

## Frozen baseline and results

The baseline cache came from the parent's independently verified frozen
`wii-rgb422-next-review`, HEAD `8f1d13822b51509c354ab676d5e6c0097b7e0552`, tree
`1dde64c7318dc1cfdb4fd7e067931d495d56b02c`, identical to the selected base tree.
All 1027 copied source-object hashes were checked. A real baseline compilation
and fresh complete official report reproduced that reference exactly.

Baseline -> candidate:
- LayoutByNW4R::create: 92.71023 -> 93.67614%.
- Function length: 351 -> 352 instructions, 1404 -> 1408 bytes; target is 1408.
- Unit fuzzy: 99.509 -> 99.56567%.
- Exact functions: 109/112 unchanged; exact code: 19988/24000 unchanged.
- Exact data: 4652/4652 unchanged; link status unchanged.
- All sibling function metrics and all other 1026 unit records unchanged.

Source SHA256 before:
`726f8910224b1f804a3bfcf5af4a4ea5ad8397d18889f0b7ed0e6841ecb97ec8`.
Source SHA256 after:
`fe5f1e07efec104d4adede90279fcb35470080b4f2eeadb495da73da7c98d9ce`.
Object SHA256 before:
`60d61cfbc40a8bd72bb04628c7a385004aff7c2b17a72421f3f10129a624f9cb`.
Object SHA256 after:
`677fd43d2cc7dc39bb0c728006c67d9498f9ca1a5046c2bc6812b2fe80a31fe4`.

## Instruction, continuation and relocation evidence

The target computes the window-name address at +0x50C, before the pane-manager
virtual call, then reuses it for both searches. The baseline instead computes
that same address separately for the two name arguments.

The candidate changes only these instructions relative to baseline:
- Inserts `addi r28,r29,0x738` at +0x50C.
- Moves the existing conditional branch to +0x510 and adjusts its destination
  from baseline +0x514 to candidate +0x518, preserving the same continuation.
- Replaces the two address calculations at baseline +0x528/+0x538 with
  `mr r4,r28` at candidate +0x52C/+0x53C.

Every instruction before the insertion is identical. Every later instruction
is identical under that single insertion-offset map except the branch and two
argument copies listed above. All earlier r28 uses have ended before its new
definition. The original data-base value r29 and new address value r28 survive
the same calls under the existing ABI. Frame 0x20, save/restore helper range,
all other argument registers and every direct/virtual call remain unchanged.
The new address is an addition, never a global-pointer or character load.

All allocated nontext section lengths and bytes, and all raw nontext relocation
section payloads, are byte-identical. Compiler string/symbol metadata is not
byte-identical. All text outside this function is byte-identical after
removing the respective function slices. Sibling function sizes and canonical
function-relative relocation targets are identical. This function's relocation
records follow exactly the same four-byte insertion-offset map.

An initial name-only audit flagged renamed compiler-generated `@NNNN` labels.
That failed check is preserved, not concealed. Resolving each data label to its
unchanged section/offset and each code target to function-plus-addend proves the
targets are unchanged. Later function placements move by four bytes because
the real function grows; these ordinary relocations are not new data, table
entry changes or metadata overrides. Canonical evidence is recorded separately
from the original name-only result.

Exhaustive accounting finds exactly four changed section payloads:
- `.text`: 28564 -> 28568 bytes. A positional comparison finds 20603 changed
  common byte positions because the tail moves; the function-splice proof
  establishes that every byte outside create is unchanged under that move.
- `.rela.text`: 4728 bytes unchanged in length, 335 changed bytes. All 394
  records preserve raw type, symbol index and addend. Source offsets at or
  after the actual insertion move by exactly four bytes: exactly 331 records
  move, and the other 63 do not.
- `.symtab`: 5392 bytes unchanged in length, 131 changed bytes. Exactly 129
  later STT_FUNC symbol values move by four bytes; only create's size changes,
  from 1404 to 1408. All bindings, names, sizes of siblings and other fields
  are unchanged.
- `.strtab`: 15521 bytes unchanged in length, 65 changed bytes representing
  59 `@NNNN` names. Every renamed symbol is STB_LOCAL/STT_OBJECT, with the same
  symbol index, string offset, section, section offset, size and other fields.
  No public symbol name changes. These names do not describe different data.

All other section payloads are identical, including `.rela.ctors`, `.rela.rodata`,
`.rela.data` and `.rela.sdata`. The ELF header is identical. Section-header
changes are limited to `.text` size and `.ctors` physical file offset
28616 -> 28620. Four pre-rodata alignment bytes are consumed; overall file size
and the rodata file position remain unchanged.

The committed read-only verifier checks pinned object hashes, every changed
byte position, every symbol entry, all 752 relocation records and referents,
the function-splice relation and the exact instruction/branch mapping above.
It does not simply discard names or register numbers. Its optional details file
enumerates all before/after byte offsets, symbol entries and relocation targets.
Run from the leaf with cached tools:

    PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=../local-tools ../.venv/bin/python \
      tools/decomp-assist/verify_tiCandidateBox_window_name.py \
      ../candidatebox-window-name-evidence/baseline.o \
      build/43U/src/src/keyboard/tiCandidateBox.o \
      --target build/43U/obj/src/keyboard/tiCandidateBox.o \
      --details ../candidatebox-window-name-evidence/exhaustive-object-proof.json

## Full verification

- Full `all_source`, default `progress` and `build/43U/ok` passed.
- All other 1026 source-object hashes remain equal to the frozen reference.
- Fresh final report equals the immutable candidate report across all 1027
  units; only this unit/function's fuzzy measures differ from baseline.
- All 109 exact siblings independently have zero instruction differences.
- Pool: all 57 strings identical.
- Literal advisory: 112 functions, 32 arguments, no skips, candidates or errors.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passes; no new assembly, padding, guards or fake storage.
- One real baseline and one candidate compilation. The full build rebuilt the
  other 1026 objects but did not recompile this already-current candidate.
- After correcting the metadata accounting, the full build/ok/DOL, official
  report, all 109 instruction-exact siblings and all 1026 other object hashes
  were checked again. They pass with zero further compilations or source edits.

Private workspace evidence: `../candidatebox-window-name-evidence/`, containing
baseline/candidate source/object/report snapshots, exact patch, frozen reference
check, instruction/continuation and canonical relocation audits, original failed
name-only audit, pool/literal logs, full build and final-verification.json.
Original binaries remain local; none are committed.

GATE: strict fuzzy improvement with preserved exact/data/link/sibling gates.
Candidate retained only for independent parent review. No new exact-function,
whole-unit completion, Wii runtime execution, main change or remote action is
claimed. No follow-on variant was run.
