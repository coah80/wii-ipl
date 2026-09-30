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
