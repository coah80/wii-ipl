# fa/pf_cache continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFCACHE_DoWriteNumSectorAndFreeIfNeeded:
- rotate independent local declarations: 233/233, 9 differences.
- common operation status exit: 233/233, 9 differences.
- reverse independent local declarations: 233/233, 9 differences.
- Retained: [233, 233, 9].

Additional right-overlap last-sector attempts: request-end minus one and sector plus (count minus one) each produce 232/233 instructions with a hoisted end-sector register; page-start minus one plus overlap retains 233/233 and the same nine differences. Restored. The remaining block uses a cached request end in the candidate while the original recomputes it after memcpy and schedules the last-sector subtraction before successful-sector bookkeeping. Earlier reconstruction attempts are in pf_cache.attempts.md.
