# zi8alpha attempts

Target: Wii Menu 4.3U, libs/RVLMiddleware/eZiText/src/clib/zi8alpha.
Baseline: e265d966, the nearest ancestor with an existing gate baseline. The
worktree's initial 70970038 merge-base has no baseline file. No branch changes
or baseline edits were made.

Ten functions are instruction-exact. Both remaining functions have at least
three distinct source-level attempts. The unit remains NonMatching.

## Zi8ChangeWordCase

1. Typed workspace argument and integer case selector: 44/44 instructions,
   11 differences, all register assignments involving the word and workspace.
2. Local word cursor copied from the input argument: 45/44 instructions,
   with an extra input spill. Rejected.
3. Void workspace argument accessed through the workspace structure: 44/44
   instructions, eight differences involving r29/r30 for the case selector
   and workspace. Final objdiff 99.09091%.
4. Tried a local workspace pointer, byte/short/long case selector types, and
   an explicit lower/upper case enum. None removed the remaining register
   differences. Kept the enum and void workspace argument.

## Zi8AlphaGetCandidates

1. Recovered the complete control flow, workspace fields, dictionary selection,
   candidate emission, prefix/suffix handling, case conversion, and punctuation
   from object decompilation and target assembly. Named the locals and replaced
   byte-offset memory accesses with structure fields and array indexing.
   4436/3946 instructions, frame 0x340 versus 0x2B0, objdiff 41.21566%.
2. Corrected the byte/halfword flag types, unsigned punctuation comparisons,
   and workspace/options argument handling. Initialized the dictionary index
   used by the early punctuation exit. 4399/3946 instructions, frame 0x330,
   objdiff 43.85555%.
3. Recovered typed external function declarations and return widths rather
   than leaving calls with unspecified argument types. 4452/3946 instructions,
   frame 0x330, objdiff 44.43614%.
4. Combined the punctuation character and its continuation storage into one
   actual 48-character buffer so pointer iteration stays within an array.
   4452/3946 instructions, final clean-build objdiff 44.43563%.

The remaining candidate-engine differences include stack layout, extra loads,
argument conversions, register allocation, and reconstructed branch structure.
This is not a compiler tie-break-only result. The recovered field names and
external declarations remain provisional, and engine behavior has not been
validated independently of the original assembly.

## Other iterations

- Workspace arguments accessed directly through a typed structure removed
  redundant pointer spills in Zi8IsWordW2 and Zi8SetHighlightedWordW.
- Signed length/index variables, branch direction for the single-character
  case, and postfix suffix indexing made ZiprocessHighlightedW exact.
- Shared true-result exits made Zi8IsVowel's switch trees exact.
- A generic beginning pointer with typed character indexing made both
  exclusion functions exact after signed-length and declaration-order trials.
- Zi8DeTokenization progressed from 692 to 811 to exactly 814 instructions
  after using postfix output indexing, recovered character/count widths,
  a 64-character output buffer, explicit input casts, and direct length return.

## Linking trial

Temporarily changed only zi8alpha to Matching and built main.dol. Linking
succeeded, but the DOL SHA1 was f7c92fc7a6790ae104636294803a7959ea628ddf.
Both original and trial DOLs were 3867904 bytes. 2045708 common bytes differed,
from file offset 0x5BA through 0x369301.

Original Zi8AlphaGetCandidates: offset 0xA40, size 0x3DA8.
Built Zi8AlphaGetCandidates: offset 0xA40, size 0x4590.
Original Zi8DeTokenization: offset 0x47E8.
Built Zi8DeTokenization: offset 0x4FD0.

unitaudit.py found 11 text symbols at their original addresses and one shifted
by 2024 bytes. The following zi8alts unit moved by +0x7E8. Later text shifts
changed to +0x7E0, and the following rodata began at +0x7C0.

The recovered exclusion tables have 330 meaningful bytes. The original rodata
section has 336 bytes, including its trailing zero alignment. No artificial
padding was added. The original anonymous French table symbol was given the
source name FrenchExcludePairs.

Restored NonMatching, rebuilt main.dol, and confirmed SHA1
26116613f624061ba99c8d1a299aaa6efa85670d. configure.py has no final changes.

## Follow-up matching attempts, 2026-09-30

Starting this continuation: 10/12 instruction-exact, code 5704/21664, data 0/564. Configuration stayed NonMatching throughout these attempts. Experiments were scoped to the named function and rejected variants were restored.

Zi8ChangeWordCase:

1. Replace the case enum with an integer flag: 44/44 instructions, the same eight register differences.
2. Use a byte flag: 44/44, the same eight register differences.
3. Declare and assign the byte flag separately: 44/44, the same eight register differences.
4. Typed work parameter: 44/44, eleven register differences.
5. Local typed work alias: 41/44; compiler combines work loads differently from the target.
6. Local word cursor: 45/44; extra cursor setup. Rejected. The original enum declaration remains.

Zi8AlphaGetCandidates:

1. Reverse local declarations: 4452/3946 instructions, 44.43538%.
2. Recover five state flags as bytes: 4452/3946, 44.341106%.
3. Explicit switch for phonetic separators F331 through F335: 4450/3946, 44.217434%.

All three candidate-engine scores were below the 44.43563% baseline. The stack frame remains 0x330 instead of 0x2B0, with branch, conversion and load differences throughout. No additional exact function was found; no source variant was retained.

## Complete-body continuation from f20fc7b8, 2026-09-30

Entry: engine 44.43563%, case conversion 99.09091%, unit 10/12 instruction-exact. Both source functions remain public; configuration remains NonMatching. The engine was walked against the original disassembly, with object rebuilds and ctxdiff after each group of blocks.

- Recovered the byte, halfword, pointer and integer declaration order from stack accesses. Separated primary/secondary completion and vowel flags, prefix flags, dictionary state, retry state, output language and phonetic flags. Removed comma-expression Boolean temporaries. Recovered the 65-character candidate buffer, including its terminator capacity: frame now 0x2b0, matching the original, rather than 0x330.
- Restored normalization, early highlighted-word output, prefix preparation, language selection and dictionary dispatch in address order. Recovered separate loop indices and lengths rather than sharing variables with overlapping lifetimes. Rebuilt the ROM/PUD/UWD/OEM and punctuation paths, candidate filtering, detokenization, duplicate filtering, key-layout filtering, output, dictionary exhaustion and all prefix/suffix retries through the final return. Intermediate engine scores: 65%, 70.35226%, then 70.829445%; no tail is omitted.
- Typed-workspace alias experiments were rejected: a local typed alias scored 67.28865%; a const pointer alias scored 67.75748%; a generic dictionary-work alias at the target initialization position scored 70.29625%. None resolved the target's unused workspace-copy stack slot without extra loads. No unused local or padding was added to reproduce that slot.
- Recovered Zi8GetTableCount's halfword return type from matched siblings. Score initially 70.65965%. Corrected the post-dictionary vowel filter to use the prefix-vowel flag and restored Italian/French/vowel call order and failure exits: 71.42676%.
- Reversed the lookup-versus-output branch to match the target's WCharCount-before-conversion order: 72.92676%. Reversed locked/unlocked suffix branches: 73.289406%. Recovered the stack-resident suffix element index and postfix field increments, preserving sequenced prefix reads/stores: 74.21439%.

Quick authority gate PASS: identical pool, zero regressions, zero added forbidden patterns and readability warnings. Engine frame matches; first strict instruction divergence is +0x14, the parameter/workspace register swap. Remaining differences include scalar stack offsets, branch structure, call conversions and register allocation, not just compiler register choices. Behavior is reviewed against assembly, without an independent runtime harness.

Additional near-match source trials in this continuation:

- Zi8ChangeWordCase: case switch; 74.88636%, src 0xc0 base 0xb0 insns 48/44. --- replace mine 9:21 base 9:14.
- Zi8ChangeWordCase: explicit cursor advance in for loop; 94.545456%, src 0xb0 base 0xb0 insns 44/44. diffs 11: [9, 10, 11, 19, 22, 25, 27, 29, 30, 31, 32].
- Zi8ChangeWordCase: loop break at entry; 67.27273%, src 0xb0 base 0xb0 insns 44/44. diffs 18: [9, 10, 11, 19, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35].

Restored the case-conversion baseline after all three rejected variants. A generic workspace argument copied into a typed local and used for the entire engine scored 70.34288%, 4096/3946 instructions; rejected in favor of the 74.21439% committed body.

Further address-order audit: changing the engine workspace formal to the shared generic pointer type, with typed field access, moved the first strict divergence from +0x14 to +0x20 and scored 74.8036%. A const dictionary-work alias in a nested scope scored 72.05246%; a cached phonetic character scored 74.60922%; rejected both rather than manufacture the unused target stack copy. Recovered invalid-language-first branch order: 75.2666%. Recovered default-buffer-first order, chained flag-store order, unsigned field casts and the signature's halfword length argument: 75.28484%.

Replaced the reconstructed Finnish retry labels with the target's backward scan and switch, including the shared vowel/space stop and decrement. Moved apostrophe punctuation termination from the loop condition into the body. Corrected the final punctuation-history check to use primary/secondary vowel restrictions rather than completion flags, as shown by target slots 0x8c/0x94. 76.430305%, frame still 0x2b0. Quick authority gate PASS, no regressions. These remaining structural fixes are separate from the unresolved workspace-copy stack slot; no padding or unused local was added.

Highlighted-output audit: recovered the element-index length slot, the last-highlighted-character test at index minus one, body comparison breaks, skip-before-emit branch and suffix output scan through the shared index. Preserved a zero dictionary index before the early highlighted-output exit; the baseline initialized it, and leaving it undefined would make the optional dictionary-count finalization read an uninitialized local. That initialization is a deliberate remaining assembly difference, not a matching trick. Corrected Zi8Memset's full-width value argument from its matched definition. 76.94551%.

Dictionary-mode dispatch audit: replaced the reconstructed comparison chain with the target's switch, in address order: punctuation, OEM, UWD, alternate sound, completion/default, ROM/PUD. Restored the forward dictionary-kind scan with a body break and initialized scan position only on the dual-language path. 81.71363%, 3978/3946 instructions. Recovered previous-count-before-clear order, ordinary-dictionary-before-terminal-punctuation order and the secondary-pass skip switch: 81.86037%. Quick gate PASS, identical pool, zero regressions and readability warnings. Every engine exit and dictionary/prefix/suffix pass remains present.

Final full gate over both units: PASS. Alpha remains 10/12 instruction-exact; exact code 5704/21664, exact data 72/564, weighted fuzzy 86.776405%. Final engine score 81.86037%, 3978/3946 instructions, frame 0x2b0; first strict divergence +0x40, before the target's retry-flag initialization. Case conversion remains 99.09091% with eight register differences. All 330 emitted rodata bytes equal the target prefix; its remaining six bytes are trailing alignment, which was not reproduced with padding objects. The target's workspace-copy slot and some field meanings remain unresolved. All source functions are complete; no additional exact function or linked-unit completion is claimed.

## Exactness continuation from a3b04ad9, 2026-09-30

Entry engine 81.86037%, case conversion 99.09091%; unit 10/12 exact. Both units remain NonMatching. Workspace snapshot used for dictionary/helper calls restored the target scalar slot offsets but scored 81.77065%; making it const scored 81.71845%. A scoped phonetic-character cache scored 80.372025% and introduced a frame-pointer register. Rejected all three variants; no unused copy was added.

Flattened terminal-punctuation selection before the shared dictionary body rather than jumping backward from the loop tail: 82.4108%, 3975/3946 instructions. Target slots 0x84 at +0x1288 and +0x18e8 control the two punctuation/ROM mode checks; corrected those checks to use the corresponding current restriction variable instead of slot 0x88. Recovered word-length-first comparison, failure branch direction, digit-before-vowel branch and the explicit failed-length reset: 82.60162%. Recovered signed result limit and direct keyboard-layout tests; removed redundant dictionary-return casts: 82.613785%, 3976/3946, frame 0x2b0. Quick gate PASS, identical pool, zero regressions.

Finalization pass: restored count-only zero output before normal letters, the trailing punctuation loop's body break and decrement/count order, terminal dictionary-count branch direction and the stack-resident count-loop comparison. 84.43994%; reversed the prefix-history update and encoded-output/null branch: 84.59275%, 3978/3946 instructions. Arrays and frame still match. A keyboard-layout workspace alias scored 84.66067%, but was rejected: it primarily occupied the unused target word while adding a redundant alias, rather than recovering a demonstrated local use. The retained source has no added workspace placeholder. Quick gate PASS, zero regressions.

Further exactness variants in this continuation (rejected unless explicitly retained):

- Zi8ChangeWordCase: full-width language formal; 99.09091%, src 0xb0 base 0xb0 insns 44/44.
- Zi8ChangeWordCase: generic word buffer with typed cursor; 95.454544%, src 0xb4 base 0xb0 insns 45/44.
- Zi8ChangeWordCase: const workspace pointer parameter; 99.09091%, src 0xb0 base 0xb0 insns 44/44.
- Zi8ChangeWordCase: case flag initialized separately; 99.09091%, src 0xb0 base 0xb0 insns 44/44.

Nested phonetic range bounds left 84.59275% unchanged. Restored target positive web-prefix branch before the ordinary hyphen fallback: 84.599594%, 3978/3946, frame 0x2b0. Quick gate PASS, zero regressions; retained.

Removing the early dictionary-index initialization scored 84.626205%, but rejected after source review: early jumps to finalization can read the index before the dictionary loop initializes it. The safe initialization remains. Swapped the remembered-length comparison operands to match target load order and branch sense: 84.65154%, 3978/3946 instructions. Quick gate PASS, zero regressions; retained.

Direct tests for all vowel and punctuation helpers together fell to 84.5593%; rejected. Isolating the initial punctuation test avoids reusing the main index temporary for this Boolean result and raises 84.65154% to 84.70755%, 3978/3946, frame 0x2b0. Quick gate PASS, zero regressions; retained. Full-width case selector with explicit byte call argument remains 44/44, eight register differences, 99.09091%; rejected.

Final rejected variants (restored the committed higher score after each):

- Zi8ChangeWordCase: read-only workspace formal with generic helper argument; 99.09091%, src 0xb0 base 0xb0 insns 44/44.
- Zi8AlphaGetCandidates: signed remembered length comparison against input minus one; 84.59503%, src 0x3e28 base 0x3da8 insns 3978/3946.
- Zi8AlphaGetCandidates: typed workspace local for structure field access; 84.00431%, src 0x3e2c base 0x3da8 insns 3979/3946.
- Zi8AlphaGetCandidates: typed workspace field view in recovered scalar declaration order; 84.04105%, src 0x3e2c base 0x3da8 insns 3979/3946.

Final retained alpha engine: 84.70755%, frame 0x2b0, 3978/3946 instructions. Every body region is present. Scalar slots remain four bytes below target; the original stores a workspace snapshot at stack 0x20 that is never loaded. Tried used generic snapshots and typed field views; they altered call or field register allocation and lowered the score. No unused snapshot or padding was introduced. Remaining structural differences include phonetic range-load reuse, result copies, punctuation/dictionary branches and cursor scheduling. Case conversion retains eight register swaps in 44/44 instructions, 99.09091%; multiple formal, selector, cursor and loop variants do not resolve them. Ten of twelve functions remain exact.

Final full gate over both owned units: GATE PASS, full build ok, original DOL hash 26116613f624061ba99c8d1a299aaa6efa85670d, both pools identical, zero regressions, zero added forbidden patterns and zero readability warnings. zi81key exact functions 4/9 -> 5/9, exact code 2588 -> 3952 of 21460 bytes, exact data 1208/1388 unchanged, weighted fuzzy 96.5146% -> 97.1719%. zi8alpha exact functions 10/12 unchanged, exact code 5704/21664 and exact data 72/564 unchanged, weighted fuzzy 86.7764% -> 88.8508%. These are partial matching improvements; the remaining functions are not claimed exact.

## Address-order continuation from 131d8f74, 2026-09-30

Entry open functions, largest first: Zi8AlphaGetCandidates, 15784 bytes,
84.70755%, 3978/3946 instructions; Zi8ChangeWordCase, 176 bytes, 99.09091%,
44/44 instructions and eight register differences. Entry unit exact functions
10/12, exact code 5704/21664, exact data 72/564, pool identical.

Frame-first experiments, rejected and restored:

- A typed workspace field view in scalar declaration order: 84.04105%,
  3979/3946. It changes parameter allocation and does not recover the snapshot.
- A generic helper workspace used for all helper calls: 83.70933%, 3990/3946.
  Scalar offsets agree, but target register moves become stack loads.
- A snapshot used once for duplicate-buffer initialization: 84.86721%,
  3979/3946. Rejected despite the small score gain: its main effect is occupying
  the target's unused workspace slot, without evidence for that source use.
- Scoped phonetic-character local and nested range comparisons: 82.6779%,
  3980/3946, introduces a frame pointer. Rejected.
- Five-case phonetic separator switch: 84.68272%, 3979/3946. Its range dispatch
  agrees structurally after accounting for the unresolved scalar offsets, but
  register changes lower the whole-function score. Rejected for now.
- Full-width table-count return with explicit halfword casts: 84.361885%,
  3979/3946. It does not recover the missing call-result copies. Rejected.
- A switch on the context table flag: 84.68221%, 3979/3946, extra branch.
- Native signed-long scalar types: exactly the original 84.70755%, 3978/3946.

Re-translated the punctuation dictionary and shared remembered/prefix append
blocks at target 81467B08..81467C4C. The target tests the value of the wide
character assignment, emits the nonzero case first, merges both history scans
before appending, and increments the append index before storing word length.
Retained these complete blocks: 85.41105%, 3980/3946, frame 0x2b0. Quick gate
PASS, identical pool, zero regressions, zero forbidden/style patterns.

Case-conversion register-only trials: byte-address workspace, unsigned-long
selector, renamed selector, renamed workspace and renamed word each retain
44/44 instructions and the same eight r29/r30 differences. A const byte
workspace conflicts with the helper's writable generic argument. All rejected;
the original readable case-conversion function remains.

The earliest engine obstacle is still the target's dead workspace store at
stack 0x20. No unused local or artificial stack placeholder was retained.
Later differences include call-result copies, signed comparisons, dispatches
and output cursor scheduling. This engine is not registers-only or exact.

Further block audit in this run:

- Recovered Zi8MatchUWDdata's halfword current-word length formal from the
  target's r6 narrowing at 81467A48. Removed the unsigned prefix-count
  comparison, restored EFF1 as the lower punctuation bound, and reversed the
  failed apostrophe branch to the target's retry-first form: 85.46452%,
  3981/3946 instructions. Other functions unchanged.
- Two contiguous next-dictionary switches: 85.34263%, 3978/3946; first switch
  alone: 85.37557%, 3978/3946. Both reduce instruction count but lower the
  whole score, so rejected.
- Recovered signed length/count comparisons with operands in target order and
  ordinary null-pointer comparison: 85.79067%, 3979/3946. Retained.
- Retried the phonetic separator switch after these fixes: 85.829956%,
  3980/3946. Retained. The range-dispatch instructions now agree from the
  function entry through normalization, apart from the unresolved workspace
  snapshot, scalar offsets and register choices. Missing call-result copies
  and the safe early dictionary-index initialization remain distinct gaps.

Final full gate over both units: GATE PASS. Full clean 43U build passes, DOL
SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, identical pools, zero
regressions, zero forbidden patterns and zero readability warnings. Alpha
remains 10/12 instruction-exact, code 5704/21664 and data 72/564; weighted
fuzzy 88.850815% -> 89.66857%. Engine 84.70755% -> 85.829956%, 3980/3946
instructions, frame 0x2b0; case conversion unchanged and registers-only.
The requested exact-count improvement and complete retranslation are not
achieved. The unresolved snapshot prevents instruction alignment at the top;
no artificial snapshot was retained to bypass that obstacle.
