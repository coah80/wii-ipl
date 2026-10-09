# o-ifl2 attempts: tiInputForm `.sdata2` data match

Worktree data-d4, branch agent/w1009/o-ifl2, base da267147 (tiInputForm linked, #1332).
Start: `.sdata2` 96.15%, unit data 3668/3772, global matched data 99.99432%.

## What the stripped constant is

- The original TU compiled `nw4r::lyt::TextBox::GetTextColor` (inline, `NW4R_ASSERT` -> OSFatal):
  `LayoutByNW4R::create` calls it out of line (target reloc at .text 0x9ef0), and its weak
  `@STRING@GetTextColor__Q34nw4r3lyt7TextBoxCFUl` (the Error#004 message, 0x41) sits in this unit's
  `.data` at 0x8165D28C. The linker kept RsoSystem's copy (0x8135A4C0, earlier in link order) and
  dropped this one along with its `{255,255,255,0}` front-color literal in `.sdata2`.
- So the weak instantiation is correct. Removing it would drop 0x41 bytes from `.data`.
- dtk 1.7.5 `stripped` cannot describe it: the flag exists for common-BSS matching, and stripped
  symbols "don't actually exist at the address" and are filtered out of splits. The split `.sdata2`
  is the 104 DOL bytes; nothing can add the 4 stripped bytes.

## Why objdiff scored 96%

objdiff 3.4.5 `diff_data_section` takes the better of a byte diff of the section (100 vs 108 bytes
here: the extra literal plus 4 bytes of double alignment -> 200/208 = 96.15%) and symbol pairing.
Compiler literals (`@N`) pair by value. The target's `.sdata2` symbols were the invented
`scInputForm*` names from #626 (they matched dummy named constants that #1332 removed), so nothing
paired and the byte diff decided. RsoSystem's object also carries an extra literal (`@17197`, 0.0f,
ahead of `scRsoZeroF`) and scores 100% the same way: its target symbol pairs.

## Fix

`config/43U/symbols.txt` 0x81694D28-0x81694D90: the 25 `scInputForm*` entries become the 22
anonymous literals the source emits (`@N`, `scope:local`, project convention for 655 `.sdata2`
entries). The four one-byte `scInputFormColor*U8` entries are one 4-byte object: `drawCursor`'s
`GXColor color = {255, 50, 50, 0}` initializer (4 lbz at +0..+3). Numbers are from the current
compile. objdiff ignores them for pairing.

Result: `.sdata2` 100%, unit data 3772/3772, 221/221 exact, DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d, gate PASS with 0 regressions, global matched data 100%.
No source change.
