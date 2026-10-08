
## drawTransferTitles (w1011/fossils) — three-Color-copy structure fully decoded
Orig emits THREE nw4r::ut::Color copies per setTitleRowColors call site, not two:
active branch: read GXColor@0x3c once (lbz x4 into r8/r7/r6/r0), byte-memberwise
stb x4 to THREE dests: 0xc (DEAD - never read again), 0x24 (arg1), 0x20 (arg2).
inactive branch: source 0x38 -> dests 0x8 (dead), 0x1c (arg1), 0x18 (arg2).
So orig keeps one dead Color copy per call; MWCC always eliminates ours.
Byte-memberwise copies = implicit Color copy ctor (u8 fields), source read
through reinterpret_cast<const Color*> (opaque alias -> lbz not lwz).
Forms tried to keep the third copy alive - ALL eliminated or word-folded:
- named `Color active0 = *re` (leaf-start form): dead-eliminated -> 2 copies.
- `Color(active0)` temps: active0 stored (copy source) but temps word-fold
  (lwz+stw) -> wrong shape AND fewer byte ops.
- `setTitleRowColors(tb, active0, active0)` by-value params: callee ABI adds
  caller-side copies but they word-fold (Color is 4B -> memcpy fold).
- `const Color& r = Color(*re)` ref-bound temp: still eliminated.
- `const` decl: no effect.
Unresolved: what makes orig's third copy non-eliminable. Suspects: a ctor
form MWCC treats as non-trivial-init, an address escape we haven't tried, or
the copy being emitted through a different expression class entirely.
## create (w1011) — reconfirmed 1064v1064 pure tie
3-web callee-pin rotation (litbase->r31, singleton-base->r26, obj->r30 vs
r30/r31/r26) - allocator-internal, matches prior documentation.

## iplMemoryCardManager _create_icon (w1011) — remat-vs-pin reconfirmed
100v100, 37 diffs, all association/coloring: m19-24 address reassociation
(`add r0,r31,r3; add r29,r30,r0; add r3,r29,r28` vs orig
`add r0,r3,r29; add r31,r0,r30; add r3,r31,r28`) and callee-web pin rotation
r29/r30/r31 + r24-r28. Rematerialization order of the *0x1fc0 / *6 / *0x15c
products is allocator-internal - no source lever found in prior or this wave.
