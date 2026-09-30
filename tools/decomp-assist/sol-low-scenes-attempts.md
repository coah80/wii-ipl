# Scene matching attempts

43U only. Failed experiments were reverted. Retained improvements passed the full gate before their final handoff. No configure.py linking changes.

All 112/129/66 original function symbols are present. String sequences are identical in all three units. No asm bodies remain in these source files. Compiler-emitted helper placement still differs from the extracted object; emitted text order is not claimed identical.

Starting instruction-exact counts: Setting 88/112, SDChannelSelect 90/129, SDMemory 49/66. Starting objdiff function counts: 89/112, 90/129, 49/66. These are different measurements.

Retained work: EULA/USB/network dispatch, Setting input and fadeout flow, missing Rect constructor, SD worker dispatch, SD memory dialog/transfer/progress/scroll flow and SD channel notice iteration. Each matching improvement has a local commit. Shared-header changes are guarded by macros defined only by the owning .cpp.

## Remaining functions and attempts

Counts below are current objdiff percentages. Each row records distinct source variations. Identical compiler output is recorded as no gain; it is not accepted as a match. Some larger functions still need deeper block-by-block reconstruction.

### src/scene/setting/iplSetting

- ipl::scene::Setting::createBrowser() | 89.86711% | 301/301 instructions; diffs 143 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 305/301 instructions; for loop with explicit while and increment: 301/301 instructions, diffs 143; invert first complete if/else: 301/301 instructions, diffs 142.
- ipl::scene::Setting::calcNormal() | 67.91796% | 1096/1158 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 1096/1158 instructions; invert first complete if/else: 1096/1158 instructions; string-pool divergence, reverted; nested short-circuit branch guards: 1096/1158 instructions.
- ipl::scene::Setting::calcFadeout() | 99.96988% | 166/166 instructions; diffs 0 in registers, scheduling, branches or relocations; instruction diff is zero but objdiff remains below 100, relocation/data reference still open.
  Attempts: name first branch condition: 167/166 instructions; for loop with explicit while and increment: 166/166 instructions, diffs 0; invert first complete if/else: 166/166 instructions, diffs 15.
- ipl::scene::Setting::draw() | 37.54272% | 276/632 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 276/632 instructions; nested short-circuit branch guards: 276/632 instructions; reverse constant comparison operands: 276/632 instructions.
- ipl::scene::Setting::initKeyboard(const char*) | 65.976524% | 210/213 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 212/213 instructions; invert first complete if/else: 210/213 instructions; nested short-circuit branch guards: 210/213 instructions.
- ipl::scene::Setting::calcKeyboard() | 75.62414% | 293/290 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 293/290 instructions; while loop as for loop: 293/290 instructions; invert first complete if/else: 293/290 instructions.
- ipl::scene::Setting::convertRevIP(unsigned char*, const char*) | 98.15069% | 73/73 instructions; diffs 21 in registers, scheduling, branches or relocations.
  Attempts: initialize output pointer earlier: 73/73 instructions, diffs 27; while loop: 73/73 instructions, diffs 14; advance pointer before count: 73/73 instructions, diffs 21.
- ipl::scene::Setting::checkIPString(const wchar_t*) | 76.210526% | 35/38 instructions; instruction count/control-flow or inlining differs.
  Attempts: explicit return branches: 32/38 instructions; named validation result: 31/38 instructions; member function pointer call: 47/38 instructions.
- ipl::scene::Setting::scanAP() | 81.21691% | 265/272 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 265/272 instructions; invert first complete if/else: 265/272 instructions; reverse constant comparison operands: 265/272 instructions.
- ipl::scene::Setting::initScroll() | 50.104694% | 272/277 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 272/277 instructions; for loop with explicit while and increment: 272/277 instructions; invert first complete if/else: 272/277 instructions.
- ipl::scene::Setting::updateScroll() | 94.46928% | 183/179 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 183/179 instructions; for loop with explicit while and increment: 183/179 instructions; invert first complete if/else: 183/179 instructions.
- ipl::scene::Setting::setAPDraw() | 62.204678% | 148/171 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 148/171 instructions; for loop with explicit while and increment: 148/171 instructions; invert first complete if/else: 148/171 instructions.
- ipl::scene::Setting::validateEULA_() | 64.414894% | 93/94 instructions; instruction count/control-flow or inlining differs.
  Attempts: result-not-zero branch and reused result: 94/94 instructions, 56 diffs; declare valid flag before calls: 94/94, 56 diffs; cache application heap: 94/94, 58 diffs.
- ipl::scene::Setting::makeSupportCode() | 99.07895% | 76/76 instructions; diffs 10 in registers, scheduling, branches or relocations.
  Attempts: separate appended length: 76/76 instructions, 13 diffs; reuse chunk length for title and label: 76/76, 3 register diffs; signed final code length: 76/76, 3 register diffs.
- ipl::scene::Setting::setUSBAP() | 78.42105% | 55/57 instructions; instruction count/control-flow or inlining differs.
  Attempts: state switch plus positive owner-result branch: 56/57 instructions; early status-zero break: 56/57 instructions; status switch: 56/57 instructions; target reloads status.

### src/scene/sdChannelSelect/iplSDChannelSelect

- ipl::scene::SDChannelSelect::create() | 94.23972% | 146/146 instructions; diffs 84 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 146/146 instructions, diffs 84; while loop as for loop: 146/146 instructions, diffs 84; reverse constant comparison operands: 146/146 instructions, diffs 84.
- ipl::scene::SDChannelSelect::enqueueStartNotice() | 94.117645% | 18/17 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 21/17 instructions; zero aggregate then nonzero fields: 19/17 instructions; memset then nonzero fields: 19/17 instructions.
- ipl::scene::SDChannelSelect::enqueueFinishNotice() | 94.44444% | 19/18 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 22/18 instructions; zero aggregate then nonzero fields: 20/18 instructions; memset then nonzero fields: 20/18 instructions.
- ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long) | 97.51111% | 46/45 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 54/45 instructions; zero aggregate then nonzero fields: 52/45 instructions; memset then nonzero fields: 52/45 instructions.
- ipl::scene::SDChannelSelect::enqueueLoadNotice() | 95.652176% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 27/23 instructions; zero aggregate then nonzero fields: 25/23 instructions; memset then nonzero fields: 25/23 instructions.
- ipl::scene::SDChannelSelect::enqueuePageNotice() | 95.652176% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 27/23 instructions; zero aggregate then nonzero fields: 25/23 instructions; memset then nonzero fields: 25/23 instructions.
- ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long) | 95.652176% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 30/23 instructions; zero aggregate then nonzero fields: 28/23 instructions; memset then nonzero fields: 31/23 instructions.
- ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long) | 90.86957% | 25/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 32/23 instructions; zero aggregate then nonzero fields: 30/23 instructions; memset then nonzero fields: 35/23 instructions.
- ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long) | 95.652176% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 29/23 instructions; zero aggregate then nonzero fields: 27/23 instructions; memset then nonzero fields: 31/23 instructions.
- ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long) | 95.13043% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 30/23 instructions; zero aggregate then nonzero fields: 28/23 instructions; memset then nonzero fields: 33/23 instructions.
- ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long) | 95.652176% | 24/23 instructions; instruction count/control-flow or inlining differs.
  Attempts: fully initialized argument aggregate: 29/23 instructions; zero aggregate then nonzero fields: 27/23 instructions; memset then nonzero fields: 31/23 instructions.
- ipl::scene::SDChannelSelect::processWorkerCommands() | 83.055214% | 327/326 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 327/326 instructions; for loop with explicit while and increment: 327/326 instructions; invert first complete if/else: 327/326 instructions.
- ipl::scene::SDChannelSelect::handleSDTitleListResult() | 99.15205% | 170/171 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 171/171 instructions, diffs 30; for loop with explicit while and increment: 170/171 instructions; invert first complete if/else: 169/171 instructions.
- ipl::scene::SDChannelSelect::handleSDChannelUpdateComplete() | 86.82407% | 105/108 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 106/108 instructions; invert first complete if/else: 105/108 instructions; reverse constant comparison operands: 105/108 instructions.
- ipl::scene::SDChannelSelect::updateDialogAnimation() | 77.24719% | 263/267 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 263/267 instructions; invert first complete if/else: 263/267 instructions; nested short-circuit branch guards: 263/267 instructions.
- ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const | 93.07843% | 50/51 instructions; instruction count/control-flow or inlining differs.
  Attempts: bytes before blocks and explicit return: 51/51 instructions, diffs 9; separate negative guards: 52/51 instructions; named sufficient result: 50/51 instructions.
- ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const | 86.82353% | 49/51 instructions; instruction count/control-flow or inlining differs.
  Attempts: explicit sums: 49/51 instructions; entry first in sums: 49/51 instructions; initialize blocks before bytes: 49/51 instructions.
- ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*) | 97.81188% | 101/101 instructions; diffs 4 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 101/101 instructions, diffs 4; nested short-circuit branch guards: 101/101 instructions, diffs 4; increment output count directly: 101/101 instructions, diffs 4; assign output count from expression: 101/101 instructions, diffs 4; positive enough-usage conjunction: 101/101 instructions, diffs 4.
- ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*) | 97.833336% | 102/102 instructions; diffs 4 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 102/102 instructions, diffs 4; nested short-circuit branch guards: 102/102 instructions, diffs 4; assign output count from expression: 102/102 instructions, diffs 4; named next output count: 102/102 instructions, diffs 4; negative remaining-usage guards: 102/102 instructions, diffs 4.
- ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*) | 86.55556% | 118/126 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 119/126 instructions; nested short-circuit branch guards: 118/126 instructions; reverse constant comparison operands: 118/126 instructions.
- ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*) | 71.63989% | 331/361 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 331/361 instructions; for loop with explicit while and increment: 331/361 instructions; nested short-circuit branch guards: 331/361 instructions.
- ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const | 48.044445% | 48/45 instructions; instruction count/control-flow or inlining differs.
  Attempts: wrap candidate at loop top: 44/45 instructions; initialized found flag: 47/45 instructions; flag assigned on both breaks: 45/45, 12 diffs; step first then wrap: 45/45, 15 diffs; explicit signed direction branch: 45/45, 12 diffs.
- ipl::scene::SDChannelSelect::flushSaveDataAndMountSD() | 99.65714% | 35/35 instructions; diffs 2 in registers, scheduling, branches or relocations.
  Attempts: cache heap and save manager: 35/35 instructions, 2 register diffs; retain manager after setter: 34/35 instructions; reload manager after setter: 35/35, 2 register diffs.
- ipl::scene::SDChannelSelect::calcCommon() | 99.07407% | 109/108 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 113/108 instructions; invert first complete if/else: 109/108 instructions; nested short-circuit branch guards: 109/108 instructions.
- ipl::scene::SDChannelSelect::destroy() | 95.097565% | 203/205 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 203/205 instructions; while loop as for loop: 203/205 instructions; reverse constant comparison operands: 203/205 instructions.
- ipl::scene::SDChannelSelect::drawChannelTransitionObjects() | 94.974846% | 153/159 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 157/159 instructions; while loop as for loop: 153/159 instructions; nested short-circuit branch guards: 153/159 instructions.
- ipl::scene::SDChannelSelect::initializeNormalPage() | 98.93617% | 95/94 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 101/94 instructions; invert first complete if/else: 95/94 instructions; reverse constant comparison operands: 95/94 instructions.
- ipl::scene::SDChannelSelect::selectChannel(int, int) | 98.305084% | 60/59 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 60/59 instructions; named page-position value: 60/59 instructions; componentwise page-position value: 62/59 instructions.
- ipl::scene::SDChannelSelect::startPageTransition(int, int) | 99.888885% | 45/45 instructions; diffs 5 in registers, scheduling, branches or relocations.
  Attempts: implicit position copy: 45/45 instructions, 6 diffs; const copy initialization: 45/45, 5 stack-offset diffs; const direct copy: 45/45, 5 stack-offset diffs.
- ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const | 93.48498% | 233/233 instructions; diffs 67 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 238/233 instructions; invert first complete if/else: 233/233 instructions, diffs 128; reverse constant comparison operands: 233/233 instructions, diffs 67.
- ipl::scene::SDChannelSelect::updatePageTransform() | 76.60645% | 151/155 instructions; instruction count/control-flow or inlining differs.
  Attempts: for loop with explicit while and increment: 151/155 instructions; named position and scale geometry: 151/155 instructions; componentwise position and scale assignment: 146/155 instructions.
- ipl::scene::SDChannelSelect::applyChannelMove() | 94.66923% | 130/130 instructions; diffs 61 in registers, scheduling, branches or relocations.
  Attempts: name first branch condition: 130/130 instructions, diffs 61; invert first complete if/else: 130/130 instructions, diffs 70; nested short-circuit branch guards: 130/130 instructions, diffs 61.
- ipl::scene::SDChannelSelect::onEventDerived(const char*, unsigned long, ipl::controller::Interface*) | 94.08572% | 103/105 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 107/105 instructions; nested short-circuit branch guards: 103/105 instructions; reverse constant comparison operands: 103/105 instructions.
- ipl::scene::SDChannelSelect::onButtonEvent(const char*, unsigned long, const ipl::controller::Interface*) | 93.73627% | 87/91 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 91/91 instructions, diffs 65; nested short-circuit branch guards: 87/91 instructions; reverse constant comparison operands: 87/91 instructions.
- ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*) | 95.68056% | 140/144 instructions; instruction count/control-flow or inlining differs.
  Attempts: name first branch condition: 140/144 instructions; invert first complete if/else: 140/144 instructions; nested short-circuit branch guards: 140/144 instructions.

### src/scene/sdChannelMemory/iplSDMemory

- ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*) | 88.6062% | 1001/1064 instructions; instruction count/control-flow or inlining differs.
  Attempts: static text-box casts: 986/1064 instructions; unsigned pane indexes: 1001/1064 instructions; pane lookup temporary before trigger call: 1001/1064 instructions.
- ipl::scene::SDMemory::setScrollLimit() | 98.888885% | 81/81 instructions; diffs 11 in registers, scheduling, branches or relocations.
  Attempts: item height then content and viewport: 81/81 instructions, 11 diffs; single geometry expression: 81/81, 12 diffs; content and viewport before items: 81/81, 12 diffs.
- ipl::scene::SDMemory::onDialogState8() | 99.77848% | 158/158 instructions; diffs 6 in registers, scheduling, branches or relocations.
  Attempts: signed elapsed-time comparison: 158/158 instructions, 6 register diffs; retained; retrieve message before pane lookups: 157/158 instructions; reverted; direct pane SetString: 157/158; reverted; TextBox local and direct ceil conversion: 157/158, missing frsp; reverted.
- ipl::scene::SDMemory::onDialogState21() | 90.060974% | 79/82 instructions; instruction count/control-flow or inlining differs.
  Attempts: wcsncpy initialization: 81/82 instructions; reverted; wmemset initialization: unresolved instruction/branch differences; reverted; wcscpy initialization: unresolved instruction/branch differences; reverted.
- ipl::scene::SDMemory::drawTransferTitles() | 66.3969% | 376/451 instructions; instruction count/control-flow or inlining differs.
  Attempts: target-derived memo position, alpha, NAND-title cursor and separate text/background rows: 419/451 instructions; componentwise memo translation and signed line length: 438/451 instructions; guarded newline-count do loop: 420/451 instructions.

## Measurement uncertainty

SDMemory::updateState has objdiff 100.0 and identical raw 1228-byte function bodies. SHA256: f6d214c0c43ea01b29a036f0056c89759db994a876e5131f0f1d3c5a8f24228c. ctxdiff/gate still report two differences: conditional CR1 branch operands are decoded using operand zero as an immediate, even though operand zero is the CR register. Subtracting the different source/target symbol addresses creates false branch differences. Gate tooling was not edited. Thus the reported instruction-exact count is 60/66 while objdiff reports 61/66.

Data scores remain partial, including None for SDMemory .data. The original objects contain zero-filled deduplicated weak data. No padding, forced placement or artificial data was added. The full DOL hash is the gate authority; none of these units was changed to Matching.

Notice argument initialization remains complete: target appears to omit a copied word, but removing its initialization would introduce an uninitialized read. SDButton callers still supply the declared unused second event-handler parameter; target omits its setup. No mismangled one-argument alias was introduced.

Failed compile variants were reverted and excluded from the successful-attempt counts. Three compile-valid source attempts exist for every function listed above. The units remain partial.

## Final full gate

```text
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] objdiff: code 21896/37884 data 472/5696 functions 97/112 fuzzy 86.6897 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 97/112
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 144/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13528/20872 data None/3344 functions 61/66 fuzzy 94.5922 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 60/66
regressions vs baseline: 0
GATE PASS
```
