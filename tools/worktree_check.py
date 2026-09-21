#!/usr/bin/env python3
import argparse
import subprocess
import sys
from pathlib import Path


def git(*args, cwd=None, check=True):
    result = subprocess.run(
        ["git", *args],
        cwd=cwd,
        check=check,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    return result.stdout.strip(), result.stderr.strip(), result.returncode


def records(root):
    output, _, _ = git("worktree", "list", "--porcelain", cwd=root)
    result = []
    current = {}
    for line in output.splitlines() + [""]:
        if not line:
            if current:
                result.append(current)
                current = {}
            continue
        key, _, value = line.partition(" ")
        if key == "worktree":
            current["path"] = str(Path(value).resolve())
        elif key == "branch":
            current["branch"] = value.removeprefix("refs/heads/")
        elif key == "HEAD":
            current["head"] = value
    return result


def record_for(items, path):
    target = str(Path(path).resolve())
    return next((item for item in items if item.get("path") == target), None)


def clean(path):
    output, _, _ = git("status", "--porcelain", "--untracked-files=all", cwd=path)
    return output == ""


def integration_root(root):
    item = next((item for item in records(root) if item.get("branch") == "main"), None)
    return Path(item["path"]) if item else None


def is_fork_url(value):
    normalized = value.rstrip("/")
    if normalized.endswith(".git"):
        normalized = normalized[:-4]
    return normalized in {
        "https://github.com/coah80/wii-ipl",
        "git@github.com:coah80/wii-ipl",
        "ssh://git@github.com/coah80/wii-ipl",
    }


def main_check(args):
    current_root = Path(git("rev-parse", "--show-toplevel")[0]).resolve()
    root = integration_root(current_root)
    if root is None:
        return "no registered main integration worktree"
    if current_root != root:
        return "run the main check from the integration worktree"
    if git("branch", "--show-current", cwd=root)[0] != "main":
        return "main worktree is not on main"
    remote, _, code = git("remote", "get-url", "origin", cwd=root, check=False)
    if code or not is_fork_url(remote):
        return "origin is not coah80/wii-ipl"
    push_url, _, code = git("remote", "get-url", "--push", "upstream", cwd=root, check=False)
    if code != 0:
        return "upstream remote is missing"
    if "DISABLED_never_push_to_upstream" not in push_url:
        return "upstream push URL is not disabled"
    if not clean(root):
        return "main worktree is dirty"
    prune, _, _ = git("worktree", "prune", "--dry-run", cwd=root)
    if prune:
        return f"orphaned worktree metadata: {prune}"
    if args.synced and git("rev-parse", "HEAD", cwd=root)[0] != git("rev-parse", "origin/main", cwd=root)[0]:
        return "main is not synchronized with origin/main"
    return None


def leaf_check(args):
    root = Path(git("rev-parse", "--show-toplevel")[0]).resolve()
    item = record_for(records(root), args.path)
    if not item:
        return "leaf path is not registered as a worktree"
    if item.get("branch") != args.branch:
        return "leaf branch does not match the worktree record"
    if not args.branch.startswith("agent/"):
        return "leaf branch must use the agent/ prefix"
    if args.path.resolve() == root:
        return "leaf path is the integration worktree"
    return None


def cleanup_check(args):
    root = Path(git("rev-parse", "--show-toplevel")[0]).resolve()
    item = record_for(records(root), args.path)
    if not item:
        return "leaf path is not registered as a worktree"
    if args.path.resolve() == root:
        return "integration worktree cannot be cleaned up"
    if not item.get("branch"):
        return "detached worktree cannot be cleaned up"
    if not item["branch"].startswith("agent/"):
        return "only agent branches can be cleaned up"
    if item.get("branch") != args.branch:
        return "leaf branch does not match the worktree record"
    if args.merged_ref != "origin/main":
        return "cleanup must verify ancestry against origin/main"
    if not clean(args.path):
        return "leaf worktree is dirty"
    _, _, code = git("merge-base", "--is-ancestor", args.branch, args.merged_ref, cwd=root, check=False)
    if code != 0:
        return f"leaf branch is not merged into {args.merged_ref}"
    return None


def main():
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest="mode", required=True)
    main_parser = subparsers.add_parser("main")
    main_parser.add_argument("--synced", action="store_true")
    leaf_parser = subparsers.add_parser("leaf")
    leaf_parser.add_argument("path", type=Path)
    leaf_parser.add_argument("branch")
    cleanup_parser = subparsers.add_parser("cleanup")
    cleanup_parser.add_argument("path", type=Path)
    cleanup_parser.add_argument("branch")
    cleanup_parser.add_argument("--merged-ref", default="origin/main")
    args = parser.parse_args()
    if args.mode == "main":
        failure = main_check(args)
    elif args.mode == "leaf":
        failure = leaf_check(args)
    else:
        failure = cleanup_check(args)
    if failure:
        print(f"WORKTREE_CHECK_FAIL: {failure}")
        return 1
    print("WORKTREE_CHECK_OK")
    return 0


if __name__ == "__main__":
    sys.exit(main())
