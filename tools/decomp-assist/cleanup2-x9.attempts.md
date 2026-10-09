# cleanup2-x9 cleanup attempts

Worktree: `/mnt/drive2/projects/wii-ipl-workers/sol-high`.
Branch: `agent/w1009/cleanup2-x9`.
Baseline: `c3dd1c08c04a38975b63dded77a7aef6fce385f3`, equal to local `origin/main` at start.

Full build first passed, 1028/1028 units and 12563/12563 functions exact and linked. Code and data are 100%. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`; completion checker `DECOMPLETE_OK`.

Owned scope: RVLMiddleware except eZiText and jpegdec/jdec_main.c; RVLFaceLib; OperaWWW. Existing untracked rx4, rx59 and rx70 evidence files are preserved.

## Largest-first audit and prior attempts

- RFL_Database, RFL_Model and RFL_NANDAccess precede the texture converters by source size. Database and NAND access already use named types and structured control flow. RFL_Model's GX casts remove const from embedded arrays because the SDK takes void pointers; the casts are required. Its private read-only model views can preserve const.
- Read cleanup-c5's texture trials. Do not repeat pragma deletion, declaration initialization, sampling-case local scopes, first-store separation, alpha masks or cancelling-add removal. All changed instructions. The three level-1 scopes and the RGBA8 first-store/alpha expressions already have concise compiler comments.
- Read cleanup2-w5's buffer trials. Keep its common-success exit and the explained empty else branches. Do not repeat structured pointer movement or empty-else deletion.
- Init parameter fields at 0x24 and 0x2C have callers in src/utility/iplJpegDecoder.cpp outside this assignment. State field 0x21 is used by excluded jdec_main.c. Preserve these names to respect ownership.
- OperaWWW consists of API/type headers with named fields. No cleanup candidates found.

## Trials

- `model-gx-redundant-void-casts`: rejected. compile failed: M_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions on -lang=c -MMD -c libs/RVLFaceLib/src/RFL_Model.c -o build/43U/src/libs/RVLFaceLib/src && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLFaceLib/src/RFL_Model.d build/43U/src/libs/RVLFaceLib/src/RFL_Model.d
### mwcceppc.exe Compiler:
#    File: libs\RVLFaceLib\src\RFL_Model.c
# ----------------------------------------
#     489:         GXSetArray(GX_VA_POS, charModelRes->vtxPosBeard, 6); 
#   Error:                                                           ^
#   (10209) illegal implicit conversion from 'const short[120]' to
#   'void *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

- `model-preserve-const-in-private-views`: retained. All allocated sections and normalized relocations identical.
- `huffman-dc-structured-head-check`: rejected. libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32: changed .text, .rela.text; TMCJPEGDEC_decode_iquant: 231 diffs, 277/276 instructions
- `huffman-dc-structured-else-return`: rejected. libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32: changed .text; TMCJPEGDEC_decode_iquant: 24 diffs, 276/276 instructions
- `huffman-dc-while-limit-helper`: retained. All allocated sections and normalized relocations identical.
- `huffman-ac-while-limit-helper`: retained. All allocated sections and normalized relocations identical.
- `huffman-remove-unused-limit-reader`: retained. All allocated sections and normalized relocations identical.
- `huffman-share-identical-long-code-decoder`: retained. All allocated sections and normalized relocations identical.
- `rfl-wait-remove-local-volatility`: rejected. libs/RVLFaceLib/src/RFL_System: changed .text, extabindex, .rela.text, .relaextabindex; bootloadDB2Res_: 105 diffs, 132/139 instructions; RFLInitResAsync: 72 diffs, 215/218 instructions; RFLInitRes: 13 diffs, 37/40 instructions; RFLExit: 60 diffs, 95/98 instructions; RFLWaitAsync: 13 diffs, 36/39 instructions
- `rfl-wait-keep-explained-status-spill`: retained. All allocated sections and normalized relocations identical.
- `resolution-huffman-typed-entry-copy`: retained. All allocated sections and normalized relocations identical.
- `resolution-huffman-structured-while-helper`: retained. All allocated sections and normalized relocations identical.
- `api-frame-result-structured-statements`: rejected. libs/RVLMiddleware/TMC_JPEG/src/api/decapi: changed .text, .rela.text; TMCCJPEGDecInit: 81 diffs, 130/131 instructions
- `api-frame-result-inline-helper`: retained. All allocated sections and normalized relocations identical.
- `api-scan-result-structured-condition`: rejected. libs/RVLMiddleware/TMC_JPEG/src/api/decapi: changed .text, .rela.text; TMCCJPEGDecInit: 73 diffs, 128/131 instructions
- `api-scan-result-inline-helper`: retained. All allocated sections and normalized relocations identical.
- `huffman-remove-unused-table-local`: rejected. compile failed: -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -use_lmw_stmw on -lang=c -MMD -c libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.c -o build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d
### mwcceppc.exe Compiler:
#    File: libs\RVLMiddleware\TMC_JPEG\src\b65\iqdec_b65_frv32.c
# --------------------------------------------------------------
#     107:         huff_tbl = work->tables.pDCHuffTbl; 
#   Error:         ^^^^^^^^
#   (10140) undefined identifier 'huff_tbl'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

- `huffman-compare-limit-without-entry-copy`: rejected. libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32: changed .text, .rela.text; TMCJPEGDEC_decode_iquant: 228 diffs, 266/276 instructions
- `resolution-huffman-compare-without-entry-copy`: rejected. libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3: changed .text; TMCJPEGDEC_vl_decode_rc: 39 diffs, 57/60 instructions
- `final-huffman-copy-notes`: retained. All allocated sections and normalized relocations identical.
- `final-all-owned-objects`: retained. All allocated sections and normalized relocations identical.

## Retained cleanup and compiler constraints

- RFL_Model.c preserves const in five private model views and two resource views. Keep GX void-pointer casts because its embedded geometry arrays become const through the resource view and the SDK requires void pointers.
- RFL_System.c retains the volatile polling result with one compiler comment. Removing it loses three instructions in RFLWaitAsync and changes four callers that inline the poll.
- iqdec_b65_frv32.c removes both jumps into the Huffman loops, the unused readHuffmanLimit function and the duplicate AC long-code decoder. Both paths use a structured while loop and one long-code decoder. Keep the decoded-entry copy: removing it drops ten instructions. The attempted huff_tbl-local deletion was invalid because the DC path assigns and uses that pointer; restored it.
- iqdec_resolution_change_a3.c removes the jump into the Huffman loop and the word/halfword pointer-punning casts. Named Huffman entries and a structured while loop preserve all bytes. Keep its decoded-entry copy: removing it drops three instructions. Both retained copies have one compiler comment.
- decapi.c removes the MCU-count comma expression and both nested result ternaries. Ordinary inline helpers preserve the original result handling. Direct statements changed 131 instructions to 130 or 128, so keep the helpers. Preserve both idiomatic common error exits.
- The remaining RFL and JPEG files already use structured control flow and named types. The condition scan found no comma operators or assignment expressions in if/while conditions. Texture scopes and RGBA8 store expressions remain as documented by cleanup-c5. Buffer common-success exits and empty else branches remain as documented by cleanup2-w5.
- No headers, hand-written assembly, eZiText sources, jpegdec/jdec_main.c or files in other worktrees changed. Applied unslop and writing-for-agents to this handoff.

## Final verification

One final gate ran with --quick over all five changed units. Full 43U build passed; GATE PASS; zero regressions, added forbidden patterns and readability warnings. Log: `/tmp/cleanup2-x9-final-gate.log`.

All 29 owned objects have identical allocated sections, sizes, alignments and normalized relocation destinations versus the initial full-build objects. Their fresh report entries have 100% code, data, function and link measures; every reported section and function is 100%. A compiler's local symbol numbering may differ without changing the relocation destinations.

| Changed unit | Exact functions before and after | Code bytes | Data bytes |
| --- | --- | --- | --- |
| RFL_Model | 15/15 | 7788/7788 | 552/552 |
| RFL_System | 28/28 | 2880/2880 | 252/252 |
| iqdec_b65_frv32 | 1/1 | 1104/1104 | 0/0 |
| iqdec_resolution_change_a3 | 2/2 | 908/908 | 0/0 |
| decapi | 3/3 | 1100/1100 | 0/0 |

Fresh pool_diff checks are identical for all five units. Fresh ctxdiff checks report diffs 0: RFLDrawOpaCore 323/323, RFLWaitAsync 39/39, TMCJPEGDEC_decode_iquant 276/276, TMCJPEGDEC_vl_decode_rc 60/60, TMCCJPEGDecInit 131/131. Focused log: `/tmp/cleanup2-x9-focused.log`. The initial pool_diff command incorrectly supplied a unit name; repeated it with the required object paths.

Fresh report and completion checker: `DECOMPLETE_OK`. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`. Whitespace check passed. Source files were committed separately; no push, PR, merge or rebase occurred.

## Source commits

- `feb726b2` libs/RVLFaceLib/src/RFL_Model.c
- `1efd071c` libs/RVLFaceLib/src/RFL_System.c
- `f7b57241` libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.c
- `475566d4` libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3.c
- `3c63ac04` libs/RVLMiddleware/TMC_JPEG/src/api/decapi.c
