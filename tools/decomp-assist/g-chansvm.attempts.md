# g-chansvm CHANSVmStep

Base 54ca052b, branch agent/w1009/g-chansvm, worktree data-d2.
Baseline CHANSVmStep 5012 bytes, odiff 262/1253 differing, objdiff 97.23%.
Pool identical, 125 entries. Unit has one non-exact function.

Recovered o2 structural findings from /tmp/o2-chansvm/sstr1.c, preserving current
const-correct conversion signatures and exact helper implementations.
Split five result matrices and five constant objects, replace cross-object
base indexing, restore loop/stack object/case-local structure.

Recovered build: odiff 299/1253, equal 5012-byte size, register-masked diffs 6
from scheduling at 511, 598, 836. All 232 other functions exact; pool identical.
Early single/pair pragma sweep: best 299, no improvement.

Allocator capture CHANSVmStep-20261009-082339 reproduces 478/478 GPRs.
Centralizing and uniquely naming scalar locals preserves 299/1253 exactly.
C++ replay of regsim searched 100000 declaration permutations, seed 11,
35 -> 5 saved-register mismatches. Compiled source 299 -> 44 differing.
Target enum traversal starts with the left operand; correcting it gives 42.
Explicit load/ref object pointers restore CopyObject argument scheduling,
42 -> 38, 5012 bytes; one 2-instruction scheduling tie remains.

Trials on declaration-order source: u16/s16 arraySize, separate byte
assignments, widened shift/add forms change instruction count and were rejected.
s32/u64/s64 index, split byte temporaries, simple read helpers and property
operand/object locals preserve codegen. Separate property index gives 46.
Property status/flag assignment order and inline array helper preserve 38.

String load: direct pVm->pActiveCtx accesses eliminate the ctx/index swap,
38 -> 29. A distinct decoded propertyOffset separates it from the absolute
program counter and allows in-place masking, 29 -> 26. Remaining 26:
GET_PROPERTY_NAME operand/object/index register cycle (12), NEW_ARRAY
accumulator/size register swap (12), status/flag scheduling (2).
Whole Step inline helper: equal size but 321 differences, rejected.
Lookup/read/array helper wrappers: unchanged. Scoped property variables:
unchanged or worse. Signed/widened array size: unchanged or extra instructions.
Earlier array accumulator lifetime: 36 differences, 14 masked, rejected.
Scoped opt_lifetimes off: equal size, 44 differences, same 2 masked ties;
other tested optimizer/scheduling pragmas worsen instruction structure.

Lifetime trials: off + separate propertyIndex scores 25, equal size and two
masked scheduling differences. Captures 085030 and 090247 replay exactly
(458/458 and 459/459), but each has two GPR passes. Final-pass-only
declaration search finds two simulated misses (array accumulator/size),
yet compiling its full permutation changes the first-pass rematerialization
choices and scores 123. Treat the final-pass graph as insufficient here;
freeze high-degree loop values when searching. Default pragma source at 26
remains the retained candidate until a full compiler replay improves it.
Intrinsic rlwimi forms, array helpers under lifetime-off, output-argument
lookup/decode, property symbol locals, and flag output pointers preserve
codegen. Direct array header accesses lose one instruction; early/success-only
accumulator pointers alter scheduling and were rejected.

Freezing degree >= 100 locals preserves the first-pass spill/rematerialization
choices. Final-pass search seed 62 (100000 permutations) improves 25 -> 14
in the full compiler, with all other 232 functions still exact. Retain the
function-scoped opt_lifetimes off setting and this declaration order.
Use a shared u64 maxIndex = 0xFFFFFFFEULL for the three integer bounds instead
of repeated split high/low temporaries; this preserves the 14-diff output.
Remove obsolete instruction union, unused ctx and comma expressions.

Sharing the accumulator pointer between BIT_NOT and NEW_ARRAY gives 14 -> 2.
The shared value's interference graph now selects r14 for the array pointer
and r17 for the decoded array size, as in the target. Sharing it with the
LOAD_STRING_CONST pointer independently reaches the same 2 differences;
other accumulator and size-local merges fail to improve or regress.

Latest capture: CHANSVmStep-20261009-093935 in
/mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/.
Reduced source build/g-chansvm/twoflagfirst.c reproduces the full function.
Regsim reproduces all 458/458 virtual registers. This variant writes status
before the flag in C; backend-00-initial-code B261 has li before stw, but
backend-01-before-regalloc already moves stw ahead of li. Reversing the two
C assignments does not change the final object.

Remaining exact ctxdiff, 5012 bytes and 1253/1253 instructions:
836 source stw r26,0xc(r1); target li r14,0
837 source li r14,0; target stw r26,0xc(r1)
All registers and all other instructions, including relocations, agree.

Final tie trials, all rejected: status/flag assignment order; negative
property guards; status locals and merged error temporaries; status assigned
from DeleteObject; status hoisted ahead of the switch or set in each arm;
separate property flag; address-based flag access; flag integer widths and
boolean normalization; const/static-const status values; inline flag setter
and full property-enumeration helper. Moving result or foundEntry through
every scalar declaration position never fixes the scheduling pair.
A complete single/pair pragma sweep on the 2-diff source retains 2 as best;
explicit scheduling/peephole on also retains 2. Numeric scheduling pragmas
are rejected by MWCC. GC/3.0a5 and every available 3.0a3 variant also retain
2; 2.7/2.6 reject the unit's ipa option. No compiler-version change retained.

Fresh final unit report: CHANSVmStep 97.23 -> 99.840385 percent; odiff and
relocation-aware ctxdiff 262 -> 2. Exactly 232/233 functions, unchanged.
Data 6904/6904 (100 percent), pool identical across 125 strings.
Matching flip is withheld because CHANSVmStep is not exact.

Final gate command:
python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/channelScript/CHANSVm --quick
GATE PASS: full 43U build, 0 regressions, 0 forbidden patterns, 0 readability
warnings, identical pool, all five data sections 100 percent.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
Unit remains NonMatching and linked code remains 0; the verified DOL still
uses the original CHANSVm object. This is an improvement, not an exact handoff.
The pragma's address/lifetime effects are documented in captures 085030,
090247 and 093935: ref/load/index frame slots and address recomputation stay
at the target locations, while high-degree roots must remain fixed to avoid
changing the first-pass rematerialization choice.
