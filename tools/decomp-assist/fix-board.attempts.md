# Fix-board block matching attempts

Target 43U. Entry e34eac26. No linking/configuration change. Instruction deficit means target count minus built count; a negative value means extra built instructions. A zero net deficit does not establish matching basic blocks.

The retained sequence is recorded in local commits. All other trials were restored. A trial had to reduce the absolute instruction deficit and avoid lowering its function score. Exact function/code/data totals did not rise.

| Retained region | Function | Instructions before -> after | Score before -> after | Commit |
| --- | --- | --- | --- | --- |
| halfword wait counter | AOSS_Init_old | 1494 -> 1501 / 1584 | 73.85038 -> 73.88826 | 3575e66c |
| protocol dispatch switch | AOSS_Init_old | 1501 -> 1503 / 1584 | 73.88826 -> 74.91351 | 0c6c08a9 |
| protocol error switch | AOSS_Init_old | 1503 -> 1504 / 1584 | 74.91351 -> 75.635735 | ceac978b |
| maximum candidate width | Zi8AlphaGetCandidates | 3980 -> 3966 / 3946 | 85.829956 -> 86.021034 | ceac978b |
| layout record comparisons | Zi8AlphaGetCandidates | 3966 -> 3965 / 3946 | 86.021034 -> 86.14293 | 50b586a4 |
| layout dispatch before loop | Zi8AlphaGetCandidates | 3965 -> 3962 / 3946 | 86.14293 -> 86.34516 | 81e08d61 |
| separate halfword retry delay | AOSS_Init_old | 1504 -> 1509 / 1584 | 75.635735 -> 76.106064 | f4e315a3 |
| shortest/longest native bytes | Zi8AlphaGetCandidates | 3962 -> 3959 / 3946 | 86.34516 -> 86.44374 | f4e315a3 |
| retry cursor subtraction | Zi8AlphaGetCandidates | 3959 -> 3957 / 3946 | 86.44374 -> 86.704765 | 95d966f2 |
| helper cursor subtraction | Zi8AlphaGetCandidates | 3957 -> 3952 / 3946 | 86.704765 -> 86.89838 | fec7b6df |
| dictionary count subtraction | Zi8AlphaGetCandidates | 3952 -> 3949 / 3946 | 86.89838 -> 87.00405 | fad9ac1f |
| direct protocol retry halfword | AOSS_Init_old | 1509 -> 1510 / 1584 | 76.106064 -> 76.132576 | fad9ac1f |

## Exhaustion audit

Basic blocks and all unequal call-aligned regions are in fix-board.block-map.md. The large paired spans are reordered blocks, not proof of missing paths. Missing instructions are assessed together with the target's calls, references, and successor branches.

| Function | Open region families | At least three distinct trials |
| --- | --- | --- |
| AOSS_Init_old | aligned frame, saved registers | init.frame.1..4 |
| AOSS_Init_old | initial stores/options | init.setup.1..4 |
| AOSS_Init_old | scan/allocation order | init.scan.1..3 |
| AOSS_Init_old | connection counters and all repeated waits | init.counters.1..3; init.wait.1..5 |
| AOSS_Init_old | socket error path | init.socket.1..3 |
| AOSS_Init_old | request identities/nonce | init.record.1..3 |
| AOSS_Init_old | packet address stores | init.address.1..4 |
| AOSS_Init_old | protocol dispatch | init.dispatch.1..3 |
| AOSS_Init_old | timeout arithmetic/stores | init.poll.1..3 |
| AOSS_Init_old | cleanup/result branches | init.cleanup.1..3 |
| AOSS_81401778 | entry/global references and saved base | hello.globals.1..3 |
| AOSS_81401778 | CRC constant propagation and instruction scheduling | hello.crc.1..3 |
| AOSS_81401778 | permutation update/load/store blocks | hello.rc4.1..3 |
| AOSS_81401778 | packet finalization/send | hello.packet.1..3 |
| Zi8AlphaGetCandidates | entry frame/normalization/workspace | zi.entry.1..3 |
| Zi8AlphaGetCandidates | language/highlighted-word selection | zi.language.1..3 |
| Zi8AlphaGetCandidates | prefix/suffix preparation | zi.prefix.1..3 |
| Zi8AlphaGetCandidates | dictionary selection | zi.dictionary.1..3 |
| Zi8AlphaGetCandidates | apostrophe/vowel filtering | zi.apostrophe.1..3 |
| Zi8AlphaGetCandidates | punctuation paths | zi.punctuation.1..3 |
| Zi8AlphaGetCandidates | matching helper widths/lengths | zi.match.1..4 |
| Zi8AlphaGetCandidates | candidate output/duplicate cursors | zi.output.1..3; zi.zero.1..3 |
| Zi8AlphaGetCandidates | layout matching loops | zi.layout.1..3 |
| Zi8AlphaGetCandidates | candidate emission | zi.emit.1..3 |
| Zi8AlphaGetCandidates | prefix/language retry | zi.retry.1..3 |
| Zi8AlphaGetCandidates | final output/dictionary counts | zi.finish.1..3 |
| Zi8ChangeWordCase | selector lifetime/loop/register allocation | zi.case.1..3 |
| AOSS_81400830 | byte operands/permutation/CRC traversal | aoss.decrypt.1..3, plus prior AOSS.attempts.md |
| AOSS_814013AC | flags lifetime/state type/view evaluation | aoss.options.1..3 |
| AOSS_81401E80 | byte XOR operands/type | aoss.xor.1..3 |

## Unresolved evidence

- AOSS_Init_old has a 32-byte aligned target frame of 0x160 and saves r14..r31. The accepted source has an ordinary frame. All four alignment trials reduced the size gap but lowered the score and were reverted.
- The target reads r14 at 813FEC9C before any assignment within the function. The current constant initialization collapses this error path. The three safe status-source hypotheses produced extra initialization/global loads absent from the target. None was kept; no uninitialized value was introduced.
- At 813FEDD0..813FEDDC the target initializes packet address word four from settings.gatewayAddress. The source's gateway local is unused. Four direct/typed publication trials recovered that store but lowered 76.132576 to 76.12563, so the requested nondecreasing-score rule required reverting them.
- AOSS polling still lacks target stores/partial quotient calculations. The direct 64-bit timeout formal improved the score but enlarged the net deficit. Full-width multiplication enlarged arithmetic beyond target 32-bit products; neither was retained.
- Hello still has different global-base lifetimes and CRC constant folding, with 270/273 instructions. No inline assembly, forced data, or global-label aliases were added.
- Zi8AlphaGetCandidates still omits the target's unused workspace snapshot at stack 0x20. No placeholder was added. Its early dictionaryIndex initialization is retained so early exits use initialized values. Corresponding scalar offsets, result copies, and reordered retry blocks remain open.
- zi.match.4 reached 3946/3946 instructions but lowered 87.00405 to 86.92727. It was reverted. Instruction count alone was not accepted.
- aoss.decrypt.1 initially failed to compile because the added byte locals followed statements in a C89 block. The failed trial was restored. The prior AOSS.attempts.md has three compiling trials for this same open function; this run also measured signed traversal and preincrement forms.
- Two earlier setup/dispatch trial forms failed to compile and were replaced by compiling, distinct forms under the same labels. Failed forms are not counted in the region audit.
- Zi8WCharCount's source definition returns ziU32. A local-prototype correction was tested; the explicit halfword conversion left output unchanged, so it was not kept as a matching improvement.

## Measured trials

Each row was built only as its owned object, then measured with a fresh objdiff report. Repeated label rows are re-alignments after intervening accepted changes. Other open functions remained at their entry score unless explicitly listed.

| Trial | Function | Built/target instructions | Deficit | Fuzzy percent |
| --- | --- | --- | ---: | ---: |
| init.frame.1 settings aligned 32 | AOSS_Init_old | 1551/1584 | +33 | 68.87689 |
| init.frame.2 address array aligned 32 | AOSS_Init_old | 1551/1584 | +33 | 68.87689 |
| init.frame.3 poll descriptors aligned 32 | AOSS_Init_old | 1551/1584 | +33 | 68.88194 |
| init.scan.1 IP configuration error before allocation | AOSS_Init_old | 1494/1584 | +90 | 74.73232 |
| hello.crc.1 counted eight-byte loop instead of explicit unrolling | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| init.poll.1 named timeval pair stores | AOSS_Init_old | 1494/1584 | +90 | 74.73232 |
| init.poll.2 real 64-bit timeout formal | AOSS_Init_old | 1493/1584 | +91 | 75.02967 |
| init.poll.3 full-width clock products before summing | AOSS_Init_old | 1503/1584 | +81 | 74.87058 |
| hello.crc.2 signed accumulator with unsigned shift | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| hello.crc.3 cursor CRC traversal | AOSS_81401778 | 234/273 | +39 | 77.08059 |
| init.wait.1 halfword countdown and connection counter | AOSS_Init_old | 1501/1584 | +83 | 73.88826 |
| init.wait.2 all sleep countdowns use halfwords | AOSS_Init_old | 1510/1584 | +74 | 73.6452 |
| init.wait.3 explicit low-halfword retry load and narrow decrement | AOSS_Init_old | 1504/1584 | +80 | 73.53283 |
| init.counters.1 full-width connection attempt locals | AOSS_Init_old | 1498/1584 | +86 | 73.93434 |
| init.counters.2 unsigned halfword attempt locals | AOSS_Init_old | 1501/1584 | +83 | 73.579544 |
| init.counters.3 target-order signed retry comparisons | AOSS_Init_old | 1501/1584 | +83 | 73.907196 |
| init.setup.1 named connection and response defaults | AOSS_Init_old | 1501/1584 | +83 | 73.88826 |
| init.setup.2 unsigned word wait union with named signed fields | AOSS_Init_old | 1501/1584 | +83 | 73.88826 |
| init.setup.3 initialize request records as aggregate | AOSS_Init_old | 1503/1584 | +81 | 73.117424 |
| init.socket.1 carry initial IP setup status instead of constant | AOSS_Init_old | 1522/1584 | +62 | 75.42298 |
| init.socket.2 carry initial connection result into socket guard | AOSS_Init_old | 1522/1584 | +62 | 75.16225 |
| init.socket.3 guard with checked socket result | AOSS_Init_old | 1520/1584 | +64 | 75.21717 |
| init.scan.2 allocation failure before success | AOSS_Init_old | 1501/1584 | +83 | 74.40594 |
| init.scan.3 access-point result switch | AOSS_Init_old | 1503/1584 | +81 | 72.66161 |
| init.dispatch.1 state switch in protocol order | AOSS_Init_old | 1503/1584 | +81 | 74.91351 |
| init.dispatch.2 dispatch switch reversed successful cases | AOSS_Init_old | 1503/1584 | +81 | 74.91351 |
| init.cleanup.1 direct returns for every cleanup error | AOSS_Init_old | 1501/1584 | +83 | 73.88826 |
| init.cleanup.2 signed return-code local | AOSS_Init_old | 1501/1584 | +83 | 73.88826 |
| init.cleanup.3 switch protocol errors in target order | AOSS_Init_old | 1502/1584 | +82 | 74.61048 |
| hello.globals.1 named runtime pointer at function entry | AOSS_81401778 | 270/273 | +3 | 84.56044 |
| hello.globals.2 packet nonce pointer borrowed after random nonce | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| hello.globals.3 final runtime address pointer scoped to send block | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| hello.rc4.1 schedule indices published as calculated | AOSS_81401778 | 270/273 | +3 | 82.91209 |
| hello.rc4.2 walk actual encrypted-data array | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| hello.rc4.3 load input byte before key byte | AOSS_81401778 | 270/273 | +3 | 86.59707 |
| hello.packet.1 compute send length immediately before sending | AOSS_81401778 | 269/273 | +4 | 85.24176 |
| hello.packet.2 native unsigned payload length throughout | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| hello.packet.3 success-first encrypted identity branch | AOSS_81401778 | 270/273 | +3 | 86.67033 |
| init.dispatch.3 saved socket argument before ordered dispatch | AOSS_Init_old | 1503/1584 | +81 | 74.91351 |
| init.dispatch retained state switch | AOSS_Init_old | 1503/1584 | +81 | 74.91351 |
| init.cleanup retained error switch after ordered dispatch | AOSS_Init_old | 1504/1584 | +80 | 75.635735 |
| zi.output.1 avoid repeated max-word-length narrowing | Zi8AlphaGetCandidates | 3966/3946 | -20 | 86.021034 |
| zi.output.2 subtract prefix from case and duplicate cursors | Zi8AlphaGetCandidates | 3967/3946 | -21 | 85.950584 |
| zi.layout.1 key-layout record length comparison target order | Zi8AlphaGetCandidates | 3965/3946 | -19 | 86.127975 |
| zi.layout.1 isolated target order | Zi8AlphaGetCandidates | 3965/3946 | -19 | 86.14293 |
| zi.output.3 total word length compared before maximum | Zi8AlphaGetCandidates | 3965/3946 | -19 | 86.144196 |
| zi.layout.2 emit duplicate-check dispatch before layout loops | Zi8AlphaGetCandidates | 3962/3946 | -16 | 86.34516 |
| init.wait.4 retry countdown halfwords after dispatch fixes | AOSS_Init_old | 1513/1584 | +71 | 75.58207 |
| init.wait.5 separate halfword retry delay from IP address | AOSS_Init_old | 1509/1584 | +75 | 76.106064 |
| zi.emit.1 native shortest and longest byte fields | Zi8AlphaGetCandidates | 3959/3946 | -13 | 86.44374 |
| zi.match.1 native minimum word length byte field | Zi8AlphaGetCandidates | 3963/3946 | -17 | 86.54384 |
| zi.prefix.1 native prefix and suffix byte counts | Zi8AlphaGetCandidates | 3959/3946 | -13 | 86.44374 |
| zi.layout.3 native layout and character byte loop bounds | Zi8AlphaGetCandidates | 3959/3946 | -13 | 86.44374 |
| zi.emit.2 suffix emission restores prefix with subtraction | Zi8AlphaGetCandidates | 3958/3946 | -12 | 86.40117 |
| zi.retry.1 prefix retry restores cursors with subtraction | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.zero.1 terminate prefix-relative output through subtraction | Zi8AlphaGetCandidates | 3959/3946 | -13 | 86.202484 |
| zi.case.1 selector initialized separately on every branch | Zi8ChangeWordCase | 46/44 | -2 | 89.86364 |
| zi.case.2 case-mode switch with ordinary integer selector | Zi8ChangeWordCase | 48/44 | -4 | 74.88636 |
| zi.case.3 advance word cursor in loop update | Zi8ChangeWordCase | 44/44 | +0 | 94.545456 |
| zi.entry.1 typed workspace for field reads | Zi8AlphaGetCandidates | 3958/3946 | -12 | 85.99265 |
| zi.entry.2 cast unsigned input loop bounds to native integer | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.entry.3 increment input normalization indices in loop updates | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.prefix.2 prefix lengths use signed comparisons in target order | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.6997 |
| zi.prefix.3 append prefix and suffix through output cursors | Zi8AlphaGetCandidates | 3972/3946 | -26 | 84.43107 |
| zi.dictionary.1 native signed dictionary loop bounds | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.dictionary.2 initialize exact-length state before selecting dictionary | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.61125 |
| zi.dictionary.3 unsigned dictionary-kind dispatch value | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.match.2 minimum word length in target operand order | Zi8AlphaGetCandidates | 3953/3946 | -7 | 86.59858 |
| zi.match.3 real wide-character-count helper return type | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.emit.3 candidate-count bound uses native halfword field | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.70603 |
| zi.zero.2 output terminator indexes explicit prefix start | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.543335 |
| zi.zero.3 case and duplicate helper arguments subtract prefix directly | Zi8AlphaGetCandidates | 3952/3946 | -6 | 86.89838 |
| zi.retry.2 signed workspace prefix comparisons | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.72453 |
| zi.retry.3 alternate-prefix loop uses native count field | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.finish.1 update count loop with predecrement | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.finish.2 compute dictionary counts with compound subtraction | Zi8AlphaGetCandidates | 3954/3946 | -8 | 86.76736 |
| zi.finish.3 native dictionary-index comparisons | Zi8AlphaGetCandidates | 3957/3946 | -11 | 86.704765 |
| zi.zero retained subtracting helper cursors | Zi8AlphaGetCandidates | 3952/3946 | -6 | 86.89838 |
| zi.finish retained compound dictionary count subtraction | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00405 |
| init.setup.4 publish protocol retry option directly into high halfword | AOSS_Init_old | 1510/1584 | +74 | 76.132576 |
| zi.match.4 minimum-length comparison after cursor fixes | Zi8AlphaGetCandidates | 3946/3946 | +0 | 86.92727 |
| zi.language.1 boolean alternate single-character condition | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.002785 |
| zi.language.2 primary language selected before boolean flags | Zi8AlphaGetCandidates | 3949/3946 | -3 | 86.886215 |
| zi.language.3 compact phonetic-language switch | Zi8AlphaGetCandidates | 3939/3946 | +7 | 86.34744 |
| zi.apostrophe.1 increment index with compound assignments | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00405 |
| zi.apostrophe.2 equivalent last-position apostrophe guard | Zi8AlphaGetCandidates | 3949/3946 | -3 | 86.95337 |
| zi.apostrophe.3 native unsigned phonetic filter comparisons | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00228 |
| init.address.1 retain gateway as packet word four | AOSS_Init_old | 1512/1584 | +72 | 76.12563 |
| zi.punctuation.1 cursor increment uses ordinary postfix update | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00405 |
| zi.punctuation.2 signed test for key character upper bound | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00405 |
| zi.punctuation.3 assign punctuation output then test stored character | Zi8AlphaGetCandidates | 3949/3946 | -3 | 87.00405 |
| init.address.2 publish named gateway temporary into packet word four | AOSS_Init_old | 1512/1584 | +72 | 76.12563 |
| init.address.3 initialize IP before gateway in packet address array | AOSS_Init_old | 1512/1584 | +72 | 76.12563 |
| init.address.4 typed address record with gateway field | AOSS_Init_old | 1512/1584 | +72 | 76.12563 |
| init.frame.4 request identity array aligned as target stack offset | AOSS_Init_old | 1557/1584 | +27 | 72.203285 |
| init.record.1 request records indexed with typed pointer | AOSS_Init_old | 1508/1584 | +76 | 76.35669 |
| init.record.2 nonce narrowed immediately at random return | AOSS_Init_old | 1510/1584 | +74 | 76.132576 |
| init.record.3 input identity copied through typed array field | AOSS_Init_old | 1508/1584 | +76 | 76.35669 |
| aoss.decrypt.2 signed permutation traversal index | AOSS_81400830 | 321/321 | +0 | 97.0405 |
| aoss.decrypt.3 checksum byte walk uses preincrement | AOSS_81400830 | 321/321 | +0 | 97.0405 |
| aoss.options.1 accumulated flags initialized after length check | AOSS_814013AC | 114/114 | +0 | 96.97369 |
| aoss.options.2 unsigned protocol state for table indexing | AOSS_814013AC | 114/114 | +0 | 98.77193 |
| aoss.options.3 network view calculated after all config views | AOSS_814013AC | 114/114 | +0 | 98.77193 |
| aoss.xor.1 update packet bytes with compound XOR | AOSS_81401E80 | 147/147 | +0 | 98.23129 |
| aoss.xor.2 byte key mask loaded before input XOR | AOSS_81401E80 | 147/147 | +0 | 98.57143 |
| aoss.xor.3 separate word-width XOR before narrowing store | AOSS_81401E80 | 147/147 | +0 | 98.605446 |
