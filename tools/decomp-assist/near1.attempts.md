# Near-miss sweep

Baseline HEAD: 29fe1efaf200c57ac4e229c08a373aece57983a1
Fetched origin/main before initial target check. Owned function sources unchanged versus origin/main.

Baseline libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL: instruction-exact 11/14; measures {'fuzzy_match_percent': 87.93594, 'total_code': '2248', 'matched_code': '1388', 'matched_code_percent': 61.74377, 'total_data': '112', 'matched_data': '112', 'matched_data_percent': 100.0, 'total_functions': 14, 'matched_functions': 11, 'matched_functions_percent': 78.57143, 'total_units': 1}. Pool identical. All owned unit data already 100%; no symbol rename or extent adjustment warranted.

Baseline libs/RevoEX/src/nwc24/NWC24Download: instruction-exact 25/30; measures {'fuzzy_match_percent': 99.15205, 'total_code': '12496', 'matched_code': '8140', 'matched_code_percent': 65.14085, 'total_data': '80', 'matched_data': '80', 'matched_data_percent': 100.0, 'total_functions': 30, 'matched_functions': 25, 'matched_functions_percent': 83.33333, 'total_units': 1}. Pool identical. All owned unit data already 100%; no symbol rename or extent adjustment warranted.

Baseline libs/RVL_SDK/src/fa/driver/sd_drv: instruction-exact 21/26; measures {'fuzzy_match_percent': 99.05442, 'total_code': '11760', 'matched_code': '8940', 'matched_code_percent': 76.02041, 'total_data': '3592', 'matched_data': '3592', 'matched_data_percent': 100.0, 'total_functions': 26, 'matched_functions': 21, 'matched_functions_percent': 80.769226, 'total_units': 1}. Pool identical. All owned unit data already 100%; no symbol rename or extent adjustment warranted.

Baseline libs/RVL_SDK/src/fa/pf_cache: instruction-exact 35/36; measures {'fuzzy_match_percent': 99.98648, 'total_code': '7396', 'matched_code': '6464', 'matched_code_percent': 87.3986, 'matched_data_percent': 100.0, 'total_functions': 36, 'matched_functions': 35, 'matched_functions_percent': 97.22222, 'complete_data_percent': 100.0, 'total_units': 1}. Pool identical. All owned unit data already 100%; no symbol rename or extent adjustment warranted.

Baseline src/scene/channelSelect/iplChannelObj: instruction-exact 54/56; measures {'fuzzy_match_percent': 99.992676, 'total_code': '10924', 'matched_code': '10144', 'matched_code_percent': 92.85976, 'total_data': '2216', 'matched_data': '2216', 'matched_data_percent': 100.0, 'total_functions': 56, 'matched_functions': 55, 'matched_functions_percent': 98.21429, 'total_units': 1}. Pool identical. All owned unit data already 100%; no symbol rename or extent adjustment warranted.

## NHTTPi_strnicmp: split char declarations
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: right local declared before left
instructions 51/51, structural/exact (2, 18); src 0xcc base 0xcc insns 51/51
diffs 18: [2, 3, 12, 13, 15, 17, 19, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    12 M extsb. r31, r6
       B extsb. r12, r6
    13 M extsb r12, r0
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: inline lower comparisons with upper bound first
instructions 47/51, structural/exact (6, 50); src 0xbc base 0xcc insns 47/51
--- replace mine 0:3 base 0:5
  M    0 li r10, 0x5a
  M    1 li r9, 0x41
  M    2 li r8, 0
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 10:12 base 12:14
  M   10 extsb. r11, r6
  M   11 extsb r12, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- insert mine 13:13 base 15:17
  B   15 cmpwi r31, 0
  B   16 bne 28
--- delete mine 14:16 base 18:18
  M   14 bne 28
  M   15 cmpwi r11, 0
--- replace mine 17:18 base 19:20
  M   17 cmpwi r12, 0
  B   19 cmpwi r31, 0
--- replace mine 21:22 base 23:34
  M   21 srawi r7, r10, 0x1f
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
--- replace mine 23:29 base 35:41
  M   23 subfc r0, r12, r10
  M   24 adde r7, r7, r6
  M   25 srawi r6, r12, 0x1f
  M   26 subfc r0, r9, r12
  M   27 adde r0, r6, r8
  M   28 and. r0, r7, r0
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
--- replace mine 31:42 base 43:44
  M   31 srawi r7, r10, 0x1f
  M   32 srwi r6, r11, 0x1f
  M   33 subfc r0, r11, r10
  M   34 adde r7, r7, r6
  M   35 srawi r6, r11, 0x1f
  M   36 subfc r0, r9, r11
  M   37 adde r0, r6, r8
  M   38 and. r0, r7, r0
  M   39 beq 8
  M   40 addi r11, r11, 0x20
  M   41 cmpw r11, r12
  B   43 cmpw r12, r31
--- insert mine 45:45 base 47:48
  B   47 lwz r31, 0xc(r1)
--- insert mine 46:46 base 49:50
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: inline lower comparisons normal order
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: nul test right first
instructions 51/51, structural/exact (2, 9); src 0xcc base 0xcc insns 51/51
diffs 9: [2, 3, 8, 9, 10, 11, 12, 13, 15]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r0, 0(r4)
       B lbz r6, 0(r3)
     9 M addi r4, r4, 1
       B addi r3, r3, 1
    10 M lbz r6, 0(r3)
       B lbz r0, 0(r4)
    11 M addi r3, r3, 1
       B addi r4, r4, 1
    12 M extsb. r31, r0
       B extsb. r12, r6
    13 M extsb r12, r6
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0

## NHTTPi_strnicmp: split nul condition with early continue
instructions 47/51, structural/exact (8, 39); src 0xbc base 0xcc insns 47/51
--- insert mine 2:2 base 2:3
  B    2 li r9, 0x5a
--- delete mine 3:4 base 4:4
  M    3 li r9, 0x5a
--- replace mine 7:8 base 7:8
  M    7 ble 144
  B    7 ble 160
--- insert mine 14:14 base 14:18
  B   14 beq 12
  B   15 cmpwi r31, 0
  B   16 bne 28
  B   17 cmpwi r12, 0
--- replace mine 42:43 base 46:47
  M   42 bdnz -136
  B   46 bdnz -152

NWC24iCheckDlHeaderConsistency: fetched origin/main; owned source identical and still non-exact. Stack frame 0x2c0 and task address 0xa8 match; only entry ordering differs: target materializes taskPointer before saving header/repair.

## NWC24iCheckDlHeaderConsistency: direct input arguments, remove aliases
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: taskPointer assignment before argument aliases
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: const header view local
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: task and pointer declarations after scalar declarations
instructions 212/212, structural/exact (2, 20); src 0x350 base 0x350 insns 212/212
diffs 20: [5, 6, 7, 8, 12, 21, 31, 52, 60, 70, 96, 101, 110, 131, 150, 158, 175, 194, 200, 202]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r30, r1, 0xa8
       B mr r29, r4
     8 M li r31, 0
       B li r30, 0
    12 M clrlwi r4, r31, 0x10
       B clrlwi r4, r30, 0x10
    21 M clrlwi r0, r31, 0x10
       B clrlwi r0, r30, 0x10
    31 M rlwinm r0, r31, 4, 0xc, 0x1b
       B rlwinm r0, r30, 4, 0xc, 0x1b
    52 M clrlwi r4, r31, 0x10
       B clrlwi r4, r30, 0x10
    60 M clrlwi r0, r31, 0x10
       B clrlwi r0, r30, 0x10
    70 M rlwinm r0, r31, 4, 0xc, 0x1b
       B rlwinm r0, r30, 4, 0xc, 0x1b
    96 M clrlwi r0, r31, 0x10
       B clrlwi r0, r30, 0x10
   101 M rlwinm r4, r31, 9, 7, 0x16
       B rlwinm r4, r30, 9, 7, 0x16
   110 M mr r3, r30
       B mr r3, r31
   131 M cmpwi r30, 0
       B cmpwi r31, 0
   150 M mr r3, r30
       B mr r3, r31
   158 M clrlwi r4, r31, 0x10
       B clrlwi r4, r30, 0x10
   175 M cmpwi r30, 0
       B cmpwi r31, 0
   194 M mr r3, r30
       B mr r3, r31
   200 M addi r31, r31, 1
       B addi r30, r30, 1
   202 M clrlwi r3, r31, 0x10
       B clrlwi r3, r30, 0x10

## NWC24iCheckDlHeaderConsistency: pointer const definition
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

pfd_sddrv_finalize: fetched origin/main; owned source identical and still non-exact. Frame 0x10 and all calls match. Final flags mask is delayed behind media_inserted store; target flags load uses r3 and completes mask/store before media_inserted.

## pfd_sddrv_finalize: clear media before flags
instructions 57/57, structural/exact (6, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stw r6, 0xc(r4)
       B stw r0, 0xc(r4)
    52 M stb r6, 0x18(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: flags compound mask assignment
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: local flags value before stores
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: local info pointer for final clears
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: reverse mask operand order
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: reverse final independent stores
instructions 57/57, structural/exact (10, 5); src 0xe4 base 0xe4 insns 57/57
diffs 5: [45, 47, 49, 50, 52]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stb r0, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    52 M stw r0, 0x10(r4)
       B stb r0, 0x18(r4)

PFCACHE_DoWriteNumSectorAndFreeIfNeeded: fetched origin/main; source identical, still non-exact. Frame 0x40 and 233 instructions match. Inline PFCACHE_RecordPageEndOverlap produces end_sector in r5 and sector load in r4; target wants reverse registers. Only helper caller is owned function. No volatile store/reload evidence.

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap sum direct, num_sector first
instructions 232/233, structural/exact (14, 106); src 0x3a0 base 0x3a4 insns 232/233
--- replace mine 39:40 base 39:40
  M   39 beq 684
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 668
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 524
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 508
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 496
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 488
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 364
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 156
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 148
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 132
  B  127 blt 136
--- replace mine 136:138 base 136:138
  M  136 lwz r4, 0x18(r30)
  M  137 addi r3, r31, -1
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 139:140 base 139:141
  M  139 subf r4, r4, r31
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 213:214 base 214:215
  M  213 bne -792
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap sum direct, sector first
instructions 232/233, structural/exact (14, 106); src 0x3a0 base 0x3a4 insns 232/233
--- replace mine 39:40 base 39:40
  M   39 beq 684
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 668
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 524
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 508
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 496
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 488
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 364
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 156
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 148
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 132
  B  127 blt 136
--- replace mine 136:138 base 136:138
  M  136 lwz r4, 0x18(r30)
  M  137 addi r3, r31, -1
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 139:140 base 139:141
  M  139 subf r4, r4, r31
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 213:214 base 214:215
  M  213 bne -792
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper last_sector declaration after num_overlap
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: inline helper const page view for sector load
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: last_sector return expression instead of local
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: compute end_sector in last_sector local
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

setLangPane: fetched origin/main; owned source identical and still non-exact. Frame 0x90 and all 195 instructions match. Both FindGroupByName results retained in r28 vs target r30, only the four mr/addi users differ. Previous loops end before each local group lifetime starts.

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: const group pointer view
BUILD FAIL bj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:8)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     677:  for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter(); it != group->GetPaneList().GetEndIter(); it++
#   Error:                                                                 ^
#   (10248) function call '[const nw4r::lyt::Group].GetPaneList()' does not
#   match
#   'nw4r::lyt::Group::GetPaneList()' (non-static)
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: group pointer const local
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: one outer shared group local
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: outer group declared before language locals
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: declare iterator before group, initialize in for
instructions 199/195, structural/exact (9, 86); src 0x31c base 0x30c insns 199/195
--- replace mine 112:114 base 112:113
  M  112 beq 116
  M  113 li r0, 0
  B  112 beq 108
--- delete mine 115:116 base 114:114
  M  115 stw r0, 0x2c(r1)
--- replace mine 118:119 base 116:117
  M  118 mr r28, r3
  B  116 mr r30, r3
--- replace mine 130:131 base 128:129
  M  130 addi r3, r28, 0xc
  B  128 addi r3, r30, 0xc
--- replace mine 140:141 base 138:139
  M  140 b 212
  B  138 b 204
--- replace mine 153:154 base 151:152
  M  153 beq 160
  B  151 beq 152
--- replace mine 160:162 base 158:159
  M  160 bne 116
  M  161 li r0, 0
  B  158 bne 108
--- delete mine 163:164 base 160:160
  M  163 stw r0, 0x28(r1)
--- replace mine 166:167 base 162:163
  M  166 mr r28, r3
  B  162 mr r30, r3
--- replace mine 178:179 base 174:175
  M  178 addi r3, r28, 0xc
  B  174 addi r3, r30, 0xc
--- replace mine 192:193 base 188:189
  M  192 blt -164
  B  188 blt -156

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper end_sector first argument
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper page argument last
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper cached sector declared before last_sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper reverse success addition operands
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper decrement remaining before increment success
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper accept sector components separately
instructions 232/233, structural/exact (14, 106); src 0x3a0 base 0x3a4 insns 232/233
--- replace mine 39:40 base 39:40
  M   39 beq 684
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 668
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 524
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 508
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 496
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 488
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 364
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 156
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 148
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 132
  B  127 blt 136
--- replace mine 136:138 base 136:138
  M  136 lwz r4, 0x18(r30)
  M  137 addi r3, r31, -1
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 139:140 base 139:141
  M  139 subf r4, r4, r31
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 213:214 base 214:215
  M  213 bne -792
  B  214 bne -796

## pfd_sddrv_finalize: load final flags through existing const accessor
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: mask clear in inline helper
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: mask clear helper pointer parameter
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: mask assignment inside nested scope local
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: use result for zero return and final stores
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overwrite helper end_sector with overlap
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper explicit subtraction before last_sector
BUILD FAIL /fa/pf_cache.o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_cache.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_cache.c
# ---------------------------------------
#     556:     pf_u32 last_sector = end_sector - 1;
#   Error:     ^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: start overlap sum with sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r26, r27
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: sum sector local on right
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r26, r27
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: sum with block-scoped end_sector argument
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## NHTTPi_strnicmp: for loop decrement clause
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: return zero at nul termination
instructions 51/51, structural/exact (5, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 21, 22, 47, 48]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    21 M li r3, 0
       B li r5, 0
    22 M b 104
       B b 100
    47 M mr r3, r5
       B lwz r31, 0xc(r1)
    48 M lwz r31, 0xc(r1)
       B mr r3, r5

## NHTTPi_strnicmp: signed char locals
instructions 53/51, structural/exact (7, 34); src 0xd4 base 0xcc insns 53/51
--- insert mine 2:2 base 2:3
  B    2 li r9, 0x5a
--- delete mine 3:4 base 4:4
  M    3 li r9, 0x5a
--- replace mine 7:8 base 7:8
  M    7 ble 168
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r31, r6
  M   13 extsb r12, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- insert mine 15:15 base 15:17
  B   15 cmpwi r31, 0
  B   16 bne 28
--- replace mine 16:17 base 18:19
  M   16 bne 28
  B   18 bne 20
--- delete mine 18:20 base 20:20
  M   18 bne 20
  M   19 cmpwi r12, 0
--- replace mine 22:23 base 22:33
  M   22 b 108
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
--- replace mine 33:46 base 43:44
  M   33 srawi r7, r31, 0x1f
  M   34 srwi r6, r31, 0x1f
  M   35 subfc r0, r11, r31
  M   36 extsb r12, r12
  M   37 adde r8, r7, r10
  M   38 srawi r7, r9, 0x1f
  M   39 subfc r0, r31, r9
  M   40 adde r0, r7, r6
  M   41 and. r0, r8, r0
  M   42 beq 8
  M   43 addi r31, r31, 0x20
  M   44 extsb r0, r31
  M   45 cmpw r0, r12
  B   43 cmpw r12, r31
--- replace mine 48:49 base 46:47
  M   48 bdnz -160
  B   46 bdnz -152

## NHTTPi_strnicmp: inline lower reversed relational operand left
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: inline lower reversed relational operand right
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: inline named lower bounds at function scope
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: inline boolean upper range locals
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: split lower assignment into separate scope
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: test mismatch right operand first
instructions 51/51, structural/exact (2, 3); src 0xcc base 0xcc insns 51/51
diffs 3: [2, 3, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    43 M cmpw r31, r12
       B cmpw r12, r31

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: extract shared visibility loop inline helper
instructions 153/195, structural/exact (77, 103); src 0x264 base 0x30c insns 153/195
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x70(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x74(r1)
  M    3 addi r11, r1, 0x70
  B    2 stw r0, 0x94(r1)
  B    3 addi r11, r1, 0x90
--- replace mine 12:13 base 12:13
  M   12 addi r4, r1, 0x27
  B   12 addi r4, r1, 0x3f
--- replace mine 22:23 base 22:23
  M   22 stw r3, 0x1c(r1)
  B   22 stw r3, 0x34(r1)
--- replace mine 26:27 base 26:27
  M   26 lwz r3, 0x1c(r1)
  B   26 lwz r3, 0x34(r1)
--- replace mine 37:38 base 37:38
  M   37 addi r3, r1, 0x20
  B   37 addi r3, r1, 0x38
--- replace mine 41:43 base 41:43
  M   41 lwz r27, 0x1c(r1)
  M   42 addi r4, r1, 0x20
  B   41 lwz r27, 0x34(r1)
  B   42 addi r4, r1, 0x38
--- replace mine 57:58 base 57:58
  M   57 stw r3, 0x18(r1)
  B   57 stw r3, 0x30(r1)
--- replace mine 59:60 base 59:60
  M   59 lwz r3, 0x18(r1)
  B   59 lwz r3, 0x30(r1)
--- replace mine 63:64 base 63:64
  M   63 addi r3, r1, 0x18
  B   63 addi r3, r1, 0x30
--- replace mine 66:67 base 66:67
  M   66 lwz r3, 0x1c(r1)
  B   66 lwz r3, 0x34(r1)
--- replace mine 69:74 base 69:74
  M   69 lwz r0, 0x18(r1)
  M   70 addi r4, r1, 0x10
  M   71 stw r3, 0x10(r1)
  M   72 addi r3, r1, 0x14
  M   73 stw r0, 0x14(r1)
  B   69 lwz r0, 0x30(r1)
  B   70 addi r4, r1, 0x20
  B   71 stw r3, 0x20(r1)
  B   72 addi r3, r1, 0x24
  B   73 stw r0, 0x24(r1)
--- replace mine 77:78 base 77:78
  M   77 lwz r26, 0x1c(r1)
  B   77 lwz r26, 0x34(r1)
--- replace mine 86:87 base 86:87
  M   86 addi r27, r1, 0x28
  B   86 addi r27, r1, 0x40
--- replace mine 98:99 base 98:99
  M   98 addi r3, r1, 0x1c
  B   98 addi r3, r1, 0x34
--- replace mine 103:108 base 103:108
  M  103 lwz r0, 0x1c(r1)
  M  104 addi r4, r1, 8
  M  105 stw r3, 8(r1)
  M  106 addi r3, r1, 0xc
  M  107 stw r0, 0xc(r1)
  B  103 lwz r0, 0x34(r1)
  B  104 addi r4, r1, 0x18
  B  105 stw r3, 0x18(r1)
  B  106 addi r3, r1, 0x1c
  B  107 stw r0, 0x1c(r1)
--- replace mine 112:113 base 112:113
  M  112 beq 24
  B  112 beq 108
--- insert mine 116:116 base 116:118
  B  116 mr r30, r3
  B  117 addi r3, r3, 0xc
--- replace mine 117:118 base 119:139
  M  117 b 120
  B  119 stw r3, 0x2c(r1)
  B  120 b 32
  B  121 lwz r3, 0x2c(r1)
  B  122 li r4, 1
  B  123 lwz r3, 8(r3)
  B  124 bl 0
  B  125 addi r3, r1, 0x2c
  B  126 li r4, 0
  B  127 bl 0
  B  128 addi r3, r30, 0xc
  B  129 bl 0
  B  130 lwz r0, 0x2c(r1)
  B  131 addi r4, r1, 0x10
  B  132 stw r3, 0x10(r1)
  B  133 addi r3, r1, 0x14
  B  134 stw r0, 0x14(r1)
  B  135 bl 0
  B  136 cmpwi r3, 0
  B  137 bne -64
  B  138 b 204
--- replace mine 130:131 base 151:152
  M  130 beq 68
  B  151 beq 152
--- replace mine 132:133 base 153:154
  M  132 addi r4, r1, 0x28
  B  153 addi r4, r1, 0x40
--- replace mine 137:138 base 158:159
  M  137 bne 24
  B  158 bne 108
--- insert mine 141:141 base 162:164
  B  162 mr r30, r3
  B  163 addi r3, r3, 0xc
--- insert mine 142:142 base 165:184
  B  165 stw r3, 0x28(r1)
  B  166 b 32
  B  167 lwz r3, 0x28(r1)
  B  168 li r4, 1
  B  169 lwz r3, 8(r3)
  B  170 bl 0
  B  171 addi r3, r1, 0x28
  B  172 li r4, 0
  B  173 bl 0
  B  174 addi r3, r30, 0xc
  B  175 bl 0
  B  176 lwz r0, 0x28(r1)
  B  177 addi r4, r1, 8
  B  178 stw r3, 8(r1)
  B  179 addi r3, r1, 0xc
  B  180 stw r0, 0xc(r1)
  B  181 bl 0
  B  182 cmpwi r3, 0
  B  183 bne -64
--- replace mine 146:148 base 188:190
  M  146 blt -72
  M  147 addi r11, r1, 0x70
  B  188 blt -156
  B  189 addi r11, r1, 0x90
--- replace mine 149:150 base 191:192
  M  149 lwz r0, 0x74(r1)
  B  191 lwz r0, 0x94(r1)
--- replace mine 151:152 base 193:194
  M  151 addi r1, r1, 0x70
  B  193 addi r1, r1, 0x90

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: extract find and visibility loop inline helper
instructions 151/195, structural/exact (80, 106); src 0x25c base 0x30c insns 151/195
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x70(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x74(r1)
  M    3 addi r11, r1, 0x70
  B    2 stw r0, 0x94(r1)
  B    3 addi r11, r1, 0x90
--- replace mine 12:13 base 12:13
  M   12 addi r4, r1, 0x27
  B   12 addi r4, r1, 0x3f
--- replace mine 22:23 base 22:23
  M   22 stw r3, 0x1c(r1)
  B   22 stw r3, 0x34(r1)
--- replace mine 26:27 base 26:27
  M   26 lwz r3, 0x1c(r1)
  B   26 lwz r3, 0x34(r1)
--- replace mine 37:38 base 37:38
  M   37 addi r3, r1, 0x20
  B   37 addi r3, r1, 0x38
--- replace mine 41:43 base 41:43
  M   41 lwz r27, 0x1c(r1)
  M   42 addi r4, r1, 0x20
  B   41 lwz r27, 0x34(r1)
  B   42 addi r4, r1, 0x38
--- replace mine 57:58 base 57:58
  M   57 stw r3, 0x18(r1)
  B   57 stw r3, 0x30(r1)
--- replace mine 59:60 base 59:60
  M   59 lwz r3, 0x18(r1)
  B   59 lwz r3, 0x30(r1)
--- replace mine 63:64 base 63:64
  M   63 addi r3, r1, 0x18
  B   63 addi r3, r1, 0x30
--- replace mine 66:67 base 66:67
  M   66 lwz r3, 0x1c(r1)
  B   66 lwz r3, 0x34(r1)
--- replace mine 69:74 base 69:74
  M   69 lwz r0, 0x18(r1)
  M   70 addi r4, r1, 0x10
  M   71 stw r3, 0x10(r1)
  M   72 addi r3, r1, 0x14
  M   73 stw r0, 0x14(r1)
  B   69 lwz r0, 0x30(r1)
  B   70 addi r4, r1, 0x20
  B   71 stw r3, 0x20(r1)
  B   72 addi r3, r1, 0x24
  B   73 stw r0, 0x24(r1)
--- replace mine 77:78 base 77:78
  M   77 lwz r26, 0x1c(r1)
  B   77 lwz r26, 0x34(r1)
--- replace mine 86:87 base 86:87
  M   86 addi r27, r1, 0x28
  B   86 addi r27, r1, 0x40
--- replace mine 98:99 base 98:99
  M   98 addi r3, r1, 0x1c
  B   98 addi r3, r1, 0x34
--- replace mine 103:108 base 103:108
  M  103 lwz r0, 0x1c(r1)
  M  104 addi r4, r1, 8
  M  105 stw r3, 8(r1)
  M  106 addi r3, r1, 0xc
  M  107 stw r0, 0xc(r1)
  B  103 lwz r0, 0x34(r1)
  B  104 addi r4, r1, 0x18
  B  105 stw r3, 0x18(r1)
  B  106 addi r3, r1, 0x1c
  B  107 stw r0, 0x1c(r1)
--- replace mine 112:114 base 112:114
  M  112 beq 20
  M  113 mr r3, r31
  B  112 beq 108
  B  113 lwz r3, 0x18(r31)
--- replace mine 116:117 base 116:139
  M  116 b 116
  B  116 mr r30, r3
  B  117 addi r3, r3, 0xc
  B  118 bl 0
  B  119 stw r3, 0x2c(r1)
  B  120 b 32
  B  121 lwz r3, 0x2c(r1)
  B  122 li r4, 1
  B  123 lwz r3, 8(r3)
  B  124 bl 0
  B  125 addi r3, r1, 0x2c
  B  126 li r4, 0
  B  127 bl 0
  B  128 addi r3, r30, 0xc
  B  129 bl 0
  B  130 lwz r0, 0x2c(r1)
  B  131 addi r4, r1, 0x10
  B  132 stw r3, 0x10(r1)
  B  133 addi r3, r1, 0x14
  B  134 stw r0, 0x14(r1)
  B  135 bl 0
  B  136 cmpwi r3, 0
  B  137 bne -64
  B  138 b 204
--- replace mine 129:130 base 151:152
  M  129 beq 64
  B  151 beq 152
--- replace mine 131:132 base 153:154
  M  131 addi r4, r1, 0x28
  B  153 addi r4, r1, 0x40
--- replace mine 136:137 base 158:160
  M  136 bne 20
  B  158 bne 108
  B  159 lwz r3, 0x18(r31)
--- delete mine 138:139 base 161:161
  M  138 mr r3, r31
--- insert mine 140:140 base 162:184
  B  162 mr r30, r3
  B  163 addi r3, r3, 0xc
  B  164 bl 0
  B  165 stw r3, 0x28(r1)
  B  166 b 32
  B  167 lwz r3, 0x28(r1)
  B  168 li r4, 1
  B  169 lwz r3, 8(r3)
  B  170 bl 0
  B  171 addi r3, r1, 0x28
  B  172 li r4, 0
  B  173 bl 0
  B  174 addi r3, r30, 0xc
  B  175 bl 0
  B  176 lwz r0, 0x28(r1)
  B  177 addi r4, r1, 8
  B  178 stw r3, 8(r1)
  B  179 addi r3, r1, 0xc
  B  180 stw r0, 0xc(r1)
  B  181 bl 0
  B  182 cmpwi r3, 0
  B  183 bne -64
--- replace mine 144:146 base 188:190
  M  144 blt -68
  M  145 addi r11, r1, 0x70
  B  188 blt -156
  B  189 addi r11, r1, 0x90
--- replace mine 147:148 base 191:192
  M  147 lwz r0, 0x74(r1)
  B  191 lwz r0, 0x94(r1)
--- replace mine 149:150 base 193:194
  M  149 addi r1, r1, 0x70
  B  193 addi r1, r1, 0x90

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: group as reference instead of pointer
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: separate group declaration and assignment
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: langCodeBuf declared before language lookup
instructions 193/195, structural/exact (14, 185); src 0x304 base 0x30c insns 193/195
--- insert mine 5:5 base 5:10
  B    5 mr r31, r3
  B    6 bl 0
  B    7 lis r5, 0
  B    8 slwi r3, r3, 2
  B    9 addi r5, r5, 0
--- replace mine 6:7 base 11:12
  M    6 mr r31, r3
  B   11 lwzx r25, r5, r3
--- delete mine 13:17 base 18:18
  M   13 bl 0
  M   14 lis r4, 0
  M   15 slwi r0, r3, 2
  M   16 addi r28, r4, 0
--- delete mine 18:19 base 19:19
  M   18 lwzx r25, r28, r0
--- insert mine 21:21 base 21:22
  B   21 lis r28, 0
--- insert mine 22:22 base 23:24
  B   23 addi r28, r28, 0
--- replace mine 114:115 base 116:117
  M  114 mr r28, r3
  B  116 mr r30, r3
--- replace mine 126:127 base 128:129
  M  126 addi r3, r28, 0xc
  B  128 addi r3, r30, 0xc
--- replace mine 160:161 base 162:163
  M  160 mr r28, r3
  B  162 mr r30, r3
--- replace mine 172:173 base 174:175
  M  172 addi r3, r28, 0xc
  B  174 addi r3, r30, 0xc

## NHTTPi_strnicmp: ternary case conversion
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: ternary negative condition case conversion
instructions 55/51, structural/exact (13, 53); src 0xdc base 0xcc insns 55/51
--- replace mine 1:4 base 1:4
  M    1 li r12, 0x41
  M    2 li r11, 0
  M    3 li r10, 0x5a
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- delete mine 5:6 base 5:5
  M    5 stw r30, 8(r1)
--- replace mine 8:9 base 7:8
  M    8 ble 168
  B    7 ble 160
--- replace mine 13:15 base 12:14
  M   13 extsb. r30, r6
  M   14 extsb r9, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 16:17 base 15:16
  M   16 cmpwi r9, 0
  B   15 cmpwi r31, 0
--- replace mine 18:19 base 17:18
  M   18 cmpwi r30, 0
  B   17 cmpwi r12, 0
--- replace mine 20:21 base 19:20
  M   20 cmpwi r9, 0
  B   19 cmpwi r31, 0
--- replace mine 23:24 base 22:27
  M   23 b 108
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
--- replace mine 25:31 base 28:29
  M   25 srwi r6, r9, 0x1f
  M   26 subfc r0, r12, r9
  M   27 addi r31, r9, 0x20
  M   28 adde r8, r7, r11
  M   29 srawi r7, r10, 0x1f
  M   30 subfc r0, r9, r10
  B   28 subfc r0, r31, r9
--- replace mine 33:42 base 31:39
  M   33 bne 8
  M   34 mr r31, r9
  M   35 srawi r7, r30, 0x1f
  M   36 srwi r6, r30, 0x1f
  M   37 subfc r0, r12, r30
  M   38 addi r9, r30, 0x20
  M   39 adde r8, r7, r11
  M   40 srawi r7, r10, 0x1f
  M   41 subfc r0, r30, r10
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
--- replace mine 44:47 base 41:44
  M   44 bne 8
  M   45 mr r9, r30
  M   46 cmpw r9, r31
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 49:50 base 46:47
  M   49 bdnz -160
  B   46 bdnz -152
--- delete mine 52:53 base 49:49
  M   52 lwz r30, 8(r1)

## NHTTPi_strnicmp: explicit else lower assignments
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NWC24iCheckDlHeaderConsistency: const input header parameter
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: task represented by typed data struct
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: remove task pointer alias entirely
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 110, 150, 194]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31
   150 M addi r3, r1, 0xa8
       B mr r3, r31
   194 M addi r3, r1, 0xa8
       B mr r3, r31

## NWC24iCheckDlHeaderConsistency: initialize task pointer at loop entry
instructions 215/212, structural/exact (4, 206); src 0x35c base 0x350 insns 215/212
--- replace mine 5:6 base 5:6
  M    5 lhz r0, 0x14(r3)
  B    5 addi r31, r1, 0xa8
--- delete mine 9:12 base 9:9
  M    9 cmpwi r0, 0
  M   10 beq 792
  M   11 addi r31, r1, 0xa8

## NWC24iCheckDlHeaderConsistency: task pointer assigned after taskId zero
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: header and repair copies in nested task scope
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NHTTPi_strnicmp: separate char declarations then assignments
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: load both chars then advance pointers
instructions 51/51, structural/exact (2, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 8, 10, 12, 13]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r12, 0(r3)
       B lbz r6, 0(r3)
    10 M lbz r31, 0(r4)
       B lbz r0, 0(r4)
    12 M extsb. r12, r12
       B extsb. r12, r6
    13 M extsb r31, r31
       B extsb r31, r0

## NHTTPi_strnicmp: integer lower helper with const input and return expressions
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: inline helper explicit upper bound locals before tests
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: lowercase temporaries instead of assignments
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: outer char declarations reused across iterations
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: remove language index temporary
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: declare bool before language, assign after buffer
instructions 195/195, structural/exact (0, 10); src 0x30c base 0x30c insns 195/195
diffs 10: [11, 19, 27, 32, 111, 114, 116, 128, 162, 174]
    11 M lwzx r24, r5, r3
       B lwzx r25, r5, r3
    19 M li r25, 0
       B li r24, 0
    27 M mr r4, r24
       B mr r4, r25
    32 M li r25, 1
       B li r24, 1
   111 M cmpwi r25, 0
       B cmpwi r24, 0
   114 M mr r4, r24
       B mr r4, r25
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: declare group before bool language buffer
instructions 195/195, structural/exact (0, 10); src 0x30c base 0x30c insns 195/195
diffs 10: [11, 19, 27, 32, 111, 114, 116, 128, 162, 174]
    11 M lwzx r24, r5, r3
       B lwzx r25, r5, r3
    19 M li r25, 0
       B li r24, 0
    27 M mr r4, r24
       B mr r4, r25
    32 M li r25, 1
       B li r24, 1
   111 M cmpwi r25, 0
       B cmpwi r24, 0
   114 M mr r4, r24
       B mr r4, r25
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: move initial bool before buffer declaration
instructions 195/195, structural/exact (2, 11); src 0x30c base 0x30c insns 195/195
diffs 11: [13, 14, 15, 16, 17, 18, 19, 116, 128, 162, 174]
    13 M li r24, 0
       B li r3, 0
    14 M li r3, 0
       B mtctr r0
    15 M mtctr r0
       B stb r3, 1(r4)
    16 M stb r3, 1(r4)
       B stbu r3, 2(r4)
    17 M stbu r3, 2(r4)
       B bdnz -8
    18 M bdnz -8
       B lwz r3, 0x18(r31)
    19 M lwz r3, 0x18(r31)
       B li r24, 0
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: pane list reference rather than group pointer
instructions 195/195, structural/exact (6, 6); src 0x30c base 0x30c insns 195/195
diffs 6: [116, 117, 128, 162, 163, 174]
   116 M addi r24, r3, 0xc
       B mr r30, r3
   117 M mr r3, r24
       B addi r3, r3, 0xc
   128 M mr r3, r24
       B addi r3, r30, 0xc
   162 M addi r24, r3, 0xc
       B mr r30, r3
   163 M mr r3, r24
       B addi r3, r3, 0xc
   174 M mr r3, r24
       B addi r3, r30, 0xc

## pfd_sddrv_finalize: definition-level volatile flags, proven repeat loads target offsets 0x20/0x2c with no intervening store
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: reuse result for flags load and return
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: reuse result only for flags load
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: mask with signed local flags
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: final clears and return in typed inline helper
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## NWC24iCheckDlHeaderConsistency: inline helper takes task first before header and repair
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 110, 150, 194]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31
   150 M addi r3, r1, 0xa8
       B mr r3, r31
   194 M addi r3, r1, 0xa8
       B mr r3, r31

## NWC24iCheckDlHeaderConsistency: inline helper takes task last after header and repair
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 110, 150, 194]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31
   150 M addi r3, r1, 0xa8
       B mr r3, r31
   194 M addi r3, r1, 0xa8
       B mr r3, r31

## pfd_sddrv_finalize: independent final clear statement order flags,media,drive,disk
instructions 57/57, structural/exact (7, 6); src 0xe4 base 0xe4 insns 57/57
diffs 6: [45, 47, 49, 50, 51, 52]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    51 M stb r0, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order flags,disk,media,drive
instructions 57/57, structural/exact (3, 5); src 0xe4 base 0xe4 insns 57/57
diffs 5: [45, 47, 49, 50, 51]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    51 M stw r0, 0x10(r4)
       B stw r0, 0xc(r4)

## pfd_sddrv_finalize: independent final clear statement order flags,disk,drive,media
instructions 57/57, structural/exact (8, 6); src 0xe4 base 0xe4 insns 57/57
diffs 6: [45, 47, 49, 50, 51, 52]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    51 M stb r0, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order flags,drive,media,disk
instructions 57/57, structural/exact (3, 6); src 0xe4 base 0xe4 insns 57/57
diffs 6: [45, 47, 49, 50, 51, 52]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stb r0, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    51 M stw r0, 0x10(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order flags,drive,disk,media
instructions 57/57, structural/exact (10, 5); src 0xe4 base 0xe4 insns 57/57
diffs 5: [45, 47, 49, 50, 52]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stb r0, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
    52 M stw r0, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,flags,disk,drive
instructions 57/57, structural/exact (6, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stw r6, 0xc(r4)
       B stw r0, 0xc(r4)
    52 M stb r6, 0x18(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,flags,drive,disk
instructions 57/57, structural/exact (7, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stb r6, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r6, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,disk,flags,drive
instructions 57/57, structural/exact (6, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0xc(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stb r6, 0x18(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,disk,drive,flags
instructions 57/57, structural/exact (6, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0xc(r4)
       B stw r0, 0x10(r4)
    51 M stb r6, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,drive,flags,disk
instructions 57/57, structural/exact (7, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stb r6, 0x18(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stw r6, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order media,drive,disk,flags
instructions 57/57, structural/exact (7, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stb r6, 0x18(r4)
       B stw r0, 0x10(r4)
    51 M stw r6, 0xc(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,flags,media,drive
instructions 57/57, structural/exact (3, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stw r6, 0x10(r4)
       B stw r0, 0xc(r4)
    52 M stb r6, 0x18(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,flags,drive,media
instructions 57/57, structural/exact (8, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stb r6, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r6, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,media,flags,drive
instructions 57/57, structural/exact (8, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0x10(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stb r6, 0x18(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,media,drive,flags
instructions 57/57, structural/exact (8, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0x10(r4)
       B stw r0, 0x10(r4)
    51 M stb r6, 0x18(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,drive,flags,media
instructions 57/57, structural/exact (5, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stb r6, 0x18(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stw r6, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order disk,drive,media,flags
instructions 57/57, structural/exact (8, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stw r6, 0xc(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stb r6, 0x18(r4)
       B stw r0, 0x10(r4)
    51 M stw r6, 0x10(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,flags,media,disk
instructions 57/57, structural/exact (3, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stw r6, 0x10(r4)
       B stw r0, 0xc(r4)
    52 M stw r6, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,flags,disk,media
instructions 57/57, structural/exact (10, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r0, 0(r5)
       B stw r0, 0x10(r4)
    51 M stw r6, 0xc(r4)
       B stw r0, 0xc(r4)
    52 M stw r6, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,media,flags,disk
instructions 57/57, structural/exact (10, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0x10(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stw r6, 0xc(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,media,disk,flags
instructions 57/57, structural/exact (3, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0x10(r4)
       B stw r0, 0x10(r4)
    51 M stw r6, 0xc(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,disk,flags,media
instructions 57/57, structural/exact (5, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0xc(r4)
       B stw r0, 0x10(r4)
    51 M stw r0, 0(r5)
       B stw r0, 0xc(r4)
    52 M stw r6, 0x10(r4)
       B stb r0, 0x18(r4)

## pfd_sddrv_finalize: independent final clear statement order drive,disk,media,flags
instructions 57/57, structural/exact (10, 9); src 0xe4 base 0xe4 insns 57/57
diffs 9: [43, 44, 45, 46, 47, 49, 50, 51, 52]
    43 M lis r5, 0
       B lis r6, 0
    44 M li r6, 0
       B li r0, 0
    45 M lwz r0, 0(r5)
       B lwz r3, 0(r6)
    46 M addi r4, r5, 0
       B addi r4, r6, 0
    47 M stb r6, 0x18(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r0, r0, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r6, 0xc(r4)
       B stw r0, 0x10(r4)
    51 M stw r6, 0x10(r4)
       B stw r0, 0xc(r4)
    52 M stw r0, 0(r5)
       B stb r0, 0x18(r4)

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper overlap copies end then subtracts page
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper last_sector then derive overlap by adding one
instructions 234/233, structural/exact (15, 108); src 0x3a8 base 0x3a4 insns 234/233
--- replace mine 39:40 base 39:40
  M   39 beq 692
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 676
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 532
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 516
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 504
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 496
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 372
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 164
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 156
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 140
  B  127 blt 136
--- replace mine 136:139 base 136:138
  M  136 add r3, r27, r26
  M  137 lwz r4, 0x18(r30)
  M  138 addi r5, r3, -1
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 140:143 base 139:142
  M  140 addi r3, r5, 1
  M  141 subf r3, r4, r3
  M  142 add r0, r0, r3
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
  B  141 add r0, r0, r4
--- replace mine 144:145 base 143:144
  M  144 subf r29, r3, r29
  B  143 subf r29, r4, r29
--- replace mine 148:150 base 147:149
  M  148 lwz r3, 0x18(r30)
  M  149 lwz r4, 4(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
--- replace mine 151:152 base 150:151
  M  151 subf r3, r3, r5
  B  150 subf r3, r4, r3
--- replace mine 153:155 base 152:154
  M  153 stw r4, 0xc(r30)
  M  154 add r3, r4, r0
  B  152 stw r5, 0xc(r30)
  B  153 add r3, r5, r0
--- replace mine 215:216 base 214:215
  M  215 bne -800
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper sector passed separately before end_sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper sector passed separately after end_sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: helper convert end_sector to last then restore overlap
instructions 234/233, structural/exact (15, 108); src 0x3a8 base 0x3a4 insns 234/233
--- replace mine 39:40 base 39:40
  M   39 beq 692
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 676
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 532
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 516
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 504
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 496
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 372
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 164
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 156
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 140
  B  127 blt 136
--- replace mine 136:139 base 136:138
  M  136 add r3, r27, r26
  M  137 lwz r4, 0x18(r30)
  M  138 addi r5, r3, -1
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 140:143 base 139:142
  M  140 addi r3, r5, 1
  M  141 subf r3, r4, r3
  M  142 add r0, r0, r3
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
  B  141 add r0, r0, r4
--- replace mine 144:145 base 143:144
  M  144 subf r29, r3, r29
  B  143 subf r29, r4, r29
--- replace mine 148:150 base 147:149
  M  148 lwz r3, 0x18(r30)
  M  149 lwz r4, 4(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
--- replace mine 151:152 base 150:151
  M  151 subf r3, r3, r5
  B  150 subf r3, r4, r3
--- replace mine 153:155 base 152:154
  M  153 stw r4, 0xc(r30)
  M  154 add r3, r4, r0
  B  152 stw r5, 0xc(r30)
  B  153 add r3, r5, r0
--- replace mine 215:216 base 214:215
  M  215 bne -800
  B  214 bne -796

## Declaration-order searches
NWC24iCheckDlHeaderConsistency: declaration block:
      NWC24DlTask task;
      NWC24DlTask* taskPointer = &task;
      NWC24DlId taskId;
      NWC24Err result;
      DlTaskListHeader* currentHeader;
      DlTaskListHeader* listHeader = header;
      BOOL shouldRepair = repair;
start (2, 3)
best (2, 3) after 52 builds; source restored; best order was:
    NWC24DlTask task;
    NWC24DlTask* taskPointer = &task;
    NWC24DlId taskId;
    NWC24Err result;
    DlTaskListHeader* currentHeader;
    DlTaskListHeader* listHeader = header;
    BOOL shouldRepair = repair;

PFCACHE_DoWriteNumSectorAndFreeIfNeeded: declaration block:
      PF_CACHE_PAGE* p_page = PF_NULL;
      pf_s32 err;
      pf_u32 num_rest_sector = num_sector;
      pf_u8* p_sbuf;
      pf_u8* p_ebuf;
      pf_u32 num_overlap;
      pf_u32 last_sector;
start (0, 4)
best (0, 4) after 52 builds; source restored; best order was:
    PF_CACHE_PAGE* p_page = PF_NULL;
    pf_s32 err;
    pf_u32 num_rest_sector = num_sector;
    pf_u8* p_sbuf;
    pf_u8* p_ebuf;
    pf_u32 num_overlap;
    pf_u32 last_sector;

Open owned function NHTTPi_strnicmp: 24 distinct logged source trials; best candidate did not become exact. All experimental source changes restored.
Open owned function NWC24iCheckDlHeaderConsistency: 13 distinct logged source trials; best candidate did not become exact. All experimental source changes restored.
Open owned function pfd_sddrv_finalize: 39 distinct logged source trials; best candidate did not become exact. All experimental source changes restored.
Open owned function PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 22 distinct logged source trials; best candidate did not become exact. All experimental source changes restored.
Open owned function setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: 15 distinct logged source trials; best candidate did not become exact. All experimental source changes restored.

Data audit: all five unit data measures were already 100% in fresh baseline. No config symbol renames or extent adjustments. No owned function overlapped next function extent; instruction counts equal target.
setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: 0x813b24c0+0x30c <= next 0x813b27cc (GetBeginIter__Q34nw4r2ut29LinkList<Q34nw4r3lyt5Group,4>Fv); no overlap.
NHTTPi_strnicmp: 0x81497ec4+0xcc <= next 0x81497f90 (NHTTPi_getUrlEncodedSize); no overlap.
NWC24iCheckDlHeaderConsistency: 0x814b0874+0x350 <= next 0x814b0bc4 (NWC24iCreateDlTaskList); no overlap.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 0x815c9f54+0x3a4 <= next 0x815ca2f8 (PFCACHE_DoFlushCache); no overlap.
pfd_sddrv_finalize: 0x815eab80+0xe4 <= next 0x815eac64 (pfd_sddrv_get_disk_info); no overlap.

## Final full gate, all five units
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1388/2248 data 112/112 functions 11/14 fuzzy 87.9359 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] instruction-exact functions: 11/14
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .data size 72 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .text size 2248 match 87.93594
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_strnicmp 99.76471
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_compareToken 54.622223
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_Base64Encode 60.285713
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] baseline: code 1388/2248 data 112 functions 11 fuzzy 87.9359
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8140/12496 data 80/80 functions 25/30 fuzzy 99.1521 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 25/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.15205
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 99.303795
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8140/12496 data 80 functions 25 fuzzy 99.1521
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 3592/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 3592 functions 21 fuzzy 99.0544
[libs/RVL_SDK/src/fa/pf_cache] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_cache] objdiff: code 6464/7396 data None/None functions 35/36 fuzzy 99.9865 linked code 0
[libs/RVL_SDK/src/fa/pf_cache] instruction-exact functions: 35/36
[libs/RVL_SDK/src/fa/pf_cache]   section .text size 7396 match 99.98648
[libs/RVL_SDK/src/fa/pf_cache]   below 100: PFCACHE_DoWriteNumSectorAndFreeIfNeeded 99.8927
[libs/RVL_SDK/src/fa/pf_cache] baseline: code 6464/7396 data None functions 35 fuzzy 99.9865
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10144/10924 data 2216/2216 functions 55/56 fuzzy 99.9927 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 54/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 99.992676
[src/scene/channelSelect/iplChannelObj]   below 100: setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object 99.89744
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.9927
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58569
global complete_code_percent: 72.43675 -> 72.50912
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 29fe1efa; compared against nearest snapshotted ancestor 45aaeb16 (1 commits back)
GATE PASS
```

Final retained result: zero new exact functions; source and config unchanged. No local commits because no gate-passing improvement was found. 113 distinct source trials plus 104 declaration-order evaluations. Each owned open function has at least three distinct source trials. Suspected compiler scheduling/register-coloring ties are not proven unavoidable.

Final NHTTPi_strnicmp
```text
src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
```

Final NWC24iCheckDlHeaderConsistency
```text
src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
```

Final pfd_sddrv_finalize
```text
src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
```

Final PFCACHE_DoWriteNumSectorAndFreeIfNeeded
```text
src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4
```

Final setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object
```text
src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
```

# XHIGH round: expression shape and types

Prior high round preserved; no declaration-order reruns planned.
HEAD 29fe1efaf200c57ac4e229c08a373aece57983a1; origin/main 29fe1efaf200c57ac4e229c08a373aece57983a1

Unit src/scene/channelSelect/iplChannelObj
POOL IDENTICAL up to 20 (mine=20 base=20)
src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

Unit libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL
POOL IDENTICAL up to 1 (mine=1 base=1)
src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

Unit libs/RevoEX/src/nwc24/NWC24Download
POOL IDENTICAL up to 3 (mine=3 base=3)
src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

Unit libs/RVL_SDK/src/fa/pf_cache
POOL IDENTICAL up to 0 (mine=0 base=0)
src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

Unit libs/RVL_SDK/src/fa/driver/sd_drv
POOL IDENTICAL up to 46 (mine=46 base=46)
src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH while loops with explicit iterator initialization
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group loops with preincrement
instructions 187/195, structural/exact (51, 93); src 0x2ec base 0x30c insns 187/195
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x80(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x84(r1)
  M    3 addi r11, r1, 0x80
  B    2 stw r0, 0x94(r1)
  B    3 addi r11, r1, 0x90
--- replace mine 12:13 base 12:13
  M   12 addi r4, r1, 0x37
  B   12 addi r4, r1, 0x3f
--- replace mine 22:23 base 22:23
  M   22 stw r3, 0x2c(r1)
  B   22 stw r3, 0x34(r1)
--- replace mine 26:27 base 26:27
  M   26 lwz r3, 0x2c(r1)
  B   26 lwz r3, 0x34(r1)
--- replace mine 37:38 base 37:38
  M   37 addi r3, r1, 0x30
  B   37 addi r3, r1, 0x38
--- replace mine 41:43 base 41:43
  M   41 lwz r27, 0x2c(r1)
  M   42 addi r4, r1, 0x30
  B   41 lwz r27, 0x34(r1)
  B   42 addi r4, r1, 0x38
--- replace mine 57:58 base 57:58
  M   57 stw r3, 0x28(r1)
  B   57 stw r3, 0x30(r1)
--- replace mine 59:60 base 59:60
  M   59 lwz r3, 0x28(r1)
  B   59 lwz r3, 0x30(r1)
--- replace mine 63:64 base 63:64
  M   63 addi r3, r1, 0x28
  B   63 addi r3, r1, 0x30
--- replace mine 66:67 base 66:67
  M   66 lwz r3, 0x2c(r1)
  B   66 lwz r3, 0x34(r1)
--- replace mine 69:70 base 69:70
  M   69 lwz r0, 0x28(r1)
  B   69 lwz r0, 0x30(r1)
--- replace mine 77:78 base 77:78
  M   77 lwz r26, 0x2c(r1)
  B   77 lwz r26, 0x34(r1)
--- replace mine 86:87 base 86:87
  M   86 addi r27, r1, 0x38
  B   86 addi r27, r1, 0x40
--- replace mine 98:99 base 98:99
  M   98 addi r3, r1, 0x2c
  B   98 addi r3, r1, 0x34
--- replace mine 103:104 base 103:104
  M  103 lwz r0, 0x2c(r1)
  B  103 lwz r0, 0x34(r1)
--- replace mine 112:113 base 112:113
  M  112 beq 92
  B  112 beq 108
--- replace mine 116:117 base 116:117
  M  116 mr r28, r3
  B  116 mr r30, r3
--- replace mine 119:122 base 119:122
  M  119 mr r30, r3
  M  120 b 20
  M  121 lwz r3, 8(r30)
  B  119 stw r3, 0x2c(r1)
  B  120 b 32
  B  121 lwz r3, 0x2c(r1)
--- insert mine 123:123 base 123:124
  B  123 lwz r3, 8(r3)
--- replace mine 124:126 base 125:127
  M  124 lwz r30, 0(r30)
  M  125 addi r3, r28, 0xc
  B  125 addi r3, r1, 0x2c
  B  126 li r4, 0
--- insert mine 127:127 base 128:132
  B  128 addi r3, r30, 0xc
  B  129 bl 0
  B  130 lwz r0, 0x2c(r1)
  B  131 addi r4, r1, 0x10
--- replace mine 129:131 base 134:135
  M  129 addi r4, r1, 0x10
  M  130 stw r30, 0x14(r1)
  B  134 stw r0, 0x14(r1)
--- replace mine 133:135 base 137:139
  M  133 bne -48
  M  134 b 188
  B  137 bne -64
  B  138 b 204
--- replace mine 147:148 base 151:152
  M  147 beq 136
  B  151 beq 152
--- replace mine 149:150 base 153:154
  M  149 addi r4, r1, 0x38
  B  153 addi r4, r1, 0x40
--- replace mine 154:155 base 158:159
  M  154 bne 92
  B  158 bne 108
--- replace mine 158:159 base 162:163
  M  158 mr r28, r3
  B  162 mr r30, r3
--- replace mine 161:164 base 165:168
  M  161 mr r30, r3
  M  162 b 20
  M  163 lwz r3, 8(r30)
  B  165 stw r3, 0x28(r1)
  B  166 b 32
  B  167 lwz r3, 0x28(r1)
--- insert mine 165:165 base 169:170
  B  169 lwz r3, 8(r3)
--- replace mine 166:168 base 171:173
  M  166 lwz r30, 0(r30)
  M  167 addi r3, r28, 0xc
  B  171 addi r3, r1, 0x28
  B  172 li r4, 0
--- insert mine 169:169 base 174:178
  B  174 addi r3, r30, 0xc
  B  175 bl 0
  B  176 lwz r0, 0x28(r1)
  B  177 addi r4, r1, 8
--- replace mine 171:173 base 180:181
  M  171 addi r4, r1, 8
  M  172 stw r30, 0xc(r1)
  B  180 stw r0, 0xc(r1)
--- replace mine 175:176 base 183:184
  M  175 bne -48
  B  183 bne -64
--- replace mine 180:182 base 188:190
  M  180 blt -140
  M  181 addi r11, r1, 0x80
  B  188 blt -156
  B  189 addi r11, r1, 0x90
--- replace mine 183:184 base 191:192
  M  183 lwz r0, 0x84(r1)
  B  191 lwz r0, 0x94(r1)
--- replace mine 185:186 base 193:194
  M  185 addi r1, r1, 0x80
  B  193 addi r1, r1, 0x90

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group loop list via const reference and const iterators
instructions 195/195, structural/exact (6, 6); src 0x30c base 0x30c insns 195/195
diffs 6: [116, 117, 128, 162, 163, 174]
   116 M addi r24, r3, 0xc
       B mr r30, r3
   117 M mr r3, r24
       B addi r3, r3, 0xc
   128 M mr r3, r24
       B addi r3, r30, 0xc
   162 M addi r24, r3, 0xc
       B mr r30, r3
   163 M mr r3, r24
       B addi r3, r3, 0xc
   174 M mr r3, r24
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group locals read-only pointer with SDK const removal
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group loops explicit member dereference syntax
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group loops postfix increment in body rather than for clause
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH group pointer result converted through void pointer local
instructions 195/195, structural/exact (6, 6); src 0x30c base 0x30c insns 195/195
diffs 6: [116, 117, 128, 162, 163, 174]
   116 M addi r27, r3, 0xc
       B mr r30, r3
   117 M mr r3, r27
       B addi r3, r3, 0xc
   128 M mr r3, r27
       B addi r3, r30, 0xc
   162 M addi r27, r3, 0xc
       B mr r30, r3
   163 M mr r3, r27
       B addi r3, r3, 0xc
   174 M mr r3, r27
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH bool found and non-rso tests as BOOL
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH found branch explicit != false comparison
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH use const group reference with SDK const removal
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional match return instead of final break
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional match return and explicit return after found group
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH reverse inequality operands in showing pane loops
instructions 195/195, structural/exact (14, 14); src 0x30c base 0x30c insns 195/195
diffs 14: [116, 128, 129, 130, 131, 132, 134, 162, 174, 175, 176, 177, 178, 180]
   116 M mr r28, r3
       B mr r30, r3
   128 M lwz r0, 0x2c(r1)
       B addi r3, r30, 0xc
   129 M addi r3, r28, 0xc
       B bl 0
   130 M stw r0, 0x10(r1)
       B lwz r0, 0x2c(r1)
   131 M bl 0
       B addi r4, r1, 0x10
   132 M stw r3, 0x14(r1)
       B stw r3, 0x10(r1)
   134 M addi r4, r1, 0x10
       B stw r0, 0x14(r1)
   162 M mr r28, r3
       B mr r30, r3
   174 M lwz r0, 0x28(r1)
       B addi r3, r30, 0xc
   175 M addi r3, r28, 0xc
       B bl 0
   176 M stw r0, 8(r1)
       B lwz r0, 0x28(r1)
   177 M bl 0
       B addi r4, r1, 8
   178 M stw r3, 0xc(r1)
       B stw r3, 8(r1)
   180 M addi r4, r1, 8
       B stw r0, 0xc(r1)

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH explicit overloaded inequality call in showing pane loops
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH postfix increment value explicitly discarded in showing loops
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH both groups share selectedGroup pointer with final return
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional iteration unsigned index
instructions 195/195, structural/exact (1, 5); src 0x30c base 0x30c insns 195/195
diffs 5: [116, 128, 162, 174, 187]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   187 M cmplwi r24, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional iteration unsigned region and index
instructions 195/195, structural/exact (1, 5); src 0x30c base 0x30c insns 195/195
diffs 5: [116, 128, 162, 174, 187]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   187 M cmplwi r24, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH all loop indices unsigned
instructions 195/195, structural/exact (3, 7); src 0x30c base 0x30c insns 195/195
diffs 7: [51, 96, 116, 128, 162, 174, 187]
    51 M cmplwi r30, 0x10
       B cmpwi r30, 0x10
    96 M cmplwi r27, 0xa
       B cmpwi r27, 0xa
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   187 M cmplwi r24, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH all loop indices short signed
instructions 195/195, structural/exact (16, 75); src 0x30c base 0x30c insns 195/195
diffs 75: [21, 23, 24, 35, 36, 37, 41, 44, 50, 51, 55, 77, 78, 79, 80, 81, 83, 84, 85, 86]
    21 M lis r29, 0
       B lis r28, 0
    23 M addi r29, r29, 0
       B addi r28, r28, 0
    24 M li r30, 0
       B li r29, 0
    35 M li r27, 0
       B li r30, 0
    36 M addi r3, r1, 0x38
       B mr r5, r30
    37 M extsh r5, r27
       B addi r3, r1, 0x38
    41 M lwz r28, 0x34(r1)
       B lwz r27, 0x34(r1)
    44 M addi r3, r28, 0x14
       B addi r3, r27, 0x14
    50 M addi r27, r27, 1
       B addi r30, r30, 1
    51 M cmpwi r27, 0x10
       B cmpwi r30, 0x10
    55 M addi r3, r28, 8
       B addi r3, r27, 8
    77 M lwz r27, 0x34(r1)
       B lwz r26, 0x34(r1)
    78 M li r28, 0
       B li r27, 0
    79 M extsh r0, r28
       B li r30, 0
    80 M addi r3, r27, 0x14
       B lwzx r4, r28, r30
    81 M slwi r26, r0, 2
       B addi r3, r26, 0x14
    83 M lwzx r4, r29, r26
       B bl 0
    84 M bl 0
       B cmpwi r3, 0
    85 M cmpwi r3, 0
       B bne 36
    86 M bne 36
       B addi r27, r1, 0x40
    87 M addi r28, r1, 0x40
       B addi r4, r26, 0x14
    88 M addi r4, r27, 0x14
       B add r27, r27, r30
    89 M add r28, r28, r26
       B li r5, 3
    90 M li r5, 3
       B mr r3, r27
    91 M mr r3, r28
       B bl 0
    92 M bl 0
       B stb r29, 3(r27)
    93 M stb r30, 3(r28)
       B b 20
    94 M b 16
       B addi r27, r27, 1
    95 M addi r28, r28, 1
       B addi r30, r30, 4
    96 M cmpwi r28, 0xa
       B cmpwi r27, 0xa
    97 M blt -72
       B blt -68
   116 M mr r29, r3
       B mr r30, r3
   128 M addi r3, r29, 0xc
       B addi r3, r30, 0xc
   146 M add r28, r5, r0
       B add r27, r5, r0
   147 M add r29, r4, r0
       B li r30, 0
   148 M extsh r0, r24
       B add r28, r4, r0
   149 M slwi r26, r0, 2
       B lwzx r3, r27, r30
   150 M lwzx r3, r28, r26
       B cmpwi r3, 0
   151 M cmpwi r3, 0
       B beq 152
   152 M beq 148
       B lwzx r0, r28, r30
   153 M lwzx r0, r29, r26
       B addi r4, r1, 0x40
   154 M addi r4, r1, 0x40
       B slwi r0, r0, 2
   155 M slwi r0, r0, 2
       B add r4, r4, r0
   156 M add r4, r4, r0
       B bl 0
   157 M bl 0
       B cmpwi r3, 0
   158 M cmpwi r3, 0
       B bne 108
   159 M bne 108
       B lwz r3, 0x18(r31)
   160 M lwz r3, 0x18(r31)
       B lwzx r4, r27, r30
   161 M lwzx r4, r28, r26
       B bl 0
   162 M bl 0
       B mr r30, r3
   163 M mr r29, r3
       B addi r3, r3, 0xc
   164 M addi r3, r3, 0xc
       B bl 0
   165 M bl 0
       B stw r3, 0x28(r1)
   166 M stw r3, 0x28(r1)
       B b 32
   167 M b 32
       B lwz r3, 0x28(r1)
   168 M lwz r3, 0x28(r1)
       B li r4, 1
   169 M li r4, 1
       B lwz r3, 8(r3)
   170 M lwz r3, 8(r3)
       B bl 0
   171 M bl 0
       B addi r3, r1, 0x28
   172 M addi r3, r1, 0x28
       B li r4, 0
   173 M li r4, 0
       B bl 0
   174 M bl 0
       B addi r3, r30, 0xc
   175 M addi r3, r29, 0xc
       B bl 0
   176 M bl 0
       B lwz r0, 0x28(r1)
   177 M lwz r0, 0x28(r1)
       B addi r4, r1, 8
   178 M addi r4, r1, 8
       B stw r3, 8(r1)
   179 M stw r3, 8(r1)
       B addi r3, r1, 0xc
   180 M addi r3, r1, 0xc
       B stw r0, 0xc(r1)
   181 M stw r0, 0xc(r1)
       B bl 0
   182 M bl 0
       B cmpwi r3, 0
   183 M cmpwi r3, 0
       B bne -64
   184 M bne -64
       B b 20
   185 M b 16
       B addi r24, r24, 1
   186 M addi r24, r24, 1
       B addi r30, r30, 4
   188 M blt -160
       B blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional language lookup pointer local per iteration
instructions 196/195, structural/exact (5, 51); src 0x310 base 0x30c insns 196/195
--- replace mine 116:117 base 116:117
  M  116 mr r28, r3
  B  116 mr r30, r3
--- replace mine 128:129 base 128:129
  M  128 addi r3, r28, 0xc
  B  128 addi r3, r30, 0xc
--- replace mine 138:139 base 138:139
  M  138 b 208
  B  138 b 204
--- replace mine 146:147 base 146:147
  M  146 add r28, r5, r0
  B  146 add r27, r5, r0
--- replace mine 148:153 base 148:153
  M  148 add r29, r4, r0
  M  149 lwzx r25, r28, r30
  M  150 cmpwi r25, 0
  M  151 beq 156
  M  152 lwzx r0, r29, r30
  B  148 add r28, r4, r0
  B  149 lwzx r3, r27, r30
  B  150 cmpwi r3, 0
  B  151 beq 152
  B  152 lwzx r0, r28, r30
--- delete mine 154:155 base 154:154
  M  154 mr r3, r25
--- replace mine 161:162 base 160:161
  M  161 mr r4, r25
  B  160 lwzx r4, r27, r30
--- replace mine 163:164 base 162:163
  M  163 mr r28, r3
  B  162 mr r30, r3
--- replace mine 175:176 base 174:175
  M  175 addi r3, r28, 0xc
  B  174 addi r3, r30, 0xc
--- replace mine 189:190 base 188:189
  M  189 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional language and language-index const pointer tables
BUILD FAIL hannelSelect && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/channelSelect/iplChannelObj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:8)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     683:          const int* regionLanguageIndices = scLangLookup[region];
#   Error:                                                                 ^
#   (10209) illegal implicit conversion from 'const unsigned long[16]' to
#   'const int *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH language-group string pointer const definition
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

XHIGH NHTTPi_strnicmp: refreshed origin/main, source unchanged/non-exact. Only 0 and Z constant hoisting order differs; range-test arithmetic remains signed 32-bit with original char sign extension. Explore expression composition and narrowed intermediate types rather than repeating declaration orders.

## NHTTPi_strnicmp: XHIGH signed 16-bit character locals
instructions 53/51, structural/exact (7, 34); src 0xd4 base 0xcc insns 53/51
--- insert mine 2:2 base 2:3
  B    2 li r9, 0x5a
--- delete mine 3:4 base 4:4
  M    3 li r9, 0x5a
--- replace mine 7:8 base 7:8
  M    7 ble 168
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r31, r6
  M   13 extsb r12, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- insert mine 15:15 base 15:17
  B   15 cmpwi r31, 0
  B   16 bne 28
--- replace mine 16:17 base 18:19
  M   16 bne 28
  B   18 bne 20
--- delete mine 18:20 base 20:20
  M   18 bne 20
  M   19 cmpwi r12, 0
--- replace mine 22:23 base 22:33
  M   22 b 108
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
--- replace mine 33:46 base 43:44
  M   33 srawi r7, r31, 0x1f
  M   34 srwi r6, r31, 0x1f
  M   35 subfc r0, r11, r31
  M   36 extsh r12, r12
  M   37 adde r8, r7, r10
  M   38 srawi r7, r9, 0x1f
  M   39 subfc r0, r31, r9
  M   40 adde r0, r7, r6
  M   41 and. r0, r8, r0
  M   42 beq 8
  M   43 addi r31, r31, 0x20
  M   44 extsh r0, r31
  M   45 cmpw r0, r12
  B   43 cmpw r12, r31
--- replace mine 48:49 base 46:47
  M   48 bdnz -160
  B   46 bdnz -152

## NHTTPi_strnicmp: XHIGH long signed character locals
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH unsigned raw char then signed 32-bit views
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH both lowercase assignments one comma expression
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH lowercase assignments inside mismatch test
instructions 51/51, structural/exact (2, 3); src 0xcc base 0xcc insns 51/51
diffs 3: [2, 3, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: XHIGH increment by conditional case offset
instructions 59/51, structural/exact (25, 58); src 0xec base 0xcc insns 59/51
--- replace mine 1:3 base 1:4
  M    1 li r6, 0x41
  M    2 li r0, 0
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- delete mine 4:6 base 5:5
  M    4 li r31, 0x5a
  M    5 stw r30, 8(r1)
--- replace mine 8:10 base 7:9
  M    8 ble 184
  M    9 lbz r7, 0(r3)
  B    7 ble 160
  B    8 lbz r6, 0(r3)
--- replace mine 11:12 base 10:11
  M   11 lbz r8, 0(r4)
  B   10 lbz r0, 0(r4)
--- replace mine 13:15 base 12:14
  M   13 extsb. r7, r7
  M   14 extsb r8, r8
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 16:17 base 15:16
  M   16 cmpwi r8, 0
  B   15 cmpwi r31, 0
--- replace mine 18:19 base 17:18
  M   18 cmpwi r7, 0
  B   17 cmpwi r12, 0
--- replace mine 20:21 base 19:20
  M   20 cmpwi r8, 0
  B   19 cmpwi r31, 0
--- replace mine 23:51 base 22:44
  M   23 b 124
  M   24 srawi r12, r8, 0x1f
  M   25 srwi r11, r8, 0x1f
  M   26 subfc r9, r6, r8
  M   27 srwi r10, r7, 0x1f
  M   28 adde r30, r12, r0
  M   29 srawi r12, r31, 0x1f
  M   30 subfc r9, r8, r31
  M   31 adde r9, r12, r11
  M   32 and r11, r30, r9
  M   33 neg r9, r11
  M   34 or r9, r9, r11
  M   35 srawi r12, r9, 0x1f
  M   36 srawi r11, r7, 0x1f
  M   37 subfc r9, r6, r7
  M   38 rlwinm r9, r12, 0, 0x1a, 0x1a
  M   39 adde r12, r11, r0
  M   40 srawi r11, r31, 0x1f
  M   41 add r8, r8, r9
  M   42 subfc r9, r7, r31
  M   43 adde r9, r11, r10
  M   44 and r10, r12, r9
  M   45 neg r9, r10
  M   46 or r9, r9, r10
  M   47 srawi r9, r9, 0x1f
  M   48 rlwinm r9, r9, 0, 0x1a, 0x1a
  M   49 add r7, r7, r9
  M   50 cmpw r7, r8
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 53:54 base 46:47
  M   53 bdnz -176
  B   46 bdnz -152
--- delete mine 56:57 base 49:49
  M   56 lwz r30, 8(r1)

## NHTTPi_strnicmp: XHIGH conditional case offset added on left
instructions 59/51, structural/exact (25, 58); src 0xec base 0xcc insns 59/51
--- replace mine 1:3 base 1:4
  M    1 li r6, 0x41
  M    2 li r0, 0
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- delete mine 4:6 base 5:5
  M    4 li r31, 0x5a
  M    5 stw r30, 8(r1)
--- replace mine 8:10 base 7:9
  M    8 ble 184
  M    9 lbz r7, 0(r3)
  B    7 ble 160
  B    8 lbz r6, 0(r3)
--- replace mine 11:12 base 10:11
  M   11 lbz r8, 0(r4)
  B   10 lbz r0, 0(r4)
--- replace mine 13:15 base 12:14
  M   13 extsb. r7, r7
  M   14 extsb r8, r8
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 16:17 base 15:16
  M   16 cmpwi r8, 0
  B   15 cmpwi r31, 0
--- replace mine 18:19 base 17:18
  M   18 cmpwi r7, 0
  B   17 cmpwi r12, 0
--- replace mine 20:21 base 19:20
  M   20 cmpwi r8, 0
  B   19 cmpwi r31, 0
--- replace mine 23:51 base 22:44
  M   23 b 124
  M   24 srawi r12, r8, 0x1f
  M   25 srwi r11, r8, 0x1f
  M   26 subfc r9, r6, r8
  M   27 srwi r10, r7, 0x1f
  M   28 adde r30, r12, r0
  M   29 srawi r12, r31, 0x1f
  M   30 subfc r9, r8, r31
  M   31 adde r9, r12, r11
  M   32 and r11, r30, r9
  M   33 neg r9, r11
  M   34 or r9, r9, r11
  M   35 srawi r12, r9, 0x1f
  M   36 srawi r11, r7, 0x1f
  M   37 subfc r9, r6, r7
  M   38 rlwinm r9, r12, 0, 0x1a, 0x1a
  M   39 adde r12, r11, r0
  M   40 srawi r11, r31, 0x1f
  M   41 add r8, r8, r9
  M   42 subfc r9, r7, r31
  M   43 adde r9, r11, r10
  M   44 and r10, r12, r9
  M   45 neg r9, r10
  M   46 or r9, r9, r10
  M   47 srawi r9, r9, 0x1f
  M   48 rlwinm r9, r9, 0, 0x1a, 0x1a
  M   49 add r7, r7, r9
  M   50 cmpw r7, r8
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 53:54 base 46:47
  M   53 bdnz -176
  B   46 bdnz -152
--- delete mine 56:57 base 49:49
  M   56 lwz r30, 8(r1)

## NHTTPi_strnicmp: XHIGH lowercase ternary in comparison operands
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH lowercase comparisons explicitly boolean BOOL results
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH lowercase signed comparison against 16-bit bounds
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH lowercase signed comparison via bool local flags
instructions 55/51, structural/exact (11, 43); src 0xdc base 0xcc insns 55/51
--- replace mine 1:3 base 1:4
  M    1 li r12, 0
  M    2 li r11, 0x5a
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- delete mine 4:5 base 5:5
  M    4 li r31, 0x41
--- replace mine 7:8 base 7:8
  M    7 ble 176
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r6, r6
  M   13 extsb r7, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 15:16 base 15:16
  M   15 cmpwi r7, 0
  B   15 cmpwi r31, 0
--- replace mine 17:18 base 17:18
  M   17 cmpwi r6, 0
  B   17 cmpwi r12, 0
--- replace mine 19:20 base 19:20
  M   19 cmpwi r7, 0
  B   19 cmpwi r31, 0
--- replace mine 22:33 base 22:31
  M   22 b 116
  M   23 srawi r9, r7, 0x1f
  M   24 srwi r8, r7, 0x1f
  M   25 subfc r0, r31, r7
  M   26 adde r10, r9, r12
  M   27 srawi r9, r11, 0x1f
  M   28 subfc r0, r7, r11
  M   29 clrlwi r10, r10, 0x18
  M   30 adde r0, r9, r8
  M   31 clrlwi r0, r0, 0x18
  M   32 and. r0, r10, r0
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
--- replace mine 34:45 base 32:41
  M   34 addi r7, r7, 0x20
  M   35 srawi r9, r6, 0x1f
  M   36 srwi r8, r6, 0x1f
  M   37 subfc r0, r31, r6
  M   38 adde r10, r9, r12
  M   39 srawi r9, r11, 0x1f
  M   40 subfc r0, r6, r11
  M   41 clrlwi r10, r10, 0x18
  M   42 adde r0, r9, r8
  M   43 clrlwi r0, r0, 0x18
  M   44 and. r0, r10, r0
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
--- replace mine 46:48 base 42:44
  M   46 addi r6, r6, 0x20
  M   47 cmpw r6, r7
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 50:51 base 46:47
  M   50 bdnz -168
  B   46 bdnz -152

## NHTTPi_strnicmp: XHIGH lowercase comparison result explicitly != 0
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH negated lower comparison
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH negated upper comparison
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH both comparisons negated
instructions 50/51, structural/exact (42, 50); src 0xc8 base 0xcc insns 50/51
--- insert mine 0:0 base 0:5
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 2:3 base 7:8
  M    2 ble 184
  B    7 ble 160
--- replace mine 7:9 base 12:14
  M    7 extsb. r9, r6
  M    8 extsb r10, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 10:11 base 15:16
  M   10 cmpwi r10, 0
  B   15 cmpwi r31, 0
--- replace mine 12:13 base 17:18
  M   12 cmpwi r9, 0
  B   17 cmpwi r12, 0
--- replace mine 14:15 base 19:20
  M   14 cmpwi r10, 0
  B   19 cmpwi r31, 0
--- replace mine 17:45 base 22:44
  M   17 b 124
  M   18 xori r0, r10, 0x41
  M   19 xori r6, r10, 0x5a
  M   20 andi. r7, r0, 0x41
  M   21 srawi r8, r0, 1
  M   22 and r0, r6, r10
  M   23 srawi r6, r6, 1
  M   24 subf r0, r0, r6
  M   25 subf r7, r7, r8
  M   26 srwi r6, r7, 0x1f
  M   27 srwi r0, r0, 0x1f
  M   28 or. r0, r6, r0
  M   29 bne 8
  M   30 addi r10, r10, 0x20
  M   31 xori r0, r9, 0x41
  M   32 xori r6, r9, 0x5a
  M   33 andi. r7, r0, 0x41
  M   34 srawi r8, r0, 1
  M   35 and r0, r6, r9
  M   36 srawi r6, r6, 1
  M   37 subf r0, r0, r6
  M   38 subf r7, r7, r8
  M   39 srwi r6, r7, 0x1f
  M   40 srwi r0, r0, 0x1f
  M   41 or. r0, r6, r0
  M   42 bne 8
  M   43 addi r9, r9, 0x20
  M   44 cmpw r9, r10
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 47:48 base 46:48
  M   47 bdnz -176
  B   46 bdnz -152
  B   47 lwz r31, 0xc(r1)
--- insert mine 49:49 base 49:50
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: XHIGH outside-range bitwise inverse
instructions 50/51, structural/exact (42, 50); src 0xc8 base 0xcc insns 50/51
--- insert mine 0:0 base 0:5
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 2:3 base 7:8
  M    2 ble 184
  B    7 ble 160
--- replace mine 7:9 base 12:14
  M    7 extsb. r9, r6
  M    8 extsb r10, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 10:11 base 15:16
  M   10 cmpwi r10, 0
  B   15 cmpwi r31, 0
--- replace mine 12:13 base 17:18
  M   12 cmpwi r9, 0
  B   17 cmpwi r12, 0
--- replace mine 14:15 base 19:20
  M   14 cmpwi r10, 0
  B   19 cmpwi r31, 0
--- replace mine 17:45 base 22:44
  M   17 b 124
  M   18 xori r0, r10, 0x41
  M   19 xori r6, r10, 0x5a
  M   20 andi. r7, r0, 0x41
  M   21 srawi r8, r0, 1
  M   22 and r0, r6, r10
  M   23 srawi r6, r6, 1
  M   24 subf r0, r0, r6
  M   25 subf r7, r7, r8
  M   26 srwi r6, r7, 0x1f
  M   27 srwi r0, r0, 0x1f
  M   28 or. r0, r6, r0
  M   29 bne 8
  M   30 addi r10, r10, 0x20
  M   31 xori r0, r9, 0x41
  M   32 xori r6, r9, 0x5a
  M   33 andi. r7, r0, 0x41
  M   34 srawi r8, r0, 1
  M   35 and r0, r6, r9
  M   36 srawi r6, r6, 1
  M   37 subf r0, r0, r6
  M   38 subf r7, r7, r8
  M   39 srwi r6, r7, 0x1f
  M   40 srwi r0, r0, 0x1f
  M   41 or. r0, r6, r0
  M   42 bne 8
  M   43 addi r9, r9, 0x20
  M   44 cmpw r9, r10
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 47:48 base 46:48
  M   47 bdnz -176
  B   46 bdnz -152
  B   47 lwz r31, 0xc(r1)
--- insert mine 49:49 base 49:50
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: XHIGH arithmetic bounds strict comparisons
instructions 50/51, structural/exact (36, 50); src 0xc8 base 0xcc insns 50/51
--- insert mine 0:0 base 0:5
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 2:3 base 7:8
  M    2 ble 184
  B    7 ble 160
--- replace mine 7:9 base 12:14
  M    7 extsb. r9, r6
  M    8 extsb r10, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 10:11 base 15:16
  M   10 cmpwi r10, 0
  B   15 cmpwi r31, 0
--- replace mine 12:13 base 17:18
  M   12 cmpwi r9, 0
  B   17 cmpwi r12, 0
--- replace mine 14:15 base 19:20
  M   14 cmpwi r10, 0
  B   19 cmpwi r31, 0
--- replace mine 17:29 base 22:31
  M   17 b 124
  M   18 xori r6, r10, 0x5b
  M   19 xori r7, r10, 0x40
  M   20 andi. r0, r6, 0x5b
  M   21 srawi r8, r7, 1
  M   22 and r7, r7, r10
  M   23 srawi r6, r6, 1
  M   24 subf r0, r0, r6
  M   25 subf r7, r7, r8
  M   26 srwi r6, r7, 0x1f
  M   27 srwi r0, r0, 0x1f
  M   28 and. r0, r6, r0
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
--- replace mine 30:42 base 32:41
  M   30 addi r10, r10, 0x20
  M   31 xori r6, r9, 0x5b
  M   32 xori r7, r9, 0x40
  M   33 andi. r0, r6, 0x5b
  M   34 srawi r8, r7, 1
  M   35 and r7, r7, r9
  M   36 srawi r6, r6, 1
  M   37 subf r0, r0, r6
  M   38 subf r7, r7, r8
  M   39 srwi r6, r7, 0x1f
  M   40 srwi r0, r0, 0x1f
  M   41 and. r0, r6, r0
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
--- replace mine 43:45 base 42:44
  M   43 addi r9, r9, 0x20
  M   44 cmpw r9, r10
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 47:48 base 46:48
  M   47 bdnz -176
  B   46 bdnz -152
  B   47 lwz r31, 0xc(r1)
--- insert mine 49:49 base 49:50
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: XHIGH upper comparison signed u16 bound
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH min comparison signed u16 bound
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH int lower conditional result cast
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH unsigned boolean comparison results
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH bool lower result equality true
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

XHIGH NWC24iCheckDlHeaderConsistency: origin/main re-fetched and owned source unchanged. Target materializes taskPointer before copies of input header and repair; same stack/frame, helper branches, instruction count. Examine pointer representation and expression sequencing, not permutations of declaration lines.

## NWC24iCheckDlHeaderConsistency: XHIGH typed task data pointer view
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task pointer derived from public data buffer
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task pointer from void view of object address
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task pointer const pointee view with explicit API casts
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH comma sequencing task and input alias initialization
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH only task pointer alias const, repair alias const
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH repair explicitly normalized to boolean value
instructions 214/212, structural/exact (4, 208); src 0x358 base 0x350 insns 214/212
--- replace mine 5:6 base 5:6
  M    5 neg r0, r4
  B    5 addi r31, r1, 0xa8
--- replace mine 7:10 base 7:8
  M    7 or r0, r0, r4
  M    8 addi r31, r1, 0xa8
  M    9 srwi r29, r0, 0x1f
  B    7 mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH for condition reversed operands
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH top-level work loop while with postfix increment
instructions 214/212, structural/exact (8, 178); src 0x358 base 0x350 insns 214/212
--- insert mine 5:5 base 5:6
  B    5 addi r31, r1, 0xa8
--- delete mine 7:8 base 8:8
  M    7 addi r31, r1, 0xa8
--- replace mine 10:11 base 10:11
  M   10 b 772
  B   10 b 764
--- replace mine 39:40 base 39:40
  M   39 bne 12
  B   39 bne 644
--- replace mine 41:44 base 41:42
  M   41 bne 12
  M   42 addi r30, r30, 1
  M   43 b 640
  B   41 beq 636
--- replace mine 206:207 base 204:205
  M  206 blt -780
  B  204 blt -772

## NWC24iCheckDlHeaderConsistency: XHIGH taskId unsigned 32-bit induction, checked u16 range
instructions 209/212, structural/exact (26, 204); src 0x344 base 0x350 insns 209/212
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x2d0(r1)
  B    0 stwu r1, -0x2c0(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x2d4(r1)
  M    3 addi r11, r1, 0x2d0
  B    2 stw r0, 0x2c4(r1)
  B    3 addi r11, r1, 0x2c0
--- replace mine 5:12 base 5:11
  M    5 mr r27, r3
  M    6 mr r28, r4
  M    7 addi r30, r1, 0xa8
  M    8 li r29, 0
  M    9 li r31, 0
  M   10 lis r26, 1
  M   11 b 752
  B    5 addi r31, r1, 0xa8
  B    6 mr r28, r3
  B    7 mr r29, r4
  B    8 li r30, 0
  B    9 lis r27, 1
  B   10 b 764
--- insert mine 13:13 base 12:13
  B   12 clrlwi r4, r30, 0x10
--- replace mine 19:22 base 19:23
  M   19 cmplw r29, r0
  M   20 bge 12
  M   21 cmplwi r29, 0xffff
  B   19 cmplw r4, r0
  B   20 bge 16
  B   21 clrlwi r0, r30, 0x10
  B   22 cmplwi r0, 0xffff
--- replace mine 24:25 base 25:26
  M   24 b 48
  B   25 b 52
--- replace mine 27:28 base 28:29
  M   27 addi r0, r5, 0x3600
  B   28 addi r3, r5, 0x3600
--- replace mine 29:31 base 30:32
  M   29 li r0, 0
  M   30 add r3, r0, r31
  B   30 li r3, 0
  B   31 rlwinm r0, r30, 4, 0xc, 0x1b
--- insert mine 32:32 base 33:34
  B   33 add r3, r3, r0
--- replace mine 37:40 base 39:42
  M   37 bne 640
  M   38 cmpwi r28, 0
  M   39 beq 632
  B   39 bne 644
  B   40 cmpwi r29, 0
  B   41 beq 636
--- replace mine 50:51 base 52:53
  M   50 clrlwi r4, r29, 0x10
  B   52 clrlwi r4, r30, 0x10
--- replace mine 58:59 base 60:61
  M   58 clrlwi r0, r29, 0x10
  B   60 clrlwi r0, r30, 0x10
--- replace mine 68:69 base 70:71
  M   68 rlwinm r0, r29, 4, 0xc, 0x1b
  B   70 rlwinm r0, r30, 4, 0xc, 0x1b
--- replace mine 94:95 base 96:97
  M   94 clrlwi r0, r29, 0x10
  B   96 clrlwi r0, r30, 0x10
--- replace mine 99:100 base 101:102
  M   99 rlwinm r4, r29, 9, 7, 0x16
  B  101 rlwinm r4, r30, 9, 7, 0x16
--- replace mine 106:107 base 108:109
  M  106 mr r25, r3
  B  108 mr r26, r3
--- replace mine 108:109 base 110:111
  M  108 mr r3, r30
  B  110 mr r3, r31
--- replace mine 113:114 base 115:116
  M  113 li r25, 0
  B  115 li r26, 0
--- replace mine 115:116 base 117:118
  M  115 mr r25, r3
  B  117 mr r26, r3
--- replace mine 118:119 base 120:121
  M  118 cmpwi r25, 0
  B  120 cmpwi r26, 0
--- replace mine 120:121 base 122:123
  M  120 mr r3, r25
  B  122 mr r3, r26
--- replace mine 129:130 base 131:132
  M  129 cmpwi r30, 0
  B  131 cmpwi r31, 0
--- replace mine 147:149 base 149:151
  M  147 bne 200
  M  148 mr r3, r30
  B  149 bne 204
  B  150 mr r3, r31
--- replace mine 151:153 base 153:155
  M  151 blt 184
  M  152 addi r0, r26, -1
  B  153 blt 188
  B  154 addi r0, r27, -1
--- replace mine 154:157 base 156:160
  M  154 b 172
  M  155 lwz r4, 0(0)
  M  156 cmpwi r4, 0
  B  156 b 176
  B  157 lwz r5, 0(0)
  B  158 clrlwi r4, r30, 0x10
  B  159 cmpwi r5, 0
--- replace mine 158:159 base 161:162
  M  158 addi r3, r4, 0x3600
  B  161 addi r3, r5, 0x3600
--- replace mine 162:163 base 165:166
  M  162 cmplw r29, r0
  B  165 cmplw r4, r0
--- replace mine 167:168 base 170:171
  M  167 cmpwi r4, 0
  B  170 cmpwi r5, 0
--- replace mine 169:170 base 172:173
  M  169 addi r3, r4, 0x3600
  B  172 addi r3, r5, 0x3600
--- replace mine 172:173 base 175:176
  M  172 cmpwi r30, 0
  B  175 cmpwi r31, 0
--- replace mine 191:192 base 194:195
  M  191 mr r3, r30
  B  194 mr r3, r31
--- replace mine 195:196 base 198:199
  M  195 addi r0, r26, -1
  B  198 addi r0, r27, -1
--- replace mine 197:203 base 200:206
  M  197 addi r31, r31, 0x10
  M  198 addi r29, r29, 1
  M  199 lhz r0, 0x14(r27)
  M  200 cmplw r29, r0
  M  201 blt -756
  M  202 addi r11, r1, 0x2d0
  B  200 addi r30, r30, 1
  B  201 lhz r0, 0x14(r28)
  B  202 clrlwi r3, r30, 0x10
  B  203 cmplw r3, r0
  B  204 blt -772
  B  205 addi r11, r1, 0x2c0
--- replace mine 205:206 base 208:209
  M  205 lwz r0, 0x2d4(r1)
  B  208 lwz r0, 0x2c4(r1)
--- replace mine 207:208 base 210:211
  M  207 addi r1, r1, 0x2d0
  B  210 addi r1, r1, 0x2c0

## NWC24iCheckDlHeaderConsistency: XHIGH result declaration type plain int
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task storage union for public and internal task views
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task storage union retaining pointer-based private fields
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH task byte buffer with SDK task-pointer view
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH cached header alias assign only at loop condition
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH repair condition expressed as explicit nonzero comparison
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: XHIGH repair false condition evaluated before result
instructions 212/212, structural/exact (4, 7); src 0x350 base 0x350 insns 212/212
diffs 7: [5, 6, 7, 38, 39, 40, 41]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
    38 M cmpwi r29, 0
       B cmpwi r4, 0
    39 M beq 644
       B bne 644
    40 M cmpwi r4, 0
       B cmpwi r29, 0
    41 M bne 636
       B beq 636

## NWC24iCheckDlHeaderConsistency: XHIGH repair path positive nested scope
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

XHIGH PFCACHE_DoWriteNumSectorAndFreeIfNeeded: re-fetched origin/main; source unchanged/non-exact. Only end-sector result and sector-load temporary register roles differ at inlined overlap bookkeeping. Data sections absent. Tests focus helper scalar types, parameter views, and explicit arithmetic shapes.

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH explicit overlap bookkeeping without inline helper
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 139, 140, 147, 148, 150, 152, 153]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   139 M addi r5, r4, -1
       B addi r3, r4, -1
   140 M subf r4, r3, r4
       B subf r4, r5, r4
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   148 M lwz r4, 4(r30)
       B lwz r5, 4(r30)
   150 M subf r3, r3, r5
       B subf r3, r4, r3
   152 M stw r4, 0xc(r30)
       B stw r5, 0xc(r30)
   153 M add r3, r4, r0
       B add r3, r5, r0

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH explicit overlap bookkeeping signed count local
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 139, 140, 147, 148, 150, 152, 153]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   139 M addi r5, r4, -1
       B addi r3, r4, -1
   140 M subf r4, r3, r4
       B subf r4, r5, r4
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   148 M lwz r4, 4(r30)
       B lwz r5, 4(r30)
   150 M subf r3, r3, r5
       B subf r3, r4, r3
   152 M stw r4, 0xc(r30)
       B stw r5, 0xc(r30)
   153 M add r3, r4, r0
       B add r3, r5, r0

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH explicit overlap bookkeeping cache sector before end arithmetic
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 139, 140, 147, 148, 150, 152, 153]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   139 M addi r5, r4, -1
       B addi r3, r4, -1
   140 M subf r4, r3, r4
       B subf r4, r5, r4
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   148 M lwz r4, 4(r30)
       B lwz r5, 4(r30)
   150 M subf r3, r3, r5
       B subf r3, r4, r3
   152 M stw r4, 0xc(r30)
       B stw r5, 0xc(r30)
   153 M add r3, r4, r0
       B add r3, r5, r0

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH inline helper end sector by const pointer view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH inline helper const scalar end sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper unsigned long overlap intermediates
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper signed last sector intermediate
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper signed overlap intermediate
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH outer overlap unsigned long intermediate
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH outer overlap signed intermediate
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH explicit sector load converted through signed view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

XHIGH pfd_sddrv_finalize: refreshed origin/main; owned source unchanged/non-exact. Existing flags volatile declaration tried high had no benefit. No new volatile proposal without new proof. Focus final expression trees and same-width flag/media field types; no changes retained unless all other unit function output remains unchanged.

## pfd_sddrv_finalize: XHIGH clear flags low bit with paired shifts
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH clear flags low bit by unsigned even rounding
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH comma expression for all final stores
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH clear flag assignment and zero return comma expression
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH compound flag assignment shares comma with media reset
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH flags mask signed complement
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH flags value retrieved through read-only struct alias
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH zero resets use FALSE and NULL constants
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH cleared flags declared const scalar
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH media_inserted field typed BOOL
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH flags field typed signed s32
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH flags field typed unsigned int
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH last sector derived from page start plus overlap
instructions 234/233, structural/exact (14, 104); src 0x3a8 base 0x3a4 insns 234/233
--- replace mine 39:40 base 39:40
  M   39 beq 692
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 676
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 532
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 516
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 504
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 496
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 372
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 164
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 156
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 140
  B  127 blt 136
--- replace mine 136:137 base 136:137
  M  136 lwz r3, 0x18(r30)
  B  136 lwz r5, 0x18(r30)
--- replace mine 139:140 base 139:141
  M  139 subf r4, r3, r4
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- delete mine 142:143 base 143:143
  M  142 add r3, r3, r4
--- delete mine 145:146 base 145:145
  M  145 addi r3, r3, -1
--- replace mine 215:216 base 214:215
  M  215 bne -800
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH last sector derived from overlap plus page start
instructions 234/233, structural/exact (14, 104); src 0x3a8 base 0x3a4 insns 234/233
--- replace mine 39:40 base 39:40
  M   39 beq 692
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 676
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 532
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 516
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 504
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 496
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 372
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 164
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 156
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 140
  B  127 blt 136
--- replace mine 136:137 base 136:137
  M  136 lwz r3, 0x18(r30)
  B  136 lwz r5, 0x18(r30)
--- replace mine 139:140 base 139:141
  M  139 subf r4, r3, r4
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- delete mine 142:143 base 143:143
  M  142 add r3, r4, r3
--- delete mine 145:146 base 145:145
  M  145 addi r3, r3, -1
--- replace mine 215:216 base 214:215
  M  215 bne -800
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH overlap as end plus negated sector
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH overlap as negated sector plus end
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH overlap using complement plus carry
instructions 235/233, structural/exact (14, 107); src 0x3ac base 0x3a4 insns 235/233
--- replace mine 39:40 base 39:40
  M   39 beq 696
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 680
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 536
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 520
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 508
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 500
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 376
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 168
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 160
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 144
  B  127 blt 136
--- replace mine 136:138 base 136:138
  M  136 lwz r4, 0x18(r30)
  M  137 add r5, r27, r26
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 139:143 base 139:141
  M  139 addi r3, r5, -1
  M  140 nor r4, r4, r4
  M  141 add r4, r5, r4
  M  142 addi r4, r4, 1
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 216:217 base 214:215
  M  216 bne -804
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector expression destructively decrement parameter
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector offset with unsigned complement constant
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper overlap subtraction after last-sector decrement
instructions 234/233, structural/exact (15, 108); src 0x3a8 base 0x3a4 insns 234/233
--- replace mine 39:40 base 39:40
  M   39 beq 692
  B   39 beq 688
--- replace mine 43:44 base 43:44
  M   43 beq 676
  B   43 beq 672
--- replace mine 79:80 base 79:80
  M   79 b 532
  B   79 b 528
--- replace mine 83:84 base 83:84
  M   83 b 516
  B   83 b 512
--- replace mine 86:87 base 86:87
  M   86 bge 504
  B   86 bge 500
--- replace mine 88:89 base 88:89
  M   88 b 496
  B   88 b 492
--- replace mine 119:120 base 119:120
  M  119 b 372
  B  119 b 368
--- replace mine 121:122 base 121:122
  M  121 ble 164
  B  121 ble 160
--- replace mine 123:124 base 123:124
  M  123 bge 156
  B  123 bge 152
--- replace mine 127:128 base 127:128
  M  127 blt 140
  B  127 blt 136
--- insert mine 136:136 base 136:137
  B  136 lwz r5, 0x18(r30)
--- delete mine 137:139 base 138:138
  M  137 lwz r3, 0x18(r30)
  M  138 addi r4, r4, -1
--- replace mine 140:143 base 139:142
  M  140 subf r3, r3, r4
  M  141 addi r3, r3, 1
  M  142 add r0, r0, r3
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
  B  141 add r0, r0, r4
--- replace mine 144:145 base 143:144
  M  144 subf r29, r3, r29
  B  143 subf r29, r4, r29
--- replace mine 148:149 base 147:148
  M  148 lwz r3, 0x18(r30)
  B  147 lwz r4, 0x18(r30)
--- replace mine 151:152 base 150:151
  M  151 subf r3, r3, r4
  B  150 subf r3, r4, r3
--- replace mine 215:216 base 214:215
  M  215 bne -800
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper success update inline arithmetic direct
instructions 233/233, structural/exact (0, 7); src 0x3a4 base 0x3a4 insns 233/233
diffs 7: [136, 137, 138, 139, 140, 141, 143]
   136 M lwz r0, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   138 M lwz r4, 0(r28)
       B lwz r0, 0(r28)
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r0, r5
       B subf r4, r5, r4
   141 M add r0, r4, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector and overlap initialization comma expression
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper all count/flag updates comma expression
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper overlap subtraction explicit conversion unsigned int
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## NHTTPi_strnicmp: XHIGH case comparisons signed 64-bit operand views
instructions 68/51, structural/exact (30, 66); src 0x110 base 0xcc insns 68/51
--- insert mine 1:1 base 1:3
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
--- delete mine 2:4 base 4:4
  M    2 xoris r8, r10, 0x8000
  M    3 li r11, 0x41
--- delete mine 5:6 base 5:5
  M    5 li r9, 0x5a
--- replace mine 8:9 base 7:8
  M    8 ble 224
  B    7 ble 160
--- replace mine 23:34 base 22:28
  M   23 b 164
  M   24 srawi r0, r31, 0x1f
  M   25 xoris r7, r10, 0x8000
  M   26 xoris r0, r0, 0x8000
  M   27 subfc r6, r11, r31
  M   28 subfe r7, r7, r0
  M   29 subfe r7, r0, r0
  M   30 neg r7, r7
  M   31 subfic r7, r7, 1
  M   32 srawi r0, r31, 0x1f
  M   33 xoris r6, r0, 0x8000
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
--- replace mine 35:40 base 29:31
  M   35 subfe r6, r6, r8
  M   36 subfe r6, r8, r8
  M   37 neg r6, r6
  M   38 subfic r6, r6, 1
  M   39 and. r0, r7, r6
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
--- replace mine 42:52 base 33:38
  M   42 srawi r0, r12, 0x1f
  M   43 xoris r7, r10, 0x8000
  M   44 xoris r0, r0, 0x8000
  M   45 subfc r6, r11, r12
  M   46 subfe r7, r7, r0
  M   47 subfe r7, r0, r0
  M   48 neg r7, r7
  M   49 subfic r7, r7, 1
  M   50 srawi r0, r12, 0x1f
  M   51 xoris r6, r0, 0x8000
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
--- replace mine 53:58 base 39:41
  M   53 subfe r6, r6, r8
  M   54 subfe r6, r8, r8
  M   55 neg r6, r6
  M   56 subfic r6, r6, 1
  M   57 and. r0, r7, r6
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
--- replace mine 63:64 base 46:47
  M   63 bdnz -216
  B   46 bdnz -152

## NHTTPi_strnicmp: XHIGH case comparisons signed 64-bit bound types
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH case comparisons signed 64-bit upper bound only
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH case comparisons signed 64-bit lower bound only
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH both input byte pointers typed signed char
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH character pointer dereferences explicit signed byte casts
instructions 51/51, structural/exact (2, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 8, 10, 12, 13]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r12, 0(r3)
       B lbz r6, 0(r3)
    10 M lbz r31, 0(r4)
       B lbz r0, 0(r4)
    12 M extsb. r12, r12
       B extsb. r12, r6
    13 M extsb r31, r31
       B extsb r31, r0

## NHTTPi_strnicmp: XHIGH lowercase conversion parameter helper signed long
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH lowercase helper parameter signed 64-bit with int return
instructions 71/51, structural/exact (43, 71); src 0x11c base 0xcc insns 71/51
--- replace mine 0:9 base 0:5
  M    0 stwu r1, -0x20(r1)
  M    1 li r8, 0
  M    2 xoris r10, r8, 0x8000
  M    3 li r9, 0x20
  M    4 stw r31, 0x1c(r1)
  M    5 li r12, 0x41
  M    6 li r11, 0x5a
  M    7 stw r30, 0x18(r1)
  M    8 stw r29, 0x14(r1)
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 11:12 base 7:8
  M   11 ble 216
  B    7 ble 160
--- replace mine 16:18 base 12:14
  M   16 extsb. r30, r6
  M   17 extsb r29, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 19:20 base 15:16
  M   19 cmpwi r29, 0
  B   15 cmpwi r31, 0
--- replace mine 21:22 base 17:18
  M   21 cmpwi r30, 0
  B   17 cmpwi r12, 0
--- replace mine 23:24 base 19:20
  M   23 cmpwi r29, 0
  B   19 cmpwi r31, 0
--- replace mine 26:62 base 22:44
  M   26 b 156
  M   27 srawi r31, r29, 0x1f
  M   28 xoris r7, r8, 0x8000
  M   29 xoris r6, r31, 0x8000
  M   30 subfc r0, r12, r29
  M   31 subfe r7, r7, r6
  M   32 subfe r7, r6, r6
  M   33 neg r7, r7
  M   34 subfic r7, r7, 1
  M   35 subfc r0, r29, r11
  M   36 subfe r0, r6, r10
  M   37 subfe r0, r10, r10
  M   38 neg r0, r0
  M   39 subfic r0, r0, 1
  M   40 and. r0, r7, r0
  M   41 beq 12
  M   42 addc r29, r29, r9
  M   43 adde r0, r31, r8
  M   44 srawi r31, r30, 0x1f
  M   45 xoris r7, r8, 0x8000
  M   46 xoris r6, r31, 0x8000
  M   47 subfc r0, r12, r30
  M   48 subfe r7, r7, r6
  M   49 subfe r7, r6, r6
  M   50 neg r7, r7
  M   51 subfic r7, r7, 1
  M   52 subfc r0, r30, r11
  M   53 subfe r0, r6, r10
  M   54 subfe r0, r10, r10
  M   55 neg r0, r0
  M   56 subfic r0, r0, 1
  M   57 and. r0, r7, r0
  M   58 beq 12
  M   59 addc r30, r30, r9
  M   60 adde r0, r31, r8
  M   61 cmpw r30, r29
  B   22 b 100
  B   23 srawi r7, r31, 0x1f
  B   24 srwi r6, r31, 0x1f
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
  B   29 adde r0, r7, r6
  B   30 and. r0, r8, r0
  B   31 beq 8
  B   32 addi r31, r31, 0x20
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 64:66 base 46:48
  M   64 bdnz -208
  M   65 lwz r31, 0x1c(r1)
  B   46 bdnz -152
  B   47 lwz r31, 0xc(r1)
--- replace mine 67:70 base 49:50
  M   67 lwz r30, 0x18(r1)
  M   68 lwz r29, 0x14(r1)
  M   69 addi r1, r1, 0x20
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: XHIGH logical-not nul checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH logical-not outer nul checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH logical-not inner nul checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH reverse nul equality operands
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH inner nul right first
instructions 51/51, structural/exact (2, 4); src 0xcc base 0xcc insns 51/51
diffs 4: [2, 3, 17, 19]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0

## NHTTPi_strnicmp: XHIGH inner equal chars then nul left
instructions 51/51, structural/exact (3, 4); src 0xcc base 0xcc insns 51/51
diffs 4: [2, 3, 17, 19]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    17 M cmpw r12, r31
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0

## NHTTPi_strnicmp: XHIGH inner equal chars then nul right
instructions 51/51, structural/exact (3, 3); src 0xcc base 0xcc insns 51/51
diffs 3: [2, 3, 17]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    17 M cmpw r12, r31
       B cmpwi r12, 0

## NHTTPi_strnicmp: XHIGH explicit boolean conversion nul checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH postfix length decrement
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH subtraction length assignment
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH add negative one length assignment
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH const regional lookup table views with correct u32 indices
instructions 195/195, structural/exact (0, 12); src 0x30c base 0x30c insns 195/195
diffs 12: [116, 128, 143, 146, 148, 149, 152, 160, 162, 174, 185, 187]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   143 M li r26, 0
       B li r24, 0
   146 M add r24, r5, r0
       B add r27, r5, r0
   148 M add r25, r4, r0
       B add r28, r4, r0
   149 M lwzx r3, r24, r30
       B lwzx r3, r27, r30
   152 M lwzx r0, r25, r30
       B lwzx r0, r28, r30
   160 M lwzx r4, r24, r30
       B lwzx r4, r27, r30
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   185 M addi r26, r26, 1
       B addi r24, r24, 1
   187 M cmpwi r26, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH const regional language table view only
instructions 195/195, structural/exact (0, 10); src 0x30c base 0x30c insns 195/195
diffs 10: [116, 128, 143, 146, 149, 160, 162, 174, 185, 187]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   143 M li r25, 0
       B li r24, 0
   146 M add r24, r5, r0
       B add r27, r5, r0
   149 M lwzx r3, r24, r30
       B lwzx r3, r27, r30
   160 M lwzx r4, r24, r30
       B lwzx r4, r27, r30
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   185 M addi r25, r25, 1
       B addi r24, r24, 1
   187 M cmpwi r25, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH const regional index table view only
instructions 195/195, structural/exact (0, 10); src 0x30c base 0x30c insns 195/195
diffs 10: [116, 128, 143, 146, 148, 152, 162, 174, 185, 187]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   143 M li r25, 0
       B li r24, 0
   146 M add r24, r5, r0
       B add r27, r5, r0
   148 M add r27, r4, r0
       B add r28, r4, r0
   152 M lwzx r0, r24, r30
       B lwzx r0, r28, r30
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   185 M addi r25, r25, 1
       B addi r24, r24, 1
   187 M cmpwi r25, 0x10
       B cmpwi r24, 0x10

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH const pointer to regional lookup table arrays
BUILD FAIL  && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/channelSelect/iplChannelObj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:8)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     682: t (*regionLanguages)[16] = &scModuleData.langGroupLookup[region];
#   Error:                                                                 ^
#   (10209) illegal implicit conversion from 'const char * (*)[16]' to
#   'const char *const  (*)[16]'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: XHIGH regional group list reference kept after selected group query
instructions 195/195, structural/exact (6, 6); src 0x30c base 0x30c insns 195/195
diffs 6: [116, 117, 128, 162, 163, 174]
   116 M addi r24, r3, 0xc
       B mr r30, r3
   117 M mr r3, r24
       B addi r3, r3, 0xc
   128 M mr r3, r24
       B addi r3, r30, 0xc
   162 M addi r24, r3, 0xc
       B mr r30, r3
   163 M mr r3, r24
       B addi r3, r3, 0xc
   174 M mr r3, r24
       B addi r3, r30, 0xc

## pfd_sddrv_finalize: XHIGH inline flag helper with mask parameter
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH inline flag helper with const mask parameter
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH inline flag helper returning masked word
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH inline flag helper taking scalar pointer
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH same-width mask via u32 cast of signed complement
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH final flag accessor result in unsigned int scalar
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH input disk pointer definition const qualification
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: XHIGH final clear mask via arithmetic -1 minus 1
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector output pointer first
BUILD FAIL o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_cache.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_cache.c
# ---------------------------------------
#     555:     pf_u32 num_overlap = end_sector - p_page->sector;
#   Error:     ^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector output pointer last
BUILD FAIL o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_cache.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_cache.c
# ---------------------------------------
#     555:     pf_u32 num_overlap = end_sector - p_page->sector;
#   Error:     ^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH read-only volume pointer local view for all bpb loads
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## NHTTPi_strnicmp: XHIGH uppercase predicate helper returns BOOL
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH uppercase predicate helper returns int
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: XHIGH uppercase predicate helper returns unsigned int
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector output pointer first after declarations
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: XHIGH helper last-sector output pointer last after declarations
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## XHIGH completeness audit
NHTTPi_strnicmp: 44 distinct XHIGH expression/type/helper trials; still open; all source experiments restored.
NWC24iCheckDlHeaderConsistency: 18 distinct XHIGH expression/type/helper trials; still open; all source experiments restored.
pfd_sddrv_finalize: 20 distinct XHIGH expression/type/helper trials; still open; all source experiments restored.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 28 distinct XHIGH expression/type/helper trials; still open; all source experiments restored.
setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: 28 distinct XHIGH expression/type/helper trials; still open; all source experiments restored.
No declaration-order reruns. All five data measures already 100%, or empty sections. No symbol rename/extent adjustment warranted. No gate-passing improvements, so no local commits.

## XHIGH final full gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1388/2248 data 112/112 functions 11/14 fuzzy 87.9359 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] instruction-exact functions: 11/14
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .data size 72 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .text size 2248 match 87.93594
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_strnicmp 99.76471
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_compareToken 54.622223
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_Base64Encode 60.285713
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] baseline: code 1388/2248 data 112 functions 11 fuzzy 87.9359
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8140/12496 data 80/80 functions 25/30 fuzzy 99.1521 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 25/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.15205
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 99.303795
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8140/12496 data 80 functions 25 fuzzy 99.1521
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 3592/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 3592 functions 21 fuzzy 99.0544
[libs/RVL_SDK/src/fa/pf_cache] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_cache] objdiff: code 6464/7396 data None/None functions 35/36 fuzzy 99.9865 linked code 0
[libs/RVL_SDK/src/fa/pf_cache] instruction-exact functions: 35/36
[libs/RVL_SDK/src/fa/pf_cache]   section .text size 7396 match 99.98648
[libs/RVL_SDK/src/fa/pf_cache]   below 100: PFCACHE_DoWriteNumSectorAndFreeIfNeeded 99.8927
[libs/RVL_SDK/src/fa/pf_cache] baseline: code 6464/7396 data None functions 35 fuzzy 99.9865
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10144/10924 data 2216/2216 functions 55/56 fuzzy 99.9927 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 54/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 99.992676
[src/scene/channelSelect/iplChannelObj]   below 100: setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object 99.89744
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.9927
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58569
global complete_code_percent: 72.50912 -> 72.50912
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final NHTTPi_strnicmp
```text
src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
```

Final NWC24iCheckDlHeaderConsistency
```text
src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
```

Final pfd_sddrv_finalize
```text
src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)
```

Final PFCACHE_DoWriteNumSectorAndFreeIfNeeded
```text
src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4
```

Final setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object
```text
src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
```

XHIGH retained outcome: zero new instruction-exact functions; 138 expression/type/helper attempts, including failed compilation attempts. All five owned functions remain open, each with at least three logged distinct XHIGH source attempts. Compiler ties remain a hypothesis, not proof. No source/config changes retained; no commits. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; zero gate regressions, forbidden patterns, or readability warnings.

# MAX round: pointer derivation and helper boundaries
HEAD 320700d49befc4547d5dd14722b191d3adab9b0b; fetched origin/main ab8bece04ed6d37828bb18c5b1b7f9a60ed43e97
The five owned sources and symbols are unchanged versus freshly fetched origin/main. Parent advanced this worktree between rounds. Compiler version already verified by parent. Preserve previous logs; add distinct tests below.

MAX baseline src/scene/channelSelect/iplChannelObj
POOL IDENTICAL up to 20 (mine=20 base=20)
src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

MAX baseline libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL
POOL IDENTICAL up to 1 (mine=1 base=1)
src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

MAX baseline libs/RevoEX/src/nwc24/NWC24Download
POOL IDENTICAL up to 3 (mine=3 base=3)
src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

MAX baseline libs/RVL_SDK/src/fa/pf_cache
POOL IDENTICAL up to 0 (mine=0 base=0)
src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

MAX baseline libs/RVL_SDK/src/fa/driver/sd_drv
POOL IDENTICAL up to 46 (mine=46 base=46)
src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

MAX setLangPane diagnosis: both group results survive a call through the begin/end iterator path; target retains them in r30, current in r28. Full-loop helper extraction failed earlier. Test only the iterator-return helper boundary, pointer/reference const views, and pointer derivation. No volatile candidate: target has no proven extra group-pointer reload.

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps begin iterator, mutable group pointer
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps end iterator, mutable group pointer
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps both iterator, mutable group pointer
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps begin iterator, const group pointer view
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps end iterator, const group pointer view
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps both iterator, const group pointer view
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps begin iterator, mutable group reference
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps end iterator, mutable group reference
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps both iterator, mutable group reference
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps begin iterator, group pointer passed by const reference
instructions 197/195, structural/exact (9, 77); src 0x314 base 0x30c insns 197/195
--- replace mine 112:113 base 112:113
  M  112 beq 112
  B  112 beq 108
--- delete mine 120:121 base 120:120
  M  120 addi r28, r30, 0xc
--- replace mine 129:130 base 128:129
  M  129 mr r3, r28
  B  128 addi r3, r30, 0xc
--- replace mine 139:140 base 138:139
  M  139 b 208
  B  138 b 204
--- replace mine 152:153 base 151:152
  M  152 beq 156
  B  151 beq 152
--- replace mine 159:160 base 158:159
  M  159 bne 112
  B  158 bne 108
--- delete mine 167:168 base 166:166
  M  167 addi r28, r30, 0xc
--- replace mine 176:177 base 174:175
  M  176 mr r3, r28
  B  174 addi r3, r30, 0xc
--- replace mine 190:191 base 188:189
  M  190 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps end iterator, group pointer passed by const reference
instructions 197/195, structural/exact (9, 77); src 0x314 base 0x30c insns 197/195
--- replace mine 112:113 base 112:113
  M  112 beq 112
  B  112 beq 108
--- delete mine 120:121 base 120:120
  M  120 addi r28, r30, 0xc
--- replace mine 129:130 base 128:129
  M  129 mr r3, r28
  B  128 addi r3, r30, 0xc
--- replace mine 139:140 base 138:139
  M  139 b 208
  B  138 b 204
--- replace mine 152:153 base 151:152
  M  152 beq 156
  B  151 beq 152
--- replace mine 159:160 base 158:159
  M  159 bne 112
  B  158 bne 108
--- delete mine 167:168 base 166:166
  M  167 addi r28, r30, 0xc
--- replace mine 176:177 base 174:175
  M  176 mr r3, r28
  B  174 addi r3, r30, 0xc
--- replace mine 190:191 base 188:189
  M  190 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps both iterator, group pointer passed by const reference
instructions 197/195, structural/exact (9, 77); src 0x314 base 0x30c insns 197/195
--- replace mine 112:113 base 112:113
  M  112 beq 112
  B  112 beq 108
--- delete mine 120:121 base 120:120
  M  120 addi r28, r30, 0xc
--- replace mine 129:130 base 128:129
  M  129 mr r3, r28
  B  128 addi r3, r30, 0xc
--- replace mine 139:140 base 138:139
  M  139 b 208
  B  138 b 204
--- replace mine 152:153 base 151:152
  M  152 beq 156
  B  151 beq 152
--- replace mine 159:160 base 158:159
  M  159 bne 112
  B  158 bne 108
--- delete mine 167:168 base 166:166
  M  167 addi r28, r30, 0xc
--- replace mine 176:177 base 174:175
  M  176 mr r3, r28
  B  174 addi r3, r30, 0xc
--- replace mine 190:191 base 188:189
  M  190 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps begin iterator, pane list reference
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps end iterator, pane list reference
instructions 197/195, structural/exact (9, 77); src 0x314 base 0x30c insns 197/195
--- replace mine 112:113 base 112:113
  M  112 beq 112
  B  112 beq 108
--- delete mine 120:121 base 120:120
  M  120 addi r28, r30, 0xc
--- replace mine 129:130 base 128:129
  M  129 mr r3, r28
  B  128 addi r3, r30, 0xc
--- replace mine 139:140 base 138:139
  M  139 b 208
  B  138 b 204
--- replace mine 152:153 base 151:152
  M  152 beq 156
  B  151 beq 152
--- replace mine 159:160 base 158:159
  M  159 bne 112
  B  158 bne 108
--- delete mine 167:168 base 166:166
  M  167 addi r28, r30, 0xc
--- replace mine 176:177 base 174:175
  M  176 mr r3, r28
  B  174 addi r3, r30, 0xc
--- replace mine 190:191 base 188:189
  M  190 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX helper wraps both iterator, pane list reference
instructions 197/195, structural/exact (9, 77); src 0x314 base 0x30c insns 197/195
--- replace mine 112:113 base 112:113
  M  112 beq 112
  B  112 beq 108
--- delete mine 120:121 base 120:120
  M  120 addi r28, r30, 0xc
--- replace mine 129:130 base 128:129
  M  129 mr r3, r28
  B  128 addi r3, r30, 0xc
--- replace mine 139:140 base 138:139
  M  139 b 208
  B  138 b 204
--- replace mine 152:153 base 151:152
  M  152 beq 156
  B  151 beq 152
--- replace mine 159:160 base 158:159
  M  159 bne 112
  B  158 bne 108
--- delete mine 167:168 base 166:166
  M  167 addi r28, r30, 0xc
--- replace mine 176:177 base 174:175
  M  176 mr r3, r28
  B  174 addi r3, r30, 0xc
--- replace mine 190:191 base 188:189
  M  190 blt -160
  B  188 blt -156

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX returned group pointer via find helper
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX returned group pointer via name-first find helper
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX returned group reference via find helper
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX selected group reference explicitly const qualified
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX pointer address passed through group-pointer holder
instructions 195/195, structural/exact (0, 0); src 0x30c base 0x30c insns 195/195
diffs 0: []

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX shallow const Group getter returns mutable list reference
BUILD FAIL  && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/channelSelect/iplChannelObj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:9)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     678:                 nw4r::lyt::Group* const* groupPointer = &group;
#   Error:                                                               ^
#   (10209) illegal implicit conversion from 'const nw4r::lyt::Group **' to
#   'nw4r::lyt::Group *const *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX const Group getter returns const list, iterator path explicit mutable view
BUILD FAIL  && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/channelSelect/iplChannelObj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:9)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     678:                 nw4r::lyt::Group* const* groupPointer = &group;
#   Error:                                                               ^
#   (10209) illegal implicit conversion from 'const nw4r::lyt::Group **' to
#   'nw4r::lyt::Group *const *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX const Group getter returns mutable list by const Group this cast
BUILD FAIL  && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/channelSelect/iplChannelObj.d build/43U/src/src/scene/channelSelect/iplChannelObj.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-d4\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\data-
#   d4\src\scene\channelSelect\iplChannelObj.cpp:9)
### mwcceppc.exe Compiler:
#    File: src\scene\channelSelect\iplChannelObj.cpp
# --------------------------------------------------
#     678:                 nw4r::lyt::Group* const* groupPointer = &group;
#   Error:                                                               ^
#   (10209) illegal implicit conversion from 'const nw4r::lyt::Group **' to
#   'nw4r::lyt::Group *const *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX exact candidate refinement: const reference to group pointer
instructions 195/195, structural/exact (0, 0); src 0x30c base 0x30c insns 195/195
diffs 0: []

## setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: MAX const reference binds directly to FindGroupByName pointer result
instructions 195/195, structural/exact (0, 4); src 0x30c base 0x30c insns 195/195
diffs 4: [116, 128, 162, 174]
   116 M mr r28, r3
       B mr r30, r3
   128 M addi r3, r28, 0xc
       B addi r3, r30, 0xc
   162 M mr r28, r3
       B mr r30, r3
   174 M addi r3, r28, 0xc
       B addi r3, r30, 0xc

## MAX retained exact setLangPane candidate
The differing mr/addi pairs at instruction 116/128 and 162/174 derive the group pointer returned by FindGroupByName. Binding a const reference to each initialized group pointer before traversing its pane list changes the pointer view and yields the target r30 coloring in both branches. Both declarations refer to real group pointers, all values are initialized, and no stack/data objects are added to the emitted object. Directly binding a const reference to the function result reverted to four diffs; the separate initialized pointer is required. Fresh ctxdiff: 195/195 instructions, diffs 0. Pool identical at 20 strings. Data already 2216/2216, no symbol changes.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10924/10924 data 2216/2216 functions 56/56 fuzzy 100.0000 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 55/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 100.0
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.9927
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.83566
global fuzzy_match_percent: 99.58569 -> 99.58572
global complete_code_percent: 72.50912 -> 72.50912
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 320700d4; compared against nearest snapshotted ancestor 73795cb3 (5 commits back)
GATE PASS

Before -> after: instruction-exact 54/56 -> 55/56; objdiff functions 55/56 -> 56/56; code 10144/10924 -> 10924/10924; data 2216/2216 -> 2216/2216. The remaining instruction-only discrepancy was already present in an unrelated objdiff-100 function and is outside this assignment.

## MAX NHTTP start
Fetched origin/main 77439a326861fc7e0fee45e944f84d5c32d57f6e: unit source unchanged from HEAD, so the owned near-miss is not already matched there. Pool identical at 1 string; frame 0x10 and 51/51 instructions match. The only disagreement is hoisted zero vs uppercase-bound initialization order at instructions 2/3, both originating in the signed bitwise uppercase tests within LowerCase. Declaration orders exhausted in earlier rounds; test real readonly character/pointer views before further expression variants. No immediate stack store/reload pair proving volatile. Data 112/112; no rename/extent correction needed.

## NHTTPi_strnicmp: MAX lowercase helper reads int character object
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX lowercase helper reads const int character object
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX lowercase helper reads signed long character object
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX lowercase helper reads const signed long character object
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly character object views used by lowercase helper
instructions 51/51, structural/exact (2, 18); src 0xcc base 0xcc insns 51/51
diffs 18: [2, 3, 12, 13, 15, 17, 19, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    12 M extsb. r31, r6
       B extsb. r12, r6
    13 M extsb r12, r0
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: MAX readonly character views for all nul and case comparisons
instructions 51/51, structural/exact (2, 18); src 0xcc base 0xcc insns 51/51
diffs 18: [2, 3, 12, 13, 15, 17, 19, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    12 M extsb. r31, r6
       B extsb. r12, r6
    13 M extsb r12, r0
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: MAX readonly input pointer object views separate character advance
instructions 51/51, structural/exact (2, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 8, 10, 12, 13]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r12, 0(r3)
       B lbz r6, 0(r3)
    10 M lbz r31, 0(r4)
       B lbz r0, 0(r4)
    12 M extsb. r12, r12
       B extsb. r12, r6
    13 M extsb r31, r31
       B extsb r31, r0

## NHTTPi_strnicmp: MAX readonly length object view used by loop and decrement
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX in-place lowercase helper on int character objects
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX in-place lowercase helper on long character objects
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly local bound objects in case conversion
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly local range array in case conversion
instructions 53/51, structural/exact (8, 53); src 0xd4 base 0xcc insns 53/51
--- replace mine 0:7 base 0:5
  M    0 stwu r1, -0x20(r1)
  M    1 stw r31, 0x1c(r1)
  M    2 lwz r11, 0(0)
  M    3 lwz r10, 0(0)
  M    4 stw r11, 8(r1)
  M    5 srwi r9, r11, 0x1f
  M    6 stw r10, 0xc(r1)
  B    0 stwu r1, -0x10(r1)
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
  B    4 stw r31, 0xc(r1)
--- replace mine 28:31 base 26:29
  M   28 adde r8, r7, r9
  M   29 srawi r7, r10, 0x1f
  M   30 subfc r0, r31, r10
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
--- replace mine 38:41 base 36:39
  M   38 adde r8, r7, r9
  M   39 srawi r7, r10, 0x1f
  M   40 subfc r0, r12, r10
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
--- replace mine 49:50 base 47:48
  M   49 lwz r31, 0x1c(r1)
  B   47 lwz r31, 0xc(r1)
--- replace mine 51:52 base 49:50
  M   51 addi r1, r1, 0x20
  B   49 addi r1, r1, 0x10

## NHTTPi_strnicmp: MAX readonly bound pointers passed to lowercase helper
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly signed boolean object views aboveMinimum first
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly signed boolean object views belowMaximum first
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX only a read through const object view in nul checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX only a read through const object view in case checks
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX only b read through const object view in nul checks
instructions 51/51, structural/exact (2, 18); src 0xcc base 0xcc insns 51/51
diffs 18: [2, 3, 12, 13, 15, 17, 19, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    12 M extsb. r31, r6
       B extsb. r12, r6
    13 M extsb r12, r0
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: MAX only b read through const object view in case checks
instructions 51/51, structural/exact (2, 18); src 0xcc base 0xcc insns 51/51
diffs 18: [2, 3, 12, 13, 15, 17, 19, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    12 M extsb. r31, r6
       B extsb. r12, r6
    13 M extsb r12, r0
       B extsb r31, r0
    15 M cmpwi r12, 0
       B cmpwi r31, 0
    17 M cmpwi r31, 0
       B cmpwi r12, 0
    19 M cmpwi r12, 0
       B cmpwi r31, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## NHTTPi_strnicmp: MAX lowercase helper result typed char
instructions 53/51, structural/exact (7, 37); src 0xd4 base 0xcc insns 53/51
--- replace mine 1:4 base 1:4
  M    1 li r12, 0x41
  M    2 li r11, 0
  M    3 li r10, 0x5a
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- replace mine 7:8 base 7:8
  M    7 ble 168
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r31, r6
  M   13 extsb r9, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 15:16 base 15:16
  M   15 cmpwi r9, 0
  B   15 cmpwi r31, 0
--- insert mine 17:17 base 17:19
  B   17 cmpwi r12, 0
  B   18 bne 20
--- delete mine 18:20 base 20:20
  M   18 bne 20
  M   19 cmpwi r9, 0
--- replace mine 22:33 base 22:23
  M   22 b 108
  M   23 srawi r7, r9, 0x1f
  M   24 srwi r6, r9, 0x1f
  M   25 subfc r0, r12, r9
  M   26 adde r8, r7, r11
  M   27 srawi r7, r10, 0x1f
  M   28 subfc r0, r9, r10
  M   29 adde r0, r7, r6
  M   30 and. r0, r8, r0
  M   31 beq 8
  M   32 addi r9, r9, 0x20
  B   22 b 100
--- replace mine 35:40 base 25:29
  M   35 subfc r0, r12, r31
  M   36 extsb r9, r9
  M   37 adde r8, r7, r11
  M   38 srawi r7, r10, 0x1f
  M   39 subfc r0, r31, r10
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
--- replace mine 44:46 base 33:44
  M   44 extsb r0, r31
  M   45 cmpw r0, r9
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 48:49 base 46:47
  M   48 bdnz -160
  B   46 bdnz -152

## NHTTPi_strnicmp: MAX lowercase helper result typed signed char
instructions 53/51, structural/exact (7, 37); src 0xd4 base 0xcc insns 53/51
--- replace mine 1:4 base 1:4
  M    1 li r12, 0x41
  M    2 li r11, 0
  M    3 li r10, 0x5a
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- replace mine 7:8 base 7:8
  M    7 ble 168
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r31, r6
  M   13 extsb r9, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 15:16 base 15:16
  M   15 cmpwi r9, 0
  B   15 cmpwi r31, 0
--- insert mine 17:17 base 17:19
  B   17 cmpwi r12, 0
  B   18 bne 20
--- delete mine 18:20 base 20:20
  M   18 bne 20
  M   19 cmpwi r9, 0
--- replace mine 22:33 base 22:23
  M   22 b 108
  M   23 srawi r7, r9, 0x1f
  M   24 srwi r6, r9, 0x1f
  M   25 subfc r0, r12, r9
  M   26 adde r8, r7, r11
  M   27 srawi r7, r10, 0x1f
  M   28 subfc r0, r9, r10
  M   29 adde r0, r7, r6
  M   30 and. r0, r8, r0
  M   31 beq 8
  M   32 addi r9, r9, 0x20
  B   22 b 100
--- replace mine 35:40 base 25:29
  M   35 subfc r0, r12, r31
  M   36 extsb r9, r9
  M   37 adde r8, r7, r11
  M   38 srawi r7, r10, 0x1f
  M   39 subfc r0, r31, r10
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
--- replace mine 44:46 base 33:44
  M   44 extsb r0, r31
  M   45 cmpw r0, r9
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 48:49 base 46:47
  M   48 bdnz -160
  B   46 bdnz -152

## NHTTPi_strnicmp: MAX lowercase helper result typed signed short
instructions 53/51, structural/exact (7, 37); src 0xd4 base 0xcc insns 53/51
--- replace mine 1:4 base 1:4
  M    1 li r12, 0x41
  M    2 li r11, 0
  M    3 li r10, 0x5a
  B    1 li r11, 0x41
  B    2 li r9, 0x5a
  B    3 li r10, 0
--- replace mine 7:8 base 7:8
  M    7 ble 168
  B    7 ble 160
--- replace mine 12:14 base 12:14
  M   12 extsb. r31, r6
  M   13 extsb r9, r0
  B   12 extsb. r12, r6
  B   13 extsb r31, r0
--- replace mine 15:16 base 15:16
  M   15 cmpwi r9, 0
  B   15 cmpwi r31, 0
--- insert mine 17:17 base 17:19
  B   17 cmpwi r12, 0
  B   18 bne 20
--- delete mine 18:20 base 20:20
  M   18 bne 20
  M   19 cmpwi r9, 0
--- replace mine 22:33 base 22:23
  M   22 b 108
  M   23 srawi r7, r9, 0x1f
  M   24 srwi r6, r9, 0x1f
  M   25 subfc r0, r12, r9
  M   26 adde r8, r7, r11
  M   27 srawi r7, r10, 0x1f
  M   28 subfc r0, r9, r10
  M   29 adde r0, r7, r6
  M   30 and. r0, r8, r0
  M   31 beq 8
  M   32 addi r9, r9, 0x20
  B   22 b 100
--- replace mine 35:40 base 25:29
  M   35 subfc r0, r12, r31
  M   36 extsh r9, r9
  M   37 adde r8, r7, r11
  M   38 srawi r7, r10, 0x1f
  M   39 subfc r0, r31, r10
  B   25 subfc r0, r11, r31
  B   26 adde r8, r7, r10
  B   27 srawi r7, r9, 0x1f
  B   28 subfc r0, r31, r9
--- replace mine 44:46 base 33:44
  M   44 extsh r0, r31
  M   45 cmpw r0, r9
  B   33 srawi r7, r12, 0x1f
  B   34 srwi r6, r12, 0x1f
  B   35 subfc r0, r11, r12
  B   36 adde r8, r7, r10
  B   37 srawi r7, r9, 0x1f
  B   38 subfc r0, r12, r9
  B   39 adde r0, r7, r6
  B   40 and. r0, r8, r0
  B   41 beq 8
  B   42 addi r12, r12, 0x20
  B   43 cmpw r12, r31
--- replace mine 48:49 base 46:47
  M   48 bdnz -160
  B   46 bdnz -152

## NHTTPi_strnicmp: MAX lowercase helper result typed unsigned long
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX const void byte views from postincremented input pointers
instructions 51/51, structural/exact (2, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 8, 10, 12, 13]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r12, 0(r3)
       B lbz r6, 0(r3)
    10 M lbz r31, 0(r4)
       B lbz r0, 0(r4)
    12 M extsb. r12, r12
       B extsb. r12, r6
    13 M extsb r31, r31
       B extsb r31, r0

## NHTTPi_strnicmp: MAX const signed byte pointer holders from postincremented input pointers
instructions 51/51, structural/exact (2, 6); src 0xcc base 0xcc insns 51/51
diffs 6: [2, 3, 8, 10, 12, 13]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
     8 M lbz r12, 0(r3)
       B lbz r6, 0(r3)
    10 M lbz r31, 0(r4)
       B lbz r0, 0(r4)
    12 M extsb. r12, r12
       B extsb. r12, r6
    13 M extsb r31, r31
       B extsb r31, r0

## NHTTPi_strnicmp: MAX value lowercase helper with readonly int input object view
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX value lowercase helper with readonly long input object view
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX value lowercase helper with readonly const int input object view
instructions 51/51, structural/exact (2, 2); src 0xcc base 0xcc insns 51/51
diffs 2: [2, 3]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0

## NHTTPi_strnicmp: MAX readonly character views with left case conversion first
instructions 51/51, structural/exact (2, 12); src 0xcc base 0xcc insns 51/51
diffs 12: [2, 3, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20

## NHTTPi_strnicmp: MAX readonly character views with left conversion first and inverted comparison operands
instructions 51/51, structural/exact (2, 13); src 0xcc base 0xcc insns 51/51
diffs 13: [2, 3, 23, 24, 25, 28, 32, 33, 34, 35, 38, 42, 43]
     2 M li r10, 0
       B li r9, 0x5a
     3 M li r9, 0x5a
       B li r10, 0
    23 M srawi r7, r12, 0x1f
       B srawi r7, r31, 0x1f
    24 M srwi r6, r12, 0x1f
       B srwi r6, r31, 0x1f
    25 M subfc r0, r11, r12
       B subfc r0, r11, r31
    28 M subfc r0, r12, r9
       B subfc r0, r31, r9
    32 M addi r12, r12, 0x20
       B addi r31, r31, 0x20
    33 M srawi r7, r31, 0x1f
       B srawi r7, r12, 0x1f
    34 M srwi r6, r31, 0x1f
       B srwi r6, r12, 0x1f
    35 M subfc r0, r11, r31
       B subfc r0, r11, r12
    38 M subfc r0, r31, r9
       B subfc r0, r12, r9
    42 M addi r31, r31, 0x20
       B addi r12, r12, 0x20
    43 M cmpw r31, r12
       B cmpw r12, r31

## MAX NHTTP disposition
30 distinct MAX pointer/type/helper attempts made and logged in addition to previous rounds; no improvement retained. All restore operations leave the baseline source unchanged. Structural difference remains only the hoisted zero and Z loads at indices 2/3. Register views sometimes swap character registers, but do not correct constant scheduling. Final declsearch score-only: structural 2, exact 2; exhaustive declaration-order attempts from earlier rounds were not repeated. No justified volatile storage or data repair. Open at objdiff 99.76471%.

## MAX NWC start
Fetched origin/main 7216fd527fee4db057af192c416f9d2fbe0e547a: owned unit source identical versus HEAD and near-miss still present. Pool identical at 3 strings. Target and ours both have frame 0x2c0, task offset 0xa8, 212 instructions and identical body/inline-helper boundaries; only the task address initialization and incoming header/repair copies are reordered at indices 5/6/7. All symbol extents already valid and data 80/80; no correction. Test readonly views of actual pointer/scalar objects after the channel result.

## NWC24iCheckDlHeaderConsistency: MAX task pointer object view typed NWC24DlTask* const*
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 139, 167, 183]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   139 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)
   183 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)

## NWC24iCheckDlHeaderConsistency: MAX task pointer object view typed NWC24DlTask**
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 139, 167, 183]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   139 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)
   183 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)

## NWC24iCheckDlHeaderConsistency: MAX task pointer object view typed NWC24DlTask* const* const
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 139, 167, 183]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   139 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)
   183 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)

## NWC24iCheckDlHeaderConsistency: MAX readonly list-header pointer object view in loop condition
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX readonly repair object view in continue condition
instructions 212/212, structural/exact (2, 5); src 0x350 base 0x350 insns 212/212
diffs 5: [5, 6, 7, 40, 201]
     5 M mr r29, r3
       B addi r31, r1, 0xa8
     6 M mr r28, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
    40 M cmpwi r28, 0
       B cmpwi r29, 0
   201 M lhz r0, 0x14(r29)
       B lhz r0, 0x14(r28)

## NWC24iCheckDlHeaderConsistency: MAX readonly header and repair argument-copy object views
instructions 212/212, structural/exact (2, 5); src 0x350 base 0x350 insns 212/212
diffs 5: [5, 6, 7, 40, 201]
     5 M mr r29, r3
       B addi r31, r1, 0xa8
     6 M mr r28, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
    40 M cmpwi r28, 0
       B cmpwi r29, 0
   201 M lhz r0, 0x14(r29)
       B lhz r0, 0x14(r28)

## NWC24iCheckDlHeaderConsistency: MAX read helper takes task-pointer view NWC24DlTask* const* taskView, NWC24DlId taskId
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 139, 167, 183]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   139 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)
   183 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)

## NWC24iCheckDlHeaderConsistency: MAX read helper takes task-pointer view NWC24DlId taskId, NWC24DlTask* const* taskView
instructions 212/212, structural/exact (5, 6); src 0x350 base 0x350 insns 212/212
diffs 6: [5, 6, 7, 139, 167, 183]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   139 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)
   183 M lhz r4, 0(r31)
       B lhz r4, 0xa8(r1)

## NWC24iCheckDlHeaderConsistency: MAX read helper takes task-pointer view NWC24DlTask** taskView, NWC24DlId taskId
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX validation helper takes readonly task-pointer object view
instructions 212/212, structural/exact (3, 4); src 0x350 base 0x350 insns 212/212
diffs 4: [5, 6, 7, 167]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   167 M lha r0, 0x18(r31)
       B lha r0, 0xc0(r1)

## NWC24iCheckDlHeaderConsistency: MAX loop bound helper takes readonly header-pointer object view
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with task ID type u32
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with task ID type int
instructions 213/212, structural/exact (11, 162); src 0x354 base 0x350 insns 213/212
--- insert mine 5:5 base 5:6
  B    5 addi r31, r1, 0xa8
--- delete mine 7:8 base 8:8
  M    7 addi r31, r1, 0xa8
--- replace mine 10:11 base 10:11
  M   10 b 768
  B   10 b 764
--- replace mine 39:40 base 39:40
  M   39 bne 648
  B   39 bne 644
--- replace mine 41:42 base 41:42
  M   41 beq 640
  B   41 beq 636
--- replace mine 50:51 base 50:51
  M   50 b 296
  B   50 b 292
--- replace mine 58:62 base 58:61
  M   58 cmpw r4, r0
  M   59 bge 20
  M   60 clrlwi r3, r30, 0x10
  M   61 addis r0, r3, 0
  B   58 cmplw r4, r0
  B   59 bge 16
  B   60 clrlwi r0, r30, 0x10
--- replace mine 98:99 base 97:98
  M   98 cmpw r0, r3
  B   97 cmplw r0, r3
--- replace mine 205:206 base 204:205
  M  205 blt -776
  B  204 blt -772

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with task ID type u16
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with task ID type const NWC24DlId
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with buffer view void*
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with buffer view u8*
instructions 212/212, structural/exact (3, 4); src 0x350 base 0x350 insns 212/212
diffs 4: [5, 6, 7, 110]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with buffer view DlTaskData*
instructions 212/212, structural/exact (3, 4); src 0x350 base 0x350 insns 212/212
diffs 4: [5, 6, 7, 110]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31

## NWC24iCheckDlHeaderConsistency: MAX read inline body cloned with buffer view NWC24DlTask* const
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX validation inline body cloned with view NWC24DlTask* const
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX validation inline body cloned with view const void*
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX validation inline body cloned with view const DlTaskData*
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX task stored as one-task array with decayed pointer
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX task pointer derived through pointer to task array
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX repair alias declared u32
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX repair alias declared unsigned int
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX repair alias declared const unsigned int
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX read helper receives task address directly while validation preserves pointer alias
instructions 212/212, structural/exact (3, 4); src 0x350 base 0x350 insns 212/212
diffs 4: [5, 6, 7, 110]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4
   110 M addi r3, r1, 0xa8
       B mr r3, r31

## NWC24iCheckDlHeaderConsistency: MAX input definition qualifiers header-const=True repair-const=False
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX input definition qualifiers header-const=False repair-const=True
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX input definition qualifiers header-const=True repair-const=True
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX typed input aggregate repair-first=False
BUILD FAIL  -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#    1050: skListHeader* header; BOOL repair; } inputs = { header, repair };
#   Error:                                                                 ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## NWC24iCheckDlHeaderConsistency: MAX typed input aggregate repair-first=True
BUILD FAIL  -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#    1050:  repair; DlTaskListHeader* header; } inputs = { repair, header };
#   Error:                                                                 ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## NWC24iCheckDlHeaderConsistency: MAX typed input aggregate const repair-first=False
BUILD FAIL  -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#    1050: skListHeader* header; BOOL repair; } inputs = { header, repair };
#   Error:                                                                 ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## NWC24iCheckDlHeaderConsistency: MAX typed input aggregate const repair-first=True
BUILD FAIL  -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#    1050:  repair; DlTaskListHeader* header; } inputs = { repair, header };
#   Error:                                                                 ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## NWC24iCheckDlHeaderConsistency: MAX nested readonly input-header view at loop-bound helper
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX input struct field assignment layout-repair-first=False init-repair-first=False
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX readonly initialized input struct view layout-repair-first=False
instructions 214/212, structural/exact (22, 211); src 0x358 base 0x350 insns 214/212
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x2d0(r1)
  B    0 stwu r1, -0x2c0(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x2d4(r1)
  M    3 addi r11, r1, 0x2d0
  B    2 stw r0, 0x2c4(r1)
  B    3 addi r11, r1, 0x2c0
--- replace mine 5:8 base 5:8
  M    5 stw r3, 8(r1)
  M    6 mr r29, r3
  M    7 addi r31, r1, 0xb0
  B    5 addi r31, r1, 0xa8
  B    6 mr r28, r3
  B    7 mr r29, r4
--- replace mine 9:12 base 9:11
  M    9 stw r4, 0xc(r1)
  M   10 lis r28, 1
  M   11 b 768
  B    9 lis r27, 1
  B   10 b 764
--- replace mine 40:43 base 39:41
  M   40 bne 648
  M   41 lwz r0, 0xc(r1)
  M   42 cmpwi r0, 0
  B   39 bne 644
  B   40 cmpwi r29, 0
--- replace mine 83:84 base 81:82
  M   83 addi r3, r1, 0x10
  B   81 addi r3, r1, 8
--- replace mine 104:105 base 102:103
  M  104 addi r3, r1, 0x10
  B  102 addi r3, r1, 8
--- replace mine 110:111 base 108:109
  M  110 mr r27, r3
  B  108 mr r26, r3
--- replace mine 113:114 base 111:112
  M  113 addi r5, r1, 0x10
  B  111 addi r5, r1, 8
--- replace mine 117:118 base 115:116
  M  117 li r27, 0
  B  115 li r26, 0
--- replace mine 119:121 base 117:119
  M  119 mr r27, r3
  M  120 addi r3, r1, 0x10
  B  117 mr r26, r3
  B  118 addi r3, r1, 8
--- replace mine 122:123 base 120:121
  M  122 cmpwi r27, 0
  B  120 cmpwi r26, 0
--- replace mine 124:125 base 122:123
  M  124 mr r3, r27
  B  122 mr r3, r26
--- replace mine 141:142 base 139:140
  M  141 lhz r4, 0xb0(r1)
  B  139 lhz r4, 0xa8(r1)
--- replace mine 156:158 base 154:156
  M  156 addi r0, r28, -1
  M  157 sth r0, 0xb0(r1)
  B  154 addi r0, r27, -1
  B  155 sth r0, 0xa8(r1)
--- replace mine 169:170 base 167:168
  M  169 lha r0, 0xc8(r1)
  B  167 lha r0, 0xc0(r1)
--- replace mine 185:186 base 183:184
  M  185 lhz r4, 0xb0(r1)
  B  183 lhz r4, 0xa8(r1)
--- replace mine 200:202 base 198:200
  M  200 addi r0, r28, -1
  M  201 sth r0, 0xb0(r1)
  B  198 addi r0, r27, -1
  B  199 sth r0, 0xa8(r1)
--- replace mine 203:204 base 201:202
  M  203 lhz r0, 0x14(r29)
  B  201 lhz r0, 0x14(r28)
--- replace mine 206:208 base 204:206
  M  206 blt -776
  M  207 addi r11, r1, 0x2d0
  B  204 blt -772
  B  205 addi r11, r1, 0x2c0
--- replace mine 210:211 base 208:209
  M  210 lwz r0, 0x2d4(r1)
  B  208 lwz r0, 0x2c4(r1)
--- replace mine 212:213 base 210:211
  M  212 addi r1, r1, 0x2d0
  B  210 addi r1, r1, 0x2c0

## NWC24iCheckDlHeaderConsistency: MAX input struct field assignment layout-repair-first=False init-repair-first=True
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX input struct field assignment layout-repair-first=True init-repair-first=False
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## NWC24iCheckDlHeaderConsistency: MAX readonly initialized input struct view layout-repair-first=True
instructions 214/212, structural/exact (22, 211); src 0x358 base 0x350 insns 214/212
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x2d0(r1)
  B    0 stwu r1, -0x2c0(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x2d4(r1)
  M    3 addi r11, r1, 0x2d0
  B    2 stw r0, 0x2c4(r1)
  B    3 addi r11, r1, 0x2c0
--- replace mine 5:8 base 5:8
  M    5 stw r3, 0xc(r1)
  M    6 mr r29, r3
  M    7 addi r31, r1, 0xb0
  B    5 addi r31, r1, 0xa8
  B    6 mr r28, r3
  B    7 mr r29, r4
--- replace mine 9:12 base 9:11
  M    9 stw r4, 8(r1)
  M   10 lis r28, 1
  M   11 b 768
  B    9 lis r27, 1
  B   10 b 764
--- replace mine 40:43 base 39:41
  M   40 bne 648
  M   41 lwz r0, 8(r1)
  M   42 cmpwi r0, 0
  B   39 bne 644
  B   40 cmpwi r29, 0
--- replace mine 83:84 base 81:82
  M   83 addi r3, r1, 0x10
  B   81 addi r3, r1, 8
--- replace mine 104:105 base 102:103
  M  104 addi r3, r1, 0x10
  B  102 addi r3, r1, 8
--- replace mine 110:111 base 108:109
  M  110 mr r27, r3
  B  108 mr r26, r3
--- replace mine 113:114 base 111:112
  M  113 addi r5, r1, 0x10
  B  111 addi r5, r1, 8
--- replace mine 117:118 base 115:116
  M  117 li r27, 0
  B  115 li r26, 0
--- replace mine 119:121 base 117:119
  M  119 mr r27, r3
  M  120 addi r3, r1, 0x10
  B  117 mr r26, r3
  B  118 addi r3, r1, 8
--- replace mine 122:123 base 120:121
  M  122 cmpwi r27, 0
  B  120 cmpwi r26, 0
--- replace mine 124:125 base 122:123
  M  124 mr r3, r27
  B  122 mr r3, r26
--- replace mine 141:142 base 139:140
  M  141 lhz r4, 0xb0(r1)
  B  139 lhz r4, 0xa8(r1)
--- replace mine 156:158 base 154:156
  M  156 addi r0, r28, -1
  M  157 sth r0, 0xb0(r1)
  B  154 addi r0, r27, -1
  B  155 sth r0, 0xa8(r1)
--- replace mine 169:170 base 167:168
  M  169 lha r0, 0xc8(r1)
  B  167 lha r0, 0xc0(r1)
--- replace mine 185:186 base 183:184
  M  185 lhz r4, 0xb0(r1)
  B  183 lhz r4, 0xa8(r1)
--- replace mine 200:202 base 198:200
  M  200 addi r0, r28, -1
  M  201 sth r0, 0xb0(r1)
  B  198 addi r0, r27, -1
  B  199 sth r0, 0xa8(r1)
--- replace mine 203:204 base 201:202
  M  203 lhz r0, 0x14(r29)
  B  201 lhz r0, 0x14(r28)
--- replace mine 206:208 base 204:206
  M  206 blt -776
  M  207 addi r11, r1, 0x2d0
  B  204 blt -772
  B  205 addi r11, r1, 0x2c0
--- replace mine 210:211 base 208:209
  M  210 lwz r0, 0x2d4(r1)
  B  208 lwz r0, 0x2c4(r1)
--- replace mine 212:213 base 210:211
  M  212 addi r1, r1, 0x2d0
  B  210 addi r1, r1, 0x2c0

## NWC24iCheckDlHeaderConsistency: MAX input struct field assignment layout-repair-first=True init-repair-first=True
instructions 212/212, structural/exact (2, 3); src 0x350 base 0x350 insns 212/212
diffs 3: [5, 6, 7]
     5 M mr r28, r3
       B addi r31, r1, 0xa8
     6 M mr r29, r4
       B mr r28, r3
     7 M addi r31, r1, 0xa8
       B mr r29, r4

## MAX NWC disposition
42 MAX task/input pointer-view, input-definition/type, array-derivation, aggregate, and inline-boundary attempts logged; no improvement retained. Four aggregate-initializer tests were repaired with supported field assignments in subsequent tests. Task-pointer views preserved count but changed direct stack field loads to pointer-relative loads; every valid variant retained the same prologue ordering difference. Final declsearch score-only: structural 2, exact 3. Earlier declaration permutations were exhausted and not repeated. Baseline source restored; open at objdiff 98.77358%.

## MAX cache start
Fetched origin/main a8ab2099cdf66a22205c6faec73834eb7f771168: owned unit source identical versus HEAD, so no duplicate match. Empty pools identical; no target/source data objects need repair. Both have frame 0x30 and 233 instructions. The four differing instructions at 136/137/139/140 map to end_sector - 1 and end_sector - p_page->sector in PFCACHE_RecordPageEndOverlap, in the page-overlaps-write-end branch after pf_memcpy. Sum operand order already num_sector + sector, as target. Page-sector and end-sector temporaries swap r4/r5, all later bookkeeping/flags/pointer math exact. Test readonly views and real in-place overlap outputs before revisiting broader expression boundaries.

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper takes page-pointer object view PF_CACHE_PAGE* const*
instructions 236/233, structural/exact (24, 224); src 0x3b0 base 0x3a4 insns 236/233
--- replace mine 5:6 base 5:6
  M    5 li r0, 0
  B    5 li r30, 0
--- replace mine 7:8 base 7:8
  M    7 stw r0, 0(r8)
  B    7 stw r30, 0(r8)
--- replace mine 14:17 base 14:16
  M   14 add r30, r6, r7
  M   15 li r31, 0
  M   16 cmpwi r31, 0
  B   14 add r31, r6, r7
  B   15 cmpwi r30, 0
--- replace mine 18:19 base 17:18
  M   18 lwz r31, 0(r24)
  B   17 lwz r30, 0(r24)
--- replace mine 20:21 base 19:20
  M   20 lwz r31, 0x20(r31)
  B   19 lwz r30, 0x20(r30)
--- replace mine 22:23 base 21:22
  M   22 cmplw r31, r0
  B   21 cmplw r30, r0
--- replace mine 24:25 base 23:24
  M   24 li r31, 0
  B   23 li r30, 0
--- replace mine 27:28 base 26:27
  M   27 lwz r3, 0x18(r31)
  B   26 lwz r3, 0x18(r30)
--- replace mine 31:33 base 30:32
  M   31 lwz r0, 4(r31)
  M   32 stw r0, 8(r31)
  B   30 lwz r0, 4(r30)
  B   31 stw r0, 8(r30)
--- replace mine 34:36 base 33:35
  M   34 lwz r31, 0x20(r31)
  M   35 lhz r0, 0(r31)
  B   33 lwz r30, 0x20(r30)
  B   34 lhz r0, 0(r30)
--- replace mine 38:43 base 37:42
  M   38 li r31, 0
  M   39 cmpwi r31, 0
  M   40 beq 696
  M   41 lwz r3, 0x18(r31)
  M   42 addis r0, r3, 1
  B   37 li r30, 0
  B   38 cmpwi r30, 0
  B   39 beq 688
  B   40 lwz r7, 0x18(r30)
  B   41 addis r0, r7, 1
--- replace mine 44:46 base 43:45
  M   44 beq 680
  M   45 cmplw r3, r26
  B   43 beq 672
  B   44 cmplw r7, r26
--- replace mine 47:50 base 46:49
  M   47 lwz r0, 0x14(r31)
  M   48 add r0, r3, r0
  M   49 cmplw r0, r30
  B   46 lwz r0, 0x14(r30)
  B   47 add r0, r7, r0
  B   48 cmplw r0, r31
--- replace mine 52:54 base 51:53
  M   52 subf r0, r3, r26
  M   53 lwz r3, 4(r31)
  B   51 subf r0, r7, r26
  B   52 lwz r3, 4(r30)
--- replace mine 64:65 base 63:64
  M   64 lhz r3, 0(r31)
  B   63 lhz r3, 0(r30)
--- replace mine 66:68 base 65:67
  M   66 sth r3, 0(r31)
  M   67 lwz r3, 0x18(r31)
  B   65 sth r3, 0(r30)
  B   66 lwz r3, 0x18(r30)
--- replace mine 69:70 base 68:69
  M   69 lwz r6, 0xc(r31)
  B   68 lwz r6, 0xc(r30)
--- replace mine 71:72 base 70:71
  M   71 lwz r4, 4(r31)
  B   70 lwz r4, 4(r30)
--- replace mine 78:81 base 77:80
  M   78 stw r3, 0xc(r31)
  M   79 stw r4, 0x10(r31)
  M   80 b 536
  B   77 stw r3, 0xc(r30)
  B   78 stw r4, 0x10(r30)
  B   79 b 528
--- replace mine 83:86 base 82:85
  M   83 stw r3, 0xc(r31)
  M   84 b 520
  M   85 lwz r0, 0x10(r31)
  B   82 stw r3, 0xc(r30)
  B   83 b 512
  B   84 lwz r0, 0x10(r30)
--- replace mine 87:91 base 86:90
  M   87 bge 508
  M   88 stw r4, 0x10(r31)
  M   89 b 500
  M   90 cmplw r3, r26
  B   86 bge 500
  B   87 stw r4, 0x10(r30)
  B   88 b 492
  B   89 cmplw r7, r26
--- replace mine 92:95 base 91:94
  M   92 lwz r4, 0x14(r31)
  M   93 add r0, r3, r4
  M   94 cmplw r0, r30
  B   91 lwz r4, 0x14(r30)
  B   92 add r0, r7, r4
  B   93 cmplw r0, r31
--- replace mine 97:99 base 96:98
  M   97 subf r0, r26, r3
  M   98 lwz r3, 4(r31)
  B   96 subf r0, r26, r7
  B   97 lwz r3, 4(r30)
--- replace mine 103:104 base 102:103
  M  103 lwz r3, 0x14(r31)
  B  102 lwz r3, 0x14(r30)
--- replace mine 108:109 base 107:108
  M  108 lhz r0, 0(r31)
  B  107 lhz r0, 0(r30)
--- replace mine 110:114 base 109:113
  M  110 sth r0, 0(r31)
  M  111 lwz r0, 4(r31)
  M  112 stw r0, 0xc(r31)
  M  113 lwz r3, 0x14(r31)
  B  109 sth r0, 0(r30)
  B  110 lwz r0, 4(r30)
  B  111 stw r0, 0xc(r30)
  B  112 lwz r3, 0x14(r30)
--- replace mine 116:117 base 115:116
  M  116 lwz r4, 4(r31)
  B  115 lwz r4, 4(r30)
--- replace mine 119:130 base 118:128
  M  119 stw r0, 0x10(r31)
  M  120 b 376
  M  121 cmplw r3, r26
  M  122 ble 164
  M  123 cmplw r3, r30
  M  124 bge 156
  M  125 lwz r0, 0x14(r31)
  M  126 add r0, r3, r0
  M  127 cmplw r0, r30
  M  128 blt 140
  M  129 lwz r0, 0x18(r31)
  B  118 stw r0, 0x10(r30)
  B  119 b 368
  B  120 cmplw r7, r26
  B  121 ble 160
  B  122 cmplw r7, r31
  B  123 bge 152
  B  124 lwz r0, 0x14(r30)
  B  125 add r0, r7, r0
  B  126 cmplw r0, r31
  B  127 blt 136
--- replace mine 131:135 base 129:133
  M  131 subf r3, r26, r0
  M  132 subf r0, r0, r30
  M  133 slw r4, r3, r5
  M  134 lwz r3, 4(r31)
  B  129 subf r4, r26, r7
  B  130 subf r0, r7, r31
  B  131 lwz r3, 4(r30)
  B  132 slw r4, r4, r5
--- replace mine 138:140 base 136:138
  M  138 lwz r4, 0x18(r31)
  M  139 add r5, r27, r26
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 141:143 base 139:141
  M  141 addi r3, r5, -1
  M  142 subf r4, r4, r5
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 146:147 base 144:145
  M  146 lhz r0, 0(r31)
  B  144 lhz r0, 0(r30)
--- replace mine 148:151 base 146:149
  M  148 sth r0, 0(r31)
  M  149 lwz r4, 0x18(r31)
  M  150 lwz r5, 4(r31)
  B  146 sth r0, 0(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
--- replace mine 154:155 base 152:153
  M  154 stw r5, 0xc(r31)
  B  152 stw r5, 0xc(r30)
--- replace mine 156:157 base 154:155
  M  156 lwz r0, 0x10(r31)
  B  154 lwz r0, 0x10(r30)
--- replace mine 160:163 base 158:165
  M  160 bge 216
  M  161 stw r3, 0x10(r31)
  M  162 b 208
  B  158 bge 212
  B  159 stw r3, 0x10(r30)
  B  160 b 204
  B  161 cmplw r7, r26
  B  162 bge 196
  B  163 lwz r0, 0x14(r30)
  B  164 add r3, r7, r0
--- replace mine 164:172 base 166:174
  M  164 bge 200
  M  165 lwz r6, 0x14(r31)
  M  166 add r0, r3, r6
  M  167 cmplw r0, r26
  M  168 ble 184
  M  169 cmplw r0, r30
  M  170 bgt 176
  M  171 lwz r0, 0x18(r31)
  B  166 ble 180
  B  167 cmplw r3, r31
  B  168 bgt 172
  B  169 lbz r6, 0x20(r23)
  B  170 subf r3, r7, r26
  B  171 lwz r5, 4(r30)
  B  172 subf r0, r3, r0
  B  173 slw r3, r3, r6
--- delete mine 173:178 base 175:175
  M  173 lbz r7, 0x20(r23)
  M  174 subf r0, r0, r26
  M  175 lwz r5, 4(r31)
  M  176 slw r3, r0, r7
  M  177 subf r0, r0, r6
--- replace mine 179:180 base 176:177
  M  179 slw r5, r0, r7
  B  176 slw r5, r0, r6
--- replace mine 181:183 base 178:180
  M  181 lwz r0, 0x18(r31)
  M  182 lwz r3, 0x14(r31)
  B  178 lwz r0, 0x18(r30)
  B  179 lwz r3, 0x14(r30)
--- replace mine 189:190 base 186:187
  M  189 lhz r0, 0(r31)
  B  186 lhz r0, 0(r30)
--- replace mine 191:194 base 188:191
  M  191 sth r0, 0(r31)
  M  192 lwz r3, 0x18(r31)
  M  193 lwz r0, 0x14(r31)
  B  188 sth r0, 0(r30)
  B  189 lwz r3, 0x18(r30)
  B  190 lwz r0, 0x14(r30)
--- replace mine 195:196 base 192:193
  M  195 lwz r5, 0xc(r31)
  B  192 lwz r5, 0xc(r30)
--- replace mine 200:201 base 197:198
  M  200 lwz r4, 4(r31)
  B  197 lwz r4, 4(r30)
--- replace mine 206:208 base 203:205
  M  206 stw r0, 0xc(r31)
  M  207 lwz r3, 0x14(r31)
  B  203 stw r0, 0xc(r30)
  B  204 lwz r3, 0x14(r30)
--- replace mine 210:211 base 207:208
  M  210 lwz r4, 4(r31)
  B  207 lwz r4, 4(r30)
--- replace mine 213:215 base 210:212
  M  213 stw r0, 0x10(r31)
  M  214 cmpwi r31, 0
  B  210 stw r0, 0x10(r30)
  B  211 cmpwi r30, 0
--- replace mine 217:218 base 214:215
  M  217 bne -804
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper takes page-pointer object view PF_CACHE_PAGE**
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper takes page-pointer object view PF_CACHE_PAGE* const* const
instructions 236/233, structural/exact (24, 224); src 0x3b0 base 0x3a4 insns 236/233
--- replace mine 5:6 base 5:6
  M    5 li r0, 0
  B    5 li r30, 0
--- replace mine 7:8 base 7:8
  M    7 stw r0, 0(r8)
  B    7 stw r30, 0(r8)
--- replace mine 14:17 base 14:16
  M   14 add r30, r6, r7
  M   15 li r31, 0
  M   16 cmpwi r31, 0
  B   14 add r31, r6, r7
  B   15 cmpwi r30, 0
--- replace mine 18:19 base 17:18
  M   18 lwz r31, 0(r24)
  B   17 lwz r30, 0(r24)
--- replace mine 20:21 base 19:20
  M   20 lwz r31, 0x20(r31)
  B   19 lwz r30, 0x20(r30)
--- replace mine 22:23 base 21:22
  M   22 cmplw r31, r0
  B   21 cmplw r30, r0
--- replace mine 24:25 base 23:24
  M   24 li r31, 0
  B   23 li r30, 0
--- replace mine 27:28 base 26:27
  M   27 lwz r3, 0x18(r31)
  B   26 lwz r3, 0x18(r30)
--- replace mine 31:33 base 30:32
  M   31 lwz r0, 4(r31)
  M   32 stw r0, 8(r31)
  B   30 lwz r0, 4(r30)
  B   31 stw r0, 8(r30)
--- replace mine 34:36 base 33:35
  M   34 lwz r31, 0x20(r31)
  M   35 lhz r0, 0(r31)
  B   33 lwz r30, 0x20(r30)
  B   34 lhz r0, 0(r30)
--- replace mine 38:43 base 37:42
  M   38 li r31, 0
  M   39 cmpwi r31, 0
  M   40 beq 696
  M   41 lwz r3, 0x18(r31)
  M   42 addis r0, r3, 1
  B   37 li r30, 0
  B   38 cmpwi r30, 0
  B   39 beq 688
  B   40 lwz r7, 0x18(r30)
  B   41 addis r0, r7, 1
--- replace mine 44:46 base 43:45
  M   44 beq 680
  M   45 cmplw r3, r26
  B   43 beq 672
  B   44 cmplw r7, r26
--- replace mine 47:50 base 46:49
  M   47 lwz r0, 0x14(r31)
  M   48 add r0, r3, r0
  M   49 cmplw r0, r30
  B   46 lwz r0, 0x14(r30)
  B   47 add r0, r7, r0
  B   48 cmplw r0, r31
--- replace mine 52:54 base 51:53
  M   52 subf r0, r3, r26
  M   53 lwz r3, 4(r31)
  B   51 subf r0, r7, r26
  B   52 lwz r3, 4(r30)
--- replace mine 64:65 base 63:64
  M   64 lhz r3, 0(r31)
  B   63 lhz r3, 0(r30)
--- replace mine 66:68 base 65:67
  M   66 sth r3, 0(r31)
  M   67 lwz r3, 0x18(r31)
  B   65 sth r3, 0(r30)
  B   66 lwz r3, 0x18(r30)
--- replace mine 69:70 base 68:69
  M   69 lwz r6, 0xc(r31)
  B   68 lwz r6, 0xc(r30)
--- replace mine 71:72 base 70:71
  M   71 lwz r4, 4(r31)
  B   70 lwz r4, 4(r30)
--- replace mine 78:81 base 77:80
  M   78 stw r3, 0xc(r31)
  M   79 stw r4, 0x10(r31)
  M   80 b 536
  B   77 stw r3, 0xc(r30)
  B   78 stw r4, 0x10(r30)
  B   79 b 528
--- replace mine 83:86 base 82:85
  M   83 stw r3, 0xc(r31)
  M   84 b 520
  M   85 lwz r0, 0x10(r31)
  B   82 stw r3, 0xc(r30)
  B   83 b 512
  B   84 lwz r0, 0x10(r30)
--- replace mine 87:91 base 86:90
  M   87 bge 508
  M   88 stw r4, 0x10(r31)
  M   89 b 500
  M   90 cmplw r3, r26
  B   86 bge 500
  B   87 stw r4, 0x10(r30)
  B   88 b 492
  B   89 cmplw r7, r26
--- replace mine 92:95 base 91:94
  M   92 lwz r4, 0x14(r31)
  M   93 add r0, r3, r4
  M   94 cmplw r0, r30
  B   91 lwz r4, 0x14(r30)
  B   92 add r0, r7, r4
  B   93 cmplw r0, r31
--- replace mine 97:99 base 96:98
  M   97 subf r0, r26, r3
  M   98 lwz r3, 4(r31)
  B   96 subf r0, r26, r7
  B   97 lwz r3, 4(r30)
--- replace mine 103:104 base 102:103
  M  103 lwz r3, 0x14(r31)
  B  102 lwz r3, 0x14(r30)
--- replace mine 108:109 base 107:108
  M  108 lhz r0, 0(r31)
  B  107 lhz r0, 0(r30)
--- replace mine 110:114 base 109:113
  M  110 sth r0, 0(r31)
  M  111 lwz r0, 4(r31)
  M  112 stw r0, 0xc(r31)
  M  113 lwz r3, 0x14(r31)
  B  109 sth r0, 0(r30)
  B  110 lwz r0, 4(r30)
  B  111 stw r0, 0xc(r30)
  B  112 lwz r3, 0x14(r30)
--- replace mine 116:117 base 115:116
  M  116 lwz r4, 4(r31)
  B  115 lwz r4, 4(r30)
--- replace mine 119:130 base 118:128
  M  119 stw r0, 0x10(r31)
  M  120 b 376
  M  121 cmplw r3, r26
  M  122 ble 164
  M  123 cmplw r3, r30
  M  124 bge 156
  M  125 lwz r0, 0x14(r31)
  M  126 add r0, r3, r0
  M  127 cmplw r0, r30
  M  128 blt 140
  M  129 lwz r0, 0x18(r31)
  B  118 stw r0, 0x10(r30)
  B  119 b 368
  B  120 cmplw r7, r26
  B  121 ble 160
  B  122 cmplw r7, r31
  B  123 bge 152
  B  124 lwz r0, 0x14(r30)
  B  125 add r0, r7, r0
  B  126 cmplw r0, r31
  B  127 blt 136
--- replace mine 131:135 base 129:133
  M  131 subf r3, r26, r0
  M  132 subf r0, r0, r30
  M  133 slw r4, r3, r5
  M  134 lwz r3, 4(r31)
  B  129 subf r4, r26, r7
  B  130 subf r0, r7, r31
  B  131 lwz r3, 4(r30)
  B  132 slw r4, r4, r5
--- replace mine 138:140 base 136:138
  M  138 lwz r4, 0x18(r31)
  M  139 add r5, r27, r26
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 141:143 base 139:141
  M  141 addi r3, r5, -1
  M  142 subf r4, r4, r5
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 146:147 base 144:145
  M  146 lhz r0, 0(r31)
  B  144 lhz r0, 0(r30)
--- replace mine 148:151 base 146:149
  M  148 sth r0, 0(r31)
  M  149 lwz r4, 0x18(r31)
  M  150 lwz r5, 4(r31)
  B  146 sth r0, 0(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
--- replace mine 154:155 base 152:153
  M  154 stw r5, 0xc(r31)
  B  152 stw r5, 0xc(r30)
--- replace mine 156:157 base 154:155
  M  156 lwz r0, 0x10(r31)
  B  154 lwz r0, 0x10(r30)
--- replace mine 160:163 base 158:165
  M  160 bge 216
  M  161 stw r3, 0x10(r31)
  M  162 b 208
  B  158 bge 212
  B  159 stw r3, 0x10(r30)
  B  160 b 204
  B  161 cmplw r7, r26
  B  162 bge 196
  B  163 lwz r0, 0x14(r30)
  B  164 add r3, r7, r0
--- replace mine 164:172 base 166:174
  M  164 bge 200
  M  165 lwz r6, 0x14(r31)
  M  166 add r0, r3, r6
  M  167 cmplw r0, r26
  M  168 ble 184
  M  169 cmplw r0, r30
  M  170 bgt 176
  M  171 lwz r0, 0x18(r31)
  B  166 ble 180
  B  167 cmplw r3, r31
  B  168 bgt 172
  B  169 lbz r6, 0x20(r23)
  B  170 subf r3, r7, r26
  B  171 lwz r5, 4(r30)
  B  172 subf r0, r3, r0
  B  173 slw r3, r3, r6
--- delete mine 173:178 base 175:175
  M  173 lbz r7, 0x20(r23)
  M  174 subf r0, r0, r26
  M  175 lwz r5, 4(r31)
  M  176 slw r3, r0, r7
  M  177 subf r0, r0, r6
--- replace mine 179:180 base 176:177
  M  179 slw r5, r0, r7
  B  176 slw r5, r0, r6
--- replace mine 181:183 base 178:180
  M  181 lwz r0, 0x18(r31)
  M  182 lwz r3, 0x14(r31)
  B  178 lwz r0, 0x18(r30)
  B  179 lwz r3, 0x14(r30)
--- replace mine 189:190 base 186:187
  M  189 lhz r0, 0(r31)
  B  186 lhz r0, 0(r30)
--- replace mine 191:194 base 188:191
  M  191 sth r0, 0(r31)
  M  192 lwz r3, 0x18(r31)
  M  193 lwz r0, 0x14(r31)
  B  188 sth r0, 0(r30)
  B  189 lwz r3, 0x18(r30)
  B  190 lwz r0, 0x14(r30)
--- replace mine 195:196 base 192:193
  M  195 lwz r5, 0xc(r31)
  B  192 lwz r5, 0xc(r30)
--- replace mine 200:201 base 197:198
  M  200 lwz r4, 4(r31)
  B  197 lwz r4, 4(r30)
--- replace mine 206:208 base 203:205
  M  206 stw r0, 0xc(r31)
  M  207 lwz r3, 0x14(r31)
  B  203 stw r0, 0xc(r30)
  B  204 lwz r3, 0x14(r30)
--- replace mine 210:211 base 207:208
  M  210 lwz r4, 4(r31)
  B  207 lwz r4, 4(r30)
--- replace mine 213:215 base 210:212
  M  213 stw r0, 0x10(r31)
  M  214 cmpwi r31, 0
  B  210 stw r0, 0x10(r30)
  B  211 cmpwi r30, 0
--- replace mine 217:218 base 214:215
  M  217 bne -804
  B  214 bne -796

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper page parameter const at definition
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper updates caller end-sector scalar in place
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper writes named overlap through caller end-sector pointer
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX end-sector value parameter read through const scalar object view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX page-sector field read through const scalar object view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX local readonly page-pointer object view only for sector load
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX last-sector return read through const scalar object view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap updates read through const scalar object view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper end_sector widened to unsigned long long with 32-bit results
instructions 235/233, structural/exact (16, 228); src 0x3ac base 0x3a4 insns 235/233
--- replace mine 5:17 base 5:16
  M    5 li r29, 0
  M    6 mr r26, r7
  M    7 stw r29, 0(r8)
  M    8 mr r22, r3
  M    9 mr r23, r4
  M   10 mr r24, r5
  M   11 mr r25, r6
  M   12 mr r27, r8
  M   13 mr r28, r26
  M   14 add r30, r6, r7
  M   15 li r31, -1
  M   16 cmpwi r29, 0
  B    5 li r30, 0
  B    6 mr r27, r7
  B    7 stw r30, 0(r8)
  B    8 mr r23, r3
  B    9 mr r24, r4
  B   10 mr r25, r5
  B   11 mr r26, r6
  B   12 mr r28, r8
  B   13 mr r29, r27
  B   14 add r31, r6, r7
  B   15 cmpwi r30, 0
--- replace mine 18:19 base 17:18
  M   18 lwz r29, 0(r23)
  B   17 lwz r30, 0(r24)
--- replace mine 20:23 base 19:22
  M   20 lwz r29, 0x20(r29)
  M   21 lwz r0, 0(r23)
  M   22 cmplw r29, r0
  B   19 lwz r30, 0x20(r30)
  B   20 lwz r0, 0(r24)
  B   21 cmplw r30, r0
--- replace mine 24:25 base 23:24
  M   24 li r29, 0
  B   23 li r30, 0
--- replace mine 27:28 base 26:27
  M   27 lwz r3, 0x18(r29)
  B   26 lwz r3, 0x18(r30)
--- replace mine 31:33 base 30:32
  M   31 lwz r0, 4(r29)
  M   32 stw r0, 8(r29)
  B   30 lwz r0, 4(r30)
  B   31 stw r0, 8(r30)
--- replace mine 34:36 base 33:35
  M   34 lwz r29, 0x20(r29)
  M   35 lhz r0, 0(r29)
  B   33 lwz r30, 0x20(r30)
  B   34 lhz r0, 0(r30)
--- replace mine 38:42 base 37:41
  M   38 li r29, 0
  M   39 cmpwi r29, 0
  M   40 beq 692
  M   41 lwz r7, 0x18(r29)
  B   37 li r30, 0
  B   38 cmpwi r30, 0
  B   39 beq 688
  B   40 lwz r7, 0x18(r30)
--- replace mine 44:46 base 43:45
  M   44 beq 676
  M   45 cmplw r7, r25
  B   43 beq 672
  B   44 cmplw r7, r26
--- replace mine 47:48 base 46:47
  M   47 lwz r0, 0x14(r29)
  B   46 lwz r0, 0x14(r30)
--- replace mine 49:50 base 48:49
  M   49 cmplw r0, r30
  B   48 cmplw r0, r31
--- replace mine 51:55 base 50:54
  M   51 lbz r5, 0x20(r22)
  M   52 subf r0, r7, r25
  M   53 lwz r3, 4(r29)
  M   54 mr r4, r24
  B   50 lbz r5, 0x20(r23)
  B   51 subf r0, r7, r26
  B   52 lwz r3, 4(r30)
  B   53 mr r4, r25
--- replace mine 56:57 base 55:56
  M   56 slw r5, r26, r5
  B   55 slw r5, r27, r5
--- replace mine 59:65 base 58:64
  M   59 lwz r3, 0(r27)
  M   60 addi r0, r26, -1
  M   61 add r3, r3, r28
  M   62 li r28, 0
  M   63 stw r3, 0(r27)
  M   64 lhz r3, 0(r29)
  B   58 lwz r3, 0(r28)
  B   59 addi r0, r27, -1
  B   60 add r3, r3, r29
  B   61 li r29, 0
  B   62 stw r3, 0(r28)
  B   63 lhz r3, 0(r30)
--- replace mine 66:72 base 65:71
  M   66 sth r3, 0(r29)
  M   67 lwz r3, 0x18(r29)
  M   68 lbz r5, 0x20(r22)
  M   69 lwz r6, 0xc(r29)
  M   70 subf r3, r3, r25
  M   71 lwz r4, 4(r29)
  B   65 sth r3, 0(r30)
  B   66 lwz r3, 0x18(r30)
  B   67 lbz r5, 0x20(r23)
  B   68 lwz r6, 0xc(r30)
  B   69 subf r3, r3, r26
  B   70 lwz r4, 4(r30)
--- replace mine 78:81 base 77:80
  M   78 stw r3, 0xc(r29)
  M   79 stw r4, 0x10(r29)
  M   80 b 532
  B   77 stw r3, 0xc(r30)
  B   78 stw r4, 0x10(r30)
  B   79 b 528
--- replace mine 83:86 base 82:85
  M   83 stw r3, 0xc(r29)
  M   84 b 516
  M   85 lwz r0, 0x10(r29)
  B   82 stw r3, 0xc(r30)
  B   83 b 512
  B   84 lwz r0, 0x10(r30)
--- replace mine 87:91 base 86:90
  M   87 bge 504
  M   88 stw r4, 0x10(r29)
  M   89 b 496
  M   90 cmplw r7, r25
  B   86 bge 500
  B   87 stw r4, 0x10(r30)
  B   88 b 492
  B   89 cmplw r7, r26
--- replace mine 92:93 base 91:92
  M   92 lwz r4, 0x14(r29)
  B   91 lwz r4, 0x14(r30)
--- replace mine 94:95 base 93:94
  M   94 cmplw r0, r30
  B   93 cmplw r0, r31
--- replace mine 96:99 base 95:98
  M   96 lbz r5, 0x20(r22)
  M   97 subf r0, r25, r7
  M   98 lwz r3, 4(r29)
  B   95 lbz r5, 0x20(r23)
  B   96 subf r0, r26, r7
  B   97 lwz r3, 4(r30)
--- replace mine 101:102 base 100:101
  M  101 add r4, r24, r0
  B  100 add r4, r25, r0
--- replace mine 103:106 base 102:105
  M  103 lwz r3, 0x14(r29)
  M  104 lwz r0, 0(r27)
  M  105 subf r28, r3, r28
  B  102 lwz r3, 0x14(r30)
  B  103 lwz r0, 0(r28)
  B  104 subf r29, r3, r29
--- replace mine 107:109 base 106:108
  M  107 stw r0, 0(r27)
  M  108 lhz r0, 0(r29)
  B  106 stw r0, 0(r28)
  B  107 lhz r0, 0(r30)
--- replace mine 110:115 base 109:114
  M  110 sth r0, 0(r29)
  M  111 lwz r0, 4(r29)
  M  112 stw r0, 0xc(r29)
  M  113 lwz r3, 0x14(r29)
  M  114 lbz r0, 0x20(r22)
  B  109 sth r0, 0(r30)
  B  110 lwz r0, 4(r30)
  B  111 stw r0, 0xc(r30)
  B  112 lwz r3, 0x14(r30)
  B  113 lbz r0, 0x20(r23)
--- replace mine 116:117 base 115:116
  M  116 lwz r4, 4(r29)
  B  115 lwz r4, 4(r30)
--- replace mine 119:126 base 118:125
  M  119 stw r0, 0x10(r29)
  M  120 b 372
  M  121 cmplw r7, r25
  M  122 ble 164
  M  123 cmplw r7, r30
  M  124 bge 156
  M  125 lwz r0, 0x14(r29)
  B  118 stw r0, 0x10(r30)
  B  119 b 368
  B  120 cmplw r7, r26
  B  121 ble 160
  B  122 cmplw r7, r31
  B  123 bge 152
  B  124 lwz r0, 0x14(r30)
--- replace mine 127:133 base 126:132
  M  127 cmplw r0, r30
  M  128 blt 140
  M  129 lbz r5, 0x20(r22)
  M  130 subf r4, r25, r7
  M  131 subf r0, r7, r30
  M  132 lwz r3, 4(r29)
  B  126 cmplw r0, r31
  B  127 blt 136
  B  128 lbz r5, 0x20(r23)
  B  129 subf r4, r26, r7
  B  130 subf r0, r7, r31
  B  131 lwz r3, 4(r30)
--- replace mine 134:135 base 133:134
  M  134 add r4, r24, r4
  B  133 add r4, r25, r4
--- replace mine 137:141 base 136:141
  M  137 lwz r3, 0x18(r29)
  M  138 add r5, r26, r25
  M  139 lwz r0, 0(r27)
  M  140 subfc r4, r3, r5
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
  B  138 lwz r0, 0(r28)
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 142:147 base 142:145
  M  142 subfe r3, r5, r5
  M  143 stw r0, 0(r27)
  M  144 addc r3, r31, r5
  M  145 subf r28, r4, r28
  M  146 lhz r0, 0(r29)
  B  142 stw r0, 0(r28)
  B  143 subf r29, r4, r29
  B  144 lhz r0, 0(r30)
--- replace mine 148:152 base 146:150
  M  148 sth r0, 0(r29)
  M  149 lwz r4, 0x18(r29)
  M  150 lwz r5, 4(r29)
  M  151 lbz r0, 0x20(r22)
  B  146 sth r0, 0(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
  B  149 lbz r0, 0x20(r23)
--- replace mine 154:155 base 152:153
  M  154 stw r5, 0xc(r29)
  B  152 stw r5, 0xc(r30)
--- replace mine 156:157 base 154:155
  M  156 lwz r0, 0x10(r29)
  B  154 lwz r0, 0x10(r30)
--- replace mine 161:162 base 159:160
  M  161 stw r3, 0x10(r29)
  B  159 stw r3, 0x10(r30)
--- replace mine 163:164 base 161:162
  M  163 cmplw r7, r25
  B  161 cmplw r7, r26
--- replace mine 165:166 base 163:164
  M  165 lwz r0, 0x14(r29)
  B  163 lwz r0, 0x14(r30)
--- replace mine 167:168 base 165:166
  M  167 cmplw r3, r25
  B  165 cmplw r3, r26
--- replace mine 169:170 base 167:168
  M  169 cmplw r3, r30
  B  167 cmplw r3, r31
--- replace mine 171:174 base 169:172
  M  171 lbz r6, 0x20(r22)
  M  172 subf r3, r7, r25
  M  173 lwz r5, 4(r29)
  B  169 lbz r6, 0x20(r23)
  B  170 subf r3, r7, r26
  B  171 lwz r5, 4(r30)
--- replace mine 176:177 base 174:175
  M  176 mr r4, r24
  B  174 mr r4, r25
--- replace mine 180:184 base 178:182
  M  180 lwz r0, 0x18(r29)
  M  181 lwz r3, 0x14(r29)
  M  182 subf r4, r0, r25
  M  183 lwz r0, 0(r27)
  B  178 lwz r0, 0x18(r30)
  B  179 lwz r3, 0x14(r30)
  B  180 subf r4, r0, r26
  B  181 lwz r0, 0(r28)
--- replace mine 186:189 base 184:187
  M  186 stw r0, 0(r27)
  M  187 subf r28, r3, r28
  M  188 lhz r0, 0(r29)
  B  184 stw r0, 0(r28)
  B  185 subf r29, r3, r29
  B  186 lhz r0, 0(r30)
--- replace mine 190:195 base 188:193
  M  190 sth r0, 0(r29)
  M  191 lwz r3, 0x18(r29)
  M  192 lwz r0, 0x14(r29)
  M  193 subf r3, r3, r25
  M  194 lwz r5, 0xc(r29)
  B  188 sth r0, 0(r30)
  B  189 lwz r3, 0x18(r30)
  B  190 lwz r0, 0x14(r30)
  B  191 subf r3, r3, r26
  B  192 lwz r5, 0xc(r30)
--- replace mine 196:197 base 194:195
  M  196 lbz r0, 0x20(r22)
  B  194 lbz r0, 0x20(r23)
--- replace mine 199:200 base 197:198
  M  199 lwz r4, 4(r29)
  B  197 lwz r4, 4(r30)
--- replace mine 205:208 base 203:206
  M  205 stw r0, 0xc(r29)
  M  206 lwz r3, 0x14(r29)
  M  207 lbz r0, 0x20(r22)
  B  203 stw r0, 0xc(r30)
  B  204 lwz r3, 0x14(r30)
  B  205 lbz r0, 0x20(r23)
--- replace mine 209:210 base 207:208
  M  209 lwz r4, 4(r29)
  B  207 lwz r4, 4(r30)
--- replace mine 212:213 base 210:213
  M  212 stw r0, 0x10(r29)
  B  210 stw r0, 0x10(r30)
  B  211 cmpwi r30, 0
  B  212 beq 12
--- replace mine 214:218 base 214:216
  M  214 beq 12
  M  215 cmpwi r28, 0
  M  216 bne -800
  M  217 cmpwi r28, 0
  B  214 bne -796
  B  215 cmpwi r29, 0
--- replace mine 219:224 base 217:222
  M  219 mr r3, r22
  M  220 mr r4, r24
  M  221 mr r5, r25
  M  222 mr r6, r26
  M  223 mr r7, r27
  B  217 mr r3, r23
  B  218 mr r4, r25
  B  219 mr r5, r26
  B  220 mr r6, r27
  B  221 mr r7, r28

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper end_sector widened to signed long long with 32-bit results
instructions 236/233, structural/exact (23, 234); src 0x3b0 base 0x3a4 insns 236/233
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x40(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x44(r1)
  M    3 addi r11, r1, 0x40
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- delete mine 5:15 base 5:5
  M    5 li r28, 0
  M    6 mr r25, r7
  M    7 stw r28, 0(r8)
  M    8 mr r21, r3
  M    9 mr r22, r4
  M   10 mr r23, r5
  M   11 mr r24, r6
  M   12 mr r26, r8
  M   13 mr r27, r25
  M   14 add r29, r6, r7
--- replace mine 16:18 base 6:16
  M   16 li r31, -1
  M   17 cmpwi r28, 0
  B    6 mr r27, r7
  B    7 stw r30, 0(r8)
  B    8 mr r23, r3
  B    9 mr r24, r4
  B   10 mr r25, r5
  B   11 mr r26, r6
  B   12 mr r28, r8
  B   13 mr r29, r27
  B   14 add r31, r6, r7
  B   15 cmpwi r30, 0
--- replace mine 19:20 base 17:18
  M   19 lwz r28, 0(r22)
  B   17 lwz r30, 0(r24)
--- replace mine 21:24 base 19:22
  M   21 lwz r28, 0x20(r28)
  M   22 lwz r0, 0(r22)
  M   23 cmplw r28, r0
  B   19 lwz r30, 0x20(r30)
  B   20 lwz r0, 0(r24)
  B   21 cmplw r30, r0
--- replace mine 25:26 base 23:24
  M   25 li r28, 0
  B   23 li r30, 0
--- replace mine 28:29 base 26:27
  M   28 lwz r3, 0x18(r28)
  B   26 lwz r3, 0x18(r30)
--- replace mine 32:34 base 30:32
  M   32 lwz r0, 4(r28)
  M   33 stw r0, 8(r28)
  B   30 lwz r0, 4(r30)
  B   31 stw r0, 8(r30)
--- replace mine 35:37 base 33:35
  M   35 lwz r28, 0x20(r28)
  M   36 lhz r0, 0(r28)
  B   33 lwz r30, 0x20(r30)
  B   34 lhz r0, 0(r30)
--- replace mine 39:43 base 37:41
  M   39 li r28, 0
  M   40 cmpwi r28, 0
  M   41 beq 692
  M   42 lwz r7, 0x18(r28)
  B   37 li r30, 0
  B   38 cmpwi r30, 0
  B   39 beq 688
  B   40 lwz r7, 0x18(r30)
--- replace mine 45:47 base 43:45
  M   45 beq 676
  M   46 cmplw r7, r24
  B   43 beq 672
  B   44 cmplw r7, r26
--- replace mine 48:49 base 46:47
  M   48 lwz r0, 0x14(r28)
  B   46 lwz r0, 0x14(r30)
--- replace mine 50:51 base 48:49
  M   50 cmplw r0, r29
  B   48 cmplw r0, r31
--- replace mine 52:56 base 50:54
  M   52 lbz r5, 0x20(r21)
  M   53 subf r0, r7, r24
  M   54 lwz r3, 4(r28)
  M   55 mr r4, r23
  B   50 lbz r5, 0x20(r23)
  B   51 subf r0, r7, r26
  B   52 lwz r3, 4(r30)
  B   53 mr r4, r25
--- replace mine 57:58 base 55:56
  M   57 slw r5, r25, r5
  B   55 slw r5, r27, r5
--- replace mine 60:66 base 58:64
  M   60 lwz r3, 0(r26)
  M   61 addi r0, r25, -1
  M   62 add r3, r3, r27
  M   63 li r27, 0
  M   64 stw r3, 0(r26)
  M   65 lhz r3, 0(r28)
  B   58 lwz r3, 0(r28)
  B   59 addi r0, r27, -1
  B   60 add r3, r3, r29
  B   61 li r29, 0
  B   62 stw r3, 0(r28)
  B   63 lhz r3, 0(r30)
--- replace mine 67:73 base 65:71
  M   67 sth r3, 0(r28)
  M   68 lwz r3, 0x18(r28)
  M   69 lbz r5, 0x20(r21)
  M   70 lwz r6, 0xc(r28)
  M   71 subf r3, r3, r24
  M   72 lwz r4, 4(r28)
  B   65 sth r3, 0(r30)
  B   66 lwz r3, 0x18(r30)
  B   67 lbz r5, 0x20(r23)
  B   68 lwz r6, 0xc(r30)
  B   69 subf r3, r3, r26
  B   70 lwz r4, 4(r30)
--- replace mine 79:82 base 77:80
  M   79 stw r3, 0xc(r28)
  M   80 stw r4, 0x10(r28)
  M   81 b 532
  B   77 stw r3, 0xc(r30)
  B   78 stw r4, 0x10(r30)
  B   79 b 528
--- replace mine 84:87 base 82:85
  M   84 stw r3, 0xc(r28)
  M   85 b 516
  M   86 lwz r0, 0x10(r28)
  B   82 stw r3, 0xc(r30)
  B   83 b 512
  B   84 lwz r0, 0x10(r30)
--- replace mine 88:92 base 86:90
  M   88 bge 504
  M   89 stw r4, 0x10(r28)
  M   90 b 496
  M   91 cmplw r7, r24
  B   86 bge 500
  B   87 stw r4, 0x10(r30)
  B   88 b 492
  B   89 cmplw r7, r26
--- replace mine 93:94 base 91:92
  M   93 lwz r4, 0x14(r28)
  B   91 lwz r4, 0x14(r30)
--- replace mine 95:96 base 93:94
  M   95 cmplw r0, r29
  B   93 cmplw r0, r31
--- replace mine 97:100 base 95:98
  M   97 lbz r5, 0x20(r21)
  M   98 subf r0, r24, r7
  M   99 lwz r3, 4(r28)
  B   95 lbz r5, 0x20(r23)
  B   96 subf r0, r26, r7
  B   97 lwz r3, 4(r30)
--- replace mine 102:103 base 100:101
  M  102 add r4, r23, r0
  B  100 add r4, r25, r0
--- replace mine 104:107 base 102:105
  M  104 lwz r3, 0x14(r28)
  M  105 lwz r0, 0(r26)
  M  106 subf r27, r3, r27
  B  102 lwz r3, 0x14(r30)
  B  103 lwz r0, 0(r28)
  B  104 subf r29, r3, r29
--- replace mine 108:110 base 106:108
  M  108 stw r0, 0(r26)
  M  109 lhz r0, 0(r28)
  B  106 stw r0, 0(r28)
  B  107 lhz r0, 0(r30)
--- replace mine 111:116 base 109:114
  M  111 sth r0, 0(r28)
  M  112 lwz r0, 4(r28)
  M  113 stw r0, 0xc(r28)
  M  114 lwz r3, 0x14(r28)
  M  115 lbz r0, 0x20(r21)
  B  109 sth r0, 0(r30)
  B  110 lwz r0, 4(r30)
  B  111 stw r0, 0xc(r30)
  B  112 lwz r3, 0x14(r30)
  B  113 lbz r0, 0x20(r23)
--- replace mine 117:118 base 115:116
  M  117 lwz r4, 4(r28)
  B  115 lwz r4, 4(r30)
--- replace mine 120:127 base 118:125
  M  120 stw r0, 0x10(r28)
  M  121 b 372
  M  122 cmplw r7, r24
  M  123 ble 164
  M  124 cmplw r7, r29
  M  125 bge 156
  M  126 lwz r0, 0x14(r28)
  B  118 stw r0, 0x10(r30)
  B  119 b 368
  B  120 cmplw r7, r26
  B  121 ble 160
  B  122 cmplw r7, r31
  B  123 bge 152
  B  124 lwz r0, 0x14(r30)
--- replace mine 128:134 base 126:132
  M  128 cmplw r0, r29
  M  129 blt 140
  M  130 lbz r5, 0x20(r21)
  M  131 subf r4, r24, r7
  M  132 subf r0, r7, r29
  M  133 lwz r3, 4(r28)
  B  126 cmplw r0, r31
  B  127 blt 136
  B  128 lbz r5, 0x20(r23)
  B  129 subf r4, r26, r7
  B  130 subf r0, r7, r31
  B  131 lwz r3, 4(r30)
--- replace mine 135:136 base 133:134
  M  135 add r4, r23, r4
  B  133 add r4, r25, r4
--- replace mine 138:142 base 136:141
  M  138 lwz r3, 0x18(r28)
  M  139 add r5, r25, r24
  M  140 lwz r0, 0(r26)
  M  141 subfc r4, r3, r5
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
  B  138 lwz r0, 0(r28)
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 143:148 base 142:145
  M  143 subfe r3, r30, r30
  M  144 stw r0, 0(r26)
  M  145 addc r3, r5, r31
  M  146 subf r27, r4, r27
  M  147 lhz r0, 0(r28)
  B  142 stw r0, 0(r28)
  B  143 subf r29, r4, r29
  B  144 lhz r0, 0(r30)
--- replace mine 149:153 base 146:150
  M  149 sth r0, 0(r28)
  M  150 lwz r4, 0x18(r28)
  M  151 lwz r5, 4(r28)
  M  152 lbz r0, 0x20(r21)
  B  146 sth r0, 0(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
  B  149 lbz r0, 0x20(r23)
--- replace mine 155:156 base 152:153
  M  155 stw r5, 0xc(r28)
  B  152 stw r5, 0xc(r30)
--- replace mine 157:158 base 154:155
  M  157 lwz r0, 0x10(r28)
  B  154 lwz r0, 0x10(r30)
--- replace mine 162:163 base 159:160
  M  162 stw r3, 0x10(r28)
  B  159 stw r3, 0x10(r30)
--- replace mine 164:165 base 161:162
  M  164 cmplw r7, r24
  B  161 cmplw r7, r26
--- replace mine 166:167 base 163:164
  M  166 lwz r0, 0x14(r28)
  B  163 lwz r0, 0x14(r30)
--- replace mine 168:169 base 165:166
  M  168 cmplw r3, r24
  B  165 cmplw r3, r26
--- replace mine 170:171 base 167:168
  M  170 cmplw r3, r29
  B  167 cmplw r3, r31
--- replace mine 172:175 base 169:172
  M  172 lbz r6, 0x20(r21)
  M  173 subf r3, r7, r24
  M  174 lwz r5, 4(r28)
  B  169 lbz r6, 0x20(r23)
  B  170 subf r3, r7, r26
  B  171 lwz r5, 4(r30)
--- replace mine 177:178 base 174:175
  M  177 mr r4, r23
  B  174 mr r4, r25
--- replace mine 181:185 base 178:182
  M  181 lwz r0, 0x18(r28)
  M  182 lwz r3, 0x14(r28)
  M  183 subf r4, r0, r24
  M  184 lwz r0, 0(r26)
  B  178 lwz r0, 0x18(r30)
  B  179 lwz r3, 0x14(r30)
  B  180 subf r4, r0, r26
  B  181 lwz r0, 0(r28)
--- replace mine 187:190 base 184:187
  M  187 stw r0, 0(r26)
  M  188 subf r27, r3, r27
  M  189 lhz r0, 0(r28)
  B  184 stw r0, 0(r28)
  B  185 subf r29, r3, r29
  B  186 lhz r0, 0(r30)
--- replace mine 191:196 base 188:193
  M  191 sth r0, 0(r28)
  M  192 lwz r3, 0x18(r28)
  M  193 lwz r0, 0x14(r28)
  M  194 subf r3, r3, r24
  M  195 lwz r5, 0xc(r28)
  B  188 sth r0, 0(r30)
  B  189 lwz r3, 0x18(r30)
  B  190 lwz r0, 0x14(r30)
  B  191 subf r3, r3, r26
  B  192 lwz r5, 0xc(r30)
--- replace mine 197:198 base 194:195
  M  197 lbz r0, 0x20(r21)
  B  194 lbz r0, 0x20(r23)
--- replace mine 200:201 base 197:198
  M  200 lwz r4, 4(r28)
  B  197 lwz r4, 4(r30)
--- replace mine 206:209 base 203:206
  M  206 stw r0, 0xc(r28)
  M  207 lwz r3, 0x14(r28)
  M  208 lbz r0, 0x20(r21)
  B  203 stw r0, 0xc(r30)
  B  204 lwz r3, 0x14(r30)
  B  205 lbz r0, 0x20(r23)
--- replace mine 210:211 base 207:208
  M  210 lwz r4, 4(r28)
  B  207 lwz r4, 4(r30)
--- replace mine 213:215 base 210:212
  M  213 stw r0, 0x10(r28)
  M  214 cmpwi r28, 0
  B  210 stw r0, 0x10(r30)
  B  211 cmpwi r30, 0
--- replace mine 216:219 base 213:216
  M  216 cmpwi r27, 0
  M  217 bne -800
  M  218 cmpwi r27, 0
  B  213 cmpwi r29, 0
  B  214 bne -796
  B  215 cmpwi r29, 0
--- replace mine 220:225 base 217:222
  M  220 mr r3, r21
  M  221 mr r4, r23
  M  222 mr r5, r24
  M  223 mr r6, r25
  M  224 mr r7, r26
  B  217 mr r3, r23
  B  218 mr r4, r25
  B  219 mr r5, r26
  B  220 mr r6, r27
  B  221 mr r7, r28
--- replace mine 230:231 base 227:228
  M  230 addi r11, r1, 0x40
  B  227 addi r11, r1, 0x30
--- replace mine 232:233 base 229:230
  M  232 lwz r0, 0x44(r1)
  B  229 lwz r0, 0x34(r1)
--- replace mine 234:235 base 231:232
  M  234 addi r1, r1, 0x40
  B  231 addi r1, r1, 0x30

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper last_sector widened to unsigned long long with 32-bit results
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper last_sector widened to signed long long with 32-bit results
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper num_overlap widened to unsigned long long with 32-bit results
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper num_overlap widened to signed long long with 32-bit results
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper last-sector type const pf_u32
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper last-sector type pf_s32
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper last-sector type unsigned long long
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper const pointer parameter
instructions 233/233, structural/exact (0, 10); src 0x3a4 base 0x3a4 insns 233/233
diffs 10: [136, 139, 140, 141, 143, 147, 148, 150, 152, 153]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   139 M addi r5, r4, -1
       B addi r3, r4, -1
   140 M subf r3, r3, r4
       B subf r4, r5, r4
   141 M add r0, r0, r3
       B add r0, r0, r4
   143 M subf r29, r3, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   148 M lwz r4, 4(r30)
       B lwz r5, 4(r30)
   150 M subf r3, r3, r5
       B subf r3, r4, r3
   152 M stw r4, 0xc(r30)
       B stw r5, 0xc(r30)
   153 M add r3, r4, r0
       B add r3, r5, r0

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper outer last-sector declaration before overlap
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap helper branch-local end-sector value
BUILD FAIL d/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_cache.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d build/43U/src/libs/RVL_SDK/src/fa/pf_cache.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_cache.c
# ---------------------------------------
#     619:                 pf_u32 num_overlap = num_sector;
#   Error:                 ^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX counter update through readonly pointer-object view p_num_success
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX counter read through readonly scalar pointer view p_num_success
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX counter update through readonly pointer-object view p_num_rest_sector
instructions 248/233, structural/exact (51, 244); src 0x3e0 base 0x3a4 insns 248/233
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x40(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x44(r1)
  M    3 addi r11, r1, 0x40
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 5:7 base 5:8
  M    5 stw r7, 8(r1)
  M    6 li r29, 0
  B    5 li r30, 0
  B    6 mr r27, r7
  B    7 stw r30, 0(r8)
--- delete mine 9:10 base 10:10
  M    9 stw r29, 0(r8)
--- delete mine 12:13 base 12:12
  M   12 mr r27, r7
--- replace mine 14:17 base 13:16
  M   14 add r30, r6, r7
  M   15 li r31, 0
  M   16 cmpwi r29, 0
  B   13 mr r29, r27
  B   14 add r31, r6, r7
  B   15 cmpwi r30, 0
--- replace mine 18:19 base 17:18
  M   18 lwz r29, 0(r24)
  B   17 lwz r30, 0(r24)
--- replace mine 20:21 base 19:20
  M   20 lwz r29, 0x20(r29)
  B   19 lwz r30, 0x20(r30)
--- replace mine 22:23 base 21:22
  M   22 cmplw r29, r0
  B   21 cmplw r30, r0
--- replace mine 24:25 base 23:24
  M   24 li r29, 0
  B   23 li r30, 0
--- replace mine 27:28 base 26:27
  M   27 lwz r3, 0x18(r29)
  B   26 lwz r3, 0x18(r30)
--- replace mine 31:33 base 30:32
  M   31 lwz r0, 4(r29)
  M   32 stw r0, 8(r29)
  B   30 lwz r0, 4(r30)
  B   31 stw r0, 8(r30)
--- replace mine 34:36 base 33:35
  M   34 lwz r29, 0x20(r29)
  M   35 lhz r0, 0(r29)
  B   33 lwz r30, 0x20(r30)
  B   34 lhz r0, 0(r30)
--- replace mine 38:42 base 37:41
  M   38 li r29, 0
  M   39 cmpwi r29, 0
  M   40 beq 736
  M   41 lwz r7, 0x18(r29)
  B   37 li r30, 0
  B   38 cmpwi r30, 0
  B   39 beq 688
  B   40 lwz r7, 0x18(r30)
--- replace mine 44:45 base 43:44
  M   44 beq 720
  B   43 beq 672
--- replace mine 46:48 base 45:47
  M   46 bgt 180
  M   47 lwz r0, 0x14(r29)
  B   45 bgt 176
  B   46 lwz r0, 0x14(r30)
--- replace mine 49:51 base 48:50
  M   49 cmplw r0, r30
  M   50 blt 164
  B   48 cmplw r0, r31
  B   49 blt 160
--- replace mine 53:54 base 52:53
  M   53 lwz r3, 4(r29)
  B   52 lwz r3, 4(r30)
--- replace mine 59:60 base 58:59
  M   59 lwz r4, 0(r28)
  B   58 lwz r3, 0(r28)
--- replace mine 61:63 base 60:62
  M   61 lwz r3, 8(r1)
  M   62 add r3, r4, r3
  B   60 add r3, r3, r29
  B   61 li r29, 0
--- replace mine 64:66 base 63:64
  M   64 stw r31, 8(r1)
  M   65 lhz r3, 0(r29)
  B   63 lhz r3, 0(r30)
--- replace mine 67:69 base 65:67
  M   67 sth r3, 0(r29)
  M   68 lwz r3, 0x18(r29)
  B   65 sth r3, 0(r30)
  B   66 lwz r3, 0x18(r30)
--- replace mine 70:71 base 68:69
  M   70 lwz r6, 0xc(r29)
  B   68 lwz r6, 0xc(r30)
--- replace mine 72:73 base 70:71
  M   72 lwz r4, 4(r29)
  B   70 lwz r4, 4(r30)
--- replace mine 79:82 base 77:80
  M   79 stw r3, 0xc(r29)
  M   80 stw r4, 0x10(r29)
  M   81 b 572
  B   77 stw r3, 0xc(r30)
  B   78 stw r4, 0x10(r30)
  B   79 b 528
--- replace mine 84:87 base 82:85
  M   84 stw r3, 0xc(r29)
  M   85 b 556
  M   86 lwz r0, 0x10(r29)
  B   82 stw r3, 0xc(r30)
  B   83 b 512
  B   84 lwz r0, 0x10(r30)
--- replace mine 88:91 base 86:89
  M   88 bge 544
  M   89 stw r4, 0x10(r29)
  M   90 b 536
  B   86 bge 500
  B   87 stw r4, 0x10(r30)
  B   88 b 492
--- replace mine 92:94 base 90:92
  M   92 blt 132
  M   93 lwz r4, 0x14(r29)
  B   90 blt 120
  B   91 lwz r4, 0x14(r30)
--- replace mine 95:97 base 93:95
  M   95 cmplw r0, r30
  M   96 bgt 116
  B   93 cmplw r0, r31
  B   94 bgt 104
--- replace mine 99:100 base 97:98
  M   99 lwz r3, 4(r29)
  B   97 lwz r3, 4(r30)
--- replace mine 104:111 base 102:106
  M  104 lwz r3, 0x14(r29)
  M  105 lwz r0, 8(r1)
  M  106 subf r0, r3, r0
  M  107 stw r0, 8(r1)
  M  108 lwz r3, 0(r28)
  M  109 lwz r0, 0x14(r29)
  M  110 add r0, r3, r0
  B  102 lwz r3, 0x14(r30)
  B  103 lwz r0, 0(r28)
  B  104 subf r29, r3, r29
  B  105 add r0, r0, r3
--- replace mine 112:113 base 107:108
  M  112 lhz r0, 0(r29)
  B  107 lhz r0, 0(r30)
--- replace mine 114:118 base 109:113
  M  114 sth r0, 0(r29)
  M  115 lwz r0, 4(r29)
  M  116 stw r0, 0xc(r29)
  M  117 lwz r3, 0x14(r29)
  B  109 sth r0, 0(r30)
  B  110 lwz r0, 4(r30)
  B  111 stw r0, 0xc(r30)
  B  112 lwz r3, 0x14(r30)
--- replace mine 120:121 base 115:116
  M  120 lwz r4, 4(r29)
  B  115 lwz r4, 4(r30)
--- replace mine 123:125 base 118:120
  M  123 stw r0, 0x10(r29)
  M  124 b 400
  B  118 stw r0, 0x10(r30)
  B  119 b 368
--- replace mine 126:130 base 121:125
  M  126 ble 168
  M  127 cmplw r7, r30
  M  128 bge 160
  M  129 lwz r0, 0x14(r29)
  B  121 ble 160
  B  122 cmplw r7, r31
  B  123 bge 152
  B  124 lwz r0, 0x14(r30)
--- replace mine 131:133 base 126:128
  M  131 cmplw r0, r30
  M  132 blt 144
  B  126 cmplw r0, r31
  B  127 blt 136
--- replace mine 135:137 base 130:132
  M  135 subf r0, r7, r30
  M  136 lwz r3, 4(r29)
  B  130 subf r0, r7, r31
  B  131 lwz r3, 4(r30)
--- replace mine 141:143 base 136:138
  M  141 lwz r4, 0x18(r29)
  M  142 add r5, r27, r26
  B  136 lwz r5, 0x18(r30)
  B  137 add r4, r27, r26
--- replace mine 144:146 base 139:141
  M  144 addi r3, r5, -1
  M  145 subf r4, r4, r5
  B  139 addi r3, r4, -1
  B  140 subf r4, r5, r4
--- replace mine 148:152 base 143:145
  M  148 lwz r0, 8(r1)
  M  149 subf r0, r4, r0
  M  150 stw r0, 8(r1)
  M  151 lhz r0, 0(r29)
  B  143 subf r29, r4, r29
  B  144 lhz r0, 0(r30)
--- replace mine 153:156 base 146:149
  M  153 sth r0, 0(r29)
  M  154 lwz r4, 0x18(r29)
  M  155 lwz r5, 4(r29)
  B  146 sth r0, 0(r30)
  B  147 lwz r4, 0x18(r30)
  B  148 lwz r5, 4(r30)
--- replace mine 159:160 base 152:153
  M  159 stw r5, 0xc(r29)
  B  152 stw r5, 0xc(r30)
--- replace mine 161:162 base 154:155
  M  161 lwz r0, 0x10(r29)
  B  154 lwz r0, 0x10(r30)
--- replace mine 165:168 base 158:161
  M  165 bge 236
  M  166 stw r3, 0x10(r29)
  M  167 b 228
  B  158 bge 212
  B  159 stw r3, 0x10(r30)
  B  160 b 204
--- replace mine 169:171 base 162:164
  M  169 bge 220
  M  170 lwz r0, 0x14(r29)
  B  162 bge 196
  B  163 lwz r0, 0x14(r30)
--- replace mine 173:176 base 166:169
  M  173 ble 204
  M  174 cmplw r3, r30
  M  175 bgt 196
  B  166 ble 180
  B  167 cmplw r3, r31
  B  168 bgt 172
--- replace mine 178:179 base 171:172
  M  178 lwz r5, 4(r29)
  B  171 lwz r5, 4(r30)
--- replace mine 185:187 base 178:180
  M  185 lwz r0, 0x18(r29)
  M  186 lwz r3, 0x14(r29)
  B  178 lwz r0, 0x18(r30)
  B  179 lwz r3, 0x14(r30)
--- replace mine 188:189 base 181:182
  M  188 lwz r0, 8(r1)
  B  181 lwz r0, 0(r28)
--- replace mine 190:194 base 183:191
  M  190 subf r0, r3, r0
  M  191 stw r0, 8(r1)
  M  192 lwz r3, 0x18(r29)
  M  193 lwz r0, 0x14(r29)
  B  183 add r0, r0, r3
  B  184 stw r0, 0(r28)
  B  185 subf r29, r3, r29
  B  186 lhz r0, 0(r30)
  B  187 ori r0, r0, 2
  B  188 sth r0, 0(r30)
  B  189 lwz r3, 0x18(r30)
  B  190 lwz r0, 0x14(r30)
--- replace mine 195:206 base 192:193
  M  195 lwz r4, 0(r28)
  M  196 subf r0, r3, r0
  M  197 add r0, r4, r0
  M  198 stw r0, 0(r28)
  M  199 lhz r0, 0(r29)
  M  200 ori r0, r0, 2
  M  201 sth r0, 0(r29)
  M  202 lwz r3, 0x18(r29)
  M  203 lwz r0, 0x14(r29)
  M  204 subf r3, r3, r26
  M  205 lwz r5, 0xc(r29)
  B  192 lwz r5, 0xc(r30)
--- replace mine 210:211 base 197:198
  M  210 lwz r4, 4(r29)
  B  197 lwz r4, 4(r30)
--- replace mine 216:218 base 203:205
  M  216 stw r0, 0xc(r29)
  M  217 lwz r3, 0x14(r29)
  B  203 stw r0, 0xc(r30)
  B  204 lwz r3, 0x14(r30)
--- replace mine 220:221 base 207:208
  M  220 lwz r4, 4(r29)
  B  207 lwz r4, 4(r30)
--- replace mine 223:224 base 210:213
  M  223 stw r0, 0x10(r29)
  B  210 stw r0, 0x10(r30)
  B  211 cmpwi r30, 0
  B  212 beq 12
--- replace mine 225:231 base 214:216
  M  225 beq 16
  M  226 lwz r0, 8(r1)
  M  227 cmpwi r0, 0
  M  228 bne -848
  M  229 lwz r0, 8(r1)
  M  230 cmpwi r0, 0
  B  214 bne -796
  B  215 cmpwi r29, 0
--- replace mine 242:243 base 227:228
  M  242 addi r11, r1, 0x40
  B  227 addi r11, r1, 0x30
--- replace mine 244:245 base 229:230
  M  244 lwz r0, 0x44(r1)
  B  229 lwz r0, 0x34(r1)
--- replace mine 246:247 base 231:232
  M  246 addi r1, r1, 0x40
  B  231 addi r1, r1, 0x30

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX counter read through readonly scalar pointer view p_num_rest_sector
instructions 233/233, structural/exact (0, 60); src 0x3a4 base 0x3a4 insns 233/233
diffs 60: [6, 8, 9, 10, 11, 12, 13, 17, 20, 44, 50, 51, 53, 55, 58, 59, 60, 61, 62, 67]
     6 M mr r28, r7
       B mr r27, r7
     8 M mr r24, r3
       B mr r23, r3
     9 M mr r25, r4
       B mr r24, r4
    10 M mr r26, r5
       B mr r25, r5
    11 M mr r27, r6
       B mr r26, r6
    12 M mr r29, r8
       B mr r28, r8
    13 M mr r23, r28
       B mr r29, r27
    17 M lwz r30, 0(r25)
       B lwz r30, 0(r24)
    20 M lwz r0, 0(r25)
       B lwz r0, 0(r24)
    44 M cmplw r7, r27
       B cmplw r7, r26
    50 M lbz r5, 0x20(r24)
       B lbz r5, 0x20(r23)
    51 M subf r0, r7, r27
       B subf r0, r7, r26
    53 M mr r4, r26
       B mr r4, r25
    55 M slw r5, r28, r5
       B slw r5, r27, r5
    58 M lwz r3, 0(r29)
       B lwz r3, 0(r28)
    59 M addi r0, r28, -1
       B addi r0, r27, -1
    60 M add r3, r3, r23
       B add r3, r3, r29
    61 M li r23, 0
       B li r29, 0
    62 M stw r3, 0(r29)
       B stw r3, 0(r28)
    67 M lbz r5, 0x20(r24)
       B lbz r5, 0x20(r23)
    69 M subf r3, r3, r27
       B subf r3, r3, r26
    89 M cmplw r7, r27
       B cmplw r7, r26
    95 M lbz r5, 0x20(r24)
       B lbz r5, 0x20(r23)
    96 M subf r0, r27, r7
       B subf r0, r26, r7
   100 M add r4, r26, r0
       B add r4, r25, r0
   103 M lwz r0, 0(r29)
       B lwz r0, 0(r28)
   104 M subf r23, r3, r23
       B subf r29, r3, r29
   106 M stw r0, 0(r29)
       B stw r0, 0(r28)
   113 M lbz r0, 0x20(r24)
       B lbz r0, 0x20(r23)
   120 M cmplw r7, r27
       B cmplw r7, r26
   128 M lbz r5, 0x20(r24)
       B lbz r5, 0x20(r23)
   129 M subf r4, r27, r7
       B subf r4, r26, r7
   133 M add r4, r26, r4
       B add r4, r25, r4
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r28, r27
       B add r4, r27, r26
   138 M lwz r0, 0(r29)
       B lwz r0, 0(r28)
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4
   142 M stw r0, 0(r29)
       B stw r0, 0(r28)
   143 M subf r23, r4, r23
       B subf r29, r4, r29
   149 M lbz r0, 0x20(r24)
       B lbz r0, 0x20(r23)
   161 M cmplw r7, r27
       B cmplw r7, r26
   165 M cmplw r3, r27
       B cmplw r3, r26
   169 M lbz r6, 0x20(r24)
       B lbz r6, 0x20(r23)
   170 M subf r3, r7, r27
       B subf r3, r7, r26
   174 M mr r4, r26
       B mr r4, r25
   180 M subf r4, r0, r27
       B subf r4, r0, r26
   181 M lwz r0, 0(r29)
       B lwz r0, 0(r28)
   184 M stw r0, 0(r29)
       B stw r0, 0(r28)
   185 M subf r23, r3, r23
       B subf r29, r3, r29
   191 M subf r3, r3, r27
       B subf r3, r3, r26
   194 M lbz r0, 0x20(r24)
       B lbz r0, 0x20(r23)
   205 M lbz r0, 0x20(r24)
       B lbz r0, 0x20(r23)
   213 M cmpwi r23, 0
       B cmpwi r29, 0
   215 M cmpwi r23, 0
       B cmpwi r29, 0
   217 M mr r3, r24
       B mr r3, r23
   218 M mr r4, r26
       B mr r4, r25
   219 M mr r5, r27
       B mr r5, r26
   220 M mr r6, r28
       B mr r6, r27
   221 M mr r7, r29
       B mr r7, r28

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place overlap scalar declared first in overlap branch
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX in-place end and last-sector locals both scoped to overlap branch
instructions 233/233, structural/exact (0, 8); src 0x3a4 base 0x3a4 insns 233/233
diffs 8: [136, 137, 139, 140, 141, 143, 147, 150]
   136 M lwz r3, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r4, r5, -1
       B addi r3, r4, -1
   140 M subf r5, r3, r5
       B subf r4, r5, r4
   141 M add r0, r0, r5
       B add r0, r0, r4
   143 M subf r29, r5, r29
       B subf r29, r4, r29
   147 M lwz r3, 0x18(r30)
       B lwz r4, 0x18(r30)
   150 M subf r3, r3, r4
       B subf r3, r4, r3

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX caller end-sector scalar computed through mutable object view
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX caller end-sector held in typed overlap object
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX overlap helper reads const typed end-sector object
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX separate readonly page input and mutable flag output read-first=True
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX separate readonly page input and mutable flag output read-first=False
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested overlap calculation helper const PF_CACHE_PAGE* page, pf_u32 end
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested overlap calculation helper pf_u32 end, const PF_CACHE_PAGE* page
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested overlap calculation helper pf_u32 start, pf_u32 end
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested overlap calculation helper pf_u32 end, pf_u32 start
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested last-sector helper before overlap bookkeeping
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## PFCACHE_DoWriteNumSectorAndFreeIfNeeded: MAX nested readonly page-sector getter helper
instructions 233/233, structural/exact (0, 4); src 0x3a4 base 0x3a4 insns 233/233
diffs 4: [136, 137, 139, 140]
   136 M lwz r4, 0x18(r30)
       B lwz r5, 0x18(r30)
   137 M add r5, r27, r26
       B add r4, r27, r26
   139 M addi r3, r5, -1
       B addi r3, r4, -1
   140 M subf r4, r4, r5
       B subf r4, r5, r4

## MAX cache disposition
40 distinct MAX pointer/field/type/inline-boundary attempts logged; no improvement retained. The failed branch-local declaration was repaired by declaring before pf_memcpy; it still differed in eight registers. Widening only intermediates reduced back to baseline four diffs, whereas widening helper input changed the calculation substantially. Separate readonly page inputs, nested overlap/getter helpers, true in-place outputs, and typed end-sector objects never produced the target r4/r5 allocation. Final declsearch score-only: structural 0, exact 4. Baseline source restored; only the four input/derived temporary registers differ in 233/233 instructions. Open at objdiff 99.8927%; no data bytes or symbols to repair.

## MAX SD start
Fetched origin/main 11c75ddb62b5df8c35d860861f9725fa91f47c8d: owned unit source unchanged versus HEAD, so near-miss still open. Pool identical at 46 strings; data 3592/3592 and extents already valid. Both frames 0x10, 57 instructions. Four differences at 45/47/49/50 arise in the final flags &= ~1 and media_inserted = 0 block: target loads old flags in r3, masks into r5 and stores flags before media; ours coalesces old/new flags in r5 and schedules media store first. SDK/global info pointer helpers otherwise exact. Definition-level volatile flags was already target-justified by consecutive pre-clear reads, but tried in HIGH and failed to improve this block. There is no corresponding proof for declaring media volatile, so do not invent it. Test real pointer/field views and widths.

## pfd_sddrv_finalize: MAX final clear low bit with u64 mask promotion
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final clear low bit with u64 value promotion
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final clear low bit with s64 mask promotion
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final clear low bit with s64 value promotion
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final flags held in u64 object before low-bit clear
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final flags held in s64 object before low-bit clear
instructions 58/57, structural/exact (6, 15); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:48 base 43:48
  M   43 lis r7, 0
  M   44 li r0, -2
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  M   47 li r5, 0
  B   43 lis r6, 0
  B   44 li r0, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:54 base 49:53
  M   49 and r0, r6, r0
  M   50 stw r5, 0x10(r4)
  M   51 stw r0, 0(r7)
  M   52 stw r5, 0xc(r4)
  M   53 stb r5, 0x18(r4)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final flags held in unsigned int object before low-bit clear
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final flags held in signed int object before low-bit clear
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final flags read through readonly field pointer
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final resets through readonly driver-info pointer object view
instructions 56/57, structural/exact (6, 15); src 0xe0 base 0xe4 insns 56/57
--- replace mine 6:7 base 6:7
  M    6 b 184
  B    6 b 188
--- replace mine 43:45 base 43:44
  M   43 lis r5, 0
  M   44 lwzu r4, 0(r5)
  B   43 lis r6, 0
--- insert mine 46:46 base 45:48
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 47:52 base 49:53
  M   47 rlwinm r4, r4, 0, 0, 0x1e
  M   48 stw r4, 0(r5)
  M   49 stw r0, 0x10(r5)
  M   50 stw r0, 0xc(r5)
  M   51 stb r0, 0x18(r5)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX final resets through mutable driver-info pointer object view
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX flags and media final resets through separate field pointers
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final flag update through readonly field-pointer object view
instructions 56/57, structural/exact (7, 15); src 0xe0 base 0xe4 insns 56/57
--- replace mine 6:7 base 6:7
  M    6 b 184
  B    6 b 188
--- replace mine 43:45 base 43:44
  M   43 lis r5, 0
  M   44 lwzu r4, 0(r5)
  B   43 lis r6, 0
--- insert mine 46:46 base 45:48
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 47:52 base 49:53
  M   47 rlwinm r4, r4, 0, 0, 0x1e
  M   48 stw r0, 0x10(r5)
  M   49 stw r4, 0(r5)
  M   50 stw r0, 0xc(r5)
  M   51 stb r0, 0x18(r5)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX reset helper accepts distinct field pointers in order flags,mediaInserted,disk,drive
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper accepts distinct field pointers in order mediaInserted,flags,disk,drive
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper accepts distinct field pointers in order disk,drive,flags,mediaInserted
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper accepts distinct field pointers in order drive,disk,mediaInserted,flags
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper receives separate readonly flags input and mutable output
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX mask-value helper reads const flags field address
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX flag-only helper receives readonly input and mutable output field pointers
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper receives readonly driver-info pointer object
instructions 56/57, structural/exact (6, 15); src 0xe0 base 0xe4 insns 56/57
--- replace mine 6:7 base 6:7
  M    6 b 184
  B    6 b 188
--- replace mine 43:45 base 43:44
  M   43 lis r5, 0
  M   44 lwzu r4, 0(r5)
  B   43 lis r6, 0
--- insert mine 46:46 base 45:48
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 47:52 base 49:53
  M   47 rlwinm r4, r4, 0, 0, 0x1e
  M   48 stw r4, 0(r5)
  M   49 stw r0, 0x10(r5)
  M   50 stw r0, 0xc(r5)
  M   51 stb r0, 0x18(r5)
  B   49 stw r5, 0(r6)
  B   50 stw r0, 0x10(r4)
  B   51 stw r0, 0xc(r4)
  B   52 stb r0, 0x18(r4)

## pfd_sddrv_finalize: MAX xor initialized bit away
instructions 58/57, structural/exact (8, 13); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:44 base 43:44
  M   43 lis r7, 0
  B   43 lis r6, 0
--- replace mine 45:47 base 45:50
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
  B   48 li r3, 0
  B   49 stw r5, 0(r6)
--- delete mine 48:51 base 51:51
  M   48 li r3, 0
  M   49 clrlwi r5, r6, 0x1f
  M   50 xor r5, r6, r5
--- delete mine 52:53 base 52:52
  M   52 stw r5, 0(r7)

## pfd_sddrv_finalize: MAX clear bit via complement or inverse
instructions 59/57, structural/exact (7, 15); src 0xec base 0xe4 insns 59/57
--- replace mine 6:7 base 6:7
  M    6 b 196
  B    6 b 188
--- replace mine 43:47 base 43:44
  M   43 lis r7, 0
  M   44 li r5, 1
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  B   43 lis r6, 0
--- insert mine 48:48 base 45:48
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
--- replace mine 49:50 base 49:50
  M   49 nor r6, r6, r6
  B   49 stw r5, 0(r6)
--- delete mine 51:53 base 51:51
  M   51 nor r5, r6, r5
  M   52 stw r5, 0(r7)

## pfd_sddrv_finalize: MAX subtract initialized bit
instructions 58/57, structural/exact (8, 13); src 0xe8 base 0xe4 insns 58/57
--- replace mine 6:7 base 6:7
  M    6 b 192
  B    6 b 188
--- replace mine 43:44 base 43:44
  M   43 lis r7, 0
  B   43 lis r6, 0
--- replace mine 45:47 base 45:50
  M   45 lwz r6, 0(r7)
  M   46 addi r4, r7, 0
  B   45 lwz r3, 0(r6)
  B   46 addi r4, r6, 0
  B   47 rlwinm r5, r3, 0, 0, 0x1e
  B   48 li r3, 0
  B   49 stw r5, 0(r6)
--- delete mine 48:51 base 51:51
  M   48 li r3, 0
  M   49 clrlwi r5, r6, 0x1f
  M   50 subf r5, r5, r6
--- delete mine 52:53 base 52:52
  M   52 stw r5, 0(r7)

## pfd_sddrv_finalize: MAX mask expressed as unsigned binary shift complement
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final mask uses read-only view of copied flags object
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX final mask uses read-only signed copied flags object
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX result object read-only view joins call status, flags read, zero return
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX reset helper receives separate const input object and mutable output object
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## MAX SD volatile combinations proof
Only the existing flags field is temporarily defined volatile. Target reads flags at function offsets 0x20 and 0x2c, both from the same global word and with no intervening store. This was already verified in HIGH; new tests combine this permitted definition with readonly field/helper boundaries. No use-site volatile cast and no unproven volatile media field is used. Any candidate must preserve every other unit output; variants with no exact gain are restored.

## pfd_sddrv_finalize: MAX target-proven volatile flags combined with readonly field pointer declaration
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX target-proven volatile flags combined with separate readonly flag input helper
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## pfd_sddrv_finalize: MAX target-proven volatile flags combined with separate readonly input object reset helper
instructions 57/57, structural/exact (6, 4); src 0xe4 base 0xe4 insns 57/57
diffs 4: [45, 47, 49, 50]
    45 M lwz r5, 0(r6)
       B lwz r3, 0(r6)
    47 M stw r0, 0x10(r4)
       B rlwinm r5, r3, 0, 0, 0x1e
    49 M rlwinm r5, r5, 0, 0, 0x1e
       B stw r5, 0(r6)
    50 M stw r5, 0(r6)
       B stw r0, 0x10(r4)

## MAX SD disposition
32 distinct MAX field/pointer/type/inline/algebra attempts logged, including target-proven volatile flags combined with readonly boundaries. No improvement retained. Widened flags and readonly driver-pointer holders changed unrelated register scheduling within the function; all simpler field views and separate reset helpers kept the original four differences. Final declsearch score-only: structural 6, exact 4. Baseline source restored; open at objdiff 92.63158%. Data remains 3592/3592, no renames/extents.

## MAX completeness audit before final full gate
NHTTPi_strnicmp: 30 logged distinct MAX tests; open, baseline source restored.
NWC24iCheckDlHeaderConsistency: 42 logged distinct MAX tests; open, baseline source restored.
pfd_sddrv_finalize: 32 logged distinct MAX tests; open, baseline source restored.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 40 logged distinct MAX tests; open, baseline source restored.
setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object: 25 logged distinct MAX tests; exact 195/195, diffs 0, objdiff 100.0% retained.
All four remaining assigned functions have at least three distinct real source attempts in this MAX round. Other unmatched functions in these partial units were explicitly outside the five-function assignment and were left untouched. No source changes retained outside setLangPane; no shared headers, configure, symbol names, extents or section totals changed. All unit data already paired exactly, with empty data in pf_cache. Failed variants are evidence only, not gains. Compiler scheduling/allocation remains an unresolved hypothesis for the four open functions; no cause is claimed proved by unsuccessful experiments.

## MAX final full gate and handoff
The following is the final non-quick full gate over all five assigned units, rebuilding clean 43U objects.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1388/2248 data 112/112 functions 11/14 fuzzy 87.9359 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] instruction-exact functions: 11/14
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .data size 72 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .text size 2248 match 87.93594
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_strnicmp 99.76471
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_compareToken 54.622223
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_Base64Encode 60.285713
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] baseline: code 1388/2248 data 112 functions 11 fuzzy 87.9359
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8140/12496 data 80/80 functions 25/30 fuzzy 99.1521 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 25/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.15205
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 99.303795
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8140/12496 data 80 functions 25 fuzzy 99.1521
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 3592/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 3592 functions 21 fuzzy 99.0544
[libs/RVL_SDK/src/fa/pf_cache] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_cache] objdiff: code 6464/7396 data None/None functions 35/36 fuzzy 99.9865 linked code 0
[libs/RVL_SDK/src/fa/pf_cache] instruction-exact functions: 35/36
[libs/RVL_SDK/src/fa/pf_cache]   section .text size 7396 match 99.98648
[libs/RVL_SDK/src/fa/pf_cache]   below 100: PFCACHE_DoWriteNumSectorAndFreeIfNeeded 99.8927
[libs/RVL_SDK/src/fa/pf_cache] baseline: code 6464/7396 data None functions 35 fuzzy 99.9865
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10924/10924 data 2216/2216 functions 56/56 fuzzy 100.0000 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 55/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 100.0
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.9927
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.83566
global fuzzy_match_percent: 99.58569 -> 99.58572
global complete_code_percent: 72.50912 -> 72.50912
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 320700d4; compared against nearest snapshotted ancestor 73795cb3 (5 commits back)
GATE PASS
```

Fresh exact-name objdiff report after the full gate:
libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL: code 1388 -> 1388; data 112 -> 112; NHTTPi_strnicmp 99.76471%; instructions 51/51; structural/exact (2, 2)
libs/RevoEX/src/nwc24/NWC24Download: code 8140 -> 8140; data 80 -> 80; NWC24iCheckDlHeaderConsistency 98.77358%; instructions 212/212; structural/exact (2, 3)
libs/RVL_SDK/src/fa/driver/sd_drv: code 8940 -> 8940; data 3592 -> 3592; pfd_sddrv_finalize 92.63158%; instructions 57/57; structural/exact (6, 4)
libs/RVL_SDK/src/fa/pf_cache: code 6464 -> 6464; data None -> None; PFCACHE_DoWriteNumSectorAndFreeIfNeeded 99.8927%; instructions 233/233; structural/exact (0, 4)
src/scene/channelSelect/iplChannelObj: code 10144 -> 10924; data 2216 -> 2216; setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object 100.0%; instructions 195/195; structural/exact (0, 0)
Remaining assigned near misses: NHTTPi_strnicmp, NWC24iCheckDlHeaderConsistency, pfd_sddrv_finalize, PFCACHE_DoWriteNumSectorAndFreeIfNeeded. Each has >=3 MAX attempts, with original source and baseline metrics restored. setLangPane is the only retained source improvement; instruction-exact ChannelObj 54/56 -> 55/56. calcCursorAnim is the inherited unrelated instruction-only discrepancy, already objdiff 100.0%; it was untouched. No further source cause is established for the four remaining functions. Final full build and DOL hash pass, regressions 0, forbidden/readability 0.

MAX round total: 169 logged source-level tests including compilation failures, by function {'NHTTP': 30, 'NWC': 42, 'SD': 32, 'cache': 40, 'ChannelObj': 25}. One exact function gained and committed as 4d92e916; four open functions each retain at least three logged MAX attempts. Only ChannelObj code gains 780 matched bytes; all data stays exact and unchanged.
calcCursorAnim tooling detail: ctxdiff reports 60/60 instructions and three conditional branch displacement differences at 11/21/22; objdiff reports 100.0% and its source is unchanged from the baseline. The strict gate count remains 55/56 for this inherited case; no workaround was attempted.
