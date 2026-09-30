# RVL SDK fa cache matching

Unit: `libs/RVL_SDK/src/fa/pf_cache`, 43U only, still NonMatching.
Starting report: 0 instruction-exact functions, 0/7396 matched code bytes.
Source adapted from the Matching RevoEX `vf/fatfs/pf_cache.c`.

The SDK variant uses the cache at volume offset 0x1624, accepts one data page,
passes the allocation-hit output through its public allocation functions,
marks modified ranges inside writes, and handles whole-page flushing when the
modified start pointer is null. Its bulk write does not perform the RevoEX
write-through clearing pass. The target's left-overlap modified-start
calculation is preserved, including its unusual endpoint arithmetic.

The existing compiler's `dont_inline` pragma preserves the target's calls
between cache operations. List manipulation and used-page scans are written
as ordinary C where the target embeds them. No shared headers were changed.

## Remaining function: PFCACHE_DoWriteNumSectorAndFreeIfNeeded

1. Retain the RevoEX range updater, then adapt dirty-pointer handling to the
   target branches. Changed the overlap branches and removed the write-through
   clearing pass. Result: 233/233 instructions, 185 instruction differences,
   95.77253% objdiff. Direct last-sector arithmetic was hoisted outside the
   loop and occupied another preserved register.
2. Introduce an explicit last-sector temporary and increment successful
   sectors before decrementing remaining sectors. Result: 234/233 instructions;
   last-sector arithmetic still hoisted and aliasing forced a repeated load.
3. Restore the full page-size overlap expression for the modified end pointer.
   Result: 236/233 instructions; an additional preserved end-sector temporary
   survived the memcpy call.
4. Cache the overlap count once and derive its last sector from the page start.
   Result: 234/233 instructions; most instructions matched, but the complex
   memcpy-length expression retained a second end-sector register.
5. Simplify the memcpy length and compute last sector directly from the request.
   Result: 232/233 instructions; last sector hoisted again, shifting registers.
6. Keep the simple memcpy length, cache the overlap count, and derive last sector
   from page start plus overlap count. Result: 233/233 instructions, nine
   instruction differences, 98.21889% objdiff. All surviving differences are
   instructions 136-144 in the right-overlap count/last-sector calculation.
7. Reverse operands in the overlap request-end expression. Result unchanged:
   233/233 instructions, the same nine differences, 98.21889% objdiff.

The retained version computes the same overlapping sector range. The compiler
uses the request end already held in r31; the target recomputes the request end
in r4 and schedules last-sector subtraction before updating success/remaining
counts. No assembly, volatile values, or uninitialized values were introduced.

## Data and validation

Both original and candidate ELF objects have zero allocated non-code sections.
There is no data or string pool in this unit. `pool_diff.py` raises KeyError
because it assumes a .data section; the gate reports IDENTICAL empty pools.
Final report: 35/36 instruction-exact functions, 6464/7396 matched code bytes,
99.77555% fuzzy code, data None/None. Full gate reports zero regressions,
zero forbidden patterns, zero readability warnings, and the target DOL SHA1.
