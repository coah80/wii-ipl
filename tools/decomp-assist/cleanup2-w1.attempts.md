# cleanup2-w1 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d2`, branch `agent/w1009/cleanup2-w1`, baseline `85d653b0`.

Full build before edits passed. All six units have 100% code, data and linking; completion checker returned `DECOMPLETE_OK`. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

Use one function per experiment. Keep changes only when every allocated section, relocation and function extent equals the baseline object. Rebuild reverted source before continuing. Temporary candidate source, objects and build output are in `/tmp/cleanup2-w1-work/`.

The October 4 data-layout notes show that statement order can move extabindex and switch-table relocations under `-opt off -inline off`. Compare the entire object, including those sections. Earlier partial matching logs are historical and do not override the exact baseline.

## Trials

- zi8dawg / Zi8MatchROMdata0-structured-key-loop: reverted; changed .text; relocations differ.
- zi81key / Zi8Get1KeyPressCandidates-sorted-ordinal-continue: reverted; changed ; relocations differ.
- zi81key / Zi8Get1KeyPressCandidates-user-ordinal-continue: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi81key / Zi8Get1KeyPressCandidates-ordinal-continue: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi81key / Zi8Get1KeyPressSpelling-entry-continue: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8cgetc / Zi8NewMatchPhonetic-group-candidate-continue: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8cgetc / Zi8GetElementCount-spaced-element-continue: reverted; changed ; relocations differ.
- zi8match / Zi8GetPyFinal-structured-row-loop: reverted; changed .text, extab, extabindex; relocations differ; function extents differ.
- zi8match / Zi8GetBpmfPhonetic-structured-initial-switch: reverted; changed ; relocations differ.

The initial comparator included generated local symbol names such as `@1362`. Removing labels renumbers them without changing relocation targets. The corrected comparator resolves every defined relocation symbol to its section and offset, and keeps names for external symbols. Rerun the three byte-identical candidates below with this correction.

- zi81key / Zi8Get1KeyPressCandidates-sorted-ordinal-continue-resolved-relocations: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / Zi8GetElementCount-spaced-element-continue-resolved-relocations: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetBpmfPhonetic-structured-initial-switch-resolved-relocations: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyFinal-while-with-row-advance: kept; allocated sections, relocations and function extents identical.
- zi81key / Zi8ZHCheckSpelling-tone-switch-break-continue: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8AlphaGetCandidates-dictionary-retry-continue: reverted; changed .text.
- zi8alpha / Zi8AlphaGetCandidates-retryDictionary-same-loop-continue: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8AlphaGetCandidates-finishDictionaryPass-same-loop-continue: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyFinal-structured-row-match: kept; allocated sections, relocations and function extents identical.
- zi81key / Zi8SpellingPY-remove-local-volatile: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / Zi8GetElementCount-flatten-separator-state: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyFinal-positive-row-match: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8AlphaGetCandidates-highlighted-dictionary-break: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8dawg / Zi8MatchROMdata0-child-or-sibling-branch: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-character-range-break: kept; allocated sections, relocations and function extents identical.
- zi8getSW / Zi8GetSyllablesCandidates-syllable-length-loop: kept; allocated sections, relocations and function extents identical.
- zi8dawg / Zi8MatchROMdata0-capacity-break: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyPhonetic-final-scan-break: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-frequency-candidate-break: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-structured-pud-candidate-loop: kept; allocated sections, relocations and function extents identical.
- zi81key / ZiIsSupportedPhonetic-structured-language-switch: kept; allocated sections, relocations and function extents identical.
- zi81key / Zi8SpellingZY-separate-initial-store: reverted; changed .text.
- zi8alpha / Zi8AlphaGetCandidates-separate-punctuation-store: reverted; changed .text.
- zi8cgetc / zi8InternalGetZH-pud-candidate-continue: kept; allocated sections, relocations and function extents identical.
- zi8getSW / Zi8GetSyllablesCandidates-invert-capacity-exit: reverted; changed .text.
- zi8getSW / Zi8GetSyllablesCandidates-structured-initial-candidate: kept; allocated sections, relocations and function extents identical.
- zi81key / MatchAltSound1Key-remove-fallthrough-goto: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8AlphaGetCandidates-remove-fallthrough-goto: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8MatchPhonetic-structured-node-filter: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyPhonetic-structured-final-match: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyPhonetic-structured-h-initial: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / Zi8NewMatchPhonetic-structured-candidate-skip: kept; allocated sections, relocations and function extents identical.
- zi81key / Zi8Get1KeyPressCandidates-user-ordinal-compound-advances: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi81key / Zi8Get1KeyPressCandidates-ordinal-compound-advances: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8getSW / Zi8GetSyllablesCandidates-structured-syllable-output: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-structured-pud-search-guard: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-structured-pud-ordinal-guard: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / Zi8GetChineseCandidates-direct-engine-returns: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8alpha / Zi8IsVowel-direct-returns: reverted; changed .text; relocations differ; function extents differ.
- zi8alpha / Zi8AlphaGetCandidates-highlighted-switch-loop-exit: kept; allocated sections, relocations and function extents identical.
- zi8getSW / Zi8GetSyllablesCandidates-name-search-state: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8MatchPhonetic-structured-phonetic-group-loop: reverted; changed .text.
- zi8match / Zi8GetPyPhonetic-separate-delimiter-load: kept; allocated sections, relocations and function extents identical.
- zi81key / MatchAltSound1Key-structured-backward-scan: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi81key / MatchAltSound1Key-backward-key-loop: reverted; changed .text.
- The preceding structured-backward-scan draft was invalid because its initial jump sat inside the loop. It failed the object check and was restored. The backward-key-loop trial above tests the complete, equivalent bounded scan.
- zi8match / Zi8GetPyPhonetic-separate-tone-adjustment: kept; allocated sections, relocations and function extents identical.
- zi8match / Zi8GetPyPhonetic-separate-post-tone-delimiter-load: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / zi8InternalGetZH-filtered-switch-match-break: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / remove-unused-labels: kept; allocated sections, relocations and function extents identical.
- zi81key / remove-unused-labels: reverted; compiler failed.
- zi8alpha / remove-unused-labels: kept; allocated sections, relocations and function extents identical.
- zi8cgetc / format-pud-loop-and-document-cursor-constraint: kept; allocated sections, relocations and function extents identical.
- zi8match / format-structured-scans-and-document-group-constraint: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8ChangeWordCase-remove-redundant-work-cast: reverted; changed .text.
- zi81key / document-retained-store-and-cursor-constraints: kept; allocated sections, relocations and function extents identical.
- zi8alpha / document-retained-punctuation-store: kept; allocated sections, relocations and function extents identical.
- zi8dawg / document-retained-key-count-test: kept; allocated sections, relocations and function extents identical.
- zi81key / MatchAltSound1Key-remove-exact-unused-process-label: kept; allocated sections, relocations and function extents identical.
- zi8alpha / Zi8ChangeWordCase-document-retained-field-cast: kept; allocated sections, relocations and function extents identical.
- zi8getSW / document-retained-capacity-branch: kept; allocated sections, relocations and function extents identical.
- zi8dawg / Zi8SyllablesROMdata-return-matched-syllable-length: reverted; changed .text, extabindex; relocations differ; function extents differ.
- zi8alpha / place-retained-cast-note-before-case-branch: kept; allocated sections, relocations and function extents identical.
- zi8getSW / name-syllable-input-key-count: kept; allocated sections, relocations and function extents identical.

## Retained source and final review

The corrected comparator proves every retained change preserves all allocated bytes, relocation destinations and function extents. Failed candidates were rebuilt from the last exact source before the next trial. No compiler pragmas or comma conditions were present in the assigned files. Shared exit paths remain.

- zi8cgetc: PUD search uses a guarded while loop with candidate rejections expressed as continue; character and frequency ranges use break. The filtered switch uses break. The separator state is a scalar. Group-candidate cursor advances remain in the body because moving them into a for header changed code and extabindex. The shared engine-return path remains because direct returns changed code.
- zi81key: removed local volatile, flattened the language switch, used continue for sorted ordinals and break/continue for the tone switch. Kept spelling, user and ordinal cursor tails after both assignment and compound-advance header forms changed code. Separating the initial-character store changed code. The bounded backward-key scan changed code.
- zi8alpha: dictionary retries and pass exits use continue only when the destination is the same enclosing loop. The remaining retry jumps escape nested loops. The highlighted dictionary scan exits its switch and loop with break. Shared vowel returns remain because direct returns changed code. The punctuation store and explicit case-mode cast remain because separate stores and removing the cast changed code.
- zi8match: Pinyin final scanning uses break, a while loop and structured match branches; delimiter loads and tone subtraction are separate statements. BPMF initial cases live in their switch. The group-end jump remains because a do/while group loop changed code.
- zi8dawg: capacity uses break and child/sibling handling uses if/else. The key-count test remains at the shared loop test because hoisting it changed code. An explicit byte return from Zi8SyllablesROMdata added code and changed extabindex, so its existing ABI form remains.
- zi8getSW: initial-candidate and syllable-output branches use if/else, and syllable lengths use a for loop with continue. Search flags, cursors, buffers and numeric labels have descriptive names. The forward capacity branch remains because reversing it changed code.

Deleted unused labels in the affected functions. The first PROCESS-label deletion used an unanchored replacement and also damaged START_PROCESS, so it failed compilation and was restored. The corrected exact-label deletion passes. No inline assembly, new volatile, headers, configuration changes or external actions.

| File | Gotos before | Gotos after | Removed |
| --- | ---: | ---: | ---: |
| zi8cgetc.c | 222 | 199 | 23 |
| zi81key.c | 68 | 52 | 16 |
| zi8alpha.c | 50 | 34 | 16 |
| zi8match.c | 36 | 18 | 18 |
| zi8dawg.c | 23 | 20 | 3 |
| zi8getSW.c | 21 | 15 | 6 |

Removed 82 gotos in total, one volatile qualifier, the one-field separator aggregate, and eight unused labels. Source review and git diff --check passed.
- zi8cgetc / align-pud-word-output-else: kept; allocated sections, relocations and function extents identical.

## Source commits

- zi8cgetc.c: `5c435e80c5b5cd89257186b7c48bb639a6a7949c`
- zi81key.c: `a9f06a6eced58c96a9ce0a81b8f8cf419e55216c`
- zi8alpha.c: `7659885f90830ca4d2c0c2a2a014e7c54949f174`
- zi8match.c: `f1d971bf6a4916c564509b4c7971e1b149b4cc95`
- zi8dawg.c: `a16e82d114dd6b7f0ec64367020b8e81d10c1e0b`
- zi8getSW.c: `e51b7fd004422d1e39e7ab8ef6228836bf0dfd5c`

Pool checks against all six original objects passed, each with zero narrow-string entries. The whole-object comparisons also cover the non-string data.

## Final validation

`gate.py` ran once with all six units and `--quick`, as required by the cleanup brief. Full build passed. Every owned section, all 46 functions, all code/data and linking measures are 100%. Regressions, added forbidden patterns and added readability warnings are all zero.

- zi81key: functions 9/9, code 21460/21460, data 1388/1388, fully linked.
- zi8alpha: functions 12/12, code 21664/21664, data 564/564, fully linked.
- zi8cgetc: functions 8/8, code 47816/47816, data 536/536, fully linked.
- zi8dawg: functions 6/6, code 4868/4868, data 120/120, fully linked.
- zi8getSW: functions 1/1, code 1852/1852, data 20/20, fully linked.
- zi8match: functions 10/10, code 8256/8256, data 728/728, fully linked.

Fresh ctxdiff on all 18 touched functions returned equal instruction counts and `diffs 0`. The report was regenerated after the gate.

```
GATE PASS
regressions vs baseline: 0
forbidden patterns added: 0
readability warnings added: 0
DECOMPLETE_OK
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
```

Full gate output: `/tmp/cleanup2-w1-work/gate.log`. No source edits followed the gate.
