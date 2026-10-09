# clean3-c1 cleanup attempts

Worktree: /mnt/drive2/projects/wii-ipl-workers/clean3-c1.
Branch: agent/w1009/clean3-c1. Baseline: 8a67b68cf.
Assigned module: channelScript. Every touched unit must remain exact and linked.

Read clean3-head.md and cleanup-common.md fully, AGENTS.md, unslop,
writing-for-agents, and graphify. Inspected cleanup-c1, cleanup2-x8, and
cleanup2-x11 attempts before editing. Memory only identified earlier CHANSVm
work; current source and object measurements determine acceptance.

Prior failed families excluded: plain lifetime-pragma removal, accumulator
pointer sharing, broad declaration permutations, and string conversion early
returns. The pragma preserves interpreter register allocation. Try a distinct
scope or control-flow hypothesis before revisiting it.

Private header fields already have meaningful names. Unused padding has no
established role and retains its layout names. Public unk0 parameters correspond
to the reserved parameters in the definitions.

Initial DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
Initial CHANSVm source object saved under /tmp/clean3-c1-baseline.o.
Each trial builds the object and compares every allocated section, layout,
resolved relocation, and exported symbol with this baseline. Restore any
trial that changes this signature. No other worktree is modified.

## Trials
- RESTORE: CHANSVmLookupScopedObject: return directly for a missing argument. .text 36 differing bytes
- KEEP: VmPushFuncReturnInfo: guard frame initialization with the allocated block. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmParseFloat: structured constant search and numeric conversion. .text layout 53564 -> 53588 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: VmCmpEq: normal object-equality branch instead of jumping into another case. .text layout 53564 -> 53632 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: VmDateCommon: structured current-time branch instead of osgettime jump. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmLinkModules: break from failed module-name resolution. .text layout 53564 -> 53580 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: CHANSVm.h: name the two reserved parameters consistently with their definitions. Allocated bytes, layout, relocations, and exports identical.
- KEEP: VmCallMethod: name the native return object and remove an unused return label. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmLookupScopedObject: guard access with a valid argument index. .text layout 53564 -> 53556 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmLinkModules: return a local-function error directly from the resolution loop. .text layout 53564 -> 53544 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmStep: group construction and function-call cases with a constructor flag. .text layout 53564 -> 53572 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmStep: select the immediate width inside grouped load cases. .text layout 53564 -> 53604 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: CHANSVmFormatString: use a typed temporary string header. Allocated bytes, layout, relocations, and exports identical.
- KEEP: CHANSVmFormatString: index a wide-character buffer directly. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmParseFloat: use an exhausted-search bound before parsing numbers. .text layout 53564 -> 53588 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmStep: remove the lifetime pragma with property-result and accumulator scoped to their opcode. .text 183 differing bytes
- RESTORE: CHANSVmAddExe: break on an invalid string-table entry. .text layout 53564 -> 53548 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmLinkModules: structured success with one common error exit. .text layout 53564 -> 53560 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: CHANSVmLinkModules: separate scoped-object lookup from its condition. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmStep: break from the strict-equality switch and keep its status. .text layout 53564 -> 53560 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: CHANSVmFormatString: name the format argument index and value-argument offset. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmStep: guard index conversion and select success with structured cases. .text layout 53564 -> 53596 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: vmBlobParsePackFormatString: break after finding a token and parse it in a guarded block. .text layout 53564 -> 53572 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: VmReserveChunkEntry: search free entries with loop bounds and breaks. .text layout 53564 -> 53588 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmAddExe: preserve string-validation status while replacing the jump with break. .text layout 53564 -> 53572 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: VmDateCommon: finish a universal-time argument without the shared-tail jump. .text layout 53564 -> 53592 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: vmBlobParsePackFormatString: name the returned format character and star support flag. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: VmBlobCreateDirect: return after failed allocation before looking up the class. .text layout 53564 -> 53572 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmInit: guard String-class lookup with successful built-in registration. .text layout 53564 -> 53572 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmInit: separate the guarded Array-class lookup from its condition. .text layout 53564 -> 53576 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmAddExe: jump straight to the existing error exit for an invalid string. .text layout 53564 -> 53540 bytes; .rela.data resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmLinkModules: keep successful initialization inside its validity branch. .text 20 differing bytes
- RESTORE: CHANSVmParseFloat: break from constant lookup while keeping the numeric store exit. .text layout 53564 -> 53588 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- KEEP: CHANSVmParseFloat: choose integer or floating conversion in a normal if/else. Allocated bytes, layout, relocations, and exports identical.
- KEEP: VmDateCommon: indent the current-time branch to match its scope. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: CHANSVmFormatString: remove the unused maximum-literal-length accumulator. .text layout 53564 -> 53520 bytes; .rela.data resolved relocations changed; .rela.rodata resolved relocations changed; .rela.sdata2 resolved relocations changed; .rela.text resolved relocations changed; exported symbols changed
- RESTORE: CHANSVmAddNativeClass2: size the trailing class name from its declared field. .text 1 differing bytes
- RESTORE: CHANSVmLookupScopedObject: explicitly choose null or the indexed argument. .text 36 differing bytes
- RESTORE: CHANSVmStep: assign the next program counter after validating the active context. .text layout 53564 -> 53572 bytes; .rela.text resolved relocations changed; exported symbols changed
- KEEP: vmBlobParsePackFormatString: derive the format-table count from the array. Allocated bytes, layout, relocations, and exports identical.
- KEEP: VmPushFuncReturnInfo: use the named success constant for frame allocation. Allocated bytes, layout, relocations, and exports identical.
- KEEP: CHANSVmAddNativeClass2: use the existing class-name length constant in allocation. Allocated bytes, layout, relocations, and exports identical.
- RESTORE: VmCallMethod: use a shared error exit outside the object-type switch. .text 760 differing bytes; .rela.text resolved relocations changed
- KEEP: CHANSVmFormatString: explain the retained unused maximum-length comparisons. Allocated bytes, layout, relocations, and exports identical.

## Retained source

CHANSVm.c: gotos 246 -> 242. Replaced the integer-versus-float parse jump
with if/else, the current-time jump with a calendar-argument branch, and the
frame-allocation jump with a guarded initialization block. Removed the unused
native-call return label. Extracted module lookup from the comma condition.
Formatting uses a real CHANSVmObjHdr and vmWChar buffer instead of byte overlays;
named the format argument index, argument offset, and native return object.
The blob parser names its character output correctly and derives its table
count from the array. Allocation uses the existing class-name length constant;
frame allocation uses CHANS_VM_OK.

CHANSVm.h: both unk0 parameters are reserved, matching the definitions.
Private module headers already have descriptive fields. Padding has no named
uses establishing a role, so it stays unchanged. No other channelScript unit
was modified.

Keep the lifetime pragma and its existing one-line compiler explanation.
The new property-scoped alternative changed 183 .text bytes. Earlier cleanup
already rejected plain removal and pointer-sharing alternatives. Keep formatter
maximum-length tracking: removing it deletes 44 .text bytes. Added its one-line
compiler explanation. Existing shared failure exits and parser/interpreter
state-machine labels stay; tested structured alternatives changed target bytes.

44 built trials: 15 retained, 29 restored. The full allocated-object signature
is identical to the initial snapshot, including every resolved relocation and
exported symbol. Pool check: 125/125 identical. The early sizeof(sName) allocation
trial was not equivalent: sName holds four bytes and classNameStorage holds the
remaining 28. It was restored; the retained form uses CHANS_VM_CLASS_NAME_LEN.

Utility corrections selected a multiline function signature, a NO_INLINE
suffix, and unique transformation spans. These failed assertions happened
before source writes. The first pool command passed a unit instead of object
paths; the corrected two-object command passed. No failed trial remains.

## Final validation

Ran the final gate once for src/channelScript/CHANSVm with --quick.
Full 43U build passed. Pool IDENTICAL; objdiff code 53564/53564, data
6904/6904, functions 233/233, all fully linked. Instruction-exact 233/233.
Every owned section is 100%: .text, .data, .rodata, .sbss, .sdata, .sdata2.
GATE PASS: 0 regressions, 0 forbidden additions, 0 readability warnings.
Transcript: /tmp/clean3-c1-gate.log.

Fresh focused ctxdiff: CHANSVmStep 1253/1253 instructions, diffs 0;
CHANSVmFormatString 431/431 instructions, diffs 0. The complete allocated
source-object signature remains identical after the full build.

Requested report.json and build/43U/ok targets are current. Completion check:
DECOMPLETE_OK. All 1028 unit measures equal the initial complete report;
12563/12563 functions remain exact. Assembly inventory: 162 ORIGINAL,
0 PLACEHOLDER, ASM INVENTORY PASS. git diff --check passed.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.

Source files committed separately: 1aab434ba CHANSVm.c; 0fa082e3d CHANSVm.h.
No configure changes, other-unit edits, push, PR, merge, rebase, subagent,
or other-worktree edits. Ready for independent parent verification.
