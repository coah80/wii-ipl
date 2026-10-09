# AGENTS.md

The Wii Menu 4.3U decompilation is finished: every unit matches and links, and
the build reproduces the retail DOL. There is no matching, linking or cleanup
work left to continue. Work only on what the user asks for.

## Never touch upstream

Do not push to, open pull requests or issues against, or comment on
`koopthekoopa/wii-ipl`. Its maintainers do not want AI-authored work. `origin`
(`coah80/wii-ipl`) is this fork; `upstream` has its push URL set to
`DISABLED_never_push_to_upstream` on purpose. Never pass
`--repo koopthekoopa/wii-ipl` to `gh`.

## Keep the build matching

Any source change must keep the output byte-identical:

```
python3 configure.py --version 43U
ninja
sha1sum build/43U/main.dol   # 26116613f624061ba99c8d1a299aaa6efa85670d
```

Comments in the source that name a compiler requirement mark code shaped to
match the original binary; changing it changes the bytes.
