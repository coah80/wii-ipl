# rx7 allocator experiments

Accepted source candidate: getComment 98.94309% -> 100.0%, 123/123 instructions, diffs 0; +492 matched code bytes and +1 exact function. Clean three-unit gate passes with zero regressions and the required DOL hash. The remaining source is unchanged. All required searches finished; the other five assigned functions remain open.

Baseline HEAD f7cc4a45a5b5dd0cc057d9b017bc8cc026eef002
Source files match fetched origin/main. Only the assigned three source files and this log are in scope. update_file_array is already exact and is excluded from edits.

Initial debugger setup: the launcher copy in build/rx7/mwdbg.py used the shared unmodified debugger and compiler, with ROOT and output validation/default adapted for this worktree. It initially used the shared debugger lock. Later private-port and batched-read changes, their failures, and independent byte-identity validations are recorded below.

src/scene/memoryCard/iplMemoryCardManager
POOL IDENTICAL up to 0 (mine=0 base=0)
{'fuzzy_match_percent': 98.22832, 'total_code': '5396', 'matched_code': '4080', 'matched_code_percent': 75.611565, 'matched_data_percent': 100.0, 'total_functions': 26, 'matched_functions': 23, 'matched_functions_percent': 88.46153, 'complete_data_percent': 100.0, 'total_units': 1}
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55%; src 0x190 base 0x190 insns 100/100; diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]
getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309%; src 0x1ec base 0x1ec insns 123/123; diffs 20: [10, 12, 14, 19, 20, 21, 23, 24, 45, 46, 48, 49, 51, 62, 66, 67, 86, 90, 91, 117]
create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453%; src 0x1a8 base 0x1a8 insns 106/106; diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]
update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 100.0%; src 0x168 base 0x168 insns 90/90; diffs 0: []
src/scene/cardSequence/iplCardSequence
POOL IDENTICAL up to 43 (mine=43 base=43)
{'fuzzy_match_percent': 97.42631, 'total_code': '9852', 'matched_code': '4168', 'matched_code_percent': 42.30613, 'total_data': '1496', 'matched_data': '1496', 'matched_data_percent': 100.0, 'total_functions': 30, 'matched_functions': 27, 'matched_functions_percent': 90.0, 'total_units': 1}
cardThreadMain: 97.9402%; src 0x4b4 base 0x4b4 insns 301/301; diffs 78: [6, 9, 11, 17, 33, 34, 48, 49, 50, 54, 57, 58, 60, 62, 67, 72, 75, 77, 79, 80]
runCardMoveOrCopy: 97.88651%; src 0x980 base 0x980 insns 608/608; diffs 176: [5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 46, 47, 50, 51, 57, 60, 73, 78, 79, 83]
src/scene/sdChannelMemory/iplSDMemory
POOL IDENTICAL up to 90 (mine=90 base=90)
{'fuzzy_match_percent': 99.26294, 'total_code': '20872', 'matched_code': '14812', 'matched_code_percent': 70.96589, 'total_data': '3344', 'matched_data': '3344', 'matched_data_percent': 100.0, 'total_functions': 66, 'matched_functions': 64, 'matched_functions_percent': 96.969696, 'total_units': 1}
create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 99.15884%; src 0x10a0 base 0x10a0 insns 1064/1064; diffs 175: [5, 10, 17, 21, 27, 33, 34, 39, 40, 45, 46, 51, 57, 63, 69, 75, 81, 109, 116, 117]

Target register map before experiments
- _create_icon: r24 metadata root and eventual return texture; r25 manager then RGB cell row; r26 slot then CI cell-row offset; r27 file then CI column offset; r28 frame then CI texture-row base; r29 slot*0x1fc0; r30 file*0x40; r31 selected IconState. The target keeps GX row and column separate across calls and only forms the returned texture after initialization. Source instead coalesces a complete texture pointer before the first call.
- getComment: r26 manager, r27 which*0x80, r28 file*0x15c, r29 slot*0xaca4, r30 selected comment, r31 unselected comment base. Narrow trim read cursor is r3, write cursor r4, zero r5. Source has r27/r28/r29/r30/r26 for the corresponding saved values, read r5 and zero r3.
- SDMemory::create: target string-pool base r31, textbox r30, System::smArg address r26. Source string-pool r30, first textbox r26, System base r31. Exact 1064-instruction shape, 175 positional differences.
- cardThreadMain: target exitThread r24, command r19, slot r22, file/listing index r23, mount result r20, disk-ID base r21. Source exitThread r26, command r23, slot r21, file/listing r20, mount result r24, disk-ID base r22. Response formation also lacks the target separate copy before rlwimi.
- runCardMoveOrCopy: 608 instructions with 176 positional differences, including saved flags and parameters plus copy status joins. Full target disassembly is in build/rx7/runCardMoveOrCopy.target.asm.

Baseline debugger captures queued on the shared lock. Manual variant preparation uses standalone snapshots, never source files awaiting capture.

icon-row-plus-column: Use array decay then pointer advance to give the IconState base value the target base-plus-row-plus-column expression. objdiff 87.55%; insns 100/100 diffs 37; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-row-plus-column.

icon-direct-metadata: Recompute selected metadata directly at each use so the original array participates in address CSE. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-direct-metadata.

icon-result-after-init: Retain a shared texture result assigned after initialization in each branch, with row-plus-column metadata. objdiff 85.3%; insns 101/100 diffs 60; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-result-after-init.

comment-named-zero-before-cursors: Name the trim terminator before cursor declarations, making its virtual register explicit while preserving every byte read and write. objdiff 98.94309%; insns 123/123 diffs 20; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-named-zero-before-cursors.

comment-named-zero-after-cursors: Declare the explicit trim terminator after both cursors to test reverse local numbering against the read-cursor color. objdiff 98.94309%; insns 123/123 diffs 20; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-named-zero-after-cursors.

comment-reuse-source-pointer: Reuse the SDK source pointer for the local conversion input after memcpy, shortening the separate compiler-temporary web. objdiff 98.94309%; insns 123/123 diffs 20; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-reuse-source-pointer.

banner-row-plus-column: Give the selected banner metadata the target base-plus-row-plus-column expression. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-row-plus-column.

banner-direct-metadata: Access banner metadata directly at each call, avoiding the cached element pointer. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-direct-metadata.

banner-distinct-rgb-image-base: RGB image address uses the original array expression while CI keeps the selected icon, matching the target distinct address webs. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-distinct-rgb-image-base.

thread-plain-response: Express the real response bit field through ordinary word masking and a reassigned reply variable, testing the missing target copy without a carrier union. objdiff 98.239204%; insns 301/301 diffs 77; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-plain-response.

thread-reuse-mount-listing-index: Reuse the file local for the nonoverlapping listing loop, preserving its unsigned comparison and u16 SDK argument. objdiff 98.03986%; insns 301/301 diffs 73; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-reuse-mount-listing-index.

thread-exit-declared-last: Move the live exit flag after other scalar locals to test its saved-register priority independently of initialization effects. objdiff 97.890366%; insns 301/301 diffs 81; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-exit-declared-last.

move-destination-file-last: Make the destination file the last declared live scalar so its -1 value can claim r30 before temporary and metadata flags. objdiff 97.77631%; insns 608/608 diffs 189; pool identical; other drops []. Trial retained only under build/rx7/trials/move-destination-file-last.

move-flags-before-file: Declare metadata, temporary-created, then destination-file in semantic dependency order to test reverse numbering of the three saved values. objdiff 97.883224%; insns 608/608 diffs 176; pool identical; other drops []. Trial retained only under build/rx7/trials/move-flags-before-file.

move-reuse-status-result: Reuse the common result for the permission query whose result is consumed before the next query, removing one named status web. objdiff 97.88651%; insns 608/608 diffs 176; pool identical; other drops []. Trial retained only under build/rx7/trials/move-reuse-status-result.

sd-textbox-declared-last: Make the reused textbox the last declared local to test whether it moves ahead of the generated System base without changing pool order. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-textbox-declared-last.

sd-textbox-reinterpret-casts: Use the zero-offset pane downcast form from the layout inheritance, testing virtual-register creation at casts. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-textbox-reinterpret-casts.

sd-independent-textbox-values: Use a separate named textbox at each lookup instead of a multiply assigned pointer, testing copy coalescing across message calls. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-independent-textbox-values.

icon-branch-local-return: Return the branch-local texture after its GX load, giving the RGB and CI paths independent address lifetimes. objdiff 83.05%; insns 101/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-branch-local-return.

icon-distinct-load-return-values: Give each load and final return its own ordinary pointer local instead of sharing an expression-only temporary. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-distinct-load-return-values.

icon-init-unsigned-file-view: Use the stored word-width file-number view for GX initialization and the signed SDK index for loading, testing conversion CSE while preserving valid card indices. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-init-unsigned-file-view.

Debugger queue recovery: after more than eight minutes on the shared lock, stopped only rx7 queued requests. The private launcher now uses a private lock and port 19007. A local LD_PRELOAD bind adapter redirects only the host emulator listener from port 9001; a private gc3.py changes only ROOT and the connection port. Compiler and capture hooks are unchanged. Captures will be checked against independent wibo objects. No other worker process or file was changed.

Tool compatibility finding: the original Ninja `-enc SJIS` invocation crashes retrowin32 at compiler PC 0x46da46 before code generation. Removing only this encoding flag reaches allocator capture. Normal trial/build commands retain `-enc SJIS`; each completed capture is independently recompiled with the original flag and compared byte for byte. Compiler flags were not changed in the project. The first local launcher failed from a local strDRIVER typo, fixed before successful execution.

_create_icon baseline allocator, build/rx7/mwdbg-icon-base-noenc, original-flags wibo object byte-identical
- PCode B5 defines v40=slot*8128, v41=file*64 and named v36=selected icon. The final simplify sweep removes v36 with degree14, then v40 degree13 and v41 degree12, against 29 colors. Coloring reverses this into v41, v40, v36, claiming r31, r30, r29 because the legal volatile masks are zero. The target needs icon r31, file offset r30 and slot offset r29.
- No copy candidate coalesces; every candidate is rejected for interference. GX destination row v44 and column v46 are shared across branches. RGB complete-pointer v43 and palette pointer v39 survive their calls and coalescing to r3 is rejected. These CSE webs exist before allocation, so changing declaration order alone cannot reconstruct the target separate row/column addresses.
- Removing the cached icon expression is the targeted source change. Its normal compile already fixes the first ten positional differences, from37 to27, at88.35%. Candidate allocator capture is queued on the private port for confirmation.

comment-indexed-trim: Let the optimizer derive read and write induction pointers from one signed index. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-indexed-trim.

comment-single-cursor-trim: Use one postdecrement trim cursor so the read and write webs are created by strength reduction. objdiff 97.34146%; insns 121/123 diffs 86; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-single-cursor-trim.

comment-reuse-comments-cursor: Reuse the consumed SDK source pointer as the trim reader, changing named-web identity without changing access order. objdiff 98.73984%; insns 123/123 diffs 22; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-reuse-comments-cursor.

getComment baseline allocator, build/rx7/mwdbg-comment-base-local, original-flags wibo byte-identical
- Before allocation B6 has v39=end, v40=tail, v77=zero. They simplify with degrees13,12,7. Reverse coloring gives zero first, legal mask0x1ff8 picks r3, then tail mask0x1ff0 picks r4 and end mask0x1fe0 picks r5. The end/tail copy cannot coalesce because both mutable induction values interfere. Target instead needs end r3 and zero r5.
- Indexed trimming creates optimizer-owned induction values instead of the low-numbered named end/tail nodes. The normal compile now matches the entire narrow trim loop and reaches99.18699%,123/123instructions,15differences. Candidate capture will confirm the changed priority.
- The remaining saved-register rotation has a separate cause. v51=unselected comment base colors first as r31, followed by v46=slot offset, v45=file offset, v44=which offset and v32=this as r30-r27. Selected pointer v50 simplifies early at degree26, so it colors later and requests r26. The target requires this pointer as r30. Testing pointer naming and real buffer-selector/clear helper boundaries to change its simplify position.

_create_icon candidate confirmation, build/rx7/mwdbg-icon-direct-metadata, original-flags wibo byte-identical
- Direct metadata indexing replaces named v36 with compiler-selected pointer v58. Priority becomes v58, v39=file offset, v38=slot offset, assigning r31,r30,r29 exactly as target. Other saved parameters retain their target colors. The remaining27differences are GX address CSE and destination lifetimes already visible before allocation.

comment-output-clear: Name the selected comment for clear while preserving indexed trimming and field expressions elsewhere. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-output-clear.

comment-output-clear-convert: Name the selected comment for clear-convert while preserving indexed trimming and field expressions elsewhere. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-output-clear-convert.

comment-output-clear-convert-return: Name the selected comment for clear-convert-return while preserving indexed trimming and field expressions elsewhere. objdiff 93.44715%; insns 123/123 diffs 31; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-output-clear-convert-return.

comment-clear-helper: Move the selected-pointer call argument into a real buffer-clearing helper to change temporary interference before allocation. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-clear-helper.

comment-clear-helper-return: Keep the same selected pointer alive through a clear-and-return helper so its parameter web can move ahead of row-offset CSE values. objdiff 99.06504%; insns 123/123 diffs 16; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-clear-helper-return.

comment-select-helper-calls: Give only the clear and conversion call sites a typed selector helper, retaining direct indexed wide-trim and return expressions. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-select-helper-calls.

banner-signed-selected-index: Separate validation address from selected metadata with signed card-index view, preserving the word value but testing typed CSE. objdiff 90.28302%; insns 106/106 diffs 75; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-signed-selected-index.

banner-signed-rgb-image-index: Create a separate RGB image address from the signed index view while retaining the named format and CI metadata pointer. objdiff 90.28302%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-signed-rgb-image-index.

banner-selected-reference: Bind the existing icon object by reference to test pointer coalescing without a new aggregate. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-selected-reference.

comment-call-which-unsigned: Use the which-unsigned view only for whole-comment call arguments, testing selected-address CSE independently of indexed loops. objdiff 87.63415%; insns 125/123 diffs 80; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-call-which-unsigned.

comment-call-file-signed: Use the file-signed view only for whole-comment call arguments, testing selected-address CSE independently of indexed loops. objdiff 81.89431%; insns 126/123 diffs 84; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-call-file-signed.

comment-call-which-long: Use the which-long view only for whole-comment call arguments, testing selected-address CSE independently of indexed loops. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-call-which-long.

comment-call-slot-unsigned: Use the slot-unsigned view only for whole-comment call arguments, testing selected-address CSE independently of indexed loops. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-call-slot-unsigned.

comment-output-newline-store: Extend the selected-pointer lifetime through the newline-store using the same destination expression. objdiff 97.60162%; insns 123/123 diffs 29; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-output-newline-store.

comment-output-wide-trim-store: Extend the selected-pointer lifetime through the wide-trim-store using the same destination expression. objdiff 97.88618%; insns 122/123 diffs 62; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-output-wide-trim-store.

icon-rgb-helper-pointer: Separate RGB texture initialization at its existing API boundary, using a pointer parameter to test destination-pointer CSE. objdiff 89.34%; insns 101/100 diffs 43; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-helper-pointer.

icon-rgb-helper-const-pointer: Separate RGB texture initialization at its existing API boundary, using a const-pointer parameter to test destination-pointer CSE. objdiff 89.34%; insns 101/100 diffs 43; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-helper-const-pointer.

icon-load-helper: Move repeated texture loading to a natural helper so its argument is a separate inline value. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-load-helper.

banner-rgb-helper-pointer: Separate RGB texture initialization at its existing API boundary, using a pointer parameter to test destination-pointer CSE. objdiff 92.92453%; insns 105/106 diffs 88; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-rgb-helper-pointer.

banner-rgb-helper-const-pointer: Separate RGB texture initialization at its existing API boundary, using a const-pointer parameter to test destination-pointer CSE. objdiff 92.92453%; insns 105/106 diffs 88; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-rgb-helper-const-pointer.

banner-load-helper: Move repeated texture loading to a natural helper so its argument is a separate inline value. objdiff 87.830185%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-load-helper.

create_banner baseline allocator, build/rx7/mwdbg-banner-base-local, original-flags wibo byte-identical
- Target uses r31 metadata root, r30 file offset, r29 slot offset, r28 file, r27 slot, r26 manager and r25 selected icon. Source v48 root takes r31, then shared v44 icon takes r30, file v35 takes r29, slot v33 r28 and this v32 r27. Their final simplify degrees are12,13,14,15,16 in reverse coloring order. Row/column v45/v46 simplify earlier, so they miss the target r29/r30 positions.
- Before allocation, v44 is shared by banner validation and format/image access. Target instead calculates one validation/image address and recomputes a second selected icon address at the format check. All copy coalesces are interference-rejected. Removing the named icon gains fuzzy score but adds two instructions; signed view at the selected-index boundary is a separate typed-CSE test. Its capture is retained even though the score falls.

Further debugger setup evidence: retrowin32 resolves header names case-sensitively, unlike the normal wibo invocation. Local include aliases were required for nw4r/lyt/textbox.h, nw4r/ut/List.h, scene/textballoon/iplBalloon.h and tiHWKeyboard.h. The alias directory contains symlinks to this worktree's original headers and their sibling headers. No header content or build configuration was changed. Capture validity still requires byte identity against original-flags wibo.

comment-array-ref: Preserve the real comment array boundary with a array-ref for whole-buffer calls. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-array-ref.

comment-line-array-pointer: Preserve the real comment array boundary with a line-array-pointer for whole-buffer calls. objdiff 99.06504%; insns 123/123 diffs 16; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-line-array-pointer.

comment-line-array-reference: Preserve the real comment array boundary with a line-array-reference for whole-buffer calls. objdiff 99.06504%; insns 123/123 diffs 16; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-line-array-reference.

comment-manager-alias: Give the manager receiver an explicit manager-alias and preserve all indexed member expressions. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-manager-alias.

comment-manager-reference: Give the manager receiver an explicit manager-reference and preserve all indexed member expressions. objdiff 99.18699%; insns 123/123 diffs 15; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-manager-reference.

getComment indexed-trim confirmation, build/rx7/mwdbg-comment-indexed-trim, original-flags wibo byte-identical
- Generated read and write inductions are now v106 and v105, while zero is v76. All simplify in the first sweep, so reverse coloring handles read before write before zero. They become r3,r4,r5, matching all narrow-loop instructions. Saved-address priorities are unchanged.
- Explicit output pointers, real array references, clear/select inline helpers, receiver aliases, and primitive index type views were tested. None repaired the selected-output priority without disturbing other target instructions. Details and all source snapshots are retained per trial.

create_banner signed-index confirmation, build/rx7/mwdbg-banner-signed-selected-index, original-flags wibo byte-identical
- The signed index separates the validation lbzx and selected-pointer definition, but the latter still reuses row-plus-column grouping. Priority becomes metadata root v49/r31, file v36/r30, icon v35/r29, slot/r28, this/r27. This fixes one addressing split but does not produce the target offset lifetimes or colors;90.28302%,75differences. Rejected.

comment-prior-returning-trim: Revalidate the isolated s1 returning trim helper on current source; preserve all other current functions and initializer fixes. objdiff 99.6748%; insns 123/123 diffs 6; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-prior-returning-trim.

comment-returning-indexed-trim: Combine the prior returning trim boundary with optimizer-owned read/write induction values proven by the allocator capture. objdiff 100.0%; insns 123/123 diffs 0; pool identical; other drops []. Trial retained only under build/rx7/trials/comment-returning-indexed-trim.

getComment exact candidate
- Revalidated the isolated returning trim helper from agent/w1004/s1, without its older uninitialized or unrelated edits. It repairs the selected-output saved-register rotation and yields99.6748%,123instructions,6remaining narrow-trim differences.
- Combining that real buffer-trimming boundary with indexed trimming yields100.0%,123/123instructions,diffs0,identical pool,and no per-function drops. The helper returns the original byte-buffer address; every byte read and zero write occurs in the same order as baseline. The loop keeps the same implicit precondition as the original target.
- Applied only this helper and getComment change to the source. Stopped the three comment searches because the requested exact-function criterion is met. Full gates and final allocator capture remain pending.

move-prior-helper-boundaries: Revalidate only the s1 temporary-file helper and separate copy/move result joins; no palette or unrelated function changes. objdiff 98.23191%; insns 608/608 diffs 167; pool identical; other drops []. Trial retained only under build/rx7/trials/move-prior-helper-boundaries.

thread-prior-declarations: Revalidate the s1 thread declaration ordering against the current baseline for allocator comparison. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-prior-declarations.

move-const-parameters: Test primitive parameter type identity and qualifier effects on the earliest allocator nodes. objdiff 97.88651%; insns 608/608 diffs 176; pool identical; other drops []. Trial retained only under build/rx7/trials/move-const-parameters.

move-native-int-parameters: Test primitive parameter type identity and qualifier effects on the earliest allocator nodes. Compile failed; see build/rx7/trials/move-native-int-parameters/compile.log.

move-receiver-aliases: Give the three input values explicit receiver-aliases before operation locals, testing whether their high-degree parameter nodes move into local ordering. Compile failed; see build/rx7/trials/move-receiver-aliases/compile.log.

move-receiver-references: Give the three input values explicit receiver-references before operation locals, testing whether their high-degree parameter nodes move into local ordering. Compile failed; see build/rx7/trials/move-receiver-references/compile.log.

thread-response-const-ref: Give the actual validity state a reference boundary to test whether the reply uses its existing live value instead of a coalesced constant. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-response-const-ref.

thread-response-ref: Give the actual validity state a reference boundary to test whether the reply uses its existing live value instead of a coalesced constant. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-response-ref.

thread-response-return-valid: Return the consumed validity state so the helper input and loop-carried state stay in one value web. objdiff 97.85714%; insns 301/301 diffs 53; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-response-return-valid.

thread-response-plain-ref: Use the existing state by reference with natural integer message packing and no bitfield carrier. objdiff 98.83721%; insns 301/301 diffs 45; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-response-plain-ref.

move-receiver-aliases-fixed: Correct mechanical member-name substitution and test the input alias or reference boundary without changing source values. objdiff 97.88651%; insns 608/608 diffs 176; pool identical; other drops []. Trial retained only under build/rx7/trials/move-receiver-aliases-fixed.

thread-priority-outer-slot-last: Move actual outer-slot and loop-state declarations to make the high-degree outer-slot node survive simplify before the persistent states. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-priority-outer-slot-last.

move-receiver-references-fixed: Correct mechanical member-name substitution and test the input alias or reference boundary without changing source values. objdiff 94.78619%; insns 609/608 diffs 602; pool identical; other drops []. Trial retained only under build/rx7/trials/move-receiver-references-fixed.

thread-priority-outer-slot-last-exit-after-valid: Move actual outer-slot and loop-state declarations to make the high-degree outer-slot node survive simplify before the persistent states. objdiff 98.48837%; insns 301/301 diffs 49; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-priority-outer-slot-last-exit-after-valid.

thread-priority-outer-slot-first: Move actual outer-slot and loop-state declarations to make the high-degree outer-slot node survive simplify before the persistent states. objdiff 98.20598%; insns 301/301 diffs 65; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-priority-outer-slot-first.

thread-priority-exit-last-outer-before-free: Move actual outer-slot and loop-state declarations to make the high-degree outer-slot node survive simplify before the persistent states. objdiff 98.57143%; insns 301/301 diffs 44; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-priority-exit-last-outer-before-free.

getComment final allocator confirmation: build/rx7/mwdbg-comment-exact-indexed-helper
- The exact candidate capture is byte-identical to an independent original-flags wibo compile. The returning helper moves trim temporaries behind the selected-address node in virtual-register numbering. Selected address v47 starts with degree 32. Earlier removals v33, v35 and v40 leave degree 29 at its first visit, equal to the 29-register budget rather than below it. It therefore waits until the final sweep and simplifies at degree 13. Priority v48(base), v47(selected), v43(slot offset), v42(file offset), v41(which offset), v32(this) produces r31,r30,r29,r28,r27,r26, exactly matching the target.
- Indexed trimming generates read cursor v106 and write cursor v105. They color in that order as r3,r4; zero v76 colors afterward as r5. The original named cursors colored after zero, giving r5,r4,r3. Coalescing cannot merge overlapping cursor ranges. Both corrected priority sequences are visible in the capture and all 123 instructions now match.
- Actual source rebuilt with Ninja; empty pools identical; quick gate passes, 24/26 instruction-exact functions (baseline 23), code 4572/5396 (baseline 4080), zero regressions, forbidden/readability scans clear. Full build DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Clean final gate remains pending.

runCardMoveOrCopy baseline allocator: build/rx7/mwdbg-move-base-headers
- Capture is byte-identical to original-flags wibo. Target saved-register mapping is r31 destinationSlot, r30 destinationFileNo, r29 temporaryCreated, r28 metadataCopied, r27 command, r26 fileNo, r25 slot, r24 callback base, r23 write-pending one, r22 pool, r21 cancelSent, r20 I/O stage, r19 offset, r18 size, r17 maxBlocks, r16 block, r15 ioResult.
- Source colors input nodes v34(command), v33(fileNo), v32(slot) first as r31,r30,r29. They survive until a third simplify sweep, ending at degrees 12,13,14. v114(callback), v110(one), v74(pool), v58(destination file), v57(destination slot), v55(created), v54(metadata) simplified in the preceding sweep, at degrees 15 through 21 in reverse order. They therefore color later as r28 through r22. The target needs destination and flag nodes to outlive the parameter nodes in simplify priority.
- Accepted coalesces include the result-to-r5 and ioResult value webs; they do not involve these overlapping saved parameters. Primitive const qualifiers and input aliases do not alter the graph. Input references add an instruction and are rejected. Revalidating the prior natural temporary-file helper plus separate copy/move status joins gives 98.23191 with 167 differences, still not exact; candidate capture queued.

cardThreadMain baseline allocator: build/rx7/mwdbg-thread-base-complete-headers
- Capture is byte-identical to original-flags wibo. Target uses r31 zero, r30 slot names, r29 one, r28 switch base, r27 string pool, r26 outerSlot, r25 validState, r24 exitThread, r23 file/listing index, r22 slot, r21 address constant, r20 result/freeBlocks, r19 command/freeFile.
- Source final simplify sweep visits v41(valid), v42(exit), v55(pool), v69(switch), v71(one), v101(slot names), v105(zero), with degrees 18 down to 12. Reverse coloring assigns r31 down to r25; exit takes r26. The outer-loop values simplify earlier and color later, displacing the target outerSlot/exit ordering. Prior declaration ordering improves the other saved locals but leaves this persistent-state priority unchanged.
- Reply insertion also diverges before allocation: inline bitfield packing substitutes the globally hoisted constant-one v71 for validState and copies after rlwimi. The target uses validState directly and copies to argument r4 before insertion. Ordinary integer packing removes the carrier but produces rlwinm/ori instead. Const/mutable reference inputs preserve the same graph; returning validState from the sender worsens the result. These source snapshots are not accepted.

thread-pack-xor-insert: Expose actual integer packet packing as a return value to change command-to-reply coalescing without a carrier type. objdiff 98.03986%; insns 302/301 diffs 260; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-pack-xor-insert.

thread-pack-clear-then-or: Expose actual integer packet packing as a return value to change command-to-reply coalescing without a carrier type. objdiff 98.83721%; insns 301/301 diffs 45; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-pack-clear-then-or.

thread-pack-or-valid-first: Expose actual integer packet packing as a return value to change command-to-reply coalescing without a carrier type. objdiff 98.83721%; insns 301/301 diffs 45; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-pack-or-valid-first.

icon-rgb-cell-pointer: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 85.85%; insns 101/100 diffs 64; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-cell-pointer.

icon-rgb-cell-reference: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 85.85%; insns 101/100 diffs 64; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-cell-reference.

icon-rgb-cell-row: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 85.85%; insns 101/100 diffs 64; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-cell-row.

banner-rgb-cell-pointer: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 89.15094%; insns 107/106 diffs 72; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-rgb-cell-pointer.

banner-rgb-cell-reference: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 89.15094%; insns 107/106 diffs 72; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-rgb-cell-reference.

banner-rgb-cell-row: Use the existing MCFileCell object boundary for RGB initialization, testing whether the allocator retains row and column across the call separately. objdiff 83.49056%; insns 109/106 diffs 83; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-rgb-cell-row.

icon-address-signed-word: Separate the indicated GX initialization address expression by a primitive word index view; metadata validation establishes the same valid array element. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-address-signed-word.

icon-address-native-word: Separate the indicated GX initialization address expression by a primitive word index view; metadata validation establishes the same valid array element. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-address-native-word.

icon-address-rgb-unsigned: Separate the indicated GX initialization address expression by a primitive word index view; metadata validation establishes the same valid array element. objdiff 93.35%; insns 100/100 diffs 17; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-address-rgb-unsigned.

icon-address-ci-unsigned: Separate the indicated GX initialization address expression by a primitive word index view; metadata validation establishes the same valid array element. objdiff 81.17%; insns 101/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-address-ci-unsigned.

icon-address-tlut-unsigned: Separate the indicated GX initialization address expression by a primitive word index view; metadata validation establishes the same valid array element. objdiff 90.24%; insns 100/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-address-tlut-unsigned.

sd-direct-message-manager: Remove the outer getMessage inline boundary while retaining every manager reload, testing whether generated load nodes precede the long smArg node. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-direct-message-manager.

sd-named-message-manager: Name each message-manager load so its value is numbered with source locals before smArg simplifies; preserve a fresh reload for every SetString call. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-named-message-manager.

sd-message-helper-pointer: Use the repeated SetString operation as a real helper boundary, testing text-box value splitting and smArg priority with a pointer parameter. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-message-helper-pointer.

sd-message-helper-pointer-ref: Use the repeated SetString operation as a real helper boundary, testing text-box value splitting and smArg priority with a pointer-ref parameter. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-message-helper-pointer-ref.

icon-rgb-slot-unsigned: Split only the RGB destination row-address expression from the CI path using an identical word-width slot value. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-slot-unsigned.

sd-message-helper-const-pointer-ref: Use the repeated SetString operation as a real helper boundary, testing text-box value splitting and smArg priority with a const-pointer-ref parameter. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-message-helper-const-pointer-ref.

icon-rgb-both-unsigned: Split only the RGB destination row-address expression from the CI path using an identical word-width slot value. objdiff 93.35%; insns 100/100 diffs 17; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-both-unsigned.

icon-rgb-slot-long: Split only the RGB destination row-address expression from the CI path using an identical word-width slot value. objdiff 82.0%; insns 103/100 diffs 76; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-rgb-slot-long.

icon-palette-row-helper-normal: Give palette initialization the existing file-row boundary to retain separate row and column address values across GX calls. objdiff 85.9%; insns 101/100 diffs 54; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-palette-row-helper-normal.

icon-palette-row-helper-rgb-unsigned: Give palette initialization the existing file-row boundary to retain separate row and column address values across GX calls. objdiff 92.15%; insns 101/100 diffs 26; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-palette-row-helper-rgb-unsigned.

SDMemory::create initial allocator evidence (first capture timed out before object completion)
- Target uses r31 string pool, r30 text-box receivers, r29 layoutFile, r28 heap, r27 this, r26 System::smArg. Baseline virtual v319 is the smArg base shared across nine title-message lookups and getSaveData. Its 43 neighbors keep it above the 29-register threshold until the final sweep. It simplifies at degree 12 after v145(pool, degree 13), v34(layoutFile,14), v33(heap,15), v32(this,16). Reverse priority gives smArg r31 and pool r30. The text-box nodes simplify early and need the later r26 saved register. Accepted coalesces concern constructor result values, not this swap.
- Named message managers, direct manager lookups, and repeated SetString helpers with pointer/const-reference/mutable-reference parameters all compile to exactly the baseline 1064 instructions and 175 differences. These aliases are normalized before allocation; they do not split the offending smArg lifetime or change its priority.
- The 600-second debugger run reached and recorded GPR allocation, then timed out during later PCode dumps. Its object is not accepted as validated evidence. A private fast driver now batches each existing instruction/node/edge memory read into one GDB request without changing decoded fields or compiler execution. Queued validation compares its graph and assignments against the already validated exact getComment capture. Future SD captures use 1200 seconds and still require original-flags wibo byte identity. Shared debugger files and compiler remain untouched.

cardThreadMain coalescing detail
- Baseline merges reply temporary v72 into command v40, then rejects the command-to-physical-r4 move for interference. This accounts for insertion into the saved command register followed by a move to r4. The target instead copies into r4 before insertion. Reference inputs and return-value packet helpers were tested; natural integer packing yields rlwinm/ori, while XOR insertion adds an instruction. None is exact.

sd-direct-receiver-expression: Let the compiler own receiver temporaries by putting pane lookup directly on SetString, preserving lookup-before-message evaluation. objdiff 86.172935%; insns 1048/1064 diffs 931; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-direct-receiver-expression.

sd-layout-message-helper: Use the repeated pane lookup and localized-message assignment as one real operation, changing temporary numbering without changing call order. objdiff 73.705826%; insns 802/1064 diffs 677; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-layout-message-helper.

thread-state-exit-u32: Change only the representation of a local with proven bounded values to test graph construction for the persistent state and outer-slot nodes. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-state-exit-u32.

thread-state-exit-int: Change only the representation of a local with proven bounded values to test graph construction for the persistent state and outer-slot nodes. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-state-exit-int.

thread-state-valid-int: Change only the representation of a local with proven bounded values to test graph construction for the persistent state and outer-slot nodes. objdiff 98.33887%; insns 301/301 diffs 47; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-state-valid-int.

thread-state-exit-bool: Change only the representation of a local with proven bounded values to test graph construction for the persistent state and outer-slot nodes. objdiff 98.53821%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-state-exit-bool.

thread-state-outer-u32: Change only the representation of a local with proven bounded values to test graph construction for the persistent state and outer-slot nodes. objdiff 98.355484%; insns 301/301 diffs 46; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-state-outer-u32.

cardThreadMain declaration-order confirmation: build/rx7/mwdbg-thread-prior-declarations
- Original-flags wibo object is byte-identical. The final priority now places outerSlot v33 immediately after validState v41, so outerSlot becomes r24 while exitThread v43 remains r26. The 301-instruction result has 46 differences versus 78 initially; the allocator dump confirms a partial priority change, not a match.
- Moving outerSlot earlier/later and swapping the two state declarations changes saved-register choices but does not produce all target colors. One permutation puts exitThread in its target r24 while validState moves to r26 instead of r25. Primitive state type variants likewise fail to fix the complete assignment. All rejected source stays in ignored trial directories.

Additional SD and GX trials
- Direct SD receiver expressions alter instruction count and scheduling; the layout-message helper does not fully inline. Both are rejected. No shared headers or compiler options were edited.
- In _create_icon, an unsigned word view only at RGB initialization separates its destination expression and reduces the direct-metadata trial to 17 differences, 93.35%, 100 instructions. It recomputes the file stride after GXInitTexObj, whereas the target keeps that stride across the call; this is still not exact. Signed/native word views are normalized away. Existing MCFileCell pointer/reference/row helpers add instructions. Palette-row helpers also add an instruction and fail to preserve the target address grouping. None is applied.

Search-tool dead-end handling
- Banner seed 19 terminated after two trials because a same-width type mutation produced a spelling that no mutation regex recognized. The private search copy now restarts from its original body on such a dead end, preserving the original time budget and global 24-slot lock. The early result is retained; seed 19 is rerun in a new directory. This changes search coverage only, not compiler flags or accepted source.

thread-search-seed19-best: Freshly compile the completed seed-19 best candidate; signed-byte compare buffer stores only zero and outerSlot uses the same bounded values. objdiff 98.6711%; insns 301/301 diffs 53; pool identical; other drops []. Trial retained only under build/rx7/trials/thread-search-seed19-best.

runCardMoveOrCopy helper confirmation: build/rx7/mwdbg-move-prior-helper-boundaries
- Original-flags wibo object is byte-identical. The helper produces a new accepted merge v76 -> v59(destinationFileNo), but the persistent color priority remains command, fileNo, slot, callback, one, pool, destination file, destination slot, created, metadata. Those values still take r31 through r22; the desired destination/flag priority is not obtained. Their final simplify degrees remain 12 through 21 in reverse color order. This confirms why the helper's 98.23191% result still has 167 instruction differences.

Private debugger batching validation
- build/rx7/mwdbg-comment-exact-fast-check is byte-identical to independent original-flags wibo. Compared with the original driver on the same exact source, all register-class pass priorities, final graph fields, neighbor sets, representatives, physical assignments and register-rewrite validation counts are identical. Evidence: driver-equivalence.json. Both drivers remain inside this worktree; no shared launcher, emulator, compiler or header was edited.

Search scheduling update
- Completed card searches: thread seeds 7/19/31 ran 212/195/204 trials; only seed 19 improved, to 98.6711% with 301 instructions and 53 differences on fresh recompile. Move seeds 7/19/31 ran 226/193/195 trials with no gain. SD seeds 7/19/31 ran 175/179/190 trials with no gain.
- The first icon seed 19 ran 766 trials from 88.35% with no gain. Five still-queued GX searches were rescheduled before they acquired a global CPU slot. The final three icon seeds use the newer 93.35% manual starting point; three banner seeds use the baseline and corrected restart-on-empty search behavior. Old logs and the early two-trial banner run remain intact.

sd-find-textbox-helper: Use a typed pane lookup helper to test real TextBox return-value coalescing while keeping lookup and message assignment as separate statements. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-find-textbox-helper.

sd-scoped-textbox-reference: Bind each real TextBox object by reference inside its localization scope, preserving lookup-before-message order and every call. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-scoped-textbox-reference.

sd-scoped-const-textbox: Make each localized receiver a distinct const pointer to test whether assignment splitting rather than string materialization controls its coloring. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7/trials/sd-scoped-const-textbox.

SD baseline validated: build/rx7/mwdbg-sd-base-fast
- The batched-read capture completed and its entire object is byte-identical to original-flags wibo. It confirms the original v319(smArg), v145(pool), v34(layoutFile), v33(heap), v32(this) priority and r31-r27 colors. The earlier timeout explanation is therefore backed by a complete validated run.
- Three further receiver-boundary trials (typed FindPane helper, scoped TextBox reference, scoped const TextBox pointer) also reproduce 99.15884%, 1064 instructions and 175 differences. No source variation so far changes the offending smArg priority without changing the instruction stream. A final helper capture remains queued/running to compare its allocator graph directly.

Coverage audit before final searches finish: sd 13 compiled source trials, thread 21 compiled source trials, move 7 compiled source trials, icon 22 compiled source trials, comment 25 compiled source trials, banner 12 compiled source trials. Every assigned open function has at least three distinct compiled source attempts. update_file_array was already exact and remains untouched.

SD helper confirmation: build/rx7/mwdbg-sd-helper-fast
- The pointer-reference SetString helper capture is byte-identical to original-flags wibo. Compared with the validated baseline, every pass priority, virtual/physical assignment, remaining degree, graph edge set and representative is identical. Source aliases and this inline boundary disappear before register allocation. The saved-register requests remain smArg r31, pool r30, layoutFile r29, heap r28, this r27; a later text-box value requests r26. The requested target pool/textBox/smArg rotation is still open. Both complete captures validate 3355 GPR rewrites with zero mismatches.

icon-destination-row-expression: Spell destination field access through the existing file-row pointer and typed element advance, testing field-offset versus element-offset CSE grouping. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-destination-row-expression.

icon-named-destination-row: Name the real destination file row once; test whether the compiler retains the row address instead of CSE of complete field pointers. objdiff 60.96%; insns 95/100 diffs 79; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-named-destination-row.

banner-destination-row-expression: Spell destination field access through the existing file-row pointer and typed element advance, testing field-offset versus element-offset CSE grouping. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-destination-row-expression.

banner-named-destination-row: Name the real destination file row once; test whether the compiler retains the row address instead of CSE of complete field pointers. objdiff 63.103775%; insns 97/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7/trials/banner-named-destination-row.

icon-returning-load-helper-pointer: Return the loaded texture from its repeated real GX load boundary so the branch result and helper argument can coalesce after initialization. objdiff 82.6%; insns 96/100 diffs 62; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-returning-load-helper-pointer.

icon-direct-returning-load-pointer: Return the loaded texture directly from each format arm through the same real load helper. objdiff 82.6%; insns 96/100 diffs 62; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-direct-returning-load-pointer.

icon-returning-load-helper-reference: Return the loaded texture from its repeated real GX load boundary so the branch result and helper argument can coalesce after initialization. objdiff 82.6%; insns 96/100 diffs 62; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-returning-load-helper-reference.

icon-direct-returning-load-reference: Return the loaded texture directly from each format arm through the same real load helper. objdiff 82.6%; insns 96/100 diffs 62; pool identical; other drops []. Trial retained only under build/rx7/trials/icon-direct-returning-load-reference.

Clean full gate: GATE PASS
- Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/memoryCard/iplMemoryCardManager src/scene/cardSequence/iplCardSequence src/scene/sdChannelMemory/iplSDMemory
- Full build passes; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. All three pools identical. Regressions 0; forbidden-pattern additions 0; readability warnings 0. Raw output: build/rx7/final-gate.txt.
- MemoryCardManager: 23 -> 24 exact functions, code 4080 -> 4572 / 5396, no data section. getComment is 100.0%, 123/123 instructions, diffs 0 after the clean build. CardSequence remains 27/30 exact, code 4168/9852, data 1496/1496. SDMemory remains 64/66 in objdiff, code 14812/20872, data 3344/3344.
- The clean gate reports 64/66 instruction-exact SD functions, versus the preliminary 63/66. SD source is byte-identical to the starting snapshot, and its baseline-source debugger object also matches updateState with zero differences against the fresh target. This is not an additional source gain; only getComment is new.
- Regenerated progress/report and build/43U/ok successfully. Ran decomp_status.py and the repository-wide completion checker; the latter still reports the project's existing incomplete units. This worker does not claim whole-project completion or new linking.
- Queued icon searches were temporarily stopped only while the clean rebuild replaced their inputs; they held no CPU slot and had not started their timed search. They resumed against the rebuilt inputs. The shared 24-slot limit was never bypassed. Still-queued processes were also staggered to avoid synchronized polling starvation; no completed trial was discarded.

Final search and handoff audit
- All six final GX searches completed their 1200-second runs. Icon seeds 7/19/31 ran 1545/1697/1393 trials from the private 93.35% candidate without improvement. Banner seeds 7/19/31 ran 1072/1361/1382 trials from 90.42453% without improvement. Logs: build/rx7/search/{icon,banner}-final-{7,19,31}/search.log. No fuzzy-only candidate was applied.
- Manual compiled source trials: SD 13, thread 21, move 7, icon 28, comment 25, banner 14. Every assigned open function received at least three distinct source attempts, target-register mapping, and validated baseline/candidate allocator captures. update_file_array remains 100.0%, 90/90 instructions, diffs 0, with no edit.
- The shared search script's global 24-slot lock block and the private copy's block are byte-identical. A local waiting wrapper staggered the last two queued jobs through existing lock slots; each search still acquired its own normal global lock before doing compiler work. Both final processes and the watcher exited successfully.
- Source commit: 0100c7bc (match memory card comment trimming). Only getComment changed. After the clean gate and completed searches, MemoryCardManager source SHA256 remains d466a4cfff609ff4cd4e01f727d06b247e19d5ecc57730c957ddf92a32bc78ca; SDMemory and CardSequence sources remain unchanged. Final DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d.
- Final accepted scores: getComment 98.94309 -> 100.0; SDMemory::create 99.15884 -> 99.15884; cardThreadMain 97.9402 -> 97.9402; runCardMoveOrCopy 97.88651 -> 97.88651; _create_icon 87.55 -> 87.55; create_banner 90.42453 -> 90.42453. GATE PASS is recorded in build/rx7/final-gate.txt. This handoff contains one new exact function; five assigned functions still need work.
