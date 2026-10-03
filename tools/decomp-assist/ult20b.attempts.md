# ult20b, 2026-10-03

Worktree data-d5, branch agent/w1003/sol-ult20b-ultra. Read supplied prompt, local AGENTS.md, unslop, coah-voice, ult20/ult3 and earlier unit logs, effort policy, prior-art index. Memory search found only old sandbox-blocked runs; current shell runs normally, no historical result used. No index entry for these units. origin/main fetched under git lock.
Baseline NWC24Download28/30, code10316/12496, data80/80; exif_parse3/6, code1348/5088, data0/0. Pools identical. Both data already100%; no rename or extent correction needed. Ground-truth disassembly and source backups in /tmp/ult20b.

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main e0d3ef03459d56dcb6056fd4cccbf98fb72b3afe, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS IFD1: target leaf with no calls/stack; dispatch pivot132 then11a, ignored111 beqlr and112..119 bgelr, compression103 beq plus bltlr and two blr,11c bgelr and preceding11b falls through rational body. Body reads two rational values with independent offset r8 and pointer r6. IFD0 target has the same rational body and an extra conditional ignored-compression exit. All endianness reads and field stores confirmed against target.

ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273, 274], omit [], default False | dffef8c1a856 | objdiff 95.1157% | structural/exact (19, 202), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273, 274, 284], omit [], default False | 9979a546274b | objdiff 96.33058% | structural/exact (19, 232), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273, 284], omit [274], default False | 9549a63fb8a6 | objdiff 97.38843% | structural/exact (16, 231), instructions 245/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273, 284], omit [274], default True | 7562a98c83be | objdiff 95.735535% | structural/exact (20, 235), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273, 274, 284], omit [], default True | dcc5532ef4aa | objdiff 94.67769% | structural/exact (23, 236), instructions 252/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | sibling-template exits return [273], omit [274], default True | 856917e32ce0 | objdiff 96.14876% | structural/exact (19, 234), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main e0d3ef03459d56dcb6056fd4cccbf98fb72b3afe, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS TMCJPEGDEC_IFD1_tag_parse: compare103 has a lower-than return missing from source dispatch. An explicit ignored TIFF width/height/bits-per-sample tag below103 may preserve the switch edge even though default also ignores the tag; this was not tried in earlier recorded rounds. Compare both siblings using one template.
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [256] at sibling switch boundary | 6be7ddafe6a7 | objdiff 96.8719% | structural/exact (15, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [257] at sibling switch boundary | 30b78fcab6ce | objdiff 96.8719% | structural/exact (15, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [258] at sibling switch boundary | 60546a6752bc | objdiff 95.94215% | structural/exact (15, 230), instructions 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [256, 257] at sibling switch boundary | 1287ac6c53b6 | objdiff 96.85124% | structural/exact (15, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [256, 257, 258] at sibling switch boundary | 518285723177 | objdiff 95.94215% | structural/exact (15, 230), instructions 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [256, 257, 258, 262] at sibling switch boundary | 143b314929c1 | objdiff 97.88843% | structural/exact (12, 229), instructions 245/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [262] at sibling switch boundary | fec1a76b00ff | objdiff 98.28099% | structural/exact (12, 230), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [277] at sibling switch boundary | 689d5e503f03 | objdiff 96.85124% | structural/exact (12, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [278] at sibling switch boundary | 991875c41c3e | objdiff 96.85124% | structural/exact (12, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [279] at sibling switch boundary | 292baa2f8a58 | objdiff 96.85124% | structural/exact (12, 232), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored standard TIFF tags [256, 257, 258, 277, 278, 279] at sibling switch boundary | 4e236d691042 | objdiff 97.26859% | structural/exact (13, 231), instructions 245/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []

BEGIN TMCJPEGDEC_IFD0_tag_parse: origin/main e0d3ef03459d56dcb6056fd4cccbf98fb72b3afe, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS TMCJPEGDEC_IFD0_tag_parse: compare103 has a lower-than return missing from source dispatch. An explicit ignored TIFF width/height/bits-per-sample tag below103 may preserve the switch edge even though default also ignores the tag; this was not tried in earlier recorded rounds. Compare both siblings using one template.
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [256] at sibling switch boundary | f9f7f113183b | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [257] at sibling switch boundary | 9474bd7a9f60 | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [258] at sibling switch boundary | f22e773cd92d | objdiff 99.47817% | structural/exact (7, 459), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [256, 257] at sibling switch boundary | 9b36ef6b99a3 | objdiff 96.977135% | structural/exact (71, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [256, 257, 258] at sibling switch boundary | 8d362c5a749d | objdiff 99.47817% | structural/exact (7, 459), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [256, 257, 258, 262] at sibling switch boundary | 87a6adcc2393 | objdiff 96.977135% | structural/exact (74, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [262] at sibling switch boundary | 2625f425ff5b | objdiff 96.97921% | structural/exact (67, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [277] at sibling switch boundary | 0c7730c272ef | objdiff 96.56341% | structural/exact (61, 462), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [278] at sibling switch boundary | 7ad9edfceff6 | objdiff 96.56341% | structural/exact (61, 462), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [279] at sibling switch boundary | 37f2724c0b64 | objdiff 96.56341% | structural/exact (61, 462), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | ignored standard TIFF tags [256, 257, 258, 277, 278, 279] at sibling switch boundary | 1d8101b7462d | objdiff 96.550934% | structural/exact (73, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | width-label in separate break case | f746cdb59420 | objdiff 95.94215% | structural/exact (15, 230), instructions 240/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | compression/strip break then explicit return after switch | 22eed6921845 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate break with unknown-tag default break | 708e6dfaba65 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate break with terminal default return | 905f37f64d75 | objdiff 96.08264% | structural/exact (21, 236), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | width-label in separate break case | ee0f7a84dfdf | objdiff 99.47817% | structural/exact (7, 459), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | compression/strip break then explicit return after switch | 7e86b10daed6 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate break with unknown-tag default break | d4db961c7744 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate break with terminal default return | 669f0e956201 | objdiff 98.86694% | structural/exact (18, 459), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0100 return, position first with strip return in IFD1 | d57da1f5a86d | objdiff 96.76923% | structural/exact (67, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0100 break, position first with strip return in IFD1 | 0b752e673bda | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0100 return, position last with strip return in IFD1 | b432a7b17799 | objdiff 96.76923% | structural/exact (67, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0100 break, position last with strip return in IFD1 | 93acbdbc98b6 | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0101 return, position first with strip return in IFD1 | 8fbef4eb1a74 | objdiff 96.76923% | structural/exact (67, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0101 break, position first with strip return in IFD1 | b60f1b65baaf | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0101 return, position last with strip return in IFD1 | ebcb45edbc63 | objdiff 96.76923% | structural/exact (67, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0101 break, position last with strip return in IFD1 | 5edd6c701230 | objdiff 96.977135% | structural/exact (66, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0102 return, position first with strip return in IFD1 | ae1adf76ee45 | objdiff 99.074844% | structural/exact (21, 460), instructions 484/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0102 break, position first with strip return in IFD1 | 58f62565a3e8 | objdiff 99.47817% | structural/exact (7, 459), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0102 return, position last with strip return in IFD1 | 803865bf7461 | objdiff 99.074844% | structural/exact (8, 460), instructions 484/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0102 break, position last with strip return in IFD1 | d0ebdad9ad5c | objdiff 99.47817% | structural/exact (7, 459), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0106 return, position first with strip return in IFD1 | 0b547e9cede5 | objdiff 96.77131% | structural/exact (68, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0106 break, position first with strip return in IFD1 | 4448662f2a09 | objdiff 96.97921% | structural/exact (67, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0106 return, position last with strip return in IFD1 | a69d7cd4ef0c | objdiff 96.77131% | structural/exact (68, 462), instructions 483/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | separate ignored TIFF 0106 break, position last with strip return in IFD1 | 279f5fba5035 | objdiff 96.97921% | structural/exact (67, 461), instructions 482/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0100 return, position first with strip return in IFD1 | bcd53796237b | objdiff 95.61157% | structural/exact (22, 236), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0100 break, position first with strip return in IFD1 | b95df7de5429 | objdiff 96.024796% | structural/exact (21, 235), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0100 return, position last with strip return in IFD1 | dbd751f9ef92 | objdiff 95.61157% | structural/exact (22, 236), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0100 break, position last with strip return in IFD1 | ae3de0a64c55 | objdiff 96.024796% | structural/exact (21, 235), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0101 return, position first with strip return in IFD1 | 66db02f426f2 | objdiff 95.61157% | structural/exact (22, 236), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0101 break, position first with strip return in IFD1 | 5c3ac2002807 | objdiff 96.024796% | structural/exact (21, 235), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0101 return, position last with strip return in IFD1 | 63637d01ab16 | objdiff 95.61157% | structural/exact (22, 236), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0101 break, position last with strip return in IFD1 | c4e68847af82 | objdiff 96.024796% | structural/exact (21, 235), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0102 return, position first with strip return in IFD1 | 693a6bff978f | objdiff 97.31405% | structural/exact (15, 230), instructions 247/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0102 break, position first with strip return in IFD1 | 669b836e61af | objdiff 98.55372% | structural/exact (11, 223), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0102 return, position last with strip return in IFD1 | 3df9bac4bfd8 | objdiff 97.31405% | structural/exact (15, 226), instructions 247/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0102 break, position last with strip return in IFD1 | 2109fd5f546e | objdiff 98.55372% | structural/exact (11, 223), instructions 244/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0106 return, position first with strip return in IFD1 | 6589bfb24db1 | objdiff 96.16942% | structural/exact (22, 234), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0106 break, position first with strip return in IFD1 | cdadda25fe01 | objdiff 96.58264% | structural/exact (21, 233), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0106 return, position last with strip return in IFD1 | f5a3b191c8d4 | objdiff 96.16942% | structural/exact (22, 234), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | separate ignored TIFF 0106 break, position last with strip return in IFD1 | 662f918c949b | objdiff 96.58264% | structural/exact (21, 233), instructions 248/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
Rational template trials: both target siblings use byte-for-byte identical bounds/decode templates for X and Y rational pairs, differing only destination offsets. Test one real inline rational helper and a typed result-output boundary; maintain aliasing of mutable IFD0 version bytes and restore each nonexact result.
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | whole-pair rational sibling template | 428a342efbe1 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | whole-pair-output-first rational sibling template | 7e4be1e094ce | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | whole-pair-offset-first rational sibling template | 20945438fef2 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | individual-read rational sibling template | b952128d197b | objdiff 96.0395% | structural/exact (34, 453), instructions 490/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | individual-offset-first rational sibling template | b3aee608cf85 | objdiff 96.0395% | structural/exact (34, 453), instructions 490/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | pair-through-long-output rational sibling template | f78f8ae724e1 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | whole-pair rational sibling template | 2fee52608f92 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | whole-pair-output-first rational sibling template | 646e3178b25f | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | whole-pair-offset-first rational sibling template | 3d5674790bf2 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual-read rational sibling template | 69437ae0ea4b | objdiff 89.28925% | structural/exact (34, 233), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | individual-offset-first rational sibling template | a34a10beace0 | objdiff 89.28925% | structural/exact (34, 233), instructions 249/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | pair-through-long-output rational sibling template | d8df9b84243c | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at first plus default-break | 3488caa4fc4f | objdiff 99.282745% | structural/exact (18, 75), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at first plus final-return | 60a04508d481 | objdiff 99.282745% | structural/exact (18, 75), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at first plus default-break | d4db961c7744 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at first plus final-return | 7e86b10daed6 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at last plus default-break | d89d6924320b | objdiff 99.282745% | structural/exact (6, 456), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at last plus final-return | 836695720846 | objdiff 99.282745% | structural/exact (6, 456), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at last plus default-break | 5891e2f5f44b | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at last plus final-return | a1a4cb52c734 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at original plus default-break | 38b882d8239a | objdiff 99.282745% | structural/exact (18, 75), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 return at original plus final-return | 4c2a49343105 | objdiff 99.282745% | structural/exact (18, 75), instructions 481/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at original plus default-break | b4d4350cf9bc | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | 0103 break at original plus final-return | bd08d5970204 | objdiff 99.49065% | structural/exact (5, 457), instructions 480/481 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at first plus default-break | 83a2273171ce | objdiff 95.54958% | structural/exact (17, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at first plus final-return | 90ed0cf9bb0f | objdiff 95.54958% | structural/exact (17, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at first plus default-break | 708e6dfaba65 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at first plus final-return | 22eed6921845 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at last plus default-break | 99bd9e85b0a9 | objdiff 95.54958% | structural/exact (15, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at last plus final-return | bf03542fa134 | objdiff 95.54958% | structural/exact (15, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at last plus default-break | 27a23f270b48 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at last plus final-return | 07acb09a25f5 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at original plus default-break | b009cca23cd1 | objdiff 95.54958% | structural/exact (17, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 return at original plus final-return | 903beb460100 | objdiff 95.54958% | structural/exact (17, 228), instructions 241/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at original plus default-break | 555adcddc2ad | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | 0111 break at original plus final-return | 1fafc4cfcb64 | objdiff 96.14876% | structural/exact (14, 226), instructions 239/242 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []

BEGIN AddTaskInternal: origin/main a4d145c010bc8a8d3198e68baff458a161899c96, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS Add: target0x30 frame, six saved registers, 401instructions. Validation tool/app/group ownership; URL nested checker performs short-error join before parameter checker clamps to zero; allocation uses word-width bounds and16-bit iterator. Inline update validates, timestamps, clears errors, walks retry mask and stores; target retry setup caches work before retry count, keeps one shift value in r4, retry result joins r5. Recovered last-round99.601 seed using only Add-local helpers, retaining exact public Update. Inspect last structural edge then helper/types, not register permutations first.
ATTEMPT AddTaskInternal | retry readonly validator uses shared false-write boundary | b10bc3dfbde1 | objdiff 99.32668% | structural/exact (6, 31), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions ['NWC24UpdateDlTask']
ATTEMPT AddTaskInternal | retry result checked through explicit negative error join | 1bf202df3c53 | objdiff 99.4389% | structural/exact (1, 44), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | Add retry parameter u16 with shared readonly validator | 334a12ea811a | objdiff 99.32668% | structural/exact (6, 31), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions ['NWC24UpdateDlTask']
ATTEMPT AddTaskInternal | Add retry parameter u32 with shared readonly validator | 931121f1ccaa | objdiff 99.32668% | structural/exact (6, 31), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions ['NWC24UpdateDlTask']
ATTEMPT AddTaskInternal | Add retry parameter s32 with shared readonly validator | 193e3ccf809f | objdiff 99.18953% | structural/exact (7, 31), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions ['NWC24UpdateDlTask']
ATTEMPT AddTaskInternal | retry validation result declared before task view | 6d8dceaf852c | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | retry result initialized by readonly validator at definition | 0dcf39cc66c5 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | count-first real retry helper boundary | 902cebf78819 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | count-first-word real retry helper boundary | 5e26bc34da94 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN NWC24InitDlTask: origin/main a4d145c010bc8a8d3198e68baff458a161899c96, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS Init: target/source144instructions, 0x60frame, five saved registers, identical calls and basic blocks. Only zero/header/ID-high/ID-low/group virtual-register choices differ. Original zero register r29 lives into first header null path. No proven store/reload volatility. Try actual parsing and validation helper boundaries and64-bit title ID representation before final declaration search.

BEGIN NWC24InitDlTask: origin/main a4d145c010bc8a8d3198e68baff458a161899c96, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS Init: target/source144instructions, 0x60frame, five saved registers, identical calls and basic blocks. Only zero/header/ID-high/ID-low/group virtual-register choices differ. Original zero register r29 lives into first header null path. No proven store/reload volatility. Try actual parsing and validation helper boundaries and64-bit title ID representation before final declaration search.
ATTEMPT NWC24InitDlTask | NAND identity parsed by inline helper with two typed output fields | 373da1e02ff6 | objdiff 98.923615% | structural/exact (0, 31), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | u64 composed NAND title identity | a4124f914f09 | objdiff 98.923615% | structural/exact (0, 31), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | s64 composed NAND title identity | af0c3f653a5d | objdiff 97.8125% | structural/exact (6, 102), instructions 145/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | u32 identity with current exact writable predicate | 697a8468afe4 | BUILD FAIL ransform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nwc24\NWC24Download.c # ---------------------------------------------- #     782: line NWC24Err ValidateWritableDlTask(const NWC24DlTask* dlTask) {  #   Error:                                                                 ^ #   (10333) object 'ValidateWritableDlTask(const struct NWC24DlTask *)'  #   redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
ATTEMPT NWC24InitDlTask | unsigned int identity with current exact writable predicate | a4170f5f98aa | BUILD FAIL ransform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nwc24\NWC24Download.c # ---------------------------------------------- #     782: line NWC24Err ValidateWritableDlTask(const NWC24DlTask* dlTask) {  #   Error:                                                                 ^ #   (10333) object 'ValidateWritableDlTask(const struct NWC24DlTask *)'  #   redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
ATTEMPT NWC24InitDlTask | header initialized at definition, null path preserves initial value | 30e7775d107b | objdiff 98.81944% | structural/exact (1, 135), instructions 145/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | header initialization plus exact writable-helper boundary | 670fd100b01e | BUILD FAIL ransform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nwc24\NWC24Download.c # ---------------------------------------------- #     780: line NWC24Err ValidateWritableDlTask(const NWC24DlTask* dlTask) {  #   Error:                                                                 ^ #   (10333) object 'ValidateWritableDlTask(const struct NWC24DlTask *)'  #   redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

BEGIN NWC24InitDlTask: origin/main a4d145c010bc8a8d3198e68baff458a161899c96, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS Init: target/source144instructions, 0x60frame, five saved registers, identical calls and basic blocks. Only zero/header/ID-high/ID-low/group virtual-register choices differ. Original zero register r29 lives into first header null path. No proven store/reload volatility. Try actual parsing and validation helper boundaries and64-bit title ID representation before final declaration search.
ATTEMPT NWC24InitDlTask | NAND identity parsed by inline helper with two typed output fields | b2a904bb4cc6 | objdiff 98.923615% | structural/exact (0, 31), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions ['NWC24UpdateDlTask']
ATTEMPT NWC24InitDlTask | u64 composed NAND title identity | a4124f914f09 | objdiff 98.923615% | structural/exact (0, 31), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | s64 composed NAND title identity | af0c3f653a5d | objdiff 97.8125% | structural/exact (6, 102), instructions 145/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | u32 identity with current exact writable predicate | 2c91c17bdc63 | objdiff 99.201385% | structural/exact (0, 23), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | unsigned int identity with current exact writable predicate | f99e4ec65a45 | objdiff 99.201385% | structural/exact (0, 23), instructions 144/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | header initialized at definition, null path preserves initial value | 30e7775d107b | objdiff 98.81944% | structural/exact (1, 135), instructions 145/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT NWC24InitDlTask | header initialization plus exact writable-helper boundary | f2da60b33191 | objdiff 98.888885% | structural/exact (1, 135), instructions 145/144 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []

BEGIN TMCJPEGDEC_exif_parse: origin/main a4d145c010bc8a8d3198e68baff458a161899c96, owned source changed on remote=False; live baseline still nonexact.

DIAGNOSIS parser:212instructions, same complete CFG and callsIFD0/IFD1/IFD0. Register-only21diffs: original TIFFbase r30 vsr27, firstcursor r27 vsr30, firstcount r23 vsr26, firstextent r26 vsr23; later cursor/count reuse follows those choices. Prior declaration/search and pointer qualifiers exhausted. Try typed inline directory-loop boundaries and input-buffer reader boundaries, then declarations only on a new improved seed.
ATTEMPT TMCJPEGDEC_exif_parse | first-directory-loop | ecb7ad42881d | objdiff 97.1934% | structural/exact (3, 59), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | all-directory-loops | 1415ca3cfefc | objdiff 94.74056% | structural/exact (9, 75), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | byte-order-first-loop | 22ba645e02b1 | objdiff 95.96698% | structural/exact (6, 67), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | count-first-loop | 4cc0e6b1a550 | objdiff 95.96698% | structural/exact (6, 67), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | unsigned-word-loop-count | 5277c3b8f2e7 | objdiff 95.96698% | structural/exact (6, 67), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | half input header reader takes byte order before bytes | 4166199b8956 | objdiff 99.43396% | structural/exact (0, 21), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | word input header reader takes byte order before bytes | 0db47b141b05 | objdiff 99.43396% | structural/exact (0, 21), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT TMCJPEGDEC_exif_parse | both input header reader takes byte order before bytes | 40bfeb764bbc | objdiff 99.43396% | structural/exact (0, 21), instructions 212/212 | POOL IDENTICAL up to 0 (mine=0 base=0) | regressions []
ATTEMPT AddTaskInternal | shared isolated retry helper | 60924f371257 | objdiff 99.32668% | structural/exact (6, 31), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | typed isolated retry helper | 7a7291d2d288 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | mutable isolated retry helper | 15a5a4220e97 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | word-id isolated retry helper | f4dd279eed27 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | mask-first isolated retry helper | 676cbda0fb2d | objdiff 99.58853% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | retry mask value retained across index validation | b80e226ea948 | objdiff 99.601% | structural/exact (1, 30), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | retry-helper | f64786b2b8dc | objdiff 98.99003% | structural/exact (12, 70), instructions 405/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions []
ATTEMPT AddTaskInternal | retry-and-store-helper | a4afc0266437 | objdiff 100.0% | structural/exact (0, 0), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | EXACT CANDIDATE
ATTEMPT AddTaskInternal | exact candidate removes duplicate retry predicate and unused URL, names final operation retry-and-store | bf1967472761 | objdiff 100.0% | structural/exact (0, 0), instructions 401/401 | POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | EXACT CANDIDATE
EXACT AddTaskInternal: retry-and-store inline boundary preserves the real nested return join; r3 holds retry result, r4 holds shift-one, r5 holds caller status, matching all401instructions. Word-width allocation bounds and16-bit ID iterator recover allocator exits. Nested URL check keeps negative-error and zero-success joins. Reuse original retry predicate, no duplicate helper or unused URL. No changes to matched public Update. Full quick gate passed before cleanup; final clean gate still required.

## Remaining-function audit

NWC24InitDlTask: 11 compiled trials, 8 distinct source hashes; all nonexact trials restored. At least3 distinct attempts for every open function.
TMCJPEGDEC_exif_parse: 8 compiled trials, 8 distinct source hashes; all nonexact trials restored. At least3 distinct attempts for every open function.
TMCJPEGDEC_IFD0_tag_parse: 49 compiled trials, 47 distinct source hashes; all nonexact trials restored. At least3 distinct attempts for every open function.
TMCJPEGDEC_IFD1_tag_parse: 55 compiled trials, 53 distinct source hashes; all nonexact trials restored. At least3 distinct attempts for every open function.
No EXIF source changes retained. Init remains baseline. Data allocation audit: NWC24Download.data56/.sdata16/.sbss8 all100%; EXIF owns no allocated data. No renames or extent edits justified. No inline asm, volatile declaration/cast, register keyword, dummy objects, config/shared-header edits, pushes, PRs, merges, rebases or other-worktree edits.

## Final clean gate

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 11920/12496 data 80/80 functions 29/30 fuzzy 99.9504 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 29/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.950386
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 10316/12496 data 80 functions 28 fuzzy 99.7071
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 98.9804 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 98.98035
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
regressions vs baseline: 0
global matched_code_percent: 91.98391 -> 92.03746
global fuzzy_match_percent: 99.72035 -> 99.72137
global complete_code_percent: 74.84181 -> 74.84181
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

Fresh full clean build passes; DOL26116613f624061ba99c8d1a299aaa6efa85670d. AddTaskInternal100.0%,401/401instructions,ctxdiff0. NWC24Download instruction-exact28/30 ->29/30 and matched code10316 ->11920bytes; data80/80unchanged. EXIF3/6and1348/5088unchanged, no data. Regression/forbidden/readability counts all0. Every open function has at least3 distinct compiled trials. No claim that any unit is fully matched or linked. Awaiting parent independent verification.
