# AGENTS.md

Guidance for AI agents working in this repository.

## CRITICAL RULE: never touch upstream

**Do not open a pull request against `koopthekoopa/wii-ipl`. Do not push to it.
Do not open issues on it. Do not comment on it. Never. Not once.**

The upstream maintainers do not want AI-authored commits in their history. This
fork exists solely so that AI-assisted matching work has somewhere to live
without disturbing them. Breaking this rule is worse than producing no matches
at all.

Concretely:

- `origin` is this fork, `coah80/wii-ipl`. Push here.
- `upstream` is `koopthekoopa/wii-ipl`. Its push URL is intentionally set to
  the sentinel `DISABLED_never_push_to_upstream` so an accidental
  `git push upstream` fails instead of uploading.
- Never run `gh pr create` with an upstream base, and never pass
  `--repo koopthekoopa/wii-ipl` to any `gh` command.
- If a task appears to require contacting upstream, stop and ask the human.

If you are reading this because you are about to open a PR: don't.

## What this repository is

A matching decompilation of the Wii Menu (system menu) 4.3U. "Matching" means
the compiled output must be byte-identical to the original binary, not merely
functionally equivalent. Correct behaviour that compiles to different assembly
is a failure.

## Build and verify

```
python3 configure.py --version 43U
ninja
```

Ninja lives at `/home/cole/projects/tests/.venv/bin/ninja` in the author's
environment.

The acceptance gate for any change is the DOL hash:

```
build/43U/main.dol  ->  26116613f624061ba99c8d1a299aaa6efa85670d
```

Objects listed as `NonMatching` in `configure.py` are **not linked** into the
DOL. Editing a `NonMatching` translation unit cannot change the DOL hash, which
makes it safe to iterate on a partial match without breaking the build. Verify
progress against the object file instead of the DOL:

```
build/43U/src/src/<path>.o        # what you just built
build/43U/obj/src/<path>.o        # the original object, ground truth
```

## Tooling for measuring progress

`objdiff` scores each function:

```
build/tools/objdiff-cli report generate -p . -o report.json -f json
```

A function counts as matched only at `fuzzy_match_percent == 100.0`. Anything
below that is not a match, regardless of how good it looks.

Helper tools live in `tools/decomp-assist/`:

- `ctxdiff.py <unit> <symbol>` — compact instruction-level diff of one function
  between your object and the original. This is the main iteration loop.
- `disasm_fn.py <object> <symbol>` — disassembly with relocation-resolved call
  names, so you can see which real functions are being called.
- `pool_diff.py` — diffs the string pool in `.data` between your object and the
  original, string by string. See below; this is the highest-signal tool.
- `export_pyghidra.py` — regenerates `ghidra_decomp.txt`, decompiled C for the
  functions still missing.

## The single most useful finding: the string pool

MWCC emits a translation unit's string literals into `.data` in the order the
compiler encounters them, and the compiler encounters them in **source-token
order**, not runtime order. Every later string's offset therefore depends on
every earlier one.

This matters enormously. If a function is missing from a translation unit, or
references its strings in a different order than the original, then every
string after it lands at the wrong offset, and *every function that reads those
strings fails to match* — even functions you have not touched.

Observable evidence: `TMDFile::Open` sat at 99.92 percent purely because a
string several functions earlier was 8 bytes off. Adding the correct
`checkContentsNum` block moved it to 99.96 without touching `Open`.

**Always run `pool_diff.py` and fix the first divergence before tuning register
allocation.** It points at exactly which function block is wrong or missing.

### Which branch you write changes the pool

Because emission follows source-token order, writing

```cpp
if (cond) { A(); } else { B(); }
```

versus

```cpp
if (!cond) { B(); } else { A(); }
```

emits the strings referenced by `A` and `B` in the opposite order. This is a
free lever: if a function's codegen looks right but its strings are swapped,
invert the condition rather than restructuring the logic. It fixed both the
pool and the instruction stream for `GetValidTicketIndex` in one change.

### Missing functions must all be present

A string block cannot be partially correct. A function that is entirely absent
leaves a hole, and everything downstream is shifted. Implement functions in
**object-order** (the order their addresses appear in `config/43U/symbols.txt`
and `splits.txt`), not in whatever order looks convenient.

## Workflow that produced matches

1. Find the next missing function in object order.
2. Get its decompiled C from `ghidra_decomp.txt` (regenerate with
   `export_pyghidra.py` if needed).
3. Write it as literally as possible: same order of operations, same branch
   direction, same number of temporaries.
4. Insert it at the correct position in the source file.
5. Build only that object: `ninja build/43U/src/src/<path>.o`.
6. `pool_diff.py` first. Fix ordering divergences before anything else.
7. `ctxdiff.py` next. Work through the instruction diff.
8. Only then look at register allocation.

## ReAgent and parallel worker workflow

This repository targets only Wii Menu 4.3U. Do not configure or build 43E,
43J, or 43K while doing matching work.

Use the installed ReAgent environment for evidence-driven reversal work:

```
/home/cole/projects/tests/reagent-venv/bin/re-agent doctor
/home/cole/projects/tests/reagent-venv/bin/re-agent status
```

ReAgent should use the authenticated local Codex provider with the requested
model and a small per-function call cap. The Codex provider uses the local
Codex login rather than an API key; API billing is not created by ReAgent, but
the account's normal model or plan usage still applies. Do not start a model
run until `doctor` reports the backend and acceptance configuration clearly.

For parallel work, orchestrate up to ten workers at once when the agent runtime
has the capacity. Use `gpt-5.6-luna` at maximum reasoning effort with the fast
service tier when those settings are available. If the runtime cannot host ten
live workers, queue the remainder; never duplicate a source file or function
range just to fill a slot. Each worker must own a disjoint translation unit or
function range and return the changed paths, exact-match measurements, and
validation results. Workers may propose code, but a candidate is not accepted
when it is only fuzzy, uses an uninitialized value, or hides a mismatch behind
artificial assembly.

### Ten-worker exact-match loop

The worker keeps iterating on its assigned function until exact-name `objdiff`
reports `100.0%`. A worker must not stop at a fuzzy score, and must not commit
or push. If the worker believes the remaining difference is a compiler
tie-break, it reports the evidence and waits for the orchestrator to terminate
or reassign the leaf; it does not self-accept a near-match. Reaching `100.0%`
is only the handoff point; it is not acceptance.

The orchestrator must independently rebuild the owned object and verify:

1. `pool_diff.py` reports identical pools, with no first divergence.
2. Exact-name `objdiff` reports `100.0%` for the requested symbol.
3. `ctxdiff.py` reports `diffs 0` and identical instruction counts.
4. The focused source diff is minimal, readable, and free of artificial
   assembly, uninitialized values, or unrelated edits.
5. The full 4.3U build passes and `build/43U/main.dol` has SHA1
   `26116613f624061ba99c8d1a299aaa6efa85670d`.

If any orchestrator gate fails, do not commit the candidate. Restore it or send
the same disjoint task back to its worker with the failing evidence. Commit and
push to `origin/main` immediately after every candidate passes all gates, then
regenerate the live progress report before accepting the next candidate.

For each candidate, the worker must:

1. Run `pool_diff.py` before tuning code generation.
2. Build the 43U object with `/home/cole/projects/tests/.venv/bin/ninja -C . build/43U/src/src/<path>.o`.
3. Require `objdiff` to report `100.0%` for the function and `ctxdiff.py` to report `diffs 0`.
4. Iterate until exact-name objdiff reaches `100.0%`, while preserving the
   pool and source-quality requirements above.
5. Return the focused exact match to the parent agent for review without
   committing or pushing. The parent reruns every gate, runs
   `/home/cole/projects/tests/.venv/bin/ninja -C . build/43U/ok`, and commits
   and pushes to `origin/main` only after acceptance.

The main agent reviews every worker result before accepting it. After each
accepted commit, record the new report from `build/43U/report.json` and keep
the DOL hash at `26116613f624061ba99c8d1a299aaa6efa85670d`. Never push to
`upstream`; only the fork's `origin` is in scope.

## Things that do NOT work

- **Frame pragmas.** `#pragma ppc_iro_level 0` fixed exactly one function out
  of roughly forty attempts and made others worse. A search across pragma
  variants produced almost no movement. Do not spend time here.
- **Reverting to pristine upstream to unblock.** The unmodified upstream tree
  is needed as a baseline, but it does not help you match anything.
- **Searching other forks for the missing functions.** The eleven unimplemented
  `iplESMisc` functions do not exist in any of the twenty-three public forks.

## Known hard cases

Many remaining diffs are pure compiler tie-breaks — register allocation and
floating-point scheduling — with no source-level lever. If `ctxdiff.py` shows
the instruction count already matches and the surviving differences are
callee-saved register names, you are probably looking at a tie-break. Record it
and move on rather than thrashing.

## Current status

Do not copy a progress number from this file. Regenerate the live 43U report
with `ninja -C . progress build/43U/report.json`; the report and DOL hash are
the authority for current status. `iplESMisc.cpp` remains `NonMatching` and
unlinked, so work there is DOL-safe.

## Reference

`tools/decomp-assist/iplESMisc.reference.cpp` is a snapshot of `iplESMisc.cpp`
with the matching work applied, kept as a reference for the string order and
function layout that the pool depends on.
