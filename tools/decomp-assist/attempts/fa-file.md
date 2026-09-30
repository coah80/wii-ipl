# fa/pf_file

Baseline 32/45 exact, 10384/17820 code bytes. Compared the existing fa source against the Matching vf counterpart before changing it. Final source defines the existing PF_FA_STR_LAYOUT header guard locally; no shared headers changed.

Remaining attempts, source/target instruction counts:
- GetSFD: corrected free-slot predicate and indexed return (113/113, 28 differences); indexed entry comparisons (113/113, 18 differences); move index initialization before pointer initialization and reverse loop updates (113/113, 42 differences); extract SFD initialization into an inline helper and remove the volume alias (113/113, 38 differences); restore original declarations and reverse loop increments (113/113, 18 differences, different increment ordering). Retained original declarations and loop order: 113/113, 18 differences. Callee-saved registers and two loop increments still differ; objdiff 99.09734%.
- fread: move p_fread definition into object order (96/67, still inlined); use a separate completed-count local (96/67); initialize that local to zero (96/67); introduce a separate read-status scope (96/67); put output initialization before volume lookup and remove the extra status scope (97/67, 28 comparison differences). Retained the last form, which follows the target's output and volume initialization order. The compiler inlines p_fread into this wrapper whereas the original calls it separately; objdiff 48.208954%. p_fread itself remains instruction exact.

New exact functions: Cursor_WriteHeadSector, Cursor_WriteBodySectors, Cursor_WriteTailSector, createEmptyFile, p_remove, p_fopen, p_fwrite, p_combine, p_divide, p_flock, fsetclstlink.

Key source corrections: pass the next sector to the last-access update; use the fa hint and string layouts; retain the removal iterator hint and original first cluster; compute the LFN checksum once and advance the previous-sector pointer; reuse the free-UFD helper; initialize the divide iterators directly and preserve its error through cleanup; propagate cache flush failures; use the target lock flags and release one lock at a time.

The other units' remaining function attempts and evidence are in fa-volume.md, fa-dir.md and fa-fat.md. No configuration state changed.

Remaining objdiff scores across the batch:
- PFVOL_p_setvol 98.82979%; reason and three or more attempts recorded in fa-volume.md.
- PFVOL_attach 98.72159%; reason and three or more attempts recorded in fa-volume.md.
- PFVOL_setcode 53.869564%; reason and three or more attempts recorded in fa-volume.md.
- PFVOL_regctx 99.0%; reason and three or more attempts recorded in fa-volume.md.
- PFDIR_GetSDD 99.710144%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_mkdir 24.046263%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_rmdir 81.4802%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_rename 24.0336%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_move 25.359747%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_fsnext 97.74612%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_fsexec_remove 98.46591%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_p_fsexec 63.478573%; reason and three or more attempts recorded in fa-dir.md.
- PFDIR_opendir 99.74359%; reason and three or more attempts recorded in fa-dir.md.
- PFFAT_DoAllocateChain 99.83796%; reason and three or more attempts recorded in fa-fat.md.
- PFFAT_GetClusterAllocated 99.57143%; reason and three or more attempts recorded in fa-fat.md.
- PFFAT_GetSector 99.431816%; reason and three or more attempts recorded in fa-fat.md.
- PFFAT_GetSectorSpecified 93.52941%; reason and three or more attempts recorded in fa-fat.md.
- PFFAT_FreeChain 97.95276%; reason and three or more attempts recorded in fa-fat.md.
- PFFAT_RefreshFSINFO 96.62366%; reason and three or more attempts recorded in fa-fat.md.
- PFFILE_GetSFD 99.09734%; register allocation and loop increment ordering.
- PFFILE_fread 48.208954%; compiler inlines the separate read operation.
