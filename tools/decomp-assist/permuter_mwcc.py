#!/usr/bin/env python3
"""Run single-function permuter candidates in their original MWCC translation unit."""

import argparse
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile
import time


sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
CAMPAIGN = ROOT / "build/perm"
PERMUTER = ROOT.parent / "_permuter"
NINJA = Path("/home/cole/projects/tests/.venv/bin/ninja")


def span(source, name):
    pattern = re.compile(r"\b" + re.escape(name) + r"\s*\([^;{}]*\)\s*(?:const\s*)?\{")
    match = pattern.search(source)
    if not match:
        raise ValueError(f"Function definition not found: {name}")
    opening = match.end() - 1
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*[\s\S]*?\*/|//[^\n]*|[{}]')
    depth = 0
    for token in tokens.finditer(source, opening):
        if token.group() == "{":
            depth += 1
        elif token.group() == "}":
            depth -= 1
            if not depth:
                start = source.rfind("\n", 0, match.start()) + 1
                return start, opening, token.end()
    raise ValueError(f"Unclosed function: {name}")


def imports():
    sys.path.insert(0, str(PERMUTER))
    from perm_pycparser import CParser, c_ast, c_generator
    from strip_other_fns import strip_other_fns
    return CParser, c_ast, c_generator, strip_other_fns


def command_for(unit):
    commands = subprocess.check_output(
        [str(NINJA), "-t", "commands", f"build/43U/src/{unit}.o"],
        cwd=ROOT, text=True,
    ).splitlines()
    command = next(line for line in reversed(commands) if "mwcceppc.exe" in line)
    words = shlex.split(command.split(" && ")[0])
    source = words[words.index("-c") + 1]
    flags = words[:words.index("-MMD")]
    return source, flags


def prepare(args):
    CParser, ca, cg, strip = imports()
    directory = CAMPAIGN / args.name
    directory.mkdir(parents=True, exist_ok=False)
    source_path, flags = command_for(args.unit)
    reference = (ROOT / source_path).read_text()
    source = Path(args.start).read_text() if args.start else reference
    mappings = {}
    edit_name = args.edit_name or args.function
    start, opening, end = span(source, edit_name)
    (directory / "original.txt").write_text(source)
    (directory / "reference.txt").write_text(reference)
    if args.seed:
        seed = Path(args.seed).read_text()
        candidate_name = args.candidate_name or args.function
    else:
        preprocessed = directory / "preprocessed.i"
        preprocess_source = str(Path(args.start).resolve()) if args.start else source_path
        subprocess.run(flags + ["-i", str(Path(source_path).parent), "-E", preprocess_source,
                                "-o", str(preprocessed)], cwd=ROOT, check=True)
        seed = strip(preprocessed.read_text(errors="replace"), edit_name)
        seed = re.sub(r"^#.*", "", seed, flags=re.M)
        for identifier in set(re.findall(r"\b\w*PERM_\w+", seed)):
            renamed = identifier.replace("PERM_", "PERMISSION_")
            mappings[renamed] = identifier
            seed = re.sub(r"\b" + re.escape(identifier) + r"\b", renamed, seed)
        candidate_name = edit_name
    ast = CParser().parse(seed)
    function = next(node for node in ast.ext if isinstance(node, ca.FuncDef) and node.decl.name == candidate_name)
    if args.lineswap:
        def mark_declarations(node):
            for _, child in node.children():
                mark_declarations(child)
            if not isinstance(node, ca.Compound):
                return
            result, declarations = [], []
            for item in list(node.block_items or []) + [None]:
                if (isinstance(item, ca.Decl) and item.init is None
                        and "\n" not in cg.CGenerator().visit(item).rstrip("\n")):
                    declarations.append(item)
                    continue
                if len(declarations) > 1:
                    result.append(ca.Pragma("permuter_decl_begin"))
                    result.extend(declarations)
                    result.append(ca.Pragma("permuter_decl_end"))
                else:
                    result.extend(declarations)
                declarations = []
                if item is not None:
                    result.append(item)
            node.block_items = result

        mark_declarations(function.body)
        generator = cg.CGenerator()
        context = generator.visit(ca.FileAST([node for node in ast.ext if node is not function]))
        definition = generator.visit(function)
        definition = re.sub(r"#pragma permuter_decl_begin", "PERM_LINESWAP(", definition)
        definition = re.sub(r"#pragma permuter_decl_end", ")", definition)
        seed = context + "\nPERM_RANDOMIZE(\n" + definition + "\n)\n"
    else:
        seed = cg.CGenerator().visit(ast)
    (directory / "base.c").write_text(seed)
    if args.mappings:
        mappings.update(json.loads(Path(args.mappings).read_text()))
    metadata = dict(unit=args.unit, symbol=args.function, source=source_path,
                    edit_name=edit_name, candidate_name=candidate_name,
                    start=start, opening=opening, end=end, flags=flags, mappings=mappings)
    (directory / "job.json").write_text(json.dumps(metadata, indent=2) + "\n")
    shutil.copyfile(ROOT / f"build/43U/obj/{args.unit}.o", directory / "target.o")
    python = CAMPAIGN / "venv/bin/python"
    tool = Path(__file__).resolve()
    compile_command = shlex.join([str(python), str(tool), "--campaign", str(CAMPAIGN), "compile", str(directory)])
    (directory / "compile.sh").write_text('#!/bin/sh\nexec ' + compile_command + ' "$@"\n')
    (directory / "compile.sh").chmod(0o755)
    objdump_command = shlex.join([str(python), str(tool), "--campaign", str(CAMPAIGN), "objdump", str(directory)])
    settings = (ROOT / "tools/decomp-assist/permuter/settings.toml").read_text()
    settings = 'func_name = ' + json.dumps(candidate_name) + '\nobjdump_command = ' + json.dumps(objdump_command) + '\n' + settings
    (directory / "settings.toml").write_text(settings)
    print(directory.relative_to(ROOT))


def materialize(directory, candidate):
    metadata = json.loads((directory / "job.json").read_text())
    _, opening, end = span(candidate, metadata["candidate_name"])
    body = candidate[opening:end] + "\n"
    definitions = []
    pattern = re.compile(r"(?m)^\s*(?:static\s+)?inline\b[^\n;{]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{")
    for match in pattern.finditer(candidate):
        name = match.group(1)
        if name != metadata["candidate_name"]:
            start, _, end = span(candidate, name)
            definitions.append(candidate[start:end] + "\n\n")
    helpers = "\n".join(definitions)
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|\b[A-Za-z_]\w*\b')
    replace = lambda match: metadata["mappings"].get(match.group(), match.group())
    body = tokens.sub(replace, body)
    helpers = tokens.sub(replace, helpers)
    original = (directory / "original.txt").read_text()
    start, opening, end = (metadata[key] for key in ("start", "opening", "end"))
    source = original[:start] + helpers + "\n" + original[start:opening] + body
    line = original.count("\n", 0, end) + 1
    source += '\n#line ' + str(line) + ' ' + json.dumps(metadata["source"]) + '\n' + original[end:]
    return metadata, '#line 1 ' + json.dumps(metadata["source"]) + '\n' + source


def compile_candidate(args):
    metadata, source = materialize(Path(args.directory), Path(args.input).read_text())
    with tempfile.TemporaryDirectory(dir=CAMPAIGN, prefix="compile-") as temporary:
        path = Path(temporary) / Path(metadata["source"]).name
        path.write_text(source)
        command = metadata["flags"] + ["-i", str(Path(metadata["source"]).parent), "-c", str(path), "-o", str(Path(args.output).resolve())]
        result = subprocess.run(command, cwd=ROOT)
    raise SystemExit(result.returncode)


def objdump(args):
    from elftools.elf.elffile import ELFFile
    metadata = json.loads((Path(args.directory) / "job.json").read_text())
    with open(args.object, "rb") as stream:
        elf = ELFFile(stream)
        symbols = elf.get_section_by_name(".symtab")
        matches = symbols.get_symbol_by_name(metadata["symbol"])
        if not matches:
            raise ValueError(f"Missing symbol: {metadata['symbol']}")
        symbol = matches[0]
        start, size = symbol["st_value"], symbol["st_size"]
        relocations = {}
        section = elf.get_section_by_name(".rela.text")
        if section is not None:
            for relocation in section.iter_relocations():
                target = symbols.get_symbol(relocation["r_info_sym"])
                index = target["st_shndx"]
                if isinstance(index, int):
                    name = elf.get_section(index).name
                    if name != ".text":
                        offset = target["st_value"] + relocation["r_addend"]
                        relocations[relocation["r_offset"]] = name.replace(".", "section_") + f"_{offset:x}"
    env = dict(os.environ)
    env["LD_LIBRARY_PATH"] = str(CAMPAIGN / "binutils/usr/lib/x86_64-linux-gnu")
    command = [str(CAMPAIGN / "binutils/usr/bin/powerpc-linux-gnu-objdump"),
               "-dr", "-EB", "-mpowerpc", "-M", "broadway", "-j", ".text",
               f"--start-address={start}", f"--stop-address={start + size}", args.object]
    output = subprocess.check_output(command, env=env, text=True)
    rows = []
    for row in output.splitlines():
        match = re.match(r"\s*([0-9a-f]+):", row)
        if match and not start <= int(match.group(1), 16) < start + size:
            continue
        if match and "R_PPC_" in row:
            address = int(match.group(1), 16)
            if address in relocations:
                row = re.sub(r"(R_PPC_\w+\s+)\S+", lambda item: item.group(1) + relocations[address], row)
        rows.append(row)
    print("\n".join(rows))


def baseline(args):
    imports()
    from src.candidate import Candidate
    from src.compiler import Compiler
    from src.helpers import get_default_randomization_weights, merge_randomization_weights
    from src.perm.parse import perm_parse
    from src.perm.eval import perm_evaluate_one
    from src.preprocess import preprocess
    from src.scorer import Scorer
    import toml

    directory = Path(args.directory).resolve()
    settings = toml.loads((directory / "settings.toml").read_text())
    weights = merge_randomization_weights(get_default_randomization_weights("mwcc"), settings["weight_overrides"])
    source, state = perm_evaluate_one(perm_parse(preprocess(str(directory / "base.c"))))
    candidate = Candidate.from_source(source, state, settings["func_name"], weights, rng_seed=0)
    (directory / "baseline.c").write_text(candidate.get_source())
    compiler = Compiler(str(directory / "compile.sh"), show_errors=True, debug_mode=False)
    compiled = candidate.compile(compiler)
    if not compiled:
        raise RuntimeError("Baseline compilation failed")
    shutil.move(compiled, directory / "baseline.o")
    scorer = Scorer(str(directory / "target.o"), stack_differences=True,
                    algorithm="difflib", debug_mode=False, ign_branch_targets=True,
                    objdump_command=settings["objdump_command"])
    score, digest = scorer.score(str(directory / "baseline.o"))
    (directory / "baseline-score.json").write_text(json.dumps(dict(score=score, digest=digest), indent=2) + "\n")
    print(directory.name, "baseline score", score)


def run_campaign(args):
    if not 7200 <= args.seconds <= 14400:
        raise ValueError("Campaign runs must last between two and four hours")
    if len(args.directories) > 6:
        raise ValueError("At most six permuter processes may run at once")
    temporary = CAMPAIGN / "tmp"
    temporary.mkdir(exist_ok=True)
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE="1", TMPDIR=str(temporary))
    jobs = []
    state_path = CAMPAIGN / "campaign.json"
    log_path = ROOT / "tools/decomp-assist" / (CAMPAIGN.name + ".attempts.md")
    try:
        for name in args.directories:
            directory = Path(name).resolve()
            metadata = json.loads((directory / "job.json").read_text())
            reference = directory / "reference.txt"
            source = (reference if reference.exists() else directory / "original.txt").read_text()
            current = (ROOT / metadata["source"]).read_text()
            remote = subprocess.check_output(["git", "show", "origin/main:" + metadata["source"]], cwd=ROOT, text=True)
            if source != current or source != remote:
                raise ValueError(f"Source changed since preparation: {metadata['source']}")
            output = (directory / "run.log").open("w")
            command = [str(CAMPAIGN / "venv/bin/python"), "-u", str(PERMUTER / "permuter.py"), str(directory),
                       "-j", "1", "--stack-diffs", "--best-only", "--better-only", "--stop-on-zero"]
            process = subprocess.Popen(command, cwd=ROOT, env=env, stdout=output, stderr=subprocess.STDOUT,
                                       start_new_session=True)
            output.close()
            job = dict(directory=str(directory), symbol=metadata["symbol"], pid=process.pid,
                       started=time.time(), seconds=args.seconds, returncode=None, stopped=False, finished=None)
            jobs.append((process, job))
            with log_path.open("a") as log:
                log.write(f"\nStarted {metadata['symbol']}, PID {process.pid}, {args.seconds} seconds, {time.strftime('%Y-%m-%d %H:%M:%S UTC', time.gmtime())}.\n")
        while any(process.poll() is None for process, _ in jobs):
            now = time.time()
            for process, job in jobs:
                if process.poll() is None and now - job["started"] >= args.seconds:
                    if not job["stopped"]:
                        os.killpg(process.pid, signal.SIGINT)
                        job["stopped"] = True
                    elif now - job["started"] >= args.seconds + 30:
                        os.killpg(process.pid, signal.SIGTERM)
                job["returncode"] = process.poll()
                if job["returncode"] is not None and job["finished"] is None:
                    job["finished"] = now
                job["elapsed"] = round((job["finished"] or now) - job["started"], 1)
            state_path.write_text(json.dumps([job for _, job in jobs], indent=2) + "\n")
            time.sleep(1)
    finally:
        for process, job in jobs:
            if process.poll() is None:
                os.killpg(process.pid, signal.SIGINT)
                try:
                    process.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    os.killpg(process.pid, signal.SIGTERM)
                    process.wait(timeout=10)
            job["returncode"] = process.returncode
            job["finished"] = job["finished"] or time.time()
            job["elapsed"] = round(job["finished"] - job["started"], 1)
        state_path.write_text(json.dumps([job for _, job in jobs], indent=2) + "\n")
    print(json.dumps([job for _, job in jobs], indent=2))


def main():
    global CAMPAIGN
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--campaign", type=Path, default=CAMPAIGN)
    subparsers = parser.add_subparsers(dest="action", required=True)
    setup = subparsers.add_parser("prepare")
    setup.add_argument("name")
    setup.add_argument("unit")
    setup.add_argument("function")
    setup.add_argument("--edit-name")
    setup.add_argument("--candidate-name")
    setup.add_argument("--seed")
    setup.add_argument("--start", help="alternate full translation unit for a source candidate")
    setup.add_argument("--mappings")
    setup.add_argument("--lineswap", action="store_true")
    setup.set_defaults(run=prepare)
    compiler = subparsers.add_parser("compile")
    compiler.add_argument("directory")
    compiler.add_argument("input")
    compiler.add_argument("-o", dest="output", required=True)
    compiler.set_defaults(run=compile_candidate)
    dump = subparsers.add_parser("objdump")
    dump.add_argument("directory")
    dump.add_argument("object")
    dump.set_defaults(run=objdump)
    check = subparsers.add_parser("baseline")
    check.add_argument("directory")
    check.set_defaults(run=baseline)
    run = subparsers.add_parser("run")
    run.add_argument("directories", nargs="+")
    run.add_argument("--seconds", type=int, default=7200)
    run.set_defaults(run=run_campaign)
    args = parser.parse_args()
    CAMPAIGN = args.campaign.resolve()
    if not CAMPAIGN.is_relative_to(ROOT / "build"):
        raise ValueError("Campaign files must stay inside this worktree build directory")
    args.run(args)


if __name__ == "__main__":
    main()
