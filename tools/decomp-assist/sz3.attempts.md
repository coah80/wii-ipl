# sz3 ATERM data layout round

Owned worktree data-d2, branch agent/w1004/sz3, starting commit f598e41020af666c8e84c47ff5204b5b94b59712. The owned unit is ATERM; changes also include its proven object-boundary metadata and a layout diagnostic. Existing a9h, a9m, a9x and u3 attempts logs remain untracked.

Read AGENTS.md, common.md, levers.md, h2/h2b/ult15 protocol attempts and orch/g3-progress:g3.attempts.md. Prior isolated time helpers, short/long TLV constructors, response/session reorderings, MD5 helpers and null-guard-only trial will not be repeated. This round accepts a data gain with no per-function fuzzy, exact, code or data regression.

Initial full ninja and progress report pass. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Pool identical, 0 strings each. ATERM code12200/19204, data18584/18864, objdiff-exact20/26, fuzzy97.74089. Protocol89.77287, source958/target951 instructions.

No jt_layout.py existed. Added one using the existing ELF relocation reader. It resolves each entry symbol plus addend into a function-relative case offset even when function sizes differ. Spans run to the next distinct case entry, or function end for the final shared loop/epilogue. State dispatcher directly indexes0..10 after unsigned bounds check, so entry index is the case value.

ATERMRunConfigProtocol: target 951 insns, source 958 insns
target table @2631 +0xac; source table @2872 +0xac
Offsets are function-relative; spans end at the next distinct case entry or function end.
case   target  source   delta  target span  source span  target relocation -> source relocation
   0   0e8c    0ea8     +28           20           20  ATERMRunConfigProtocol+0xe8c -> ATERMRunConfigProtocol+0xea8
   1   00f0    0100     +16           35           35  ATERMRunConfigProtocol+0xf0 -> ATERMRunConfigProtocol+0x100
   2   017c    018c     +16           31           31  ATERMRunConfigProtocol+0x17c -> ATERMRunConfigProtocol+0x18c
   3   01f8    0208     +16           33           34  ATERMRunConfigProtocol+0x1f8 -> ATERMRunConfigProtocol+0x208
   4   027c    0290     +20           72           71  ATERMRunConfigProtocol+0x27c -> ATERMRunConfigProtocol+0x290
   5   039c    03ac     +16          156          153  ATERMRunConfigProtocol+0x39c -> ATERMRunConfigProtocol+0x3ac
   6   060c    0610      +4          259          262  ATERMRunConfigProtocol+0x60c -> ATERMRunConfigProtocol+0x610
   7   0a18    0a28     +16           63           64  ATERMRunConfigProtocol+0xa18 -> ATERMRunConfigProtocol+0xa28
   8   0b14    0b28     +20          127          129  ATERMRunConfigProtocol+0xb14 -> ATERMRunConfigProtocol+0xb28
   9   0d10    0d2c     +28           75           75  ATERMRunConfigProtocol+0xd10 -> ATERMRunConfigProtocol+0xd2c
  10   0e3c    0e58     +28           20           20  ATERMRunConfigProtocol+0xe3c -> ATERMRunConfigProtocol+0xe58
Cases at target offset: 0/11

The target orders states1..10 followed by the shared state0/default loop tail. The source has the same order. Physical span differences source minus target: entry+4, case3+1, case4-1, case5-3, case6+3, case7+1, case8+2. Case1/2/9/10/tail agree. No blind case permutation is justified.

Lever10 proof freshly checked in target object: function at.text+0x170c, size0xedc. At0x1ed0 compare TLV pointer with end; empty edge0x1ed8 sets r16=0 then branches0x1efc. Nonempty path calls SONtoHs(type), stores r0 to0x120(r1) at0x1ef0, then calls SONtoHs(length). At0x1efc target unconditionally lwz r0,0x120(r1), then cmpwi r0,0x101. The only store to0x120(r1) in the entire target function is0x1ef0. Empty edge therefore reads an unassigned local. There is no null-value guard. Restoring this exact path is allowed by the explicit lever10 exception, but the previously tried isolated guard removal regresses fuzzy and is not a standalone candidate.


- t01 | Keep the received packet view alive across protocol states, as target r15 does | {"sha256": "f3a56406f315", "insns": [957, 951], "score": 89.20294, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.20294]], "case_deltas": [6, 5, 5, 5, 6, 5, 2, 4, 5, 6, 6], "span_deltas": [0, 0, 0, 1, -1, -3, 2, 1, 1, 0, 0], "cases_matched": 0}

- t02 | Persistent packet view with default checksum payload and the assembly-proven TLV type guard | {"sha256": "b28297d1bb8d", "insns": [961, 951], "score": 88.8654, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.8654]], "case_deltas": [10, 4, 5, 5, 7, 6, 4, 5, 7, 9, 10], "span_deltas": [0, 1, 0, 2, -1, -2, 1, 2, 2, 1, 0], "cases_matched": 0}

- t03 | Persistent packet view and proven TLV guard with inverted checksum selection | {"sha256": "2e6b8e8d3fea", "insns": [955, 951], "score": 89.31546, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.31546]], "case_deltas": [4, 5, 5, 5, 6, 5, 2, 2, 3, 4, 4], "span_deltas": [0, 0, 0, 1, -1, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t04 | Use the authentication key within the existing response view, at the same proven BSS address | {"sha256": "66d286762936", "insns": [950, 951], "score": 90.11356, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [-1, 0, 0, 0, 1, 0, -3, -3, -2, -1, -1], "span_deltas": [0, 0, 0, 1, -1, -3, 0, 1, 1, 0, 0], "cases_matched": 4}

- t05 | Restore the peer-address argument explicitly prepared in target r4 at text+0x19d0 | {"sha256": "703568787de3", "insns": [951, 951], "score": 90.586754, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [0, 0, 0, 0, 1, 1, -2, -2, -1, 0, 0], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 6}

- t06 | Read TLV options from their owning response buffer while deriving the session key from the header view | {"sha256": "74a679a65f6a", "insns": [959, 951], "score": 88.644585, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.644585]], "case_deltas": [8, 4, 5, 5, 7, 7, 5, 4, 6, 7, 8], "span_deltas": [0, 1, 0, 2, 0, -2, -1, 2, 1, 1, 0], "cases_matched": 0}

- t07 | Use the persistent packet view at all send, receive and decoder call boundaries, plus the proven peer-address argument | {"sha256": "99b61d19d3b3", "insns": [960, 951], "score": 88.00631, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.00631]], "case_deltas": [9, 6, 6, 6, 7, 8, 5, 6, 8, 9, 9], "span_deltas": [0, 0, 0, 1, 1, -3, 1, 2, 1, 0, 0], "cases_matched": 0}

- t08 | Keep the association request view beside the packet and response views throughout the state machine | {"sha256": "9ae875ebe740", "insns": [958, 951], "score": 88.46162, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.46162]], "case_deltas": [7, 6, 6, 6, 7, 7, 4, 5, 6, 7, 7], "span_deltas": [0, 0, 0, 1, 0, -3, 1, 1, 1, 0, 0], "cases_matched": 0}

Boundary hypothesis: the exported configuration is0xe8 bytes, proven by ATERMi_ApConfigStart memset and ATERMi_ApConfigReturnConfig memcpy. Protocol request identity is16 bytes atBSS+0xc88, packet buffer0x800 at+0xc98, response header8 at+0x1498, followed by existing response options at+0x14a0. Try independent globals with exactly these byte extents. No config metadata edited for the trial; this tests whether the spurious long-lived configuration base caused entry spills. All new fields correspond to existing bytes, no new storage.

- t09 | Split the configuration export from the request identity, packet buffer and decoded header at proven field boundaries | {"sha256": "16639a49d29e", "insns": [948, 951], "score": 91.210304, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [-3, 1, 1, 1, 1, 1, -3, -2, -3, -2, -3], "span_deltas": [0, 0, 0, 0, 0, -4, 1, -1, 1, -1, 0], "cases_matched": 0}

- t10 | Keep the decoded header with its existing response storage, and initialize request, packet and response views in address order | {"sha256": "b6e5c2c6d859", "insns": [952, 951], "score": 88.58885, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.58885], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [1, -1, -1, -1, 0, 0, -3, 2, 2, 1, 1], "span_deltas": [0, 0, 0, 1, 0, -3, 5, 0, -1, 0, 0], "cases_matched": 2}

- t11 | Name the real session challenge/digest fields and read the reply digest from its owning buffer | {"sha256": "4815a522c7e3", "insns": [961, 951], "score": 88.78233, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.78233]], "case_deltas": [10, 4, 5, 5, 7, 7, 5, 5, 8, 9, 10], "span_deltas": [0, 1, 0, 2, 0, -2, 0, 3, 1, 1, 0], "cases_matched": 0}

- t12 | Initialize state before all protocol views and scalar state in the target semantic order | {"sha256": "d14871a1183d", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t13 | Assembly-derived global response accessor boundary on state-first setup | {"sha256": "38b95277ff81", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t14 | Assembly-derived global packet accessor boundary on state-first setup | {"sha256": "3d28eabeffbc", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t15 | Assembly-derived global session key accessor boundary on state-first setup | {"sha256": "335cc5e15fce", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t16 | Materialize the session-key address at each protocol use instead of keeping a function-local key view | {"sha256": "8210872288e2", "insns": [956, 951], "score": 89.26709, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.26709]], "case_deltas": [5, 4, 4, 4, 5, 5, 2, 2, 3, 4, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 1, 0], "cases_matched": 0}

- t17 | Materialize the response header view at each use instead of keeping a function-local response view | {"sha256": "943c7d56ff17", "insns": [958, 951], "score": 88.291275, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.291275]], "case_deltas": [7, 9, 9, 9, 10, 10, 7, 7, 7, 8, 7], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 0, 1, -1, 0], "cases_matched": 0}

- t18 | Confine the fixed reciprocal constant to its millisecond conversion expressions with the new packet lifetime | {"sha256": "809b4b82aa58", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t19 | Combined short and long option helper lifetimes with the proven guard, packet view and call signature | {"sha256": "303524870eb6", "insns": [957, 951], "score": 89.68875, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.68875]], "case_deltas": [6, 5, 5, 5, 6, 6, 4, 4, 5, 6, 6], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 1, 1, 0, 0], "cases_matched": 0}

- t20 | Use a u16 protocol port shared by socket binding and all outgoing addresses | {"sha256": "2f799bd759f4", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t21 | Use a u32 protocol port shared by socket binding and all outgoing addresses | {"sha256": "b442a4357a7e", "insns": [956, 951], "score": 89.78864, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [5, 5, 5, 5, 6, 6, 3, 3, 4, 5, 5], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 0}

- t22 | Preserve each generated message length across SOHtoNs and NCDGetLinkStatus, matching target r16 lifetime | {"sha256": "32d75406e3ee", "insns": [959, 951], "score": 90.268135, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [8, 5, 5, 5, 6, 6, 4, 4, 6, 7, 8], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 2, 1, 1, 0], "cases_matched": 0}

- t23 | Separate packet and response-header storage from the exported configuration and association request without moving any bytes | {"sha256": "a186b94d3498", "insns": [953, 951], "score": 91.628815, "exact": 20, "code": "12200", "data": "10424", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10424"]], "case_deltas": [2, 1, 1, 1, 1, 2, -1, 0, 1, 2, 2], "span_deltas": [0, 0, 0, 0, 1, -3, 1, 1, 1, 0, 0], "cases_matched": 1}

- t24 | Use one typed packet/header storage view without splitting or moving the existing globals | {"sha256": "7b57a5016dd8", "insns": [964, 951], "score": 88.997894, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.997894]], "case_deltas": [13, 7, 7, 7, 8, 9, 7, 8, 11, 12, 13], "span_deltas": [0, 0, 0, 1, 1, -2, 1, 3, 1, 1, 0], "cases_matched": 0}

- t25 | Model packet/header storage as a named nested record inside the unchanged configuration global | {"sha256": "e1d4c52a5dc0", "insns": [959, 951], "score": 90.268135, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [8, 5, 5, 5, 6, 6, 4, 4, 6, 7, 8], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 2, 1, 1, 0], "cases_matched": 0}

- t26 | Declare the real request-options pointer before the protocol so its response buffer remains in original BSS order | {"sha256": "2ee61314915d", "insns": [951, 951], "score": 90.586754, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [0, 0, 0, 0, 1, 1, -2, -2, -1, 0, 0], "span_deltas": [0, 0, 0, 1, 0, -3, 0, 1, 1, 0, 0], "cases_matched": 6}

- t27 | Use the same typed session authentication view for the received challenge, computed digest and AES key | {"sha256": "17453c9087be", "insns": [967, 951], "score": 88.59937, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.59937]], "case_deltas": [16, 5, 5, 5, 6, 6, 4, 12, 14, 15, 16], "span_deltas": [0, 0, 0, 1, 0, -2, 8, 2, 1, 1, 0], "cases_matched": 0}

- t28 | Represent the exported configuration, association identity, packet, decoded payload and session workspace as their actual nonoverlapping regions | {"sha256": "ea5c915367af", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t29 | Read each MD5 state word directly for every encoded byte, without the loop-local cached word, on t28 | {"sha256": "438df3eeef06", "insns": [955, 951], "score": 89.83701, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t30 | Read each MD5 state word directly for every encoded byte, without the loop-local cached word, on t22 | {"sha256": "d3ea0a97b76d", "insns": [971, 951], "score": 89.55836, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.55836]], "case_deltas": [20, 5, 5, 5, 6, 6, 4, 16, 18, 19, 20], "span_deltas": [0, 0, 0, 1, 0, -2, 12, 2, 1, 1, 0], "cases_matched": 0}

- t31 | Confine little-endian digest encoding to a const-input inline helper on t28 | {"sha256": "90e69af81f50", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t32 | Confine little-endian digest encoding to a const-input inline helper on t22 | {"sha256": "b75292b9dce5", "insns": [959, 951], "score": 90.268135, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [8, 5, 5, 5, 6, 6, 4, 4, 6, 7, 8], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 2, 1, 1, 0], "cases_matched": 0}

- t33 | Digest encoding with advancing output cursor on t22 | {"sha256": "0a96f2030ee8", "insns": [959, 951], "score": 90.268135, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [8, 5, 5, 5, 6, 6, 4, 4, 6, 7, 8], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 2, 1, 1, 0], "cases_matched": 0}

- t34 | Digest encoding with byte-offset loop on t22 | {"sha256": "3782f13e030a", "insns": [959, 951], "score": 90.268135, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [8, 5, 5, 5, 6, 6, 4, 4, 6, 7, 8], "span_deltas": [0, 0, 0, 1, 0, -2, 0, 2, 1, 1, 0], "cases_matched": 0}

- t35 | Digest encoding with countdown over state and output cursors on t22 | {"sha256": "3e3d8abd93ed", "insns": [942, 951], "score": 88.88328, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 88.88328]], "case_deltas": [-9, 5, 5, 5, 6, 6, 4, -13, -11, -10, -9], "span_deltas": [0, 0, 0, 1, 0, -2, -17, 2, 1, 1, 0], "cases_matched": 0}

- t36 | Digest encoding with advancing output cursor on t28 | {"sha256": "8bca8398d0e6", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t37 | Digest encoding with byte-offset loop on t28 | {"sha256": "e05d80dff879", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t38 | Digest encoding with countdown over state and output cursors on t28 | {"sha256": "05ceb589b951", "insns": [937, 951], "score": 72.105156, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 72.105156], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [-14, 0, 0, 0, 1, 1, -1, -17, -16, -15, -14], "span_deltas": [0, 0, 0, 1, 0, -2, -16, 1, 1, 1, 0], "cases_matched": 3}

- t39 | Per-word little-endian writer inside the digest loop | {"sha256": "fc3424430602", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t40 | Serialize the four MD5 state words through four explicit inline writer calls | {"sha256": "3cb1d0e3ac0c", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t41 | Per-word little-endian writer with a const input word pointer | {"sha256": "cef9d356e7bb", "insns": [955, 951], "score": 89.763405, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["ATERMRunConfigProtocol", 89.77287, 89.763405], ["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, -1, -1, -1, 0, 0, -2, 3, 4, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 5, 1, -1, 1, 0], "cases_matched": 2}

- t42 | Use the copied authentication record returned by memcpy for digest serialization | {"sha256": "d1e7436aabd0", "insns": [955, 951], "score": 90.551, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [4, 0, 0, 0, 1, 1, -1, 1, 2, 3, 4], "span_deltas": [0, 0, 0, 1, 0, -2, 2, 1, 1, 1, 0], "cases_matched": 3}

- t43 | Resolve the association identity at each use through a typed accessor, releasing the long-lived request register | {"sha256": "26b2f97caa2c", "insns": [951, 951], "score": 91.70768, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [0, 0, 0, 0, 0, 0, -3, -1, -1, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -3, 2, 0, 1, 0, 0], "cases_matched": 8}

- t44 | Read the received checksum before choosing the default payload pointer, preserving target call and branch order | {"sha256": "beb50f7ddd9d", "insns": [949, 951], "score": 92.06204, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [-2, 0, 0, 0, 0, 0, -3, -2, -2, -2, -2], "span_deltas": [0, 0, 0, 0, 0, -3, 1, 0, 0, 0, 0], "cases_matched": 5}

- t45 | Build the five outgoing TLVs with a generic eight-byte-aligned record appender matching every observed capacity | {"sha256": "2fbb6ae8cf46", "insns": [950, 951], "score": 92.32072, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [-1, 0, 0, 0, 0, 0, -2, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -2, 1, 0, 0, 0, 0], "cases_matched": 5}

- t46 | Distinguish the association request record from its AES key view, retaining the request pointer only for request construction | {"sha256": "e2d45847b078", "insns": [951, 951], "score": 91.72029, "exact": 20, "code": "12200", "data": "10368", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [["main/src/scene/setting/ATERM", "matched_data", "18584", "10368"]], "case_deltas": [0, 0, 0, 0, 0, 0, -3, -1, -1, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -3, 2, 0, 1, 0, 0], "cases_matched": 8}

Object-boundary correction under lever13: preserve the exact old combined0x1118 bytes from0x810BF840 to0x810C0958. The exported configuration is0xe8 bytes, proven by both export/init calls. The16-byte association identity starts0x810BF928 and doubles as the128-bit AES key. SORecvFrom/SOSendTo take the0x800-byte packet region at0x810BF938. The decoded header is at0x810C0138, with request options at+8 and session authentication at+0x800. The remaining original32-byte session workspace starts0x810C0938 and ends at the unchanged thread object. Its challenge occupies bytes0..7 and digest bytes8..23; bytes24..31 were already allocated in the original aggregate and remain part of the same key workspace. No byte is inserted, deleted or moved. Old inferred boundaries incorrectly placed the decoded header in the configuration aggregate and the remaining response eight bytes later. Snapshot original object before symbol corrections; require all section bytes/sizes and every relocation resolved to section+address unchanged.

- t47 | Verify the address-preserving boundary metadata against the original object before further layout work | {"sha256": "e2d45847b078", "insns": [951, 951], "score": 91.72029, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -3, -1, -1, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -3, 2, 0, 1, 0, 0], "cases_matched": 8}

- t48 | Combine checksum-call order with a TLV appender and a stable view of the two long option records | {"sha256": "1be023fa173f", "insns": [950, 951], "score": 92.39222, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-1, 0, 0, 0, 0, 0, -2, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -2, 1, 0, 0, 0, 0], "cases_matched": 5}

- t49 | Return the end of the copied twelve-byte value area from the long-option initializer | {"sha256": "658a069c494b", "insns": [951, 951], "score": 92.21661, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t50 | Use a separate typed long-option initializer while retaining the caller long-record view | {"sha256": "efd32a77c45b", "insns": [951, 951], "score": 92.00736, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t51 | Return a typed next long record from the long-option helper | {"sha256": "97a461a14af5", "insns": [951, 951], "score": 92.00736, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t52 | Return the initialized long record and advance the caller record pointer | {"sha256": "c38738105240", "insns": [951, 951], "score": 92.00736, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t53 | Typed short records with byte-pointer long returns | {"sha256": "bf21afbda6aa", "insns": [954, 951], "score": 91.50368, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [3, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3], "span_deltas": [0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0], "cases_matched": 5}

- t54 | Typed next-record returns for both short and long options | {"sha256": "bf2db61a5608", "insns": [954, 951], "score": 91.50368, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [3, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3], "span_deltas": [0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0], "cases_matched": 5}

- t55 | Indexed byte clear of the completed digest context | {"sha256": "7f7e8798a0bf", "insns": [951, 951], "score": 92.00736, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t56 | Count down the remaining digest-context bytes while advancing the output cursor | {"sha256": "83eb993ed04c", "insns": [951, 951], "score": 92.00736, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0], "cases_matched": 10}

- t57 | Clear the digest context backward with a bounded descending index | {"sha256": "0aee0ba5c988", "insns": [950, 951], "score": 91.90115, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0], "cases_matched": 5}

- t58 | Use the digest context end pointer as the forward byte-clear bound | {"sha256": "d68b2047a145", "insns": [963, 951], "score": 90.824394, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [12, 0, 0, 0, 0, 0, -1, 12, 12, 12, 12], "span_deltas": [0, 0, 0, 0, 0, -1, 13, 0, 0, 0, 0], "cases_matched": 5}

- t59 | Use the cleared long-option header returned by memset | {"sha256": "7603a0f92dc3", "insns": [951, 951], "score": 92.100945, "exact": 20, "code": "12200", "data": "18864", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "cases_matched": 11}

- t60 | Accept a byte cursor and bind the typed long record inside its initializer | {"sha256": "aa519c33c885", "insns": [949, 951], "score": 92.22713, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-2, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2], "span_deltas": [0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0], "cases_matched": 5}

- t61 | Use a size_t payload count in the long-record constructor | {"sha256": "712c3a583e86", "insns": [950, 951], "score": 91.90115, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0], "cases_matched": 5}

- t62 | Use an unsigned type argument until encoding the long-record header | {"sha256": "71739423be3d", "insns": [950, 951], "score": 91.90115, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0], "cases_matched": 5}

- t63 | Use a size_t payload count in the generic record constructor | {"sha256": "404faa8debdf", "insns": [950, 951], "score": 91.90115, "exact": 20, "code": "12200", "data": "18584", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [-1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1], "span_deltas": [0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0], "cases_matched": 5}

- t64 | Restore the all-eleven-entry data candidate for source review and final verification | {"sha256": "7603a0f92dc3", "insns": [951, 951], "score": 92.100945, "exact": 20, "code": "12200", "data": "18864", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "cases_matched": 11}

- t65 | Remove redundant byte-pointer casts from typed response arguments before final review | {"sha256": "67fe2a6a8f90", "insns": [951, 951], "score": 92.100945, "exact": 20, "code": "12200", "data": "18864", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "drops": [], "case_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "span_deltas": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "cases_matched": 11}

baseline fresh object instruction-exact 19/26: ATERMStartNetworkStack, ATERMScanAccessPoints, ATERMFindChangedApRecord, ATERMParseAssociationResponse, ATERMParseHexBytes, ATERMApplyScanSecuritySettings, ATERMAesKeyWrap, ATERMAesKeyUnwrap, ATERMAesExpandDecryptKey, ATERMAesEncryptBlock, ATERMAesDecryptBlock, ATERMMd5Update, ATERMMd5Transform, ATERMAlarmWakeQueue, ATERMi_ApConfigStart, ATERMi_ApConfigEnd, ATERMi_ApConfigGetState, ATERMi_ApConfigGetResult, ATERMi_ApConfigGetVersion

final fresh object instruction-exact 19/26: ATERMStartNetworkStack, ATERMScanAccessPoints, ATERMFindChangedApRecord, ATERMParseAssociationResponse, ATERMParseHexBytes, ATERMApplyScanSecuritySettings, ATERMAesKeyWrap, ATERMAesKeyUnwrap, ATERMAesExpandDecryptKey, ATERMAesEncryptBlock, ATERMAesDecryptBlock, ATERMMd5Update, ATERMMd5Transform, ATERMAlarmWakeQueue, ATERMi_ApConfigStart, ATERMi_ApConfigEnd, ATERMi_ApConfigGetState, ATERMi_ApConfigGetResult, ATERMi_ApConfigGetVersion

## Retained data candidate

t59 first attained all11 jump entries and all18864 data bytes. t65 removes redundant pointer casts with unchanged results. The final source keeps real configuration, association identity, packet, decoded payload and session storage separate. The association record also exposes its existing16 bytes as an AES key. It restores the peer-address argument placed in r4 by the target at.text+0x19d0; the callee does not read that argument, and its compiled instruction stream is unchanged. The received packet view spans protocol states. Outgoing message lengths stay local across the byte-order conversion call. Both packet checksum paths read the checksum before selecting the payload pointer.

The short and long TLV constructors preserve the original clear/copy lengths and option ordering. The long constructor uses the returned cleared header from memset. The authentication record returned by the existing memcpy supplies the digest destination. Clearing the finished MD5 context backward gives the same zero bytes with the required case length. The lever10 guard follows the logged target uninitialized-type path. No assembly, forced data, extra storage, dummy objects, pragmas, compiler flags, shared headers or linking-status edits were used. Case order remains1..10 then the shared0/default tail; each physical case span now agrees.

Fresh source before/after objects prove that only ATERMRunConfigProtocol changes its normalized instruction stream. All other25 instruction streams, including the callee with its restored unused address parameter, agree with the starting object. Exact objdiff20/26 and instruction-exact19/26 stay unchanged. Code12200/19204 unchanged. Data18584/18864 ->18864/18864. Protocol89.77287 ->92.100945,958 ->951 instructions. ctxdiff still reports427 differing instructions, so this is a data-layout success, not an exact code match. Full-report comparison against the locally regenerated f598e410 baseline found zero lower per-function fuzzy percentages or unit code/data/exact/link measures.

Target object boundary proof after regeneration: every PROGBITS/NOBITS section retains its type, byte count and SHA256; all594 relocations retain owner section, relocation offset, relocation kind, and resolved target section+offset or undefined symbol+addend. Old and corrected target instruction/data bytes are identical. Source global addresses are unchanged atBSS+0xba0 configuration,0xc88 association,0xc98 packet,0x1498 response,0x1c98 session,0x1cb8 thread. Config metadata total remains0x1118 bytes across the replaced inferred aggregates. The protocol table stays44 bytes at.data+0xac; total unit data stays18864.

Coverage: ATERMRunConfigProtocol is the only function assigned for source experiments in this data round. Sixty-five checkpoints were measured, including metadata verification, candidate restoration and cast cleanup. Experiments that moved data, reduced fuzzy scores or failed to match the complete table were rejected. Other open functions remain untouched under the explicit data-only task scope.

## Final clean verification

The full gate rebuilt 4.3U without `--quick`, against the assigned starting commit `f598e410`. Its exit status was 0. The canonical report was then regenerated with `ninja -C . progress build/43U/report.json`. A full-report comparison against the locally regenerated starting report found no lower function score or unit code, data, exact-function, or link measure. The target's section contents and all relocation destinations were checked again after the clean build.

```
python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/ATERM --base f598e410
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 12200/19204 data 18864/18864 functions 20/26 fuzzy 98.2020 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 19/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match 100.0
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 100.0
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 98.20204
[src/scene/setting/ATERM]   below 100: ATERMDiscoverAccessPoints 98.31939
[src/scene/setting/ATERM]   below 100: ATERMBuildEncryptedMessage 99.791664
[src/scene/setting/ATERM]   below 100: ATERMBuildAssociationRequest 98.7594
[src/scene/setting/ATERM]   below 100: ATERMRunConfigProtocol 92.100945
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERMAesExpandEncryptKey 98.94403
[src/scene/setting/ATERM] baseline: code 12200/19204 data 18584 functions 20 fuzzy 97.7409
regressions vs baseline: 0
global matched_code_percent: 92.59315 -> 92.59315
global fuzzy_match_percent: 99.74084 -> 99.74379
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.96224
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Final relocation layout from `python3 tools/decomp-assist/jt_layout.py src/scene/setting/ATERM ATERMRunConfigProtocol`:

```
ATERMRunConfigProtocol: target 951 insns, source 951 insns
target table @2631 +0xac; source table @2931 +0xac
Offsets are function-relative; spans end at the next distinct case entry or function end.
case   target  source   delta  target span  source span  target relocation -> source relocation
   0   0e8c    0e8c      +0           20           20  ATERMRunConfigProtocol+0xe8c -> ATERMRunConfigProtocol+0xe8c
   1   00f0    00f0      +0           35           35  ATERMRunConfigProtocol+0xf0 -> ATERMRunConfigProtocol+0xf0
   2   017c    017c      +0           31           31  ATERMRunConfigProtocol+0x17c -> ATERMRunConfigProtocol+0x17c
   3   01f8    01f8      +0           33           33  ATERMRunConfigProtocol+0x1f8 -> ATERMRunConfigProtocol+0x1f8
   4   027c    027c      +0           72           72  ATERMRunConfigProtocol+0x27c -> ATERMRunConfigProtocol+0x27c
   5   039c    039c      +0          156          156  ATERMRunConfigProtocol+0x39c -> ATERMRunConfigProtocol+0x39c
   6   060c    060c      +0          259          259  ATERMRunConfigProtocol+0x60c -> ATERMRunConfigProtocol+0x60c
   7   0a18    0a18      +0           63           63  ATERMRunConfigProtocol+0xa18 -> ATERMRunConfigProtocol+0xa18
   8   0b14    0b14      +0          127          127  ATERMRunConfigProtocol+0xb14 -> ATERMRunConfigProtocol+0xb14
   9   0d10    0d10      +0           75           75  ATERMRunConfigProtocol+0xd10 -> ATERMRunConfigProtocol+0xd10
  10   0e3c    0e3c      +0           20           20  ATERMRunConfigProtocol+0xe3c -> ATERMRunConfigProtocol+0xe3c
Cases at target offset: 11/11
```

Target object comparison with the preserved original target, after the clean rebuild:

```
Section bytes, sizes and types unchanged: True
Resolved relocation targets unchanged: True entries 594 594
Post-clean full-report regressions: 0
[]
src 0xedc base 0xedc insns 951/951
diffs 427: [6, 7, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 36, 62]
```

The data-round acceptance condition is satisfied locally: +280 matched data bytes, all 11 protocol case offsets correct, and zero regressions. The unit remains NonMatching and unlinked. Parent verification is still required before integration. Existing untracked logs were left untracked; trial sources, reports, and original object snapshots remain under `sz3.work/` for review.
