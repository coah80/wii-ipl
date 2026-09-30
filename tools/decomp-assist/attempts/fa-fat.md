# fa/pf_fat

Baseline 22/35 exact. Diff against Matching vf source inspected first. Final source preserves all 35 function bodies and changes no headers.

Remaining attempts, source/target instruction counts:
- DoAllocateChain: page-before-sector initialization (216/216, five register differences); initialize flush error after loading page (same); reorder page/sector locals (same); direct page buffer alias (217/216). Restored original 216/216.
- GetClusterAllocated: reorder hint/fat type loads (69/70, 45 differences); reorder first/last cluster locals (same); isolate range check in traversal helper (70/70, eight differences); restore original load ordering (70/70, six differences); reorder hint/fat type declarations (unchanged). Six pointer register differences remain.
- GetSector: preload FAT type before root check (88/88, seven register differences); swap quotient/remainder declaration order (same); reverse addition operand order (same); spell rounded sector count directly (same). Division span and quotient registers remain swapped.
- GetSectorSpecified: immediate error return (17/17, four differences, compiler uses arithmetic normalization); explicit success/error scopes (16/17); inline wrapper boundary (20/17). Restored original 16/17, one conditional branch expansion remains.
- FreeChain: remove page alias (260/254); reorder flush scan locals (256/254, 113 differences); cache FAT type before the loop (different register/control stream). Restored 256/254. Status lifetime and flush registers remain different.
- RefreshFSINFO: reorder endian expression (88/93); explicit FSINFO buffer local (87/93); shared allocation-failure exit (93/93, fourteen differences). Restored endian expression and retained common return; remaining allocation status branch and endian store scheduling differ.

Other experiments yielded exact read/write cluster functions, cluster-link traversal, allocated-cluster counting and specified cluster traversal. Invalid intermediate code with an uninitialized alias was corrected immediately and is absent from the final source.
