# SD channel event predicate correction, 2026-10-03

Separate follow-on to eac8c5d6 (scissor reconstruction), on baseline b9407106.
Only four call sites in SDChannelSelectEventHandler::onEvent change.
No headers, metadata, other source units, constructor aliases or linking change.

## Original binary evidence

Independently parsed the DOL section table in orig/43U/00000008.app, verified
SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, and decoded the signed relative
branch displacement at each call. No symbol-name or objdiff assumption was
used to select the destinations.

onEvent begins at 0x813E28B4. Its calls at offsets 0x124, 0x1DC, 0x218 and
0x270 (addresses 0x813E29D8, 0x813E2A90, 0x813E2ACC, 0x813E2B24) all branch
to 0x813E3330. The raw callee reads the channel word at offset 0x84 and
returns true for values zero or three. The extracted object relocations
independently name iplSDChannelObj_hasAppMeta at all four calls, and its
source reads mStateFlags with those same tests.

The old source instead calls isChannelReady, whose original address is
0x813DF1E4. That raw callee reads offset 0x14 and returns true only for three.
Its source tests mState == 3. These are distinct fields and predicates, not
interchangeable aliases. Restore hasAppMeta for trigger, drag, point and
leave event dispatch. Keep every existing event/state/controller/card guard.

For the separately observed constructor-name mismatches, raw original bodies
at 0x81362A5C and 0x81374884 are byte-identical. No constructor change is made
merely to alter names. Existing vtable placement/binding differences also
remain outside this patch.

## Measurement and verification

- onEvent was reported 100% before this correction and remains 100%; no
  progress credit is claimed for the semantic repair
- Relocation-aware ctxdiff improves four differences -> zero, 168/168 instructions
- Compared to eac8c5d6, only the four call relocations change; every other
  function's normalized instructions/relocations remain identical
- All allocated section bytes, including raw .text, remain identical to
  eac8c5d6; this is why relocation targets must be checked separately
- The complete project report is identical to the scissor candidate
- Unit remains 122/129 reported-exact, code 29412/33828, data 2960/2960,
  fuzzy 99.749435%; setChannelScissor remains 99.5279%
- Full 43U all_source/report/ok build passes
- Pool identical, 101/101; literal audit 73 arguments across 122 functions,
  no skips/candidates/errors
- DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

## Distinguishing tests

The native C++ harness extracts the old/new handler bodies and supplies
local event/controller/scene mocks. The two predicates use the independently
verified field tests. GCC -O2 -Wall -Wextra -Werror (excluding the preexisting
unused label warning), with UBSan enabled, passes 198 cases.

Six channel-state values, eight state-flag values and all four events give
192 combinations, including 64 cases where the old predicate dispatched
differently. State 0 with flags 0 is accepted by the original predicate;
state 3 with flags 2 is rejected. Six additional checks preserve the scene,
broken-card and write-protection guards. These are focused handler tests,
not a UI or console integration test.

Local tools: /tmp/sdselection-dol-audit.py and
/tmp/sdselection-event-test.cpp (executable without .cpp).
No original binary or disassembly is committed.

GATE: raw-DOL/relocation destination agreement, exact corrected function,
complete-report and other-function preservation, pool/literals/data,
focused event tests, full 43U build and DOL checks pass.
