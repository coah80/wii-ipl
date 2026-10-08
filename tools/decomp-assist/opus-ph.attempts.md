# opus-ph attempts

Branch agent/w1008/data-d3-c. Measure: `odiff.py <unit> <symbol>` differing count.

## TMCJPEGDEC_err_restart

Start: rx5b finishRestart candidate (114/115 insns, odiff 73 differing because of the 1-insn shift).
Key finding: mwdbg backend-00 shows the marker test is already folded (`bt gt -> loop`) in the
initial PCode, so the target's `ble found; b loop` is decided before the backend. In matched
code (`__OSInitNet`) the same unfolded shape comes from `if (a || b) return;`, i.e. a jump the
IR folder does not treat as a goto.

- v0 rx5b baseline: 73/115 (114 insns).
- A `if (m>=D0 && m<=D7) break;` + finish after loop: 73.
- B `if (m>=D0 && m<=D7) return finish;`: 73.
- C `if (m<D0 || m>D7) continue; return finish;`: 73.
- E nested `if (m>=D0) { if (m<=D7) return finish; }`: 73.
- H `goto found` after loop: 73.
- I empty-then / else return: 73.
- D1 `{ result = 0; continue; }`: 73. D2 else-arm assignment: 73. D3 continue/else break: 73.
- W1 do/while(byte<D0||byte>D7) using byte: 73. W2 byte instead of marker: 73.
- W3 marker as loop-carried while condition: 98/118.
- E1 else-if chain: 73. E2 inverted D9 test: 81. E3 inverted D9 inner test + break: 76.
- G1 `goto retry` label before inner while: 73.
- P1/P2/P3 isRestartMarker inline predicate (3 shapes x 2 uses): 76-78, 118-119 insns.
- S1 `switch (marker) { case 0xD0..0xD7: return finish; }`: 21/115, size equal. Switch
  lowering emits the unfolded `bge case; b default`, but as signed `cmpwi d8; bge; cmpwi d0`
  instead of target `cmplwi d0; blt; cmplwi d7; ble; b`. Marker lands in r4 not r6.
- S2 switch on (u32): 21. S3 default: continue: 21. S4 default: break: 21.
- S5/S6/S7 marker as u32/s32/u16 with switch: 21 (switch compares stay signed).

Result: not exact. Best is S1 (equal size, 21 differing). Remaining: switch compares are signed
and use a different tree (hi+1 then lo); marker gets r4 instead of r6, which shifts the finish
block's temporaries. Next lever: a construct whose jump the IR folder leaves alone (like the
`return` in `__OSInitNet`) but keeps the unsigned `cmplwi d0 / blt / cmplwi d7 / ble` order.

## getUnScrambleId

Start: rx30 id-08 (loop + inline helpers). That source is now auto-inlined into both C callers
(target keeps it out of line), so loop forms are out; the function must be written unrolled.
Metric below is (insns, exact positional, opcode positional) out of 161.

- u1 unrolled inline get/set/unscramble helpers: 156 differing.
- m1 macros GET_BYTE/SET_BYTE/UNSCRAMBLE, lazy permutation: 159 differing; multiset differs
  only by two rlwimi shift-combines (b2/b3 read from rotated hi in target).
- x1 read all six bytes into b0..b5 first, then set: 111 differing.
- x1 extraction orders (4) / declaration order: 111-112.
- xf/xg `(x >> 1) | ((x & 1) << 52)` rotation: b2/b3 match but b1/b4/b5 stop combining; 113.
- greedy over GET/SET/UNSCRAMBLE/rotation/mask/permutation/substitution/final forms (24 builds):
  best r2 (`mixId |= (mixId & 1) << 53; mixId >>= 1;`) + t2 (substitution via `b` temp): 69.
- p3 copy + `b = GET_BYTE(copy, k); mixId = SET_BYTE(mixId, i, b);`: 68 (prologue and rotation
  now exact; b3 combine matches).
- greedy from p3 over all dims + declaration orders (≈30 builds): no gain.
- SET split into &=/|= (3 variants): 162-166 insns. inline get/set helpers: 161-163, ≤93 exact.
- b as u32/int/u16/s32: 164-175 insns. GET without cast / const shift / u64 cast: unchanged.
- SET mask spellings, (u8) value cast, assignment-macro, block-scoped/const copy: unchanged.
- per-pair inline GET in SET for subsets of the six moves: worse.
- distinct b0..b5 lazily: 156. separate perm/subst temps: 163 insns.
- 160 spellings of the mask/xor/rotate statements: all identical (IR canonicalizes).

Finding: mwdbg backend-00 shows MWCC splits this straight-line function into ~100-instruction
blocks at statement ends (B1 ends after `b = GET_BYTE(copy, 2)` at 103; before it 97). Combines
and scheduling are block-local. The target splits one statement earlier (b2/b3 both read the
uncombined rotated hi), so the original has 1-6 more initial PCode instructions before set 3.
No natural spelling found that adds them without changing final code.

Best: 161/161, 68 differing (93 exact positional), saved in opus-ph.best.c.

## Round 2 (higher effort)

### getUnScrambleId: exact

- u1 substitution as a `for (i = 0; i < 6; i++)` loop over GET/SET: 68 (identical to the unrolled form;
  MWCC fully unrolls it, so loop source is fine as long as the function stays out of line).
- final step spellings: `return (rot) ^ B3` 61 (tail exact), operand swap 67, copy temp 68, split 80.
- copies/temps at the start (id_direct, copyfirst, idcopy, block-scoped inst temp): 68, IR propagates them.
- inline u8 getByte for the permutation only: 156 (different prologue allocation).
- permutation statement orders (source order, reversed): 148-159.
- prior art: `gh search code getUnScrambleId` found SMGCommunity/Petari src/RVL_SDK/nwc24/NWC24UserId.c
  (same SDK, same 0x284 size in SMG). Its shape: static `getbyte`/`setbyte` helpers (auto-inlined), a
  `static const u8 ExcTable[8] = {1, 5, 0, 4, 2, 3, 6, 7}` permutation table read in a `u8 i` loop,
  a second loop for the TtableInv substitution, rotation spelled `v |= (((v & 0xFF) << 5) & 0x20) << 48`.
  Compiled as is: 0/161. Unrolling the ExcTable loop by hand gives 159/163, so the table loop is what
  shapes the PCode blocks. ExcTable lands in .sdata2 of the object (constant-folded after unrolling,
  never referenced) and the linker dead-strips it: main.dol SHA1 unchanged, gate data 16/16.
- Final: renamed to repo style (getByte/setByte/copy/id), still 0/161; NWC24CheckUserId and
  NWC24iCheckUserIdCRC stay 0. gate.py --quick: GATE PASS.

### TMCJPEGDEC_err_restart: not exact (best stays S1, 21/115, equal size)

Standalone harness (/tmp, same flags, `-ipa file`) to test the range-test shape. Target wants
`cmplwi d0; blt test; cmplwi d7; ble F; b test` (unsigned, unfolded).
- switch lowering is always signed and hi-first (`cmpwi hi+1; bge def; cmpwi lo; bge case; b def`),
  for u8, u32, `unsigned long`, `(u32)` casts, `m - 0xD0` with cases 0..7, `(u8)(m - 0xD0)`, and even
  case values >= 0x80000000. So the target is not a switch.
- if-forms all fold to `bgt test` (≈45 shapes): &&/|| in either direction, continue/break/goto
  found/goto label, do-while with `||` or `!(&&)`, else-if chains, nested ifs, empty then, else
  continue, flag loops (`found`, `keepGoing` style as in parse_para), ternary conditions,
  `(u32)(m - 0xD0) <= 7`, `(m & 0xF8) == 0xD0`, the whole loop inside a static inline.
- `{ r = 0; continue; }`, `{ m = 0; continue; }`, `{ nop(); continue; }`, `{ (void)0; continue; }`:
  still folded (IR removes the dead statement before folding).
- IRO 0 around the function (levers.md 26): no change (21 / 73). Target shows no IRO-off symptoms.
- inline predicates with `return` (`if (m < D0 || m > D7) return 0; return 1;`) give the unfolded
  `ble` but materialize a bool (`li r0,0/1; cmpwi; beq`) that the target lacks.
- Scan of all compiled C objects: unfolded backward `bc +8; b back` appears only in switch lowering
  (NHTTP) and inline-function exits (VF Advance/MoveTo); in retail, err_restart is the only
  `cmplwi lo; blt; cmplwi hi; ble +8; b back` in the DOL.
- Mechanism found (t13): a then-arm with a surviving non-jump statement, e.g.
  `if (m < 0xD0 || m > 0xD7) { last = r; continue; }`, gives exactly `blt X; cmplwi d7; ble F;
  X: mr; b top`. The target matches this if that statement is a register copy that coalesces away
  after the IR fold (same as tolower's empty ternary arm in MSL stricmp). No natural loop-carried
  register variable exists in this function to carry such a copy (byte is address-taken, result/
  marker are dead on that path), so not adopted.
- upstream koopthekoopa C (read-only) is the same nonmatching shape as our #else branch.
Next lever: find what loop-carried value the original kept in a register on the "other marker" path
(the copy that vanished), e.g. a marker/previous-marker variable or a result carried to the EOI return.
