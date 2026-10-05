# MWCC permuter adapter

Run `tools/decomp-assist/permuter_mwcc.py` from the assigned worktree. It reads the real 43U
compiler command from Ninja, inserts each candidate into a complete source
snapshot, and scores only the selected retail symbol. The source snapshot keeps
inline definitions and the translation unit's literal pool available to MWCC.

Use `--campaign build/perm2` before the subcommand to keep another campaign separate.
Each campaign needs its own `venv` and `binutils` paths; symlinks to an existing
installation inside the worktree are sufficient. Its attempts log uses the
campaign directory name under `tools/decomp-assist/`.

Prepare the local environment:

1. Build the requested 43U source and original objects. The adapter expects
   decomp-permuter at `../_permuter` and Ninja at the path in the adapter.
2. Create `build/perm/venv` and install `toml`, `python-Levenshtein`, and
   `pyelftools` there. `capstone` is also needed for instruction review.
3. Extract `binutils-powerpc-linux-gnu` into `build/perm/binutils`. The adapter
   uses its `usr/bin/powerpc-linux-gnu-objdump` and
   `usr/lib/x86_64-linux-gnu` library directory. This campaign used Ubuntu's
   `2.42-4ubuntu2.10` amd64 package.

A C input can be prepared directly from MWCC's preprocessed source:

```sh
PYTHONDONTWRITEBYTECODE=1 build/perm/venv/bin/python tools/decomp-assist/permuter_mwcc.py prepare cdb libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt --lineswap
PYTHONDONTWRITEBYTECODE=1 build/perm/venv/bin/python tools/decomp-assist/permuter_mwcc.py baseline build/perm/cdb
```

For C++, pass `--seed` and `--mappings` from
`tools/decomp-assist/permuter/seeds/`, plus `--edit-name` for the source
definition and `--candidate-name` for the parser definition:

| Seed | Source definition | Parser definition |
| --- | --- | --- |
| window | Window::DrawFrame | DrawFrame |
| scan | Setting::scanAP | scanAP |
| es | InitSavedata | InitSavedata |

The positional function argument is the exact retail symbol from the live
objdiff report, including C++ mangling.
The parser context is never compiled. Only the selected body and generated
inline definitions are copied into the real translation unit. Private member
references in extracted helpers can fail compilation; those trials are rejected.
For ESMisc, edit `InitSavedata`, which inlines into `DeleteUnauthorizedData`.

Compare `baseline.o` against the normal source object before starting a search.
Require identical selected-function instructions, matching code/data measures,
and unchanged string pools. Then run up to six prepared inputs:

```sh
PYTHONDONTWRITEBYTECODE=1 build/perm/venv/bin/python tools/decomp-assist/permuter_mwcc.py run build/perm/cdb --seconds 7200
```

`campaign.json` records process lifetimes. Each input has `run.log` and saved
`output-*/source.c` candidates. `settings.toml` raises the MWCC declaration,
commutative, inline, and conditional-block weights. Declaration blocks also use
`PERM_LINESWAP`. Source and `origin/main` must still match the prepared snapshot
when the campaign starts.

The permuter score is a search heuristic. Review every changed expression for
semantics, use mwdbg to explain allocation changes, and rewrite useful hints as
ordinary source. Check the rewritten source with pool_diff, exact-name objdiff,
ctxdiff, and the full gate before retaining it. Empty conditionals and artificial
wrappers can score better and still fail source review.
