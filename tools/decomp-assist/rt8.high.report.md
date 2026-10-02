# rt8 HIGH report

Final full gate: GATE PASS. Full 43U build passed, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, zero regressions and zero forbidden/readability additions. Final gate output is rt8.high.final-gate.txt.

Before -> after:
- MemoryCardManager instruction-exact18->18, objdiff code2572->2572/5396, data absent.
- RakuRakuThread instruction-exact12->14, objdiff code1252->2168/2168, data456->456/456.
- tiCandidateBox gate instruction-exact108->108, objdiff exact109->109, code19988->19988/24000, data4652->4652/4652.

Remaining functions:
- isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | 99.830505% | two commuted address-add operands
- isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | 99.830505% | two commuted address-add operands
- isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | 92.30769% | epilogue setup scheduled before flag load
- update_file_array__Q33ipl5scene17MemoryCardManagerFUc | 99.72222% | four command/address register substitutions
- _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | 87.55% | texture-base lifetimes, address operands and register allocation
- getComment__Q33ipl5scene17MemoryCardManagerFUcsi | 98.94309% | comment/trim pointer register allocation
- create_banner__Q33ipl5scene17MemoryCardManagerFUcs | 90.42453% | render address lifetimes and register allocation
- getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | 92.0% | epilogue setup scheduled before size load
- create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | 92.71023% | inlined initialization loop and pane-name lifetimes
- createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | 96.56481% | descriptor reloads and constructor register allocation
- CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | 99.873566% | eleven forward-width f2/f3 substitutions

Matched this round:
- start__Q33ipl5scene14RakuRakuThreadFv: separate progress and configuration objects restore compiler BSS pooling,96/96 instructions,diffs0.
- finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi: structured finish guard and typed inline privacy copy restore133/133 instructions,diffs0.

Data proof: previous F4-byte sRakuStatus bundled12-byte progress with adjacent232-byte configuration. Target callback copy/clear and result/clear API arguments prove separate C/E8 objects at unchanged810BDDE0/810BDDEC. Combined byte ownership and BSS section0x128 remain unchanged. Both functions and all data now match fully.

Commits: d408dadb,14b52bf2.
Retained implementation files: src/scene/setting/iplRakuRakuThread.cpp, config/43U/symbols.txt.
Verification files: rt8.attempts.md,rt8.high.raku13-gate.txt,rt8.high.raku14-gate.txt,rt8.high.final-gate.txt.

Measurement caveat: gate reports candidatebox108/112 while objdiff reports109/112. onGUIEvent raw1800bytes are identical; odiff treats a condition-register operand as a branch target and subtracts different function starts. Tools were not changed.
All remaining functions have at least three distinct compiled HIGH attempts recorded in rt8.attempts.md.
