# BS2Tick loader-output capture, 2026-10-03

Base: `93e97b7ff12fb7866bf5de6baa57a0c65e349304`, including #1077.
One source trial in `src/BS2/BS2Mach.c`; no declaration search.

The original BS2Tick at `0x8137D3B8` loads the loader address at +0x14AC,
length at +0x14B0 and offset at +0x14B4 after BS2ReadDiskID returns. It then
stores LoaderLength at +0x14B8, LoaderAddress at +0x14C0 and LoaderOffset at
+0x14C4. Capture the address in a real `u32 readAddress` local, then preserve
that publication order. The full-width field, local and destination are all
32-bit unsigned values. Assignment immediately precedes its only use; no
path reads an uninitialized value and its address never escapes.

The capture remains after the helper call. Original BS2ReadDiskID consumes
r3/r4/r5 as buffer/length/offset, so retaining a pre-call output value would
not be justified. Original caller and entire callee relocations/words were
checked against the linked DOL. The change does not alter calls or qualifiers.

Historical lead: `big1.attempts.md:540` recorded this capture at 99.03144%
to 99.03918% within an older compound. Line 465's earlier publication
inversion is excluded because target load order and store order differ.
Partition-entry, title-family and banner-alignment changes from that compound
are already incorporated; the compound's 99.106186% is not this edit's score.

| Measure | Baseline | Candidate |
| --- | ---: | ---: |
| BS2Tick fuzzy | 98.73196% | 98.74072% |
| Unit fuzzy | 99.138985% | 99.14299% |
| Instructions / target | 1937 / 1940 | 1937 / 1940 |
| Exact functions | 25 / 29 | 25 / 29 |
| Matched code | 5112 / 16980 | 5112 / 16980 |
| Matched data | 155504 / 158528 | 155504 / 158528 |

Only five instructions change, all now matching the corresponding original
operands: source offsets +0x14A0, +0x14A4, +0x14AC, +0x14B4 and +0x14DC.
The last is the dependent transfer-length store. All other text and allocated
nontext bytes are identical. All 1461 relocation positions, types, target
addresses and addends are identical; 15 compiler-generated anonymous local
labels referenced by 39 relocations are renumbered. All 201 direct call sites
are unchanged, and all original call destinations agree with raw DOL addresses.

Validation: 16250 executions of actual baseline/candidate/original publication
instructions cover all 17 slice instructions and branch outcomes, 32-bit
boundaries, deterministic arbitrary post-call outputs and IRQ values. Final
state agrees in all three; candidate field-read/publication traces match
the original. A stale pre-call address mutation is detected. This is a
bounded instruction model, not a complete Wii runtime or exhaustive 32-bit
Cartesian-product test. Every baseline exact function remains instruction-exact;
all other 1026 unit reports are unchanged.

Full 43U all_source/report/ok, 91-string pool, literal audit (97 arguments,
28 functions; unchanged BS2Tick unequal-extent skip), and diff-check pass.
DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
No assembly, linking, metadata or shared-header change.

Private workspace evidence: `validation/bs2-compound-recovery-20261003/`
contains `loader_check.py`, `loader-check.json`, `raw-audit.json` and the
read-only historical classification. Baseline/candidate objects, reports and
build/audit logs are retained in `/tmp/bs2-loader-lifetime/`. No original
binary or assembly is committed.
