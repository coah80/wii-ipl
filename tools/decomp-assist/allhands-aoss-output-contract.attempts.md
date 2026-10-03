# AOSS scan-result output-slot contract

Base: bf8ebfa3; 43U. One source line changed in AOSSLink.c.

## Evidence

Both actual callers are in AOSS.c. They declare AOSSi_WLANGetBSSList(void**) and pass &s_accessPointList, whose type is void*. The former definition instead accepted AOSSAccessPointList**, a different cross-translation-unit function type and an incompatible lvalue for publishing through that void* slot.

The definition now accepts void**. Internal list allocation, record types, parsing, callbacks, retries and ownership are unchanged. Assigning the typed internal list to *output now performs the ordinary C object-pointer-to-void* conversion. No AOSS.c/header or protocol change.

The read-only scan audit found no missing behavior: 227/227 instructions, 25 differences explained by real counter/descriptor register allocation plus independent constant/channel-store scheduling. Count and descriptor fields are unsigned halfwords; descriptor length scales by two. Scan capacity is 0x3200 bytes, output records are 84 bytes, and all 12 rate-mask entries fit the 16-byte rate array. Output remains published even if later cleanup/unlock failure changes the return value, as the target and callers require. No missing validation or unused-field initialization was invented.

Call-boundary verification pins actual ABI inputs, not just names or freely renamed registers: WD_Startup consumes flags in r3; WD_GetInfo the info pointer in r3; WD_Scan the scan pointer, buffer and length in r3/r4/r5; NCDUnlockWirelessDriver the saved positive driver ID in r3; the release callback receives 0/buffer/0 in r3/r4/r5. NCDLockWirelessDriver and WD_Cleanup genuinely take no caller arguments. Implementations were inspected, and all nine named AOSS/NCD/WD helper bodies additionally compare exactly with original instructions and resolved relocation destinations.

## Gates

- Baseline configured with the 43U wibo wrapper and built with WIBO_SJIS_MISSING_IMPORTS=1
- Entire AOSSLink.o is byte-identical before/after, including payload, symbols and relocations
- Full-project objdiff reports identical; no matching gain claimed
- Unit remains 99.007286% fuzzy, 12/14 exact functions, 668 exact code bytes, 2432/2432 data bytes
- GetBSSList remains 98.48018%, 227/227 instructions, same 25 differences
- Pool empty and identical; literal audit examines all 14 functions with no candidates/errors/skips (zero string arguments)
- ASan/UBSan host harness uses the extracted production scan/allocation/free functions and actual source structure declarations. Passes 18,825 scenarios: every 12-bit rate mask with all four mode-bit values, 200 variable-length descriptors exactly filling scan capacity, SSID width boundaries, callback/driver/allocation failures, retry limits, cancellation, partial-scan status, publication followed by cleanup/unlock failures, and actual void* output-slot canaries. Expected results and published fields are checked independently
- LeakSanitizer disabled for the execution environment's ptrace restriction; address and undefined-behavior instrumentation remain enabled
- Full build, build/43U/ok and git diff --check pass
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d

Private evidence and reproducible host validator: /tmp/aoss-scan-output-contract. Earlier original disassembly/call evidence remains private in /tmp/aoss-bss-audit.
