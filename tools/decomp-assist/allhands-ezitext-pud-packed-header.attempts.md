# PUD packed-header halfword decoding, 2026-10-03

Parent: a71dfa9c; its byte-return correction is unchanged.
Owned source: two expressions in zi8pud2.c / Zi8MatchPUDdata_ZHS.

## Recovered arithmetic and widths

The eight-byte PUD section record contains two-byte big-endian count and
offset fields. The target separately promotes each of their four component
bytes through a halfword boundary before shifting or adding. The source
previously expressed plain byte arithmetic and omitted those four target
conversions.

Restored explicit ziU16 promotions for count[0], count[1], offset[0] and
offset[1]. The offset is now decoded as one grouped big-endian value before
adding the table base. This reproduces the target's base/high/low load and
addition order, without a new local, helper, casted memory access or storage.

Bounded isolated trials, all retaining 6 exact functions and 48 exact data:
- Halfword promotions with the existing offset association:
  ZHS 98.52542%, unit 99.02247%
- Conventional grouped high/low offset sum:
  ZHS 99.717514%, unit 99.81274%; selected
- Grouped low/high offset sum:
  ZHS 99.10452%, unit 99.406364%; rejected
- Grouped multiplication form:
  ZHS 99.10452%, unit 99.406364%; rejected

All 65,536 possible packed values preserve the decoded count. Another
524,288 offset/base combinations, covering eight bases including 32-bit
wrap boundaries for every packed value, preserve the computed address.
These arithmetic tests supplement the target instruction correspondence.

## Remaining workspace snapshot

The target stores its incoming workspace pointer once into frame 0x24 at
function +0x3C. A width-aware access and address-provenance audit finds no
read, overlapping use, or address escape for that slot. The workspace stays
in its existing saved register. The only ordinary local whose address is
passed to a helper is the halfword at frame 0x0E. Save/restore addresses the
separate upper frame region. No source-visible distinct alias role was found.

That single dead store remains absent. No unused local, dummy assignment,
padding, volatile or forced spill was added to manufacture it.

## Validation

Fresh final report: /tmp/ezi-pud-packed-full-report.json.
Full build: /tmp/ezi-pud-packed-full-build.log.
Detailed gates: /tmp/ezi-pud-packed-verification.txt.
Snapshot audit: /tmp/ezi-pud-work-snapshot-audit.txt.

Zi8MatchPUDdata_ZHS: 98.32204% -> 99.717514%.
Unit fuzzy: 98.88764% -> 99.81274%, about 19.76 weighted bytes gained.
Exact functions remain 6/7, exact code 720/2136, exact data 48/120.
All 1027 units and their per-function fuzzy scores were checked with no
regressions; this unit/producer improvement is the only measure change.

Producer instructions: 349 -> 353 versus target 354.
Producer size: 0x574 -> 0x584 versus target 0x588; frame remains 0x60.
After accounting solely for the missing dead store and its four-byte branch
destination displacement, every remaining instruction is identical, including
registers, immediates, calls and memory operands. All 65 direct branches and
13 calls correspond. This is not an exact match: the missing instruction
and function extent are explicitly retained as unresolved.

All six existing exact functions retain ctxdiff diffs 0 and identical counts.
The 48-byte extab is baseline-identical. The already-unmatched 72-byte
extabindex changes only the producer extent byte at 0x2B, 0x74 -> 0x84;
canonical relocations and its 98.61111% score are unchanged. No real data
object, section extent or metadata declaration was changed.

Pool first: identical and empty. Full 43U build passes with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No remote, linking, header, new assembly, volatile,
dummy-storage, undefined-value or forced-register changes.
