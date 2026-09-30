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
