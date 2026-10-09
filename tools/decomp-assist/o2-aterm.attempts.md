# o2-aterm attempts (ATERM, 2026-10-09)

Start (a6e74ad2): ATERM 22/26 exact; open: DiscoverAccessPoints 7, BuildEncryptedMessage 2,
BuildAssociationRequest 28, RunConfigProtocol 294.
End (2882435b): 25/26 exact; BuildEncryptedMessage 2 (scheduler tie-break, below). ATERM stays
NonMatching.

## Prior art: the DS build of the same library

The DS DWC library ships the same NEC "AtermStation" code with its real static names
(CacaBueno64/ie3ogres `lib/TwlDWC_dl/asm/util/atermset.s`, read-only). Name map:
ScanAP = DiscoverAccessPoints, CheckAccessPoint = FindChangedApRecord, GetMacEncKey =
BuildAssociationRequest, GetWLanSetElement = ParseAssociationResponse, AsciiToHex = ParseHexBytes,
StoreNetParam = ApplyScanSecuritySettings, AutoConfigThreadEx = RunConfigProtocol,
keywrap_encrypt/decrypt = AesKeyWrap/Unwrap, rijndael* = Aes*, MY_MD5Update = Md5Update,
PutHex/PutMac = the hex and MAC formatters (non-inlined on DS, so their bodies are visible).

## MAC formatter (DiscoverAccessPoints 7 -> 0, BuildAssociationRequest 28 -> 0)

Cause: the register swap was input pointer r9 vs r5 and low nibble r5 vs r9. With the
`nibbles[2]` array helper both nibbles are codegen temps, which are numbered above every inline
variable and therefore colored first, so the low nibble always took r5 (array element types,
declaration orders, 400 sampled formatter shapes, pragmas and compiler versions: no change).
The DS PutHex keeps one nibble variable and rotates it: `h = (c & 0xF0) >> 4; for (2) { emit h;
h = c & 0xF; }`. On MWCC the loop-invariant `c & 0xF` becomes an IR temp numbered below the
inline locals, so it is colored last (r9), and PutMac's `*mac++` parameter takes r5. Both
functions exact; ParseAssociationResponse (GetWLanSetElement calls PutHex on DS) stays exact with
the same helper (`key += atermFormatHexByte(key, *optionValue++)`), so the separate straight-line
atermEncodeHexByte is gone.

## Readability: scan buffer header

`(u16*)scanBuffer + 1` replaced by `((AtermScanBuffer*)scanBuffer)->descriptorWords`
(count, then the descriptor word stream): 0 diffs. Typing the scanBuffer local itself as
AtermScanBuffer* changes the alignment arithmetic (98 diffs, size 0x418).

## RunConfigProtocol (294 -> 2) = DS AutoConfigThreadEx

Rebuilt from the DS layout instead of the hand-inlined body: GetTickCount, Sleep (alarm), SendNotify,
SendFrame -> SendBroadcast -> SendFrameViaInterface, GetFrameData/GetCommandElement,
GetElementData/GetFirstElement, SetElementData/SetSingleElement/SetSearchRes, RFC 1321 MD5
Init/Encode/Final/memset as static inlines, globals used directly (no request/packet/response/session
pointer locals). Findings, each measured:
- .bss order follows the first reference in the function IR. Passing a cast global address
  (`(u8*)&gAtermDecodedResponse`, `(u16*)buf`) into a static inline hoists it to the function entry
  and moves it first. The element buffer is a plain `u8[0x800]` in the original (like FrameData), so
  it is now one, with an AtermElementHeader view; that keeps the target order without pointer locals.
- Inline helper uses of a global address get a hoisted register (r25/r31/r15) while direct call
  arguments rematerialize `addi rN, base, off`. This is plain MWCC behaviour, matching the target.
- MD5: the exact RFC 1321 Encode/MD5_memset text (`unsigned int` lengths, `unsigned char` masks)
  keeps IRO from unrolling the Encode loops, so the PCode unroller produces the target's
  load/store order (u32 types: 35 diffs; RFC types: 0).
- SetElementData must advance its own cursor parameter (`cursor += recordSize; return cursor;`)
  for the r16/r17 alternation; the value pointer as `cursor + sizeof(AtermOptionHeader)`.
- GetFrameData returns `frame + sizeof(AtermFrameHeader)` (not `packet->payload`), declares
  `end` before `cursor` (inline locals number in reverse order); SetSingleElement writes through a
  header pointer local.
Remaining 2 at 23addcb1: SetSearchRes' second element folds its value pointer to the first
element's base (`addi r3, r16, 0xc`, target `addi r3, r17, 4`).

## RunConfigProtocol (2 -> 0): the DS SetElementData body with an int pad size

Found with IRO dumps. The compiler prints them once two dump flags are set: gdb breaks at
0x5ed507 (log open) and writes 0x725e5c, then toggles 0x725e5c/0x70f24d per function at
0x577716. That is o2-keyboard's /tmp/o2-keyboard/irodump1_gdb.py; the log is `<source>.log`. A
copy that keeps its temporary source in this worktree is /tmp/o2-aterm/irod/run.sh. It drops
the AES tables and the bodies after RunConfigProtocol, which leaves the function's code identical
and takes about a minute.
- Elements 1 and 2 share one IRO block. Block-local expression propagation chains element 2's
  cursor copies back to element 1's cursor temp, so element 2's `cursor + 4` reads element 1's
  temp. IRO_PropagateSelfAssignments (inc/dec propagation, 0x5f2150) then folds element 1's
  `+= 8` into it, giving base1 + 0xc. Elements 5 and 4 sit in their own blocks: global copy
  propagation reaches them one step at a time, so they fold onto the previous element's base,
  which is what the target does.
- Inc/dec propagation is all-or-nothing per `+=` def. Every reached use must have that def as its
  only reaching definition. More than one use needs the helper at 0x5f24e0, which builds
  `var op const` and asks a backend predicate (0x56ac90).
- The DS SetElementData does `p += sizeof(header); memset(p, 0, pad); memcpy(p, data, len);
  return p + pad`. A mid-body `+= 4` kills the copy before element 2's value uses. With
  `cursor += paddedLength; return cursor;` and an `int` (or unsigned int, u16, short) pad size, the
  first PropagateSelfAssignments round leaves those incs alone. Element 1's `+= 8` therefore
  reaches element 2's cursor copy (`@c2 = @c1 + 8`, no longer a copy) before any copy
  propagation reaches the value uses, and they stay `base2 + 4`. With `s32`/`u32` (long) pad
  sizes, the first round merges the `+= 4`. Second-pass copy propagation then rewrites the
  value uses to element 1's temp, and the fold comes back (2 diffs). A mini repro with `int`
  typedefs behaves like the `int` case, which is how the type dependence showed up. Measured
  variants: E4 (`+= pad; return cursor`) int/unsigned/u16/short: 0. E4 s32/u32: 2. E1 any type: 2.
  E3 (`return cursor + pad`) any type: 661.
- Bisecting the full function (other switch cases, the loop condition, atermSleep, the
  epilogue) changed nothing. Only the helper text matters.

## BuildEncryptedMessage (2, unchanged): entry-block scheduler order

Target `mr r27,r5; mr r30,r3; mr r26,r4; mr r28,r6; mr r3,r27; mr r29,r7`; ours puts
`mr r29,r7` before `mr r3,r27`. The mwdbg capture shows the entry block is list-scheduled before
register allocation, with the program order r3..r7 parameter moves, `li checksum`, `mr r3,payload`,
`li r4`, `li r5`, `bl memset`. The 750 model gives the memset call latency 0, and the GPR
anti-dependency edges have latency 0. The call's operand list also clobbers r6 and r7. So the r6
copy and the r7 copy have identical dependencies, unlocked-successor counts, heights,
criticality and rank. Program order then always places both before `mr r3,payload`, but the
target puts r6 before it and r7 after. Not reachable by:
- K&R parameter declaration orders
- every `#pragma scheduling` model (740/750/7400/altivec/on/reset: 2; others: 12-40)
- key copies, extra param copies and inline wrappers (the earlier session)
Recorded as a scheduler tie-break.
