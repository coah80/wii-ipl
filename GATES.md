# Gates: Wii Menu decompilation progress

OWNS: src/**, include/**, configure.py, GATES.md

Scope: raise the 43U Wii Menu code match from the current baseline toward 99 percent while preserving build and matching-object correctness

- [x] G0: this ledger passes structural lint
  CHECK: node /home/cole/.agents/skills/unlazy/scripts/gate-lint.mjs GATES.md
  EXPECT: LINT OK
  EVIDENCE: LINT OK (2026-09-19)

- [ ] G1: the measured 43U matched-code percentage reaches 99 percent
  CHECK: /home/cole/projects/tests/.venv/bin/ninja && build/tools/objdiff-cli report generate -p . -o /tmp/wii-ipl-goal-report.json -f json >/dev/null && python3 -c "import json; x=json.load(open('/tmp/wii-ipl-goal-report.json')); p=float(x['measures']['matched_code_percent']); assert p >= 99.0, p; print('99 percent code match passed: %.6f' % p)"
  EXPECT: 99 percent code match passed
  EVIDENCE: 57.463276 percent, 1721124 / 2995172 code bytes, 8736 / 12563 functions (2026-09-19); threshold not reached

- [x] G2: the complete 43U build succeeds after each matching change
  CHECK: python3 configure.py --version 43U && /home/cole/projects/tests/.venv/bin/ninja && test -s build/43U/main.dol && echo 'full 43U build passed'
  EXPECT: full 43U build passed
  EVIDENCE: full 43U build passed after ipl::scene::ChannelTitle::draw match (2026-09-19)

- [x] G3: existing matching objects remain byte-identical to the original DOL
  CHECK: python3 -c "import hashlib; p='build/43U/main.dol'; h=hashlib.sha1(open(p,'rb').read()).hexdigest(); assert h=='26116613f624061ba99c8d1a299aaa6efa85670d', h; print('baseline DOL hash passed')"
  EXPECT: baseline DOL hash passed
  EVIDENCE: baseline DOL SHA-1 26116613f624061ba99c8d1a299aaa6efa85670d (2026-09-19)

- [x] G4: the final working tree has no whitespace errors
  CHECK: git diff --check && echo 'diff check passed'
  EXPECT: diff check passed
  EVIDENCE: diff check passed (2026-09-19)
