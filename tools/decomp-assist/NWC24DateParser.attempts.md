# NWC24DateParser matching attempts

Baseline: no source; 0/8 exact functions, 0/2372 code, 0/40 data.
Initial readable C reference in /tmp was checked against target assembly.
Calendar fields reuse NWC24Date and OSCalendarTime. Month-length and
year-day tables follow original .rodata order, with all 40 bytes identical.
Epoch conversion adds 2208988800 seconds before clamping, as in the target.
The stack date workspace reproduces calendar conversion aliasing and offsets.

## Source attempts

NWC24iEpochSecondsToDate | clamp epoch after signed epoch offset addition | (100.0, 0) | src 0x13c base 0x13c insns 79/79
NWC24iMinutesToOSCalendarTime | calendar conversion uses date structure workspace | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24DateParser.o
NWC24iMinutesToOSCalendarTime | workspace and byte leap flag | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24DateParser.o
NWC24iMinutesToOSCalendarTime | workspace with leap flag declared before date | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24DateParser.o
NWC24iDateToOSCalendarTime | explicit local year before leap flag | (96.588234, -19) | src 0x154 base 0x154 insns 85/85
NWC24iDateToOSCalendarTime | byte leap flag | (99.17647, -13) | src 0x154 base 0x154 insns 85/85
NWC24iDateToOSCalendarTime | leap flag initialized at declaration | (99.17647, -13) | src 0x154 base 0x154 insns 85/85
ConvertDateToDays | shared non-leap day validation and leap-year predicate | (83.07079, -21) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | signed leap flag with reordered annual sum | (83.07079, -21) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | unsigned leap flag and shared validation | (83.07079, -21) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDaysToDate | subtract annual and monthly spans before testing remaining days | (79.32039, -9999) | src 0x178 base 0x19c insns 94/103
ConvertDaysToDate | annual leap result stored in byte | (79.32039, -9999) | src 0x178 base 0x19c insns 94/103
ConvertDaysToDate | cache signed current year | (79.32039, -9999) | src 0x178 base 0x19c insns 94/103
NWC24iMinutesToOSCalendarTime | date structure workspace with named calendar fields | (100.0, 0) | src 0x1d8 base 0x1d8 insns 118/118
ConvertDateToDays | subtract one from day before adding month prefix | (83.07079, -21) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | annual sum before leap correction | (90.33628, -21) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | annual base computed in named temporary | (90.33628, -21) | src 0x1c4 base 0x1c4 insns 113/113
NWC24iMinutesToOSCalendarTime | shared leap-year predicate | (93.05085, -9999) | src 0x1e8 base 0x1d8 insns 122/118
NWC24iDateToOSCalendarTime | shared leap-year predicate | (94.329414, -9999) | src 0x164 base 0x154 insns 89/85
ConvertDateToDays | shared leap-year predicate | (90.33628, -21) | src 0x1c4 base 0x1c4 insns 113/113
NWC24iDateToOSCalendarTime | cache year after leap flag initialization | (99.17647, -13) | src 0x154 base 0x154 insns 85/85
NWC24iDateToOSCalendarTime | leap check through shared year helper | (94.329414, -9999) | src 0x164 base 0x154 insns 89/85
NWC24iDateToOSCalendarTime | leap result assigned after calendar stores | (94.44706, -9999) | src 0x158 base 0x154 insns 86/85
ConvertDateToDays | day offset prepared before month table access | (90.95575, -18) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | annual day and leap counts use independent temporaries | (95.02655, -19) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDateToDays | annual days calculated before leap century count | (95.02655, -19) | src 0x1c4 base 0x1c4 insns 113/113
ConvertDaysToDate | monthly leap flag materialized before subtraction | (86.35922, -9999) | src 0x1a8 base 0x19c insns 106/103
ConvertDaysToDate | annual leap calculation uses year helper | (75.23301, -9999) | src 0x168 base 0x19c insns 90/103
ConvertDaysToDate | monthly and annual named leap predicates | (82.31068, -9999) | src 0x198 base 0x19c insns 102/103

## Remaining functions

NWC24iDateToOSCalendarTime, 99.17647%: 85/85 instructions; thirteen differences exchanging year and leap-flag registers.
ConvertDateToDays, 95.02655%: 113/113 instructions; nineteen differences in month-prefix addition and annual arithmetic scheduling.
ConvertDaysToDate, 86.35922%: 106/103 instructions; annual/monthly leap branches and register allocation differ.
