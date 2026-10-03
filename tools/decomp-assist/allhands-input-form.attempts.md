# Input-form source reconstruction, 2026-10-02/03 UTC

Base `cc812ad3`, branch `agent/bittle/input-form-reconstruction`, 43U only.
Only `src/keyboard/tiInputForm.cpp` and this log are changed. Existing attempt
logs, headers, metadata, compiler settings, linking flags and assembly bodies
are untouched.

## Retained changes and target evidence

### LayoutByNW4R::create

The first language text-pane lookup in the target loads the layout's root pane
and invokes FindPaneByName with the recursive flag. The old source instead
invoked the Layout virtual getPane slot. The retained source directly expresses
the root-pane lookup, recovering two missing instructions and the correct call
receiver path. The later const getLanguageTextPane fallback remains intact.

The animation loop in the target keeps the address of the selected files[] slot.
It loads the file for GetResource, then reloads that slot after the resource and
animation-transform calls to obtain the animation ID. The old source captured
the file pointer once. A const reference to the existing typed pointer slot now
expresses the target's lifetime and recovers the other two missing loads. No
new storage, qualifier forcing, table entry, or helper was introduced.

Together these changes restore the target's 356-instruction body. The fallback
name-selection block still schedules some receiver loads differently, and most
remaining differences concern register allocation. This is not an exact match.

### Base::calcCursorPos

The source now uses the already defined Rect::GetWidth accessor for glyph and
form widths. That existing accessor computes exactly right minus left. The
change preserves the arithmetic, hit-test inequalities, wrap/newline paths,
scroll handling, recursive fallback, and all helper calls. It recovers more of
the target's rectangle-expression boundaries at unchanged body size. Height
accessors and midpoint operand reversal did not improve the result and were not
retained. No new geometry abstraction or arithmetic reassociation was added.

## Attempts and rejected alternatives

- Read the previous sol-high-inputform and data-d4 logs. Revisited their concrete
  root-query and file-slot defects under the user's current partial-decompilation
  priority; did not repeat the historical declaration searches.
- Tested the two create corrections independently and together. Explicit fallback
  selector locals produced the same code. Duplicating the root lookup in both
  fallback branches grew the function to 363 instructions and was rejected.
- Tested small inline fallback-lookup wrappers; they added source complexity
  without improving the retained result. A trial binding the derived layout
  pointer to a base pointer reference did not compile and was restored.
- Existing width and height accessors and midpoint operand order were tested
  independently. Only the width accessor change is retained.
- No artificial allocation sweep, new assembly, use-site volatile, dummy storage,
  undefined input, padding, header edit, or linking experiment was used.

## Gates

Before -> after:
- calcCursorPos: 91.622696 -> 93.05215% fuzzy, 326/326 instructions unchanged;
  final raw ctxdiff 50 differences (baseline 52, including existing relocation
  aliases and floating-point scheduling/allocation differences).
- LayoutByNW4R::create: 95.02809 -> 96.40169% fuzzy, 352 -> 356 instructions against
  target 356; final ctxdiff 155 differences.
- Unit fuzzy: 99.578094 -> 99.6535%.
- Existing objdiff-exact symbols: 218/221 unchanged; exact code 46980/50656 bytes;
  matched data 3772/3772 (100%); linked status unchanged.
- Independently rebuilt the baseline and candidate objects. All 218 previously
  objdiff-100 symbols have identical baseline/candidate instruction streams.
  This preserves the pre-existing distinction between objdiff and raw ctxdiff
  exactness rather than claiming every alias-normalized symbol has diffs 0.
- Baseline/candidate raw .data, .rodata, .bss, .sdata, .sbss, .sdata2 and .ctors
  section bytes and extents are identical. All 20 pool strings match the target.
- Literal audit: 20 arguments checked, 221 functions analyzed, no candidates,
  skips or errors. Target-sized create is now included in that audit.
- Full 1027-unit report: no exact-function, exact-code, data or fuzzy regressions.
- Full 43U build and build/43U/ok passed, again after rebuilding the baseline and
  restoring the candidate. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

## Focused behavior coverage and limits

A private host harness extracts the production baseline/candidate calcCursorPos
bodies without rewriting them, supplies the same Rect::GetWidth expression, and
uses deterministic font/scale/wrap stubs. Compiled with single-precision float,
-fno-fast-math and -ffp-contract=off, it checks returned positions, helper-call
traces and wrap counters across empty text, newlines, forced word wraps, width
wraps, boundary hits, scale, non-positive scroll and recursive fallback.

159,320 terminating cases agreed. Another 680 synthetic font/wrap states reached
the same 1,000-scale-call model budget with identical traces in both versions;
no termination claim is made for those states. The initial unrestricted harness
also reached its budget in the baseline, so this is equivalence coverage for the
accessor change, not proof of general termination or a newly diagnosed Wii bug.
The layout/resource creation path is validated by target call/load evidence and
the real 43U compile; no Wii UI/runtime execution is claimed.

Private local evidence: `/tmp/input-form-reconstruction/` contains baseline/final
reports and object copies, pool/literal audits, both final ctxdiffs, build logs,
validate_cursor.py and cursor-tests.log, plus rejected experiments. No retail
assembly or binary is committed or uploaded.

GATE: validated partial source/control/data-flow reconstruction; no regressions.
Exact matching and linking remain open. Candidate frozen for parent validation.
