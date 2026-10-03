# Chinese Zhuyin initial dispatch correction, 2026-10-02

Parent: 1b1a944a on base 654c65dd. The pointer-contract candidate is unchanged.
Changed source: two case-label lines in zi8cgetc.c / zi8InternalGetZH.
This is a demonstrated behavioral correction; aggregate metrics are neutral.

## Discovery

A complete fresh flow audit checked the compiler-generated switch tables as
well as direct branches. All 1594 mapped direct branches and all 168 ordered
helper calls agreed before this change. However, four of the 98 generated
switch relocation entries dispatched to the wrong semantic bodies. A direct
branch-only audit cannot see that defect, and the linear effect audit compares
both bodies without knowing which switch cases reach them.

The relevant switch uses the phonetic initial (match.phon2[index] >> 9),
subtracts case 24 for its 40-entry table and rejects indexes greater than39.
The table starts at .data+0x58. Its four incorrect entries were:

- .data+0xC8, case52: source selected bANDp; target selects gANDk
- .data+0xD4, case55: source selected bANDp; target selects gANDk
- .data+0xE8, case60: source selected gANDk; target selects bANDp
- .data+0xF4, case63: source selected gANDk; target selects bANDp

The bodies are identified by their actual tests of the workspace word at
0x1B2C: bANDp tests the bit at MSB-relative position10, while gANDk tests
position11. Both successful bodies store the same phonetic mask0xF9FF, but
they consult independent user fuzzy-pair settings. Crossing the labels
therefore changes behavior, even though both body instruction shapes match.
Target cases52/55 enter function+0x1288 (position11), while60/63 enter+0x1264
(position10). Current compiled bodies are four bytes later, and the corrected
entries now select their corresponding semantic bodies.

The fix swaps only the two case-label pairs, preserving body/source order,
header layout, tests, masks, all other cases and function size. It does not
change shared bitfield names to compensate for the bad dispatch.

## Verification

Fresh report: /tmp/ezi-chinese-switch-full-report.json.
Full build: /tmp/ezi-chinese-switch-full-build.log.
Detailed gates: /tmp/ezi-chinese-switch-verification.txt.
Switch/direct-flow audit: /tmp/ezi-chinese-switch-flow-audit.txt.

After correction, all 98 switch entries have corresponding target semantic
destinations, with zero destination mismatches. The four table extents remain
44,44,160,144 bytes. The 1594 mapped direct branches and168 ordered helper
calls also still agree. This is an advisory relocation/control-flow check,
not formal whole-program equivalence or a claim of exact assembly.

Every code/data section size and payload is baseline-identical. All normalized
relocations are unchanged except exactly the four corrected .data entries.
The .text section, extab and extabindex are unchanged byte-for-byte. The
engine stays10676/10676 instructions with the same0x4E0 frame.

All1027 unit measures are unchanged with no regressions. Unit fuzzy remains
96.65468%; engine fuzzy96.27482%. Exact functions5/8, code4168/47816 and
matched data144/536 are preserved. The switch section remains unmatched
because case body addresses still differ from the target; no percentage or
new exact function is claimed.

All five previously exact functions still have ctxdiff diffs0 and identical
instruction counts. Pool first: identical and empty. Full43U build passes
with the approved wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No shared header, metadata, link flag, assembly,
volatile, register/storage workaround, or remote action was changed.
