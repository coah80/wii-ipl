# BS2Mach assembly reconstruction, round 2

Baseline 6ade1630. Only BS2Mach source is in scope. Target blocks are processed in address order, with frame and earliest structural differences first.

| Function | Original bytes | Baseline fuzzy |
| --- | --- | --- |
| BS2Tick | 7760 | 76.669075 |
| CheckBS2CommandStatus | 1624 | 80.697044 |
| BS2StartGame | 1572 | 95.496185 |
| BS2StartGCGame | 912 | 98.24561 |
| BS2NANDDivideCallback | 512 | 85.03906 |
| BS2NANDDivideReadAsync | 188 | 60.31915 |
| BS2NANDDivideWriteAsync | 188 | 60.31915 |
| Run | 172 | 0.88372093 |

## BS2Tick, frame and 8137D40C–8137D514

Target and source frame are 0x70. Initial switch prologue already aligns except branch distances. The first body discrepancy is initialization scheduling at 8137D44C, before the first state transition.

| BS2Tick | 2 | 8137D44C: derive progress once and clear through stored pointer | 76.66908 -> 76.66908; src 0x1db8 base 0x1e50 insns 1902/1940; restored |

| BS2Tick | 3 | 8137D44C: keep progress and partition-parameter addresses in scoped typed locals | 76.66908 -> 76.39175; src 0x1db8 base 0x1e50 insns 1902/1940; restored |

| BS2Tick | 4 | 8137D44C: load no-disk flag before final initialization stores | 76.66908 -> 76.65619; src 0x1db8 base 0x1e50 insns 1902/1940; restored |

BS2Tick prefix allocation depends on 64-bit elapsed-time comparisons later in the same function. Target 8137D69C uses mulhwu/mullw for a 64-bit 100ms threshold; the existing C truncates that product to 32 bits. Reconstruct that real type boundary before continuing the prefix.

| BS2Tick | 5 | frame-wide time lifetime: restore 64-bit 100ms products from target blocks | 76.66908 -> 76.28299; src 0x1dd8 base 0x1e50 insns 1910/1940; restored |

| BS2Tick | 6 | 8137D4F4: retain promoted clock addend before system time | 76.66908 -> 76.66908; src 0x1db8 base 0x1e50 insns 1902/1940; restored |

| BS2Tick | 7 | 8137D698: use signed wide milliseconds as OS conversion input | 76.66908 -> 79.39536; src 0x1e28 base 0x1e50 insns 1930/1940; kept |

| BS2Tick | 8 | 8137D4F4: named 32-bit spinup duration promoted at addition boundary | 79.39536 -> 79.39536; src 0x1e28 base 0x1e50 insns 1930/1940; restored |

Signed OS milliseconds input retained: BS2Tick 1902 -> 1930 instructions against 1940 target; fuzzy 76.669075 -> 79.39536. The first initialization group remains the same count but has scheduling and register lifetime differences. No block beyond the already-present structure is treated as validated until prefix ordering is resolved.

| BS2Tick | 9 | 8137D4E4: express deadline as clock call plus OS seconds macro | 79.39536 -> 79.45052; src 0x1e28 base 0x1e50 insns 1930/1940; kept |

| BS2Tick | 10 | 8137D44C: move audio initialization before progress pointer computation | 79.45052 -> 79.43402; src 0x1e28 base 0x1e50 insns 1930/1940; restored |

| BS2Tick | 11 | 8137D44C: keep command reset after all partition stores via local pointer | 79.45052 -> 79.44021; src 0x1e28 base 0x1e50 insns 1930/1940; restored |

The initial BS2Tick group has no missing operations: remaining prefix differences are scheduling, use of addze versus the live zero register, and register lifetimes. Scoped-pointer and literal-call translations have been tested before advancing. A direct logger alias is tested as an inline-helper boundary, without changing BS2Report or any other function.

| BS2Tick | 12 | prefix/helper boundary: invoke existing logger through typed local alias | 79.45052 -> 71.64794; src 0x1f9c base 0x1e50 insns 2023/1940; restored |

| BS2Tick | 13 | 8137D44C: clear parameter fields through a compound struct assignment | 79.45052 -> 79.45000; src 0x1e28 base 0x1e50 insns 1930/1940; restored |

## BS2Tick region blocks, address-order reconstruction

Target 8137D970 reads audio flags only after the unconfigured-state test; the existing C reads and sign-extends the disc byte before that test. Target 8137DAxx and 8137DDxx use explicit shared false branches rather than synthesized cntlzw booleans. These are real source structure differences; the initial scheduling group remains open and no complete-function claim is made.

| BS2Tick | 14 | 8137D970: read unsigned audio bytes after pending-state validation | 79.45052 -> 79.25258; src 0x1e24 base 0x1e50 insns 1929/1940; restored |

| BS2Tick | 15 | 8137DA20 and 8137DCB0: load country only on completed command path | 79.45052 -> 79.47217; src 0x1e20 base 0x1e50 insns 1928/1940; kept |

| BS2Tick | 16 | 8137DA20/8137DCD0: correct each region load within its own state block | 79.47217 -> 79.37990; src 0x1e28 base 0x1e50 insns 1930/1940; kept |

Attempt 15 had a transformation-scope error: its second country assignment was inserted in state 14 instead of state 20. Attempt 16 fixes the source scope before any gate or commit; measurements of attempt 15 are rejected.

| BS2Tick | 17 | 8137DAxx/8137DDxx: translate region case blocks with explicit boolean stores | 79.37990 -> 80.30154; src 0x1e70 base 0x1e50 insns 1948/1940; kept |

| BS2Tick | 18 | 8137DAxx: share false region branch at target default block | 80.30154 -> 80.30154; src 0x1e70 base 0x1e50 insns 1948/1940; restored |

| BS2Tick | 19 | region fields: retain unsigned country comparisons and signed API region | 80.30154 -> 80.43144; src 0x1e70 base 0x1e50 insns 1948/1940; kept |

## BS2Tick stack outputs

Target frame 0x70: titleCharacters at sp+8, readOffset at sp+c, readLength at sp+10, readAddress at sp+14, bannerFile at sp+18. Current frame is also 0x70 but the three loader outputs are allocated in the opposite order, pushing the title-character array to sp+14. Reconstruct a typed loader-read descriptor rather than introducing padding.

| BS2Tick | 20 | frame: group actual loader outputs in offset-length-address order | 80.43144 -> 80.44485; src 0x1e70 base 0x1e50 insns 1948/1940; kept |

| BS2Tick | 21 | frame: declare loader descriptor before title character buffer | 80.44485 -> 80.44485; src 0x1e70 base 0x1e50 insns 1948/1940; restored |

| BS2Tick | 22 | 8137D71C and 8137D808: put cache branches before DVD branches | 80.44485 -> 81.44846; src 0x1e70 base 0x1e50 insns 1948/1940; kept |

BS2Tick loader descriptor now matches all target stack output slots: sp+14 address, sp+10 length, sp+c offset; title character bytes are sp+8..b. Target frame remains 0x70. Subsequent block comparison is performed against this frame layout.

| BS2Tick | 23 | 8137E02x and 8137E8xx: use layout format directly for loader word offsets | 81.44846 -> 82.05876; src 0x1e68 base 0x1e50 insns 1946/1940; kept |

| BS2Tick | 24 | loader helper boundary: call stored entry pointers without pointer punning | 82.05876 -> 82.05876; src 0x1e68 base 0x1e50 insns 1946/1940; restored |

## BS2Tick disc identity and audio basic blocks

Target retains the boot disc ID address across memcpy and strncmp calls. The old source repeatedly reconstructs raw addresses. Translate the same fields through DVDDiskID and preserve literal pool order.

| BS2Tick | 25 | 8137D84x-8137D970: keep a typed boot disc pointer across signature calls | 82.05876 -> 82.17114; src 0x1e64 base 0x1e50 insns 1945/1940; kept |

| BS2Tick | 26 | 8137D970-8137D9E8: translate unsigned audio fields with positive branch first | 82.17114 -> 82.55618; src 0x1e60 base 0x1e50 insns 1944/1940; kept |

| BS2Tick | 27 | 8137D9A4: express default streaming-buffer size as conditional value | 82.55618 -> 82.65928; src 0x1e64 base 0x1e50 insns 1945/1940; kept |

| BS2Tick | 28 | 8137DA4x-8137DD64: share region rejection blocks exactly as target branches | 82.65928 -> 83.42732; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

| BS2Tick | 29 | 8137DAA4: emit region-reject state before region-success state | 83.42732 -> 83.43093; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

| BS2Tick | 30 | 8137DD64-8137DE34: flatten region, disc validity and partition branches in address order | 83.43093 -> 83.83402; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

## BS2Tick title-region block 8137E4BC–8137E700

Translate the title header through CurrentTmd, compare the full system version, then use the target product-region switch instead of the previous hand-expanded if tree. Keep the literal strings and order unchanged.

| BS2Tick | 31 | 8137DE5x/8137E4D4: read first TMD version through typed current header | 83.83402 -> 84.53093; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

| BS2Tick | 32 | 8137E558: compare the full required IOS title ID in one condition | 84.53093 -> 84.61031; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

| BS2Tick | 33 | 8137E59C: keep extracted title prefix as promoted signed integer | 84.61031 -> 84.39278; src 0x1e24 base 0x1e50 insns 1929/1940; restored |

| BS2Tick | 34 | 8137E5E0–8137E700: reconstruct regional title checks as target switch blocks | 84.61031 -> 85.61340; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

## BS2Tick banner, closing and error-state blocks 8137E858–8137F1E4
Continue the loader-positive branch, banner early exit, partition transitions, then move ticket and error groups into actual target address order.

| BS2Tick | 35 | 8137E858: emit loader-read positive branch before loader-close state | 85.61340 -> 86.15154; src 0x1e24 base 0x1e50 insns 1929/1940; kept |

| BS2Tick | 36 | 8137E8xx–8137EA6C: translate banner early exit and unmasked disc layout shift | 86.15154 -> 86.63145; src 0x1e20 base 0x1e50 insns 1928/1940; kept |

| BS2Tick | 37 | 8137EB1C: put nonzero TMD locked-disc state before regular-disc state | 86.63145 -> 86.63505; src 0x1e20 base 0x1e50 insns 1928/1940; kept |

| BS2Tick | 38 | 8137ED24/8137EFBC: express DVD transfer state bounds as 4 <= state < 6 | 86.63505 -> 86.63609; src 0x1e20 base 0x1e50 insns 1928/1940; kept |

| BS2Tick | 39 | 8137EE54–8137EF60: arrange close, ticket and error groups in target address order | 86.63609 -> 93.01392; src 0x1e20 base 0x1e50 insns 1928/1940; kept |

| BS2Tick | 40 | 8137F134: use wide signed millisecond conversion for cover-open delay | 93.01392 -> 93.39794; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

Gate 3: PASS; pool identical, regressions 0, forbidden/readability 0, DOL hash correct; Tick 93.39794%, 1932/1940 instructions. Retain TMD, region-switch, loader-positive, banner, partition and address-order corrections.

| BS2Tick | 41 | 8137DFxx: emit positive update-apploader read branch first | 93.39794 -> 93.84742; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

| BS2Tick | 42 | 8137E9AC: express actual banner alignment as subtraction of low address bits | 93.84742 -> 93.61495; src 0x1e34 base 0x1e50 insns 1933/1940; restored |

| BS2Tick | 43 | 8137EEEC: scan ticket bytes as unsigned bytes | 93.84742 -> 93.75413; src 0x1e30 base 0x1e50 insns 1932/1940; restored |

| BS2Tick | 44 | 8137EF60–8137F050: reconstruct error and abort exits before polling path | 93.84742 -> 94.28712; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

| BS2Tick | 45 | 8137F054–8137F0EC: reconstruct restart error and partition exits before drive path | 94.28712 -> 95.13505; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

| BS2Tick | 46 | 8137E3D8–8137E49C: emit cached partition branch before physical drive branch | 95.13505 -> 95.88454; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

| BS2Tick | 47 | 8137E59C: place unrestricted-title block before regional validation in address order | 95.88454 -> 96.23659; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 48 | 8137E650/8137E668: reconstruct Korean and Chinese title suffix switches | 96.23659 -> 96.39690; src 0x1e3c base 0x1e50 insns 1935/1940; kept |

| BS2Tick | 49 | 8137E070/8137E13C: evaluate update-state calls separately from short-circuit booleans | 96.39690 -> 96.62938; src 0x1e2c base 0x1e50 insns 1931/1940; kept |

| BS2Tick | 50 | 8137DEEC: put valid update disc state before invalid state | 96.62938 -> 96.82886; src 0x1e30 base 0x1e50 insns 1932/1940; kept |

| BS2Tick | 51 | 8137DD80: put update partition present branch before absent branch | 96.82886 -> 96.98711; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 52 | 8137E39C: put game-partition present branch before absent branch | 96.98711 -> 96.90464; src 0x1e38 base 0x1e50 insns 1934/1940; restored |

## CheckBS2CommandStatus end-to-end block map
8137CC28–CC54 frame 0x20/save29; CC58–CCF0 readiness and completion exits; CCF0–CD18 dispatch; CD18–CD58 seek; CD5C–CDD0 drive; CDD4–CE48 ID; CE4C–CEC0 TOC; CEC4–CF60 partitions; CF64–CFD8 BI3; CFDC–D054 TMD; D058–D0CC loader header; D0D0–D150 loader; D154–D1CC loader payload; D1D0–D258 banner; D25C–D27C returns. Prefix through CD74 aligns structurally. First blocker CD90 is a reload of CacheLength immediately after its store; compiler forwards the stored nonvolatile value. Re-translate the following chunks with typed pointers and fresh field expressions; do not add volatile.

| CheckBS2CommandStatus | 2 | CD18–CD90: test block-scoped report declaration at inline-helper boundary | 80.69704 -> 80.69704; src 0x610 base 0x658 insns 388/406; restored |

| CheckBS2CommandStatus | 3 | CEC4–CF60: retranslate partition length without early cached length temporary | 80.69704 -> 83.23645; src 0x620 base 0x658 insns 392/406; kept |

| CheckBS2CommandStatus | 4 | CF64–D27C: retranslate fixed and rounded cache chunks with SDK alignment operations | 83.23645 -> 83.23645; src 0x620 base 0x658 insns 392/406; restored |

| CheckBS2CommandStatus | 5 | CC74–CCC0: retranslate cache readiness as direct combined condition | 83.23645 -> 83.23645; src 0x620 base 0x658 insns 392/406; restored |

Gate 4-valid: PASS; pool identical, regressions 0, forbidden/readability 0. Tick 96.98711%, CheckBS2CommandStatus 83.23645%. Earlier gate 4 ran concurrently with an experiment and is discarded; only the stable rerun is evidence. CheckBS2CommandStatus frame/prefix align, remaining 392/406 count and missing global reloads are structural; not a register-only completion.

| BS2Tick | 53 | 8137E59C: declare extracted title prefix separately as signed word | 96.98711 -> 97.04948; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 54 | 8137E614: use suffix switch for US E and X-Y-Z region checks | 97.04948 -> 97.16392; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

## BS2StartGame full address-order translation
BD64–BD94 frame 0x50/save24 and CoverBlock; BD94–BE14 cover polling, report, NAND close; BE14–BE78 controller and boot fields; BE78–BED4 OS flags; BED4–BFF4 ticket/security/launch; BFF4–C0B4 IPC restoration; C0B8–C10C disc callback/poll; C10C–C194 error/fatal; C198–C244 identity and partition issue; C244–C318 partition result/error; C318–C364 fatal and partition reporting; C364–C3x legacy DI/audio/entry handoff. Frame and all non-poll blocks already align modulo registers. Target BD94 is a reloading empty CoverBlock.state loop; existing source uses the DVD status API to avoid unsafe compiler hoisting. C0E4/C130/C244/C2A0 likewise need repeated LowReadResult loads; current source uses interrupt calls. No volatile or assembly is permitted. Test distinct readable forms without accepting a hoisted asynchronous loop.

| BS2StartGame | 2 | C0F0–C194: retranslate disk completion and error dispatch as signed switch | 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; restored |

| BS2StartGame | 3 | C250–C318: retranslate partition completion, error and ticket dispatch as signed switch | 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; restored |

| BS2StartGame | 4 | BED4–BFF4: retranslate required IOS selection with full title ID temporary | 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; restored |

| BS2StartGame | 5 | BD64 frame: declare state flags and ticket output before transient values | 95.49618 -> 95.49618; src 0x644 base 0x624 insns 401/393; restored |

## BS2StartGCGame full address-order translation
C388–C3C4 frame 0x40, rtc sp+c, state flags sp+10, tickets sp+8; C3C4–C46C sound/video/language; C46C–C4A8 full-width RTC ticks; C4AC–C4E0 SRAM; C4E4–C53C NAND close; C53C–C594 controller/audio/state; C598–C5C8 legacy PI register; C5CC–C714 ES tickets/launch and return. First block still has API polling versus target field reload. One missing tail instruction is a hardware register readback: use the existing SDK PI register access definitions, not a new qualifier or hand-placed symbol.

| BS2StartGCGame | 2 | C598–C5C8: translate processor-interface control through existing SDK register macro | 98.24561 -> 98.24561; src 0x38c base 0x390 insns 227/228; restored |

| BS2StartGCGame | 3 | C388 frame: move state flag object beside RTC and ticket outputs | 98.24561 -> 98.24561; src 0x38c base 0x390 insns 227/228; restored |

| BS2StartGCGame | 4 | C46C–C4A8: retranslate RTC conversion through wide signed seconds macro | 98.24561 -> 98.24561; src 0x38c base 0x390 insns 227/228; restored |

| BS2StartGCGame | 5 | C3C4–C468: inline value temporaries at sound and progressive API boundaries | 98.24561 -> 98.24561; src 0x38c base 0x390 insns 227/228; restored |

## BS2NANDDivideCallback full address-order translation
C8B0–C8EC frame 0x10/save31 and cancellation; C8EC–C904 negative result; C904–C934 transferred/buffer and remaining bound; C934–C9AC write/read full chunk; C9AC–C9C8 callback error; C9C8–CA70 write/read final chunk; CA70–CA8C callback error; CA8C–CAAC completion/epilogue. Target reloads NandTransferred after store and rereads length/transferred at each later operation. Current compiler forwards nonvolatile globals. Translate early exits first, then chunk branches and completion in address order.

| BS2NANDDivideCallback | 2 | C8B0–C904: reconstruct cancellation and negative-result early returns | 85.03906 -> 85.03906; src 0x1dc base 0x200 insns 119/128; restored |

| BS2NANDDivideCallback | 3 | C904–C934: update byte pointer before transferred count | 85.03906 -> 85.00000; src 0x1dc base 0x200 insns 119/128; restored |

| BS2NANDDivideCallback | 4 | C9C8–CAAC: retranslate final chunk with explicit remaining-byte temporary | 85.03906 -> 70.85938; src 0x1dc base 0x200 insns 119/128; restored |

| BS2NANDDivideCallback | 5 | C934–CA70: use unsigned operation switch at NAND helper boundary | 85.03906 -> 84.94531; src 0x1dc base 0x200 insns 119/128; restored |

## BS2NANDDivideReadAsync full address-order translation
CAB0 frame 0x10/save31; six transfer-state stores; unsigned maximum 0x40000; report and NAND issue for full chunk; report and issue for final length; restore31/return. First structural gap is NandLength reload immediately after initialization. Body is fully represented in readable C but compiler forwards globals. No new qualifiers or artificial side effects are added.

| BS2NANDDivideReadAsync | 2 | initialization: keep file and buffer assignment before operation/length setup | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| BS2NANDDivideReadAsync | 3 | helper boundary: test direct block-scoped report prototype | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| BS2NANDDivideReadAsync | 4 | full-to-final chunk: retranslate length choice and common NAND issue | 60.31915 -> 35.31915; src 0x90 base 0xbc insns 36/47; restored |

| BS2NANDDivideReadAsync | 5 | initialization temporaries: snapshot incoming length through argument instead of stored global | 60.31915 -> 52.44681; src 0xc0 base 0xbc insns 48/47; restored |

## BS2NANDDivideWriteAsync full address-order translation
CB6C frame 0x10/save31; six transfer-state stores; unsigned maximum 0x40000; report and NAND issue for full chunk; report and issue for final length; restore31/return. First structural gap is NandLength reload immediately after initialization. Body is fully represented in readable C but compiler forwards globals. No new qualifiers or artificial side effects are added.

| BS2NANDDivideWriteAsync | 2 | initialization: keep file and buffer assignment before operation/length setup | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| BS2NANDDivideWriteAsync | 3 | helper boundary: test direct block-scoped report prototype | 60.31915 -> 60.31915; src 0xb4 base 0xbc insns 45/47; restored |

| BS2NANDDivideWriteAsync | 4 | full-to-final chunk: retranslate length choice and common NAND issue | 60.31915 -> 35.31915; src 0x90 base 0xbc insns 36/47; restored |

| BS2NANDDivideWriteAsync | 5 | initialization temporaries: snapshot incoming length through argument instead of stored global | 60.31915 -> 52.44681; src 0xc0 base 0xbc insns 48/47; restored |

## Run end-to-end instruction audit
B3EC–B3F0 CTR/LR handoff; B3F4–B464 clears r0,r2,r3,r5,r7..r31; B468–B470 resets stack to 0x81600000; B474–B484 cache-line zero/flush counted loop; B488–B490 clears r4 and returns through LR; B494 loops to cache block. Target has no C frame. Ordinary C cannot specify these ABI register and stack resets, and new assembly is forbidden. Re-translate the expressible cache and entry operations; do not invent dummy locals for the register reset.

| Run | 2 | B48C–B490: reconstruct boot entry with zero r3 and r4 arguments | 0.88372 -> 0.00000; src 0x78 base 0xac insns 30/43; restored |

| Run | 3 | B474–B484: translate counted cache loop as explicit while | 0.88372 -> 0.88372; src 0x78 base 0xac insns 30/43; restored |

| Run | 4 | B478–B484: translate cache bounds through end pointer | 0.88372 -> 0.88372; src 0x78 base 0xac insns 30/43; restored |

## BS2Tick second structural pass
All state groups have now been translated through the shared epilogue in target address order. 97.16392%, 1933/1940 instructions. Remaining concrete differences include initial scheduling, low-memory address materialization, DVD magic failure ordering, banner alignment, unsigned ticket scan and DVD state range branch form. Continue source forms at those exact blocks; register-only status has not been reached.

| BS2Tick | 55 | 8137D860–8137D890: reconstruct header pointer only after memcpy | 97.16392 -> 97.24020; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 56 | 8137DCCC: emit valid magic and region path before magic failure | 97.24020 -> 97.16908; src 0x1e38 base 0x1e50 insns 1934/1940; restored |

| BS2Tick | 57 | 8137D44C: establish audio setup flag before transfer zeroing | 97.24020 -> 97.06186; src 0x1e2c base 0x1e50 insns 1931/1940; restored |

| BS2Tick | 58 | 8137ED20/8137EFB8: translate active DVD state range as target switch form | 97.24020 -> 97.30825; src 0x1e3c base 0x1e50 insns 1935/1940; kept |

Run compiler binary exposes __dcbz and __dcbf intrinsics. These express the actual cache instructions as C, but do not expose the all-GPR and stack reset. Test intrinsic cache loop without introducing assembly.

| Run | 5 | B478–B47C: translate cache-line zero and flush with compiler cache intrinsics | compile failed |

Gate 5: PASS; pool identical, regressions 0, forbidden/readability 0; Tick 97.30825%. All eight full target functions have been read through their epilogues and at least three distinct source experiments compiled for each. This is not completion: several functions still have structural mismatches and do not meet the exact/register-only endpoint.

Tick device field is the existing SDK __OSDeviceCode at 800030E6; use that named SDK field rather than the raw absolute cast. No new volatile declaration or mapped symbol is introduced.

| BS2Tick | 59 | 8137D7A4–8137D7CC: use named SDK boot device code field | 97.30825 -> 97.30825; src 0x1e3c base 0x1e50 insns 1935/1940; restored |

| Run | 6 | B478–B47C: translate cache instructions with correct two-argument intrinsics | 0.88372 -> 16.74419; src 0x2c base 0xac insns 11/43; kept |

Run intrinsic cache translation is retained: 30 -> 11 instructions, 0.88372 -> 16.74419%. Prefix mtctr and cache loop now use actual target operations. CPU register/stack handoff remains outside the permitted C operations.

| Run | 7 | B474–B484: use unconditional cache loop as target, including zero-count behavior | 16.74419 -> 10.11628; src 0x24 base 0xac insns 9/43; restored |

| Run | 8 | B48C–B490: translate zero-valued boot arguments after intrinsic cache loop | 16.74419 -> 15.69768; src 0x30 base 0xac insns 12/43; restored |

| BS2Tick | 60 | 8137D44C: use typed partition reset descriptor and direct progress pointer | 97.30825 -> 97.30825; src 0x1e3c base 0x1e50 insns 1935/1940; restored |

| BS2Tick | 61 | 8137D44C: assign one actual initialization constant across reset fields | 97.30825 -> 97.30773; src 0x1e3c base 0x1e50 insns 1935/1940; restored |

| BS2Tick | 62 | 8137D44C and timeout blocks: keep clock temporary as signed OSTime | 97.30825 -> 97.30825; src 0x1e3c base 0x1e50 insns 1935/1940; restored |

GC target C5B4 stores the processor-interface control word, then C5B8 reads the same MMIO register back. This is a real target hardware readback, not a RAM reload. Translate it using the existing SDK PI access macros; no new volatile qualifier or addressed object is added. CoverBlock polling remains the separate unresolved issue.

| BS2StartGCGame | 6 | C598–C5C8: translate target PI control write and actual MMIO readback | 98.24561 -> 99.56140; src 0x390 base 0x390 insns 228/228; kept |

Test direct cover-state source control-flow forms only if compiler actually reloads in the loop. Reject hoisted polls even if fuzzy score rises.

| BS2StartGCGame | 7 | cover-prefix: translate target label and backward branch explicitly | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

| BS2StartGCGame | 8 | cover-prefix: translate target do-while read loop | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

| BS2StartGCGame | 9 | cover-prefix: translate break-controlled cover loop | 99.56140 -> 96.88596; src 0x390 base 0x390 insns 228/228; restored |

| BS2StartGame | 6 | cover-prefix: translate target label and backward branch explicitly | 95.49618 -> 93.94402; src 0x644 base 0x624 insns 401/393; restored |

| BS2StartGame | 7 | cover-prefix: translate target do-while read loop | 95.49618 -> 93.94402; src 0x644 base 0x624 insns 401/393; restored |

| BS2StartGame | 8 | cover-prefix: translate break-controlled cover loop | 95.49618 -> 93.94402; src 0x644 base 0x624 insns 401/393; restored |

Test the repository NO_INLINE helper boundary on the real BS2Report body. Original target retains direct calls to an empty report function; this experiment changes no behavior, data, qualifier or function name. Keep only measurable aggregate progress with no exact-function regression.

| BS2Report | 1 | inline helper boundary: explicitly retain report calls with repository NO_INLINE | compile failed |

| BS2Report | 2 | inline helper boundary: test compiler noinline declaration form for C | compile failed |

Gate 7: PASS; pool identical, regressions 0, forbidden/readability 0. Run cache intrinsics and GC processor-interface readback reviewed against target; no assembly, new qualifier, or hand-placed object. GC now 228/228 instructions with one opcode mismatch at the cover wait (bl API versus lwz state), not a register-only result.

| BS2StartGCGame | 10 | C490–C4A4: put timer frequency before signed seconds in full-width product | 99.56140 -> 99.42982; src 0x390 base 0x390 insns 228/228; restored |

| BS2Tick | 63 | 8137DCCC–8137DD98: include region and disc validity checks inside valid-magic branch | 97.30825 -> 97.78866; src 0x1e3c base 0x1e50 insns 1935/1940; kept |

| BS2Tick | 64 | 8137E59C–8137E5C4: reconstruct restricted title families as sparse switch | 97.78866 -> 97.70773; src 0x1e40 base 0x1e50 insns 1936/1940; restored |

| BS2Tick | 65 | 8137D938–8137D96C: assign GC layout successor after both magic branches | 97.78866 -> 97.83402; src 0x1e3c base 0x1e50 insns 1935/1940; kept |

Assembly audit found real unfinished loader control flow: 8137E014 falls directly into LoaderMain at E018; E808 likewise falls into E80C. The old C broke after loader initialization and delayed the first loader read to another tick. Remove both breaks to reproduce target behavior.

| BS2Tick | 66 | 8137E014/E808: restore immediate loader-main fallthrough after initialization | 97.83402 -> 98.04021; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 67 | 8137EEEC: promote ticket scan byte as unsigned before zero comparison | 98.04021 -> 98.25309; src 0x1e34 base 0x1e50 insns 1933/1940; kept |

| BS2Tick | 68 | 8137E9AC: reconstruct target banner alignment by removing low five address bits | 98.25309 -> 97.99278; src 0x1e38 base 0x1e50 insns 1934/1940; restored |

BS2Tick now 98.25309%, 1933/1940. Real semantic gaps corrected: loader initialization immediately enters LoaderMain in the same tick; valid RVL magic includes region and disc validity checks before the later magic-reject block; unsigned ticket byte comparison matches target. Reindent the reconstructed valid-magic scope for review; no instruction change intended.

| BS2Tick | 69 | 8137D98C: load streaming byte before clearing audio configuration flag | 98.25309 -> 98.24794; src 0x1e34 base 0x1e50 insns 1933/1940; restored |

Gate 8: PASS; pool identical, regressions 0, forbidden/readability 0; Tick 98.25309%, 1933/1940. Streaming snapshot attempt 69 restored because it lowered fuzzy without instruction-count gain. Review confirms the new initialization fallthroughs and MMIO readback are actual target operations. All remaining nonmatches are structural; none is claimed finished or register-only.

BS2Tick: current 98.25309%; src 0x1e34 base 0x1e50 insns 1933/1940. Detailed final ctxdiff: /tmp/bs2r2-final-BS2Tick.diff.

CheckBS2CommandStatus: current 83.23645%; src 0x620 base 0x658 insns 392/406. Detailed final ctxdiff: /tmp/bs2r2-final-CheckBS2CommandStatus.diff.

BS2StartGame: current 95.496185%; src 0x644 base 0x624 insns 401/393. Detailed final ctxdiff: /tmp/bs2r2-final-BS2StartGame.diff.

BS2StartGCGame: current 99.5614%; src 0x390 base 0x390 insns 228/228. Detailed final ctxdiff: /tmp/bs2r2-final-BS2StartGCGame.diff.

BS2NANDDivideCallback: current 85.03906%; src 0x1dc base 0x200 insns 119/128. Detailed final ctxdiff: /tmp/bs2r2-final-BS2NANDDivideCallback.diff.

BS2NANDDivideReadAsync: current 60.31915%; src 0xb4 base 0xbc insns 45/47. Detailed final ctxdiff: /tmp/bs2r2-final-BS2NANDDivideReadAsync.diff.

BS2NANDDivideWriteAsync: current 60.31915%; src 0xb4 base 0xbc insns 45/47. Detailed final ctxdiff: /tmp/bs2r2-final-BS2NANDDivideWriteAsync.diff.

Run: current 16.744186%; src 0x2c base 0xac insns 11/43. Detailed final ctxdiff: /tmp/bs2r2-final-Run.diff.

Unmet endpoint: instruction-exact remains 21/29. Run still lacks GPR/stack/LR reset, StartGame/StartGCGame cover polling still uses an API call, and NAND/cache globals still have missing reloads. The forbidden volatile/assembly/configuration tricks were not used. All eight have target block maps through their returns and distinct compiled source attempts, but the requested exact-or-register-only endpoint has not been achieved.

## Final full clean gate and endpoint audit

Instruction-exact 21/29 -> 21/29; objdiff code 4052/16980 -> 4052/16980; data 155504/158528 -> 155504/158528; unit fuzzy 84.64641 -> 94.98469.

INCOMPLETE: none of the eight reaches the exact-or-register-only endpoint. No compiler/register/qualifier bypass is used to conceal this.

BS2Tick: 76.669075 -> 98.25309%; 68 logged attempts. 1933/1940 instructions; address materialization, initial/store scheduling, partition reloads, title-prefix branch and banner alignment still differ. This is structural, not register-only.

CheckBS2CommandStatus: 80.697044 -> 83.23645%; 4 logged attempts. 392/406; target reloads CacheLength after stores and repeats loader/banner length loads; generated C forwards those globals. Prefix/frame aligned.

BS2StartGame: 95.496185 -> 95.496185%; 7 logged attempts. 401/393; cover API call replaces target load and low-level callback waits add interrupt calls; direct loops tested this round hoist the load and are rejected.

BS2StartGCGame: 98.24561 -> 99.5614%; 9 logged attempts. 228/228; cover API bl/compare/backward branch differs from target lwz/cmpwi/bne. Direct label, do-while and break loops all produce bne -4 with the load outside the loop and are rejected. Remaining RTC operand registers also differ.

BS2NANDDivideCallback: 85.03906 -> 85.03906%; 4 logged attempts. 119/128; transferred/length/buffer reloads are forwarded and cancellation callback load is scheduled before the store.

BS2NANDDivideReadAsync: 60.31915 -> 60.31915%; 4 logged attempts. 45/47; stored length and final length reloads are forwarded; registers also differ.

BS2NANDDivideWriteAsync: 60.31915 -> 60.31915%; 4 logged attempts. 45/47; stored length and final length reloads are forwarded; registers also differ.

Run: 0.88372093 -> 16.744186%; 7 logged attempts. 11/43; actual dcbz/dcbf counted loop now present, but target GPR clears, SP replacement and LR handoff have no ordinary C expression in the exposed compiler intrinsics. New assembly is forbidden.

Retained source commits: 7d4bdea4, ad5c371e, 240d7a58, 0d575639, cb4db7d6, 9c829f69, ccd3577f. Only src/BS2/BS2Mach.c and this attempt log changed.

Final full gate (no --quick), after clean object rebuild:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4052/16980 data 155504/158528 functions 21/29 fuzzy 94.9847 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 21/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 94.98469
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 95.496185
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: BS2NANDDivideCallback 85.03906
[src/BS2/BS2Mach]   below 100: BS2NANDDivideReadAsync 60.31915
[src/BS2/BS2Mach]   below 100: BS2NANDDivideWriteAsync 60.31915
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 83.23645
[src/BS2/BS2Mach]   below 100: BS2Tick 98.25309
[src/BS2/BS2Mach] baseline: code 4052/16980 data 155504 functions 21 fuzzy 84.6464
regressions vs baseline: 0
global matched_code_percent: 84.84254 -> 84.84254
global fuzzy_match_percent: 98.07848 -> 98.13709
global complete_code_percent: 59.34297 -> 59.34297
global matched_data_percent: 90.43305 -> 90.43305
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
