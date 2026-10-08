# opus-mwdbg: unblocking mwdbg for large C++ units, and regsim verdicts (base d9d33ca0)

These are tool changes only. No source file in this worktree was edited. The tool changes are in `_mwdbg` (see its README section "Emulator limits, sjiswrap, and the socket stub").

## Why mwdbg stopped (follow-up to opus-ties.attempts.md)

1. The 1 MB stack overflowed. The emulator now reads `RETROWIN32_MEMORY_MB` and `RETROWIN32_MIN_STACK_MB`, and mwdbg.py sets them to 1024 and 32 by default (`--memory-mb`, `--stack-mb`).
2. `ws2_32!send` was missing. I added a builtin ws2_32 that logs every call to `<capture>/socket.log`. With that log, the message turned out to be `(10430) system does not support converting from 'SHIFT-JIS', treating as ASCII`. Afterwards the compiler longjmps through an empty jmp_buf (`WRITE_UNMAPPED @40495a`, esp 0).
3. The cause of that message: mwdbg drops `wibo sjiswrap.exe` from the Ninja command, so the compiler read UTF-8 sources directly and could not convert them. retrowin32 now emulates sjiswrap when `RETROWIN32_SJISWRAP=1`, and mwdbg.py turns it on automatically when the Ninja command uses sjiswrap. The emulation re-encodes source files to Shift JIS, makes `GetACP` return 932, has `IsValidCodePage(932)` succeed, and decodes code pages 0 and 932 in MultiByteToWideChar.
4. Then iplESMisc failed with `(10151) the file 'nw4r/lyt/textbox.h' cannot be opened`. The file on disk is `textBox.h`, and wibo matches paths case-insensitively. retrowin32 now falls back to a case-insensitive match when the exact path is missing.
5. regsim reproduced the iplESMisc capture only 157/161. The capture needed a second pass with a spill candidate, and regsim picked the spill node by maximum degree. MWCC picks by minimum `cost/degree`, with ties going to the later node in scan order. After fixing that, the capture reproduces 161/161, and `examples/pressure` goes from 108/126 to 126/126. None of the other 76 stored runs changed.

## Validation (data-d4, build/43U objects rebuilt before comparing)

| capture | regsim | unit.o vs ninja object |
|---|---|---|
| kbd_lib / kbdProcMod | 156/156 | identical (sha256 6a85c207…) |
| iplESMisc / DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap | 161/161 (2 GPR passes) | identical (8a31efdb…) |
| tiZiString / update__Q39textinput8tistring6WithZiFv | 161/161 | identical (da68c526…) |
| www_wiisetting / Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue | 312/312 | identical (ff8f136d…) |

## Verdicts

Method: `_mwdbg/scratch_opusmwdbg/vmap2.py` builds the want-list. It aligns the scheduled PCode with our object using difflib, because opus-ties.vmap.py's index alignment drifted and left 210 operand mismatches on tiZiString. Each want is keyed by virtual number, since names such as `candidate`, `output` and `i` repeat. A virtual is kept when at least 75% of its uses agree on one target register. `_mwdbg/scratch_opusmwdbg/regsim_locals.py` then anneals over the numbering of real source locals only, leaving `@` temps, parameters and unnamed values in place. For www_wiisetting I enumerated every ordering of its 8 locals instead.

| function | wants | as built | best with source locals reordered | best with `@` values reordered too | verdict |
|---|---|---|---|---|---|
| DeleteUnauthorizedData | 64 | 54 | 60 | 64 | structural |
| WithZi::update | 98 | 83 | 92 | 98 | structural (callee-saved part fixable by order) |
| wiisetting::Getter_ | 159 | 156 | 156 (exhaustive, 8! orders) | not needed | structural |

- **DeleteUnauthorizedData** is `return InitSavedata(heap);`. Every mismatched value is a local of an inlined function, which is why they all have `@` names.
  - InitSavedata: v33 `titleIds`, v34 `ret`, v35 `ticketScratch`, v36 `i`.
  - verifySavedataZD: v37/38 `titleId` parameter (hi/lo), v39/40 `block`, v41 `valid`, v42 `j`, v43 `offset`, v44 `deleteSaveData`, v45 `fileOpen`, v46 `saveData`, v47 `ret`.
  - DeleteTicketsForce: v49/50 `titleId`, v51 `j`, v52 `ret`, v53 `ticketViewList`.

  Reordering locals inside each inlinee reaches 60/64. That search was exhaustive over InitSavedata × DeleteTicketsForce and annealed over verifySavedataZD. The four misses are `titleId` v37/v38 (wants r19/r20) against `saveData`/`deleteSaveData` (want r30/r31). Reaching 64/64 requires numbering the inlined `titleId` parameter after verifySavedataZD's locals, and declaration order can't do that. A possible lever, still untested: copy `titleId` into a local in verifySavedataZD that is declared last, or change how titleId is passed.
- **WithZi::update**: reordering locals fixes the 9 callee-saved mismatches (index, destination, source, length v44, count, elementCount, v64, v70, v175). The order regsim found, lowest number first: index, character, length(v37), position, keyIndex, source, copied, wordLength, elementCount, count, candidate(v34), output(v38), candidate(v47), length(v44), destination, candidateOutput, output(v49), output(v36). It is untested and may conflict with nested scopes.

  Six volatile-register misses remain: copied r4→r5, wordLength r7→r4, @1343 r6→r7, @1338 r5→r4, @1330 r5→r6, v148 r5→r4. @1343/@1341, @1338/@1336 and @1349 are the induction pointers of the 8-way unrolled copy loop, and @1330 is `length-8`. All of these are optimizer temps. They reach 98/98 only when the temps are renumbered, so this is structural, and it needs a loop shape that makes the unroller create its temps in a different order.
- **wiisetting::Getter_**: no ordering of the 8 locals (str, val, i ×3, kbLang, staIdx, retVal) improves on 156/159. The misses are `i`(v35) r25→r31, `i`(v38) r25→r26 and temp `@17419`(v42) r26→r25. This confirms opus-ties' result that swapping `strBuf`/`i` changes nothing, so the function is structural.
