# Fuzzy lane round 2, final verified handoff

One new exact function: `BS2UpdateInit`. Two additional target-proven volatile/poll corrections improve fuzzy code, and remain non-matching. All 31 remaining functions have at least three distinct successfully compiled source forms logged; build failures do not count.

Final full gate (no `--quick`; clean build):

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/api/FAAttach] objdiff: code None/500 data 240/240 functions 0/1 fuzzy 99.3600 linked code 0
[libs/RVL_SDK/src/fa/api/FAAttach] instruction-exact functions: 0/1
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] objdiff: code 332/5200 data 96/180 functions 1/7 fuzzy 98.6539 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] instruction-exact functions: 1/7
[src/system/iplKeyboard] objdiff: code 4752/6024 data 1184/1184 functions 31/32 fuzzy 98.7351 linked code 0
[src/system/iplKeyboard] instruction-exact functions: 31/32
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 94.2300 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/channelScript/CHANSVm] objdiff: code 37608/53564 data 6904/6904 functions 221/233 fuzzy 99.3644 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 221/233
[src/BS2/BS2Mach] objdiff: code 4940/16980 data 155504/158528 functions 24/29 fuzzy 98.1595 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 24/29
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3928/3928 functions 16/21 fuzzy 96.7779 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after (matched code/data bytes; denominators unchanged):

| Unit | Raw gate exact functions | Objdiff exact functions | Code bytes | Data bytes |
|---|---|---|---|---|
| `libs/RVL_SDK/src/fa/api/FAAttach` | 0/1 -> 0/1 | 0/1 -> 0/1 | 0 -> 0 / 500 | 240 -> 240 / 240 |
| `libs/RVLMiddleware/eZiText/src/clib/zkokeyp` | 1/7 -> 1/7 | 1/7 -> 1/7 | 332 -> 332 / 5200 | 96 -> 96 / 180 |
| `src/system/iplKeyboard` | 31/32 -> 31/32 | 31/32 -> 31/32 | 4752 -> 4752 / 6024 | 1184 -> 1184 / 1184 |
| `src/BS2/BS2Update` | 8/10 -> 9/10 | 8/10 -> 9/10 | 112 -> 400 / 4052 | 10488 -> 10488 / 10488 |
| `src/channelScript/CHANSVm` | 221/233 -> 221/233 | 221/233 -> 221/233 | 37608 -> 37608 / 53564 | 6904 -> 6904 / 6904 |
| `src/BS2/BS2Mach` | 24/29 -> 24/29 | 24/29 -> 24/29 | 4940 -> 4940 / 16980 | 155504 -> 155504 / 158528 |
| `src/scene/setting/AOSS` | 15/21 -> 15/21 | 16/21 -> 16/21 | 6436 -> 6436 / 16192 | 3928 -> 3928 / 3928 |

Remaining functions (one line each; successful distinct source forms are additional to declaration permutations):

- `libs/RVL_SDK/src/fa/api/FAAttach::FAAttach` — 99.36%; Drive index narrowing and attached-table base register allocation; 125/125 instructions. 9 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8_8148302C` — 99.49152%; Work pointer and key-table value registers exchange; 59/59. 5 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8_81483264` — 98.902435%; Parameter/metadata and byte iteration index registers exchange; 41/41. 6 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8_81483308` — 99.13793%; Count pointer and running counter registers exchange; 58/58. 5 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8_814833F0` — 99.04256%; Metadata pointer and candidate index registers exchange; 47/47. 5 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8_814834AC` — 99.3586%; Zero initialization chain emits an extra clrlwi; addressing/register operands also differ; 344/343. 8 source forms.
- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp::Zi8GetKOcandidates` — 97.96712%; Candidate loop boundaries, helper return narrowing and temporary scheduling; 673/669. 6 source forms.
- `src/system/iplKeyboard::create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap` — 94.00944%; Inline resource-node constructor boundary, OEM dictionary index and MemoSetting stack copy order; 318/318. 7 source forms.
- `src/BS2/BS2Update::UpdateThread` — 93.59803%; Import/scan branch and store scheduling, common bases and temporaries; proven rc reloads restored, nine target instructions still absent; 904/913. 10 source forms.
- `src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr` — 97.59036%; End pointer initialization store and object-type compare occur in opposite order; 83/83. 6 source forms.
- `src/channelScript/CHANSVm::VmDateDtor` — 94.96703%; Variadic date argument and year stack-store scheduling; 91/91. 4 source forms.
- `src/channelScript/CHANSVm::VmStringReplace` — 97.878784%; Search/replacement lengths and live cursor register allocation; 132/132. 3 source forms.
- `src/channelScript/CHANSVm::VmStringSplit` — 98.04054%; Delimiter/parent cursor and result array register allocation; 222/222. 4 source forms.
- `src/channelScript/CHANSVm::CHANSVmFormatString` — 99.84919%; Two temporary object/string-length registers exchange late in the formatter; 431/431. 6 source forms.
- `src/channelScript/CHANSVm::VmBlobGetHexString` — 98.71951%; Output offset and decoded hex digit registers exchange; 82/82. 4 source forms.
- `src/channelScript/CHANSVm::VmBlobPackCommon` — 97.949104%; Packing mode, format and copy-loop temporary register allocation; 668/668. 4 source forms.
- `src/channelScript/CHANSVm::VmBlobUnpack` — 98.452614%; Two-pass format parser and blob cursor/count register allocation; 517/517. 5 source forms.
- `src/channelScript/CHANSVm::VmWinEmuWrite` — 99.62687%; String object and total byte-length registers exchange; 67/67. 4 source forms.
- `src/channelScript/CHANSVm::CHANSVmAddExe` — 99.625984%; Module header and executable type argument registers exchange, plus address operand order; 254/254. 4 source forms.
- `src/channelScript/CHANSVm::CHANSVmLinkModules` — 98.677246%; Dispatch/module/index and global-list pointer registers exchange; 189/189. 4 source forms.
- `src/channelScript/CHANSVm::CHANSVmStep` — 96.46608%; Default step count and loop-entry branch form, floating constant bases and opcode temporaries; 1253/1253. 5 source forms.
- `src/BS2/BS2Mach::Run` — 16.744186%; Target explicitly clears fixed GPRs and the stack pointer and enters via LR; ordinary C cache-loop/callback forms cannot encode that handoff under the no-asm constraint; 11/43. 3 source forms.
- `src/BS2/BS2Mach::BS2StartGame` — 98.72774%; Five initial base/store scheduling operands and five legacy DI address/value register operands remain after fixing all polling loops; 393/393. 17 source forms.
- `src/BS2/BS2Mach::BS2StartGCGame` — 99.5614%; External DVD getter call versus inline state load, and wide tick multiplication operand allocation; 228/228. 8 source forms.
- `src/BS2/BS2Mach::CheckBS2CommandStatus` — 99.50739%; Partition-count slwi and CacheCommandComplete store occur in opposite order; 406/406. 13 source forms.
- `src/BS2/BS2Mach::BS2Tick` — 98.230415%; Boot/hardware address-base sharing, progress-store scheduling and loader output scope; six target instructions absent; 1934/1940. 4 source forms.
- `src/scene/setting/AOSS::AOSS_Init_old` — 93.78725%; Timeout default loads share an array base instead of independent references; local/global allocation and initialization/branch scheduling also differ; 1575/1584. 7 source forms.
- `src/scene/setting/AOSS::AOSSDecryptMessage` — 97.74143%; Checksum and key schedule/state/input/output cursor registers exchange; 321/321. 4 source forms.
- `src/scene/setting/AOSS::AOSSApplyAuthOptions` — 98.77193%; Authentication flags and configuration subrecord pointers use different registers; 114/114. 4 source forms.
- `src/scene/setting/AOSS::AOSSSendHelloRequest` — 92.190475%; Common CRC/key-state base hoisting and packet/key/socket local boundaries differ; 271/273. 8 source forms.
- `src/scene/setting/AOSS::AOSSXorBufferWithKey` — 98.605446%; Unrolled XOR result ownership and packet/mask address register allocation; 147/147. 21 source forms.

Data proof and limits:

- `BS2Update`: `Thread` at 0x810B2580 is an OSThread of size 0x318; target OSCreateThread uses a separate 4096-byte stack starting at thread+0x318. Corrected only the data extent from 0x1318 to 0x318, kept the address and full .bss section size 9056, and left stack bytes unowned. Separate real, initialized thread/stack objects produce 72/72 identical Init instructions and preserve data 10488/10488.
- `zkokeyp`: .data and .extab bytes match. .extabindex has two differing real function-size words (1376/1372 and 2692/2676), corresponding to the two remaining functions with extra instructions. No data rename/extent fix can legitimately conceal that.
- `BS2Mach`: the first 3020 .data bytes are identical, followed by four zero alignment bytes in the target. Anonymous string/table symbols have no authorized real source object name to pair. Two jump table relocation sets also refer into non-matching functions. Data remains 155504/158528; no invented names, pinned literals or padding objects were added.
- Other owned units retain 100% objdiff data. No weak inline/vtable data was suppressed. No other symbol rename or extent correction was made.

Target proof for qualifiers:

- DVD state field: repeated target CoverBlock.state reads at 0xDE0 with a back edge from 0xDE8 and no call. Qualification is guarded by BS2_MACH_VOLATILE_DVD_STATE, defined only by BS2Mach.c; all other translation units compile the original header field.
- LowReadResult: empty repeated polls at 0x1130/0x117C/0x1290/0x12E8, with further loads at 0x113C/0x129C immediately after poll exits. The previous interrupt calls were absent from target code.
- Static signed rc: target store at 0xD5C followed by load at 0xD64, and store at 0xE48 followed by load at 0xE50, with no intervening call. Signed volatile restores two real reads. No use-site volatile cast was added.

Uncertainties:

- AOSSParseNetworkSettings is objdiff 100%, byte-identical, and declaration-tool score (0,0). The gate uses odiff, which incorrectly rebases its CR1 conditional branches by the 36-byte function-position delta. The raw gate consequently prints 15/21, while objdiff and bytes prove 16/21. Raw output is preserved verbatim above; source/metadata were not changed to manipulate this metric.
- Remaining allocation/scheduling causes are hypotheses supported by target diffs and unsuccessful source experiments, not claims that the original source is known.
- Run needs the fixed-register handoff described above; no forbidden assembly or fabricated match was attempted.

Files changed and source commits:

```text
fcbd5a298408059adaf22d29cecb21b9a9cfa301
match update thread creation and object extent

config/43U/symbols.txt
src/BS2/BS2Update.c
tools/decomp-assist/fz1.attempts.md
```

```text
9ab3eb8183594c3a940d7bbb147de7e3c085bca0
restore dvd callback polling

libs/RVL_SDK/include/revolution/dvd.h
src/BS2/BS2Mach.c
tools/decomp-assist/fz1.attempts.md
```

```text
ce9cff4fa6c2d03310c780b1592d02c49bc6c367
preserve update result reloads

src/BS2/BS2Update.c
tools/decomp-assist/fz1.attempts.md
```

Verification artifacts:

- `tools/decomp-assist/fz1.attempts.md` — structural diagnoses, source variant hashes/results, proofs and final all-open audit.
- `tools/decomp-assist/fz1.r2.final-gate.txt` — complete final clean gate output.
- `tools/decomp-assist/fz1.r2.report.md` — this report.

No push, PR, branch switch, rebase, other worktree mutation or subagent was used. Earlier untracked artifacts were left untouched.
