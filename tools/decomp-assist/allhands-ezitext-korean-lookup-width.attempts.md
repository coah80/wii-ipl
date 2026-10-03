# Korean lookup halfword contract, 2026-10-03

Parent: dea3851e; its empty-context correction is unchanged.
Owned source: zkokeyp.c / Zi8_8148302C and its two local callers.

## Recovered type boundary

The lookup traverses a table whose count is ziU16, comparing and addressing
records through a halfword index, and returns either that index or0xFFFF.
For countN<=65535, successful indexes are0..N-1. The loop exits atN; a
halfword index cannot wrap on any traversed iteration. There is no need for
a full-word index or return value in this contract.

Both callers store the result into the halfword search.keyIndex. The target
stores the returned register directly through the halfword store. The first
caller then narrows for its assignment-value comparison, while the second
reloads the halfword for comparison. The current full-word declaration made
MWCC emit an additional narrowing before both stores.

Recovered the helper's ziU16 return and ziU16 loop index together, then used
the typed index directly in the loop condition and nine-byte address
expressions. The old explicit masks were the reconstruction of those same
halfword promotions while the local had the wrong full-word type. They are
not stripped from a full-word value or replaced by register constraints.

The resulting helper body is byte-for-byte identical to its previous body,
including its59 instructions and resolved calls. This demonstrates that the
same lookup operations and return representation are preserved while its
callers recover the target halfword assignment boundary. Both source callers
are in this unit. A scan of all extracted target objects found the same two
text references and only the helper's own extabindex reference otherwise.
No shared declaration or header changes are needed.

## Separate trials

A native unsigned-int return alone and explicit caller-store casts were
codegen-neutral and were not retained. The coherent halfword index/return
pair is the sole selected candidate. No old Chinese ABI experiment or
arbitrary declaration/register sweep was repeated.

## Validation

Baseline: /tmp/ezi-korean-flow-full-report.json.
Fresh full report: /tmp/ezi-korean-lookup-full-report.json.
Full build: /tmp/ezi-korean-lookup-full-build.log.
Detailed gates: /tmp/ezi-korean-lookup-verification.txt.

Zi8GetKOcandidates: 97.97459% ->98.146484%.
Unit fuzzy: 98.65769% ->98.746155%.
Relative to initial1fa33882, unit98.65385% ->98.746155%.
Exact functions remain1/7, exact code332/5200, matched data96/180.
All1027 unit measures and all per-function fuzzy scores were checked: the
Korean unit/main-function gains are the only metric changes, with no
regressions. No new exact function or complete unit is claimed.

Every other function's disassembly is baseline-identical, including the
changed lookup helper. The existing exact packing helper remains83/83
instructions and ctxdiff diffs0. Main shrinks673 ->671 instructions versus
target669, from0xA84 to0xA7C versus target0xA74. Its0x60 frame is preserved.
The remaining normalized differences are one zero materialization and one
call-result move; no further width or flow difference is identified.

.data40 and extab56 retain identical payloads and canonical relocations.
The already-unmatched84-byte extabindex changes only its main-function size
byte at0x4F,0x84 ->0x7C; its score remains97.61904%, and exact-data accounting
is unchanged. No real data object or section extent was changed.

Pool first: identical and empty. All92 mapped main branches preserve their
corrected target destinations; all17 helper calls correspond. An associative,
register-value-aware advisory audit pairs all163 store/call/branch effects
without differences. These checks are not formal equivalence or exactness
claims. Full43U build passes with the approved wrapper and
WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No linking, remote, header, assembly, volatile,
dummy-storage, undefined-value or forced-register change.
