#!/usr/bin/env python3
"""Require an inventory entry for every assembly function and zero placeholders."""

import argparse
import ast
import re
import sys
from dataclasses import dataclass
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inc", ".inl"}
ASM_SUFFIXES = {".s", ".asm"}
IDENTIFIER = r"[A-Za-z_$~][\w$~]*(?:::[A-Za-z_$~][\w$~]*)*"
ASM_IDENTIFIER = r"[A-Za-z_.$][\w.$]*"
ASM_TOKEN = re.compile(r"\b(?:asm|__asm|__asm__|nofralloc)\b")
LITERALS = re.compile(
    r'R"(?P<delimiter>[^ ()\\\t\r\n]{0,16})\(.*?\)(?P=delimiter)"'
    r'|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    r"|//(?:\\\r?\n|[^\n])*|/\*.*?\*/",
    re.DOTALL,
)


@dataclass(frozen=True)
class Body:
    file: str
    function: str
    line: int

    @property
    def key(self):
        return self.file, self.function


def mask_literals(text):
    return LITERALS.sub(lambda match: re.sub(r"[^\n]", " ", match.group()), text)


def read_source(path):
    data = path.read_bytes()
    encoding = "utf-16" if data.startswith((b"\xff\xfe", b"\xfe\xff")) else "utf-8-sig"
    return data.decode(encoding)


def closing(text, start, left, right):
    depth = 0
    for pos in range(start, len(text)):
        if text[pos] == left:
            depth += 1
        elif text[pos] == right:
            depth -= 1
            if depth == 0:
                return pos
    raise ValueError(f"unclosed {left!r} at line {text.count(chr(10), 0, start) + 1}")


def function_spans(text):
    spans = []
    for match in re.finditer(rf"(?P<name>{IDENTIFIER})\s*\(", text):
        name = match["name"]
        if name in {"if", "for", "while", "switch", "catch", "sizeof", "__declspec"}:
            continue
        end = closing(text, match.end() - 1, "(", ")")
        tail = re.match(r"\s*(?:(?:const|volatile|override|final|noexcept)\s*)*\{", text[end + 1:])
        if tail:
            start = end + tail.end()
            spans.append((match.start(), start, closing(text, start, "{", "}"), name))
    return spans


def scan_source(path, relative):
    text = read_source(path)
    if not ASM_TOKEN.search(text):
        return []
    text = mask_literals(text)
    markers = list(ASM_TOKEN.finditer(text))
    if not markers:
        return []
    spans = function_spans(text)
    bodies = []
    covered = []
    owners = {}

    def record(span, line):
        name = span[3]
        if name in owners and owners[name] != span[0]:
            raise ValueError(f"line {line}: ambiguous assembly function name: {name}")
        owners[name] = span[0]
        bodies.append(Body(relative, name, line))

    for marker in markers:
        pos = marker.start()
        if any(start <= pos <= end for start, end in covered):
            continue
        line = text.count("\n", 0, pos) + 1
        owner = next((span for span in reversed(spans) if span[1] < pos < span[2]), None)
        if marker.group() == "nofralloc":
            if owner is None:
                raise ValueError(f"line {line}: nofralloc outside a recognized function")
            record(owner, line)
            continue
        tail = re.match(r"\s*(?:(?:volatile|__volatile__|__volatile|inline|goto)\s*)*([({])", text[marker.end():])
        if tail:
            start = marker.end() + tail.end() - 1
            end = closing(text, start, tail[1], "}" if tail[1] == "{" else ")")
            if owner is None:
                raise ValueError(f"line {line}: assembly outside a recognized function")
            record(owner, line)
            covered.append((pos, end))
            continue
        boundary = re.search(r"[;{}]", text[marker.end():])
        if boundary is None:
            raise ValueError(f"line {line}: unrecognized assembly declaration")
        end = marker.end() + boundary.start()
        definition = next((span for span in spans if pos < span[0] < end and span[1] == end), None)
        if definition:
            record(definition, line)
            covered.append((pos, definition[2]))
        elif boundary.group() != ";" or not re.search(rf"{IDENTIFIER}\s*\([^;{{}}]*\)\s*(?:const\s*)?$", text[marker.end():end]):
            raise ValueError(f"line {line}: unrecognized assembly syntax")
    return bodies


def scan_assembly(path, relative):
    text = re.sub(r"/\*.*?\*/", lambda match: "\n" * match.group().count("\n"), read_source(path), flags=re.DOTALL)
    text = re.sub(r"(?m)(?:#|//).*", "", text)
    declared = set()
    for match in re.finditer(r"(?m)^\s*\.(?:global|globl|weak)\s+([^\n]+)", text):
        declared.update(name.strip() for name in match[1].split(","))
    declared.update(re.findall(rf"\.type\s+({ASM_IDENTIFIER})\s*,\s*[@%]function", text))
    bodies = []
    in_code = True
    owner = None
    for line, source in enumerate(text.splitlines(), 1):
        source = source.strip()
        if re.match(r"\.(?:include|incbin|macro|rept|irp|irpc|pushsection|popsection|previous)\b", source):
            raise ValueError(f"line {line}: assembly expansion requires inspection: {source}")
        if re.match(r"(?:\.endfn|endfunc|endfunction)\b", source):
            owner = None
            continue
        section = re.match(r'\.(?:section\s+"?(\.?[\w.$]+)|((?:text|init|fini|data|rodata|bss|sdata2?|sbss2?)\b))', source)
        if section:
            name = (section[1] or section[2]).lstrip(".")
            in_code = name.split(".")[0] in {"text", "init", "fini"} or bool(re.search(r'"[^"\n]*x[^"\n]*"', source))
            owner = None
            continue
        entry = re.match(rf"(?:\.fn|glabel|func|function)\s+({ASM_IDENTIFIER})(?:\s|,|$)", source)
        label = re.match(rf"({ASM_IDENTIFIER})\s*:", source)
        if in_code and (entry or label):
            name = (entry or label)[1]
            if entry or name in declared or owner is None:
                bodies.append(Body(relative, name, line))
                owner = name
            elif name != owner and not name.startswith(".L"):
                raise ValueError(f"line {line}: untyped assembly label requires inspection: {name}")
        elif in_code and source and owner is None:
            if not source.startswith(".") or re.match(r"\.(?:byte|short|word|long|4byte|8byte)\b", source):
                raise ValueError(f"line {line}: executable assembly without a function label")
    return list({body.key: body for body in bodies}.values())


def scan_tree(root):
    paths = set()
    failures = []
    for directory in ("src", "libs"):
        parent = root / directory
        if not parent.is_dir():
            failures.append(f"missing source directory: {directory}")
        else:
            paths.update(path for path in parent.rglob("*") if path.is_file())
    config = root / "configure.py"
    if not config.is_file():
        failures.append("missing configure.py")
    else:
        try:
            tree = ast.parse(config.read_text(encoding="utf-8"))
            for node in ast.walk(tree):
                if not isinstance(node, ast.Constant) or not isinstance(node.value, str):
                    continue
                name = node.value
                if name.lower() in ASM_SUFFIXES:
                    failures.append(f"configure.py: dynamic assembly path requires inspection: {name}")
                    continue
                if Path(name).suffix.lower() not in ASM_SUFFIXES:
                    continue
                candidate = root / name
                matches = [candidate] if candidate.is_file() else [path for path in paths if path.as_posix().endswith("/" + name)]
                if len(matches) != 1:
                    failures.append(f"configure.py: unresolved or ambiguous assembly path: {name}")
                else:
                    paths.add(matches[0])
        except (SyntaxError, OSError, UnicodeError) as exc:
            failures.append(f"configure.py: {exc}")
    bodies = []
    for path in sorted(paths):
        suffix = path.suffix.lower()
        if suffix not in SOURCE_SUFFIXES | ASM_SUFFIXES:
            continue
        try:
            relative = path.relative_to(root).as_posix()
            scanner = scan_assembly if suffix in ASM_SUFFIXES else scan_source
            bodies.extend(scanner(path, relative))
        except (ValueError, OSError, UnicodeError) as exc:
            failures.append(f"{path}: {exc}")
    return bodies, failures


def read_inventory(path):
    rows = {}
    failures = []
    for line, text in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if not text.startswith("|"):
            continue
        cells = [cell.strip() for cell in re.split(r"(?<!\\)\|", text.strip().strip("|"))]
        if cells[0] == "File" or all(re.fullmatch(r":?-+:?", cell) for cell in cells):
            continue
        if len(cells) != 4:
            failures.append(f"inventory line {line}: expected four columns")
            continue
        file, function, verdict, evidence = (cell.strip("`") for cell in cells)
        key = file, function
        if not file or not function or not evidence or verdict not in {"ORIGINAL", "PLACEHOLDER"}:
            failures.append(f"inventory line {line}: invalid entry")
        if key in rows:
            failures.append(f"inventory line {line}: duplicate entry: {file}: {function}")
        rows[key] = verdict
    return rows, failures


def check_inventory(root, inventory=None):
    root = Path(root).resolve()
    bodies, failures = scan_tree(root)
    path = Path(inventory) if inventory is not None else root / "docs/asm-inventory.md"
    try:
        rows, row_failures = read_inventory(path)
    except (OSError, UnicodeError) as exc:
        return bodies, {}, failures + [f"inventory: {exc}"]
    failures.extend(row_failures)
    found = {body.key for body in bodies}
    for file, function in sorted(found - rows.keys()):
        failures.append(f"unlisted assembly: {file}: {function}")
    for file, function in sorted(rows.keys() - found):
        failures.append(f"stale inventory entry: {file}: {function}")
    for (file, function), verdict in sorted(rows.items()):
        if verdict == "PLACEHOLDER":
            failures.append(f"placeholder: {file}: {function}")
    return bodies, rows, failures


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--inventory", type=Path)
    args = parser.parse_args()
    bodies, rows, failures = check_inventory(args.root, args.inventory)
    print(f"Assembly inventory: {len({body.key for body in bodies})} functions, {len(bodies)} bodies/blocks, "
          f"{sum(verdict == 'ORIGINAL' for verdict in rows.values())} ORIGINAL, "
          f"{sum(verdict == 'PLACEHOLDER' for verdict in rows.values())} PLACEHOLDER")
    for failure in failures:
        print(failure, file=sys.stderr)
    print("ASM INVENTORY FAIL" if failures else "ASM INVENTORY PASS")
    return int(bool(failures))


if __name__ == "__main__":
    sys.exit(main())
