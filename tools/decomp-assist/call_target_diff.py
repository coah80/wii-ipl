"""Advisory direct-call destination audit for objdiff100, equal-size functions.

Run from the repository root: python tools/decomp-assist/call_target_diff.py [unit ...]
Checks REL24/ADDR24 relocations and raw PPC direct BL against the original DOL.
Exit 0: no review rows or skips; 1: review needed; 2: invalid/changing input.
This is not a completion gate or a proof of callee behavior. See call_target_diff.md.
"""

import argparse
from collections import Counter, defaultdict
from dataclasses import dataclass
import hashlib
import io
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

from elftools.common.exceptions import ELFError
from elftools.elf.elffile import ELFFile

import jump_table_diff as elf

DOL_SHA1 = "26116613f624061ba99c8d1a299aaa6efa85670d"


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def branch_target(word, address):
    """Return a PPC I-form direct BL destination, or None for other instructions."""
    if word >> 26 != 18 or not word & 1:
        return None
    displacement = signed(word & 0x03FFFFFC, 26)
    return (displacement if word & 2 else address + displacement) & 0xFFFFFFFF


class Inputs:
    """Fingerprint exact bytes read; detect changes before presenting a result."""

    def __init__(self):
        self.hashes = {}

    def read(self, path):
        path = Path(path)
        raw = path.read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        previous = self.hashes.setdefault(str(path), digest)
        if previous != digest:
            raise ValueError("input changed while reading: " + str(path))
        return raw

    def changed(self):
        return [path for path, digest in self.hashes.items()
                if not Path(path).is_file()
                or hashlib.sha256(Path(path).read_bytes()).hexdigest() != digest]


@dataclass
class CallObject:
    info: elf.ObjectInfo
    data: dict

    def function(self, name):
        symbol = self.info.symbol(name)
        if symbol.kind != "STT_FUNC" or symbol.value % 4 or symbol.size % 4:
            raise ValueError("expected an aligned function: " + name)
        return symbol

    def location(self, section, offset, mechanism):
        functions = [s for s in self.info.symbols if s.section == section
                     and s.kind == "STT_FUNC" and s.value <= offset < s.value + s.size]
        # Multiple names at one start are aliases; overlapping starts are ambiguous.
        starts = {s.value for s in functions}
        start = next(iter(starts)) if len(starts) == 1 else None
        names = sorted({s.name for s in functions}) if start is not None else []
        return {"mechanism": mechanism, "names": names,
                "addend": offset - start if start is not None else 0,
                "section": self.info.sections[section][0], "offset": offset}

    def call(self, function, offset):
        at = function.value + offset
        word = int.from_bytes(self.data[function.section][at:at + 4], "big")
        raw_target = branch_target(word, at)
        if raw_target is None:
            return None
        relocation = self.info.relocs(function.section).get(at)
        if relocation is not None:
            expected = 2 if word & 2 else 10  # R_PPC_ADDR24 / R_PPC_REL24
            if relocation.kind != expected:
                raise ValueError("direct BL has an unsupported relocation kind")
            location = self.info.location(relocation)
            if location is not None:
                section, value = location
                if section not in self.data or value % 4 or not 0 <= value < len(self.data[section]):
                    raise ValueError("call relocation is outside an allocated section")
                return self.location(section, value, "relocation")
            symbol = self.info.symbols[relocation.symbol]
            return {"mechanism": "relocation", "names": [symbol.name],
                    "addend": relocation.addend}
        if word & 2:
            return {"mechanism": "raw_absolute", "names": [], "addend": 0,
                    "address": raw_target}
        return self.location(function.section, raw_target, "raw_relative")


def read_object(path, inputs):
    raw = inputs.read(path)
    info = elf.read_object(path)
    inputs.read(path)  # Shared ELF helper reads the path; reject a concurrent change.
    parsed = ELFFile(io.BytesIO(raw))
    data = {i: section.data() for i, section in enumerate(parsed.iter_sections())
            if section["sh_type"] == "SHT_PROGBITS" and section["sh_flags"] & 2}
    return CallObject(info, data)


class Dol:
    def __init__(self, raw, expected_sha1):
        self.sha1 = hashlib.sha1(raw).hexdigest()
        if self.sha1 != expected_sha1:
            raise ValueError("original DOL SHA1 does not match --dol-sha1")
        if len(raw) < 256:
            raise ValueError("truncated DOL header")
        self.raw = raw
        header = struct.unpack(">64I", raw[:256])
        self.spans = []
        for index in range(18):
            offset, address, size = header[index], header[18 + index], header[36 + index]
            if size:
                if offset < 256 or offset + size > len(raw) or address + size > 0x100000000:
                    raise ValueError("DOL section is outside its file/address space")
                if any(max(address, a) < min(address + size, a + n) for a, n, _ in self.spans):
                    raise ValueError("overlapping DOL address sections")
                self.spans.append((address, size, offset))

    def read(self, address, size):
        matches = [self.raw[offset + address - start:offset + address - start + size]
                   for start, length, offset in self.spans
                   if start <= address and address + size <= start + length]
        if size <= 0 or len(matches) != 1:
            raise ValueError("address is not in one DOL section: 0x%X" % address)
        return matches[0]

    def call(self, address):
        return branch_target(int.from_bytes(self.read(address, 4), "big"), address)


def read_maps(symbol_text, split_text):
    names, sizes, splits = defaultdict(set), defaultdict(set), {}
    for line in symbol_text.splitlines():
        match = re.match(r"(.*?) = (\S+):0x([0-9a-fA-F]+);(.*)", line)
        if not match or not re.search(r"type:(function|label)\b", match[4]):
            continue
        address = int(match[3], 16)
        names[match[1]].add(address)
        size = re.search(r"size:(0x[0-9a-fA-F]+|\d+)\b", match[4])
        if "type:function" in match[4] and size:
            sizes[address].add(int(size[1], 0))
    unit = None
    for line in split_text.splitlines():
        if line and not line[0].isspace() and line.endswith(":") and line != "Sections:":
            unit = line[:-1]
            splits[unit] = {}
        match = re.match(r"\s+(\S+)\s+start:0x([0-9a-fA-F]+)", line)
        if match and unit:
            splits[unit][match[1]] = int(match[2], 16)
    return names, sizes, splits


def addresses(destination, reference, bases, names):
    if destination is None:
        return set()
    if "address" in destination:
        return {destination["address"]}
    result = set()
    for name in destination["names"]:
        local = [s for s in reference.info.symbols if s.name == name
                 and s.kind == "STT_FUNC" and isinstance(s.section, int)]
        if local:
            for symbol in local:
                section = reference.info.sections[symbol.section][0]
                if section in bases:
                    result.add(bases[section] + symbol.value + destination["addend"])
        elif len(names.get(name, ())) == 1:
            result.update(address + destination["addend"] for address in names[name])
    return result


def position_independent_leaf(raw):
    """Conservative filter for body-alias hints, never an equivalence proof."""
    for offset in range(0, len(raw), 4):
        word = int.from_bytes(raw[offset:offset + 4], "big")
        op = word >> 26
        branch_op = (word >> 1) & 1023
        if op == 19 and branch_op in (16, 528) and (word & 1 or branch_op == 528):
            return False  # Indirect call or tail transfer.
        if op in (16, 18):
            displacement = signed(word & (0x03FFFFFC if op == 18 else 0xFFFC),
                                  26 if op == 18 else 16)
            if word & 3 or not 0 <= offset + displacement < len(raw):
                return False  # Link/absolute branches or transfers outside the body.
    return bool(raw) and len(raw) % 4 == 0


def alias_hint(source, destination, source_addresses, target_address, dol, sizes):
    if destination is None or target_address is None or len(sizes.get(target_address, ())) != 1:
        return None
    size = next(iter(sizes[target_address]))
    target_body = dol.read(target_address, size)
    if not position_independent_leaf(target_body):
        return None
    # Different known addresses can share a retail body (e.g. folded constructors).
    if len(source_addresses) == 1:
        address = next(iter(source_addresses))
        if sizes.get(address) == {size} and dol.read(address, size) == target_body:
            return "identical_original_leaf_bodies; current callee implementation not proved"
    # Renamed local helpers need no guessed symbol pairing or name allowlist.
    for name in destination["names"]:
        try:
            function = source.function(name)
        except ValueError:
            continue
        if destination["addend"] or function.size != size:
            continue
        relocations = source.info.relocs(function.section)
        if any(function.value <= at < function.value + size for at in relocations):
            continue
        body = source.data[function.section][function.value:function.value + size]
        if body == target_body:
            return "identical_relocation_free_local_body; alias requires review"
    return None


def compare_function(source, reference, name, bases, names, sizes, dol):
    src, ref = source.function(name), reference.function(name)
    if src.size != ref.size:
        raise ValueError("function extents differ")
    section = reference.info.sections[ref.section][0]
    if section not in bases:
        raise ValueError("no original section base for " + section)
    caller = bases[section] + ref.value
    counts, rows = Counter(), []
    for offset in range(0, ref.size, 4):
        left, right = source.call(src, offset), reference.call(ref, offset)
        expected = dol.call(caller + offset)
        if left is None and right is None and expected is None:
            continue
        counts["calls"] += 1
        for prefix, destination in (("source_", left), ("reference_", right)):
            if destination:
                counts[prefix + destination["mechanism"]] += 1
        actual = addresses(left, reference, bases, names)
        target = addresses(right, reference, bases, names)
        if right and right.get("section") in bases:
            target = {bases[right["section"]] + right["offset"]}
        if bool(right) != (expected is not None) or (target and target != {expected}):
            raise ValueError("reference ELF/DOL disagreement at +0x%X" % offset)
        if left and right and expected is not None and actual == {expected}:
            counts["same_destination"] += 1
            if set(left["names"]) == set(right["names"]):
                continue
            classification = "same_address_alias"
        elif not left or not right:
            classification = "call_shape_difference"
        elif len(actual) != 1:
            classification = "unresolved_destination"
        else:
            classification = "different_destination"
        hint = alias_hint(source, left, actual, expected, dol, sizes)
        rows.append({"function": name, "offset": offset, "caller_address": caller,
                     "classification": classification, "source": left, "reference": right,
                     "source_addresses": sorted(actual), "reference_addresses": sorted(target),
                     "dol_destination": expected, "alias_hint": hint})
        counts[classification] += 1
    return counts, rows


def git_head(root):
    result = subprocess.run(["git", "-C", str(root), "rev-parse", "HEAD"],
                            capture_output=True, text=True)
    return result.stdout.strip() if result.returncode == 0 else None


def audit(root, report_path, dol_path, expected_sha1, units=(), function=None):
    inputs = Inputs()
    inputs.read(Path(__file__))
    inputs.read(Path(elf.__file__))
    before = git_head(root)
    report = json.loads(inputs.read(report_path))
    names, sizes, splits = read_maps(
        inputs.read(root / "config/43U/symbols.txt").decode(),
        inputs.read(root / "config/43U/splits.txt").decode())
    dol = Dol(inputs.read(dol_path), expected_sha1)
    counts, rows, skipped, errors = Counter(), [], [], []
    selected = set(units)
    found = set()
    for unit in report["units"]:
        key = unit["name"].removeprefix("main/")
        if selected and key not in selected:
            continue
        found.add(key)
        functions = [f for f in unit.get("functions", [])
                     if f.get("fuzzy_match_percent") == 100
                     and (function is None or function == f["name"])]
        if not functions:
            if function:
                skipped.append({"unit": key, "function": function,
                                "reason": "function absent or not objdiff100"})
            continue
        try:
            source = read_object(root / "build/43U/src" / (key + ".o"), inputs)
            reference = read_object(root / "build/43U/obj" / (key + ".o"), inputs)
        except (OSError, ValueError, ELFError) as error:
            errors.append({"unit": key, "reason": str(error)})
            continue
        bases = splits.get(unit.get("metadata", {}).get("source_path"), {})
        counts["units"] += 1
        for entry in functions:
            try:
                src, ref = source.function(entry["name"]), reference.function(entry["name"])
                if src.size != ref.size:
                    raise ValueError("function extents differ")
            except ValueError as error:
                skipped.append({"unit": key, "function": entry["name"], "reason": str(error)})
                continue
            try:
                measured, result = compare_function(source, reference, entry["name"],
                                                     bases, names, sizes, dol)
            except (ValueError, KeyError) as error:
                errors.append({"unit": key, "function": entry["name"], "reason": str(error)})
                continue
            counts.update(measured)
            counts["functions"] += 1
            rows.extend(dict(row, unit=key) for row in result)
    for missing in sorted(selected - found):
        errors.append({"unit": missing, "reason": "unit absent from report"})
    after = git_head(root)
    changed = inputs.changed()
    if before != after or changed:
        errors.append({"reason": "inputs changed during audit", "paths": changed})
    result = {"advisory": True, "counts": dict(counts), "rows": rows,
              "skipped_functions": skipped, "errors": errors,
              "provenance": {"head_before": before, "head_after": after,
                             "dol_sha1": dol.sha1, "sha256": inputs.hashes},
              "limits": "Direct BL, objdiff100 and equal extents only. Alias hints require review; "
                        "no callee-behavior, build-freshness or completion proof."}
    return result, 2 if errors else 1 if rows or skipped else 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("units", nargs="*")
    parser.add_argument("--root", type=Path, default=Path("."))
    parser.add_argument("--report", type=Path, help="default: ROOT/build/43U/report.json")
    parser.add_argument("--dol", type=Path, help="default: ROOT/orig/43U/00000008.app")
    parser.add_argument("--dol-sha1", default=DOL_SHA1)
    parser.add_argument("--function", help="one exact-name objdiff100 function; requires one unit")
    parser.add_argument("--output", type=Path, help="write JSON here instead of stdout")
    args = parser.parse_args(argv)
    if args.function and len(args.units) != 1:
        parser.error("--function requires exactly one unit")
    try:
        result, status = audit(args.root, args.report or args.root / "build/43U/report.json",
                               args.dol or args.root / "orig/43U/00000008.app",
                               args.dol_sha1, args.units, args.function)
        output = json.dumps(result, indent=2) + "\n"
        if args.output:
            if args.output.resolve() in {Path(p).resolve() for p in result["provenance"]["sha256"]}:
                raise ValueError("output must not overwrite an audit input")
            args.output.write_text(output)
        else:
            print(output, end="")
        return status
    except (OSError, ValueError, KeyError, ELFError) as error:
        print("ERROR: " + str(error), file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
