# Right-scroll address capture, 2026-10-03

Base: `d0c82cfe83c4e02d6ee9957fe34a5c2cde8dd181`, 43U only.
Branch: `agent/bittle/candidatebox-right-names`. Exactly one authorized form.

## Source-grounded hypothesis and scope

The sole production change captures the two actual right-scroll arguments
immediately before their existing Create call:

    const char* rightScrollBoundName = paneNames + 88;
    const char* rightScrollPaneName = paneNames + 108;
    mRightScroll.Create(this, rightScrollPaneName, rightScrollBoundName);

The existing paneNames initialization, left captures, window capture, every
helper, constructor, call order and other production statement remain unchanged.
Both new locals are initialized, unshadowed, and not address-taken. No source
forcing, padding, extra allocation, raw offsets into unrelated objects,
uninitialized values, array-bound violations, assembly, volatile, compiler
flags, data declarations or symbol configuration changes were introduced.

The target computes the bounding and visible-pane addresses at create
+0x464/+0x46C, before getPaneManager, and retains them for arguments at
+0x490/+0x4A0/+0x4B0. The baseline instead computes the corresponding three
addresses at +0x498/+0x4A8/+0x4B8. This trial tests that specific lifetime;
it is not a local-order search.

scPaneNameTable is a fixed const char[132] array, not a mutable pointer variable.
Its source and target ELF objects have identical bytes at .data+0x6B4, size 132.
The original DOL independently contains the same 132 bytes at 0x8165D984.
Offsets 88 and 108 select B_prdc_scrl_Rght and P_prdc_scrl_Rght. Both records
contain 16 characters plus NUL, ending at exclusive offsets 105 and 125, within 132.
The pointer calculations capture storage addresses, not character contents.

UIButton::Create remains unchanged: getPaneManager, searchPaneComponent(pane),
searchPaneComponent(bound), searchAnmPane(pane), then setting the bound listener.
The source change preserves all argument values and observable operations.
Non-recording additions may be scheduled around the preceding listener store
without changing it, the condition register, or any pointer/content read.

Prior rt8.attempts.md:88 tested direct scroll-name arguments after removing the
shared base. data-d15.attempts.md:341 tested a full-array reference.
partial-oct2f.attempts.md:803 tested the window capture. Other inspected records
cover allocation, receiver and Init-loop forms. No specific right-pair capture
was found; historical source snapshots are unavailable, so exhaustive novelty
is not claimed. The earlier left capture was already present in this baseline.

## Frozen baseline and measured result

Cache source: parent-frozen wii-candidatebox-left-review, HEAD
`791865aac94388ec175372982a4e8543389c3d4c`, tree
`8216868fbd230fc69c806247d8b283ac15ef0682`, identical to the selected base tree.
All 1027 inherited source objects were checked against that frozen cache.
A real baseline compile and complete official report reproduced the reference
exactly before the sole candidate compile.

- create fuzzy: 94.59091 -> 95.99148%.
- Unit fuzzy: 99.61933 -> 99.7015%.
- Baseline: 1416 bytes / 354 instructions / frame 0x30 /save/restore r25-r31.
- Candidate: 1424 bytes / 356 instructions / frame 0x30 /save/restore r25-r31.
- Original target: 1408 bytes / 352 instructions / frame 0x20 /save/restore r26-r31.
- Exact functions 109/112, matched code 19988/24000, exact data 4652/4652,
  unit link status and every sibling metric remain unchanged.

The extra two instructions are a real code-size cost. The existing 16-byte
frame excess remains. Neither exact matching nor acceptance follows from the
fuzzy gain. Four earlier structural excess instructions remain: two Init-loop
address additions and two separate shared-data-base materializations.

Source SHA256 before/after:
`936ab4742caa71293284a33425f73321f172dc5b563cc215c7f213ddd3bef3e3`
`0e66ae8a498610825923bddf1a9df1904bb5513a7e7a44cd031b01ee0c04aa23`.
Object SHA256 before/after:
`31106c95cfcd2e8274f43ee2b5eb51be9861e577a5d967a96e667766feb71200`
`3baa124ace040d28f7790fd73e31a20a749f7380b9794f88c51a42bdd4cac8c5`.

## Exhaustive instruction, CFG, lifetime and ABI proof

Candidate inserts addi r25,r30,0x58 at +0x474 and addi r26,r30,0x6C at +0x47C.
Baseline instructions below +0x474 keep their offsets; baseline+0x474 moves by 4;
all baseline instructions from +0x478 onward move by 8. The interleaved listener
store is otherwise unchanged.

Exactly five existing instructions change:
- Baseline+0x478 beq0x480 becomes candidate+0x480 beq0x488.
- Baseline+0x498/+0x4A8/+0x4B8 additions become candidate+0x4A0/+0x4B0/+0x4C0
  moves from r26/r25/r26, respectively.
- Baseline+0x518 beq0x520 becomes candidate+0x520 beq0x528.

Every other instruction is identical under the location map. Every branch
source/target pair is checked, including the two adjusted continuations, and
the entire direct/indirect call sequence is unchanged. The fixed r30 table base
was established at+0x29C from the unchanged .data base and remains unmodified.
New addresses survive intervening calls under the same callee-saved ABI.

The old left-bound r26 last use is+0x43C; the old left-pane r25 last use is+0x44C.
Both precede the new definitions. The new right-bound/pane last uses are
+0x4B0/+0x4C0, before the separate window-name r25 definition at+0x51C.
No blanket register renaming is used in the proof; all other register uses are
identical, and there are no baseline r25/r26 uses between these definitions.

Frame, save/restore helper targets, LR slot, GPR slots, alignment and epilogue
are unchanged. Both versions use the same six r1/r11 instructions under the
location map, with no other stack load/store, stack argument, exposed local
address or new callback-visible storage. r25-r31 save slots remain incoming-SP
minus 28 through minus 4; LR remains incoming-SP+4. Both actual helper bodies are
checked against the original Runtime object and original DOL addresses
0x815F94B8/0x815F9504. No runtime execution or stack-introspection equivalence
claim is made; this is an instruction/lifetime/ABI audit.

The original DOL SHA1 is checked. Its linked data-base setup proves the target
right names resolve to the actual array. All 320 target instruction words without
relocations compare directly with the DOL; the 32 relocated words are explicitly
excluded from that raw comparison. The two linked base-setup instructions and
five target right-name instructions are checked separately.

## Exhaustive ELF accounting

Every allocated nontext section size and byte is unchanged. Text outside
create is byte-identical under removal of the respective function slices.
Exactly four section payloads change:
- .text: 28576 -> 28584 bytes; 20906 positional common bytes differ because of
  insertion/tail shift. The exact splice proof accounts for that shift.
- .rela.text: 4728 bytes unchanged in length; 338 changed bytes, solely source
  offsets of 333 records moving by 8.
- .symtab: 5392 bytes unchanged in length; 134 changed bytes. Exactly 129 later
  function values move by 8; only create's size changes.
- .strtab: 15521 bytes unchanged in length; 70 changed bytes for 59 private @NNNN
  names advancing by 2. Every renamed symbol is STB_LOCAL/STT_OBJECT with
  unchanged index, string offset, data section/offset/extent and other fields.

All 337 symbols are checked field-by-field. No symbol index, public name,
binding or visibility changes; no symbol appears or disappears. Both complete
string tables are reconstructed from symbol-name intervals, accounting for
every byte. All 752 relocations retain symbol index, type and addend; only the
333 text source offsets described above move. Their symbol targets retain
identity under the proven symbol relation. All raw nontext relocation payloads,
including .rela.data, are byte-identical. All other section payloads, including
.comment and .shstrtab, are byte-identical. ELF/file offsets after .text and
file size advance by 8, and every header field change is checked explicitly.

An initial proof assumption that every code-target addend was zero failed on
seven existing .rela.data jump-table entries into CandidateScrollAnmPane's
onAnmEvent. That failure is preserved. These are unchanged, bounded intra-function
addends 192/228/332/296/400/468/500 in the unchanged 524-byte sibling function;
the corrected proof checks the same function, addend, size and instruction
bytes at each destination. This is not ignored relocation drift.

## Validation and reproduction

- All_source rebuilt the other 1026 objects, with no further candidate compile.
- Full default build and progress/build/43U/ok pass; main.dol SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- All 1026 other object hashes and entire official unit records equal baseline.
- All 109 exact functions independently compare at zero instruction differences.
- Fresh final report equals the immutable candidate report. Within the owned
  unit only create's fuzzy score and the text/unit fuzzy aggregates change.
- Pool: 57 identical strings. An initial wrong-path read-only invocation was
  corrected; its error did not run any compiler or change inputs.
- Literal advisory: 111 functions/27 arguments pass, zero candidates/errors.
  It explicitly skips create because target/candidate sizes differ. The complete
  instruction map plus source/target/original-DOL address and byte proof above
  supply separate argument evidence; the tool skip is not concealed.
- git diff --check passes; production diff is exactly three insertions and one
  deletion at the right-scroll call. No shared tools or flags were changed.

Read-only reproduction from this leaf:

    PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=../local-tools ../.venv/bin/python \
      tools/decomp-assist/verify_tiCandidateBox_right_names.py \
      ../candidatebox-right-names-evidence/baseline.o \
      build/43U/src/src/keyboard/tiCandidateBox.o \
      --target build/43U/obj/src/keyboard/tiCandidateBox.o \
      --runtime build/43U/src/libs/Runtime/src/runtime.o \
      --original-runtime build/43U/obj/libs/Runtime/src/runtime.o \
      --original-dol orig/43U/00000008.app \
      --details ../candidatebox-right-names-evidence/exhaustive-proof.json

Evidence: ../candidatebox-right-names-evidence/ contains immutable sources,
objects, full reports, patch, compile logs, full build, original proof failure,
corrected exhaustive proof, and final-verification.json. Original binaries are
not committed. Exactly one baseline and one candidate were compiled; no further
source form or remote action occurred.

GATE: strict fuzzy gain with unchanged exact/data/link/sibling measures;
extra 8 code bytes and inherited larger frame explicitly disclosed. Candidate
is frozen for independent parent review, not an exact-match or score-only
acceptance claim.
