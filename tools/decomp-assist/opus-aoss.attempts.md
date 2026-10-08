# opus-aoss: AOSS.c .bss ownership (s_packetState, s_crcTable)

## Evidence

Target relocations (pyelftools over build/43U/obj/src/scene/setting/*.o):

- `AOSS_810BE838` (0x68) and `AOSS_810BE8A0` (0x400) are referenced only by
  `AOSSDecryptMessage` (0x81400830) and `AOSSSendHelloRequest` (0x81401778).
  No other object in build/43U/obj references them (grep over every .o).
- Those two functions are not contiguous in .text (7 functions between them,
  4 after), so (a) "split AOSS.c into a CRC/packet TU with its own functions"
  is ruled out: there is no function tail that moves with the objects.
- ATERM.c never references them, so (b) "they are ATERM's" has no support.
- (c) common/tentative: MWLD puts SHN_COMMON blocks after all other .bss of the
  link, but ATERM.c's .bss follows these objects, so they are not commons.

Addressing-pattern experiments (AOSS.o, -O4,p -inline off), SendHello differing
lines out of 273 (odiff.py), every other function checked each time:

| AOSS.c form of the two objects | SendHello | other effect |
|---|---|---|
| `static`, defined before the functions (main) | 254 (size 0x43c vs 0x444) | - |
| non-static, defined before the functions | 254 | none |
| `extern` decl at top, definition at end of AOSS.c | 254 | none |
| `extern`, not defined in AOSS.c | 97 (size 0x444) | none |
| all five .bss objects `extern` | 97 | HandleAuthReply 0 -> 103 |
| s_configData + s_networkBuffer also `extern` | 97 | HandleAuthReply 0 -> 103 |

Any definition inside AOSS.c (static, global, early, late) makes MWCC share one
`...bss.0` base register across s_runtime / s_packetState / s_crcTable in
SendHello. The target forms a separate `lis/addi` per object (two for
s_runtime alone), which this compiler only produces when the symbol is
undefined in the TU. Meanwhile s_runtime, s_configData, s_networkBuffer must
stay defined in AOSS.c, or HandleAuthReply loses its exact match. So the two
objects are defined in a different TU that the linker places right after
AOSS.c, with no .text of its own.

## Applied split

- New data-only TU `src/scene/setting/AOSSData.c` (Matching), linked between
  AOSS.c and ATERM.c; splits.txt `.bss 0x810BE838..0x810BECA0`.
- They're tentative definitions, so MWCC emits them in reverse order: the
  source declares `s_crcTable` and then `s_packetState` (first try in forward
  order gave the wrong order and a wrong DOL hash).
- symbols.txt: `AOSS_810BE838` -> `s_packetState`, `AOSS_810BE8A0` -> `s_crcTable`
  (needed so the retail AOSS.o asm links against the new definitions).
- `AOSSKeyMaterial`, `AOSSPacketState` and the extern declarations moved to
  include/scene/setting/AOSS.h (only AOSS.c includes it).
- Full build: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; symorder
  AOSSData ORDER OK. All 17 exact AOSS functions are still exact.

## SendHello follow-up (254 -> 58)

| attempt | differing |
|---|---|
| split only, existing source | 97 |
| drop `crcTable` alias local | 97 |
| decl order permutations of response/payload/checksum/sequence (24) | best 82 |
| flat `for (index < 8)` / int index / pointer / sizeof bound / operand swap | 237 (first iteration constant-folded) |
| 2x4 nested loop | 82 |
| `index = 0; while (index < 8) ... bytes[index++]` | 58 |
| decl permutations on top of the while loop | best 58 |
| swap `sequence = 0` / `checksum = 0` | 59 |
| `payload = &response->payload` earlier / at declaration | 69 / 82 |

Remaining in SendHello: checksum r31 vs r30 and payload r30 vs r31 (decl order
can't reach it), and the RC4 loop addresses `construction` from its base
(r1+0x10, offsets 8/9) where the target holds a pointer to `hello.data.bytes`
(r1+0x18, offsets 0/1). The second points at the `construction` carrier struct:
the target probably has `hello` as its own local. That's the next lever.

## Gate (AOSS AOSSData ATERM --quick)

`GATE FAIL: 1 regressions vs main`. The only one is `AOSS: matched_data 3928 -> 2800`,
which is exactly the 1128 bytes now in AOSSData (1128/1128, linked). Global
matched data stays 100%, global fuzzy goes 99.88565 -> 99.88798, no forbidden or
readability findings, DOL SHA1 OK. AOSS is 17/21 exact (unchanged), ATERM 20/26 (unchanged).

## Round 2: alternatives to the data-only TU

| alternative | result |
|---|---|
| definitions in ATERM.c (AOSSData removed, ATERM .bss split moved to 0x810BE838, `AOSSPacketState s_packetState; u32 s_crcTable[0x100];` placed before `gAtermIpConfig`) | built ATERM.o puts them at .bss offsets 8144/9168, i.e. after every ATERM object (unreferenced in the TU, emitted last in reverse order); target needs offset 0/104. MWCC emits a TU's .bss referenced-first, so ATERM can't own the start of its .bss with objects it never uses. Rejected. |
| function-local `static` arrays in SendHello (shadowing the externs) | SendHello 58 -> 231; local statics join the TU's shared `...bss.0` base exactly like file statics. Also ruled out by relocations: AOSSDecryptMessage references both objects directly, so neither function can own them as locals. |
| AOSSLink.c / iplRakuRakuThread.cpp | earlier in link order, their .bss sits before AOSS.c's, can't hold 0x810BE838. Not tried. |

Data-only AOSSData.c remains the only form that gives a separate lis/addi per object.

## Round 2: AOSSSendHelloRequest 58 -> 0

| attempt | differing |
|---|---|
| carrier struct `construction` removed, four plain locals in old order | 84 (hello now addressed at r1+0x18 directly; stack order wrong) |
| 24 permutations of the four locals | best 74: `accessPointName, hello, destination, schedule` (schedule position irrelevant); stack layout now matches |
| RC4 loop reads `*input++` from `input = hello.data.bytes`, as AOSSDecryptMessage does | 57 |
| single-line moves of every declaration (460 builds) | none below 57 |
| no `payload` local (`response->payload.` everywhere) | 261, rejected |
| mwdbg capture (first two runs crashed in the emulator before the function, third worked): `@2964` = checksum's {0, final} web, a split compiler temp numbered above all locals, so it's colored first and takes r31 before `payload`; `@2966` = the reused `index` split for the RC4 loop, colored before `state` and takes r3 | - |
| separate `crc` accumulator for the CRC loop, `checksum = (crc ^ 0xffffffff) & 0xff` | 55 |
| + `checksum` declared right after `payload` (move search) | 23 (r30/r31 fixed) |
| + RC4 loop gets its own counter `i` instead of reusing `index`, declared after `state` | **0**, size 0x444 = 0x444 |

AOSS after: 18/21 exact (was 17). AOSSDecryptMessage still 0/321. Unchanged non-exact:
AOSS_Init_old 1306/1584, AOSSApplyAuthOptions 22/114, AOSSXorBufferWithKey 34/147. Pool identical.

## Gate round 2 (AOSS AOSSData ATERM --quick)

`GATE FAIL: 1 regressions vs main`, again only `AOSS: matched_data 3928 -> 2800` (the 1128 bytes now in
AOSSData, 1128/1128). AOSS 18/21 exact (17 -> 18), code 7720 -> 8812/16192, ATERM 20/26 unchanged, pools
identical, global matched code 97.12163 -> 97.15810, fuzzy 99.88565 -> 99.88839, data 100%, 0 forbidden, 0
readability, DOL SHA1 OK.
