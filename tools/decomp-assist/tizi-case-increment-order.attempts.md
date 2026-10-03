# tiZiString case-loop increment order

Base: `da41bad9527780fbb8b2c697b894bcadcd7f2a1a`, 43U only.
Leaf: `agent/bittle/tizi-case-increment-order`.
Owned source: `src/keyboard/tiZiString.cpp`, `WithZi::update`, exactly one
natural comma-expression trial in the existing case-conversion loop.
Current declarations, initializers, scopes, switch and helper calls stay fixed.

## Target evidence and finite coverage

After the accepted case-local declaration pair, current `.text` 0x1144/0x1148
increments position then candidate (`addi r24,r24,1; addi r25,r25,2`). Target
0x1130/0x1134 increments candidate then position. These two instructions have
disjoint GPR read/write sets and no memory, branch or condition-register effect.
The character load follows both increments in each version.

Reviewed the unit's tiZiString, structural-matching, fz7 and ult15 attempt
coverage and all-history source searches for both comma-expression orders.
No prior `++candidate, ++position` trial was found. Earlier declaration trials
did not move either increment and were not repeated.

Authorized single source form: replace the for increment `++candidate` with
`++candidate, ++position`, then remove the trailing body `++position;`.
No normalization, alternative expression, source adjustment, or adaptive trial.

| Version | update fuzzy | Compiled / target bytes |
| --- | ---: | ---: |
| Fresh baseline | 97.40807% | 1792 / 1784 |
| Single comma-increment candidate | 97.4574% | 1792 / 1784 |

Only tiZiString.o changes among all 1027 source objects. The candidate is
retained for independent review; no exact-function or linking gain is claimed.

## Source semantics and limits

Built-in comma explicitly sequences candidate increment before position
increment. Both locals remain in their existing lifetimes; no constructor,
volatile access, address escape, assignment, pointer dereference, or helper
call is introduced or moved across a memory access. Helpers still receive
character values. The loop body has no continue, loop break, return, or goto;
its break statements leave only the switch. Thus each completed iteration
performs each increment once before the next condition test.

The local scalar increments are independent. On defined C++ executions,
candidate accesses remain within `CandidatedWord[0xA00]`; starting position at
zero cannot approach signed overflow while those array accesses remain valid.
The same pointer validity and one-past requirements apply in both versions.
This is not a global bounds or termination proof: `count` is refreshed after
its earlier clamp, so the clamp does not establish safety for all inputs.
Malformed/out-of-bounds executions are not made safe or claimed defined.
No guards, terminators or read-error behavior changes were introduced.

## Executable instruction and continuation proof

Evidence directory:
`/workspace/shared/tizi-case-increment-da41bad9/`.
Run from a configured leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python \
  /workspace/shared/tizi-case-increment-da41bad9/check_increment_evidence.py \
  --repo . --candidate build/43U/src/src/keyboard/tiZiString.o
PYTHONPATH=../local-tools ../.venv/bin/python \
  /workspace/shared/tizi-case-increment-da41bad9/test_increment_evidence.py
```

Checker SHA256:
`16c5d12d7d01879f95efdb82a373b9acf8db09cb637aee77c765434726c6212d`.
The unchanged companion parser/checking support, `case_pair_support.py`, has
SHA256 `d8c041e106f6ccda1c75ed6e80404aac33a9204a910e835330a4a1e954954f27`.

Exactly two instruction words change, 0x1144/0x1148. They are an exact swap
and equal the original target pair. The checker inspects actual operands,
proves disjoint register effects, and symbolically executes both orders as
32-bit additions. All 32 GPRs are equal at 0x114C. Opcode-14 addi changes no
CR, XER, LR, CTR or memory; the common exit PC is also equal. There is no
alternate ordinary CFG entry to the second instruction. All other update
words, CFG edges, ordered memory instructions and calls remain identical.
Therefore no changed register value reaches a load/store, branch, call or
return, including on later loop reentries. This does not reuse the earlier
caller-clobbered exception or allow a callee-saved difference at void return.

The actual unchanged `_savegpr_24` and `_restgpr_24` bodies and call sites are
also checked. The 0x30-byte frame saves/restores r24 at SP+0x10 and r25 at
SP+0x14. Both registers and memory already agree after each pair, before
subsequent calls or restores, so the same caller state is restored.
The proof assumes ordinary control-flow entry; forged indirect targets or
asynchronous inspection of intermediate registers are outside this
compiler-level functional-equivalence argument. It is not a general ISA
verifier or a claim that the remaining partial function matches retail.

## Exact private-label metadata exception

One nonallocated `.strtab` byte also changes: offset 210 changes the local
jump-table spelling `@1391` to `@1393`. This is not ignored generally.
The checker requires that exact one-byte/string substitution and verifies:

- `.strtab` flags are zero; all section headers are identical.
- Symbol index 11 remains the same STB_LOCAL/STT_OBJECT symbol. The entire
  symbol entry is byte-identical: section index 3 (`.data`), offset 12,
  size 48, with unchanged string-table name offset.
- The jump-table data bytes are identical. Every allocated data section,
  `.symtab`, and every relocation section is byte-identical.
- Every reference to symbol 11 remains identical: `.rela.text` offsets
  0x141A (ADDR16_HA/type 6) and 0x1422 (ADDR16_LO/type 4), both addend zero.
- No other symbol name or string-table byte changes. External bindings and
  relocation semantics are unchanged; whole non-text byte identity is not
  claimed because the private compiler label is renumbered.

Eight in-memory negative tests pass: incorrect pointer stride, incorrect
position stride, changed following memory read, second-instruction CFG entry,
extra string-table byte, local symbol becoming global, changed relocation
addend, and changed allocated jump-table data. All are rejected. Tests neither
edit nor compile source or ELF files.

## Final gates and fingerprints

- Only update changes among all 1027 report units; all 28 sibling function
  records and code bytes unchanged. Every non-fuzzy full-report field agrees.
- Unit fuzzy 98.308136% -> 98.32413%. Exact functions remain 26/29, matched
  code 3136/5504 and data 7680/7680. Linking metrics do not change.
- Fresh full default 43U build, final default build and `build/43U/ok` pass.
  DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Pool identical, zero strings. Literal audit: 27 analyzed, zero checked
  arguments/candidates/errors. update and clearCandidates are skipped for
  differing source/target sizes; this is not a full-function literal proof.
- Source diff is exactly the authorized two increment locations.
  `git diff --check` passes. Existing cached tools, explicit configure paths,
  `WIBO_SJIS_MISSING_IMPORTS=1` and workspace TMPDIR are used. Workspace remains
  above the specified 1 GiB floor; no previous evidence is deleted.

Baseline object SHA256:
`1617890835c018e253238e21f65a2629b893e2bbc2ee60fa0a4ac69cc141fbc4`.
Candidate object SHA256:
`80b0085988ec2043263cc092f7fc030c690097267f98cf93bf179e16caa3acbb`.
Candidate source SHA256:
`95953dbc9a11cd51275c108e6ee7c780887a7d72ec836b15ed3af53504ab19e4`.
Baseline full-report SHA256:
`72540252f7b164ad6fe0bb3ae63447de6d292ad85d475e60c34d135229e5882e`.
Candidate full-report SHA256:
`571c8ba5e0cb3b436a12a5d7c26c7123f4f58ced217d3033119c5a940351d3c7`.
Evidence includes the one-variant driver, preserved source/object/report
snapshots and all-object manifests, checker/self-tests, disassembly and gate
logs, `increment-machine-evidence.json` and `final-audit.json`.
Candidate frozen for parent verification. No main edit or remote action.
