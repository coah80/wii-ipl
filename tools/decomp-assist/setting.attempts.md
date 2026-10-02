# setting leaf — attempt log

## Decode landed this wave

### iplSetting::draw — struct-copy emission split (91.53 → 97.69, unit 99.29 → 99.70)
`GXRenderModeObj renderMode = *System::getRenderModeObj();` emitted a memcpy-style
word-copy loop (lwzu/stwu, ~8 insns). Orig emits a memberwise copy (lhz/sth for u16
fields, lwz/stw for u32, lbz/stb for the u8 arrays — ~30 insns).
Fix: split declaration from assignment:
```
GXRenderModeObj renderMode;
renderMode = *System::getRenderModeObj();
```
Copy-INITIALIZATION of a C++ POD goes through MWCC's aggregate/memcpy path;
copy-ASSIGNMENT expands memberwise. draw now 629 vs orig 632 insns.

### AOSS_Init_old (prior session, committed this wave)
dead-but-emitted else arm (`else if (state != 0)` chained-beq form), `0 <= x`
bound form, `(u32)*ptr == 1u` cast, two switch→if/else decodes, ternary-arg Sleep.

## Walls verified (ties, not structure)

### scanAP — `subi+cntlzw` bool-materialization family (3 sites)
`if (!mpMainLayout->getAnim(i)->isPlaying())` — orig materializes the callee's
bool (`addi r0,r3,-1; cntlzw; rlwinm. r0,r0,27,5,31; bne`), mine fuses to
`cmpwi 1; beq`. Tried: bool local, named Animator* local, `== true`, `== false`,
`!= 0` on the inline's return, `AnimState`-typed and `u32`-typed mState —
MWCC folds every form to the direct compare. No out-of-line isPlaying exists on
either side. Residual also includes 2-3 insns of lwz/addi scheduling ties.

### convertRevIP (98.70)
Normalized-identical instruction stream (73=73 insns); fuzzy residual is a
word-level register binding — regname family.

### draw residual (97.69, -3 insns)
Two clusters: a `bne`/`beq+lbz+b` 3-insn branch-layout diff around the
browserWindow guard (O56-62), and an int→f32 divide/store scheduling window
(`srawi/stw/lfd/fsubs/fmr`, O275-293). The `beq '#F'` diffs in the normalized
log are normalization artifacts (branch-target immediates), not real diffs.

### AOSS/AOSSSendHelloRequest
Identical unrolled CRC x8 structure verified; residual is table-base pinning.
### ATERM Md5Update
Index-form kept (fuzzy 91.26 > pointer-walk 84.21 — fuzzy is positional).

## Owner ruling (PR #973)
Dead objects that only pad a section are forbidden; unreferenced .sbss/.data
gaps stay unowned unless a target relocation references the address.
