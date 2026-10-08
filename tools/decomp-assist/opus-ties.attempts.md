# opus-ties: one-function-from-linking triage (base f9ebd2f4)

Full build at base: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Diff counts are from `odiff.py` (differing / total).
Result: no new exact function, and no source changes kept.

| unit | function | diff | class | regsim verdict | result |
|---|---|---|---|---|---|
| src/utility/iplESMisc | DeleteUnauthorizedData | 74/449 | GPR register-only | n.a. (trace blocked, see below) | unchanged |
| src/iplwww/www_wiisetting | Getter_ | 14/609 | GPR register-only (two named loop counters: `i`/`strBuf` in DUMMY_SECURITY_KEY, `i` in EUR 0x3b loop -> r31) | n.a. (trace blocked) | swapping `strBuf`/`i` declarations: no change (14) |
| src/keyboard/tiZiString | WithZi::update | 85/446 | GPR register-only plus 2 dependent swaps (163/164, 291/292) | n.a. (trace blocked) | unchanged |
| libs/RVL_SDK/src/nup/nup | __nupParseServerInfo | 66/452 | GPR register-only | structural: every named local already matches; all mismatches are @-temps of the inlined `__nupFindTag`/`strlen` (@1858,@1852,@1849,@1807,@1805,@1804,@1798,@1795 + unnamed r114/r120/r128/r134/r140/r150/r158/r166/r170). Best 7/8 needs @-temps interleaved with named locals | swapping `start`/`end` in `__nupFindTag`: no change (66) |
| libs/NW4R/src/lyt/lyt_window | Window::DrawFrame | 119/376 | GPR + FPR register | structural: unnamed temp v92 (`lis/addi` table base, wants r21 instead of r31) shifts this/basePt/frameSize/alpha/bUseVtxCol and v95..v124 up by one; regsim best 4/11; FPR diffs also | unchanged |
| src/scene/memoryCard/iplMemoryCardManager | _create_icon | 37/100 | scheduling + register (same count) | n.a. | target recomputes `&mFileCell[slot][file].icon` / `.iconTlut` adds after each GX call (keeps row base and index*0x15c in separate registers); ours CSEs the full address. `texObj` local assigned before GXLoadTexObj: 61/101 (worse) |
| src/keyboard/tiString | Decolated::inputChar | 73/136 (0x1f8 vs 0x220) | instruction count | n.a. | first diff: mode-3 (`CharacterOutput`) path; target keeps a runtime index (`sthx` at count*2, dead `cmplwi ch,10`, `clrlwi` count), ours folds to constant stores. Not attempted again (see tiString.attempts.md) |
| libs/RevoEX/src/nhttp/NHTTP_recvbuf | NHTTPi_compareTokenN_HdrRecvBuf | 5/124 | scheduling only (same registers) | n.a. | loop-preheader order: target `li 0x41, li 0x5a, extsb delim, addi limit-1, li 0`, ours `extsb, addi, li 0x41, li 0, li 0x5a`. Tried: for(;;)+break 63, swap LowerCase operands 40, `<= 'Z'` first 34, constants on the left 5, if/return form 40, `inline` 5, macro 5, s8 param 5 |
| libs/RVLMiddleware/TMC_JPEG/.../Texture_MCUtoY8U8V8 | TMCJPEGDEC_set_converterY8U8V8 | 195/196 (0x30c vs 0x310) | instruction count | n.a. | target materializes `work->convBuf` (`addi r4,r3,0x1858`) at entry and adds row offsets to it; ours folds into each offset. Already covered by tex1/g5/fz15; IRO and pragma sweep (irosweep --all): no hit |
| libs/RVLMiddleware/TMC_JPEG/.../Texture_MCUtoRGB565 | TMCJPEGDEC_set_converterRGB565 | 169/170 (0x2a4 vs 0x2a8) | instruction count | n.a. | same as Y8U8V8 (convBuf base kept at entry); irosweep --all: no hit |
| libs/RVL_SDK/src/fa/pdm_partition | pdm_part_is_master_boot_sector | 84/86 (0x158 vs 0x150) | scheduling + register pressure (extra saved r29 -> frame 0x40) | n.a. | byte loads of `read_partition_u32` scheduled differently, so one more live value; perm8/perm8d already tried 4950 permutations. irosweep --all: no hit |

## mwdbg on the three blocked units

`mwdbg.py` fails before reaching the function for iplESMisc, tiZiString and www_wiisetting (also with the stock tool):

1. Stock retrowin32: `WRITE_UNMAPPED @47e090` / `READ_UNMAPPED @46da46` with esp near 0xf18. The emulated compiler overflows its 1 MB stack (the PE's SizeOfStackReserve is 0x100000).
2. A private copy (`/tmp/ot/rw32`) with the stack raised to 32 MB and memory to 1 GB (`win32/src/pe/loader.rs` stack_size max(32<<20); `machine_unicorn.rs` MemImpl::new(1024<<20)) gets further. The compiler then calls its `UCBReportMessage` callback, which goes through `ws2_32!send` (ordinal 19, the call at 0x42c8b1), and retrowin32 has no ws2_32 shim.
3. The message is not the iplTree.h "return value expected" warning. Adding `-w off`, or an include override that fixes the warning, compiles silently under wibo but still hits `send` under the emulator.

The shared `_mwdbg` tool was not modified. To unblock these units, the next step is either a ws2_32 `send` shim that writes to stderr (to read the message) or a fix for whatever emulator difference triggers it.

nup and lyt_window traced fine; regsim reproduced 162/162 and 197/197.
`tools/decomp-assist/opus-ties.vmap.py <capdir> <unit> <symbol>` maps each traced virtual register to our physical register and the target's, by aligning backend-04 with after-color PCode and the two objects. That gives the `--want` list.
