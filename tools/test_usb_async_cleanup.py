#!/usr/bin/env python3
"""Run host-only USB failure-path tests; does not use or change the 43U build."""

import argparse
import os
from pathlib import Path
import shlex
import subprocess
import tempfile


def main():
    root = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cc", default=os.environ.get("CC", "cc"), help="C11 compiler command (default: CC or cc)")
    parser.add_argument("--source", type=Path, default=root / "libs/RVL_SDK/src/usb/usb.c", help="usb.c to test, optionally an extracted baseline")
    parser.add_argument("--case", choices=["all", "iso", "insertion", "class", "list", "unicode", "wrappers"], default="all")
    parser.add_argument("--no-sanitize", action="store_true", help="run without AddressSanitizer and UBSan")
    parser.add_argument("--leak-check", action="store_true", help="enable LeakSanitizer; requires an environment without ptrace")
    args = parser.parse_args()
    source = args.source.resolve(strict=True)
    tests = root / "tools/tests/usb"
    env = dict(os.environ)
    # Allocation tracking in the harness also checks exactly-once frees.
    env["ASAN_OPTIONS"] = f"detect_leaks={int(args.leak_check)}:abort_on_error=1"
    env["UBSAN_OPTIONS"] = "halt_on_error=1:print_stacktrace=1"
    with tempfile.TemporaryDirectory(prefix="usb-async-tests-") as temporary:
        for signedness in ("signed", "unsigned"):
            binary = Path(temporary) / f"usb-{signedness}"
            command = shlex.split(args.cc) + [
                "-std=c11", "-O1", "-g", f"-f{signedness}-char",
                "-I", str(tests / "include"),
                f'-DUSB_SOURCE="{source}"', str(tests / "usb_async_cleanup_test.c"),
                "-o", str(binary),
            ]
            if not args.no_sanitize:
                command += ["-fsanitize=address,undefined", "-fno-omit-frame-pointer", "-no-pie"]
            print(f"Testing {source} with {signedness} char", flush=True)
            subprocess.run(command, check=True)
            subprocess.run([str(binary), args.case], check=True, env=env)


if __name__ == "__main__":
    main()
