# AOSS WLAN connection argument contract

Base 9c7d87ab, 43U. This correction is separate from the key-material representation work.

AOSSConnectAndAwaitHost receives settings and config pointers but previously called AOSSi_WLANConnect through a false no-argument declaration. The actual callee takes a connection record and status output. In the original caller, incoming r3/r4 are forwarded untouched to the first call; the callee preserves r3/r4 and consumes both. The compiler happened to retain the same register contents despite the missing source arguments, hiding this defect behind exact generated code.

The local declaration now uses forward-declared struct AOSSConnection and struct AOSSConnectionStatus, matching the existing tags in AOSSLink.c. The wrapper explicitly passes settings and config. No shared header or AOSSLink.c edit. All three original outer callsites supply r3 = sp+0xb8 (settings) and r4 = s_accessPointConfig, matching the source caller expressions. No arguments are reordered or synthesized.

Validation:
- Configured/built 43U using the approved wibo wrapper and WIBO_SJIS_MISSING_IMPORTS=1
- AOSSConnectAndAwaitHost remains 60/60 instructions, ctxdiff zero
- Every code/data/relocation section, section header, and symbol record is byte-identical to baseline; only five compiler-generated anonymous local symbol spellings change in .strtab
- Full-project objdiff report unchanged: AOSS unit 97.71665% fuzzy, 16/21 exact, 6436 exact code bytes and 3928/3928 data bytes; no matching gain claimed
- Pool identical, 1/1 strings; literal audit checks 12 arguments across 19 functions, no candidates/errors; AOSS_Init_old and AOSSSendHelloRequest are skipped for their existing unequal sizes
- ASan/UBSan extracted-production wrapper harness passes 30,600 cases, asserting actual typed callee pointer identities, driver/startup failures, host readiness, cancellation, all retry boundaries and the original timeout behavior (cleanup and status clear, then return zero). No network calls occur; platform functions are controlled stubs
- LeakSanitizer disabled for ptrace restriction; address/undefined instrumentation enabled
- Full 43U build and ok gate pass; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

Private reproducible evidence: /tmp/aoss-key-call-contracts, with original caller/callee disassembly retained privately under /tmp/aoss-decrypt-audit.
