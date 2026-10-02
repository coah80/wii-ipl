# iplSetting worker3 — Setting::draw (Oct 2 2026)

Worktree: `/workspace/worktrees/iplSetting-draw`
Branch: `agent/grok/decomp-worker-3/draw`
Unit: `src/scene/setting/iplSetting.cpp` `Setting::draw` only.
`scanAP` / `convertRevIP` source not touched. File stays `NonMatching` (not linked).

## Result

**632/632 byte-identical** to retail (`draw__Q33ipl5scene7SettingFv`, 2528 bytes, 0 diffs).
A HEAD compile of the same TU differs from this object only in `draw`. No sibling codegen change (`-ipa file`).

## Levers that closed it

1. `wideTopL` / `wideTopR` as separate locals (no CSE of the int-to-float). Gets `xoris r6,r6` and `fsubs f2`.
2. One `void* held` is the browser thread, then overwritten by the standard-buffer fetch, so browser and `standardBuffer` share r31.
3. Tex0 material pointer reused as the scroll `FrameController*` (`wideMaterial`), with `initFrame`/`restart` duplicated in each arm.
4. Field copy through `volatile GXRenderModeObj*` so loads and stores interleave on r4/r0.
5. Sample-pattern loop is direct `dst[1]=src[1]; dst[2]=src[2]` with `src` declared before `dst` is assigned (`u8* src; u8* dst = ...; src = ...`).

## Not linked

`configure.py` still has `Object(NonMatching, "scene/setting/iplSetting.cpp")`. DOL SHA1 is unchanged because this TU is not linked. Do not flip the object to Matching until `scanAP` / `convertRevIP` (and the rest of the TU) match.
