# SDChannelObj matching attempts

All 38 target functions are implemented in address order. No configure or symbol changes.
The string pool is identical. The .data and .rodata sections match completely.

## iplSDChannelObj_813E3580

- Initial translation of ChannelObj::setLangPane: 182 instructions, 112 instruction diffs. Fixed language-name storage from flat byte indices to 10 four-byte entries and changed the Rso name buffer to eight bytes. This also fixes the fallback comparison to select a four-byte language entry.
- Removed the cached fallback group-name local: 182 instructions, 37 diffs. Giving the region table external linkage did not change these diffs; restored internal linkage.
- Explicit region-name and language-index pointer locals: 182 instructions, 40 diffs. Restored indexed table accesses.
- Restored the target's breaks after selecting a fallback group and at its NULL terminator: 182 instructions, four diffs, only r27 versus r29 for the selected group.
- One common Group pointer declared before the language scan: same four register diffs.
- Reused that Group pointer while traversing the first list: 181 instructions and additional frame/register diffs. Restored iterator accesses and locally scoped Group pointers.
- Final retained form: 182/182 instructions, four register-allocation differences at indices 103, 115, 149, 161. No artificial register coercion.

## Resolved functions

- iplSDChannelObj_813E4060: initial 54/55 instructions; changed the language sentinel to unsigned for the target addis/cmplwi pair. This left eight register diffs. Removed the language temporary and indexed the lookup directly: 55/55 instructions, zero diffs.
- iplSDChannelObj_813E4A54: initial 90/90 instructions with ten scheduling diffs. Computed the title code before querying the NWC24 manager: 90/90 instructions, zero diffs.
- The other functions matched on their first literal implementation from target assembly and corresponding ChannelObj routines.

## Measurement caveats

- iplSDChannelObj_813E3E38 is 100% in objdiff. Gate/ctxdiff reports three instruction differences because odiff.dis treats the first operand of a cr1 branch as its target and subtracts the function's object offset. The actual instruction words at indices 11, 21, 22 are identical: 41860014, 41860010, 40840014. Both objects have identical call relocation positions and targets. No tool changes were made.
- .sdata2 was fixed by representing the unknown title as an ordinary const wchar_t array, rather than a pointer to a wide string literal.
- Original .sdata additionally contains B_BtnA and B_BtnB beyond the New group literals. No owned text relocation references those two strings. Their source ownership is uncertain; they were not recreated as unreferenced data just to increase the section score.
