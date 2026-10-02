# Data lane d2

Base HEAD and origin/main: eecf16f0. All four initial pool checks pass.
Initial data: BS2Update 1328/10488; iplSound 188/3316; AOSSLink 48/2432; RakuRakuThread 144/456.
Initial instruction-exact: BS2Update 8/10; iplSound 56/57; AOSSLink 12/14; RakuRakuThread 12/14.
Scope is data matching. Existing nonexact code is retained unless a data correction fixes it; no code-only compiler experiments are required for this lane.

## Initial evidence

- BS2Update: Flags0/Flags1/Thread/header source allocation differs from target. Thread source size 0x1318, target label covers 0x1320 with alignment gap. Static sbss allocation is reversed by compiler optimization, unlike declaration order. Target short literal at 0x81696598 is `.` whereas source is `-`.
- iplSound: .bss bytes and overall size already equal, but extracted `_seBlk` size 0xd8 includes two 12-byte runtime destructor registration records at offsets 0xcc and 0xd8. `sSystem` size 0x63c includes destructor record at offset 0x710 plus alignment. Target startup registers records via r5 = bss base + 0, +0xcc, +0xd8, +0x710 before `__register_global_object`; generated source has separate unnamed compiler records at those exact offsets. No dummy objects or size changes to conceal this discrepancy will be added.
- AOSSLink: source has all real objects. NCDIfConfig sizeof 0x15e versus extracted symbol extent 0x160; NCDIpConfig sizeof 0x7c4 versus extent 0x7c8. These include linker alignment, not missing fields. Source small-data statics are reverse allocated.
- RakuRakuThread: target OSMessageQueue symbol extends 0x24 but actual SDK type is 0x20; trailing four bytes are alignment. Target clock halves have separate symbols, source OSTime has one 8-byte symbol. Store sequence in syncRakuProgress is stw r3 at 0x81698c60 and stw r4 at 0x81698c64, proving one 64-bit clock value. No fabricated queue fields will be added.

## BS2Update attempts

1. Explicit zero initialization allocates static globals in definition order. Flags0 now offset 0, Flags1 offset 0x800, Thread offset 0x1000, headers 0x2320/0x2340. Nonexact init still uses separate symbol references instead of target common bss anchor. No exact function dropped.
2. Initialize public small-data globals too. This restores State 0x10, CurrentEntry 0x14, StartUpdate 0x28, CancelUpdate 0x2c. Replacing the two filename separators with the target `.` makes .sdata 100% and adds 24 matched bytes.
3. Explicit Thread/header zero initialization and a 32-byte aligned Thread type did not improve instruction codegen. Reverted the type alignment because the object-size gap is not enough evidence to change the real type's alignment. Thread is already the correct real OSThread plus 4096-byte stack. Remaining target extent includes eight bytes before the aligned header.
4. Named four anonymous small-data flags by target relocations: 0x81698b10 is set on reboot attributes and tested for State 4 versus State 3; 0x81698b14 is the seat-title flag returned by BS2ContainsSeatTitles; 0x81698b18/1c are cleared by the final UpdateThread block in the source's matching order. Renames preserve all addresses, sizes, split ranges, and total bytes.

## AOSSLink attempts

1. Before starting: fetched origin/main, source still unchanged from base. All pool checks are identical. Explicit zero initialization for cancel flag, IPv4 octets and callback pointers restores the declared target order.
2. Named original anonymous IPv4 and callback symbols using .text relocations: SetNCDIPAddr passes 0x81698c3c/40/44/48/4c to StoreIpv4Octets in address/netmask/gateway/dns1/dns2 order; Alloc and Free load pointers at 0x81698c50/54; Status calls pointer at 0x81698c58. All original addresses and sizes retained.

## RakuRakuThread attempts

1. Fresh origin fetch showed no owned-source changes since HEAD. Split the original 64-bit clock into two real u32 globals, assigned from one local OSTime. `syncRakuProgress` remains 27/27 instructions, diffs 0. The original has separate word relocation targets and getState only reads the low word. This models those real words without label-pinning or raw offset casts.
2. Explicit zero initializers preserve small-data definition order. Named clock words, active flag, message slot, and display state using their direct .text relocations. .sbss now 100%; matched_data 144 -> 160. Original display state is initialized to one and switch stores are identical.

## Proven extraction metadata ownership

Before changing any inferred data extent, checked the target's actual code uses, actual SDK type, generated symbol boundaries and split ranges. These are data-ownership corrections, not removing mismatched payload or changing any function size. Every split range and total section byte count stays unchanged. Alignment bytes remain in the original sections and cannot be represented by fake C++ fields.

- BS2 Thread: OSCreateThread at 0x8137f334 receives object at bss+0x1000, stack top at bss+0x1318+0x1000, size 0x1000. Thus actual Thread payload ends at +0x2318; +0x2318..2320 is alignment before UpdateHeader0. Real SDK OSThread size is 0x318 and stack is 0x1000.
- AOSS interface: memset at 0x813fd76c explicitly receives 0x15e bytes for relocated AOSSi_NcdIfConfig. IP memset at 0x813fd83c explicitly receives 0x7c4 bytes for relocated AOSSi_NcdIpConfig. The 2 and 4 trailing bytes are alignment, not fields.
- Raku queue: constructor passes relocated sRakuMsgQueue to OSInitMessageQueue. Its target implementation initializes two 8-byte queues plus fields at 0x10/14/18/1c, exactly 0x20 bytes. The original extent incorrectly absorbs four bytes of end-of-unit alignment.
- Sound: __sinit at 0x8136c588 loads one bss anchor. Four calls of __register_global_object pass r5 = anchor+0, +0xcc, +0xd8, +0x710. Runtime's real DestructorChain has three pointers, size 0xc. _seBlk starts at +0xc, has 16 elements of 0xc (explicit __construct_array r6=0xc,r7=16), ends at +0xcc. System starts at +0xe4 and the generated real class ends at +0x710. Thus previously inferred `_seBlk` and `sSystem` extents overlap distinct destructor registration objects. Separate those real records in metadata. No source objects, forced sections, force-active entries, assembly, or fabricated padding are added.

Checkpoint quick full gate: GATE PASS, regressions 0, forbidden 0, readability 0, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Data BS2Update 1432, AOSSLink 88, RakuRakuThread 160, Sound 188. Instruction-exact counts unchanged 8/56/12/12.

Ownership corrections result: BS2Update data 10488/10488; AOSSLink data 2432/2432; RakuRakuThread 456/456, every non-text section 100%. Original section totals unchanged. Sound .bss rises to 99.615875%; the remaining 12 bytes are the first real compiler-generated destructor record, originally mislabeled `unk__Q23ipl3snd`. Rename it to its generated local symbol @15968, with the same address and size. The other three record names @15969/70/71 follow generated object metadata and the exact target registration order.

Sound was fetched and checked against origin/main again before this change; no owned-source changes. No source experiment is appropriate because target and generated .bss contain the same real objects at the same offsets, and every code function has objdiff 100%. Existing `UnkCls` destructor name represents the compiler array destructor; instruction-only matching by its old inferred name reports 56/57, while objdiff reports 57/57. No function is deleted or renamed here.

Second quick full gate: GATE PASS, regressions 0, forbidden 0, readability 0, target DOL hash retained. All four matched_data equal their unchanged initial total_data. Every emitted non-text section is 100% in objdiff, including ctors. No extab/extabindex sections exist in these units. Instruction-exact counts remain BS2Update 8/10, Sound 56/57, AOSSLink 12/14, RakuRakuThread 12/14.

Scope audit: no remaining non-text mismatches, so no open data objects require further attempts. Existing code-only mismatches are outside the explicitly assigned DATA LANE and were not tuned. No configure.py or splits.txt changes, no shared headers or other translation units changed, no push or PR.

## Final clean gate

```text
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Update] objdiff: code 112/4052 data 10488/10488 functions 8/10 fuzzy 91.6604 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 8/10
[src/sound/iplSound] objdiff: code 5576/5576 data 3316/3316 functions 57/57 fuzzy 100.0000 linked code 5576
[src/sound/iplSound] instruction-exact functions: 56/57
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 91.1111 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/iplRakuRakuThread] objdiff: code 1252/2168 data 456/456 functions 12/14 fuzzy 94.6900 linked code 0
[src/scene/setting/iplRakuRakuThread] instruction-exact functions: 12/14
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final raw section check: every owned data payload equals original bytes; source section-end omissions are zero linker alignment only. All original split ranges and total_data remain unchanged. nm/objdump symbol and relocation evidence was saved in /tmp/data-d2-<unit>-<obj|src>.*. Source vtable entries match the original by relocation target and offset; relocation list ordering is irrelevant. No deduplicated weak-data exemption needed.

Local source checkpoint 44a7b170; ownership checkpoint 078753b9. These data-symbol corrections require parent review of the evidence above. Remaining code-only nonexact functions were already nonexact at baseline and are outside this data task.
