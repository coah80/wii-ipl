# AGENTS.md

Guidance for AI agents working in this repository.

Keep code comments to cases where they are necessary.

## CRITICAL RULE: never touch upstream

**Do not open a pull request against `koopthekoopa/wii-ipl`. Do not push to it.
Do not open issues on it. Do not comment on it. Never. Not once.**

The upstream maintainers do not want AI-authored commits in their history. This
fork exists solely so that AI-assisted matching work has somewhere to live
without disturbing them. Breaking this rule is worse than producing no matches
at all.

Concretely:

- `origin` is this fork, `coah80/wii-ipl`. Only the orchestrator pushes
  validated leaf branches here.
- `upstream` is `koopthekoopa/wii-ipl`. Its push URL is intentionally set to
  the sentinel `DISABLED_never_push_to_upstream` so an accidental
  `git push upstream` fails instead of uploading.
- Never run `gh pr create` with an upstream base, and never pass
  `--repo koopthekoopa/wii-ipl` to any `gh` command.
- If a task appears to require contacting upstream, stop and ask the human.

If you are reading this because you are about to open a PR against upstream:
don't. PRs for validated leaf branches belong only to this fork.

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

The final completion assertion is machine-checkable:

```
python3 tools/check_decomp_complete.py build/43U/report.json \
    --dol build/43U/main.dol
```

It must pass before claiming full completion. GitHub Actions runs the same
assertion when manually dispatched with `require_complete=true`.
Normal push and pull-request builds publish progress without failing on the
current incomplete state. Use the manual `require_complete=true` dispatch for
the terminal all-100% gate.

`tools/test_workflow_guards.py` exercises the completion checker, and
`tools/worktree_check.py` validates the main, leaf, and cleanup states before
integration.

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

## Subagent and PR workflow

This repository targets only Wii Menu 4.3U. Do not configure or build 43E,
43J, or 43K while doing matching work.

Most workers should pursue exact matching or safe linking; assign the remainder
to decompilation. Keep up to 75 live workers when the runtime allows it, while
reserving capacity for fixer and validation workers. Fill completed slots with
disjoint tasks. Never duplicate a source file or function
range. Workers return changed paths, exact objdiff measurements, and validation
results. Fuzzy-only results are not accepted.

### Worker loop

Workers iterate until exact-name `objdiff` reports `100.0%`. They must not stop
at a fuzzy score, push, open a PR, or merge. A local commit is fine. Compiler
tie-breaks should be reported with evidence, not hidden behind artificial
assembly or uninitialized values. Exact matching is the handoff point, not
acceptance. A candidate is incomplete until every owned code and data section
and its link metrics are 100%; matching a few functions alone is not enough.
Write new matches as readable C or C++ and keep new inline assembly out of the
source unless the existing target structure makes it unavoidable.

Worker measurements are advisory. Only a fresh orchestrator verification can
accept, push, open, or merge a candidate. Workers are persistent across
validation. After reaching a candidate result,
the worker enters a paused or awaiting-parent state while the orchestrator
performs its checks. Keep the worker handle and its leaf assignment alive. If
pool, ctxdiff, source review, or any other gate fails, send the failure evidence
back to that same worker and resume it on the same leaf. Do not discard a
near-match and silently replace it with a new worker. A worker may be closed
only after its leaf is accepted, explicitly abandoned, or the orchestrator is
stopping the entire goal. A wait timeout is not worker termination; poll the
same handle or inspect its authoritative status before taking recovery action.

The orchestrator must independently rebuild the owned object and verify:

1. `pool_diff.py` reports identical pools, with no first divergence.
2. Exact-name `objdiff` reports `100.0%` for the requested symbol.
3. `ctxdiff.py` reports `diffs 0` and identical instruction counts.
4. Unit-level code, data, function, and link measures for the owned range are
   100%, including every owned section.
5. The focused source diff is minimal, readable, and free of artificial
   assembly, uninitialized values, or unrelated edits.
6. The full 4.3U build passes and `build/43U/main.dol` has SHA1
   `26116613f624061ba99c8d1a299aaa6efa85670d`.

If any orchestrator gate fails, do not promote, push, open a PR, or merge the
candidate. Restore it or send the same disjoint task back to its worker with
the failing evidence. Stage the candidate branch for a PR only after every
gate passes, then regenerate the live progress report before accepting the
next candidate.

For each candidate, the worker must:

1. Run `pool_diff.py` before tuning code generation.
2. Build the 43U object with `/home/cole/projects/tests/.venv/bin/ninja -C . build/43U/src/src/<path>.o`.
3. Require `objdiff` to report `100.0%` for the function and `ctxdiff.py` to report `diffs 0`.
4. Iterate until exact-name objdiff reaches `100.0%`, while preserving the
   pool and source-quality requirements above.
5. Return the focused exact match to the parent agent for review. The parent
   reruns every gate, runs `tools/decomp_status.py` and
   `tools/check_decomp_complete.py`, and runs `/home/cole/projects/tests/.venv/bin/ninja -C . build/43U/ok`;
   the worker does not push, open a PR, or merge.

The main agent reviews every worker result before accepting it. After each
accepted merge, record the new report from `build/43U/report.json` and keep
the DOL hash at `26116613f624061ba99c8d1a299aaa6efa85670d`. Never push to
`upstream`; only the fork's `origin` is in scope.

### Orchestrator ownership boundary

The orchestrator does not perform decompilation or hand-tune worker source.
All source-level reverse engineering, implementation, compiler experiments,
and match iteration belong to the persistent subagents. The orchestrator may
only select disjoint leaves, start and pause workers, resume a worker with
failure evidence, run independent verification commands, review diffs, record
wave state, commit validated leaf-branch changes, push the leaf branch, open
and merge the PR, fast-forward `origin/main`, and publish progress. If a
candidate fails validation, return it to its worker; do not fix the candidate
inline in the orchestrator.

A new thread must begin by reading this file, checking the live 43U report and
remote branch, and dispatching the worker pool. The parent must not claim a
match without fresh independent verification.

### Worktrees, branches, and PR integration

Every leaf gets its own worktree and branch created from the latest
`origin/main`, for example `agent/<wave>/<leaf>`. No two workers may share a
worktree, branch, or source file. A worker may commit locally on its leaf branch
if that is needed to preserve its exact result, but it must not push, open a PR,
or merge.

Use the repository worktree checker before integration and cleanup:

```
python3 tools/worktree_check.py main --synced
python3 tools/worktree_check.py leaf <leaf-worktree> agent/<wave>/<leaf>
python3 tools/worktree_check.py cleanup <leaf-worktree> agent/<wave>/<leaf>
```

The cleanup check is read-only. It succeeds only for a clean leaf branch that
is already an ancestor of `origin/main`; the orchestrator then performs the
explicit `git worktree remove` and local branch deletion.

After the worker reaches its handoff point, the orchestrator validates the
worker's worktree from a fresh build. If every gate passes, the orchestrator
pushes that leaf branch to the fork, opens a PR against `coah80/wii-ipl:main`,
and merges it only after the same gates are recorded in the PR. Never create a
PR against `koopthekoopa/wii-ipl`.

Merge one accepted leaf at a time. After each merge, fetch the new
`origin/main`, regenerate progress, and rebase or recreate all not-yet-merged
leaf branches before their next validation. Re-run objdiff, pool, ctxdiff, the
full build, and the DOL hash after rebasing. The PR itself is not acceptance;
the post-merge main branch is the authority.

The orchestrator may resolve mechanical branch conflicts such as unchanged
context or generated bookkeeping. It must not resolve a semantic source
conflict by inventing decompilation. Send semantic conflicts back to the same
leaf worker, resume it in its worktree, and require the full gates again. Keep
the worktree and worker handle until the leaf is merged, explicitly abandoned,
or the whole goal is stopped; clean them up only after that terminal state.

After a successful merge:

1. Confirm the PR is merged into the fork's `main` and the leaf worktree has no
   uncommitted changes.
2. In the integration/main worktree, run `git fetch origin` followed by
   `git merge --ff-only origin/main` (or an equivalent non-destructive fast
   forward). Do not use `git reset --hard` or overwrite unrelated user work.
3. Re-run the live progress report and the full 4.3U/DOL gates on the updated
   main branch.
4. Rebase each still-active leaf branch onto the new `origin/main` in its own
   worktree, resolve only mechanical conflicts centrally, and send semantic
   conflicts back to that leaf's worker.
5. Only after the leaf is merged, clean, and no longer needed, remove its
   worktree and local branch. A failed or conflicted leaf keeps its worktree
   and worker alive.

## Goal completion contract

The decompilation loop does not stop after a successful wave, a convenient
near-match, or a code-only milestone. Keep dispatching and resuming workers
until the live 43U report proves all of the following:

- Code is 100.00% exact-matched, not merely fuzzy-matched.
- Code is 100.00% fully linked, with no remaining unlinked code units.
- Data is 100.00% extracted/decompiled and 100.00% fully linked.
- Every source unit and function in the 4.3U target is accounted for; no
  `NonMatching`, missing, fuzzy-only, or unlinked unit remains.
- The final full build passes, the DOL hash remains correct, and the report,
  object files, and linked DOL agree.

Until every condition is true and independently verified, the goal remains
active. A worker wave with zero accepted matches is a failed attempt, not a
completion condition; preserve useful workers, resume fixable leaves, and
dispatch the next disjoint batch.

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
