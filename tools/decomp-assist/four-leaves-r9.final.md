[libs/RVL_SDK/src/nup/nup_nhttp] objdiff: code 2588/2588 data 144/144 functions 9/9 fuzzy 100.0000 linked code 0
[src/utility/iplESMisc] objdiff: code 9404/11200 data None/4416 functions 30/31 fuzzy 96.7604 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1008/2248 data 72/112 functions 10/14 fuzzy 87.1886 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.8031 linked code 0
GATE PASS
libs/RVL_SDK/src/nup/nup_nhttp: exact 8/9 -> 9/9; code 2364/2588 -> 2588/2588; data 144/144 -> 144/144
src/utility/iplESMisc: exact 30/31 -> 30/31; code 9404/11200 -> 9404/11200; data 0/4416 -> 0/4416
DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap 79.797325%: 434/449 instructions; inline boundaries, retained status lifetime, masked title switch; pool first divergence83. Real helpers fixed114 strings but not instruction structure.
libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL: exact 10/14 -> 10/14; code 1008/2248 -> 1008/2248; data 72/112 -> 72/112
NHTTPi_strnicmp 99.76471%: 51/51; only two initial constant loads swapped: target A,Z,zero; ours A,zero,Z. Twelve valid source variants plus declaration search did not change scheduling.
NHTTPi_intToStr 95.57895%: 95/95; output cursor is saved r28 instead of target scratch r5; array initializer registers and zero-digit increment scheduling. Seven valid variants and23 declaration builds plateaued.
NHTTPi_compareToken 54.622223%: 44/45 retained; ternary right fold and condition-entry loop recovered45 but constant ordering and raw/folded left colors stayed different. Eleven valid variants and6 declaration builds.
NHTTPi_Base64Encode 60.285713%: 119/119; signed padding compares and interleaved input loads, shifted fragments and alphabet indexing. Eight valid variants and13 declaration builds;best43 structural differences.
libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var: exact 0/2 -> 0/2; code 0/2844 -> 0/2844; data 0/0 -> 0/0
TMCJPEGDEC_IdctBlock_Lumi 82.31518%: 257/257; row and column butterfly scheduling, pitch temporaries and register lifetimes. Five valid variants and180 declaration builds;best25 structural differences.
TMCJPEGDEC_IdctBlock_Col 92.47577%: 454/454; DC clamp hoists output argument too early, general-row arithmetic/store scheduling and register lifetimes. Seven valid variants and180 declaration builds;best16 structural differences.
Files changed: libs/RVL_SDK/src/nup/nup_nhttp.cpp; tools/decomp-assist/four-leaves-r9.attempts.md; tools/decomp-assist/four-leaves-r9.final-gate.txt; tools/decomp-assist/four-leaves-r9.final.md.
Code commit: e53a013d match http string flush. Evidence commit follows this full gate.
Uncertain: original unauthorized-data API result type, which was tested with a local guarded declaration and restored; JPEG local lifetimes and decimal rodata final word. No guesses retained.
