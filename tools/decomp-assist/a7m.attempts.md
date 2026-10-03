# a7 max attempts

Scope: the twelve assigned eZiText units in sol-low only. Focus is the few smallest differences per the latest task, extending the medium/high/xhigh trials without repeating them. No flag sweeps, register permuters, fake objects or new assembly.

Start HEAD and fetched origin/main: 5af01fa8b9ed69e08d153b6ecb6aae4eb43e9efb

Prior a7h/a7x logs are untracked and remain untouched.

zconvert: {"fuzzy_match_percent": 99.83696, "total_code": "2208", "matched_code": "1380", "matched_code_percent": 62.5, "total_data": "112", "matched_data": "112", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}
zi81key: {"fuzzy_match_percent": 98.23523, "total_code": "21460", "matched_code": "3952", "matched_code_percent": 18.415657, "total_data": "1388", "matched_data": "1280", "matched_data_percent": 92.21902, "total_functions": 9, "matched_functions": 5, "matched_functions_percent": 55.555557, "total_units": 1}
zi8alpha: {"fuzzy_match_percent": 96.52474, "total_code": "21664", "matched_code": "5880", "matched_code_percent": 27.141804, "total_data": "564", "matched_data": "516", "matched_data_percent": 91.489365, "total_functions": 12, "matched_functions": 11, "matched_functions_percent": 91.66667, "total_units": 1}
zi8cgetc: {"fuzzy_match_percent": 96.65468, "total_code": "47816", "matched_code": "4168", "matched_code_percent": 8.716747, "total_data": "536", "matched_data": "144", "matched_data_percent": 26.865673, "total_functions": 8, "matched_functions": 5, "matched_functions_percent": 62.5, "total_units": 1}
zi8getc2: {"fuzzy_match_percent": 99.95064, "total_code": "6888", "matched_code": "6360", "matched_code_percent": 92.334496, "total_data": "332", "matched_data": "332", "matched_data_percent": 100.0, "total_functions": 17, "matched_functions": 15, "matched_functions_percent": 88.2353, "total_units": 1}
zi8match: {"fuzzy_match_percent": 99.98062, "total_code": "8256", "matched_code": "8044", "matched_code_percent": 97.432175, "total_data": "728", "matched_data": "728", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}
zi8uwd: {"fuzzy_match_percent": 99.91717, "total_code": "2656", "matched_code": "2192", "matched_code_percent": 82.53012, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}
zidawg1: {"fuzzy_match_percent": 99.71154, "total_code": "1664", "matched_code": "888", "matched_code_percent": 53.365387, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 6, "matched_functions": 4, "matched_functions_percent": 66.66667, "total_units": 1}
zkokeyp: {"fuzzy_match_percent": 98.746155, "total_code": "5200", "matched_code": "332", "matched_code_percent": 6.3846154, "total_data": "180", "matched_data": "96", "matched_data_percent": 53.333336, "total_functions": 7, "matched_functions": 1, "matched_functions_percent": 14.285715, "total_units": 1}
zmtkey: {"fuzzy_match_percent": 99.84657, "total_code": "2216", "matched_code": "1488", "matched_code_percent": 67.14801, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}
zoemdata: {"fuzzy_match_percent": 98.934425, "total_code": "976", "matched_code": "208", "matched_code_percent": 21.311476, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 3, "matched_functions": 2, "matched_functions_percent": 66.66667, "total_units": 1}
zprepare: {"fuzzy_match_percent": 96.802124, "total_code": "3760", "total_data": "68", "matched_data": "8", "matched_data_percent": 11.764706, "total_functions": 1, "total_units": 1}

zi8getc2 pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zidawg1 pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zoemdata pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zkokeyp pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zmtkey pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zi8uwd pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zconvert pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zi81key pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zi8alpha pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zprepare pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zi8cgetc pool: POOL IDENTICAL up to 0 (mine=0 base=0)

zi8match pool: POOL IDENTICAL up to 0 (mine=0 base=0)

Baseline structure: Zi8SpellingZY 123/123 instructions, six scratch-register differences at 27,28,35-38. Zi8GetPyFinal 53/53, eight scratch-register differences at 26-29,34-37. No missing loads/stores in either function. Zi8getKeyLayout 182/182, sixteen differences from language/tableCount register homes; the xhigh split-extent trial had four differences and is the starting evidence for a narrower lifetime investigation.

## zi81key / Zi8SpellingZY
Fetched origin; current function source agrees with starting branch: True.

### actual final table stored as a flat pair sequence, rather than a cast over a two-dimensional object
Source SHA256 prefix 0292d7595f35
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -59,69 +59,69 @@
 };

-const ziWChar zi8ZYfinalSpelling[64][2] = {
-    { 0x0000, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF8 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
+const ziWChar zi8ZYfinalSpelling[128] = {
+    0x0000, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF9, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0xEFFA, 0xEFF8,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF8,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
 };

@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex * 2];
+  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex * 2 + 1];
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "actual final table stored as a flat pair sequence, rather than a cast over a two-dimensional object", "sha": "0292d7595f35", "build": 0, "insns": [125, 123], "diffs": 99, "first": [[26, ["slwi", "r0, r0, 1"], ["slwi", "r0, r0, 2"]], [27, ["slwi", "r0, r0, 1"], ["lis", "r6, 0"]], [28, ["lis", "r6, 0"], ["addi", "r6, r6, 0"]], [29, ["addi", "r6, r6, 0"], ["lhzx", "r0, r6, r0"]], [30, ["lhzx", "r0, r6, r0"], ["clrlwi", "r6, r0, 0x10"]], [31, ["clrlwi", "r6, r0, 0x10"], ["clrlwi", "r0, r31, 0x18"]], [32, ["clrlwi", "r0, r31, 0x18"], ["slwi", "r0, r0, 1"]], [33, ["slwi", "r0, r0, 1"], ["sthx", "r6, r3, r0"]], [34, ["sthx", "r6, r3, r0"], ["clrlwi", "r0, r30, 0x10"]], [35, ["clrlwi", "r0, r30, 0x10"], ["slwi", "r7, r0, 2"]]]}

### widen final characters at the assignment boundary before output halfword conversion
Source SHA256 prefix c804a3ed1cc2
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = (ziU32)zi8ZYfinalSpelling[finalIndex][0];
+  output[(length & 0xff) + 1] = (ziU32)zi8ZYfinalSpelling[finalIndex][1];
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "widen final characters at the assignment boundary before output halfword conversion", "sha": "c804a3ed1cc2", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### explicit character-width mask at final character emission consistent with key decoding
Source SHA256 prefix 7dc68f784236
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0] & 0xffff;
+  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1] & 0xffff;
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "explicit character-width mask at final character emission consistent with key decoding", "sha": "7dc68f784236", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### flat character-pair table with row address formed before constant column selection
Source SHA256 prefix ba821db8fa3f
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -59,69 +59,69 @@
 };

-const ziWChar zi8ZYfinalSpelling[64][2] = {
-    { 0x0000, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF7, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF8, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0xEFF9, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0xEFFA, 0xEFF8 },
-    { 0xEFFA, 0xEFF8 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF7 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0x0000, 0x0000 },
-    { 0xEFFA, 0xEFF9 },
-    { 0xEFFA, 0xEFF9 },
+const ziWChar zi8ZYfinalSpelling[128] = {
+    0x0000, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF7, 0x0000,
+    0xEFF9, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF8, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0xEFF9, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0xEFFA, 0xEFF8,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0xEFFA, 0xEFF8,
+    0xEFFA, 0xEFF8,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF7,
+    0x0000, 0x0000,
+    0xEFFA, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0x0000, 0x0000,
+    0xEFFA, 0xEFF9,
+    0xEFFA, 0xEFF9,
 };

@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = *(zi8ZYfinalSpelling + finalIndex * 2);
+  output[(length & 0xff) + 1] = (zi8ZYfinalSpelling + finalIndex * 2)[1];
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "flat character-pair table with row address formed before constant column selection", "sha": "ba821db8fa3f", "build": 0, "insns": [125, 123], "diffs": 99, "first": [[26, ["slwi", "r0, r0, 1"], ["slwi", "r0, r0, 2"]], [27, ["slwi", "r0, r0, 1"], ["lis", "r6, 0"]], [28, ["lis", "r7, 0"], ["addi", "r6, r6, 0"]], [29, ["addi", "r6, r7, 0"], ["lhzx", "r0, r6, r0"]], [30, ["lhzx", "r0, r6, r0"], ["clrlwi", "r6, r0, 0x10"]], [31, ["clrlwi", "r6, r0, 0x10"], ["clrlwi", "r0, r31, 0x18"]], [32, ["clrlwi", "r0, r31, 0x18"], ["slwi", "r0, r0, 1"]], [33, ["slwi", "r0, r0, 1"], ["sthx", "r6, r3, r0"]], [34, ["sthx", "r6, r3, r0"], ["clrlwi", "r0, r30, 0x10"]], [35, ["clrlwi", "r0, r30, 0x10"], ["slwi", "r7, r0, 2"]]]}

### halfword-scaled row address before each constant column load
Source SHA256 prefix 2c4e3666f76f
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = ((const ziWChar*)zi8ZYfinalSpelling + finalIndex * 2)[0];
+  output[(length & 0xff) + 1] = ((const ziWChar*)zi8ZYfinalSpelling + finalIndex * 2)[1];
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "halfword-scaled row address before each constant column load", "sha": "2c4e3666f76f", "build": 0, "insns": [125, 123], "diffs": 99, "first": [[26, ["slwi", "r0, r0, 1"], ["slwi", "r0, r0, 2"]], [27, ["slwi", "r0, r0, 1"], ["lis", "r6, 0"]], [28, ["lis", "r7, 0"], ["addi", "r6, r6, 0"]], [29, ["addi", "r6, r7, 0"], ["lhzx", "r0, r6, r0"]], [30, ["lhzx", "r0, r6, r0"], ["clrlwi", "r6, r0, 0x10"]], [31, ["clrlwi", "r6, r0, 0x10"], ["clrlwi", "r0, r31, 0x18"]], [32, ["clrlwi", "r0, r31, 0x18"], ["slwi", "r0, r0, 1"]], [33, ["slwi", "r0, r0, 1"], ["sthx", "r6, r3, r0"]], [34, ["sthx", "r6, r3, r0"], ["clrlwi", "r0, r30, 0x10"]], [35, ["clrlwi", "r0, r30, 0x10"], ["slwi", "r7, r0, 2"]]]}

## zi8match / Zi8GetPyFinal
Fetched origin; current function source agrees with starting branch: True.

### actual flat Pinyin row storage addressed as serialized rows before component selection
Source SHA256 prefix 48273db62951
```diff
--- start/zi8match.c
+++ trial/zi8match.c
@@ -14,59 +14,59 @@
     0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x0D, 0x0F, 0x04, 0x00, 0x00
 };
-const ziU8 Zi8PinyinFinals[0x36][8] = {
-    {0x0F, 0xFF, 0x00, 0x00, 0x3C, 0x28, 0x00, 0x00},
-    {0x0F, 0x00, 0x00, 0x00, 0x3F, 0x2B, 0x00, 0x00},
-    {0x0F, 0x0E, 0xFF, 0x00, 0x3F, 0x28, 0x00, 0x00},
-    {0x0F, 0x0E, 0x07, 0x00, 0x3F, 0x28, 0x00, 0x00},
-    {0x0F, 0x15, 0x00, 0x00, 0x3F, 0x2A, 0x00, 0x00},
-    {0x09, 0xFF, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00},
-    {0x09, 0x00, 0x00, 0x00, 0x3F, 0x08, 0x00, 0x00},
-    {0x09, 0x01, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x00},
-    {0x09, 0x01, 0x00, 0x00, 0x3F, 0x04, 0x00, 0x00},
-    {0x09, 0x01, 0x0F, 0x00, 0x3F, 0x01, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0xFF, 0x3E, 0x02, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0x00, 0x3F, 0x02, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0x07, 0x3F, 0x03, 0x00, 0x00},
-    {0x09, 0x05, 0x00, 0x00, 0x3F, 0x09, 0x00, 0x00},
-    {0x09, 0x15, 0x00, 0x00, 0x3F, 0x0B, 0x00, 0x00},
-    {0x09, 0x0E, 0xFF, 0x00, 0x3E, 0x0C, 0x00, 0x00},
-    {0x09, 0x0E, 0x00, 0x00, 0x3F, 0x0C, 0x00, 0x00},
-    {0x09, 0x0E, 0x07, 0x00, 0x3F, 0x0D, 0x00, 0x00},
-    {0x09, 0x0F, 0xFF, 0x00, 0x3E, 0x0E, 0x00, 0x00},
-    {0x09, 0x0F, 0x15, 0x00, 0x3F, 0x0E, 0x00, 0x00},
-    {0x09, 0x0F, 0x0E, 0xFF, 0x3F, 0x0F, 0x00, 0x00},
-    {0x09, 0x0F, 0x0E, 0x07, 0x3F, 0x0F, 0x00, 0x00},
-    {0x15, 0xFF, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00},
-    {0x15, 0x00, 0x00, 0x00, 0x3F, 0x18, 0x00, 0x00},
-    {0x15, 0x01, 0xFF, 0x00, 0x38, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x00, 0x00, 0x3F, 0x17, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0xFF, 0x3E, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0x00, 0x3F, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0x07, 0x3F, 0x11, 0x00, 0x00},
-    {0x15, 0x01, 0x09, 0x00, 0x3F, 0x13, 0x00, 0x00},
-    {0x15, 0x0E, 0x00, 0x00, 0x3F, 0x1C, 0x00, 0x00},
-    {0x15, 0x09, 0x00, 0x00, 0x3F, 0x1D, 0x00, 0x00},
-    {0x15, 0x0F, 0x00, 0x00, 0x3F, 0x1E, 0x00, 0x00},
-    {0x15, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
-    {0x01, 0xFF, 0x00, 0x00, 0x38, 0x20, 0x00, 0x00},
-    {0x01, 0x00, 0x00, 0x00, 0x3F, 0x23, 0x00, 0x00},
-    {0x01, 0x0E, 0xFF, 0x00, 0x3E, 0x20, 0x00, 0x00},
-    {0x01, 0x0E, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x00},
-    {0x01, 0x0E, 0x07, 0x00, 0x3F, 0x21, 0x00, 0x00},
-    {0x01, 0x09, 0x00, 0x00, 0x3F, 0x25, 0x00, 0x00},
-    {0x01, 0x0F, 0x00, 0x00, 0x3F, 0x26, 0x00, 0x00},
-    {0x05, 0xFF, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00},
-    {0x05, 0x00, 0x00, 0x00, 0x3F, 0x34, 0x00, 0x00},
-    {0x05, 0x0E, 0xFF, 0x00, 0x3E, 0x30, 0x00, 0x00},
-    {0x05, 0x0E, 0x00, 0x00, 0x3F, 0x30, 0x00, 0x00},
-    {0x05, 0x0E, 0x07, 0x00, 0x3F, 0x31, 0x00, 0x00},
-    {0x05, 0x09, 0x00, 0x00, 0x3F, 0x35, 0x00, 0x00},
-    {0x05, 0x12, 0x00, 0x00, 0x3F, 0x33, 0x00, 0x00},
-    {0x16, 0xFF, 0x00, 0x00, 0x3C, 0x38, 0x00, 0x00},
-    {0x16, 0x00, 0x00, 0x00, 0x3F, 0x38, 0x00, 0x00},
-    {0x16, 0x01, 0xFF, 0x00, 0x3F, 0x39, 0x00, 0x00},
-    {0x16, 0x01, 0x0E, 0x00, 0x3F, 0x39, 0x00, 0x00},
-    {0x16, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
-    {0x16, 0x0E, 0x00, 0x00, 0x3F, 0x3B, 0x00, 0x00}
+const ziU8 Zi8PinyinFinals[0x36 * 8] = {
+    0x0F, 0xFF, 0x00, 0x00, 0x3C, 0x28, 0x00, 0x00,
+    0x0F, 0x00, 0x00, 0x00, 0x3F, 0x2B, 0x00, 0x00,
+    0x0F, 0x0E, 0xFF, 0x00, 0x3F, 0x28, 0x00, 0x00,
+    0x0F, 0x0E, 0x07, 0x00, 0x3F, 0x28, 0x00, 0x00,
+    0x0F, 0x15, 0x00, 0x00, 0x3F, 0x2A, 0x00, 0x00,
+    0x09, 0xFF, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
+    0x09, 0x00, 0x00, 0x00, 0x3F, 0x08, 0x00, 0x00,
+    0x09, 0x01, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x00,
+    0x09, 0x01, 0x00, 0x00, 0x3F, 0x04, 0x00, 0x00,
+    0x09, 0x01, 0x0F, 0x00, 0x3F, 0x01, 0x00, 0x00,
+    0x09, 0x01, 0x0E, 0xFF, 0x3E, 0x02, 0x00, 0x00,
+    0x09, 0x01, 0x0E, 0x00, 0x3F, 0x02, 0x00, 0x00,
+    0x09, 0x01, 0x0E, 0x07, 0x3F, 0x03, 0x00, 0x00,
+    0x09, 0x05, 0x00, 0x00, 0x3F, 0x09, 0x00, 0x00,
+    0x09, 0x15, 0x00, 0x00, 0x3F, 0x0B, 0x00, 0x00,
+    0x09, 0x0E, 0xFF, 0x00, 0x3E, 0x0C, 0x00, 0x00,
+    0x09, 0x0E, 0x00, 0x00, 0x3F, 0x0C, 0x00, 0x00,
+    0x09, 0x0E, 0x07, 0x00, 0x3F, 0x0D, 0x00, 0x00,
+    0x09, 0x0F, 0xFF, 0x00, 0x3E, 0x0E, 0x00, 0x00,
+    0x09, 0x0F, 0x15, 0x00, 0x3F, 0x0E, 0x00, 0x00,
+    0x09, 0x0F, 0x0E, 0xFF, 0x3F, 0x0F, 0x00, 0x00,
+    0x09, 0x0F, 0x0E, 0x07, 0x3F, 0x0F, 0x00, 0x00,
+    0x15, 0xFF, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00,
+    0x15, 0x00, 0x00, 0x00, 0x3F, 0x18, 0x00, 0x00,
+    0x15, 0x01, 0xFF, 0x00, 0x38, 0x10, 0x00, 0x00,
+    0x15, 0x01, 0x00, 0x00, 0x3F, 0x17, 0x00, 0x00,
+    0x15, 0x01, 0x0E, 0xFF, 0x3E, 0x10, 0x00, 0x00,
+    0x15, 0x01, 0x0E, 0x00, 0x3F, 0x10, 0x00, 0x00,
+    0x15, 0x01, 0x0E, 0x07, 0x3F, 0x11, 0x00, 0x00,
+    0x15, 0x01, 0x09, 0x00, 0x3F, 0x13, 0x00, 0x00,
+    0x15, 0x0E, 0x00, 0x00, 0x3F, 0x1C, 0x00, 0x00,
+    0x15, 0x09, 0x00, 0x00, 0x3F, 0x1D, 0x00, 0x00,
+    0x15, 0x0F, 0x00, 0x00, 0x3F, 0x1E, 0x00, 0x00,
+    0x15, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00,
+    0x01, 0xFF, 0x00, 0x00, 0x38, 0x20, 0x00, 0x00,
+    0x01, 0x00, 0x00, 0x00, 0x3F, 0x23, 0x00, 0x00,
+    0x01, 0x0E, 0xFF, 0x00, 0x3E, 0x20, 0x00, 0x00,
+    0x01, 0x0E, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x00,
+    0x01, 0x0E, 0x07, 0x00, 0x3F, 0x21, 0x00, 0x00,
+    0x01, 0x09, 0x00, 0x00, 0x3F, 0x25, 0x00, 0x00,
+    0x01, 0x0F, 0x00, 0x00, 0x3F, 0x26, 0x00, 0x00,
+    0x05, 0xFF, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00,
+    0x05, 0x00, 0x00, 0x00, 0x3F, 0x34, 0x00, 0x00,
+    0x05, 0x0E, 0xFF, 0x00, 0x3E, 0x30, 0x00, 0x00,
+    0x05, 0x0E, 0x00, 0x00, 0x3F, 0x30, 0x00, 0x00,
+    0x05, 0x0E, 0x07, 0x00, 0x3F, 0x31, 0x00, 0x00,
+    0x05, 0x09, 0x00, 0x00, 0x3F, 0x35, 0x00, 0x00,
+    0x05, 0x12, 0x00, 0x00, 0x3F, 0x33, 0x00, 0x00,
+    0x16, 0xFF, 0x00, 0x00, 0x3C, 0x38, 0x00, 0x00,
+    0x16, 0x00, 0x00, 0x00, 0x3F, 0x38, 0x00, 0x00,
+    0x16, 0x01, 0xFF, 0x00, 0x3F, 0x39, 0x00, 0x00,
+    0x16, 0x01, 0x0E, 0x00, 0x3F, 0x39, 0x00, 0x00,
+    0x16, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00,
+    0x16, 0x0E, 0x00, 0x00, 0x3F, 0x3B, 0x00, 0x00
 };
 const ziU8 nodeHeaderTable[0x20] = {
@@ -722,5 +722,5 @@
 scan_row:
     while (index < 4) {
-        if (pinyin[index] != Zi8PinyinFinals[row][index]) {
+        if (pinyin[index] != (Zi8PinyinFinals + row * 8)[index]) {
             break;
         }
@@ -730,6 +730,6 @@
         goto next_row;
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = (Zi8PinyinFinals + row * 8)[4];
+    *final = (Zi8PinyinFinals + row * 8)[5];
     return 1;
 next_row:
```
{"unit": "zi8match", "function": "Zi8GetPyFinal", "trial": "actual flat Pinyin row storage addressed as serialized rows before component selection", "sha": "48273db62951", "build": 0, "insns": [53, 53], "diffs": 8, "first": [[26, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [29, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]], [34, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [35, ["lis", "r7, 0"], ["lis", "r6, 0"]], [36, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [37, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### promoted decoded metadata before narrowing to caller byte fields
Source SHA256 prefix 2255ebe8fc47
```diff
--- start/zi8match.c
+++ trial/zi8match.c
@@ -730,6 +730,6 @@
         goto next_row;
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = (unsigned int)Zi8PinyinFinals[row][4];
+    *final = (unsigned int)Zi8PinyinFinals[row][5];
     return 1;
 next_row:
```
{"unit": "zi8match", "function": "Zi8GetPyFinal", "trial": "promoted decoded metadata before narrowing to caller byte fields", "sha": "2255ebe8fc47", "build": 0, "insns": [53, 53], "diffs": 8, "first": [[26, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [29, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]], [34, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [35, ["lis", "r7, 0"], ["lis", "r6, 0"]], [36, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [37, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### metadata component masks at output boundary
Source SHA256 prefix 35a54843b0a3
```diff
--- start/zi8match.c
+++ trial/zi8match.c
@@ -730,6 +730,6 @@
         goto next_row;
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = Zi8PinyinFinals[row][4] & 0xff;
+    *final = Zi8PinyinFinals[row][5] & 0xff;
     return 1;
 next_row:
```
{"unit": "zi8match", "function": "Zi8GetPyFinal", "trial": "metadata component masks at output boundary", "sha": "35a54843b0a3", "build": 0, "insns": [53, 53], "diffs": 8, "first": [[26, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [29, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]], [34, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [35, ["lis", "r7, 0"], ["lis", "r6, 0"]], [36, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [37, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### byte spelling length and byte function result, retaining native packed-key input
Source SHA256 prefix 86d4476e4725
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -203,10 +203,10 @@
 extern ziU8 _Zi8CheckCandidates(ziGetParam*,ziPtr);

-Zi8UInt Zi8SpellingZY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
+ziU8 Zi8SpellingZY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
 {
   ziU16 initialIndex;
   ziU16 finalIndex;
   ziU16 tone;
-  Zi8UInt length;
+  ziU8 length;

   length = 0;
@@ -217,9 +217,9 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
-  output[(length & 0xff) + 2] = 0;
-  output[(length & 0xff) + 3] = 0;
-  while (output[length & 0xff] != 0) {
+  output[length] = zi8ZYfinalSpelling[finalIndex][0];
+  output[(length) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[(length) + 2] = 0;
+  output[(length) + 3] = 0;
+  while (output[length] != 0) {
     length++;
   }
@@ -227,17 +227,17 @@
     switch (tone) {
     case 1:
-      output[(length++) & 0xff] = 0xeff1;
+      output[length++] = 0xeff1;
       break;
     case 2:
-      output[(length++) & 0xff] = 0xeff2;
+      output[length++] = 0xeff2;
       break;
     case 3:
-      output[(length++) & 0xff] = 0xeff3;
+      output[length++] = 0xeff3;
       break;
     case 4:
-      output[(length++) & 0xff] = 0xeff4;
+      output[length++] = 0xeff4;
       break;
     case 5:
-      output[(length++) & 0xff] = 0xeff5;
+      output[length++] = 0xeff5;
       break;
     }
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "byte spelling length and byte function result, retaining native packed-key input", "sha": "86d4476e4725", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

### tone emission assigns then advances the output cursor
Source SHA256 prefix cdcd0e7cb691
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -227,17 +227,22 @@
     switch (tone) {
     case 1:
-      output[(length++) & 0xff] = 0xeff1;
+      output[length & 0xff] = 0xeff1;
+      length++;
       break;
     case 2:
-      output[(length++) & 0xff] = 0xeff2;
+      output[length & 0xff] = 0xeff2;
+      length++;
       break;
     case 3:
-      output[(length++) & 0xff] = 0xeff3;
+      output[length & 0xff] = 0xeff3;
+      length++;
       break;
     case 4:
-      output[(length++) & 0xff] = 0xeff4;
+      output[length & 0xff] = 0xeff4;
+      length++;
       break;
     case 5:
-      output[(length++) & 0xff] = 0xeff5;
+      output[length & 0xff] = 0xeff5;
+      length++;
       break;
     }
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "tone emission assigns then advances the output cursor", "sha": "cdcd0e7cb691", "build": 0, "insns": [118, 123], "diffs": 56, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]], [64, ["beq", 188], ["beq", 208]], [67, ["beq", 96], ["beq", 104]], [71, ["bge", 52], ["bge", 56]], [72, ["b", 156], ["b", 176]]]}

### explicit no-tone default shares switch exit with the fifth tone
Source SHA256 prefix 0df71bd8b271
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -240,4 +240,5 @@
     case 5:
       output[(length++) & 0xff] = 0xeff5;
+    default:
       break;
     }
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "explicit no-tone default shares switch exit with the fifth tone", "sha": "0df71bd8b271", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}

## zmtkey / Zi8getKeyLayout
Fetched origin; current function source agrees with starting branch: True.

### prefix character accumulation belongs to key traversal continuation
Source SHA256 prefix 53e7d8f7114d
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -95,6 +95,6 @@
         tableCount = 0;
         keyIndex = tableCount;
-        for (; (ziU16)keyIndex < key; keyIndex++) {
-            tableCount += dataAddress[(ziU16)keyIndex];
+        for (; (ziU16)keyIndex < key;
+             tableCount += dataAddress[(ziU16)keyIndex], keyIndex++) {
         }
         if ((charCount = (ziU8)dataAddress[key]) == 0) {
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "prefix character accumulation belongs to key traversal continuation", "sha": "53e7d8f7114d", "build": 0, "insns": [184, 182], "diffs": 73, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [40, ["b", 552], ["b", 544]], [65, ["b", 452], ["b", 444]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]]]}

### serialized prefix scan with an explicit count continuation matching target branch order
Source SHA256 prefix 52cba1e31406
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -95,7 +95,10 @@
         tableCount = 0;
         keyIndex = tableCount;
-        for (; (ziU16)keyIndex < key; keyIndex++) {
-            tableCount += dataAddress[(ziU16)keyIndex];
-        }
+        goto count_key_characters;
+add_key_characters:
+        tableCount += dataAddress[(ziU16)keyIndex];
+        keyIndex++;
+count_key_characters:
+        if ((ziU16)keyIndex < key) goto add_key_characters;
         if ((charCount = (ziU8)dataAddress[key]) == 0) {
             return 0;
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "serialized prefix scan with an explicit count continuation matching target branch order", "sha": "52cba1e31406", "build": 0, "insns": [182, 182], "diffs": 16, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [85, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [90, ["mr", "r27, r3"], ["mr", "r26, r3"]]]}

### accumulate and consume the current key-count entry together
Source SHA256 prefix 8d40d73d114e
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -95,6 +95,6 @@
         tableCount = 0;
         keyIndex = tableCount;
-        for (; (ziU16)keyIndex < key; keyIndex++) {
-            tableCount += dataAddress[(ziU16)keyIndex];
+        for (; (ziU16)keyIndex < key;) {
+            tableCount += dataAddress[(ziU16)keyIndex++];
         }
         if ((charCount = (ziU8)dataAddress[key]) == 0) {
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "accumulate and consume the current key-count entry together", "sha": "8d40d73d114e", "build": 0, "insns": [183, 182], "diffs": 74, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [40, ["b", 548], ["b", 544]], [65, ["b", 448], ["b", 444]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]]]}

### prefix scan in a pre-tested while with count update adjacent to the advance
Source SHA256 prefix 4df67825aa97
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -95,6 +95,7 @@
         tableCount = 0;
         keyIndex = tableCount;
-        for (; (ziU16)keyIndex < key; keyIndex++) {
+        while ((ziU16)keyIndex < key) {
             tableCount += dataAddress[(ziU16)keyIndex];
+            keyIndex++;
         }
         if ((charCount = (ziU8)dataAddress[key]) == 0) {
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "prefix scan in a pre-tested while with count update adjacent to the advance", "sha": "4df67825aa97", "build": 0, "insns": [182, 182], "diffs": 16, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [85, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [90, ["mr", "r27, r3"], ["mr", "r26, r3"]]]}

## zconvert / Zi8ConvertUC2Key
Fetched origin; current function source agrees with starting branch: True.

### conversion API takes its actual workspace structure within this translation unit
Source SHA256 prefix 244bd266e7e0
```diff
--- start/zconvert.c
+++ trial/zconvert.c
@@ -1,2 +1,5 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
 #include <zi8clib/zconvert.h>
 #include <zi8clib/zierror.h>
```
{"unit": "zconvert", "function": "Zi8ConvertUC2Key", "trial": "conversion API takes its actual workspace structure within this translation unit", "sha": "244bd266e7e0", "build": 0, "insns": [207, 207], "diffs": 18, "first": [[7, ["mr", "r27, r5"], ["mr", "r28, r5"]], [8, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["mr", "r4, r27"], ["mr", "r4, r28"]], [20, ["add", "r3, r27, r0"], ["add", "r3, r28, r0"]], [26, ["mr", "r5, r27"], ["mr", "r5, r28"]], [32, ["mr", "r5, r27"], ["mr", "r5, r28"]], [40, ["mr", "r5, r27"], ["mr", "r5, r28"]], [48, ["mr", "r4, r27"], ["mr", "r4, r28"]], [92, ["clrlwi", "r28, r0, 0x10"], ["clrlwi", "r27, r0, 0x10"]], [99, ["clrlwi", "r4, r28, 0x10"], ["clrlwi", "r4, r27, 0x10"]]]}

### typed conversion workspace formal accesses user key tables directly
Source SHA256 prefix 2b33cdf246e9
```diff
--- start/zconvert.c
+++ trial/zconvert.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zconvert.h>
 #include <zi8clib/zierror.h>
```
{"unit": "zconvert", "function": "Zi8ConvertUC2Key", "trial": "typed conversion workspace formal accesses user key tables directly", "sha": "2b33cdf246e9", "build": 0, "insns": [207, 207], "diffs": 0, "first": []}
EXACT CHECK {"name": "Zi8ConvertUC2Key", "size": "828", "fuzzy_match_percent": 100.0, "metadata": {}, "address": "1292"}

### built-in range traversal advances only when the character does not select a range
Source SHA256 prefix 6f30f0114c29
```diff
--- start/zconvert.c
+++ trial/zconvert.c
@@ -167,5 +167,6 @@
         }
         count = Zi8CvrtTables.keys.count;
-        for (index = 0; index < count; index++) {
+        index = 0;
+        while (index < count) {
             if (character >= ranges[index].first && character <= ranges[index].last) {
                 if (ranges[index].first == ranges[index].last) {
@@ -177,4 +178,5 @@
                 break;
             }
+            index++;
         }
     }
```
{"unit": "zconvert", "function": "Zi8ConvertUC2Key", "trial": "built-in range traversal advances only when the character does not select a range", "sha": "6f30f0114c29", "build": 0, "insns": [207, 207], "diffs": 18, "first": [[7, ["mr", "r27, r5"], ["mr", "r28, r5"]], [8, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["mr", "r4, r27"], ["mr", "r4, r28"]], [20, ["add", "r3, r27, r0"], ["add", "r3, r28, r0"]], [26, ["mr", "r5, r27"], ["mr", "r5, r28"]], [32, ["mr", "r5, r27"], ["mr", "r5, r28"]], [40, ["mr", "r5, r27"], ["mr", "r5, r28"]], [48, ["mr", "r4, r27"], ["mr", "r4, r28"]], [92, ["clrlwi", "r28, r0, 0x10"], ["clrlwi", "r27, r0, 0x10"]], [99, ["clrlwi", "r4, r28, 0x10"], ["clrlwi", "r4, r27, 0x10"]]]}

## Exact candidate: conversion workspace type
The typed workspace formal alone retained 18 differences. Removing the redundant ZI_WORK cast as well changes register-weight accounting and gives Zi8ConvertUC2Key 207/207 instructions with zero differences and exact-name objdiff 100.0. The entire zconvert unit is 4/4, code 2208/2208, data 112/112, all other functions preserved. The local macro configuration exposes the real workspace structure for this C translation unit; no compiler option, register keyword, assembly, dummy object or shared-header change. Full clean gate started before committing.

## First full clean gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 2208/2208 data 112/112 functions 4/4 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 4/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
regressions vs baseline: 0
global matched_code_percent: 92.38495 -> 92.41260
global fuzzy_match_percent: 99.73445 -> 99.73458
global complete_code_percent: 74.91312 -> 74.91312
global matched_data_percent: 99.78196 -> 99.78196
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Fresh post-gate ctxdiff: Zi8ConvertUC2Key 207/207, diffs 0. The original local macro API is intentionally only made typed in this source file; no other translation unit sees the type change.

## zoemdata / Zi8MatchOEMdata
Fetched origin; current function source agrees with starting branch: True.

### native workspace formal and direct member access, following the exact zconvert result
Source SHA256 prefix 22d382a5404f
```diff
--- start/zoemdata.c
+++ trial/zoemdata.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <stddef.h>
 #include <zi8clib/zitypes.h>
```
{"unit": "zoemdata", "function": "Zi8MatchOEMdata", "trial": "native workspace formal and direct member access, following the exact zconvert result", "sha": "22d382a5404f", "build": 0, "insns": [192, 192], "diffs": 62, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [6, ["mr", "r26, r4"], ["mr", "r27, r4"]], [9, ["mr", "r23, r7"], ["mr", "r24, r7"]], [12, ["mr", "r30, r10"], ["mr", "r29, r10"]], [13, ["li", "r24, 0"], ["li", "r23, 0"]], [18, ["stw", "r0, 0x328(r30)"], ["stw", "r0, 0x328(r29)"]], [19, ["lwz", "r28, 0x328(r30)"], ["lwz", "r26, 0x328(r29)"]], [20, ["lhz", "r0, 0x324(r30)"], ["lhz", "r0, 0x324(r29)"]], [21, ["cmpw", "r28, r0"], ["cmpw", "r26, r0"]], [23, ["lwz", "r0, 0x320(r30)"], ["lwz", "r0, 0x320(r29)"]]]}

## zmtkey / Zi8getKeyLayout
Fetched origin; current function source agrees with starting branch: True.

### native workspace formal and direct member access, following the exact zconvert result
Source SHA256 prefix 58dd14fd0246
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zconvert.h>
 #include <zi8clib/zierror.h>
@@ -5,9 +10,9 @@
 typedef struct ziUserKeyMap { ziWChar* upper[32]; ziWChar* lower[32]; } ziUserKeyMap;

-ziU16 Zi8GetTableCount(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
-ziU32 Zi8GetTableAddress(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
-ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data);
-
-ziBool Zi8MapKeyCode(ziWChar character, ziWChar* output, ziPtr __zi8_work_data) {
+ziU16 Zi8GetTableCount(ziU8 language, ziU8 tableIndex, struct __zi8_work_data_s* __zi8_work_data);
+ziU32 Zi8GetTableAddress(ziU8 language, ziU8 tableIndex, struct __zi8_work_data_s* __zi8_work_data);
+ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, struct __zi8_work_data_s* __zi8_work_data);
+
+ziBool Zi8MapKeyCode(ziWChar character, ziWChar* output, struct __zi8_work_data_s* __zi8_work_data) {
     if (character == 0xeffa) {
         *output = 0;
@@ -22,5 +27,5 @@
 }

-static ziU8 ziNumKeysWithChars(ziU8 language, ziPtr __zi8_work_data) {
+static ziU8 ziNumKeysWithChars(ziU8 language, struct __zi8_work_data_s* __zi8_work_data) {
     ziU16 tableCount;
     ziU8* table;
@@ -44,5 +49,5 @@
 }

-ziBool Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data) {
+ziBool Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, struct __zi8_work_data_s* __zi8_work_data) {
     ziU16 tableCount;
     ziU8 numKeys;
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "native workspace formal and direct member access, following the exact zconvert result", "sha": "58dd14fd0246", "build": 0, "insns": [182, 182], "diffs": 16, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [85, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [90, ["mr", "r27, r3"], ["mr", "r26, r3"]]]}

## zi8uwd / Zi8_81480224
Fetched origin; current function source agrees with starting branch: True.

### native workspace formal and direct member access, following the exact zconvert result
Source SHA256 prefix 2b69c5e3301d
```diff
--- start/zi8uwd.c
+++ trial/zi8uwd.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zitypes.h>
 #include <zi8clib/zierror.h>
@@ -69,5 +74,5 @@
     return 1;
 }
-ziUserWord* Zi8_814803F4(ziPtr __zi8_work_data) {
+ziUserWord* Zi8_814803F4(struct __zi8_work_data_s* __zi8_work_data) {
     ziUserWord* word;
     if (ZI_WORK->uwdCount != 0) {
@@ -81,5 +86,5 @@
     return 0;
 }
-void Zi8_8148047C(ziPtr __zi8_work_data) {
+void Zi8_8148047C(struct __zi8_work_data_s* __zi8_work_data) {
     Zi8Memset(ZI_WORK->uwdNodes, 0, sizeof(ZI_WORK->uwdNodes));
     ZI_WORK->uwdCount = 0;
```
{"unit": "zi8uwd", "function": "Zi8_81480224", "trial": "native workspace formal and direct member access, following the exact zconvert result", "sha": "2b69c5e3301d", "build": 0, "insns": [116, 116], "diffs": 9, "first": [[5, ["mr", "r26, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r26, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r25, 2(r26)"], ["lbz", "r25, 2(r28)"]], [46, ["lwz", "r28, 4(r30)"], ["lwz", "r26, 4(r30)"]], [54, ["blt", 144], ["bgt", 144]], [55, ["lbz", "r0, 2(r28)"], ["lbz", "r0, 2(r26)"]], [63, ["add", "r3, r28, r0"], ["add", "r3, r0, r26"]], [67, ["add", "r3, r26, r0"], ["add", "r3, r0, r28"]], [104, ["stw", "r26, 4(r29)"], ["stw", "r28, 4(r29)"]]]}

## zi8getc2 / Zi8GetDataSignature
Fetched origin; current function source agrees with starting branch: True.

### native workspace formal and direct member access, following the exact zconvert result
Source SHA256 prefix 42b4f9f8252a
```diff
--- start/zi8getc2.c
+++ trial/zi8getc2.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zitypes.h>
 #include <zi8clib/zierror.h>
@@ -618,5 +623,5 @@
 }

-void Zi8InitDupWordBuf(ziPtr __zi8_work_data) {
+void Zi8InitDupWordBuf(struct __zi8_work_data_s* __zi8_work_data) {
     ZI_WORK->unk_0x539 = 0;
 }
```
```text
[1/1] MWCC build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8getc2.o
FAILED: [code=2] build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8getc2.o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -inline off -opt off -str readonly -sdata 0 -fp_contract off -Cpp_exceptions on -lang=c -MMD -c libs/RVLMiddleware/eZiText/src/clib/zi8getc2.c -o build/43U/src/libs/RVLMiddleware/eZiText/src/clib && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8getc2.d build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8getc2.d
### mwcceppc.exe Compiler:
#    File: libs\RVLMiddleware\eZiText\src\clib\zi8getc2.c
# -------------------------------------------------------
#     309: GetParam* parameters, ZiCandidateOptions* options ZI_NEED_WORK) {
#   Error:                                                                 ^
#   (10563) identifier 'Zi8GetCandidatesOrCount(struct _ziGetParam *, struct
#   *, void *)' redeclared as 'unsigned long (struct _ziGetParam *, struct  *,
#   struct __zi8_work_data_s *)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
```

## zkokeyp / Zi8_8148302C
Fetched origin; current function source agrees with starting branch: True.

### native workspace formal and direct member access, following the exact zconvert result
Source SHA256 prefix db567bad7117
```diff
--- start/zkokeyp.c
+++ trial/zkokeyp.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zierror.h>

```
{"unit": "zkokeyp", "function": "Zi8_8148302C", "trial": "native workspace formal and direct member access, following the exact zconvert result", "sha": "db567bad7117", "build": 0, "insns": [59, 59], "diffs": 6, "first": [[7, ["mr", "r27, r5"], ["mr", "r29, r5"]], [12, ["mr", "r5, r27"], ["mr", "r5, r29"]], [32, ["clrlwi", "r29, r0, 0x10"], ["clrlwi", "r27, r0, 0x10"]], [34, ["cmplw", "r29, r0"], ["cmplw", "r27, r0"]], [38, ["mr", "r4, r27"], ["mr", "r4, r29"]], [49, ["mr", "r4, r27"], ["mr", "r4, r29"]]]}
Native workspace full-unit audit {"unit": "zoemdata", "measures": {"fuzzy_match_percent": 98.58607, "total_code": "976", "matched_code": "208", "matched_code_percent": 21.311476, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 3, "matched_functions": 2, "matched_functions_percent": 66.66667, "total_units": 1}, "functions": [["Zi8AttachOEMdata", 100.0], ["Zi8DetachOEMdata", 100.0], ["Zi8MatchOEMdata", 98.203125]]}
Native workspace full-unit audit {"unit": "zmtkey", "measures": {"fuzzy_match_percent": 99.67509, "total_code": "2216", "matched_code": "324", "matched_code_percent": 14.620939, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 2, "matched_functions_percent": 50.0, "total_units": 1}, "functions": [["Zi8MapKeyCode", 100.0], ["ziNumKeysWithChars", 100.0], ["Zi8getKeyLayout", 99.53297], ["Zi8ChangeCharCase", 99.67354]]}
Native workspace full-unit audit {"unit": "zi8uwd", "measures": {"fuzzy_match_percent": 99.91717, "total_code": "2656", "matched_code": "2192", "matched_code_percent": 82.53012, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}, "functions": [["Zi8_81480224", 99.52586], ["Zi8_814803F4", 100.0], ["Zi8_8148047C", 100.0], ["Zi8MatchUWDdata", 100.0]]}
Native workspace full-unit audit {"unit": "zkokeyp", "measures": {"fuzzy_match_percent": 98.746155, "total_code": "5200", "matched_code": "332", "matched_code_percent": 6.3846154, "total_data": "180", "matched_data": "96", "matched_data_percent": 53.333336, "total_functions": 7, "matched_functions": 1, "matched_functions_percent": 14.285715, "total_units": 1}, "functions": [["Zi8_8148302C", 99.49152], ["Zi8_81483118", 100.0], ["Zi8_81483264", 98.902435], ["Zi8_81483308", 99.13793], ["Zi8_814833F0", 99.04256], ["Zi8_814834AC", 99.3586], ["Zi8GetKOcandidates", 98.146484]]}

## zi8getc2 / Zi8IsDupWChar
Fetched origin; current function source agrees with starting branch: True.

### consistent typed workspace prototypes and direct fields for duplicate-character and signature helpers
Source SHA256 prefix 4d9ba2c443bf
```diff
--- start/zi8getc2.c
+++ trial/zi8getc2.c
@@ -1,2 +1,7 @@
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zitypes.h>
 #include <zi8clib/zierror.h>
@@ -22,12 +27,12 @@
 const ziFuzzyZYPairs Zi8ZYdefaultFuzzyPairs = {0};

-ziU8 Zi8GetFormatVersion(ziU8 language, ziPtr work);
-ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
-ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
-ziU16 Zi8GetVersion(ziPtr work);
-ziU16 Zi8GetOEMID(ziPtr work);
-ziU16 Zi8GetBuildID(ziPtr work);
+ziU8 Zi8GetFormatVersion(ziU8 language, struct __zi8_work_data_s* work);
+ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, struct __zi8_work_data_s* work);
+ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, struct __zi8_work_data_s* work);
+ziU16 Zi8GetVersion(struct __zi8_work_data_s* work);
+ziU16 Zi8GetOEMID(struct __zi8_work_data_s* work);
+ziU16 Zi8GetBuildID(struct __zi8_work_data_s* work);
 void Zi8Memcpy(ziU8* destination, ziU8* source, ziS32 count);
-ziU32 Zi8GetCandidatesOrCount(ziGetParam* parameters, ZiCandidateOptions* options, ziPtr work);
+ziU32 Zi8GetCandidatesOrCount(ziGetParam* parameters, ZiCandidateOptions* options, struct __zi8_work_data_s* work);

 ziBool Zi8ZHsetPYfuzzyPairs(ziFuzzyPYPairs pairs ZI_NEED_WORK) {
@@ -64,5 +69,5 @@
 }

-static ziU16 Zi8GetDataSignature(ziU8* destination, ziU16 capacity, ziU8 language, ziPtr work) {
+static ziU16 Zi8GetDataSignature(ziU8* destination, ziU16 capacity, ziU8 language, struct __zi8_work_data_s* work) {
     ziU8* signature;
     ziU16 length;
@@ -88,5 +93,5 @@
 }

-static ziU16 Zi8GetEngineSignature(ziU8* destination, ziPtr work) {
+static ziU16 Zi8GetEngineSignature(ziU8* destination, struct __zi8_work_data_s* work) {
     ziU16 index = 0;
     struct { ziU16 minor; } version;
@@ -290,15 +295,15 @@
     return Zi8GetCandidatesOrCount(parameters, &options, ZI_WORK);
 }
-ziU8 Zi8LangSupported(ziU8 language, ziPtr work);
-ziBool Zi8IsCharacter(ziWChar character, ziPtr work);
-ziU8 Zi8GetCharInfo(ziWChar character, ziWChar* output, ziU8 capacity, ziU8 type, ziPtr work);
-ziU32 Zi8GetKOcandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8GetKoreanCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8Punctuation(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8GetChineseCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8Get1KeyPressCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8Get1KeyPressSpelling(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8GetSyllablesCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
-ziU32 Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
+ziU8 Zi8LangSupported(ziU8 language, struct __zi8_work_data_s* work);
+ziBool Zi8IsCharacter(ziWChar character, struct __zi8_work_data_s* work);
+ziU8 Zi8GetCharInfo(ziWChar character, ziWChar* output, ziU8 capacity, ziU8 type, struct __zi8_work_data_s* work);
+ziU32 Zi8GetKOcandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8GetKoreanCandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8Punctuation(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8GetChineseCandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8Get1KeyPressCandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8Get1KeyPressSpelling(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8GetSyllablesCandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);
+ziU32 Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr options, struct __zi8_work_data_s* work);

 ziU32 Zi8GetCandidatesOrCount(ziGetParam* parameters, ZiCandidateOptions* options ZI_NEED_WORK) {
@@ -618,5 +623,5 @@
 }

-void Zi8InitDupWordBuf(ziPtr __zi8_work_data) {
+void Zi8InitDupWordBuf(struct __zi8_work_data_s* __zi8_work_data) {
     ZI_WORK->unk_0x539 = 0;
 }
```
{"unit": "zi8getc2", "function": "Zi8IsDupWChar", "trial": "consistent typed workspace prototypes and direct fields for duplicate-character and signature helpers", "sha": "4d9ba2c443bf", "build": 0, "insns": [63, 63], "diffs": 8, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["sth", "r27, 2(r31)"], ["sth", "r28, 2(r31)"]], [25, ["clrlwi", "r3, r27, 0x10"], ["clrlwi", "r3, r28, 0x10"]], [30, ["li", "r28, 1"], ["li", "r27, 1"]], [41, ["sthx", "r27, r31, r0"], ["sthx", "r28, r31, r0"]], [49, ["sth", "r27, 2(r31)"], ["sth", "r28, 2(r31)"]], [56, ["mr", "r3, r28"], ["mr", "r3, r27"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.95064, "total_code": "6888", "matched_code": "6360", "matched_code_percent": 92.334496, "total_data": "332", "matched_data": "332", "matched_data_percent": 100.0, "total_functions": 17, "matched_functions": 15, "matched_functions_percent": 88.2353, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8GetDataSignature", 99.347824], ["Zi8IsDupWChar", 99.36508]]}

### declare actual Zhuyin final records and read named members without a cast over array storage
Source SHA256 prefix 515c538078a7
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -59,5 +59,7 @@
 };

-const ziWChar zi8ZYfinalSpelling[64][2] = {
+typedef struct { ziWChar first; ziWChar second; } ZiZhuyinFinal;
+
+const ZiZhuyinFinal zi8ZYfinalSpelling[64] = {
     { 0x0000, 0x0000 },
     { 0xEFF7, 0x0000 },
@@ -217,6 +219,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex].first;
+  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex].second;
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "declare actual Zhuyin final records and read named members without a cast over array storage", "sha": "515c538078a7", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 98.23523, "total_code": "21460", "matched_code": "3952", "matched_code_percent": 18.415657, "total_data": "1388", "matched_data": "1280", "matched_data_percent": 92.21902, "total_functions": 9, "matched_functions": 5, "matched_functions_percent": 55.555557, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8SpellingZY", 99.756096], ["Zi8SpellingPY", 99.36306], ["Zi8Get1KeyPressSpelling", 99.555885], ["Zi8Get1KeyPressCandidates", 96.41927]]}

### declare actual Pinyin records instead of reinterpreting an array at the output fields
Source SHA256 prefix 3928bba4bfe6
```diff
--- start/zi8match.c
+++ trial/zi8match.c
@@ -14,59 +14,61 @@
     0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x0D, 0x0F, 0x04, 0x00, 0x00
 };
-const ziU8 Zi8PinyinFinals[0x36][8] = {
-    {0x0F, 0xFF, 0x00, 0x00, 0x3C, 0x28, 0x00, 0x00},
-    {0x0F, 0x00, 0x00, 0x00, 0x3F, 0x2B, 0x00, 0x00},
-    {0x0F, 0x0E, 0xFF, 0x00, 0x3F, 0x28, 0x00, 0x00},
-    {0x0F, 0x0E, 0x07, 0x00, 0x3F, 0x28, 0x00, 0x00},
-    {0x0F, 0x15, 0x00, 0x00, 0x3F, 0x2A, 0x00, 0x00},
-    {0x09, 0xFF, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00},
-    {0x09, 0x00, 0x00, 0x00, 0x3F, 0x08, 0x00, 0x00},
-    {0x09, 0x01, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x00},
-    {0x09, 0x01, 0x00, 0x00, 0x3F, 0x04, 0x00, 0x00},
-    {0x09, 0x01, 0x0F, 0x00, 0x3F, 0x01, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0xFF, 0x3E, 0x02, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0x00, 0x3F, 0x02, 0x00, 0x00},
-    {0x09, 0x01, 0x0E, 0x07, 0x3F, 0x03, 0x00, 0x00},
-    {0x09, 0x05, 0x00, 0x00, 0x3F, 0x09, 0x00, 0x00},
-    {0x09, 0x15, 0x00, 0x00, 0x3F, 0x0B, 0x00, 0x00},
-    {0x09, 0x0E, 0xFF, 0x00, 0x3E, 0x0C, 0x00, 0x00},
-    {0x09, 0x0E, 0x00, 0x00, 0x3F, 0x0C, 0x00, 0x00},
-    {0x09, 0x0E, 0x07, 0x00, 0x3F, 0x0D, 0x00, 0x00},
-    {0x09, 0x0F, 0xFF, 0x00, 0x3E, 0x0E, 0x00, 0x00},
-    {0x09, 0x0F, 0x15, 0x00, 0x3F, 0x0E, 0x00, 0x00},
-    {0x09, 0x0F, 0x0E, 0xFF, 0x3F, 0x0F, 0x00, 0x00},
-    {0x09, 0x0F, 0x0E, 0x07, 0x3F, 0x0F, 0x00, 0x00},
-    {0x15, 0xFF, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00},
-    {0x15, 0x00, 0x00, 0x00, 0x3F, 0x18, 0x00, 0x00},
-    {0x15, 0x01, 0xFF, 0x00, 0x38, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x00, 0x00, 0x3F, 0x17, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0xFF, 0x3E, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0x00, 0x3F, 0x10, 0x00, 0x00},
-    {0x15, 0x01, 0x0E, 0x07, 0x3F, 0x11, 0x00, 0x00},
-    {0x15, 0x01, 0x09, 0x00, 0x3F, 0x13, 0x00, 0x00},
-    {0x15, 0x0E, 0x00, 0x00, 0x3F, 0x1C, 0x00, 0x00},
-    {0x15, 0x09, 0x00, 0x00, 0x3F, 0x1D, 0x00, 0x00},
-    {0x15, 0x0F, 0x00, 0x00, 0x3F, 0x1E, 0x00, 0x00},
-    {0x15, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
-    {0x01, 0xFF, 0x00, 0x00, 0x38, 0x20, 0x00, 0x00},
-    {0x01, 0x00, 0x00, 0x00, 0x3F, 0x23, 0x00, 0x00},
-    {0x01, 0x0E, 0xFF, 0x00, 0x3E, 0x20, 0x00, 0x00},
-    {0x01, 0x0E, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x00},
-    {0x01, 0x0E, 0x07, 0x00, 0x3F, 0x21, 0x00, 0x00},
-    {0x01, 0x09, 0x00, 0x00, 0x3F, 0x25, 0x00, 0x00},
-    {0x01, 0x0F, 0x00, 0x00, 0x3F, 0x26, 0x00, 0x00},
-    {0x05, 0xFF, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00},
-    {0x05, 0x00, 0x00, 0x00, 0x3F, 0x34, 0x00, 0x00},
-    {0x05, 0x0E, 0xFF, 0x00, 0x3E, 0x30, 0x00, 0x00},
-    {0x05, 0x0E, 0x00, 0x00, 0x3F, 0x30, 0x00, 0x00},
-    {0x05, 0x0E, 0x07, 0x00, 0x3F, 0x31, 0x00, 0x00},
-    {0x05, 0x09, 0x00, 0x00, 0x3F, 0x35, 0x00, 0x00},
-    {0x05, 0x12, 0x00, 0x00, 0x3F, 0x33, 0x00, 0x00},
-    {0x16, 0xFF, 0x00, 0x00, 0x3C, 0x38, 0x00, 0x00},
-    {0x16, 0x00, 0x00, 0x00, 0x3F, 0x38, 0x00, 0x00},
-    {0x16, 0x01, 0xFF, 0x00, 0x3F, 0x39, 0x00, 0x00},
-    {0x16, 0x01, 0x0E, 0x00, 0x3F, 0x39, 0x00, 0x00},
-    {0x16, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
-    {0x16, 0x0E, 0x00, 0x00, 0x3F, 0x3B, 0x00, 0x00}
+typedef struct { ziU8 spelling[4]; ziU8 initial; ziU8 final; ziU8 flags[2]; } ZiPinyinFinal;
+
+const ZiPinyinFinal Zi8PinyinFinals[0x36] = {
+    {{0x0F, 0xFF, 0x00, 0x00}, 0x3C, 0x28, {0x00, 0x00}},
+    {{0x0F, 0x00, 0x00, 0x00}, 0x3F, 0x2B, {0x00, 0x00}},
+    {{0x0F, 0x0E, 0xFF, 0x00}, 0x3F, 0x28, {0x00, 0x00}},
+    {{0x0F, 0x0E, 0x07, 0x00}, 0x3F, 0x28, {0x00, 0x00}},
+    {{0x0F, 0x15, 0x00, 0x00}, 0x3F, 0x2A, {0x00, 0x00}},
+    {{0x09, 0xFF, 0x00, 0x00}, 0x30, 0x00, {0x00, 0x00}},
+    {{0x09, 0x00, 0x00, 0x00}, 0x3F, 0x08, {0x00, 0x00}},
+    {{0x09, 0x01, 0xFF, 0x00}, 0x38, 0x00, {0x00, 0x00}},
+    {{0x09, 0x01, 0x00, 0x00}, 0x3F, 0x04, {0x00, 0x00}},
+    {{0x09, 0x01, 0x0F, 0x00}, 0x3F, 0x01, {0x00, 0x00}},
+    {{0x09, 0x01, 0x0E, 0xFF}, 0x3E, 0x02, {0x00, 0x00}},
+    {{0x09, 0x01, 0x0E, 0x00}, 0x3F, 0x02, {0x00, 0x00}},
+    {{0x09, 0x01, 0x0E, 0x07}, 0x3F, 0x03, {0x00, 0x00}},
+    {{0x09, 0x05, 0x00, 0x00}, 0x3F, 0x09, {0x00, 0x00}},
+    {{0x09, 0x15, 0x00, 0x00}, 0x3F, 0x0B, {0x00, 0x00}},
+    {{0x09, 0x0E, 0xFF, 0x00}, 0x3E, 0x0C, {0x00, 0x00}},
+    {{0x09, 0x0E, 0x00, 0x00}, 0x3F, 0x0C, {0x00, 0x00}},
+    {{0x09, 0x0E, 0x07, 0x00}, 0x3F, 0x0D, {0x00, 0x00}},
+    {{0x09, 0x0F, 0xFF, 0x00}, 0x3E, 0x0E, {0x00, 0x00}},
+    {{0x09, 0x0F, 0x15, 0x00}, 0x3F, 0x0E, {0x00, 0x00}},
+    {{0x09, 0x0F, 0x0E, 0xFF}, 0x3F, 0x0F, {0x00, 0x00}},
+    {{0x09, 0x0F, 0x0E, 0x07}, 0x3F, 0x0F, {0x00, 0x00}},
+    {{0x15, 0xFF, 0x00, 0x00}, 0x30, 0x10, {0x00, 0x00}},
+    {{0x15, 0x00, 0x00, 0x00}, 0x3F, 0x18, {0x00, 0x00}},
+    {{0x15, 0x01, 0xFF, 0x00}, 0x38, 0x10, {0x00, 0x00}},
+    {{0x15, 0x01, 0x00, 0x00}, 0x3F, 0x17, {0x00, 0x00}},
+    {{0x15, 0x01, 0x0E, 0xFF}, 0x3E, 0x10, {0x00, 0x00}},
+    {{0x15, 0x01, 0x0E, 0x00}, 0x3F, 0x10, {0x00, 0x00}},
+    {{0x15, 0x01, 0x0E, 0x07}, 0x3F, 0x11, {0x00, 0x00}},
+    {{0x15, 0x01, 0x09, 0x00}, 0x3F, 0x13, {0x00, 0x00}},
+    {{0x15, 0x0E, 0x00, 0x00}, 0x3F, 0x1C, {0x00, 0x00}},
+    {{0x15, 0x09, 0x00, 0x00}, 0x3F, 0x1D, {0x00, 0x00}},
+    {{0x15, 0x0F, 0x00, 0x00}, 0x3F, 0x1E, {0x00, 0x00}},
+    {{0x15, 0x05, 0x00, 0x00}, 0x3F, 0x1F, {0x00, 0x00}},
+    {{0x01, 0xFF, 0x00, 0x00}, 0x38, 0x20, {0x00, 0x00}},
+    {{0x01, 0x00, 0x00, 0x00}, 0x3F, 0x23, {0x00, 0x00}},
+    {{0x01, 0x0E, 0xFF, 0x00}, 0x3E, 0x20, {0x00, 0x00}},
+    {{0x01, 0x0E, 0x00, 0x00}, 0x3F, 0x20, {0x00, 0x00}},
+    {{0x01, 0x0E, 0x07, 0x00}, 0x3F, 0x21, {0x00, 0x00}},
+    {{0x01, 0x09, 0x00, 0x00}, 0x3F, 0x25, {0x00, 0x00}},
+    {{0x01, 0x0F, 0x00, 0x00}, 0x3F, 0x26, {0x00, 0x00}},
+    {{0x05, 0xFF, 0x00, 0x00}, 0x38, 0x30, {0x00, 0x00}},
+    {{0x05, 0x00, 0x00, 0x00}, 0x3F, 0x34, {0x00, 0x00}},
+    {{0x05, 0x0E, 0xFF, 0x00}, 0x3E, 0x30, {0x00, 0x00}},
+    {{0x05, 0x0E, 0x00, 0x00}, 0x3F, 0x30, {0x00, 0x00}},
+    {{0x05, 0x0E, 0x07, 0x00}, 0x3F, 0x31, {0x00, 0x00}},
+    {{0x05, 0x09, 0x00, 0x00}, 0x3F, 0x35, {0x00, 0x00}},
+    {{0x05, 0x12, 0x00, 0x00}, 0x3F, 0x33, {0x00, 0x00}},
+    {{0x16, 0xFF, 0x00, 0x00}, 0x3C, 0x38, {0x00, 0x00}},
+    {{0x16, 0x00, 0x00, 0x00}, 0x3F, 0x38, {0x00, 0x00}},
+    {{0x16, 0x01, 0xFF, 0x00}, 0x3F, 0x39, {0x00, 0x00}},
+    {{0x16, 0x01, 0x0E, 0x00}, 0x3F, 0x39, {0x00, 0x00}},
+    {{0x16, 0x05, 0x00, 0x00}, 0x3F, 0x1F, {0x00, 0x00}},
+    {{0x16, 0x0E, 0x00, 0x00}, 0x3F, 0x3B, {0x00, 0x00}}
 };
 const ziU8 nodeHeaderTable[0x20] = {
@@ -722,5 +724,5 @@
 scan_row:
     while (index < 4) {
-        if (pinyin[index] != Zi8PinyinFinals[row][index]) {
+        if (pinyin[index] != Zi8PinyinFinals[row].spelling[index]) {
             break;
         }
@@ -730,6 +732,6 @@
         goto next_row;
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = Zi8PinyinFinals[row].initial;
+    *final = Zi8PinyinFinals[row].final;
     return 1;
 next_row:
```
{"unit": "zi8match", "function": "Zi8GetPyFinal", "trial": "declare actual Pinyin records instead of reinterpreting an array at the output fields", "sha": "3928bba4bfe6", "build": 0, "insns": [53, 53], "diffs": 8, "first": [[26, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [29, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]], [34, ["slwi", "r6, r0, 3"], ["slwi", "r7, r0, 3"]], [35, ["lis", "r7, 0"], ["lis", "r6, 0"]], [36, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [37, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.98062, "total_code": "8256", "matched_code": "8044", "matched_code_percent": 97.432175, "total_data": "728", "matched_data": "728", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8GetPyFinal", 99.245285]]}

## zidawg1 / ZiDAWGgetCHARattribute
Fetched origin; current function source agrees with starting branch: True.

### remove redundant byte-pointer casts from typed DAWG character tables
Source SHA256 prefix dbc755efcbd1
```diff
--- start/zidawg1.c
+++ trial/zidawg1.c
@@ -150,7 +150,7 @@

     attribute = key << 24;
-    attribute |= ((ziU8*)context->p0C)[key] << 16;
-    attribute |= (((ziU32)((ziU8*)context->p08)[key * 2] & 0xFFFF) << 8) +
-                 ((ziU8*)context->p08 + key * 2)[1];
+    attribute |= context->p0C[key] << 16;
+    attribute |= (((ziU32)context->p08[key * 2] & 0xFFFF) << 8) +
+                 (context->p08 + key * 2)[1];
     Zi8LogError(0x64, __zi8_work_data);
     return attribute;
```
{"unit": "zidawg1", "function": "ZiDAWGgetCHARattribute", "trial": "remove redundant byte-pointer casts from typed DAWG character tables", "sha": "dbc755efcbd1", "build": 0, "insns": [60, 60], "diffs": 12, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [14, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [18, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [19, ["clrlwi", "r3, r31, 0x18"], ["clrlwi", "r3, r30, 0x18"]], [20, ["lhz", "r0, 4(r30)"], ["lhz", "r0, 4(r31)"]], [29, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]], [31, ["lwz", "r3, 0xc(r30)"], ["lwz", "r3, 0xc(r31)"]], [32, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]], [36, ["lwz", "r3, 8(r30)"], ["lwz", "r3, 8(r31)"]], [37, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.71154, "total_code": "1664", "matched_code": "888", "matched_code_percent": 53.365387, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 6, "matched_functions": 4, "matched_functions_percent": 66.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["ZiDAWGgetCHARattribute", 99.0], ["ZiDAWGGetGraphInfo", 99.55224]]}

## zi8uwd / Zi8_81480224
Fetched origin; current function source agrees with starting branch: True.
Header trial guard applies only with ZI8_TYPED_USER_WORD defined by zi8uwd.c. ziUwdNode field is a native struct ziUserWord pointer with unchanged offset/size.
```diff
---
+++
@@ -201,5 +201,9 @@
 typedef struct _ziUwdNode {
     struct _ziUwdNode* next;
+#ifdef ZI8_TYPED_USER_WORD
+    struct ziUserWord* word;
+#else
     ziU8* word;
+#endif
 } ziUwdNode;

```

### dictionary nodes store typed user-word records, avoiding casts on candidate load and insertion
Source SHA256 prefix e4bf1772fb7d
```diff
--- start/zi8uwd.c
+++ trial/zi8uwd.c
@@ -1,2 +1,4 @@
+#define ZI8_TYPED_USER_WORD
+struct ziUserWord;
 #include <zi8clib/zitypes.h>
 #include <zi8clib/zierror.h>
@@ -41,5 +43,5 @@
     current = ZI_WORK->uwdList;
     while (current != 0) {
-        candidate = (ziUserWord*)current->word;
+        candidate = current->word;
         if (ZI_WORK->uwdPrioritySort == 1 && candidate->priority < word->priority) break;
         if (candidate->length == length) {
@@ -65,5 +67,5 @@
         added->next = current;
     }
-    added->word = (ziU8*)word;
+    added->word = word;
     Zi8LogError(100, __zi8_work_data);
     return 1;
```
{"unit": "zi8uwd", "function": "Zi8_81480224", "trial": "dictionary nodes store typed user-word records, avoiding casts on candidate load and insertion", "sha": "e4bf1772fb7d", "build": 0, "insns": [116, 116], "diffs": 9, "first": [[5, ["mr", "r26, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r26, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r25, 2(r26)"], ["lbz", "r25, 2(r28)"]], [46, ["lwz", "r28, 4(r30)"], ["lwz", "r26, 4(r30)"]], [54, ["blt", 144], ["bgt", 144]], [55, ["lbz", "r0, 2(r28)"], ["lbz", "r0, 2(r26)"]], [63, ["add", "r3, r28, r0"], ["add", "r3, r0, r26"]], [67, ["add", "r3, r26, r0"], ["add", "r3, r0, r28"]], [104, ["stw", "r26, 4(r29)"], ["stw", "r28, 4(r29)"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.91717, "total_code": "2656", "matched_code": "2192", "matched_code_percent": 82.53012, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8_81480224", 99.52586]]}

### typed dictionary records with target incoming-priority comparison order
Source SHA256 prefix aa459cba8ced
```diff
--- start/zi8uwd.c
+++ trial/zi8uwd.c
@@ -1,2 +1,4 @@
+#define ZI8_TYPED_USER_WORD
+struct ziUserWord;
 #include <zi8clib/zitypes.h>
 #include <zi8clib/zierror.h>
@@ -41,6 +43,6 @@
     current = ZI_WORK->uwdList;
     while (current != 0) {
-        candidate = (ziUserWord*)current->word;
-        if (ZI_WORK->uwdPrioritySort == 1 && candidate->priority < word->priority) break;
+        candidate = current->word;
+        if (ZI_WORK->uwdPrioritySort == 1 && word->priority > candidate->priority) break;
         if (candidate->length == length) {
             position = 0;
@@ -65,5 +67,5 @@
         added->next = current;
     }
-    added->word = (ziU8*)word;
+    added->word = word;
     Zi8LogError(100, __zi8_work_data);
     return 1;
```
{"unit": "zi8uwd", "function": "Zi8_81480224", "trial": "typed dictionary records with target incoming-priority comparison order", "sha": "aa459cba8ced", "build": 0, "insns": [116, 116], "diffs": 10, "first": [[5, ["mr", "r26, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r26, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r25, 2(r26)"], ["lbz", "r25, 2(r28)"]], [46, ["lwz", "r28, 4(r30)"], ["lwz", "r26, 4(r30)"]], [50, ["lbz", "r0, 3(r26)"], ["lbz", "r0, 3(r28)"]], [52, ["lbz", "r0, 3(r28)"], ["lbz", "r0, 3(r26)"]], [55, ["lbz", "r0, 2(r28)"], ["lbz", "r0, 2(r26)"]], [63, ["add", "r3, r28, r0"], ["add", "r3, r0, r26"]], [67, ["add", "r3, r26, r0"], ["add", "r3, r0, r28"]], [104, ["stw", "r26, 4(r29)"], ["stw", "r28, 4(r29)"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.90964, "total_code": "2656", "matched_code": "2192", "matched_code_percent": 82.53012, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8_81480224", 99.48276]]}
Header trial guard applies only with ZI8_TYPED_KEY_MAP defined by zmtkey.c. userKeys keeps its full array extent and pointer layout.
```diff
---
+++
@@ -264,5 +264,9 @@
     ziWChar unk_0x57A[0x641];
     ziPtr unk_0x11FC;
-    ziPtr userKeys[0x83];  // 0x1200
+#ifdef ZI8_TYPED_KEY_MAP
+    struct ziUserKeyMap* userKeys[0x83];
+#else
+    ziPtr userKeys[0x83];
+#endif  // 0x1200
     ziU8 unk_0x140C[4];
     ziU32 formats;  // 0x1410
```

### workspace user-key array has its actual key-map pointer type
Source SHA256 prefix de9fa833cc91
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -1,2 +1,4 @@
+#define ZI8_TYPED_KEY_MAP
+struct ziUserKeyMap;
 #include <zi8clib/zconvert.h>
 #include <zi8clib/zierror.h>
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "workspace user-key array has its actual key-map pointer type", "sha": "de9fa833cc91", "build": 0, "insns": [182, 182], "diffs": 16, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [85, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [90, ["mr", "r27, r3"], ["mr", "r26, r3"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.84657, "total_code": "2216", "matched_code": "1488", "matched_code_percent": 67.14801, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 3, "matched_functions_percent": 75.0, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8getKeyLayout", 99.53297]]}

### typed key-map array and native workspace remove both nested opaque pointer conversions
Source SHA256 prefix 2bcb53e88ad5
```diff
--- start/zmtkey.c
+++ trial/zmtkey.c
@@ -1,2 +1,9 @@
+#define ZI8_TYPED_KEY_MAP
+struct ziUserKeyMap;
+#include <zi8clib/zitypes.h>
+#undef ZI_NEED_WORK
+#define ZI_NEED_WORK , struct __zi8_work_data_s* __zi8_work_data
+#undef ZI_WORK
+#define ZI_WORK __zi8_work_data
 #include <zi8clib/zconvert.h>
 #include <zi8clib/zierror.h>
@@ -5,9 +12,9 @@
 typedef struct ziUserKeyMap { ziWChar* upper[32]; ziWChar* lower[32]; } ziUserKeyMap;

-ziU16 Zi8GetTableCount(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
-ziU32 Zi8GetTableAddress(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
-ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data);
-
-ziBool Zi8MapKeyCode(ziWChar character, ziWChar* output, ziPtr __zi8_work_data) {
+ziU16 Zi8GetTableCount(ziU8 language, ziU8 tableIndex, struct __zi8_work_data_s* __zi8_work_data);
+ziU32 Zi8GetTableAddress(ziU8 language, ziU8 tableIndex, struct __zi8_work_data_s* __zi8_work_data);
+ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, struct __zi8_work_data_s* __zi8_work_data);
+
+ziBool Zi8MapKeyCode(ziWChar character, ziWChar* output, struct __zi8_work_data_s* __zi8_work_data) {
     if (character == 0xeffa) {
         *output = 0;
@@ -22,5 +29,5 @@
 }

-static ziU8 ziNumKeysWithChars(ziU8 language, ziPtr __zi8_work_data) {
+static ziU8 ziNumKeysWithChars(ziU8 language, struct __zi8_work_data_s* __zi8_work_data) {
     ziU16 tableCount;
     ziU8* table;
@@ -44,5 +51,5 @@
 }

-ziBool Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data) {
+ziBool Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, struct __zi8_work_data_s* __zi8_work_data) {
     ziU16 tableCount;
     ziU8 numKeys;
```
{"unit": "zmtkey", "function": "Zi8getKeyLayout", "trial": "typed key-map array and native workspace remove both nested opaque pointer conversions", "sha": "2bcb53e88ad5", "build": 0, "insns": [182, 182], "diffs": 16, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [27, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]], [69, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [74, ["mr", "r27, r3"], ["mr", "r26, r3"]], [75, ["clrlwi", "r0, r27, 0x10"], ["clrlwi", "r0, r26, 0x10"]], [78, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [85, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [90, ["mr", "r27, r3"], ["mr", "r26, r3"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.67509, "total_code": "2216", "matched_code": "324", "matched_code_percent": 14.620939, "total_data": "60", "matched_data": "60", "matched_data_percent": 100.0, "total_functions": 4, "matched_functions": 2, "matched_functions_percent": 50.0, "total_units": 1}, "gains": [], "regressions": ["Zi8ChangeCharCase"], "open": [["Zi8getKeyLayout", 99.53297], ["Zi8ChangeCharCase", 99.67354]]}

### signature table address returned as native byte pointer and assigned without a cast
Source SHA256 prefix 69b51d4419db
```diff
--- start/zi8getc2.c
+++ trial/zi8getc2.c
@@ -23,5 +23,5 @@

 ziU8 Zi8GetFormatVersion(ziU8 language, ziPtr work);
-ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
+ziU8* Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
 ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
 ziU16 Zi8GetVersion(ziPtr work);
@@ -76,5 +76,5 @@
         length = 3;
     }
-    signature = (ziU8*)Zi8GetTableAddress(language, (ziU8)length, work);
+    signature = Zi8GetTableAddress(language, (ziU8)length, work);
     length = Zi8GetTableCount(language, (ziU8)length, work);
     if (length == 0 || length > capacity) {
```
{"unit": "zi8getc2", "function": "Zi8GetDataSignature", "trial": "signature table address returned as native byte pointer and assigned without a cast", "sha": "69b51d4419db", "build": 0, "insns": [69, 69], "diffs": 9, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [9, ["clrlwi", "r0, r28, 0x18"], ["clrlwi", "r0, r29, 0x18"]], [28, ["clrlwi", "r3, r28, 0x18"], ["clrlwi", "r3, r29, 0x18"]], [32, ["mr", "r29, r3"], ["mr", "r27, r3"]], [33, ["clrlwi", "r3, r28, 0x18"], ["clrlwi", "r3, r29, 0x18"]], [51, ["mr", "r3, r27"], ["mr", "r3, r28"]], [52, ["mr", "r4, r29"], ["mr", "r4, r27"]], [57, ["stbx", "r3, r27, r0"], ["stbx", "r3, r28, r0"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.95064, "total_code": "6888", "matched_code": "6360", "matched_code_percent": 92.334496, "total_data": "332", "matched_data": "332", "matched_data_percent": 100.0, "total_functions": 17, "matched_functions": 15, "matched_functions_percent": 88.2353, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8GetDataSignature", 99.347824], ["Zi8IsDupWChar", 99.36508]]}

### halfword key parameter with redundant explicit word masks removed at decode
Source SHA256 prefix a35cdcca4d11
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -203,5 +203,5 @@
 extern ziU8 _Zi8CheckCandidates(ziGetParam*,ziPtr);

-Zi8UInt Zi8SpellingZY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
+Zi8UInt Zi8SpellingZY(ziU16 *output,ziU16 key,ziU8 includeTone)
 {
   ziU16 initialIndex;
@@ -211,6 +211,6 @@

   length = 0;
-  initialIndex = (ziU16)(((key & 0xffff) >> 9) & 0x3f);
-  finalIndex = (ziU16)(((key & 0xffff) >> 3) & 0x3f);
+  initialIndex = (ziU16)((key >> 9) & 0x3f);
+  finalIndex = (ziU16)((key >> 3) & 0x3f);
   tone = (ziU16)(key & 7);
   if ((output[0] = zi8ZYinitialSpelling[initialIndex]) != 0) {
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "halfword key parameter with redundant explicit word masks removed at decode", "sha": "a35cdcca4d11", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 98.23523, "total_code": "21460", "matched_code": "3952", "matched_code_percent": 18.415657, "total_data": "1388", "matched_data": "1280", "matched_data_percent": 92.21902, "total_functions": 9, "matched_functions": 5, "matched_functions_percent": 55.555557, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8SpellingZY", 99.756096], ["Zi8SpellingPY", 99.36306], ["Zi8Get1KeyPressSpelling", 99.555885], ["Zi8Get1KeyPressCandidates", 96.41927]]}

### native tone flag with explicit byte-domain test
Source SHA256 prefix 993e1a695d9e
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -203,5 +203,5 @@
 extern ziU8 _Zi8CheckCandidates(ziGetParam*,ziPtr);

-Zi8UInt Zi8SpellingZY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
+Zi8UInt Zi8SpellingZY(ziU16 *output,Zi8UInt key,Zi8UInt includeTone)
 {
   ziU16 initialIndex;
@@ -224,5 +224,5 @@
     length++;
   }
-  if (includeTone != '\0') {
+  if ((includeTone & 0xff) != 0) {
     switch (tone) {
     case 1:
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "native tone flag with explicit byte-domain test", "sha": "993e1a695d9e", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 98.19702, "total_code": "21460", "matched_code": "3564", "matched_code_percent": 16.607643, "total_data": "1388", "matched_data": "1280", "matched_data_percent": 92.21902, "total_functions": 9, "matched_functions": 4, "matched_functions_percent": 44.444447, "total_units": 1}, "gains": [], "regressions": ["Zi8IsMatch1Key"], "open": [["Zi8SpellingZY", 99.756096], ["Zi8SpellingPY", 99.36306], ["Zi8IsMatch1Key", 98.91753], ["Zi8Get1KeyPressSpelling", 99.497055], ["Zi8Get1KeyPressCandidates", 96.41927]]}

### native final index stores decoded halfword and narrows at row reads
Source SHA256 prefix e46505e2f4b2
```diff
--- start/zi81key.c
+++ trial/zi81key.c
@@ -206,5 +206,5 @@
 {
   ziU16 initialIndex;
-  ziU16 finalIndex;
+  Zi8UInt finalIndex;
   ziU16 tone;
   Zi8UInt length;
@@ -217,6 +217,6 @@
     length = 1;
   }
-  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
-  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
+  output[length & 0xff] = zi8ZYfinalSpelling[(ziU16)finalIndex][0];
+  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[(ziU16)finalIndex][1];
   output[(length & 0xff) + 2] = 0;
   output[(length & 0xff) + 3] = 0;
```
{"unit": "zi81key", "function": "Zi8SpellingZY", "trial": "native final index stores decoded halfword and narrows at row reads", "sha": "e46505e2f4b2", "build": 0, "insns": [123, 123], "diffs": 6, "first": [[27, ["lis", "r7, 0"], ["lis", "r6, 0"]], [28, ["addi", "r6, r7, 0"], ["addi", "r6, r6, 0"]], [35, ["slwi", "r6, r0, 2"], ["slwi", "r7, r0, 2"]], [36, ["lis", "r7, 0"], ["lis", "r6, 0"]], [37, ["addi", "r0, r7, 0"], ["addi", "r0, r6, 0"]], [38, ["add", "r6, r0, r6"], ["add", "r6, r0, r7"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 98.23523, "total_code": "21460", "matched_code": "3952", "matched_code_percent": 18.415657, "total_data": "1388", "matched_data": "1280", "matched_data_percent": 92.21902, "total_functions": 9, "matched_functions": 5, "matched_functions_percent": 55.555557, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8SpellingZY", 99.756096], ["Zi8SpellingPY", 99.36306], ["Zi8Get1KeyPressSpelling", 99.555885], ["Zi8Get1KeyPressCandidates", 96.41927]]}

## zidawg1 / ZiDAWGGetGraphInfo
Fetched origin; current function source agrees with starting branch: True.

### DAWG graph helper and caller use native context through the complete call boundary
Source SHA256 prefix 85d45756014d
```diff
--- start/zidawg1.c
+++ trial/zidawg1.c
@@ -157,8 +157,8 @@
 }

-ziU32 ZiDAWGGetGraph(ziPtr context) {
-    return (((ziU32)((zi8DawgCtx*)context)->table[2] & 0xFFFF) << 8) +
-           ((zi8DawgCtx*)context)->table[3] +
-           ((ziU32)((zi8DawgCtx*)context)->table + 4);
+ziU32 ZiDAWGGetGraph(zi8DawgCtx* context) {
+    return (((ziU32)context->table[2] & 0xFFFF) << 8) +
+           context->table[3] +
+           ((ziU32)context->table + 4);
 }

@@ -200,8 +200,8 @@

         result = graph + (ziU32)entry[4] * 0x10000 + (((ziU16)entry[5] << 8) + entry[6]);
-        ((zi8DawgCtx*)context)->endNode =
+        context->endNode =
             graph + (ziU32)entry[7] * 0x10000 + (((ziU16)entry[8] << 8) + entry[9]);
-        if (((zi8DawgCtx*)context)->endNode == graph) {
-            ((zi8DawgCtx*)context)->endNode = 0;
+        if (context->endNode == graph) {
+            context->endNode = 0;
         }

```
{"unit": "zidawg1", "function": "ZiDAWGGetGraphInfo", "trial": "DAWG graph helper and caller use native context through the complete call boundary", "sha": "85d45756014d", "build": 0, "insns": [134, 134], "diffs": 11, "first": [[10, ["mr", "r28, r3"], ["mr", "r26, r3"]], [35, ["add", "r26, r31, r0"], ["add", "r27, r31, r0"]], [37, ["li", "r27, 0"], ["li", "r28, 0"]], [62, ["cmplw", "r31, r26"], ["cmplw", "r31, r27"]], [75, ["cmplw", "r31, r26"], ["cmplw", "r31, r27"]], [85, ["add", "r3, r28, r3"], ["add", "r3, r26, r3"]], [94, ["add", "r3, r28, r3"], ["add", "r3, r26, r3"]], [99, ["cmplw", "r0, r28"], ["cmplw", "r0, r26"]], [117, ["addi", "r26, r3, 0xa"], ["addi", "r27, r3, 0xa"]], [119, ["addi", "r27, r27, 1"], ["addi", "r28, r28, 1"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.71154, "total_code": "1664", "matched_code": "888", "matched_code_percent": 53.365387, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 6, "matched_functions": 4, "matched_functions_percent": 66.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["ZiDAWGgetCHARattribute", 99.0], ["ZiDAWGGetGraphInfo", 99.55224]]}

### character-attribute decoder takes native byte-node input rather than integer-cast loads
Source SHA256 prefix e3064a9344a6
```diff
--- start/zidawg1.c
+++ trial/zidawg1.c
@@ -134,12 +134,12 @@
 }

-ziU32 ZiDAWGgetCHARattribute(zi8DawgCtx* context, ziU32 node, ziPtr __zi8_work_data) {
+ziU32 ZiDAWGgetCHARattribute(zi8DawgCtx* context, ziU8* node, ziPtr __zi8_work_data) {
     ziU8 key;
     ziU32 attribute;

-    if ((*(ziU8*)node & 0xf) == 0xf) {
-        key = (ziU32)*((ziU8*)node + 1) + 0xf;
+    if ((*node & 0xf) == 0xf) {
+        key = (ziU32)*(node + 1) + 0xf;
     } else {
-        key = (ziU32)*(ziU8*)node & 0xf;
+        key = (ziU32)*node & 0xf;
     }

```
{"unit": "zidawg1", "function": "ZiDAWGgetCHARattribute", "trial": "character-attribute decoder takes native byte-node input rather than integer-cast loads", "sha": "e3064a9344a6", "build": 0, "insns": [60, 60], "diffs": 12, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [14, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [18, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [19, ["clrlwi", "r3, r31, 0x18"], ["clrlwi", "r3, r30, 0x18"]], [20, ["lhz", "r0, 4(r30)"], ["lhz", "r0, 4(r31)"]], [29, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]], [31, ["lwz", "r3, 0xc(r30)"], ["lwz", "r3, 0xc(r31)"]], [32, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]], [36, ["lwz", "r3, 8(r30)"], ["lwz", "r3, 8(r31)"]], [37, ["clrlwi", "r0, r31, 0x18"], ["clrlwi", "r0, r30, 0x18"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 99.71154, "total_code": "1664", "matched_code": "888", "matched_code_percent": 53.365387, "total_data": "80", "matched_data": "80", "matched_data_percent": 100.0, "total_functions": 6, "matched_functions": 4, "matched_functions_percent": 66.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["ZiDAWGgetCHARattribute", 99.0], ["ZiDAWGGetGraphInfo", 99.55224]]}

## zi8alpha / Zi8AlphaGetCandidates
Fetched origin; current function source agrees with starting branch: True.

### Alpha options are a native typed formal, with direct field access and no extra local copy
Source SHA256 prefix ce393080ca06
```diff
--- start/zi8alpha.c
+++ trial/zi8alpha.c
@@ -312,5 +312,5 @@
 ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* characters, ziU8 capacity, ziPtr work);

-int Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr optionData, ziPtr workData)
+int Zi8AlphaGetCandidates(ziGetParam* parameters, ZiAlphaOptions* optionData, ziPtr workData)

 {
@@ -450,8 +450,8 @@
   }
   if (((((ZiAlphaWork*)workData)->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
-     (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
+     (optionData->lookupMode == '\0')) {
     ZiprocessHighlightedW(parameters->elementCount,workData);
   }
-  if (((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->elementCount <= 1)) && (parameters->firstCandidate == 0)) {
+  if (((optionData->lookupMode == '\0') && (parameters->elementCount <= 1)) && (parameters->firstCandidate == 0)) {
     ((ZiAlphaWork*)workData)->highlightedWord[0] = 0;
   }
@@ -459,5 +459,5 @@
     contextEnabled = ZI8_TRUE;
   }
-  if (!(((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->subLanguage != 7)) &&
+  if (!(((optionData->lookupMode == '\0') && (parameters->subLanguage != 7)) &&
      ((parameters->subLanguage != language &&
       ((((parameters->subLanguage != 0 && (parameters->subLanguage != 1)) && (parameters->subLanguage != 2)) &&
@@ -485,5 +485,5 @@
     }
   }
-  if ((parameters->elementCount == 1) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
+  if ((parameters->elementCount == 1) && (optionData->lookupMode == '\0')) {
     if (parameters->wordCharCount >= 3 && parameters->currentWord != 0 &&
         parameters->currentWord[parameters->wordCharCount - 1] == 0x77 &&
@@ -496,5 +496,5 @@
     }
   }
-  if (((elementCount != 0) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
+  if (((elementCount != 0) && (optionData->lookupMode == '\0')) && (optionData->countOnly == '\0')) {
     if (Zi8IsAlphaPunct(elements[elementCount - 1]) == '\0') {
       ((ZiAlphaWork*)workData)->rememberedCount = elementCount;
@@ -524,12 +524,12 @@
   }
   encodedOutput = (ziChar*)parameters->candidates;
-  if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+  if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
     wordCursor = candidateWord;
     wordCapacity = 0x3f;
   } else {
     wordCursor = parameters->candidates;
-    wordCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
-  }
-  remainingCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
+    wordCapacity = optionData->capacity - 1;
+  }
+  remainingCapacity = optionData->capacity - 1;
   if ((elementCount < ((ZiAlphaWork*)workData)->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
     exactLengthOnly = 1;
@@ -550,5 +550,5 @@
   Zi8InitDupWordBuf(workData);
   dictionaryIndex = 0;
-  if ((((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
+  if ((((optionData->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
      ((((parameters->getOptions & 0xfd) != 0x80 && (parameters->elementCount != 0)) &&
       ((parameters->elements[parameters->elementCount - 1] != 0xEFF1 &&
@@ -584,6 +584,6 @@
         } else {
           candidateCount = 1;
-          if (((ZiAlphaOptions*)optionData)->countOnly == 0) {
-            if (((ZiAlphaOptions*)optionData)->suffixOnly != 0) {
+          if (optionData->countOnly == 0) {
+            if (optionData->suffixOnly != 0) {
               for (index = 0; parameters->elementCount + index < elementIndex; index++) {
                 wordCursor[index] = wordCursor[index + parameters->elementCount];
@@ -607,5 +607,5 @@
     }
   }
-  if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
+  if (optionData->lookupMode == '\0') {
     if ((parameters->elementCount <= 1) && (parameters->firstCandidate == 0)) {
       ((ZiAlphaWork*)workData)->prefixEnabled = 0;
@@ -642,5 +642,5 @@
         ((ZiAlphaWork*)workData)->prefixCount--;
       }
-      if ((elementCount <= ((ZiAlphaWork*)workData)->prefixCount) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
+      if ((elementCount <= ((ZiAlphaWork*)workData)->prefixCount) && (optionData->countOnly == '\0')) {
         ((ZiAlphaWork*)workData)->suffixMode = 0;
         ((ZiAlphaWork*)workData)->prefixCount = 0;
@@ -666,5 +666,5 @@
   if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
     secondLanguagePass = ZI8_FALSE;
-    if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+    if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
       wordCursor = candidateWord;
       wordCapacity = 0x40;
@@ -775,5 +775,5 @@
       }
     } else {
-      if (((ZiAlphaOptions*)optionData)->lookupMode != 0) goto finishDictionaryPass;
+      if (optionData->lookupMode != 0) goto finishDictionaryPass;
       dictionaryKind = 10;
     }
@@ -830,8 +830,8 @@
             break;
           case 4:
-            if (((ZiAlphaOptions*)optionData)->minWordLength > elementCount) goto finishDictionaryPass;
+            if (optionData->minWordLength > elementCount) goto finishDictionaryPass;
             break;
           case 3:
-            if (((ZiAlphaOptions*)optionData)->minWordLength > elementCount || elementCount == 1) goto finishDictionaryPass;
+            if (optionData->minWordLength > elementCount || elementCount == 1) goto finishDictionaryPass;
             break;
           case 9:
@@ -1070,5 +1070,5 @@
                    ))) && ((((currentVowelRestriction && (prefixCount == 0)) && (dictionaryKind != 0xb)) &&
                            ((((int)dictionaryIndex < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount &&
-                             (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) &&
+                             (optionData->lookupMode == '\0')) &&
                             (((ZiAlphaWork*)workData)->dictionaries[language] == 0)))))) {
                 if (language != ((ZiAlphaWork*)workData)->language) break;
@@ -1090,5 +1090,5 @@
                  ((((elementCount == 0 || (elements[elementCount - 1] != 0xeff1)) ||
                    ((((ZiAlphaWork*)workData)->rememberedCount != parameters->elementCount - 1 ||
-                    (((((ZiAlphaWork*)workData)->rememberedWord[0] == 0 || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
+                    (((((ZiAlphaWork*)workData)->rememberedWord[0] == 0 || (optionData->lookupMode != '\0')) ||
                      (((ZiAlphaWork*)workData)->dictionaries[language] != 0)))))) ||
                   (languagePassCount == 2)))) break;
@@ -1101,5 +1101,5 @@
               dictionaryKind = 0xb;
             }
-            else if (((ZiAlphaOptions*)optionData)->minWordLength <= wordLength) {
+            else if (optionData->minWordLength <= wordLength) {
               if (prefixVowelRestriction) {
                 if (*wordCursor >= 0x30 && *wordCursor <= 0x39) goto retryDictionary;
@@ -1138,17 +1138,17 @@
                     Zi8ChangeWordCase(wordCursor - prefixCount,language,workData);
                   }
-                  if ((((ZiAlphaOptions*)optionData)->suffixOnly != '\0') &&
-                     ((wordLength + prefixCount) > ((ZiAlphaOptions*)optionData)->maxWordLength)) {
-                    wordLength = ((ZiAlphaOptions*)optionData)->maxWordLength - prefixCount;
+                  if ((optionData->suffixOnly != '\0') &&
+                     ((wordLength + prefixCount) > optionData->maxWordLength)) {
+                    wordLength = optionData->maxWordLength - prefixCount;
                     wordCursor[wordLength] = 0;
                   }
-                  if (((int)((ZiAlphaOptions*)optionData)->maxWordLength < (int)(wordLength + prefixCount)) ||
+                  if (((int)optionData->maxWordLength < (int)(wordLength + prefixCount)) ||
                      ((Zi8IsDupWordW(wordCursor - prefixCount,wordLength + prefixCount & 0xff,
                                                workData)) != '\0')) {
-                    if ((prefixCount != 0) && (((ZiAlphaOptions*)optionData)->maxWordLength <= prefixCount)) break;
+                    if ((prefixCount != 0) && (optionData->maxWordLength <= prefixCount)) break;
                   }
                   else {

-                    if ((((keyLayoutCount == 0) || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
+                    if ((((keyLayoutCount == 0) || (optionData->lookupMode != '\0')) ||
                         ((int)(wordLength + prefixCount) <= 1)) ||
                        (0x40 < (int)(wordLength + prefixCount))) goto emitCandidate;
@@ -1195,24 +1195,24 @@
 emitCandidate:
                     if (firstCandidate == 0) {
-                      if (((ZiAlphaOptions*)optionData)->countOnly != '\0') {
-                        if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
-                          if ((int)((ZiAlphaOptions*)optionData)->shortestWord > (int)(wordLength + prefixCount)) {
-                            ((ZiAlphaOptions*)optionData)->shortestWord = wordLength + prefixCount;
+                      if (optionData->countOnly != '\0') {
+                        if (optionData->suffixOnly != '\0') {
+                          if ((int)optionData->shortestWord > (int)(wordLength + prefixCount)) {
+                            optionData->shortestWord = wordLength + prefixCount;
                           }
-                          if ((int)((ZiAlphaOptions*)optionData)->longestWord < (int)(wordLength + prefixCount)) {
-                            ((ZiAlphaOptions*)optionData)->longestWord = wordLength + prefixCount;
+                          if ((int)optionData->longestWord < (int)(wordLength + prefixCount)) {
+                            optionData->longestWord = wordLength + prefixCount;
                           }
                         }
                         candidateCount = candidateCount + 1;
-                        if (((ZiAlphaOptions*)optionData)->maxResults <= candidateCount) goto finishCandidates;
+                        if (optionData->maxResults <= candidateCount) goto finishCandidates;
                       } else {
-                        if (((ZiAlphaOptions*)optionData)->lookupMode != '\0') {
+                        if (optionData->lookupMode != '\0') {
                           for (index = 0; index <= wordLength; index++) {
-                            if (wordCursor[index] != ((ZiAlphaOptions*)optionData)->dictionary[index]) break;
+                            if (wordCursor[index] != optionData->dictionary[index]) break;
                           }
                           if ((((((ZiAlphaWork*)workData)->operation != '\0') || (index >= wordLength))
                               && ((((ZiAlphaWork*)workData)->operation == '\0' ||
                                   ((exactLengthOnly == 0 ||
-                                   (index >= (int)(ziU16)Zi8WCharCount(((ZiAlphaOptions*)optionData)->dictionary,workData))))))) &&
+                                   (index >= (int)(ziU16)Zi8WCharCount(optionData->dictionary,workData))))))) &&
                              ((exactLengthOnly != 0 || (index >= wordLength)))) {
                             candidateCount = 1;
@@ -1311,5 +1311,5 @@
                           }
                           else {
-                            if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
+                            if (optionData->suffixOnly != '\0') {
                               wordCursor = wordCursor - prefixCount;
                               wordCapacity = wordCapacity + prefixCount;
@@ -1335,5 +1335,5 @@
                           }
                           if (prefixCount != 0) {
-                            if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+                            if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
                               wordCursor = candidateWord;
                               wordCapacity = 0x40;
@@ -1380,5 +1380,5 @@
   if (((candidateCount == 0) && (punctuationCandidate)) && (firstCandidate == 0)) {
     candidateCount = 1;
-    if (((ZiAlphaOptions*)optionData)->countOnly != 0 || (parameters->getOptions & 0xFD) == 0x81) {
+    if (optionData->countOnly != 0 || (parameters->getOptions & 0xFD) == 0x81) {
       if (parameters->getMode == 1) {
         *wordCursor = *elements;
@@ -1392,5 +1392,5 @@
       encodedOutput[1] = encodedOutput[2] = 0;
     }
-    if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
+    if (optionData->lookupMode == '\0') {
       ((ZiAlphaWork*)workData)->singleCharacter = 0;
     }
@@ -1427,5 +1427,5 @@
     currentVowelRestriction = secondaryVowelRestriction;
   }
-  if ((((ZiAlphaOptions*)optionData)->lookupMode != '\0') || ((!completionAllowed && (!currentVowelRestriction)))) goto finishCandidates;
+  if ((optionData->lookupMode != '\0') || ((!completionAllowed && (!currentVowelRestriction)))) goto finishCandidates;
   if ((currentVowelRestriction) &&
      ((((((ZiAlphaWork*)workData)->suffixMode == '\0' && (2 < (int)elementCount)) &&
@@ -1570,5 +1570,5 @@
 finishCandidates:
               ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
-              if (((ZiAlphaOptions*)optionData)->countOnly != '\0') {
+              if (optionData->countOnly != '\0') {
                 parameters->letters = 0;
               }
@@ -1577,5 +1577,5 @@
               }
               wordCursor[-prefixCount] = 0;
-              if (((((ZiAlphaOptions*)optionData)->countOnly == '\0') && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (parameters->elementCount != 0)) {
+              if (((optionData->countOnly == '\0') && (optionData->lookupMode == '\0')) && (parameters->elementCount != 0)) {
                 elementIndex = parameters->elementCount - 1;
                 if (((primaryVowelRestriction) || (secondaryVowelRestriction)) &&
```
{"unit": "zi8alpha", "function": "Zi8AlphaGetCandidates", "trial": "Alpha options are a native typed formal, with direct field access and no extra local copy", "sha": "ce393080ca06", "build": 0, "insns": [3946, 3946], "diffs": 3738, "first": [[17, ["stw", "r0, 0xa8(r1)"], ["stw", "r0, 0xac(r1)"]], [18, ["li", "r0, 0"], ["li", "r4, 0"]], [19, ["stw", "r0, 0xa4(r1)"], ["stw", "r4, 0xa8(r1)"]], [21, ["stw", "r3, 0xa0(r1)"], ["stw", "r3, 0xa4(r1)"]], [22, ["li", "r3, 0"], ["li", "r4, 0"]], [23, ["stw", "r3, 0x9c(r1)"], ["stw", "r4, 0xa0(r1)"]], [24, ["li", "r5, 0"], ["li", "r6, 0"]], [25, ["stw", "r5, 0x98(r1)"], ["stw", "r6, 0x9c(r1)"]], [27, ["stw", "r3, 0x94(r1)"], ["stw", "r3, 0x98(r1)"]], [28, ["li", "r0, 1"], ["li", "r5, 1"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 96.52474, "total_code": "21664", "matched_code": "5880", "matched_code_percent": 27.141804, "total_data": "564", "matched_data": "516", "matched_data_percent": 91.489365, "total_functions": 12, "matched_functions": 11, "matched_functions_percent": 91.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8AlphaGetCandidates", 95.23011]]}

### Alpha workspace is a native typed formal, with direct field access and no extra local copy
Source SHA256 prefix feb267dff5e7
```diff
--- start/zi8alpha.c
+++ trial/zi8alpha.c
@@ -312,5 +312,5 @@
 ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* characters, ziU8 capacity, ziPtr work);

-int Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr optionData, ziPtr workData)
+int Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr optionData, ZiAlphaWork* workData)

 {
@@ -433,6 +433,6 @@
     elements = normalizedElements;
   }
-  if (((ZiAlphaWork*)workData)->context != 0) contextEnabled = 1;
-  if ((((parameters->elementCount != 0) && (((ZiAlphaWork*)workData)->normalizeCase != '\0')) && (!phoneticInput)) && (!phoneticSeparator)) {
+  if (workData->context != 0) contextEnabled = 1;
+  if ((((parameters->elementCount != 0) && (workData->normalizeCase != '\0')) && (!phoneticInput)) && (!phoneticSeparator)) {
     index = 0;
     for (elementIndex = index; (int)elementIndex < (int)(unsigned int)parameters->elementCount; elementIndex = elementIndex + 1) {
@@ -449,10 +449,10 @@
     }
   }
-  if (((((ZiAlphaWork*)workData)->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
+  if (((workData->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
      (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
     ZiprocessHighlightedW(parameters->elementCount,workData);
   }
   if (((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->elementCount <= 1)) && (parameters->firstCandidate == 0)) {
-    ((ZiAlphaWork*)workData)->highlightedWord[0] = 0;
+    workData->highlightedWord[0] = 0;
   }
   if (((Zi8GetTableCount(parameters->language,0x1f,workData) & 0x80) != 0) && (parameters->subLanguage == 0x80)) {
@@ -464,6 +464,6 @@
        ((parameters->subLanguage != 0x80 && ((Zi8LangSupported(parameters->subLanguage,workData)) != '\0'))))))))) {
     languagePassCount = 0;
-    if (((ZiAlphaWork*)workData)->language != parameters->language) {
-      ((ZiAlphaWork*)workData)->language = 0;
+    if (workData->language != parameters->language) {
+      workData->language = 0;
     }
   } else {
@@ -490,29 +490,29 @@
         parameters->currentWord[parameters->wordCharCount - 2] == 0x77 &&
         parameters->currentWord[parameters->wordCharCount - 3] == 0x77) {
-      ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
+      workData->letterHyphen = 0x2e;
     }
     else {
-      ((ZiAlphaWork*)workData)->letterHyphen = 0x2d;
+      workData->letterHyphen = 0x2d;
     }
   }
   if (((elementCount != 0) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
     if (Zi8IsAlphaPunct(elements[elementCount - 1]) == '\0') {
-      ((ZiAlphaWork*)workData)->rememberedCount = elementCount;
-    }
-    else if (((ZiAlphaWork*)workData)->rememberedCount > elementCount) {
-      ((ZiAlphaWork*)workData)->rememberedCount = elementCount - 1;
-    }
-  }
-  if (((ZiAlphaWork*)workData)->usePrefixAsElements == 1) {
-    elements = ((ZiAlphaWork*)workData)->prefix;
-    if (parameters->elementCount > ((ZiAlphaWork*)workData)->prefixCount) {
-    for (index = (unsigned int)((ZiAlphaWork*)workData)->prefixCount; (int)index < (int)(unsigned int)parameters->elementCount;
+      workData->rememberedCount = elementCount;
+    }
+    else if (workData->rememberedCount > elementCount) {
+      workData->rememberedCount = elementCount - 1;
+    }
+  }
+  if (workData->usePrefixAsElements == 1) {
+    elements = workData->prefix;
+    if (parameters->elementCount > workData->prefixCount) {
+    for (index = (unsigned int)workData->prefixCount; (int)index < (int)(unsigned int)parameters->elementCount;
         index = index + 1) {
-      ((ZiAlphaWork*)workData)->prefix[index] =
+      workData->prefix[index] =
            parameters->elements[index];
     }
-    ((ZiAlphaWork*)workData)->prefix[index] = 0;
-    ((ZiAlphaWork*)workData)->prefixCount = (ziU8)index;
-    elementCount = ((ZiAlphaWork*)workData)->prefixCount;
+    workData->prefix[index] = 0;
+    workData->prefixCount = (ziU8)index;
+    elementCount = workData->prefixCount;
     }
   }
@@ -532,5 +532,5 @@
   }
   remainingCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
-  if ((elementCount < ((ZiAlphaWork*)workData)->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
+  if ((elementCount < workData->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
     exactLengthOnly = 1;
   }
@@ -555,14 +555,14 @@
        ((Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1])) != '\0')))))) {
     for (elementIndex = 0; elementIndex < parameters->elementCount - 1; elementIndex++) {
-      if (((ZiAlphaWork*)workData)->highlightedWord[elementIndex] != parameters->elements[elementIndex]) break;
-      wordCursor[elementIndex] = ((ZiAlphaWork*)workData)->highlightedWord[elementIndex];
+      if (workData->highlightedWord[elementIndex] != parameters->elements[elementIndex]) break;
+      wordCursor[elementIndex] = workData->highlightedWord[elementIndex];
     }
     wordCursor[elementIndex] = parameters->elements[elementIndex];
     elementIndex++;
-    if (parameters->elementCount == 1) ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
+    if (parameters->elementCount == 1) workData->singleCharacter = *wordCursor;
     if (elementIndex == parameters->elementCount &&
-        (firstCandidate == 0 || ((ZiAlphaWork*)workData)->reuseHighlightedWord != 0)) {
-      for (index = 0; index < ((ZiAlphaWork*)workData)->dictionaryCount; index++) {
-        switch ((int)((ZiAlphaWork*)workData)->dictionaryKinds[index]) {
+        (firstCandidate == 0 || workData->reuseHighlightedWord != 0)) {
+      for (index = 0; index < workData->dictionaryCount; index++) {
+        switch ((int)workData->dictionaryKinds[index]) {
         case 1:
         case 9:
@@ -571,12 +571,12 @@
       }
 foundHighlightedDictionary:
-      if (firstCandidate == 0 && ((ZiAlphaWork*)workData)->highlightedWord[elementIndex - 1] != 0) {
-        if (((ZiAlphaWork*)workData)->requiredLength < parameters->elementCount)
-          ((ZiAlphaWork*)workData)->reuseHighlightedWord = 0;
+      if (firstCandidate == 0 && workData->highlightedWord[elementIndex - 1] != 0) {
+        if (workData->requiredLength < parameters->elementCount)
+          workData->reuseHighlightedWord = 0;
       } else {
-        ((ZiAlphaWork*)workData)->reuseHighlightedWord = 1;
-      }
-      if (index < ((ZiAlphaWork*)workData)->dictionaryCount &&
-          ((ZiAlphaWork*)workData)->reuseHighlightedWord != 0 &&
+        workData->reuseHighlightedWord = 1;
+      }
+      if (index < workData->dictionaryCount &&
+          workData->reuseHighlightedWord != 0 &&
           Zi8IsDupWordW(wordCursor,elementIndex,workData) == 0) {
         if (firstCandidate != 0) {
@@ -592,9 +592,9 @@
             }
             wordCursor[elementIndex++] = 0;
-            if (((ZiAlphaWork*)workData)->caseMode != 0) {
-              if (((ZiAlphaWork*)workData)->suffixMode == 0)
+            if (workData->caseMode != 0) {
+              if (workData->suffixMode == 0)
                 Zi8ChangeWordCase(wordCursor,language,workData);
               else
-                Zi8ChangeWordCase(wordCursor,((ZiAlphaWork*)workData)->language,workData);
+                Zi8ChangeWordCase(wordCursor,workData->language,workData);
             }
             wordCursor += elementIndex;
@@ -609,49 +609,49 @@
   if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
     if ((parameters->elementCount <= 1) && (parameters->firstCandidate == 0)) {
-      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
-      ((ZiAlphaWork*)workData)->requiredLength = 0;
-      ((ZiAlphaWork*)workData)->previousPrefixCount = 0;
-      ((ZiAlphaWork*)workData)->prefixCount = 0;
-      ((ZiAlphaWork*)workData)->suffixMode = 0;
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-      ((ZiAlphaWork*)workData)->suffixElementCount = 0;
-      ((ZiAlphaWork*)workData)->previousSuffixCount = 0;
-      ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
-      ((ZiAlphaWork*)workData)->rememberedCount = 0;
-      ((ZiAlphaWork*)workData)->suffixCount = 0;
-    }
-    if (((((ZiAlphaWork*)workData)->suffixLocked != '\0') && (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount)) &&
-       ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
+      workData->prefixEnabled = 0;
+      workData->requiredLength = 0;
+      workData->previousPrefixCount = 0;
+      workData->prefixCount = 0;
+      workData->suffixMode = 0;
+      workData->suffixLocked = 0;
+      workData->suffixElementCount = 0;
+      workData->previousSuffixCount = 0;
+      workData->usePrefixAsElements = 0;
+      workData->rememberedCount = 0;
+      workData->suffixCount = 0;
+    }
+    if (((workData->suffixLocked != '\0') && (parameters->elementCount <= workData->suffixElementCount)) &&
+       ((ZiIsLetterHyphen(workData->suffix[(workData->suffixCount - 1)],
                                   workData)) != '\0')) {
-      ((ZiAlphaWork*)workData)->suffixCount--;
-      ((ZiAlphaWork*)workData)->suffixElementCount = ((ZiAlphaWork*)workData)->previousSuffixCount;
-    }
-    if (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount) {
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-    }
-    if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
-      if ((parameters->elementCount <= ((ZiAlphaWork*)workData)->prefixElementCount) &&
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+      workData->suffixCount--;
+      workData->suffixElementCount = workData->previousSuffixCount;
+    }
+    if (parameters->elementCount <= workData->suffixElementCount) {
+      workData->suffixLocked = 0;
+    }
+    if (workData->suffixMode != '\0') {
+      if ((parameters->elementCount <= workData->prefixElementCount) &&
+         ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                     workData)) != '\0')) {
-        ((ZiAlphaWork*)workData)->prefixCount--;
-        ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->previousPrefixCount;
-      }
-      if ((elementCount == ((ZiAlphaWork*)workData)->prefixCount) &&
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+        workData->prefixCount--;
+        workData->prefixElementCount = workData->previousPrefixCount;
+      }
+      if ((elementCount == workData->prefixCount) &&
+         ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                     workData)) != '\0')) {
-        ((ZiAlphaWork*)workData)->prefixCount--;
-      }
-      if ((elementCount <= ((ZiAlphaWork*)workData)->prefixCount) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
-        ((ZiAlphaWork*)workData)->suffixMode = 0;
-        ((ZiAlphaWork*)workData)->prefixCount = 0;
-      }
-    }
-    if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (parameters->elementCount < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->prefixCount--;
+      }
+      if ((elementCount <= workData->prefixCount) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
+        workData->suffixMode = 0;
+        workData->prefixCount = 0;
+      }
+    }
+    if ((workData->suffixMode != '\0') && (parameters->elementCount < workData->alternatePrefixCount)) {
+      workData->alternatePrefixCount = 0;
     }
   }
   goto prepareDictionaryOrder;
 preparePrefix:
-  prefixMode = ((ZiAlphaWork*)workData)->suffixMode;
+  prefixMode = workData->suffixMode;
   prefixTableFlags = Zi8GetTableCount(language,0x1f,workData);
   prefixVowelFlags = prefixTableFlags & 0x10;
@@ -664,5 +664,5 @@
     prefixVowelRestriction = ZI8_FALSE;
   }
-  if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
+  if (workData->suffixMode != '\0') {
     secondLanguagePass = ZI8_FALSE;
     if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
@@ -673,25 +673,25 @@
       dictionaryStatus[index] = 0;
     }
-    for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount; index = index + 1) {
-      wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+    for (index = 0; index < (int)(unsigned int)workData->prefixCount; index = index + 1) {
+      wordCursor[index] = workData->prefix[index];
       if ((elements[index] != wordCursor[index]) &&
          (elements[index] != (ziU16)Zi8ConvertWC2Key(wordCursor[index],language,workData))) goto finishCandidates;
     }
-    wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
-    elements = elements + ((ZiAlphaWork*)workData)->prefixCount;
-    elementCount = elementCount - ((ZiAlphaWork*)workData)->prefixCount;
-    wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
-    prefixCount = (unsigned int)((ZiAlphaWork*)workData)->prefixCount;
-    if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount; index = index + 1) {
-        wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
+    wordCursor = wordCursor + workData->prefixCount;
+    elements = elements + workData->prefixCount;
+    elementCount = elementCount - workData->prefixCount;
+    wordCapacity = wordCapacity - workData->prefixCount;
+    prefixCount = (unsigned int)workData->prefixCount;
+    if (workData->suffixLocked != '\0') {
+      for (index = 0; index < (int)(unsigned int)workData->suffixCount; index = index + 1) {
+        wordCursor[index] = workData->suffix[index];
         if ((elements[index] != wordCursor[index]) &&
            (elements[index] != (ziU16)Zi8ConvertWC2Key(wordCursor[index],language,workData))) goto finishCandidates;
       }
-      wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
-      elements = elements + ((ZiAlphaWork*)workData)->suffixCount;
-      elementCount = elementCount - ((ZiAlphaWork*)workData)->suffixCount;
-      wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
-      prefixCount = prefixCount + ((ZiAlphaWork*)workData)->suffixCount;
+      wordCursor = wordCursor + workData->suffixCount;
+      elements = elements + workData->suffixCount;
+      elementCount = elementCount - workData->suffixCount;
+      wordCapacity = wordCapacity - workData->suffixCount;
+      prefixCount = prefixCount + workData->suffixCount;
     }
     if ((prefixVowelRestriction) && (wordCursor[-1] != 0x27)) {
@@ -701,5 +701,5 @@
   goto prepareDictionaryOrder;
 prepareDictionaryOrder:
-  ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 0;
+  workData->dictionaryOrder[0] = 0;
   if ((Zi8GetTableCount(language,0x1f,workData) & 0x20) != 0) {
     if (parameters->currentWord == 0 || parameters->wordCharCount == 0 ||
@@ -707,7 +707,7 @@
         parameters->currentWord[parameters->wordCharCount - 1] > 0xfe ||
         Zi8ConvertWC2Key(parameters->currentWord[parameters->wordCharCount - 1],language,workData) == 0xEFF1) {
-      ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 1;
+      workData->dictionaryOrder[1] = 1;
     } else {
-      ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
+      workData->dictionaryOrder[1] = 0;
       if (language == 10 && parameters->wordCharCount != 0) {
         for (elementIndex = parameters->wordCharCount - 1; elementIndex >= 0; elementIndex--) {
@@ -716,5 +716,5 @@
           case 0x6f:
           case 0x75:
-            ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 1;
+            workData->dictionaryOrder[0] = 1;
           case 0x20:
             elementIndex = 0;
@@ -724,5 +724,5 @@
     }
   } else {
-    ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
+    workData->dictionaryOrder[1] = 0;
   }
 prepareDictionaries:
@@ -743,5 +743,5 @@
   }
   if ((((currentVowelRestriction) && (languagePassCount != 2)) && (parameters->elementCount == 2)) &&
-     ((parameters->elements[1] == 0xEFF1 && (((ZiAlphaWork*)workData)->singleCharacter != 0)))) {
+     ((parameters->elements[1] == 0xEFF1 && (workData->singleCharacter != 0)))) {
     if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
       punctuationBuffer[0] = 0;
@@ -753,5 +753,5 @@
   punctuationCursor = &punctuationBuffer[0];
   keyLayoutCount = Zi8GetTableCount(language,4,workData);
-  if (((ZiAlphaWork*)workData)->wordState != '\0') {
+  if (workData->wordState != '\0') {
     keyLayoutCount = 0;
   }
@@ -759,15 +759,15 @@
     keyLayout = (ziU8 *)Zi8GetTableAddress(language,4,workData);
   }
-  for (dictionaryIndex = 0; (int)dictionaryIndex <= (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount;
+  for (dictionaryIndex = 0; (int)dictionaryIndex <= (int)(unsigned int)workData->dictionaryCount;
       dictionaryIndex = dictionaryIndex + 1) {
-    if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
+    if (workData->dictionaryCounts != 0) {
       if (dictionaryIndex != 0) {
-        ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex - 1] = (ziU8)candidateCount;
+        workData->dictionaryCounts[dictionaryIndex - 1] = (ziU8)candidateCount;
       } else {
-        Zi8Memset(((ZiAlphaWork*)workData)->dictionaryCounts,0,((ZiAlphaWork*)workData)->dictionaryCount);
-      }
-    }
-    if (dictionaryIndex != ((ZiAlphaWork*)workData)->dictionaryCount) {
-      dictionaryKind = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex];
+        Zi8Memset(workData->dictionaryCounts,0,workData->dictionaryCount);
+      }
+    }
+    if (dictionaryIndex != workData->dictionaryCount) {
+      dictionaryKind = workData->dictionaryKinds[dictionaryIndex];
       if (dictionaryKind == 12) {
         if (languagePassCount != 2) goto finishDictionaryPass;
@@ -799,5 +799,5 @@
                   ((Zi8getKeyLayout(language,*elements,(punctuationBuffer + 1),parameters->elementCount,workData
                                            )) == '\0')))))) ||
-               (((((ZiAlphaWork*)workData)->suffixMode == '\0' &&
+               (((workData->suffixMode == '\0' &&
                  ((parameters->firstCandidate == 0 && (candidateCount == 0)))) &&
                 ((parameters->currentWord == 0 ||
@@ -816,5 +816,5 @@
             if (((candidateCount == 0) &&
                 (((parameters->firstCandidate == 0 || (parameters->firstCandidate == firstCandidate))
-                 && (((ZiAlphaWork*)workData)->suffixMode == '\0')))) &&
+                 && (workData->suffixMode == '\0')))) &&
                (((parameters->currentWord == 0 || (parameters->wordCharCount == 0)) ||
                 (parameters->currentWord[parameters->wordCharCount - 1] == 0x20)))) {
@@ -845,14 +845,14 @@
             dictionaryExact = 0;
             if (languagePassCount == 2) {
-              for (index = dictionaryIndex + 1; index < ((ZiAlphaWork*)workData)->dictionaryCount; index++) {
-                if (((ZiAlphaWork*)workData)->dictionaryKinds[index] == 1 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 2 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 4 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 3) {
+              for (index = dictionaryIndex + 1; index < workData->dictionaryCount; index++) {
+                if (workData->dictionaryKinds[index] == 1 ||
+                    workData->dictionaryKinds[index] == 2 ||
+                    workData->dictionaryKinds[index] == 4 ||
+                    workData->dictionaryKinds[index] == 3) {
                   switchedLanguage = 1;
                   break;
                 }
               }
-              if (index >= ((ZiAlphaWork*)workData)->dictionaryCount) {
+              if (index >= workData->dictionaryCount) {
                 languagePassCount = 1;
                 language = parameters->subLanguage;
@@ -892,6 +892,6 @@
               if ((((matchMode == 0) && (currentVowelRestriction)) &&
                   ((2 < (int)elementCount &&
-                   ((((ZiAlphaWork*)workData)->language == language &&
-                    (((ZiAlphaWork*)workData)->prefixCount == elementCount - 1)))))) &&
+                   ((workData->language == language &&
+                    (workData->prefixCount == elementCount - 1)))))) &&
                  (elements[elementCount - 1] == 0xeff1)) {
                 wordLength = 0;
@@ -919,6 +919,6 @@
               }
               if ((((wordLength == 0) && (*punctuationCursor != 0)) && (dictionaryExact != 0)) &&
-                 ((((ZiAlphaWork*)workData)->singleCharacter != 0 && (parameters->elementCount == 2)))) {
-                *wordCursor = ((ZiAlphaWork*)workData)->singleCharacter;
+                 ((workData->singleCharacter != 0 && (parameters->elementCount == 2)))) {
+                *wordCursor = workData->singleCharacter;
                 wordCursor[1] = *punctuationCursor++;
                 wordCursor[2] = 0;
@@ -1033,5 +1033,5 @@
               if (retryPunctuation) {
                 for (index = 0; index < parameters->elementCount - 1; index++) {
-                  wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+                  wordCursor[index] = workData->prefix[index];
                   if (wordCursor[index] == 0) break;
                 }
@@ -1041,9 +1041,9 @@
                 }
               } else {
-                for (index = 0; index < ((ZiAlphaWork*)workData)->rememberedCount; index++) {
-                  wordCursor[index] = ((ZiAlphaWork*)workData)->rememberedWord[index];
+                for (index = 0; index < workData->rememberedCount; index++) {
+                  wordCursor[index] = workData->rememberedWord[index];
                   if (wordCursor[index] == 0) break;
                 }
-                if (index < ((ZiAlphaWork*)workData)->rememberedCount) {
+                if (index < workData->rememberedCount) {
                   wordLength = 0;
                   break;
@@ -1061,17 +1061,17 @@
             if (wordLength == 0) {
               dictionaryStatus[dictionaryKind] = 2;
-              if ((((((((ZiAlphaWork*)workData)->prefixEnabled != '\0') && (!retryPunctuation)) && (parameters->elementCount != 0)) &&
-                   ((((ZiAlphaWork*)workData)->requiredLength >= parameters->elementCount - 1 &&
+              if ((((((workData->prefixEnabled != '\0') && (!retryPunctuation)) && (parameters->elementCount != 0)) &&
+                   ((workData->requiredLength >= parameters->elementCount - 1 &&
                     (parameters->elements[parameters->elementCount - 1] == 0xEFF1)))) &&
-                  (((((ZiAlphaWork*)workData)->prefixEnabled != '\x01' ||
-                    (((ZiAlphaWork*)workData)->requiredLength != parameters->elementCount)) &&
-                   (((((ZiAlphaWork*)workData)->prefixLength == '\0' ||
-                     (((ZiAlphaWork*)workData)->prefixLength + 1 >= parameters->elementCount)) && (dictionaryExact != 0)))
+                  (((workData->prefixEnabled != '\x01' ||
+                    (workData->requiredLength != parameters->elementCount)) &&
+                   (((workData->prefixLength == '\0' ||
+                     (workData->prefixLength + 1 >= parameters->elementCount)) && (dictionaryExact != 0)))
                    ))) && ((((currentVowelRestriction && (prefixCount == 0)) && (dictionaryKind != 0xb)) &&
-                           ((((int)dictionaryIndex < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount &&
+                           ((((int)dictionaryIndex < (int)(unsigned int)workData->dictionaryCount &&
                              (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) &&
-                            (((ZiAlphaWork*)workData)->dictionaries[language] == 0)))))) {
-                if (language != ((ZiAlphaWork*)workData)->language) break;
-                index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
+                            (workData->dictionaries[language] == 0)))))) {
+                if (language != workData->language) break;
+                index = workData->dictionaryKinds[dictionaryIndex + 1];
                 if (index == 0xc || (index < 9 && index >= 5)) {
                   if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
@@ -1086,12 +1086,12 @@
               if ((((((dictionaryExact == 0) || (!currentVowelRestriction)) || (prefixCount != 0)) ||
                    ((dictionaryKind == 0xb ||
-                    (dictionaryIndex >= ((ZiAlphaWork*)workData)->dictionaryCount)))) ||
+                    (dictionaryIndex >= workData->dictionaryCount)))) ||
                   (elements == 0)) ||
                  ((((elementCount == 0 || (elements[elementCount - 1] != 0xeff1)) ||
-                   ((((ZiAlphaWork*)workData)->rememberedCount != parameters->elementCount - 1 ||
-                    (((((ZiAlphaWork*)workData)->rememberedWord[0] == 0 || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
-                     (((ZiAlphaWork*)workData)->dictionaries[language] != 0)))))) ||
+                   ((workData->rememberedCount != parameters->elementCount - 1 ||
+                    (((workData->rememberedWord[0] == 0 || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
+                     (workData->dictionaries[language] != 0)))))) ||
                   (languagePassCount == 2)))) break;
-              index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
+              index = workData->dictionaryKinds[dictionaryIndex + 1];
               if ((index != 0xc) && (((0xb < index || (8 < index)) || (index < 5)))) break;
               if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
@@ -1135,5 +1135,5 @@
                    ((Zi8ZHCheckSpelling(wordCursor,parameters->elements,parameters->elementCount,
                                              workData)) != '\0')) {
-                  if ((((ZiAlphaWork*)workData)->caseMode != '\0') && ((!phoneticInput && (!phoneticSeparator)))) {
+                  if ((workData->caseMode != '\0') && ((!phoneticInput && (!phoneticSeparator)))) {
                     Zi8ChangeWordCase(wordCursor - prefixCount,language,workData);
                   }
@@ -1211,6 +1211,6 @@
                             if (wordCursor[index] != ((ZiAlphaOptions*)optionData)->dictionary[index]) break;
                           }
-                          if ((((((ZiAlphaWork*)workData)->operation != '\0') || (index >= wordLength))
-                              && ((((ZiAlphaWork*)workData)->operation == '\0' ||
+                          if ((((workData->operation != '\0') || (index >= wordLength))
+                              && ((workData->operation == '\0' ||
                                   ((exactLengthOnly == 0 ||
                                    (index >= (int)(ziU16)Zi8WCharCount(((ZiAlphaOptions*)optionData)->dictionary,workData))))))) &&
@@ -1220,81 +1220,81 @@
                           }
                         } else {
-                          if (((((ZiAlphaWork*)workData)->suffixMode == '\0') && (wordCursor[1] == 0)) &&
+                          if (((workData->suffixMode == '\0') && (wordCursor[1] == 0)) &&
                              (candidateCount == 0)) {
                             if (*wordCursor >= 0xeff1 && *wordCursor <= 0xf010) {
-                              ((ZiAlphaWork*)workData)->singleCharacter = 0;
+                              workData->singleCharacter = 0;
                             }
                             else {
-                              ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
+                              workData->singleCharacter = *wordCursor;
                             }
                           }
                           if (dictionaryExact != 0 &&
-                              parameters->elementCount == ((ZiAlphaWork*)workData)->rememberedCount &&
+                              parameters->elementCount == workData->rememberedCount &&
                               (parameters->maxCandidates == 1 ||
                                (candidateCount == 0 && parameters->firstCandidate == 0))) {
                             for (index = 0; (int)index < (int)prefixCount; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[index]
+                              workData->rememberedWord[index]
                                    = wordCursor[index - prefixCount];
                             }
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] =
+                              workData->rememberedWord[index + prefixCount] =
                                    wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] = 0;
+                            workData->rememberedWord[index + prefixCount] = 0;
                           }
                           else {
-                            if (((dictionaryExact == 0) && (parameters->elementCount == ((ZiAlphaWork*)workData)->rememberedCount))
+                            if (((dictionaryExact == 0) && (parameters->elementCount == workData->rememberedCount))
                                && ((parameters->maxCandidates == 1 ||
                                    ((candidateCount == 0 && (parameters->firstCandidate == 0)))))) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[0] = 0;
+                              workData->rememberedWord[0] = 0;
                             }
                           }
-                          if ((((ZiAlphaWork*)workData)->suffixMode == '\0') &&
-                             ((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                 ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
-                                ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)))) ||
-                               ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0)))) &&
+                          if ((workData->suffixMode == '\0') &&
+                             ((((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                 ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0)))) ||
+                                ((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0)))) ||
+                               ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0)))) &&
                               ((parameters->maxCandidates == 1 ||
                                ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
+                              workData->prefix[index] = wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->prefixCount = wordLength;
-                            ((ZiAlphaWork*)workData)->language = language;
+                            workData->prefixCount = wordLength;
+                            workData->language = language;
                           }
-                          else if ((((ZiAlphaWork*)workData)->suffixLocked == '\0') &&
-                                  (((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                       ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0))))
-                                      || ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0))))
-                                     || ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))
-                                    && (((ZiAlphaWork*)workData)->language == language)) &&
+                          else if ((workData->suffixLocked == '\0') &&
+                                  (((((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                       ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0))))
+                                      || ((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0))))
+                                     || ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0))))
+                                    && (workData->language == language)) &&
                                    ((parameters->maxCandidates == 1 ||
                                     ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                             if (wordLength == parameters->elementCount) {
                               for (index = 0; index < (int)wordLength; index = index + 1) {
-                                ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
+                                workData->prefix[index] = wordCursor[index];
                               }
-                              ((ZiAlphaWork*)workData)->prefixCount = wordLength;
+                              workData->prefixCount = wordLength;
                             }
                             else {
                               for (index = 0; index < (int)wordLength; index = index + 1) {
-                                ((ZiAlphaWork*)workData)->suffix[index] = wordCursor[index];
+                                workData->suffix[index] = wordCursor[index];
                               }
-                              ((ZiAlphaWork*)workData)->suffixCount = wordLength;
+                              workData->suffixCount = wordLength;
                             }
                           }
-                          else if ((((ZiAlphaWork*)workData)->suffixMode != '\0') &&
-                                  (((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                     ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
-                                    (((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)) ||
-                                     ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))))
-                                   && ((((ZiAlphaWork*)workData)->language != language &&
+                          else if ((workData->suffixMode != '\0') &&
+                                  (((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                     ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0)))) ||
+                                    (((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0)) ||
+                                     ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0))))))
+                                   && ((workData->language != language &&
                                        ((parameters->maxCandidates == 1 ||
                                         ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))
                                    ))) {
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->alternatePrefix[index] = wordCursor[index];
+                              workData->alternatePrefix[index] = wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->alternatePrefixCount = (ziU8)index;
+                            workData->alternatePrefixCount = (ziU8)index;
                           }
                           wordLength = wordLength + 1;
@@ -1339,17 +1339,17 @@
                               wordCapacity = 0x40;
                             }
-                            for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount;
+                            for (index = 0; index < (int)(unsigned int)workData->prefixCount;
                                 index = index + 1) {
-                              wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+                              wordCursor[index] = workData->prefix[index];
                             }
-                            wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
-                            wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
-                            if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-                              for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount;
+                            wordCursor = wordCursor + workData->prefixCount;
+                            wordCapacity = wordCapacity - workData->prefixCount;
+                            if (workData->suffixLocked != '\0') {
+                              for (index = 0; index < (int)(unsigned int)workData->suffixCount;
                                   index = index + 1) {
-                                wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
+                                wordCursor[index] = workData->suffix[index];
                               }
-                              wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
-                              wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
+                              wordCursor = wordCursor + workData->suffixCount;
+                              wordCapacity = wordCapacity - workData->suffixCount;
                             }
                           }
@@ -1393,5 +1393,5 @@
     }
     if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
-      ((ZiAlphaWork*)workData)->singleCharacter = 0;
+      workData->singleCharacter = 0;
     }
   }
@@ -1416,5 +1416,5 @@
     goto prepareDictionaries;
   }
-  language = ((ZiAlphaWork*)workData)->language;
+  language = workData->language;
   if (language == 0) {
     language = parameters->language;
@@ -1429,26 +1429,26 @@
   if ((((ZiAlphaOptions*)optionData)->lookupMode != '\0') || ((!completionAllowed && (!currentVowelRestriction)))) goto finishCandidates;
   if ((currentVowelRestriction) &&
-     ((((((ZiAlphaWork*)workData)->suffixMode == '\0' && (2 < (int)elementCount)) &&
+     ((((workData->suffixMode == '\0' && (2 < (int)elementCount)) &&
        (elements[elementCount - 2] == 0xeff1)) &&
-      ((int)((ZiAlphaWork*)workData)->prefixCount == elementCount - 2)))) {
-    ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->prefixCount + '\x01';
-    ((ZiAlphaWork*)workData)->suffixMode = 1;
-  }
-  if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (!prefixPrepared)) {
+      ((int)workData->prefixCount == elementCount - 2)))) {
+    workData->prefixElementCount = workData->prefixCount + '\x01';
+    workData->suffixMode = 1;
+  }
+  if ((workData->suffixMode != '\0') && (!prefixPrepared)) {
     prefixPrepared = ZI8_TRUE;
     goto preparePrefix;
   }
-  if (currentVowelRestriction && ((ZiAlphaWork*)workData)->suffixMode != 0 &&
-      ((ZiAlphaWork*)workData)->suffixLocked == 0 && elementCount > 2 &&
+  if (currentVowelRestriction && workData->suffixMode != 0 &&
+      workData->suffixLocked == 0 && elementCount > 2 &&
       ((elements[elementCount - 2] == 0xEFF1 &&
-        ((ZiAlphaWork*)workData)->suffixCount == elementCount - 2) ||
-       (((ZiAlphaWork*)workData)->suffixCount == elementCount - 1 &&
+        workData->suffixCount == elementCount - 2) ||
+       (workData->suffixCount == elementCount - 1 &&
         Zi8IsAlphaPunct(elements[elementCount - 1]) != 0))) {
-    if (((ZiAlphaWork*)workData)->prefixEnabled >= 1 && elements[elementCount - 1] == 0xEFF1) {
+    if (workData->prefixEnabled >= 1 && elements[elementCount - 1] == 0xEFF1) {
       goto checkPrefixPunctuation;
     }
     if (!primaryMatched && !secondaryMatched) {
-      ((ZiAlphaWork*)workData)->suffixLocked = 1;
-      ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount - 1;
+      workData->suffixLocked = 1;
+      workData->suffixElementCount = parameters->elementCount - 1;
       if (prefixCount != 0) {
         wordCursor -= prefixCount;
@@ -1461,14 +1461,14 @@
     }
   }
-  if ((prefixPrepared) && (1 < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
+  if ((prefixPrepared) && (1 < workData->alternatePrefixCount)) {
     if (language == parameters->language) {
       if (primaryMatched) {
-        ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->alternatePrefixCount = 0;
       }
     }
     else if (secondaryMatched) {
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
-    }
-    if (((ZiAlphaWork*)workData)->alternatePrefixCount != '\0') {
+      workData->alternatePrefixCount = 0;
+    }
+    if (workData->alternatePrefixCount != '\0') {
       wordCursor -= prefixCount;
       elements -= prefixCount;
@@ -1477,19 +1477,19 @@
       prefixCount = 0;
       prefixPrepared = ZI8_FALSE;
-      ((ZiAlphaWork*)workData)->suffixMode = 0;
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-      ((ZiAlphaWork*)workData)->suffixCount = 0;
-      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->alternatePrefixCount; index = index + 1) {
-        ((ZiAlphaWork*)workData)->prefix[index] =
-             ((ZiAlphaWork*)workData)->alternatePrefix[index];
-      }
-      ((ZiAlphaWork*)workData)->prefixCount = (ziU8)index;
-      if (((ZiAlphaWork*)workData)->language == parameters->language) {
-        ((ZiAlphaWork*)workData)->language = parameters->subLanguage;
+      workData->suffixMode = 0;
+      workData->suffixLocked = 0;
+      workData->suffixCount = 0;
+      for (index = 0; index < (int)(unsigned int)workData->alternatePrefixCount; index = index + 1) {
+        workData->prefix[index] =
+             workData->alternatePrefix[index];
+      }
+      workData->prefixCount = (ziU8)index;
+      if (workData->language == parameters->language) {
+        workData->language = parameters->subLanguage;
       }
       else {
-        ((ZiAlphaWork*)workData)->language = parameters->language;
-      }
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->language = parameters->language;
+      }
+      workData->alternatePrefixCount = 0;
     }
   }
@@ -1499,15 +1499,15 @@
   if (currentVowelRestriction) {
 checkPrefixPunctuation:
-    if ((1 < ((ZiAlphaWork*)workData)->prefixEnabled) &&
+    if ((1 < workData->prefixEnabled) &&
        (parameters->elements[parameters->elementCount - 1] != 0xEFF1))
     goto finishCandidates;
     if ((((*elements == 0xeff1) ||
          ((ZiIsLetterHyphen(*elements,workData)) != '\0')) &&
-        ((((ZiAlphaWork*)workData)->suffixLocked == '\0' ||
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
+        ((workData->suffixLocked == '\0' ||
+         ((ZiIsLetterHyphen(workData->suffix[(workData->suffixCount - 1)],
                                     workData)) == '\0')))) &&
-       (((((ZiAlphaWork*)workData)->suffixMode == '\0' ||
-         ((((ZiAlphaWork*)workData)->suffixLocked != '\0' ||
-          ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+       (((workData->suffixMode == '\0' ||
+         ((workData->suffixLocked != '\0' ||
+          ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                      workData)) == '\0')))) &&
         ((((Zi8GetTableCount(language,0x1f,workData)) & 8) == 0 &&
@@ -1520,31 +1520,31 @@
         prefixCount = 0;
       }
-      if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-        ((ZiAlphaWork*)workData)->previousSuffixCount = ((ZiAlphaWork*)workData)->suffixElementCount;
-        ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount;
-        elementIndex = (int)((ZiAlphaWork*)workData)->prefixCount + (int)((ZiAlphaWork*)workData)->suffixCount;
+      if (workData->suffixLocked != '\0') {
+        workData->previousSuffixCount = workData->suffixElementCount;
+        workData->suffixElementCount = parameters->elementCount;
+        elementIndex = (int)workData->prefixCount + (int)workData->suffixCount;
         if (elements[elementIndex] != 0xEFF1 && Zi8IsAlphaPunct(elements[elementIndex]) != 0) {
-          ((ZiAlphaWork*)workData)->suffix[((ZiAlphaWork*)workData)->suffixCount++] = elements[elementIndex];
+          workData->suffix[workData->suffixCount++] = elements[elementIndex];
         } else {
-          ((ZiAlphaWork*)workData)->suffix[((ZiAlphaWork*)workData)->suffixCount++] = ((ZiAlphaWork*)workData)->letterHyphen;
+          workData->suffix[workData->suffixCount++] = workData->letterHyphen;
         }
         prefixPrepared = ZI8_TRUE;
       } else {
-        ((ZiAlphaWork*)workData)->previousPrefixCount = ((ZiAlphaWork*)workData)->prefixElementCount;
-        ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
-        if (((ZiAlphaWork*)workData)->suffixMode == '\0') {
-          ((ZiAlphaWork*)workData)->suffixMode = 1;
-          ((ZiAlphaWork*)workData)->prefixCount = 0;
-        }
-        if (((((((ZiAlphaWork*)workData)->prefixCount == '\x03') && (((ZiAlphaWork*)workData)->prefix[0] == 0x77)) &&
-             (((ZiAlphaWork*)workData)->prefix[1] == 0x77)) && (((ZiAlphaWork*)workData)->prefix[2] == 0x77)) ||
+        workData->previousPrefixCount = workData->prefixElementCount;
+        workData->prefixElementCount = parameters->elementCount;
+        if (workData->suffixMode == '\0') {
+          workData->suffixMode = 1;
+          workData->prefixCount = 0;
+        }
+        if (((((workData->prefixCount == '\x03') && (workData->prefix[0] == 0x77)) &&
+             (workData->prefix[1] == 0x77)) && (workData->prefix[2] == 0x77)) ||
            (((Zi8GetTableCount(language,0x1f,workData)) & 0x100) != 0)) {
-          ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
-        }
-        if (elements[((ZiAlphaWork*)workData)->prefixCount] != 0xEFF1 && Zi8IsAlphaPunct(elements[((ZiAlphaWork*)workData)->prefixCount]) != 0) {
-          ((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount] = elements[((ZiAlphaWork*)workData)->prefixCount];
-          ((ZiAlphaWork*)workData)->prefixCount++;
+          workData->letterHyphen = 0x2e;
+        }
+        if (elements[workData->prefixCount] != 0xEFF1 && Zi8IsAlphaPunct(elements[workData->prefixCount]) != 0) {
+          workData->prefix[workData->prefixCount] = elements[workData->prefixCount];
+          workData->prefixCount++;
         } else {
-          ((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount++] = ((ZiAlphaWork*)workData)->letterHyphen;
+          workData->prefix[workData->prefixCount++] = workData->letterHyphen;
         }
         prefixPrepared = ZI8_TRUE;
@@ -1553,21 +1553,21 @@
     }
   }
-  if (!completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && ((ZiAlphaWork*)workData)->prefixCount != 0 &&
-      elementCount > 2 && ((ZiAlphaWork*)workData)->prefixCount == elementCount - 1 &&
-      Zi8IsAlphaPunct(parameters->elements[((ZiAlphaWork*)workData)->prefixCount - 1]) != 0) goto checkPrefixFields;
-  if (!completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && parameters->elementCount > 1 &&
+  if (!completionAllowed && workData->suffixMode == 0 && workData->prefixCount != 0 &&
+      elementCount > 2 && workData->prefixCount == elementCount - 1 &&
+      Zi8IsAlphaPunct(parameters->elements[workData->prefixCount - 1]) != 0) goto checkPrefixFields;
+  if (!completionAllowed && workData->suffixMode == 0 && parameters->elementCount > 1 &&
       Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1]) == 0) goto finishCandidates;
 checkPrefixFields:
-  prefixMode = ((ZiAlphaWork*)workData)->suffixMode;
-  prefixLength = ((ZiAlphaWork*)workData)->prefixCount;
+  prefixMode = workData->suffixMode;
+  prefixLength = workData->prefixCount;
   if (prefixMode != 0 || prefixLength == 0 || elementCount <= 2 ||
       prefixLength != elementCount - 1 || parameters->elements[parameters->elementCount - 1] == 0xEFF1) goto finishCandidates;
-  ((ZiAlphaWork*)workData)->suffixMode = 1;
-  ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
+  workData->suffixMode = 1;
+  workData->prefixElementCount = parameters->elementCount;
   prefixPrepared = ZI8_TRUE;
   goto preparePrefix;

 finishCandidates:
-              ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
+              workData->usePrefixAsElements = 0;
               if (((ZiAlphaOptions*)optionData)->countOnly != '\0') {
                 parameters->letters = 0;
@@ -1580,5 +1580,5 @@
                 elementIndex = parameters->elementCount - 1;
                 if (((primaryVowelRestriction) || (secondaryVowelRestriction)) &&
-                   ((((ZiAlphaWork*)workData)->prefixEnabled <= 1 ||
+                   ((workData->prefixEnabled <= 1 ||
                     (parameters->elements[elementIndex] == 0xEFF1)))) {
                   index = 0;
@@ -1589,12 +1589,12 @@
                   }
                   if (index != 0) {
-                    ((ZiAlphaWork*)workData)->prefixEnabled = (ziU8)index;
+                    workData->prefixEnabled = (ziU8)index;
                   } else {
                     if (candidateCount != 0) {
-                      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
-                      ((ZiAlphaWork*)workData)->requiredLength = 0;
+                      workData->prefixEnabled = 0;
+                      workData->requiredLength = 0;
                     }
                   }
-                  ((ZiAlphaWork*)workData)->requiredLength = parameters->elementCount;
+                  workData->requiredLength = parameters->elementCount;
                 }
                 if ((parameters->letters != 0) && (parameters->maxCandidates == 1)) {
@@ -1617,17 +1617,17 @@
                 }
               }
-              if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
-                if ((int)dictionaryIndex >= (int)((ZiAlphaWork*)workData)->dictionaryCount) {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[((ZiAlphaWork*)workData)->dictionaryCount - 1] = candidateCount;
+              if (workData->dictionaryCounts != 0) {
+                if ((int)dictionaryIndex >= (int)workData->dictionaryCount) {
+                  workData->dictionaryCounts[workData->dictionaryCount - 1] = candidateCount;
                 } else {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex] = candidateCount;
+                  workData->dictionaryCounts[dictionaryIndex] = candidateCount;
                 }
                 countIndex = dictionaryIndex;
-                if (countIndex >= ((ZiAlphaWork*)workData)->dictionaryCount) {
-                  countIndex = ((ZiAlphaWork*)workData)->dictionaryCount - 1;
+                if (countIndex >= workData->dictionaryCount) {
+                  countIndex = workData->dictionaryCount - 1;
                 }
                 for (; countIndex >= 1; countIndex = countIndex - 1) {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex] -=
-                       ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex - 1];
+                  workData->dictionaryCounts[countIndex] -=
+                       workData->dictionaryCounts[countIndex - 1];
                 }
               }
```
{"unit": "zi8alpha", "function": "Zi8AlphaGetCandidates", "trial": "Alpha workspace is a native typed formal, with direct field access and no extra local copy", "sha": "feb267dff5e7", "build": 0, "insns": [3946, 3946], "diffs": 3758, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [7, ["mr", "r31, r5"], ["mr", "r30, r5"]], [17, ["stw", "r0, 0xa8(r1)"], ["stw", "r0, 0xac(r1)"]], [18, ["li", "r0, 0"], ["li", "r4, 0"]], [19, ["stw", "r0, 0xa4(r1)"], ["stw", "r4, 0xa8(r1)"]], [21, ["stw", "r3, 0xa0(r1)"], ["stw", "r3, 0xa4(r1)"]], [22, ["li", "r3, 0"], ["li", "r4, 0"]], [23, ["stw", "r3, 0x9c(r1)"], ["stw", "r4, 0xa0(r1)"]], [24, ["li", "r5, 0"], ["li", "r6, 0"]], [25, ["stw", "r5, 0x98(r1)"], ["stw", "r6, 0x9c(r1)"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 96.03545, "total_code": "21664", "matched_code": "5880", "matched_code_percent": 27.141804, "total_data": "564", "matched_data": "516", "matched_data_percent": 91.489365, "total_functions": 12, "matched_functions": 11, "matched_functions_percent": 91.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8AlphaGetCandidates", 94.55854]]}

### Alpha options and workspace both use native record formals at every field read
Source SHA256 prefix 0633912127b6
```diff
--- start/zi8alpha.c
+++ trial/zi8alpha.c
@@ -312,5 +312,5 @@
 ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* characters, ziU8 capacity, ziPtr work);

-int Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr optionData, ziPtr workData)
+int Zi8AlphaGetCandidates(ziGetParam* parameters, ZiAlphaOptions* optionData, ZiAlphaWork* workData)

 {
@@ -433,6 +433,6 @@
     elements = normalizedElements;
   }
-  if (((ZiAlphaWork*)workData)->context != 0) contextEnabled = 1;
-  if ((((parameters->elementCount != 0) && (((ZiAlphaWork*)workData)->normalizeCase != '\0')) && (!phoneticInput)) && (!phoneticSeparator)) {
+  if (workData->context != 0) contextEnabled = 1;
+  if ((((parameters->elementCount != 0) && (workData->normalizeCase != '\0')) && (!phoneticInput)) && (!phoneticSeparator)) {
     index = 0;
     for (elementIndex = index; (int)elementIndex < (int)(unsigned int)parameters->elementCount; elementIndex = elementIndex + 1) {
@@ -449,21 +449,21 @@
     }
   }
-  if (((((ZiAlphaWork*)workData)->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
-     (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
+  if (((workData->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
+     (optionData->lookupMode == '\0')) {
     ZiprocessHighlightedW(parameters->elementCount,workData);
   }
-  if (((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->elementCount <= 1)) && (parameters->firstCandidate == 0)) {
-    ((ZiAlphaWork*)workData)->highlightedWord[0] = 0;
+  if (((optionData->lookupMode == '\0') && (parameters->elementCount <= 1)) && (parameters->firstCandidate == 0)) {
+    workData->highlightedWord[0] = 0;
   }
   if (((Zi8GetTableCount(parameters->language,0x1f,workData) & 0x80) != 0) && (parameters->subLanguage == 0x80)) {
     contextEnabled = ZI8_TRUE;
   }
-  if (!(((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->subLanguage != 7)) &&
+  if (!(((optionData->lookupMode == '\0') && (parameters->subLanguage != 7)) &&
      ((parameters->subLanguage != language &&
       ((((parameters->subLanguage != 0 && (parameters->subLanguage != 1)) && (parameters->subLanguage != 2)) &&
        ((parameters->subLanguage != 0x80 && ((Zi8LangSupported(parameters->subLanguage,workData)) != '\0'))))))))) {
     languagePassCount = 0;
-    if (((ZiAlphaWork*)workData)->language != parameters->language) {
-      ((ZiAlphaWork*)workData)->language = 0;
+    if (workData->language != parameters->language) {
+      workData->language = 0;
     }
   } else {
@@ -485,34 +485,34 @@
     }
   }
-  if ((parameters->elementCount == 1) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
+  if ((parameters->elementCount == 1) && (optionData->lookupMode == '\0')) {
     if (parameters->wordCharCount >= 3 && parameters->currentWord != 0 &&
         parameters->currentWord[parameters->wordCharCount - 1] == 0x77 &&
         parameters->currentWord[parameters->wordCharCount - 2] == 0x77 &&
         parameters->currentWord[parameters->wordCharCount - 3] == 0x77) {
-      ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
+      workData->letterHyphen = 0x2e;
     }
     else {
-      ((ZiAlphaWork*)workData)->letterHyphen = 0x2d;
-    }
-  }
-  if (((elementCount != 0) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
+      workData->letterHyphen = 0x2d;
+    }
+  }
+  if (((elementCount != 0) && (optionData->lookupMode == '\0')) && (optionData->countOnly == '\0')) {
     if (Zi8IsAlphaPunct(elements[elementCount - 1]) == '\0') {
-      ((ZiAlphaWork*)workData)->rememberedCount = elementCount;
-    }
-    else if (((ZiAlphaWork*)workData)->rememberedCount > elementCount) {
-      ((ZiAlphaWork*)workData)->rememberedCount = elementCount - 1;
-    }
-  }
-  if (((ZiAlphaWork*)workData)->usePrefixAsElements == 1) {
-    elements = ((ZiAlphaWork*)workData)->prefix;
-    if (parameters->elementCount > ((ZiAlphaWork*)workData)->prefixCount) {
-    for (index = (unsigned int)((ZiAlphaWork*)workData)->prefixCount; (int)index < (int)(unsigned int)parameters->elementCount;
+      workData->rememberedCount = elementCount;
+    }
+    else if (workData->rememberedCount > elementCount) {
+      workData->rememberedCount = elementCount - 1;
+    }
+  }
+  if (workData->usePrefixAsElements == 1) {
+    elements = workData->prefix;
+    if (parameters->elementCount > workData->prefixCount) {
+    for (index = (unsigned int)workData->prefixCount; (int)index < (int)(unsigned int)parameters->elementCount;
         index = index + 1) {
-      ((ZiAlphaWork*)workData)->prefix[index] =
+      workData->prefix[index] =
            parameters->elements[index];
     }
-    ((ZiAlphaWork*)workData)->prefix[index] = 0;
-    ((ZiAlphaWork*)workData)->prefixCount = (ziU8)index;
-    elementCount = ((ZiAlphaWork*)workData)->prefixCount;
+    workData->prefix[index] = 0;
+    workData->prefixCount = (ziU8)index;
+    elementCount = workData->prefixCount;
     }
   }
@@ -524,13 +524,13 @@
   }
   encodedOutput = (ziChar*)parameters->candidates;
-  if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+  if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
     wordCursor = candidateWord;
     wordCapacity = 0x3f;
   } else {
     wordCursor = parameters->candidates;
-    wordCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
-  }
-  remainingCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
-  if ((elementCount < ((ZiAlphaWork*)workData)->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
+    wordCapacity = optionData->capacity - 1;
+  }
+  remainingCapacity = optionData->capacity - 1;
+  if ((elementCount < workData->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
     exactLengthOnly = 1;
   }
@@ -550,19 +550,19 @@
   Zi8InitDupWordBuf(workData);
   dictionaryIndex = 0;
-  if ((((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
+  if ((((optionData->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
      ((((parameters->getOptions & 0xfd) != 0x80 && (parameters->elementCount != 0)) &&
       ((parameters->elements[parameters->elementCount - 1] != 0xEFF1 &&
        ((Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1])) != '\0')))))) {
     for (elementIndex = 0; elementIndex < parameters->elementCount - 1; elementIndex++) {
-      if (((ZiAlphaWork*)workData)->highlightedWord[elementIndex] != parameters->elements[elementIndex]) break;
-      wordCursor[elementIndex] = ((ZiAlphaWork*)workData)->highlightedWord[elementIndex];
+      if (workData->highlightedWord[elementIndex] != parameters->elements[elementIndex]) break;
+      wordCursor[elementIndex] = workData->highlightedWord[elementIndex];
     }
     wordCursor[elementIndex] = parameters->elements[elementIndex];
     elementIndex++;
-    if (parameters->elementCount == 1) ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
+    if (parameters->elementCount == 1) workData->singleCharacter = *wordCursor;
     if (elementIndex == parameters->elementCount &&
-        (firstCandidate == 0 || ((ZiAlphaWork*)workData)->reuseHighlightedWord != 0)) {
-      for (index = 0; index < ((ZiAlphaWork*)workData)->dictionaryCount; index++) {
-        switch ((int)((ZiAlphaWork*)workData)->dictionaryKinds[index]) {
+        (firstCandidate == 0 || workData->reuseHighlightedWord != 0)) {
+      for (index = 0; index < workData->dictionaryCount; index++) {
+        switch ((int)workData->dictionaryKinds[index]) {
         case 1:
         case 9:
@@ -571,12 +571,12 @@
       }
 foundHighlightedDictionary:
-      if (firstCandidate == 0 && ((ZiAlphaWork*)workData)->highlightedWord[elementIndex - 1] != 0) {
-        if (((ZiAlphaWork*)workData)->requiredLength < parameters->elementCount)
-          ((ZiAlphaWork*)workData)->reuseHighlightedWord = 0;
+      if (firstCandidate == 0 && workData->highlightedWord[elementIndex - 1] != 0) {
+        if (workData->requiredLength < parameters->elementCount)
+          workData->reuseHighlightedWord = 0;
       } else {
-        ((ZiAlphaWork*)workData)->reuseHighlightedWord = 1;
-      }
-      if (index < ((ZiAlphaWork*)workData)->dictionaryCount &&
-          ((ZiAlphaWork*)workData)->reuseHighlightedWord != 0 &&
+        workData->reuseHighlightedWord = 1;
+      }
+      if (index < workData->dictionaryCount &&
+          workData->reuseHighlightedWord != 0 &&
           Zi8IsDupWordW(wordCursor,elementIndex,workData) == 0) {
         if (firstCandidate != 0) {
@@ -584,6 +584,6 @@
         } else {
           candidateCount = 1;
-          if (((ZiAlphaOptions*)optionData)->countOnly == 0) {
-            if (((ZiAlphaOptions*)optionData)->suffixOnly != 0) {
+          if (optionData->countOnly == 0) {
+            if (optionData->suffixOnly != 0) {
               for (index = 0; parameters->elementCount + index < elementIndex; index++) {
                 wordCursor[index] = wordCursor[index + parameters->elementCount];
@@ -592,9 +592,9 @@
             }
             wordCursor[elementIndex++] = 0;
-            if (((ZiAlphaWork*)workData)->caseMode != 0) {
-              if (((ZiAlphaWork*)workData)->suffixMode == 0)
+            if (workData->caseMode != 0) {
+              if (workData->suffixMode == 0)
                 Zi8ChangeWordCase(wordCursor,language,workData);
               else
-                Zi8ChangeWordCase(wordCursor,((ZiAlphaWork*)workData)->language,workData);
+                Zi8ChangeWordCase(wordCursor,workData->language,workData);
             }
             wordCursor += elementIndex;
@@ -607,51 +607,51 @@
     }
   }
-  if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
+  if (optionData->lookupMode == '\0') {
     if ((parameters->elementCount <= 1) && (parameters->firstCandidate == 0)) {
-      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
-      ((ZiAlphaWork*)workData)->requiredLength = 0;
-      ((ZiAlphaWork*)workData)->previousPrefixCount = 0;
-      ((ZiAlphaWork*)workData)->prefixCount = 0;
-      ((ZiAlphaWork*)workData)->suffixMode = 0;
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-      ((ZiAlphaWork*)workData)->suffixElementCount = 0;
-      ((ZiAlphaWork*)workData)->previousSuffixCount = 0;
-      ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
-      ((ZiAlphaWork*)workData)->rememberedCount = 0;
-      ((ZiAlphaWork*)workData)->suffixCount = 0;
-    }
-    if (((((ZiAlphaWork*)workData)->suffixLocked != '\0') && (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount)) &&
-       ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
+      workData->prefixEnabled = 0;
+      workData->requiredLength = 0;
+      workData->previousPrefixCount = 0;
+      workData->prefixCount = 0;
+      workData->suffixMode = 0;
+      workData->suffixLocked = 0;
+      workData->suffixElementCount = 0;
+      workData->previousSuffixCount = 0;
+      workData->usePrefixAsElements = 0;
+      workData->rememberedCount = 0;
+      workData->suffixCount = 0;
+    }
+    if (((workData->suffixLocked != '\0') && (parameters->elementCount <= workData->suffixElementCount)) &&
+       ((ZiIsLetterHyphen(workData->suffix[(workData->suffixCount - 1)],
                                   workData)) != '\0')) {
-      ((ZiAlphaWork*)workData)->suffixCount--;
-      ((ZiAlphaWork*)workData)->suffixElementCount = ((ZiAlphaWork*)workData)->previousSuffixCount;
-    }
-    if (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount) {
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-    }
-    if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
-      if ((parameters->elementCount <= ((ZiAlphaWork*)workData)->prefixElementCount) &&
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+      workData->suffixCount--;
+      workData->suffixElementCount = workData->previousSuffixCount;
+    }
+    if (parameters->elementCount <= workData->suffixElementCount) {
+      workData->suffixLocked = 0;
+    }
+    if (workData->suffixMode != '\0') {
+      if ((parameters->elementCount <= workData->prefixElementCount) &&
+         ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                     workData)) != '\0')) {
-        ((ZiAlphaWork*)workData)->prefixCount--;
-        ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->previousPrefixCount;
-      }
-      if ((elementCount == ((ZiAlphaWork*)workData)->prefixCount) &&
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+        workData->prefixCount--;
+        workData->prefixElementCount = workData->previousPrefixCount;
+      }
+      if ((elementCount == workData->prefixCount) &&
+         ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                     workData)) != '\0')) {
-        ((ZiAlphaWork*)workData)->prefixCount--;
-      }
-      if ((elementCount <= ((ZiAlphaWork*)workData)->prefixCount) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
-        ((ZiAlphaWork*)workData)->suffixMode = 0;
-        ((ZiAlphaWork*)workData)->prefixCount = 0;
-      }
-    }
-    if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (parameters->elementCount < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->prefixCount--;
+      }
+      if ((elementCount <= workData->prefixCount) && (optionData->countOnly == '\0')) {
+        workData->suffixMode = 0;
+        workData->prefixCount = 0;
+      }
+    }
+    if ((workData->suffixMode != '\0') && (parameters->elementCount < workData->alternatePrefixCount)) {
+      workData->alternatePrefixCount = 0;
     }
   }
   goto prepareDictionaryOrder;
 preparePrefix:
-  prefixMode = ((ZiAlphaWork*)workData)->suffixMode;
+  prefixMode = workData->suffixMode;
   prefixTableFlags = Zi8GetTableCount(language,0x1f,workData);
   prefixVowelFlags = prefixTableFlags & 0x10;
@@ -664,7 +664,7 @@
     prefixVowelRestriction = ZI8_FALSE;
   }
-  if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
+  if (workData->suffixMode != '\0') {
     secondLanguagePass = ZI8_FALSE;
-    if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+    if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
       wordCursor = candidateWord;
       wordCapacity = 0x40;
@@ -673,25 +673,25 @@
       dictionaryStatus[index] = 0;
     }
-    for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount; index = index + 1) {
-      wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+    for (index = 0; index < (int)(unsigned int)workData->prefixCount; index = index + 1) {
+      wordCursor[index] = workData->prefix[index];
       if ((elements[index] != wordCursor[index]) &&
          (elements[index] != (ziU16)Zi8ConvertWC2Key(wordCursor[index],language,workData))) goto finishCandidates;
     }
-    wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
-    elements = elements + ((ZiAlphaWork*)workData)->prefixCount;
-    elementCount = elementCount - ((ZiAlphaWork*)workData)->prefixCount;
-    wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
-    prefixCount = (unsigned int)((ZiAlphaWork*)workData)->prefixCount;
-    if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount; index = index + 1) {
-        wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
+    wordCursor = wordCursor + workData->prefixCount;
+    elements = elements + workData->prefixCount;
+    elementCount = elementCount - workData->prefixCount;
+    wordCapacity = wordCapacity - workData->prefixCount;
+    prefixCount = (unsigned int)workData->prefixCount;
+    if (workData->suffixLocked != '\0') {
+      for (index = 0; index < (int)(unsigned int)workData->suffixCount; index = index + 1) {
+        wordCursor[index] = workData->suffix[index];
         if ((elements[index] != wordCursor[index]) &&
            (elements[index] != (ziU16)Zi8ConvertWC2Key(wordCursor[index],language,workData))) goto finishCandidates;
       }
-      wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
-      elements = elements + ((ZiAlphaWork*)workData)->suffixCount;
-      elementCount = elementCount - ((ZiAlphaWork*)workData)->suffixCount;
-      wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
-      prefixCount = prefixCount + ((ZiAlphaWork*)workData)->suffixCount;
+      wordCursor = wordCursor + workData->suffixCount;
+      elements = elements + workData->suffixCount;
+      elementCount = elementCount - workData->suffixCount;
+      wordCapacity = wordCapacity - workData->suffixCount;
+      prefixCount = prefixCount + workData->suffixCount;
     }
     if ((prefixVowelRestriction) && (wordCursor[-1] != 0x27)) {
@@ -701,5 +701,5 @@
   goto prepareDictionaryOrder;
 prepareDictionaryOrder:
-  ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 0;
+  workData->dictionaryOrder[0] = 0;
   if ((Zi8GetTableCount(language,0x1f,workData) & 0x20) != 0) {
     if (parameters->currentWord == 0 || parameters->wordCharCount == 0 ||
@@ -707,7 +707,7 @@
         parameters->currentWord[parameters->wordCharCount - 1] > 0xfe ||
         Zi8ConvertWC2Key(parameters->currentWord[parameters->wordCharCount - 1],language,workData) == 0xEFF1) {
-      ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 1;
+      workData->dictionaryOrder[1] = 1;
     } else {
-      ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
+      workData->dictionaryOrder[1] = 0;
       if (language == 10 && parameters->wordCharCount != 0) {
         for (elementIndex = parameters->wordCharCount - 1; elementIndex >= 0; elementIndex--) {
@@ -716,5 +716,5 @@
           case 0x6f:
           case 0x75:
-            ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 1;
+            workData->dictionaryOrder[0] = 1;
           case 0x20:
             elementIndex = 0;
@@ -724,5 +724,5 @@
     }
   } else {
-    ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
+    workData->dictionaryOrder[1] = 0;
   }
 prepareDictionaries:
@@ -743,5 +743,5 @@
   }
   if ((((currentVowelRestriction) && (languagePassCount != 2)) && (parameters->elementCount == 2)) &&
-     ((parameters->elements[1] == 0xEFF1 && (((ZiAlphaWork*)workData)->singleCharacter != 0)))) {
+     ((parameters->elements[1] == 0xEFF1 && (workData->singleCharacter != 0)))) {
     if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
       punctuationBuffer[0] = 0;
@@ -753,5 +753,5 @@
   punctuationCursor = &punctuationBuffer[0];
   keyLayoutCount = Zi8GetTableCount(language,4,workData);
-  if (((ZiAlphaWork*)workData)->wordState != '\0') {
+  if (workData->wordState != '\0') {
     keyLayoutCount = 0;
   }
@@ -759,15 +759,15 @@
     keyLayout = (ziU8 *)Zi8GetTableAddress(language,4,workData);
   }
-  for (dictionaryIndex = 0; (int)dictionaryIndex <= (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount;
+  for (dictionaryIndex = 0; (int)dictionaryIndex <= (int)(unsigned int)workData->dictionaryCount;
       dictionaryIndex = dictionaryIndex + 1) {
-    if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
+    if (workData->dictionaryCounts != 0) {
       if (dictionaryIndex != 0) {
-        ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex - 1] = (ziU8)candidateCount;
+        workData->dictionaryCounts[dictionaryIndex - 1] = (ziU8)candidateCount;
       } else {
-        Zi8Memset(((ZiAlphaWork*)workData)->dictionaryCounts,0,((ZiAlphaWork*)workData)->dictionaryCount);
-      }
-    }
-    if (dictionaryIndex != ((ZiAlphaWork*)workData)->dictionaryCount) {
-      dictionaryKind = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex];
+        Zi8Memset(workData->dictionaryCounts,0,workData->dictionaryCount);
+      }
+    }
+    if (dictionaryIndex != workData->dictionaryCount) {
+      dictionaryKind = workData->dictionaryKinds[dictionaryIndex];
       if (dictionaryKind == 12) {
         if (languagePassCount != 2) goto finishDictionaryPass;
@@ -775,5 +775,5 @@
       }
     } else {
-      if (((ZiAlphaOptions*)optionData)->lookupMode != 0) goto finishDictionaryPass;
+      if (optionData->lookupMode != 0) goto finishDictionaryPass;
       dictionaryKind = 10;
     }
@@ -799,5 +799,5 @@
                   ((Zi8getKeyLayout(language,*elements,(punctuationBuffer + 1),parameters->elementCount,workData
                                            )) == '\0')))))) ||
-               (((((ZiAlphaWork*)workData)->suffixMode == '\0' &&
+               (((workData->suffixMode == '\0' &&
                  ((parameters->firstCandidate == 0 && (candidateCount == 0)))) &&
                 ((parameters->currentWord == 0 ||
@@ -816,5 +816,5 @@
             if (((candidateCount == 0) &&
                 (((parameters->firstCandidate == 0 || (parameters->firstCandidate == firstCandidate))
-                 && (((ZiAlphaWork*)workData)->suffixMode == '\0')))) &&
+                 && (workData->suffixMode == '\0')))) &&
                (((parameters->currentWord == 0 || (parameters->wordCharCount == 0)) ||
                 (parameters->currentWord[parameters->wordCharCount - 1] == 0x20)))) {
@@ -830,8 +830,8 @@
             break;
           case 4:
-            if (((ZiAlphaOptions*)optionData)->minWordLength > elementCount) goto finishDictionaryPass;
+            if (optionData->minWordLength > elementCount) goto finishDictionaryPass;
             break;
           case 3:
-            if (((ZiAlphaOptions*)optionData)->minWordLength > elementCount || elementCount == 1) goto finishDictionaryPass;
+            if (optionData->minWordLength > elementCount || elementCount == 1) goto finishDictionaryPass;
             break;
           case 9:
@@ -845,14 +845,14 @@
             dictionaryExact = 0;
             if (languagePassCount == 2) {
-              for (index = dictionaryIndex + 1; index < ((ZiAlphaWork*)workData)->dictionaryCount; index++) {
-                if (((ZiAlphaWork*)workData)->dictionaryKinds[index] == 1 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 2 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 4 ||
-                    ((ZiAlphaWork*)workData)->dictionaryKinds[index] == 3) {
+              for (index = dictionaryIndex + 1; index < workData->dictionaryCount; index++) {
+                if (workData->dictionaryKinds[index] == 1 ||
+                    workData->dictionaryKinds[index] == 2 ||
+                    workData->dictionaryKinds[index] == 4 ||
+                    workData->dictionaryKinds[index] == 3) {
                   switchedLanguage = 1;
                   break;
                 }
               }
-              if (index >= ((ZiAlphaWork*)workData)->dictionaryCount) {
+              if (index >= workData->dictionaryCount) {
                 languagePassCount = 1;
                 language = parameters->subLanguage;
@@ -892,6 +892,6 @@
               if ((((matchMode == 0) && (currentVowelRestriction)) &&
                   ((2 < (int)elementCount &&
-                   ((((ZiAlphaWork*)workData)->language == language &&
-                    (((ZiAlphaWork*)workData)->prefixCount == elementCount - 1)))))) &&
+                   ((workData->language == language &&
+                    (workData->prefixCount == elementCount - 1)))))) &&
                  (elements[elementCount - 1] == 0xeff1)) {
                 wordLength = 0;
@@ -919,6 +919,6 @@
               }
               if ((((wordLength == 0) && (*punctuationCursor != 0)) && (dictionaryExact != 0)) &&
-                 ((((ZiAlphaWork*)workData)->singleCharacter != 0 && (parameters->elementCount == 2)))) {
-                *wordCursor = ((ZiAlphaWork*)workData)->singleCharacter;
+                 ((workData->singleCharacter != 0 && (parameters->elementCount == 2)))) {
+                *wordCursor = workData->singleCharacter;
                 wordCursor[1] = *punctuationCursor++;
                 wordCursor[2] = 0;
@@ -1033,5 +1033,5 @@
               if (retryPunctuation) {
                 for (index = 0; index < parameters->elementCount - 1; index++) {
-                  wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+                  wordCursor[index] = workData->prefix[index];
                   if (wordCursor[index] == 0) break;
                 }
@@ -1041,9 +1041,9 @@
                 }
               } else {
-                for (index = 0; index < ((ZiAlphaWork*)workData)->rememberedCount; index++) {
-                  wordCursor[index] = ((ZiAlphaWork*)workData)->rememberedWord[index];
+                for (index = 0; index < workData->rememberedCount; index++) {
+                  wordCursor[index] = workData->rememberedWord[index];
                   if (wordCursor[index] == 0) break;
                 }
-                if (index < ((ZiAlphaWork*)workData)->rememberedCount) {
+                if (index < workData->rememberedCount) {
                   wordLength = 0;
                   break;
@@ -1061,17 +1061,17 @@
             if (wordLength == 0) {
               dictionaryStatus[dictionaryKind] = 2;
-              if ((((((((ZiAlphaWork*)workData)->prefixEnabled != '\0') && (!retryPunctuation)) && (parameters->elementCount != 0)) &&
-                   ((((ZiAlphaWork*)workData)->requiredLength >= parameters->elementCount - 1 &&
+              if ((((((workData->prefixEnabled != '\0') && (!retryPunctuation)) && (parameters->elementCount != 0)) &&
+                   ((workData->requiredLength >= parameters->elementCount - 1 &&
                     (parameters->elements[parameters->elementCount - 1] == 0xEFF1)))) &&
-                  (((((ZiAlphaWork*)workData)->prefixEnabled != '\x01' ||
-                    (((ZiAlphaWork*)workData)->requiredLength != parameters->elementCount)) &&
-                   (((((ZiAlphaWork*)workData)->prefixLength == '\0' ||
-                     (((ZiAlphaWork*)workData)->prefixLength + 1 >= parameters->elementCount)) && (dictionaryExact != 0)))
+                  (((workData->prefixEnabled != '\x01' ||
+                    (workData->requiredLength != parameters->elementCount)) &&
+                   (((workData->prefixLength == '\0' ||
+                     (workData->prefixLength + 1 >= parameters->elementCount)) && (dictionaryExact != 0)))
                    ))) && ((((currentVowelRestriction && (prefixCount == 0)) && (dictionaryKind != 0xb)) &&
-                           ((((int)dictionaryIndex < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount &&
-                             (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) &&
-                            (((ZiAlphaWork*)workData)->dictionaries[language] == 0)))))) {
-                if (language != ((ZiAlphaWork*)workData)->language) break;
-                index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
+                           ((((int)dictionaryIndex < (int)(unsigned int)workData->dictionaryCount &&
+                             (optionData->lookupMode == '\0')) &&
+                            (workData->dictionaries[language] == 0)))))) {
+                if (language != workData->language) break;
+                index = workData->dictionaryKinds[dictionaryIndex + 1];
                 if (index == 0xc || (index < 9 && index >= 5)) {
                   if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
@@ -1086,12 +1086,12 @@
               if ((((((dictionaryExact == 0) || (!currentVowelRestriction)) || (prefixCount != 0)) ||
                    ((dictionaryKind == 0xb ||
-                    (dictionaryIndex >= ((ZiAlphaWork*)workData)->dictionaryCount)))) ||
+                    (dictionaryIndex >= workData->dictionaryCount)))) ||
                   (elements == 0)) ||
                  ((((elementCount == 0 || (elements[elementCount - 1] != 0xeff1)) ||
-                   ((((ZiAlphaWork*)workData)->rememberedCount != parameters->elementCount - 1 ||
-                    (((((ZiAlphaWork*)workData)->rememberedWord[0] == 0 || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
-                     (((ZiAlphaWork*)workData)->dictionaries[language] != 0)))))) ||
+                   ((workData->rememberedCount != parameters->elementCount - 1 ||
+                    (((workData->rememberedWord[0] == 0 || (optionData->lookupMode != '\0')) ||
+                     (workData->dictionaries[language] != 0)))))) ||
                   (languagePassCount == 2)))) break;
-              index = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
+              index = workData->dictionaryKinds[dictionaryIndex + 1];
               if ((index != 0xc) && (((0xb < index || (8 < index)) || (index < 5)))) break;
               if (Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData) == 0) {
@@ -1101,5 +1101,5 @@
               dictionaryKind = 0xb;
             }
-            else if (((ZiAlphaOptions*)optionData)->minWordLength <= wordLength) {
+            else if (optionData->minWordLength <= wordLength) {
               if (prefixVowelRestriction) {
                 if (*wordCursor >= 0x30 && *wordCursor <= 0x39) goto retryDictionary;
@@ -1135,20 +1135,20 @@
                    ((Zi8ZHCheckSpelling(wordCursor,parameters->elements,parameters->elementCount,
                                              workData)) != '\0')) {
-                  if ((((ZiAlphaWork*)workData)->caseMode != '\0') && ((!phoneticInput && (!phoneticSeparator)))) {
+                  if ((workData->caseMode != '\0') && ((!phoneticInput && (!phoneticSeparator)))) {
                     Zi8ChangeWordCase(wordCursor - prefixCount,language,workData);
                   }
-                  if ((((ZiAlphaOptions*)optionData)->suffixOnly != '\0') &&
-                     ((wordLength + prefixCount) > ((ZiAlphaOptions*)optionData)->maxWordLength)) {
-                    wordLength = ((ZiAlphaOptions*)optionData)->maxWordLength - prefixCount;
+                  if ((optionData->suffixOnly != '\0') &&
+                     ((wordLength + prefixCount) > optionData->maxWordLength)) {
+                    wordLength = optionData->maxWordLength - prefixCount;
                     wordCursor[wordLength] = 0;
                   }
-                  if (((int)((ZiAlphaOptions*)optionData)->maxWordLength < (int)(wordLength + prefixCount)) ||
+                  if (((int)optionData->maxWordLength < (int)(wordLength + prefixCount)) ||
                      ((Zi8IsDupWordW(wordCursor - prefixCount,wordLength + prefixCount & 0xff,
                                                workData)) != '\0')) {
-                    if ((prefixCount != 0) && (((ZiAlphaOptions*)optionData)->maxWordLength <= prefixCount)) break;
+                    if ((prefixCount != 0) && (optionData->maxWordLength <= prefixCount)) break;
                   }
                   else {

-                    if ((((keyLayoutCount == 0) || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
+                    if ((((keyLayoutCount == 0) || (optionData->lookupMode != '\0')) ||
                         ((int)(wordLength + prefixCount) <= 1)) ||
                        (0x40 < (int)(wordLength + prefixCount))) goto emitCandidate;
@@ -1195,24 +1195,24 @@
 emitCandidate:
                     if (firstCandidate == 0) {
-                      if (((ZiAlphaOptions*)optionData)->countOnly != '\0') {
-                        if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
-                          if ((int)((ZiAlphaOptions*)optionData)->shortestWord > (int)(wordLength + prefixCount)) {
-                            ((ZiAlphaOptions*)optionData)->shortestWord = wordLength + prefixCount;
+                      if (optionData->countOnly != '\0') {
+                        if (optionData->suffixOnly != '\0') {
+                          if ((int)optionData->shortestWord > (int)(wordLength + prefixCount)) {
+                            optionData->shortestWord = wordLength + prefixCount;
                           }
-                          if ((int)((ZiAlphaOptions*)optionData)->longestWord < (int)(wordLength + prefixCount)) {
-                            ((ZiAlphaOptions*)optionData)->longestWord = wordLength + prefixCount;
+                          if ((int)optionData->longestWord < (int)(wordLength + prefixCount)) {
+                            optionData->longestWord = wordLength + prefixCount;
                           }
                         }
                         candidateCount = candidateCount + 1;
-                        if (((ZiAlphaOptions*)optionData)->maxResults <= candidateCount) goto finishCandidates;
+                        if (optionData->maxResults <= candidateCount) goto finishCandidates;
                       } else {
-                        if (((ZiAlphaOptions*)optionData)->lookupMode != '\0') {
+                        if (optionData->lookupMode != '\0') {
                           for (index = 0; index <= wordLength; index++) {
-                            if (wordCursor[index] != ((ZiAlphaOptions*)optionData)->dictionary[index]) break;
+                            if (wordCursor[index] != optionData->dictionary[index]) break;
                           }
-                          if ((((((ZiAlphaWork*)workData)->operation != '\0') || (index >= wordLength))
-                              && ((((ZiAlphaWork*)workData)->operation == '\0' ||
+                          if ((((workData->operation != '\0') || (index >= wordLength))
+                              && ((workData->operation == '\0' ||
                                   ((exactLengthOnly == 0 ||
-                                   (index >= (int)(ziU16)Zi8WCharCount(((ZiAlphaOptions*)optionData)->dictionary,workData))))))) &&
+                                   (index >= (int)(ziU16)Zi8WCharCount(optionData->dictionary,workData))))))) &&
                              ((exactLengthOnly != 0 || (index >= wordLength)))) {
                             candidateCount = 1;
@@ -1220,81 +1220,81 @@
                           }
                         } else {
-                          if (((((ZiAlphaWork*)workData)->suffixMode == '\0') && (wordCursor[1] == 0)) &&
+                          if (((workData->suffixMode == '\0') && (wordCursor[1] == 0)) &&
                              (candidateCount == 0)) {
                             if (*wordCursor >= 0xeff1 && *wordCursor <= 0xf010) {
-                              ((ZiAlphaWork*)workData)->singleCharacter = 0;
+                              workData->singleCharacter = 0;
                             }
                             else {
-                              ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
+                              workData->singleCharacter = *wordCursor;
                             }
                           }
                           if (dictionaryExact != 0 &&
-                              parameters->elementCount == ((ZiAlphaWork*)workData)->rememberedCount &&
+                              parameters->elementCount == workData->rememberedCount &&
                               (parameters->maxCandidates == 1 ||
                                (candidateCount == 0 && parameters->firstCandidate == 0))) {
                             for (index = 0; (int)index < (int)prefixCount; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[index]
+                              workData->rememberedWord[index]
                                    = wordCursor[index - prefixCount];
                             }
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] =
+                              workData->rememberedWord[index + prefixCount] =
                                    wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] = 0;
+                            workData->rememberedWord[index + prefixCount] = 0;
                           }
                           else {
-                            if (((dictionaryExact == 0) && (parameters->elementCount == ((ZiAlphaWork*)workData)->rememberedCount))
+                            if (((dictionaryExact == 0) && (parameters->elementCount == workData->rememberedCount))
                                && ((parameters->maxCandidates == 1 ||
                                    ((candidateCount == 0 && (parameters->firstCandidate == 0)))))) {
-                              ((ZiAlphaWork*)workData)->rememberedWord[0] = 0;
+                              workData->rememberedWord[0] = 0;
                             }
                           }
-                          if ((((ZiAlphaWork*)workData)->suffixMode == '\0') &&
-                             ((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                 ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
-                                ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)))) ||
-                               ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0)))) &&
+                          if ((workData->suffixMode == '\0') &&
+                             ((((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                 ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0)))) ||
+                                ((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0)))) ||
+                               ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0)))) &&
                               ((parameters->maxCandidates == 1 ||
                                ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
+                              workData->prefix[index] = wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->prefixCount = wordLength;
-                            ((ZiAlphaWork*)workData)->language = language;
+                            workData->prefixCount = wordLength;
+                            workData->language = language;
                           }
-                          else if ((((ZiAlphaWork*)workData)->suffixLocked == '\0') &&
-                                  (((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                       ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0))))
-                                      || ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0))))
-                                     || ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))
-                                    && (((ZiAlphaWork*)workData)->language == language)) &&
+                          else if ((workData->suffixLocked == '\0') &&
+                                  (((((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                       ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0))))
+                                      || ((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0))))
+                                     || ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0))))
+                                    && (workData->language == language)) &&
                                    ((parameters->maxCandidates == 1 ||
                                     ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                             if (wordLength == parameters->elementCount) {
                               for (index = 0; index < (int)wordLength; index = index + 1) {
-                                ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
+                                workData->prefix[index] = wordCursor[index];
                               }
-                              ((ZiAlphaWork*)workData)->prefixCount = wordLength;
+                              workData->prefixCount = wordLength;
                             }
                             else {
                               for (index = 0; index < (int)wordLength; index = index + 1) {
-                                ((ZiAlphaWork*)workData)->suffix[index] = wordCursor[index];
+                                workData->suffix[index] = wordCursor[index];
                               }
-                              ((ZiAlphaWork*)workData)->suffixCount = wordLength;
+                              workData->suffixCount = wordLength;
                             }
                           }
-                          else if ((((ZiAlphaWork*)workData)->suffixMode != '\0') &&
-                                  (((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
-                                     ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
-                                    (((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)) ||
-                                     ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))))
-                                   && ((((ZiAlphaWork*)workData)->language != language &&
+                          else if ((workData->suffixMode != '\0') &&
+                                  (((((dictionaryKind == 1 && ((workData->dictionaryFlags & 1) != 0)) ||
+                                     ((dictionaryKind == 3 && ((workData->dictionaryFlags & 2) != 0)))) ||
+                                    (((dictionaryKind == 2 && ((workData->dictionaryFlags & 4) != 0)) ||
+                                     ((dictionaryKind == 4 && ((workData->dictionaryFlags & 8) != 0))))))
+                                   && ((workData->language != language &&
                                        ((parameters->maxCandidates == 1 ||
                                         ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))
                                    ))) {
                             for (index = 0; index < (int)wordLength; index = index + 1) {
-                              ((ZiAlphaWork*)workData)->alternatePrefix[index] = wordCursor[index];
+                              workData->alternatePrefix[index] = wordCursor[index];
                             }
-                            ((ZiAlphaWork*)workData)->alternatePrefixCount = (ziU8)index;
+                            workData->alternatePrefixCount = (ziU8)index;
                           }
                           wordLength = wordLength + 1;
@@ -1311,5 +1311,5 @@
                           }
                           else {
-                            if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
+                            if (optionData->suffixOnly != '\0') {
                               wordCursor = wordCursor - prefixCount;
                               wordCapacity = wordCapacity + prefixCount;
@@ -1335,21 +1335,21 @@
                           }
                           if (prefixCount != 0) {
-                            if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
+                            if ((optionData->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
                               wordCursor = candidateWord;
                               wordCapacity = 0x40;
                             }
-                            for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount;
+                            for (index = 0; index < (int)(unsigned int)workData->prefixCount;
                                 index = index + 1) {
-                              wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
+                              wordCursor[index] = workData->prefix[index];
                             }
-                            wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
-                            wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
-                            if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-                              for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount;
+                            wordCursor = wordCursor + workData->prefixCount;
+                            wordCapacity = wordCapacity - workData->prefixCount;
+                            if (workData->suffixLocked != '\0') {
+                              for (index = 0; index < (int)(unsigned int)workData->suffixCount;
                                   index = index + 1) {
-                                wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
+                                wordCursor[index] = workData->suffix[index];
                               }
-                              wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
-                              wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
+                              wordCursor = wordCursor + workData->suffixCount;
+                              wordCapacity = wordCapacity - workData->suffixCount;
                             }
                           }
@@ -1380,5 +1380,5 @@
   if (((candidateCount == 0) && (punctuationCandidate)) && (firstCandidate == 0)) {
     candidateCount = 1;
-    if (((ZiAlphaOptions*)optionData)->countOnly != 0 || (parameters->getOptions & 0xFD) == 0x81) {
+    if (optionData->countOnly != 0 || (parameters->getOptions & 0xFD) == 0x81) {
       if (parameters->getMode == 1) {
         *wordCursor = *elements;
@@ -1392,6 +1392,6 @@
       encodedOutput[1] = encodedOutput[2] = 0;
     }
-    if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
-      ((ZiAlphaWork*)workData)->singleCharacter = 0;
+    if (optionData->lookupMode == '\0') {
+      workData->singleCharacter = 0;
     }
   }
@@ -1416,5 +1416,5 @@
     goto prepareDictionaries;
   }
-  language = ((ZiAlphaWork*)workData)->language;
+  language = workData->language;
   if (language == 0) {
     language = parameters->language;
@@ -1427,28 +1427,28 @@
     currentVowelRestriction = secondaryVowelRestriction;
   }
-  if ((((ZiAlphaOptions*)optionData)->lookupMode != '\0') || ((!completionAllowed && (!currentVowelRestriction)))) goto finishCandidates;
+  if ((optionData->lookupMode != '\0') || ((!completionAllowed && (!currentVowelRestriction)))) goto finishCandidates;
   if ((currentVowelRestriction) &&
-     ((((((ZiAlphaWork*)workData)->suffixMode == '\0' && (2 < (int)elementCount)) &&
+     ((((workData->suffixMode == '\0' && (2 < (int)elementCount)) &&
        (elements[elementCount - 2] == 0xeff1)) &&
-      ((int)((ZiAlphaWork*)workData)->prefixCount == elementCount - 2)))) {
-    ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->prefixCount + '\x01';
-    ((ZiAlphaWork*)workData)->suffixMode = 1;
-  }
-  if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (!prefixPrepared)) {
+      ((int)workData->prefixCount == elementCount - 2)))) {
+    workData->prefixElementCount = workData->prefixCount + '\x01';
+    workData->suffixMode = 1;
+  }
+  if ((workData->suffixMode != '\0') && (!prefixPrepared)) {
     prefixPrepared = ZI8_TRUE;
     goto preparePrefix;
   }
-  if (currentVowelRestriction && ((ZiAlphaWork*)workData)->suffixMode != 0 &&
-      ((ZiAlphaWork*)workData)->suffixLocked == 0 && elementCount > 2 &&
+  if (currentVowelRestriction && workData->suffixMode != 0 &&
+      workData->suffixLocked == 0 && elementCount > 2 &&
       ((elements[elementCount - 2] == 0xEFF1 &&
-        ((ZiAlphaWork*)workData)->suffixCount == elementCount - 2) ||
-       (((ZiAlphaWork*)workData)->suffixCount == elementCount - 1 &&
+        workData->suffixCount == elementCount - 2) ||
+       (workData->suffixCount == elementCount - 1 &&
         Zi8IsAlphaPunct(elements[elementCount - 1]) != 0))) {
-    if (((ZiAlphaWork*)workData)->prefixEnabled >= 1 && elements[elementCount - 1] == 0xEFF1) {
+    if (workData->prefixEnabled >= 1 && elements[elementCount - 1] == 0xEFF1) {
       goto checkPrefixPunctuation;
     }
     if (!primaryMatched && !secondaryMatched) {
-      ((ZiAlphaWork*)workData)->suffixLocked = 1;
-      ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount - 1;
+      workData->suffixLocked = 1;
+      workData->suffixElementCount = parameters->elementCount - 1;
       if (prefixCount != 0) {
         wordCursor -= prefixCount;
@@ -1461,14 +1461,14 @@
     }
   }
-  if ((prefixPrepared) && (1 < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
+  if ((prefixPrepared) && (1 < workData->alternatePrefixCount)) {
     if (language == parameters->language) {
       if (primaryMatched) {
-        ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->alternatePrefixCount = 0;
       }
     }
     else if (secondaryMatched) {
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
-    }
-    if (((ZiAlphaWork*)workData)->alternatePrefixCount != '\0') {
+      workData->alternatePrefixCount = 0;
+    }
+    if (workData->alternatePrefixCount != '\0') {
       wordCursor -= prefixCount;
       elements -= prefixCount;
@@ -1477,19 +1477,19 @@
       prefixCount = 0;
       prefixPrepared = ZI8_FALSE;
-      ((ZiAlphaWork*)workData)->suffixMode = 0;
-      ((ZiAlphaWork*)workData)->suffixLocked = 0;
-      ((ZiAlphaWork*)workData)->suffixCount = 0;
-      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->alternatePrefixCount; index = index + 1) {
-        ((ZiAlphaWork*)workData)->prefix[index] =
-             ((ZiAlphaWork*)workData)->alternatePrefix[index];
-      }
-      ((ZiAlphaWork*)workData)->prefixCount = (ziU8)index;
-      if (((ZiAlphaWork*)workData)->language == parameters->language) {
-        ((ZiAlphaWork*)workData)->language = parameters->subLanguage;
+      workData->suffixMode = 0;
+      workData->suffixLocked = 0;
+      workData->suffixCount = 0;
+      for (index = 0; index < (int)(unsigned int)workData->alternatePrefixCount; index = index + 1) {
+        workData->prefix[index] =
+             workData->alternatePrefix[index];
+      }
+      workData->prefixCount = (ziU8)index;
+      if (workData->language == parameters->language) {
+        workData->language = parameters->subLanguage;
       }
       else {
-        ((ZiAlphaWork*)workData)->language = parameters->language;
-      }
-      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
+        workData->language = parameters->language;
+      }
+      workData->alternatePrefixCount = 0;
     }
   }
@@ -1499,15 +1499,15 @@
   if (currentVowelRestriction) {
 checkPrefixPunctuation:
-    if ((1 < ((ZiAlphaWork*)workData)->prefixEnabled) &&
+    if ((1 < workData->prefixEnabled) &&
        (parameters->elements[parameters->elementCount - 1] != 0xEFF1))
     goto finishCandidates;
     if ((((*elements == 0xeff1) ||
          ((ZiIsLetterHyphen(*elements,workData)) != '\0')) &&
-        ((((ZiAlphaWork*)workData)->suffixLocked == '\0' ||
-         ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
+        ((workData->suffixLocked == '\0' ||
+         ((ZiIsLetterHyphen(workData->suffix[(workData->suffixCount - 1)],
                                     workData)) == '\0')))) &&
-       (((((ZiAlphaWork*)workData)->suffixMode == '\0' ||
-         ((((ZiAlphaWork*)workData)->suffixLocked != '\0' ||
-          ((ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
+       (((workData->suffixMode == '\0' ||
+         ((workData->suffixLocked != '\0' ||
+          ((ZiIsLetterHyphen(workData->prefix[workData->prefixCount - 1],
                                      workData)) == '\0')))) &&
         ((((Zi8GetTableCount(language,0x1f,workData)) & 8) == 0 &&
@@ -1520,31 +1520,31 @@
         prefixCount = 0;
       }
-      if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
-        ((ZiAlphaWork*)workData)->previousSuffixCount = ((ZiAlphaWork*)workData)->suffixElementCount;
-        ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount;
-        elementIndex = (int)((ZiAlphaWork*)workData)->prefixCount + (int)((ZiAlphaWork*)workData)->suffixCount;
+      if (workData->suffixLocked != '\0') {
+        workData->previousSuffixCount = workData->suffixElementCount;
+        workData->suffixElementCount = parameters->elementCount;
+        elementIndex = (int)workData->prefixCount + (int)workData->suffixCount;
         if (elements[elementIndex] != 0xEFF1 && Zi8IsAlphaPunct(elements[elementIndex]) != 0) {
-          ((ZiAlphaWork*)workData)->suffix[((ZiAlphaWork*)workData)->suffixCount++] = elements[elementIndex];
+          workData->suffix[workData->suffixCount++] = elements[elementIndex];
         } else {
-          ((ZiAlphaWork*)workData)->suffix[((ZiAlphaWork*)workData)->suffixCount++] = ((ZiAlphaWork*)workData)->letterHyphen;
+          workData->suffix[workData->suffixCount++] = workData->letterHyphen;
         }
         prefixPrepared = ZI8_TRUE;
       } else {
-        ((ZiAlphaWork*)workData)->previousPrefixCount = ((ZiAlphaWork*)workData)->prefixElementCount;
-        ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
-        if (((ZiAlphaWork*)workData)->suffixMode == '\0') {
-          ((ZiAlphaWork*)workData)->suffixMode = 1;
-          ((ZiAlphaWork*)workData)->prefixCount = 0;
-        }
-        if (((((((ZiAlphaWork*)workData)->prefixCount == '\x03') && (((ZiAlphaWork*)workData)->prefix[0] == 0x77)) &&
-             (((ZiAlphaWork*)workData)->prefix[1] == 0x77)) && (((ZiAlphaWork*)workData)->prefix[2] == 0x77)) ||
+        workData->previousPrefixCount = workData->prefixElementCount;
+        workData->prefixElementCount = parameters->elementCount;
+        if (workData->suffixMode == '\0') {
+          workData->suffixMode = 1;
+          workData->prefixCount = 0;
+        }
+        if (((((workData->prefixCount == '\x03') && (workData->prefix[0] == 0x77)) &&
+             (workData->prefix[1] == 0x77)) && (workData->prefix[2] == 0x77)) ||
            (((Zi8GetTableCount(language,0x1f,workData)) & 0x100) != 0)) {
-          ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
-        }
-        if (elements[((ZiAlphaWork*)workData)->prefixCount] != 0xEFF1 && Zi8IsAlphaPunct(elements[((ZiAlphaWork*)workData)->prefixCount]) != 0) {
-          ((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount] = elements[((ZiAlphaWork*)workData)->prefixCount];
-          ((ZiAlphaWork*)workData)->prefixCount++;
+          workData->letterHyphen = 0x2e;
+        }
+        if (elements[workData->prefixCount] != 0xEFF1 && Zi8IsAlphaPunct(elements[workData->prefixCount]) != 0) {
+          workData->prefix[workData->prefixCount] = elements[workData->prefixCount];
+          workData->prefixCount++;
         } else {
-          ((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount++] = ((ZiAlphaWork*)workData)->letterHyphen;
+          workData->prefix[workData->prefixCount++] = workData->letterHyphen;
         }
         prefixPrepared = ZI8_TRUE;
@@ -1553,22 +1553,22 @@
     }
   }
-  if (!completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && ((ZiAlphaWork*)workData)->prefixCount != 0 &&
-      elementCount > 2 && ((ZiAlphaWork*)workData)->prefixCount == elementCount - 1 &&
-      Zi8IsAlphaPunct(parameters->elements[((ZiAlphaWork*)workData)->prefixCount - 1]) != 0) goto checkPrefixFields;
-  if (!completionAllowed && ((ZiAlphaWork*)workData)->suffixMode == 0 && parameters->elementCount > 1 &&
+  if (!completionAllowed && workData->suffixMode == 0 && workData->prefixCount != 0 &&
+      elementCount > 2 && workData->prefixCount == elementCount - 1 &&
+      Zi8IsAlphaPunct(parameters->elements[workData->prefixCount - 1]) != 0) goto checkPrefixFields;
+  if (!completionAllowed && workData->suffixMode == 0 && parameters->elementCount > 1 &&
       Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1]) == 0) goto finishCandidates;
 checkPrefixFields:
-  prefixMode = ((ZiAlphaWork*)workData)->suffixMode;
-  prefixLength = ((ZiAlphaWork*)workData)->prefixCount;
+  prefixMode = workData->suffixMode;
+  prefixLength = workData->prefixCount;
   if (prefixMode != 0 || prefixLength == 0 || elementCount <= 2 ||
       prefixLength != elementCount - 1 || parameters->elements[parameters->elementCount - 1] == 0xEFF1) goto finishCandidates;
-  ((ZiAlphaWork*)workData)->suffixMode = 1;
-  ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
+  workData->suffixMode = 1;
+  workData->prefixElementCount = parameters->elementCount;
   prefixPrepared = ZI8_TRUE;
   goto preparePrefix;

 finishCandidates:
-              ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
-              if (((ZiAlphaOptions*)optionData)->countOnly != '\0') {
+              workData->usePrefixAsElements = 0;
+              if (optionData->countOnly != '\0') {
                 parameters->letters = 0;
               }
@@ -1577,8 +1577,8 @@
               }
               wordCursor[-prefixCount] = 0;
-              if (((((ZiAlphaOptions*)optionData)->countOnly == '\0') && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (parameters->elementCount != 0)) {
+              if (((optionData->countOnly == '\0') && (optionData->lookupMode == '\0')) && (parameters->elementCount != 0)) {
                 elementIndex = parameters->elementCount - 1;
                 if (((primaryVowelRestriction) || (secondaryVowelRestriction)) &&
-                   ((((ZiAlphaWork*)workData)->prefixEnabled <= 1 ||
+                   ((workData->prefixEnabled <= 1 ||
                     (parameters->elements[elementIndex] == 0xEFF1)))) {
                   index = 0;
@@ -1589,12 +1589,12 @@
                   }
                   if (index != 0) {
-                    ((ZiAlphaWork*)workData)->prefixEnabled = (ziU8)index;
+                    workData->prefixEnabled = (ziU8)index;
                   } else {
                     if (candidateCount != 0) {
-                      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
-                      ((ZiAlphaWork*)workData)->requiredLength = 0;
+                      workData->prefixEnabled = 0;
+                      workData->requiredLength = 0;
                     }
                   }
-                  ((ZiAlphaWork*)workData)->requiredLength = parameters->elementCount;
+                  workData->requiredLength = parameters->elementCount;
                 }
                 if ((parameters->letters != 0) && (parameters->maxCandidates == 1)) {
@@ -1617,17 +1617,17 @@
                 }
               }
-              if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
-                if ((int)dictionaryIndex >= (int)((ZiAlphaWork*)workData)->dictionaryCount) {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[((ZiAlphaWork*)workData)->dictionaryCount - 1] = candidateCount;
+              if (workData->dictionaryCounts != 0) {
+                if ((int)dictionaryIndex >= (int)workData->dictionaryCount) {
+                  workData->dictionaryCounts[workData->dictionaryCount - 1] = candidateCount;
                 } else {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex] = candidateCount;
+                  workData->dictionaryCounts[dictionaryIndex] = candidateCount;
                 }
                 countIndex = dictionaryIndex;
-                if (countIndex >= ((ZiAlphaWork*)workData)->dictionaryCount) {
-                  countIndex = ((ZiAlphaWork*)workData)->dictionaryCount - 1;
+                if (countIndex >= workData->dictionaryCount) {
+                  countIndex = workData->dictionaryCount - 1;
                 }
                 for (; countIndex >= 1; countIndex = countIndex - 1) {
-                  ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex] -=
-                       ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex - 1];
+                  workData->dictionaryCounts[countIndex] -=
+                       workData->dictionaryCounts[countIndex - 1];
                 }
               }
```
{"unit": "zi8alpha", "function": "Zi8AlphaGetCandidates", "trial": "Alpha options and workspace both use native record formals at every field read", "sha": "0633912127b6", "build": 0, "insns": [3946, 3946], "diffs": 3758, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [7, ["mr", "r31, r5"], ["mr", "r30, r5"]], [17, ["stw", "r0, 0xa8(r1)"], ["stw", "r0, 0xac(r1)"]], [18, ["li", "r0, 0"], ["li", "r4, 0"]], [19, ["stw", "r0, 0xa4(r1)"], ["stw", "r4, 0xa8(r1)"]], [21, ["stw", "r3, 0xa0(r1)"], ["stw", "r3, 0xa4(r1)"]], [22, ["li", "r3, 0"], ["li", "r4, 0"]], [23, ["stw", "r3, 0x9c(r1)"], ["stw", "r4, 0xa0(r1)"]], [24, ["li", "r5, 0"], ["li", "r6, 0"]], [25, ["stw", "r5, 0x98(r1)"], ["stw", "r6, 0x9c(r1)"]]]}
Objdiff {"measures": {"fuzzy_match_percent": 96.03545, "total_code": "21664", "matched_code": "5880", "matched_code_percent": 27.141804, "total_data": "564", "matched_data": "516", "matched_data_percent": 91.489365, "total_functions": 12, "matched_functions": 11, "matched_functions_percent": 91.66667, "total_units": 1}, "gains": [], "regressions": [], "open": [["Zi8AlphaGetCandidates", 94.55854]]}

## Dead-store audit and scope closeout
The latest max-round task focused on a few smallest differences. High/xhigh already tried every other open function at least three times, with full diffs in the untracked a7h/a7x logs. Their attempts were read and were not relaunched as new trials.
zconvert/Zi8ConvertUC2Key: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
zi81key/Zi8SpellingZY: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
zi81key/Zi8SpellingPY: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
zi8match/Zi8GetPyFinal: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
zi8uwd/Zi8_81480224: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
zmtkey/Zi8getKeyLayout: no unmatched never-read scalar stack store to add; target-only stores after prologue scan: [].
Alpha target stores the workspace at +0x15c to 0x20(r1) with no scalar read of that slot; Prepare writes its componentPresent byte at +0x48 and +0x124 to 0x0f(r1). These exact stores were already reconstructed in medium and retried in xhigh, still nonexact. No repeat of those trials, unsupported stores, or new uninitialized values in this round. All guarded header/type experiments restored; the retained change is the five-line native-workspace configuration in zconvert only.
tools/decomp-assist/a7h.attempts.md: preserved SHA256 33df48be7b658d6462b675e54b5cb7e9fb0cb493e4a238fc30b00f2c4913f39f
tools/decomp-assist/a7x.attempts.md: preserved SHA256 fe0e3240fc6280cc4e24d8491af1d8e43e1ab2874377e1fce72f518974b1edfe
Local exact commit d083f43d. All four zconvert functions and every section are exact; link status deliberately remains NonMatching per the matching-only phase. Parent must independently verify before promotion.

## Final full clean gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] objdiff: code 6360/6888 data 332/332 functions 15/17 fuzzy 99.9506 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] instruction-exact functions: 15/17
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .data size 80 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .rodata size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .text size 6888 match 99.95064
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section extab size 88 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section extabindex size 132 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   below 100: Zi8GetDataSignature 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   below 100: Zi8IsDupWChar 99.36508
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] baseline: code 6360/6888 data 332 functions 15 fuzzy 99.9506
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] objdiff: code 888/1664 data 80/80 functions 4/6 fuzzy 99.7115 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] instruction-exact functions: 4/6
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section .text size 1664 match 99.71154
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   below 100: ZiDAWGgetCHARattribute 99.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   below 100: ZiDAWGGetGraphInfo 99.55224
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] baseline: code 888/1664 data 80 functions 4 fuzzy 99.7115
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] objdiff: code 208/976 data 60/60 functions 2/3 fuzzy 98.9344 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] instruction-exact functions: 2/3
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section .text size 976 match 98.934425
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   below 100: Zi8MatchOEMdata 98.645836
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] baseline: code 208/976 data 60 functions 2 fuzzy 98.9344
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] objdiff: code 332/5200 data 96/180 functions 1/7 fuzzy 98.7462 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] instruction-exact functions: 1/7
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .data size 40 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .text size 5200 match 98.746155
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extab size 56 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extabindex size 84 match 97.61904
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_8148302C 99.49152
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483264 98.902435
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483308 99.13793
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814833F0 99.04256
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814834AC 99.3586
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8GetKOcandidates 98.146484
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] baseline: code 332/5200 data 96 functions 1 fuzzy 98.7462
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] objdiff: code 2192/2656 data 80/80 functions 3/4 fuzzy 99.9172 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section .text size 2656 match 99.91717
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   below 100: Zi8_81480224 99.52586
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] baseline: code 2192/2656 data 80 functions 3 fuzzy 99.9172
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 2208/2208 data 112/112 functions 4/4 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 4/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
[libs/RVLMiddleware/eZiText/src/clib/zi81key] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi81key] objdiff: code 3952/21460 data 1280/1388 functions 5/9 fuzzy 98.2352 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi81key] instruction-exact functions: 5/9
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .data size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .rodata size 1152 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section .text size 21460 match 98.23523
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   section extabindex size 108 match 98.14815
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingZY 99.756096
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8SpellingPY 99.36306
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressSpelling 99.555885
[libs/RVLMiddleware/eZiText/src/clib/zi81key]   below 100: Zi8Get1KeyPressCandidates 96.41927
[libs/RVLMiddleware/eZiText/src/clib/zi81key] baseline: code 3952/21460 data 1280 functions 5 fuzzy 98.2352
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] objdiff: code 5880/21664 data 516/564 functions 11/12 fuzzy 96.5247 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] instruction-exact functions: 11/12
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .rodata size 336 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .text size 21664 match 96.52474
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extabindex size 108 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   below 100: Zi8AlphaGetCandidates 95.23011
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] baseline: code 5880/21664 data 516 functions 11 fuzzy 96.5247
[libs/RVLMiddleware/eZiText/src/clib/zprepare] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zprepare] objdiff: code None/3760 data 8/68 functions 0/1 fuzzy 96.8021 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zprepare] instruction-exact functions: 0/1
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .text size 3760 match 96.802124
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extab size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extabindex size 12 match 91.66667
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   below 100: Zi8PrepareMatch 96.802124
[libs/RVLMiddleware/eZiText/src/clib/zprepare] baseline: code None/3760 data 8 functions 0 fuzzy 96.8021
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.6547 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 96.65468
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 96.27482
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.6547
[libs/RVLMiddleware/eZiText/src/clib/zi8match] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8match] objdiff: code 8044/8256 data 728/728 functions 9/10 fuzzy 99.9806 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8match] instruction-exact functions: 9/10
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section .rodata size 528 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section .text size 8256 match 99.98062
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section extab size 80 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section extabindex size 120 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   below 100: Zi8GetPyFinal 99.245285
[libs/RVLMiddleware/eZiText/src/clib/zi8match] baseline: code 8044/8256 data 728 functions 9 fuzzy 99.9806
regressions vs baseline: 0
global matched_code_percent: 92.38495 -> 92.41260
global fuzzy_match_percent: 99.73445 -> 99.73458
global complete_code_percent: 74.91312 -> 74.91312
global matched_data_percent: 99.78196 -> 99.78196
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Fresh report and remaining functions
zi8getc2: exact 15/17 -> 15/17; code 6360 -> 6360/6888; data 332 -> 332/332.
OPEN zi8getc2/Zi8GetDataSignature: 99.347824%; 69/69 instructions, 9 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('mr', 'r28, r5'), ('mr', 'r29, r5')), (9, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r29, 0x18'))].
OPEN zi8getc2/Zi8IsDupWChar: 99.36508%; 63/63 instructions, 8 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('li', 'r28, 0'), ('li', 'r27, 0')), (14, ('sth', 'r27, 2(r31)'), ('sth', 'r28, 2(r31)'))].
zidawg1: exact 4/6 -> 4/6; code 888 -> 888/1664; data 80 -> 80/80.
OPEN zidawg1/ZiDAWGgetCHARattribute: 99.0%; 60/60 instructions, 12 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (14, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (18, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18'))].
OPEN zidawg1/ZiDAWGGetGraphInfo: 99.55224%; 134/134 instructions, 12 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r25, r3'), ('mr', 'r29, r3')), (8, ('mr', 'r3, r25'), ('mr', 'r3, r29')), (10, ('mr', 'r29, r3'), ('mr', 'r26, r3'))].
zoemdata: exact 2/3 -> 2/3; code 208 -> 208/976; data 60 -> 60/60.
OPEN zoemdata/Zi8MatchOEMdata: 98.645836%; 192/192 instructions, 47 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (6, ('mr', 'r26, r4'), ('mr', 'r27, r4')), (9, ('mr', 'r23, r7'), ('mr', 'r24, r7'))].
zkokeyp: exact 1/7 -> 1/7; code 332 -> 332/5200; data 96 -> 96/180.
OPEN zkokeyp/Zi8_8148302C: 99.49152%; 59/59 instructions, 6 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(7, ('mr', 'r27, r5'), ('mr', 'r29, r5')), (12, ('mr', 'r5, r27'), ('mr', 'r5, r29')), (32, ('clrlwi', 'r29, r0, 0x10'), ('clrlwi', 'r27, r0, 0x10'))].
OPEN zkokeyp/Zi8_81483264: 98.902435%; 41/41 instructions, 8 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (8, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (17, ('li', 'r31, 0'), ('li', 'r30, 0'))].
OPEN zkokeyp/Zi8_81483308: 99.13793%; 58/58 instructions, 9 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(7, ('mr', 'r29, r5'), ('mr', 'r30, r5')), (22, ('li', 'r30, 0'), ('li', 'r29, 0')), (26, ('clrlwi', 'r0, r30, 0x18'), ('clrlwi', 'r0, r29, 0x18'))].
OPEN zkokeyp/Zi8_814833F0: 99.04256%; 47/47 instructions, 8 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (13, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (22, ('li', 'r31, 0'), ('li', 'r30, 0'))].
OPEN zkokeyp/Zi8_814834AC: 99.3586%; 344/343 instructions, 329 positional differences; instruction count/control-flow differences remain; first differences [(9, ('mr', 'r25, r7'), ('mr', 'r26, r7')), (16, ('clrlwi', 'r0, r0, 0x18'), ('stb', 'r0, 0x20(r1)')), (17, ('stb', 'r0, 0x20(r1)'), ('li', 'r3, 0x64'))].
OPEN zkokeyp/Zi8GetKOcandidates: 98.146484%; 671/669 instructions, 639 positional differences; instruction count/control-flow differences remain; first differences [(15, ('li', 'r0, 0'), ('stb', 'r0, 0x3c(r1)')), (16, ('stb', 'r0, 0x3c(r1)'), ('li', 'r0, 0')), (17, ('li', 'r0, 0'), ('stb', 'r0, 0xe(r1)'))].
zmtkey: exact 3/4 -> 3/4; code 1488 -> 1488/2216; data 60 -> 60/60.
OPEN zmtkey/Zi8getKeyLayout: 99.53297%; 182/182 instructions, 16 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r26, r3'), ('mr', 'r27, r3')), (11, ('clrlwi', 'r3, r26, 0x18'), ('clrlwi', 'r3, r27, 0x18')), (21, ('clrlwi', 'r0, r26, 0x18'), ('clrlwi', 'r0, r27, 0x18'))].
zi8uwd: exact 3/4 -> 3/4; code 2192 -> 2192/2656; data 80 -> 80/80.
OPEN zi8uwd/Zi8_81480224: 99.52586%; 116/116 instructions, 9 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r26, r3'), ('mr', 'r28, r3')), (16, ('cmpwi', 'r26, 0'), ('cmpwi', 'r28, 0')), (24, ('lbz', 'r25, 2(r26)'), ('lbz', 'r25, 2(r28)'))].
zconvert: exact 3/4 -> 4/4; code 1380 -> 2208/2208; data 112 -> 112/112.
zi81key: exact 5/9 -> 5/9; code 3952 -> 3952/21460; data 1280 -> 1280/1388.
OPEN zi81key/Zi8SpellingZY: 99.756096%; 123/123 instructions, 6 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(27, ('lis', 'r7, 0'), ('lis', 'r6, 0')), (28, ('addi', 'r6, r7, 0'), ('addi', 'r6, r6, 0')), (35, ('slwi', 'r6, r0, 2'), ('slwi', 'r7, r0, 2'))].
OPEN zi81key/Zi8SpellingPY: 99.36306%; 157/157 instructions, 20 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(16, ('lis', 'r7, 0'), ('lis', 'r6, 0')), (17, ('addi', 'r6, r7, 0'), ('addi', 'r6, r6, 0')), (22, ('slwi', 'r6, r0, 2'), ('slwi', 'r7, r0, 2'))].
OPEN zi81key/Zi8Get1KeyPressSpelling: 99.555885%; 1701/1700 instructions, 770 positional differences; instruction count/control-flow differences remain; first differences [(40, ('b', 6620), ('b', 6616)), (60, ('rlwinm', 'r6, r3, 0, 0x1a, 0x1a'), ('rlwinm', 'r4, r3, 0, 0x1a, 0x1a')), (61, ('cmpwi', 'r6, 0'), ('cmpwi', 'r4, 0'))].
OPEN zi81key/Zi8Get1KeyPressCandidates: 96.41927%; 2405/2397 instructions, 2067 positional differences; instruction count/control-flow differences remain; first differences [(10, ('li', 'r3, 0'), ('li', 'r0, 0')), (11, ('stw', 'r3, 0x94(r1)'), ('stw', 'r0, 0x94(r1)')), (26, ('li', 'r4, 0'), ('li', 'r3, 0'))].
zi8alpha: exact 11/12 -> 11/12; code 5880 -> 5880/21664; data 516 -> 516/564.
OPEN zi8alpha/Zi8AlphaGetCandidates: 95.23011%; 3946/3946 instructions, 3738 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(17, ('stw', 'r0, 0xa8(r1)'), ('stw', 'r0, 0xac(r1)')), (18, ('li', 'r0, 0'), ('li', 'r4, 0')), (19, ('stw', 'r0, 0xa4(r1)'), ('stw', 'r4, 0xa8(r1)'))].
zprepare: exact 0/1 -> 0/1; code 0 -> 0/3760; data 8 -> 8/68.
OPEN zprepare/Zi8PrepareMatch: 96.802124%; 936/940 instructions, 891 positional differences; instruction count/control-flow differences remain; first differences [(11, ('li', 'r3, 0x20'), ('li', 'r0, 0x20')), (12, ('stb', 'r3, 0xb(r1)'), ('stb', 'r0, 0xb(r1)')), (17, ('li', 'r28, 0'), ('li', 'r0, 0'))].
zi8cgetc: exact 5/8 -> 5/8; code 4168 -> 4168/47816; data 144 -> 144/536.
OPEN zi8cgetc/ZiMatchZHSpelling: 98.80165%; 121/121 instructions, 29 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(5, ('mr', 'r27, r4'), ('mr', 'r28, r4')), (6, ('mr', 'r22, r5'), ('mr', 'r23, r5')), (7, ('mr', 'r23, r6'), ('mr', 'r24, r6'))].
OPEN zi8cgetc/zi8InternalGetZH: 96.27482%; 10676/10676 instructions, 9311 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(8, ('addi', 'r3, r1, 0x2d4'), ('addi', 'r7, r1, 0x2d4')), (9, ('li', 'r7, 0'), ('li', 'r6, 0')), (10, ('li', 'r6, 0x3d'), ('li', 'r5, 0x3d'))].
OPEN zi8cgetc/Zi8GetElementCount: 99.347824%; 115/115 instructions, 13 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(6, ('mr', 'r27, r4'), ('mr', 'r28, r4')), (11, ('clrlwi', 'r0, r27, 0x18'), ('clrlwi', 'r0, r28, 0x18')), (17, ('mr', 'r3, r27'), ('mr', 'r3, r28'))].
zi8match: exact 9/10 -> 9/10; code 8044 -> 8044/8256; data 728 -> 728/728.
OPEN zi8match/Zi8GetPyFinal: 99.245285%; 53/53 instructions, 8 positional differences; same instruction count; register/operand or stack layout remains different; first differences [(26, ('slwi', 'r6, r0, 3'), ('slwi', 'r7, r0, 3')), (27, ('lis', 'r7, 0'), ('lis', 'r6, 0')), (28, ('addi', 'r0, r7, 0'), ('addi', 'r0, r6, 0'))].
Owned totals before: {"matched_functions": 61, "total_functions": 85, "matched_code": 34892, "total_code": 124764, "matched_data": 3496, "total_data": 4188}; after: {"matched_functions": 62, "total_functions": 85, "matched_code": 35720, "total_code": 124764, "matched_data": 3496, "total_data": 4188}.
Final progress/report regeneration and build/43U/ok passed. Fresh ctxdiff on Zi8ConvertUC2Key: 207/207 instructions, diffs 0. SHA1 independently rechecked as 26116613f624061ba99c8d1a299aaa6efa85670d. The final clean gate reports zero regressions, zero net forbidden patterns and zero readability warnings. No source/config/header change survives outside zconvert.c.
New compiled trials: 39. Focused counts: Zi8SpellingZY 12; Zi8GetPyFinal 4; Zi8getKeyLayout 7; Zi8_81480224 3; Zi8ConvertUC2Key 3. The other probes applied the newly found native-workspace lever to sibling units. Failed/inapplicable type declarations are not counted. Earlier complete high/xhigh coverage is referenced rather than repeated. The only retained exact gain is Zi8ConvertUC2Key; zconvert reaches all-code/all-data 100 percent. Other units remain open, and parent verification is still required.

Handoff: origin/main advanced to 4de92186c8915cd5fe13f0f933f0b812eebbe556 during the round. Gate comparison used this leaf merge-base 5af01fa8b9ed69e08d153b6ecb6aae4eb43e9efb. No worker rebase performed; parent must validate on its current integration base. Trailing whitespace in captured trial diffs/compiler output was normalized in this log.
