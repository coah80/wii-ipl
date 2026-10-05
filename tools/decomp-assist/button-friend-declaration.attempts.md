# Button friend declaration consistency

2026-10-05; base `7b29f284c1c864222e88e5e83418ee7b0c50bb1d`.
Leaf: `agent/fix/button-friend-declaration`.

The implementation-only friend introduced in PR1176 made the `Button` class
definition differ across translation units. Remove only the four conditional
directives around its existing namespace forward declaration and friend.
Both declarations now appear consistently; the function remains the existing
`ipl::scene` C-linkage `BOOL push_button_queue(void*, const void*)`.
No definition, export, layout, function body, symbol configuration, compiler
flag, or linkage changes. The unused source macro is deliberately untouched.

## Independent trial

Preserved all 1,027 source objects, the complete report, and the linked DOL
before editing. Configured 43U from this leaf with the recovered local tool
paths, then ran `ninja -j4` and
`ninja -j4 progress build/43U/report.json build/43U/ok`.
The build log records all 1,027 MWCC compilations.

- All 1,027 rebuilt **entire ELF files** are byte-identical to the baseline,
  including debug information and all 22 header-dependent objects
- Separately compared 2,717 allocated sections, 117,545 allocated-section
  relocations, and 15,880 defined-function entries and their symbol order:
  zero differences
- The relocation comparison resolves section/symbol table indices to their
  exact identities; it does not mask instruction bytes, rename anonymous
  symbols, ignore addends, or reorder symbols
- The complete 1,027-unit report is byte-identical, including every function,
  section, exact sibling, and link measure. Report SHA256:
  `9d3c9a79796a042508e6dba0ba26db6e153ad7ffa44deef7eb95900a048cde38`
- Queue wrapper versus the original `Queue<Command,8>::push`: 28/28
  instructions, zero diagnostic differences, zero relocations; string pool
  32/32 identical
- DOL bytes unchanged; SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes. The global completion checker still reports the
  unchanged pre-existing incomplete project; this is not a completion claim

The 22 dependencies are `src/system/RsoSystem.cpp`, and these scene units:
`address/{iplAddress,iplAddressAddSel,iplAddressEdit}`,
`board/{iplBoard,iplBoardObject,iplFocusObject}`, `button/{iplButton,iplArrow}`,
`calendar/{iplCalendar,iplDate}`, `channelSelect/iplChannelSelect`,
`channelTitle/iplChannelTitle`, `faceSelect/iplFaceSelect`,
`letterWriter/iplLetterWriter`, `mailAddSel/iplMailAddressSelect`,
`sceneMisc/iplReboot`, `sceneSystem/iplSceneCreator`, `sdButton/iplSDMenuButton`,
`sdChannelMemory/iplSDMemory`, `sdChannelTitle/iplSDChannelTitle`, and
`textWriter/iplTextWriter` (all `.cpp`). The fresh dependency records agree.

Local evidence: `build/button-friend-review/` contains the preserved baseline,
`configure.log`, `build.log`, `audit.py`, `audit-results.json`,
`audit-summary.json`, and completion/status output. Audit script SHA256:
`ede148cf70ac05d0e7a5be5a257311b786293969d6fb2ff404ae5f654e070c90`.
The audit script uses installed pyelftools; the focused instruction diagnostic
uses the separately restored local helper, not a claimed recovery of the
historical helper. Raw ELF equality is the stronger neutrality evidence here.

GATE PASS: bounded binary-neutral declaration repair. No runtime execution,
new matching gain, upstream contact, push, PR, merge, or main-worktree edit.
