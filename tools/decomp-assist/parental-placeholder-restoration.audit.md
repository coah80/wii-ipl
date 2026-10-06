# Restore the unresolved parental dump placeholder

Base: `c3dbaf8c8ec41e7c48bd0e93c895c97e089de65d` (fork main after #1245).
This is a corrective rollback of #1244, not a reconstruction or a new match.

## Scope and evidence

Restore only the production files `src/scene/setting/iplParental.cpp` and
`include/scene/setting/iplParental.h` to their exact pre-#1244 blobs from
`7c6393f9^` (`1fd09707`). The board FocusObject changes from #1245 are untouched.
The eleven `DECOMP_FORCE_ACTIVE` calls remain known, unresolved string-retention
placeholders. They preserve the observed literals and their order, without
claiming to recover their stripped owner or exposing an invented callable API.

The removed `Parental::dump` was 248 bytes in the freshly compiled baseline
object. It has no function counterpart in the 43U retail object, no configured
retail symbol, and no symbol in the baseline linked ELF. The earlier
`grok-parental.attempts.md` establishes pool and retained-function preservation;
it does not supply an original body, pinned source, or recovered contract for
the added dump. Its matching gates therefore do not validate that body.
`rx67b.classification.md:145-155` already records that no declared/called dump
method or complete source had been recovered.

Two concrete formatting defects also block retaining this speculative body:

- `SCParentalControlsInfo::password` is `char[4]`, immediately followed by
  `secretQuestion` (`libs/RVL_SDK/include/revolution/sc.h:116-130`).
  `Parental::checkPass` copies all four password bytes without appending a NUL
  (`src/scene/setting/iplParental.cpp:92-101`). Passing that field directly to
  unbounded `%s` can read beyond the password into adjacent fields
- `secretAnswer` is `u16[32]`, and `getSecA`/`setSecA` treat it as wide-character
  text. Passing it to narrow `%s` reads byte representations instead of wide
  characters. On this big-endian target an ordinary ASCII-range first wide
  character begins with a zero byte and prints as an empty string

`OSReport` forwards to `vprintf` (`libs/RVL_SDK/src/os/OSError.c:16-24`).
The narrow `%s` branch extracts `char*` and calls `strlen` when no precision is
present (`libs/MSL/src/MSL_Common/printf.c:1144,1164`), confirming both defects.

These are source-level defects in discarded code. No runtime regression in the
existing linked retail DOL is asserted. Merely adjusting format strings or
inventing conversion code would still leave the original implementation
unproven, so this correction restores the explicit unresolved placeholder.
The old attempts log is preserved as history, not treated as reconstruction
proof. No new dump semantics are proposed.

## Fresh isolated 43U validation

An untouched c3dbaf8c baseline was fully built in this leaf with the recovered
source-built toolchain, then its entire `build/43U` directory was saved before
restoring the two production files. The candidate's affected objects, full
link, report, progress and explicit `build/43U/ok` targets were rebuilt.
Only 43U was configured or built.

- Baseline and candidate builds pass; DOL bytes are identical, with SHA1
  `26116613f624061ba99c8d1a299aaa6efa85670d`
- All 30 retail functions remain exact and fully linked: 2,376 bytes / 594
  instructions and 161 normalized relocation records. Direct per-function
  instruction bytes and resolved relocations equal both baseline and retail
- Source `.data` (332 bytes), `.bss` (1,208), `.sdata` (10) and `.sbss` (13)
  and all their relocations are unchanged. They equal retail after existing
  trailing zero alignment padding (336 / 1,208 / 16 / 16 bytes)
- Literal pools are identical to retail, 17/17, with no first divergence.
  Unit code/data/function/link measures remain 100%; retail data is 1,576 bytes
- 1,026 of 1,027 source objects are wholly byte-identical. Only Parental.o
  differs: the discarded dump is replaced by eleven known retention helpers.
  FocusObject.o and every other source object are unchanged
- Linked ELF allocated sections are byte-identical; only non-allocated
  `.strtab` differs. The dump symbol is absent from both linked ELFs
- The entire report is byte-identical, including all unit/function/section and
  global measures; SHA256
  `b11f5b449a1426e2ebf16edc60ece3dfad28d0204a72de8f06c99a6e93a3c7f0`
- Direct-call audit: 56/56 identical destinations across 30 functions, no
  skips/errors. Literal-reference audit: 30 functions, 8 arguments, no
  candidates/skips/errors
- Stock `ctxdiff.py` is blocked by its unavailable external `odiff` module.
  No stock ctxdiff pass is claimed. The direct instruction-byte and resolved
  relocation comparisons above establish the retained-function equality
- All 20 workflow-guard tests and `git diff --check` pass
- The terminal checker correctly reports `DECOMPLETE_FAIL`: overall code
  96.43266% exact / 99.86033% fuzzy / 83.58948% linked; data 100% exact /
  85.56216% linked; 12,491/12,563 functions exact and 993/1,027 units complete.
  This corrective rollback does not complete the project

Local evidence is under `build/audit-parental/`: preserved baseline output,
build logs, `validate_objects.py`, `validation.json`, pool, call-target and
literal-reference audits, status, workflow tests, and the expected terminal
checker failure. Reproduce with `build/build-43U.sh` and
`../wii-toolchain-venv/bin/python build/audit-parental/validate_objects.py`.
The comparison uses function-relative code identities and actual data locations
for relocations, rather than relying on compiler-local symbol spelling.

This leaf is local only: no main-source edits, push, PR, merge, upstream contact
or upload is part of this work. The parent must independently verify it before
any acceptance or integration.
