# zi8cinfo attempts

Baseline source was absent. All ten functions are implemented in object order.
Nine functions have objdiff 100.0 and ctxdiff diffs 0. All 1,848 data bytes match.
No shared headers or other units were changed.

## Zi8GetSInfo, still open

- Separate count decrement followed by the zero store: 99.09775, 133/133 instructions. Only instructions 43 and 44 are swapped. Retained this version.
- Prefix decrement inside the output index: 98.42105, 131/133 instructions. Constant loading moves before the decrement, but extraCount moves from the stack to r25, removing its store/load pair.
- Assign count minus one inside the index: 98.270676 with an 8-bit count. Adds truncation of the assigned count and still moves extraCount into r25. With an int count: 98.42105.
- Post-decrement minus one inside the index: 96.729324, worse indexing and register allocation.
- Named last-index temporary: 97.89474, additional indexing/register differences.
- Changing local declaration order with prefix decrement, three orders: all 98.42105. Does not restore extraCount's stack allocation.
- Unsigned extraCount with a signed loop-bound cast: 98.42105. Same unwanted r25 allocation.
- Comma expression in the output index: 97.14286. Rejected.
- Store at count minus one, then decrement count: 99.172935, 134/133 instructions. Duplicates the decrement for address calculation and count maintenance. Rejected despite the higher fuzzy score.

The retained code emits `addi r30,r30,-1; li r3,0`, while the target emits
`li r3,0; addi r30,r30,-1`. No register, volatile, assembly, or pragma hints used.

## Functions resolved

- Zi8GetCJInfo: first reconstruction 99.888885 with two differences. Separating the initial shift caused 12 register differences. Keeping the packed assignment within its shift expression reached 100.0, 90/90 instructions. A later typed-work/separate-shift alternative produced 14 register differences and was rejected.
- Zi8GetPInfo: first reconstruction 67.7494. Using an int output count, ordinary indexed stores, post-increment for multi-character spellings, source-order initial cases, and a tone switch reached 100.0, 830/830 instructions.
- Zi8GetZInfo: initial reconstruction reached 100.0, 765/765 instructions.
- zi8StrokeCode: initial switch reached 100.0, 53/53 instructions.
- Zi81KeyPYinfo: initial switch reached 100.0, 120/120 instructions.
- Zi81KeyZYinfo: initial switch reached 100.0, 153/153 instructions.
- Zi8GetCharInfo: wrapper reached 100.0, 21/21 instructions.
- ZiCharInfo2: initial reconstruction 37.02924. Moving normalization ahead of the general lookup and reconstructing table operations reached 80.38596. Initializing the phonetic-table pointer gave 80.37622. Reconstructing the alternate-search loop, element loop, record fields, and shared normalization block gave 92.70565. Using the actual normalization switch cases and returning from that block gave 97.38012. Separating table lookup from Zi8GetPCode gave 99.48538 and the correct register allocation. Reordering real local declarations and correcting 16-bit byte promotions gave 100.0, 513/513 instructions.
- Zi8GetCharInfo2: initial reconstruction 97.9661. A word-sized result/return gave 98.98305 with only work/state registers swapped. Swapping local declarations and initializing the saved state at declaration left 98.98305. A separate work pointer gave 96.52542; a word-sized saved state gave 97.28814. Giving the work argument its real struct-pointer type resolved the allocation tie: 100.0, 59/59 instructions.

## Linking investigation

Temporarily changed only zi8cinfo to Matching and built main.dol. The result was
3,867,904 bytes, the same as the original. SHA1 was
e216152519ae06ed2d325eefaa60d96030dbf381.

Exactly eight bytes differed, all within Zi8GetSInfo:

| DOL file offset | Original word | Rebuilt word |
| --- | --- | --- |
| 0x1486d8 | 38600000 | 3bdeffff |
| 0x1486dc | 3bdeffff | 38600000 |

unitaudit.py reported no address steps or internal layout disagreements.
`nm -n` showed identical function offsets and jump-table offsets; only compiler
local-symbol names differed. Restored NonMatching because the DOL was not exact.

## Validation baseline and type notes

The default gate cannot pass because baseline-a620eec6.json is absent. Used
`--base 5cdca2e8`, the immediate ancestor with an existing immutable baseline.
This baseline records zero exact functions, zero matched code bytes, and zero
matched data bytes for this unit. No baseline files were written or modified.

The existing public header declares Zi8GetCharInfo2's result as ziU8. This unit
uses a word-sized internal declaration/definition, as required by the observed
untruncated return and callers inside this object. Results remain character
counts within the byte range; the shared public header remains unchanged.
ZiInfoWork names the accessed fields at 0x16 and 0x18; prefix-field names do not
claim that the full work-data structure has been independently decompiled.
