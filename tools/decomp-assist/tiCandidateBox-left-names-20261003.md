# Left-scroll address capture, 2026-10-03

Base: `30d968099a52cc95308f99ba589b2a91c0bc7645`, 43U only.
Branch: `agent/bittle/candidatebox-left-names`. One authorized candidate.

## Source scope and history

The sole production change captures two real arguments immediately before the
existing left-scroll Create call:

    const char* leftScrollBoundName = paneNames + 48;
    const char* leftScrollPaneName = paneNames + 68;
    mLeftScroll.Create(this, leftScrollPaneName, leftScrollBoundName);

The existing paneNames initializer, right-scroll call, accepted window-name
capture, all constructors, helpers and subsequent statements remain unchanged.
Both locals are initialized, unshadowed and not address-taken. Only their values
are passed; no new local storage is exposed to a callback.

paneNames is a local const-char pointer initialized once from the sole definition
of `scPaneNameTable`, a const char[132] object. This is fixed array storage, not
a mutable global pointer read. Original and compiled objects agree on size 132,
`.data+0x6B4`, target address 0x8165D984 and all bytes. Offsets 48 and 68 point to
the B_prdc_scrl_Left and P_prdc_scrl_Left records. Each name has 16 characters
plus NUL, 17 bytes within its 20-byte record; ends 65 and 85 lie within 132.
The transformation caches addresses, not character contents.

UIButton::Create is unchanged. Its observable order remains getPaneManager,
searchPaneComponent(s1), searchPaneComponent(s2), searchAnmPane(s1), then setting
the bounding pane listener. Both pointer additions are side-effect-free and
remain within the same array. All lookup arguments and their order are retained.

Target create +0x3F4/+0x3F8 materializes the bounding and visible-pane addresses
before the pane-manager call. The baseline rematerializes them for the three
lookup arguments. The previously accepted window capture supports the source
form, but is not treated as a promise of this candidate's result.

Prior rt8.attempts.md:86-89 includes removing the shared paneNames base and
passing direct array expressions, yielding 353/352 instructions. data-d15:341
includes a full-array reference; earlier logs include receiver and shared Init
loop changes. No exact two-local left-pair capture was found in the surviving
records. Those historical source snapshots are unavailable, so broader overlap
cannot be excluded. No old numeric result is claimed for this specific form.

## Frozen baseline and measured result

The baseline came from parent `wii-candidatebox-review`, HEAD
`60c782b0e7ea507e4f74a2d0419cec9c6527c84d`, tree
`598351eedd350d39d3f4edabed2b861d055b497f`, identical to the selected base tree.
All 1027 cached objects were checked. The real baseline compile and complete
official report reproduced this frozen reference exactly.

- create fuzzy: 93.67614 -> 94.59091%.
- Unit fuzzy: 99.56567 -> 99.61933%.
- Baseline: 1408 bytes / 352 instructions / frame 0x20.
- Candidate: 1416 bytes / 354 instructions / frame 0x30.
- Original target: 1408 bytes / 352 instructions / frame 0x20.
- Exact functions 109/112, matched code 19988/24000, exact data 4652/4652,
  and link status are unchanged.

The larger frame and extra two instructions are real costs, not hidden or
treated as original matches. Score alone is not acceptance.

Source hashes before/after:
`fe5f1e07efec104d4adede90279fcb35470080b4f2eeadb495da73da7c98d9ce`
`936ab4742caa71293284a33425f73321f172dc5b563cc215c7f213ddd3bef3e3`.
Object hashes before/after:
`677fd43d2cc7dc39bb0c728006c67d9498f9ca1a5046c2bc6812b2fe80a31fe4`
`31106c95cfcd2e8274f43ee2b5eb51be9861e577a5d967a96e667766feb71200`.

## Exact instruction and lifetime mapping

Two address calculations are inserted at candidate +0x404/+0x408:
`addi r26,r30,0x30` and `addi r25,r30,0x44`. r30 is proved to be .data+0x6B4,
defined at baseline +0x29C from the unchanged r29 data base. These non-recording
instructions do not alter the condition register between the comparison and
existing branch.

The baseline left-call arguments at +0x424/+0x434/+0x444 become candidate
+0x42C/+0x43C/+0x44C register copies from r25/r26/r25. Branch mappings are
baseline +0x404 -> candidate +0x40C (target +0x40C -> +0x414), +0x470 -> +0x478
(target +0x478 -> +0x480), and +0x510 -> +0x518 (target +0x518 -> +0x520).
All other following instruction locations advance by eight bytes.

The allocator's register role changes r27 -> r25 only at its definition +0x18
and five argument moves +0x24/+0x54/+0x64/+0xCC/+0x110. Its last use precedes
the later left-pane definition. The retained window address changes r28 -> r25
only at its own definition and two argument moves, baseline offsets
+0x50C/+0x52C/+0x53C. These are separate per-definition lifetimes, not a blanket
register renaming. All remaining differences are the explicit prologue/epilogue
changes below. The verifier checks all 23 changed existing instructions and both
insertions; everything else is instruction-identical under the location map.

### Stack and ABI audit

The frame increases by 16 bytes, retaining 16-byte alignment. r1/r11 occur only
in six prologue/epilogue instructions. No other stack-relative load/store, stack
address formation, stack argument, address-taken local, or stack address passed
to a lookup/allocation/callback exists in this function. Existing object/member
addresses remain based on this; allocation buffers are heap values. No stack
address is explicitly retained, compared or hashed by the owned code.

Both versions save LR at incoming-SP+4. Both reconstruct r11 as incoming SP for
the save/restore helpers. Existing r27-r31 slots stay at incoming-SP-20 through
-4. Candidate adds r25/r26 at incoming-SP-28/-24, inside its larger private
frame. The actual `_savegpr_25` and `_restgpr_25` bodies were compared with the
original Runtime object: seven matching word stores/loads followed by blr.
They touch no argument register and restore every additional callee-saved GPR.
The common epilogue restores LR and incoming SP on the sole return path.

Ordinary ABI argument values, object addresses and branch continuations are
preserved. The 16 extra stack bytes remain a resource cost. No Wii runtime,
stack-exhaustion equivalence or arbitrary callback stack-introspection
equivalence is claimed. Parent review of this measured larger-frame candidate
is required; no attempt was made to force the old frame.

## Exhaustive object accounting

All allocated nontext section sizes and payloads are identical. Text outside
create is identical after removing the respective function slices. Exactly six
section payloads change:
- .text: 28568 -> 28576 bytes; 21016 positional common bytes differ due to the
  insertion and tail shift, with the exact function-splice relation verified.
- .rela.text: same 4728-byte length, 397 changed bytes.
- .rela.data: same 3780-byte length, 40 changed bytes. Raw bytes are NOT identical.
- .symtab: same 5392-byte length, 320 changed bytes.
- .strtab: same 15521-byte length, 2665 changed bytes.
- .comment: same 2740-byte length, 26 changed bytes.

The verifier proves a bijection of all 337 symbols. 59 private STB_LOCAL/
STT_OBJECT @NNNN names advance by two, with data section/offset/extent and all
other semantic attributes unchanged. No public name changes or symbols appear
or disappear. 44 symbol indices reorder; 129 later function values move by
eight bytes; only create's size increases. Both complete string tables are
reconstructed from the checked symbol-name intervals, accounting for every byte.

All 752 relocation records are checked. Exactly 335 .rela.text source offsets
move by eight bytes; types and addends do not change. 53 text and 40 data
relocation symbol indices change. The data changes and all but two text changes
resolve through the proved symbol bijection to the same targets. The two
explicit exceptions are create's save/restore helper calls, r27 -> r25, whose
actual behavior is verified above. All sibling relocation referents and
function-relative instruction semantics remain unchanged.

The entire .comment difference is accounted byte-for-byte as an unchanged
44-byte prefix followed by 337 unchanged eight-byte records permuted by the
same symbol-index bijection. This is an exact byte relationship, not an
assumption that an unknown metadata difference can be ignored. The ELF section
table/file offsets advance by eight bytes after the enlarged .text section;
file size also grows by eight. All other section payloads remain identical.

## Validation and reproduction

- Full all_source/default progress/build/43U/ok passes; DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- All other 1026 source objects and complete unit records equal frozen baseline.
- All 109 exact functions independently compare at zero instruction differences.
- Fresh final report equals the immutable candidate report; no sibling metrics
  or data/exact/link measure regressions exist.
- Pool: 57 identical strings.
- Literal advisory: 111 functions/27 arguments pass, zero candidates/errors.
  create is explicitly skipped because its size now differs from target. The
  exact instruction/lifetime map and original-array address/byte checks above
  supply the separate argument evidence; the automated skip is not concealed.
- One real baseline and one candidate compilation; the full build rebuilt the
  other 1026 objects, with no candidate recompile or follow-on form.

Runnable read-only proof, using cached tools from this leaf:

    PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=../local-tools ../.venv/bin/python \
      tools/decomp-assist/verify_tiCandidateBox_left_names.py \
      ../candidatebox-left-names-evidence/baseline.o \
      build/43U/src/src/keyboard/tiCandidateBox.o \
      --target build/43U/obj/src/keyboard/tiCandidateBox.o \
      --runtime build/43U/src/libs/Runtime/src/runtime.o \
      --original-runtime build/43U/obj/libs/Runtime/src/runtime.o \
      --details ../candidatebox-left-names-evidence/exhaustive-proof.json

Evidence is local in `../candidatebox-left-names-evidence/`: immutable sources,
objects, reports, patch and compile logs; full build; pool/literal advisory;
exhaustive symbol/section/relocation/instruction proof; final-verification.json.
Original binaries are not committed. Source remains frozen at the one measured
candidate. No main or remote action occurred.

GATE: strict fuzzy gain with exact/data/link/sibling preservation; larger frame
and literal-tool skip explicitly disclosed. Candidate awaits independent parent
review, with no claim of exact completion or acceptance from score alone.
