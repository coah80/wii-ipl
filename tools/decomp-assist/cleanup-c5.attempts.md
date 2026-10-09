# cleanup-c5 attempts

Worktree: `/mnt/drive2/projects/wii-ipl-workers/data-d5`
Branch: `agent/w1009/cleanup-c5`
Baseline: `f1db6b656e386063a8bc263fb75a299f36ae4803`

Full build first passed: all 1028 units, 12563 functions, code and data 100% matched and linked.
DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`. Completion check: `DECOMPLETE_OK`.

## Compiler pragmas

- Removing all scoped pragmas changed KBDSetModState and kbdProcMod by four register operands each, shortened kbd_led_handler from 25 to 22 instructions, shortened each texture setter by one instruction, and changed FAT32 builder control flow from 222 to 216 instructions. Restored.
- Removing only pfd_sddrv_init's IRO 0 scope preserves the entire sd_drv object byte for byte. Accepted.
- kbd_lib: remove KBDSetModState IRO 1 only: KBDSetModState: 4 instruction differences. Restored.
- kbd_lib: without setter IRO, load modifier directly into bitfield: kbdProcMod: 4 instruction differences; KBDSetModState: 4 instruction differences. Restored.
- kbd_lib: without setter IRO, use a word for old modifiers: KBDSetModState: 4 instruction differences. Restored.
- kbd_lib: remove kbdProcMod propagation scope only: kbdProcMod: 4 instruction differences. Restored.
- kbd_lib: without propagation scope, pass modifiers directly: kbdProcMod: 4 instruction differences. Restored.
- kbd_lib: without propagation scope, update modifier word before setter call: kbdProcMod: 256 -> 257 instructions. Restored.
- kbd_lib: remove LED IRO 0 only: kbd_led_handler: 25 -> 22 instructions. Restored.
- kbd_lib: without LED IRO, select callback result with ternary: kbd_led_handler: 25 -> 22 instructions. Restored.
- kbd_lib: without LED IRO, initialize failure and override on success: kbd_led_handler: 25 -> 22 instructions. Restored.
- sd_drv: remove FAT32 builder IRO only: pfd_sddrv_full_format: 3 instruction differences; pfd_sddrv_build_fat32_mbr_bpb: 222 -> 216 instructions; .data changed. Restored.
- sd_drv: without FAT32 IRO, combine media checks: pfd_sddrv_full_format: 3 instruction differences; pfd_sddrv_build_fat32_mbr_bpb: 222 -> 208 instructions; .data changed. Restored.
- sd_drv: without FAT32 IRO, pass write-block arguments directly: pfd_sddrv_full_format: 3 instruction differences; pfd_sddrv_build_fat32_mbr_bpb: 222 -> 216 instructions; .data changed. Restored.
- sd_drv: without FAT32 IRO, define reserved-sector helper after caller: pfd_sddrv_full_format: 3 instruction differences; pfd_sddrv_build_fat32_mbr_bpb: 222 -> 216 instructions; .data changed. Restored.
- Texture_MCUtoRGBA8: remove setter optimization scope only: TMCJPEGDEC_converterYUV411toRGBA8: 6 instruction differences; TMCJPEGDEC_set_converterRGBA8: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGBA8: without setter scope, initialize buffer and state at declaration: TMCJPEGDEC_converterYUV411toRGBA8: 6 instruction differences; TMCJPEGDEC_set_converterRGBA8: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGBA8: without setter scope, put row locals in their sampling cases: TMCJPEGDEC_converterYUV411toRGBA8: 6 instruction differences; TMCJPEGDEC_set_converterRGBA8: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGBA8: with setter scope retained, put row locals in their sampling cases: TMCJPEGDEC_set_converterRGBA8: 44 instruction differences. Restored.
- Texture_MCUtoRGB565: remove setter optimization scope only: TMCJPEGDEC_set_converterRGB565: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGB565: without setter scope, initialize buffer and state at declaration: TMCJPEGDEC_set_converterRGB565: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGB565: without setter scope, put row locals in their sampling cases: TMCJPEGDEC_set_converterRGB565: 170 -> 169 instructions. Restored.
- Texture_MCUtoRGB565: with setter scope retained, put row locals in their sampling cases: TMCJPEGDEC_set_converterRGB565: 44 instruction differences. Restored.
- Texture_MCUtoY8U8V8: remove setter optimization scope only: TMCJPEGDEC_set_converterY8U8V8: 196 -> 195 instructions. Restored.
- Texture_MCUtoY8U8V8: without setter scope, initialize buffer and state at declaration: TMCJPEGDEC_set_converterY8U8V8: 196 -> 195 instructions. Restored.
- Texture_MCUtoY8U8V8: without setter scope, put row locals in their sampling cases: TMCJPEGDEC_set_converterY8U8V8: 196 -> 195 instructions. Restored.
- Texture_MCUtoY8U8V8: with setter scope retained, put row locals in their sampling cases: TMCJPEGDEC_set_converterY8U8V8: 58 instruction differences. Restored.
- kbd_lib: retain propagation scope, remove finalState temporary: whole object identical. Accepted.
- kbd_lib: retain setter IRO, replace old union with modifier word: object metadata or relocation bytes changed. Restored.
- kbd_lib: remove channel initialization overwritten by for loops: whole object identical. Accepted.
- sd_drv: store aligned little-endian words through the typed field: pfd_sddrv_store_bpb_buf: 4 instruction differences; pfd_sddrv_store_mbr_buf: 2 instruction differences; pfd_sddrv_store_fat32_mbr_buf: 2 instruction differences; pfd_sddrv_store_fat32_bpb_buf: 4 instruction differences. Restored.
- sd_drv: use format and settings sizes in memset calls: whole object identical. Accepted.
- sd_drv: use existing SDDev type size instead of 0x28: whole object identical. Accepted.
- Texture_MCUtoRGBA8: separate first-store output and tile-row assignments: TMCJPEGDEC_converterYUV411toRGBA8: 242 -> 243 instructions. Restored.
- Texture_MCUtoRGBA8: separate first-store assignments in row-before-output order: TMCJPEGDEC_converterYUV411toRGBA8: 242 -> 243 instructions. Restored.
- Texture_MCUtoRGBA8: compute output and tile-row addresses once per row: TMCJPEGDEC_converterYUV411toRGBA8: 5 instruction differences. Restored.
- Texture_MCUtoRGBA8: separate first-store assignments with row-scoped tileRow: compile failed. Restored.
- kbd_lib: retain setter IRO, use a word for old modifiers with metadata-aware comparison: all code, data, symbols and relocations identical; only compiler string metadata changed. Accepted.
- Texture_MCUtoRGBA8: separate first-store assignments with a row-local tileRow, corrected scope: TMCJPEGDEC_converterYUV411toRGBA8: 242 -> 243 instructions. Restored.
- Texture_MCUtoRGBA8: write opaque-alpha red words with a bit mask: TMCJPEGDEC_converterYUV411toRGBA8: 242 -> 238 instructions; TMCJPEGDEC_converterYUV411toRGBA8edge: 112 -> 111 instructions; TMCJPEGDEC_converterYUV422toRGBA8: 148 -> 146 instructions; TMCJPEGDEC_converterYUV422toRGBA8edge: 113 -> 112 instructions; TMCJPEGDEC_converterYUV420toRGBA8: 153 -> 151 instructions; TMCJPEGDEC_converterYUV420toRGBA8edge: 120 -> 119 instructions; TMCJPEGDEC_converterYUV211toRGBA8: 104 -> 103 instructions; TMCJPEGDEC_converterYUV211toRGBA8edge: 115 -> 114 instructions; TMCJPEGDEC_converterYUV444toRGBA8: 97 -> 96 instructions; TMCJPEGDEC_converterYUV444toRGBA8edge: 110 -> 109 instructions; TMCJPEGDEC_converterYUV400toRGBA8: 76 -> 75 instructions; TMCJPEGDEC_converterYUV400toRGBA8edge: 89 -> 88 instructions. Restored.
- Texture_MCUtoRGBA8: remove cancelling high-word addition from opaque-alpha stores: TMCJPEGDEC_converterYUV411toRGBA8: 242 -> 238 instructions; TMCJPEGDEC_converterYUV411toRGBA8edge: 112 -> 111 instructions; TMCJPEGDEC_converterYUV422toRGBA8: 148 -> 146 instructions; TMCJPEGDEC_converterYUV422toRGBA8edge: 113 -> 112 instructions; TMCJPEGDEC_converterYUV420toRGBA8: 153 -> 151 instructions; TMCJPEGDEC_converterYUV420toRGBA8edge: 120 -> 119 instructions; TMCJPEGDEC_converterYUV211toRGBA8: 104 -> 103 instructions; TMCJPEGDEC_converterYUV211toRGBA8edge: 115 -> 114 instructions; TMCJPEGDEC_converterYUV444toRGBA8: 97 -> 96 instructions; TMCJPEGDEC_converterYUV444toRGBA8edge: 110 -> 109 instructions; TMCJPEGDEC_converterYUV400toRGBA8: 76 -> 75 instructions; TMCJPEGDEC_converterYUV400toRGBA8edge: 89 -> 88 instructions. Restored.

## Retained changes

- kbd_lib.c: removed three channel assignments overwritten by their for-loop initializers and the finalState copy. Old modifier state is now a u32 instead of a union used only as a word. Only compiler-generated label strings change in the object; code, data, symbol offsets and relocations remain identical.
- sd_drv.c: removed the pfd_sddrv_init IRO scope; replaced format/settings/device memset lengths with sizeof of the existing types. The complete object remains identical.
- All three texture setters retain optimization_level 1: ordinary default optimization folds away the shared conversion-buffer base and changes register allocation. Function-local declarations in the sampling cases also change the registers.
- Keyboard scopes remain: default optimization swaps four register operands in each modifier function and eliminates the LED handler callback reload and conditional branch.
- FAT32 builder IRO 0 remains: ordinary optimization eliminates its reserved-sector error path and the associated strings. Direct field stores also change boot-sector addressing.
- RGBA8 first-store assignments and full-width alpha arithmetic remain: separate statements add an instruction; opaque-alpha bit masks or cancelling-add removal shorten all converters.
- Added one-line MWCC requirements at the retained scopes and tested source workarounds.

## File commits

- `3537cc8576f8ce2d979e324c3d55f9b4769fb334`: `libs/RVL_SDK/src/kbd/kbd_lib.c`.
- `0ae3719590c72c0c4787f52c80e727fade3c4b1b`: `libs/RVL_SDK/src/fa/driver/sd_drv.c`.
- `d19ec502fdac3a027222ce4f3f0cb1b6d84df9f2`: `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
- `fbbb88ed142ee16e15bce96ac0a5f3fadc7b567b`: `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.c`.
- `7ed8b7edf17ed04f9050a032a68590dbf6bcefb9`: `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8.c`.

The leaf checker run from this assigned worktree rejects its own current directory as the integration root. Git worktree records independently confirm the assigned leaf path and branch; parent integration must run that checker from its integration tree. No other worktree was changed.

## Final validation

`gate.py` ran once at the end over all five assigned units with `--quick`.

- full build: ok
- main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
- regressions vs baseline: 0
- forbidden patterns added (net, per file): 0
- readability warnings (net, per file; must be 0 in the final result): 0
- GATE PASS
- Fresh `build/43U/report.json` and completion checker: `DECOMPLETE_OK`.
- `kbd_lib`: 21/21 exact functions; all code, data, sections and link measures 100%.
- `sd_drv`: 26/26 exact functions; all code, data, sections and link measures 100%.
- `Texture_MCUtoRGBA8`: 13/13 exact functions; all code, data, sections and link measures 100%.
- `Texture_MCUtoRGB565`: 13/13 exact functions; all code, data, sections and link measures 100%.
- `Texture_MCUtoY8U8V8`: 13/13 exact functions; all code, data, sections and link measures 100%.
- Baseline-to-final object comparison: SD and all three texture objects are fully identical; keyboard differs only in compiler label strings, with code/data/symbol offsets/relocations identical.
- No source, headers or configuration outside the five assigned files changed; no pushes, PRs, merges or rebases.
