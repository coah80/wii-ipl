# revisit leaf — second-pass evidence (agent/w1007/revisit @ origin/main 29fe1efa)

Scope: iplSDChannelTitle (99.98883), ut_ArchiveFontBase (98.52), lyt_window (99.76),
iplMemoryCardManager (97.88). Post-#834 (linkgap emit gates + .data object names).

## iplSDChannelTitle — all gates landed

Per-TU `IPL_SD_CHANNEL_TITLE_CPP` declared-only gates applied to:
RuntimeTypeInfo.h DynamicCast, iplMathTypes.h VEC3 3-arg ctor, GUIManager.h
(EventHandler setManager/setLatestEventCtrlNo/getLatestEventCtrlNo,
Component setTriggerTarget, PaneComponent setPane/getPane), iplGraphics.h
setOrthoTrans/setOrthoScale, iplSceneBase.h isReady/isResetProcessDone/getParent/
getChild/getNext/getPrev, iplFaderSceneBase.h initCalcNormal/calcCommonAfter,
iplNand.h File::isFinished/checkData, iplInterporation.h HermiteIntp<f32>::get
(nested under IPL_CHANNEL_TITLE_NOVTABLE spec), Rect.h 0-arg ctor
(IPL_SOUND_RECT_OUT_OF_LINE gate), iplGuiManager.h ~PaneManager.
Deleted 2 unreferenced extern "C" trampolines (onTitleButtonEvent/onTitlePaneEvent)
orig lacks. Result: all data sections 100%; .text 99.98883.

### VERIFIED WALL — dtor emission policy (decl-immune)
Residual .text gap = 2 unreferenced weak deleting-dtor bodies
(~FaderSceneBase 88B + ~FrameController 64B) + ~5 dangling no-reloc UNDs
(__vt__LangFile, __vt__SDButtonEventHandlerBase, __vt__FrameController,
mArg/typeInfo syms — symtab noise, no relocs). Orig's TU had these dtors
trivial/implicit: ~SDChannelTitle calls ~Base directly (28 insns), Rect
temporaries carry no dtor calls, so correct forms are `virtual ~X() {}`
inline or NO decl at all. Declaring them out-of-line adds real `bl` calls →
fuzzy dropped 99.98883→99.55799. Implicit/non-virtual variants still emit the
weak bodies AND slightly regress — front-end-level MWCC instantiation drag,
no decl form eliminates it. Remaining fn wall: flushSaveBeforeExit 98.59 —
&smArg materialization register choice (orig r3→scratch r4, mine r4/r5→recv-first);
8+ source forms all shift the home, never to r3.

## ut_ArchiveFontBase — ConstructOpAnalyzeGLGR 92.09 (956B)

20 normalized diffs, insns 116-147 of 239 — issue-order inside the
ready-set around the CalcOffsetSheetFlags/CalcSizeFlagSet scratch math.
Orig hoists lhz 0x1c (sheetGlyphCount) / lhz 0x24 (sheetCount) / lhz 0xe
(dataBlockCount) + lwz 0x4c(r20) into the marshal block.
FAILED variants: decl-order swap of the three u16s (identical 20 diffs —
scheduler ignores decl order); moving ctx->m* tail stores adjacent to the
u16 loads (regressed 20→108, whole-web rotation). Conclusion: pure list-
scheduling tie, same family as before.

## lyt_window — DrawFrame 98.18 (1504B)

376=376 insns. One callee-window permutation: orig numbers the static
flipInfos[] array base early (r21, first materialized at insn 36) pushing
arg webs to r27-r31; mine puts it deepest (r31), args r26-r30. Same web
count (12 callee webs r20-r31 both), identical prologue/epilogue; only the
allocator's numbering differs. Plus a repeated stfsx/fadds store-weave in
the 4 DRAW_QUAD_FOR_FRAME_1 corner blocks.
FAILED variants: scoping polPt/polSize inside the macro (385 insns,
worse); moving texSize decl after polPt/polSize (372 insns, worse).
NOTE: paired-single ops — capstone can't decode psq_*/ps_* insns, so
ndiff.py/disasm_fn.py truncate at the first one; use raw-word diffs.

## iplMemoryCardManager — 8 sub-100 fns all decomposed

- isMoveEnable/isCopyEnable (99.83), update_file_array (99.72),
  getComment (98.94): 0 normalized diffs — pure regname webs.
- isBannerEnable (92.31, 26 insns, 7 diffs) + getBlocks (92.0, 25 insns,
  6 diffs): single diff = `addi r11,r1,0x20` restgpr-setup placement —
  orig emits it at tail (after the full member-chain load), mine hoists
  to slot 11. Folded-return variant (`return icons[slot][mFile..]` no
  locals) emits identical code — scheduler-internal, decl-form insensitive.
  Folded form kept (same output, terser).
- _create_icon (87.55) + create_banner (90.42): `(base+const)+var`
  member-chain regroup — orig computes (&mFileCell + memberOffs) +
  (slot*row + file*0x15C combined index) with `this+0x10EC`/`this+0x110C`
  bases cached in callee regs reused across both GX_TF branches, and
  rematerializes &cell.icon per call (`add r3,...` then `add r24,...`
  post-bl) while mine pins it; marshal order `li r4,0` before `mr r3`
  in orig. FAILED variants: `MCFileCell* cell = &mFileCell[slot][file]`
  (90 insns — MWCC folded the pointer, worse); `mFileCell[0] +
  slot*0x7F + file` flat-index (89 insns — aggressive CSE, worse).
  Same documented mcard2 wall.

All units stay NonMatching — no shims, no flips. Every residual is a
verified allocator/scheduler/emission-policy tie with source-form evidence.
