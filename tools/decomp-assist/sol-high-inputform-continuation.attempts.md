# tiInputForm continuation
Baseline quick gate: instruction-exact 214/221; objdiff 216/221; code 45080/50656; data 908/3772; asm bodies 3; pool identical; regressions 0; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Structural diagnosis before experiments:
- onCursor: same 0x120 frame and 473 instructions; five differences at width temporaries and two multiplication operands. Inline Rect accessors affect operand form.
- calcCursorPos: same 0xf0 frame and 326 instructions; scale components occupy reversed FP registers, rectangle arithmetic is jointly scheduled rather than the target's separate inline height/width boundaries.
- LayoutByNW4R::create: 352/356 instructions; initial root query uses virtual getPane instead of direct FindPaneByName; later conditional query hoists receiver loads; animation-file pointer is cached across calls where target reloads it.
- setLanguage: same frame and 237 instructions; two conditional pane-name blocks hoist layout/root loads before branch. No string-pool divergence.
- Concatenated isEnableCursorCache/getStartPos: original eight-byte symbol covers two existing members. No source/config renaming or resizing allowed.
- disasm_fn stops at paired-single instructions on this Capstone build; ctxdiff and per-instruction declsearch decoding expose the full body.
Initial nine cursor trials were rerun with corrected pool_diff arguments below. First copies without pool output are excluded from the audit.

onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-0 | 540b49819992 | score (0, 4) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-1 | 1018ca1bcebf | score (0, 3) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-2 | 10371ce40618 | score (10, 17) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-3 | f728d01ca4c9 | score (0, 4) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-4 | 318a3e072a93 | score (4, 8) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-0 | df65ad444316 | score (14, 17) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-1 | 39992fee9a8b | score (14, 17) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-2 | db564c79896e | score (0, 7) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-3 | 9868b91a4ea9 | score (0, 3) instructions 473/473 | 
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-0 | 540b49819992 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-1 | 1018ca1bcebf | score (0, 3) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-2 | 10371ce40618 | score (10, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-3 | f728d01ca4c9 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-accessor-boundary-4 | 318a3e072a93 | score (4, 8) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-0 | df65ad444316 | score (14, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-1 | 39992fee9a8b | score (14, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-2 | db564c79896e | score (0, 7) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-center-helper-3 | 9868b91a4ea9 | score (0, 3) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-0 | fbfea889b955 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-1 | 30287152ca58 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-2 | db5ab9c485e4 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-3 | 03cd168ad159 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-4 | 58ce0d8ec056 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-5 | 74a1b2358802 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-6 | a5f82cf8538b | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-7 | b147b955a959 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-8 | 3930e547f58d | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-9 | ba9eb102785b | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-10 | 7ad938b508c7 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-reuse-rectangle-11 | 3c182590a36c | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-0 | d11215cf5e08 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-0 | 266cd86b5276 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-0 | 9cfc32375c4d | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-1 | 3afe057a0e80 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-1 | 49f309a1542e | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-1 | 21300e88c458 | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-2 | 6040e571ab84 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-2 | 68e4541c6b7e | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-2 | 420ff29a9882 | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-3 | 6e91b9f42d87 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-3 | 11a0ffa84178 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-3 | e9c8fd782fdc | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-4 | e91f413718f5 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-4 | b6eb44567fbb | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-4 | 4a9aa7494020 | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-0-5 | f728d01ca4c9 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-1-5 | 67c80fb73b61 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-decl-scope-2-5 | 15913b71258b | score (0, 6) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-0 | 229f61d14189 | score (26, 43) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-1 | 0c12625beaf2 | score (26, 43) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-2 | b2f56ff914f1 | score (80, 235) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-3 | 721eb7bbb34b | score (80, 235) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-4 | 23f72561d7f1 | score (26, 54) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-5 | 7382d3822dec | score (26, 54) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-6 | c099e471bba7 | score (26, 54) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-7 | b8accdca32b1 | score (26, 54) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-8 | 0c49513b1190 | score (72, 329) instructions 331/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-9 | 567002642739 | score (72, 329) instructions 331/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-10 | 30a4359e3249 | score (245, 397) instructions 401/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-inline-geometry-11 | 81459b226e6c | score (245, 397) instructions 401/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-0 | ce49aebb516b | score (0, 5) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-1 | a135e0144bc9 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-2 | c286200c90fa | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-3 | e8a7bfb851a4 | score (0, 3) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-4 | 8c86eb679ff1 | score (0, 7) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-5 | 293a7c71503b | score (14, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-6 | b01025a3ca45 | score (0, 7) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-7 | 2003dd441280 | score (0, 7) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-8 | 917a6209708b | score (14, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-9 | d9346cd0dc50 | score (0, 7) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-10 | e70ab2990eaf | score (10, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-11 | 9a1a3c6f0761 | score (0, 4) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-12 | 20b779c34e7e | score (10, 17) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-operand-helper-13 | 93c0fbd6d383 | score (0, 3) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-0 | de89b173bcd2 | score (0, 2) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-1 | 859f4ef7ab72 | score (0, 1) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-2 | 87ff22954cef | score (0, 2) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-3 | 1097890e7782 | score (0, 1) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-4 | 81faa3d995dc | score (0, 1) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)
onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos | cursor-all-accessors-5 | 8e7f6ceaecca | score (0, 0) instructions 473/473 | POOL IDENTICAL up to 20 (mine=20 base=20)

Accepted onCursor: fresh full gate PASS; objdiff 100.0%; ctxdiff 473/473, diffs 0; pool identical; regressions 0; readability/forbidden 0; DOL correct. Inline width accessors throughout onCursor plus a single centered width expression preserve target temporary homes and multiplication operands. Shared headers unchanged.
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-0 | 0d0c42639971 | score (24, 186) instructions 239/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-1 | a2a02ac0dc07 | score (24, 186) instructions 239/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-2 | build failed; excluded
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-3 | fdbfdb7f264d | score (12, 22) instructions 237/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-4 | e659de7a358f | score (12, 22) instructions 237/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-5 | 9f7f572dbf04 | score (23, 190) instructions 252/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-selector-boundary-6 | ba10179ece2a | score (31, 190) instructions 252/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-0 | 8e7f6ceaecca | score (20, 230) instructions 352/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-1 | 0a364a04c1a3 | score (15, 178) instructions 354/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-2 | 3dd47ea1b7d0 | score (11, 231) instructions 354/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-3 | eefda73f93e6 | score (6, 153) instructions 356/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-4 | 9420eff8e29f | score (20, 230) instructions 352/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-5 | 01d2c5a19793 | score (15, 178) instructions 354/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-6 | 62883ff07dd4 | score (11, 231) instructions 354/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | layoutcreate-query-file-slots-7 | 379e110e3fb7 | score (6, 153) instructions 356/356 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-0 | f1745af389f0 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-1 | build failed; excluded
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-2 | 29237d032c25 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-3 | d100c1be01c9 | score (0, 27) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-4 | 53166392bdfb | score (0, 27) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-5 | build failed; excluded
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-6 | 8eb55addec1d | score (0, 27) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-row-helper-7 | 229f003b20cb | score (0, 27) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-0 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-1 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-2 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-3 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-4 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-5 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-6 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-7 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-8 | build failed; excluded
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-9 | build failed; excluded

Assembly conversion diagnosis:
- Base::create target frame 0x20, 72 instructions. First C++ form has identical structure and frame, 26 register differences confined to circular row removal/insertion. The inline-helper boundary trials retain structure but change row/index register homes.
- Base::calc target frame 0x40, 165 instructions. Animation, kana timer and color interpolation calls are structurally represented; remaining checks compare sine angle operands, float conversion/store scheduling and counter/phase updates.
- RowInfoManager::init target leaf, 39 instructions. u16 loop index; row Back/Next/StrCount/DispRowCount stores; target re-reads capacity for free/active sentinels and uses update-address stores.
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-0 | 239a30680a4e | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-1 | d0c86385a93f | score (15, 21) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-2 | 0f58ed0ac038 | score (15, 21) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-3 | 49b8cf4e2fec | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-4 | 04b55da1bd68 | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-5 | 618bd5ec4be4 | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-6 | 33ff141f1f0a | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-7 | 1e799393dd2d | score (15, 24) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-8 | 9e6d79635811 | score (19, 22) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-9 | 33bef97a5cd5 | score (13, 21) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-0 | ec8b1b6f2d22 | score (8, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-1 | 09e37bef8e4a | score (8, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-2 | e789d7c358de | score (7, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-3 | 83832dfadf25 | score (7, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-4 | 86c40292827f | score (8, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-5 | d2f1f0e27b81 | score (8, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-6 | 4a519ea9b66e | score (7, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-head-boundary-7 | 417c06aece08 | score (7, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-inspect | 49b8cf4e2fec | score (15, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-0 | 2126f11ffa6e | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-1 | dafd3daec426 | score (10, 16) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-2 | 1ee30699a55d | score (10, 16) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-3 | 1e7b8c222fa3 | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-4 | 35c8f47bee42 | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-5 | 6767ce1a898b | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-6 | 43069bea0824 | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)

Calc semantic correction from target offsets: 0x78 is Decolated::isOnSustain, not 0xC0 isKanaFix. The store at Base+0x100 is mfDrawScrollY, not CharWriter cursorY. Initial calc trials used these incorrect APIs and were not candidates; corrected and rerun.
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-7 | ce8459d74e29 | score (10, 19) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-8 | a76720f622cd | score (14, 17) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-color-sine-boundary-9 | 6777eef4b9ad | score (8, 16) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-corrected-inspect | 1e7b8c222fa3 | score (10, 14) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-init-inspect | ec8b1b6f2d22 | score (8, 15) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-0 | 4640f7059093 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-1 | 2ba30cd77e4b | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-2 | 7f88daa38038 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-3 | 48a587ce1fde | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-4 | f18185222219 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-5 | 2ce8c5cc738f | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-6 | f3dfcf774839 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-7 | 2ce8c5cc738f | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-8 | ca4f607b4fd7 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-9 | 3b2250a30010 | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-10 | ca4f607b4fd7 | score (0, 5) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-blue-angle-phase-staging-11 | a18dc38b6b17 | score (4, 9) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-0 | aa8541648f06 | score (5, 20) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-1 | e21fdd48c5c6 | score (5, 20) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-2 | faca7686c58e | score (5, 20) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-3 | b4249a99d930 | score (5, 20) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-4 | 9ab268f25ddd | score (5, 20) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-5 | ee59a86845cc | score (5, 16) instructions 166/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-6 | a3120eb506b9 | score (2, 6) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-7 | 1fe2ad3b1397 | score (2, 6) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-8 | a1beabe08f52 | score (2, 6) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-9 | 363f9e0250f8 | score (2, 6) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-10 | 79f77912079d | score (2, 6) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-11 | 902951983695 | score (2, 2) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-12 | 7b9abaf39016 | score (0, 4) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-13 | ffac791f24ec | score (0, 4) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-14 | be4f91ea1749 | score (0, 4) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-15 | b438cb6f1be9 | score (0, 4) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-16 | 862dc5c969dd | score (0, 4) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)
calc__Q39textinput9inputform4BaseFv | calc-conversion-phase-order-17 | 2576056bcbd8 | score (0, 0) instructions 165/165 | POOL IDENTICAL up to 20 (mine=20 base=20)

Accepted Base::calc conversion: fresh full gate PASS; exact-name objdiff 100.0%; ctxdiff 165/165, diffs 0; pool identical; regressions/readability/forbidden 0; DOL correct. Ordinary phase, angle and blue locals plus inline sine/phase helpers reproduce conversion scheduling. Asm bodies 3 -> 2. Shared headers unchanged.
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-0 | dfc2c3928b7b | score (6, 29) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-1 | 79524dce7876 | score (1, 19) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-2 | 6ac603673f04 | score (7, 29) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-3 | de7cfab457b6 | score (1, 13) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-4 | e8c333cd6103 | score (6, 29) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-5 | 8a721e15fd5f | score (1, 19) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-6 | 86f2f41a660b | score (7, 29) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-loop-inline-boundary-7 | 28aa8b233900 | score (1, 13) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-helper-inspect | de7cfab457b6 | score (1, 13) instructions 40/39 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-0 | 1e041c5fef80 | score (30, 44) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-1 | 4f7f7c023d8b | score (30, 41) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-2 | 00e14a2f6393 | score (26, 43) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-3 | 0d019d99741b | score (26, 43) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-4 | 5627486657ea | score (47, 274) instructions 328/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-5 | 8868c258fb15 | score (47, 274) instructions 328/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-6 | 8d4526a2623b | score (43, 274) instructions 328/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-7 | 4031d758a885 | score (43, 274) instructions 328/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-8 | d143733e3881 | score (87, 236) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-9 | b4f2b359a081 | score (87, 236) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-10 | defd99d47ba5 | score (83, 236) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-width-height-staging-11 | 411946c62b40 | score (83, 236) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
init__Q49textinput9inputform4Base14RowInfoManagerFv | rows-sentinel-link-pointer-0 | da8f49bed7c6 | score (0, 0) instructions 39/39 | POOL IDENTICAL up to 20 (mine=20 base=20)

RowInfoManager::init exact source: the inline initialization loop returns its final capacity read; the caller obtains the free sentinel separately, then retains one row-array pointer while linking last/first free rows. This removes the erroneous extra pointer reload after the last-row Next store. All 39 instructions now match.

Accepted RowInfoManager::init conversion: fresh full gate PASS; exact-name objdiff 100.0%; ctxdiff 39/39, diffs 0; pool identical; regressions/readability/forbidden 0; DOL correct; asm bodies 2 -> 1. Shared headers unchanged.
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-0 | e042cd32ef69 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-1 | ade50018c439 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-2 | 599cf4ca313c | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-3 | 49a2bbe294f3 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-4 | 62954c466ad1 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-5 | 91272c7d5545 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-6 | a53d64c51aa3 | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-7 | e39b83eaa20b | score (40, 84) instructions 110/72 | POOL IDENTICAL up to 20 (mine=20 base=20)

Conversion integration check: the full row-init gate passed exact/regression checks, but LayoutByNW4R::create fell from 95.02809% to 84.07865% because MWCC auto-inlined the newly available initializer. Target create explicitly calls RowInfoManager::init. Definition-only never_inline was too late for earlier callers. Added the repository-standard never_inline declaration only for TIINPUTFORM_IMPLEMENTATION inside the existing RowInfoManager guard; the TIMANAGER side retains its original void init declaration. Only this .cpp defines TIINPUTFORM_IMPLEMENTATION. No guard was removed or widened. Fresh full gate follows before committing this boundary correction.

Accepted initializer boundary correction: full gate PASS; LayoutByNW4R::create restored to 352/356 instructions and 95.02809%; RowInfoManager::init still 39/39, diffs 0 and objdiff 100.0%; pool identical, regressions/readability/forbidden 0; DOL correct.
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-0 | e042cd32ef69 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-1 | ade50018c439 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-2 | 599cf4ca313c | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-3 | 49a2bbe294f3 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-4 | 62954c466ad1 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-5 | 91272c7d5545 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-6 | a53d64c51aa3 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-7 | e39b83eaa20b | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-8 | df9472b3186e | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-9 | 6895d3bc27eb | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-10 | 5a0360a632d8 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-11 | 75e599406c64 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-12 | f344d29fa00d | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-13 | ac42aaba75f3 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-14 | 61f231e282c7 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-reference-helper-15 | c8e3540e4959 | score (1, 39) instructions 73/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-0 | f776393f0aed | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-1 | 2b0fb7b0c98b | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-2 | d5215b77be19 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-3 | 44f54d993847 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-4 | 8601c987d6ad | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-5 | 6f1e7633e326 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-6 | 6014399e7ba8 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-leading-ring-locals-7 | 65428f0b90c0 | score (0, 26) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-0 | 4417f7ecc4a2 | score (12, 184) instructions 245/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-1 | b5b75ace0dc1 | score (8, 183) instructions 241/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-2 | 9afb465f5890 | score (12, 22) instructions 237/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-3 | 922960de967b | score (16, 26) instructions 237/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-4 | 149947ecad68 | score (12, 22) instructions 237/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language | language-switch-selector-5 | 4e1574eddac8 | score (34, 250) instructions 256/237 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-0 | 49a0a5720575 | score (42, 59) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-1 | b068c5da5a9b | score (44, 62) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-2 | 3b2c10513378 | score (42, 59) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-3 | fdeede389926 | score (87, 234) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-4 | b5ed4ad23f31 | score (42, 59) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-5 | 05c76f1f77d6 | score (44, 62) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-6 | 17176a8e11bd | score (42, 59) instructions 326/326 | POOL IDENTICAL up to 20 (mine=20 base=20)
calcCursorPos__Q39textinput9inputform4BaseFff | cursorpos-three-value-inline-7 | 93af05e2b2f8 | score (87, 234) instructions 317/326 | POOL IDENTICAL up to 20 (mine=20 base=20)

Base::create register search seed 0:
```text
declaration block:
      Info_* rows;
      Info_* selected;
      u16 previous;
      u16 next;
      u16 selectedIndex;
      Info_* listEnd;
start (0, 26)
improved (0, 25)
improved (0, 22)
improved (0, 20)
best (0, 20) after 57 builds; kept in source:
    u16 previous;
    Info_* listEnd;
    Info_* rows;
    u16 next;
    Info_* selected;
    u16 selectedIndex;
```
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-declsearch-0 | 126621259fa8 | score (0, 20) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)

Base::create register search seed 7:
```text
declaration block:
      u16 selectedIndex;
      Info_* rows;
      Info_* listEnd;
      u16 next;
      Info_* selected;
      u16 previous;
start (0, 25)
improved (0, 24)
improved (0, 22)
improved (0, 20)
best (0, 20) after 52 builds; kept in source:
    u16 previous;
    Info_* rows;
    Info_* listEnd;
    u16 next;
    Info_* selected;
    u16 selectedIndex;
```
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-declsearch-7 | 55560468d892 | score (0, 20) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)

Base::create register search seed 19:
```text
declaration block:
      Info_* selected;
      u16 next;
      u16 previous;
      u16 selectedIndex;
      Info_* rows;
      Info_* listEnd;
start (0, 27)
improved (0, 25)
improved (0, 24)
improved (0, 23)
improved (0, 19)
best (0, 19) after 59 builds; kept in source:
    u16 next;
    Info_* rows;
    Info_* selected;
    u16 previous;
    u16 selectedIndex;
    Info_* listEnd;
```

Remaining source forms after structural trials:
- calcCursorPos: scalar/vector scale forms, direct/inline rectangle extents, height/width temporaries and order were built. No exact C++ candidate; original 326-instruction body retained.
- LayoutByNW4R::create: direct initial root lookup and animation-file slot references recover 356/356 instructions; conditional receiver load timing and register allocation still differ. Restored original body.
- setLanguage: inline name/root selectors, explicit temporaries, duplicate calls, switch/loop/goto forms all built; receiver hoisting or extra branch instructions persist. Restored original body.
- Base::create: circular row helpers and pointer/reference boundaries were built; plain C++ reaches 72/72 with zero structural differences. Declaration searches are the final register-only experiments; no non-exact conversion will be retained.
- Concatenated cache/start symbol remains an eight-byte original symbol spanning two existing C++ members, without an exact-name source counterpart. Renaming or resizing either source/config symbol is forbidden; no trials can legitimately repair its identity.
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer | basecreate-declsearch-19 | 54bad2f75ddf | score (0, 19) instructions 72/72 | POOL IDENTICAL up to 20 (mine=20 base=20)

Final open-function audit, all non-exact trials restored:
calcCursorPos__Q39textinput9inputform4BaseFff: 32 distinct successfully built source variants, pool identical.
create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: 8 distinct successfully built source variants, pool identical.
setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: 12 distinct successfully built source variants, pool identical.
create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: 33 distinct successfully built source variants, pool identical.
Register search total: 168 builds, three distinct initial declaration orders; best C++ Base::create score structural 0 / exact 19, instructions 72/72; restored. Asm bodies 3 -> 1.

Final full clean-build gate PASS. Instruction-exact 214 -> 215; objdiff-exact 216 -> 217; code bytes 45080 -> 46972; data 908 -> 908; asm bodies 3 -> 1. Pool identical, regressions 0, forbidden/readability 0, DOL SHA1 correct. All unaccepted source trials restored.
