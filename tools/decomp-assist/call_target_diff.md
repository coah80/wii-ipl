# Direct-call destination advisory

`call_target_diff.py` checks the callees of functions reported as objdiff100.
A 100% instruction score can still conceal a different relocation target. This
tool compares resolved destination addresses with branches decoded independently
from the original 43U DOL. It does not change source, build outputs, configuration,
CI, or the completion policy.

Requires Python and pyelftools, as do the neighboring ELF tools. Run from the
repository root after preparing the normal 43U objects and report:

```sh
python tools/decomp-assist/call_target_diff.py --output /tmp/call-targets.json
python tools/decomp-assist/call_target_diff.py src/scene/setting/iplSetting
python tools/decomp-assist/call_target_diff.py UNIT --function EXACT_SYMBOL
python -m unittest discover -s tools/decomp-assist -p test_call_target_diff.py
```

With no unit arguments, it scans the report. Unit names omit the `main/` prefix
and `.o` suffix. `--function` requires exactly one unit and still requires that
function to be reported100. JSON goes to stdout unless `--output` is supplied.
The output path cannot overwrite an input.

`--root` selects another prepared repository. `--report` and `--dol` override
input paths; otherwise they are `ROOT/build/43U/report.json` and
`ROOT/orig/43U/00000008.app`. Relative overrides are relative to the current
working directory. The DOL must match the known 43U SHA1 by default; `--dol-sha1`
accepts an explicitly verified alternative hash, including authored test inputs.
The configuration remains 43U.

## What it checks

Only exact-name functions with equal source/reference extents and
`fuzzy_match_percent == 100` are compared. Missing/ambiguous functions and
unequal extents are reported as skips. Direct unconditional PPC `bl` instructions
are decoded whether they have explicit `R_PPC_REL24`/`R_PPC_ADDR24` relocations or
already contain resolved branch displacements. Signed relative and absolute
encodings are supported.

Section-relative relocation targets and raw local branches resolve through
actual function extents. Aliases sharing one function start are retained;
overlapping distinct function starts remain unresolved. A matching reference
symbol or an unambiguous configured address maps the source callee into the
original address space. The original DOL supplies the reference call destination,
and reference-object disagreement is an input error. Symbol spelling alone is
not accepted as proof that two distinct callees are equivalent.

Rows classify:

- `different_destination`: source resolves to a different original address
- `unresolved_destination`: source has no unique original-address mapping
- `same_address_alias`: different names resolve to the same original address
- `call_shape_difference`: only one object has a direct call at that offset

Rows are candidates for inspection, not automatic bug reports. Different
constructor addresses can have identical bodies; a generated assignment or
anonymous wrapper can implement the same operation under another name. Optional
`alias_hint` evidence identifies identical original leaf bodies or a local
relocation-free body identical to the original callee. Hints require compatible
extents, equal bytes, and conservative branch checks; they do not suppress rows
or establish general semantic equivalence. Helpers containing relocations may
remain unresolved even when manual review can establish equivalence. No symbol
name, constructor prefix, or wrapper prefix is silently excluded.

An unresolved symbol is not necessarily a missing implementation: it may be a
renamed helper, external symbol, or ambiguous map entry. Check source definitions,
linker aliases, receiver types, and the actual callee before proposing a fix.

## Provenance and exits

JSON includes both observed Git heads, the original-DOL SHA1, and SHA-256 hashes
of the exact report, symbol/split maps, object files, tool, and shared ELF helper
read by the scan. Inputs are fingerprinted again at the end. A changed head or
input produces an error rather than a clean result. No binary or assembly bytes
are written into the report.

These fingerprints identify what was inspected. They do not prove that cached
objects were rebuilt from the stated source commit or that the report is fresh.
For a serious candidate, preserve its inputs and independently rebuild/verify
that specific commit before changing source.

Exit statuses are advisory:

- 0: no review rows, skips, or input errors in the selected scope
- 1: rows or skipped functions require review
- 2: invalid, missing, inconsistent, or changing input

An empty or entirely nonexact selection can check zero calls. Always inspect the
counts. A clean result does not establish completion, whole-program equivalence,
or correct callee bodies. Indirect calls, tail calls, conditional branch-and-link,
nonexact callers, and unequal extents are outside this pass. Runtime behavior,
callback effects, and floating-point evaluation order still require focused
review.

## Tests

Tests build small ELF32/PPC objects and DOL containers from authored instruction
words and metadata in temporary directories. They cover an incorrect relocation
destination despite identical instruction bytes, raw local branches, shifted
function locations, interior targets, address/constructor/wrapper aliases,
undefined destinations, malformed references, original-DOL disagreement,
selection skips, input changes, and JSON exit behavior. No original executable
bytes or assembly are embedded in the tool, documentation, or tests.
