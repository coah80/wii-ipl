# opus-odh attempts (src/system/odh)

Worktree data-d6, branch agent/w1009/o-odh from origin/main 72e9c8d6. Read opus-common.md, sol-r4 and
sol-m2 logs, effort-policy entries, levers.md, the mwdbg README and the allocator reference.

Baseline: LineConv11 12/146, huffmanDecoder 171/306, unit 26/28 exact, pool identical.

## combosweep (run first)

- main source: LineConv11 12 -> 12, huffmanDecoder 171 -> 166 (opt_propagation off). No exact.
- sol-m2 seed: LineConv11 6 -> 6, huffmanDecoder 114 -> 114. No exact.

## LineConv11: EXACT

mwdbg capture of the seed: inside the loop r8 is the only free volatile GPR, so every other temp takes a
saved register and the lowest claimed one wins. The packed RGB565 word (v68) was colored before the
high byte (v66) and took r8. The target needs the high byte on r8, the pointer on r29, and the packed word
colored after cbValue claims r25. So the packed word has to be a named local numbered below cbValue.

Petari's matching SMG source (SMGCommunity/Petari src/Game/Screen/odh.cpp, read-only) does exactly that:
cbValue/crValue are declared with red/green/blue before the format chain, and `pixel` is built high byte
first (`pixel = src[o]; pixel <<= 8; pixel |= src[o + 1];`) inside the RGB565 block. Ported as-is with
this file's names: LineConv11 0/146, ctxdiff diffs 0, pool identical, no other function changes.

Lever isolation (each from the exact version):
- cbValue/crValue declared at their assignment instead: 5 diffs.
- pixel low byte first (`pixel = src[o + 1]; pixel |= src[o] << 8`): 6 diffs.
- pixel as one expression `(src[o] << 8) | src[o + 1]`: 6 diffs.
- planeSize indexing instead of cbSource/crSource pointers: 0 (either form works).

## huffmanDecoder: EXACT

Started from a fresh natural rewrite (early returns, `length`/`tableIndex`/`category` names, Petari-style
tree walks) instead of the Ghidra-shaped seed: 170 diffs, same 306 instructions. Structural fixes first:
- `coefficient = 1` before the first refill loop (the target sets it in the DC block): 163.
- DC leaf through a named `leafIndex` (target keeps `(idx + off + 1) * 2` + lhzx only in the DC walk).
- `length = 1;` before `tableIndex = 0;` in every walk (li order): 139, 0 structural left.

Then allocator work with mwdbg + a per-vreg want list built by aligning backend-04 PCode with the target
object (/tmp/opus-odh-want.py), and an annealer over the numbering (/tmp/opus-odh-anneal.py):
- A full renumbering (temps included) reached 1 miss and showed both maxLength values must be colored
  after their walk temps, i.e. behave as codegen temps. `maxLength = component == 0 ? 9 : 11;` gets
  copy-propagated into the ternary temp: 139 -> 80.
- `dc` must be colored before the predictor-index temp, so no named `dc`:
  `coefficientOutput[0] = value + *pred; *pred = coefficientOutput[0];` (store forwarded, no reload): 68.
- AC tail: target creates the store address before `length + category`:
  `coefficientOutput[coefficient++] = value; bitOffset += length + category;`: 66.
- Remaining misses were named-local order only. Simulator: declare sourceCursor, bitOffset, coefficient,
  category before bytesConsumed (sourceCursor colors first and takes r12, bitOffset claims r31, then
  coefficient r30, category r29, bytesConsumed r28). C89 declarations at the top of the function: 9.
- Last 9: the run walk needs `branch` numbered above `node` (declared first). Per-walk C89 blocks
  `u32 branch; u16 node;` then assignments: 0. Only the run walk needs it; using it in all three walks
  is also exact, so the final source is uniform.

Checked and rejected along the way: function-scope shared node/branch (always 9, any position);
`value += *pred` (80); chained assignment for the predictor works (68) but the two-statement form reads
better. maxLength/value/mask/leafIndex/run/i can sit anywhere in the top declaration list.

Final: huffmanDecoder 0/306, ctxdiff diffs 0, pool identical, unit 28/28, code 14684/14684, data 6360/6360.

## Link

Flipped system/odh.cpp to Matching. ODHEncodeRGBA8/ODHEncodeY8U8V8/ODHDecodeY8U8V8 are in the source but
not in the split target (unreferenced, dead-stripped); the link output is unchanged.
Full build: main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, "system/odh.cpp: linked True".

Gate (`gate.py src/system/odh --quick`): GATE PASS, 28/28 instruction-exact, linked code 14684,
0 regressions, 0 forbidden patterns, 0 readability warnings. Global matched code 98.14728 -> 98.20765.
