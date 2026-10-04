# sz2 jump-table data round

Worktree data-d4, branch agent/w1004/sz2, baseline f598e410. Fork fetch confirms the assigned sources are current. Initial full build and empty string pools pass. Existing untracked attempts logs are untouched.

Acceptance: increase whole-section matched data with no function percentage or exact/data/link regressions; preserve readable C, full clean gate and retail DOL. Only zi8InternalGetZH and Zi8AlphaGetCandidates are source targets. Keep jt_layout.py for reuse.

Baseline: zi8cgetc data 144/536, exact functions 5/8, code 4168/47816, engine 96.27482%, 10676 instructions. zi8alpha data 516/564, exact functions 11/12, code 5880/21664, engine 95.23011%, 3946 instructions.

Live ELF correction: zi8cgetc owns four tables, 11 + 11 + 40 + 36 = 98 entries. The 11-entry table at .data+0x2c already has the target offsets. The other three tables have uniform shifts of +8, +4 and +4 bytes. Alpha owns 12 entries with varying shifts. Prior Zhuyin semantic label correction is retained. Prior declaration-order, generic workspace and unsafe cursor experiments are not repeated.

Trial zi8alpha alpha-discard-signature: {"label": "alpha-discard-signature", "score": 95.23011, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 0, 12, [-8, 8, 12]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "78816ffc9dec"}.

Trial zi8cgetc zh-charset-explicit: {"label": "zh-charset-explicit", "score": 96.27482, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "a65e88b8f288"}.

Trial zi8cgetc zh-charset-shift: {"label": "zh-charset-shift", "score": 96.27014, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 96.27014]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b2e8ffeabcaf"}.

Trial zi8cgetc zh-charset-fullwidth: {"label": "zh-charset-fullwidth", "score": 96.27482, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b4f91fdec556"}.

Trial zi8cgetc zh-charset-local: {"label": "zh-charset-local", "score": 93.49054, "insns": [10679, 10676], "data": "24", "matched_functions": 5, "tables": [[0, 0, 11, [12]], [44, 0, 11, [8]], [88, 0, 40, [20]], [248, 0, 36, [20]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.49054]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "de5ed1dce5d6"}.

Trial zi8cgetc zh-charset-case-scope: {"label": "zh-charset-case-scope", "score": 93.490074, "insns": [10679, 10676], "data": "24", "matched_functions": 5, "tables": [[0, 0, 11, [12]], [44, 0, 11, [8]], [88, 0, 40, [20]], [248, 0, 36, [20]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.490074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "57ab7f759167"}.

Trial zi8alpha alpha-workspace-state: {"label": "alpha-workspace-state", "score": 95.255196, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.490074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "716f21d498e9"}.

Trial zi8alpha alpha-result-tests: {"label": "alpha-result-tests", "score": 95.05398, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 12, 16]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.05398], ["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.490074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "e189d55ca746"}.

Trial zi8alpha alpha-rom-direct-tests: {"label": "alpha-rom-direct-tests", "score": 95.05651, "insns": [3952, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.05651], ["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.490074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "792df2a8f6d0"}.

Trial zi8alpha alpha-rom-cursor: {"label": "alpha-rom-cursor", "score": 95.22504, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 0, 12, [-8, 8, 12]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.22504], ["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 93.490074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "3661ce11e452"}.

Trial zi8alpha alpha-work-direct-all: {"label": "alpha-work-direct-all", "score": 95.093, "insns": [3955, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [16, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.093]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0904346dfd55"}.

Trial zi8alpha alpha-work-direct-vowels: {"label": "alpha-work-direct-vowels", "score": 95.098076, "insns": [3952, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.098076]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "016f40d9ebc0"}.

Trial zi8alpha alpha-work-direct-exclusions: {"label": "alpha-work-direct-exclusions", "score": 95.112015, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [12, 16, 20]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.112015]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "77b1623dc1b0"}.

Trial zi8alpha alpha-work-prefix-mask: {"label": "alpha-work-prefix-mask", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "2c9164b556fb"}.

Trial zi8alpha alpha-work-rom-mask: {"label": "alpha-work-rom-mask", "score": 95.255196, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "52007b4454be"}.

Trial zi8cgetc zh-charset-if: {"label": "zh-charset-if", "score": 95.88394, "insns": [10675, 10676], "data": "24", "matched_functions": 5, "tables": [[0, 0, 11, [-4]], [44, 0, 11, [-12]], [88, 40, 40, [0]], [248, 36, 36, [0]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 95.88394]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "1712c7cbbfa3"}.

Trial zi8cgetc zh-charset-switch-descending: {"label": "zh-charset-switch-descending", "score": 96.26264, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 96.26264]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "7dfff5d50c88"}.

Trial zi8cgetc zh-charset-switch-independent: {"label": "zh-charset-switch-independent", "score": 95.86427, "insns": [10673, 10676], "data": "24", "matched_functions": 5, "tables": [[0, 0, 11, [-12]], [44, 0, 11, [-20]], [88, 0, 40, [-8]], [248, 0, 36, [-8]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 95.86427]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "39221d9155ac"}.

Trial zi8alpha alpha-rom-test-0: {"label": "alpha-rom-test-0", "score": 95.14749, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.14749]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "ac47c66f9ad7"}.

Trial zi8alpha alpha-rom-test-1: {"label": "alpha-rom-test-1", "score": 95.17537, "insns": [3948, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 16, 20]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.17537]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "c39ebcb0f473"}.

Trial zi8alpha alpha-rom-test-2: {"label": "alpha-rom-test-2", "score": 95.176636, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.176636]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "852fe05623b4"}.

Trial zi8alpha alpha-rom-test-3: {"label": "alpha-rom-test-3", "score": 95.15256, "insns": [3950, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 24, 28]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.15256]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "c0f644eb2e1b"}.

Trial zi8alpha alpha-rom-test-4: {"label": "alpha-rom-test-4", "score": 95.176636, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.176636]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "63f9a7f37b0e"}.

Trial zi8alpha alpha-rom-test-5: {"label": "alpha-rom-test-5", "score": 95.17917, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 20, 24]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.17917]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "429f68481d6b"}.

Trial zi8alpha alpha-rom-assign-0: {"label": "alpha-rom-assign-0", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "c03c813ce27c"}.

Trial zi8alpha alpha-rom-assign-1: {"label": "alpha-rom-assign-1", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "bb34dc16c3f6"}.

Trial zi8alpha alpha-rom-assign-2: {"label": "alpha-rom-assign-2", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "c69272dc9e3b"}.

Trial zi8alpha alpha-rom-assign-3: {"label": "alpha-rom-assign-3", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b9431e76dad5"}.

Trial zi8alpha alpha-rom-assign-4: {"label": "alpha-rom-assign-4", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "bbc58258caf0"}.

Trial zi8alpha alpha-rom-assign-5: {"label": "alpha-rom-assign-5", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "085e2657bccc"}.

Trial zi8alpha alpha-rom-assign-all: {"label": "alpha-rom-assign-all", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "39edabc35710"}.

Trial zi8alpha alpha-rom-scope-int: {"label": "alpha-rom-scope-int", "score": 92.28662, "insns": [3970, 3946], "data": "336", "matched_functions": 11, "tables": [[0, 0, 12, [24, 84, 88]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 92.28662]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "7849a0ad293c"}.

Trial zi8alpha alpha-rom-scope-ziBool: {"label": "alpha-rom-scope-ziBool", "score": 92.48074, "insns": [3965, 3946], "data": "336", "matched_functions": 11, "tables": [[0, 0, 12, [24, 52, 56]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 92.48074]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "eab53c49a105"}.

Trial zi8alpha alpha-rom-scope-ziU32: {"label": "alpha-rom-scope-ziU32", "score": 92.28662, "insns": [3970, 3946], "data": "336", "matched_functions": 11, "tables": [[0, 0, 12, [24, 84, 88]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 92.28662]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "eb89ae7ba0da"}.

Trial zi8alpha alpha-rom-true-arms: {"label": "alpha-rom-true-arms", "score": 95.299545, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "f410dfa84ed2"}.

Trial zi8alpha alpha-rom-signature-output: {"label": "alpha-rom-signature-output", "score": 95.27167, "insns": [3950, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 24]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "f48893930bd7"}.

Trial zi8alpha alpha-rom-pointer-preincrement: {"label": "alpha-rom-pointer-preincrement", "score": 95.29447, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "08e32f805fd2"}.

Trial zi8alpha alpha-workspace-local: {"label": "alpha-workspace-local", "score": 95.42397, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "cb2c719a7fd0"}.

Trial zi8alpha alpha-workspace-typed: {"label": "alpha-workspace-typed", "score": 95.42397, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "f9c2caa46f76"}.

Trial zi8alpha alpha-workspace-final: {"label": "alpha-workspace-final", "score": 95.42397, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "a49b37f78ef7"}.

Trial zi8alpha alpha-workspace-state-reverse: {"label": "alpha-workspace-state-reverse", "score": 95.255196, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9a125b934fc5"}.

Trial zi8alpha alpha-keys-native-address: {"label": "alpha-keys-native-address", "score": 95.42397, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "48b71a2e2508"}.

Trial zi8alpha alpha-workspace-formal: {"label": "alpha-workspace-formal", "score": 95.42397, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [-4, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "cd87132fc69d"}.

Trial zi8alpha alpha-prefix-unsigned-mask: {"label": "alpha-prefix-unsigned-mask", "score": 95.46832, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "d85eb24d34ca"}.

Trial zi8alpha alpha-capacity-plain-args: {"label": "alpha-capacity-plain-args", "score": 95.315254, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [12, 24, 28]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b6178cfe4e52"}.

Trial zi8cgetc zh-native-work-formal: {"label": "zh-native-work-formal", "score": 96.27482, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "735cd3e200eb"}.

Trial zi8cgetc zh-shared-charset-failure: {"label": "zh-shared-charset-failure", "score": 95.053856, "insns": [10669, 10676], "data": "24", "matched_functions": 5, "tables": [[0, 0, 11, [-28]], [44, 0, 11, [-36]], [88, 0, 40, [-16]], [248, 0, 36, [-16]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 95.053856]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "ff12660bcd36"}.

Trial zi8cgetc zh-charset-switch-default-first: {"label": "zh-charset-switch-default-first", "score": 96.27482, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "6e4b43680225"}.

Trial zi8cgetc zh-charset-statement-order: {"label": "zh-charset-statement-order", "score": 96.27482, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "394765caeac1"}.

Trial zi8cgetc zh-scope-request-state: {"label": "zh-scope-request-state", "score": 96.24606, "insns": [10676, 10676], "data": "144", "matched_functions": 5, "tables": [[0, 0, 11, [8]], [44, 11, 11, [0]], [88, 0, 40, [4]], [248, 0, 36, [4]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc", "zi8InternalGetZH", 96.27482, 96.24606]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9fff367c6107"}.

Trial zi8alpha alpha-rom-native-result: {"label": "alpha-rom-native-result", "score": 95.46832, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "355bbb7b9097"}.

Trial zi8alpha alpha-rom-explicit-result: {"label": "alpha-rom-explicit-result", "score": 95.28206, "insns": [3958, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [36, 52, 56]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "a0f9ca11c5f8"}.

Trial zi8alpha alpha-rom-byte-tests: {"label": "alpha-rom-byte-tests", "score": 95.08439, "insns": [3962, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [20, 48, 52]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.08439]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "7d67c83eb933"}.

Trial zi8alpha alpha-result-widths: {"label": "alpha-result-widths", "score": 95.2073, "insns": [3957, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [28, 40, 44, 48]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.2073]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "794700fcbd68"}.

Trial zi8alpha alpha-rom-shared-zero: {"label": "alpha-rom-shared-zero", "score": 95.194626, "insns": [3948, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8, 12]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 95.194626]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "44b9d9f01f94"}.

Trial zi8alpha alpha-rom-body-guard: {"label": "alpha-rom-body-guard", "score": 95.46832, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "69da7de73db3"}.

Trial zi8alpha alpha-rom-true-filter: {"label": "alpha-rom-true-filter", "score": 95.46832, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b625c3c56b0f"}.

Trial zi8alpha alpha-rom-call-tail: {"label": "alpha-rom-call-tail", "score": 95.46832, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "d5665867c324"}.

The early alpha snapshot struct trials were rejected: the compiler put the aggregate at stack 0xa8, not the target 0x20. A standalone ziPtr workspace is the proved source form. Target +0x015c stores r30 at 0x20(r1), with no loads from that slot anywhere in the function. The standalone trial emits that exact store and preserves frame 0x2b0. This is the allowed assigned-but-never-read workspace snapshot, not padding.

Lever 10 evidence for the pre-existing extra dictionaryIndex initialization: target first write to slot 0x64(r1) is +0x13d0. The highlighted-output early exit at +0x0c18 branches directly to +0x3af8 when maxCandidates == 1; the +0x0c28 capacity exit does likewise. No store to slot 0x64 occurs on those paths. Finalization tests the dictionaryCounts pointer at +0x3ccc and reads the uninitialized slot at +0x3cd8 when that pointer is nonzero. The earlier safety initialization has no corresponding target assignment. The next trials may remove only this initialization under the explicit lever-10 policy; no other uninitialized local is introduced.

Several early trial reports showed a Chinese regression from a restored source with its prior trial object still built. The runner now rebuilds both owned objects before measuring. These stale cross-unit entries are not candidate results. Later reports include current objects. Failed const-elements trial conflicted with existing mutable helper parameters; restored.

Trial zi8alpha alpha-target-index-init: {"label": "alpha-target-index-init", "score": 95.48125, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 20, 24]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b6e9634e68c3"}.

Trial zi8alpha alpha-target-candidate-count: {"label": "alpha-target-candidate-count", "score": 95.46351, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "6d2d9a9e8f94"}.

Trial zi8alpha alpha-target-candidate-skip: {"label": "alpha-target-candidate-skip", "score": 95.57501, "insns": [3948, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b9ad199ae62e"}.

Trial zi8alpha alpha-target-dictionary-switch: {"label": "alpha-target-dictionary-switch", "score": 95.460976, "insns": [3954, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 20, 24]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0eacf5aceefa"}.
Alpha structural combination {"mask": [0, 0, 0, 0, 0, 0], "matched": 0, "insns": 3947, "deltas": [12, -4, 16, 16, 12, -4, 16, 16, 12, -4, 12, 12]}.
Alpha structural combination {"mask": [0, 0, 0, 0, 0, 1], "matched": 3, "insns": 3946, "deltas": [8, 0, 12, 12, 8, 0, 12, 12, 8, 0, 8, 8]}.
Alpha structural combination {"mask": [0, 0, 0, 0, 1, 0], "matched": 3, "insns": 3952, "deltas": [16, 0, 20, 20, 16, 0, 20, 20, 16, 0, 16, 16]}.
Alpha structural combination {"mask": [0, 0, 0, 0, 1, 1], "matched": 0, "insns": 3948, "deltas": [8, 4, 12, 12, 8, 4, 12, 12, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [0, 0, 0, 1, 0, 0], "matched": 0, "insns": 3948, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [0, 0, 0, 1, 0, 1], "matched": 8, "insns": 3946, "deltas": [0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0]}.

Trial zi8alpha alpha-combo-000101: {"label": "alpha-combo-000101", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "150504e0736f"}.
Alpha structural combination {"mask": [0, 0, 0, 1, 1, 0], "matched": 0, "insns": 3949, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [0, 0, 0, 1, 1, 1], "matched": 0, "insns": 3951, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-000111: {"label": "alpha-combo-000111", "score": 95.833755, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "eecbefea3fd5"}.
Alpha structural combination {"mask": [0, 0, 1, 0, 0, 0], "matched": 0, "insns": 3951, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [0, 0, 1, 0, 0, 1], "matched": 0, "insns": 3948, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [0, 0, 1, 0, 1, 0], "matched": 0, "insns": 3956, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [0, 0, 1, 0, 1, 1], "matched": 0, "insns": 3949, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [0, 0, 1, 1, 0, 0], "matched": 3, "insns": 3946, "deltas": [4, 0, 8, 8, 4, 0, 8, 8, 4, 0, 4, 4]}.

Trial zi8alpha alpha-combo-001100: {"label": "alpha-combo-001100", "score": 95.519005, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "2151dca3af70"}.
Alpha structural combination {"mask": [0, 0, 1, 1, 0, 1], "matched": 0, "insns": 3946, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-001101: {"label": "alpha-combo-001101", "score": 95.75621, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "931038802db7"}.
Alpha structural combination {"mask": [0, 0, 1, 1, 1, 0], "matched": 3, "insns": 3945, "deltas": [4, 0, 8, 8, 4, 0, 8, 8, 4, 0, 4, 4]}.

Trial zi8alpha alpha-combo-001110: {"label": "alpha-combo-001110", "score": 95.593, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "d2650d4d30bc"}.
Alpha structural combination {"mask": [0, 0, 1, 1, 1, 1], "matched": 0, "insns": 3949, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-001111: {"label": "alpha-combo-001111", "score": 95.90091, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "acd2b2209be1"}.
Alpha structural combination {"mask": [0, 1, 0, 0, 0, 0], "matched": 3, "insns": 3949, "deltas": [20, 0, 20, 20, 20, 0, 20, 20, 20, 0, 20, 20]}.
Alpha structural combination {"mask": [0, 1, 0, 0, 0, 1], "matched": 0, "insns": 3948, "deltas": [16, 4, 16, 16, 16, 4, 16, 16, 16, 4, 16, 16]}.
Alpha structural combination {"mask": [0, 1, 0, 0, 1, 0], "matched": 0, "insns": 3954, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [0, 1, 0, 0, 1, 1], "matched": 0, "insns": 3951, "deltas": [16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16]}.
Alpha structural combination {"mask": [0, 1, 0, 1, 0, 0], "matched": 0, "insns": 3951, "deltas": [20, 8, 20, 20, 20, 8, 20, 20, 20, 8, 20, 20]}.
Alpha structural combination {"mask": [0, 1, 0, 1, 0, 1], "matched": 0, "insns": 3949, "deltas": [8, 4, 8, 8, 8, 4, 8, 8, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [0, 1, 0, 1, 1, 0], "matched": 0, "insns": 3951, "deltas": [16, 8, 20, 20, 16, 8, 20, 20, 16, 8, 16, 16]}.
Alpha structural combination {"mask": [0, 1, 0, 1, 1, 1], "matched": 0, "insns": 3953, "deltas": [12, 8, 12, 12, 12, 8, 12, 12, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [0, 1, 1, 0, 0, 0], "matched": 0, "insns": 3951, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [0, 1, 1, 0, 0, 1], "matched": 0, "insns": 3948, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [0, 1, 1, 0, 1, 0], "matched": 0, "insns": 3956, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [0, 1, 1, 0, 1, 1], "matched": 0, "insns": 3949, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [0, 1, 1, 1, 0, 0], "matched": 3, "insns": 3945, "deltas": [4, 0, 8, 8, 4, 0, 8, 8, 4, 0, 4, 4]}.

Trial zi8alpha alpha-combo-011100: {"label": "alpha-combo-011100", "score": 95.563354, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "f882c2f1db9a"}.
Alpha structural combination {"mask": [0, 1, 1, 1, 0, 1], "matched": 0, "insns": 3945, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-011101: {"label": "alpha-combo-011101", "score": 95.78155, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b428e829158c"}.
Alpha structural combination {"mask": [0, 1, 1, 1, 1, 0], "matched": 3, "insns": 3945, "deltas": [4, 0, 8, 8, 4, 0, 8, 8, 4, 0, 4, 4]}.

Trial zi8alpha alpha-combo-011110: {"label": "alpha-combo-011110", "score": 95.646225, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "17ddcd60081f"}.
Alpha structural combination {"mask": [0, 1, 1, 1, 1, 1], "matched": 0, "insns": 3949, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-011111: {"label": "alpha-combo-011111", "score": 95.970604, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "475d7a0500c6"}.
Alpha structural combination {"mask": [1, 0, 0, 0, 0, 0], "matched": 0, "insns": 3952, "deltas": [24, 8, 24, 24, 20, 8, 24, 24, 20, 8, 24, 24]}.
Alpha structural combination {"mask": [1, 0, 0, 0, 0, 1], "matched": 0, "insns": 3948, "deltas": [12, 12, 12, 12, 8, 12, 12, 12, 8, 12, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 0, 0, 1, 0], "matched": 3, "insns": 3950, "deltas": [8, 0, 12, 12, 8, 0, 12, 12, 8, 0, 8, 8]}.
Alpha structural combination {"mask": [1, 0, 0, 0, 1, 1], "matched": 3, "insns": 3950, "deltas": [8, 0, 12, 12, 8, 0, 12, 12, 8, 0, 8, 8]}.
Alpha structural combination {"mask": [1, 0, 0, 1, 0, 0], "matched": 0, "insns": 3953, "deltas": [28, 12, 28, 28, 24, 12, 28, 28, 24, 12, 28, 28]}.
Alpha structural combination {"mask": [1, 0, 0, 1, 0, 1], "matched": 0, "insns": 3948, "deltas": [16, 12, 16, 16, 12, 12, 16, 16, 12, 12, 16, 16]}.
Alpha structural combination {"mask": [1, 0, 0, 1, 1, 0], "matched": 3, "insns": 3949, "deltas": [12, 0, 16, 16, 12, 0, 16, 16, 12, 0, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 0, 1, 1, 1], "matched": 3, "insns": 3948, "deltas": [12, 0, 16, 16, 12, 0, 16, 16, 12, 0, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 1, 0, 0, 0], "matched": 0, "insns": 3953, "deltas": [24, 8, 24, 24, 20, 8, 24, 24, 20, 8, 24, 24]}.
Alpha structural combination {"mask": [1, 0, 1, 0, 0, 1], "matched": 0, "insns": 3949, "deltas": [12, 12, 12, 12, 8, 12, 12, 12, 8, 12, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 1, 0, 1, 0], "matched": 3, "insns": 3951, "deltas": [12, 0, 16, 16, 12, 0, 16, 16, 12, 0, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 1, 0, 1, 1], "matched": 3, "insns": 3951, "deltas": [12, 0, 16, 16, 12, 0, 16, 16, 12, 0, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 1, 1, 0, 0], "matched": 0, "insns": 3949, "deltas": [20, 4, 20, 20, 16, 4, 20, 20, 16, 4, 20, 20]}.
Alpha structural combination {"mask": [1, 0, 1, 1, 0, 1], "matched": 0, "insns": 3946, "deltas": [12, 8, 12, 12, 8, 8, 12, 12, 8, 8, 12, 12]}.
Alpha structural combination {"mask": [1, 0, 1, 1, 1, 0], "matched": 3, "insns": 3949, "deltas": [16, 0, 20, 20, 16, 0, 20, 20, 16, 0, 16, 16]}.
Alpha structural combination {"mask": [1, 0, 1, 1, 1, 1], "matched": 3, "insns": 3950, "deltas": [16, 0, 20, 20, 16, 0, 20, 20, 16, 0, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 0, 0, 0, 0], "matched": 0, "insns": 3954, "deltas": [28, 12, 28, 28, 24, 12, 28, 28, 24, 12, 28, 28]}.
Alpha structural combination {"mask": [1, 1, 0, 0, 0, 1], "matched": 0, "insns": 3950, "deltas": [16, 16, 16, 16, 12, 16, 16, 16, 12, 16, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 0, 0, 1, 0], "matched": 0, "insns": 3950, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [1, 1, 0, 0, 1, 1], "matched": 0, "insns": 3951, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [1, 1, 0, 1, 0, 0], "matched": 0, "insns": 3955, "deltas": [32, 16, 32, 32, 28, 16, 32, 32, 28, 16, 32, 32]}.
Alpha structural combination {"mask": [1, 1, 0, 1, 0, 1], "matched": 0, "insns": 3949, "deltas": [20, 16, 20, 20, 16, 16, 20, 20, 16, 16, 20, 20]}.
Alpha structural combination {"mask": [1, 1, 0, 1, 1, 0], "matched": 0, "insns": 3949, "deltas": [16, 4, 20, 20, 16, 4, 20, 20, 16, 4, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 0, 1, 1, 1], "matched": 0, "insns": 3949, "deltas": [16, 4, 20, 20, 16, 4, 20, 20, 16, 4, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 1, 0, 0, 0], "matched": 0, "insns": 3954, "deltas": [28, 12, 28, 28, 24, 12, 28, 28, 24, 12, 28, 28]}.
Alpha structural combination {"mask": [1, 1, 1, 0, 0, 1], "matched": 0, "insns": 3950, "deltas": [16, 16, 16, 16, 12, 16, 16, 16, 12, 16, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 1, 0, 1, 0], "matched": 0, "insns": 3953, "deltas": [16, 4, 20, 20, 16, 4, 20, 20, 16, 4, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 1, 0, 1, 1], "matched": 0, "insns": 3952, "deltas": [16, 4, 20, 20, 16, 4, 20, 20, 16, 4, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 1, 1, 0, 0], "matched": 0, "insns": 3950, "deltas": [24, 8, 24, 24, 20, 8, 24, 24, 20, 8, 24, 24]}.
Alpha structural combination {"mask": [1, 1, 1, 1, 0, 1], "matched": 0, "insns": 3947, "deltas": [16, 12, 16, 16, 12, 12, 16, 16, 12, 12, 16, 16]}.
Alpha structural combination {"mask": [1, 1, 1, 1, 1, 0], "matched": 0, "insns": 3951, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [1, 1, 1, 1, 1, 1], "matched": 0, "insns": 3951, "deltas": [20, 4, 24, 24, 20, 4, 24, 24, 20, 4, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 0, 0, 0, 0], "matched": 0, "insns": 3951, "deltas": [20, 12, 20, 20, 16, 12, 20, 20, 16, 12, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 0, 0, 0, 1], "matched": 0, "insns": 3949, "deltas": [20, 16, 20, 20, 16, 16, 20, 20, 16, 16, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 0, 0, 1, 0], "matched": 0, "insns": 3949, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-200010: {"label": "alpha-combo-200010", "score": 95.26609, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "c3ca4b51b85e"}.
Alpha structural combination {"mask": [2, 0, 0, 0, 1, 1], "matched": 0, "insns": 3949, "deltas": [4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4]}.

Trial zi8alpha alpha-combo-200011: {"label": "alpha-combo-200011", "score": 95.61708, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "325c7ef77435"}.
Alpha structural combination {"mask": [2, 0, 0, 1, 0, 0], "matched": 0, "insns": 3951, "deltas": [24, 16, 24, 24, 20, 16, 24, 24, 20, 16, 24, 24]}.
Alpha structural combination {"mask": [2, 0, 0, 1, 0, 1], "matched": 0, "insns": 3949, "deltas": [24, 16, 24, 24, 20, 16, 24, 24, 20, 16, 24, 24]}.
Alpha structural combination {"mask": [2, 0, 0, 1, 1, 0], "matched": 0, "insns": 3948, "deltas": [8, 4, 12, 12, 8, 4, 12, 12, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [2, 0, 0, 1, 1, 1], "matched": 0, "insns": 3947, "deltas": [8, 4, 12, 12, 8, 4, 12, 12, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [2, 0, 1, 0, 0, 0], "matched": 0, "insns": 3952, "deltas": [20, 12, 20, 20, 16, 12, 20, 20, 16, 12, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 1, 0, 0, 1], "matched": 0, "insns": 3950, "deltas": [20, 16, 20, 20, 16, 16, 20, 20, 16, 16, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 1, 0, 1, 0], "matched": 0, "insns": 3950, "deltas": [8, 4, 12, 12, 8, 4, 12, 12, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [2, 0, 1, 0, 1, 1], "matched": 0, "insns": 3950, "deltas": [8, 4, 12, 12, 8, 4, 12, 12, 8, 4, 8, 8]}.
Alpha structural combination {"mask": [2, 0, 1, 1, 0, 0], "matched": 0, "insns": 3947, "deltas": [16, 8, 16, 16, 12, 8, 16, 16, 12, 8, 16, 16]}.
Alpha structural combination {"mask": [2, 0, 1, 1, 0, 1], "matched": 0, "insns": 3947, "deltas": [20, 12, 20, 20, 16, 12, 20, 20, 16, 12, 20, 20]}.
Alpha structural combination {"mask": [2, 0, 1, 1, 1, 0], "matched": 0, "insns": 3948, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [2, 0, 1, 1, 1, 1], "matched": 0, "insns": 3949, "deltas": [12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 12, 12]}.
Alpha structural combination {"mask": [2, 1, 0, 0, 0, 0], "matched": 0, "insns": 3953, "deltas": [24, 16, 24, 24, 20, 16, 24, 24, 20, 16, 24, 24]}.
Alpha structural combination {"mask": [2, 1, 0, 0, 0, 1], "matched": 0, "insns": 3951, "deltas": [24, 20, 24, 24, 20, 20, 24, 24, 20, 20, 24, 24]}.
Alpha structural combination {"mask": [2, 1, 0, 0, 1, 0], "matched": 0, "insns": 3949, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [2, 1, 0, 0, 1, 1], "matched": 0, "insns": 3950, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [2, 1, 0, 1, 0, 0], "matched": 0, "insns": 3953, "deltas": [28, 20, 28, 28, 24, 20, 28, 28, 24, 20, 28, 28]}.
Alpha structural combination {"mask": [2, 1, 0, 1, 0, 1], "matched": 0, "insns": 3950, "deltas": [28, 20, 28, 28, 24, 20, 28, 28, 24, 20, 28, 28]}.
Alpha structural combination {"mask": [2, 1, 0, 1, 1, 0], "matched": 0, "insns": 3948, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [2, 1, 0, 1, 1, 1], "matched": 0, "insns": 3948, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [2, 1, 1, 0, 0, 0], "matched": 0, "insns": 3953, "deltas": [24, 16, 24, 24, 20, 16, 24, 24, 20, 16, 24, 24]}.
Alpha structural combination {"mask": [2, 1, 1, 0, 0, 1], "matched": 0, "insns": 3951, "deltas": [24, 20, 24, 24, 20, 20, 24, 24, 20, 20, 24, 24]}.
Alpha structural combination {"mask": [2, 1, 1, 0, 1, 0], "matched": 0, "insns": 3952, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [2, 1, 1, 0, 1, 1], "matched": 0, "insns": 3951, "deltas": [12, 8, 16, 16, 12, 8, 16, 16, 12, 8, 12, 12]}.
Alpha structural combination {"mask": [2, 1, 1, 1, 0, 0], "matched": 0, "insns": 3948, "deltas": [20, 12, 20, 20, 16, 12, 20, 20, 16, 12, 20, 20]}.
Alpha structural combination {"mask": [2, 1, 1, 1, 0, 1], "matched": 0, "insns": 3948, "deltas": [24, 16, 24, 24, 20, 16, 24, 24, 20, 16, 24, 24]}.
Alpha structural combination {"mask": [2, 1, 1, 1, 1, 0], "matched": 0, "insns": 3950, "deltas": [16, 8, 20, 20, 16, 8, 20, 20, 16, 8, 16, 16]}.
Alpha structural combination {"mask": [2, 1, 1, 1, 1, 1], "matched": 0, "insns": 3950, "deltas": [16, 8, 20, 20, 16, 8, 20, 20, 16, 8, 16, 16]}.
Alpha structural combination {"mask": [3, 0, 0, 0, 0, 0], "matched": 0, "insns": 3955, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 0, 0, 0, 1], "matched": 0, "insns": 3955, "deltas": [28, 24, 28, 32, 28, 24, 28, 32, 28, 24, 28, 28]}.
Alpha structural combination {"mask": [3, 0, 0, 0, 1, 0], "matched": 0, "insns": 3956, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [3, 0, 0, 0, 1, 1], "matched": 0, "insns": 3956, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 0, 0, 1, 0, 0], "matched": 0, "insns": 3954, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 0, 1, 0, 1], "matched": 0, "insns": 3953, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 0, 1, 1, 0], "matched": 0, "insns": 3955, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [3, 0, 0, 1, 1, 1], "matched": 0, "insns": 3953, "deltas": [8, 8, 12, 12, 8, 8, 12, 12, 8, 8, 8, 8]}.
Alpha structural combination {"mask": [3, 0, 1, 0, 0, 0], "matched": 0, "insns": 3953, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 1, 0, 0, 1], "matched": 0, "insns": 3955, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 0, 1, 0, 1, 0], "matched": 0, "insns": 3954, "deltas": [12, 12, 16, 16, 12, 12, 16, 16, 12, 12, 12, 12]}.
Alpha structural combination {"mask": [3, 0, 1, 0, 1, 1], "matched": 0, "insns": 3955, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 0, 1, 1, 0, 0], "matched": 0, "insns": 3955, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 1, 1, 0, 1], "matched": 0, "insns": 3951, "deltas": [20, 16, 20, 24, 20, 16, 20, 24, 20, 16, 20, 20]}.
Alpha structural combination {"mask": [3, 0, 1, 1, 1, 0], "matched": 0, "insns": 3955, "deltas": [12, 12, 16, 16, 12, 12, 16, 16, 12, 12, 12, 12]}.
Alpha structural combination {"mask": [3, 0, 1, 1, 1, 1], "matched": 0, "insns": 3952, "deltas": [12, 12, 16, 16, 12, 12, 16, 16, 12, 12, 12, 12]}.
Alpha structural combination {"mask": [3, 1, 0, 0, 0, 0], "matched": 0, "insns": 3956, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 0, 0, 0, 1], "matched": 0, "insns": 3956, "deltas": [32, 28, 32, 36, 32, 28, 32, 36, 32, 28, 32, 32]}.
Alpha structural combination {"mask": [3, 1, 0, 0, 1, 0], "matched": 0, "insns": 3959, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 1, 0, 0, 1, 1], "matched": 0, "insns": 3958, "deltas": [24, 24, 28, 28, 24, 24, 28, 28, 24, 24, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 0, 1, 0, 0], "matched": 0, "insns": 3955, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 0, 1, 0, 1], "matched": 0, "insns": 3954, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 0, 1, 1, 0], "matched": 0, "insns": 3956, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 1, 0, 1, 1, 1], "matched": 0, "insns": 3954, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 1, 1, 0, 0, 0], "matched": 0, "insns": 3954, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 1, 0, 0, 1], "matched": 0, "insns": 3955, "deltas": [28, 24, 28, 32, 28, 24, 28, 32, 28, 24, 28, 28]}.
Alpha structural combination {"mask": [3, 1, 1, 0, 1, 0], "matched": 0, "insns": 3955, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 1, 1, 0, 1, 1], "matched": 0, "insns": 3956, "deltas": [20, 20, 24, 24, 20, 20, 24, 24, 20, 20, 20, 20]}.
Alpha structural combination {"mask": [3, 1, 1, 1, 0, 0], "matched": 0, "insns": 3955, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 1, 1, 0, 1], "matched": 0, "insns": 3952, "deltas": [24, 20, 24, 28, 24, 20, 24, 28, 24, 20, 24, 24]}.
Alpha structural combination {"mask": [3, 1, 1, 1, 1, 0], "matched": 0, "insns": 3956, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.
Alpha structural combination {"mask": [3, 1, 1, 1, 1, 1], "matched": 0, "insns": 3953, "deltas": [16, 16, 20, 20, 16, 16, 20, 20, 16, 16, 16, 16]}.

Trial zi8alpha alpha-eight-uwd-for: {"label": "alpha-eight-uwd-for", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "bba4957d7c30"}.

Trial zi8alpha alpha-eight-uwd-test: {"label": "alpha-eight-uwd-test", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "6b8b3a8d18e6"}.

Trial zi8alpha alpha-eight-uwd-mask: {"label": "alpha-eight-uwd-mask", "score": 95.65864, "insns": [3948, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "a4dc0d96d394"}.

Trial zi8alpha alpha-eight-rom-cursor: {"label": "alpha-eight-rom-cursor", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "997b73bede85"}.

Trial zi8alpha alpha-eight-rom-pointer: {"label": "alpha-eight-rom-pointer", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "b7ab8cf9c760"}.

Trial zi8alpha alpha-eight-signature-void: {"label": "alpha-eight-signature-void", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "81d12ad5b9f8"}.

Trial zi8alpha alpha-eight-clean-skip: {"label": "alpha-eight-clean-skip", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0a02b3a9d6fe"}.

Trial zi8alpha alpha-eight-direct-0: {"label": "alpha-eight-direct-0", "score": 95.509125, "insns": [3951, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [12, 20, 24]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "361065d202bc"}.

Trial zi8alpha alpha-eight-direct-1: {"label": "alpha-eight-direct-1", "score": 95.54207, "insns": [3950, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 16, 20]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0a7ad6c9adba"}.

Trial zi8alpha alpha-eight-direct-2: {"label": "alpha-eight-direct-2", "score": 95.56234, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "54725a261ea3"}.

Trial zi8alpha alpha-eight-direct-3: {"label": "alpha-eight-direct-3", "score": 95.60036, "insns": [3950, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12, 16]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "41fd24601523"}.

Trial zi8alpha alpha-eight-direct-4: {"label": "alpha-eight-direct-4", "score": 95.61936, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "e42d56d83d3c"}.

Trial zi8alpha alpha-eight-direct-5: {"label": "alpha-eight-direct-5", "score": 95.614296, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "280a8c0ddd9a"}.

Trial zi8alpha alpha-eight-uwd-condition: {"label": "alpha-eight-uwd-condition", "score": 95.363914, "insns": [3944, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 6, 12, [-4, 0, 4, 24]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "1f3424f15af3"}.

Trial zi8alpha alpha-eight-uwd-do: {"label": "alpha-eight-uwd-do", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9bc2c795f346"}.

Trial zi8alpha alpha-eight-mode-first: {"label": "alpha-eight-mode-first", "score": 95.698685, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "d839ee510c75"}.

Trial zi8alpha alpha-eight-rom-plain-count: {"label": "alpha-eight-rom-plain-count", "score": 95.68905, "insns": [3944, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 5, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9d2c4c48b646"}.

Trial zi8alpha alpha-eight-rom-plain-capacity: {"label": "alpha-eight-rom-plain-capacity", "score": 95.70806, "insns": [3944, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 5, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "37a1f72cf123"}.

Trial zi8alpha alpha-eight-rom-typed-count: {"label": "alpha-eight-rom-typed-count", "score": 95.68905, "insns": [3944, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 5, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "628505c892e5"}.

Trial zi8alpha alpha-eight-signature-length: {"label": "alpha-eight-signature-length", "score": 95.61683, "insns": [3949, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "e316a809dd92"}.

Trial zi8alpha alpha-eight-mark-secondary-first: {"label": "alpha-eight-mark-secondary-first", "score": 95.726555, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "8b0d4189100d"}.

Trial zi8alpha alpha-eight-punctuation-zero-first: {"label": "alpha-eight-punctuation-zero-first", "score": 95.652306, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 7, 12, [-4, 0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "49fab8aea1ff"}.

Trial zi8alpha alpha-eight-uwd-plain-count: {"label": "alpha-eight-uwd-plain-count", "score": 95.63837, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9214c2ee564d"}.

Trial zi8alpha alpha-eight-uwd-plain-capacity: {"label": "alpha-eight-uwd-plain-capacity", "score": 95.63837, "insns": [3947, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 3, 12, [0, 4, 8]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "16f7c2407467"}.

Trial zi8alpha alpha-eight-uwd-plain-status: {"label": "alpha-eight-uwd-plain-status", "score": 95.72833, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 8, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "2f2409d65b49"}.

Trial zi8alpha alpha-seven-uwd-count: {"label": "alpha-seven-uwd-count", "score": 95.557274, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 9, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "74a51dbbfd5a"}.

Trial zi8alpha alpha-seven-uwd-capacity: {"label": "alpha-seven-uwd-capacity", "score": 95.557274, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 9, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "cbaab67406ac"}.

Trial zi8alpha alpha-seven-uwd-status: {"label": "alpha-seven-uwd-status", "score": 95.652306, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 7, 12, [-4, 0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0ac38054bbb0"}.

Trial zi8alpha alpha-seven-uwd-call-count: {"label": "alpha-seven-uwd-call-count", "score": 95.652306, "insns": [3945, 3946], "data": "408", "matched_functions": 11, "tables": [[0, 7, 12, [-4, 0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9ad911131a9b"}.

Trial zi8alpha alpha-seven-uwd-byte-result: {"label": "alpha-seven-uwd-byte-result", "score": 93.258995, "insns": [3949, 3946], "data": "336", "matched_functions": 11, "tables": [[0, 0, 12, [4]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 93.258995]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "9e228141d82e"}.

Trial zi8alpha alpha-seven-uwd-int-result: {"label": "alpha-seven-uwd-int-result", "score": 93.01267, "insns": [3951, 3946], "data": "336", "matched_functions": 11, "tables": [[0, 0, 12, [8, 12]]], "regressions": [["main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha", "Zi8AlphaGetCandidates", 95.23011, 93.01267]], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "8d333acbfbdc"}.

Trial zi8alpha alpha-nine-oem-1: {"label": "alpha-nine-oem-1", "score": 95.56234, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 9, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "28779c6bb6e2"}.

Trial zi8alpha alpha-nine-oem-2: {"label": "alpha-nine-oem-2", "score": 95.55981, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 9, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "e1f7beb25be2"}.

Trial zi8alpha alpha-nine-oem-3: {"label": "alpha-nine-oem-3", "score": 95.648506, "insns": [3946, 3946], "data": "564", "matched_functions": 11, "tables": [[0, 12, 12, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "388c5b35afd9"}.

Trial zi8alpha alpha-nine-oem-4: {"label": "alpha-nine-oem-4", "score": 95.56234, "insns": [3946, 3946], "data": "516", "matched_functions": 11, "tables": [[0, 9, 12, [0, 4]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "7b8acde0dfc0"}.

Trial zi8alpha alpha-nine-oem-5: {"label": "alpha-nine-oem-5", "score": 95.65737, "insns": [3946, 3946], "data": "564", "matched_functions": 11, "tables": [[0, 12, 12, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "63498a8fa6c1"}.

Trial zi8alpha alpha-nine-oem-6: {"label": "alpha-nine-oem-6", "score": 95.66498, "insns": [3946, 3946], "data": "564", "matched_functions": 11, "tables": [[0, 12, 12, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "0e3d499e26a8"}.

Trial zi8alpha alpha-nine-oem-7: {"label": "alpha-nine-oem-7", "score": 95.64597, "insns": [3946, 3946], "data": "564", "matched_functions": 11, "tables": [[0, 12, 12, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "007a7b31b210"}.

Trial zi8alpha alpha-candidate: {"label": "alpha-candidate", "score": 95.648506, "insns": [3946, 3946], "data": "564", "matched_functions": 11, "tables": [[0, 12, 12, [0]]], "regressions": [], "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "sha256": "388c5b35afd9"}.

## Accepted alpha data result

Accepted alpha-nine-oem-3, source SHA256 prefix 388c5b35afd9. The live final object has 3946/3946 instructions and all 12 table entries at the target offsets. Matched data rises 516/564 -> 564/564, while instruction-exact functions stay 11/12 and code stays 5880/21664. Engine objdiff rises 95.23011 -> 95.648506%; unit fuzzy rises 96.52474 -> 96.82958%. No fuzzy gain is counted as an exact function.

The retained change adds the proved standalone workspace snapshot, emits candidate skipping before ordinary output, combines the two increment-and-limit tests, writes the punctuation terminator before its second character, and lets the declared byte/halfword parameters narrow the UWD/OEM arguments. No helper declaration or shared header changes. The original early dictionaryIndex initialization remains; no uninitialized-value trial is retained.

Punctuation-store alias review: punctuationCursor is initialized only from the local punctuationBuffer array, either its start or element 1, and advances within it. wordCursor points to the distinct local candidateWord array or the caller output, with the existing prefix/suffix cursor adjustments. Swapping its terminator store with the punctuation read preserves these paths. Removing count & 0xff and capacity & 0xffff preserves their low bits because the corresponding formal parameters are ziU8 and ziU16. The swapped skip branch and combined increments preserve the same conditions, values and exits.

Alpha target/final case offsets: 0/default 0x2040; 1/5 0x18d0; 2/6 0x1db4; 3/7 0x1e0c; 4/8 0x1ea4; 9 0x18c8; 10 0x1efc; 11 0x1f38. Every first basic-block length and every known case span also matches. An independent ELF comparison proves all 48 .data payload bytes and all 12 symbol-relative relocations identical, not just the displayed offsets. Target and source both contain exactly one access to stack 0x20: +0x15c stw r30,0x20(r1), with no load.

Chinese result: restore every source trial. Matched data 144/536, code 4168/47816, exact functions 5/8, engine 96.27482%, all unchanged. Cases at target offsets 11/98 -> 11/98. The already matching 11-entry table is .data+0x2c. Tables at +0, +0x58 and +0xf8 remain shifted +8, +4 and +4 bytes. The if-chain trial aligned the 76 phonetic entries but regressed the engine and exception metadata; it is rejected. Both owned engine functions have more than three distinct compiled source attempts. Other functions were not edited in this data round.

## Final validation

Full non-quick gate over both units: GATE PASS. Clean 43U build, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, identical empty pools, zero regressions, zero new forbidden patterns, zero readability warnings. The gate used the nearest stored baseline 631f31b7, so a separate comparison against this worktree's fresh f598e410 baseline checked all 1027 units and every function percentage. It found zero regressions; alpha data and alpha fuzzy are the only changed unit measures. All 11 alpha and all 5 Chinese previously exact functions independently retain equal sizes and ctxdiff-equivalent zero instruction differences. The main alpha engine remains non-exact, ctxdiff 3227 differences with equal 3946 instruction counts.

Regenerated live progress/report and explicit build/43U/ok pass. jt_layout.py was checked against baseline and final objects, both original table ranges, all 110 entries, and identical-object comparisons. Its numeric block lengths stop at control-flow leaders; the optional span column stops at the next case/default entry, with ? for the final span that cannot be inferred. It does not claim register or complete instruction identity.

Only zi8alpha.c, jt_layout.py and this new attempts log are retained. Existing a4h, a4m, h4 and u6 attempts logs remain untracked. No push, PR, merge, rebase, other-worktree edit or upstream action was performed. Scratch candidates and detailed measurements remain in build/sz2.

Final gate excerpt:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.6547 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] objdiff: code 5880/21664 data 564/564 functions 11/12 fuzzy 96.8296 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] instruction-exact functions: 11/12
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
