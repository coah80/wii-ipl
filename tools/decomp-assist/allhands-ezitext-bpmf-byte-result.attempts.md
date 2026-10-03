# Bpmf consumed-count return contract, 2026-10-03

Base: 029dd7ea on the Chinese source-reconstruction leaf. Previous candidates
are unchanged. Owned source: zi8match.c / Zi8GetBpmfPhonetic only.
This is type-correctness reconstruction with zero percentage gain.

## Evidence and change

All three source callers declare Zi8GetBpmfPhonetic as returning ziU8:
zi81key.c, zi8space.c and zprepare.c. The definition instead returned ziS32
and used a ziU32 resultCount. Its result is the consumed Bopomofo character
count: the four sequential initial/medial/final/tone stages can increment it
at most four times, and all failure paths return zero. There is no negative
result or full-word quantity to communicate.

Changing only the return type to ziU8 introduced return narrowing and made
the previously exact function nonexact (98.64078%, exact count8 ->7). That
isolated trial was rejected. Recovering the counter's own byte type along
with the byte return restored the entire309-instruction exact function.
The retained two-line change therefore aligns all caller declarations and
the bounded consumed-count representation without explicit casts or masks.
No caller, shared header, parameter or control flow is changed.

## Other remaining-helper inspection

A fresh Zi8GetPyPhonetic audit found718/718 instructions. One fixed bijection
among its six differing callee-saved registers makes every instruction,
branch destination, call and relocation identical. It remains nonexact;
the register map is diagnostic only and was not encoded in source.

Zi8GetPyFinal remains53/53 instructions with eight differences in two table
row-address calculations. Each computes the same table +8*row address into
the same result register, uses identical byte-column offsets4 and5, and has
no live-out dependence on the differing temporary. No type/access/flow defect
was found in either nonexact helper, and no allocation sweep was performed.

## Validation

Baseline object: /tmp/ezi-pinyin-contract/baseline.o.
Fresh full report: /tmp/ezi-bpmf-byte-full-report.json.
Full build: /tmp/ezi-bpmf-byte-full-build.log.
Detailed checks: /tmp/ezi-bpmf-byte-verification.txt.

All1027 full-report unit measures are unchanged. zi8match remains99.53004%
fuzzy,8/10 exact functions,5172/8256 exact code and728/728 exact data.
All emitted .text/.rodata/extab/extabindex lengths, payload bytes and canonical
relocations are baseline-identical. No new exact function or percentage gain
is claimed. Each of the eight existing exact functions has ctxdiff diffs0
and identical instruction counts; Zi8GetBpmfPhonetic remains309/309.

Pool first: identical and empty. Full43U build passes with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No remote, linking, shared-header, metadata, assembly,
volatile, artificial storage, forced-register or undefined-value change.
