# clean3-c2 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/clean3-c2`, branch `agent/w1009/clean3-c2`, baseline `8a67b68cf`.

Scope: eZiText sources and their module headers. Each cleanup must preserve allocated section bytes, sizes and alignments, normalized relocation destinations, and function extents. Rebuild rejected source before the next trial. Commit cleaned files separately and gate all changed units together at the end.

Baseline DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`. Live report has 12563/12563 exact functions and 100% code, data and linking. Global fuzzy is 99.999886; exact-unit gates take priority over that rounded global value.

Read clean3-head.md, cleanup-common.md, AGENTS.md and prior cleanup2-w1 and cleanup-c6 evidence. The cleanup2-w3 and cleanup2-x9 eZiText mentions only describe out-of-scope files; they contain no further eZiText trials. Applied unslop and writing-for-agents to this log.

Skip previously rejected direct engine returns, spelling/punctuation store separation, candidate advances moved to for headers, backward alternate-sound scan rewrites, phonetic-group loop rewrites, and scalar removal of the PUD workspace carrier. New trials target remaining forward guards and exits, preserving existing cursor statements and common cleanup exits.

No function-scoped optimizer pragmas or use-site volatile casts occur in this module. The two volatile locals are checked separately. Temporary snapshots and compiler output live under `/tmp/clean3-c2-baseline`.

## Trials
- KEEP `zi8cinfo` remove volatile extraCount: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8uwd` remove volatile entryLength: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cinfo` Zi8GetSInfo guarded high stroke: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alts` Zi8MatchAltSound bounded backward scan: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard context_phrase_next at line 1257: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard user_character_next at line 1801: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard global_character_next at line 1836: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard component_phrase_next at line 1994: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard component_phrase_charset at line 2008: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard frequency_record_next at line 2078: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard phonetic_pair_next at line 2249: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard next_group_candidate at line 2680: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` forward guard START_PROCESS at line 360: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` forward guard finishCandidates at line 1434: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` forward guard checkPrefixFields at line 1559: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8dawg` forward guard finish_graph at line 33: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8dawg` forward guard descend at line 127: compile failed.
- KEEP `zi8match` forward guard phonetic_skip at line 396: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8match` forward guard check_pinyin_extension at line 482: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8match` forward guard invalid_pinyin at line 487: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8getSW` forward guard end at line 182: allocated sections, resolved relocations and function extents identical.
- REVERT `zkokeyp` forward guard scan_key_table at line 304: compile failed.
- KEEP `zi8alts` forward guard up at line 25: allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` forward guard oemFailed at line 67: allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` forward guard tail0 at line 72: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify inverted negated guards: allocated sections, resolved relocations and function extents identical.
- Trial generator correction: the first descend and scan_key_table drafts inverted the greater-than character in a pointer arrow. Both failed compilation and were restored. The corrected generator leaves pointer arrows intact; retest those equivalent guards.
- KEEP `zi8dawg` forward guard descend at line 127: allocated sections, resolved relocations and function extents identical.
- KEEP `zkokeyp` forward guard scan_key_table at line 304: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8space` forward guard fail at line 79: allocated sections, resolved relocations and function extents identical.
- KEEP `zmtkey` forward guard table_1e at line 71: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard context_phrase_next at line 1259: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard global_character_next at line 1846: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard global_character_next at line 1861: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard component_phrase_next at line 2031: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard next_group_candidate at line 2707: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` forward guard next_group_candidate at line 2709: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` forward guard nextPhrase at line 1490: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` forward guard nextUserOrdinal at line 1625: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` forward guard nextOrdinal at line 1681: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` forward guard nextOrdinal at line 1683: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` forward guard filterVowelCandidate at line 946: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` forward guard finishCandidates at line 1568: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8getSW` forward guard search_syllables at line 130: .text.
- KEEP `zkokeyp` forward guard skip_word at line 388: allocated sections, resolved relocations and function extents identical.
- KEEP `zkokeyp` forward guard skip_word at line 392: allocated sections, resolved relocations and function extents identical.
- KEEP `zkokeyp` forward guard search_table at line 415: allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` forward guard oemFailed at line 68: allocated sections, resolved relocations and function extents identical.
- KEEP `zmtkey` forward guard table_1e at line 72: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` numeric_setup loop break: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` vowel loop break: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` prepareRememberedPunctuation loop break: allocated sections, resolved relocations and function extents identical.
- REVERT `ziswordw` found loop break: .text.
- REVERT `zi8cgetc` phonetic_record_next structured else branch: compile failed.
- KEEP `zi81key` START_PROCESS structured else branch: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8dawg` descend structured else branch: compile failed.
- KEEP `zi8getSW` end structured else branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alts` up structured else branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alts` hi_check structured else branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` matchRetry structured else branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8is` next structured else branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8misc` map structured else branch: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !*spelling || spelling == end: .text.
- REVERT `zi8cgetc` simplify predicate !candidate || !spellingLength: .text.
- REVERT `zi8cgetc` simplify predicate !candidate[index] || candidate[index] != spelling[index]: .text.
- KEEP `zi8cgetc` simplify predicate !Zi8ZHaddSpace(spelling, spellingLength, spacedSpelling, 64, __zi8_work_data): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !Zi8ZHaddSpace(candidate, candidateLength, spacedCandidate, 64, __zi8_work_data): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !ZiPartialMatch(spellingCursor, spacedSpelling + 64,                                 : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !((struct __zi8_work_data_s*)work)->cangjieEnabled || request->elementCount > 6: .text.
- REVERT `zi8cgetc` simplify predicate !index || index + 1 != request->elementCount: .text.
- REVERT `zi8cgetc` simplify predicate !(request->context & 0x10) &&             (elements[request->elementCount - 1] == 0xF: .text.
- REVERT `zi8cgetc` simplify predicate !ordinalCount && getMode == 0 && request->elementCount == 1 && elements[0] == 0xEF00: .text.
- REVERT `zi8cgetc` simplify predicate !Zi8IsCharacter(character, work) || (!emitWords && character == previousOrdinal): .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                 Zi8MatchAlt: .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                            : .text.
- KEEP `zi8cgetc` simplify predicate !(((options->countOnly && getOptions != 5) || !wordLength || getMode == 5 ||         : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !request->elementCount || (getMode == 0 && request->elementCount == 1 && elements[0] : .text.
- KEEP `zi8cgetc` simplify predicate !((currentSpelling[rangeCount] == 0x2C9 && elements[rangeIndex] == 0xF331) ||        : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                         Zi8: .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                     Zi8Matc: .text.
- REVERT `zi8cgetc` simplify predicate !candidateWord[0] || ZiMatchZHSpelling(currentSpelling, candidateWord, request->eleme: .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull && !filteringMode &&          : .text.
- KEEP `zi8cgetc` simplify predicate !(!emitWords && isFirstCandidate == previousOrdinal): allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !request->elementCount && !options->countOnly && request->wordCharCount &&         Zi: .text.
- REVERT `zi8cgetc` simplify predicate !options->countOnly && !ordinalCount && match.nCand <= 1 && match.nSeg <= 1 &&       : .text.
- REVERT `zi8cgetc` simplify predicate !request->elementCount && (getMode == 7 || getMode == 8 || getMode == 9): .text.
- REVERT `zi8cgetc` simplify predicate !options->countOnly && ordinalCount && (getMode == 7 || getMode == 8 || getMode == 9): .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && !((phraseEntry[0] & 7) >= match.length &&                 match.p: .text.
- KEEP `zi8cgetc` simplify predicate !Zi8ExactMatchNextChar(record, match.prefixMasks[0], match.prefixValues[0], match.pre: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !options->countOnly && phoneticRetry && ordinalCount && getMode != 5: .text.
- REVERT `zi8cgetc` simplify predicate !Zi8PriMatchNextChar(record, match.recordMasks[0], match.recordValues[0], match.recor: .text.
- REVERT `zi8cgetc` simplify predicate !options->countOnly && !phoneticRetry && ordinalCount &&         getMode != 7 && getM: .text.
- KEEP `zi8cgetc` simplify predicate !Zi8MatchPhonetic(phoneticTable, records, alternateTable, alternateCount,            : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                         Zi8: .text.
- KEEP `zi8cgetc` simplify predicate !(!candidateStatus && !((phraseEntry[0] & 7) >= match.length &&                      : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !filteringMode || match.nSeg <= 1: .text.
- KEEP `zi8cgetc` simplify predicate !Zi8PriMatchNextChar(record, match.recordMasks[0], match.recordValues[0], match.recor: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !emitWords || request->getMode != 16 || match.nSeg <= 1: .text.
- KEEP `zi8cgetc` simplify predicate !(ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !(duplicateIndex < match.nSeg &&                     (match.segmentValues[duplicateIn: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !Zi8PriMatchNextChar(record, match.recordMasks[0], match.recordValues[0], match.recor: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !(ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !(charsetTable && !(charsetEntry[0] & charsetFilter)): allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !charsetTable || charsetEntry[0] & charsetFilter: .text.
- KEEP `zi8cgetc` simplify predicate !Zi8IsDupWordW(&candidateOrdinal, 1, work): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !Zi8PriMatchNextComp(componentCursor, match.recordMasks[0], match.recordValues[0], ma: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !emitWords && emittedCount < request->maxCandidates && getMode != 5: .text.
- REVERT `zi8cgetc` simplify predicate !frequencyEntry[1] || !frequencyEntry[2]: .text.
- REVERT `zi8cgetc` simplify predicate !frequencyEntry[3] || !frequencyEntry[4]: .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                            : .text.
- REVERT `zi8cgetc` simplify predicate !candidateStatus && (record[0] & 0x80) && !requireFull &&                            : .text.
- KEEP `zi8cgetc` simplify predicate !Zi8IsDupWordW(output + outputIndex, 2, work): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !(ziU8)Zi8NewMatchPhonetic(request, (ZiChineseRecord*)records, alternateTable, altern: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` simplify predicate !Zi8MatchPhonetic(phoneticTable, records, alternateTable, alternateCount,            : allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !emitWords || match.nCand <= 1: .text.
- REVERT `zi8cgetc` simplify predicate !switchedPhonetic || emittedCount >= request->maxCandidates: .text.
- REVERT `zi8cgetc` simplify predicate !totalResults && !request->firstCandidate && getMode == 1 && match.nCand > 1 &&      : .text.
- KEEP `zi8cgetc` simplify predicate !(wordMode && Zi8IsDupWordW(&character, 1, work)): allocated sections, resolved relocations and function extents identical.
- REVERT `zi8cgetc` simplify predicate !wordMode || !(Zi8IsDupWordW(&character, 1, work)): .text.
- KEEP `zi8cgetc` simplify predicate !Zi8MatchPhonetic(phonetics, (ziU8*)records, indexTable, indexCount,                 : allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` simplify predicate !((keyHigh == records[searchIndex].keyHigh) &&             (keyLow == records[searchI: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8alpha` simplify predicate !work->suffixMode || !work->suffixLocked: .text.
- REVERT `zi8alpha` simplify predicate !work->requiredLength || length == work->requiredLength: .text.
- REVERT `zi8alpha` simplify predicate !work->suffixLocked && work->highlightedLanguage > 1: .text.
- KEEP `zi8alpha` simplify predicate !Zi8IsVowel(47, *ending): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` simplify predicate !Zi8IsVowel(88, *ending): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` simplify predicate !(((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->subLanguage !=: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` simplify predicate !((((ZiAlphaOptions*)optionData)->lookupMode != '\0') || ((!completionAllowed && (!cu: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8alpha` simplify predicate !primaryMatched && !secondaryMatched: .text.
- KEEP `zi8alpha` simplify predicate !(!completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && ((ZiAlphaWork*)w: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8alpha` simplify predicate !completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && parameters->elemen: .text.
- KEEP `zi8alpha` simplify predicate !(prefixMode != 0 || prefixLength == 0 || elementCount <= 2 ||           prefixLength: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8dawg` simplify predicate !(count == 1 && mode != 0 && graphTable == 0xe): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8match` simplify predicate !(hasString): allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alts` simplify predicate !((elements + j * 4)[1] == hi && (elements + j * 4)[0] == lo): allocated sections, resolved relocations and function extents identical.
- REVERT `zoemdata` simplify predicate !ZI_WORK->ignoreCase || language == ZI8_LANG_ZH: .text.
- REVERT `zoemdata` simplify predicate !Zi8ChangeCharCase(1, &folded, language, __zi8_work_data) || folded != word[position]: .text.
- KEEP `zoemdata` simplify predicate !(!ZI_WORK->oemMatch(index, word, capacity, ZI_WORK->oemData)): allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` simplify predicate !(length != 1 || !complete || continuation): allocated sections, resolved relocations and function extents identical.
- KEEP `zmtkey` simplify predicate !Zi8MapKeyCode(key, &key, __zi8_work_data): allocated sections, resolved relocations and function extents identical.
- REVERT `zmtkey` simplify predicate !Zi8MapKeyCode(key, &key, __zi8_work_data) || (key >= numKeys): .text.
- KEEP `zi81key` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cinfo` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8dawg` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8match` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8getSW` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8is` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8misc` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zmtkey` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zoemdata` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alts` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zkokeyp` format structured guards and remove extra call parentheses: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cinfo` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8dawg` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8getSW` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.
- KEEP `zkokeyp` preserve existing indentation outside changed scopes: allocated sections, resolved relocations and function extents identical.

Predicate trial review: only whole-condition negations were valid simplification candidates. Drafts that negated an initial operand of a compound condition changed code and were rejected. Redundant parentheses added around single calls were removed in the final format pass. The branch generator also rejected two drafts whose final goto belonged to an unbraced nested if; these were restored, and later trials required a standalone goto statement.
- REVERT `zi8cgetc` remove unused labels: .text, extabindex, resolved relocations, function extents.
- REVERT `zi81key` remove unused labels: .text, extabindex, resolved relocations, function extents.
- REVERT `zi8alpha` remove unused labels: .text, extabindex, resolved relocations, function extents.
- REVERT `zi8match` remove unused labels: .text, extabindex, resolved relocations, function extents.
- REVERT `zi8cinfo` remove unused labels: .text, extab, extabindex, resolved relocations, function extents.
- KEEP `zi8alts` remove unused labels: allocated sections, resolved relocations and function extents identical.
- REVERT `zi8misc` remove unused labels: .text, extabindex, resolved relocations, function extents.
- REVERT `ziswordw` remove unused labels: .text, extabindex, resolved relocations, function extents.
- KEEP `zmtkey` collapse redundant nested scope: allocated sections, resolved relocations and function extents identical.
- Unused-label draft correction: the first label sweep also selected switch default labels. All seven byte-changing drafts were restored. The corrected sweep excludes default and retains every switch arm.
- KEEP `zi8alts` name ordinal and phonetic search locals: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8is` Zi8GetZHCharSet nested candidate alternatives: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8misc` Zi8Uni2Ptr structured range fallback: allocated sections, resolved relocations and function extents identical.
- REVERT `zoemdata` Zi8MatchOEMdata structured retry and fallback loops: .text, extabindex, resolved relocations, function extents.
- KEEP `zi8cgetc` retain readable original PUD and tone predicates: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` final indentation and condition line breaks: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8cgetc` final indentation and condition line breaks: allocated sections, resolved relocations and function extents identical.
- KEEP `zmtkey` final indentation and condition line breaks: allocated sections, resolved relocations and function extents identical.
- KEEP `zi81key` align alternate-sound search branch: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8dawg` retain common exit instead of a broad nested guard: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8alpha` retain common exit instead of a broad nested guard: allocated sections, resolved relocations and function extents identical.
- KEEP `zi8getSW` retain common alpha exit instead of nesting the search: allocated sections, resolved relocations and function extents identical.

## Final source review

Retained common exits in zi8dawg, zi8alpha and zi8getSW rather than nesting most of those functions for a single removed goto. All three restorations preserve the baseline objects. Retained the original PUD eligibility and tone predicates because the expanded inversions were harder to read.

All 30 clib objects compare identical to baseline in allocated bytes, sizes, alignments, resolved relocation destinations and function extents. Removed 54 gotos and both volatile locals. Added no optimizer pragma, asm, carrier, cast workaround, or code comment. No headers changed.

| File | Gotos before | Gotos after |
| --- | --- | --- |
| zi81key.c | 52 | 46 |
| zi8alpha.c | 34 | 29 |
| zi8alts.c | 12 | 6 |
| zi8cgetc.c | 199 | 184 |
| zi8cinfo.c | 12 | 10 |
| zi8dawg.c | 20 | 19 |
| zi8getSW.c | 15 | 14 |
| zi8is.c | 4 | 2 |
| zi8match.c | 18 | 15 |
| zi8misc.c | 2 | 0 |
| zi8space.c | 3 | 2 |
| zi8uwd.c | 7 | 7 |
| zkokeyp.c | 12 | 8 |
| zmtkey.c | 3 | 1 |
| zoemdata.c | 10 | 6 |

Remaining jumps serve shared error/success exits, candidate cursor advances, binary-search transitions, or phonetic/dictionary state transitions. Keep the prior compiler constraints and PUD carrier as documented in cleanup2-w1 and cleanup-c6. The new equivalent OEM retry-loop trial changed text, function extents and extabindex, so its existing retry transitions remain.

## Retained cleanup by file

- zi81key.c: Guard phrase/user/ordinal matches and duplicate characters. Keep binary-search transitions, candidate cursor advances and the stored-initial-character condition.
- zi8alpha.c: Use switch breaks and positive vowel/prefix guards. Simplify the language-eligibility predicate. Keep shared candidate exit, dictionary transitions and punctuation-store constraint.
- zi8alts.c: Use a bounded backward scan and structured binary-search alternatives; name ordinal, cursor and phonetic locals. Keep the two binary-search transitions and shared match entry.
- zi8cgetc.c: Use positive candidate, duplicate, charset and phonetic guards; break the prediction range. Keep shared engine exit and dictionary/phonetic state transitions with their original cursor statements.
- zi8cinfo.c: Remove volatile extraCount; guard high-stroke decoding. Keep the common badStroke error path.
- zi8dawg.c: Guard terminal candidate checks before child traversal. Keep shared finish_graph and sibling/child state transitions.
- zi8getSW.c: Guard the single-key fallback. Keep the common exit and syllable retry/output transitions, including the required forward capacity branch.
- zi8is.c: Use nested alternatives for the three candidate modes. Keep the sublanguage retry transition.
- zi8match.c: Guard phonetic lookup and both pinyin ranges. Keep phonetic group transitions and common invalid-pinyin handling.
- zi8misc.c: Select the two Unicode ranges through structured alternatives; remove both map jumps.
- zi8space.c: Guard the successful output copy. Keep the shared fallback-copy path.
- zi8uwd.c: Remove volatile entryLength. Keep UWD retry/error paths.
- zkokeyp.c: Guard context-word lookup, capacity handling and sibling continuation. Keep matching-word retry and required cursor advances.
- zmtkey.c: Guard the preferred key table; remove an extra nested scope. Keep the common table-ready join.
- zoemdata.c: Guard callback retry and one-character fallback through structured alternatives. Keep OEM retry transitions; the nested-loop alternative changed bytes.

## Final validation

Ran gate.py once with --quick over all 30 clib units, including reverted-trial units. Full 43U build passed. GATE PASS; zero regressions, added forbidden patterns and added readability warnings. Gate output: `/tmp/clean3-c2-gate.log`.

Fresh report: every one of the 30 units has 100% code, data, functions, sections and linking. All 30 compiled objects also equal the initial baseline with normalized relocations. Focused pools for all 15 changed units are identical; ctxdiff for all 19 edited functions gives diffs 0 with equal instruction counts. Focused output: `/tmp/clean3-c2-focused.log`.

Completion checker: DECOMPLETE_OK. Assembly checker: ASM INVENTORY PASS, 162 ORIGINAL functions, 0 PLACEHOLDER. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`. Whitespace check passed. No source changes followed validation.

| Changed unit | Exact functions before and after | Code bytes | Data bytes |
| --- | --- | --- | --- |
| zi81key | 9/9 | 21460/21460 | 1388/1388 |
| zi8alpha | 12/12 | 21664/21664 | 564/564 |
| zi8alts | 1/1 | 1200/1200 | 20/20 |
| zi8cgetc | 8/8 | 47816/47816 | 536/536 |
| zi8cinfo | 10/10 | 10948/10948 | 1848/1848 |
| zi8dawg | 6/6 | 4868/4868 | 120/120 |
| zi8getSW | 1/1 | 1852/1852 | 20/20 |
| zi8is | 3/3 | 1136/1136 | 40/40 |
| zi8match | 10/10 | 8256/8256 | 728/728 |
| zi8misc | 4/4 | 1636/1636 | 80/80 |
| zi8space | 1/1 | 776/776 | 20/20 |
| zi8uwd | 4/4 | 2656/2656 | 80/80 |
| zkokeyp | 7/7 | 5200/5200 | 180/180 |
| zmtkey | 4/4 | 2216/2216 | 60/60 |
| zoemdata | 3/3 | 976/976 | 60/60 |

## Source commits

- `957a39055` libs/RVLMiddleware/eZiText/src/clib/zi81key.c
- `12bdc2a7e` libs/RVLMiddleware/eZiText/src/clib/zi8alpha.c
- `838370954` libs/RVLMiddleware/eZiText/src/clib/zi8alts.c
- `0eb24cad5` libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c
- `8152d3da6` libs/RVLMiddleware/eZiText/src/clib/zi8cinfo.c
- `9482de173` libs/RVLMiddleware/eZiText/src/clib/zi8dawg.c
- `fc8f41798` libs/RVLMiddleware/eZiText/src/clib/zi8getSW.c
- `a6a23be5d` libs/RVLMiddleware/eZiText/src/clib/zi8is.c
- `48605c7b0` libs/RVLMiddleware/eZiText/src/clib/zi8match.c
- `037dad697` libs/RVLMiddleware/eZiText/src/clib/zi8misc.c
- `d3300f748` libs/RVLMiddleware/eZiText/src/clib/zi8space.c
- `4152a2f2c` libs/RVLMiddleware/eZiText/src/clib/zi8uwd.c
- `3eff13e83` libs/RVLMiddleware/eZiText/src/clib/zkokeyp.c
- `3cddf9998` libs/RVLMiddleware/eZiText/src/clib/zmtkey.c
- `330dd0bd7` libs/RVLMiddleware/eZiText/src/clib/zoemdata.c

Each source file was committed separately. No push, PR, merge, rebase, cross-worktree edit or subagent occurred.
