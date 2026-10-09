# sol-m11 AOSS_Init_old, 2026-10-09

Worktree data-d1, branch agent/w1009/aoss-init, initial HEAD 9936f0a9.
Scope is src/scene/setting/AOSS.c. Keep the existing untracked rx67c log.
Read sol-common, brief-v2, every lever, AGENTS.md, unslop and writing-for-agents.
Read c49db1c6:tools/decomp-assist/sol-r1.attempts.md and AOSS effort-policy
entries through the dedicated MAX assignment. No push, PR, merge, rebase,
other-worktree mutation or subagent.

## Earlier ideas excluded

- Blind local declaration permutations and compiler version/unit flag sweeps.
- Scoped optimization 0..3 and IRO 0/1, including the previous product/cursor matrices.
- Prior poll-time signedness, named timeval, two-product/reused-product, expression ordering and timeout-parameter trials.
- Wide seconds products that reach 1584 instructions by changing overflow behavior.
- Request-record indexed/bumped-pointer spellings, early runtime pointers and receive-buffer cursor aliases already measured in sol-x2 and sol-r1.
- The previously measured success guard, unsigned connection and initialization-result type spellings.
- SDK packing/alignment and unrelated AOSS XOR/Auth/Link work.
- Padding, carrier structs, artificial dependencies, redundant guards and use-site volatile casts.

## Baseline

Full requested Ninja build passed. DOL SHA1 is
26116613f624061ba99c8d1a299aaa6efa85670d. Fresh origin/main fetch has no
AOSS source change. Live checkout is 1306/1584 differing, 1581/1584
instructions; its string pool is identical. The requested 1278/1584,
1578/1584 baseline is the saved sol-r1 Init diagnostic, not current main.
Replay that diagnostic only as a control before new experiments.

Prior call-anchored analysis found eleven unequal intervals, net six
target instructions. Three intervals had extra source instructions. Each
new source change must explain its actual target block, not add arbitrary
instructions until total sizes match.

## Attempts

New trials and block evidence follow below.
- poll-zero-accumulator-before-descriptors: 1353/1584 differing, 1581/1584 instructions, objdiff 96.25%, data 2800, pool True, sibling exact drops []. Retain two native 64-bit accumulation steps, with each clock product truncated to u32 before widening. Source 22f716c422f2.
- poll-zero-accumulator-signed-casts: 1353/1584 differing, 1581/1584 instructions, objdiff 96.31376%, data 2800, pool True, sibling exact drops []. Retain two native 64-bit accumulation steps, with each clock product truncated to u32 before widening. Source 8169077114fb.
- poll-zero-accumulator-binary-assignments: 1353/1584 differing, 1581/1584 instructions, objdiff 96.25%, data 2800, pool True, sibling exact drops []. Retain two native 64-bit accumulation steps, with each clock product truncated to u32 before widening. Source e5b53f5c7340.
- poll-zero-after-descriptors: 1341/1584 differing, 1580/1584 instructions, objdiff 96.46528%, data 2800, pool True, sibling exact drops []. Move native accumulation after descriptor setup, matching the target data dependencies. Source 25a4d77568b7.
- poll-zero-before-microseconds: 1354/1584 differing, 1581/1584 instructions, objdiff 96.28094%, data 2800, pool True, sibling exact drops []. Initialize the real tick accumulator while constructing the timeval, then add each component after descriptors. Source 3bfbd1838f29.
- manufacturer-positive-label: 1353/1584 differing, 1581/1584 instructions, objdiff 96.31376%, data 2800, pool True, sibling exact drops []. Express the observed positive branch and following unconditional branch with direct control-flow labels, without another condition. Source b5a33e5a57d9.
- manufacturer-conditional-call: 1353/1584 differing, 1581/1584 instructions, objdiff 96.31376%, data 2800, pool True, sibling exact drops []. Use one conditional expression for the bounded manufacturer copy; no additional side effect. Source 5397757ee35b.
- initial-link-result-switch: 1336/1584 differing, 1583/1584 instructions, objdiff 95.709595%, data 2800, pool True, sibling exact drops []. Dispatch real error/success/default return states with a switch, preserving cleanup and sleep paths. Source f580e22a3dce.
- initial-link-nested-success: 1353/1584 differing, 1581/1584 instructions, objdiff 96.31376%, data 2800, pool True, sibling exact drops []. Separate connection success from the access-point status test using nested conditions. Source fe62a9d0281e.
- record-transaction-field-pointer: 1461/1584 differing, 1579/1584 instructions, objdiff 96.440025%, data 2800, pool True, sibling exact drops []. Keep the transaction halfword address across its byte-order conversion, as target r21 does. Source 4e9309ea0e91.
- record-transaction-pointer-after-rand: 1461/1584 differing, 1579/1584 instructions, objdiff 96.56313%, data 2800, pool True, sibling exact drops []. Compute the halfword address after rand, then retain it across SOHtoNs. Source 001abbc6224f.
- record-transaction-convert-assignment: 1338/1584 differing, 1580/1584 instructions, objdiff 96.25316%, data 2800, pool True, sibling exact drops []. Keep the generated nonce in its actual halfword field during conversion; audit sequencing and truncation. Source c47f7bb77dcf.
- ipv4-scoped-address-values: 1389/1584 differing, 1579/1584 instructions, objdiff 96.59154%, data 2800, pool True, sibling exact drops []. Give IPv4 calculation its own mask, subnet and local-address locals instead of reusing the receive-length variable. Source 6549936e43ea.
- ipv4-scoped-host-part: 1389/1584 differing, 1579/1584 instructions, objdiff 96.59154%, data 2800, pool True, sibling exact drops []. Name the host portion before incrementing it, preserving u32 wrap and boundary fallback. Source c601f7b21a0f.
- ipv4-scoped-separated-assignment: 1389/1584 differing, 1579/1584 instructions, objdiff 96.59154%, data 2800, pool True, sibling exact drops []. Separate declaration and assignment of the new local IPv4 address. Source 0ac141ee725e.
- receive-address-block-scope: 1341/1584 differing, 1580/1584 instructions, objdiff 96.46528%, data 2800, pool True, sibling exact drops []. Limit the output address lifetime to SORecvFrom; the target initializes its length locally. Source c99bc40f3ea5.
- receive-address-length-sizeof: 1341/1584 differing, 1580/1584 instructions, objdiff 96.46528%, data 2800, pool True, sibling exact drops []. Use the actual output-address size, testing unsigned sizeof conversion and constant reuse. Source 30e706154660.
- receive-address-length-unsigned: 1341/1584 differing, 1580/1584 instructions, objdiff 96.46528%, data 2800, pool True, sibling exact drops []. Use an unsigned address length matching the u8 field. Source 674de1b8547f.
- poll-time-block-scope: 1341/1584 differing, 1580/1584 instructions, objdiff 96.46528%, data 2800, pool True, sibling exact drops []. Keep the real timeval within poll setup, testing the target stack stores at +0x60/+0x64. Source c85d5df7b378.
- ipv4-poll-defined-result: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Keep the main branch defined initialization-result guard; isolate the native poll and scoped IPv4 changes from the unassigned-r14 diagnostic. Source abd1167c1d54.
- poll-only-defined-result: 1306/1584 differing, 1581/1584 instructions, objdiff 96.272095%, data 2800, pool True, sibling exact drops []. Keep the defined initialization-result guard and change only the real poll ABI and accumulator. Source eee35601423e.
- target-stack-address-order: 1363/1584 differing, 1580/1584 instructions, objdiff 96.382576%, data 2800, pool True, sibling exact drops []. Order the real 8-byte objects by the target offsets: receive +0x68, timeval +0x60, reply +0x58, aligned bind +0x40, identity +0x2c. Source dc1f9b60ef1b.
- target-stack-address-order-diagnostic: 1393/1584 differing, 1579/1584 instructions, objdiff 96.57513%, data 2800, pool True, sibling exact drops []. Apply the same evidenced stack order to the saved r14 diagnostic for measurement only. Source 234854dc882b. Diagnostic only.
- target-stack-receive-first-identity-last: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39899%, data 2800, pool True, sibling exact drops []. Move the receive record first and the identity last, isolating their target stack-lifetime grouping. Source 879985a7f718.
- initial-link-success-first-switch: 1383/1584 differing, 1583/1584 instructions, objdiff 95.53977%, data 2800, pool True, sibling exact drops []. Put the success arm first in the natural connection-result switch and retain the common retry path. Source dc6209b1db2a.
- initial-link-error-else-success: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Use one error/else-success chain instead of independent conditions. Source 824b705aa0d3.
- initial-link-named-success-flag: 1413/1584 differing, 1582/1584 instructions, objdiff 96.357956%, data 2800, pool True, sibling exact drops []. Compute the actual connection-success predicate before handling the error, then consume it once for the status check. Source 12858bdbebaf.
- cleanup-replaced-time-address-locals: compile failed. Remove the three locals made unused by native poll accumulation and scoped IPv4 calculation. Source 35c727f8cc3d. See /tmp/sol-m11-trials/cleanup-replaced-time-address-locals.build.txt.
- cleanup-old-tick-remainder: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Isolate removal of the obsolete locals; retained source will remove every newly unused declaration. Source 280774f5d7f3.
- cleanup-old-subnet-values: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Isolate removal of the obsolete locals; retained source will remove every newly unused declaration. Source 904da8601337.
- scoped-ipv4-plus-transaction-pointer: compile failed. Combine the independently useful local-address calculation with the target-proven nonce pointer retained across SOHtoNs. Source 0c38e0bd9654. See /tmp/sol-m11-trials/scoped-ipv4-plus-transaction-pointer.build.txt.
- nonce-record-pointer-after-rand: compile failed. Create the record pointer only after rand, preserving the target computed address across conversion. Source 188be1d9bb21. See /tmp/sol-m11-trials/nonce-record-pointer-after-rand.build.txt.
- nonce-narrow-return-value: compile failed. Name the generated halfword nonce and convert that value, retaining the required pre-conversion field store. Source 00abf0b37b03. See /tmp/sol-m11-trials/nonce-narrow-return-value.build.txt.
- cleanup-replaced-time-address-locals-corrected: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Remove unused declarations only inside Init; the earlier transformer removed the runtime mask field and failed compilation. Source 761e0f55240f.
- nonce-record-pointer-after-rand-corrected: 1376/1584 differing, 1579/1584 instructions, objdiff 96.36048%, data 2800, pool True, sibling exact drops []. Compute the real record address after rand and retain it across halfword conversion; runtime fields are unchanged. Source e022b34f54b4.
- nonce-narrow-return-value-corrected: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Name the generated halfword value without changing the required store before conversion. Source d22b40b25dbf.
- ipv4-conditional-address-fallback: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Select the same wrapped-address fallback with one conditional expression. Source c0beafc7fc1c.
- ipv4-named-broadcast-boundary: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Name the actual broadcast-address boundary before checking the next host address. Source 94a324b0dfa5.
- ipv4-compound-host-combination: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Initialize the local address from the network and combine the incremented host portion with compound OR. Source 4265f744a3b6.
- ipv4-named-gateway-load: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Give the unchanged gateway read a local value while preserving fresh global call arguments. Source 7d9b7baba52c.
- typed-protocol-message-identity: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Model the eight-byte protocol identity as its real address-plus-transaction record, preserving all memcpy/XOR bytes. Source d93eba18827f.
- protocol-state-enum: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Use the actual protocol states as an int-width C enum, preserving the default path and all return-value assignments. Source 7fd2d3dee278.
- protocol-state-enum-invalid: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2800, pool True, sibling exact drops []. Use the actual protocol states as an int-width C enum, preserving the default path and all return-value assignments. Source ce5b5362609e.
- receive-narrow-size-local: 1354/1584 differing, 1581/1584 instructions, objdiff 96.62184%, data 2800, pool True, sibling exact drops []. Use a locally computed byte-width output-address size within the receive call lifetime. Source 9de119e18263.
- receive-byte-size-const: 1355/1584 differing, 1580/1584 instructions, objdiff 96.39836%, data 2792, pool True, sibling exact drops []. Keep the actual output-record byte size const within the receive call scope. Source c78ba842e757.
- receive-halfword-size-local: 1354/1584 differing, 1581/1584 instructions, objdiff 96.62184%, data 2800, pool True, sibling exact drops []. Check whether the separate size copy needs byte width or merely a named narrow temporary. Source 43a5d5fe1084.
- receive-byte-size-function-local: 1354/1584 differing, 1581/1584 instructions, objdiff 96.62184%, data 2800, pool True, sibling exact drops []. Declare the real address-size byte with the other C89 locals, and assign it only at the receive path. Source 15421bae35a5.

## Alignment evidence and disposition

The aligner is /tmp/sol-m11-align.py. It reads ELF relocations, anchors
corresponding calls by symbol, then runs difflib.SequenceMatcher with
opcode, normalized register operands and resolved relocation tokens in
each interval. Full replay/final instructions and interval JSON are
/tmp/sol-m11-replay-alignment.{txt,json} and
/tmp/sol-m11-final-alignment.{txt,json}. Offsets below are relative to Init.

| Target interval or instruction | Replay target minus source | Source construct |
| --- | ---: | --- |
| Defaults +0x20 through +0x4c | -1 | Source materializes an array base; target addresses the two halfwords independently. Earlier object-split trials are excluded. |
| Manufacturer +0x440/+0x444 | +1 | Target has ble followed by an unconditional branch; the source if becomes one inverse branch. Positive labels and a conditional call do not preserve the extra branch. |
| First connection +0x5cc/+0x5d0 | +1 | Two consecutive bne branches reuse the same compare result. Ordinary switch, nested-if, else-if and named-success forms do not reproduce both. |
| Request record +0x784 through +0x794 | -1 | Source recomputes the record address after SOHtoNs; target keeps r21 across the call. Scoped halfword/record pointers remove one instruction but reduce or move other matches. |
| Protocol setup +0x900 through +0x910 | +1 | Target keeps constants 0x11, 0, 8, -1 and 1; source hoists/reuses a different constant set. |
| IPv4 +0x9dc through +0xa04 | -1 | Source has an extra mr to the first call argument. Scoped address locals remove that copy in the retained source. |
| Second connection +0xb24/+0xb28 | +1 | Another repeated bne using unchanged condition flags. |
| Discovery/status +0xd64 | +1 | Target materializes li 3 before the state store; source reuses a hoisted constant. |
| Poll +0xf6c through +0xf7c | +2 | Target has two addc/adde accumulation pairs, including the initial zero addition. The retained native OSTime accumulation restores equal 32-instruction intervals. |
| Receive +0x10b4 | +1 | Target locally materializes li 8; source reuses an outer constant. A byte-width local size restores this exact opcode and argument sequence, with different buffer register and stack offset. |
| Final connection +0x13e4/+0x13e8 | +1 | Third repeated bne using unchanged condition flags. |

The eleven deltas total +6. The retained source additionally keeps the
main branch defined initializationResult guard. Its final unequal
intervals are 1:-1, 28:+1, 30:-1, 41:+1, 53:-1, 64:+1, 79:+1, 95:+1,
146:+1, totaling +3. IPv4, poll and receive intervals now have equal
instruction counts. Total size alone would not settle the remaining
redundant branch shapes or register/stack differences.

The native poll capture /tmp/sol-m11-init-cap matches all emitted native
code/data/relocation sections of its independently built source object.
Regsim reproduces 623/623 virtual registers. The missing connection
branches are absent in initial PCode, so changing register colors cannot
restore them. vmap2 requires equal source/target instruction counts;
there is no honest equal-size candidate to feed it.

Four compile failures came from removing the runtime subnetMask field
instead of only Init's obsolete local. The corrected transformer is
bounded to the function. Failed compiles do not count as successful
coverage. Target-stack ordering was also tested in older h2b history;
this round's layout combinations are controls, not a new untested lever.
The const byte-size trial drops eight data bytes and is rejected.

No repeated success checks, use-site volatile casts, uninitialized
reads, artificial locals, pragmas or inline assembly are retained.
The saved unassigned-r14 guard is diagnostic only. Current main's
defined initializationResult test stays intact. Both time products retain
their u32 truncation before widening; their sum is at most twice UINT32_MAX
and fits signed OSTime. Scoped IPv4 arithmetic preserves every u32
wrap, comparison, fallback and fresh global call argument. The eight-byte
output-address size is stored in its u8 length field before SORecvFrom.

Coverage: 47 logged compiler attempts, 43 successful compiles, 43 distinct successfully compiled source hashes. Replays and equivalent assembly are explicitly controls.

Retained Init: live main 96.18624% -> 96.62184%, 1581 -> 1581/1584
instructions, strict positional differences 1306 -> 1354. The requested
saved diagnostic remains the smallest positional difference count,
1278/1584 at 1578/1584 instructions; no new candidate beats it on that
metric. These are clean partial source/ABI improvements, explicitly
allowed by the task, not an exact match or completion claim. AOSS remains
19/21 exact with 2800/2800 data. configure.py and other sources are unchanged.

Final gate follows.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 9268/16192 data 2800/2800 functions 19/21 fuzzy 98.6275 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 19/21
[src/scene/setting/AOSS]   section .bss size 2368 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 98.62747
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 96.62184
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 9268/16192 data 2800 functions 19 fuzzy 98.4570
regressions vs baseline: 0
global matched_code_percent: 98.11310 -> 98.11310
global fuzzy_match_percent: 99.92802 -> 99.92894
global complete_code_percent: 91.03011 -> 91.03011
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final source SHA256 9de119e1826338f5b16cdc8c2b0583c97d45a4dd72124993df290df111ec6565.
Saved focused partial diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-m11.AOSS.diff.
The gate passes full 43U build, DOL SHA1, identical pools, 19/21 instruction-exact siblings, all sections of data, zero baseline regressions and zero new forbidden/readability patterns. It does not establish an exact Init match.
Leaf base stays 9936f0a9ed2f075315d28141b678ecdb525aab8d; shared origin/main advanced to 2d169c59cffd578cd52a308ab94a0903cc782a44 while experiments ran. No merge or rebase. The parent owns integration and fresh validation.
