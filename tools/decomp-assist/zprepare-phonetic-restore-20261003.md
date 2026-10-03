# Zi8PrepareMatch paired phonetic restoration

Base: `5d7760d341938a55e7613de85a3e1e5a3ba6bcb7`.
Leaf: `agent/bittle/prepare-phonetic-restore`.
Only `libs/RVLMiddleware/eZiText/src/clib/zprepare.c` and this log change.
The separate CHANSVm candidate and the one-key/PUD sources are untouched.

## Retained source reconstruction

On a failed Bopomofo parse ending in the separator, the previous initial and
final phonetics restore both the current and best outputs. The original loads
each previous halfword once and writes its two destinations immediately.
The source instead assigned the best outputs, then reloaded them to assign the
current outputs.

Express the two paired restores directly:

```c
bestInitial = initial = previousInitial;
bestFinal = final = previousFinal;
```

The original six instructions at `0x81485D24` through `0x81485D38` are now
byte-identical to the candidate's corresponding restore block. Those words
were checked against the original DOL, independently of relocation matching.
No new behavioral bug is claimed: this reconstructs the target's data flow.

All six variables are distinct `ziWChar` halfword locals. There is no call,
volatile access, or other intervening operation between these assignments.
The two snapshots and all existing initialization remain present. Pairing the
stores introduces no alias-dependent result or new evaluation dependency.

## Caller/callee audit

- The original Pinyin call at `0x81485B68` resolves to `0x8147DDE8`, and the
  Bopomofo call at `0x81485BEC` resolves to `0x8147E9F4`. Raw DOL branches agree
  with extracted relocations.
- Pinyin receives the request's UTF-16 input, byte count, the two halfword
  output arrays at match offsets `0x26`/`0x46`, byte completion at request
  offset `0x22`, and halfword best outputs at match offsets `0x66`/`0x68`.
- Bopomofo receives the same four distinct halfword output locals whose
  pointers and snapshots are traced in the restore block. Its count and
  consumed-count result are bytes; the caller's halfword running length is
  narrowed to a byte at the call exactly as in the target.
- No phonetic output-pointer, request-field width, or return-width correction
  is warranted. The target's unconsumed component flag stores remain omitted;
  no dummy state is introduced.
- Prior `ezi3.round2/3/4` and `fz15` logs were read. Earlier restore-order trials
  did not express the paired assignments. Prior register, helper, and dummy-flag
  investigations were not repeated.

## Separate bounded trials

| Trial | Function fuzzy | Source/target instructions | Matched data | Decision |
| --- | ---: | ---: | ---: | --- |
| Fresh baseline | 96.319145% | 939/940 | 8/68 | baseline |
| Paired restore | 96.802124% | 936/940 | 8/68 | retain |
| Joint index/phonetic-length loop increment | 96.313830% | 941/940 | 8/68 | reject |
| Both changes | 96.748940% | 937/940 | 8/68 | reject |

The retained source removes two restore reloads and one redundant move elsewhere
in the function. Its 22 ordered call identities are unchanged. Register choices
and code layout still differ elsewhere; no exact match or linking gain is claimed.

## Validation

- Fresh configured 43U baseline and final `all_source`, report, and `ok` gates
  pass with the assigned wibo wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
- Full 1,027-unit report comparison: only zprepare changes, zero per-function
  fuzzy/exact/code/data regressions. The unit still has 0/1 exact functions.
- Source-extracted baseline/candidate restore harness: 165,536 cases pass under
  UBSan, covering every previous-initial halfword plus deterministic generated
  states. All four outputs, both snapshots and adjacent guard halfwords agree
  with an independent paired-output reference. This is a focused block test,
  not a complete dictionary-engine or Wii runtime test.
- Pool before/after: identical, no strings.
- Literal advisory: no candidates/errors; its one function is skipped because
  source and target extents differ. No literal coverage is claimed from that skip.
- `git diff --check`: PASS.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Final source SHA256:
  `0df8e9d97309fe5aef8336de71b3ec7aebf549ddd024cb927fa3f93a3d3e8333`.
- Final object SHA256:
  `bdd28374efdc511ad35278dbf1b2f88f553d36f0cba901af13a3105b41281b34`.

Private local evidence: `/tmp/zprepare-contract-audit/` contains the fresh
baseline, separate trial sources/objects/reports, trials.py, test_restore.py,
focused test output, raw-address audit, pool/literal results and build logs.
No original binary/disassembly, header change, metadata, linking flags, assembly,
volatile forcing, register search, dummy storage or other-region build is included.

GATE: validated partial source-data-flow gain; frozen for independent review.
