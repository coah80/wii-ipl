# NHTTP_thread leaf attempts

Target: Wii Menu 4.3U, libs/RevoEX/src/nhttp/NHTTP_thread.c.
Baseline: no source, 0/26 instruction-exact functions, 0/11292 matched code bytes,
0/504 matched data bytes. Implemented all 26 functions in object order using the
private nhttp structures. Other translation units and shared headers are unchanged.

Current: 23/26 instruction-exact functions, 8504/11292 matched code bytes,
88/504 matched data bytes. The eight-string .data pool is identical.
The unit remains NonMatching after a failed linking experiment.

## Remaining functions

### NHTTPi_RecvProxyConnectHeader: 99.92063%

126/126 instructions. Only the order of the two zero initializations differs:
source initializes r5 then r4; target initializes r4 then r5.

- Initial pointer/countdown scan: 90.2381%.
- Materialized communication buffer and a for loop: 96.74603%.
- Index-bounded scan: 98.690475%; pointer-end bound: 95.833336%.
- Declared request/response before the accepted flag: 99.44444%.
- Cursor declaration before index: 99.7619%; while-loop pointer increments:
  99.92063%, retained.
- Initialized index before the end flag: still 99.92063%.
- Moved flag before cursor declarations: 99.24603%.
- Other scan declaration orders: 99.64286%, 99.32539%, 99.166664%.
- Inline header scan helper: 97.53968%, rejected and restored.

### NHTTPi_ThreadParseHeaderProc: 98.58639%

191/191 instructions. Differences remain in string-base and request registers,
and zero initialization/scheduling around the Keep-Alive comparison. There are
no missing branches or instructions in the retained version.

- Shared error label: 66.84293%; individual error returns: 85.125656%.
- Positive Content-Length branch first: 89.84293%.
- Positive header-value branches first: 94.84293%.
- Secure connection branch first, with all false assignments preserved:
  98.03665%.
- Store computed chunked flag after its length branches: 98.58639%, retained.
- Default keepalive value before comparison, and declaration hoisting:
  98.58639%, no improvement.
- Buffer declaration first: 98.50785%, rejected.
- Request declaration first: 98.58639%, no improvement.

### NHTTPi_ThreadRecvBodyProc: 99.1579%

379/380 instructions. Register assignment differs for system info, the chunk
count and the two-byte recent-character buffer. The ignored trailer-line return
lets the compiler reuse a zero-valued loop counter for scratch initialization;
the target emits a separate zero load. No undefined values are used.

- Initial implementation: 75.11053%.
- Half-open informational status range: 75.12631%.
- Incomplete fixed-length body branch first: 76.71842%.
- Hoisted chunk count: 76.86316%; scratch array scope variations: unchanged
  or 76.71842%.
- Corrected Ghidra's apparent 64-bit chunk count to the assembly's 32-bit
  count, and restored the consumed-byte return from the inline chunk-line
  reader: 81.48421%.
- Positive chunk branch before zero-chunk trailers: 96.905266%.
- Handle end-of-stream success inside the receive loop: 99.1579%, retained.
- Unsigned recent-character local and function-scope recent array:
  99.1579%, no improvement. Hoisted byte count: 98.07895%, rejected.

## Linking experiment

Temporarily changed only NHTTP_thread.c to Matching and built main.dol.
The final experiment produced SHA1 18abd4071ea17c4ef4708fa149dc479009c12b8d,
so configure.py was restored to NonMatching.

unitaudit.py reported 25 text symbols at their target addresses, with only the
following CommThreadProcMain shifted by -4. The next unit,
d_nhttp_private.c at 0x8149b390, and subsequent text also shifted by -4.
nm confirms the source .text is 11288 bytes, against 11292 target bytes.
The missing instruction is in ThreadRecvBodyProc.

The real named multipart string arrays were declared as ordinary const char
arrays. Source STR_POST_DISPOS starts at 0x0, STR_POST_TYPE_BIN at 0x28,
STR_POST_TYPE_URLENCODE at 0x74, and STR_POST_TYPE_MULTIPART at 0xa8. The target
object names these symbols at 0x0, 0x27, 0x74, and 0xa6. unitaudit reports
rodata deltas of 0, +1, and +2. Source section sizes are .data 194, .rodata 213,
.sdata 88; target sizes are .data 200, .rodata 216, .sdata 88. The pool's string
contents and offsets agree; section trailing alignment and named constant
boundaries still need investigation. No padding or address-pinning was added.

A byte comparison against orig/43U/00000008.app found 1305353 differing bytes,
first at file offset 0x5bb. Both files are 3867904 bytes. The text shift changes
relocated references outside this unit, so that count is not a count of local
instruction mismatches.

Final acceptance uses the full non-quick gate after restoring NonMatching.
