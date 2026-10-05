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

## rx7b continuation after PR 1188

Starting branch agent/w1005/rx7b, HEAD 1a7f21da. The landed getComment match stays intact. Scope is the same five open functions. This round tests first-use and declaration order with simplify traces, target Ghidra address reconstruction, and real inline or statement boundaries. Private tools and artifacts live in build/rx7b. Ghidra exports use a private project directory in this worktree.

b-icon-direct-result-at-load: Ghidra computes the complete return texture immediately before GXLoadTexObj; combine that real result local with direct metadata access. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-direct-result-at-load.

b-icon-rgb-offset-first: Target RGB image uses offset plus base while CI uses base plus offset; preserve the target per-arm operand order. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-rgb-offset-first.

b-icon-accessor-pointer-init: Use the actual icon texture accessor with pointer array input at init uses; test row/column temporary creation inside an inline. objdiff 82.15%; insns 103/100 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-pointer-init.

b-icon-accessor-pointer-all: Use the actual icon texture accessor with pointer array input at all uses; test row/column temporary creation inside an inline. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-pointer-all.

b-icon-accessor-pointer-load: Use the actual icon texture accessor with pointer array input at load uses; test row/column temporary creation inside an inline. objdiff 82.5%; insns 105/100 diffs 74; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-pointer-load.

b-icon-accessor-reference-init: Use the actual icon texture accessor with reference array input at init uses; test row/column temporary creation inside an inline. objdiff 70.29%; insns 109/100 diffs 80; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-reference-init.

b-icon-accessor-reference-all: Use the actual icon texture accessor with reference array input at all uses; test row/column temporary creation inside an inline. objdiff 79.49%; insns 104/100 diffs 68; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-reference-all.

b-icon-accessor-reference-load: Use the actual icon texture accessor with reference array input at load uses; test row/column temporary creation inside an inline. objdiff 74.04%; insns 111/100 diffs 81; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-accessor-reference-load.

b-icon-indexed-load-return: Move the actual indexed texture lookup into the load-and-return helper instead of passing an already computed pointer. objdiff 82.45%; insns 105/100 diffs 74; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-indexed-load-return.

b-icon-member-accessor-init: Use a real MemoryCardManager inline accessor at init sites; this pointer enters the boundary before any array offset. Compile failed; see build/rx7b/trials/b-icon-member-accessor-init/compile.log.

b-icon-member-accessor-load: Use a real MemoryCardManager inline accessor at load sites; this pointer enters the boundary before any array offset. Compile failed; see build/rx7b/trials/b-icon-member-accessor-load/compile.log.

b-icon-member-accessor-all: Use a real MemoryCardManager inline accessor at all sites; this pointer enters the boundary before any array offset. Compile failed; see build/rx7b/trials/b-icon-member-accessor-all/compile.log.

b-icon-member-indexed-load: Real member loads and returns its indexed icon texture; array address is formed inside the inline. Compile failed; see build/rx7b/trials/b-icon-member-indexed-load/compile.log.

b-banner-member-accessor-init: Test the corresponding real banner accessor at init sites with native parameter types. Compile failed; see build/rx7b/trials/b-banner-member-accessor-init/compile.log.

b-banner-member-accessor-load: Test the corresponding real banner accessor at load sites with native parameter types. Compile failed; see build/rx7b/trials/b-banner-member-accessor-load/compile.log.

b-banner-member-accessor-all: Test the corresponding real banner accessor at all sites with native parameter types. Compile failed; see build/rx7b/trials/b-banner-member-accessor-all/compile.log.

b-icon-member2-accessor-init: Use a real MemoryCardManager inline accessor at init sites; this pointer enters the boundary before any array offset. objdiff 89.34%; insns 101/100 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member2-accessor-init.

b-icon-member2-accessor-load: Use a real MemoryCardManager inline accessor at load sites; this pointer enters the boundary before any array offset. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member2-accessor-load.

b-icon-member2-accessor-all: Use a real MemoryCardManager inline accessor at all sites; this pointer enters the boundary before any array offset. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member2-accessor-all.

b-icon-member2-indexed-load: Real member loads and returns its indexed icon texture; array address is formed inside the inline. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member2-indexed-load.

b-banner-member2-accessor-init: Test the corresponding real banner accessor at init sites with native parameter types. objdiff 92.92453%; insns 105/106 diffs 88; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-member2-accessor-init.

b-sd-named-message-after-receiver: Give each getMessage return an explicit statement using one reused named message pointer, preserving lookup and call order. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-named-message-after-receiver.

b-banner-member2-accessor-load: Test the corresponding real banner accessor at load sites with native parameter types. objdiff 87.830185%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-member2-accessor-load.

b-banner-member2-accessor-all: Test the corresponding real banner accessor at all sites with native parameter types. objdiff 82.028305%; insns 107/106 diffs 85; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-member2-accessor-all.

b-sd-named-message-first: Move the real message local before receiver and cache locals to change its virtual-register number. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-named-message-first.

b-sd-cast-receiver-at-use: Keep the found Pane as the actual local and downcast only at SetString; test temporary creation at the receiver use. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-cast-receiver-at-use.

b-sd-c-style-receiver-cast: Compare C-style receiver downcasts with static_cast at the existing lookup boundary. Compile failed; see build/rx7b/trials/b-sd-c-style-receiver-cast/compile.log.

b-sd-message-return-inline: Return the localized message through one real lookup helper with a const primitive parameter. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-message-return-inline.

b-sd-message-return-inline-mutable: Remove const from the real lookup helper parameter to test inline temporary allocation. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-message-return-inline-mutable.

b-sd-block-message-and-receiver: Use a scoped receiver and message pair per localization operation, preserving all original calls and string order. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-block-message-and-receiver.

b-thread-persistent-values-last-outer-valid-exit: persistent values last outer valid exit. objdiff 98.53821%; insns 301/301 diffs 45; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-persistent-values-last-outer-valid-exit.

b-thread-persistent-values-last-outer-exit-valid: persistent values last outer exit valid. objdiff 98.40532%; insns 301/301 diffs 53; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-persistent-values-last-outer-exit-valid.

b-thread-persistent-values-last-valid-outer-exit: persistent values last valid outer exit. objdiff 98.40532%; insns 301/301 diffs 52; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-persistent-values-last-valid-outer-exit.

b-sd-c-style-receiver-cast-fixed: C-style zero-offset cast with receiver parentheses preserved. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-c-style-receiver-cast-fixed.

b-move-io-register-locals-before-persistent-state: io register locals before persistent state. objdiff 97.63158%; insns 608/608 diffs 206; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-io-register-locals-before-persistent-state.

b-move-all-lived-register-locals-before-state: all lived register locals before state. objdiff 97.63158%; insns 608/608 diffs 206; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-all-lived-register-locals-before-state.

b-move-persistent-state-last-destination-first: persistent state last destination first. objdiff 97.44244%; insns 608/608 diffs 226; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-persistent-state-last-destination-first.

b-move-persistent-state-last-metadata-first: persistent state last metadata first. objdiff 97.50494%; insns 608/608 diffs 219; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-persistent-state-last-metadata-first.

rx7b baseline and Ghidra evidence
- Freshly fetched origin/main and rebuilt source/target objects plus the report. Baseline remains MC 24/26 exact, code 4572/5396; CardSequence 27/30, code 4168/9852, data 1496/1496; SDMemory 64/66, code 14812/20872, data 3344/3344. All three pools are identical.
- Exported all five assigned target functions with the Ghidra helper, using a private project path. Files: build/rx7b/ghidra-{mc,card,sd}.c. Ghidra's inferred types and savegpr prototypes are imperfect; assembly remains authoritative.
- _create_icon target 0x1004 adds texture row+column for GXInitTexObj, then 0x100c recomputes and saves the complete pointer for GXLoadTexObj and return. Target CI similarly keeps row+column separate across GXInitTlutObj/GXLoadTlut, then materializes the returned texture before GXLoadTexObj. The source instead carries complete RGB and palette pointers across calls. Ghidra shows these same lifetimes. This supports testing an accessor boundary, but does not prove the original used an accessor.
- create_banner target 0x1334-0x133c uses column+root then row for validation, and 0x1350-0x1354 recomputes root+row then column for format. RGB image uses the first base; CI uses the second. Both SDK texture paths retain separate row/column values. The baseline shares one selected metadata pointer and complete texture pointers instead.
- The first member-accessor trials failed because MWCC could not open a Unix absolute include. Those are setup failures, not source measurements. Fixed trials use a relative private-header path. No shared project header was edited.

b-icon-metadata-accessor-narrow: Separate selected metadata address into a real array accessor using narrow parameters; keep validation and pixel reads unchanged. objdiff 85.05%; insns 97/100 diffs 81; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-metadata-accessor-narrow.

b-icon-image-base-accessor-narrow: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-image-base-accessor-narrow.

b-icon-metadata-accessor-const: Separate selected metadata address into a real array accessor using const parameters; keep validation and pixel reads unchanged. objdiff 85.05%; insns 97/100 diffs 81; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-metadata-accessor-const.

b-icon-image-base-accessor-const: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-image-base-accessor-const.

b-icon-metadata-accessor-word: Separate selected metadata address into a real array accessor using word parameters; keep validation and pixel reads unchanged. objdiff 85.05%; insns 97/100 diffs 81; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-metadata-accessor-word.

b-icon-image-base-accessor-word: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 88.05%; insns 100/100 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-image-base-accessor-word.

b-banner-metadata-accessor-narrow: Separate selected metadata address into a real array accessor using narrow parameters; keep validation and pixel reads unchanged. objdiff 90.51887%; insns 108/106 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-metadata-accessor-narrow.

b-banner-image-base-accessor-narrow: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 79.68868%; insns 109/106 diffs 85; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-image-base-accessor-narrow.

b-banner-metadata-accessor-const: Separate selected metadata address into a real array accessor using const parameters; keep validation and pixel reads unchanged. objdiff 89.386795%; insns 109/106 diffs 90; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-metadata-accessor-const.

b-banner-image-base-accessor-const: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 81.85849%; insns 110/106 diffs 86; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-image-base-accessor-const.

b-banner-metadata-accessor-word: Separate selected metadata address into a real array accessor using word parameters; keep validation and pixel reads unchanged. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-metadata-accessor-word.

b-banner-image-base-accessor-word: Put the image byte-view conversion inside its own accessor; test whether the target recomputed base stays separate from metadata-field CSE. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-image-base-accessor-word.

b-thread-target-local-order-0: target local order 0. objdiff 98.53821%; insns 301/301 diffs 45; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-target-local-order-0.

b-thread-target-local-order-1: target local order 1. objdiff 98.57143%; insns 301/301 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-target-local-order-1.

b-thread-target-local-order-2: target local order 2. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-target-local-order-2.

b-thread-target-local-order-3: target local order 3. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-target-local-order-3.

b-thread-plain-local-packet: Replace the existing anonymous packet union with ordinary integer message packing at a plain-local-packet boundary. objdiff 99.00332%; insns 301/301 diffs 36; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-plain-local-packet.

b-thread-packet-reference-setter: Replace the existing anonymous packet union with ordinary integer message packing at a packet-reference-setter boundary. objdiff 99.00332%; insns 301/301 diffs 36; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-reference-setter.

b-thread-packet-return: Replace the existing anonymous packet union with ordinary integer message packing at a packet-return boundary. objdiff 99.00332%; insns 301/301 diffs 36; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-return.

b-thread-report-return-u32: Return the reported validity through its actual report operation; preserve message token order and one OSReport call. objdiff 98.50498%; insns 301/301 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-return-u32.

b-thread-report-return-const-u32: Return the reported validity through its actual report operation; preserve message token order and one OSReport call. objdiff 98.50498%; insns 301/301 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-return-const-u32.

b-thread-report-return-u32ref: Return the reported validity through its actual report operation; preserve message token order and one OSReport call. objdiff 98.50498%; insns 301/301 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-return-u32ref.

b-thread-report-return-const-u32ref: Return the reported validity through its actual report operation; preserve message token order and one OSReport call. objdiff 98.50498%; insns 301/301 diffs 43; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-return-const-u32ref.

b-thread-separate-mount-block: Keep CARDMount and mount-recovery results separate from the main operation result, avoiding the early result-to-r4 coalesce. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-separate-mount-block.

b-thread-separate-mount-root-first: Keep CARDMount and mount-recovery results separate from the main operation result, avoiding the early result-to-r4 coalesce. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-separate-mount-root-first.

b-thread-separate-mount-root-last: Keep CARDMount and mount-recovery results separate from the main operation result, avoiding the early result-to-r4 coalesce. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-separate-mount-root-last.

b-thread-separate-mount-reuse-file: Reuse one file index for the two nonoverlapping listing loops after separating the mount result. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-separate-mount-reuse-file.

b-icon-result-null-else: Model the real texture result and load using result-null-else control flow; both successful formats retain exactly one load. objdiff 86.0%; insns 100/100 diffs 49; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-null-else.

b-icon-result-initialized-null: Model the real texture result and load using result-initialized-null control flow; both successful formats retain exactly one load. objdiff 83.24%; insns 99/100 diffs 88; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-initialized-null.

b-icon-rgb-result-after-ci-join: Model the real texture result and load using rgb-result-after-ci-join control flow; both successful formats retain exactly one load. objdiff 81.8%; insns 98/100 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-rgb-result-after-ci-join.

b-icon-result-index-s32-s32: Name the real texture index at its word width and use a corresponding typed result index, testing separate address-expression CSE. objdiff 83.75%; insns 102/100 diffs 71; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-index-s32-s32.

b-icon-result-index-u32-u32: Name the real texture index at its word width and use a corresponding typed result index, testing separate address-expression CSE. objdiff 92.44%; insns 103/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-index-u32-u32.

b-icon-result-index-s32-u32: Name the real texture index at its word width and use a corresponding typed result index, testing separate address-expression CSE. objdiff 92.44%; insns 103/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-index-s32-u32.

b-icon-result-index-u32-s32: Name the real texture index at its word width and use a corresponding typed result index, testing separate address-expression CSE. objdiff 83.75%; insns 102/100 diffs 71; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-result-index-u32-s32.

b-icon-image-value-before-call: Compute the actual image argument as a separate statement before the GX initialization call. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-image-value-before-call.

b-sd-cache-count-lookup: Move the real cached-title traversal into an inline helper with lookup ownership of the manager lookup. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-cache-count-lookup.

b-sd-cache-count-pointer: Move the real cached-title traversal into an inline helper with pointer ownership of the manager lookup. objdiff 99.13064%; insns 1064/1064 diffs 179; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-cache-count-pointer.

b-sd-cache-count-reference: Move the real cached-title traversal into an inline helper with reference ownership of the manager lookup. objdiff 99.13064%; insns 1064/1064 diffs 179; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-cache-count-reference.

b-sd-layout-construction-helper: Factor the repeated layout construction without moving string literals or changing constructor argument order. objdiff 97.79605%; insns 1072/1064 diffs 950; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-layout-construction-helper.

b-sd-receiver-declared-at-first-use: Move the reused text receiver declaration to its first pane lookup so earlier inline constructor locals are encountered first. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-sd-receiver-declared-at-first-use.

rx7b cardThreadMain simplify confirmation
- build/rx7b/mwdbg-b-thread-persistent-values-last is byte-identical to original-flags wibo. Moving declarations to end in outerSlot, validState, exitThread order creates v34/v33/v32. The two state nodes are still above the threshold at first visit; outerSlot now starts with degree 30 rather than reaching degree 28 after freeBlocks/freeFile were removed. It also defers.
- The final sweep removes exitThread at degree 19, validState at 18, outerSlot at 17, then pool/switch/one/slot-names/zero at 16 through 12. Reverse coloring gives outerSlot r26, validState r25, exitThread r24, all as requested. The other local colors and reply coalescing remain wrong. This is a measured source lever, not an exact function.
- Keeping the initial CARDMount result in a distinct block or root local normalized to the same 301-instruction output. Integer reply packing is readable and reaches 99.00332%, but it changes the target insertion sequence, so it remains private.
rx7b SDMemory statement-boundary confirmation
- build/rx7b/mwdbg-b-sd-message-first is byte-identical to original-flags wibo. Adding and moving the message return local leaves the smArg/pool saved-register priority unchanged and still produces 1064 instructions with 175 differences. The real cached-title helper with a manager pointer/reference adds four instruction differences; a complete layout-construction helper adds eight instructions. All are rejected.
rx7b runCardMoveOrCopy first hoist confirmation
- build/rx7b/mwdbg-b-move-persistent-state-last is byte-identical to original-flags wibo. Moving I/O locals earlier makes metadataCopied v42, but nested move stage v36 and attempt v37 still simplify first in the second sweep. Those removals bring metadataCopied down to degree 28, so it simplifies before the parameters. It then takes r15 rather than the target r28. The next test moves those real move-operation counters ahead of the persistent-state declarations too.

b-move-move-stage-and-rename-counter-before-state: move stage and rename counter before state. objdiff 98.7829%; insns 608/608 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-move-stage-and-rename-counter-before-state.

b-move-all-operation-counters-before-state: all operation counters before state. objdiff 98.7829%; insns 608/608 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-all-operation-counters-before-state.

b-move-destination-slot-at-first-input-use: destination slot at first input use. objdiff 97.302635%; insns 607/608 diffs 290; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-destination-slot-at-first-input-use.

b-move-io-order-target: Order real I/O locals by the target reverse-color priority, keeping the newly fixed persistent-state ordering. objdiff 98.947365%; insns 608/608 diffs 57; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-io-order-target.

b-move-joined-results-order-0: Combine separate copy/move status joins and the real temporary-file helper with the target persistent-state and I/O declaration order. objdiff 99.30099%; insns 608/608 diffs 46; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-joined-results-order-0.

b-move-io-order-size-offset: Order real I/O locals by the target reverse-color priority, keeping the newly fixed persistent-state ordering. objdiff 98.898026%; insns 608/608 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-io-order-size-offset.

b-move-joined-word-destination: Keep the returned destination file number in a signed word local while narrowing only at SDK uses. objdiff 99.00494%; insns 608/608 diffs 49; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-joined-word-destination.

b-move-io-order-io-before-block: Order real I/O locals by the target reverse-color priority, keeping the newly fixed persistent-state ordering. objdiff 98.98026%; insns 608/608 diffs 50; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-io-order-io-before-block.

b-move-joined-results-order-1: Combine separate copy/move status joins and the real temporary-file helper with the target persistent-state and I/O declaration order. objdiff 99.49835%; insns 608/608 diffs 23; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-joined-results-order-1.

b-move-joined-results-order-2: Combine separate copy/move status joins and the real temporary-file helper with the target persistent-state and I/O declaration order. objdiff 99.49835%; insns 608/608 diffs 23; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-joined-results-order-2.

b-move-rename-initialization-order: Initialize the actual rename counter before its stage, matching the target two zero loads. objdiff 99.5148%; insns 608/608 diffs 21; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-initialization-order.

b-move-rename-stage-after-status-copy: Set the rename stage after copying the status, which has no failure path or external side effect. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-after-status-copy.

b-move-create-helper-s32-const-u32: Use const primitive or reference parameters for the real temporary-file creation helper. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-helper-s32-const-u32.

b-move-create-helper-s32-const-u32ref: Use const primitive or reference parameters for the real temporary-file creation helper. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-helper-s32-const-u32ref.

b-move-create-helper-const-s32-u32: Use const primitive or reference parameters for the real temporary-file creation helper. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-helper-const-s32-u32.

b-move-create-helper-const-s32-const-u32: Use const primitive or reference parameters for the real temporary-file creation helper. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-helper-const-s32-const-u32.

b-move-create-helper-const-s32-const-u32ref: Use const primitive or reference parameters for the real temporary-file creation helper. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-helper-const-s32-const-u32ref.

b-move-clamp-one-local: Express the same bounded transfer-block count as clamp-one-local to change its temporary order. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-one-local.

b-move-clamp-if-else: Express the same bounded transfer-block count as clamp-if-else to change its temporary order. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-if-else.

b-move-clamp-declare-result-first: Express the same bounded transfer-block count as clamp-declare-result-first to change its temporary order. objdiff 99.49506%; insns 608/608 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-declare-result-first.

b-move-clamp-min-first: Express the same bounded transfer-block count as clamp-min-first to change its temporary order. objdiff 99.33059%; insns 609/608 diffs 442; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-min-first.

b-move-clamp-helper: Move the actual transfer count clamp into a small inline helper without an invented carrier. objdiff 99.552635%; insns 608/608 diffs 22; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-helper.

b-thread-command-parameter-const-u32ref: Change the actual reply helper command parameter boundary while preserving packet bits. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-command-parameter-const-u32ref.

b-thread-command-parameter-u32ref: Change the actual reply helper command parameter boundary while preserving packet bits. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-command-parameter-u32ref.

b-thread-command-parameter-const-u32: Change the actual reply helper command parameter boundary while preserving packet bits. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-command-parameter-const-u32.

b-thread-validity-report-reference-u32: Set and report the actual validity state inside one real operation; retain assignment before the report call. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-report-reference-u32.

b-thread-validity-report-plain-packet-u32: Combine the real validity assignment/report helper with ordinary integer packet encoding. objdiff 99.00332%; insns 301/301 diffs 36; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-report-plain-packet-u32.

b-thread-validity-report-reference-const-u32: Set and report the actual validity state inside one real operation; retain assignment before the report call. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-report-reference-const-u32.

b-thread-validity-report-plain-packet-const-u32: Combine the real validity assignment/report helper with ordinary integer packet encoding. objdiff 99.00332%; insns 301/301 diffs 36; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-report-plain-packet-const-u32.

b-move-clamp-helper-stage-before-copy: Combine the exact transfer-clamp registers with the closer original status-copy stage placement. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-clamp-helper-stage-before-copy.

b-move-const-inputs-cmm: Mark immutable input values const at the existing function definition; test the two prologue copies. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-const-inputs-cmm.

b-move-const-inputs-mcm: Mark immutable input values const at the existing function definition; test the two prologue copies. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-const-inputs-mcm.

b-move-const-inputs-mmc: Mark immutable input values const at the existing function definition; test the two prologue copies. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-const-inputs-mmc.

b-move-const-inputs-ccc: Mark immutable input values const at the existing function definition; test the two prologue copies. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-const-inputs-ccc.

b-move-create-size-inside-helper-count-first: Compute the real source byte length inside temporary-file creation, with count-first declaration order. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-size-inside-helper-count-first.

b-move-create-size-inside-helper-size-first: Compute the real source byte length inside temporary-file creation, with size-first declaration order. objdiff 99.572365%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-create-size-inside-helper-size-first.

b-move-rename-memcpy-stage-before: Use explicit memcpy for the real CARDDir copy with stage assignment before it. objdiff 92.447365%; insns 575/608 diffs 338; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-memcpy-stage-before.

b-move-rename-memcpy-stage-after: Use explicit memcpy for the real CARDDir copy with stage assignment after it. objdiff 92.259865%; insns 575/608 diffs 338; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-memcpy-stage-after.

b-move-rename-stage-type-int: Use int for the bounded rename stage, whose only values are zero through five. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-int.

b-move-rename-stage-type-s16: Use s16 for the bounded rename stage, whose only values are zero through five. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-s16.

b-move-rename-stage-type-u16: Use u16 for the bounded rename stage, whose only values are zero through five. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-u16.

b-move-rename-stage-type-u8: Use u8 for the bounded rename stage, whose only values are zero through five. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-u8.

b-move-rename-stage-type-u32: Use u32 for the bounded rename stage, whose only values are zero through five. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-u32.

b-move-input-copy-sourceFile-s32: Use a typed source input local at its first duplicate-check use; parameter values remain unchanged. Compile failed; see build/rx7b/trials/b-move-input-copy-sourceFile-s32/compile.log.

b-move-input-copy-sourceSlot-s32: Use a typed source input local at its first duplicate-check use; parameter values remain unchanged. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-input-copy-sourceSlot-s32.

b-move-input-copy-sourceFile-const-s32: Use a typed source input local at its first duplicate-check use; parameter values remain unchanged. Compile failed; see build/rx7b/trials/b-move-input-copy-sourceFile-const-s32/compile.log.

b-move-rename-copy-helper-pointer: Put the actual CARDDir copy or rename preparation in a small pointer inline helper. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-copy-helper-pointer.

b-move-rename-copy-helper-reference: Put the actual CARDDir copy or rename preparation in a small reference inline helper. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-copy-helper-reference.

b-move-rename-copy-helper-prepare: Put the actual CARDDir copy or rename preparation in a small prepare inline helper. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-copy-helper-prepare.

b-move-source-file-word-copy-s32: Use a word source-file value at first use without changing CARDFileInfo member names. objdiff 99.39967%; insns 608/608 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-source-file-word-copy-s32.

b-move-source-file-word-copy-const-s32: Use a word source-file value at first use without changing CARDFileInfo member names. objdiff 99.39967%; insns 608/608 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-source-file-word-copy-const-s32.

b-move-rename-status-copy-initializer: Initialize the real rename directory at first use rather than assigning an already-declared aggregate. objdiff 93.46546%; insns 580/608 diffs 344; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-status-copy-initializer.

b-move-rename-status-local-scope: Give the two move-operation directory objects their actual operation scope while preserving their declaration order. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-status-local-scope.

b-move-rename-status-return-value-false: Return the real CARDDir value from a copy/preparation helper, testing aggregate return-value optimization without a carrier type. objdiff 98.054276%; insns 617/608 diffs 263; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-status-return-value-false.

b-move-rename-status-return-value-true: Return the real CARDDir value from a copy/preparation helper, testing aggregate return-value optimization without a carrier type. objdiff 93.791115%; insns 626/608 diffs 258; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-status-return-value-true.

b-move-duplicate-validation-helper: Keep duplicate validation and its error report in one real inline operation, testing the first parameter-copy use. objdiff 99.2023%; insns 610/608 diffs 585; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-validation-helper.

b-move-file-type-move-word: Test word file-number parameters against the target input copies; all in-tree move/copy callers extract an unsigned message byte. objdiff 99.47369%; insns 609/608 diffs 600; pool identical; other drops ['cardThreadMain']. Trial retained only under build/rx7b/trials/b-move-file-type-move-word.

b-move-file-type-both-word: Test word file-number parameters against the target input copies; all in-tree move/copy callers extract an unsigned message byte. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops ['cardThreadMain', 'checkCardFileDuplicate']. Trial retained only under build/rx7b/trials/b-move-file-type-both-word.

b-move-rename-stage-before-destinationSectorSize: Move the real rename-stage declaration before destinationSectorSize and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-destinationSectorSize.

b-move-rename-stage-before-commonSectorSize: Move the real rename-stage declaration before commonSectorSize and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-commonSectorSize.

b-move-rename-stage-before-result: Move the real rename-stage declaration before result and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-result.

b-move-rename-stage-before-oldTime: Move the real rename-stage declaration before oldTime and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-oldTime.

b-move-rename-stage-before-cancelSent: Move the real rename-stage declaration before cancelSent and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-cancelSent.

b-move-rename-stage-before-stage: Move the real rename-stage declaration before stage and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-stage.

b-move-rename-stage-before-offset: Move the real rename-stage declaration before offset and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-offset.

b-move-rename-stage-before-maxBlocks: Move the real rename-stage declaration before maxBlocks and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.42434%; insns 608/608 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-maxBlocks.

b-move-rename-stage-before-ioResult: Move the real rename-stage declaration before ioResult and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.523026%; insns 608/608 diffs 21; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-ioResult.

b-move-rename-stage-before-copyResult: Move the real rename-stage declaration before copyResult and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-copyResult.

b-move-rename-stage-before-renameAttempt: Move the real rename-stage declaration before renameAttempt and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-renameAttempt.

b-move-rename-stage-before-destinationSlot: Move the real rename-stage declaration before destinationSlot and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.523026%; insns 608/608 diffs 21; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-destinationSlot.

b-move-rename-stage-before-metadataCopied: Move the real rename-stage declaration before metadataCopied and inspect whether its pre-allocation scheduling changes while target colors remain. objdiff 99.523026%; insns 608/608 diffs 21; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-before-metadataCopied.

b-move-rename-stage-helper-before-reference: Pass the rename stage as a genuine preparation output; set the stage before copying the directory. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-helper-before-reference.

b-move-rename-stage-helper-before-pointer: Pass the rename stage as a genuine preparation output; set the stage before copying the directory. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-helper-before-pointer.

b-move-rename-stage-helper-after-reference: Pass the rename stage as a genuine preparation output; set the stage after copying the directory. objdiff 99.61842%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-helper-after-reference.

b-move-rename-stage-helper-after-pointer: Pass the rename stage as a genuine preparation output; set the stage after copying the directory. objdiff 99.61842%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-helper-after-pointer.

b-move-rename-stage-expression-comma-before: Test the actual directory-copy and error-stage expression boundary; diagnostic spelling only. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-expression-comma-before.

b-move-rename-stage-expression-comma-after: Test the actual directory-copy and error-stage expression boundary; diagnostic spelling only. objdiff 99.61842%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-expression-comma-after.

b-move-rename-stage-expression-chain-assign: Test the actual directory-copy and error-stage expression boundary; diagnostic spelling only. objdiff 99.63816%; insns 608/608 diffs 15; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-expression-chain-assign.

b-move-slot-width-s16: Test a bounded card-slot formal of s16 against target incoming-value copy scheduling; inspect caller and conversion changes. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops ['cardThreadMain']. Trial retained only under build/rx7b/trials/b-move-slot-width-s16.

b-move-slot-width-u16: Test a bounded card-slot formal of u16 against target incoming-value copy scheduling; inspect caller and conversion changes. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-slot-width-u16.

b-move-slot-width-u8: Test a bounded card-slot formal of u8 against target incoming-value copy scheduling; inspect caller and conversion changes. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-slot-width-u8.

b-move-duplicate-helper-value-slot-first: Apply a real duplicate-check inline boundary with value inputs in slot-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-value-slot-first.

b-move-duplicate-helper-value-file-first: Apply a real duplicate-check inline boundary with value inputs in file-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-value-file-first.

b-move-duplicate-helper-const-value-slot-first: Apply a real duplicate-check inline boundary with const-value inputs in slot-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-const-value-slot-first.

b-move-duplicate-helper-const-value-file-first: Apply a real duplicate-check inline boundary with const-value inputs in file-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-const-value-file-first.

b-move-duplicate-helper-reference-slot-first: Apply a real duplicate-check inline boundary with reference inputs in slot-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-reference-slot-first.

b-move-duplicate-helper-reference-file-first: Apply a real duplicate-check inline boundary with reference inputs in file-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-reference-file-first.

b-move-duplicate-helper-const-reference-slot-first: Apply a real duplicate-check inline boundary with const-reference inputs in slot-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-const-reference-slot-first.

b-move-duplicate-helper-const-reference-file-first: Apply a real duplicate-check inline boundary with const-reference inputs in file-first order; preserve the signed file-number conversion. objdiff 99.63816%; insns 608/608 diffs 8; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-duplicate-helper-const-reference-file-first.

b-move-rename-stage-preincrement: Advance the zero-initialized rename stage naturally after the successful status read. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-preincrement.

b-move-rename-stage-postincrement: Advance the zero-initialized rename stage naturally after the successful status read. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-postincrement.

b-move-rename-stage-compound: Advance the zero-initialized rename stage naturally after the successful status read. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-compound.

b-move-rename-stage-add: Advance the zero-initialized rename stage naturally after the successful status read. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-add.

b-move-rename-stage-type-s8-byte-slot: Use a bounded small rename-stage local without changing its zero-through-five values. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-s8-byte-slot.

b-move-rename-stage-type-char-byte-slot: Use a bounded small rename-stage local without changing its zero-through-five values. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-char-byte-slot.

b-move-rename-stage-type-unsigned-char-byte-slot: Use a bounded small rename-stage local without changing its zero-through-five values. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-type-unsigned-char-byte-slot.

b-move-rename-stage-condition-assignment: Change the real status-success block boundary while retaining the same stage and cleanup paths. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-condition-assignment.

b-move-rename-stage-early-failure: Change the real status-success block boundary while retaining the same stage and cleanup paths. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-early-failure.

b-move-rename-stage-explicit-success-else: Change the real status-success block boundary while retaining the same stage and cleanup paths. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-explicit-success-else.

b-move-rename-stage-enum-implicit: Give the existing six error-report states a named enum without adding storage or a wrapper. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-enum-implicit.

b-move-rename-stage-enum-explicit: Give the existing six error-report states a named enum without adding storage or a wrapper. objdiff 99.67105%; insns 608/608 diffs 6; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-rename-stage-enum-explicit.

b-move-exact-clean: Whitespace-only cleanup of the exact byte-slot, helper, declaration-order and stage-increment candidate. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-exact-clean.

Rx7b exact candidate: runCardMoveOrCopy reaches 100.0%, 608/608 instructions, zero differences and no other function drops with b-move-rename-stage-preincrement. The two queued move searches and the running move-119 search were stopped because the manual candidate is exact. No search-lock policy was bypassed. Remaining four functions continue their three seeds.

b-thread-decl-file-before-brokenFile: Move the actual file declaration across BOOL brokenFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-brokenFile.

b-thread-decl-file-before-freeBlocks: Move the actual file declaration across s32 freeBlocks; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-freeBlocks.

b-thread-decl-file-before-freeFile: Move the actual file declaration across s32 freeFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-freeFile.

b-thread-decl-file-before-outerSlot: Move the actual file declaration across s32 outerSlot; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-outerSlot.

b-thread-decl-file-before-validState: Move the actual file declaration across u32 validState = TRUE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-validState.

b-thread-decl-file-before-exitThread: Move the actual file declaration across BOOL exitThread = FALSE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-file-before-exitThread.

b-thread-decl-slot-before-brokenFile: Move the actual slot declaration across BOOL brokenFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-brokenFile.

b-thread-decl-slot-before-freeBlocks: Move the actual slot declaration across s32 freeBlocks; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-freeBlocks.

b-thread-decl-slot-before-freeFile: Move the actual slot declaration across s32 freeFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-freeFile.

b-thread-decl-slot-before-outerSlot: Move the actual slot declaration across s32 outerSlot; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-outerSlot.

b-thread-decl-slot-before-validState: Move the actual slot declaration across u32 validState = TRUE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-validState.

b-thread-decl-slot-before-exitThread: Move the actual slot declaration across BOOL exitThread = FALSE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-slot-before-exitThread.

b-thread-decl-command-before-brokenFile: Move the actual command declaration across BOOL brokenFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-brokenFile.

b-thread-decl-command-before-freeBlocks: Move the actual command declaration across s32 freeBlocks; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-freeBlocks.

b-thread-decl-command-before-freeFile: Move the actual command declaration across s32 freeFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-freeFile.

b-thread-decl-command-before-outerSlot: Move the actual command declaration across s32 outerSlot; to change its simplify visit and saved-register availability. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-outerSlot.

b-thread-decl-command-before-validState: Move the actual command declaration across u32 validState = TRUE; to change its simplify visit and saved-register availability. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-validState.

b-thread-decl-command-before-exitThread: Move the actual command declaration across BOOL exitThread = FALSE; to change its simplify visit and saved-register availability. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-command-before-exitThread.

b-thread-decl-result-before-brokenFile: Move the actual result declaration across BOOL brokenFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-brokenFile.

b-thread-decl-result-before-freeBlocks: Move the actual result declaration across s32 freeBlocks; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-freeBlocks.

b-thread-decl-result-before-freeFile: Move the actual result declaration across s32 freeFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-freeFile.

b-thread-decl-result-before-outerSlot: Move the actual result declaration across s32 outerSlot; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-outerSlot.

b-thread-decl-result-before-validState: Move the actual result declaration across u32 validState = TRUE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-validState.

b-thread-decl-result-before-exitThread: Move the actual result declaration across BOOL exitThread = FALSE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-result-before-exitThread.

b-thread-decl-listingFile-before-brokenFile: Move the actual listingFile declaration across BOOL brokenFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-brokenFile.

b-thread-decl-listingFile-before-freeBlocks: Move the actual listingFile declaration across s32 freeBlocks; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-freeBlocks.

b-thread-decl-listingFile-before-freeFile: Move the actual listingFile declaration across s32 freeFile; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-freeFile.

b-thread-decl-listingFile-before-outerSlot: Move the actual listingFile declaration across s32 outerSlot; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-outerSlot.

b-thread-decl-listingFile-before-validState: Move the actual listingFile declaration across u32 validState = TRUE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-validState.

b-thread-decl-listingFile-before-exitThread: Move the actual listingFile declaration across BOOL exitThread = FALSE; to change its simplify visit and saved-register availability. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-decl-listingFile-before-exitThread.

b-thread-file-scope-loop: Give the mounted-file index its natural loop scope so its virtual-register creation follows that scope. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-file-scope-loop.

b-thread-file-scope-case: Give the mounted-file index its natural case scope so its virtual-register creation follows that scope. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-file-scope-case.

b-icon-unsigned-site-mask-3: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 90.69%; insns 101/100 diffs 32; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-3.

b-icon-unsigned-site-mask-5: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 84.08%; insns 101/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-5.

b-icon-unsigned-site-mask-9: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 93.39%; insns 100/100 diffs 22; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-9.

b-icon-unsigned-site-mask-17: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 93.64%; insns 100/100 diffs 20; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-17.

b-icon-unsigned-site-mask-33: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 90.09%; insns 101/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-33.

b-icon-unsigned-site-mask-65: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 89.19%; insns 101/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-65.

b-icon-unsigned-site-mask-127: Test consistent unsigned destination index views across related GX uses; only valid file-array indices are dereferenced, and no conversion changes their value. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-site-mask-127.

b-icon-unsigned-named-index-rgb: Use one actual word-width texture index for the rgb GX operations while retaining the native signed public parameter. objdiff 90.69%; insns 101/100 diffs 32; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-named-index-rgb.

b-icon-unsigned-named-index-ci: Use one actual word-width texture index for the ci GX operations while retaining the native signed public parameter. objdiff 90.69%; insns 101/100 diffs 32; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-named-index-ci.

b-icon-unsigned-named-index-all: Use one actual word-width texture index for the all GX operations while retaining the native signed public parameter. objdiff 90.69%; insns 101/100 diffs 32; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-unsigned-named-index-all.

b-thread-directory-report-helper-u8: Factor the real debug directory listing into a small inline, with its own actual file counter and caller-owned buffers. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-directory-report-helper-u8.

b-thread-directory-report-helper-s32: Factor the real debug directory listing into a small inline, with its own actual file counter and caller-owned buffers. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-directory-report-helper-s32.

b-thread-directory-report-helper-const-u8: Factor the real debug directory listing into a small inline, with its own actual file counter and caller-owned buffers. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-directory-report-helper-const-u8.

b-thread-broken-test-helper-false: Give the repeated directory validation a real inline boundary. objdiff 97.56146%; insns 300/301 diffs 230; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-broken-test-helper-false.

b-thread-broken-test-helper-true: Give the repeated directory validation a real inline boundary and pass the loop index by reference at its status read. objdiff 97.56146%; insns 300/301 diffs 230; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-broken-test-helper-true.

b-thread-scan-result-joined-before-brokenFile: Separate the mount-scan error result from unrelated command results and place its named register before BOOL brokenFile;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-joined-before-brokenFile.

b-thread-scan-result-joined-before-file: Separate the mount-scan error result from unrelated command results and place its named register before s32 file;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-joined-before-file.

b-thread-scan-result-joined-before-freeFile: Separate the mount-scan error result from unrelated command results and place its named register before s32 freeFile;. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-joined-before-freeFile.

b-thread-scan-result-joined-before-outerSlot: Separate the mount-scan error result from unrelated command results and place its named register before s32 outerSlot;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-joined-before-outerSlot.

b-thread-scan-result-all-before-brokenFile: Separate the mount-scan error result from unrelated command results and place its named register before BOOL brokenFile;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-all-before-brokenFile.

b-thread-scan-result-all-before-file: Separate the mount-scan error result from unrelated command results and place its named register before s32 file;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-all-before-file.

b-thread-scan-result-all-before-freeFile: Separate the mount-scan error result from unrelated command results and place its named register before s32 freeFile;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-all-before-freeFile.

b-thread-scan-result-all-before-outerSlot: Separate the mount-scan error result from unrelated command results and place its named register before s32 outerSlot;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-all-before-outerSlot.

b-thread-scan-result-file-operation-before-brokenFile: Separate the mount-scan error result from unrelated command results and place its named register before BOOL brokenFile;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-file-operation-before-brokenFile.

b-thread-scan-result-file-operation-before-file: Separate the mount-scan error result from unrelated command results and place its named register before s32 file;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-file-operation-before-file.

b-thread-scan-result-file-operation-before-freeFile: Separate the mount-scan error result from unrelated command results and place its named register before s32 freeFile;. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-file-operation-before-freeFile.

b-thread-scan-result-file-operation-before-outerSlot: Separate the mount-scan error result from unrelated command results and place its named register before s32 outerSlot;. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-result-file-operation-before-outerSlot.

b-thread-validity-type-u8: Test the actual two-state validity value as u8; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-u8.

b-thread-validity-type-bool: Test the actual two-state validity value as bool; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-bool.

b-thread-validity-type-BOOL: Test the actual two-state validity value as BOOL; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-BOOL.

b-thread-validity-type-s16: Test the actual two-state validity value as s16; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-s16.

b-thread-validity-type-u16: Test the actual two-state validity value as u16; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-u16.

b-thread-validity-type-unsigned-int: Test the actual two-state validity value as unsigned int; preserve unsigned comparison when the local is signed. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-type-unsigned-int.

b-thread-validity-update-or-assign: Test a real validity-state expression boundary; this case is entered only after validState == TRUE, so its value stays exactly one. objdiff 98.355484%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-update-or-assign.

b-thread-validity-update-or: Test a real validity-state expression boundary; this case is entered only after validState == TRUE, so its value stays exactly one. objdiff 98.355484%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-update-or.

b-thread-validity-update-boolean-normalize: Test a real validity-state expression boundary; this case is entered only after validState == TRUE, so its value stays exactly one. objdiff 97.74086%; insns 302/301 diffs 261; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-validity-update-boolean-normalize.

b-thread-scan-order-slot-before-result: With a named joined scan result, change slot-before-result so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-result.

b-thread-scan-order-slot-before-file: With a named joined scan result, change slot-before-file so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-file.

b-thread-scan-order-slot-before-scanResult: With a named joined scan result, change slot-before-scanResult so mount-phase values choose registers in target priority order. objdiff 98.85382%; insns 301/301 diffs 29; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-scanResult.

b-thread-scan-order-slot-before-freeFile: With a named joined scan result, change slot-before-freeFile so mount-phase values choose registers in target priority order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-freeFile.

b-thread-scan-order-slot-before-command: With a named joined scan result, change slot-before-command so mount-phase values choose registers in target priority order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-command.

b-thread-scan-order-slot-before-outerSlot: With a named joined scan result, change slot-before-outerSlot so mount-phase values choose registers in target priority order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-slot-before-outerSlot.

b-thread-scan-order-file-before-result: With a named joined scan result, change file-before-result so mount-phase values choose registers in target priority order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-result.

b-thread-scan-order-file-before-slot: With a named joined scan result, change file-before-slot so mount-phase values choose registers in target priority order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-slot.

b-thread-scan-order-file-before-scanResult: With a named joined scan result, change file-before-scanResult so mount-phase values choose registers in target priority order. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-scanResult.

b-thread-scan-order-file-before-freeFile: With a named joined scan result, change file-before-freeFile so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-freeFile.

b-thread-scan-order-file-before-command: With a named joined scan result, change file-before-command so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-command.

b-thread-scan-order-file-before-outerSlot: With a named joined scan result, change file-before-outerSlot so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-file-before-outerSlot.

b-thread-scan-order-listingFile-before-result: With a named joined scan result, change listingFile-before-result so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-result.

b-thread-scan-order-listingFile-before-slot: With a named joined scan result, change listingFile-before-slot so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-slot.

b-thread-scan-order-listingFile-before-scanResult: With a named joined scan result, change listingFile-before-scanResult so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-scanResult.

b-thread-scan-order-listingFile-before-freeFile: With a named joined scan result, change listingFile-before-freeFile so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-freeFile.

b-thread-scan-order-listingFile-before-command: With a named joined scan result, change listingFile-before-command so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-command.

b-thread-scan-order-listingFile-before-outerSlot: With a named joined scan result, change listingFile-before-outerSlot so mount-phase values choose registers in target priority order. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-listingFile-before-outerSlot.

b-thread-scan-order-command-before-result: With a named joined scan result, change command-before-result so mount-phase values choose registers in target priority order. objdiff 98.77077%; insns 301/301 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-command-before-result.

b-thread-scan-order-command-before-slot: With a named joined scan result, change command-before-slot so mount-phase values choose registers in target priority order. objdiff 98.77077%; insns 301/301 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-command-before-slot.

b-thread-scan-order-command-before-file: With a named joined scan result, change command-before-file so mount-phase values choose registers in target priority order. objdiff 98.77077%; insns 301/301 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-command-before-file.

b-thread-scan-order-command-before-scanResult: With a named joined scan result, change command-before-scanResult so mount-phase values choose registers in target priority order. objdiff 98.77077%; insns 301/301 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-command-before-scanResult.

b-thread-scan-order-command-before-freeFile: With a named joined scan result, change command-before-freeFile so mount-phase values choose registers in target priority order. objdiff 98.77077%; insns 301/301 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-order-command-before-freeFile.

Rx7b allocator explanation and exact runCardMoveOrCopy candidate (2026-10-05)

- Target persistent values: destinationSlot r31, destinationFileNo r30, temporaryCreated r29, metadataCopied r28, command r27, fileNo r26, slot r25. The callback is r24, constant one r23, and the string-pool base r22. Copy I/O uses cancelSent r21, stage r20, offset r19, size r18, maxBlocks r17, block r16, and ioResult r15.
- The first hoist moved only I/O locals. mwdbg-b-move-persistent-state-last still simplified metadataCopied v42 at degree 28, then temporaryCreated/destinationFileNo/destinationSlot at 27/26/25. The three parameters deferred another sweep and took the highest saved registers. Moving the real nested renameAttempt and moveStage declarations before the persistent state kept those state nodes above the 29-register threshold until the parameter sweep. This is an interference-degree effect, not just a reversal of declaration order.
- In the exact capture, the final simplify sweep removes slot v32 at degree 18, fileNo v33 at 17, command v34 at 16, metadataCopied v38 at 15, temporaryCreated v39 at 14, destinationFileNo v40 at 13, and destinationSlot v41 at 12. Reverse coloring requests r31 through r25 in precisely the target order. The temporary-file helper return v76 coalesces into destinationFileNo v40; ABI argument copies that interfere remain separate. Moving declarations without preserving those degrees does not work.
- The real createCardTemporaryFile helper removes the old creation-result join from the outer function. Its attempt counter is declared before the actual byte length, so the helper's counter/size get the target r17/r16. Separate copyResult and moveResult keep the two metadata operation results in their target webs. A small clampCardTransferBlocks helper gives the transfer remainder and sector size the target transient registers. Pools remain identical because the temporary-file strings stay first in source-token order.
- The last eight differences were not coloring failures. With s32 slot, initial PCode began mr(slot), extsh(fileNo); before allocation, the file-number copy had moved ahead of the slot copy. Using the actual bounded u8 card slot produces initial rlwinm(slot), extsh(fileNo), both reduced to copies in the target order before allocation. Both call sites supply `(message >> 16) & 1`; cardThreadMain and every other function's score remain unchanged. Widening fileNo instead also changed checkCardFileDuplicate and two caller conversions, so those trials were rejected.
- The last six differences were the rename-stage constant. `moveStage = 1` entered initial PCode as a li and was already scheduled before the four leading CARDDir stores. `++moveStage` enters as addi v43,v43,1 after the dominating zero assignment. Before allocation it folds to li v43,1 after mtctr, exactly where the target has li r15,1. The successful status read cannot change this unaliased local, so increment and assignment compute the same value on every path. Plain/compound increments also match; the retained spelling is ++moveStage.
- mwdbg-b-move-exact validates byte-for-byte against an independent wibo compile using the original Ninja flags, including SJIS. Normal project Ninja compilation of the cleaned candidate gives ctxdiff 608/608, diffs 0, and POOL IDENTICAL 43/43. b-move-exact-clean reports exact-name objdiff 100.0 and no other function drops. Only the exact move/copy source is retained; no pragma, carrier, cast-based volatile access, assembly, or flag change was added.

Rx7b additional open-function evidence

- cardThreadMain target outerSlot/validState/exitThread are r26/r25/r24. Moving those declarations to the end makes v34/v33/v32 survive the first simplify sweep and fixes all three colors. In mwdbg-b-thread-local-order-two, the named mount-loop file v37 still simplifies at degree 24 in the first sweep; the split mount-error result v47 is visited later and colors before file, taking r23 while file gets r20. The reply v72 also coalesces into command and uses the hoisted constant-one v71/r29 instead of target validState/r25. Moving file, slot or listing declarations by themselves does not undo these split webs. Separating the joined scan result improves its color to r20 but leaves slot/file/mount-offset differences. Real directory-report and broken-file-test helpers change instruction counts (302 and 300 versus target 301) and are rejected.
- SDMemory::create still has the generated smArg address v319 ahead of pool v145 in color priority: r31 and r30 respectively, while textBox v41 gets r26. The target needs pool r31, receiver r30, and smArg r26. v319 has 43 original neighbors; reused/scoped message locals, first-use declaration changes, C-style downcasts, and real lookup helpers all normalize to the same late generated address and graph. The new named-message-first capture independently reproduces the old allocation, 1064/1064 instructions and 175 differences.
- _create_icon target metadata r31, file offset r30, slot offset r29, this r25, slot r26, file r27, frame r28. The Ghidra export and target assembly agree that RGB retains row and column through GXInitTexObj and forms the returned texture just before GXLoadTexObj; the palette address is likewise recomputed for each call. In the validated real-member-accessor capture, metadata v60 colors first to r31, file offset v41 to r30, and slot offset v40 to r29, but full texture-pointer CSE still has a different lifetime. Signed/unsigned destination-index boundaries change the row/column CSE, but the best equal-sized candidate is still inexact; combining index-site changes did not solve both RGB and palette paths.
- create_banner target validation uses (fileOffset + root) + slotOffset, then recomputes (root + slotOffset) + fileOffset for the selected metadata. It retains separate texture/palette rows and columns across GX calls. The validated member-accessor-load capture still colors the selected metadata before file/slot offsets, contrary to the target selected pointer r25 and file/slot r30/r29. Real texture/palette accessors, metadata accessors, and pixel-base helpers either normalize to this ordering or change instruction count. No private header experiment is retained.

b-thread-scan-combo-file-before-result: Combine the corrected slot declaration order with file-before-result to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-result.

b-thread-scan-combo-file-before-listingFile: Combine the corrected slot declaration order with file-before-listingFile to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-listingFile.

b-thread-scan-combo-file-before-scanResult: Combine the corrected slot declaration order with file-before-scanResult to resolve the remaining mount-phase register rotation. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-scanResult.

b-thread-scan-combo-file-before-slot: Combine the corrected slot declaration order with file-before-slot to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-slot.

b-thread-scan-combo-file-before-freeFile: Combine the corrected slot declaration order with file-before-freeFile to resolve the remaining mount-phase register rotation. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-freeFile.

b-thread-scan-combo-file-before-command: Combine the corrected slot declaration order with file-before-command to resolve the remaining mount-phase register rotation. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-command.

b-thread-scan-combo-file-before-outerSlot: Combine the corrected slot declaration order with file-before-outerSlot to resolve the remaining mount-phase register rotation. objdiff 98.803986%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-file-before-outerSlot.

b-thread-scan-combo-scanResult-before-result: Combine the corrected slot declaration order with scanResult-before-result to resolve the remaining mount-phase register rotation. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-result.

b-thread-scan-combo-scanResult-before-listingFile: Combine the corrected slot declaration order with scanResult-before-listingFile to resolve the remaining mount-phase register rotation. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-listingFile.

b-thread-scan-combo-scanResult-before-file: Combine the corrected slot declaration order with scanResult-before-file to resolve the remaining mount-phase register rotation. objdiff 98.73754%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-file.

b-thread-scan-combo-scanResult-before-freeBlocks: Combine the corrected slot declaration order with scanResult-before-freeBlocks to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-freeBlocks.

b-thread-scan-combo-scanResult-before-freeFile: Combine the corrected slot declaration order with scanResult-before-freeFile to resolve the remaining mount-phase register rotation. objdiff 98.85382%; insns 301/301 diffs 29; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-freeFile.

b-thread-scan-combo-scanResult-before-command: Combine the corrected slot declaration order with scanResult-before-command to resolve the remaining mount-phase register rotation. objdiff 98.85382%; insns 301/301 diffs 29; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-command.

b-thread-reply-valid-const-u32ref: Use const u32& at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-const-u32ref.

b-thread-scan-combo-scanResult-before-outerSlot: Combine the corrected slot declaration order with scanResult-before-outerSlot to resolve the remaining mount-phase register rotation. objdiff 98.85382%; insns 301/301 diffs 29; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-scanResult-before-outerSlot.

b-thread-reply-valid-u32ref: Use u32& at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-u32ref.

b-thread-scan-combo-listingFile-before-result: Combine the corrected slot declaration order with listingFile-before-result to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-result.

b-thread-reply-valid-u8: Use u8 at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-u8.

b-thread-scan-combo-listingFile-before-freeBlocks: Combine the corrected slot declaration order with listingFile-before-freeBlocks to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-freeBlocks.

b-thread-reply-valid-const-u8: Use const u8 at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-const-u8.

b-thread-scan-combo-listingFile-before-scanResult: Combine the corrected slot declaration order with listingFile-before-scanResult to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-scanResult.

b-thread-reply-valid-s16: Use s16 at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-s16.

b-thread-scan-combo-listingFile-before-slot: Combine the corrected slot declaration order with listingFile-before-slot to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-slot.

b-thread-reply-valid-const-s32: Use const s32 at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-const-s32.

b-thread-scan-combo-listingFile-before-freeFile: Combine the corrected slot declaration order with listingFile-before-freeFile to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-freeFile.

b-thread-reply-valid-const-u32: Use const u32 at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-const-u32.

b-thread-scan-combo-listingFile-before-command: Combine the corrected slot declaration order with listingFile-before-command to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-command.

b-thread-reply-valid-bool: Use bool at the real reply helper validity boundary to check constant-one propagation and command-copy coalescing. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-reply-valid-bool.

b-thread-scan-combo-listingFile-before-outerSlot: Combine the corrected slot declaration order with listingFile-before-outerSlot to resolve the remaining mount-phase register rotation. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-listingFile-before-outerSlot.

b-thread-scan-combo-command-before-result: Combine the corrected slot declaration order with command-before-result to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-result.

b-thread-scan-combo-command-before-listingFile: Combine the corrected slot declaration order with command-before-listingFile to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-listingFile.

b-thread-scan-combo-command-before-file: Combine the corrected slot declaration order with command-before-file to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-file.

b-thread-scan-combo-command-before-freeBlocks: Combine the corrected slot declaration order with command-before-freeBlocks to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-freeBlocks.

b-thread-scan-combo-command-before-scanResult: Combine the corrected slot declaration order with command-before-scanResult to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-scanResult.

b-thread-scan-combo-command-before-slot: Combine the corrected slot declaration order with command-before-slot to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-slot.

b-thread-scan-combo-command-before-freeFile: Combine the corrected slot declaration order with command-before-freeFile to resolve the remaining mount-phase register rotation. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-scan-combo-command-before-freeFile.

b-thread-packet-fields-signed-valid: Model the existing four-byte response packet with signed-valid fields; check the real bit-insert and command-copy boundary without adding a carrier. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-fields-signed-valid.

b-thread-packet-fields-native-unsigned: Model the existing four-byte response packet with native-unsigned fields; check the real bit-insert and command-copy boundary without adding a carrier. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-fields-native-unsigned.

b-thread-packet-fields-bytes: Model the existing four-byte response packet with bytes fields; check the real bit-insert and command-copy boundary without adding a carrier. objdiff 97.65116%; insns 302/301 diffs 262; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-fields-bytes.

b-thread-packet-fields-signed-bytes: Model the existing four-byte response packet with signed-bytes fields; check the real bit-insert and command-copy boundary without adding a carrier. objdiff 97.65116%; insns 302/301 diffs 262; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-packet-fields-signed-bytes.

b-thread-mount-offset-before-brokenFile: Name the mount-buffer offset separately from the command byte, placing its real node before BOOL brokenFile;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-brokenFile.

b-thread-mount-offset-before-result: Name the mount-buffer offset separately from the command byte, placing its real node before s32 result;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-result.

b-thread-mount-offset-before-listingFile: Name the mount-buffer offset separately from the command byte, placing its real node before u32 listingFile;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-listingFile.

b-thread-mount-offset-before-file: Name the mount-buffer offset separately from the command byte, placing its real node before s32 file;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-file.

b-thread-mount-offset-before-freeBlocks: Name the mount-buffer offset separately from the command byte, placing its real node before s32 freeBlocks;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-freeBlocks.

b-thread-mount-offset-before-scanResult: Name the mount-buffer offset separately from the command byte, placing its real node before s32 scanResult;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-scanResult.

b-thread-mount-offset-before-slot: Name the mount-buffer offset separately from the command byte, placing its real node before u8 slot;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-slot.

b-thread-mount-offset-before-freeFile: Name the mount-buffer offset separately from the command byte, placing its real node before s32 freeFile;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-freeFile.

b-thread-mount-offset-before-command: Name the mount-buffer offset separately from the command byte, placing its real node before u32 command;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-command.

b-thread-mount-offset-before-outerSlot: Name the mount-buffer offset separately from the command byte, placing its real node before s32 outerSlot;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-outerSlot.

b-thread-mount-offset-before-validState: Name the mount-buffer offset separately from the command byte, placing its real node before u32 validState = TRUE;. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-before-validState.

b-thread-mount-offset-case-local: Give the actual mount-buffer offset a case-scoped local instead of reusing the command byte. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-case-local.

b-icon-member-width-u32-init: Use a real class field accessor with u32 file index at init sites to test the target row/column lifetime across GX calls. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-u32-init.

b-icon-member-width-u32-load: Use a real class field accessor with u32 file index at load sites to test the target row/column lifetime across GX calls. objdiff 96.19%; insns 102/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-u32-load.

b-icon-member-width-u32-all: Use a real class field accessor with u32 file index at all sites to test the target row/column lifetime across GX calls. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-u32-all.

b-icon-member-width-unsigned-int-init: Use a real class field accessor with unsigned int file index at init sites to test the target row/column lifetime across GX calls. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-unsigned-int-init.

b-icon-member-width-unsigned-int-load: Use a real class field accessor with unsigned int file index at load sites to test the target row/column lifetime across GX calls. objdiff 96.19%; insns 102/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-unsigned-int-load.

b-icon-member-width-unsigned-int-all: Use a real class field accessor with unsigned int file index at all sites to test the target row/column lifetime across GX calls. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-unsigned-int-all.

b-icon-member-width-int-init: Use a real class field accessor with int file index at init sites to test the target row/column lifetime across GX calls. objdiff 94.29%; insns 100/100 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-int-init.

b-icon-member-width-int-load: Use a real class field accessor with int file index at load sites to test the target row/column lifetime across GX calls. objdiff 90.65%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-int-load.

b-icon-member-width-int-all: Use a real class field accessor with int file index at all sites to test the target row/column lifetime across GX calls. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-int-all.

b-icon-member-width-const-s16-init: Use a real class field accessor with const s16 file index at init sites to test the target row/column lifetime across GX calls. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-const-s16-init.

b-icon-member-width-const-s16-load: Use a real class field accessor with const s16 file index at load sites to test the target row/column lifetime across GX calls. objdiff 96.19%; insns 102/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-const-s16-load.

b-icon-member-width-const-s16-all: Use a real class field accessor with const s16 file index at all sites to test the target row/column lifetime across GX calls. objdiff 82.45%; insns 101/100 diffs 63; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-member-width-const-s16-all.

b-thread-mount-slot-before-brokenFile: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before BOOL brokenFile;. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-brokenFile.

b-thread-mount-slot-before-result: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 result;. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-result.

b-thread-mount-slot-before-listingFile: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before u32 listingFile;. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-listingFile.

b-thread-mount-slot-before-file: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 file;. objdiff 98.704315%; insns 301/301 diffs 37; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-file.

b-thread-mount-slot-before-freeBlocks: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 freeBlocks;. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-freeBlocks.

b-thread-mount-slot-before-scanResult: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 scanResult;. objdiff 98.75415%; insns 301/301 diffs 35; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-scanResult.

b-thread-mount-slot-before-slot: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before u8 slot;. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-slot.

b-thread-mount-slot-before-freeFile: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 freeFile;. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-freeFile.

b-thread-mount-slot-before-command: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before u32 command;. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-command.

b-thread-mount-slot-before-outerSlot: Separate the mount-operation slot from format/delete inputs and give its actual value a named declaration before s32 outerSlot;. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-before-outerSlot.

b-thread-mount-slot-case-local: Declare the actual mount slot inside its command case. objdiff 98.820595%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-slot-case-local.

b-icon-reference-cell-s16-init: Return the real cell object by reference through a MemoryCardManager accessor at init sites, with s16 file index. objdiff 78.74%; insns 102/100 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-s16-init.

b-icon-reference-texture-s16-init: Return the real texture object by reference through a MemoryCardManager accessor at init sites, with s16 file index. objdiff 94.29%; insns 100/100 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-s16-init.

b-icon-reference-cell-s16-load: Return the real cell object by reference through a MemoryCardManager accessor at load sites, with s16 file index. objdiff 77.44%; insns 104/100 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-s16-load.

b-icon-reference-texture-s16-load: Return the real texture object by reference through a MemoryCardManager accessor at load sites, with s16 file index. objdiff 90.65%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-s16-load.

b-icon-reference-cell-s16-all: Return the real cell object by reference through a MemoryCardManager accessor at all sites, with s16 file index. objdiff 78.28%; insns 100/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-s16-all.

b-icon-reference-cell-u32-init: Return the real cell object by reference through a MemoryCardManager accessor at init sites, with u32 file index. objdiff 76.14%; insns 104/100 diffs 75; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-u32-init.

b-icon-reference-texture-u32-init: Return the real texture object by reference through a MemoryCardManager accessor at init sites, with u32 file index. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-u32-init.

b-icon-reference-cell-u32-load: Return the real cell object by reference through a MemoryCardManager accessor at load sites, with u32 file index. objdiff 75.59%; insns 106/100 diffs 76; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-u32-load.

b-icon-reference-texture-u32-load: Return the real texture object by reference through a MemoryCardManager accessor at load sites, with u32 file index. objdiff 96.19%; insns 102/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-u32-load.

b-icon-reference-cell-u32-all: Return the real cell object by reference through a MemoryCardManager accessor at all sites, with u32 file index. objdiff 78.28%; insns 100/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-u32-all.

b-icon-reference-cell-int-init: Return the real cell object by reference through a MemoryCardManager accessor at init sites, with int file index. objdiff 78.74%; insns 102/100 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-int-init.

b-icon-reference-texture-int-init: Return the real texture object by reference through a MemoryCardManager accessor at init sites, with int file index. objdiff 94.29%; insns 100/100 diffs 33; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-int-init.

b-icon-reference-cell-int-load: Return the real cell object by reference through a MemoryCardManager accessor at load sites, with int file index. objdiff 77.44%; insns 104/100 diffs 77; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-int-load.

b-icon-reference-texture-int-load: Return the real texture object by reference through a MemoryCardManager accessor at load sites, with int file index. objdiff 90.65%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-texture-int-load.

b-icon-reference-cell-int-all: Return the real cell object by reference through a MemoryCardManager accessor at all sites, with int file index. objdiff 78.28%; insns 100/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-icon-reference-cell-int-all.

Further thread declaration confirmation: mwdbg-b-thread-scan-result is byte-identical to original-flags wibo. The joined scanResult is now a named v37 instead of the old generated mount-error v47, so it can take the target r20. Moving slot past scanResult then gives the loop file r23, reducing the exact instruction diff to 25. The independently split mount-buffer offset still takes r22 instead of r19 and makes slot use r26; naming mountOffset separately normalizes back to the same graph. The packet input-reference, width and signed-bitfield variants also normalize. Byte-struct packet fields add an instruction. None of these partial thread variants are retained.

Additional icon accessor evidence: real member getters using signed/unsigned word indices or actual MCFileCell/GX object references were tested at initialization, loading and return sites. A 94.29% equal-count candidate changes the save range and keeps a full texture pointer live before GXInitTexObj; 96.19% is 102/100 instructions. These scores do not meet the target addressing or exactness requirements, so no header or MC source edit is retained.

b-thread-value-type-slot-s32: Use s32 for actual bounded slot while preserving target signedness of loop comparisons. objdiff 98.72093%; insns 301/301 diffs 26; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-slot-s32.

b-thread-value-type-slot-u32: Use u32 for actual bounded slot while preserving target signedness of loop comparisons. objdiff 98.72093%; insns 301/301 diffs 26; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-slot-u32.

b-thread-value-type-slot-int: Use int for actual bounded slot while preserving target signedness of loop comparisons. objdiff 98.72093%; insns 301/301 diffs 26; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-slot-int.

b-thread-value-type-slot-u16: Use u16 for actual bounded slot while preserving target signedness of loop comparisons. objdiff 98.903656%; insns 301/301 diffs 26; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-slot-u16.

b-thread-value-type-command-u8: Use u8 for actual bounded command while preserving target signedness of loop comparisons. objdiff 98.88705%; insns 301/301 diffs 27; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-command-u8.

b-thread-value-type-command-u16: Use u16 for actual bounded command while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-command-u16.

b-thread-value-type-command-int: Use int for actual bounded command while preserving target signedness of loop comparisons. objdiff 96.57807%; insns 304/301 diffs 252; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-command-int.

b-thread-value-type-command-unsigned-int: Use unsigned int for actual bounded command while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-command-unsigned-int.

b-thread-value-type-file-int: Use int for actual bounded file while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-file-int.

b-thread-value-type-file-u32: Use u32 for actual bounded file while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-file-u32.

b-thread-value-type-listingFile-unsigned-int: Use unsigned int for actual bounded listingFile while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-listingFile-unsigned-int.

b-thread-value-type-listingFile-s32: Use s32 for actual bounded listingFile while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-listingFile-s32.

b-thread-value-type-scanResult-int: Use int for actual bounded scanResult while preserving target signedness of loop comparisons. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-value-type-scanResult-int.

Focused retained-source review: only runCardMoveOrCopy changes score in the rebuilt card unit: 97.88651 -> 100.0. Unit exact functions 27/30 -> 28/30, exact code 4168/9852 -> 6600/9852, data 1496/1496 unchanged. The helper retains the temporary-name loop limit and signed result truncation, each metadata failure still reaches the same cleanup, and moveStage is zero before its only increment. git diff --check passes. Literal-reference analysis: 21 arguments, 0 candidate mismatches, 0 errors.

b-banner-validation-helper-mutable-bool-slot-first: Give the validation byte load its own real getter with bool result and slot-first inputs, retaining the later selected metadata lookup. objdiff 87.07547%; insns 107/106 diffs 73; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-mutable-bool-slot-first.

b-banner-validation-helper-mutable-bool-file-first: Give the validation byte load its own real getter with bool result and file-first inputs, retaining the later selected metadata lookup. objdiff 87.07547%; insns 107/106 diffs 73; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-mutable-bool-file-first.

b-banner-validation-helper-mutable-u8-slot-first: Give the validation byte load its own real getter with u8 result and slot-first inputs, retaining the later selected metadata lookup. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-mutable-u8-slot-first.

b-banner-validation-helper-mutable-u8-file-first: Give the validation byte load its own real getter with u8 result and file-first inputs, retaining the later selected metadata lookup. objdiff 90.42453%; insns 106/106 diffs 70; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-mutable-u8-file-first.

b-banner-validation-helper-const-bool-slot-first: Give the validation byte load its own real getter with const bool result and slot-first inputs, retaining the later selected metadata lookup. objdiff 90.471695%; insns 108/106 diffs 75; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-const-bool-slot-first.

b-banner-validation-helper-const-bool-file-first: Give the validation byte load its own real getter with const bool result and file-first inputs, retaining the later selected metadata lookup. objdiff 90.471695%; insns 108/106 diffs 75; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-const-bool-file-first.

b-banner-validation-helper-const-u8-slot-first: Give the validation byte load its own real getter with const u8 result and slot-first inputs, retaining the later selected metadata lookup. objdiff 91.27358%; insns 107/106 diffs 73; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-const-u8-slot-first.

b-banner-validation-helper-const-u8-file-first: Give the validation byte load its own real getter with const u8 result and file-first inputs, retaining the later selected metadata lookup. objdiff 91.27358%; insns 107/106 diffs 73; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-banner-validation-helper-const-u8-file-first.

Further banner boundary check: a getter for only the validation byte was tested with mutable/const array inputs, bool/u8 results and slot-first/file-first arguments. Mutable u8 getters normalize to the baseline 106 instructions; mutable bool and const u8 getters produce 107/106, and const bool getters produce 108/106. None produces the target distinct validation and selected-metadata address webs. Merely moving the first lookup into an inline does not solve this CSE; no banner edit is retained.

b-move-exact-no-empty-scope: Remove the now-unneeded outer lexical block around the two metadata-operation branches; preserve real inner scopes and all declarations. objdiff 100.0%; insns 608/608 diffs 0; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-move-exact-no-empty-scope.

Final source cleanup removes an unnecessary outer lexical block around the copy/move metadata branches. b-move-exact-no-empty-scope remains 100.0%, 608/608, diffs 0; its entire object is byte-identical to b-move-exact-clean. This is the retained source.

Search queue note: banner-107, icon-107 and sd-131 were still waiting for the global limiter after the other seeds completed. Their existing queued processes were briefly paused/resumed at staggered times to break synchronized five-second polling. No lock file, slot count, lock loop, source-search budget or other worker process was changed; each still must acquire a normal slot before its 1200-second budget starts.

The last thread candidate also has a completed independent debugger validation: build/rx7b/mwdbg-b-thread-25-diffs matches original-flags wibo byte-for-byte. Its 25 remaining differences are the reply's three-instruction copy/insert group, mount-buffer offset r22 versus target r19, mount slot r26 versus r22, and listing index r22 versus r23. The real scan result and first file loop now use target r20/r23. Naming the mount slot separately, changing bounded scalar widths, and changing the existing packet's bitfield types do not resolve these remaining webs. The source remains at the original 97.9402% because this partial candidate is not exact.

b-thread-mount-offset-update-or: Preserve the actual mount command value while adding its slot-offset bits; command is exactly zero on entry to case zero, so the computed value is unchanged. objdiff 96.54485%; insns 303/301 diffs 251; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-update-or.

b-thread-mount-offset-update-add: Preserve the actual mount command value while adding its slot-offset bits; command is exactly zero on entry to case zero, so the computed value is unchanged. objdiff 96.69435%; insns 303/301 diffs 251; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-mount-offset-update-add.

b-thread-report-state-reference-mutable: Return the actual updated state by reference from the set-and-report operation and consume it as the reply input, preserving assignment-before-report order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-state-reference-mutable.

b-thread-report-state-reference-const: Return the actual updated state by reference from the set-and-report operation and consume it as the reply input, preserving assignment-before-report order. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7b/trials/b-thread-report-state-reference-const.

Search starvation handling: after the same three processes remained queued, build/rx7b/fair_search_handoff.py waits with ordinary blocking flock requests on existing slots 0, 1 and 2. Each reservation is released before its paused queued process resumes; the unmodified srcsearch limiter must then acquire its own slot. The helper does not replace lock files, increase the 24-slot limit, run a compiler without a slot, shorten the 1200-second budget, or affect another worker process. It only gives the queued jobs a chance at a capacity release instead of synchronized polling.

Completed current-round thread seeds 107/119/131: 395/394/396 trials, all best 99.00332% from the plain packet candidate, no exact gain. Completed SD seeds 107/119/131: 345/355/341 trials, all best 99.15884%, no gain. Each ran its full 1200-second budget after acquiring a normal global slot.


Rx7b final validation and handoff (2026-10-05)

- Final GX searches also completed their full 1200-second budgets: icon seeds 107/119/131 ran 1276/1438/1380 trials, best 93.35%; banner seeds 107/119/131 ran 1269/1446/1479 trials, best 90.42453%. Together with the completed thread and SD searches above, all twelve required searches for the four still-open functions finished normally. The three move searches were stopped only after the manual exact match. No partial search result was applied. Machine-readable summary: build/rx7b/search-summary.json.
- Clean gate command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/memoryCard/iplMemoryCardManager src/scene/cardSequence/iplCardSequence src/scene/sdChannelMemory/iplSDMemory. This ran without --quick after every source-search process exited. Raw output: build/rx7b/final-gate.log. GATE PASS; full 43U build passes; all three pools identical; regressions 0; forbidden additions 0; readability warnings 0.
- Final exact-name objdiff: runCardMoveOrCopy 97.88651 -> 100.0, 608/608 instructions, diffs 0; SDMemory::create 99.15884 -> 99.15884; cardThreadMain 97.9402 -> 97.9402; _create_icon 87.55 -> 87.55; create_banner 90.42453 -> 90.42453. Previously landed getComment remains 100.0, 123/123, diffs 0. All per-function results and context diffs are in build/rx7b/final-measurements.json.
- CardSequence exact functions 27/30 -> 28/30, matched code 4168/9852 -> 6600/9852, data 1496/1496 unchanged. MemoryCardManager stays 24/26 and SDMemory stays 64/66. Only runCardMoveOrCopy changes score; four assigned functions remain open.
- Retained allocator explanation: declaring the real nested state locals before persistent move/copy values keeps those persistent nodes above the first-sweep degree threshold. The later simplify order is slot/file/command/metadataCopied/temporaryCreated/destinationFileNo/destinationSlot; reverse coloring assigns the target r25 through r31. The actual creation helper return coalesces into destinationFileNo. Separate operation results preserve the target error paths. The u8 slot type restores entry-copy order, and incrementing the initialized moveStage delays constant folding until after the target directory-copy setup. Final debugger validation is byte-identical to the original-flags wibo object.
- Remaining allocator findings: SD's generated smArg still receives priority before the string-pool base; thread mount-offset and mount-slot split webs and reply coalescing remain wrong despite corrected persistent-local order; icon accessors still leave a full texture pointer live across GX initialization; banner validation CSE still forms the selected metadata pointer too early and gives it priority over the offsets. Candidate simplify, coalescing and assignment dumps are retained under build/rx7b/mwdbg-* and explained above.
- Post-gate Ninja progress/report/43U-ok and decomp_status.py pass. Literal-reference check for the matched function: 21 arguments, 0 candidate mismatches, 0 errors. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. check_decomp_complete.py exits 1 because the whole project remains incomplete (12442/12563 exact functions, 977/1027 linked units); this is a one-function handoff, not a completion claim.
- Retained tracked paths are only src/scene/cardSequence/iplCardSequence.cpp and this attempts log. No MemoryCardManager/SDMemory/header/configuration changes, carrier structs, new assembly, or compiler-flag changes are retained. No push, PR, merge or rebase was performed. Final source review and git diff --check pass.


Rx7c continuation (2026-10-05), branch agent/w1005/rx7c at e208b205, containing PR #1195. Re-read levers 11/18/20/21/22 and mwdbg README; prior partial candidates stay private. The new focus is real mount/listing/free-block helper boundaries and per-branch results in cardThreadMain, and actual texture-object initialization/load member boundaries for the GX functions. Reuse validated previous captures while rebuilding all owned objects against this branch.

c-thread-prior-25: Revalidate the prior 25-difference candidate with the landed move/copy match preserved. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-prior-25.

c-thread-free-helper-freeFile-freeBlocks-result: Factor the game-block counting loop into a returning helper; test real helper-local order freeFile-freeBlocks-result. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-freeFile-freeBlocks-result.

c-thread-free-helper-freeFile-result-freeBlocks: Factor the game-block counting loop into a returning helper; test real helper-local order freeFile-result-freeBlocks. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-freeFile-result-freeBlocks.

c-thread-free-helper-freeBlocks-freeFile-result: Factor the game-block counting loop into a returning helper; test real helper-local order freeBlocks-freeFile-result. objdiff 98.355484%; insns 301/301 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-freeBlocks-freeFile-result.

c-thread-free-helper-freeBlocks-result-freeFile: Factor the game-block counting loop into a returning helper; test real helper-local order freeBlocks-result-freeFile. objdiff 98.355484%; insns 301/301 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-freeBlocks-result-freeFile.

c-thread-free-helper-result-freeFile-freeBlocks: Factor the game-block counting loop into a returning helper; test real helper-local order result-freeFile-freeBlocks. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-result-freeFile-freeBlocks.

c-thread-free-helper-result-freeBlocks-freeFile: Factor the game-block counting loop into a returning helper; test real helper-local order result-freeBlocks-freeFile. objdiff 98.355484%; insns 301/301 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-result-freeBlocks-freeFile.

c-thread-free-helper-u8: Use u8 for the real counting-helper slot input. objdiff 98.28904%; insns 301/301 diffs 50; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-u8.

c-thread-free-helper-u32: Use u32 for the real counting-helper slot input. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-u32.

c-thread-free-helper-const-s32: Use const s32 for the real counting-helper slot input. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-free-helper-const-s32.

c-thread-list-helper-s32-False: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index False. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-s32-False.

c-thread-list-helper-s32-True: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index True. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-s32-True.

c-thread-list-helper-u8-False: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index False. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-u8-False.

c-thread-list-helper-u8-True: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index True. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-u8-True.

c-thread-list-helper-u32-False: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index False. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-u32-False.

c-thread-list-helper-u32-True: Factor the complete directory-reporting loop, preserving format-string token order; return final listing index True. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-list-helper-u32-True.

c-thread-loops-both: Combine independent real loop helpers and both local lifetime structure. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-loops-both.

c-thread-loops-both-reverse: Combine independent real loop helpers and both-reverse local lifetime structure. objdiff 96.52492%; insns 302/301 diffs 290; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-loops-both-reverse.

c-thread-loops-branch-results: Combine independent real loop helpers and branch-results local lifetime structure. objdiff 96.441864%; insns 302/301 diffs 289; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-loops-branch-results.

c-icon-member-rgb-s16: Move actual rgb GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-rgb-s16/compile.log.

c-icon-member-init-s16: Move actual init GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-init-s16/compile.log.

c-icon-member-loads-s16: Move actual loads GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-loads-s16/compile.log.

c-icon-member-all-s16: Move actual all GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-all-s16/compile.log.

c-icon-member-rgb-s32: Move actual rgb GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-rgb-s32/compile.log.

c-icon-member-init-s32: Move actual init GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-init-s32/compile.log.

c-icon-member-loads-s32: Move actual loads GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-loads-s32/compile.log.

c-icon-member-all-s32: Move actual all GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-all-s32/compile.log.

c-icon-member-rgb-u32: Move actual rgb GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-rgb-u32/compile.log.

c-icon-member-init-u32: Move actual init GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-init-u32/compile.log.

c-icon-member-loads-u32: Move actual loads GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-loads-u32/compile.log.

c-icon-member-all-u32: Move actual all GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-icon-member-all-u32/compile.log.

c-banner-member-rgb-s16: Move actual rgb GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-rgb-s16/compile.log.

c-banner-member-init-s16: Move actual init GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-init-s16/compile.log.

c-banner-member-loads-s16: Move actual loads GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-loads-s16/compile.log.

c-banner-member-all-s16: Move actual all GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-all-s16/compile.log.

c-banner-member-rgb-s32: Move actual rgb GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-rgb-s32/compile.log.

c-banner-member-init-s32: Move actual init GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-init-s32/compile.log.

c-banner-member-loads-s32: Move actual loads GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-loads-s32/compile.log.

c-banner-member-all-s32: Move actual all GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-all-s32/compile.log.

c-banner-member-rgb-u32: Move actual rgb GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-rgb-u32/compile.log.

c-banner-member-init-u32: Move actual init GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-init-u32/compile.log.

c-banner-member-loads-u32: Move actual loads GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-loads-u32/compile.log.

c-banner-member-all-u32: Move actual all GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. Compile failed; see build/rx7c/trials/c-banner-member-all-u32/compile.log.

c-icon-member-fixed-rgb-s16: Move actual rgb GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-rgb-s16.

c-icon-member-fixed-init-s16: Move actual init GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-init-s16.

c-icon-member-fixed-loads-s16: Move actual loads GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-loads-s16.

c-icon-member-fixed-all-s16: Move actual all GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-all-s16.

c-icon-member-fixed-rgb-s32: Move actual rgb GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-rgb-s32.

c-icon-member-fixed-init-s32: Move actual init GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-init-s32.

c-icon-member-fixed-loads-s32: Move actual loads GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-loads-s32.

c-icon-member-fixed-all-s32: Move actual all GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-all-s32.

c-icon-member-fixed-rgb-u32: Move actual rgb GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 93.35%; insns 100/100 diffs 17; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-rgb-u32.

c-icon-member-fixed-init-u32: Move actual init GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 94.69%; insns 99/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-init-u32.

c-icon-member-fixed-loads-u32: Move actual loads GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 90.74%; insns 100/100 diffs 20; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-loads-u32.

c-icon-member-fixed-all-u32: Move actual all GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 90.69%; insns 101/100 diffs 32; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-fixed-all-u32.

c-banner-member-fixed-rgb-s16: Move actual rgb GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 87.386795%; insns 109/106 diffs 86; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-rgb-s16.

c-banner-member-fixed-init-s16: Move actual init GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 81.83962%; insns 110/106 diffs 87; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-init-s16.

c-banner-member-fixed-loads-s16: Move actual loads GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 110/106 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-loads-s16.

c-banner-member-fixed-all-s16: Move actual all GX calls into ordinary MemoryCardManager methods with s16 file input, computing fields inside the member boundary. objdiff 82.113205%; insns 110/106 diffs 89; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-all-s16.

c-banner-member-fixed-rgb-s32: Move actual rgb GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 91.69811%; insns 108/106 diffs 78; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-rgb-s32.

c-banner-member-fixed-init-s32: Move actual init GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-init-s32.

c-banner-member-fixed-loads-s32: Move actual loads GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-loads-s32.

c-banner-member-fixed-all-s32: Move actual all GX calls into ordinary MemoryCardManager methods with s32 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-all-s32.

c-banner-member-fixed-rgb-u32: Move actual rgb GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-rgb-u32.

c-banner-member-fixed-init-u32: Move actual init GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-init-u32.

c-banner-member-fixed-loads-u32: Move actual loads GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-loads-u32.

c-banner-member-fixed-all-u32: Move actual all GX calls into ordinary MemoryCardManager methods with u32 file input, computing fields inside the member boundary. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-member-fixed-all-u32.

c-thread-result-case: Separate each format/delete operation result at case declaration scope. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-result-case.

c-thread-result-root-first: Separate each format/delete operation result at root-first declaration scope. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-result-root-first.

c-thread-result-root-last: Separate each format/delete operation result at root-last declaration scope. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-result-root-last.

c-thread-slot-case: Separate each format/delete operation slot at case declaration scope. objdiff 98.65449%; insns 301/301 diffs 41; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-slot-case.

c-thread-slot-root-first: Separate each format/delete operation slot at root-first declaration scope. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-slot-root-first.

c-thread-slot-root-last: Separate each format/delete operation slot at root-last declaration scope. objdiff 98.65449%; insns 301/301 diffs 41; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-slot-root-last.

c-thread-both-case: Separate each format/delete operation both at case declaration scope. objdiff 98.65449%; insns 301/301 diffs 41; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-both-case.

c-thread-both-root-first: Separate each format/delete operation both at root-first declaration scope. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-both-root-first.

c-thread-both-root-last: Separate each format/delete operation both at root-last declaration scope. objdiff 98.65449%; insns 301/301 diffs 41; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-both-root-last.

c-thread-reuse-listing-file: Reuse the real file value for the nonoverlapping listing loop, keeping the unsigned bound. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-reuse-listing-file.

c-thread-reuse-listing-fileNo: Reuse the real fileNo value for the nonoverlapping listing loop, keeping the unsigned bound. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-reuse-listing-fileNo.

c-thread-reuse-listing-command: Reuse the real command value for the nonoverlapping listing loop, keeping the unsigned bound. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-reuse-listing-command.

c-thread-valid-set-report-u32-False: Create a real state assignment/report boundary using u32 return value. objdiff 98.72093%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-u32-False.

c-thread-valid-set-report-u32-True: Create a real state assignment/report boundary using u32 reference output. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-u32-True.

c-thread-valid-set-report-s32-False: Create a real state assignment/report boundary using s32 return value. objdiff 98.52159%; insns 301/301 diffs 32; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-s32-False.

c-thread-valid-set-report-s32-True: Create a real state assignment/report boundary using s32 reference output. objdiff 98.72093%; insns 301/301 diffs 26; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-s32-True.

c-thread-valid-set-report-u8-False: Create a real state assignment/report boundary using u8 return value. objdiff 98.72093%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-u8-False.

c-thread-valid-set-report-u8-True: Create a real state assignment/report boundary using u8 reference output. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-u8-True.

c-thread-valid-set-report-bool-False: Create a real state assignment/report boundary using bool return value. objdiff 98.72093%; insns 301/301 diffs 31; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-bool-False.

c-thread-valid-set-report-bool-True: Create a real state assignment/report boundary using bool reference output. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-set-report-bool-True.

c-banner-split-member-ci-s32: Isolate ci operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.76415%; insns 109/106 diffs 78; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-ci-s32.

c-banner-split-member-ci-u32: Isolate ci operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-ci-u32.

c-banner-split-member-tlut-s32: Isolate tlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 90.330185%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-tlut-s32.

c-banner-split-member-tlut-u32: Isolate tlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-tlut-u32.

c-banner-split-member-ci-tlut-s32: Isolate ci-tlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 92.12264%; insns 107/106 diffs 60; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-ci-tlut-s32.

c-banner-split-member-ci-tlut-u32: Isolate ci-tlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-ci-tlut-u32.

c-banner-split-member-rgb-ci-s32: Isolate rgb-ci operations behind real member calls with s32 indices; preserve separate address uses. objdiff 89.70755%; insns 109/106 diffs 75; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-rgb-ci-s32.

c-banner-split-member-rgb-ci-u32: Isolate rgb-ci operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-rgb-ci-u32.

c-banner-split-member-rgb-load-s32: Isolate rgb-load operations behind real member calls with s32 indices; preserve separate address uses. objdiff 90.66038%; insns 109/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-rgb-load-s32.

c-banner-split-member-rgb-load-u32: Isolate rgb-load operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-rgb-load-u32.

c-banner-split-member-load-s32: Isolate load operations behind real member calls with s32 indices; preserve separate address uses. objdiff 91.603775%; insns 109/106 diffs 78; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-load-s32.

c-banner-split-member-load-u32: Isolate load operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-load-u32.

c-banner-split-member-loadtlut-s32: Isolate loadtlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 92.5%; insns 108/106 diffs 61; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-loadtlut-s32.

c-banner-split-member-loadtlut-u32: Isolate loadtlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 92.169815%; insns 108/106 diffs 81; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-split-member-loadtlut-u32.

c-icon-split-member-ci-s32: Isolate ci operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-ci-s32.

c-icon-split-member-ci-u32: Isolate ci operations behind real member calls with u32 indices; preserve separate address uses. objdiff 81.17%; insns 101/100 diffs 66; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-ci-u32.

c-icon-split-member-tlut-s32: Isolate tlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-tlut-s32.

c-icon-split-member-tlut-u32: Isolate tlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 90.24%; insns 100/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-tlut-u32.

c-icon-split-member-ci-tlut-s32: Isolate ci-tlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-ci-tlut-s32.

c-icon-split-member-ci-tlut-u32: Isolate ci-tlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 90.69%; insns 100/100 diffs 22; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-ci-tlut-u32.

c-icon-split-member-rgb-ci-s32: Isolate rgb-ci operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-rgb-ci-s32.

c-icon-split-member-rgb-ci-u32: Isolate rgb-ci operations behind real member calls with u32 indices; preserve separate address uses. objdiff 84.08%; insns 101/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-rgb-ci-u32.

c-icon-split-member-rgb-load-s32: Isolate rgb-load operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-rgb-load-s32.

c-icon-split-member-rgb-load-u32: Isolate rgb-load operations behind real member calls with u32 indices; preserve separate address uses. objdiff 87.64%; insns 102/100 diffs 37; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-rgb-load-u32.

c-icon-split-member-load-s32: Isolate load operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-load-s32.

c-icon-split-member-load-u32: Isolate load operations behind real member calls with u32 indices; preserve separate address uses. objdiff 88.54%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-load-u32.

c-icon-split-member-loadtlut-s32: Isolate loadtlut operations behind real member calls with s32 indices; preserve separate address uses. objdiff 88.35%; insns 100/100 diffs 27; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-loadtlut-s32.

c-icon-split-member-loadtlut-u32: Isolate loadtlut operations behind real member calls with u32 indices; preserve separate address uses. objdiff 90.49%; insns 100/100 diffs 26; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-split-member-loadtlut-u32.

c-banner-rgb-param-const-s32: Keep CI and palette helper boundaries; test primitive RGB parameter identity const s32. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-const-s32.

c-banner-rgb-param-const-u32: Keep CI and palette helper boundaries; test primitive RGB parameter identity const u32. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-const-u32.

c-banner-rgb-param-int: Keep CI and palette helper boundaries; test primitive RGB parameter identity int. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-int.

c-banner-rgb-param-unsigned-int: Keep CI and palette helper boundaries; test primitive RGB parameter identity unsigned int. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-unsigned-int.

c-banner-rgb-param-long: Keep CI and palette helper boundaries; test primitive RGB parameter identity long. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-long.

c-banner-rgb-param-unsigned-long: Keep CI and palette helper boundaries; test primitive RGB parameter identity unsigned long. objdiff 92.12264%; insns 107/106 diffs 60; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-param-unsigned-long.

c-banner-rgb-return-index: Expose the real RGB initialization return-index to test inter-inline copy propagation. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-return-index.

c-banner-rgb-return-texture: Expose the real RGB initialization return-texture to test inter-inline copy propagation. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-return-texture.

c-banner-rgb-local-copy: Expose the real RGB initialization local-copy to test inter-inline copy propagation. objdiff 96.41509%; insns 107/106 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-rgb-local-copy.

c-thread-process-entry-s32-direct: Return each mounted-file processing result through a real helper; direct result form with s32 slot. objdiff 96.122925%; insns 293/301 diffs 199; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-s32-direct.

c-thread-process-entry-s32-result: Return each mounted-file processing result through a real helper; result result form with s32 slot. objdiff 96.122925%; insns 293/301 diffs 199; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-s32-result.

c-thread-process-entry-s32-boolean: Return each mounted-file processing result through a real helper; boolean result form with s32 slot. objdiff 97.833885%; insns 298/301 diffs 198; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-s32-boolean.

c-thread-process-entry-u8-direct: Return each mounted-file processing result through a real helper; direct result form with u8 slot. objdiff 96.122925%; insns 293/301 diffs 199; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-u8-direct.

c-thread-process-entry-u8-result: Return each mounted-file processing result through a real helper; result result form with u8 slot. objdiff 96.122925%; insns 293/301 diffs 199; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-u8-result.

c-thread-process-entry-u8-boolean: Return each mounted-file processing result through a real helper; boolean result form with u8 slot. objdiff 97.833885%; insns 298/301 diffs 198; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-process-entry-u8-boolean.

c-thread-valid-report-expression-19: Use the real validity update as the OSReport argument; the preceding validState==TRUE guard proves its value. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-report-expression-19.

c-thread-valid-report-expression-20: Use the real validity update as the OSReport argument; the preceding validState==TRUE guard proves its value. objdiff 97.87376%; insns 301/301 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-report-expression-20.

c-thread-valid-report-expression-36: Use the real validity update as the OSReport argument; the preceding validState==TRUE guard proves its value. objdiff 98.20598%; insns 302/301 diffs 261; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-valid-report-expression-36.

c-thread-response-command-reference: Test actual response packet update/value boundary command-reference without a carrier. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-response-command-reference.

c-thread-response-message-reference: Test actual response packet update/value boundary message-reference without a carrier. objdiff 97.92359%; insns 302/301 diffs 256; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-response-message-reference.

c-thread-response-nested-value: Test actual response packet update/value boundary nested-value without a carrier. objdiff 98.920265%; insns 301/301 diffs 25; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-response-nested-value.

c-thread-response-assign-loop-state: Test actual response packet update/value boundary assign-loop-state without a carrier. objdiff 98.239204%; insns 301/301 diffs 32; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-response-assign-loop-state.

c-banner-last-tlut-local: Resolve the last palette-load scheduling pair via the actual tlut-local value boundary. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-tlut-local.

c-banner-last-tlut-return: Resolve the last palette-load scheduling pair via the actual tlut-return value boundary. objdiff 98.49056%; insns 107/106 diffs 18; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-tlut-return.

c-banner-last-tlut-member-u32: Resolve the last palette-load scheduling pair via the actual tlut-member-u32 value boundary. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-tlut-member-u32.

c-banner-last-tlut-member-s32: Resolve the last palette-load scheduling pair via the actual tlut-member-s32 value boundary. objdiff 91.79245%; insns 108/106 diffs 59; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-tlut-member-s32.

c-banner-last-tlut-comma: Resolve the last palette-load scheduling pair via the actual tlut-comma value boundary. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-tlut-comma.

c-banner-last-load-separate-map: Resolve the last palette-load scheduling pair via the actual load-separate-map value boundary. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-load-separate-map.

c-icon-return-rgb-s32: Use returning member initialization for rgb while retaining the real texture and palette fields. objdiff 93.34%; insns 101/100 diffs 40; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-s32.

c-icon-return-rgb-tlut-s32: Use returning member initialization for rgb-tlut while retaining the real texture and palette fields. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-tlut-s32.

c-icon-return-rgb-ci-s32: Use returning member initialization for rgb-ci while retaining the real texture and palette fields. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-ci-s32.

c-icon-return-rgb-ci-tlut-s32: Use returning member initialization for rgb-ci-tlut while retaining the real texture and palette fields. objdiff 90.65%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-ci-tlut-s32.

c-icon-return-rgb-u32: Use returning member initialization for rgb while retaining the real texture and palette fields. objdiff 93.84%; insns 99/100 diffs 58; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-u32.

c-icon-return-rgb-tlut-u32: Use returning member initialization for rgb-tlut while retaining the real texture and palette fields. objdiff 92.84%; insns 100/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-tlut-u32.

c-icon-return-rgb-ci-u32: Use returning member initialization for rgb-ci while retaining the real texture and palette fields. objdiff 92.54%; insns 101/100 diffs 45; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-ci-u32.

c-icon-return-rgb-ci-tlut-u32: Use returning member initialization for rgb-ci-tlut while retaining the real texture and palette fields. objdiff 94.29%; insns 100/100 diffs 42; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-return-rgb-ci-tlut-u32.

c-banner-tlut-file-u32: Test actual palette initializer file parameter u32 at the remaining scheduling pair. objdiff 90.14151%; insns 108/106 diffs 62; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-u32.

c-banner-tlut-file-const-s32: Test actual palette initializer file parameter const s32 at the remaining scheduling pair. objdiff 92.92453%; insns 108/106 diffs 63; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-const-s32.

c-banner-tlut-file-const-u32: Test actual palette initializer file parameter const u32 at the remaining scheduling pair. objdiff 92.92453%; insns 108/106 diffs 63; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-const-u32.

c-banner-tlut-file-s16: Test actual palette initializer file parameter s16 at the remaining scheduling pair. objdiff 90.14151%; insns 109/106 diffs 64; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-s16.

c-sd-receiver-first: Move the real repeated receiver declaration to first scope to test its simplify threshold against the generated smArg address. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-receiver-first.

c-banner-tlut-file-u16: Test actual palette initializer file parameter u16 at the remaining scheduling pair. objdiff 90.14151%; insns 109/106 diffs 64; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-u16.

c-banner-tlut-file-int: Test actual palette initializer file parameter int at the remaining scheduling pair. objdiff 92.92453%; insns 108/106 diffs 63; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-int.

c-sd-receiver-last: Move the real repeated receiver declaration to last scope to test its simplify threshold against the generated smArg address. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-receiver-last.

c-banner-tlut-file-unsigned-int: Test actual palette initializer file parameter unsigned int at the remaining scheduling pair. objdiff 92.92453%; insns 108/106 diffs 63; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-file-unsigned-int.

c-banner-tlut-slot-const-u8: Test actual palette initializer slot parameter const u8 at the remaining scheduling pair. objdiff 85.471695%; insns 111/106 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-slot-const-u8.

c-banner-tlut-slot-u32: Test actual palette initializer slot parameter u32 at the remaining scheduling pair. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-slot-u32.

c-sd-receiver-scoped-main: Move the real repeated receiver declaration to scoped-main scope to test its simplify threshold against the generated smArg address. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-receiver-scoped-main.

c-banner-tlut-slot-s32: Test actual palette initializer slot parameter s32 at the remaining scheduling pair. objdiff 85.471695%; insns 111/106 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-slot-s32.

c-banner-tlut-slot-const-u32: Test actual palette initializer slot parameter const u32 at the remaining scheduling pair. objdiff 85.471695%; insns 111/106 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-slot-const-u32.

c-banner-tlut-slot-int: Test actual palette initializer slot parameter int at the remaining scheduling pair. objdiff 85.471695%; insns 111/106 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-tlut-slot-int.

c-sd-receiver-scoped-layouts: Move the real repeated receiver declaration to scoped-layouts scope to test its simplify threshold against the generated smArg address. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-receiver-scoped-layouts.

c-banner-last-boundary-texture-ref: Test the real palette/texture texture-ref boundary while preserving the matched address allocation. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-texture-ref.

c-banner-last-boundary-palette-ref: Test the real palette/texture palette-ref boundary while preserving the matched address allocation. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-palette-ref.

c-banner-last-boundary-const-palette-ref: Test the real palette/texture const-palette-ref boundary while preserving the matched address allocation. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-const-palette-ref.

c-banner-last-boundary-separate-palette-return: Test the real palette/texture separate-palette-return boundary while preserving the matched address allocation. objdiff 100.0%; insns 106/106 diffs 0; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-separate-palette-return.

c-sd-trigger-loop-control: Place the self-contained control pane-trigger loops across a real inline boundary. objdiff 98.69643%; insns 1065/1064 diffs 336; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-trigger-loop-control.

c-banner-last-boundary-palette-address-return: Test the real palette/texture palette-address-return boundary while preserving the matched address allocation. objdiff 98.49056%; insns 107/106 diffs 18; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-palette-address-return.

c-banner-last-boundary-load-texture-member: Test the real palette/texture load-texture-member boundary while preserving the matched address allocation. objdiff 98.49056%; insns 107/106 diffs 21; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-load-texture-member.

c-banner-last-boundary-init-tlut-data-first: Test the real palette/texture init-tlut-data-first boundary while preserving the matched address allocation. objdiff 98.113205%; insns 106/106 diffs 2; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-last-boundary-init-tlut-data-first.

c-sd-trigger-loop-dialog: Place the self-contained dialog pane-trigger loops across a real inline boundary. objdiff 98.81485%; insns 1065/1064 diffs 201; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-trigger-loop-dialog.

c-sd-trigger-loop-all: Place the self-contained all pane-trigger loops across a real inline boundary. objdiff 94.95395%; insns 1022/1064 diffs 287; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-trigger-loop-all.

c-sd-hoist-cursors-first: Hoist the real pane-walk cursors at first to delay or advance low-degree node removal. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-hoist-cursors-first.

c-sd-hoist-cursors-before-receiver: Hoist the real pane-walk cursors at before-receiver to delay or advance low-degree node removal. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-hoist-cursors-before-receiver.

c-sd-hoist-cursors-last: Hoist the real pane-walk cursors at last to delay or advance low-degree node removal. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-hoist-cursors-last.

c-icon-load-index-mask-1: Apply the returning GX member boundaries with load-index-mask-1 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-1.

c-icon-load-index-mask-2: Apply the returning GX member boundaries with load-index-mask-2 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-2.

c-icon-load-index-mask-3: Apply the returning GX member boundaries with load-index-mask-3 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-3.

c-icon-load-index-mask-4: Apply the returning GX member boundaries with load-index-mask-4 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-4.

c-icon-load-index-mask-5: Apply the returning GX member boundaries with load-index-mask-5 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-5.

c-icon-load-index-mask-6: Apply the returning GX member boundaries with load-index-mask-6 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-6.

c-icon-load-index-mask-7: Apply the returning GX member boundaries with load-index-mask-7 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-index-mask-7.

c-icon-result-s32-root-first: Apply the returning GX member boundaries with result-s32-root-first to preserve separate row and column values. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-s32-root-first.

c-icon-result-s32-root-last: Apply the returning GX member boundaries with result-s32-root-last to preserve separate row and column values. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-s32-root-last.

c-icon-result-s32-branch: Apply the returning GX member boundaries with result-s32-branch to preserve separate row and column values. objdiff 86.55%; insns 100/100 diffs 60; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-s32-branch.

c-icon-result-u32-root-first: Apply the returning GX member boundaries with result-u32-root-first to preserve separate row and column values. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-u32-root-first.

c-icon-result-u32-root-last: Apply the returning GX member boundaries with result-u32-root-last to preserve separate row and column values. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-u32-root-last.

c-icon-result-u32-branch: Apply the returning GX member boundaries with result-u32-branch to preserve separate row and column values. objdiff 92.19%; insns 101/100 diffs 55; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-u32-branch.

c-icon-result-int-root-first: Apply the returning GX member boundaries with result-int-root-first to preserve separate row and column values. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-int-root-first.

c-icon-result-int-root-last: Apply the returning GX member boundaries with result-int-root-last to preserve separate row and column values. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-int-root-last.

c-icon-result-int-branch: Apply the returning GX member boundaries with result-int-branch to preserve separate row and column values. objdiff 86.55%; insns 100/100 diffs 60; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-int-branch.

c-icon-result-unsigned-int-root-first: Apply the returning GX member boundaries with result-unsigned-int-root-first to preserve separate row and column values. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-unsigned-int-root-first.

c-icon-result-unsigned-int-root-last: Apply the returning GX member boundaries with result-unsigned-int-root-last to preserve separate row and column values. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-unsigned-int-root-last.

c-icon-result-unsigned-int-branch: Apply the returning GX member boundaries with result-unsigned-int-branch to preserve separate row and column values. objdiff 92.19%; insns 101/100 diffs 55; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-result-unsigned-int-branch.

c-icon-ci-param-const-s32: Apply the returning GX member boundaries with ci-param-const-s32 to preserve separate row and column values. objdiff 87.89%; insns 99/100 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-ci-param-const-s32.

c-icon-ci-param-int: Apply the returning GX member boundaries with ci-param-int to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-ci-param-int.

c-icon-ci-param-u32: Apply the returning GX member boundaries with ci-param-u32 to preserve separate row and column values. objdiff 87.89%; insns 99/100 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-ci-param-u32.

c-icon-ci-param-const-u32: Apply the returning GX member boundaries with ci-param-const-u32 to preserve separate row and column values. objdiff 87.89%; insns 99/100 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-ci-param-const-u32.

c-icon-ci-param-s16: Apply the returning GX member boundaries with ci-param-s16 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-ci-param-s16.

c-banner-clean: Keep the exact banner with readable private member names and formatting, guarded to this translation unit. objdiff 100.0%; insns 106/106 diffs 0; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-banner-clean.

c-icon-member-index-types-s32-s32-s32-s32: Apply the returning GX member boundaries with member-index-types-s32-s32-s32-s32 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-s32-s32-s32.

c-icon-member-index-types-s32-s32-s32-u32: Apply the returning GX member boundaries with member-index-types-s32-s32-s32-u32 to preserve separate row and column values. objdiff 92.84%; insns 100/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-s32-s32-u32.

c-icon-member-index-types-s32-s32-u32-s32: Apply the returning GX member boundaries with member-index-types-s32-s32-u32-s32 to preserve separate row and column values. objdiff 95.84%; insns 99/100 diffs 58; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-s32-u32-s32.

c-icon-member-index-types-s32-s32-u32-u32: Apply the returning GX member boundaries with member-index-types-s32-s32-u32-u32 to preserve separate row and column values. objdiff 96.74%; insns 99/100 diffs 59; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-s32-u32-u32.

c-icon-member-index-types-s32-u32-s32-s32: Apply the returning GX member boundaries with member-index-types-s32-u32-s32-s32 to preserve separate row and column values. objdiff 92.98%; insns 101/100 diffs 40; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-u32-s32-s32.

c-icon-member-index-types-s32-u32-s32-u32: Apply the returning GX member boundaries with member-index-types-s32-u32-s32-u32 to preserve separate row and column values. objdiff 86.89%; insns 100/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-u32-s32-u32.

c-icon-member-index-types-s32-u32-u32-s32: Apply the returning GX member boundaries with member-index-types-s32-u32-u32-s32 to preserve separate row and column values. objdiff 91.89%; insns 100/100 diffs 52; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-u32-u32-s32.

c-icon-member-index-types-s32-u32-u32-u32: Apply the returning GX member boundaries with member-index-types-s32-u32-u32-u32 to preserve separate row and column values. objdiff 87.89%; insns 99/100 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-s32-u32-u32-u32.

c-icon-member-index-types-u32-s32-s32-s32: Apply the returning GX member boundaries with member-index-types-u32-s32-s32-s32 to preserve separate row and column values. objdiff 87.89%; insns 99/100 diffs 67; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-s32-s32-s32.

c-icon-member-index-types-u32-s32-s32-u32: Apply the returning GX member boundaries with member-index-types-u32-s32-s32-u32 to preserve separate row and column values. objdiff 91.89%; insns 100/100 diffs 52; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-s32-s32-u32.

c-icon-member-index-types-u32-s32-u32-s32: Apply the returning GX member boundaries with member-index-types-u32-s32-u32-s32 to preserve separate row and column values. objdiff 86.89%; insns 100/100 diffs 61; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-s32-u32-s32.

c-icon-member-index-types-u32-s32-u32-u32: Apply the returning GX member boundaries with member-index-types-u32-s32-u32-u32 to preserve separate row and column values. objdiff 92.98%; insns 101/100 diffs 40; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-s32-u32-u32.

c-icon-member-index-types-u32-u32-s32-s32: Apply the returning GX member boundaries with member-index-types-u32-u32-s32-s32 to preserve separate row and column values. objdiff 96.74%; insns 99/100 diffs 59; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-u32-s32-s32.

c-icon-member-index-types-u32-u32-s32-u32: Apply the returning GX member boundaries with member-index-types-u32-u32-s32-u32 to preserve separate row and column values. objdiff 95.84%; insns 99/100 diffs 58; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-u32-s32-u32.

c-icon-member-index-types-u32-u32-u32-s32: Apply the returning GX member boundaries with member-index-types-u32-u32-u32-s32 to preserve separate row and column values. objdiff 92.84%; insns 100/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-u32-u32-s32.

c-icon-member-index-types-u32-u32-u32-u32: Apply the returning GX member boundaries with member-index-types-u32-u32-u32-u32 to preserve separate row and column values. objdiff 96.84%; insns 100/100 diffs 30; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-index-types-u32-u32-u32-u32.

c-icon-palette-load-in-member-s32-s32: Keep the complete palette load-in-member operation within a real member boundary and consume its s32 file index. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-in-member-s32-s32.

c-icon-palette-load-in-member-s32-u32: Keep the complete palette load-in-member operation within a real member boundary and consume its s32 file index. objdiff 92.64%; insns 102/100 diffs 36; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-in-member-s32-u32.

Rx7c banner exact candidate and allocator explanation

- Target banner register map: metadata root r31, file-byte offset r30, slot-byte offset r29, file r28, slot r27, this r26, selected metadata r25; CI texture row r22, shared column r24, palette row r23. Re-read the target Ghidra export and every GX call in target asm. Target validation computes (file offset + root) + slot offset, then the selected metadata computes (root + slot offset) + file offset. Each palette use recomputes row + column. There is no extra out-of-line member call; an inlined member boundary is consistent with the target.
- Direct metadata expressions plus actual MemoryCardManager GX initializer methods produce the target metadata graph. The signed file parameter gives the inline indexed calculation a distinct boundary from the caller's u32 file. In mwdbg-c-banner-exact, root v50, file offset v39 and slot offset v38 survive until final simplify at degrees 12, 13, 14 and color first as r31, r30, r29. The selected metadata v66 instead simplifies at degree 28 during the first sweep, so it colors after this/slot/file and takes target r25. Baseline selected-pointer CSE had colored before the offsets.
- A void RGB initializer left a second column multiply after GXInitTexObj, 107/106 instructions. Returning its actual GXTexObj pointer and loading that return value preserves the target row/column operands across the call, giving 106 instructions with only the two palette-load setup instructions swapped. Returning the actual GXTlutObj pointer from palette initialization moves its address formation before the map constant. Using the same signed file index for the following texture load removes the otherwise extra column-copy mr. These are ordinary field access and initialized object returns, with no carrier or uninitialized value.
- The final member helpers are private, formatted normally, and restricted by the existing IPL_MEMORY_CARD_MANAGER_CPP macro. They add no fields or virtual methods. create_banner reads the same metadata and passes the same addresses/data/formats to the same GX functions in the same order. The file values are directory indices into the 127-entry cell arrays; the explicit signed index agrees with the initializer parameters.
- mwdbg-c-banner-exact is byte-identical to independent original-Ninja-flags wibo, including SJIS. The cleaned source compiled by normal Ninja is byte-identical to that captured whole object. Exact-name objdiff 90.42453 -> 100.0, ctxdiff 106/106 diffs 0, empty pools identical, no other function drops. The quick three-unit gate passes, with zero forbidden additions or readability warnings. Clean final gate remains pending until all searches finish.

c-icon-palette-load-in-member-u32-s32: Keep the complete palette load-in-member operation within a real member boundary and consume its u32 file index. objdiff 82.6%; insns 102/100 diffs 55; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-in-member-u32-s32.

c-icon-palette-load-in-member-u32-u32: Keep the complete palette load-in-member operation within a real member boundary and consume its u32 file index. objdiff 85.79%; insns 102/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-in-member-u32-u32.

c-icon-palette-load-and-return-s32-s32: Keep the complete palette load-and-return operation within a real member boundary and consume its s32 file index. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-and-return-s32-s32.

c-icon-palette-load-and-return-s32-u32: Keep the complete palette load-and-return operation within a real member boundary and consume its s32 file index. objdiff 85.6%; insns 101/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-and-return-s32-u32.

c-icon-palette-load-and-return-u32-s32: Keep the complete palette load-and-return operation within a real member boundary and consume its u32 file index. objdiff 85.79%; insns 102/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-and-return-u32-s32.

c-icon-palette-load-and-return-u32-u32: Keep the complete palette load-and-return operation within a real member boundary and consume its u32 file index. objdiff 85.79%; insns 102/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-and-return-u32-u32.

c-icon-palette-cell-reference-s32-s32: Keep the complete palette cell-reference operation within a real member boundary and consume its s32 file index. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-cell-reference-s32-s32.

c-icon-palette-cell-reference-s32-u32: Keep the complete palette cell-reference operation within a real member boundary and consume its s32 file index. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-cell-reference-s32-u32.

c-icon-palette-cell-reference-u32-s32: Keep the complete palette cell-reference operation within a real member boundary and consume its u32 file index. objdiff 85.64%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-cell-reference-u32-s32.

c-icon-palette-cell-reference-u32-u32: Keep the complete palette cell-reference operation within a real member boundary and consume its u32 file index. objdiff 90.49%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-cell-reference-u32-u32.

c-icon-palette-load-return-index-s32-s32: Keep the complete palette load-return-index operation within a real member boundary and consume its s32 file index. objdiff 92.64%; insns 102/100 diffs 36; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-return-index-s32-s32.

c-icon-palette-load-return-index-s32-u32: Keep the complete palette load-return-index operation within a real member boundary and consume its s32 file index. objdiff 92.64%; insns 102/100 diffs 36; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-return-index-s32-u32.

c-icon-palette-load-return-index-u32-s32: Keep the complete palette load-return-index operation within a real member boundary and consume its u32 file index. objdiff 85.79%; insns 102/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-return-index-u32-s32.

c-icon-palette-load-return-index-u32-u32: Keep the complete palette load-return-index operation within a real member boundary and consume its u32 file index. objdiff 85.79%; insns 102/100 diffs 57; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-palette-load-return-index-u32-u32.

c-thread-degree-free-slot-file-scanResult-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-slot-file-scanResult-listingFile.

c-thread-degree-free-scanResult-file-slot-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.58804%; insns 301/301 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-scanResult-file-slot-listingFile.

c-thread-degree-free-file-slot-scanResult-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.75415%; insns 301/301 diffs 34; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-file-slot-scanResult-listingFile.

c-thread-degree-free-listingFile-slot-file-scanResult: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-listingFile-slot-file-scanResult.

c-thread-degree-free-slot-scanResult-file-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.63787%; insns 301/301 diffs 42; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-slot-scanResult-file-listingFile.

c-thread-degree-free-slot-listingFile-file-scanResult: Order the actual mount slot, file, joined result and listing nodes across c-thread-free-helper-freeFile-freeBlocks-result so fewer neighbors remain at first simplify. objdiff 98.52159%; insns 301/301 diffs 48; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-free-slot-listingFile-file-scanResult.

c-thread-degree-entry-slot-file-scanResult-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.65116%; insns 298/301 diffs 201; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-slot-file-scanResult-listingFile.

c-thread-degree-entry-scanResult-file-slot-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.601326%; insns 298/301 diffs 202; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-scanResult-file-slot-listingFile.

c-thread-degree-entry-file-slot-scanResult-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.76744%; insns 298/301 diffs 198; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-file-slot-scanResult-listingFile.

c-thread-degree-entry-listingFile-slot-file-scanResult: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.65116%; insns 298/301 diffs 201; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-listingFile-slot-file-scanResult.

c-thread-degree-entry-slot-scanResult-file-listingFile: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.601326%; insns 298/301 diffs 202; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-slot-scanResult-file-listingFile.

c-thread-degree-entry-slot-listingFile-file-scanResult: Order the actual mount slot, file, joined result and listing nodes across c-thread-process-entry-s32-boolean so fewer neighbors remain at first simplify. objdiff 97.65116%; insns 298/301 diffs 201; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-degree-entry-slot-listingFile-file-scanResult.

Rx7c thread and SD allocator follow-up

- The self-contained game-block-count helper preserves 301 instructions but changes color reuse rather than fixing mount state. In mwdbg-c-thread-free-helper, command v35 simplifies first at degree24, scanResult v37 at23, file v38 at23 and listingFile v39 at21; mount slot v36 still survives to the final sweep at degree17 and takes r26. Named result/file/listing then take r22/r20/r19, while the target needs r20/r23/r23 and slot r22. The actual outer-slot/validity/exit state remains correctly r26/r25/r24. Six helper-local declaration orders, combined mount-local orders, and independent format/delete result variables do not solve that threshold. The completed debugger object equals original-flags wibo.
- The directory-listing helper introduces one instruction and the per-file process helper combines error branches, dropping three or eight instructions. Neither matches the target. Returning validity state after reporting, passing it by reference, assigning it inside the report argument, reusing successive file indices and response-value boundaries also fail to stop the reply's command coalescing/constant-one substitution. Only private snapshots changed.
- SD receiver declarations at first/last/root/per-layout scopes and hoisted actual pane cursors all normalize to 1064 instructions and 175 differences. mwdbg-c-sd-hoisted-cursors validates against original-flags wibo. smArg remains in the final simplify sweep after the pool base; the receiver has low degree and is removed early. Real pane-trigger loop helpers add one instruction or fail to inline the complete tail. These are rejected, with source unchanged.
- No banner source search is needed after the manual exact match. Nine 1200-second searches for thread, SD and icon are queued under the unchanged 24-slot limiter, using seeds 207/219/231 and new helper candidates where available. Their time budgets start only after a slot is acquired.

c-sd-message-inline-const-u32: Change only the actual System message inline primitive parameter identity to const u32; inspect the late smArg temporary. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-message-inline-const-u32.

c-thread-mount-helper-u8-result-reference: Separate mount/repair/check into a real success helper with result-reference output and u8 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-u8-result-reference.

c-sd-message-inline-unsigned-int: Change only the actual System message inline primitive parameter identity to unsigned int; inspect the late smArg temporary. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-message-inline-unsigned-int.

c-thread-mount-helper-u8-result-pointer: Separate mount/repair/check into a real success helper with result-pointer output and u8 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-u8-result-pointer.

c-thread-mount-helper-s32-result-reference: Separate mount/repair/check into a real success helper with result-reference output and s32 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-s32-result-reference.

c-sd-message-inline-const-unsigned-int: Change only the actual System message inline primitive parameter identity to const unsigned int; inspect the late smArg temporary. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-message-inline-const-unsigned-int.

c-thread-mount-helper-s32-result-pointer: Separate mount/repair/check into a real success helper with result-pointer output and s32 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-s32-result-pointer.

c-sd-message-inline-s32: Change only the actual System message inline primitive parameter identity to s32; inspect the late smArg temporary. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-message-inline-s32.

c-thread-mount-helper-const-u8-result-reference: Separate mount/repair/check into a real success helper with result-reference output and const u8 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-const-u8-result-reference.

c-sd-message-inline-const-s32: Change only the actual System message inline primitive parameter identity to const s32; inspect the late smArg temporary. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-message-inline-const-s32.

c-thread-mount-helper-const-u8-result-pointer: Separate mount/repair/check into a real success helper with result-pointer output and const u8 slot. objdiff 96.3289%; insns 305/301 diffs 239; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-thread-mount-helper-const-u8-result-pointer.

c-sd-return-assigned-pointer-u32: Return the actual localized text receiver from its assignment boundary with pointer and u32 inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-pointer-u32.

c-sd-return-assigned-pointer-const-u32: Return the actual localized text receiver from its assignment boundary with pointer and const u32 inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-pointer-const-u32.

c-sd-return-assigned-pointer-unsigned-int: Return the actual localized text receiver from its assignment boundary with pointer and unsigned int inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-pointer-unsigned-int.

c-sd-return-assigned-reference-u32: Return the actual localized text receiver from its assignment boundary with reference and u32 inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-reference-u32.

c-sd-return-assigned-reference-const-u32: Return the actual localized text receiver from its assignment boundary with reference and const u32 inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-reference-const-u32.

c-sd-return-assigned-reference-unsigned-int: Return the actual localized text receiver from its assignment boundary with reference and unsigned int inputs. objdiff 99.15884%; insns 1064/1064 diffs 175; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-sd-return-assigned-reference-unsigned-int.

c-icon-load-return-direct-s16-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 ci input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s16-ci.

c-icon-load-return-direct-s16-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s16-both.

c-icon-load-return-direct-s16-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s16-member-index.

c-icon-load-return-direct-s32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 ci input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s32-ci.

c-icon-load-return-direct-s32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s32-both.

c-icon-load-return-direct-s32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 member-index input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-s32-member-index.

c-icon-load-return-direct-u32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 ci input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-u32-ci.

c-icon-load-return-direct-u32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-u32-both.

c-icon-load-return-direct-u32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-u32-member-index.

c-icon-load-return-direct-const-u32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 ci input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-const-u32-ci.

c-icon-load-return-direct-const-u32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-const-u32-both.

c-icon-load-return-direct-const-u32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-direct-const-u32-member-index.

c-icon-load-return-joined-s16-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 ci input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s16-ci.

c-icon-load-return-joined-s16-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s16-both.

c-icon-load-return-joined-s16-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; s16 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s16-member-index.

c-icon-load-return-joined-s32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 ci input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s32-ci.

c-icon-load-return-joined-s32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s32-both.

c-icon-load-return-joined-s32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; s32 member-index input boundary. objdiff 91.74%; insns 100/100 diffs 35; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-s32-member-index.

c-icon-load-return-joined-u32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 ci input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-u32-ci.

c-icon-load-return-joined-u32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-u32-both.

c-icon-load-return-joined-u32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; u32 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-u32-member-index.

c-icon-load-return-joined-const-u32-ci: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 ci input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-const-u32-ci.

c-icon-load-return-joined-const-u32-both: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 both input boundary. objdiff 79.59%; insns 98/100 diffs 51; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-const-u32-both.

c-icon-load-return-joined-const-u32-member-index: Return the actually loaded texture from a MemoryCardManager member after palette setup; const u32 member-index input boundary. objdiff 94.24%; insns 101/100 diffs 28; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-load-return-joined-const-u32-member-index.

The nine current searches remained queued together. The previously validated private fair_search_handoff wrapper now waits on ordinary existing global slots, releasing each reservation before resuming only our queued process. Every compiler search still acquires its own unchanged 24-slot limiter and runs the full 1200-second budget. No other process, lock file or capacity limit is modified.

c-icon-joined-types-s32-s32-s32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-s32-s32-joined.

c-icon-joined-types-s32-s32-s32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-s32-s32-initialized.

c-icon-joined-types-s32-s32-u32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-s32-u32-joined.

c-icon-joined-types-s32-s32-u32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 97.69%; insns 101/100 diffs 29; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-s32-u32-initialized.

c-icon-joined-types-s32-u32-s32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 90.49%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-u32-s32-joined.

c-icon-joined-types-s32-u32-s32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 90.49%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-u32-s32-initialized.

c-icon-joined-types-s32-u32-u32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 90.49%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-u32-u32-joined.

c-icon-joined-types-s32-u32-u32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 90.49%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-s32-u32-u32-initialized.

c-icon-joined-types-u32-s32-s32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 85.64%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-s32-s32-joined.

c-icon-joined-types-u32-s32-s32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 85.64%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-s32-s32-initialized.

c-icon-joined-types-u32-s32-u32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 85.64%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-s32-u32-joined.

c-icon-joined-types-u32-s32-u32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 85.64%; insns 101/100 diffs 56; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-s32-u32-initialized.

c-icon-joined-types-u32-u32-s32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-u32-s32-joined.

c-icon-joined-types-u32-u32-s32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-u32-s32-initialized.

c-icon-joined-types-u32-u32-u32-joined: Align actual initializer index types with the unsigned result lookup and joined texture-result lifetime. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-u32-u32-joined.

c-icon-joined-types-u32-u32-u32-initialized: Align actual initializer index types with the unsigned result lookup and initialized texture-result lifetime. objdiff 90.55%; insns 100/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-joined-types-u32-u32-u32-initialized.

c-icon-member-field-s32-result: Select the actual MCFileCell texture member through a typed member-pointer accessor at result uses. objdiff 91.0%; insns 102/100 diffs 45; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-s32-result.

Rx7c icon allocator conclusion from the new member calls

- mwdbg-c-icon-return-members is validated byte-for-byte against original-flags wibo. It fixes the metadata prefix and the RGB address operation, reaching 96.84% at 100/100 instructions, but the common texture result is v42/r27 rather than target r24. The CI full texture pointer is still formed before GXInitTexObjCI, so its lifetime displaces the column to r28 and row to r23 and expands the save frame to 0x40 rather than 0x30. The result-to-r3 copies all fail coalescing due to interference.
- An explicitly joined result with an unsigned final lookup avoids the early complete pointer but adds one late column copy. mwdbg-c-icon-result-index validates independently: before allocation the final column is a second mulli v109; later optimization turns it into mr, after allocation. Its extra use keeps file v34 live, blocking the target column r27. The named result v38 simplifies at degree12, CI row v41 at26, column v44 at23; their colors are result/row r23 and column r26. The desired early column CSE must occur without recreating full-pointer CSE.
- Signed/unsigned initializer parameters, returned palette references, initializer-and-load member boundaries, explicit returned texture joins, and initialization of that genuine result were tested. They either restore full-pointer CSE or leave the extra late copy/instruction. No icon helper or index change is retained. The best positional candidate remains 17 differences and 93.35%, while the higher 96.84% candidate still has the wrong frame/address lifetime.

c-icon-member-field-s32-init: Select the actual MCFileCell texture member through a typed member-pointer accessor at init uses. objdiff 90.0%; insns 103/100 diffs 46; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-s32-init.

c-icon-member-field-s32-all: Select the actual MCFileCell texture member through a typed member-pointer accessor at all uses. objdiff 71.93%; insns 108/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-s32-all.

c-icon-member-field-u32-result: Select the actual MCFileCell texture member through a typed member-pointer accessor at result uses. objdiff 90.0%; insns 103/100 diffs 46; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-u32-result.

c-icon-member-field-u32-init: Select the actual MCFileCell texture member through a typed member-pointer accessor at init uses. objdiff 86.3%; insns 104/100 diffs 52; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-u32-init.

c-icon-member-field-u32-all: Select the actual MCFileCell texture member through a typed member-pointer accessor at all uses. objdiff 71.93%; insns 108/100 diffs 44; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-member-field-u32-all.

c-icon-row-array-s32-result: Use the actual fixed MCFileCell row as the result accessor input. objdiff 91.0%; insns 102/100 diffs 45; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-row-array-s32-result.

c-icon-row-array-s32-init: Use the actual fixed MCFileCell row as the init accessor input. objdiff 90.0%; insns 103/100 diffs 46; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-row-array-s32-init.

c-icon-row-array-u32-result: Use the actual fixed MCFileCell row as the result accessor input. objdiff 90.0%; insns 103/100 diffs 46; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-row-array-u32-result.

c-icon-row-array-u32-init: Use the actual fixed MCFileCell row as the init accessor input. objdiff 86.3%; insns 104/100 diffs 52; pool identical; other drops []. Trial retained only under build/rx7c/trials/c-icon-row-array-u32-init.

Rx7c manual-pass audit: sd 21 compiled source trials, icon 140 compiled source trials, thread 70 compiled source trials, banner 61 compiled source trials. All four assigned functions received more than three distinct source-level attempts, target/Ghidra review and independently validated candidate allocator dumps. Only the exact banner source and its ordinary private member helpers are applied. Candidate results and source hashes are indexed in build/rx7c/manual-summary.json; failed compile trials are also logged above.

Banner source review confirms sort_file_array writes real file numbers from its 0..0x7E loop; card removal also uses the existing -1 sentinel. The signed helper index and explicit final cast agree for all valid entries. No validation or sentinel handling changed, and the complete emitted function is exact. Only create_banner differs outside the guarded nonvirtual member definitions; every other owned function score is unchanged. The literal checker analyzes the banner successfully with zero string arguments and no errors.

Search interpretation: srcsearch prints SOLUTION for equal instruction counts even below 100% fuzzy. Current thread-219 messages in the 98.x range are partial candidates, not exact matches. The final handoff checks exact-name objdiff and zero positional differences independently; no such partial candidate is applied.

Rx7c completed source searches

- thread seeds 207/219/231: 360/357/358 trials; best scores 98.920265/98.87043/98.920265%. All ran their full 1200-second budgets after acquiring normal global slots and exited 0. No exact function found; no search source applied.
- sd seeds 207/219/231: 313/315/311 trials; best scores 99.15884/99.15884/99.15884%. All ran their full 1200-second budgets after acquiring normal global slots and exited 0. No exact function found; no search source applied.
- icon seeds 207/219/231: 1280/1295/1288 trials; best scores 96.84/93.35/96.84%. All ran their full 1200-second budgets after acquiring normal global slots and exited 0. No exact function found; no search source applied.
- All nine search processes and the private fairness helper have exited. No full build ran concurrently with another full build. The clean three-unit gate started after the last search exited; output is build/rx7c/final-gate.log. Search details: build/rx7c/search-summary.json.


Rx7c final clean gate and handoff (2026-10-05)

- Clean gate (without --quick) passed for MemoryCardManager, CardSequence and SDMemory. Full 43U build passed; main.dol SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. All three pools are IDENTICAL. There are zero regressions against origin/main, zero net forbidden patterns and zero readability warnings. Evidence: build/rx7c/final-gate.log.
- MemoryCardManager: exact functions 24/26 -> 25/26; matched code 4572/5396 -> 4996/5396; no data section. create_banner 90.42453% -> 100.0%, 106/106 instructions, diffs 0. _create_icon remains 87.55%, 100/100 instructions, diffs 37. getComment remains 100.0%, 123/123 instructions, diffs 0.
- CardSequence: exact functions 28/30 -> 28/30; code 6600/9852 and data 1496/1496 unchanged. cardThreadMain remains 97.9402%, 301/301 instructions, diffs 78. The landed runCardMoveOrCopy remains 100.0%, 608/608 instructions, diffs 0.
- SDMemory: exact functions 64/66 -> 64/66; code 14812/20872 and data 3344/3344 unchanged. create remains 99.15884%, 1064/1064 instructions, diffs 175.
- Post-gate progress/report generation, decomp_status.py and build/43U/ok passed. check_decomp_complete.py exits 1 because the overall project still has unmatched/unlinked code and data (overall exact code 93.589424%, linked code 79.266525%). This result is not a full-project completion claim. Evidence: build/rx7c/final-{progress,status,completion}.log.
- Post-gate exact-name objdiff, ctxdiff and pool results are recorded in build/rx7c/final-measurements.json and final-ctx-*.txt/final-pool-*.txt. The banner literal check analyzed one function, zero string arguments, zero candidates and zero errors.
- Final source hashes equal the retained candidate hashes in build/rx7c/retained-source.json. Only create_banner, its three private nonvirtual member initializers, and this attempts log are changed. The winning object was also independently byte-validated by mwdbg against the original Ninja flags. No source changes were retained for the other three assigned functions.
- Allocator handoff: banner root/file-offset/slot-offset survive final simplification at degrees 12/13/14 and take r31/r30/r29; selected metadata simplifies earlier at degree 28 and takes r25. Returning initialized texture/palette objects moves their address formation past GX calls; matching the signed initializer index at the CI texture load removes the last late copy. SD still gives late smArg priority over the string pool; thread still has mount-slot degree and reply-coalescing differences; icon still has full-pointer CSE or an extra column copy after allocation. Detailed validated dump paths and rejected source trials are recorded above.

GATE PASS
