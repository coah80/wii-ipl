# Secondary component matcher workspace formal, 2026-10-02

Parent: bfcc8a44. Scope extension to zi8match.c was coordinated before editing.
Changed source: the Zi8SecMatchComp definition's parameter list only.
This is an interface correction with no percentage or code-generation gain.

## All-caller and callee evidence

A source-wide search finds one caller, in zi8InternalGetZH, and its explicit
four-argument declaration. A scan of every extracted43U object's relocation
tables likewise finds exactly one text reference, in zi8cgetc.o. The only
other direct symbol reference is the function's own extabindex entry.
No function-pointer data reference or second callsite was found.

The target caller at zi8InternalGetZH+0x8380 supplies the component cursor,
match object, dictionary base and workspace in argument registers3..6.
The workspace is the same saved incoming pointer used by the surrounding
engine helpers. This agrees with the reconstructed caller and its declaration.

The target callee is68 instructions /0x110 bytes and does not consume the
incoming fourth argument. Every path that reads register6 first defines a
new temporary there; no incoming workspace load or use is present. The
missing fourth formal is therefore an unused workspace parameter, consistent
with neighboring component matchers' ZI_NEED_WORK convention. Removing the
caller argument would contradict the target call sequence.

Added ZI_NEED_WORK to the existing definition, preserving its first three
formals and entire body. No local or storage was added, no value was made
volatile, and no register/spill was forced. The existing shared macro simply
expands to the same ziPtr workspace formal already declared by the caller.
No shared header or caller change was needed.

## Validation

Before-object: /tmp/ezi-chinese-reconstruction/zi8match-before-work-formal.o.
Fresh full report: /tmp/ezi-component-contract-full-report.json.
Build log: /tmp/ezi-component-contract-full-build.log.
Detailed checks: /tmp/ezi-component-contract-verification.txt.

All owned emitted sections have identical lengths, payloads and normalized
relocations: .text8256, .rodata528, extab80, extabindex120. The compiler
comment section is also unchanged. Symbol entries, relocation records and
section extents are unchanged; only compiler-generated anonymous extab names
in .strtab advance numerically after the additional formal. The entire object
file is therefore not byte-identical, but its emitted code/data and relocation
meaning are identical. No symbol-metadata edits were made to hide this.

All1027 full-report unit measures are unchanged. zi8match remains8/10 exact,
5172/8256 exact code,728/728 exact data and99.53004% unit fuzzy. All eight
baseline exact functions have ctxdiff diffs0 and identical instruction counts;
Zi8SecMatchComp remains68/68 instructions,0x110 bytes and exact100%.

Pool first: identical and empty. Full43U build passes with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No remote, linking, shared-header, assembly, metadata,
artificial storage or undefined-value change.
