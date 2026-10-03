# Card thread entry contract

Base: `be7ded2fdc4ebba0b87695a132905e38e7f984df`.
Owned source: `src/scene/cardSequence/iplCardSequence.cpp` only.

## Retained source correction

Give `cardThreadMain` its unused `void*` entry parameter in both its declaration
and definition, and remove the function-pointer cast at `OSCreateThread`.
The unnamed parameter follows the existing unused-parameter style in this unit.
The function body and registration arguments are unchanged.

`OSCreateThread` declares its entry as `void* (*)(void*)`. The previous C++
`void* cardThreadMain()` declaration describes a different function type;
its explicit cast hid that mismatch. A C++98 direct-binding compile check rejects
the previous declaration and accepts the corrected declaration. This is a source
interface correction. No runtime sanitizer diagnosis or fuzzy improvement is
claimed: the SDK launches the entry by restoring a machine context.

## Original-machine contract

- The original `initCardThread` is at `0x813D2660`, 668 bytes. Its call to
  `OSCreateThread` at `0x813D28B0` passes entry `0x813D2C8C` in r4 and null in r5.
- Original `OSCreateThread` at `0x81534548` preserves the parameter from r5 in
  r26, calls `OSInitContext` at `+0x88`, then stores r26 at context `+0x0C`
  (`gpr[3]`) at `+0xA4`.
- Original `OSInitContext` at `0x8152E18C` stores entry r4 at context `+0x198`
  (`srr0`). `OSLoadContext` at `0x8152E028` restores r3 from context `+0x0C`
  at `+0xD0`, immediately before its `rfi`.
- Original `cardThreadMain` is 1204 bytes. The entry prologue calls
  `_savegpr_19` at `+0x10`; that helper only stores r19 through r31 and returns.
  The body overwrites r3 from `sThread` at `+0x14` before consuming it.
  The extra formal is genuinely unused, with no dummy read or receiver.
- The existing null return in r3 remains unchanged. `OSCreateThread` sets the
  saved LR to `OSExitThread`, whose original entry preserves returned r3.
- Both original and source retain the existing global C symbol binding. There
  is no linkage or callback-address change.

A read-only original-object/DOL audit checked six entry/caller/SDK functions:
656 nonrelocated instruction words and 73 direct calls agree with the original
DOL. The registration's raw address construction was independently decoded;
the evidence does not rely only on objdiff relocation matching.

## Measurements and gates

The baseline and candidate were both explicitly rebuilt with the same 43U
configuration and compiler. No header, build setting, or other source changed.

- `cardThreadMain`: unchanged 97.9402%, 301/301 instructions
- Unit: unchanged 97.20097%, 27/30 exact functions, 4168/9852 matched code bytes
- All 27 exact functions: individually checked, zero instruction differences
- Matched data: unchanged 1496/1496 bytes
- All five allocated sections: byte-identical, including extents and attributes
- All 522 relocation records and all symbol-table records: byte-identical
- The only ELF section difference is `.strtab`: 46 compiler-generated anonymous
  `@number` labels are renumbered; each retains its section, value, size and binding
- Full 1027-unit report: byte-identical to baseline
- String pool: 43/43 identical, checked before and after
- Literal-reference check: 45 arguments across 29 functions; no candidates or
  errors. The unchanged unequal-extent `loadCardFileIcons` is the only skip
- Full 43U `all_source`, report and DOL gates: pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check`: pass

Object SHA256 values:

- Baseline: `071b634c812dca8dc853fb57562509e1de1c927d8619aba34f34694ec0e3bf93`
- Candidate: `5bbe85c6a9d2e7aa8559f9b75024cb841bcb76a4273ad9e4dbe8fae23ec6963b`

The prior CardSequence attempts, card-icon reconstruction record, scene-call
contract audit, and current report were inspected first. Earlier trials covered
message packing, local lifetimes, icon parsing and copy/move branches; they did
not correct this callback declaration. No prior register-allocation trial was
repeated. This correction leaves the nonexact scene routines unresolved.
