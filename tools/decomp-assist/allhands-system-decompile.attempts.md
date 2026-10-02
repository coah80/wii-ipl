# System remainder decompilation, 2026-10-02

Baseline: `449529d92405f8f7fda610660c7794914a81dfe6`.
Branch: `agent/bittle/allhands-system-decompile`.
Owned units: `src/utility/iplESMisc.cpp`, `src/scene/setting/AOSS.c`,
`src/scene/setting/ATERM.c`. Parent additionally approved the single ESMisc
return-type declaration change in `include/utility/iplESMisc.h`.

The current user priority is complete source reconstruction first, exact code
matching second, linking last. This candidate is decompilation progress, not an
exact match or a linking change. No configuration, symbol, split, or link flag
was changed. AOSS and ATERM are unchanged.

## Initial audit

- Read AGENTS.md, CONTRIBUTING.md, local skill inventory, AOSS/ATERM attempt
  histories, and ESMisc rounds 9/11. The sole local skill is unrelated TypeSafe
  integration guidance.
- Configured and built only 43U with the approved Wibo wrapper.
- Before source work, pool_diff found ATERM 0/0 strings and AOSS 1/1 identical.
  ESMisc first diverged at string 83; both contained 114 strings.
- ESMisc's 30 exact functions were preserved in earlier rounds, but a meaningful
  helper reconstruction had been discarded solely because it was not exact.
  Reconstructed it from the current C++ and target object, without importing an
  old experimental source or altering linker behavior.

## ESMisc reconstruction

Restored three ordinary inline boundaries named by the target's diagnostic
literals: `verifySavedataZD`, `DeleteTicketsForce`, and `InitSavedata`.
`ESMisc::DeleteUnauthorizedData` returns the initializer status.

Concrete correctness corrections:

1. Use a real NAND_MAX_PATH buffer and a real caller-owned, 32-byte-aligned
   NANDFileInfo. Removed the out-of-object `path - 8` and `fileInfo - 0x20`
   accesses. The caller also owns the aligned, rounded ticket-view scratch.
2. Traverse `ESTitleId` values by typed array index, with one unconditional loop
   increment for every title. The old verifier branch continued without
   advancing its separate byte offset and could repeat the same title.
3. Replace the handwritten nested 64-bit switch-lowering expression with the
   five actual title cases and the independently masked save-title predicate.
4. Preserve the two ES_ListTitlesOnCard results independently of inlined file
   and ticket operation status. The public declaration now returns s32.
5. A negative NANDRead result jumps to cleanup, which frees the save buffer
   before closing the still-open file. The old source took the success-path
   close before freeing it. Successful or invalid-size reads retain their
   close-before-delete/free path.
6. Use sizeof(ESTicketView) for the 0xD8-byte copy and OSRoundUp32B for the 0xE0
   scratch/allocation extent, preserving the target's distinct sizes.

### ABI and control-flow evidence

Target function: address 0x813673E0, size 0x704 (449 instructions).
At original object offsets 0x1D20 and 0x1D9C, the two enumeration return values
are saved in r27. Calls through both verifier/ticket paths leave that saved
value independent. At 0x23C0 it is copied to return register r3 after the
optional title-list free. The prior void declaration discarded this ABI.

The only declaration is in include/utility/iplESMisc.h. The only call is
src/system/iplSystem.cpp:680; it intentionally ignores the result. The symbol
name is unchanged because the return type is not encoded in this member name.
All 1027 compiled source objects were compared after a forced full rebuild;
iplSystem and every unit except iplESMisc were byte/relocation unchanged.

The target's verifier branch joins the common increment at 0x238C (index +1,
byte offset +8). Its negative-read path joins cleanup at 0x2104, whereas its
successful close begins at 0x20E0. The reconstruction restores these distinct
paths instead of compensating with stack offsets or register tricks.

### Measurements

| Unit / measure | Before | After |
| --- | ---: | ---: |
| ESMisc exact functions | 30/31 | 30/31 |
| ESMisc exact code | 9404/11200 | 9404/11200 |
| ESMisc fuzzy | 96.76036% | 99.33143% |
| DeleteUnauthorizedData fuzzy | 79.797325% | 95.830734% |
| Function instructions | 434/449 | 446/449 |
| ESMisc matched data | 4416/4416 | 4416/4416 |
| ATERM exact / fuzzy / data | 17/26; 96.624664%; 18584/18864 | unchanged |
| AOSS exact / fuzzy / data | 16/21; 96.777916%; 3928/3928 | unchanged |
| Whole-report fuzzy | 99.588615% | 99.598236% |

pool_diff now reports all 114 strings identical. The source .data is 4378
bytes and exactly equals the original section's first 4378 bytes. The target
section is 4384 bytes and ends in six zero alignment bytes. No synthetic
padding was added. The objdiff data score remains 100%, and the literal audit
checks 204 arguments in all 30 exact functions with zero candidates or errors.

The candidate remains non-exact. ctxdiff shows 446/449 instructions and
remaining register allocation, -1 mask materialization, and scratch-pointer
lifetime differences. No brute-force declaration/register search was run.

## Validation

Commands:

- python3 configure.py --version 43U --wrapper ../toolchain/wibo-build/wibo
- Delete generated native `build/43U/src/**/*.o`, retaining a private baseline
  object snapshot for comparison.
- WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source build/43U/report.json build/43U/ok
- PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/pool_diff.py
- PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/ctxdiff.py src/utility/iplESMisc DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap
- PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/literal_reference_diff.py src/utility/iplESMisc
- Compare every unit in the fresh report and all 1027 source objects' allocated
  bytes and normalized relocations against the baseline.
- git diff --check

Full rebuild passed (1031 Ninja steps). DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.

Only the ESMisc report changed: its fuzzy and one function's fuzzy improved.
No report metric regressed. Only ESMisc's allocated .text and .data changed:
.text 11360 -> 11408 bytes (390 relocations on both sides), .data 4378 -> 4378
bytes (zero relocations). Every other allocated section/object is unchanged.

A temporary host harness extracted the actual reconstructed helper bodies,
substituted fake Wii/heap calls, and exercised 12 control-flow scenarios:
first and second enumeration errors, title-list allocation failure, mixed
Zelda/blocked/ordinary title traversal, negative read, short read, second-save
verification failure, absent file, save-buffer allocation failure, ChangeUid
failure, ticket enumeration failure, and zero-ticket handling. Tests ran with
AddressSanitizer and UndefinedBehaviorSanitizer. LeakSanitizer is unavailable
under the execution environment's ptrace, so only that component was disabled.
The harness is supplemental behavioral validation, not a retail runtime test.

GATE: focused decompilation improvement; full 43U/DOL and no-regression checks
pass; exact-matching gate remains incomplete at 30/31. No linking claimed.

## Follow-on: recover the last ESMisc structural differences

Baseline for this follow-on is the accepted reconstruction `1f9db89d`:
30/31 exact functions, function 95.830734%, unit 99.33143%, 446/449 instructions,
data 4416/4416. The source/header correction remains intact.

Natural source attempts, in order:

| Attempt | Instructions | Function fuzzy | Disposition |
| --- | ---: | ---: | --- |
| Ticket helper uses error-first cleanup and returns early with no tickets | 446/449 | 95.830734% | Same generated code |
| Caller gives aligned ticket scratch an explicit pointer lifetime | 448/449 | 98.004456% | Improved |
| Move aligned ticket scratch into the ticket helper | 446/449 | 95.817375% | Rejected |
| Scope caller's scratch pointer to successful title enumeration | 448/449 | 98.89755% | Retained |
| Restore nested ticket helper with scoped scratch | 448/449 | 98.89755% | Same generated code |
| Ticket helper returns its actual ES operation status | 449/449 | 99.14254% | Retained |

The scratch pointer is initialized only in the block reached after successful
second enumeration, and remains live across the title loop. This restores the
saved scratch cursor and per-iteration 64-bit mask materialization. No pointer
is used before initialization and no artificial use extends its lifetime.

The private ticket helper now returns the status already obtained from
ES_GetTicketViews or ES_DeleteTicket, including its zero-ticket early return
and normal cleanup. Its caller intentionally discards that status. The return
contract of an independently emitted original helper cannot be established
because this helper was fully inlined; this is a natural equivalent source
form whose zero-ticket branch structure is confirmed by the target. It does
not overwrite the outer enumeration status or change the public ABI further.

Final ctxdiff: 449/449 instructions, 74 differences. Every mnemonic,
non-register operand, stack offset, resolved call target and branch target
agrees. The remaining differences are register substitutions, including the
title list, scratch cursor, title index, verifier flags and title halves. No
register/declaration permutation search was performed after reaching this
structural agreement.

Measurements after a fresh full report:

- ESMisc exact functions 30/31 -> 30/31
- ESMisc exact code 9404/11200 -> 9404/11200
- ESMisc fuzzy 99.33143% -> 99.8625%
- DeleteUnauthorizedData fuzzy 95.830734% -> 99.14254%
- Matched data 4416/4416 -> 4416/4416
- Pool: all 114 strings identical
- Literal audit: 204 arguments in 30 exact functions, no candidates/errors
- Every other unit's full report is unchanged
- Full 43U build/check and DOL SHA1 pass:
  26116613f624061ba99c8d1a299aaa6efa85670d
- The same 12 ASan/UBSan host control-flow scenarios pass on helper bodies
  freshly extracted from this final candidate (LeakSanitizer disabled only
  for the environment limitation already noted)
- git diff --check passes

This remains a partial matching improvement, not an exact function or unit.

### Rejected ATERM ownership experiment

Read-only target evidence identified that the old typed reply view spans the
last eight bytes of one BSS object and the following option-buffer allocation.
With parent approval, tried a real two-object protocol-workspace aggregate and
corresponding narrow metadata consolidation. It preserved storage, addresses,
all 17 exact functions and matched data, and reduced the main protocol from
972 to 959 instructions (target 951). However, its unit fuzzy regressed from
96.624664% to 96.49781%; wider grouping and a decoder-helper experiment also
failed the no-regression condition. All ATERM source and symbol metadata were
restored. Fresh report after restoration was identical to the accepted ESMisc
baseline, and the DOL hash passed. Detailed rejected source/metadata and
address evidence were kept privately for future work; none is in this commit.
