# opus-sections: remove section-placement / padding tricks

## 1. iplCSPane.cpp (scCsFatalColorR/G/B/A)
- plain non-const u8 x4: A (= 0) moves to .sbss -> rejected.
- local `GXColor front = {0xff,0xff,0xff,0}`: emitted as anonymous const in .sdata2 -> rejected.
- non-const global `GXColor scCsFatalColor = {0xff,0xff,0xff,0}` copied in the assert macro:
  every section byte-identical to baseline, same lbz x4 / stb x4 copy. The four 1-byte
  symbols were a split artefact; symbols.txt now has one 4-byte scCsFatalColor. SetTextColor 0/52, pool identical. ACCEPTED.

## 2. tiInputForm.cpp (const_type/data_type pragma blocks) - PARTIAL
- scP_/scN_/scT_ strings and csButtonAnimations made non-const: they stay in .data on their own
  (csButtonAnimations also becomes global, as in the target). csAninationFile/VisiblePanes/LanguagePaneData
  /pppURLCheck are const and land in .rodata with no pragma.
- csVisiblePaneCHN was `const void*[10]` (non-const array of pointers -> .data); now `const void* const[10]`.
- Left: the 32-byte DeadKeyStream::isCompatible table (@6599, .data). Target copies it to the stack
  every iteration (frame 0x100, lhz/sth x16), so it is a local array initializer image. Tried:
  non-const local (.rodata), local `= L"..."` const and non-const (.rodata), file-scope `wchar_t*`
  literal (pointer emitted in .sdata2, code changes), file-scope non-const static array (.data ok
  but no stack copy, onCommand -240 bytes, onSpaceKeyHWKB -240 bytes), static const local (.rodata),
  probe file on GC 1.0a..3.0a5.2 and Wii 0x4201_127..1.7: local initializer images always go to
  .rodata. Kept one narrow `#pragma section const_type ".data"` around isCompatible only.
- Object identical to baseline except csButtonAnimations binding L->G (matches target). Pool identical.

## 3. iplButton.cpp (scPaneName_B_Stop declspec)
- Definition is `char scPaneName_B_Stop[] = "B_Stop"` in iplFocusObject.cpp (7 bytes, .sdata). The
  unsized extern made MWCC use lis/addi; declaring `extern char scPaneName_B_Stop[7];` gives the sda21
  access on its own. Object identical to baseline. ACCEPTED.

## 4. RsoSystem.cpp (rso_data_pad_*, scRsoFatalMsg/scRsoZeroF declspecs)
- The 7 zero bytes after scRsoFatalMsg (0x41..0x48) have no owner: .data is 8-aligned and the next
  unit's .data starts on 8, so dtk folds the alignment gap into this split. Removing the pads gives a
  65-byte .data; objdiff still reports .data 72/72, unit data 96/96, complete.
- scRsoFatalMsg is non-const `char[]` (like scCsFatalMsg) and lands in .data on its own;
  scRsoZeroF is a plain const f32 and lands in .sdata2 on its own. Sections otherwise identical. ACCEPTED.

## 5. tiPredictLang.cpp (tiPredictLang_rodata_pad)
- The .rodata word after csAninationFile (9 x 0x44 = 0x264) is the 8-byte alignment gap before the
  next unit; dtk had sized the symbol 0x268 to cover it. Pad removed, symbols.txt size set to 0x264.
  Unit data 2300/2300, .rodata 100%, pool identical. ACCEPTED.
