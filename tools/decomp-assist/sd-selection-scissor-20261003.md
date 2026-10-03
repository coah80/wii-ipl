# SD channel scissor reconstruction, 2026-10-03

Baseline b9407106. Read AGENTS and the prior SD selection, fz16, scene4,
data-d5, and structural-round attempt records. Only the owned SD selection
source and this evidence file change; no header or linking changes.

## Retained expression reconstruction

- Express each orthographic bound directly from position and the projection
  quotient, rather than keeping four extra quotient temporaries.
- Keep the input projection width distinct from the output scissor width.
- Calculate transformed X before Y and use the width quotient directly,
  removing the one-use widthScale temporary.

These ordinary expressions also occur in the sibling ChannelSelect routine.
The arithmetic grouping is preserved. The original framebuffer conversion,
projection and transformed-bound sequence is recovered; no register sweep or
allocation directive was used.

setChannelScissor: 93.4721% -> 99.14163% with separated projection width and
X/Y calculations, then -> 99.5279% with direct orthographic bounds.
233/233 instructions throughout. Fifteen register substitutions remain,
primarily exchanging the X and width values. Unit fuzzy:
99.582596% -> 99.749435%. Exact code stays 29412/33828, functions 122/129,
and data 2960/2960. All other functions and all other units are unchanged.

collectTitlesBySpecialChannels remains unchanged. The 361/361-instruction
comparison has four repeated count-store/threshold-load schedules, 16 total
instruction differences. Lookup arguments, special-title constants, reverse
NAND and cache traversal, 42-byte names, 64-bit title writes, usage additions,
and threshold exits agree. No new qualifier or forced alias barrier was used.

## Verification

- Configured 43U with ../toolchain/wibo-build/wibo
- Full all_source/report/ok build passes
- Pool identical, 101/101 strings
- Literal audit: 73 arguments in 122 reported-exact functions, no skips/errors
- Every reported-exact function is instruction/relocation-identical to the
  baseline; 117 also have zero ctxdiff against the original
- Five preexisting reported-exact functions have relocation differences:
  constructor and createBaseLayout vtable offsets/binding, draw and
  getChannelPanePosition VEC3 constructor family, and four onEvent predicate
  calls. The predicate calls test different fields and were reported to the
  parent immediately for a separate correction; no claim that all 122
  functions are semantically exact is made
- Every allocated non-code section is byte-identical to the baseline
- Complete report comparison: only setChannelScissor improves; no regression
- DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

The native C++ harness uses the extracted before/after function bodies with
local matrix/render-mode shims and captured GX calls. With floating-point
contraction disabled and UBSan/float-cast checks enabled, 250000 finite cases
pass, including all three transformed states, ordinary states, framebuffer
boundaries up to the existing 1705 clip cap, and 219852 fully clipped cases.
All orthographic bounds are bit-identical and all four GX arguments agree.
This checks the local equations and clipping, not the Wii rendering pipeline.
An initial out-of-domain test with 65535-wide framebuffers reproduced an
existing negative-to-unsigned clipping conversion; that domain is excluded
from the equivalence test, not changed in production.

Local harness: /tmp/sdselection-scissor-test.cpp, executable without .cpp.
GATE: full build, DOL, pool, literal, data/exact preservation, report
nonregression and focused numeric tests pass. Known preexisting relocation
false positives are recorded above and require separate review.
