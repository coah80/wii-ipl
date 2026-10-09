# cleanup-c3

Baseline `f1db6b656e386063a8bc263fb75a299f36ae4803`, branch `agent/w1009/cleanup-c3`.
Initial full 43U build passed. The live report is 100% matched and linked for code and data.
`DECOMPLETE_OK`; DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

Each trial rebuilds the owned object and compares its sections with the initial object.
Code, data, relocations and symbol records must remain identical. Compiler-generated local literal names and local-static numeric suffixes may change without changing the linked bytes.
Trials changing compiled bytes are restored. Final acceptance requires the four-unit gate and completion checker.
`drawTransferTitles` already uses `nw4r::ut::Color` directly, with no GXColor reinterpret casts or color copy chain.

## Trials
- REVERT `iplSDChannelSelect` remove scoped IRO pragma from void SDChannelSelect::create(): changed sections: .rela.text, .strtab, .symtab, .text.
- REVERT `iplSDChannelSelect` remove scoped IRO pragma from void SDChannelSelect::flushSaveDataAndMountSD(): changed sections: .text.
- REVERT `iplSDMemory` remove scoped IRO pragma from void SDMemory::create(: changed sections: .strtab, .text; .text 21992 -> 21992 bytes, 191 differing bytes.
- REVERT `iplSDChannelTitle` remove scoped IRO pragma from void iplSDChannelTitle_flushSaveBeforeExit: changed sections: .text; .text 19480 -> 19480 bytes, 8 differing bytes.
- REVERT `iplChannelTitle` remove scoped IRO pragma from void ChannelTitle::calcNormalParentalDialog(): changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 5 differing bytes.
- REVERT `iplChannelTitle` remove scoped IRO pragma from void ChannelTitle::calcNormalWaitTmd(): changed sections: .rela.text, .strtab, .symtab, .text; .text 30156 -> 30136 bytes, 13771 differing bytes.
- REVERT `iplChannelTitle` remove scoped IRO pragma from void ChannelTitle::calcNormalUpdating(): changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 12 differing bytes.
- KEEP `iplChannelTitle` remove scoped IRO pragma from void ChannelTitle::getTicketLimitTask: all ELF sections identical.
- REVERT `iplSDMemory` drawTransferTitles remove unused memo-position component copies: changed sections: .rela.text, .strtab, .symtab, .text; .text 21992 -> 21972 bytes, 5289 differing bytes.
- REVERT `iplSDMemory` drawTransferTitles replace component copy chain with VEC3 copy: changed sections: .rela.text, .strtab, .symtab, .text; .text 21992 -> 21996 bytes, 5275 differing bytes.
- REVERT `iplSDMemory` drawTransferTitles replace component copies with VEC3 assignment: changed sections: .strtab.
- KEEP `iplSDMemory` drawTransferTitles VEC3 assignment, allowing harmless local-literal renumbering: code, data, relocations and symbol records identical; local literal names renumbered.
- REVERT `iplSDMemory` onDialogState21 remove zero-length memset: changed sections: .comment, .rela.data, .rela.text, .strtab, .symtab, .text; .text 21992 -> 21976 bytes, 5873 differing bytes.
- REVERT `iplSDMemory` onDialogState21 use typed pointer difference for marker length: changed sections: .rela.text, .strtab, .symtab, .text; .text 21992 -> 21996 bytes, 6116 differing bytes.
- REVERT `iplSDChannelSelect` remove comma operators in drag traversal conditions: changed sections: .strtab.
- REVERT `iplChannelTitle` remove redundant group reference aliases: changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 12 differing bytes.
- REVERT `iplChannelTitle` checkNetSetting replace goto and bool copy with early returns: changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 13 differing bytes.
- REVERT `iplSDChannelTitle` updateMemoryCalc split chained title-range assignment: changed sections: .rela.text, .symtab, .text; .text 19480 -> 19484 bytes, 8220 differing bytes.
- REVERT `iplSDChannelSelect` drag traversal remove comma operators, allowing compiler-local names: changed sections: .strtab.
- REVERT `iplSDChannelSelect` flushSaveDataAndMountSD remove pragma with named save-data receiver: changed sections: .strtab, .text; .text 35264 -> 35264 bytes, 4 differing bytes.
- REVERT `iplSDChannelSelect` flushSaveDataAndMountSD remove pragma with named flush heap: changed sections: .strtab, .text; .text 35264 -> 35264 bytes, 4 differing bytes.
- REVERT `iplSDChannelTitle` flushSaveBeforeExit remove pragma with named page reference: compile failed.
- REVERT `iplSDChannelTitle` flushSaveBeforeExit remove pragma with named page value: changed sections: .strtab, .text; .text 19480 -> 19480 bytes, 8 differing bytes.
- REVERT `iplChannelTitle` calcNormalUpdating remove pragma with named update size: changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 13 differing bytes.
- REVERT `iplChannelTitle` calcNormalUpdating remove pragma with named update offset: changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 12 differing bytes.
- KEEP `iplSDChannelSelect` drag and prepare traversal remove comma operators; normalize local static suffixes: code, data, relocations and symbol records identical; local literal names renumbered.
- REVERT `iplSDChannelTitle` flushSaveBeforeExit remove pragma with correctly typed page reference: changed sections: .strtab, .text; .text 19480 -> 19480 bytes, 8 differing bytes.
- REVERT `iplSDChannelTitle` remove six duplicate helper forward declarations: compile failed.
- REVERT `iplSDChannelTitle` updateMemoryCalc split range copies in destination order: changed sections: .rela.text, .symtab, .text; .text 19480 -> 19484 bytes, 8202 differing bytes.
- REVERT `iplChannelTitle` checkNetSetting remove goto with existing boolean temporaries: changed sections: .rela.text, .strtab, .symtab, .text; .text 30156 -> 30164 bytes, 6831 differing bytes.
- REVERT `iplChannelTitle` calcFadeout replace exit goto with early return: changed sections: .rela.text, .strtab, .symtab, .text; .text 30156 -> 30164 bytes, 19807 differing bytes.
- REVERT `iplChannelTitle` isTimeLimitedChannel express remaining minutes with modulo: changed sections: .rela.text, .symtab, .text; .text 30156 -> 30160 bytes, 3840 differing bytes.
- KEEP `iplSDChannelTitle` remove duplicate helper declarations with declaration-only matching: code, data, relocations and symbol records identical; local literal names renumbered.
- REVERT `iplSDMemory` create remove pragma and declare title-cache locals at use: changed sections: .strtab, .text; .text 21992 -> 21992 bytes, 191 differing bytes.
- REVERT `iplSDChannelSelect` create remove pragma with upfront heap/timing declarations: changed sections: .rela.text, .strtab, .symtab, .text; .text 35264 -> 35260 bytes, 27101 differing bytes.
- REVERT `iplSDChannelSelect` prepare use for-loop list traversal without assignment condition: changed sections: .rela.text, .strtab, .symtab, .text; .text 35264 -> 35276 bytes, 27194 differing bytes.
- REVERT `iplSDChannelSelect` updateChannelObjects use for-loop list traversal without assignment condition: changed sections: .rela.text, .strtab, .symtab, .text; .text 35264 -> 35276 bytes, 13953 differing bytes.
- REVERT `iplSDChannelSelect` calcChannelObjects use for-loop list traversal without assignment condition: changed sections: .rela.text, .strtab, .symtab, .text; .text 35264 -> 35276 bytes, 13788 differing bytes.
- REVERT `iplSDChannelSelect` finishDrag use for-loop list traversal without assignment condition: changed sections: .rela.text, .strtab, .symtab, .text; .text 35264 -> 35276 bytes, 2198 differing bytes.
- REVERT `iplChannelTitle` calcNormalParentalDialog remove pragma with upfront dialog declaration: changed sections: .strtab, .text; .text 30156 -> 30156 bytes, 5 differing bytes.
- REVERT `iplChannelTitle` calcNormalWaitTmd remove pragma with direct ticket-flag initialization: changed sections: .rela.text, .strtab, .symtab, .text; .text 30156 -> 30136 bytes, 13771 differing bytes.
- REVERT `iplSDChannelTitle` updateMemoryCalc copy title range separately into both destinations: changed sections: .strtab, .text; .text 19480 -> 19480 bytes, 7 differing bytes.
- REVERT `iplSDChannelSelect` remove scoped dont_inline pragma: changed sections: .comment, .rela.text, .strtab, .symtab, .text; .text 35264 -> 35256 bytes, 13654 differing bytes.
- REVERT `iplSDChannelSelect` processWorkerCommands replace goto dispatch with structured state guard: changed sections: .rela.data, .rela.text, .strtab, .symtab, .text; .text 35264 -> 35256 bytes, 25748 differing bytes.
- KEEP `iplChannelTitle` remove discarded jokes and commented-out modulo alternative: all ELF sections identical.
- REVERT `iplSDChannelSelect` isChannelReady replace scoped pragma with existing NO_INLINE attribute: changed sections: .comment, .rela.text, .strtab, .symtab, .text; .text 35264 -> 35256 bytes, 13654 differing bytes.
- REVERT `iplSDChannelSelect` flushSaveDataAndMountSD remove pragma with named heap and save receiver: changed sections: .strtab, .text; .text 35264 -> 35264 bytes, 4 differing bytes.
- REVERT `iplSDChannelTitle` flushSaveBeforeExit remove pragma with named heap and save receiver: changed sections: .strtab, .text; .text 19480 -> 19480 bytes, 8 differing bytes.

## Retained cleanup

- `iplSDChannelSelect.cpp`: removed comma operators from all nine channel traversals. Kept the ordinary assignment conditions because for-loop versions added three instructions. Kept both IRO-0 scopes, the drawing-loop no-inline pragma and worker-state dispatch, with concise compiler explanations.
- `iplSDMemory.cpp`: replaced three component copies with `memoPosition = translation`. Colors were already direct `nw4r::ut::Color` values. Kept IRO-1, the zero-length memset call and unsigned marker-address subtraction, with concise compiler explanations.
- `iplSDChannelTitle.cpp`: removed five duplicate forward declarations. Kept IRO-0 and the chained title-range copy, with concise compiler explanations.
- `iplChannelTitle.cpp`: removed the IRO-1 scope from `getTicketLimitTask`, discarded jokes and the commented-out modulo alternative. Kept the other three IRO scopes, group references, shared goto exits and stored-quotient subtraction, with concise compiler explanations.

The first duplicate-declaration regex crossed into a definition and failed compilation; the source was restored and the corrected declaration-only trial passed. The first page-reference trial used `s32&` for an `int&` accessor; the corrected type compiled and still changed bytes.

Final focused object rebuild passed. All four objects have identical code, data, relocations and symbol records versus the initial objects. Only local literal labels and local-static numeric suffixes were renumbered in the first three units; `iplChannelTitle.o` is entirely identical.

Instruction evidence for retained pragmas: SDChannelSelect create loses one BS2-loop instruction without IRO-0; its flush swaps receiver/heap loads. SDMemory create changes its string-base register without IRO-1. SDChannelTitle flush changes the save-manager address register without IRO-0. ChannelTitle parental changes BS2 argument-base registers, TMD waiting loses five instructions, and update progress changes registers without their scopes.

## Final acceptance

`gate.py src/scene/sdChannelSelect/iplSDChannelSelect src/scene/sdChannelMemory/iplSDMemory src/scene/sdChannelTitle/iplSDChannelTitle src/scene/channelTitle/iplChannelTitle --quick` passed.

| Unit | Exact functions before -> after | Matched code | Matched data | Pools |
| --- | --- | --- | --- | --- |
| SDChannelSelect | 129/129 -> 129/129 | 33828/33828 | 2960/2960 | identical |
| SDMemory | 66/66 -> 66/66 | 20872/20872 | 3344/3344 | identical |
| SDChannelTitle | 69/69 -> 69/69 | 18624/18624 | 1976/1976 | identical |
| ChannelTitle | 95/95 -> 95/95 | 28788/28788 | 3144/3144 | identical |

Every owned objdiff section remains 100%. The gate independently found every owned function instruction-exact, 0 regressions, 0 forbidden patterns and 0 readability warnings. A separate comparison against the initial live report also found 0 regressions across all units and exact functions.

Full build passed; refreshed `build/43U/report.json` passed `DECOMPLETE_OK`.
DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
Final gate transcript: `/tmp/cleanup-c3-final-gate.log`.

Source commits: SDChannelSelect `dde666c3`; SDMemory `9c7cd77f`; SDChannelTitle `f5bfa17b`; ChannelTitle `8b101cc3`.
GATE PASS
