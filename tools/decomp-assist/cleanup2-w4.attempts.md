# cleanup2-w4 attempts

Scope: NWC24MsgSubject.c, nup.cpp, nup_nhttp.cpp, WDScan.c.
Baseline: 85d653b0, clean branch agent/w1009/cleanup2-w4.
Read cleanup-common.md, including wave-2 goto/comma guidance, AGENTS.md, unslop, graphify, and writing-for-agents.
Initial full 43U build passed; DECOMPLETE_OK; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
All four units are Matching with every code/data section at 100%.
Keep common error/cleanup exits; test each structural cleanup separately and restore any byte-changing trial.
Earlier cleanup logs contain no attempts for these four files.

## Trials

- REVERT `nup.cpp`: remove __nupSetAuditState dont_inline pragmas. sections ['.data', '.text'], relocations ['.text'], functions ['__nupOp size 1844/1752', '__nupSetAuditState__FUc missing']
- REVERT `nup.cpp`: remove __nupGetTmdView dont_inline pragmas. sections ['.text'], relocations ['.text'], functions ['__nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion size 752/652', '__nupGetTmdView__FUxPP9ESTmdView missing', '__nupOp size 1952/1752']
- REVERT `WDScan.c`: replace nine volatile access macros with definition-level volatile const. sections ['.sdata', '.sbss', '.sbss2', '.text', '.sdata2'], relocations ['.text'], functions ['WDGetPrivacyMode size 468/460']
- REVERT `WDScan.c`: WDCheckEnableChannel structured driver error returns. sections ['.text'], relocations ['.text'], functions ['WDCheckEnableChannel size 652/656']
- REVERT `WDScan.c`: WDScanOnce structured driver error returns. sections ['.text'], relocations ['.text'], functions ['WDScanOnce size 644/648']
- KEEP `nup.cpp`: NUP_Init split comma assignment into two statements. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `nup.cpp`: __nupHasContent remove assignment within dereference. sections [], relocations ['.text'], functions []
- REVERT `nup.cpp`: __nupHasInstalledContent remove assignment within dereference. sections [], relocations ['.text'], functions []
- REVERT `nup.cpp`: NUP_Start remove unreachable status alternatives. sections ['.text'], relocations ['.text'], functions ['NUP_Start size 448/508']
- REVERT `nup.cpp`: __nupCleanup remove redundant nested title null test. sections ['.text'], relocations ['.text'], functions ['__nupCleanup__FP14NUPContextInfo size 272/276']
- REVERT `nup.cpp`: __nupGetBoot2Version use else for successful narrowing. sections [], relocations ['.text'], functions []
- KEEP `nup.cpp`: remove redundant casts of typed tmdView pointers. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `nup_nhttp.cpp`: __nupNhttpBufFull replace pointer switch with null check. sections ['.text'], relocations ['.text'], functions ['__nupNhttpBufFull size 384/388']
- REVERT `nup_nhttp.cpp`: __nupNhttpOp remove goto immediately before cleanup label. sections [], relocations ['.text'], functions []
- REVERT `WDScan.c`: WDCheckEnableChannel structured success branch before NCD failure return. sections ['.text'], relocations ['.text'], functions ['WDCheckEnableChannel size 652/656']
- REVERT `WDScan.c`: WDScanOnce structured success branch before NCD failure return. sections ['.text'], relocations ['.text'], functions ['WDScanOnce size 644/648']

Relocation comparison correction: MWCC renumbers internal string symbols when tokens change. Compare defined relocation symbols by section and offset, and undefined symbols by name; revisit the four trials whose only difference was an internal relocation symbol name.

- KEEP `nup.cpp`: __nupHasContent remove assignment within dereference. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `nup.cpp`: __nupHasInstalledContent remove assignment within dereference. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `nup.cpp`: NUP_Start remove unreachable status alternatives. sections ['.text'], relocations ['.text'], functions ['NUP_Start size 448/508']
- REVERT `nup.cpp`: __nupCleanup remove redundant nested title null test. sections ['.text'], relocations ['.text'], functions ['__nupCleanup__FP14NUPContextInfo size 272/276']
- KEEP `nup.cpp`: __nupGetBoot2Version use else for successful narrowing. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `nup_nhttp.cpp`: __nupNhttpBufFull replace pointer switch with null check. sections ['.text'], relocations ['.text'], functions ['__nupNhttpBufFull size 384/388']
- KEEP `nup_nhttp.cpp`: __nupNhttpOp remove goto immediately before cleanup label. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `WDScan.c`: WDCheckEnableChannel structured success branch before NCD failure return. sections ['.text'], relocations ['.text'], functions ['WDCheckEnableChannel size 652/656']
- REVERT `WDScan.c`: WDScanOnce structured success branch before NCD failure return. sections ['.text'], relocations ['.text'], functions ['WDScanOnce size 644/648']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertToInternalEncoding replace error dispatch gotos with structured conditions. sections ['.text'], relocations ['.text'], functions ['NWC24iConvertToInternalEncoding size 392/388']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertToInternalEncoding replace error dispatch gotos with enum switch. sections ['.text'], relocations [], functions ['NWC24iConvertToInternalEncoding diffs 7/97']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertFromInternalEncoding replace error dispatch gotos with structured conditions. sections ['.text'], relocations ['.text'], functions ['NWC24iConvertFromInternalEncoding size 404/400']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertFromInternalEncoding replace error dispatch gotos with enum switch. sections ['.text'], relocations [], functions ['NWC24iConvertFromInternalEncoding diffs 7/100']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertToInternalEncoding separate encoding setup assignments from condition. sections ['.text'], relocations [], functions ['NWC24iConvertToInternalEncoding diffs 4/97']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertFromInternalEncoding separate encoding setup assignments from condition. sections ['.text'], relocations [], functions ['NWC24iConvertFromInternalEncoding diffs 4/100']
- KEEP `NWC24MsgSubject.c`: use existing encoding-region enum names. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `WDScan.c`: WDGetPrivacyMode structure RSN cipher dispatch as switch. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `WDScan.c`: WDGetPrivacyMode structure WPA cipher dispatch and fallback as switch. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `WDScan.c`: remove OUI volatile access macros and use plain constants. sections ['.text'], relocations ['.text'], functions ['WDGetPrivacyMode size 468/460']
- KEEP `WDScan.c`: WDCheckEnableChannel place NCD failure else before shared WD result dispatch. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `WDScan.c`: WDScanOnce place NCD failure else before shared WD result dispatch. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `nup_nhttp.cpp`: __nupNhttpOp split header parsing assignments from loop condition. sections ['.text'], relocations ['.text'], functions ['__nupNhttpOp__FPc14NHTTPReqMethodPcPUcUlUlPFPvUl_vPvPFPUcUlUlPv_lPv diffs 84/348']
- REVERT `nup.cpp`: __nupFindTag separate tag searches from null tests. sections ['.text'], relocations ['.text'], functions ['__nupParseServerInfo__FP14NUPContextInfoPcPcUx size 1984/1808']
- REVERT `nup.cpp`: __nupParseServerInfo split counting loop assignments. sections ['.text'], relocations ['.text'], functions ['__nupParseServerInfo__FP14NUPContextInfoPcPcUx diffs 39/452']
- REVERT `nup.cpp`: __nupParseServerInfo split title parsing loop assignments. sections ['.text'], relocations ['.text'], functions ['__nupParseServerInfo__FP14NUPContextInfoPcPcUx diffs 86/452']
- KEEP `NWC24MsgSubject.c`: NWC24iConvertToInternalEncoding enum switch with original result-block order. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `NWC24MsgSubject.c`: NWC24iConvertFromInternalEncoding enum switch with original result-block order. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `NWC24MsgSubject.c`: NWC24SetMsgSubjectPublic simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24SetMsgSubjectPublic size 452/456']
- REVERT `NWC24MsgSubject.c`: NWC24SetMsgSubjectAndTextPublic simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24SetMsgSubjectAndTextPublic size 748/760']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertToInternalEncoding simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24iConvertToInternalEncoding size 384/388']
- REVERT `NWC24MsgSubject.c`: NWC24iConvertFromInternalEncoding simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24iConvertFromInternalEncoding size 396/400']
- REVERT `NWC24MsgSubject.c`: NWC24iSetMsgSubjectQP simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24iSetMsgSubjectQP size 572/576']
- REVERT `NWC24MsgSubject.c`: NWC24iSetMsgSubjectBase64 simplify success-only switch to error guard. sections ['.text'], relocations ['.text'], functions ['NWC24iSetMsgSubjectBase64 size 536/544']
- REVERT `NWC24MsgSubject.c`: combine while-loop cleanup with removal of the input cast. MWCC rejects conversion from const unsigned char pointer to unsigned char pointer because NWC24EncodeWord takes mutable input. Restored; retested the loop alone below.

- KEEP `NWC24MsgSubject.c`: NWC24iSetMsgSubjectQP use while loop. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `NWC24MsgSubject.c`: NWC24iSetMsgSubjectBase64 use while loop. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `NWC24MsgSubject.c`: NWC24iSetMsgSubjectBase64 remove unnecessary const qualification and casts. sections ['.text'], relocations [], functions ['NWC24iSetMsgSubjectBase64 diffs 5/136']
- REVERT `nup_nhttp.cpp`: __nupNhttpOpString remove NO_INLINE forward declaration. sections ['.text'], relocations ['.text'], functions ['__nupHttpGetFull__FPcPPUcPUlUlPFPvUl_vPv size 220/76', '__nupHttpPostFull__FPcPcPcPPUcPUlUlPFPvUl_vPv size 284/172', '__nupNhttpOpString__FPPUcPUlPc14NHTTPReqMethodPcPUcUlUlPFPvUl_vPv missing']
- KEEP `WDScan.c`: WDCheckEnableChannel rename result2 to infoResult. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `WDScan.c`: WDScanOnce rename result2 to scanResult. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `NWC24MsgSubject.c`: NWC24iGetDefaultCharset replace case exit gotos with break. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `nup.cpp`: remove parentheses left by typed tmdView cast cleanup. All allocated sections, function bytes, and relocations equal baseline.
- KEEP `NWC24MsgSubject.c`: use existing charset and transfer-encoding enum names. All allocated sections, function bytes, and relocations equal baseline.
- REVERT `WDScan.c`: remove WPA small-data section pragma. sections ['.sdata2', '.sdata'], relocations ['.text'], functions []
- KEEP `WDScan.c`: WDGetPrivacyMode remove redundant signed casts in cipher switches. All allocated sections, function bytes, and relocations equal baseline.

## Final changes and retained requirements

- NWC24MsgSubject.c: replaced both ENC error-dispatch ladders with enum switches in the original result-block order, replaced default-charset case gotos with breaks, replaced two empty-clause for loops with while loops, and used existing region/charset/transfer-encoding enums. Common error exits stay. Success-only switches, short-circuit ENC setup, and the const Base64 input alias stay because their alternatives change instructions; each has a one-line compiler note.
- nup.cpp: removed the initializer comma expression and both pointer-assignment expressions, removed redundant typed-pointer casts, and used an else branch for boot-version narrowing. Both dont_inline regions stay because removal inlines the helpers and changes their callers. Tag searches stay in short-circuit conditions; standalone statements change register allocation. The title null check and negative-status alternatives stay because removal shrinks the object. Retained requirements have one-line compiler notes.
- nup_nhttp.cpp: removed the jump immediately before the cleanup label. Common cleanup gotos stay. The buffer-allocation pointer switch, header-condition assignments, and NO_INLINE declaration stay because removal changes instruction counts or caller allocation; each has a one-line compiler note.
- WDScan.c: replaced driver-error jumps with structured branches and both privacy-mode ladders with switches; renamed operation result locals and removed redundant switch casts. All gotos removed. The OUI access macros and WPA .sdata pragma stay because changing volatility or placement changes instructions or relocations; both have one-line compiler notes.

Object verification compares every allocated section and function against the initial exact object, with defined relocation symbols normalized to section/offset and undefined symbols compared by name. Final objects equal that baseline.

## Gate retry

The first final gate built successfully, kept the DOL hash, found all 49 functions instruction-exact, all owned sections at 100%, and 0 regressions. Its forbidden-pattern scanner treated the phrase "register allocation" in three block comments as a register-keyword source addition. Reworded only those comments to "instruction order" and reran the required gate.

## Final verification

Final gate command used all four owned units with --quick, as cleanup-common.md requests.
- Full 43U build: passed.
- NWC24MsgSubject: 12/12 instruction-exact functions; code 5352/5352; data 232/232.
- nup: 23/23 instruction-exact functions; code 10764/10764; data 1720/1720.
- nup_nhttp: 9/9 instruction-exact functions; code 2588/2588; data 144/144.
- WDScan: 5/5 instruction-exact functions; code 2180/2180; data 16/16.
- Every owned section: 100%; all pools identical; 0 regressions; 0 forbidden additions; 0 readability warnings.
- Focused ctxdiff checks: conversion helpers 97/97 and 100/100, default charset 75/75, NUP_Init 34/34, HTTP operation 348/348, driver helpers 164/164 and 162/162, privacy mode 115/115; every check reports diffs 0.
- Gotos removed: NWC24MsgSubject 31, nup_nhttp 1, WDScan 23; nup keeps common error exits.
- Refreshed build/43U/report.json; DECOMPLETE_OK.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- git diff --check: passed.

GATE PASS

Source commits: 72d86af3, c0446e2b, 12b1f54a, 0c2ba030.
Compiler-note wording fixes: 87b8b348, 465f5d83.
