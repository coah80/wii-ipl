# Scenes round 2 attempts

Baseline: merged main `4f78910f`. Original function symbols present: Setting 112/112, SDChannelSelect 129/129, SDMemory 66/66; no missing functions or assembly bodies.

## Retained changes

- `checkIPString`: NO_INLINE alone produced 38/38 instructions and 28 register differences. Explicit conditional returns produced 38/38, diffs 0, objdiff 100%.
- `calcFadeout`: restored the actual `hoge` OSReport argument. Raw instructions were already identical; the relocation was wrong. Objdiff now 100%.
- Setting vtable: removed an undefined calc override from the owner-only header branch; original vtable uses inherited FaderSceneBase::calc.
- SDMemory create: restored cache-count branching, N_Btn_3/N_Btn_4 visibility, display mode and button label. Trial 1:1085/1064 instructions; ordinary new trial 2:1078/1064; advancing cache pointer trial 3:1076/1064. Retained ordinary typed new and indexed cache loop.
- SDMemory setScrollLimit: original pane is N_Body and offset is 160.0. Direct arithmetic trial matched 81/81 with diffs 0; named item-height trial had 12 differences; loading heights before count had 9. Retained direct arithmetic.
- SDMemory drawTransferTitles: target-derived rewrite 419/451 instructions; componentwise memo translation, VEC2 out-of-line declaration, actual color helper, and corrected 500/40/79.5 literals:422/451. Its subsequent three condition-lifetime trials are below. All small data sections now match.
- SDChannelSelect: moved existing functions to original object order, preserved isChannelReady dont_inline pair; .sdata2 first 80 bytes became identical. Replaced three local const title-ID objects with their ordinary comparison literals; section is now exactly 80 bytes and 100%.
- Setting createBrowser: restored separator/path/separator reporting and RSO reporting after ICInvalidateRange.
- Setting draw: restored N_Tra0 and Tex0/Tex1/Tex2 material lookups, texture assignments and transition restart. Replaced opaque animation structure with actual FrameController pointers under IPL_SETTING_IMPLEMENTATION. Corrected opaque and fade colors and centered screen rectangle from integer absolute dimensions.
- Setting initScroll: re-derived all 277 instructions block by block: show AP2..AP7; switch 0/1/2/3 falls through hide calls; initialize animation; hide arrow and AP1; <= count branch first; indexed visibility loops; final state stores. 277/277, diffs 0, objdiff 100%.
- Setting scanAP: restored actual N_AP1/N_AP6/N_AP0/N_AP7 pane literals. validateEULA error tag is ES. Error-dialog spacing is 78.0, not 46.0. Used ordinary wide format literals. Both .sdata and .sdata2 now match.
- SDMemory: placed onDialogState7 before 8 and transfer-drawing helpers immediately after drawTransferTitles.

## Remaining functions and new attempts

Every remaining objdiff function has at least three distinct successful source builds this round. Trials were restored unless recorded above. Counts below come from the final retained source. Compiler-folded condition/temporary changes are explicitly recorded without claiming progress.

### src/scene/setting/iplSetting

- `makeSupportCode` 99.078950%: 76/76 instructions; register allocation or operand scheduling differs.
  - retain title length separately from appended length: build 0; src 0x130 base 0x130 insns 76/76; diffs 13: [30, 32, 35, 38, 40, 46, 49, 51, 54, 56, 58, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - measure support code before appending label: build 0; src 0x130 base 0x130 insns 76/76; diffs 19: [6, 17, 38, 40, 42, 46, 47, 48, 49, 50, 51, 52, 54, 56, 57, 58, 59, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use named append cursors: build 0; src 0x12c base 0x130 insns 75/76; --- replace mine 38:39 base 38:39; POOL IDENTICAL up to 108 (mine=108 base=108).
- `convertRevIP` 98.150690%: 73/73 instructions; register allocation or operand scheduling differs.
  - name branch condition 6: build 0; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 5: build 0; src 0x134 base 0x124 insns 77/73; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `updateScroll` 94.469280%: 183/179 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0x2dc base 0x2cc insns 183/179; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0x2dc base 0x2cc insns 183/179; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 3: build 0; src 0x2dc base 0x2cc insns 183/179; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 8:9 target 8:9, replace mine 12:13 target 12:13, replace mine 17:18 target 17:18, delete mine 20:22 target 20:20, insert mine 23:23 target 21:22, replace mine 24:25 target 23:24.
- `createBrowser` 93.687706%: 308/301 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 6: build 0; src 0x4b8 base 0x4b4 insns 302/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 5: build 0; src 0x4b4 base 0x4b4 insns 301/301; diffs 143: [0, 2, 3, 16, 18, 20, 45, 65, 67, 69, 71, 135, 136, 137, 138, 139, 140, 141, 142, 143]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0x4b4 base 0x4b4 insns 301/301; diffs 143: [0, 2, 3, 16, 18, 20, 45, 65, 67, 69, 71, 135, 136, 137, 138, 139, 140, 141, 142, 143]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 0:1 target 0:1, replace mine 2:4 target 2:4, replace mine 16:17 target 16:17, replace mine 18:19 target 18:19, replace mine 20:21 target 20:21, replace mine 45:46 target 45:46.
- `scanAP` 88.106620%: 255/272 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 9: build 0; src 0x424 base 0x440 insns 265/272; --- delete mine 5:6 base 5:5; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 8: build 0; src 0x424 base 0x440 insns 265/272; --- delete mine 5:6 base 5:5; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 7: build 0; src 0x424 base 0x440 insns 265/272; --- delete mine 5:6 base 5:5; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 7:8 target 7:8, replace mine 38:39 target 38:39, replace mine 49:50 target 49:50, replace mine 90:91 target 90:91, replace mine 94:95 target 94:95, replace mine 99:100 target 99:100.
- `setUSBAP` 78.421050%: 55/57 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 3: build 0; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 7:9 target 7:9, replace mine 10:11 target 10:12, replace mine 14:15 target 15:16, replace mine 19:25 target 20:21, replace mine 39:40 target 35:44, delete mine 41:43 target 45:45.
- `calcKeyboard` 75.624140%: 293/290 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 6: build 0; src 0x494 base 0x488 insns 293/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 5: build 0; src 0x4ac base 0x488 insns 299/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0x494 base 0x488 insns 293/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 0:1 target 0:1, replace mine 2:5 target 2:6, delete mine 6:7 target 7:7, replace mine 8:9 target 8:18, replace mine 11:12 target 20:21, replace mine 13:17 target 22:25.
- `calcNormal` 67.917960%: 1096/1158 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 63: build 0; src 0x1120 base 0x1218 insns 1096/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 62: build 0; src 0x1130 base 0x1218 insns 1100/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 61: build 0; src 0x1120 base 0x1218 insns 1096/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 36:37 target 36:37, replace mine 125:127 target 125:127, replace mine 166:167 target 166:167, delete mine 173:176 target 173:173, replace mine 181:182 target 178:179, replace mine 187:188 target 184:185.
- `initKeyboard` 67.309860%: 211/213 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 6: build 0; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 5: build 0; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 4: build 0; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 8:9 target 8:9, delete mine 17:18 target 17:17, delete mine 19:20 target 18:18, replace mine 26:27 target 24:25, replace mine 33:34 target 31:32, replace mine 35:44 target 33:40.
- `validateEULA_` 64.414894%: 93/94 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 3: build 0; src 0x174 base 0x178 insns 93/94; --- replace mine 5:6 base 5:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 2: build 0; src 0x188 base 0x178 insns 98/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 1: build 0; src 0x188 base 0x178 insns 98/94; --- replace mine 5:6 base 5:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 5:6 target 5:8, replace mine 7:10 target 9:10, replace mine 11:12 target 11:12, insert mine 16:16 target 16:17, delete mine 17:18 target 18:18, replace mine 37:38 target 37:53.
- `setAPDraw` 62.204678%: 148/171 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 3: build 0; src 0x250 base 0x2ac insns 148/171; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 2: build 0; src 0x260 base 0x2ac insns 152/171; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 1: build 0; src 0x250 base 0x2ac insns 148/171; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 6:7 target 6:7, replace mine 8:22 target 8:23, replace mine 25:26 target 26:27, replace mine 27:28 target 28:29, replace mine 30:32 target 31:33, insert mine 33:33 target 34:35.
- `draw` 49.120255%: 412/632 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 10: build 0; src 0x460 base 0x9e0 insns 280/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 9: build 0; src 0x450 base 0x9e0 insns 276/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name branch condition 8: build 0; src 0x460 base 0x9e0 insns 280/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - Target/source block differences: replace mine 0:1 target 0:1, replace mine 2:4 target 2:8, replace mine 8:9 target 12:13, replace mine 10:12 target 14:16, replace mine 14:15 target 18:19, replace mine 21:22 target 25:26.

### src/scene/sdChannelSelect/iplSDChannelSelect

- `startPageTransition` 99.888885%: 45/45 instructions; two vector stack slots are reversed, 5 operand differences.
  - initialize transform input by components: build 0; src 0xb0 base 0xb4 insns 44/45; --- replace mine 16:17 base 16:21; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve channel pane before constructing transform input: build 0; src 0xb8 base 0xb4 insns 46/45; --- insert mine 16:16 base 16:21; POOL IDENTICAL up to 101 (mine=101 base=101).
  - copy through vector base reference: build 0; src 0xb4 base 0xb4 insns 45/45; diffs 5: [17, 24, 28, 29, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `flushSaveDataAndMountSD` 99.657140%: 35/35 instructions; heap/manager loads are reversed, 2 instruction differences.
  - name branch condition 1: build 0; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cache flush heap before looking up manager: build 0; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain save manager across flag update and flush: build 0; src 0x88 base 0x8c insns 34/35; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use manager and heap references for flush: build 0; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `handleSDTitleListResult` 99.152050%: 170/171 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 15: build 0; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 14: build 0; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 13: build 0; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 9:10 target 9:10, replace mine 14:15 target 14:15, replace mine 30:31 target 30:32, replace mine 115:116 target 116:117, replace mine 121:123 target 122:124, replace mine 126:128 target 127:129.
- `calcCommon` 99.074070%: 109/108 instructions; unused SDButton event-handler second argument emits an extra li r5,0.
  - name branch condition 6: build 0; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 5: build 0; src 0x1cc base 0x1b0 insns 115/108; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x1c4 base 0x1b0 insns 113/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 8:9 target 8:9, replace mine 13:14 target 13:14, replace mine 21:22 target 21:22, delete mine 23:24 target 23:23.
- `initializeNormalPage` 98.936170%: 95/94 instructions; unused SDButton event-handler second argument emits an extra li r5,0.
  - name branch condition 3: build 0; src 0x18c base 0x178 insns 99/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 2: build 0; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 1: build 0; src 0x194 base 0x178 insns 101/94; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 9:10 target 9:10, replace mine 16:17 target 16:17, delete mine 50:51 target 50:50.
- `selectChannel` 98.305084%: 60/59 instructions; unused SDButton event-handler second argument emits an extra li r5,0.
  - name branch condition 2: build 0; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 1: build 0; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cache base pane translation before animation setup: build 0; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve button before updating selected channel: build 0; src 0xf4 base 0xec insns 61/59; --- replace mine 5:7 base 5:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compare arrow visibility explicitly: build 0; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: delete mine 41:42 target 41:41.
- `collectTitlesFromNandUsage` 97.833336%: 102/102 instructions; output-count increment and usage loads are scheduled differently, 4 differences.
  - name branch condition 4: build 0; src 0x194 base 0x198 insns 101/102; --- insert mine 69:69 base 69:72; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x1a8 base 0x198 insns 106/102; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 2: build 0; src 0x1a0 base 0x198 insns 104/102; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 101 (mine=101 base=101).
- `collectTitlesByUsage` 97.811880%: 101/101 instructions; output-count increment and usage loads are scheduled differently, 4 differences.
  - name branch condition 4: build 0; src 0x190 base 0x194 insns 100/101; --- insert mine 67:67 base 67:70; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x1a4 base 0x194 insns 105/101; --- replace mine 21:22 base 21:22; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 2: build 0; src 0x19c base 0x194 insns 103/101; --- replace mine 21:22 base 21:22; POOL IDENTICAL up to 101 (mine=101 base=101).
- `enqueueNotice` 97.511110%: 46/45 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 10:11 target 10:12, delete mine 12:13 target 13:13, delete mine 18:19 target 18:18.
- `onEventDerived` 95.680560%: 140/144 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 10: build 0; src 0x240 base 0x240 insns 144/144; diffs 110: [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 9: build 0; src 0x230 base 0x240 insns 140/144; --- insert mine 20:20 base 20:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 8: build 0; src 0x234 base 0x240 insns 141/144; --- insert mine 20:20 base 20:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: insert mine 20:20 target 20:27, replace mine 21:25 target 28:29, replace mine 32:33 target 36:38, replace mine 34:35 target 39:40, replace mine 43:44 target 48:49, replace mine 45:46 target 50:51.
- `enqueueLoadNotice` 95.652176%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:8, delete mine 17:18 target 17:17.
- `enqueuePageNotice` 95.652176%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:8, delete mine 17:18 target 17:17.
- `enqueueResultNotice` 95.652176%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:8, delete mine 17:18 target 17:17.
- `enqueueMoveNotice` 95.652176%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:8, delete mine 17:18 target 17:17.
- `enqueueErrorNotice` 95.652176%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:8, delete mine 17:18 target 17:17.
- `enqueueStateNotice` 95.130430%: 24/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:8 target 7:9, delete mine 9:10 target 10:10, delete mine 17:18 target 17:17.
- `destroy` 95.097565%: 203/205 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 7: build 0; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 6: build 0; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 5: build 0; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: insert mine 11:11 target 11:12, replace mine 13:14 target 14:15, insert mine 20:20 target 21:22, delete mine 21:22 target 23:23, replace mine 61:62 target 62:63, insert mine 98:98 target 99:101.
- `drawChannelTransitionObjects` 94.974846%: 153/159 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0x294 base 0x27c insns 165/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x274 base 0x27c insns 157/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x294 base 0x27c insns 165/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 6:10 target 6:20, replace mine 12:13 target 22:26, replace mine 15:29 target 28:29, replace mine 31:32 target 31:32, replace mine 33:34 target 33:35, replace mine 35:36 target 36:37.
- `applyChannelMove` 94.669230%: 130/130 instructions; register allocation or operand scheduling differs.
  - name branch condition 4: build 0; src 0x208 base 0x208 insns 130/130; diffs 61: [41, 43, 46, 50, 51, 52, 57, 61, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x208 base 0x208 insns 130/130; diffs 61: [41, 43, 46, 50, 51, 52, 57, 61, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 2: build 0; src 0x218 base 0x208 insns 134/130; --- replace mine 12:13 base 12:13; POOL IDENTICAL up to 101 (mine=101 base=101).
- `enqueueFinishNotice` 94.444440%: 19/18 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x4c base 0x48 insns 19/18; --- insert mine 8:8 base 8:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: delete mine 12:13 target 12:12.
- `create` 94.239720%: 146/146 instructions; register allocation or operand scheduling differs.
  - name branch condition 3: build 0; src 0x248 base 0x248 insns 146/146; diffs 84: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 2: build 0; src 0x248 base 0x248 insns 146/146; diffs 84: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 1: build 0; src 0x248 base 0x248 insns 146/146; diffs 84: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `enqueueStartNotice` 94.117645%: 18/17 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x48 base 0x44 insns 18/17; --- insert mine 8:8 base 8:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: delete mine 12:13 target 12:12.
- `onEventDerived` 94.085720%: 103/105 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 6: build 0; src 0x1ac base 0x1a4 insns 107/105; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 5: build 0; src 0x1ac base 0x1a4 insns 107/105; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x19c base 0x1a4 insns 103/105; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 19:20 target 19:20, replace mine 25:26 target 25:26, replace mine 27:29 target 27:32, replace mine 30:31 target 33:35, replace mine 37:38 target 41:42, replace mine 43:46 target 47:48.
- `onButtonEvent` 93.736270%: 87/91 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 7: build 0; src 0x16c base 0x16c insns 91/91; diffs 50: [22, 24, 26, 27, 33, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 6: build 0; src 0x16c base 0x16c insns 91/91; diffs 39: [22, 24, 26, 27, 33, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 5: build 0; src 0x160 base 0x16c insns 88/91; --- replace mine 17:18 base 17:18; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 17:18 target 17:18, replace mine 20:21 target 20:21, replace mine 22:25 target 22:25, replace mine 26:28 target 26:28, replace mine 33:34 target 33:34, replace mine 36:38 target 36:38.
- `setChannelScissor` 93.484980%: 233/233 instructions; register allocation or operand scheduling differs.
  - name branch condition 6: build 0; src 0x3ac base 0x3a4 insns 235/233; --- replace mine 38:42 base 38:42; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 5: build 0; src 0x3ac base 0x3a4 insns 235/233; --- replace mine 38:42 base 38:42; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x3ac base 0x3a4 insns 235/233; --- replace mine 38:42 base 38:42; POOL IDENTICAL up to 101 (mine=101 base=101).
- `isCurrentTitleUsageEnough` 93.078430%: 50/51 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 2: build 0; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 1: build 0; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - for loop with explicit while and increment: build 0; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 5:6 target 5:6, replace mine 7:9 target 7:9, replace mine 35:37 target 35:44, delete mine 38:44 target 45:45.
- `enqueueChannelNotice` 90.869570%: 25/23 instructions; command stores and zero/type registers differ.
  - initialize command payload in reverse order: build 0; src 0x64 base 0x5c insns 25/23; --- replace mine 7:12 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in payload first order: build 0; src 0x64 base 0x5c insns 25/23; --- replace mine 7:12 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize command payload in title before flags order: build 0; src 0x64 base 0x5c insns 25/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 7:9 target 7:9, delete mine 10:11 target 10:10, replace mine 15:16 target 14:15, delete mine 18:19 target 17:17.
- `handleSDChannelUpdateComplete` 86.824070%: 105/108 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0x1a4 base 0x1b0 insns 105/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x1a4 base 0x1b0 insns 105/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x1ac base 0x1b0 insns 107/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 9:10 target 9:10, replace mine 11:12 target 11:12, replace mine 15:19 target 15:19, insert mine 26:26 target 26:27, delete mine 27:28 target 28:28, replace mine 33:34 target 33:34.
- `getCurrentTitleUsage` 86.823530%: 49/51 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 2: build 0; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 1: build 0; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - for loop with explicit while and increment: build 0; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 5:6 target 5:6, insert mine 7:7 target 7:10, delete mine 8:11 target 11:11, replace mine 31:32 target 31:32, replace mine 33:38 target 33:38, replace mine 39:42 target 39:44.
- `collectTitlesByChannelOrder` 86.555560%: 118/126 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0x1d4 base 0x1f8 insns 117/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0x1e8 base 0x1f8 insns 122/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0x1d8 base 0x1f8 insns 118/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 5:11 target 5:11, replace mine 15:30 target 15:30, replace mine 32:34 target 32:34, replace mine 35:38 target 35:41, replace mine 39:56 target 42:59, replace mine 57:59 target 60:62.
- `processWorkerCommands` 83.055214%: 327/326 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 11: build 0; src 0x52c base 0x518 insns 331/326; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 10: build 0; src 0x51c base 0x518 insns 327/326; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 9: build 0; src 0x51c base 0x518 insns 327/326; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 8:9 target 8:9, replace mine 17:18 target 17:18, replace mine 26:27 target 26:27, replace mine 28:29 target 28:29, replace mine 33:34 target 33:34, replace mine 36:37 target 36:37.
- `updateDialogAnimation` 77.247190%: 263/267 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 9: build 0; src 0x41c base 0x42c insns 263/267; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 8: build 0; src 0x41c base 0x42c insns 263/267; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 7: build 0; src 0x41c base 0x42c insns 263/267; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 15:16 target 15:16, delete mine 44:47 target 44:44, replace mine 48:54 target 45:46, replace mine 56:58 target 48:50, replace mine 59:60 target 51:53, replace mine 62:63 target 55:56.
- `updatePageTransform` 76.606450%: 151/155 instructions; instruction count and block scheduling/control flow differ.
  - for loop with explicit while and increment: build 0; src 0x25c base 0x26c insns 151/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name channel frame center coordinates: build 0; src 0x25c base 0x26c insns 151/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - sample three frame animations explicitly: build 0; src 0x108 base 0x26c insns 66/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cache projection dimensions before computing transform: build 0; src 0x25c base 0x26c insns 151/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 0:1 target 0:1, replace mine 2:15 target 2:13, replace mine 25:26 target 23:24, replace mine 41:43 target 39:40, replace mine 44:46 target 41:44, insert mine 47:47 target 45:55.
- `collectTitlesBySpecialChannels` 71.639890%: 331/361 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 13: build 0; src 0x528 base 0x5a4 insns 330/361; --- replace mine 5:20 base 5:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 12: build 0; src 0x53c base 0x5a4 insns 335/361; --- replace mine 5:20 base 5:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 11: build 0; src 0x52c base 0x5a4 insns 331/361; --- replace mine 5:20 base 5:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: replace mine 5:20 target 5:13, insert mine 21:21 target 14:35, replace mine 22:43 target 36:43, replace mine 44:47 target 44:49, replace mine 50:51 target 52:96, delete mine 52:93 target 97:97.
- `findAdjacentChannel` 48.044445%: 48/45 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 5: build 0; src 0xc0 base 0xb4 insns 48/45; --- delete mine 2:3 base 2:2; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 4: build 0; src 0xc0 base 0xb4 insns 48/45; --- delete mine 2:3 base 2:2; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name branch condition 3: build 0; src 0xc0 base 0xb4 insns 48/45; --- delete mine 2:3 base 2:2; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Target/source block differences: delete mine 2:3 target 2:2, replace mine 5:9 target 4:8, replace mine 12:14 target 11:15, replace mine 15:17 target 16:18, replace mine 18:22 target 19:28, replace mine 23:24 target 29:30.

### src/scene/sdChannelMemory/iplSDMemory

- `onDialogState8` 99.778480%: 158/158 instructions; header pointer and row-count registers differ, 6 differences.
  - name branch condition 5: build 0; src 0x27c base 0x278 insns 159/158; --- replace mine 49:50 base 49:50; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 4: build 0; src 0x278 base 0x278 insns 158/158; diffs 6: [83, 89, 91, 137, 142, 143]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 3: build 0; src 0x284 base 0x278 insns 161/158; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 90 (mine=90 base=90).
- `create` 95.456764%: 1078/1064 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 3: build 0; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 2: build 0; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 1: build 0; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - Target/source block differences: replace mine 5:6 target 5:6, replace mine 10:11 target 10:11, replace mine 17:18 target 17:18, replace mine 21:22 target 21:22, replace mine 27:28 target 27:28, replace mine 33:35 target 33:35.
- `onDialogState21` 90.060974%: 79/82 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 2: build 0; src 0x13c base 0x148 insns 79/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 1: build 0; src 0x14c base 0x148 insns 83/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - nested short-circuit branch guards: build 0; src 0x13c base 0x148 insns 79/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - Target/source block differences: replace mine 5:8 target 5:8, replace mine 9:10 target 9:10, replace mine 13:14 target 13:14, replace mine 16:17 target 16:22, replace mine 21:25 target 26:36, replace mine 26:38 target 37:41.
- `drawTransferTitles` 85.421290%: 422/451 instructions; instruction count and block scheduling/control flow differ.
  - name branch condition 8: build 0; src 0x6a0 base 0x70c insns 424/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 7: build 0; src 0x6a8 base 0x70c insns 426/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name branch condition 6: build 0; src 0x6a8 base 0x70c insns 426/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - Target/source block differences: replace mine 0:1 target 0:1, replace mine 2:20 target 2:20, replace mine 23:24 target 23:24, replace mine 26:27 target 26:27, replace mine 33:35 target 33:35, replace mine 36:38 target 36:38.

## Data limits and measurement uncertainty

- Setting: .sdata 504 bytes and .sdata2 64 bytes 100%; .bss/.sbss 100%. Original .rodata includes two trailing 20-byte UTF-16 digit maps with no object-code references. They were not fabricated as unused padding. Animation bindings and pointer tables are present; original symbol scAnmTable aggregates adjoining tables.
- SDChannelSelect: .rodata 64 bytes, .sdata 80 bytes, .sdata2 80 bytes 100%.
- SDMemory: .sdata 152 bytes and .sdata2 48 bytes 100%.
- Remaining .data differences include original zero-filled deduplicated weak vtables versus compiler-emitted vtable relocations, symbol grouping and layout. No replacement zero arrays, force-active entries or linker changes were used.
- Gate instruction counts differ from objdiff counts by one in Setting and SDMemory. Raw relocation handling and the conditional CR1 decoder affect these counts; objdiff 100% remains the function authority. The pre-existing SDMemory updateState discrepancy was not hidden by changing tooling.

## Gate blocks

All captured gate blocks are copied below, including rejected trial states. Only gate-passing retained source was committed. The final block is a full clean gate over all three units.

### sol-r2-baseline-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 21896/37884 data 472/5696 functions 97/112 fuzzy 86.6897 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 97/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 94.5922 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-vtable-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 21896/37884 data 472/5696 functions 97/112 fuzzy 86.6897 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 97/112
regressions vs baseline: 0
GATE PASS
```

### sol-r2-input-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 21896/37884 data 472/5696 functions 97/112 fuzzy 86.6331 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 97/112
regressions vs baseline: 0
GATE PASS
```

### sol-r2-input2-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22048/37884 data 472/5696 functions 98/112 fuzzy 86.8151 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate1.txt

```
[src/scene/setting/iplSetting] objdiff: code 22048/37884 data 472/5696 functions 98/112 fuzzy 86.8151 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 94.5922 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-fade-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate2.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 94.5922 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-create-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 95.8476 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-data-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 95.9891 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-draw-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 97.5115 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-draw2-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data 48/3344 functions 61/66 fuzzy 97.6334 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate3.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data 48/3344 functions 61/66 fuzzy 97.6334 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate4.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-reorder-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-reorder2-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-reorder3-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-reorder4-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE FAIL: full build failed
```

### sol-r2-reorder5-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-select-data-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate5.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.8157 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-setting-data-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.9371 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-setting-material-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 86.9371 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE FAIL: full build failed
```

### sol-r2-setting-material2-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 87.6831 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate6.txt

```
[src/scene/setting/iplSetting] objdiff: code 22712/37884 data 472/5696 functions 99/112 fuzzy 87.6831 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 98/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-init-scroll-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 472/5696 functions 100/112 fuzzy 89.3403 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate7.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 976/5696 functions 100/112 fuzzy 89.3403 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-setting-colors-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 976/5696 functions 100/112 fuzzy 89.3669 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate8.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 976/5696 functions 100/112 fuzzy 89.3669 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-setting-rect-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 976/5696 functions 100/112 fuzzy 89.3669 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE FAIL: full build failed
```

### sol-r2-setting-rect2-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 976/5696 functions 100/112 fuzzy 89.3669 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE FAIL: full build failed
```

### sol-r2-setting-rect3-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 1040/5696 functions 100/112 fuzzy 89.3668 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-gate9.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 1040/5696 functions 100/112 fuzzy 89.3668 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-memory-order-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 1040/5696 functions 100/112 fuzzy 89.3668 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

### sol-r2-final-gate.txt

```
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 1040/5696 functions 100/112 fuzzy 89.3668 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
regressions vs baseline: 0
GATE PASS
```

