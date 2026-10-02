# linkgap leaf — iplChannelTitle + eggAudioExpMgr

Owner PR #815 review directives:
1. CT: restore weak vtable emission (orig .o emits them; they lose link-dedup
   so the DOL tail is zeros), while matched_data stays 3144.
2. audio: delete invented `class Sample`; fix [dtor][calc] thunk order via
   real decl order or leave Equivalent documented.
3. Split into two leaf branches off origin/main.

## iplChannelTitle — emission restored, 3144 is provably impossible

Orig .o `.data` = 0x950; last symbol ends 0x87c; bytes 0x87c-0x950 are zeros
in both the extraction .o and the DOL (verified at DOL file off 0x31F504).
The 0xd4 tail = 5 weak-emitted vtables that lost link dedup:

| off   | size | symbol                        |
|-------|------|-------------------------------|
| 0x87c | 92   | __vt__ipl::gui::PaneManager   |
| 0x8d8 | 24   | __vt__gui::EventHandler       |
| 0x8f0 | 32   | __vt__gui::Interface          |
| 0x910 | 32   | __vt__ipl::nand::LayoutFile   |
| 0x930 | 32   | __vt__ipl::nand::LangFile     |

Emit rule used (old agent/w0929/linkgap scheme): a class weak-emits its
vtable in a TU that ODR-uses it (construction site; elided vptr stores
count) when every virtual DECLARED IN THAT CLASS is inline — inherited
non-inline virtuals don't block (LayoutFile emits despite non-inline
inherited virtuals because its own ~LayoutFile is inline here).

Source mechanism, all real decls, no invented names:
- `#define IPL_CHANNEL_TITLE_NOVTABLE` at cpp top (undef after includes).
- GUIManager.h: ~Interface -> `~Interface(){}` for CT (gate); EventHandler
  loses `__declspec(novtable)` for CT.
- iplGuiManager.h: ~PaneManager -> `~PaneManager(){}` for CT.
- iplNand.h: LangFile's five virtuals gated to inline dummies for CT;
  ~LayoutFile -> `~LayoutFile(){}` for CT.
- `#pragma dont_instantiate ipl::math::HermiteIntp<float>` keeps
  HermiteIntp's vtable UND (orig also UNDs it).

Result: all 5 emit STB_WEAK at the exact orig offsets, .data=0x950, the
raw .data bytes are byte-identical to orig's (all-zero tail), and the
full DOL is byte-identical (sha1 26116613f624061ba99c8d1a299aaa6efa85670d)
with the unit flipped Matching.

### Why matched_data cannot stay 3144 — objdiff internals, proven

`matched_data` sums sizes of sections at fuzzy==100. `.data` fuzzy is
computed (objdiff-core diff/data.rs `diff_data_section`) as:

- left_max/right_max = max end offset of scored symbols in the section
  (symbols with size>0, not Section-kind, not Hidden).
- Compare section bytes over 0..max (patience diff) AND pair relocations
  in the same range; if every left reloc matches, score =
  max(symbol-name-match%, byte-diff%). Otherwise symbol-name-match only.
- Symbol-name-match = sum(size*match%)/sum(size) over left symbols.

Any symbol'd object emitted at 0x87c+ therefore scores <100 regardless
of content, because orig's extraction .o has neither a symbol nor a
reloc there (dedup'd weak emits are invisible in the DOL, so the
extractor dropped them — rela.data max offset is 0x878). Measured:

- 0 emits (.data=0x87c): .data fuzzy 100.0 -> matched_data 3144
- 5 emits (.data=0x950):  .data fuzzy 95.35 -> matched_data 760

The only objdiff-invisible emit is a Hidden symbol (objdiff marks
ELF Linkage-scope/STB_LOCAL symbols Hidden). But a local emit cannot
lose dedup, so its content (vtable pointers) would be written into the
DOL -> nonzero tail -> hash fails. A local *zero-content* object would
satisfy both, but that is an invented score-only pad (owner rule 3) —
vetoed, not used.

CONCLUSION: `.data` extent 0x950 (required for the link; flipped units
must place the next unit's .data at 0x8164F0B8) and matched_data 3144
are mutually exclusive — the drop is an extraction-model artifact, not
a fidelity regression. Emitted-vs-orig emit set matches orig's real
mechanism (weak defs that dedup away); the linked DOL is byte-identical
either way.

## eggAudioExpMgr — see linkgap-audio branch notes

(Sample class deleted; secondary-vt [dtor][calc] thunk-order handled on
agent/w1005/linkgap-audio.)
