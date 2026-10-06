# OSNet dead NWC24 functions (grok-osnet)

Target object keeps only __OSInitNet and __OSSyncTimeWithNetRM. The eight fossil strings are the caller names and paths from the SDK shutdown/scheduler/rtc helpers. RevoEX already defines NWC24iPrepareShutdown, NWC24SuspendScheduler, and NWC24ResumeScheduler, so those three are weak here and the linker keeps the RevoEX copies.

- Full zeldaret bodies, including CheckCallingStatus's "Illegal status..." report: pool diverged (extra string, and IPA inlined the helpers into __OSInitNet).
- never_inline on the definition only: still inlined. MWCC uses the first declaration. Prototypes with NO_INLINE before private/nwc24.h stop the inline. __OSInitNet 0xb4/0xb4 differing 0, __OSSyncTimeWithNetRM 0x8/0x8 differing 0. Pool identical, 11 strings.
- Strong definitions: link failed, multiply-defined against NWC24System.o and NWC24Schedule.o.
- DECL_WEAK on those three: link succeeded. main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
