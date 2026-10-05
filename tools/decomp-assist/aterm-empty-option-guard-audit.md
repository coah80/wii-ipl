# ATERM empty-option guard correction

Base: `d1ad0d823868730c4083bef29fb7e636c7856f24` (PR #1154).
One source change: restore the short-circuit null guard in protocol state 6.
No additional tuning, padding, flags, storage, symbols, or linking changes.

## Source-quality finding

When the decoded response length is zero, `optionEnd == option`, so the
empty-option branch assigns `optionValue = NULL` without assigning
`optionType`. The removed guard allowed the following condition to read the
uninitialized local, and potentially allowed the challenge copy to read NULL.
The receive checks do not establish that the decoded option length is positive:
the enclosing condition checks the outer payload length instead, and the
unwrap return value is ignored. Thus the empty decoded list is not excluded by
the existing code's input checks.

The original target has a corresponding machine-level defect: its only store
to stack slot `0x120(r1)` is on the nonempty path at `.text+0x1ef0`; the empty
path branches directly to the load at `.text+0x1efc` (DOL VA `0x814040b8`).
That does not justify an uninitialized C read. The PR's compiled source reads
a different unassigned slot, `0x124(r1)`, at `.text+0x1ef4`.

The restored condition first checks `optionValue == NULL`. The empty path
breaks out of the switch without evaluating `optionType` or copying a
challenge. Nonempty paths still initialize and check the type. Compiled source
confirms `cmpwi r15,0; beq` at `.text+0x1ef4/0x1ef8` precedes the local load
at `.text+0x1efc`. This is a defensive source correction, not an exact recovery
of the retail defect. Validation is static and local; no network or hardware
execution was performed.

## Measured cost

Fresh local default 43U build and explicit `progress build/43U/report.json
build/43U/ok` succeed using the existing toolchain. The DOL remains
`26116613f624061ba99c8d1a299aaa6efa85670d`; ATERM remains NonMatching.

- Protocol fuzzy: 92.100945 -> 91.91693
- Protocol instructions: 951 -> 953; target 951
- Unit fuzzy: 98.20204 -> 98.16559
- Unit matched code: unchanged, 12200/19204
- Objdiff exact functions: unchanged, 20/26
- Relocation-normalized strict instruction exact functions: unchanged, 20/26
- Matched data: 18864/18864 -> 18584/18864
- Protocol case offsets at target: 11/11 -> 6/11; cases 7-10 and default move +8
- Only `ATERMRunConfigProtocol` changes its normalized instruction stream

The data regression reflects the changed case-table targets. All 25 sibling
function streams are preserved. Empty string pools remain identical. The
literal-reference audit checks 20 exact functions and 6 arguments with no
candidates or errors; its all-functions pass checks 24 functions and 7
arguments, skipping discovery and protocol because their sizes differ.
`git diff --check` passes. This corrective candidate deliberately does not
satisfy the ordinary no-regression matching gate and needs parent acceptance.

## PR audit cross-checks

The pre-PR source preserved with the discovery-tail evidence is byte-identical
to `f598e410` (SHA256
`842ad263c2e5a65352e138f29343d3c4b7ad5aab0e00be9975dbf40d6eebdc31`).
Pre-PR versus PR target object section types, sizes, and bytes agree; all 594
resolved relocations agree. The buffer split preserves the full 0x1118-byte
region. The PR changes only the protocol's normalized source instructions.
Both pre-PR and PR have 20 strict exact siblings under the local normalized
comparison. `ATERMParsePacket` is exact but absent from the author's list of
19; there is no lost exact sibling.
