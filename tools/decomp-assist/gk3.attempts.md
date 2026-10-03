# gk3 MAX structural and sibling-idiom round

2026-10-03T02:41:57.184346+00:00

HEAD 20ba34a80f9d0a09c4a8fad51352f0dd97d84be0; origin/main 20ba34a80f9d0a09c4a8fad51352f0dd97d84be0.

Owned sources: src/scene/address/iplAddress.cpp, src/scene/address/iplAddressEdit.cpp, src/scene/cardSequence/iplCardSequence.cpp; config/43U/symbols.txt only if proven metadata correction is needed. Matching only; no configure.py or linking changes.

Acceptance: pool preserved, exact-name objdiff and instruction-exact gains, no regressions/forbidden or readability patterns, full non-quick gate across all three units, correct DOL SHA1; commit every passing improvement. All remaining functions require three distinct source-level attempts with matched sibling references first.

Baseline objdiff exact functions/code/data: Address 98/101, 21856/23988, 1964/1964; AddressEdit 91/94, 23344/27112, 2560/2560; CardSequence 27/30, 4168/9852, 1496/1496. All assigned data already 100%; no missing-name or extent correction indicated. Reference index has no entries for the assigned units. All three pools identical.

## Address::start_drag_event
Fresh origin fetch: assigned source unchanged. Target and ours both 223 instructions/frame 0x40, only seven icon/pane register differences. Matched sibling AddressEdit::nigaoe_create_callback_edit uses a named Pane and a texture accessor; Address::MiiObj::create_callback uses a typed MiiObj receiver and getIconTexture. Using those idioms before declaration search; reference index has no hit. No overlap in symbol extent.

- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | read-only nigaoe pointer for const texture/image accessors: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | typed MiiObj reference shared by texture access and reset: 223/223 instructions; structural/exact (4, 50); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | explicit root pane lookup used by exact movePane_onDrag: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | named const texture reference following matched callback accessor idiom: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | named image pointer for memcpy using matched pointer-local idiom: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | pane lookup through named layout reference: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | named root pane boundary mirroring exact scene construction: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | named material receiver mirroring matched MiiObj callback: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | explicit root with const texture reference boundary: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | single-use inline texture installation with const object reference: BUILD FAILED, reverted. ive2\projects\wii-ipl-workers\data- #   d4\src\scene\address\iplAddress.cpp:6) ### mwcceppc.exe Compiler: #    File: src\scene\address\iplAddress.cpp # ----------------------------------------- #    1174:                 nw4r::lyt::Pane* miiPane = address.mpLayout->FindPaneByName("mii_move");  #   Error:                                                            ^^ #   (10412) illegal access from 'ipl::scene::Address' to protected/private  #   member 'ipl::scene::Address::mpLayout' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.

## Address::onEventDerived
Fetched origin; source unchanged there. Both 270 instructions, frame 0x30; remaining differences are saved register assignments. Matched sibling AddressAddSel::onEventDerived and MailAddressSelect::onEventDerived split PaneComponent from name lookup; matched AddressEdit::onEventDerived also names manager and pane. Branch structure and string order already correct; no extent overlap/reference-index hit.

- onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface | matched sibling PaneComponent local boundary: 270/270 instructions; structural/exact (0, 81); pool identical; exact regressions []; reverted.
- onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface | matched AddressEdit manager/component/pane lookup boundaries: 270/270 instructions; structural/exact (0, 81); pool identical; exact regressions []; reverted.
- onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface | named animator reuse and initFrame/restart used by exact AddressEdit states: 270/270 instructions; structural/exact (0, 81); pool identical; exact regressions []; reverted.

Address::onEventDerived register-only last: official declsearch --score-only structural 0 exact 81. No independent leading declaration block to permute safely. Restored baseline after three sibling-based attempts.

## FriendListCache::update
Fresh origin fetch; source unchanged. Target 40 instructions/0x20 frame, ours 39/0x20. Target recomputes mInfos[index] after wcsncpy; ours retains a record pointer in r31. Exact sibling FriendListCache::add recalculates direct mInfos[index] for writeFriendInfo after memcpy. No pool/data issue or extent overlap/reference-index hit.

- update__Q33ipl5scene15FriendListCacheFUlPCwUx | direct member-array access matching exact FriendListCache::add: 38/40 instructions; structural/exact (7, 33); pool identical; exact regressions []; reverted.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx | read-only cache view for name and update-info accessors: 39/40 instructions; structural/exact (2, 11); pool identical; exact regressions []; reverted.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx | named manager followed by const record accessor as in cache init: 39/40 instructions; structural/exact (2, 11); pool identical; exact regressions []; reverted.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx | const accessor for name but direct member address for update, matching add: 39/40 instructions; structural/exact (4, 19); pool identical; exact regressions []; reverted.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx | direct writable name with const accessor only for final update: 39/40 instructions; structural/exact (10, 32); pool identical; exact regressions []; reverted.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx | explicit signed friend index in final member lookup: 40/40 instructions; structural/exact (0, 0); pool identical; exact regressions []; retained for gate.

## AddressEdit::create
Fresh origin fetch, source unchanged. Target 820 instructions versus ours 818, frame 0x50. Constant text-pool base and board file use swapped saved registers; tail has argument-load order and two lost conditional margin loads because source creates margin locals before new. Exact sibling Address::create and AddressAddSel::create use getSceneHeap and natural constructor arguments; exact AddressEdit::stt_wait_decide_anm names animator/text receivers. TextBalloon construction idiom from siblings will be compared. No pool/extent/reference-index issue.

- create__Q33ipl5scene11AddressEditFv | literal margins in new constructor, matching target conditional argument evaluation: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | literal margins plus direct getSceneHeap used by exact sibling create: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | named board receiver before layout file accessor, sibling scene idiom: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.

FriendListCache::update exact result: final signed native mInfos subscript prevents MWCC retaining the earlier const accessor result across wcsncpy, matching the target repeated 0x140 multiply. Uses the same member array as exact add, with signed indexing consistent with getInfo(int). 40/40 instructions, ctxdiff diffs 0. Quick three-unit gate PASS, zero regressions/forbidden/readability warnings; data remains exact.
Baseline instruction-exact counts freshly measured: Address 97/101, AddressEdit 91/94, CardSequence 27/30. Address objdiff count is 98, one existing objdiff-exact stream is not instruction-exact.
AddressEdit::create note correction: frame is 0x60, not 0x50; direct literal margins dropped saved floats and grew the structural mismatch. Exact SDButton::create confirms the direct-literal idiom but our target retains saved margins across the position constructor.

Full non-quick three-unit gate 1: GATE PASS; DOL 26116613f624061ba99c8d1a299aaa6efa85670d; zero regressions/forbidden/readability warnings; Address code 22016/23988, objdiff 99/101, instruction-exact 98/101, data 1964/1964. Other owned units unchanged. Gate log /tmp/gk3.gate2.log.
The baseline objdiff/instruction count discrepancy is AddressEvent::onEvent: odiff interprets the first condition-register operand of two beq instructions as a branch immediate, yielding source-offset-dependent false instruction differences. Objdiff remains 100%; no source change warranted.
- create__Q33ipl5scene11AddressEditFv | TextBalloon default margin arguments before VEC3 evaluation: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | default margin constructor plus exact sibling getSceneHeap spelling: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | default margins with heap-before-manager creation arguments as target loads: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.

## AddressEdit::get_friendinfo
Fresh origin fetch; assigned source unchanged. Target 84/ours 82 instructions, both frame 0x420. Target holds name/display-text member addresses across FindPaneByName virtual calls, ours computes them after. Matched local idiom is AddressEdit::create mode 0 and exact stt_add_name_fadein/stt_wait_decide_anm, which bind text and Pane before set_textbox. Matching add_friendinfo also binds typed source/destination. No pool/extent/reference-index issue.

- get_friendinfo__Q33ipl5scene11AddressEditFv | name/display pointer lifetimes across pane lookup matching scene text idiom: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | typed record-copy input and destination boundaries with named text pointers: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | named friend index and cache before copy, keeping text accessor lifetimes: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.

## AddressEdit::update_friendinfo
Fresh origin fetch, assigned source unchanged. 38/38 instructions and 0x10 frame, only wcsncpy source/destination address instruction order differs. Exact add_friendinfo creates const name and writable storedName locals in that order. Porting that source-evaluation idiom; no pool/data/extent/reference-index issue.

- update_friendinfo__Q33ipl5scene11AddressEditFv | named source and destination matching exact add_friendinfo: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | read-only String view for source alias and load ordering: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | typed global friend-info reference plus const name pointer: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.

Accessor-boundary reconstruction: trying guarded read-only String getName/getDisplayText helpers, matching existing getDispCodeLong and Address::getInfo getter style. Header guard affects only AddressEdit CPP. Pure member-address temporaries alone were sunk after virtual calls; inline accessor return lifetimes may recover the two target saved addresses.

- get_friendinfo__Q33ipl5scene11AddressEditFv | const inline String accessor return across pane lookup: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | mutable inline String receiver with const returned text: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | const inline name getter in wcsncpy argument, matching accessor evaluation idiom: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | explicit first element address for stored UTF16 name: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | explicit source first element address in wcsncpy: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | ordinary wide pointer cast spelling as in matching FriendListCache update: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.

## cardThreadMain
Fresh origin fetch; owned source unchanged. Target/ours 301 instructions, frame 0x130. Structural mismatch is validity response packing order plus many register assignments. Exact matched siblings probeCard and sendCardSlotState use OSMessage, typed slot/command extraction, queue locals and a union packet; clearAllCardFileEntries uses a signed do/while index. Matched index checked: all are 100. No pool/data/extent/reference-index issue.

- cardThreadMain | native OSMessage receive/storage matching exact probeCard: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- cardThreadMain | queue local before union field assembly matching exact sendCardSlotState: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- cardThreadMain | signed do/while mounted-file scan following exact clearAllCardFileEntries: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- cardThreadMain | union packet-return helper evaluated in message argument, exact sendCardSlotState idiom: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- cardThreadMain | const by-value packet parameters for read-only response view: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- cardThreadMain | explicit low-byte command mask before validity bitfield insertion: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.

## loadCardFileIcons
Fresh origin fetch; source unchanged. Target 512 instructions/frame 0x60, ours 508/frame 0x60. Structural differences include image/comment error joins, signed icon-array indexing and saved-register allocation. Exact matched refreshCardSlotInfo uses native u32 sector-size locals, checkCardFileDuplicate uses typed CARDDir and signed file loops, clearAllCardFileEntries uses signed do/while. Matched MemoryCardManager icon_set uses a const IconState* read-only view. Target keeps the previous palette byte count for reserved format 3; first-format-3 appears to read an unspecified incoming register. No uninitialized C local will be introduced. All 1496 data bytes exact; pool/extent/reference-index checks clean.

- loadCardFileIcons | const CARDDir input matching read-only icon metadata view: 505/512 instructions; structural/exact (103, 431); pool identical; exact regressions []; reverted.
- loadCardFileIcons | native unsigned sector size outputs matching exact refreshCardSlotInfo: 508/512 instructions; structural/exact (66, 436); pool identical; exact regressions []; reverted.
- loadCardFileIcons | signed do/while animation speed scan matching clearAllCardFileEntries: 509/512 instructions; structural/exact (71, 423); pool identical; exact regressions []; reverted.

## runCardMoveOrCopy
Fresh origin fetch; owned source unchanged. 608/608 instructions, frame 0x1E0. Structural diffs are permission/metadata error joins and scheduling; most of 185 instruction differences are saved-register assignments. Closest exact sibling checkCardFileDuplicate uses scoped native result/status values and signed do/while scan; handleCardMountResult uses helper error returns; sendCardSlotState packs explicit byte masks. Applying helper and typed-local idioms before declaration search. No pool/data/extent/reference-index issue.
loadCardFileIcons sibling-reference correction: MemoryCardManager::_create_icon uses a mutable typed IconState*, not a const pointer; the const CARDDir experiment tests the proven read-only-input lever. The exact typed return view is getIconComment.

- runCardMoveOrCopy | inline common-sector helper with reference outputs and exact sibling error returns: 608/608 instructions; structural/exact (12, 185); pool identical; exact regressions []; reverted.
- runCardMoveOrCopy | scoped permission result matching exact status-helper local lifetime: 608/608 instructions; structural/exact (12, 176); pool identical; exact regressions []; reverted.
- runCardMoveOrCopy | explicit block count guard following exact sibling native loop locals: 609/608 instructions; structural/exact (24, 498); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | explicit signed friend index for const cache getter: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | const reference receiver for initial friend cache read: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | unsigned getter index view guarded to the owning AddressEdit translation unit: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | const margin locals matching read-only constructor settings: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | double literal conversion in direct constructor defaults: 808/820 instructions; structural/exact (37, 803); pool identical; exact regressions []; reverted.
- create__Q33ipl5scene11AddressEditFv | const reference margin locals retaining setting view through vector constructor: 818/820 instructions; structural/exact (23, 331); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | real inline UTF16 name-copy helper with const String input: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | mutable String helper receiver with const wcsncpy input: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- update_friendinfo__Q33ipl5scene11AddressEditFv | inline name accessor/copy boundary retaining the original clear call: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | layout FindPaneByName wrapper used by exact Address text methods: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | direct layout root accessor boundary before virtual lookup: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.
- get_friendinfo__Q33ipl5scene11AddressEditFv | named read-only text plus layout wrapper boundary: 82/84 instructions; structural/exact (10, 68); pool identical; exact regressions []; reverted.

Address::start_drag_event member-helper attempt: correct the earlier free-helper access error with a private real inline member guarded to IPL_ADDRESS_MATCHING. This ports the matched MiiObj::create_callback texture-installation boundary without changing another translation unit.

- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | real inline Address member for const icon installation: 224/223 instructions; structural/exact (8, 109); pool DIVERGES; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | read-only pointer parameter for inline member texture installation: 224/223 instructions; structural/exact (8, 109); pool DIVERGES; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | inline const icon member with matched callback root-pane lookup: 224/223 instructions; structural/exact (8, 109); pool DIVERGES; exact regressions []; reverted.
- loadCardFileIcons | explicit image result join matching target helper success/error returns: 507/512 instructions; structural/exact (65, 431); pool identical; exact regressions []; reverted.
- loadCardFileIcons | named image status before joined success/error path: 507/512 instructions; structural/exact (65, 431); pool identical; exact regressions []; reverted.
- loadCardFileIcons | separate comment base lifetime matching target inlined read regions: 507/512 instructions; structural/exact (65, 431); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | typed picture receiver for texture installation, matching NW4R picture role: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | typed picture with read-only icon object accessor: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | pane reference receiver for matched callback texture idiom: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.

Register allocation last: update_friendinfo official declsearch over two independent name-pointer initializers after the clear, following three structural/sibling attempts. declaration block: |       const wchar_t* name = mString.mName; |       wchar_t* storedName = reinterpret_cast<wchar_t*>(ipl::scene::sFriendInfo.attr.name); | start (2, 2) | best (2, 2) after 2 builds; source restored; best order was: |     const wchar_t* name = mString.mName; |     wchar_t* storedName = reinterpret_cast<wchar_t*>(ipl::scene::sFriendInfo.attr.name); |
- update_friendinfo__Q33ipl5scene11AddressEditFv | official declsearch final name argument scheduling check: 38/38 instructions; structural/exact (2, 2); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | explicit unsigned valid MiiObj index, matching stored friend-index view: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | unsigned MiiObj indexing with exact callback root lookup: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.
- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface | native unsigned friend-index local for both icon access and reset: 223/223 instructions; structural/exact (0, 7); pool identical; exact regressions []; reverted.

Register allocation last for cardThreadMain: after six structural/sibling/helper attempts, official declsearch over its independent scalar locals, max 120 evaluations. The packet insertion scheduling is the only remaining normalized structure difference; no added storage or undefined values.

declaration block: |       BOOL brokenFile; |       BOOL exitThread = FALSE; |       u32 validState = TRUE; |       u32 command; |       s16 fileNo; |       u8 slot; |       s32 result; |       s32 file; |       u32 listingFile; |       s32 outerSlot; |       s32 freeFile; |       s32 freeBlocks; | start (2, 78) | improved (2, 73) | improved (2, 58) | improved (2, 54) | improved (2, 50) | improved (2, 41) | improved (2, 39) | best (2, 39) after 120 builds; kept in source: |     s32 freeBlocks; |     s32 outerSlot; |     s32 freeFile; |     u32 command; |     u32 validState = TRUE; |     u8 slot; |     s32 result; |     s32 file; |     BOOL brokenFile; |     BOOL exitThread = FALSE; |     u32 listingFile; |     s16 fileNo; |
- cardThreadMain | final official scalar-declaration search check: 301/301 instructions; structural/exact (2, 39); pool identical; exact regressions []; reverted.

Decoder discrepancy confirmed from raw ELF bytes: AddressEvent::onEvent instruction 32 is 418601ec and instruction 37 is 41860020 in both baseline and target. Capstone yields beq cr1, immediate; odiff incorrectly reads operand 0 (the condition-register identifier 13) instead of the last immediate. The gate instruction-exact count excludes this existing byte-identical function. Gate scripts remain untouched.

Card thread last-register continuation: first declsearch improved 78 -> 39 instruction differences, preserving 301 instructions and every exact function/pool. It was restored while preparing a bounded continuation from that real scalar order. Continue official search for 240 evaluations; source trials have already covered native packet, helper, and loop idioms.
declaration block: |       s32 freeBlocks; |       s32 outerSlot; |       s32 freeFile; |       u32 command; |       u32 validState = TRUE; |       u8 slot; |       s32 result; |       s32 file; |       BOOL brokenFile; |       BOOL exitThread = FALSE; |       u32 listingFile; |       s16 fileNo; | start (2, 39) | improved (2, 35) | best (2, 35) after 240 builds; kept in source: |     s16 fileNo; |     s32 freeBlocks; |     s32 outerSlot; |     s32 freeFile; |     u32 command; |     u32 validState = TRUE; |     u8 slot; |     s32 result; |     s32 file; |     BOOL brokenFile; |     BOOL exitThread = FALSE; |     u32 listingFile; |
- cardThreadMain | continued official scalar allocation search: 301/301 instructions; structural/exact (2, 35); pool identical; exact regressions []; reverted.

Card thread final structural packing trials start from the real scalar order found by declsearch. Test exact sibling byte-mask and typed wire-field idioms; preserve initialized packet storage and command bits. Nonexact results are restored.

- cardThreadMain | explicit masked validity byte merge matching exact sendCardSlotState masks: 301/301 instructions; structural/exact (2, 34); pool identical; exact regressions []; reverted.
- cardThreadMain | byte-typed validity parameter matching packed response field: 301/301 instructions; structural/exact (2, 35); pool identical; exact regressions []; reverted.
- cardThreadMain | aggregate initialized response union with named native message result: 301/301 instructions; structural/exact (2, 35); pool identical; exact regressions []; reverted.
- cardThreadMain | byte-field native packet matching exact response wire layout: 302/301 instructions; structural/exact (45, 263); pool identical; exact regressions []; reverted.

## Final completeness audit

Fresh origin/main 885cdfeee63a4b681bb5242e198dd7220834eb43. Owned sources/headers unchanged since the starting main.

- start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface: 18 compiled distinct source/helper/type/loop trials before final gate.
- onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface: 3 compiled distinct source/helper/type/loop trials before final gate.
- update__Q33ipl5scene15FriendListCacheFUlPCwUx: 6 compiled distinct source/helper/type/loop trials before final gate.
- create__Q33ipl5scene11AddressEditFv: 9 compiled distinct source/helper/type/loop trials before final gate.
- get_friendinfo__Q33ipl5scene11AddressEditFv: 11 compiled distinct source/helper/type/loop trials before final gate.
- update_friendinfo__Q33ipl5scene11AddressEditFv: 10 compiled distinct source/helper/type/loop trials before final gate.
- cardThreadMain: 10 compiled distinct source/helper/type/loop trials before final gate.
- loadCardFileIcons: 6 compiled distinct source/helper/type/loop trials before final gate.
- runCardMoveOrCopy: 3 compiled distinct source/helper/type/loop trials before final gate.

All experimental header and nonexact source changes restored. Retained code: only the gate-passing signed FriendListCache member subscript. Owned pools/data require no symbol rename or extent correction. Final non-quick three-unit gate follows.

## Final full gate and open-function audit

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 22016/23988 data 1964/1964 functions 99/101 fuzzy 99.9233 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 98/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.923294
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.84305
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 98.42593
[src/scene/address/iplAddress] baseline: code 21856/23988 data 1964 functions 98 fuzzy 99.8933
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 23344/27112 data 2560/2560 functions 91/94 fuzzy 99.5528 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 91/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.55282
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.5561
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit] baseline: code 23344/27112 data 2560 functions 91 fuzzy 99.5528
[src/scene/cardSequence/iplCardSequence] pool: IDENTICAL
[src/scene/cardSequence/iplCardSequence] objdiff: code 4168/9852 data 1496/1496 functions 27/30 fuzzy 97.2010 linked code 0
[src/scene/cardSequence/iplCardSequence] instruction-exact functions: 27/30
[src/scene/cardSequence/iplCardSequence]   section .bss size 16 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .data size 1464 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .sbss size 8 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .sdata size 8 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .text size 9852 match 97.20097
[src/scene/cardSequence/iplCardSequence]   below 100: cardThreadMain 97.9402
[src/scene/cardSequence/iplCardSequence]   below 100: loadCardFileIcons 90.34375
[src/scene/cardSequence/iplCardSequence]   below 100: runCardMoveOrCopy 97.8125
[src/scene/cardSequence/iplCardSequence] baseline: code 4168/9852 data 1496 functions 27 fuzzy 97.2010
regressions vs baseline: 0
global matched_code_percent: 91.53532 -> 91.54067
global fuzzy_match_percent: 99.69871 -> 99.69896
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.55890
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh objdiff report regenerated after the full clean build. build/43U/ok up to date; FriendListCache::update objdiff 100.0, ctxdiff 40/40 instructions and diffs 0. All three owned pools identical and all owned data sections 100.0.

- src/scene/address/iplAddress: objdiff exact functions 98/101 -> 99/101; matched code bytes 21856 -> 22016/23988; data bytes 1964 -> 1964/1964.
  - OPEN start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface: 99.84305%; 18 distinct compiled source attempts. 223/223 instructions, seven saved icon/pane register differences; sibling accessor/root/picture trials unchanged.
  - OPEN onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface: 98.42593%; 3 distinct compiled source attempts. 270/270 instructions, normalized structure exact; 81 saved-register differences after sibling lookup/animator boundaries.
- src/scene/address/iplAddressEdit: objdiff exact functions 91/94 -> 91/94; matched code bytes 23344 -> 23344/27112; data bytes 2560 -> 2560/2560.
  - OPEN create__Q33ipl5scene11AddressEditFv: 97.5561%; 9 distinct compiled source attempts. 818/820 instructions; conditional margin loads, saved pool/file registers, argument scheduling; literal/default/const margins did not recover target.
  - OPEN get_friendinfo__Q33ipl5scene11AddressEditFv: 88.03571%; 11 distinct compiled source attempts. 82/84 instructions; target preserves text addresses across virtual pane lookup, ours rematerializes them; accessor/helper/const-view trials unchanged.
  - OPEN update_friendinfo__Q33ipl5scene11AddressEditFv: 99.42105%; 10 distinct compiled source attempts. 38/38 instructions; wcsncpy source/destination address setup order swapped; typed const views/accessors/name-copy helper and final declsearch unchanged.
- src/scene/cardSequence/iplCardSequence: objdiff exact functions 27/30 -> 27/30; matched code bytes 4168 -> 4168/9852; data bytes 1496 -> 1496/1496.
  - OPEN cardThreadMain: 97.9402%; 10 distinct compiled source attempts. 301/301 instructions; validity-byte merge scheduling and saved-register lifetimes; 360 official declaration evaluations reduced a reverted candidate to 35 differences, byte-mask variant 34 but no exact gain.
  - OPEN loadCardFileIcons: 90.34375%; 6 distinct compiled source attempts. 508/512 instructions; image/comment error joins, indexing and palette lifetime for reserved format 3. No undefined-value reconstruction introduced.
  - OPEN runCardMoveOrCopy: 97.8125%; 3 distinct compiled source attempts. 608/608 instructions; permission/metadata joins and saved-register allocation. Scoped result variant reduced 185 to 176 differences but was restored.

Instruction-exact gate counts before -> after: Address 97/101 -> 98/101; AddressEdit 91/94 -> 91/94; CardSequence 27/30 -> 27/30. AddressEvent::onEvent remains objdiff 100.0 and byte-identical; the existing condition-register branch decoder discrepancy explains the one-count difference.
Only code delta: signed direct member indexing in FriendListCache::update, committed as fd527e4a. No other CPP/header/config edit retained. No upstream writes, pushes, PRs, workers or linking changes.
Unresolved source inference: loadCardFileIcons reserved initial palette format 3; target appears to carry an incoming register, so no uninitialized local was substituted. All reverted helper/register candidates remain documented above.
