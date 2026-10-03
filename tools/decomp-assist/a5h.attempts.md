# a5h high-effort CHANSVm round

Owned worktree data-d5, branch agent/w1003/astra-a5-high, starting HEAD/origin f170531a. Read a5 prior attempts and final gate, shared prompt and all ten levers, CHANSVm policy entries, local CHANSVm/fz1/big1 histories. Prior-art index has no entry. Prior medium round gained no exact functions; its Step operand-order change is absent from this fresh main. Baseline 222/233 exact, code 38136/53564, data 6904/6904, fuzzy 99.4341. Pool first: 125/125 identical. All data sections already exact; no symbol edits warranted.

High-round focus: float parser store/compare scheduling, document-writer lifetime reuse, formatter temporary lifetimes, executable table fixup registers. Do not repeat previously logged plain declaration permutations or five orchestrator writer shapes. No target evidence permits an uninitialized local; preserve every initialization. No eZiText optimization-off lever applies. Follow helpers/types/const/lifetimes before allocation searches. Remaining functions receive at least three new source forms before handoff.
- {"function": "CHANSVmConvertToFloatFromStr", "attempt": "end-pointer scratch initialized by inline parser formal argument", "source": "fcfdea703d2c", "build": 0, "fuzzy": 95.180725, "insns": [83, 83], "diffs": 3, "code": "38136", "data": "6904"}
- {"function": "CHANSVmConvertToFloatFromStr", "attempt": "caller owns addressable end pointer, parser initializes via formal output", "source": "3dcf785ca76e", "build": 0, "fuzzy": 97.59036, "insns": [83, 83], "diffs": 2, "code": "38136", "data": "6904"}
- {"function": "CHANSVmConvertToFloatFromStr", "attempt": "parser output is native float object instead of scalar field address", "source": "ea36389b824e", "build": 0, "fuzzy": 97.59036, "insns": [83, 83], "diffs": 2, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "whole writer body through vm-only inline helper", "source": "aa8222d6230b", "build": 0, "fuzzy": 99.10448, "insns": [67, 67], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "argument index passed through whole writer helper", "source": "0b85ce17d3ad", "build": 0, "fuzzy": 99.10448, "insns": [67, 67], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "writer conversion type through inline formal enum", "source": "c37487e4baa2", "build": 0, "fuzzy": 99.10448, "insns": [67, 67], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "native formatted string ownership record: const wchar_t* data; CHANSVmObjHdr* object;", "source": "4195315f4732", "build": 0, "fuzzy": 99.84919, "insns": [431, 431], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "native formatted string ownership record: CHANSVmObjHdr* object; const wchar_t* data;", "source": "e9b3a96255b6", "build": 0, "fuzzy": 99.84919, "insns": [431, 431], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "native formatted string ownership record: const wchar_t* data; CHANSVmObjHdr* object; s32 length;", "source": "a8e576986777", "build": 0, "fuzzy": 99.84919, "insns": [431, 431], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "only string input gets independent typed lifetime; existing cleanup and output counts retained", "source": "5923077b2fa8", "build": 0, "fuzzy": 99.187935, "insns": [431, 431], "diffs": 53, "code": "38136", "data": "6904"}
- {"function": "VmDateDtor", "attempt": "calendar table indices widened explicitly to unsigned native indices", "source": "f1be39516ed0", "build": 0, "fuzzy": 94.96703, "insns": [91, 91], "diffs": 7, "code": "38136", "data": "6904"}
- {"function": "VmDateDtor", "attempt": "calendar table lookup uses shared unsigned accessor with month evaluated as helper first", "source": "e39110d7d93c", "build": 0, "fuzzy": 94.96703, "insns": [91, 91], "diffs": 7, "code": "38136", "data": "6904"}
- {"function": "VmDateDtor", "attempt": "calendar format call receives returned date value through inline boundary", "source": "f1da6f67f1a2", "build": 0, "fuzzy": 72.98901, "insns": [107, 91], "diffs": 97, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "argument acquisition and conversion in inline helper with CHANSVm*", "source": "dd098720f2f6", "build": 0, "fuzzy": 99.62687, "insns": [67, 67], "diffs": 5, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "argument acquisition and conversion in inline helper with const CHANSVm*", "source": "e2aa528796b4", "build": 0, "fuzzy": 99.62687, "insns": [67, 67], "diffs": 5, "code": "38136", "data": "6904"}
- {"function": "VmWinEmuWrite", "attempt": "encoder scratch and bound scoped after successful converted-object check", "source": "292969d911b0", "build": 0, "fuzzy": 99.62687, "insns": [67, 67], "diffs": 5, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method fixup helper header precedes VM in formal argument order", "source": "666757906e2a", "build": 0, "fuzzy": 99.744095, "insns": [254, 254], "diffs": 10, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method fixup helper gets table as independent const formal", "source": "f4b21b6a6f11", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method fixup helper gets table as independent mutable formal", "source": "315f755a9816", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method helper counter declaration before table binding", "source": "e9373aac8d33", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method helper table pointer const binding", "source": "7b539fde55dc", "build": 0, "fuzzy": 99.744095, "insns": [254, 254], "diffs": 10, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "module clear uses offset declared before index", "source": "5a52a46d26af", "build": 0, "fuzzy": 99.66535, "insns": [254, 254], "diffs": 13, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "module initialization loop through header-only helper", "source": "bd1650d81d65", "build": 0, "fuzzy": 99.744095, "insns": [254, 254], "diffs": 10, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "typed module entry indexed memset with compiler-managed byte stride", "source": "e766de18a400", "build": 0, "fuzzy": 99.96063, "insns": [254, 254], "diffs": 1, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "module stride is function-scoped beside region offsets", "source": "78e9121d89c6", "build": 0, "fuzzy": 99.80315, "insns": [254, 254], "diffs": 7, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "module clear offset is native signed byte offset", "source": "a710deff2beb", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method name end address: (vmU32)methodTable + methodTable[i].nameLength + methodTable[i].offset", "source": "3a910e6ab28e", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method name end address: methodTable[i].offset + (methodTable[i].nameLength + (vmU32)methodTable)", "source": "1a3385de7f93", "build": 0, "fuzzy": 99.92126, "insns": [254, 254], "diffs": 3, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "method name end address: (vmU32)((u8*)methodTable + methodTable[i].nameLength) + methodTable[i].offset", "source": "83c732793800", "build": 0, "fuzzy": 99.88189, "insns": [254, 254], "diffs": 4, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "typed clear plus method end address: (vmU32)methodTable + methodTable[i].nameLength + methodTable[i].offset", "source": "688f0a2ef623", "build": 0, "fuzzy": 99.96063, "insns": [254, 254], "diffs": 1, "code": "38136", "data": "6904"}
- {"function": "CHANSVmAddExe", "attempt": "typed clear plus method end address: methodTable[i].offset + (methodTable[i].nameLength + (vmU32)methodTable)", "source": "16bc72f47d1f", "build": 0, "fuzzy": 100.0, "insns": [254, 254], "diffs": 0, "code": "39152", "data": "6904"}

## CHANSVmAddExe exact candidate

Method-table fixup has its own loop and success/failure result in target instructions183..214. Extracting it with index declared before table pointer fixes the initial module/type register exchange and method loop registers. Typed module entry indexing gives target compiler-managed stride r29 instead of manual offset r28. Reassociating the validated end address as offset+(nameLength+table) gives target add r3,r5,r28. All arithmetic operands remain unsigned32 with identical wrap behavior; table validation and calls retain order. Result100.0%,254/254instructions,diffs0,code39152,data6904. Quick full-build GATE PASS, zero regressions/forbidden/readability, exact223/233, correctDOL. Formatting cleanup follows, then fresh gate before local commit.
- {"function": "VmBlobGetHexString", "attempt": "raw byte encoder inline boundary with output first", "source": "3e7e12925d9d", "build": 0, "fuzzy": 97.35366, "insns": [82, 82], "diffs": 32, "code": "39152", "data": "6904"}
- {"function": "VmBlobGetHexString", "attempt": "raw byte encoder read-only source and explicit digit table", "source": "91218592b8d3", "build": 0, "fuzzy": 97.35366, "insns": [82, 82], "diffs": 32, "code": "39152", "data": "6904"}
- {"function": "VmBlobGetHexString", "attempt": "raw byte encoder loop counter initialized at helper boundary", "source": "5e32f6e45a16", "build": 0, "fuzzy": 97.35366, "insns": [82, 82], "diffs": 32, "code": "39152", "data": "6904"}
- {"function": "VmStringSplit", "attempt": "typed real metadata record for parent split span", "source": "fb732f313bac", "build": 0, "fuzzy": 97.567566, "insns": [222, 222], "diffs": 84, "code": "39152", "data": "6904"}
- {"function": "VmStringSplit", "attempt": "typed real metadata record for delimiter split span", "source": "190fa665d513", "build": 0, "fuzzy": 97.72523, "insns": [222, 222], "diffs": 76, "code": "39152", "data": "6904"}
- {"function": "VmStringSplit", "attempt": "typed real metadata record for both split spans", "source": "b88a5d1ad181", "build": 0, "fuzzy": 97.432434, "insns": [222, 222], "diffs": 90, "code": "39152", "data": "6904"}
- {"function": "VmBlobPackCommon", "attempt": "native blob copy and zero-fill helper with BlobHeader* source", "source": "8af1bfdec68f", "build": 0, "fuzzy": 97.97156, "insns": [668, 668], "diffs": 242, "code": "39152", "data": "6904"}
- {"function": "VmBlobPackCommon", "attempt": "native blob copy and zero-fill helper with const BlobHeader* source", "source": "718b0dd3c12a", "build": 0, "fuzzy": 97.97156, "insns": [668, 668], "diffs": 242, "code": "39152", "data": "6904"}
- {"function": "VmBlobPackCommon", "attempt": "integer staging buffer lifetime belongs to packing iteration", "source": "9c318ea16d63", "build": 0, "fuzzy": 97.949104, "insns": [668, 668], "diffs": 244, "code": "39152", "data": "6904"}
- {"function": "VmBlobUnpack", "attempt": "integer staging union lifetime belongs to unpacking iteration", "source": "6017037ff266", "build": 0, "fuzzy": 98.452614, "insns": [517, 517], "diffs": 141, "code": "39152", "data": "6904"}
- {"function": "VmBlobUnpack", "attempt": "signed and unsigned integer decoding helper with u32* input", "source": "e6f7a5f031d0", "build": 0, "fuzzy": 95.46228, "insns": [526, 517], "diffs": 366, "code": "39152", "data": "6904"}
- {"function": "VmBlobUnpack", "attempt": "signed and unsigned integer decoding helper with const u32* input", "source": "52628f4f9f18", "build": 0, "fuzzy": 95.46228, "insns": [526, 517], "diffs": 366, "code": "39152", "data": "6904"}
- {"function": "CHANSVmLinkModules", "attempt": "third module pass separated with CHANSVmModule* input", "source": "c2880482ee9c", "build": 0, "fuzzy": 98.677246, "insns": [189, 189], "diffs": 43, "code": "39152", "data": "6904"}
- {"function": "CHANSVmLinkModules", "attempt": "third module pass separated with const CHANSVmModule* input", "source": "50e11723d30b", "build": 0, "fuzzy": 98.677246, "insns": [189, 189], "diffs": 43, "code": "39152", "data": "6904"}
- {"function": "CHANSVmLinkModules", "attempt": "shared typed dispatch-name validation and comparison boundary", "source": "47e9680b69cd", "build": 0, "fuzzy": 84.08995, "insns": [173, 189], "diffs": 169, "code": "39152", "data": "6904"}
- {"function": "CHANSVmStep", "attempt": "floating immediate load uses typed scratch output helper", "source": "319c356e86f7", "build": 0, "fuzzy": 96.98723, "insns": [1253, 1253], "diffs": 276, "code": "39152", "data": "6904"}
- {"function": "CHANSVmStep", "attempt": "signal consumption isolated as initialized boolean helper", "source": "ad852802744f", "build": 0, "fuzzy": 96.73743, "insns": [1257, 1253], "diffs": 1160, "code": "39152", "data": "2232"}
- {"function": "CHANSVmStep", "attempt": "instruction range validation through const execution-context helper", "source": "75bd6182f4ed", "build": 0, "fuzzy": 96.47805, "insns": [1260, 1253], "diffs": 1214, "code": "39152", "data": "2232"}
- {"function": "CHANSVmFormatString", "attempt": "formatted ownership record assigned before copy call", "source": "3bf8fcb93c2c", "build": 0, "fuzzy": 96.92575, "insns": [431, 431], "diffs": 150, "code": "39152", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "formatted owner is allocated directly into cleanup record", "source": "af2098b87259", "build": 0, "fuzzy": 97.38979, "insns": [431, 431], "diffs": 147, "code": "39152", "data": "6904"}
- {"function": "CHANSVmFormatString", "attempt": "direct formatted owner with character ownership initialized before data binding", "source": "e4428eea5fcd", "build": 0, "fuzzy": 96.89095, "insns": [430, 431], "diffs": 249, "code": "39152", "data": "2232"}
- {"function": "CHANSVmConvertToFloatFromStr", "attempt": "float parser tag dispatch expressed as single supported switch case", "source": "72a9cfd97545", "build": 0, "fuzzy": 96.26506, "insns": [84, 83], "diffs": 69, "code": "39152", "data": "6904"}
- {"function": "CHANSVmConvertToFloatFromStr", "attempt": "float parser tag guard branches to common invalid result", "source": "d2b34ee3b2d0", "build": 0, "fuzzy": 97.59036, "insns": [83, 83], "diffs": 2, "code": "39152", "data": "6904"}

## Coverage and retained result

New high-round boundaries were compiled for every remaining function. Split222, Hex82, Pack668, Unpack517 and Link189 already share the target CFG and instruction counts; their new span/encoder/decoder/pass boundaries tested real lifetime changes. Rejected all fuzzy-only experiments. Step1253 has structural and allocation differences; its floating load boundary changes no instructions, while signal/range boolean helpers add instructions and lose jump-table data. Restored all three. Formatter431 keeps its13register differences; ownership-record stores before copy regress allocation. Parser83 still has the adjacent initialization-store/type-compare inversion; target initializes the end pointer, so removal/volatile tricks are unwarranted. Writer67 still has5register differences; whole writer and argument-acquisition boundaries do not resolve vm/string register reuse. Date91 retains7table and varargs scheduling differences.

All ten levers reviewed: helpers, true field types, const views, separate locals and scopes tested; new AddExe graph and typed indexing resolve register lifetimes without another exhaustive declaration sweep. No eZiText-specific lever applies. Counted traversal preserves Hex CTR. Prior-art index has no matching entry. Target initialization audit from the preceding round remains valid; no undefined values introduced. All data already100%, so no relocation rename/extent correction applies.

Distinct successful source forms this round:
- CHANSVmConvertToFloatFromStr: 5
- VmWinEmuWrite: 6
- CHANSVmFormatString: 7
- VmDateDtor: 3
- CHANSVmAddExe: 15
- VmBlobGetHexString: 3
- VmStringSplit: 3
- VmBlobPackCommon: 3
- VmBlobUnpack: 3
- CHANSVmLinkModules: 3
- CHANSVmStep: 3

Only CHANSVmAddExe source changes retained, exact100.0 with254/254instructions anddiffs0. Initial candidate committed470bb80e after fresh quick full-build gate. Full clean final gate follows. Worker result remains subject to independent parent verification.

Final fetch 934587c4: owned source unchanged from startingmain. No concurrent match duplicated. All54successful distinct source trials recorded; temporary variants will be removed after final measurements.

Final clean non-quick GATE PASS. CHANSVm exact222/233 ->223/233, code38136 ->39152/53564, data6904/6904unchanged, fuzzy99.43410 ->99.44119. No regressions, forbidden additions or readability warnings. Full43Ubuild, pool and targetDOLhash pass. Regenerated live progress/report and build/43U/ok, then independently rechecked AddExe254/254,diffs0. No source changes after470bb80e. Parent verification required before acceptance.
