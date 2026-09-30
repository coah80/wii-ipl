# sol-med matching attempts

Baseline and per-attempt instruction differences were measured with ctxdiff. Unaccepted variants were restored.

## Initial pool: src/scene/address/iplAddressEdit

POOL IDENTICAL up to 57 (mine=57 base=57)

## Initial pool: src/scene/address/iplAddress

POOL IDENTICAL up to 81 (mine=81 base=81)

## Initial pool: src/iplwww/www_wiisetting

POOL IDENTICAL up to 72 (mine=72 base=72)

## Initial pool: src/scene/cardSequence/iplCardSequence

POOL IDENTICAL up to 43 (mine=43 base=43)

## src/scene/address/iplAddressEdit: stt_wait_decide_anm__Q33ipl5scene11AddressEditFv

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- local type: name-edit text panes retained as TextBox pointers: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- temporary type: first question pane a TextBox, later labels remain Pane pointers: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- inline boundaries: typed name-edit panes and base animation controller: exact False; insns 379/379; differences 4; objdiff 99.94723

```text
src 0x5ec base 0x5ec insns 379/379
diffs 4: [109, 113, 148, 156]
   109 M mr r27, r3
       B mr r28, r3
   113 M stw r30, 0x14(r27)
       B stw r30, 0x14(r28)
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

## src/scene/address/iplAddressEdit: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x178 base 0x178 insns 94/94
diffs 5: [20, 29, 41, 82, 86]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
    82 M mr r30, r3
       B mr r29, r3
    86 M stw r3, 0x14(r30)
       B stw r3, 0x14(r29)
```

- local declaration order: long friend status before completion, base final animator: exact False; insns 94/94; differences 3; objdiff 99.84042

```text
src 0x178 base 0x178 insns 94/94
diffs 3: [20, 29, 41]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
```

- local type: int friend status with base animation controller: exact False; insns 94/94; differences 4; objdiff 99.202126

```text
src 0x178 base 0x178 insns 94/94
diffs 4: [11, 20, 29, 41]
    11 M cmpwi r0, 2
       B cmplwi r0, 2
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
```

- inline/local types: int status and TextBox message label: exact False; insns 94/94; differences 4; objdiff 99.202126

```text
src 0x178 base 0x178 insns 94/94
diffs 4: [11, 20, 29, 41]
    11 M cmpwi r0, 2
       B cmplwi r0, 2
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
```

## src/scene/address/iplAddressEdit: stt_add_code_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- local types: all labels retained as TextBox pointers: exact False; insns 111/111; differences 8; objdiff 99.63964

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- inline boundaries: TextBox labels and base animation controller: exact False; insns 111/111; differences 8; objdiff 99.63964

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- temporary lifetime: typed labels, name pointer computed before lookup: exact False; insns 111/111; differences 8; objdiff 99.63964

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

## src/scene/address/iplAddressEdit: update_friendinfo__Q33ipl5scene11AddressEditFv

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

- inline boundary: copy helper accepts source name before destination record: exact False; insns 38/38; differences 2; objdiff 99.42105

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

- inline helper with source name pointer initialized before invocation: exact False; insns 38/38; differences 2; objdiff 99.42105

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

- inline helper with name array reference at copy boundary: exact False; insns 38/38; differences 2; objdiff 99.42105

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

## src/scene/address/iplAddressEdit: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface

```text
src 0x2d4 base 0x2d8 insns 181/182
--- replace mine 12:14 base 12:14
  M   12 beq 468
  M   13 bge 648
  B   12 beq 472
  B   13 bge 652
--- replace mine 16:17 base 16:17
  M   16 b 636
  B   16 b 640
--- replace mine 18:20 base 18:20
  M   18 beq 168
  M   19 bge 624
  B   18 beq 172
  B   19 bge 628
--- replace mine 21:23 base 21:24
  M   21 beq 12
  M   22 bge 312
  B   21 beq 16
  B   22 bge 316
  B   23 b 612
--- insert mine 83:83 base 84:86
  B   84 lfs f1, 0(0)
  B   85 addi r4, r1, 0x14
--- delete mine 84:86 base 87:87
  M   84 addi r4, r1, 0x14
  M   85 lfs f1, 0(0)
--- insert mine 155:155 base 156:158
  B  156 lfs f1, 0(0)
  B  157 addi r4, r1, 8
--- delete mine 156:158 base 159:159
  M  156 addi r4, r1, 8
  M  157 lfs f1, 0(0)
```

- branch structure: nested state/button switches with balloon fallthrough: exact False; insns 181/182; differences None; objdiff 99.34066

```text
src 0x2d4 base 0x2d8 insns 181/182
--- replace mine 12:14 base 12:14
  M   12 beq 468
  M   13 bge 648
  B   12 beq 472
  B   13 bge 652
--- replace mine 16:17 base 16:17
  M   16 b 636
  B   16 b 640
--- replace mine 18:20 base 18:20
  M   18 beq 168
  M   19 bge 624
  B   18 beq 172
  B   19 bge 628
--- replace mine 21:23 base 21:24
  M   21 beq 12
  M   22 bge 312
  B   21 beq 16
  B   22 bge 316
  B   23 b 612
--- insert mine 83:83 base 84:86
  B   84 lfs f1, 0(0)
  B   85 addi r4, r1, 0x14
--- delete mine 84:86 base 87:87
  M   84 addi r4, r1, 0x14
  M   85 lfs f1, 0(0)
--- insert mine 155:155 base 156:158
  B  156 lfs f1, 0(0)
  B  157 addi r4, r1, 8
--- delete mine 156:158 base 159:159
  M  156 addi r4, r1, 8
  M  157 lfs f1, 0(0)
```

- nested dispatch and local type: signed-long button selector: exact False; insns 181/182; differences None; objdiff 99.34066

```text
src 0x2d4 base 0x2d8 insns 181/182
--- replace mine 12:14 base 12:14
  M   12 beq 468
  M   13 bge 648
  B   12 beq 472
  B   13 bge 652
--- replace mine 16:17 base 16:17
  M   16 b 636
  B   16 b 640
--- replace mine 18:20 base 18:20
  M   18 beq 168
  M   19 bge 624
  B   18 beq 172
  B   19 bge 628
--- replace mine 21:23 base 21:24
  M   21 beq 12
  M   22 bge 312
  B   21 beq 16
  B   22 bge 316
  B   23 b 612
--- insert mine 83:83 base 84:86
  B   84 lfs f1, 0(0)
  B   85 addi r4, r1, 0x14
--- delete mine 84:86 base 87:87
  M   84 addi r4, r1, 0x14
  M   85 lfs f1, 0(0)
--- insert mine 155:155 base 156:158
  B  156 lfs f1, 0(0)
  B  157 addi r4, r1, 8
--- delete mine 156:158 base 159:159
  M  156 addi r4, r1, 8
  M  157 lfs f1, 0(0)
```

- nested dispatch and operand order: height before scale in balloon offset product: exact False; insns 181/182; differences None; objdiff 99.23077

```text
src 0x2d4 base 0x2d8 insns 181/182
--- replace mine 12:14 base 12:14
  M   12 beq 468
  M   13 bge 648
  B   12 beq 472
  B   13 bge 652
--- replace mine 16:17 base 16:17
  M   16 b 636
  B   16 b 640
--- replace mine 18:20 base 18:20
  M   18 beq 168
  M   19 bge 624
  B   18 beq 172
  B   19 bge 628
--- replace mine 21:23 base 21:24
  M   21 beq 12
  M   22 bge 312
  B   21 beq 16
  B   22 bge 316
  B   23 b 612
--- insert mine 83:83 base 84:86
  B   84 lfs f1, 0(0)
  B   85 addi r4, r1, 0x14
--- delete mine 84:86 base 87:87
  M   84 addi r4, r1, 0x14
  M   85 lfs f1, 0(0)
--- replace mine 89:90 base 90:91
  M   89 fmuls f1, f0, f1
  B   90 fmuls f1, f1, f0
--- insert mine 155:155 base 156:158
  B  156 lfs f1, 0(0)
  B  157 addi r4, r1, 8
--- delete mine 156:158 base 159:159
  M  156 addi r4, r1, 8
  M  157 lfs f1, 0(0)
--- replace mine 161:162 base 162:163
  M  161 fmuls f1, f0, f1
  B  162 fmuls f1, f1, f0
```

## src/scene/address/iplAddressEdit: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err

```text
src 0x130 base 0x12c insns 76/75
--- delete mine 46:47 base 46:46
  M   46 li r4, 0x1c5
```

- local type: initialized error message held as int: exact False; insns 76/75; differences None; objdiff 98.666664

```text
src 0x130 base 0x12c insns 76/75
--- delete mine 46:47 base 46:46
  M   46 li r4, 0x1c5
```

- branch form: server/full/default share explicit initialized switch arm: exact False; insns 73/75; differences None; objdiff 97.2

```text
src 0x124 base 0x12c insns 73/75
--- replace mine 46:49 base 46:51
  M   46 beq 24
  M   47 bge 8
  M   48 b 24
  B   46 beq 32
  B   47 bge 16
  B   48 cmpwi r30, -0x20
  B   49 bge 28
  B   50 b 28
--- replace mine 51:52 base 53:54
  M   51 b 12
  B   53 b 16
```

- stack construction: value-initialized error string replaces memset: exact False; insns 79/75; differences None; objdiff 92.18667

```text
src 0x13c base 0x12c insns 79/75
--- replace mine 26:33 base 26:30
  M   26 li r0, 0x10
  M   27 addi r4, r1, 6
  M   28 li r3, 0
  M   29 mtctr r0
  M   30 sth r3, 2(r4)
  M   31 sthu r3, 4(r4)
  M   32 bdnz -8
  B   26 addi r3, r1, 8
  B   27 li r4, 0
  B   28 li r5, 0x40
  B   29 bl 0
--- delete mine 49:50 base 46:46
  M   49 li r4, 0x1c5
```

## src/scene/address/iplAddressEdit: create__Q33ipl5scene11AddressEditFv

```text
src 0xcd0 base 0xcd0 insns 820/820
diffs 323: [10, 14, 17, 24, 25, 30, 31, 36, 37, 42, 43, 48, 49, 54, 55, 60, 61, 66, 67, 72]
    10 M lis r30, 0
       B lis r31, 0
    14 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M lwz r31, 0xd20(r3)
       B lwz r30, 0xd20(r3)
    24 M mr r5, r31
       B mr r5, r30
    25 M addi r7, r30, 0x72
       B addi r7, r31, 0x72
    30 M addi r4, r30, 0x84
       B addi r4, r31, 0x84
    31 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
    36 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    37 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    42 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    43 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    48 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    49 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    54 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    55 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    60 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    61 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    66 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    67 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    72 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    73 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    78 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    79 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    84 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    85 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    90 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    91 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    96 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
    97 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   102 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   103 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   108 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   109 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   114 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   115 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   120 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   121 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   126 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   127 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   132 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   133 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   138 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   139 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   144 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   145 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   150 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   151 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   156 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   157 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   162 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   163 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   168 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   169 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   174 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   175 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   180 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   181 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   186 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   187 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   192 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   193 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   198 M addi r4, r30, 0x17e
       B addi r4, r31, 0x17e
   199 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   204 M addi r4, r30, 0x1a9
       B addi r4, r31, 0x1a9
   205 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   210 M addi r4, r30, 0x1cc
       B addi r4, r31, 0x1cc
   211 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
   252 M addi r27, r30, 0x44
       B addi r27, r31, 0x44
   271 M addi r4, r30, 0x1e8
       B addi r4, r31, 0x1e8
   281 M mr r23, r3
       B mr r27, r3
   289 M mr r4, r23
       B mr r4, r27
   292 M addi r4, r30, 0x1f5
       B addi r4, r31, 0x1f5
   300 M mr r25, r3
       B mr r27, r3
   306 M mr r4, r25
       B mr r4, r27
   309 M addi r4, r30, 0x202
       B addi r4, r31, 0x202
   317 M mr r25, r3
       B mr r27, r3
   323 M mr r4, r25
       B mr r4, r27
   326 M addi r4, r30, 0x20f
       B addi r4, r31, 0x20f
   334 M mr r25, r3
       B mr r27, r3
   340 M mr r4, r25
       B mr r4, r27
   343 M addi r4, r30, 0x21d
       B addi r4, r31, 0x21d
   355 M addi r4, r30, 0x22b
       B addi r4, r31, 0x22b
   367 M addi r4, r30, 0xf5
       B addi r4, r31, 0xf5
   384 M mr r5, r31
       B mr r5, r30
   385 M addi r7, r30, 0x235
       B addi r7, r31, 0x235
   390 M addi r4, r30, 0x247
       B addi r4, r31, 0x247
   391 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   396 M addi r4, r30, 0x274
       B addi r4, r31, 0x274
   397 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   402 M addi r4, r30, 0x2a4
       B addi r4, r31, 0x2a4
   403 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   408 M addi r4, r30, 0x2cc
       B addi r4, r31, 0x2cc
   409 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   414 M addi r4, r30, 0x2f2
       B addi r4, r31, 0x2f2
   420 M addi r4, r30, 0x30f
       B addi r4, r31, 0x30f
   421 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   426 M addi r4, r30, 0x332
       B addi r4, r31, 0x332
   427 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   432 M addi r4, r30, 0x351
       B addi r4, r31, 0x351
   433 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   438 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   444 M addi r4, r30, 0x38d
       B addi r4, r31, 0x38d
   445 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   505 M mr r5, r31
       B mr r5, r30
   506 M addi r7, r30, 0x3a9
       B addi r7, r31, 0x3a9
   510 M addi r4, r30, 0x3b9
       B addi r4, r31, 0x3b9
   511 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   516 M addi r4, r30, 0x3da
       B addi r4, r31, 0x3da
   517 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   536 M lis r31, 0
       B lis r30, 0
   538 M addi r31, r31, 0
       B addi r30, r30, 0
   541 M lwz r3, 0x64(r31)
       B lwz r3, 0x64(r30)
   547 M beq 300
       B beq 308
   551 M b 832
       B b 840
   553 M bge 824
       B bge 832
   554 M b 548
       B b 556
   591 M mr r25, r3
       B mr r27, r3
   594 M addi r4, r30, 0x22b
       B addi r25, r29, 0x2b4
   595 M stw r0, 0x14(r25)
       B stw r0, 0x14(r27)
   596 M li r5, 1
       B addi r4, r31, 0x22b
   597 M lwz r3, 0x68(r29)
       B li r5, 1
   598 M lwz r3, 0x14(r3)
       B lwz r3, 0x68(r29)
   599 M lwz r12, 0(r3)
       B lwz r3, 0x14(r3)
   600 M lwz r12, 0x3c(r12)
       B lwz r12, 0(r3)
   601 M mtctr r12
       B lwz r12, 0x3c(r12)
   602 M bctrl
       B mtctr r12
   603 M mr r4, r3
       B bctrl
   604 M mr r3, r29
       B mr r4, r3
   605 M addi r5, r29, 0x2b4
       B mr r3, r29
   606 M bl 0
       B mr r5, r25
   607 M lwz r3, 0x68(r29)
       B bl 0
   608 M addi r4, r30, 0xf5
       B lwz r3, 0x68(r29)
   609 M li r5, 1
       B addi r25, r29, 0x2cc
   610 M lwz r3, 0x14(r3)
       B addi r4, r31, 0xf5
   611 M lwz r12, 0(r3)
       B li r5, 1
   612 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   613 M mtctr r12
       B lwz r12, 0(r3)
   614 M bctrl
       B lwz r12, 0x3c(r12)
   615 M mr r4, r3
       B mtctr r12
   616 M mr r3, r29
       B bctrl
   617 M addi r5, r29, 0x2cc
       B mr r4, r3
   618 M bl 0
       B mr r3, r29
   619 M li r0, 0
       B mr r5, r25
   620 M stw r0, 0x64(r29)
       B bl 0
   621 M b 552
       B li r0, 0
   622 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   623 M li r4, 0
       B b 552
   624 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   625 M bl 0
       B li r4, 0
   626 M mr r25, r3
       B addi r3, r3, 0x28c
   628 M li r28, 1
       B mr r27, r3
   629 M li r4, 1
       B bl 0
   630 M stw r28, 0x14(r25)
       B li r28, 1
   631 M lwz r3, 0x74(r29)
       B li r4, 1
   632 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   633 M bl 0
       B lwz r3, 0x74(r29)
   634 M mr r25, r3
       B addi r3, r3, 0x28c
   636 M stw r28, 0x14(r25)
       B mr r27, r3
   637 M li r4, 3
       B bl 0
   638 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   639 M addi r3, r3, 0x28c
       B li r4, 3
   640 M bl 0
       B lwz r3, 0x74(r29)
   641 M mr r25, r3
       B addi r3, r3, 0x28c
   643 M stw r28, 0x14(r25)
       B mr r27, r3
   644 M li r4, 0x1a
       B bl 0
   645 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   646 M addi r3, r3, 0x28c
       B li r4, 0x1a
   647 M bl 0
       B lwz r3, 0x68(r29)
   648 M bl 0
       B addi r3, r3, 0x28c
   649 M lwz r3, 0x68(r29)
       B bl 0
   650 M li r4, 0x10
       B bl 0
   651 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   652 M bl 0
       B li r4, 0x10
   653 M bl 0
       B addi r3, r3, 0x28c
   654 M lwz r3, 0x74(r29)
       B bl 0
   655 M addi r4, r30, 0x3ef
       B bl 0
   656 M li r5, 1
       B lwz r3, 0x74(r29)
   657 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   658 M lwz r12, 0(r3)
       B li r5, 1
   659 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   660 M mtctr r12
       B lwz r12, 0(r3)
   661 M bctrl
       B lwz r12, 0x3c(r12)
   662 M lwz r5, 0x80(r31)
       B mtctr r12
   663 M mr r25, r3
       B bctrl
   664 M li r4, 0x31
       B lwz r5, 0x80(r30)
   665 M lwz r3, 0(r5)
       B mr r27, r3
   666 M bl 0
       B li r4, 0x31
   667 M mr r5, r3
       B lwz r3, 0(r5)
   668 M mr r3, r29
       B bl 0
   669 M mr r4, r25
       B mr r5, r3
   670 M bl 0
       B mr r3, r29
   671 M lwz r3, 0x74(r29)
       B mr r4, r27
   672 M addi r4, r30, 0x3fd
       B bl 0
   673 M li r5, 1
       B lwz r3, 0x74(r29)
   674 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   675 M lwz r12, 0(r3)
       B li r5, 1
   676 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   677 M mtctr r12
       B lwz r12, 0(r3)
   678 M bctrl
       B lwz r12, 0x3c(r12)
   679 M lwz r5, 0x80(r31)
       B mtctr r12
   680 M mr r25, r3
       B bctrl
   681 M li r4, 0x47
       B lwz r5, 0x80(r30)
   682 M lwz r3, 0(r5)
       B mr r27, r3
   683 M bl 0
       B li r4, 0x47
   684 M mr r5, r3
       B lwz r3, 0(r5)
   685 M mr r3, r29
       B bl 0
   686 M mr r4, r25
       B mr r5, r3
   687 M bl 0
       B mr r3, r29
   688 M li r0, 0x10
       B mr r4, r27
   689 M stw r0, 0x64(r29)
       B bl 0
   690 M b 276
       B li r0, 0x10
   691 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   692 M li r4, 0
       B b 276
   693 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   694 M bl 0
       B li r4, 0
   695 M mr r25, r3
       B addi r3, r3, 0x28c
   697 M li r28, 1
       B mr r27, r3
   698 M li r4, 1
       B bl 0
   699 M stw r28, 0x14(r25)
       B li r28, 1
   700 M lwz r3, 0x74(r29)
       B li r4, 1
   701 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   702 M bl 0
       B lwz r3, 0x74(r29)
   703 M mr r25, r3
       B addi r3, r3, 0x28c
   705 M stw r28, 0x14(r25)
       B mr r27, r3
   706 M li r4, 3
       B bl 0
   707 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   708 M addi r3, r3, 0x28c
       B li r4, 3
   709 M bl 0
       B lwz r3, 0x74(r29)
   710 M mr r25, r3
       B addi r3, r3, 0x28c
   712 M stw r28, 0x14(r25)
       B mr r27, r3
   713 M li r4, 0x1a
       B bl 0
   714 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   715 M addi r3, r3, 0x28c
       B li r4, 0x1a
   716 M bl 0
       B lwz r3, 0x68(r29)
   717 M bl 0
       B addi r3, r3, 0x28c
   718 M lwz r3, 0x68(r29)
       B bl 0
   719 M li r4, 0x10
       B bl 0
   720 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   721 M bl 0
       B li r4, 0x10
   722 M bl 0
       B addi r3, r3, 0x28c
   723 M lwz r3, 0x74(r29)
       B bl 0
   724 M addi r4, r30, 0x3ef
       B bl 0
   725 M li r5, 1
       B lwz r3, 0x74(r29)
   726 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   727 M lwz r12, 0(r3)
       B li r5, 1
   728 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   729 M mtctr r12
       B lwz r12, 0(r3)
   730 M bctrl
       B lwz r12, 0x3c(r12)
   731 M lwz r5, 0x80(r31)
       B mtctr r12
   732 M mr r25, r3
       B bctrl
   733 M li r4, 0x3f
       B lwz r5, 0x80(r30)
   734 M lwz r3, 0(r5)
       B mr r27, r3
   735 M bl 0
       B li r4, 0x3f
   736 M mr r5, r3
       B lwz r3, 0(r5)
   737 M mr r3, r29
       B bl 0
   738 M mr r4, r25
       B mr r5, r3
   739 M bl 0
       B mr r3, r29
   740 M lwz r3, 0x74(r29)
       B mr r4, r27
   741 M addi r4, r30, 0x3fd
       B bl 0
   742 M li r5, 1
       B lwz r3, 0x74(r29)
   743 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   744 M lwz r12, 0(r3)
       B li r5, 1
   745 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   746 M mtctr r12
       B lwz r12, 0(r3)
   747 M bctrl
       B lwz r12, 0x3c(r12)
   748 M lwz r5, 0x80(r31)
       B mtctr r12
   749 M mr r25, r3
       B bctrl
   750 M li r4, 0x48
       B lwz r5, 0x80(r30)
   751 M lwz r3, 0(r5)
       B mr r27, r3
   752 M bl 0
       B li r4, 0x48
   753 M mr r5, r3
       B lwz r3, 0(r5)
   754 M mr r3, r29
       B bl 0
   755 M mr r4, r25
       B mr r5, r3
   756 M bl 0
       B mr r3, r29
   757 M li r0, 0x10
       B mr r4, r27
   758 M stw r0, 0x64(r29)
       B bl 0
   759 M addi r3, r29, 0x4e0
       B li r0, 0x10
   760 M addi r4, r1, 8
       B stw r0, 0x64(r29)
   761 M bl 0
       B addi r3, r29, 0x4e0
   762 M cmpwi r3, 0
       B addi r4, r1, 8
   763 M beq 56
       B bl 0
   764 M lis r4, 0
       B cmpwi r3, 0
   765 M lis r8, 0
       B beq 56
   766 M addi r4, r4, 0
       B lis r3, 0
   767 M lha r7, 8(r1)
       B lis r8, 0
   768 M lwz r3, 0x70(r4)
       B addi r3, r3, 0
   769 M mr r9, r29
       B lha r7, 8(r1)
   770 M lwz r4, 0x28(r4)
       B lwz r4, 0x28(r3)
   771 M addi r8, r8, 0
       B mr r9, r29
   772 M li r5, 0x4c
       B lwz r3, 0x70(r3)
   773 M li r6, 0x4c
       B addi r8, r8, 0
   774 M bl 0
       B li r5, 0x4c
   775 M li r0, 1
       B li r6, 0x4c
   776 M stw r0, 0x4e8(r29)
       B bl 0
   777 M lis r3, 0
       B li r0, 1
   778 M addi r3, r3, 0
       B stw r0, 0x4e8(r29)
   779 M lwz r3, 0x90(r3)
       B lis r3, 0
   780 M lwz r12, 0(r3)
       B addi r3, r3, 0
   781 M lwz r12, 0xc(r12)
       B lwz r3, 0x90(r3)
   782 M mtctr r12
       B lwz r12, 0(r3)
   783 M bctrl
       B lwz r12, 0xc(r12)
   784 M li r3, 0x3c
       B mtctr r12
   785 M bl 0
       B bctrl
   786 M cmpwi r3, 0
       B li r3, 0x3c
   787 M mr r23, r3
       B bl 0
   788 M beq 84
       B cmpwi r3, 0
   789 M lfs f1, 0(0)
       B mr r25, r3
   790 M addi r3, r1, 0xc
       B beq 76
   791 M lfs f31, 0(0)
       B lfs f1, 0(0)
   792 M fmr f2, f1
       B addi r3, r1, 0xc
   793 M lfs f30, 0(0)
       B lfs f31, 0(0)
   794 M fmr f3, f1
       B fmr f2, f1
   795 M lwz r25, 0x24(r29)
       B lfs f30, 0(0)
   796 M bl 0
       B fmr f3, f1
   797 M cmpwi r23, 0
       B lwz r26, 0x24(r29)
   798 M beq 44
       B bl 0
   800 M lwz r5, 0xac(r29)
       B mr r8, r3
   802 M mr r3, r23
       B lwz r5, 0xac(r29)
   803 M mr r4, r25
       B mr r3, r25
   804 M addi r7, r30, 0x406
       B mr r4, r26
   805 M addi r8, r1, 0xc
       B addi r7, r31, 0x406
   808 M mr r23, r3
       B mr r25, r3
   809 M stw r23, 0xa8(r29)
       B stw r25, 0xa8(r29)
```

- local type: board archive retained as LangFile base pointer: exact False; insns 820/820; differences 323; objdiff 97.44634

```text
src 0xcd0 base 0xcd0 insns 820/820
diffs 323: [10, 14, 17, 24, 25, 30, 31, 36, 37, 42, 43, 48, 49, 54, 55, 60, 61, 66, 67, 72]
    10 M lis r30, 0
       B lis r31, 0
    14 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M lwz r31, 0xd20(r3)
       B lwz r30, 0xd20(r3)
    24 M mr r5, r31
       B mr r5, r30
    25 M addi r7, r30, 0x72
       B addi r7, r31, 0x72
    30 M addi r4, r30, 0x84
       B addi r4, r31, 0x84
    31 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
    36 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    37 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    42 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    43 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    48 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    49 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    54 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    55 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    60 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    61 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    66 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    67 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    72 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    73 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    78 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    79 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    84 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    85 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    90 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    91 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    96 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
    97 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   102 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   103 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   108 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   109 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   114 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   115 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   120 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   121 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   126 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   127 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   132 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   133 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   138 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   139 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   144 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   145 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   150 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   151 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   156 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   157 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   162 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   163 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   168 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   169 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   174 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   175 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   180 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   181 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   186 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   187 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   192 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   193 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   198 M addi r4, r30, 0x17e
       B addi r4, r31, 0x17e
   199 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   204 M addi r4, r30, 0x1a9
       B addi r4, r31, 0x1a9
   205 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   210 M addi r4, r30, 0x1cc
       B addi r4, r31, 0x1cc
   211 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
   252 M addi r27, r30, 0x44
       B addi r27, r31, 0x44
   271 M addi r4, r30, 0x1e8
       B addi r4, r31, 0x1e8
   281 M mr r23, r3
       B mr r27, r3
   289 M mr r4, r23
       B mr r4, r27
   292 M addi r4, r30, 0x1f5
       B addi r4, r31, 0x1f5
   300 M mr r25, r3
       B mr r27, r3
   306 M mr r4, r25
       B mr r4, r27
   309 M addi r4, r30, 0x202
       B addi r4, r31, 0x202
   317 M mr r25, r3
       B mr r27, r3
   323 M mr r4, r25
       B mr r4, r27
   326 M addi r4, r30, 0x20f
       B addi r4, r31, 0x20f
   334 M mr r25, r3
       B mr r27, r3
   340 M mr r4, r25
       B mr r4, r27
   343 M addi r4, r30, 0x21d
       B addi r4, r31, 0x21d
   355 M addi r4, r30, 0x22b
       B addi r4, r31, 0x22b
   367 M addi r4, r30, 0xf5
       B addi r4, r31, 0xf5
   384 M mr r5, r31
       B mr r5, r30
   385 M addi r7, r30, 0x235
       B addi r7, r31, 0x235
   390 M addi r4, r30, 0x247
       B addi r4, r31, 0x247
   391 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   396 M addi r4, r30, 0x274
       B addi r4, r31, 0x274
   397 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   402 M addi r4, r30, 0x2a4
       B addi r4, r31, 0x2a4
   403 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   408 M addi r4, r30, 0x2cc
       B addi r4, r31, 0x2cc
   409 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   414 M addi r4, r30, 0x2f2
       B addi r4, r31, 0x2f2
   420 M addi r4, r30, 0x30f
       B addi r4, r31, 0x30f
   421 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   426 M addi r4, r30, 0x332
       B addi r4, r31, 0x332
   427 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   432 M addi r4, r30, 0x351
       B addi r4, r31, 0x351
   433 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   438 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   444 M addi r4, r30, 0x38d
       B addi r4, r31, 0x38d
   445 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   505 M mr r5, r31
       B mr r5, r30
   506 M addi r7, r30, 0x3a9
       B addi r7, r31, 0x3a9
   510 M addi r4, r30, 0x3b9
       B addi r4, r31, 0x3b9
   511 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   516 M addi r4, r30, 0x3da
       B addi r4, r31, 0x3da
   517 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   536 M lis r31, 0
       B lis r30, 0
   538 M addi r31, r31, 0
       B addi r30, r30, 0
   541 M lwz r3, 0x64(r31)
       B lwz r3, 0x64(r30)
   547 M beq 300
       B beq 308
   551 M b 832
       B b 840
   553 M bge 824
       B bge 832
   554 M b 548
       B b 556
   591 M mr r25, r3
       B mr r27, r3
   594 M addi r4, r30, 0x22b
       B addi r25, r29, 0x2b4
   595 M stw r0, 0x14(r25)
       B stw r0, 0x14(r27)
   596 M li r5, 1
       B addi r4, r31, 0x22b
   597 M lwz r3, 0x68(r29)
       B li r5, 1
   598 M lwz r3, 0x14(r3)
       B lwz r3, 0x68(r29)
   599 M lwz r12, 0(r3)
       B lwz r3, 0x14(r3)
   600 M lwz r12, 0x3c(r12)
       B lwz r12, 0(r3)
   601 M mtctr r12
       B lwz r12, 0x3c(r12)
   602 M bctrl
       B mtctr r12
   603 M mr r4, r3
       B bctrl
   604 M mr r3, r29
       B mr r4, r3
   605 M addi r5, r29, 0x2b4
       B mr r3, r29
   606 M bl 0
       B mr r5, r25
   607 M lwz r3, 0x68(r29)
       B bl 0
   608 M addi r4, r30, 0xf5
       B lwz r3, 0x68(r29)
   609 M li r5, 1
       B addi r25, r29, 0x2cc
   610 M lwz r3, 0x14(r3)
       B addi r4, r31, 0xf5
   611 M lwz r12, 0(r3)
       B li r5, 1
   612 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   613 M mtctr r12
       B lwz r12, 0(r3)
   614 M bctrl
       B lwz r12, 0x3c(r12)
   615 M mr r4, r3
       B mtctr r12
   616 M mr r3, r29
       B bctrl
   617 M addi r5, r29, 0x2cc
       B mr r4, r3
   618 M bl 0
       B mr r3, r29
   619 M li r0, 0
       B mr r5, r25
   620 M stw r0, 0x64(r29)
       B bl 0
   621 M b 552
       B li r0, 0
   622 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   623 M li r4, 0
       B b 552
   624 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   625 M bl 0
       B li r4, 0
   626 M mr r25, r3
       B addi r3, r3, 0x28c
   628 M li r28, 1
       B mr r27, r3
   629 M li r4, 1
       B bl 0
   630 M stw r28, 0x14(r25)
       B li r28, 1
   631 M lwz r3, 0x74(r29)
       B li r4, 1
   632 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   633 M bl 0
       B lwz r3, 0x74(r29)
   634 M mr r25, r3
       B addi r3, r3, 0x28c
   636 M stw r28, 0x14(r25)
       B mr r27, r3
   637 M li r4, 3
       B bl 0
   638 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   639 M addi r3, r3, 0x28c
       B li r4, 3
   640 M bl 0
       B lwz r3, 0x74(r29)
   641 M mr r25, r3
       B addi r3, r3, 0x28c
   643 M stw r28, 0x14(r25)
       B mr r27, r3
   644 M li r4, 0x1a
       B bl 0
   645 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   646 M addi r3, r3, 0x28c
       B li r4, 0x1a
   647 M bl 0
       B lwz r3, 0x68(r29)
   648 M bl 0
       B addi r3, r3, 0x28c
   649 M lwz r3, 0x68(r29)
       B bl 0
   650 M li r4, 0x10
       B bl 0
   651 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   652 M bl 0
       B li r4, 0x10
   653 M bl 0
       B addi r3, r3, 0x28c
   654 M lwz r3, 0x74(r29)
       B bl 0
   655 M addi r4, r30, 0x3ef
       B bl 0
   656 M li r5, 1
       B lwz r3, 0x74(r29)
   657 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   658 M lwz r12, 0(r3)
       B li r5, 1
   659 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   660 M mtctr r12
       B lwz r12, 0(r3)
   661 M bctrl
       B lwz r12, 0x3c(r12)
   662 M lwz r5, 0x80(r31)
       B mtctr r12
   663 M mr r25, r3
       B bctrl
   664 M li r4, 0x31
       B lwz r5, 0x80(r30)
   665 M lwz r3, 0(r5)
       B mr r27, r3
   666 M bl 0
       B li r4, 0x31
   667 M mr r5, r3
       B lwz r3, 0(r5)
   668 M mr r3, r29
       B bl 0
   669 M mr r4, r25
       B mr r5, r3
   670 M bl 0
       B mr r3, r29
   671 M lwz r3, 0x74(r29)
       B mr r4, r27
   672 M addi r4, r30, 0x3fd
       B bl 0
   673 M li r5, 1
       B lwz r3, 0x74(r29)
   674 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   675 M lwz r12, 0(r3)
       B li r5, 1
   676 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   677 M mtctr r12
       B lwz r12, 0(r3)
   678 M bctrl
       B lwz r12, 0x3c(r12)
   679 M lwz r5, 0x80(r31)
       B mtctr r12
   680 M mr r25, r3
       B bctrl
   681 M li r4, 0x47
       B lwz r5, 0x80(r30)
   682 M lwz r3, 0(r5)
       B mr r27, r3
   683 M bl 0
       B li r4, 0x47
   684 M mr r5, r3
       B lwz r3, 0(r5)
   685 M mr r3, r29
       B bl 0
   686 M mr r4, r25
       B mr r5, r3
   687 M bl 0
       B mr r3, r29
   688 M li r0, 0x10
       B mr r4, r27
   689 M stw r0, 0x64(r29)
       B bl 0
   690 M b 276
       B li r0, 0x10
   691 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   692 M li r4, 0
       B b 276
   693 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   694 M bl 0
       B li r4, 0
   695 M mr r25, r3
       B addi r3, r3, 0x28c
   697 M li r28, 1
       B mr r27, r3
   698 M li r4, 1
       B bl 0
   699 M stw r28, 0x14(r25)
       B li r28, 1
   700 M lwz r3, 0x74(r29)
       B li r4, 1
   701 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   702 M bl 0
       B lwz r3, 0x74(r29)
   703 M mr r25, r3
       B addi r3, r3, 0x28c
   705 M stw r28, 0x14(r25)
       B mr r27, r3
   706 M li r4, 3
       B bl 0
   707 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   708 M addi r3, r3, 0x28c
       B li r4, 3
   709 M bl 0
       B lwz r3, 0x74(r29)
   710 M mr r25, r3
       B addi r3, r3, 0x28c
   712 M stw r28, 0x14(r25)
       B mr r27, r3
   713 M li r4, 0x1a
       B bl 0
   714 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   715 M addi r3, r3, 0x28c
       B li r4, 0x1a
   716 M bl 0
       B lwz r3, 0x68(r29)
   717 M bl 0
       B addi r3, r3, 0x28c
   718 M lwz r3, 0x68(r29)
       B bl 0
   719 M li r4, 0x10
       B bl 0
   720 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   721 M bl 0
       B li r4, 0x10
   722 M bl 0
       B addi r3, r3, 0x28c
   723 M lwz r3, 0x74(r29)
       B bl 0
   724 M addi r4, r30, 0x3ef
       B bl 0
   725 M li r5, 1
       B lwz r3, 0x74(r29)
   726 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   727 M lwz r12, 0(r3)
       B li r5, 1
   728 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   729 M mtctr r12
       B lwz r12, 0(r3)
   730 M bctrl
       B lwz r12, 0x3c(r12)
   731 M lwz r5, 0x80(r31)
       B mtctr r12
   732 M mr r25, r3
       B bctrl
   733 M li r4, 0x3f
       B lwz r5, 0x80(r30)
   734 M lwz r3, 0(r5)
       B mr r27, r3
   735 M bl 0
       B li r4, 0x3f
   736 M mr r5, r3
       B lwz r3, 0(r5)
   737 M mr r3, r29
       B bl 0
   738 M mr r4, r25
       B mr r5, r3
   739 M bl 0
       B mr r3, r29
   740 M lwz r3, 0x74(r29)
       B mr r4, r27
   741 M addi r4, r30, 0x3fd
       B bl 0
   742 M li r5, 1
       B lwz r3, 0x74(r29)
   743 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   744 M lwz r12, 0(r3)
       B li r5, 1
   745 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   746 M mtctr r12
       B lwz r12, 0(r3)
   747 M bctrl
       B lwz r12, 0x3c(r12)
   748 M lwz r5, 0x80(r31)
       B mtctr r12
   749 M mr r25, r3
       B bctrl
   750 M li r4, 0x48
       B lwz r5, 0x80(r30)
   751 M lwz r3, 0(r5)
       B mr r27, r3
   752 M bl 0
       B li r4, 0x48
   753 M mr r5, r3
       B lwz r3, 0(r5)
   754 M mr r3, r29
       B bl 0
   755 M mr r4, r25
       B mr r5, r3
   756 M bl 0
       B mr r3, r29
   757 M li r0, 0x10
       B mr r4, r27
   758 M stw r0, 0x64(r29)
       B bl 0
   759 M addi r3, r29, 0x4e0
       B li r0, 0x10
   760 M addi r4, r1, 8
       B stw r0, 0x64(r29)
   761 M bl 0
       B addi r3, r29, 0x4e0
   762 M cmpwi r3, 0
       B addi r4, r1, 8
   763 M beq 56
       B bl 0
   764 M lis r4, 0
       B cmpwi r3, 0
   765 M lis r8, 0
       B beq 56
   766 M addi r4, r4, 0
       B lis r3, 0
   767 M lha r7, 8(r1)
       B lis r8, 0
   768 M lwz r3, 0x70(r4)
       B addi r3, r3, 0
   769 M mr r9, r29
       B lha r7, 8(r1)
   770 M lwz r4, 0x28(r4)
       B lwz r4, 0x28(r3)
   771 M addi r8, r8, 0
       B mr r9, r29
   772 M li r5, 0x4c
       B lwz r3, 0x70(r3)
   773 M li r6, 0x4c
       B addi r8, r8, 0
   774 M bl 0
       B li r5, 0x4c
   775 M li r0, 1
       B li r6, 0x4c
   776 M stw r0, 0x4e8(r29)
       B bl 0
   777 M lis r3, 0
       B li r0, 1
   778 M addi r3, r3, 0
       B stw r0, 0x4e8(r29)
   779 M lwz r3, 0x90(r3)
       B lis r3, 0
   780 M lwz r12, 0(r3)
       B addi r3, r3, 0
   781 M lwz r12, 0xc(r12)
       B lwz r3, 0x90(r3)
   782 M mtctr r12
       B lwz r12, 0(r3)
   783 M bctrl
       B lwz r12, 0xc(r12)
   784 M li r3, 0x3c
       B mtctr r12
   785 M bl 0
       B bctrl
   786 M cmpwi r3, 0
       B li r3, 0x3c
   787 M mr r23, r3
       B bl 0
   788 M beq 84
       B cmpwi r3, 0
   789 M lfs f1, 0(0)
       B mr r25, r3
   790 M addi r3, r1, 0xc
       B beq 76
   791 M lfs f31, 0(0)
       B lfs f1, 0(0)
   792 M fmr f2, f1
       B addi r3, r1, 0xc
   793 M lfs f30, 0(0)
       B lfs f31, 0(0)
   794 M fmr f3, f1
       B fmr f2, f1
   795 M lwz r25, 0x24(r29)
       B lfs f30, 0(0)
   796 M bl 0
       B fmr f3, f1
   797 M cmpwi r23, 0
       B lwz r26, 0x24(r29)
   798 M beq 44
       B bl 0
   800 M lwz r5, 0xac(r29)
       B mr r8, r3
   802 M mr r3, r23
       B lwz r5, 0xac(r29)
   803 M mr r4, r25
       B mr r3, r25
   804 M addi r7, r30, 0x406
       B mr r4, r26
   805 M addi r8, r1, 0xc
       B addi r7, r31, 0x406
   808 M mr r23, r3
       B mr r25, r3
   809 M stw r23, 0xa8(r29)
       B stw r25, 0xa8(r29)
```

- local type: board archive retained as const LayoutFile pointer: exact False; insns 820/820; differences 323; objdiff 97.44634

```text
src 0xcd0 base 0xcd0 insns 820/820
diffs 323: [10, 14, 17, 24, 25, 30, 31, 36, 37, 42, 43, 48, 49, 54, 55, 60, 61, 66, 67, 72]
    10 M lis r30, 0
       B lis r31, 0
    14 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M lwz r31, 0xd20(r3)
       B lwz r30, 0xd20(r3)
    24 M mr r5, r31
       B mr r5, r30
    25 M addi r7, r30, 0x72
       B addi r7, r31, 0x72
    30 M addi r4, r30, 0x84
       B addi r4, r31, 0x84
    31 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
    36 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    37 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    42 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    43 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    48 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    49 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    54 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    55 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    60 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    61 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    66 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    67 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    72 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    73 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    78 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    79 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    84 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    85 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    90 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    91 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    96 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
    97 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   102 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   103 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   108 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   109 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   114 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   115 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   120 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   121 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   126 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   127 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   132 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   133 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   138 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   139 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   144 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   145 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   150 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   151 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   156 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   157 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   162 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   163 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   168 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   169 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   174 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   175 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   180 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   181 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   186 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   187 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   192 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   193 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   198 M addi r4, r30, 0x17e
       B addi r4, r31, 0x17e
   199 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   204 M addi r4, r30, 0x1a9
       B addi r4, r31, 0x1a9
   205 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   210 M addi r4, r30, 0x1cc
       B addi r4, r31, 0x1cc
   211 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
   252 M addi r27, r30, 0x44
       B addi r27, r31, 0x44
   271 M addi r4, r30, 0x1e8
       B addi r4, r31, 0x1e8
   281 M mr r23, r3
       B mr r27, r3
   289 M mr r4, r23
       B mr r4, r27
   292 M addi r4, r30, 0x1f5
       B addi r4, r31, 0x1f5
   300 M mr r25, r3
       B mr r27, r3
   306 M mr r4, r25
       B mr r4, r27
   309 M addi r4, r30, 0x202
       B addi r4, r31, 0x202
   317 M mr r25, r3
       B mr r27, r3
   323 M mr r4, r25
       B mr r4, r27
   326 M addi r4, r30, 0x20f
       B addi r4, r31, 0x20f
   334 M mr r25, r3
       B mr r27, r3
   340 M mr r4, r25
       B mr r4, r27
   343 M addi r4, r30, 0x21d
       B addi r4, r31, 0x21d
   355 M addi r4, r30, 0x22b
       B addi r4, r31, 0x22b
   367 M addi r4, r30, 0xf5
       B addi r4, r31, 0xf5
   384 M mr r5, r31
       B mr r5, r30
   385 M addi r7, r30, 0x235
       B addi r7, r31, 0x235
   390 M addi r4, r30, 0x247
       B addi r4, r31, 0x247
   391 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   396 M addi r4, r30, 0x274
       B addi r4, r31, 0x274
   397 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   402 M addi r4, r30, 0x2a4
       B addi r4, r31, 0x2a4
   403 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   408 M addi r4, r30, 0x2cc
       B addi r4, r31, 0x2cc
   409 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   414 M addi r4, r30, 0x2f2
       B addi r4, r31, 0x2f2
   420 M addi r4, r30, 0x30f
       B addi r4, r31, 0x30f
   421 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   426 M addi r4, r30, 0x332
       B addi r4, r31, 0x332
   427 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   432 M addi r4, r30, 0x351
       B addi r4, r31, 0x351
   433 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   438 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   444 M addi r4, r30, 0x38d
       B addi r4, r31, 0x38d
   445 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   505 M mr r5, r31
       B mr r5, r30
   506 M addi r7, r30, 0x3a9
       B addi r7, r31, 0x3a9
   510 M addi r4, r30, 0x3b9
       B addi r4, r31, 0x3b9
   511 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   516 M addi r4, r30, 0x3da
       B addi r4, r31, 0x3da
   517 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   536 M lis r31, 0
       B lis r30, 0
   538 M addi r31, r31, 0
       B addi r30, r30, 0
   541 M lwz r3, 0x64(r31)
       B lwz r3, 0x64(r30)
   547 M beq 300
       B beq 308
   551 M b 832
       B b 840
   553 M bge 824
       B bge 832
   554 M b 548
       B b 556
   591 M mr r25, r3
       B mr r27, r3
   594 M addi r4, r30, 0x22b
       B addi r25, r29, 0x2b4
   595 M stw r0, 0x14(r25)
       B stw r0, 0x14(r27)
   596 M li r5, 1
       B addi r4, r31, 0x22b
   597 M lwz r3, 0x68(r29)
       B li r5, 1
   598 M lwz r3, 0x14(r3)
       B lwz r3, 0x68(r29)
   599 M lwz r12, 0(r3)
       B lwz r3, 0x14(r3)
   600 M lwz r12, 0x3c(r12)
       B lwz r12, 0(r3)
   601 M mtctr r12
       B lwz r12, 0x3c(r12)
   602 M bctrl
       B mtctr r12
   603 M mr r4, r3
       B bctrl
   604 M mr r3, r29
       B mr r4, r3
   605 M addi r5, r29, 0x2b4
       B mr r3, r29
   606 M bl 0
       B mr r5, r25
   607 M lwz r3, 0x68(r29)
       B bl 0
   608 M addi r4, r30, 0xf5
       B lwz r3, 0x68(r29)
   609 M li r5, 1
       B addi r25, r29, 0x2cc
   610 M lwz r3, 0x14(r3)
       B addi r4, r31, 0xf5
   611 M lwz r12, 0(r3)
       B li r5, 1
   612 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   613 M mtctr r12
       B lwz r12, 0(r3)
   614 M bctrl
       B lwz r12, 0x3c(r12)
   615 M mr r4, r3
       B mtctr r12
   616 M mr r3, r29
       B bctrl
   617 M addi r5, r29, 0x2cc
       B mr r4, r3
   618 M bl 0
       B mr r3, r29
   619 M li r0, 0
       B mr r5, r25
   620 M stw r0, 0x64(r29)
       B bl 0
   621 M b 552
       B li r0, 0
   622 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   623 M li r4, 0
       B b 552
   624 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   625 M bl 0
       B li r4, 0
   626 M mr r25, r3
       B addi r3, r3, 0x28c
   628 M li r28, 1
       B mr r27, r3
   629 M li r4, 1
       B bl 0
   630 M stw r28, 0x14(r25)
       B li r28, 1
   631 M lwz r3, 0x74(r29)
       B li r4, 1
   632 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   633 M bl 0
       B lwz r3, 0x74(r29)
   634 M mr r25, r3
       B addi r3, r3, 0x28c
   636 M stw r28, 0x14(r25)
       B mr r27, r3
   637 M li r4, 3
       B bl 0
   638 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   639 M addi r3, r3, 0x28c
       B li r4, 3
   640 M bl 0
       B lwz r3, 0x74(r29)
   641 M mr r25, r3
       B addi r3, r3, 0x28c
   643 M stw r28, 0x14(r25)
       B mr r27, r3
   644 M li r4, 0x1a
       B bl 0
   645 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   646 M addi r3, r3, 0x28c
       B li r4, 0x1a
   647 M bl 0
       B lwz r3, 0x68(r29)
   648 M bl 0
       B addi r3, r3, 0x28c
   649 M lwz r3, 0x68(r29)
       B bl 0
   650 M li r4, 0x10
       B bl 0
   651 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   652 M bl 0
       B li r4, 0x10
   653 M bl 0
       B addi r3, r3, 0x28c
   654 M lwz r3, 0x74(r29)
       B bl 0
   655 M addi r4, r30, 0x3ef
       B bl 0
   656 M li r5, 1
       B lwz r3, 0x74(r29)
   657 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   658 M lwz r12, 0(r3)
       B li r5, 1
   659 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   660 M mtctr r12
       B lwz r12, 0(r3)
   661 M bctrl
       B lwz r12, 0x3c(r12)
   662 M lwz r5, 0x80(r31)
       B mtctr r12
   663 M mr r25, r3
       B bctrl
   664 M li r4, 0x31
       B lwz r5, 0x80(r30)
   665 M lwz r3, 0(r5)
       B mr r27, r3
   666 M bl 0
       B li r4, 0x31
   667 M mr r5, r3
       B lwz r3, 0(r5)
   668 M mr r3, r29
       B bl 0
   669 M mr r4, r25
       B mr r5, r3
   670 M bl 0
       B mr r3, r29
   671 M lwz r3, 0x74(r29)
       B mr r4, r27
   672 M addi r4, r30, 0x3fd
       B bl 0
   673 M li r5, 1
       B lwz r3, 0x74(r29)
   674 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   675 M lwz r12, 0(r3)
       B li r5, 1
   676 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   677 M mtctr r12
       B lwz r12, 0(r3)
   678 M bctrl
       B lwz r12, 0x3c(r12)
   679 M lwz r5, 0x80(r31)
       B mtctr r12
   680 M mr r25, r3
       B bctrl
   681 M li r4, 0x47
       B lwz r5, 0x80(r30)
   682 M lwz r3, 0(r5)
       B mr r27, r3
   683 M bl 0
       B li r4, 0x47
   684 M mr r5, r3
       B lwz r3, 0(r5)
   685 M mr r3, r29
       B bl 0
   686 M mr r4, r25
       B mr r5, r3
   687 M bl 0
       B mr r3, r29
   688 M li r0, 0x10
       B mr r4, r27
   689 M stw r0, 0x64(r29)
       B bl 0
   690 M b 276
       B li r0, 0x10
   691 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   692 M li r4, 0
       B b 276
   693 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   694 M bl 0
       B li r4, 0
   695 M mr r25, r3
       B addi r3, r3, 0x28c
   697 M li r28, 1
       B mr r27, r3
   698 M li r4, 1
       B bl 0
   699 M stw r28, 0x14(r25)
       B li r28, 1
   700 M lwz r3, 0x74(r29)
       B li r4, 1
   701 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   702 M bl 0
       B lwz r3, 0x74(r29)
   703 M mr r25, r3
       B addi r3, r3, 0x28c
   705 M stw r28, 0x14(r25)
       B mr r27, r3
   706 M li r4, 3
       B bl 0
   707 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   708 M addi r3, r3, 0x28c
       B li r4, 3
   709 M bl 0
       B lwz r3, 0x74(r29)
   710 M mr r25, r3
       B addi r3, r3, 0x28c
   712 M stw r28, 0x14(r25)
       B mr r27, r3
   713 M li r4, 0x1a
       B bl 0
   714 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   715 M addi r3, r3, 0x28c
       B li r4, 0x1a
   716 M bl 0
       B lwz r3, 0x68(r29)
   717 M bl 0
       B addi r3, r3, 0x28c
   718 M lwz r3, 0x68(r29)
       B bl 0
   719 M li r4, 0x10
       B bl 0
   720 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   721 M bl 0
       B li r4, 0x10
   722 M bl 0
       B addi r3, r3, 0x28c
   723 M lwz r3, 0x74(r29)
       B bl 0
   724 M addi r4, r30, 0x3ef
       B bl 0
   725 M li r5, 1
       B lwz r3, 0x74(r29)
   726 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   727 M lwz r12, 0(r3)
       B li r5, 1
   728 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   729 M mtctr r12
       B lwz r12, 0(r3)
   730 M bctrl
       B lwz r12, 0x3c(r12)
   731 M lwz r5, 0x80(r31)
       B mtctr r12
   732 M mr r25, r3
       B bctrl
   733 M li r4, 0x3f
       B lwz r5, 0x80(r30)
   734 M lwz r3, 0(r5)
       B mr r27, r3
   735 M bl 0
       B li r4, 0x3f
   736 M mr r5, r3
       B lwz r3, 0(r5)
   737 M mr r3, r29
       B bl 0
   738 M mr r4, r25
       B mr r5, r3
   739 M bl 0
       B mr r3, r29
   740 M lwz r3, 0x74(r29)
       B mr r4, r27
   741 M addi r4, r30, 0x3fd
       B bl 0
   742 M li r5, 1
       B lwz r3, 0x74(r29)
   743 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   744 M lwz r12, 0(r3)
       B li r5, 1
   745 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   746 M mtctr r12
       B lwz r12, 0(r3)
   747 M bctrl
       B lwz r12, 0x3c(r12)
   748 M lwz r5, 0x80(r31)
       B mtctr r12
   749 M mr r25, r3
       B bctrl
   750 M li r4, 0x48
       B lwz r5, 0x80(r30)
   751 M lwz r3, 0(r5)
       B mr r27, r3
   752 M bl 0
       B li r4, 0x48
   753 M mr r5, r3
       B lwz r3, 0(r5)
   754 M mr r3, r29
       B bl 0
   755 M mr r4, r25
       B mr r5, r3
   756 M bl 0
       B mr r3, r29
   757 M li r0, 0x10
       B mr r4, r27
   758 M stw r0, 0x64(r29)
       B bl 0
   759 M addi r3, r29, 0x4e0
       B li r0, 0x10
   760 M addi r4, r1, 8
       B stw r0, 0x64(r29)
   761 M bl 0
       B addi r3, r29, 0x4e0
   762 M cmpwi r3, 0
       B addi r4, r1, 8
   763 M beq 56
       B bl 0
   764 M lis r4, 0
       B cmpwi r3, 0
   765 M lis r8, 0
       B beq 56
   766 M addi r4, r4, 0
       B lis r3, 0
   767 M lha r7, 8(r1)
       B lis r8, 0
   768 M lwz r3, 0x70(r4)
       B addi r3, r3, 0
   769 M mr r9, r29
       B lha r7, 8(r1)
   770 M lwz r4, 0x28(r4)
       B lwz r4, 0x28(r3)
   771 M addi r8, r8, 0
       B mr r9, r29
   772 M li r5, 0x4c
       B lwz r3, 0x70(r3)
   773 M li r6, 0x4c
       B addi r8, r8, 0
   774 M bl 0
       B li r5, 0x4c
   775 M li r0, 1
       B li r6, 0x4c
   776 M stw r0, 0x4e8(r29)
       B bl 0
   777 M lis r3, 0
       B li r0, 1
   778 M addi r3, r3, 0
       B stw r0, 0x4e8(r29)
   779 M lwz r3, 0x90(r3)
       B lis r3, 0
   780 M lwz r12, 0(r3)
       B addi r3, r3, 0
   781 M lwz r12, 0xc(r12)
       B lwz r3, 0x90(r3)
   782 M mtctr r12
       B lwz r12, 0(r3)
   783 M bctrl
       B lwz r12, 0xc(r12)
   784 M li r3, 0x3c
       B mtctr r12
   785 M bl 0
       B bctrl
   786 M cmpwi r3, 0
       B li r3, 0x3c
   787 M mr r23, r3
       B bl 0
   788 M beq 84
       B cmpwi r3, 0
   789 M lfs f1, 0(0)
       B mr r25, r3
   790 M addi r3, r1, 0xc
       B beq 76
   791 M lfs f31, 0(0)
       B lfs f1, 0(0)
   792 M fmr f2, f1
       B addi r3, r1, 0xc
   793 M lfs f30, 0(0)
       B lfs f31, 0(0)
   794 M fmr f3, f1
       B fmr f2, f1
   795 M lwz r25, 0x24(r29)
       B lfs f30, 0(0)
   796 M bl 0
       B fmr f3, f1
   797 M cmpwi r23, 0
       B lwz r26, 0x24(r29)
   798 M beq 44
       B bl 0
   800 M lwz r5, 0xac(r29)
       B mr r8, r3
   802 M mr r3, r23
       B lwz r5, 0xac(r29)
   803 M mr r4, r25
       B mr r3, r25
   804 M addi r7, r30, 0x406
       B mr r4, r26
   805 M addi r8, r1, 0xc
       B addi r7, r31, 0x406
   808 M mr r23, r3
       B mr r25, r3
   809 M stw r23, 0xa8(r29)
       B stw r25, 0xa8(r29)
```

- local lifetime: board scene reference before layout-file lookup: exact False; insns 820/820; differences 323; objdiff 97.44634

```text
src 0xcd0 base 0xcd0 insns 820/820
diffs 323: [10, 14, 17, 24, 25, 30, 31, 36, 37, 42, 43, 48, 49, 54, 55, 60, 61, 66, 67, 72]
    10 M lis r30, 0
       B lis r31, 0
    14 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M lwz r31, 0xd20(r3)
       B lwz r30, 0xd20(r3)
    24 M mr r5, r31
       B mr r5, r30
    25 M addi r7, r30, 0x72
       B addi r7, r31, 0x72
    30 M addi r4, r30, 0x84
       B addi r4, r31, 0x84
    31 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
    36 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    37 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    42 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    43 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    48 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    49 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    54 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    55 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    60 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    61 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    66 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    67 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    72 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    73 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    78 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    79 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    84 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    85 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    90 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    91 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    96 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
    97 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   102 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   103 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   108 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   109 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   114 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   115 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   120 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   121 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   126 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   127 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   132 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   133 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   138 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   139 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   144 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   145 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   150 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   151 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   156 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   157 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   162 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   163 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   168 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   169 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   174 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   175 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   180 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   181 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   186 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   187 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   192 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   193 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   198 M addi r4, r30, 0x17e
       B addi r4, r31, 0x17e
   199 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   204 M addi r4, r30, 0x1a9
       B addi r4, r31, 0x1a9
   205 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   210 M addi r4, r30, 0x1cc
       B addi r4, r31, 0x1cc
   211 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
   252 M addi r27, r30, 0x44
       B addi r27, r31, 0x44
   271 M addi r4, r30, 0x1e8
       B addi r4, r31, 0x1e8
   281 M mr r23, r3
       B mr r27, r3
   289 M mr r4, r23
       B mr r4, r27
   292 M addi r4, r30, 0x1f5
       B addi r4, r31, 0x1f5
   300 M mr r25, r3
       B mr r27, r3
   306 M mr r4, r25
       B mr r4, r27
   309 M addi r4, r30, 0x202
       B addi r4, r31, 0x202
   317 M mr r25, r3
       B mr r27, r3
   323 M mr r4, r25
       B mr r4, r27
   326 M addi r4, r30, 0x20f
       B addi r4, r31, 0x20f
   334 M mr r25, r3
       B mr r27, r3
   340 M mr r4, r25
       B mr r4, r27
   343 M addi r4, r30, 0x21d
       B addi r4, r31, 0x21d
   355 M addi r4, r30, 0x22b
       B addi r4, r31, 0x22b
   367 M addi r4, r30, 0xf5
       B addi r4, r31, 0xf5
   384 M mr r5, r31
       B mr r5, r30
   385 M addi r7, r30, 0x235
       B addi r7, r31, 0x235
   390 M addi r4, r30, 0x247
       B addi r4, r31, 0x247
   391 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   396 M addi r4, r30, 0x274
       B addi r4, r31, 0x274
   397 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   402 M addi r4, r30, 0x2a4
       B addi r4, r31, 0x2a4
   403 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   408 M addi r4, r30, 0x2cc
       B addi r4, r31, 0x2cc
   409 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   414 M addi r4, r30, 0x2f2
       B addi r4, r31, 0x2f2
   420 M addi r4, r30, 0x30f
       B addi r4, r31, 0x30f
   421 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   426 M addi r4, r30, 0x332
       B addi r4, r31, 0x332
   427 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   432 M addi r4, r30, 0x351
       B addi r4, r31, 0x351
   433 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   438 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   444 M addi r4, r30, 0x38d
       B addi r4, r31, 0x38d
   445 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   505 M mr r5, r31
       B mr r5, r30
   506 M addi r7, r30, 0x3a9
       B addi r7, r31, 0x3a9
   510 M addi r4, r30, 0x3b9
       B addi r4, r31, 0x3b9
   511 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   516 M addi r4, r30, 0x3da
       B addi r4, r31, 0x3da
   517 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   536 M lis r31, 0
       B lis r30, 0
   538 M addi r31, r31, 0
       B addi r30, r30, 0
   541 M lwz r3, 0x64(r31)
       B lwz r3, 0x64(r30)
   547 M beq 300
       B beq 308
   551 M b 832
       B b 840
   553 M bge 824
       B bge 832
   554 M b 548
       B b 556
   591 M mr r25, r3
       B mr r27, r3
   594 M addi r4, r30, 0x22b
       B addi r25, r29, 0x2b4
   595 M stw r0, 0x14(r25)
       B stw r0, 0x14(r27)
   596 M li r5, 1
       B addi r4, r31, 0x22b
   597 M lwz r3, 0x68(r29)
       B li r5, 1
   598 M lwz r3, 0x14(r3)
       B lwz r3, 0x68(r29)
   599 M lwz r12, 0(r3)
       B lwz r3, 0x14(r3)
   600 M lwz r12, 0x3c(r12)
       B lwz r12, 0(r3)
   601 M mtctr r12
       B lwz r12, 0x3c(r12)
   602 M bctrl
       B mtctr r12
   603 M mr r4, r3
       B bctrl
   604 M mr r3, r29
       B mr r4, r3
   605 M addi r5, r29, 0x2b4
       B mr r3, r29
   606 M bl 0
       B mr r5, r25
   607 M lwz r3, 0x68(r29)
       B bl 0
   608 M addi r4, r30, 0xf5
       B lwz r3, 0x68(r29)
   609 M li r5, 1
       B addi r25, r29, 0x2cc
   610 M lwz r3, 0x14(r3)
       B addi r4, r31, 0xf5
   611 M lwz r12, 0(r3)
       B li r5, 1
   612 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   613 M mtctr r12
       B lwz r12, 0(r3)
   614 M bctrl
       B lwz r12, 0x3c(r12)
   615 M mr r4, r3
       B mtctr r12
   616 M mr r3, r29
       B bctrl
   617 M addi r5, r29, 0x2cc
       B mr r4, r3
   618 M bl 0
       B mr r3, r29
   619 M li r0, 0
       B mr r5, r25
   620 M stw r0, 0x64(r29)
       B bl 0
   621 M b 552
       B li r0, 0
   622 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   623 M li r4, 0
       B b 552
   624 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   625 M bl 0
       B li r4, 0
   626 M mr r25, r3
       B addi r3, r3, 0x28c
   628 M li r28, 1
       B mr r27, r3
   629 M li r4, 1
       B bl 0
   630 M stw r28, 0x14(r25)
       B li r28, 1
   631 M lwz r3, 0x74(r29)
       B li r4, 1
   632 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   633 M bl 0
       B lwz r3, 0x74(r29)
   634 M mr r25, r3
       B addi r3, r3, 0x28c
   636 M stw r28, 0x14(r25)
       B mr r27, r3
   637 M li r4, 3
       B bl 0
   638 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   639 M addi r3, r3, 0x28c
       B li r4, 3
   640 M bl 0
       B lwz r3, 0x74(r29)
   641 M mr r25, r3
       B addi r3, r3, 0x28c
   643 M stw r28, 0x14(r25)
       B mr r27, r3
   644 M li r4, 0x1a
       B bl 0
   645 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   646 M addi r3, r3, 0x28c
       B li r4, 0x1a
   647 M bl 0
       B lwz r3, 0x68(r29)
   648 M bl 0
       B addi r3, r3, 0x28c
   649 M lwz r3, 0x68(r29)
       B bl 0
   650 M li r4, 0x10
       B bl 0
   651 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   652 M bl 0
       B li r4, 0x10
   653 M bl 0
       B addi r3, r3, 0x28c
   654 M lwz r3, 0x74(r29)
       B bl 0
   655 M addi r4, r30, 0x3ef
       B bl 0
   656 M li r5, 1
       B lwz r3, 0x74(r29)
   657 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   658 M lwz r12, 0(r3)
       B li r5, 1
   659 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   660 M mtctr r12
       B lwz r12, 0(r3)
   661 M bctrl
       B lwz r12, 0x3c(r12)
   662 M lwz r5, 0x80(r31)
       B mtctr r12
   663 M mr r25, r3
       B bctrl
   664 M li r4, 0x31
       B lwz r5, 0x80(r30)
   665 M lwz r3, 0(r5)
       B mr r27, r3
   666 M bl 0
       B li r4, 0x31
   667 M mr r5, r3
       B lwz r3, 0(r5)
   668 M mr r3, r29
       B bl 0
   669 M mr r4, r25
       B mr r5, r3
   670 M bl 0
       B mr r3, r29
   671 M lwz r3, 0x74(r29)
       B mr r4, r27
   672 M addi r4, r30, 0x3fd
       B bl 0
   673 M li r5, 1
       B lwz r3, 0x74(r29)
   674 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   675 M lwz r12, 0(r3)
       B li r5, 1
   676 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   677 M mtctr r12
       B lwz r12, 0(r3)
   678 M bctrl
       B lwz r12, 0x3c(r12)
   679 M lwz r5, 0x80(r31)
       B mtctr r12
   680 M mr r25, r3
       B bctrl
   681 M li r4, 0x47
       B lwz r5, 0x80(r30)
   682 M lwz r3, 0(r5)
       B mr r27, r3
   683 M bl 0
       B li r4, 0x47
   684 M mr r5, r3
       B lwz r3, 0(r5)
   685 M mr r3, r29
       B bl 0
   686 M mr r4, r25
       B mr r5, r3
   687 M bl 0
       B mr r3, r29
   688 M li r0, 0x10
       B mr r4, r27
   689 M stw r0, 0x64(r29)
       B bl 0
   690 M b 276
       B li r0, 0x10
   691 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   692 M li r4, 0
       B b 276
   693 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   694 M bl 0
       B li r4, 0
   695 M mr r25, r3
       B addi r3, r3, 0x28c
   697 M li r28, 1
       B mr r27, r3
   698 M li r4, 1
       B bl 0
   699 M stw r28, 0x14(r25)
       B li r28, 1
   700 M lwz r3, 0x74(r29)
       B li r4, 1
   701 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   702 M bl 0
       B lwz r3, 0x74(r29)
   703 M mr r25, r3
       B addi r3, r3, 0x28c
   705 M stw r28, 0x14(r25)
       B mr r27, r3
   706 M li r4, 3
       B bl 0
   707 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   708 M addi r3, r3, 0x28c
       B li r4, 3
   709 M bl 0
       B lwz r3, 0x74(r29)
   710 M mr r25, r3
       B addi r3, r3, 0x28c
   712 M stw r28, 0x14(r25)
       B mr r27, r3
   713 M li r4, 0x1a
       B bl 0
   714 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   715 M addi r3, r3, 0x28c
       B li r4, 0x1a
   716 M bl 0
       B lwz r3, 0x68(r29)
   717 M bl 0
       B addi r3, r3, 0x28c
   718 M lwz r3, 0x68(r29)
       B bl 0
   719 M li r4, 0x10
       B bl 0
   720 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   721 M bl 0
       B li r4, 0x10
   722 M bl 0
       B addi r3, r3, 0x28c
   723 M lwz r3, 0x74(r29)
       B bl 0
   724 M addi r4, r30, 0x3ef
       B bl 0
   725 M li r5, 1
       B lwz r3, 0x74(r29)
   726 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   727 M lwz r12, 0(r3)
       B li r5, 1
   728 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   729 M mtctr r12
       B lwz r12, 0(r3)
   730 M bctrl
       B lwz r12, 0x3c(r12)
   731 M lwz r5, 0x80(r31)
       B mtctr r12
   732 M mr r25, r3
       B bctrl
   733 M li r4, 0x3f
       B lwz r5, 0x80(r30)
   734 M lwz r3, 0(r5)
       B mr r27, r3
   735 M bl 0
       B li r4, 0x3f
   736 M mr r5, r3
       B lwz r3, 0(r5)
   737 M mr r3, r29
       B bl 0
   738 M mr r4, r25
       B mr r5, r3
   739 M bl 0
       B mr r3, r29
   740 M lwz r3, 0x74(r29)
       B mr r4, r27
   741 M addi r4, r30, 0x3fd
       B bl 0
   742 M li r5, 1
       B lwz r3, 0x74(r29)
   743 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   744 M lwz r12, 0(r3)
       B li r5, 1
   745 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   746 M mtctr r12
       B lwz r12, 0(r3)
   747 M bctrl
       B lwz r12, 0x3c(r12)
   748 M lwz r5, 0x80(r31)
       B mtctr r12
   749 M mr r25, r3
       B bctrl
   750 M li r4, 0x48
       B lwz r5, 0x80(r30)
   751 M lwz r3, 0(r5)
       B mr r27, r3
   752 M bl 0
       B li r4, 0x48
   753 M mr r5, r3
       B lwz r3, 0(r5)
   754 M mr r3, r29
       B bl 0
   755 M mr r4, r25
       B mr r5, r3
   756 M bl 0
       B mr r3, r29
   757 M li r0, 0x10
       B mr r4, r27
   758 M stw r0, 0x64(r29)
       B bl 0
   759 M addi r3, r29, 0x4e0
       B li r0, 0x10
   760 M addi r4, r1, 8
       B stw r0, 0x64(r29)
   761 M bl 0
       B addi r3, r29, 0x4e0
   762 M cmpwi r3, 0
       B addi r4, r1, 8
   763 M beq 56
       B bl 0
   764 M lis r4, 0
       B cmpwi r3, 0
   765 M lis r8, 0
       B beq 56
   766 M addi r4, r4, 0
       B lis r3, 0
   767 M lha r7, 8(r1)
       B lis r8, 0
   768 M lwz r3, 0x70(r4)
       B addi r3, r3, 0
   769 M mr r9, r29
       B lha r7, 8(r1)
   770 M lwz r4, 0x28(r4)
       B lwz r4, 0x28(r3)
   771 M addi r8, r8, 0
       B mr r9, r29
   772 M li r5, 0x4c
       B lwz r3, 0x70(r3)
   773 M li r6, 0x4c
       B addi r8, r8, 0
   774 M bl 0
       B li r5, 0x4c
   775 M li r0, 1
       B li r6, 0x4c
   776 M stw r0, 0x4e8(r29)
       B bl 0
   777 M lis r3, 0
       B li r0, 1
   778 M addi r3, r3, 0
       B stw r0, 0x4e8(r29)
   779 M lwz r3, 0x90(r3)
       B lis r3, 0
   780 M lwz r12, 0(r3)
       B addi r3, r3, 0
   781 M lwz r12, 0xc(r12)
       B lwz r3, 0x90(r3)
   782 M mtctr r12
       B lwz r12, 0(r3)
   783 M bctrl
       B lwz r12, 0xc(r12)
   784 M li r3, 0x3c
       B mtctr r12
   785 M bl 0
       B bctrl
   786 M cmpwi r3, 0
       B li r3, 0x3c
   787 M mr r23, r3
       B bl 0
   788 M beq 84
       B cmpwi r3, 0
   789 M lfs f1, 0(0)
       B mr r25, r3
   790 M addi r3, r1, 0xc
       B beq 76
   791 M lfs f31, 0(0)
       B lfs f1, 0(0)
   792 M fmr f2, f1
       B addi r3, r1, 0xc
   793 M lfs f30, 0(0)
       B lfs f31, 0(0)
   794 M fmr f3, f1
       B fmr f2, f1
   795 M lwz r25, 0x24(r29)
       B lfs f30, 0(0)
   796 M bl 0
       B fmr f3, f1
   797 M cmpwi r23, 0
       B lwz r26, 0x24(r29)
   798 M beq 44
       B bl 0
   800 M lwz r5, 0xac(r29)
       B mr r8, r3
   802 M mr r3, r23
       B lwz r5, 0xac(r29)
   803 M mr r4, r25
       B mr r3, r25
   804 M addi r7, r30, 0x406
       B mr r4, r26
   805 M addi r8, r1, 0xc
       B addi r7, r31, 0x406
   808 M mr r23, r3
       B mr r25, r3
   809 M stw r23, 0xa8(r29)
       B stw r25, 0xa8(r29)
```

## src/scene/address/iplAddressEdit: get_friendinfo__Q33ipl5scene11AddressEditFv

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline boundary: mutable String name accessor in textbox argument: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline boundary: mutable display-text accessor in textbox argument: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline boundaries: both mutable String accessors before pane lookup evaluation: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

## src/scene/address/iplAddressEdit: start_left_event__Q33ipl5scene11AddressEditFPCc

```text
src 0x184 base 0x180 insns 97/96
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x10(r1)
  B    0 stwu r1, -0x20(r1)
--- replace mine 2:4 base 2:8
  M    2 stw r0, 0x14(r1)
  M    3 stw r31, 0xc(r1)
  B    2 stw r0, 0x24(r1)
  B    3 addi r11, r1, 0x20
  B    4 bl 0
  B    5 mr r30, r3
  B    6 bl 0
  B    7 lwz r0, 0x64(r30)
--- delete mine 5:8 base 9:9
  M    5 stw r30, 8(r1)
  M    6 bl 0
  M    7 lwz r0, 0x64(r31)
--- replace mine 9:11 base 10:12
  M    9 beq 280
  M   10 bge 324
  B   10 beq 268
  B   11 bge 316
--- replace mine 13:14 base 14:15
  M   13 b 312
  B   14 b 304
--- replace mine 15:17 base 16:18
  M   15 beq 132
  M   16 bge 300
  B   16 beq 136
  B   17 bge 292
--- replace mine 18:23 base 19:25
  M   18 beq 12
  M   19 bge 160
  M   20 b 284
  M   21 lwz r0, 0xa4(r31)
  M   22 lwz r4, 0x4ec(r31)
  B   19 beq 16
  B   20 bge 148
  B   21 b 276
  B   22 b 272
  B   23 lwz r0, 0xa4(r30)
  B   24 lwz r4, 0x4ec(r30)
--- replace mine 27:28 base 29:30
  M   27 bne 256
  B   29 bne 244
--- replace mine 29:31 base 31:33
  M   29 add r30, r31, r0
  M   30 lwz r0, 0x90(r30)
  B   31 add r29, r30, r0
  B   32 lwz r0, 0x90(r29)
--- replace mine 33:35 base 35:37
  M   33 lwz r5, 0x68(r31)
  M   34 addi r0, r3, 0xb
  B   35 lwz r3, 0x68(r30)
  B   36 addi r0, r31, 0xb
--- replace mine 36:37 base 38:39
  M   36 addi r3, r5, 0x28c
  B   38 addi r3, r3, 0x28c
--- replace mine 38:39 base 40:41
  M   38 mr r31, r3
  B   40 mr r30, r3
--- replace mine 41:43 base 43:45
  M   41 stw r0, 0x14(r31)
  M   42 lwz r3, 0x90(r30)
  B   43 stw r0, 0x14(r30)
  B   44 lwz r3, 0x90(r29)
--- replace mine 44:45 base 46:47
  M   44 ble 188
  B   46 ble 176
--- replace mine 46:48 base 48:50
  M   46 stw r0, 0x90(r30)
  M   47 b 176
  B   48 stw r0, 0x90(r29)
  B   49 b 164
--- replace mine 49:51 base 51:53
  M   49 add r30, r31, r0
  M   50 lwz r0, 0x90(r30)
  B   51 add r3, r30, r0
  B   52 lwz r0, 0x90(r3)
--- replace mine 53:54 base 55:56
  M   53 lwz r3, 0xa8(r31)
  B   55 lwz r3, 0xa8(r30)
--- replace mine 55:62 base 57:60
  M   55 lwz r3, 0x90(r30)
  M   56 addi r0, r3, -1
  M   57 stw r0, 0x90(r30)
  M   58 b 132
  M   59 slwi r0, r3, 2
  M   60 add r30, r31, r0
  M   61 lwz r0, 0x90(r30)
  B   57 slwi r0, r31, 2
  B   58 add r29, r30, r0
  B   59 lwz r0, 0x90(r29)
--- replace mine 64:66 base 62:64
  M   64 lwz r5, 0x68(r31)
  M   65 addi r0, r3, 0xb
  B   62 lwz r3, 0x68(r30)
  B   63 addi r0, r31, 0xb
--- replace mine 67:68 base 65:66
  M   67 addi r3, r5, 0x28c
  B   65 addi r3, r3, 0x28c
--- replace mine 69:70 base 67:68
  M   69 mr r31, r3
  B   67 mr r30, r3
--- replace mine 72:74 base 70:72
  M   72 stw r0, 0x14(r31)
  M   73 lwz r3, 0x90(r30)
  B   70 stw r0, 0x14(r30)
  B   71 lwz r3, 0x90(r29)
--- replace mine 75:76 base 73:74
  M   75 ble 64
  B   73 ble 68
--- replace mine 77:79 base 75:77
  M   77 stw r0, 0x90(r30)
  M   78 b 52
  B   75 stw r0, 0x90(r29)
  B   76 b 56
--- replace mine 80:81 base 78:80
  M   80 bne 44
  B   78 beq 8
  B   79 b 44
--- replace mine 82:84 base 81:83
  M   82 add r30, r31, r0
  M   83 lwz r0, 0x90(r30)
  B   81 add r31, r30, r0
  B   82 lwz r0, 0x90(r31)
--- replace mine 86:87 base 85:86
  M   86 lwz r3, 0xa8(r31)
  B   85 lwz r3, 0xa8(r30)
--- replace mine 88:89 base 87:88
  M   88 lwz r3, 0x90(r30)
  B   87 lwz r3, 0x90(r31)
--- replace mine 90:94 base 89:93
  M   90 stw r0, 0x90(r30)
  M   91 lwz r0, 0x14(r1)
  M   92 lwz r31, 0xc(r1)
  M   93 lwz r30, 8(r1)
  B   89 stw r0, 0x90(r31)
  B   90 addi r11, r1, 0x20
  B   91 bl 0
  B   92 lwz r0, 0x24(r1)
--- replace mine 95:96 base 94:95
  M   95 addi r1, r1, 0x10
  B   94 addi r1, r1, 0x20
```

- branch structure and local type: nested button fallthrough with signed-long selector: exact False; insns 95/96; differences None; objdiff 98.958336

```text
src 0x17c base 0x180 insns 95/96
--- replace mine 10:12 base 10:12
  M   10 beq 264
  M   11 bge 312
  B   10 beq 268
  B   11 bge 316
--- replace mine 14:15 base 14:15
  M   14 b 300
  B   14 b 304
--- replace mine 16:18 base 16:18
  M   16 beq 132
  M   17 bge 288
  B   16 beq 136
  B   17 bge 292
--- replace mine 19:21 base 19:22
  M   19 beq 12
  M   20 bge 144
  B   19 beq 16
  B   20 bge 148
  B   21 b 276
```

- nested fallthrough with explicit status temporary and base animation controllers: exact False; insns 95/96; differences None; objdiff 98.958336

```text
src 0x17c base 0x180 insns 95/96
--- replace mine 10:12 base 10:12
  M   10 beq 264
  M   11 bge 312
  B   10 beq 268
  B   11 bge 316
--- replace mine 14:15 base 14:15
  M   14 b 300
  B   14 b 304
--- replace mine 16:18 base 16:18
  M   16 beq 132
  M   17 bge 288
  B   16 beq 136
  B   17 bge 292
--- replace mine 19:21 base 19:22
  M   19 beq 12
  M   20 bge 144
  B   19 beq 16
  B   20 bge 148
  B   21 b 276
```

- nested fallthrough and local temporary: retain state before dispatch: exact False; insns 95/96; differences None; objdiff 98.958336

```text
src 0x17c base 0x180 insns 95/96
--- replace mine 10:12 base 10:12
  M   10 beq 264
  M   11 bge 312
  B   10 beq 268
  B   11 bge 316
--- replace mine 14:15 base 14:15
  M   14 b 300
  B   14 b 304
--- replace mine 16:18 base 16:18
  M   16 beq 132
  M   17 bge 288
  B   16 beq 136
  B   17 bge 292
--- replace mine 19:21 base 19:22
  M   19 beq 12
  M   20 bge 144
  B   19 beq 16
  B   20 bge 148
  B   21 b 276
```

## src/scene/address/iplAddressEdit: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x178 base 0x178 insns 94/94
diffs 5: [20, 29, 41, 82, 86]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
    82 M mr r30, r3
       B mr r29, r3
    86 M stw r3, 0x14(r30)
       B stw r3, 0x14(r29)
```

- distinct completion phases with base animation controller: exact False; insns 94/94; differences 13; objdiff 89.94681

```text
src 0x178 base 0x178 insns 94/94
diffs 13: [37, 38, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51]
    37 M addi r0, r5, -1
       B addi r5, r5, -1
    38 M cntlzw r0, r0
       B addic r0, r5, -1
    40 M srwi r30, r0, 5
       B subfe r0, r0, r5
    41 M bl 0
       B and r5, r29, r0
    42 M cntlzw r0, r30
       B addic r0, r5, -1
    43 M lwz r3, 0x14(r3)
       B subfe r30, r0, r5
    44 M srwi r0, r0, 5
       B bl 0
    45 M and r4, r29, r0
       B lwz r3, 0x14(r3)
    47 M addic r0, r4, -1
       B addic r0, r3, -1
    48 M subfe r4, r0, r4
       B subfe r0, r0, r3
    49 M addic r0, r3, -1
       B and r3, r30, r0
    50 M subfe r0, r0, r3
       B addic r0, r3, -1
    51 M and. r0, r4, r0
       B subfe. r0, r0, r3
```

- distinct BOOL completion phases and base controller: exact False; insns 92/94; differences None; objdiff 89.94681

```text
src 0x170 base 0x178 insns 92/94
--- replace mine 37:39 base 37:39
  M   37 addi r0, r5, -1
  M   38 cntlzw r0, r0
  B   37 addi r5, r5, -1
  B   38 addic r0, r5, -1
--- replace mine 40:41 base 40:44
  M   40 srwi r30, r0, 5
  B   40 subfe r0, r0, r5
  B   41 and r5, r29, r0
  B   42 addic r0, r5, -1
  B   43 subfe r30, r0, r5
--- delete mine 43:45 base 46:46
  M   43 cntlzw r0, r30
  M   44 srwi r4, r0, 5
--- delete mine 47:48 base 48:48
  M   47 and r4, r29, r4
--- replace mine 49:50 base 49:52
  M   49 and. r0, r4, r0
  B   49 and r3, r30, r0
  B   50 addic r0, r3, -1
  B   51 subfe. r0, r0, r3
```

- distinct completion phases with typed text box: exact False; insns 94/94; differences 13; objdiff 89.94681

```text
src 0x178 base 0x178 insns 94/94
diffs 13: [37, 38, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51]
    37 M addi r0, r5, -1
       B addi r5, r5, -1
    38 M cntlzw r0, r0
       B addic r0, r5, -1
    40 M srwi r30, r0, 5
       B subfe r0, r0, r5
    41 M bl 0
       B and r5, r29, r0
    42 M cntlzw r0, r30
       B addic r0, r5, -1
    43 M lwz r3, 0x14(r3)
       B subfe r30, r0, r5
    44 M srwi r0, r0, 5
       B bl 0
    45 M and r4, r29, r0
       B lwz r3, 0x14(r3)
    47 M addic r0, r4, -1
       B addic r0, r3, -1
    48 M subfe r4, r0, r4
       B subfe r0, r0, r3
    49 M addic r0, r3, -1
       B and r3, r30, r0
    50 M subfe r0, r0, r3
       B addic r0, r3, -1
    51 M and. r0, r4, r0
       B subfe. r0, r0, r3
```

## src/scene/address/iplAddressEdit: stt_add_code_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- distinct pane locals combined with base animator pointer: exact False; insns 111/111; differences 6; objdiff 99.72973

```text
src 0x1bc base 0x1bc insns 111/111
diffs 6: [74, 77, 85, 87, 93, 95]
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- distinct pane locals and separate fade controller: exact False; insns 111/111; differences 4; objdiff 99.81982

```text
src 0x1bc base 0x1bc insns 111/111
diffs 4: [85, 87, 93, 95]
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- distinct pane locals and BOOL name-present temporary: exact False; insns 111/111; differences 6; objdiff 99.72973

```text
src 0x1bc base 0x1bc insns 111/111
diffs 6: [74, 77, 85, 87, 93, 95]
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

## src/scene/address/iplAddress: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface

```text
src 0x378 base 0x37c insns 222/223
--- replace mine 12:13 base 12:13
  M   12 beq 816
  B   12 beq 820
--- replace mine 19:20 base 19:20
  M   19 blt 788
  B   19 blt 792
--- replace mine 22:23 base 22:24
  M   22 bne 776
  B   22 beq 8
  B   23 b 776
--- replace mine 116:118 base 117:119
  M  116 lwz r29, 0x104(r3)
  M  117 cmpwi r29, 0
  B  117 lwz r26, 0x104(r3)
  B  118 cmpwi r26, 0
--- replace mine 129:130 base 130:131
  M  129 mr r26, r3
  B  130 mr r29, r3
--- replace mine 132:133 base 133:134
  M  132 addi r4, r29, 0x14
  B  133 addi r4, r26, 0x14
--- replace mine 143:144 base 144:145
  M  143 lwz r4, 0(r29)
  B  144 lwz r4, 0(r26)
--- replace mine 154:156 base 155:157
  M  154 lwz r12, 0(r26)
  M  155 mr r3, r26
  B  155 lwz r12, 0(r29)
  B  156 mr r3, r29
```

- branch direction: switch normal-state scope contains drag operation: exact False; insns 222/223; differences None; objdiff 99.34978

```text
src 0x378 base 0x37c insns 222/223
--- replace mine 12:13 base 12:13
  M   12 beq 816
  B   12 beq 820
--- replace mine 19:20 base 19:20
  M   19 blt 788
  B   19 blt 792
--- replace mine 23:24 base 23:24
  M   23 b 772
  B   23 b 776
--- replace mine 26:27 base 26:28
  M   26 bne 760
  B   26 beq 8
  B   27 b 760
--- replace mine 116:118 base 117:119
  M  116 lwz r29, 0x104(r3)
  M  117 cmpwi r29, 0
  B  117 lwz r26, 0x104(r3)
  B  118 cmpwi r26, 0
--- replace mine 129:130 base 130:131
  M  129 mr r26, r3
  B  130 mr r29, r3
--- replace mine 132:133 base 133:134
  M  132 addi r4, r29, 0x14
  B  133 addi r4, r26, 0x14
--- replace mine 143:144 base 144:145
  M  143 lwz r4, 0(r29)
  B  144 lwz r4, 0(r26)
--- replace mine 154:156 base 155:157
  M  154 lwz r12, 0(r26)
  M  155 mr r3, r26
  B  155 lwz r12, 0(r29)
  B  156 mr r3, r29
```

- local type: signed-long button selector combined with state switch: exact False; insns 222/223; differences None; objdiff 99.34978

```text
src 0x378 base 0x37c insns 222/223
--- replace mine 12:13 base 12:13
  M   12 beq 816
  B   12 beq 820
--- replace mine 19:20 base 19:20
  M   19 blt 788
  B   19 blt 792
--- replace mine 23:24 base 23:24
  M   23 b 772
  B   23 b 776
--- replace mine 26:27 base 26:28
  M   26 bne 760
  B   26 beq 8
  B   27 b 760
--- replace mine 116:118 base 117:119
  M  116 lwz r29, 0x104(r3)
  M  117 cmpwi r29, 0
  B  117 lwz r26, 0x104(r3)
  B  118 cmpwi r26, 0
--- replace mine 129:130 base 130:131
  M  129 mr r26, r3
  B  130 mr r29, r3
--- replace mine 132:133 base 133:134
  M  132 addi r4, r29, 0x14
  B  133 addi r4, r26, 0x14
--- replace mine 143:144 base 144:145
  M  143 lwz r4, 0(r29)
  B  144 lwz r4, 0(r26)
--- replace mine 154:156 base 155:157
  M  154 lwz r12, 0(r26)
  M  155 mr r3, r26
  B  155 lwz r12, 0(r29)
  B  156 mr r3, r29
```

- local lifetime: Mii object reference before nullable icon lookup: exact False; insns 222/223; differences None; objdiff 98.139015

```text
src 0x378 base 0x37c insns 222/223
--- replace mine 12:13 base 12:13
  M   12 beq 816
  B   12 beq 820
--- replace mine 19:20 base 19:20
  M   19 blt 788
  B   19 blt 792
--- replace mine 23:24 base 23:24
  M   23 b 772
  B   23 b 776
--- replace mine 26:27 base 26:28
  M   26 bne 760
  B   26 beq 8
  B   27 b 760
--- replace mine 114:120 base 115:120
  M  114 mulli r0, r31, 0x28
  M  115 add r3, r28, r0
  M  116 lwz r29, 0x104(r3)
  M  117 addi r27, r3, 0xe4
  M  118 cmpwi r29, 0
  M  119 beq 188
  B  115 mulli r27, r31, 0x28
  B  116 add r3, r28, r27
  B  117 lwz r26, 0x104(r3)
  B  118 cmpwi r26, 0
  B  119 beq 192
--- replace mine 130:131 base 130:131
  M  130 mr r26, r3
  B  130 mr r29, r3
--- replace mine 133:134 base 133:134
  M  133 addi r4, r29, 0x14
  B  133 addi r4, r26, 0x14
--- replace mine 144:145 base 144:145
  M  144 lwz r4, 0(r29)
  B  144 lwz r4, 0(r26)
--- replace mine 155:157 base 155:157
  M  155 lwz r12, 0(r26)
  M  156 mr r3, r26
  B  155 lwz r12, 0(r29)
  B  156 mr r3, r29
--- replace mine 163:164 base 163:165
  M  163 mr r3, r27
  B  163 add r3, r28, r27
  B  164 addi r3, r3, 0xe4
```

## src/scene/address/iplAddress: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err

```text
src 0x144 base 0x140 insns 81/80
--- delete mine 26:27 base 26:26
  M   26 li r30, 0x190
```

- local type: initialized message selector held as int: exact False; insns 81/80; differences None; objdiff 98.6

```text
src 0x144 base 0x140 insns 81/80
--- delete mine 26:27 base 26:26
  M   26 li r30, 0x190
```

- stack construction: error-code array value initialization: exact False; insns 86/80; differences None; objdiff 88.3625

```text
src 0x158 base 0x140 insns 86/80
--- replace mine 5:8 base 5:8
  M    5 mr r28, r4
  M    6 mr r29, r5
  M    7 mr r30, r6
  B    5 mr r27, r4
  B    6 mr r28, r5
  B    7 mr r29, r6
--- replace mine 9:10 base 9:10
  M    9 mr r3, r28
  B    9 mr r3, r27
--- replace mine 12:13 base 12:13
  M   12 lis r3, 0
  B   12 lis r31, 0
--- replace mine 14:16 base 14:16
  M   14 addi r3, r3, 0
  M   15 lwz r3, 0x80(r3)
  B   14 addi r31, r31, 0
  B   15 lwz r3, 0x80(r31)
--- replace mine 18:20 base 18:20
  M   18 mr r31, r3
  M   19 mr r3, r28
  B   18 mr r30, r3
  B   19 mr r3, r27
--- replace mine 21:24 base 21:24
  M   21 subf r5, r3, r29
  M   22 mr r3, r28
  M   23 mr r4, r31
  B   21 subf r5, r3, r28
  B   22 mr r3, r27
  B   23 mr r4, r30
--- replace mine 25:36 base 25:30
  M   25 li r0, 0x10
  M   26 addi r4, r1, 6
  M   27 li r31, 0x190
  M   28 li r3, 0
  M   29 mtctr r0
  M   30 sth r3, 2(r4)
  M   31 sthu r3, 4(r4)
  M   32 bdnz -8
  M   33 lis r3, 0
  M   34 addi r3, r3, 0
  M   35 lbz r0, 0x2bc(r3)
  B   25 addi r3, r1, 8
  B   26 li r4, 0
  B   27 li r5, 0x40
  B   28 bl 0
  B   29 lbz r0, 0x2bc(r31)
--- replace mine 40:41 base 34:35
  M   40 lwz r3, 0x8c(r3)
  B   34 lwz r3, 0x8c(r31)
--- replace mine 49:50 base 43:44
  M   49 mr r3, r28
  B   43 mr r3, r27
--- replace mine 51:53 base 45:47
  M   51 subf r5, r3, r29
  M   52 mr r3, r28
  B   45 subf r5, r3, r28
  B   46 mr r3, r27
--- replace mine 55:56 base 49:50
  M   55 cmpwi r30, -0x1f
  B   49 cmpwi r29, -0x1f
--- replace mine 58:59 base 52:53
  M   58 cmpwi r30, -0x20
  B   52 cmpwi r29, -0x20
--- replace mine 61:62 base 55:56
  M   61 cmpwi r30, -6
  B   55 cmpwi r29, -6
--- replace mine 64:65 base 58:59
  M   64 li r31, 0x19a
  B   58 li r30, 0x19a
--- replace mine 66:67 base 60:61
  M   66 li r31, 0x1c5
  B   60 li r30, 0x1c5
--- replace mine 68:69 base 62:63
  M   68 mr r4, r31
  B   62 mr r4, r30
--- replace mine 73:75 base 67:69
  M   73 mr r31, r3
  M   74 mr r3, r28
  B   67 mr r30, r3
  B   68 mr r3, r27
--- replace mine 76:79 base 70:73
  M   76 subf r5, r3, r29
  M   77 mr r3, r28
  M   78 mr r4, r31
  B   70 subf r5, r3, r28
  B   71 mr r3, r27
  B   72 mr r4, r30
```

- condition order: initialized default arm in server-first switch: exact False; insns 81/80; differences None; objdiff 95.7875

```text
src 0x144 base 0x140 insns 81/80
--- replace mine 50:51 base 50:51
  M   50 beq 40
  B   50 beq 32
--- replace mine 53:55 base 53:55
  M   53 bge 20
  M   54 b 32
  B   53 bge 28
  B   54 b 28
--- replace mine 56:59 base 56:57
  M   56 beq 8
  M   57 b 20
  M   58 li r4, 0x1c5
  B   56 beq 16
--- replace mine 60:61 base 58:59
  M   60 li r4, 0x19a
  B   58 li r30, 0x19a
--- replace mine 62:63 base 60:61
  M   62 li r4, 0x190
  B   60 li r30, 0x1c5
--- insert mine 64:64 base 62:63
  B   62 mr r4, r30
```

## src/scene/address/iplAddress: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface

```text
src 0x43c base 0x438 insns 271/270
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x24(r1)
  M    3 addi r11, r1, 0x20
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 5:6 base 5:6
  M    5 mr r30, r3
  B    5 mr r29, r3
--- replace mine 7:9 base 7:9
  M    7 lis r28, 0
  M    8 mr r31, r5
  B    7 lis r27, 0
  B    8 mr r25, r5
--- replace mine 10:12 base 10:12
  M   10 mr r29, r6
  M   11 addi r28, r28, 0
  B   10 mr r30, r6
  B   11 addi r27, r27, 0
--- replace mine 19:22 base 19:22
  M   19 cmpwi r31, 1
  M   20 addi r27, r3, 0xb4
  M   21 beq 716
  B   19 cmpwi r25, 1
  B   20 addi r31, r3, 0xb4
  B   21 beq 712
--- replace mine 23:24 base 23:24
  M   23 cmpwi r31, 0
  B   23 cmpwi r25, 0
--- replace mine 25:32 base 25:32
  M   25 b 960
  M   26 cmpwi r31, 3
  M   27 bge 952
  M   28 b 832
  M   29 cmpwi r29, 0
  M   30 beq 940
  M   31 lwz r12, 0(r29)
  B   25 b 956
  B   26 cmpwi r25, 3
  B   27 bge 948
  B   28 b 828
  B   29 cmpwi r30, 0
  B   30 beq 936
  B   31 lwz r12, 0(r30)
--- replace mine 33:34 base 33:34
  M   33 mr r3, r29
  B   33 mr r3, r30
--- replace mine 39:40 base 39:40
  M   39 beq 644
  B   39 beq 640
--- replace mine 45:47 base 45:47
  M   45 lwz r0, 0xac(r30)
  M   46 mr r31, r3
  B   45 lwz r0, 0xac(r29)
  B   46 mr r26, r3
--- replace mine 50:55 base 50:55
  M   50 bne 860
  M   51 lis r29, 0
  M   52 mr r3, r27
  M   53 addi r29, r29, 0
  M   54 lwz r4, 0x14(r29)
  B   50 bne 596
  B   51 lis r28, 0
  B   52 mr r3, r31
  B   53 addi r28, r28, 0
  B   54 lwz r4, 0x14(r28)
--- replace mine 63:65 base 63:65
  M   63 mr r27, r3
  M   64 mr r3, r31
  B   63 mr r25, r3
  B   64 mr r3, r26
--- replace mine 67:68 base 67:68
  M   67 lwz r0, 0x88(r30)
  B   67 lwz r0, 0x88(r29)
--- replace mine 77:78 base 77:78
  M   77 cmpwi r27, 0
  B   77 cmpwi r25, 0
--- replace mine 79:80 base 79:80
  M   79 mr r3, r27
  B   79 mr r3, r25
--- replace mine 81:82 base 81:82
  M   81 lwz r3, 0x8c(r30)
  B   81 lwz r3, 0x8c(r29)
--- replace mine 85:86 base 85:86
  M   85 mr r27, r3
  B   85 mr r28, r3
--- replace mine 88:90 base 88:90
  M   88 mr r3, r31
  M   89 stw r0, 0x14(r27)
  B   88 mr r3, r26
  B   89 stw r0, 0x14(r28)
--- replace mine 92:93 base 92:93
  M   92 mr r3, r31
  B   92 mr r3, r26
--- replace mine 96:97 base 96:97
  M   96 lwz r3, 0x8c(r30)
  B   96 lwz r3, 0x8c(r29)
--- replace mine 100:101 base 100:101
  M  100 mr r27, r3
  B  100 mr r25, r3
--- replace mine 102:103 base 102:103
  M  102 li r29, 1
  B  102 li r28, 1
--- replace mine 104:106 base 104:106
  M  104 stw r29, 0x14(r27)
  M  105 lwz r3, 0xa0(r30)
  B  104 stw r28, 0x14(r25)
  B  105 lwz r3, 0xa0(r29)
--- replace mine 108:109 base 108:109
  M  108 mr r27, r3
  B  108 mr r25, r3
--- replace mine 110:112 base 110:112
  M  110 stw r29, 0x14(r27)
  M  111 mr r3, r31
  B  110 stw r28, 0x14(r25)
  B  111 mr r3, r26
--- replace mine 114:115 base 114:115
  M  114 mr r3, r31
  B  114 mr r3, r26
--- replace mine 118:119 base 118:119
  M  118 lwz r3, 0x8c(r30)
  B  118 lwz r3, 0x8c(r29)
--- replace mine 122:123 base 122:123
  M  122 mr r27, r3
  B  122 mr r25, r3
--- replace mine 124:125 base 124:125
  M  124 li r29, 1
  B  124 li r28, 1
--- replace mine 126:128 base 126:128
  M  126 stw r29, 0x14(r27)
  M  127 lwz r3, 0xa0(r30)
  B  126 stw r28, 0x14(r25)
  B  127 lwz r3, 0xa0(r29)
--- replace mine 130:131 base 130:131
  M  130 mr r27, r3
  B  130 mr r25, r3
--- replace mine 132:134 base 132:134
  M  132 stw r29, 0x14(r27)
  M  133 mr r3, r31
  B  132 stw r28, 0x14(r25)
  B  133 mr r3, r26
--- replace mine 136:137 base 136:137
  M  136 mr r3, r31
  B  136 mr r3, r26
--- replace mine 140:141 base 140:141
  M  140 mr r3, r31
  B  140 mr r3, r26
--- replace mine 144:145 base 144:145
  M  144 mr r3, r31
  B  144 mr r3, r26
--- replace mine 147:148 base 147:148
  M  147 mr r3, r31
  B  147 mr r3, r26
--- replace mine 150:151 base 150:151
  M  150 mr r3, r31
  B  150 mr r3, r26
--- replace mine 154:155 base 154:155
  M  154 addi r4, r28, 0x5a1
  B  154 addi r4, r27, 0x5a1
--- replace mine 158:162 base 158:162
  M  158 stw r0, 0xac(r30)
  M  159 b 424
  M  160 lwz r4, 0x1c(r29)
  M  161 mr r3, r27
  B  158 stw r0, 0xac(r29)
  B  159 b 160
  B  160 lwz r4, 0x1c(r28)
  B  161 mr r3, r31
--- replace mine 166:168 base 166:168
  M  166 mr r3, r30
  M  167 stw r0, 0xc0(r30)
  B  166 mr r3, r29
  B  167 stw r0, 0xc0(r29)
--- replace mine 169:172 base 169:172
  M  169 b 384
  M  170 lwz r4, 0x24(r29)
  M  171 mr r3, r27
  B  169 b 120
  B  170 lwz r4, 0x24(r28)
  B  171 mr r3, r31
--- replace mine 175:176 base 175:176
  M  175 mr r3, r31
  B  175 mr r3, r26
--- replace mine 179:180 base 179:180
  M  179 addi r4, r28, 0x456
  B  179 addi r4, r27, 0x456
--- replace mine 182:183 base 182:183
  M  182 mr r3, r30
  B  182 mr r3, r29
--- replace mine 184:187 base 184:187
  M  184 b 324
  M  185 lwz r4, 0x28(r29)
  M  186 mr r3, r27
  B  184 b 60
  B  185 lwz r4, 0x28(r28)
  B  186 mr r3, r31
--- replace mine 189:191 base 189:191
  M  189 bne 304
  M  190 mr r3, r31
  B  189 bne 40
  B  190 mr r3, r26
--- replace mine 194:195 base 194:195
  M  194 addi r4, r28, 0x515
  B  194 addi r4, r27, 0x515
--- replace mine 197:198 base 197:198
  M  197 mr r3, r30
  B  197 mr r3, r29
--- replace mine 199:201 base 199:200
  M  199 b 264
  M  200 lbz r0, 0x84(r30)
  B  199 lbz r0, 0x84(r29)
--- replace mine 203:204 base 202:203
  M  203 cmpwi r29, 0
  B  202 cmpwi r30, 0
--- replace mine 206:207 base 205:206
  M  206 lwz r4, 0x6c(r30)
  B  205 lwz r4, 0x6c(r29)
--- replace mine 210:211 base 209:210
  M  210 cmplw r29, r3
  B  209 cmplw r30, r3
--- replace mine 212:216 base 211:215
  M  212 lis r31, 0
  M  213 mr r3, r27
  M  214 addi r31, r31, 0
  M  215 lwz r4, 0x28(r31)
  B  211 lis r30, 0
  B  212 mr r3, r31
  B  213 addi r30, r30, 0
  B  214 lwz r4, 0x28(r30)
--- replace mine 219:220 base 218:219
  M  219 lwz r0, 0x7c(r30)
  B  218 lwz r0, 0x7c(r29)
--- replace mine 223:224 base 222:223
  M  223 stw r0, 0x7c(r30)
  B  222 stw r0, 0x7c(r29)
--- replace mine 225:227 base 224:226
  M  225 lwz r4, 0x24(r31)
  M  226 mr r3, r27
  B  224 lwz r4, 0x24(r30)
  B  225 mr r3, r31
--- replace mine 230:231 base 229:230
  M  230 lwz r0, 0x78(r30)
  B  229 lwz r0, 0x78(r29)
--- replace mine 234:235 base 233:234
  M  234 stw r0, 0x78(r30)
  B  233 stw r0, 0x78(r29)
--- replace mine 236:237 base 235:236
  M  236 lbz r0, 0x84(r30)
  B  235 lbz r0, 0x84(r29)
--- replace mine 239:240 base 238:239
  M  239 cmpwi r29, 0
  B  238 cmpwi r30, 0
--- replace mine 242:243 base 241:242
  M  242 lwz r4, 0x6c(r30)
  B  241 lwz r4, 0x6c(r29)
--- replace mine 246:247 base 245:246
  M  246 cmplw r29, r3
  B  245 cmplw r30, r3
--- replace mine 248:252 base 247:251
  M  248 lis r31, 0
  M  249 mr r3, r27
  M  250 addi r31, r31, 0
  M  251 lwz r4, 0x28(r31)
  B  247 lis r30, 0
  B  248 mr r3, r31
  B  249 addi r30, r30, 0
  B  250 lwz r4, 0x28(r30)
--- replace mine 256:257 base 255:256
  M  256 stw r0, 0x7c(r30)
  B  255 stw r0, 0x7c(r29)
--- replace mine 258:260 base 257:259
  M  258 lwz r4, 0x24(r31)
  M  259 mr r3, r27
  B  257 lwz r4, 0x24(r30)
  B  258 mr r3, r31
--- replace mine 264:266 base 263:265
  M  264 stw r0, 0x78(r30)
  M  265 addi r11, r1, 0x20
  B  263 stw r0, 0x78(r29)
  B  264 addi r11, r1, 0x30
--- replace mine 267:268 base 266:267
  M  267 lwz r0, 0x24(r1)
  B  266 lwz r0, 0x34(r1)
--- replace mine 269:270 base 268:269
  M  269 addi r1, r1, 0x20
  B  268 addi r1, r1, 0x30
```

- near-target local type: retain mailbox as scene base pointer: exact False; insns 270/270; differences 84; objdiff 98.37037

```text
src 0x438 base 0x438 insns 270/270
diffs 84: [5, 7, 10, 11, 20, 29, 31, 33, 45, 46, 51, 52, 53, 54, 63, 64, 67, 77, 79, 81]
     5 M mr r27, r3
       B mr r29, r3
     7 M lis r31, 0
       B lis r27, 0
    10 M mr r28, r6
       B mr r30, r6
    11 M addi r31, r31, 0
       B addi r27, r27, 0
    20 M addi r30, r3, 0xb4
       B addi r31, r3, 0xb4
    29 M cmpwi r28, 0
       B cmpwi r30, 0
    31 M lwz r12, 0(r28)
       B lwz r12, 0(r30)
    33 M mr r3, r28
       B mr r3, r30
    45 M lwz r0, 0xac(r27)
       B lwz r0, 0xac(r29)
    46 M mr r29, r3
       B mr r26, r3
    51 M lis r26, 0
       B lis r28, 0
    52 M mr r3, r30
       B mr r3, r31
    53 M addi r26, r26, 0
       B addi r28, r28, 0
    54 M lwz r4, 0x14(r26)
       B lwz r4, 0x14(r28)
    63 M mr r26, r3
       B mr r25, r3
    64 M mr r3, r29
       B mr r3, r26
    67 M lwz r0, 0x88(r27)
       B lwz r0, 0x88(r29)
    77 M cmpwi r26, 0
       B cmpwi r25, 0
    79 M mr r3, r26
       B mr r3, r25
    81 M lwz r3, 0x8c(r27)
       B lwz r3, 0x8c(r29)
    85 M mr r26, r3
       B mr r28, r3
    88 M mr r3, r29
       B mr r3, r26
    89 M stw r0, 0x14(r26)
       B stw r0, 0x14(r28)
    92 M mr r3, r29
       B mr r3, r26
    96 M lwz r3, 0x8c(r27)
       B lwz r3, 0x8c(r29)
   102 M li r26, 1
       B li r28, 1
   104 M stw r26, 0x14(r25)
       B stw r28, 0x14(r25)
   105 M lwz r3, 0xa0(r27)
       B lwz r3, 0xa0(r29)
   110 M stw r26, 0x14(r25)
       B stw r28, 0x14(r25)
   111 M mr r3, r29
       B mr r3, r26
   114 M mr r3, r29
       B mr r3, r26
   118 M lwz r3, 0x8c(r27)
       B lwz r3, 0x8c(r29)
   124 M li r26, 1
       B li r28, 1
   126 M stw r26, 0x14(r25)
       B stw r28, 0x14(r25)
   127 M lwz r3, 0xa0(r27)
       B lwz r3, 0xa0(r29)
   132 M stw r26, 0x14(r25)
       B stw r28, 0x14(r25)
   133 M mr r3, r29
       B mr r3, r26
   136 M mr r3, r29
       B mr r3, r26
   140 M mr r3, r29
       B mr r3, r26
   144 M mr r3, r29
       B mr r3, r26
   147 M mr r3, r29
       B mr r3, r26
   150 M mr r3, r29
       B mr r3, r26
   154 M addi r4, r31, 0x5a1
       B addi r4, r27, 0x5a1
   158 M stw r0, 0xac(r27)
       B stw r0, 0xac(r29)
   160 M lwz r4, 0x1c(r26)
       B lwz r4, 0x1c(r28)
   161 M mr r3, r30
       B mr r3, r31
   166 M mr r3, r27
       B mr r3, r29
   167 M stw r0, 0xc0(r27)
       B stw r0, 0xc0(r29)
   170 M lwz r4, 0x24(r26)
       B lwz r4, 0x24(r28)
   171 M mr r3, r30
       B mr r3, r31
   175 M mr r3, r29
       B mr r3, r26
   179 M addi r4, r31, 0x456
       B addi r4, r27, 0x456
   182 M mr r3, r27
       B mr r3, r29
   185 M lwz r4, 0x28(r26)
       B lwz r4, 0x28(r28)
   186 M mr r3, r30
       B mr r3, r31
   190 M mr r3, r29
       B mr r3, r26
   194 M addi r4, r31, 0x515
       B addi r4, r27, 0x515
   197 M mr r3, r27
       B mr r3, r29
   199 M lbz r0, 0x84(r27)
       B lbz r0, 0x84(r29)
   202 M cmpwi r28, 0
       B cmpwi r30, 0
   205 M lwz r4, 0x6c(r27)
       B lwz r4, 0x6c(r29)
   209 M cmplw r28, r3
       B cmplw r30, r3
   211 M lis r28, 0
       B lis r30, 0
   212 M mr r3, r30
       B mr r3, r31
   213 M addi r28, r28, 0
       B addi r30, r30, 0
   214 M lwz r4, 0x28(r28)
       B lwz r4, 0x28(r30)
   218 M lwz r0, 0x7c(r27)
       B lwz r0, 0x7c(r29)
   222 M stw r0, 0x7c(r27)
       B stw r0, 0x7c(r29)
   224 M lwz r4, 0x24(r28)
       B lwz r4, 0x24(r30)
   225 M mr r3, r30
       B mr r3, r31
   229 M lwz r0, 0x78(r27)
       B lwz r0, 0x78(r29)
   233 M stw r0, 0x78(r27)
       B stw r0, 0x78(r29)
   235 M lbz r0, 0x84(r27)
       B lbz r0, 0x84(r29)
   238 M cmpwi r28, 0
       B cmpwi r30, 0
   241 M lwz r4, 0x6c(r27)
       B lwz r4, 0x6c(r29)
   245 M cmplw r28, r3
       B cmplw r30, r3
   247 M lis r28, 0
       B lis r30, 0
   248 M mr r3, r30
       B mr r3, r31
   249 M addi r28, r28, 0
       B addi r30, r30, 0
   250 M lwz r4, 0x28(r28)
       B lwz r4, 0x28(r30)
   255 M stw r0, 0x7c(r27)
       B stw r0, 0x7c(r29)
   257 M lwz r4, 0x24(r28)
       B lwz r4, 0x24(r30)
   258 M mr r3, r30
       B mr r3, r31
   263 M stw r0, 0x78(r27)
       B stw r0, 0x78(r29)
```

- near-target temporary boundary: mailbox lookup after cancel animation: exact False; insns 268/270; differences None; objdiff 97.01852

```text
src 0x430 base 0x438 insns 268/270
--- replace mine 21:22 base 21:22
  M   21 beq 704
  B   21 beq 712
--- replace mine 25:26 base 25:26
  M   25 b 948
  B   25 b 956
--- replace mine 27:29 base 27:29
  M   27 bge 940
  M   28 b 820
  B   27 bge 948
  B   28 b 828
--- replace mine 30:31 base 30:31
  M   30 beq 928
  B   30 beq 936
--- replace mine 39:40 base 39:40
  M   39 beq 632
  B   39 beq 640
--- replace mine 50:51 base 50:51
  M   50 bne 588
  B   50 bne 596
--- replace mine 57:61 base 57:58
  M   57 bne 404
  M   58 mr r3, r26
  M   59 li r4, 0x1b
  M   60 bl 0
  B   57 bne 412
--- insert mine 66:66 base 63:67
  B   63 mr r25, r3
  B   64 mr r3, r26
  B   65 li r4, 0x1b
  B   66 bl 0
--- replace mine 68:69 base 69:70
  M   68 beq 104
  B   69 beq 108
--- replace mine 72:73 base 73:74
  M   72 b 292
  B   73 b 296
--- replace mine 74:78 base 75:80
  M   74 bge 284
  M   75 b 164
  M   76 cmpwi r3, 0
  M   77 beq 8
  B   75 bge 288
  B   76 b 168
  B   77 cmpwi r25, 0
  B   78 beq 12
  B   79 mr r3, r25
```

- near-target condition form: explicit scene-pointer test and u32 event local: exact False; insns 270/270; differences 3; objdiff 99.94444

```text
src 0x438 base 0x438 insns 270/270
diffs 3: [63, 77, 79]
    63 M mr r28, r3
       B mr r25, r3
    77 M cmpwi r28, 0
       B cmpwi r25, 0
    79 M mr r3, r28
       B mr r3, r25
```

## src/scene/address/iplAddress: draw__Q33ipl5scene7AddressFv

```text
src 0x394 base 0x3ac insns 229/235
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x80(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:6 base 2:6
  M    2 stw r0, 0x84(r1)
  M    3 stfd f31, 0x70(r1)
  M    4 xxsel vs31, vs1, vs0, v1
  M    5 addi r11, r1, 0x70
  B    2 stw r0, 0x94(r1)
  B    3 stfd f31, 0x80(r1)
  B    4 xsmsubasp f31, f1, f0
  B    5 addi r11, r1, 0x80
--- replace mine 13:14 base 13:14
  M   13 stw r0, 0x40(r1)
  B   13 stw r0, 0x50(r1)
--- replace mine 16:17 base 16:17
  M   16 stw r0, 0x48(r1)
  B   16 stw r0, 0x58(r1)
--- replace mine 18:19 base 18:19
  M   18 bne 736
  B   18 bne 760
--- replace mine 33:34 base 33:34
  M   33 b 112
  B   33 b 136
--- replace mine 36:37 base 36:37
  M   36 stw r0, 0x44(r1)
  B   36 stw r0, 0x54(r1)
--- replace mine 39:43 base 39:43
  M   39 addi r4, r1, 0x38
  M   40 stw r0, 0x4c(r1)
  M   41 lfd f3, 0x40(r1)
  M   42 lfd f1, 0x48(r1)
  B   39 addi r4, r1, 0x48
  B   40 stw r0, 0x5c(r1)
  B   41 lfd f3, 0x50(r1)
  B   42 lfd f1, 0x58(r1)
--- replace mine 47:49 base 47:55
  M   47 stfs f2, 0x3c(r1)
  M   48 stfs f0, 0x38(r1)
  B   47 stfs f2, 0xc(r1)
  B   48 lwz r0, 0xc(r1)
  B   49 stfs f0, 8(r1)
  B   50 lwz r5, 8(r1)
  B   51 stw r0, 0x2c(r1)
  B   52 stw r5, 0x28(r1)
  B   53 stw r5, 0x48(r1)
  B   54 stw r0, 0x4c(r1)
--- replace mine 62:63 base 68:69
  M   62 bge -112
  B   68 bge -136
--- replace mine 99:101 base 105:107
  M   99 stw r0, 0x44(r1)
  M  100 lfd f0, 0x40(r1)
  B  105 stw r0, 0x54(r1)
  B  106 lfd f0, 0x50(r1)
--- replace mine 103:108 base 109:114
  M  103 stw r4, 0x1c(r1)
  M  104 stw r4, 0x34(r1)
  M  105 addi r4, r1, 0x30
  M  106 stw r3, 0x18(r1)
  M  107 stw r3, 0x30(r1)
  B  109 stw r4, 0x24(r1)
  B  110 stw r4, 0x44(r1)
  B  111 addi r4, r1, 0x40
  B  112 stw r3, 0x20(r1)
  B  113 stw r3, 0x40(r1)
--- replace mine 145:147 base 151:153
  M  145 stw r0, 0x4c(r1)
  M  146 lfd f0, 0x48(r1)
  B  151 stw r0, 0x5c(r1)
  B  152 lfd f0, 0x58(r1)
--- replace mine 149:154 base 155:160
  M  149 stw r4, 0x14(r1)
  M  150 stw r4, 0x2c(r1)
  M  151 addi r4, r1, 0x28
  M  152 stw r3, 0x10(r1)
  M  153 stw r3, 0x28(r1)
  B  155 stw r4, 0x1c(r1)
  B  156 stw r4, 0x3c(r1)
  B  157 addi r4, r1, 0x38
  B  158 stw r3, 0x18(r1)
  B  159 stw r3, 0x38(r1)
--- replace mine 176:178 base 182:184
  M  176 stw r0, 0x44(r1)
  M  177 lfd f0, 0x40(r1)
  B  182 stw r0, 0x54(r1)
  B  183 lfd f0, 0x50(r1)
--- replace mine 180:185 base 186:191
  M  180 stw r4, 0xc(r1)
  M  181 stw r4, 0x24(r1)
  M  182 addi r4, r1, 0x20
  M  183 stw r3, 8(r1)
  M  184 stw r3, 0x20(r1)
  B  186 stw r4, 0x14(r1)
  B  187 stw r4, 0x34(r1)
  B  188 addi r4, r1, 0x30
  B  189 stw r3, 0x10(r1)
  B  190 stw r3, 0x30(r1)
--- replace mine 221:224 base 227:230
  M  221 .long e3e10078
  M  222 addi r11, r1, 0x70
  M  223 lfd f31, 0x70(r1)
  B  227 .long e3e10088
  B  228 addi r11, r1, 0x80
  B  229 lfd f31, 0x80(r1)
--- replace mine 225:226 base 231:232
  M  225 lwz r0, 0x84(r1)
  B  231 lwz r0, 0x94(r1)
--- replace mine 227:228 base 233:234
  M  227 addi r1, r1, 0x80
  B  233 addi r1, r1, 0x90
```

- stack copies: product in derived vector then derived copy to translation: exact False; insns 233/235; differences None; objdiff 98.07234

```text
src 0x3a4 base 0x3ac insns 233/235
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x80(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:6 base 2:6
  M    2 stw r0, 0x84(r1)
  M    3 stfd f31, 0x70(r1)
  M    4 xxsel vs31, vs1, vs0, v1
  M    5 addi r11, r1, 0x70
  B    2 stw r0, 0x94(r1)
  B    3 stfd f31, 0x80(r1)
  B    4 xsmsubasp f31, f1, f0
  B    5 addi r11, r1, 0x80
--- replace mine 13:14 base 13:14
  M   13 stw r0, 0x48(r1)
  B   13 stw r0, 0x50(r1)
--- replace mine 16:17 base 16:17
  M   16 stw r0, 0x50(r1)
  B   16 stw r0, 0x58(r1)
--- replace mine 18:19 base 18:19
  M   18 bne 752
  B   18 bne 760
--- replace mine 33:34 base 33:34
  M   33 b 128
  B   33 b 136
--- replace mine 36:37 base 36:37
  M   36 stw r0, 0x4c(r1)
  B   36 stw r0, 0x54(r1)
--- replace mine 39:43 base 39:43
  M   39 addi r4, r1, 0x38
  M   40 stw r0, 0x54(r1)
  M   41 lfd f3, 0x48(r1)
  M   42 lfd f1, 0x50(r1)
  B   39 addi r4, r1, 0x48
  B   40 stw r0, 0x5c(r1)
  B   41 lfd f3, 0x50(r1)
  B   42 lfd f1, 0x58(r1)
--- replace mine 47:53 base 47:55
  M   47 stfs f2, 0x44(r1)
  M   48 stfs f0, 0x40(r1)
  M   49 lwz r0, 0x44(r1)
  M   50 lwz r5, 0x40(r1)
  M   51 stw r0, 0x3c(r1)
  M   52 stw r5, 0x38(r1)
  B   47 stfs f2, 0xc(r1)
  B   48 lwz r0, 0xc(r1)
  B   49 stfs f0, 8(r1)
  B   50 lwz r5, 8(r1)
  B   51 stw r0, 0x2c(r1)
  B   52 stw r5, 0x28(r1)
  B   53 stw r5, 0x48(r1)
  B   54 stw r0, 0x4c(r1)
--- replace mine 66:67 base 68:69
  M   66 bge -128
  B   68 bge -136
--- replace mine 103:105 base 105:107
  M  103 stw r0, 0x4c(r1)
  M  104 lfd f0, 0x48(r1)
  B  105 stw r0, 0x54(r1)
  B  106 lfd f0, 0x50(r1)
--- replace mine 107:112 base 109:114
  M  107 stw r4, 0x1c(r1)
  M  108 stw r4, 0x34(r1)
  M  109 addi r4, r1, 0x30
  M  110 stw r3, 0x18(r1)
  M  111 stw r3, 0x30(r1)
  B  109 stw r4, 0x24(r1)
  B  110 stw r4, 0x44(r1)
  B  111 addi r4, r1, 0x40
  B  112 stw r3, 0x20(r1)
  B  113 stw r3, 0x40(r1)
--- replace mine 149:151 base 151:153
  M  149 stw r0, 0x54(r1)
  M  150 lfd f0, 0x50(r1)
  B  151 stw r0, 0x5c(r1)
  B  152 lfd f0, 0x58(r1)
--- replace mine 153:158 base 155:160
  M  153 stw r4, 0x14(r1)
  M  154 stw r4, 0x2c(r1)
  M  155 addi r4, r1, 0x28
  M  156 stw r3, 0x10(r1)
  M  157 stw r3, 0x28(r1)
  B  155 stw r4, 0x1c(r1)
  B  156 stw r4, 0x3c(r1)
  B  157 addi r4, r1, 0x38
  B  158 stw r3, 0x18(r1)
  B  159 stw r3, 0x38(r1)
--- replace mine 180:182 base 182:184
  M  180 stw r0, 0x4c(r1)
  M  181 lfd f0, 0x48(r1)
  B  182 stw r0, 0x54(r1)
  B  183 lfd f0, 0x50(r1)
--- replace mine 184:189 base 186:191
  M  184 stw r4, 0xc(r1)
  M  185 stw r4, 0x24(r1)
  M  186 addi r4, r1, 0x20
  M  187 stw r3, 8(r1)
  M  188 stw r3, 0x20(r1)
  B  186 stw r4, 0x14(r1)
  B  187 stw r4, 0x34(r1)
  B  188 addi r4, r1, 0x30
  B  189 stw r3, 0x10(r1)
  B  190 stw r3, 0x30(r1)
--- replace mine 225:228 base 227:230
  M  225 .long e3e10078
  M  226 addi r11, r1, 0x70
  M  227 lfd f31, 0x70(r1)
  B  227 .long e3e10088
  B  228 addi r11, r1, 0x80
  B  229 lfd f31, 0x80(r1)
--- replace mine 229:230 base 231:232
  M  229 lwz r0, 0x84(r1)
  B  231 lwz r0, 0x94(r1)
--- replace mine 231:232 base 233:234
  M  231 addi r1, r1, 0x80
  B  233 addi r1, r1, 0x90
```

- stack copies: product in base aggregate followed by aggregate copy and conversion: exact False; insns 237/235; differences None; objdiff 97.10213

```text
src 0x3b4 base 0x3ac insns 237/235
--- replace mine 18:19 base 18:19
  M   18 bne 768
  B   18 bne 760
--- replace mine 33:34 base 33:34
  M   33 b 144
  B   33 b 136
--- replace mine 35:36 base 35:36
  M   35 lfs f2, 0(0)
  B   35 lfs f2, 4(r29)
--- replace mine 38:40 base 38:40
  M   38 lfs f0, 4(r29)
  M   39 addi r4, r1, 0x38
  B   38 lfs f0, 0(0)
  B   39 addi r4, r1, 0x48
--- replace mine 47:57 base 47:55
  M   47 stfs f2, 0x48(r1)
  M   48 stfs f0, 0x4c(r1)
  M   49 lwz r5, 0x48(r1)
  M   50 lwz r0, 0x4c(r1)
  M   51 stw r5, 0x40(r1)
  M   52 stw r0, 0x44(r1)
  M   53 lfs f1, 0x40(r1)
  M   54 lfs f0, 0x44(r1)
  M   55 stfs f1, 0x38(r1)
  M   56 stfs f0, 0x3c(r1)
  B   47 stfs f2, 0xc(r1)
  B   48 lwz r0, 0xc(r1)
  B   49 stfs f0, 8(r1)
  B   50 lwz r5, 8(r1)
  B   51 stw r0, 0x2c(r1)
  B   52 stw r5, 0x28(r1)
  B   53 stw r5, 0x48(r1)
  B   54 stw r0, 0x4c(r1)
--- replace mine 70:71 base 68:69
  M   70 bge -144
  B   68 bge -136
--- replace mine 111:116 base 109:114
  M  111 stw r4, 0x1c(r1)
  M  112 stw r4, 0x34(r1)
  M  113 addi r4, r1, 0x30
  M  114 stw r3, 0x18(r1)
  M  115 stw r3, 0x30(r1)
  B  109 stw r4, 0x24(r1)
  B  110 stw r4, 0x44(r1)
  B  111 addi r4, r1, 0x40
  B  112 stw r3, 0x20(r1)
  B  113 stw r3, 0x40(r1)
--- replace mine 157:162 base 155:160
  M  157 stw r4, 0x14(r1)
  M  158 stw r4, 0x2c(r1)
  M  159 addi r4, r1, 0x28
  M  160 stw r3, 0x10(r1)
  M  161 stw r3, 0x28(r1)
  B  155 stw r4, 0x1c(r1)
  B  156 stw r4, 0x3c(r1)
  B  157 addi r4, r1, 0x38
  B  158 stw r3, 0x18(r1)
  B  159 stw r3, 0x38(r1)
--- replace mine 188:193 base 186:191
  M  188 stw r4, 0xc(r1)
  M  189 stw r4, 0x24(r1)
  M  190 addi r4, r1, 0x20
  M  191 stw r3, 8(r1)
  M  192 stw r3, 0x20(r1)
  B  186 stw r4, 0x14(r1)
  B  187 stw r4, 0x34(r1)
  B  188 addi r4, r1, 0x30
  B  189 stw r3, 0x10(r1)
  B  190 stw r3, 0x30(r1)
```

- local type and stack copies: signed-long page walk with explicit derived copy: exact False; insns 233/235; differences None; objdiff 98.07234

```text
src 0x3a4 base 0x3ac insns 233/235
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x80(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:6 base 2:6
  M    2 stw r0, 0x84(r1)
  M    3 stfd f31, 0x70(r1)
  M    4 xxsel vs31, vs1, vs0, v1
  M    5 addi r11, r1, 0x70
  B    2 stw r0, 0x94(r1)
  B    3 stfd f31, 0x80(r1)
  B    4 xsmsubasp f31, f1, f0
  B    5 addi r11, r1, 0x80
--- replace mine 13:14 base 13:14
  M   13 stw r0, 0x48(r1)
  B   13 stw r0, 0x50(r1)
--- replace mine 16:17 base 16:17
  M   16 stw r0, 0x50(r1)
  B   16 stw r0, 0x58(r1)
--- replace mine 18:19 base 18:19
  M   18 bne 752
  B   18 bne 760
--- replace mine 33:34 base 33:34
  M   33 b 128
  B   33 b 136
--- replace mine 36:37 base 36:37
  M   36 stw r0, 0x4c(r1)
  B   36 stw r0, 0x54(r1)
--- replace mine 39:43 base 39:43
  M   39 addi r4, r1, 0x38
  M   40 stw r0, 0x54(r1)
  M   41 lfd f3, 0x48(r1)
  M   42 lfd f1, 0x50(r1)
  B   39 addi r4, r1, 0x48
  B   40 stw r0, 0x5c(r1)
  B   41 lfd f3, 0x50(r1)
  B   42 lfd f1, 0x58(r1)
--- replace mine 47:53 base 47:55
  M   47 stfs f2, 0x44(r1)
  M   48 stfs f0, 0x40(r1)
  M   49 lwz r0, 0x44(r1)
  M   50 lwz r5, 0x40(r1)
  M   51 stw r0, 0x3c(r1)
  M   52 stw r5, 0x38(r1)
  B   47 stfs f2, 0xc(r1)
  B   48 lwz r0, 0xc(r1)
  B   49 stfs f0, 8(r1)
  B   50 lwz r5, 8(r1)
  B   51 stw r0, 0x2c(r1)
  B   52 stw r5, 0x28(r1)
  B   53 stw r5, 0x48(r1)
  B   54 stw r0, 0x4c(r1)
--- replace mine 66:67 base 68:69
  M   66 bge -128
  B   68 bge -136
--- replace mine 103:105 base 105:107
  M  103 stw r0, 0x4c(r1)
  M  104 lfd f0, 0x48(r1)
  B  105 stw r0, 0x54(r1)
  B  106 lfd f0, 0x50(r1)
--- replace mine 107:112 base 109:114
  M  107 stw r4, 0x1c(r1)
  M  108 stw r4, 0x34(r1)
  M  109 addi r4, r1, 0x30
  M  110 stw r3, 0x18(r1)
  M  111 stw r3, 0x30(r1)
  B  109 stw r4, 0x24(r1)
  B  110 stw r4, 0x44(r1)
  B  111 addi r4, r1, 0x40
  B  112 stw r3, 0x20(r1)
  B  113 stw r3, 0x40(r1)
--- replace mine 149:151 base 151:153
  M  149 stw r0, 0x54(r1)
  M  150 lfd f0, 0x50(r1)
  B  151 stw r0, 0x5c(r1)
  B  152 lfd f0, 0x58(r1)
--- replace mine 153:158 base 155:160
  M  153 stw r4, 0x14(r1)
  M  154 stw r4, 0x2c(r1)
  M  155 addi r4, r1, 0x28
  M  156 stw r3, 0x10(r1)
  M  157 stw r3, 0x28(r1)
  B  155 stw r4, 0x1c(r1)
  B  156 stw r4, 0x3c(r1)
  B  157 addi r4, r1, 0x38
  B  158 stw r3, 0x18(r1)
  B  159 stw r3, 0x38(r1)
--- replace mine 180:182 base 182:184
  M  180 stw r0, 0x4c(r1)
  M  181 lfd f0, 0x48(r1)
  B  182 stw r0, 0x54(r1)
  B  183 lfd f0, 0x50(r1)
--- replace mine 184:189 base 186:191
  M  184 stw r4, 0xc(r1)
  M  185 stw r4, 0x24(r1)
  M  186 addi r4, r1, 0x20
  M  187 stw r3, 8(r1)
  M  188 stw r3, 0x20(r1)
  B  186 stw r4, 0x14(r1)
  B  187 stw r4, 0x34(r1)
  B  188 addi r4, r1, 0x30
  B  189 stw r3, 0x10(r1)
  B  190 stw r3, 0x30(r1)
--- replace mine 225:228 base 227:230
  M  225 .long e3e10078
  M  226 addi r11, r1, 0x70
  M  227 lfd f31, 0x70(r1)
  B  227 .long e3e10088
  B  228 addi r11, r1, 0x80
  B  229 lfd f31, 0x80(r1)
--- replace mine 229:230 base 231:232
  M  229 lwz r0, 0x84(r1)
  B  231 lwz r0, 0x94(r1)
--- replace mine 231:232 base 233:234
  M  231 addi r1, r1, 0x80
  B  233 addi r1, r1, 0x90
```

## src/scene/address/iplAddress: onPreviousPage__Q33ipl5scene7AddressFv

```text
src 0x284 base 0x294 insns 161/165
--- replace mine 14:15 base 14:15
  M   14 b 564
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 552
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 348
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 272
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:102 base 99:102
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0xc(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
--- insert mine 103:103 base 103:107
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- replace mine 111:112 base 115:116
  M  111 addi r5, r1, 8
  B  115 addi r5, r1, 0x10
```

- stack copies: derived product copied to translation offset: exact False; insns 165/165; differences 11; objdiff 99.77576

```text
src 0x294 base 0x294 insns 165/165
diffs 11: [92, 97, 99, 100, 101, 102, 103, 104, 105, 106, 115]
    92 M lfs f2, 0(0)
       B lfs f1, 0(0)
    97 M lfs f1, 4(r6)
       B lfs f2, 4(r6)
    99 M fmuls f1, f2, f1
       B fmuls f2, f2, f1
   100 M fmuls f0, f2, f0
       B fmuls f0, f0, f1
   101 M stfs f1, 0x14(r1)
       B stfs f2, 0xc(r1)
   102 M stfs f0, 0x10(r1)
       B stfs f0, 8(r1)
   103 M lwz r0, 0x14(r1)
       B lwz r0, 0xc(r1)
   104 M lwz r6, 0x10(r1)
       B lwz r6, 8(r1)
   105 M stw r0, 0xc(r1)
       B stw r0, 0x14(r1)
   106 M stw r6, 8(r1)
       B stw r6, 0x10(r1)
   115 M addi r5, r1, 8
       B addi r5, r1, 0x10
```

- stack copies: base product copied as aggregate then converted to offset: exact False; insns 169/165; differences None; objdiff 96.49697

```text
src 0x2a4 base 0x294 insns 169/165
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x40(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x44(r1)
  M    3 addi r11, r1, 0x40
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 14:15 base 14:15
  M   14 b 596
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 584
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 380
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 304
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:105 base 97:106
  M   97 lfs f1, 0(0)
  M   98 lfs f0, 4(r6)
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0x18(r1)
  M  102 stfs f0, 0x1c(r1)
  M  103 lwz r6, 0x18(r1)
  M  104 lwz r0, 0x1c(r1)
  B   97 lfs f2, 4(r6)
  B   98 lfs f0, 0(0)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
  B  102 stfs f0, 8(r1)
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
--- delete mine 106:111 base 107:107
  M  106 stw r0, 0x14(r1)
  M  107 lfs f1, 0x10(r1)
  M  108 lfs f0, 0x14(r1)
  M  109 stfs f1, 8(r1)
  M  110 stfs f0, 0xc(r1)
--- replace mine 119:120 base 115:116
  M  119 addi r5, r1, 8
  B  115 addi r5, r1, 0x10
--- replace mine 163:164 base 159:160
  M  163 addi r11, r1, 0x40
  B  159 addi r11, r1, 0x30
--- replace mine 165:166 base 161:162
  M  165 lwz r0, 0x44(r1)
  B  161 lwz r0, 0x34(r1)
--- replace mine 167:168 base 163:164
  M  167 addi r1, r1, 0x40
  B  163 addi r1, r1, 0x30
```

- operand order and temporary boundary: product helper with integer page-count local: exact False; insns 184/165; differences None; objdiff 84.42424

```text
src 0x2e0 base 0x294 insns 184/165
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x60(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x64(r1)
  M    3 addi r11, r1, 0x60
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 14:15 base 14:15
  M   14 b 656
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 644
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 440
  B   68 b 364
--- replace mine 87:91 base 87:88
  M   87 b 364
  M   88 li r4, 0x14
  M   89 lis r0, 0x4330
  M   90 xoris r5, r4, 0x8000
  B   87 b 288
--- replace mine 92:104 base 89:94
  M   92 stw r5, 0x34(r1)
  M   93 li r6, 0x13
  M   94 lfd f1, 0(0)
  M   95 li r4, 0
  M   96 stw r0, 0x30(r1)
  M   97 lfd f0, 0x30(r1)
  M   98 stw r5, 0x3c(r1)
  M   99 fsubs f3, f0, f1
  M  100 stw r0, 0x38(r1)
  M  101 lfd f0, 0x38(r1)
  M  102 stw r6, 0xb0(r3)
  M  103 fsubs f2, f0, f1
  B   89 li r0, 0x13
  B   90 stw r0, 0xb0(r3)
  B   91 li r6, 0
  B   92 lfs f1, 0(0)
  B   93 addi r4, r31, 0x529
--- insert mine 105:105 base 95:96
  B   95 li r5, 1
--- replace mine 106:124 base 97:108
  M  106 addi r3, r1, 0x10
  M  107 lfs f1, 0(0)
  M  108 lfs f0, 4(r4)
  M  109 fmuls f1, f3, f1
  M  110 fmuls f2, f2, f0
  M  111 bl 0
  M  112 lwz r6, 0(r3)
  M  113 addi r4, r31, 0x529
  M  114 lwz r0, 4(r3)
  M  115 li r5, 1
  M  116 stw r6, 0x28(r1)
  M  117 stw r0, 0x2c(r1)
  M  118 lfs f1, 0x28(r1)
  M  119 lfs f0, 0x2c(r1)
  M  120 stfs f1, 0x20(r1)
  M  121 stfs f0, 0x24(r1)
  M  122 lwz r3, 0x8c(r30)
  M  123 stw r6, 8(r1)
  B   97 lfs f2, 4(r6)
  B   98 lfs f0, 0(0)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
  B  102 stfs f0, 8(r1)
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
  B  107 lwz r3, 0x8c(r3)
--- delete mine 125:126 base 109:109
  M  125 stw r0, 0xc(r1)
--- delete mine 127:128 base 110:110
  M  127 stw r6, 0x18(r1)
--- delete mine 129:130 base 111:111
  M  129 stw r0, 0x1c(r1)
--- replace mine 134:135 base 115:116
  M  134 addi r5, r1, 0x20
  B  115 addi r5, r1, 0x10
--- replace mine 178:179 base 159:160
  M  178 addi r11, r1, 0x60
  B  159 addi r11, r1, 0x30
--- replace mine 180:181 base 161:162
  M  180 lwz r0, 0x64(r1)
  B  161 lwz r0, 0x34(r1)
--- replace mine 182:183 base 163:164
  M  182 addi r1, r1, 0x60
  B  163 addi r1, r1, 0x30
```

## src/scene/address/iplAddress: movePane_onDrag__Q33ipl5scene7AddressFv

```text
src 0x268 base 0x26c insns 154/155
--- replace mine 34:36 base 34:36
  M   34 lwz r6, 0x8c(r31)
  M   35 lis r7, 0
  B   34 lwz r7, 0x8c(r31)
  B   35 lis r6, 0
--- replace mine 39:40 base 39:40
  M   39 lwz r3, 0x14(r6)
  B   39 lwz r3, 0x14(r7)
--- replace mine 43:44 base 43:44
  M   43 addi r4, r7, 0
  B   43 addi r4, r6, 0
--- replace mine 50:51 base 50:51
  M   50 mr r28, r3
  B   50 mr r27, r3
--- replace mine 56:61 base 56:62
  M   56 add r27, r5, r0
  M   57 addi r27, r27, 8
  M   58 beq 112
  M   59 cmpwi r27, 0
  M   60 beq 104
  B   56 add r0, r5, r0
  B   57 bne 8
  B   58 b 124
  B   59 addic. r29, r0, 8
  B   60 bne 8
  B   61 b 112
--- replace mine 69:70 base 70:71
  M   69 mr r3, r28
  B   70 mr r3, r27
--- replace mine 72:73 base 73:74
  M   72 mr r4, r29
  B   73 mr r4, r28
--- replace mine 78:79 base 79:80
  M   78 addi r27, r27, 2
  B   79 addi r29, r29, 2
--- replace mine 83:85 base 84:86
  M   83 lhz r29, 0(r27)
  M   84 cmpwi r29, 0
  B   84 lhz r28, 0(r29)
  B   85 cmpwi r28, 0
--- insert mine 87:87 base 88:89
  B   88 fadds f30, f0, f30
--- delete mine 88:89 base 90:90
  M   88 fadds f30, f30, f0
--- replace mine 108:110 base 109:111
  M  108 fmuls f0, f5, f0
  M  109 fneg f0, f0
  B  109 fmuls f5, f5, f0
  B  110 fneg f0, f5
```

- local type: friend name retained as wchar_t pointer: exact False; insns 154/155; differences None; objdiff 95.70968

```text
src 0x268 base 0x26c insns 154/155
--- replace mine 34:36 base 34:36
  M   34 lwz r6, 0x8c(r31)
  M   35 lis r7, 0
  B   34 lwz r7, 0x8c(r31)
  B   35 lis r6, 0
--- replace mine 39:40 base 39:40
  M   39 lwz r3, 0x14(r6)
  B   39 lwz r3, 0x14(r7)
--- replace mine 43:44 base 43:44
  M   43 addi r4, r7, 0
  B   43 addi r4, r6, 0
--- replace mine 50:51 base 50:51
  M   50 mr r28, r3
  B   50 mr r27, r3
--- replace mine 56:61 base 56:62
  M   56 add r27, r5, r0
  M   57 addi r27, r27, 8
  M   58 beq 112
  M   59 cmpwi r27, 0
  M   60 beq 104
  B   56 add r0, r5, r0
  B   57 bne 8
  B   58 b 124
  B   59 addic. r29, r0, 8
  B   60 bne 8
  B   61 b 112
--- replace mine 69:70 base 70:71
  M   69 mr r3, r28
  B   70 mr r3, r27
--- replace mine 72:73 base 73:74
  M   72 mr r4, r29
  B   73 mr r4, r28
--- replace mine 78:79 base 79:80
  M   78 addi r27, r27, 2
  B   79 addi r29, r29, 2
--- replace mine 83:85 base 84:86
  M   83 lhz r29, 0(r27)
  M   84 cmpwi r29, 0
  B   84 lhz r28, 0(r29)
  B   85 cmpwi r28, 0
--- insert mine 87:87 base 88:89
  B   88 fadds f30, f0, f30
--- delete mine 88:89 base 90:90
  M   88 fadds f30, f30, f0
--- replace mine 108:110 base 109:111
  M  108 fmuls f0, f5, f0
  M  109 fneg f0, f0
  B  109 fmuls f5, f5, f0
  B  110 fneg f0, f5
```

- branch direction: name-first guard with font pointer bound before character loop: compile failed: ers\sol-
#   med\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\include\scene\address\iplAddress.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\src\scene\address\iplAddress.cpp:6)
### mwcceppc.exe Compiler:
#    File: src\scene\address\iplAddress.cpp
# -----------------------------------------
#    1748:                 nw4r::ut::Font* font = textBox->GetFont();
#   Error:                                                          ^
#   (10209) illegal implicit conversion from 'const nw4r::ut::Font *' to
#   'nw4r::ut::Font *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


```text
compile failed: ers\sol-
#   med\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\include\scene\address\iplAddress.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   med\src\scene\address\iplAddress.cpp:6)
### mwcceppc.exe Compiler:
#    File: src\scene\address\iplAddress.cpp
# -----------------------------------------
#    1748:                 nw4r::ut::Font* font = textBox->GetFont();
#   Error:                                                          ^
#   (10209) illegal implicit conversion from 'const nw4r::ut::Font *' to
#   'nw4r::ut::Font *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
```

- pointer walk: retain first-character pointer and use signed-long index: exact False; insns 155/155; differences 24; objdiff 94.80645

```text
src 0x26c base 0x26c insns 155/155
diffs 24: [34, 35, 39, 43, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 78, 79, 84]
    34 M lwz r6, 0x8c(r31)
       B lwz r7, 0x8c(r31)
    35 M lis r7, 0
       B lis r6, 0
    39 M lwz r3, 0x14(r6)
       B lwz r3, 0x14(r7)
    43 M addi r4, r7, 0
       B addi r4, r6, 0
    56 M add r26, r5, r0
       B add r0, r5, r0
    57 M addi r26, r26, 8
       B bne 8
    58 M beq 116
       B b 124
    59 M cmpwi r26, 0
       B addic. r29, r0, 8
    60 M beq 108
       B bne 8
    61 M bl 0
       B b 112
    62 M lwz r12, 0(r3)
       B bl 0
    63 M lwz r12, 0xc(r12)
       B lwz r12, 0(r3)
    64 M mtctr r12
       B lwz r12, 0xc(r12)
    65 M bctrl
       B mtctr r12
    66 M lfd f31, 0(0)
       B bctrl
    67 M li r30, 0
       B lfd f31, 0(0)
    68 M lis r29, 0x4330
       B lis r30, 0x4330
    78 M stw r29, 0x48(r1)
       B stw r30, 0x48(r1)
    79 M addi r30, r30, 2
       B addi r29, r29, 2
    84 M lhzx r28, r26, r30
       B lhz r28, 0(r29)
    88 M addi r3, r1, 0x28
       B fadds f30, f0, f30
    89 M fadds f30, f30, f0
       B addi r3, r1, 0x28
   109 M fmuls f0, f5, f0
       B fmuls f5, f5, f0
   110 M fneg f0, f0
       B fneg f0, f5
```

## src/scene/address/iplAddress: stt_loop_forward__Q33ipl5scene7AddressFv

```text
src 0x194 base 0x18c insns 101/99
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x60(r1)
  B    0 stwu r1, -0x50(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x64(r1)
  M    3 addi r11, r1, 0x60
  B    2 stw r0, 0x54(r1)
  B    3 addi r11, r1, 0x50
--- replace mine 14:15 base 14:15
  M   14 beq 304
  B   14 beq 296
--- replace mine 16:19 base 16:21
  M   16 lfs f1, 0(0)
  M   17 lfs f0, 4(r3)
  M   18 addi r3, r1, 0x20
  B   16 lfs f0, 0(0)
  B   17 lfs f1, 4(r3)
  B   18 addi r3, r1, 0x10
  B   19 fneg f0, f0
  B   20 lfs f2, 0(0)
--- replace mine 20:30 base 22:30
  M   20 fneg f2, f0
  M   21 bl 0
  M   22 lwz r4, 0(r3)
  M   23 lwz r0, 4(r3)
  M   24 addi r3, r1, 0x18
  M   25 stw r4, 0x28(r1)
  M   26 lfs f2, 0(0)
  M   27 stw r0, 0x2c(r1)
  M   28 lfs f1, 0x28(r1)
  M   29 lfs f0, 0x2c(r1)
  B   22 stfs f0, 0x18(r1)
  B   23 stfs f1, 0x1c(r1)
  B   24 lwz r4, 0x18(r1)
  B   25 lwz r0, 0x1c(r1)
  B   26 stw r4, 0x20(r1)
  B   27 stw r0, 0x24(r1)
  B   28 lfs f1, 0x20(r1)
  B   29 lfs f0, 0x24(r1)
--- delete mine 31:32 base 31:31
  M   31 stw r4, 0x10(r1)
--- delete mine 33:34 base 32:32
  M   33 stw r0, 0x14(r1)
--- replace mine 39:45 base 37:43
  M   39 stw r6, 0x30(r1)
  M   40 stw r0, 0x34(r1)
  M   41 lfs f1, 0x30(r1)
  M   42 lfs f0, 0x34(r1)
  M   43 stfs f1, 0x38(r1)
  M   44 stfs f0, 0x3c(r1)
  B   37 stw r6, 0x28(r1)
  B   38 stw r0, 0x2c(r1)
  B   39 lfs f1, 0x28(r1)
  B   40 lfs f0, 0x2c(r1)
  B   41 stfs f1, 0x30(r1)
  B   42 stfs f0, 0x34(r1)
--- replace mine 55:56 base 53:54
  M   55 addi r5, r1, 0x38
  B   53 addi r5, r1, 0x30
--- replace mine 95:96 base 93:94
  M   95 addi r11, r1, 0x60
  B   93 addi r11, r1, 0x50
--- replace mine 97:98 base 95:96
  M   97 lwz r0, 0x64(r1)
  B   95 lwz r0, 0x54(r1)
--- replace mine 99:100 base 97:98
  M   99 addi r1, r1, 0x60
  B   97 addi r1, r1, 0x50
```

- stack copies: named base negation and ordinary base copy before offset: exact False; insns 99/99; differences 21; objdiff 94.90909

```text
src 0x18c base 0x18c insns 99/99
diffs 21: [16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 37, 38, 39, 40, 41, 42]
    16 M lfs f1, 0(0)
       B lfs f0, 0(0)
    17 M lfs f0, 4(r3)
       B lfs f1, 4(r3)
    18 M addi r3, r1, 0x30
       B addi r3, r1, 0x10
    19 M fneg f1, f1
       B fneg f0, f0
    20 M fneg f2, f0
       B lfs f2, 0(0)
    21 M bl 0
       B fneg f1, f1
    22 M lwz r4, 0x30(r1)
       B stfs f0, 0x18(r1)
    23 M addi r3, r1, 0x10
       B stfs f1, 0x1c(r1)
    24 M lwz r0, 0x34(r1)
       B lwz r4, 0x18(r1)
    25 M stw r4, 0x28(r1)
       B lwz r0, 0x1c(r1)
    26 M lfs f2, 0(0)
       B stw r4, 0x20(r1)
    27 M stw r0, 0x2c(r1)
       B stw r0, 0x24(r1)
    28 M lfs f1, 0x28(r1)
       B lfs f1, 0x20(r1)
    29 M lfs f0, 0x2c(r1)
       B lfs f0, 0x24(r1)
    37 M stw r6, 0x18(r1)
       B stw r6, 0x28(r1)
    38 M stw r0, 0x1c(r1)
       B stw r0, 0x2c(r1)
    39 M lfs f1, 0x18(r1)
       B lfs f1, 0x28(r1)
    40 M lfs f0, 0x1c(r1)
       B lfs f0, 0x2c(r1)
    41 M stfs f1, 0x20(r1)
       B stfs f1, 0x30(r1)
    42 M stfs f0, 0x24(r1)
       B stfs f0, 0x34(r1)
    53 M addi r5, r1, 0x20
       B addi r5, r1, 0x30
```

- stack copies: named negation copied through raw vector base: exact False; insns 99/99; differences 39; objdiff 85.242424

```text
src 0x18c base 0x18c insns 99/99
diffs 39: [0, 2, 3, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32]
     0 M stwu r1, -0x60(r1)
       B stwu r1, -0x50(r1)
     2 M stw r0, 0x64(r1)
       B stw r0, 0x54(r1)
     3 M addi r11, r1, 0x60
       B addi r11, r1, 0x50
    16 M lfs f1, 0(0)
       B lfs f0, 0(0)
    17 M lfs f0, 4(r3)
       B lfs f1, 4(r3)
    18 M addi r3, r1, 0x38
       B addi r3, r1, 0x10
    19 M fneg f1, f1
       B fneg f0, f0
    20 M fneg f2, f0
       B lfs f2, 0(0)
    21 M bl 0
       B fneg f1, f1
    22 M lwz r4, 0x38(r1)
       B stfs f0, 0x18(r1)
    23 M addi r3, r1, 0x10
       B stfs f1, 0x1c(r1)
    24 M lwz r0, 0x3c(r1)
       B lwz r4, 0x18(r1)
    25 M stw r4, 0x30(r1)
       B lwz r0, 0x1c(r1)
    26 M lfs f0, 0(0)
       B stw r4, 0x20(r1)
    27 M lfs f2, 0x30(r1)
       B stw r0, 0x24(r1)
    28 M stw r0, 0x34(r1)
       B lfs f1, 0x20(r1)
    29 M fmuls f1, f2, f0
       B lfs f0, 0x24(r1)
    30 M lfs f3, 0x34(r1)
       B fmuls f1, f2, f1
    31 M stfs f2, 0x18(r1)
       B fmuls f2, f2, f0
    32 M fmuls f2, f3, f0
       B bl 0
    33 M stfs f3, 0x1c(r1)
       B lwz r6, 0(r3)
    34 M bl 0
       B addi r4, r28, 0x529
    35 M lwz r6, 0(r3)
       B lwz r0, 4(r3)
    36 M addi r4, r28, 0x529
       B li r5, 1
    37 M lwz r0, 4(r3)
       B stw r6, 0x28(r1)
    38 M li r5, 1
       B stw r0, 0x2c(r1)
    39 M stw r6, 8(r1)
       B lfs f1, 0x28(r1)
    40 M stw r6, 0x28(r1)
       B lfs f0, 0x2c(r1)
    41 M stw r0, 0x2c(r1)
       B stfs f1, 0x30(r1)
    42 M lwz r3, 0x8c(r31)
       B stfs f0, 0x34(r1)
    43 M stw r0, 0xc(r1)
       B lwz r3, 0x8c(r31)
    44 M lwz r3, 0x14(r3)
       B stw r6, 8(r1)
    45 M stw r6, 0x20(r1)
       B lwz r3, 0x14(r3)
    46 M lwz r12, 0(r3)
       B stw r0, 0xc(r1)
    47 M stw r0, 0x24(r1)
       B lwz r12, 0(r3)
    53 M addi r5, r1, 0x28
       B addi r5, r1, 0x30
    93 M addi r11, r1, 0x60
       B addi r11, r1, 0x50
    95 M lwz r0, 0x64(r1)
       B lwz r0, 0x54(r1)
    97 M addi r1, r1, 0x60
       B addi r1, r1, 0x50
```

- operand evaluation: retained translation pane before unary vector offset: exact False; insns 102/99; differences None; objdiff 40.11111

```text
src 0x198 base 0x18c insns 102/99
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x60(r1)
  B    0 stwu r1, -0x50(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x64(r1)
  M    3 addi r11, r1, 0x60
  B    2 stw r0, 0x54(r1)
  B    3 addi r11, r1, 0x50
--- replace mine 14:15 base 14:43
  M   14 beq 308
  B   14 beq 296
  B   15 li r3, 0
  B   16 lfs f0, 0(0)
  B   17 lfs f1, 4(r3)
  B   18 addi r3, r1, 0x10
  B   19 fneg f0, f0
  B   20 lfs f2, 0(0)
  B   21 fneg f1, f1
  B   22 stfs f0, 0x18(r1)
  B   23 stfs f1, 0x1c(r1)
  B   24 lwz r4, 0x18(r1)
  B   25 lwz r0, 0x1c(r1)
  B   26 stw r4, 0x20(r1)
  B   27 stw r0, 0x24(r1)
  B   28 lfs f1, 0x20(r1)
  B   29 lfs f0, 0x24(r1)
  B   30 fmuls f1, f2, f1
  B   31 fmuls f2, f2, f0
  B   32 bl 0
  B   33 lwz r6, 0(r3)
  B   34 addi r4, r28, 0x529
  B   35 lwz r0, 4(r3)
  B   36 li r5, 1
  B   37 stw r6, 0x28(r1)
  B   38 stw r0, 0x2c(r1)
  B   39 lfs f1, 0x28(r1)
  B   40 lfs f0, 0x2c(r1)
  B   41 stfs f1, 0x30(r1)
  B   42 stfs f0, 0x34(r1)
--- replace mine 16:18 base 44:45
  M   16 addi r4, r28, 0x529
  M   17 li r5, 1
  B   44 stw r6, 8(r1)
--- insert mine 19:19 base 46:47
  B   46 stw r0, 0xc(r1)
--- replace mine 23:47 base 51:52
  M   23 li r4, 0
  M   24 lfs f1, 0(0)
  M   25 lfs f0, 4(r4)
  M   26 mr r29, r3
  M   27 fneg f1, f1
  M   28 addi r3, r1, 0x20
  M   29 fneg f2, f0
  M   30 bl 0
  M   31 lwz r4, 0(r3)
  M   32 lwz r0, 4(r3)
  M   33 addi r3, r1, 0x18
  M   34 stw r4, 0x28(r1)
  M   35 lfs f2, 0(0)
  M   36 stw r0, 0x2c(r1)
  M   37 lfs f1, 0x28(r1)
  M   38 lfs f0, 0x2c(r1)
  M   39 fmuls f1, f2, f1
  M   40 stw r4, 0x10(r1)
  M   41 fmuls f2, f2, f0
  M   42 stw r0, 0x14(r1)
  M   43 bl 0
  M   44 lwz r6, 0(r3)
  M   45 mr r4, r29
  M   46 lwz r0, 4(r3)
  B   51 mr r4, r3
--- replace mine 48:57 base 53:54
  M   48 stw r6, 0x30(r1)
  M   49 addi r5, r1, 0x38
  M   50 stw r0, 0x34(r1)
  M   51 lfs f1, 0x30(r1)
  M   52 lfs f0, 0x34(r1)
  M   53 stw r6, 8(r1)
  M   54 stw r0, 0xc(r1)
  M   55 stfs f1, 0x38(r1)
  M   56 stfs f0, 0x3c(r1)
  B   53 addi r5, r1, 0x30
--- replace mine 96:97 base 93:94
  M   96 addi r11, r1, 0x60
  B   93 addi r11, r1, 0x50
--- replace mine 98:99 base 95:96
  M   98 lwz r0, 0x64(r1)
  B   95 lwz r0, 0x54(r1)
--- replace mine 100:101 base 97:98
  M  100 addi r1, r1, 0x60
  B   97 addi r1, r1, 0x50
```

## src/scene/address/iplAddress: stt_backward__Q33ipl5scene7AddressFv

```text
src 0x16c base 0x164 insns 91/89
--- replace mine 14:19 base 14:20
  M   14 beq 264
  M   15 lwz r5, 0xb4(r31)
  M   16 li r4, 0
  M   17 addi r3, r1, 0x10
  M   18 addi r0, r5, 1
  B   14 beq 256
  B   15 lwz r6, 0xb4(r31)
  B   16 li r3, 0
  B   17 addi r4, r28, 0x529
  B   18 li r5, 1
  B   19 addi r0, r6, 1
--- replace mine 20:22 base 21:23
  M   20 lfs f1, 0(0)
  M   21 lfs f0, 4(r4)
  B   21 lfs f1, 4(r3)
  B   22 lfs f0, 0(0)
--- replace mine 23:35 base 24:35
  M   23 fneg f2, f0
  M   24 bl 0
  M   25 lwz r6, 0(r3)
  M   26 addi r4, r28, 0x529
  M   27 lwz r0, 4(r3)
  M   28 li r5, 1
  M   29 stw r6, 0x18(r1)
  M   30 stw r0, 0x1c(r1)
  M   31 lfs f1, 0x18(r1)
  M   32 lfs f0, 0x1c(r1)
  M   33 stfs f1, 0x20(r1)
  M   34 stfs f0, 0x24(r1)
  B   24 fneg f0, f0
  B   25 stfs f1, 0xc(r1)
  B   26 stfs f0, 8(r1)
  B   27 lwz r0, 0xc(r1)
  B   28 lwz r3, 8(r1)
  B   29 stw r0, 0x14(r1)
  B   30 stw r3, 0x10(r1)
  B   31 lfs f0, 0x14(r1)
  B   32 lfs f1, 0x10(r1)
  B   33 stfs f0, 0x1c(r1)
  B   34 stfs f1, 0x18(r1)
--- delete mine 36:37 base 36:36
  M   36 stw r6, 8(r1)
--- delete mine 38:39 base 37:37
  M   38 stw r0, 0xc(r1)
--- replace mine 45:46 base 43:44
  M   45 addi r5, r1, 0x20
  B   43 addi r5, r1, 0x18
```

- stack copies: named base negation and ordinary base copy before offset: exact False; insns 89/89; differences 21; objdiff 91.96629

```text
src 0x164 base 0x164 insns 89/89
diffs 21: [15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
    15 M lwz r5, 0xb4(r31)
       B lwz r6, 0xb4(r31)
    16 M li r4, 0
       B li r3, 0
    17 M addi r3, r1, 0x18
       B addi r4, r28, 0x529
    18 M addi r0, r5, 1
       B li r5, 1
    19 M stw r0, 0xb4(r31)
       B addi r0, r6, 1
    20 M lfs f1, 0(0)
       B stw r0, 0xb4(r31)
    21 M lfs f0, 4(r4)
       B lfs f1, 4(r3)
    22 M fneg f1, f1
       B lfs f0, 0(0)
    23 M fneg f2, f0
       B fneg f1, f1
    24 M bl 0
       B fneg f0, f0
    25 M lwz r3, 0x18(r1)
       B stfs f1, 0xc(r1)
    26 M addi r4, r28, 0x529
       B stfs f0, 8(r1)
    27 M lwz r0, 0x1c(r1)
       B lwz r0, 0xc(r1)
    28 M li r5, 1
       B lwz r3, 8(r1)
    29 M stw r3, 0x10(r1)
       B stw r0, 0x14(r1)
    30 M stw r0, 0x14(r1)
       B stw r3, 0x10(r1)
    31 M lfs f1, 0x10(r1)
       B lfs f0, 0x14(r1)
    32 M lfs f0, 0x14(r1)
       B lfs f1, 0x10(r1)
    33 M stfs f1, 8(r1)
       B stfs f0, 0x1c(r1)
    34 M stfs f0, 0xc(r1)
       B stfs f1, 0x18(r1)
    43 M addi r5, r1, 8
       B addi r5, r1, 0x18
```

- stack copies: named negation copied through raw vector base: exact False; insns 89/89; differences 21; objdiff 91.96629

```text
src 0x164 base 0x164 insns 89/89
diffs 21: [15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
    15 M lwz r5, 0xb4(r31)
       B lwz r6, 0xb4(r31)
    16 M li r4, 0
       B li r3, 0
    17 M addi r3, r1, 0x18
       B addi r4, r28, 0x529
    18 M addi r0, r5, 1
       B li r5, 1
    19 M stw r0, 0xb4(r31)
       B addi r0, r6, 1
    20 M lfs f1, 0(0)
       B stw r0, 0xb4(r31)
    21 M lfs f0, 4(r4)
       B lfs f1, 4(r3)
    22 M fneg f1, f1
       B lfs f0, 0(0)
    23 M fneg f2, f0
       B fneg f1, f1
    24 M bl 0
       B fneg f0, f0
    25 M lwz r3, 0x18(r1)
       B stfs f1, 0xc(r1)
    26 M addi r4, r28, 0x529
       B stfs f0, 8(r1)
    27 M lwz r0, 0x1c(r1)
       B lwz r0, 0xc(r1)
    28 M li r5, 1
       B lwz r3, 8(r1)
    29 M stw r3, 0x10(r1)
       B stw r0, 0x14(r1)
    30 M stw r0, 0x14(r1)
       B stw r3, 0x10(r1)
    31 M lfs f1, 0x10(r1)
       B lfs f0, 0x14(r1)
    32 M lfs f0, 0x14(r1)
       B lfs f1, 0x10(r1)
    33 M stfs f1, 8(r1)
       B stfs f0, 0x1c(r1)
    34 M stfs f0, 0xc(r1)
       B stfs f1, 0x18(r1)
    43 M addi r5, r1, 8
       B addi r5, r1, 0x18
```

- operand evaluation: retained translation pane before unary vector offset: exact False; insns 92/89; differences None; objdiff 61.50562

```text
src 0x170 base 0x164 insns 92/89
--- replace mine 14:15 base 14:15
  M   14 beq 268
  B   14 beq 256
--- insert mine 16:16 base 16:17
  B   16 li r3, 0
--- delete mine 17:18 base 18:18
  M   17 lwz r3, 0x8c(r31)
--- insert mine 21:21 base 21:36
  B   21 lfs f1, 4(r3)
  B   22 lfs f0, 0(0)
  B   23 fneg f1, f1
  B   24 fneg f0, f0
  B   25 stfs f1, 0xc(r1)
  B   26 stfs f0, 8(r1)
  B   27 lwz r0, 0xc(r1)
  B   28 lwz r3, 8(r1)
  B   29 stw r0, 0x14(r1)
  B   30 stw r3, 0x10(r1)
  B   31 lfs f0, 0x14(r1)
  B   32 lfs f1, 0x10(r1)
  B   33 stfs f0, 0x1c(r1)
  B   34 stfs f1, 0x18(r1)
  B   35 lwz r3, 0x8c(r31)
--- replace mine 26:37 base 41:42
  M   26 li r4, 0
  M   27 lfs f1, 0(0)
  M   28 lfs f0, 4(r4)
  M   29 mr r29, r3
  M   30 fneg f1, f1
  M   31 addi r3, r1, 0x10
  M   32 fneg f2, f0
  M   33 bl 0
  M   34 lwz r6, 0(r3)
  M   35 mr r4, r29
  M   36 lwz r0, 4(r3)
  B   41 mr r4, r3
--- replace mine 38:47 base 43:44
  M   38 stw r6, 0x18(r1)
  M   39 addi r5, r1, 0x20
  M   40 stw r0, 0x1c(r1)
  M   41 lfs f1, 0x18(r1)
  M   42 lfs f0, 0x1c(r1)
  M   43 stw r6, 8(r1)
  M   44 stw r0, 0xc(r1)
  M   45 stfs f1, 0x20(r1)
  M   46 stfs f0, 0x24(r1)
  B   43 addi r5, r1, 0x18
```

## src/scene/address/iplAddress: stt_cover_backward__Q33ipl5scene7AddressFv

```text
src 0xc4 base 0xe4 insns 49/57
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 3:5 base 3:5
  M    3 stw r0, 0x24(r1)
  M    4 stw r31, 0x1c(r1)
  B    3 stw r0, 0x34(r1)
  B    4 stw r31, 0x2c(r1)
--- replace mine 11:12 base 11:12
  M   11 beq 112
  B   11 beq 144
--- replace mine 13:15 base 13:15
  M   13 lfs f1, 0(0)
  M   14 lfs f0, 4(r3)
  B   13 lfs f0, 0(0)
  B   14 lfs f1, 4(r3)
--- insert mine 16:16 base 16:18
  B   16 fneg f0, f0
  B   17 addi r4, r4, 0
--- delete mine 17:19 base 19:19
  M   17 addi r4, r4, 0
  M   18 fneg f0, f0
--- replace mine 20:22 base 20:30
  M   20 stfs f1, 8(r1)
  M   21 stfs f0, 0xc(r1)
  B   20 stfs f0, 8(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
  B   28 stfs f1, 0x18(r1)
  B   29 stfs f0, 0x1c(r1)
--- replace mine 30:31 base 38:39
  M   30 addi r5, r1, 8
  B   38 addi r5, r1, 0x18
--- replace mine 44:46 base 52:54
  M   44 lwz r0, 0x24(r1)
  M   45 lwz r31, 0x1c(r1)
  B   52 lwz r0, 0x34(r1)
  B   53 lwz r31, 0x2c(r1)
--- replace mine 47:48 base 55:56
  M   47 addi r1, r1, 0x20
  B   55 addi r1, r1, 0x30
```

- stack copies: named base negation copied to base vector before conversion: exact False; insns 57/57; differences 15; objdiff 77.5614

```text
src 0xe4 base 0xe4 insns 57/57
diffs 15: [13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 38]
    13 M lfs f1, 0(0)
       B lfs f0, 0(0)
    14 M lfs f0, 4(r3)
       B lfs f1, 4(r3)
    15 M addi r3, r1, 0x18
       B lis r4, 0
    16 M fneg f1, f1
       B fneg f0, f0
    17 M fneg f2, f0
       B addi r4, r4, 0
    18 M bl 0
       B fneg f1, f1
    19 M lwz r3, 0x18(r1)
       B li r5, 1
    20 M lis r4, 0
       B stfs f0, 8(r1)
    21 M lwz r0, 0x1c(r1)
       B stfs f1, 0xc(r1)
    22 M addi r4, r4, 0
       B lwz r3, 8(r1)
    23 M stw r3, 0x10(r1)
       B lwz r0, 0xc(r1)
    24 M li r5, 1
       B stw r3, 0x10(r1)
    28 M stfs f1, 8(r1)
       B stfs f1, 0x18(r1)
    29 M stfs f0, 0xc(r1)
       B stfs f0, 0x1c(r1)
    38 M addi r5, r1, 8
       B addi r5, r1, 0x18
```

- stack copies: named base negation copied through raw vector base: exact False; insns 57/57; differences 15; objdiff 77.5614

```text
src 0xe4 base 0xe4 insns 57/57
diffs 15: [13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 38]
    13 M lfs f1, 0(0)
       B lfs f0, 0(0)
    14 M lfs f0, 4(r3)
       B lfs f1, 4(r3)
    15 M addi r3, r1, 0x18
       B lis r4, 0
    16 M fneg f1, f1
       B fneg f0, f0
    17 M fneg f2, f0
       B addi r4, r4, 0
    18 M bl 0
       B fneg f1, f1
    19 M lwz r3, 0x18(r1)
       B li r5, 1
    20 M lis r4, 0
       B stfs f0, 8(r1)
    21 M lwz r0, 0x1c(r1)
       B stfs f1, 0xc(r1)
    22 M addi r4, r4, 0
       B lwz r3, 8(r1)
    23 M stw r3, 0x10(r1)
       B lwz r0, 0xc(r1)
    24 M li r5, 1
       B stw r3, 0x10(r1)
    28 M stfs f1, 8(r1)
       B stfs f1, 0x18(r1)
    29 M stfs f0, 0xc(r1)
       B stfs f0, 0x1c(r1)
    38 M addi r5, r1, 8
       B addi r5, r1, 0x18
```

- operand evaluation: Y-negation first with aggregate copy before conversion: exact False; insns 57/57; differences 7; objdiff 99.87719

```text
src 0xe4 base 0xe4 insns 57/57
diffs 7: [20, 21, 22, 23, 28, 29, 38]
    20 M stfs f0, 0x18(r1)
       B stfs f0, 8(r1)
    21 M stfs f1, 0x1c(r1)
       B stfs f1, 0xc(r1)
    22 M lwz r3, 0x18(r1)
       B lwz r3, 8(r1)
    23 M lwz r0, 0x1c(r1)
       B lwz r0, 0xc(r1)
    28 M stfs f1, 8(r1)
       B stfs f1, 0x18(r1)
    29 M stfs f0, 0xc(r1)
       B stfs f0, 0x1c(r1)
    38 M addi r5, r1, 8
       B addi r5, r1, 0x18
```

## src/iplwww/www_wiisetting: Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue

```text
src 0x984 base 0x984 insns 609/609
diffs 14: [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589, 592, 593]
   252 M li r25, 0
       B li r26, 0
   255 M add r3, r26, r25
       B add r3, r25, r26
   256 M addi r25, r25, 1
       B addi r26, r26, 1
   258 M lwz r26, 0(0)
       B lwz r25, 0(0)
   259 M addi r3, r26, 0x1f
       B addi r3, r25, 0x1f
   261 M cmplw r25, r3
       B cmplw r26, r3
   263 M cmpwi r25, 0x20
       B cmpwi r26, 0x20
   267 M stb r0, 0x5dc(r26)
       B stb r0, 0x5dc(r25)
   269 M add r3, r0, r25
       B add r3, r0, r26
   578 M li r25, 0
       B li r31, 0
   583 M add r3, r25, r3
       B add r3, r31, r3
   589 M addi r0, r25, 0x40
       B addi r0, r31, 0x40
   592 M addi r25, r25, 1
       B addi r31, r31, 1
   593 M cmpwi r25, 0x3b
       B cmpwi r31, 0x3b
```

- loop counter types: unsigned-int security and Europe indices: exact False; insns 609/609; differences 14; objdiff 99.6798

```text
src 0x984 base 0x984 insns 609/609
diffs 14: [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589, 592, 593]
   252 M li r25, 0
       B li r26, 0
   255 M add r3, r26, r25
       B add r3, r25, r26
   256 M addi r25, r25, 1
       B addi r26, r26, 1
   258 M lwz r26, 0(0)
       B lwz r25, 0(0)
   259 M addi r3, r26, 0x1f
       B addi r3, r25, 0x1f
   261 M cmplw r25, r3
       B cmplw r26, r3
   263 M cmplwi r25, 0x20
       B cmpwi r26, 0x20
   267 M stb r0, 0x5dc(r26)
       B stb r0, 0x5dc(r25)
   269 M add r3, r0, r25
       B add r3, r0, r26
   578 M li r25, 0
       B li r31, 0
   583 M add r3, r25, r3
       B add r3, r31, r3
   589 M addi r0, r25, 0x40
       B addi r0, r31, 0x40
   592 M addi r25, r25, 1
       B addi r31, r31, 1
   593 M cmplwi r25, 0x3b
       B cmpwi r31, 0x3b
```

- condition direction: explicit stop condition with post-body character increment: exact False; insns 609/609; differences 18; objdiff 98.56322

```text
src 0x984 base 0x984 insns 609/609
diffs 18: [252, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 267, 269, 578, 583, 589, 592, 593]
   252 M li r25, 0
       B li r26, 0
   254 M lwz r26, 0(0)
       B b 16
   255 M addi r3, r26, 0x1f
       B add r3, r25, r26
   256 M bl 0
       B addi r26, r26, 1
   257 M cmplw r25, r3
       B stb r27, 0x5bc(r3)
   258 M bge 20
       B lwz r25, 0(0)
   259 M add r3, r26, r25
       B addi r3, r25, 0x1f
   260 M addi r25, r25, 1
       B bl 0
   261 M stb r27, 0x5bc(r3)
       B cmplw r26, r3
   262 M b -32
       B blt -28
   263 M cmpwi r25, 0x20
       B cmpwi r26, 0x20
   267 M stb r0, 0x5dc(r26)
       B stb r0, 0x5dc(r25)
   269 M add r3, r0, r25
       B add r3, r0, r26
   578 M li r25, 0
       B li r31, 0
   583 M add r3, r25, r3
       B add r3, r31, r3
   589 M addi r0, r25, 0x40
       B addi r0, r31, 0x40
   592 M addi r25, r25, 1
       B addi r31, r31, 1
   593 M cmpwi r25, 0x3b
       B cmpwi r31, 0x3b
```

- local lifetimes: security buffer and character counter declared at getter entry: exact False; insns 609/609; differences 14; objdiff 99.86043

```text
src 0x984 base 0x984 insns 609/609
diffs 14: [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589, 592, 593]
   252 M li r25, 0
       B li r26, 0
   255 M add r3, r26, r25
       B add r3, r25, r26
   256 M addi r25, r25, 1
       B addi r26, r26, 1
   258 M lwz r26, 0(0)
       B lwz r25, 0(0)
   259 M addi r3, r26, 0x1f
       B addi r3, r25, 0x1f
   261 M cmplw r25, r3
       B cmplw r26, r3
   263 M cmpwi r25, 0x20
       B cmpwi r26, 0x20
   267 M stb r0, 0x5dc(r26)
       B stb r0, 0x5dc(r25)
   269 M add r3, r0, r25
       B add r3, r0, r26
   578 M li r25, 0
       B li r31, 0
   583 M add r3, r25, r3
       B add r3, r31, r3
   589 M addi r0, r25, 0x40
       B addi r0, r31, 0x40
   592 M addi r25, r25, 1
       B addi r31, r31, 1
   593 M cmpwi r25, 0x3b
       B cmpwi r31, 0x3b
```

## src/scene/address/iplAddress: stt_cover_backward__Q33ipl5scene7AddressFv

```text
src 0xc4 base 0xe4 insns 49/57
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 3:5 base 3:5
  M    3 stw r0, 0x24(r1)
  M    4 stw r31, 0x1c(r1)
  B    3 stw r0, 0x34(r1)
  B    4 stw r31, 0x2c(r1)
--- replace mine 11:12 base 11:12
  M   11 beq 112
  B   11 beq 144
--- replace mine 13:15 base 13:15
  M   13 lfs f1, 0(0)
  M   14 lfs f0, 4(r3)
  B   13 lfs f0, 0(0)
  B   14 lfs f1, 4(r3)
--- insert mine 16:16 base 16:18
  B   16 fneg f0, f0
  B   17 addi r4, r4, 0
--- delete mine 17:19 base 19:19
  M   17 addi r4, r4, 0
  M   18 fneg f0, f0
--- replace mine 20:22 base 20:30
  M   20 stfs f1, 8(r1)
  M   21 stfs f0, 0xc(r1)
  B   20 stfs f0, 8(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
  B   28 stfs f1, 0x18(r1)
  B   29 stfs f0, 0x1c(r1)
--- replace mine 30:31 base 38:39
  M   30 addi r5, r1, 8
  B   38 addi r5, r1, 0x18
--- replace mine 44:46 base 52:54
  M   44 lwz r0, 0x24(r1)
  M   45 lwz r31, 0x1c(r1)
  B   52 lwz r0, 0x34(r1)
  B   53 lwz r31, 0x2c(r1)
--- replace mine 47:48 base 55:56
  M   47 addi r1, r1, 0x20
  B   55 addi r1, r1, 0x30
```

- stack declaration order: final offset before copied and negated base vectors: exact False; insns 55/57; differences None; objdiff 82.2807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 18:19 base 18:19
  M   18 fneg f2, f1
  B   18 fneg f1, f1
--- delete mine 20:21 base 20:20
  M   20 frsp f1, f0
--- replace mine 22:24 base 21:28
  M   22 frsp f0, f2
  M   23 stfs f2, 0xc(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x10(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x14(r1)
```

- stack declaration order: copied vector before final offset and negation: exact False; insns 55/57; differences None; objdiff 82.22807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 18:19 base 18:19
  M   18 fneg f2, f1
  B   18 fneg f1, f1
--- delete mine 20:21 base 20:20
  M   20 frsp f1, f0
--- replace mine 22:26 base 21:30
  M   22 frsp f0, f2
  M   23 stfs f2, 0xc(r1)
  M   24 stfs f1, 0x10(r1)
  M   25 stfs f0, 0x14(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
  B   28 stfs f1, 0x18(r1)
  B   29 stfs f0, 0x1c(r1)
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x18(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x1c(r1)
--- replace mine 36:37 base 38:39
  M   36 addi r5, r1, 0x10
  B   38 addi r5, r1, 0x18
```

- conversion boundary: raw base assignment of copied vector to retained offset: exact False; insns 55/57; differences None; objdiff 82.2807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 18:19 base 18:19
  M   18 fneg f2, f1
  B   18 fneg f1, f1
--- delete mine 20:21 base 20:20
  M   20 frsp f1, f0
--- replace mine 22:24 base 21:28
  M   22 frsp f0, f2
  M   23 stfs f2, 0xc(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x10(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x14(r1)
```

## src/scene/address/iplAddress: onPreviousPage__Q33ipl5scene7AddressFv

```text
src 0x284 base 0x294 insns 161/165
--- replace mine 14:15 base 14:15
  M   14 b 564
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 552
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 348
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 272
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:102 base 99:102
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0xc(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
--- insert mine 103:103 base 103:107
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- replace mine 111:112 base 115:116
  M  111 addi r5, r1, 8
  B  115 addi r5, r1, 0x10
```

- stack order: offset before product and base-vector copy assignment: exact False; insns 163/165; differences None; objdiff 96.88485

```text
src 0x28c base 0x294 insns 163/165
--- replace mine 14:15 base 14:15
  M   14 b 572
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 560
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 356
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 280
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:103 base 99:107
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0x14(r1)
  M  102 stfs f0, 0x10(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
  B  102 stfs f0, 8(r1)
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- delete mine 104:105 base 108:108
  M  104 stfs f1, 0xc(r1)
--- delete mine 106:107 base 109:109
  M  106 stfs f0, 8(r1)
```

- operand order: scalar first in product with retained offset: exact False; insns 163/165; differences None; objdiff 96.88485

```text
src 0x28c base 0x294 insns 163/165
--- replace mine 14:15 base 14:15
  M   14 b 572
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 560
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 356
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 280
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:103 base 99:107
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0x14(r1)
  M  102 stfs f0, 0x10(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
  B  102 stfs f0, 8(r1)
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- delete mine 104:105 base 108:108
  M  104 stfs f1, 0xc(r1)
--- delete mine 106:107 base 109:109
  M  106 stfs f0, 8(r1)
```

- float temporary: page scale named before product and aggregate assignment: exact False; insns 163/165; differences None; objdiff 96.854546

```text
src 0x28c base 0x294 insns 163/165
--- replace mine 14:15 base 14:15
  M   14 b 572
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 560
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 356
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 280
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:103 base 99:107
  M   99 fmuls f1, f1, f2
  M  100 fmuls f0, f0, f2
  M  101 stfs f1, 0x14(r1)
  M  102 stfs f0, 0x10(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
  B  102 stfs f0, 8(r1)
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- delete mine 104:105 base 108:108
  M  104 stfs f1, 0xc(r1)
--- delete mine 106:107 base 109:109
  M  106 stfs f0, 8(r1)
```

## src/scene/address/iplAddress: movePane_onDrag__Q33ipl5scene7AddressFv

```text
src 0x268 base 0x26c insns 154/155
--- replace mine 34:36 base 34:36
  M   34 lwz r6, 0x8c(r31)
  M   35 lis r7, 0
  B   34 lwz r7, 0x8c(r31)
  B   35 lis r6, 0
--- replace mine 39:40 base 39:40
  M   39 lwz r3, 0x14(r6)
  B   39 lwz r3, 0x14(r7)
--- replace mine 43:44 base 43:44
  M   43 addi r4, r7, 0
  B   43 addi r4, r6, 0
--- replace mine 50:51 base 50:51
  M   50 mr r28, r3
  B   50 mr r27, r3
--- replace mine 56:61 base 56:62
  M   56 add r27, r5, r0
  M   57 addi r27, r27, 8
  M   58 beq 112
  M   59 cmpwi r27, 0
  M   60 beq 104
  B   56 add r0, r5, r0
  B   57 bne 8
  B   58 b 124
  B   59 addic. r29, r0, 8
  B   60 bne 8
  B   61 b 112
--- replace mine 69:70 base 70:71
  M   69 mr r3, r28
  B   70 mr r3, r27
--- replace mine 72:73 base 73:74
  M   72 mr r4, r29
  B   73 mr r4, r28
--- replace mine 78:79 base 79:80
  M   78 addi r27, r27, 2
  B   79 addi r29, r29, 2
--- replace mine 83:85 base 84:86
  M   83 lhz r29, 0(r27)
  M   84 cmpwi r29, 0
  B   84 lhz r28, 0(r29)
  B   85 cmpwi r28, 0
--- insert mine 87:87 base 88:89
  B   88 fadds f30, f0, f30
--- delete mine 88:89 base 90:90
  M   88 fadds f30, f30, f0
--- replace mine 108:110 base 109:111
  M  108 fmuls f0, f5, f0
  M  109 fneg f0, f0
  B  109 fmuls f5, f5, f0
  B  110 fneg f0, f5
```

- valid font boundary: name-first condition and const font local: exact False; insns 154/155; differences None; objdiff 89.55484

```text
src 0x268 base 0x26c insns 154/155
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x80(r1)
  B    0 stwu r1, -0x90(r1)
--- replace mine 2:8 base 2:8
  M    2 stw r0, 0x84(r1)
  M    3 stfd f31, 0x70(r1)
  M    4 xxsel vs31, vs1, vs0, v1
  M    5 stfd f30, 0x60(r1)
  M    6 .long f3c10068
  M    7 addi r11, r1, 0x60
  B    2 stw r0, 0x94(r1)
  B    3 stfd f31, 0x80(r1)
  B    4 xsmsubasp f31, f1, f0
  B    5 stfd f30, 0x70(r1)
  B    6 xxsel vs30, vs1, vs0, v1
  B    7 addi r11, r1, 0x70
--- replace mine 34:36 base 34:36
  M   34 lwz r6, 0x8c(r31)
  M   35 lis r7, 0
  B   34 lwz r7, 0x8c(r31)
  B   35 lis r6, 0
--- replace mine 39:40 base 39:40
  M   39 lwz r3, 0x14(r6)
  B   39 lwz r3, 0x14(r7)
--- replace mine 43:44 base 43:44
  M   43 addi r4, r7, 0
  B   43 addi r4, r6, 0
--- replace mine 48:49 base 48:49
  M   48 mr r30, r3
  B   48 cmpwi r3, 0
--- insert mine 50:50 base 50:51
  B   50 mr r27, r3
--- replace mine 55:60 base 56:62
  M   55 add r29, r5, r0
  M   56 addic. r29, r29, 8
  M   57 beq 116
  M   58 cmpwi r3, 0
  M   59 beq 108
  B   56 add r0, r5, r0
  B   57 bne 8
  B   58 b 124
  B   59 addic. r29, r0, 8
  B   60 bne 8
  B   61 b 112
--- replace mine 65:66 base 67:71
  M   65 mr r3, r30
  B   67 lfd f31, 0(0)
  B   68 lis r30, 0x4330
  B   69 b 60
  B   70 mr r3, r27
--- replace mine 67:73 base 72:74
  M   67 lfd f31, 0(0)
  M   68 mr r28, r3
  M   69 lis r30, 0x4330
  M   70 b 52
  M   71 lwz r12, 0(r28)
  M   72 mr r3, r28
  B   72 lwz r12, 0(r3)
  B   73 mr r4, r28
--- replace mine 83:86 base 84:87
  M   83 lhz r4, 0(r29)
  M   84 cmpwi r4, 0
  M   85 bne -56
  B   84 lhz r28, 0(r29)
  B   85 cmpwi r28, 0
  B   86 bne -64
--- insert mine 87:87 base 88:89
  B   88 fadds f30, f0, f30
--- delete mine 88:89 base 90:90
  M   88 fadds f30, f30, f0
--- replace mine 108:110 base 109:111
  M  108 fmuls f0, f5, f0
  M  109 fneg f0, f0
  B  109 fmuls f5, f5, f0
  B  110 fneg f0, f5
--- replace mine 144:149 base 145:150
  M  144 .long e3e10078
  M  145 lfd f31, 0x70(r1)
  M  146 .long e3c10068
  M  147 addi r11, r1, 0x60
  M  148 lfd f30, 0x60(r1)
  B  145 .long e3e10088
  B  146 lfd f31, 0x80(r1)
  B  147 .long e3c10078
  B  148 addi r11, r1, 0x70
  B  149 lfd f30, 0x70(r1)
--- replace mine 150:151 base 151:152
  M  150 lwz r0, 0x84(r1)
  B  151 lwz r0, 0x94(r1)
--- replace mine 152:153 base 153:154
  M  152 addi r1, r1, 0x80
  B  153 addi r1, r1, 0x90
```

## src/scene/address/iplAddress: update__Q33ipl5scene15FriendListCacheFUlPCwUx

```text
src 0x90 base 0xa0 insns 36/40
--- replace mine 6:8 base 6:10
  M    6 mr r29, r4
  M    7 mr r30, r5
  B    6 mr r29, r3
  B    7 mr r30, r4
  B    8 mr r31, r5
  B    9 add r3, r3, r0
--- replace mine 9:10 base 11:12
  M    9 add r31, r3, r0
  B   11 stw r8, 0x24(r3)
--- replace mine 11:14 base 13:15
  M   11 stw r8, 0x24(r31)
  M   12 addi r3, r31, 8
  M   13 stw r7, 0x20(r31)
  B   13 stw r7, 0x20(r3)
  B   14 addi r3, r3, 8
--- replace mine 15:17 base 16:18
  M   15 mr r4, r30
  M   16 addi r3, r31, 8
  B   16 mulli r0, r30, 0x140
  B   17 mr r4, r31
--- insert mine 18:18 base 19:21
  B   19 add r3, r29, r0
  B   20 addi r3, r3, 8
--- replace mine 27:29 base 30:33
  M   27 mr r4, r31
  M   28 mr r5, r29
  B   30 mulli r0, r30, 0x140
  B   31 mr r5, r30
  B   32 add r4, r29, r0
```

- inline boundaries: writable reference through getInfo at each operation: exact False; insns 37/40; differences None; objdiff 78.475

```text
src 0x94 base 0xa0 insns 37/40
--- replace mine 6:8 base 6:10
  M    6 mr r28, r4
  M    7 mr r29, r5
  B    6 mr r29, r3
  B    7 mr r30, r4
  B    8 mr r31, r5
  B    9 add r3, r3, r0
--- replace mine 9:10 base 11:12
  M    9 add r31, r3, r0
  B   11 stw r8, 0x24(r3)
--- replace mine 11:15 base 13:15
  M   11 stw r8, 0x24(r31)
  M   12 addi r30, r31, 8
  M   13 mr r3, r30
  M   14 stw r7, 0x20(r31)
  B   13 stw r7, 0x20(r3)
  B   14 addi r3, r3, 8
--- replace mine 16:18 base 16:18
  M   16 mr r3, r30
  M   17 mr r4, r29
  B   16 mulli r0, r30, 0x140
  B   17 mr r4, r31
--- insert mine 19:19 base 19:21
  B   19 add r3, r29, r0
  B   20 addi r3, r3, 8
--- replace mine 28:30 base 30:33
  M   28 mr r4, r31
  M   29 mr r5, r28
  B   30 mulli r0, r30, 0x140
  B   31 mr r5, r30
  B   32 add r4, r29, r0
```

- operand ordering: name copy index cast through signed-int getter: exact False; insns 37/40; differences None; objdiff 78.475

```text
src 0x94 base 0xa0 insns 37/40
--- replace mine 6:8 base 6:10
  M    6 mr r28, r4
  M    7 mr r29, r5
  B    6 mr r29, r3
  B    7 mr r30, r4
  B    8 mr r31, r5
  B    9 add r3, r3, r0
--- replace mine 9:10 base 11:12
  M    9 add r31, r3, r0
  B   11 stw r8, 0x24(r3)
--- replace mine 11:15 base 13:15
  M   11 stw r8, 0x24(r31)
  M   12 addi r30, r31, 8
  M   13 mr r3, r30
  M   14 stw r7, 0x20(r31)
  B   13 stw r7, 0x20(r3)
  B   14 addi r3, r3, 8
--- replace mine 16:18 base 16:18
  M   16 mr r3, r30
  M   17 mr r4, r29
  B   16 mulli r0, r30, 0x140
  B   17 mr r4, r31
--- insert mine 19:19 base 19:21
  B   19 add r3, r29, r0
  B   20 addi r3, r3, 8
--- replace mine 28:30 base 30:33
  M   28 mr r4, r31
  M   29 mr r5, r28
  B   30 mulli r0, r30, 0x140
  B   31 mr r5, r30
  B   32 add r4, r29, r0
```

- local identity: name pointer reference and signed-int friend index: exact False; insns 37/40; differences None; objdiff 78.6

```text
src 0x94 base 0xa0 insns 37/40
--- replace mine 6:8 base 6:10
  M    6 mr r29, r4
  M    7 mr r28, r5
  B    6 mr r29, r3
  B    7 mr r30, r4
  B    8 mr r31, r5
  B    9 add r3, r3, r0
--- replace mine 9:10 base 11:12
  M    9 add r31, r3, r0
  B   11 stw r8, 0x24(r3)
--- replace mine 11:15 base 13:15
  M   11 stw r8, 0x24(r31)
  M   12 addi r30, r31, 8
  M   13 mr r3, r30
  M   14 stw r7, 0x20(r31)
  B   13 stw r7, 0x20(r3)
  B   14 addi r3, r3, 8
--- replace mine 16:18 base 16:18
  M   16 mr r3, r30
  M   17 mr r4, r28
  B   16 mulli r0, r30, 0x140
  B   17 mr r4, r31
--- insert mine 19:19 base 19:21
  B   19 add r3, r29, r0
  B   20 addi r3, r3, 8
--- replace mine 28:30 base 30:33
  M   28 mr r4, r31
  M   29 mr r5, r29
  B   30 mulli r0, r30, 0x140
  B   31 mr r5, r30
  B   32 add r4, r29, r0
```

## src/scene/cardSequence/iplCardSequence: CardSequence_813D2C8C

```text
src 0x4b4 base 0x4b4 insns 301/301
diffs 78: [6, 9, 11, 17, 33, 34, 48, 49, 50, 54, 57, 58, 60, 62, 67, 72, 75, 77, 79, 80]
     6 M li r26, 0
       B li r24, 0
     9 M stw r26, 0xc18(r3)
       B stw r24, 0xc18(r3)
    11 M lis r22, -0x8000
       B lis r21, -0x8000
    17 M stw r26, 0xc1c(r3)
       B stw r24, 0xc1c(r3)
    33 M clrlwi r23, r4, 0x18
       B clrlwi r19, r4, 0x18
    34 M extsb r5, r23
       B extsb r5, r19
    48 M rlwimi r23, r29, 8, 0x10, 0x17
       B mr r4, r19
    49 M li r5, 1
       B rlwimi r4, r25, 8, 0x10, 0x17
    50 M mr r4, r23
       B li r5, 1
    54 M li r26, 1
       B li r24, 1
    57 M rlwinm r23, r4, 0x12, 0x1d, 0x1d
       B rlwinm r19, r4, 0x12, 0x1d, 0x1d
    58 M rlwinm r21, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
    60 M add r3, r0, r23
       B add r3, r0, r19
    62 M mr r3, r21
       B mr r3, r22
    67 M mr r3, r21
       B mr r3, r22
    72 M mr r3, r21
       B mr r3, r22
    75 M mr r24, r3
       B mr r20, r3
    77 M mr r3, r21
       B mr r3, r22
    79 M li r20, 0
       B li r23, 0
    80 M mr r3, r21
       B mr r3, r22
    81 M extsh r4, r20
       B extsh r4, r23
    87 M mr r3, r21
       B mr r3, r22
   121 M mr r3, r21
       B mr r3, r22
   122 M extsh r4, r20
       B extsh r4, r23
   125 M mr r24, r3
       B mr r20, r3
   128 M mr r3, r21
       B mr r3, r22
   129 M extsh r4, r20
       B extsh r4, r23
   133 M mr r24, r3
       B mr r20, r3
   135 M addi r20, r20, 1
       B addi r23, r23, 1
   136 M cmpwi r20, 0x7f
       B cmpwi r23, 0x7f
   138 M mr r3, r21
       B mr r3, r22
   141 M mr r3, r21
       B mr r3, r22
   144 M add r6, r0, r23
       B add r6, r0, r19
   147 M lbzx r4, r30, r21
       B lbzx r4, r30, r22
   152 M li r20, 0
       B li r23, 0
   153 M mr r3, r21
       B mr r3, r22
   154 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   166 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   170 M addi r20, r20, 1
       B addi r23, r23, 1
   171 M cmplwi r20, 0x7f
       B cmplwi r23, 0x7f
   177 M mr r3, r21
       B mr r3, r22
   178 M mr r5, r24
       B mr r5, r20
   187 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   188 M mr r3, r23
       B mr r3, r22
   193 M mr r3, r23
       B mr r3, r22
   198 M rlwinm r0, r23, 2, 0x16, 0x1d
       B rlwinm r0, r22, 2, 0x16, 0x1d
   199 M mr r3, r23
       B mr r3, r22
   203 M mr r3, r23
       B mr r3, r22
   219 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   220 M extsh r24, r0
       B extsh r23, r0
   221 M mr r3, r23
       B mr r3, r22
   222 M mr r4, r24
       B mr r4, r23
   227 M mr r3, r23
       B mr r3, r22
   231 M mr r3, r23
       B mr r3, r22
   232 M mr r4, r24
       B mr r4, r23
   234 M mr r3, r23
       B mr r3, r22
   236 M mr r3, r23
       B mr r3, r22
   237 M clrlwi r5, r24, 0x18
       B clrlwi r5, r23, 0x18
   241 M li r20, 0
       B li r26, 0
   242 M li r24, 0
       B li r23, 0
   243 M li r23, 0
       B li r22, 0
   245 M add r3, r0, r23
       B add r3, r0, r22
   249 M li r19, 0
       B li r20, 0
   250 M li r21, 0
       B li r19, 0
   251 M mr r3, r20
       B mr r3, r26
   252 M mr r4, r21
       B mr r4, r19
   259 M li r19, -1
       B li r20, -1
   270 M addi r4, r22, 4
       B addi r4, r21, 4
   276 M add r19, r19, r0
       B add r20, r20, r0
   277 M addi r21, r21, 1
       B addi r19, r19, 1
   278 M cmpwi r21, 0x7f
       B cmpwi r19, 0x7f
   281 M add r3, r0, r24
       B add r3, r0, r23
   282 M sth r19, 0x12(r3)
       B sth r20, 0x12(r3)
   283 M addi r20, r20, 1
       B addi r26, r26, 1
   284 M addi r23, r23, 4
       B addi r22, r22, 4
   285 M cmpwi r20, 2
       B cmpwi r26, 2
   286 M addi r24, r24, 0x14
       B addi r23, r23, 0x14
   292 M cmpwi r26, 0
       B cmpwi r24, 0
```

- local register types: native int status and scan counters: exact False; insns 301/301; differences 78; objdiff 97.9402

```text
src 0x4b4 base 0x4b4 insns 301/301
diffs 78: [6, 9, 11, 17, 33, 34, 48, 49, 50, 54, 57, 58, 60, 62, 67, 72, 75, 77, 79, 80]
     6 M li r26, 0
       B li r24, 0
     9 M stw r26, 0xc18(r3)
       B stw r24, 0xc18(r3)
    11 M lis r22, -0x8000
       B lis r21, -0x8000
    17 M stw r26, 0xc1c(r3)
       B stw r24, 0xc1c(r3)
    33 M clrlwi r23, r4, 0x18
       B clrlwi r19, r4, 0x18
    34 M extsb r5, r23
       B extsb r5, r19
    48 M rlwimi r23, r29, 8, 0x10, 0x17
       B mr r4, r19
    49 M li r5, 1
       B rlwimi r4, r25, 8, 0x10, 0x17
    50 M mr r4, r23
       B li r5, 1
    54 M li r26, 1
       B li r24, 1
    57 M rlwinm r23, r4, 0x12, 0x1d, 0x1d
       B rlwinm r19, r4, 0x12, 0x1d, 0x1d
    58 M rlwinm r21, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
    60 M add r3, r0, r23
       B add r3, r0, r19
    62 M mr r3, r21
       B mr r3, r22
    67 M mr r3, r21
       B mr r3, r22
    72 M mr r3, r21
       B mr r3, r22
    75 M mr r24, r3
       B mr r20, r3
    77 M mr r3, r21
       B mr r3, r22
    79 M li r20, 0
       B li r23, 0
    80 M mr r3, r21
       B mr r3, r22
    81 M extsh r4, r20
       B extsh r4, r23
    87 M mr r3, r21
       B mr r3, r22
   121 M mr r3, r21
       B mr r3, r22
   122 M extsh r4, r20
       B extsh r4, r23
   125 M mr r24, r3
       B mr r20, r3
   128 M mr r3, r21
       B mr r3, r22
   129 M extsh r4, r20
       B extsh r4, r23
   133 M mr r24, r3
       B mr r20, r3
   135 M addi r20, r20, 1
       B addi r23, r23, 1
   136 M cmpwi r20, 0x7f
       B cmpwi r23, 0x7f
   138 M mr r3, r21
       B mr r3, r22
   141 M mr r3, r21
       B mr r3, r22
   144 M add r6, r0, r23
       B add r6, r0, r19
   147 M lbzx r4, r30, r21
       B lbzx r4, r30, r22
   152 M li r20, 0
       B li r23, 0
   153 M mr r3, r21
       B mr r3, r22
   154 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   166 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   170 M addi r20, r20, 1
       B addi r23, r23, 1
   171 M cmplwi r20, 0x7f
       B cmplwi r23, 0x7f
   177 M mr r3, r21
       B mr r3, r22
   178 M mr r5, r24
       B mr r5, r20
   187 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   188 M mr r3, r23
       B mr r3, r22
   193 M mr r3, r23
       B mr r3, r22
   198 M rlwinm r0, r23, 2, 0x16, 0x1d
       B rlwinm r0, r22, 2, 0x16, 0x1d
   199 M mr r3, r23
       B mr r3, r22
   203 M mr r3, r23
       B mr r3, r22
   219 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   220 M extsh r24, r0
       B extsh r23, r0
   221 M mr r3, r23
       B mr r3, r22
   222 M mr r4, r24
       B mr r4, r23
   227 M mr r3, r23
       B mr r3, r22
   231 M mr r3, r23
       B mr r3, r22
   232 M mr r4, r24
       B mr r4, r23
   234 M mr r3, r23
       B mr r3, r22
   236 M mr r3, r23
       B mr r3, r22
   237 M clrlwi r5, r24, 0x18
       B clrlwi r5, r23, 0x18
   241 M li r20, 0
       B li r26, 0
   242 M li r24, 0
       B li r23, 0
   243 M li r23, 0
       B li r22, 0
   245 M add r3, r0, r23
       B add r3, r0, r22
   249 M li r19, 0
       B li r20, 0
   250 M li r21, 0
       B li r19, 0
   251 M mr r3, r20
       B mr r3, r26
   252 M mr r4, r21
       B mr r4, r19
   259 M li r19, -1
       B li r20, -1
   270 M addi r4, r22, 4
       B addi r4, r21, 4
   276 M add r19, r19, r0
       B add r20, r20, r0
   277 M addi r21, r21, 1
       B addi r19, r19, 1
   278 M cmpwi r21, 0x7f
       B cmpwi r19, 0x7f
   281 M add r3, r0, r24
       B add r3, r0, r23
   282 M sth r19, 0x12(r3)
       B sth r20, 0x12(r3)
   283 M addi r20, r20, 1
       B addi r26, r26, 1
   284 M addi r23, r23, 4
       B addi r22, r22, 4
   285 M cmpwi r20, 2
       B cmpwi r26, 2
   286 M addi r24, r24, 0x14
       B addi r23, r23, 0x14
   292 M cmpwi r26, 0
       B cmpwi r24, 0
```

- loop-counter identity: one unsigned file number for mount and listing scans: exact False; insns 301/301; differences 73; objdiff 98.03986

```text
src 0x4b4 base 0x4b4 insns 301/301
diffs 73: [6, 9, 11, 17, 33, 34, 48, 49, 50, 54, 57, 58, 60, 62, 67, 72, 75, 77, 79, 80]
     6 M li r26, 0
       B li r24, 0
     9 M stw r26, 0xc18(r3)
       B stw r24, 0xc18(r3)
    11 M lis r22, -0x8000
       B lis r21, -0x8000
    17 M stw r26, 0xc1c(r3)
       B stw r24, 0xc1c(r3)
    33 M clrlwi r23, r4, 0x18
       B clrlwi r19, r4, 0x18
    34 M extsb r5, r23
       B extsb r5, r19
    48 M rlwimi r23, r29, 8, 0x10, 0x17
       B mr r4, r19
    49 M li r5, 1
       B rlwimi r4, r25, 8, 0x10, 0x17
    50 M mr r4, r23
       B li r5, 1
    54 M li r26, 1
       B li r24, 1
    57 M rlwinm r23, r4, 0x12, 0x1d, 0x1d
       B rlwinm r19, r4, 0x12, 0x1d, 0x1d
    58 M rlwinm r21, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
    60 M add r3, r0, r23
       B add r3, r0, r19
    62 M mr r3, r21
       B mr r3, r22
    67 M mr r3, r21
       B mr r3, r22
    72 M mr r3, r21
       B mr r3, r22
    75 M mr r24, r3
       B mr r20, r3
    77 M mr r3, r21
       B mr r3, r22
    79 M li r20, 0
       B li r23, 0
    80 M mr r3, r21
       B mr r3, r22
    81 M extsh r4, r20
       B extsh r4, r23
    87 M mr r3, r21
       B mr r3, r22
   121 M mr r3, r21
       B mr r3, r22
   122 M extsh r4, r20
       B extsh r4, r23
   125 M mr r24, r3
       B mr r20, r3
   128 M mr r3, r21
       B mr r3, r22
   129 M extsh r4, r20
       B extsh r4, r23
   133 M mr r24, r3
       B mr r20, r3
   135 M addi r20, r20, 1
       B addi r23, r23, 1
   136 M cmpwi r20, 0x7f
       B cmpwi r23, 0x7f
   138 M mr r3, r21
       B mr r3, r22
   141 M mr r3, r21
       B mr r3, r22
   144 M add r6, r0, r23
       B add r6, r0, r19
   147 M lbzx r4, r30, r21
       B lbzx r4, r30, r22
   153 M mr r3, r21
       B mr r3, r22
   177 M mr r3, r21
       B mr r3, r22
   178 M mr r5, r24
       B mr r5, r20
   187 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   188 M mr r3, r23
       B mr r3, r22
   193 M mr r3, r23
       B mr r3, r22
   198 M rlwinm r0, r23, 2, 0x16, 0x1d
       B rlwinm r0, r22, 2, 0x16, 0x1d
   199 M mr r3, r23
       B mr r3, r22
   203 M mr r3, r23
       B mr r3, r22
   219 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   220 M extsh r24, r0
       B extsh r23, r0
   221 M mr r3, r23
       B mr r3, r22
   222 M mr r4, r24
       B mr r4, r23
   227 M mr r3, r23
       B mr r3, r22
   231 M mr r3, r23
       B mr r3, r22
   232 M mr r4, r24
       B mr r4, r23
   234 M mr r3, r23
       B mr r3, r22
   236 M mr r3, r23
       B mr r3, r22
   237 M clrlwi r5, r24, 0x18
       B clrlwi r5, r23, 0x18
   241 M li r20, 0
       B li r26, 0
   242 M li r24, 0
       B li r23, 0
   243 M li r23, 0
       B li r22, 0
   245 M add r3, r0, r23
       B add r3, r0, r22
   249 M li r19, 0
       B li r20, 0
   250 M li r21, 0
       B li r19, 0
   251 M mr r3, r20
       B mr r3, r26
   252 M mr r4, r21
       B mr r4, r19
   259 M li r19, -1
       B li r20, -1
   270 M addi r4, r22, 4
       B addi r4, r21, 4
   276 M add r19, r19, r0
       B add r20, r20, r0
   277 M addi r21, r21, 1
       B addi r19, r19, 1
   278 M cmpwi r21, 0x7f
       B cmpwi r19, 0x7f
   281 M add r3, r0, r24
       B add r3, r0, r23
   282 M sth r19, 0x12(r3)
       B sth r20, 0x12(r3)
   283 M addi r20, r20, 1
       B addi r26, r26, 1
   284 M addi r23, r23, 4
       B addi r22, r22, 4
   285 M cmpwi r20, 2
       B cmpwi r26, 2
   286 M addi r24, r24, 0x14
       B addi r23, r23, 0x14
   292 M cmpwi r26, 0
       B cmpwi r24, 0
```

- inline-response boundary: explicit union value passed without command reuse: exact False; insns 301/301; differences 78; objdiff 97.9402

```text
src 0x4b4 base 0x4b4 insns 301/301
diffs 78: [6, 9, 11, 17, 33, 34, 48, 49, 50, 54, 57, 58, 60, 62, 67, 72, 75, 77, 79, 80]
     6 M li r26, 0
       B li r24, 0
     9 M stw r26, 0xc18(r3)
       B stw r24, 0xc18(r3)
    11 M lis r22, -0x8000
       B lis r21, -0x8000
    17 M stw r26, 0xc1c(r3)
       B stw r24, 0xc1c(r3)
    33 M clrlwi r23, r4, 0x18
       B clrlwi r19, r4, 0x18
    34 M extsb r5, r23
       B extsb r5, r19
    48 M rlwimi r23, r29, 8, 0x10, 0x17
       B mr r4, r19
    49 M li r5, 1
       B rlwimi r4, r25, 8, 0x10, 0x17
    50 M mr r4, r23
       B li r5, 1
    54 M li r26, 1
       B li r24, 1
    57 M rlwinm r23, r4, 0x12, 0x1d, 0x1d
       B rlwinm r19, r4, 0x12, 0x1d, 0x1d
    58 M rlwinm r21, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
    60 M add r3, r0, r23
       B add r3, r0, r19
    62 M mr r3, r21
       B mr r3, r22
    67 M mr r3, r21
       B mr r3, r22
    72 M mr r3, r21
       B mr r3, r22
    75 M mr r24, r3
       B mr r20, r3
    77 M mr r3, r21
       B mr r3, r22
    79 M li r20, 0
       B li r23, 0
    80 M mr r3, r21
       B mr r3, r22
    81 M extsh r4, r20
       B extsh r4, r23
    87 M mr r3, r21
       B mr r3, r22
   121 M mr r3, r21
       B mr r3, r22
   122 M extsh r4, r20
       B extsh r4, r23
   125 M mr r24, r3
       B mr r20, r3
   128 M mr r3, r21
       B mr r3, r22
   129 M extsh r4, r20
       B extsh r4, r23
   133 M mr r24, r3
       B mr r20, r3
   135 M addi r20, r20, 1
       B addi r23, r23, 1
   136 M cmpwi r20, 0x7f
       B cmpwi r23, 0x7f
   138 M mr r3, r21
       B mr r3, r22
   141 M mr r3, r21
       B mr r3, r22
   144 M add r6, r0, r23
       B add r6, r0, r19
   147 M lbzx r4, r30, r21
       B lbzx r4, r30, r22
   152 M li r20, 0
       B li r23, 0
   153 M mr r3, r21
       B mr r3, r22
   154 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   166 M clrlwi r4, r20, 0x10
       B clrlwi r4, r23, 0x10
   170 M addi r20, r20, 1
       B addi r23, r23, 1
   171 M cmplwi r20, 0x7f
       B cmplwi r23, 0x7f
   177 M mr r3, r21
       B mr r3, r22
   178 M mr r5, r24
       B mr r5, r20
   187 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   188 M mr r3, r23
       B mr r3, r22
   193 M mr r3, r23
       B mr r3, r22
   198 M rlwinm r0, r23, 2, 0x16, 0x1d
       B rlwinm r0, r22, 2, 0x16, 0x1d
   199 M mr r3, r23
       B mr r3, r22
   203 M mr r3, r23
       B mr r3, r22
   219 M rlwinm r23, r4, 0x10, 0x1f, 0x1f
       B rlwinm r22, r4, 0x10, 0x1f, 0x1f
   220 M extsh r24, r0
       B extsh r23, r0
   221 M mr r3, r23
       B mr r3, r22
   222 M mr r4, r24
       B mr r4, r23
   227 M mr r3, r23
       B mr r3, r22
   231 M mr r3, r23
       B mr r3, r22
   232 M mr r4, r24
       B mr r4, r23
   234 M mr r3, r23
       B mr r3, r22
   236 M mr r3, r23
       B mr r3, r22
   237 M clrlwi r5, r24, 0x18
       B clrlwi r5, r23, 0x18
   241 M li r20, 0
       B li r26, 0
   242 M li r24, 0
       B li r23, 0
   243 M li r23, 0
       B li r22, 0
   245 M add r3, r0, r23
       B add r3, r0, r22
   249 M li r19, 0
       B li r20, 0
   250 M li r21, 0
       B li r19, 0
   251 M mr r3, r20
       B mr r3, r26
   252 M mr r4, r21
       B mr r4, r19
   259 M li r19, -1
       B li r20, -1
   270 M addi r4, r22, 4
       B addi r4, r21, 4
   276 M add r19, r19, r0
       B add r20, r20, r0
   277 M addi r21, r21, 1
       B addi r19, r19, 1
   278 M cmpwi r21, 0x7f
       B cmpwi r19, 0x7f
   281 M add r3, r0, r24
       B add r3, r0, r23
   282 M sth r19, 0x12(r3)
       B sth r20, 0x12(r3)
   283 M addi r20, r20, 1
       B addi r26, r26, 1
   284 M addi r23, r23, 4
       B addi r22, r22, 4
   285 M cmpwi r20, 2
       B cmpwi r26, 2
   286 M addi r24, r24, 0x14
       B addi r23, r23, 0x14
   292 M cmpwi r26, 0
       B cmpwi r24, 0
```

## src/scene/cardSequence/iplCardSequence: CardSequence_813D3D14

```text
src 0x980 base 0x980 insns 608/608
diffs 186: [5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 22, 42, 46, 47, 50, 51, 53, 57, 60, 66]
     5 M lis r26, 0
       B lis r22, 0
     6 M mr r30, r4
       B mr r25, r3
     7 M mr r29, r3
       B mr r26, r4
     8 M mr r31, r5
       B mr r27, r5
     9 M addi r26, r26, 0
       B addi r22, r22, 0
    10 M li r25, -1
       B li r30, -1
    11 M li r23, 0
       B li r29, 0
    12 M li r22, 0
       B li r28, 0
    17 M mr r3, r29
       B mr r3, r25
    18 M mr r4, r31
       B mr r4, r27
    22 M li r16, 0
       B li r15, 0
    42 M mr r16, r3
       B mr r15, r3
    46 M mr r3, r29
       B mr r3, r25
    47 M mr r4, r31
       B mr r4, r27
    50 M mr r3, r29
       B mr r3, r25
    51 M mr r4, r30
       B mr r4, r26
    53 M li r15, 0
       B li r16, 0
    57 M cmpwi r31, 3
       B cmpwi r27, 3
    60 M cmpwi r31, 2
       B cmpwi r27, 2
    66 M li r15, -0xa
       B li r16, -0xa
    71 M li r15, -0xa
       B li r16, -0xa
    73 M mr r3, r29
       B mr r3, r25
    75 M mr r15, r3
       B mr r16, r3
    76 M cmpwi r15, 0
       B cmpwi r16, 0
    78 M mr r3, r29
       B mr r3, r25
    79 M mr r4, r31
       B mr r4, r27
    80 M mr r5, r15
       B mr r5, r16
    83 M mr r3, r29
       B mr r3, r25
    84 M mr r4, r30
       B mr r4, r26
    90 M xori r24, r29, 1
       B xori r31, r25, 1
    92 M mullw r16, r0, r16
       B mullw r16, r0, r15
    95 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   101 M mr r3, r24
       B mr r3, r31
   113 M addi r3, r26, 0x350
       B addi r3, r22, 0x350
   116 M extsh r25, r15
       B extsh r30, r15
   128 M extsh r25, r0
       B extsh r30, r0
   130 M li r25, -0x80
       B li r30, -0x80
   131 M cmpwi r25, 0
       B cmpwi r30, 0
   133 M mr r3, r24
       B mr r3, r31
   134 M mr r4, r31
       B mr r4, r27
   135 M mr r5, r25
       B mr r5, r30
   138 M mr r3, r29
       B mr r3, r25
   139 M mr r4, r30
       B mr r4, r26
   141 M li r23, 1
       B li r29, 1
   146 M mr r17, r3
       B mr r15, r3
   148 M mr r3, r29
       B mr r3, r25
   153 M mr r17, r3
       B mr r15, r3
   158 M mr r3, r29
       B mr r3, r25
   159 M divwu r19, r4, r0
       B divwu r17, r4, r0
   160 M mr r4, r30
       B mr r4, r26
   166 M mr r17, r3
       B mr r15, r3
   168 M li r18, 0
       B li r16, 0
   170 M li r27, 1
       B li r23, 1
   171 M lis r28, 0
       B lis r24, 0
   173 M subf r5, r18, r0
       B subf r0, r16, r0
   174 M cmplw r5, r19
       B cmplw r0, r17
   176 M mr r5, r19
       B mr r0, r17
   177 M lwz r0, 8(r1)
       B lwz r5, 8(r1)
   179 M mullw r16, r18, r0
       B mullw r19, r16, r5
   183 M mullw r15, r5, r0
       B mullw r18, r0, r5
   184 M mr r6, r16
       B mr r6, r19
   185 M mr r5, r15
       B mr r5, r18
   188 M mr r17, r3
       B mr r15, r3
   191 M mr r5, r15
       B mr r5, r18
   192 M mr r6, r16
       B mr r6, r19
   193 M addi r7, r28, 0
       B addi r7, r24, 0
   195 M stw r27, -0x2428(r3)
       B stw r23, -0x2428(r3)
   202 M mr r17, r3
       B mr r15, r3
   205 M mr r3, r29
       B mr r3, r25
   221 M add r18, r18, r19
       B add r16, r16, r17
   223 M cmpw r18, r0
       B cmpw r16, r0
   231 M mr r17, r3
       B mr r15, r3
   239 M mr r17, r3
       B mr r15, r3
   241 M li r17, 0
       B li r15, 0
   256 M addi r3, r26, 0x373
       B addi r3, r22, 0x373
   260 M addi r3, r26, 0x39a
       B addi r3, r22, 0x39a
   264 M addi r3, r26, 0x3c6
       B addi r3, r22, 0x3c6
   268 M addi r3, r26, 0x3e4
       B addi r3, r22, 0x3e4
   272 M addi r3, r26, 0x3ff
       B addi r3, r22, 0x3ff
   276 M addi r3, r26, 0x41b
       B addi r3, r22, 0x41b
   280 M mr r3, r24
       B mr r3, r31
   284 M cmpwi r17, 0
       B cmpwi r15, 0
   285 M blt 1008
       B blt 1068
   286 M cmpwi r31, 2
       B cmpwi r27, 2
   288 M mr r3, r29
       B mr r3, r25
   289 M mr r4, r30
       B mr r4, r26
   293 M mr r17, r3
       B mr r16, r3
   295 M addi r3, r26, 0x437
       B addi r3, r22, 0x437
   298 M b 956
       B b 252
   300 M mr r3, r29
       B mr r3, r25
   301 M mr r4, r30
       B mr r4, r26
   307 M mr r17, r3
       B mr r16, r3
   309 M mr r4, r17
       B mr r4, r16
   310 M addi r3, r26, 0x456
       B addi r3, r22, 0x456
   313 M b 896
       B b 192
   322 M mr r3, r24
       B mr r3, r31
   323 M mr r4, r25
       B mr r4, r30
   327 M mr r17, r3
       B mr r16, r3
   329 M addi r3, r26, 0x478
       B addi r3, r22, 0x478
   332 M cmpwi r17, -3
       B cmpwi r16, -3
   338 M mr r3, r29
       B mr r3, r25
   339 M mr r4, r30
       B mr r4, r26
   343 M bge 776
       B bge 72
   344 M addi r3, r26, 0x4ae
       B addi r3, r22, 0x4ae
   347 M b 760
       B b 56
   348 M mr r3, r24
       B mr r3, r31
   349 M mr r4, r25
       B mr r4, r30
   351 M li r22, 1
       B li r28, 1
   354 M mr r17, r3
       B mr r16, r3
   356 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   360 M li r17, 0
       B li r16, 0
   361 M cmpwi r17, 0
       B cmpwi r16, 0
   363 M b 696
       B b 704
   364 M cmpwi r31, 3
       B cmpwi r27, 3
   365 M bne 688
       B bne 696
   366 M mr r3, r29
       B mr r3, r25
   367 M mr r4, r30
       B mr r4, r26
   369 M li r15, 0
       B li r16, 0
   370 M li r16, 0
       B li r15, 0
   382 M li r16, 1
       B stw r8, 0x54(r1)
   383 M stw r8, 0x54(r1)
       B sth r7, 0x58(r1)
   384 M sth r7, 0x58(r1)
       B stb r6, 0x5a(r1)
   385 M stb r6, 0x5a(r1)
       B stb r3, 0x5b(r1)
   386 M stb r3, 0x5b(r1)
       B mtctr r0
   387 M mtctr r0
       B li r15, 1
   426 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   427 M extsh r5, r15
       B extsh r5, r16
   430 M mr r3, r29
       B mr r3, r25
   431 M mr r4, r30
       B mr r4, r26
   440 M addi r15, r15, 1
       B addi r16, r16, 1
   442 M extsh r0, r15
       B extsh r0, r16
   444 M blt -76
       B blt -92
   445 M mr r3, r24
       B mr r3, r31
   446 M mr r4, r25
       B mr r4, r30
   448 M li r16, 2
       B li r15, 2
   455 M mr r3, r29
       B mr r3, r25
   456 M mr r4, r30
       B mr r4, r26
   458 M mr r3, r29
       B mr r3, r25
   459 M mr r4, r30
       B mr r4, r26
   462 M mr r3, r29
       B mr r3, r25
   463 M mr r4, r30
       B mr r4, r26
   468 M addi r3, r26, 0x505
       B addi r3, r22, 0x505
   472 M mr r3, r29
       B mr r3, r25
   473 M mr r4, r30
       B mr r4, r26
   474 M li r22, 1
       B li r28, 1
   475 M li r16, 3
       B li r15, 3
   480 M mr r3, r29
       B mr r3, r25
   481 M mr r4, r30
       B mr r4, r26
   483 M mr r3, r24
       B mr r3, r31
   484 M mr r4, r25
       B mr r4, r30
   486 M li r16, 4
       B li r15, 4
   491 M mr r3, r24
       B mr r3, r31
   492 M mr r4, r25
       B mr r4, r30
   494 M li r16, 5
       B li r15, 5
   501 M cmpwi r16, 3
       B cmpwi r15, 3
   504 M cmpwi r16, 1
       B cmpwi r15, 1
   507 M cmpwi r16, 0
       B cmpwi r15, 0
   510 M cmpwi r16, 5
       B cmpwi r15, 5
   514 M addi r3, r26, 0x526
       B addi r3, r22, 0x526
   518 M addi r3, r26, 0x546
       B addi r3, r22, 0x546
   522 M addi r3, r26, 0x565
       B addi r3, r22, 0x565
   526 M addi r3, r26, 0x57c
       B addi r3, r22, 0x57c
   530 M addi r3, r26, 0x593
       B addi r3, r22, 0x593
   534 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   539 M mr r3, r29
       B mr r3, r25
   541 M mr r3, r24
       B mr r3, r31
   543 M mr r3, r29
       B mr r3, r25
   544 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   547 M mr r3, r24
       B mr r3, r31
   548 M mr r4, r31
       B mr r4, r27
   549 M clrlwi r5, r25, 0x18
       B clrlwi r5, r30, 0x18
   552 M xori r15, r29, 1
       B xori r15, r25, 1
   559 M mr r4, r31
       B mr r4, r27
   562 M cmpwi r23, 0
       B cmpwi r29, 0
   564 M cmpwi r22, 0
       B cmpwi r28, 0
   567 M mr r4, r25
       B extsh r4, r30
   569 M cmpwi r22, 0
       B cmpwi r28, 0
   572 M mr r4, r25
       B extsh r4, r30
   578 M mr r4, r25
       B extsh r4, r30
   584 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   587 M mr r3, r29
       B mr r3, r25
   592 M mr r3, r29
       B mr r3, r25
   593 M mr r4, r31
       B mr r4, r27
   596 M mr r3, r29
       B mr r3, r25
   598 M mr r3, r29
       B mr r3, r25
   599 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
```

- local register types: native int operation status and transfer counters: exact False; insns 608/608; differences 186; objdiff 97.804276

```text
src 0x980 base 0x980 insns 608/608
diffs 186: [5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 22, 42, 46, 47, 50, 51, 53, 57, 60, 66]
     5 M lis r26, 0
       B lis r22, 0
     6 M mr r30, r4
       B mr r25, r3
     7 M mr r29, r3
       B mr r26, r4
     8 M mr r31, r5
       B mr r27, r5
     9 M addi r26, r26, 0
       B addi r22, r22, 0
    10 M li r25, -1
       B li r30, -1
    11 M li r23, 0
       B li r29, 0
    12 M li r22, 0
       B li r28, 0
    17 M mr r3, r29
       B mr r3, r25
    18 M mr r4, r31
       B mr r4, r27
    22 M li r16, 0
       B li r15, 0
    42 M mr r16, r3
       B mr r15, r3
    46 M mr r3, r29
       B mr r3, r25
    47 M mr r4, r31
       B mr r4, r27
    50 M mr r3, r29
       B mr r3, r25
    51 M mr r4, r30
       B mr r4, r26
    53 M li r15, 0
       B li r16, 0
    57 M cmpwi r31, 3
       B cmpwi r27, 3
    60 M cmpwi r31, 2
       B cmpwi r27, 2
    66 M li r15, -0xa
       B li r16, -0xa
    71 M li r15, -0xa
       B li r16, -0xa
    73 M mr r3, r29
       B mr r3, r25
    75 M mr r15, r3
       B mr r16, r3
    76 M cmpwi r15, 0
       B cmpwi r16, 0
    78 M mr r3, r29
       B mr r3, r25
    79 M mr r4, r31
       B mr r4, r27
    80 M mr r5, r15
       B mr r5, r16
    83 M mr r3, r29
       B mr r3, r25
    84 M mr r4, r30
       B mr r4, r26
    90 M xori r24, r29, 1
       B xori r31, r25, 1
    92 M mullw r16, r0, r16
       B mullw r16, r0, r15
    95 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   101 M mr r3, r24
       B mr r3, r31
   113 M addi r3, r26, 0x350
       B addi r3, r22, 0x350
   116 M extsh r25, r15
       B extsh r30, r15
   128 M extsh r25, r0
       B extsh r30, r0
   130 M li r25, -0x80
       B li r30, -0x80
   131 M cmpwi r25, 0
       B cmpwi r30, 0
   133 M mr r3, r24
       B mr r3, r31
   134 M mr r4, r31
       B mr r4, r27
   135 M mr r5, r25
       B mr r5, r30
   138 M mr r3, r29
       B mr r3, r25
   139 M mr r4, r30
       B mr r4, r26
   141 M li r23, 1
       B li r29, 1
   146 M mr r17, r3
       B mr r15, r3
   148 M mr r3, r29
       B mr r3, r25
   153 M mr r17, r3
       B mr r15, r3
   158 M mr r3, r29
       B mr r3, r25
   159 M divwu r19, r4, r0
       B divwu r17, r4, r0
   160 M mr r4, r30
       B mr r4, r26
   166 M mr r17, r3
       B mr r15, r3
   168 M li r18, 0
       B li r16, 0
   170 M li r27, 1
       B li r23, 1
   171 M lis r28, 0
       B lis r24, 0
   173 M subf r5, r18, r0
       B subf r0, r16, r0
   174 M cmplw r5, r19
       B cmplw r0, r17
   176 M mr r5, r19
       B mr r0, r17
   177 M lwz r0, 8(r1)
       B lwz r5, 8(r1)
   179 M mullw r16, r18, r0
       B mullw r19, r16, r5
   183 M mullw r15, r5, r0
       B mullw r18, r0, r5
   184 M mr r6, r16
       B mr r6, r19
   185 M mr r5, r15
       B mr r5, r18
   188 M mr r17, r3
       B mr r15, r3
   191 M mr r5, r15
       B mr r5, r18
   192 M mr r6, r16
       B mr r6, r19
   193 M addi r7, r28, 0
       B addi r7, r24, 0
   195 M stw r27, -0x2428(r3)
       B stw r23, -0x2428(r3)
   202 M mr r17, r3
       B mr r15, r3
   205 M mr r3, r29
       B mr r3, r25
   221 M add r18, r18, r19
       B add r16, r16, r17
   223 M cmpw r18, r0
       B cmpw r16, r0
   231 M mr r17, r3
       B mr r15, r3
   239 M mr r17, r3
       B mr r15, r3
   241 M li r17, 0
       B li r15, 0
   256 M addi r3, r26, 0x373
       B addi r3, r22, 0x373
   260 M addi r3, r26, 0x39a
       B addi r3, r22, 0x39a
   264 M addi r3, r26, 0x3c6
       B addi r3, r22, 0x3c6
   268 M addi r3, r26, 0x3e4
       B addi r3, r22, 0x3e4
   272 M addi r3, r26, 0x3ff
       B addi r3, r22, 0x3ff
   276 M addi r3, r26, 0x41b
       B addi r3, r22, 0x41b
   280 M mr r3, r24
       B mr r3, r31
   284 M cmpwi r17, 0
       B cmpwi r15, 0
   285 M blt 1008
       B blt 1068
   286 M cmpwi r31, 2
       B cmpwi r27, 2
   288 M mr r3, r29
       B mr r3, r25
   289 M mr r4, r30
       B mr r4, r26
   293 M mr r17, r3
       B mr r16, r3
   295 M addi r3, r26, 0x437
       B addi r3, r22, 0x437
   298 M b 956
       B b 252
   300 M mr r3, r29
       B mr r3, r25
   301 M mr r4, r30
       B mr r4, r26
   307 M mr r17, r3
       B mr r16, r3
   309 M mr r4, r17
       B mr r4, r16
   310 M addi r3, r26, 0x456
       B addi r3, r22, 0x456
   313 M b 896
       B b 192
   322 M mr r3, r24
       B mr r3, r31
   323 M mr r4, r25
       B mr r4, r30
   327 M mr r17, r3
       B mr r16, r3
   329 M addi r3, r26, 0x478
       B addi r3, r22, 0x478
   332 M cmpwi r17, -3
       B cmpwi r16, -3
   338 M mr r3, r29
       B mr r3, r25
   339 M mr r4, r30
       B mr r4, r26
   343 M bge 776
       B bge 72
   344 M addi r3, r26, 0x4ae
       B addi r3, r22, 0x4ae
   347 M b 760
       B b 56
   348 M mr r3, r24
       B mr r3, r31
   349 M mr r4, r25
       B mr r4, r30
   351 M li r22, 1
       B li r28, 1
   354 M mr r17, r3
       B mr r16, r3
   356 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   360 M li r17, 0
       B li r16, 0
   361 M cmpwi r17, 0
       B cmpwi r16, 0
   363 M b 696
       B b 704
   364 M cmpwi r31, 3
       B cmpwi r27, 3
   365 M bne 688
       B bne 696
   366 M mr r3, r29
       B mr r3, r25
   367 M mr r4, r30
       B mr r4, r26
   369 M li r15, 0
       B li r16, 0
   370 M li r16, 0
       B li r15, 0
   382 M li r16, 1
       B stw r8, 0x54(r1)
   383 M stw r8, 0x54(r1)
       B sth r7, 0x58(r1)
   384 M sth r7, 0x58(r1)
       B stb r6, 0x5a(r1)
   385 M stb r6, 0x5a(r1)
       B stb r3, 0x5b(r1)
   386 M stb r3, 0x5b(r1)
       B mtctr r0
   387 M mtctr r0
       B li r15, 1
   426 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   427 M extsh r5, r15
       B extsh r5, r16
   430 M mr r3, r29
       B mr r3, r25
   431 M mr r4, r30
       B mr r4, r26
   440 M addi r15, r15, 1
       B addi r16, r16, 1
   442 M extsh r0, r15
       B extsh r0, r16
   444 M blt -76
       B blt -92
   445 M mr r3, r24
       B mr r3, r31
   446 M mr r4, r25
       B mr r4, r30
   448 M li r16, 2
       B li r15, 2
   455 M mr r3, r29
       B mr r3, r25
   456 M mr r4, r30
       B mr r4, r26
   458 M mr r3, r29
       B mr r3, r25
   459 M mr r4, r30
       B mr r4, r26
   462 M mr r3, r29
       B mr r3, r25
   463 M mr r4, r30
       B mr r4, r26
   468 M addi r3, r26, 0x505
       B addi r3, r22, 0x505
   472 M mr r3, r29
       B mr r3, r25
   473 M mr r4, r30
       B mr r4, r26
   474 M li r22, 1
       B li r28, 1
   475 M li r16, 3
       B li r15, 3
   480 M mr r3, r29
       B mr r3, r25
   481 M mr r4, r30
       B mr r4, r26
   483 M mr r3, r24
       B mr r3, r31
   484 M mr r4, r25
       B mr r4, r30
   486 M li r16, 4
       B li r15, 4
   491 M mr r3, r24
       B mr r3, r31
   492 M mr r4, r25
       B mr r4, r30
   494 M li r16, 5
       B li r15, 5
   501 M cmpwi r16, 3
       B cmpwi r15, 3
   504 M cmpwi r16, 1
       B cmpwi r15, 1
   507 M cmpwi r16, 0
       B cmpwi r15, 0
   510 M cmpwi r16, 5
       B cmpwi r15, 5
   514 M addi r3, r26, 0x526
       B addi r3, r22, 0x526
   518 M addi r3, r26, 0x546
       B addi r3, r22, 0x546
   522 M addi r3, r26, 0x565
       B addi r3, r22, 0x565
   526 M addi r3, r26, 0x57c
       B addi r3, r22, 0x57c
   530 M addi r3, r26, 0x593
       B addi r3, r22, 0x593
   534 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   539 M mr r3, r29
       B mr r3, r25
   541 M mr r3, r24
       B mr r3, r31
   543 M mr r3, r29
       B mr r3, r25
   544 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   547 M mr r3, r24
       B mr r3, r31
   548 M mr r4, r31
       B mr r4, r27
   549 M clrlwi r5, r25, 0x18
       B clrlwi r5, r30, 0x18
   552 M xori r15, r29, 1
       B xori r15, r25, 1
   559 M mr r4, r31
       B mr r4, r27
   562 M cmpwi r23, 0
       B cmpwi r29, 0
   564 M cmpwi r22, 0
       B cmpwi r28, 0
   567 M mr r4, r25
       B extsh r4, r30
   569 M cmpwi r22, 0
       B cmpwi r28, 0
   572 M mr r4, r25
       B extsh r4, r30
   578 M mr r4, r25
       B extsh r4, r30
   584 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   587 M mr r3, r29
       B mr r3, r25
   592 M mr r3, r29
       B mr r3, r25
   593 M mr r4, r31
       B mr r4, r27
   596 M mr r3, r29
       B mr r3, r25
   598 M mr r3, r29
       B mr r3, r25
   599 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
```

- temporary merging: transfer status reuses the sector-result temporary: exact False; insns 608/608; differences 207; objdiff 97.63158

```text
src 0x980 base 0x980 insns 608/608
diffs 207: [5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 22, 42, 46, 47, 50, 51, 53, 57, 60, 66]
     5 M lis r26, 0
       B lis r22, 0
     6 M mr r30, r4
       B mr r25, r3
     7 M mr r29, r3
       B mr r26, r4
     8 M mr r31, r5
       B mr r27, r5
     9 M addi r26, r26, 0
       B addi r22, r22, 0
    10 M li r24, -1
       B li r30, -1
    11 M li r22, 0
       B li r29, 0
    12 M li r21, 0
       B li r28, 0
    17 M mr r3, r29
       B mr r3, r25
    18 M mr r4, r31
       B mr r4, r27
    22 M li r16, 0
       B li r15, 0
    42 M mr r16, r3
       B mr r15, r3
    46 M mr r3, r29
       B mr r3, r25
    47 M mr r4, r31
       B mr r4, r27
    50 M mr r3, r29
       B mr r3, r25
    51 M mr r4, r30
       B mr r4, r26
    53 M li r15, 0
       B li r16, 0
    57 M cmpwi r31, 3
       B cmpwi r27, 3
    60 M cmpwi r31, 2
       B cmpwi r27, 2
    66 M li r15, -0xa
       B li r16, -0xa
    71 M li r15, -0xa
       B li r16, -0xa
    73 M mr r3, r29
       B mr r3, r25
    75 M mr r15, r3
       B mr r16, r3
    76 M cmpwi r15, 0
       B cmpwi r16, 0
    78 M mr r3, r29
       B mr r3, r25
    79 M mr r4, r31
       B mr r4, r27
    80 M mr r5, r15
       B mr r5, r16
    83 M mr r3, r29
       B mr r3, r25
    84 M mr r4, r30
       B mr r4, r26
    90 M xori r23, r29, 1
       B xori r31, r25, 1
    92 M mullw r16, r0, r16
       B mullw r16, r0, r15
    95 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   101 M mr r3, r23
       B mr r3, r31
   113 M addi r3, r26, 0x350
       B addi r3, r22, 0x350
   116 M extsh r24, r15
       B extsh r30, r15
   128 M extsh r24, r0
       B extsh r30, r0
   130 M li r24, -0x80
       B li r30, -0x80
   131 M cmpwi r24, 0
       B cmpwi r30, 0
   133 M mr r3, r23
       B mr r3, r31
   134 M mr r4, r31
       B mr r4, r27
   135 M mr r5, r24
       B mr r5, r30
   138 M mr r3, r29
       B mr r3, r25
   139 M mr r4, r30
       B mr r4, r26
   141 M li r22, 1
       B li r29, 1
   142 M li r19, 0
       B li r20, 0
   143 M li r20, 0
       B li r21, 0
   146 M mr r25, r3
       B mr r15, r3
   148 M mr r3, r29
       B mr r3, r25
   150 M li r19, 1
       B li r20, 1
   153 M mr r25, r3
       B mr r15, r3
   158 M mr r3, r29
       B mr r3, r25
   159 M divwu r18, r4, r0
       B divwu r17, r4, r0
   160 M mr r4, r30
       B mr r4, r26
   162 M li r19, 2
       B li r20, 2
   166 M mr r25, r3
       B mr r15, r3
   168 M li r17, 0
       B li r16, 0
   169 M li r19, 3
       B li r20, 3
   170 M li r27, 1
       B li r23, 1
   171 M lis r28, 0
       B lis r24, 0
   173 M subf r5, r17, r0
       B subf r0, r16, r0
   174 M cmplw r5, r18
       B cmplw r0, r17
   176 M mr r5, r18
       B mr r0, r17
   177 M lwz r0, 8(r1)
       B lwz r5, 8(r1)
   179 M mullw r16, r17, r0
       B mullw r19, r16, r5
   183 M mullw r15, r5, r0
       B mullw r18, r0, r5
   184 M mr r6, r16
       B mr r6, r19
   185 M mr r5, r15
       B mr r5, r18
   188 M mr r25, r3
       B mr r15, r3
   191 M mr r5, r15
       B mr r5, r18
   192 M mr r6, r16
       B mr r6, r19
   193 M addi r7, r28, 0
       B addi r7, r24, 0
   195 M stw r27, -0x2428(r3)
       B stw r23, -0x2428(r3)
   202 M mr r25, r3
       B mr r15, r3
   205 M mr r3, r29
       B mr r3, r25
   209 M cmpwi r20, 0
       B cmpwi r21, 0
   215 M li r20, 1
       B li r21, 1
   221 M add r17, r17, r18
       B add r16, r16, r17
   223 M cmpw r17, r0
       B cmpw r16, r0
   226 M li r19, 4
       B li r20, 4
   231 M mr r25, r3
       B mr r15, r3
   234 M li r19, 5
       B li r20, 5
   239 M mr r25, r3
       B mr r15, r3
   241 M li r25, 0
       B li r15, 0
   243 M cmpwi r19, 3
       B cmpwi r20, 3
   246 M cmpwi r19, 1
       B cmpwi r20, 1
   249 M cmpwi r19, 0
       B cmpwi r20, 0
   252 M cmpwi r19, 5
       B cmpwi r20, 5
   256 M addi r3, r26, 0x373
       B addi r3, r22, 0x373
   260 M addi r3, r26, 0x39a
       B addi r3, r22, 0x39a
   264 M addi r3, r26, 0x3c6
       B addi r3, r22, 0x3c6
   268 M addi r3, r26, 0x3e4
       B addi r3, r22, 0x3e4
   272 M addi r3, r26, 0x3ff
       B addi r3, r22, 0x3ff
   276 M addi r3, r26, 0x41b
       B addi r3, r22, 0x41b
   280 M mr r3, r23
       B mr r3, r31
   284 M cmpwi r25, 0
       B cmpwi r15, 0
   285 M blt 1008
       B blt 1068
   286 M cmpwi r31, 2
       B cmpwi r27, 2
   288 M mr r3, r29
       B mr r3, r25
   289 M mr r4, r30
       B mr r4, r26
   293 M mr r25, r3
       B mr r16, r3
   295 M addi r3, r26, 0x437
       B addi r3, r22, 0x437
   298 M b 956
       B b 252
   300 M mr r3, r29
       B mr r3, r25
   301 M mr r4, r30
       B mr r4, r26
   307 M mr r25, r3
       B mr r16, r3
   309 M mr r4, r25
       B mr r4, r16
   310 M addi r3, r26, 0x456
       B addi r3, r22, 0x456
   313 M b 896
       B b 192
   322 M mr r3, r23
       B mr r3, r31
   323 M mr r4, r24
       B mr r4, r30
   327 M mr r25, r3
       B mr r16, r3
   329 M addi r3, r26, 0x478
       B addi r3, r22, 0x478
   332 M cmpwi r25, -3
       B cmpwi r16, -3
   338 M mr r3, r29
       B mr r3, r25
   339 M mr r4, r30
       B mr r4, r26
   343 M bge 776
       B bge 72
   344 M addi r3, r26, 0x4ae
       B addi r3, r22, 0x4ae
   347 M b 760
       B b 56
   348 M mr r3, r23
       B mr r3, r31
   349 M mr r4, r24
       B mr r4, r30
   351 M li r21, 1
       B li r28, 1
   354 M mr r25, r3
       B mr r16, r3
   356 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   360 M li r25, 0
       B li r16, 0
   361 M cmpwi r25, 0
       B cmpwi r16, 0
   363 M b 696
       B b 704
   364 M cmpwi r31, 3
       B cmpwi r27, 3
   365 M bne 688
       B bne 696
   366 M mr r3, r29
       B mr r3, r25
   367 M mr r4, r30
       B mr r4, r26
   369 M li r15, 0
       B li r16, 0
   370 M li r16, 0
       B li r15, 0
   373 M mr r25, r3
       B mr r17, r3
   382 M li r16, 1
       B stw r8, 0x54(r1)
   383 M stw r8, 0x54(r1)
       B sth r7, 0x58(r1)
   384 M sth r7, 0x58(r1)
       B stb r6, 0x5a(r1)
   385 M stb r6, 0x5a(r1)
       B stb r3, 0x5b(r1)
   386 M stb r3, 0x5b(r1)
       B mtctr r0
   387 M mtctr r0
       B li r15, 1
   426 M addi r4, r26, 0x340
       B addi r4, r22, 0x340
   427 M extsh r5, r15
       B extsh r5, r16
   430 M mr r3, r29
       B mr r3, r25
   431 M mr r4, r30
       B mr r4, r26
   435 M mr r25, r3
       B mr r17, r3
   440 M addi r15, r15, 1
       B addi r16, r16, 1
   442 M extsh r0, r15
       B extsh r0, r16
   444 M blt -76
       B blt -92
   445 M mr r3, r23
       B mr r3, r31
   446 M mr r4, r24
       B mr r4, r30
   448 M li r16, 2
       B li r15, 2
   451 M mr r25, r3
       B mr r17, r3
   455 M mr r3, r29
       B mr r3, r25
   456 M mr r4, r30
       B mr r4, r26
   458 M mr r3, r29
       B mr r3, r25
   459 M mr r4, r30
       B mr r4, r26
   462 M mr r3, r29
       B mr r3, r25
   463 M mr r4, r30
       B mr r4, r26
   468 M addi r3, r26, 0x505
       B addi r3, r22, 0x505
   472 M mr r3, r29
       B mr r3, r25
   473 M mr r4, r30
       B mr r4, r26
   474 M li r21, 1
       B li r28, 1
   475 M li r16, 3
       B li r15, 3
   478 M mr r25, r3
       B mr r17, r3
   480 M mr r3, r29
       B mr r3, r25
   481 M mr r4, r30
       B mr r4, r26
   483 M mr r3, r23
       B mr r3, r31
   484 M mr r4, r24
       B mr r4, r30
   486 M li r16, 4
       B li r15, 4
   489 M mr r25, r3
       B mr r17, r3
   491 M mr r3, r23
       B mr r3, r31
   492 M mr r4, r24
       B mr r4, r30
   494 M li r16, 5
       B li r15, 5
   497 M mr r25, r3
       B mr r17, r3
   499 M li r25, 0
       B li r17, 0
   501 M cmpwi r16, 3
       B cmpwi r15, 3
   504 M cmpwi r16, 1
       B cmpwi r15, 1
   507 M cmpwi r16, 0
       B cmpwi r15, 0
   510 M cmpwi r16, 5
       B cmpwi r15, 5
   514 M addi r3, r26, 0x526
       B addi r3, r22, 0x526
   518 M addi r3, r26, 0x546
       B addi r3, r22, 0x546
   522 M addi r3, r26, 0x565
       B addi r3, r22, 0x565
   526 M addi r3, r26, 0x57c
       B addi r3, r22, 0x57c
   530 M addi r3, r26, 0x593
       B addi r3, r22, 0x593
   534 M addi r3, r26, 0x4e3
       B addi r3, r22, 0x4e3
   537 M cmpwi r25, 0
       B cmpwi r17, 0
   539 M mr r3, r29
       B mr r3, r25
   541 M mr r3, r23
       B mr r3, r31
   543 M mr r3, r29
       B mr r3, r25
   544 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   547 M mr r3, r23
       B mr r3, r31
   548 M mr r4, r31
       B mr r4, r27
   549 M clrlwi r5, r24, 0x18
       B clrlwi r5, r30, 0x18
   552 M xori r15, r29, 1
       B xori r15, r25, 1
   559 M mr r4, r31
       B mr r4, r27
   562 M cmpwi r22, 0
       B cmpwi r29, 0
   564 M cmpwi r21, 0
       B cmpwi r28, 0
   567 M mr r4, r24
       B extsh r4, r30
   569 M cmpwi r21, 0
       B cmpwi r28, 0
   572 M mr r4, r24
       B extsh r4, r30
   578 M mr r4, r24
       B extsh r4, r30
   584 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
   587 M mr r3, r29
       B mr r3, r25
   592 M mr r3, r29
       B mr r3, r25
   593 M mr r4, r31
       B mr r4, r27
   596 M mr r3, r29
       B mr r3, r25
   598 M mr r3, r29
       B mr r3, r25
   599 M clrlwi r5, r30, 0x18
       B clrlwi r5, r26, 0x18
```

- temporary width: full-width destination file with narrow card-call arguments: exact False; insns 607/608; differences None; objdiff 97.54934

```text
src 0x97c base 0x980 insns 607/608
--- replace mine 5:13 base 5:13
  M    5 lis r26, 0
  M    6 mr r30, r4
  M    7 mr r29, r3
  M    8 mr r31, r5
  M    9 addi r26, r26, 0
  M   10 li r25, -1
  M   11 li r23, 0
  M   12 li r22, 0
  B    5 lis r22, 0
  B    6 mr r25, r3
  B    7 mr r26, r4
  B    8 mr r27, r5
  B    9 addi r22, r22, 0
  B   10 li r30, -1
  B   11 li r29, 0
  B   12 li r28, 0
--- replace mine 17:19 base 17:19
  M   17 mr r3, r29
  M   18 mr r4, r31
  B   17 mr r3, r25
  B   18 mr r4, r27
--- replace mine 20:21 base 20:21
  M   20 b 2324
  B   20 b 2328
--- replace mine 22:23 base 22:23
  M   22 li r16, 0
  B   22 li r15, 0
--- replace mine 42:43 base 42:43
  M   42 mr r16, r3
  B   42 mr r15, r3
--- replace mine 46:48 base 46:48
  M   46 mr r3, r29
  M   47 mr r4, r31
  B   46 mr r3, r25
  B   47 mr r4, r27
--- replace mine 49:52 base 49:52
  M   49 b 2208
  M   50 mr r3, r29
  M   51 mr r4, r30
  B   49 b 2212
  B   50 mr r3, r25
  B   51 mr r4, r26
--- replace mine 53:54 base 53:54
  M   53 li r15, 0
  B   53 li r16, 0
--- replace mine 57:58 base 57:58
  M   57 cmpwi r31, 3
  B   57 cmpwi r27, 3
--- replace mine 60:61 base 60:61
  M   60 cmpwi r31, 2
  B   60 cmpwi r27, 2
--- replace mine 66:67 base 66:67
  M   66 li r15, -0xa
  B   66 li r16, -0xa
--- replace mine 71:72 base 71:72
  M   71 li r15, -0xa
  B   71 li r16, -0xa
--- replace mine 73:74 base 73:74
  M   73 mr r3, r29
  B   73 mr r3, r25
--- replace mine 75:77 base 75:77
  M   75 mr r15, r3
  M   76 cmpwi r15, 0
  B   75 mr r16, r3
  B   76 cmpwi r16, 0
--- replace mine 78:81 base 78:81
  M   78 mr r3, r29
  M   79 mr r4, r31
  M   80 mr r5, r15
  B   78 mr r3, r25
  B   79 mr r4, r27
  B   80 mr r5, r16
--- replace mine 82:85 base 82:85
  M   82 b 2076
  M   83 mr r3, r29
  M   84 mr r4, r30
  B   82 b 2080
  B   83 mr r3, r25
  B   84 mr r4, r26
--- replace mine 88:89 base 88:89
  M   88 blt 1852
  B   88 blt 1856
--- replace mine 90:91 base 90:91
  M   90 xori r24, r29, 1
  B   90 xori r31, r25, 1
--- replace mine 92:93 base 92:93
  M   92 mullw r16, r0, r16
  B   92 mullw r16, r0, r15
--- replace mine 95:96 base 95:96
  M   95 addi r4, r26, 0x340
  B   95 addi r4, r22, 0x340
--- replace mine 101:102 base 101:102
  M  101 mr r3, r24
  B  101 mr r3, r31
--- replace mine 113:114 base 113:114
  M  113 addi r3, r26, 0x350
  B  113 addi r3, r22, 0x350
--- replace mine 116:118 base 116:118
  M  116 extsh r25, r15
  M  117 b 52
  B  116 extsh r30, r15
  B  117 b 56
--- replace mine 124:125 base 124:125
  M  124 bge 20
  B  124 bge 24
--- replace mine 127:128 base 127:129
  M  127 lwz r25, -0x6fd0(r3)
  B  127 lwz r0, -0x6fd0(r3)
  B  128 extsh r30, r0
--- replace mine 129:131 base 130:132
  M  129 li r25, -0x80
  M  130 cmpwi r25, 0
  B  130 li r30, -0x80
  B  131 cmpwi r30, 0
--- replace mine 132:135 base 133:136
  M  132 mr r3, r24
  M  133 mr r4, r31
  M  134 mr r5, r25
  B  133 mr r3, r31
  B  134 mr r4, r27
  B  135 mr r5, r30
--- replace mine 137:139 base 138:140
  M  137 mr r3, r29
  M  138 mr r4, r30
  B  138 mr r3, r25
  B  139 mr r4, r26
--- replace mine 140:141 base 141:142
  M  140 li r23, 1
  B  141 li r29, 1
--- replace mine 145:146 base 146:147
  M  145 mr r17, r3
  B  146 mr r15, r3
--- replace mine 147:148 base 148:149
  M  147 mr r3, r29
  B  148 mr r3, r25
--- replace mine 152:153 base 153:154
  M  152 mr r17, r3
  B  153 mr r15, r3
--- replace mine 157:160 base 158:161
  M  157 mr r3, r29
  M  158 divwu r19, r4, r0
  M  159 mr r4, r30
  B  158 mr r3, r25
  B  159 divwu r17, r4, r0
  B  160 mr r4, r26
--- replace mine 165:166 base 166:167
  M  165 mr r17, r3
  B  166 mr r15, r3
--- replace mine 167:168 base 168:169
  M  167 li r18, 0
  B  168 li r16, 0
--- replace mine 169:171 base 170:172
  M  169 li r27, 1
  M  170 lis r28, 0
  B  170 li r23, 1
  B  171 lis r24, 0
--- replace mine 172:174 base 173:175
  M  172 subf r5, r18, r0
  M  173 cmplw r5, r19
  B  173 subf r0, r16, r0
  B  174 cmplw r0, r17
--- replace mine 175:177 base 176:178
  M  175 mr r5, r19
  M  176 lwz r0, 8(r1)
  B  176 mr r0, r17
  B  177 lwz r5, 8(r1)
--- replace mine 178:179 base 179:180
  M  178 mullw r16, r18, r0
  B  179 mullw r19, r16, r5
--- replace mine 182:185 base 183:186
  M  182 mullw r15, r5, r0
  M  183 mr r6, r16
  M  184 mr r5, r15
  B  183 mullw r18, r0, r5
  B  184 mr r6, r19
  B  185 mr r5, r18
--- replace mine 187:188 base 188:189
  M  187 mr r17, r3
  B  188 mr r15, r3
--- replace mine 190:193 base 191:194
  M  190 mr r5, r15
  M  191 mr r6, r16
  M  192 addi r7, r28, 0
  B  191 mr r5, r18
  B  192 mr r6, r19
  B  193 addi r7, r24, 0
--- replace mine 194:195 base 195:196
  M  194 stw r27, -0x2428(r3)
  B  195 stw r23, -0x2428(r3)
--- replace mine 201:202 base 202:203
  M  201 mr r17, r3
  B  202 mr r15, r3
--- replace mine 204:205 base 205:206
  M  204 mr r3, r29
  B  205 mr r3, r25
--- replace mine 220:221 base 221:222
  M  220 add r18, r18, r19
  B  221 add r16, r16, r17
--- replace mine 222:223 base 223:224
  M  222 cmpw r18, r0
  B  223 cmpw r16, r0
--- replace mine 230:231 base 231:232
  M  230 mr r17, r3
  B  231 mr r15, r3
--- replace mine 238:239 base 239:240
  M  238 mr r17, r3
  B  239 mr r15, r3
--- replace mine 240:241 base 241:242
  M  240 li r17, 0
  B  241 li r15, 0
--- replace mine 255:256 base 256:257
  M  255 addi r3, r26, 0x373
  B  256 addi r3, r22, 0x373
--- replace mine 259:260 base 260:261
  M  259 addi r3, r26, 0x39a
  B  260 addi r3, r22, 0x39a
--- replace mine 263:264 base 264:265
  M  263 addi r3, r26, 0x3c6
  B  264 addi r3, r22, 0x3c6
--- replace mine 267:268 base 268:269
  M  267 addi r3, r26, 0x3e4
  B  268 addi r3, r22, 0x3e4
--- replace mine 271:272 base 272:273
  M  271 addi r3, r26, 0x3ff
  B  272 addi r3, r22, 0x3ff
--- replace mine 275:276 base 276:277
  M  275 addi r3, r26, 0x41b
  B  276 addi r3, r22, 0x41b
--- replace mine 279:280 base 280:281
  M  279 mr r3, r24
  B  280 mr r3, r31
--- replace mine 283:286 base 284:287
  M  283 cmpwi r17, 0
  M  284 blt 1008
  M  285 cmpwi r31, 2
  B  284 cmpwi r15, 0
  B  285 blt 1068
  B  286 cmpwi r27, 2
--- replace mine 287:289 base 288:290
  M  287 mr r3, r29
  M  288 mr r4, r30
  B  288 mr r3, r25
  B  289 mr r4, r26
--- replace mine 292:293 base 293:294
  M  292 mr r17, r3
  B  293 mr r16, r3
--- replace mine 294:295 base 295:296
  M  294 addi r3, r26, 0x437
  B  295 addi r3, r22, 0x437
--- replace mine 297:298 base 298:299
  M  297 b 956
  B  298 b 252
--- replace mine 299:301 base 300:302
  M  299 mr r3, r29
  M  300 mr r4, r30
  B  300 mr r3, r25
  B  301 mr r4, r26
--- replace mine 306:307 base 307:308
  M  306 mr r17, r3
  B  307 mr r16, r3
--- replace mine 308:310 base 309:311
  M  308 mr r4, r17
  M  309 addi r3, r26, 0x456
  B  309 mr r4, r16
  B  310 addi r3, r22, 0x456
--- replace mine 312:313 base 313:314
  M  312 b 896
  B  313 b 192
--- replace mine 321:323 base 322:324
  M  321 mr r3, r24
  M  322 extsh r4, r25
  B  322 mr r3, r31
  B  323 mr r4, r30
--- replace mine 326:327 base 327:328
  M  326 mr r17, r3
  B  327 mr r16, r3
--- replace mine 328:329 base 329:330
  M  328 addi r3, r26, 0x478
  B  329 addi r3, r22, 0x478
--- replace mine 331:332 base 332:333
  M  331 cmpwi r17, -3
  B  332 cmpwi r16, -3
--- replace mine 337:339 base 338:340
  M  337 mr r3, r29
  M  338 mr r4, r30
  B  338 mr r3, r25
  B  339 mr r4, r26
--- replace mine 342:344 base 343:345
  M  342 bge 776
  M  343 addi r3, r26, 0x4ae
  B  343 bge 72
  B  344 addi r3, r22, 0x4ae
--- replace mine 346:349 base 347:350
  M  346 b 760
  M  347 mr r3, r24
  M  348 extsh r4, r25
  B  347 b 56
  B  348 mr r3, r31
  B  349 mr r4, r30
--- replace mine 350:351 base 351:352
  M  350 li r22, 1
  B  351 li r28, 1
--- replace mine 353:354 base 354:355
  M  353 mr r17, r3
  B  354 mr r16, r3
--- replace mine 355:356 base 356:357
  M  355 addi r3, r26, 0x4e3
  B  356 addi r3, r22, 0x4e3
--- replace mine 359:361 base 360:362
  M  359 li r17, 0
  M  360 cmpwi r17, 0
  B  360 li r16, 0
  B  361 cmpwi r16, 0
--- replace mine 362:367 base 363:368
  M  362 b 696
  M  363 cmpwi r31, 3
  M  364 bne 688
  M  365 mr r3, r29
  M  366 mr r4, r30
  B  363 b 704
  B  364 cmpwi r27, 3
  B  365 bne 696
  B  366 mr r3, r25
  B  367 mr r4, r26
--- insert mine 368:368 base 369:370
  B  369 li r16, 0
--- delete mine 369:370 base 371:371
  M  369 li r16, 0
--- delete mine 381:382 base 382:382
  M  381 li r16, 1
--- insert mine 387:387 base 387:388
  B  387 li r15, 1
--- replace mine 425:427 base 426:428
  M  425 addi r4, r26, 0x340
  M  426 extsh r5, r15
  B  426 addi r4, r22, 0x340
  B  427 extsh r5, r16
--- replace mine 429:431 base 430:432
  M  429 mr r3, r29
  M  430 mr r4, r30
  B  430 mr r3, r25
  B  431 mr r4, r26
--- replace mine 439:440 base 440:441
  M  439 addi r15, r15, 1
  B  440 addi r16, r16, 1
--- replace mine 441:442 base 442:443
  M  441 extsh r0, r15
  B  442 extsh r0, r16
--- replace mine 443:446 base 444:447
  M  443 blt -76
  M  444 mr r3, r24
  M  445 extsh r4, r25
  B  444 blt -92
  B  445 mr r3, r31
  B  446 mr r4, r30
--- replace mine 447:448 base 448:449
  M  447 li r16, 2
  B  448 li r15, 2
--- replace mine 454:456 base 455:457
  M  454 mr r3, r29
  M  455 mr r4, r30
  B  455 mr r3, r25
  B  456 mr r4, r26
--- replace mine 457:459 base 458:460
  M  457 mr r3, r29
  M  458 mr r4, r30
  B  458 mr r3, r25
  B  459 mr r4, r26
--- replace mine 461:463 base 462:464
  M  461 mr r3, r29
  M  462 mr r4, r30
  B  462 mr r3, r25
  B  463 mr r4, r26
--- replace mine 467:468 base 468:469
  M  467 addi r3, r26, 0x505
  B  468 addi r3, r22, 0x505
--- replace mine 471:475 base 472:476
  M  471 mr r3, r29
  M  472 mr r4, r30
  M  473 li r22, 1
  M  474 li r16, 3
  B  472 mr r3, r25
  B  473 mr r4, r26
  B  474 li r28, 1
  B  475 li r15, 3
--- replace mine 479:480 base 480:484
  M  479 mr r3, r29
  B  480 mr r3, r25
  B  481 mr r4, r26
  B  482 bl 0
  B  483 mr r3, r31
--- delete mine 481:484 base 485:485
  M  481 bl 0
  M  482 mr r3, r24
  M  483 mr r4, r25
--- replace mine 485:486 base 486:487
  M  485 li r16, 4
  B  486 li r15, 4
--- replace mine 490:492 base 491:493
  M  490 mr r3, r24
  M  491 extsh r4, r25
  B  491 mr r3, r31
  B  492 mr r4, r30
--- replace mine 493:494 base 494:495
  M  493 li r16, 5
  B  494 li r15, 5
--- replace mine 500:501 base 501:502
  M  500 cmpwi r16, 3
  B  501 cmpwi r15, 3
--- replace mine 503:504 base 504:505
  M  503 cmpwi r16, 1
  B  504 cmpwi r15, 1
--- replace mine 506:507 base 507:508
  M  506 cmpwi r16, 0
  B  507 cmpwi r15, 0
--- replace mine 509:510 base 510:511
  M  509 cmpwi r16, 5
  B  510 cmpwi r15, 5
--- replace mine 513:514 base 514:515
  M  513 addi r3, r26, 0x526
  B  514 addi r3, r22, 0x526
--- replace mine 517:518 base 518:519
  M  517 addi r3, r26, 0x546
  B  518 addi r3, r22, 0x546
--- replace mine 521:522 base 522:523
  M  521 addi r3, r26, 0x565
  B  522 addi r3, r22, 0x565
--- replace mine 525:526 base 526:527
  M  525 addi r3, r26, 0x57c
  B  526 addi r3, r22, 0x57c
--- replace mine 529:530 base 530:531
  M  529 addi r3, r26, 0x593
  B  530 addi r3, r22, 0x593
--- replace mine 533:534 base 534:535
  M  533 addi r3, r26, 0x4e3
  B  534 addi r3, r22, 0x4e3
--- replace mine 538:539 base 539:540
  M  538 mr r3, r29
  B  539 mr r3, r25
--- replace mine 540:541 base 541:542
  M  540 mr r3, r24
  B  541 mr r3, r31
--- replace mine 542:544 base 543:545
  M  542 mr r3, r29
  M  543 clrlwi r5, r30, 0x18
  B  543 mr r3, r25
  B  544 clrlwi r5, r26, 0x18
--- replace mine 546:549 base 547:550
  M  546 mr r3, r24
  M  547 mr r4, r31
  M  548 clrlwi r5, r25, 0x18
  B  547 mr r3, r31
  B  548 mr r4, r27
  B  549 clrlwi r5, r30, 0x18
--- replace mine 551:552 base 552:553
  M  551 xori r15, r29, 1
  B  552 xori r15, r25, 1
--- replace mine 558:559 base 559:560
  M  558 mr r4, r31
  B  559 mr r4, r27
--- replace mine 561:562 base 562:563
  M  561 cmpwi r23, 0
  B  562 cmpwi r29, 0
--- replace mine 563:564 base 564:565
  M  563 cmpwi r22, 0
  B  564 cmpwi r28, 0
--- replace mine 566:567 base 567:568
  M  566 extsh r4, r25
  B  567 extsh r4, r30
--- replace mine 568:569 base 569:570
  M  568 cmpwi r22, 0
  B  569 cmpwi r28, 0
--- replace mine 571:572 base 572:573
  M  571 extsh r4, r25
  B  572 extsh r4, r30
--- replace mine 577:578 base 578:579
  M  577 extsh r4, r25
  B  578 extsh r4, r30
--- replace mine 583:584 base 584:585
  M  583 clrlwi r5, r30, 0x18
  B  584 clrlwi r5, r26, 0x18
--- replace mine 586:587 base 587:588
  M  586 mr r3, r29
  B  587 mr r3, r25
--- replace mine 591:593 base 592:594
  M  591 mr r3, r29
  M  592 mr r4, r31
  B  592 mr r3, r25
  B  593 mr r4, r27
--- replace mine 595:596 base 596:597
  M  595 mr r3, r29
  B  596 mr r3, r25
--- replace mine 597:599 base 598:600
  M  597 mr r3, r29
  M  598 clrlwi r5, r30, 0x18
  B  598 mr r3, r25
  B  599 clrlwi r5, r26, 0x18
```

## src/scene/cardSequence/iplCardSequence: CardSequence_813D3424

```text
src 0x7cc base 0x800 insns 499/512
--- replace mine 5:8 base 5:8
  M    5 mr r31, r5
  M    6 mr r29, r3
  M    7 mr r30, r4
  B    5 mr r26, r5
  B    6 mr r24, r3
  B    7 mr r25, r4
--- replace mine 12:16 base 12:16
  M   12 b 1924
  M   13 lbz r0, 7(r31)
  M   14 li r7, 0
  M   15 lwz r3, 0x2c(r31)
  B   12 b 1976
  B   13 lbz r0, 7(r26)
  B   14 li r8, 0
  B   15 lwz r3, 0x2c(r26)
--- replace mine 18:20 base 18:20
  M   18 rlwinm r24, r3, 0, 0, 0x16
  M   19 subf r23, r24, r3
  B   18 rlwinm r31, r3, 0, 0, 0x16
  B   19 subf r23, r31, r3
--- replace mine 26:28 base 26:28
  M   26 mulli r27, r29, 0x1fc0
  M   27 slwi r28, r30, 6
  B   26 mulli r29, r24, 0x1fc0
  B   27 slwi r30, r25, 6
--- replace mine 29:30 base 29:30
  M   29 add r0, r0, r27
  B   29 add r0, r0, r29
--- replace mine 31:33 base 31:33
  M   31 add r3, r0, r28
  M   32 slwi r26, r30, 2
  B   31 add r3, r0, r30
  B   32 slwi r28, r25, 2
--- replace mine 34:35 base 34:35
  M   34 li r7, 0xe00
  B   34 li r8, 0xe00
--- replace mine 36:37 base 36:37
  M   36 mulli r25, r29, 0x1fc
  B   36 mulli r27, r24, 0x1fc
--- replace mine 39:41 base 39:41
  M   39 add r0, r0, r27
  M   40 add r3, r0, r28
  B   39 add r0, r0, r29
  B   40 add r3, r0, r30
--- replace mine 44:48 base 44:48
  M   44 add r4, r3, r27
  M   45 add r0, r3, r25
  M   46 add r3, r0, r26
  M   47 add r4, r4, r28
  B   44 add r4, r3, r29
  B   45 add r0, r3, r27
  B   46 add r3, r0, r28
  B   47 add r4, r4, r30
--- replace mine 54:56 base 54:56
  M   54 add r0, r0, r27
  M   55 add r4, r0, r28
  B   54 add r0, r0, r29
  B   55 add r4, r0, r30
--- replace mine 61:63 base 61:63
  M   61 add r0, r0, r27
  M   62 add r4, r0, r28
  B   61 add r0, r0, r29
  B   62 add r4, r0, r30
--- replace mine 68:70 base 68:70
  M   68 mulli r27, r29, 0x1fc0
  M   69 slwi r28, r30, 6
  B   68 mulli r29, r24, 0x1fc0
  B   69 slwi r30, r25, 6
--- replace mine 71:72 base 71:72
  M   71 add r0, r0, r27
  B   71 add r0, r0, r29
--- replace mine 73:75 base 73:75
  M   73 add r3, r0, r28
  M   74 slwi r26, r30, 2
  B   73 add r3, r0, r30
  B   74 slwi r28, r25, 2
--- replace mine 76:77 base 76:77
  M   76 li r7, 0x1800
  B   76 li r8, 0x1800
--- replace mine 78:79 base 78:79
  M   78 mulli r25, r29, 0x1fc
  B   78 mulli r27, r24, 0x1fc
--- replace mine 81:83 base 81:83
  M   81 add r0, r0, r27
  M   82 add r3, r0, r28
  B   81 add r0, r0, r29
  B   82 add r3, r0, r30
--- replace mine 86:90 base 86:90
  M   86 add r4, r3, r27
  M   87 add r0, r3, r25
  M   88 add r3, r0, r26
  M   89 add r4, r4, r28
  B   86 add r4, r3, r29
  B   87 add r0, r3, r27
  B   88 add r3, r0, r28
  B   89 add r4, r4, r30
--- replace mine 96:98 base 96:98
  M   96 add r0, r0, r27
  M   97 add r4, r0, r28
  B   96 add r0, r0, r29
  B   97 add r4, r0, r30
--- replace mine 103:105 base 103:105
  M  103 mulli r27, r29, 0x1fc0
  M  104 slwi r28, r30, 6
  B  103 mulli r29, r24, 0x1fc0
  B  104 slwi r30, r25, 6
--- replace mine 106:107 base 106:107
  M  106 add r0, r0, r27
  B  106 add r0, r0, r29
--- replace mine 108:110 base 108:110
  M  108 add r3, r0, r28
  M  109 slwi r26, r30, 2
  B  108 add r3, r0, r30
  B  109 slwi r28, r25, 2
--- replace mine 111:112 base 111:112
  M  111 mulli r25, r29, 0x1fc
  B  111 mulli r27, r24, 0x1fc
--- replace mine 114:116 base 114:116
  M  114 add r0, r0, r27
  M  115 add r3, r0, r28
  B  114 add r0, r0, r29
  B  115 add r3, r0, r30
--- replace mine 119:123 base 119:123
  M  119 add r0, r3, r25
  M  120 add r4, r3, r27
  M  121 add r3, r0, r26
  M  122 add r4, r4, r28
  B  119 add r0, r3, r27
  B  120 add r4, r3, r29
  B  121 add r3, r0, r28
  B  122 add r4, r4, r30
--- replace mine 127:128 base 127:128
  M  127 lwz r5, 0(0)
  B  127 lwz r4, 0(0)
--- replace mine 130:135 base 130:132
  M  130 add r4, r27, r28
  M  131 addis r5, r5, 1
  M  132 li r8, 0
  M  133 add r6, r5, r27
  M  134 add r6, r6, r28
  B  130 add r9, r29, r30
  B  131 addis r4, r4, 1
--- replace mine 136:155 base 133:156
  M  136 stb r3, -0x6fba(r6)
  M  137 lwz r6, 0(0)
  M  138 addis r6, r6, 1
  M  139 add r6, r6, r27
  M  140 add r6, r6, r28
  M  141 sth r3, -0x6faa(r6)
  M  142 lwz r6, 0(0)
  M  143 lhz r9, 0x32(r31)
  M  144 addis r6, r6, 1
  M  145 add r6, r6, r27
  M  146 add r6, r6, r28
  M  147 sth r9, -0x6fac(r6)
  M  148 lwz r6, 0(0)
  M  149 lhz r9, 0x32(r31)
  M  150 addis r6, r6, 1
  M  151 add r6, r6, r27
  M  152 rlwinm r9, r9, 2, 0x1c, 0x1d
  M  153 add r6, r6, r28
  M  154 stb r9, -0x6fb6(r6)
  B  133 add r4, r4, r29
  B  134 li r7, 0
  B  135 add r4, r4, r30
  B  136 stb r3, -0x6fba(r4)
  B  137 li r4, 0
  B  138 lwz r10, 0(0)
  B  139 addis r10, r10, 1
  B  140 add r10, r10, r29
  B  141 add r10, r10, r30
  B  142 sth r3, -0x6faa(r10)
  B  143 lwz r10, 0(0)
  B  144 lhz r11, 0x32(r26)
  B  145 addis r10, r10, 1
  B  146 add r10, r10, r29
  B  147 add r10, r10, r30
  B  148 sth r11, -0x6fac(r10)
  B  149 lwz r10, 0(0)
  B  150 lhz r11, 0x32(r26)
  B  151 addis r10, r10, 1
  B  152 add r10, r10, r29
  B  153 rlwinm r11, r11, 2, 0x1c, 0x1d
  B  154 add r10, r10, r30
  B  155 stb r11, -0x6fb6(r10)
--- replace mine 156:158 base 157:159
  M  156 lhz r6, 0x32(r31)
  M  157 sraw r0, r6, r3
  B  157 lhz r10, 0x32(r26)
  B  158 sraw r0, r10, r3
--- replace mine 160:167 base 161:168
  M  160 lwz r9, 0(0)
  M  161 slwi r6, r0, 2
  M  162 addis r9, r9, 1
  M  163 addi r9, r9, -0x6faa
  M  164 lhax r0, r4, r9
  M  165 add r0, r6, r0
  M  166 sthx r0, r4, r9
  B  161 lwz r10, 0(0)
  B  162 slwi r0, r0, 2
  B  163 addis r10, r10, 1
  B  164 addi r11, r10, -0x6faa
  B  165 lhax r10, r9, r11
  B  166 add r0, r10, r0
  B  167 sthx r0, r9, r11
--- replace mine 169:171 base 170:172
  M  169 addi r0, r5, -1
  M  170 slwi r5, r0, 1
  B  170 addi r0, r4, -1
  B  171 slwi r4, r0, 1
--- replace mine 172:177 base 173:178
  M  172 sraw r3, r6, r5
  M  173 add r0, r0, r27
  M  174 rlwinm r5, r3, 2, 0x1c, 0x1d
  M  175 add r3, r0, r28
  M  176 stb r5, -0x6fb5(r3)
  B  173 sraw r3, r10, r4
  B  174 add r0, r0, r29
  B  175 rlwinm r4, r3, 2, 0x1c, 0x1d
  B  176 add r3, r0, r30
  B  177 stb r4, -0x6fb5(r3)
--- replace mine 178:179 base 179:180
  M  178 addi r5, r5, 1
  B  179 addi r4, r4, 1
--- replace mine 182:183 base 183:184
  M  182 lhz r5, 0x32(r31)
  B  183 lhz r4, 0x32(r26)
--- replace mine 184:189 base 185:190
  M  184 add r0, r0, r27
  M  185 rlwinm r5, r5, 0x14, 0x1c, 0x1d
  M  186 add r3, r0, r28
  M  187 stb r5, -0x6fb5(r3)
  M  188 lhz r0, 0x32(r31)
  B  185 add r0, r0, r29
  B  186 rlwinm r4, r4, 0x14, 0x1c, 0x1d
  B  187 add r3, r0, r30
  B  188 stb r4, -0x6fb5(r3)
  B  189 lhz r0, 0x32(r26)
--- replace mine 191:192 base 192:193
  M  191 lhz r0, 0x30(r31)
  B  192 lhz r0, 0x30(r26)
--- replace mine 193:194 base 194:195
  M  193 bne 32
  B  194 bne 36
--- replace mine 195:196 base 196:198
  M  195 li r8, 0
  B  196 li r4, 0
  B  197 li r7, 0
--- replace mine 197:204 base 199:205
  M  197 add r0, r0, r27
  M  198 add r3, r0, r28
  M  199 stb r8, -0x6fbb(r3)
  M  200 b 440
  M  201 li r10, 8
  M  202 li r9, 0
  M  203 li r6, 0
  B  199 add r0, r0, r29
  B  200 add r3, r0, r30
  B  201 stb r4, -0x6fbb(r3)
  B  202 b 444
  B  203 li r4, 8
  B  204 li r10, 0
--- replace mine 205:206 base 206:207
  M  205 li r5, 0
  B  206 li r12, 0
--- replace mine 208:217 base 209:218
  M  208 mtctr r10
  M  209 lhz r10, 0x32(r31)
  M  210 sraw r10, r10, r5
  M  211 clrlwi. r10, r10, 0x1e
  M  212 beq 256
  M  213 lhz r10, 0x30(r31)
  M  214 sraw r10, r10, r5
  M  215 clrlwi r10, r10, 0x1e
  M  216 cmpwi r10, 1
  B  209 mtctr r4
  B  210 lhz r4, 0x32(r26)
  B  211 sraw r4, r4, r12
  B  212 clrlwi. r4, r4, 0x1e
  B  213 beq 264
  B  214 lhz r4, 0x30(r26)
  B  215 sraw r4, r4, r12
  B  216 clrlwi r4, r4, 0x1e
  B  217 cmpwi r4, 1
--- replace mine 219:220 base 220:221
  M  219 cmpwi r10, 0
  B  220 cmpwi r4, 0
--- replace mine 221:224 base 222:225
  M  221 b 112
  M  222 cmpwi r10, 3
  M  223 bge 104
  B  222 b 108
  B  223 cmpwi r4, 3
  B  224 bge 100
--- replace mine 225:226 base 226:227
  M  225 add r9, r6, r4
  B  226 add r4, r10, r9
--- replace mine 227:234 base 228:235
  M  227 addis r9, r9, 1
  M  228 li r10, 0x400
  M  229 addi r12, r9, -0x6fb4
  M  230 stbx r3, r21, r12
  M  231 li r9, 1
  M  232 b 72
  M  233 add r10, r6, r4
  B  228 addis r4, r4, 1
  B  229 li r6, 0x400
  B  230 addi r4, r4, -0x6fb4
  B  231 li r5, 1
  B  232 stbx r3, r21, r4
  B  233 b 64
  B  234 add r4, r10, r9
--- replace mine 235:259 base 236:262
  M  235 addis r12, r10, 1
  M  236 addi r12, r12, -0x6fb4
  M  237 li r10, 0x800
  M  238 stbx r0, r21, r12
  M  239 b 44
  M  240 lwz r12, 0(0)
  M  241 li r10, 0
  M  242 addis r12, r12, 1
  M  243 add r12, r12, r27
  M  244 add r12, r12, r28
  M  245 add r21, r12, r6
  M  246 lbz r12, -0x6fb5(r21)
  M  247 stb r12, -0x6fb4(r21)
  M  248 b 8
  M  249 li r10, 0
  M  250 cmpwi r6, 7
  M  251 bge 36
  M  252 lwz r12, 0(0)
  M  253 add r12, r4, r12
  M  254 add r12, r11, r12
  M  255 addis r21, r12, 1
  M  256 lwz r12, -0x6fa0(r21)
  M  257 add r12, r10, r12
  M  258 stw r12, -0x6f9c(r21)
  B  236 addis r4, r4, 1
  B  237 li r6, 0x800
  B  238 addi r4, r4, -0x6fb4
  B  239 stbx r0, r21, r4
  B  240 b 36
  B  241 add r4, r10, r9
  B  242 lwz r21, 0(0)
  B  243 addis r4, r4, 1
  B  244 li r6, 0
  B  245 addi r22, r4, -0x6fb4
  B  246 add r22, r21, r22
  B  247 lbz r4, -1(r22)
  B  248 stb r4, 0(r22)
  B  249 cmpwi r10, 7
  B  250 bge 52
  B  251 lwz r4, 0(0)
  B  252 addis r22, r11, 1
  B  253 addi r21, r10, 1
  B  254 add r4, r9, r4
  B  255 addi r22, r22, -0x6fa0
  B  256 slwi r21, r21, 2
  B  257 lwzx r22, r4, r22
  B  258 addis r21, r21, 1
  B  259 add r22, r6, r22
  B  260 addi r21, r21, -0x6fa0
  B  261 stwx r22, r4, r21
--- replace mine 261:275 base 264:278
  M  261 addis r12, r11, 1
  M  262 addi r12, r12, -0x6fa0
  M  263 add r22, r4, r21
  M  264 lwzx r21, r22, r12
  M  265 addis r12, r22, 1
  M  266 add r21, r10, r21
  M  267 stw r21, -0x6f80(r12)
  M  268 lwz r12, 0(0)
  M  269 add r8, r8, r10
  M  270 addis r10, r12, 1
  M  271 addi r12, r10, -0x6fba
  M  272 lbzx r10, r4, r12
  M  273 addi r10, r10, 1
  M  274 stbx r10, r4, r12
  B  264 addis r4, r11, 1
  B  265 addi r4, r4, -0x6fa0
  B  266 add r22, r9, r21
  B  267 lwzx r21, r22, r4
  B  268 addis r4, r22, 1
  B  269 add r21, r6, r21
  B  270 stw r21, -0x6f80(r4)
  B  271 lwz r4, 0(0)
  B  272 add r7, r7, r6
  B  273 addis r4, r4, 1
  B  274 addi r21, r4, -0x6fba
  B  275 lbzx r4, r9, r21
  B  276 addi r4, r4, 1
  B  277 stbx r4, r9, r21
--- replace mine 277:278 base 280:281
  M  277 slwi r0, r6, 2
  B  280 slwi r0, r10, 2
--- replace mine 279:281 base 282:284
  M  279 add r3, r3, r27
  M  280 add r4, r3, r28
  B  282 add r3, r3, r29
  B  283 add r4, r3, r30
--- replace mine 285:286 base 288:289
  M  285 addi r6, r6, 1
  B  288 addi r10, r10, 1
--- replace mine 287:290 base 290:293
  M  287 addi r5, r5, 2
  M  288 bdnz -316
  M  289 cmpwi r9, 0
  B  290 addi r12, r12, 2
  B  291 bdnz -324
  B  292 cmpwi r5, 0
--- replace mine 291:292 base 294:295
  M  291 addi r8, r8, 0x200
  B  294 addi r7, r7, 0x200
--- replace mine 295:297 base 298:300
  M  295 add r0, r0, r27
  M  296 add r3, r0, r28
  B  298 add r0, r0, r29
  B  299 add r3, r0, r30
--- replace mine 299:300 base 302:303
  M  299 lbz r4, 7(r31)
  B  302 lbz r4, 7(r26)
--- replace mine 301:302 base 304:305
  M  301 add r0, r0, r27
  B  304 add r0, r0, r29
--- replace mine 303:304 base 306:307
  M  303 add r3, r0, r28
  B  306 add r3, r0, r30
--- replace mine 307:309 base 310:312
  M  307 add r0, r0, r27
  M  308 add r3, r0, r28
  B  310 add r0, r0, r29
  B  311 add r3, r0, r30
--- replace mine 310:313 base 313:316
  M  310 add r22, r7, r8
  M  311 mr r3, r29
  M  312 add r5, r22, r23
  B  313 add r21, r8, r7
  B  314 mr r3, r24
  B  315 add r5, r21, r23
--- replace mine 315:316 base 318:319
  M  315 rlwinm r21, r0, 0, 0, 0x16
  B  318 rlwinm r22, r0, 0, 0, 0x16
--- replace mine 318:332 base 321:336
  M  318 bge 52
  M  319 lwz r3, 0(0)
  M  320 li r4, 0
  M  321 addis r0, r3, 1
  M  322 add r0, r0, r27
  M  323 add r3, r0, r28
  M  324 stb r4, -0x6fbc(r3)
  M  325 lwz r3, 0(0)
  M  326 addis r0, r3, 1
  M  327 add r0, r0, r27
  M  328 add r3, r0, r28
  M  329 stb r4, -0x6fbb(r3)
  M  330 b 244
  M  331 lhz r3, 0x38(r31)
  B  321 bge 56
  B  322 lwz r4, 0(0)
  B  323 li r5, 0
  B  324 li r3, 0
  B  325 addis r0, r4, 1
  B  326 add r0, r0, r29
  B  327 add r4, r0, r30
  B  328 stb r5, -0x6fbc(r4)
  B  329 lwz r4, 0(0)
  B  330 addis r0, r4, 1
  B  331 add r0, r0, r29
  B  332 add r4, r0, r30
  B  333 stb r5, -0x6fbb(r4)
  B  334 b 256
  B  335 lhz r3, 0x38(r26)
--- replace mine 334:349 base 338:354
  M  334 cmplw r24, r3
  M  335 ble 52
  M  336 lwz r3, 0(0)
  M  337 li r4, 0
  M  338 addis r0, r3, 1
  M  339 add r0, r0, r27
  M  340 add r3, r0, r28
  M  341 stb r4, -0x6fbc(r3)
  M  342 lwz r3, 0(0)
  M  343 addis r0, r3, 1
  M  344 add r0, r0, r27
  M  345 add r3, r0, r28
  M  346 stb r4, -0x6fbb(r3)
  M  347 b 176
  M  348 add r0, r24, r21
  B  338 cmplw r31, r3
  B  339 ble 56
  B  340 lwz r4, 0(0)
  B  341 li r5, 0
  B  342 li r3, 0
  B  343 addis r0, r4, 1
  B  344 add r0, r0, r29
  B  345 add r4, r0, r30
  B  346 stb r5, -0x6fbc(r4)
  B  347 lwz r4, 0(0)
  B  348 addis r0, r4, 1
  B  349 add r0, r0, r29
  B  350 add r4, r0, r30
  B  351 stb r5, -0x6fbb(r4)
  B  352 b 184
  B  353 add r0, r31, r22
--- replace mine 350:364 base 355:370
  M  350 ble 52
  M  351 lwz r3, 0(0)
  M  352 li r4, 0
  M  353 addis r0, r3, 1
  M  354 add r0, r0, r27
  M  355 add r3, r0, r28
  M  356 stb r4, -0x6fbc(r3)
  M  357 lwz r3, 0(0)
  M  358 addis r0, r3, 1
  M  359 add r0, r0, r27
  M  360 add r3, r0, r28
  M  361 stb r4, -0x6fbb(r3)
  M  362 b 116
  M  363 cmpwi r22, 0
  B  355 ble 56
  B  356 lwz r4, 0(0)
  B  357 li r5, 0
  B  358 li r3, 0
  B  359 addis r0, r4, 1
  B  360 add r0, r0, r29
  B  361 add r4, r0, r30
  B  362 stb r5, -0x6fbc(r4)
  B  363 lwz r4, 0(0)
  B  364 addis r0, r4, 1
  B  365 add r0, r0, r29
  B  366 add r4, r0, r30
  B  367 stb r5, -0x6fbb(r4)
  B  368 b 120
  B  369 cmpwi r21, 0
--- replace mine 366:368 base 372:374
  M  366 mr r5, r21
  M  367 mr r6, r24
  B  372 mr r5, r22
  B  373 mr r6, r31
--- replace mine 373:375 base 379:381
  M  373 mr r24, r3
  M  374 blt 320
  B  379 bge 8
  B  380 b 72
--- replace mine 376:377 base 382:383
  M  376 mr r5, r22
  B  382 mr r5, r21
--- replace mine 378:379 base 384:385
  M  378 add r3, r4, r25
  B  384 add r3, r4, r27
--- replace mine 380:381 base 386:387
  M  380 add r3, r3, r26
  B  386 add r3, r3, r28
--- replace mine 385:386 base 391:392
  M  385 mr r4, r21
  B  391 mr r4, r22
--- replace mine 387:389 base 393:395
  M  387 add r0, r0, r25
  M  388 add r3, r0, r26
  B  393 add r0, r0, r27
  B  394 add r3, r0, r28
--- replace mine 391:393 base 397:403
  M  391 lwz r5, 0x3c(r31)
  M  392 mr r3, r29
  B  397 li r3, 0
  B  398 cmpwi r3, 0
  B  399 bge 8
  B  400 b 424
  B  401 lwz r5, 0x3c(r26)
  B  402 mr r3, r24
--- replace mine 395:396 base 405:406
  M  395 rlwinm r22, r5, 0, 0, 0x16
  B  405 rlwinm r23, r5, 0, 0, 0x16
--- replace mine 397:399 base 407:409
  M  397 subf r21, r22, r5
  M  398 subf r23, r22, r0
  B  407 subf r21, r23, r5
  B  408 subf r22, r23, r0
--- replace mine 401:406 base 411:416
  M  401 mr r24, r3
  M  402 blt 168
  M  403 cmpwi r22, 0
  M  404 blt 156
  M  405 lhz r3, 0x38(r31)
  B  411 mr r29, r3
  B  412 blt 180
  B  413 cmpwi r23, 0
  B  414 blt 24
  B  415 lhz r3, 0x38(r26)
--- replace mine 408:412 base 418:424
  M  408 cmplw r22, r0
  M  409 bgt 136
  M  410 add. r3, r22, r23
  M  411 blt 128
  B  418 cmplw r23, r0
  B  419 ble 12
  B  420 li r29, 0
  B  421 b 144
  B  422 add. r3, r23, r22
  B  423 blt 12
--- replace mine 413:414 base 425:428
  M  413 bgt 120
  B  425 ble 12
  B  426 li r29, 0
  B  427 b 120
--- replace mine 415:417 base 429:431
  M  415 mr r5, r23
  M  416 mr r6, r22
  B  429 mr r5, r22
  B  430 mr r6, r23
--- replace mine 422:424 base 436:438
  M  422 mr r24, r3
  M  423 blt 84
  B  436 mr r29, r3
  B  437 blt 80
--- replace mine 428:430 base 442:444
  M  428 add r0, r0, r25
  M  429 add r3, r0, r26
  B  442 add r0, r0, r27
  B  443 add r3, r0, r28
--- replace mine 435:437 base 449:451
  M  435 add r0, r4, r25
  M  436 add r3, r0, r26
  B  449 add r0, r4, r27
  B  450 add r3, r0, r28
--- replace mine 441:444 base 455:457
  M  441 li r24, 0
  M  442 b 40
  M  443 li r24, 0
  B  455 li r29, 0
  B  456 b 36
--- replace mine 448:450 base 461:463
  M  448 add r0, r0, r25
  M  449 add r3, r0, r26
  B  461 add r0, r0, r27
  B  462 add r3, r0, r28
--- replace mine 452:453 base 465:466
  M  452 cmpwi r24, 0
  B  465 cmpwi r29, 0
--- replace mine 454:455 base 467:468
  M  454 mr r3, r24
  B  467 mr r3, r29
--- replace mine 461:462 base 474:475
  M  461 mulli r7, r29, 0x5f4
  B  474 mulli r7, r24, 0x5f4
--- replace mine 465:466 base 478:479
  M  465 mulli r6, r30, 0xc
  B  478 mulli r6, r25, 0xc
--- replace mine 470:471 base 483:484
  M  470 lhz r5, 0x38(r31)
  B  483 lhz r5, 0x38(r26)
--- replace mine 475:476 base 488:489
  M  475 lwz r5, 0x28(r31)
  B  488 lwz r5, 0x28(r26)
--- replace mine 479:480 base 492:493
  M  479 lbz r4, 0x34(r31)
  B  492 lbz r4, 0x34(r26)
--- replace mine 486:487 base 499:500
  M  486 lbz r4, 0x34(r31)
  B  499 lbz r4, 0x34(r26)
```

- stack record order: sector-size members both unsigned with file handle first: exact False; insns 499/512; differences None; objdiff 89.42969

```text
src 0x7cc base 0x800 insns 499/512
--- replace mine 5:9 base 5:9
  M    5 mr r31, r5
  M    6 mr r29, r3
  M    7 mr r30, r4
  M    8 addi r5, r1, 8
  B    5 mr r26, r5
  B    6 mr r24, r3
  B    7 mr r25, r4
  B    8 addi r5, r1, 0x10
--- replace mine 12:16 base 12:16
  M   12 b 1924
  M   13 lbz r0, 7(r31)
  M   14 li r7, 0
  M   15 lwz r3, 0x2c(r31)
  B   12 b 1976
  B   13 lbz r0, 7(r26)
  B   14 li r8, 0
  B   15 lwz r3, 0x2c(r26)
--- replace mine 18:20 base 18:20
  M   18 rlwinm r24, r3, 0, 0, 0x16
  M   19 subf r23, r24, r3
  B   18 rlwinm r31, r3, 0, 0, 0x16
  B   19 subf r23, r31, r3
--- replace mine 26:28 base 26:28
  M   26 mulli r27, r29, 0x1fc0
  M   27 slwi r28, r30, 6
  B   26 mulli r29, r24, 0x1fc0
  B   27 slwi r30, r25, 6
--- replace mine 29:30 base 29:30
  M   29 add r0, r0, r27
  B   29 add r0, r0, r29
--- replace mine 31:33 base 31:33
  M   31 add r3, r0, r28
  M   32 slwi r26, r30, 2
  B   31 add r3, r0, r30
  B   32 slwi r28, r25, 2
--- replace mine 34:35 base 34:35
  M   34 li r7, 0xe00
  B   34 li r8, 0xe00
--- replace mine 36:37 base 36:37
  M   36 mulli r25, r29, 0x1fc
  B   36 mulli r27, r24, 0x1fc
--- replace mine 39:41 base 39:41
  M   39 add r0, r0, r27
  M   40 add r3, r0, r28
  B   39 add r0, r0, r29
  B   40 add r3, r0, r30
--- replace mine 44:48 base 44:48
  M   44 add r4, r3, r27
  M   45 add r0, r3, r25
  M   46 add r3, r0, r26
  M   47 add r4, r4, r28
  B   44 add r4, r3, r29
  B   45 add r0, r3, r27
  B   46 add r3, r0, r28
  B   47 add r4, r4, r30
--- replace mine 54:56 base 54:56
  M   54 add r0, r0, r27
  M   55 add r4, r0, r28
  B   54 add r0, r0, r29
  B   55 add r4, r0, r30
--- replace mine 61:63 base 61:63
  M   61 add r0, r0, r27
  M   62 add r4, r0, r28
  B   61 add r0, r0, r29
  B   62 add r4, r0, r30
--- replace mine 68:70 base 68:70
  M   68 mulli r27, r29, 0x1fc0
  M   69 slwi r28, r30, 6
  B   68 mulli r29, r24, 0x1fc0
  B   69 slwi r30, r25, 6
--- replace mine 71:72 base 71:72
  M   71 add r0, r0, r27
  B   71 add r0, r0, r29
--- replace mine 73:75 base 73:75
  M   73 add r3, r0, r28
  M   74 slwi r26, r30, 2
  B   73 add r3, r0, r30
  B   74 slwi r28, r25, 2
--- replace mine 76:77 base 76:77
  M   76 li r7, 0x1800
  B   76 li r8, 0x1800
--- replace mine 78:79 base 78:79
  M   78 mulli r25, r29, 0x1fc
  B   78 mulli r27, r24, 0x1fc
--- replace mine 81:83 base 81:83
  M   81 add r0, r0, r27
  M   82 add r3, r0, r28
  B   81 add r0, r0, r29
  B   82 add r3, r0, r30
--- replace mine 86:90 base 86:90
  M   86 add r4, r3, r27
  M   87 add r0, r3, r25
  M   88 add r3, r0, r26
  M   89 add r4, r4, r28
  B   86 add r4, r3, r29
  B   87 add r0, r3, r27
  B   88 add r3, r0, r28
  B   89 add r4, r4, r30
--- replace mine 96:98 base 96:98
  M   96 add r0, r0, r27
  M   97 add r4, r0, r28
  B   96 add r0, r0, r29
  B   97 add r4, r0, r30
--- replace mine 103:105 base 103:105
  M  103 mulli r27, r29, 0x1fc0
  M  104 slwi r28, r30, 6
  B  103 mulli r29, r24, 0x1fc0
  B  104 slwi r30, r25, 6
--- replace mine 106:107 base 106:107
  M  106 add r0, r0, r27
  B  106 add r0, r0, r29
--- replace mine 108:110 base 108:110
  M  108 add r3, r0, r28
  M  109 slwi r26, r30, 2
  B  108 add r3, r0, r30
  B  109 slwi r28, r25, 2
--- replace mine 111:112 base 111:112
  M  111 mulli r25, r29, 0x1fc
  B  111 mulli r27, r24, 0x1fc
--- replace mine 114:116 base 114:116
  M  114 add r0, r0, r27
  M  115 add r3, r0, r28
  B  114 add r0, r0, r29
  B  115 add r3, r0, r30
--- replace mine 119:123 base 119:123
  M  119 add r0, r3, r25
  M  120 add r4, r3, r27
  M  121 add r3, r0, r26
  M  122 add r4, r4, r28
  B  119 add r0, r3, r27
  B  120 add r4, r3, r29
  B  121 add r3, r0, r28
  B  122 add r4, r4, r30
--- replace mine 127:128 base 127:128
  M  127 lwz r5, 0(0)
  B  127 lwz r4, 0(0)
--- replace mine 130:135 base 130:132
  M  130 add r4, r27, r28
  M  131 addis r5, r5, 1
  M  132 li r8, 0
  M  133 add r6, r5, r27
  M  134 add r6, r6, r28
  B  130 add r9, r29, r30
  B  131 addis r4, r4, 1
--- replace mine 136:155 base 133:156
  M  136 stb r3, -0x6fba(r6)
  M  137 lwz r6, 0(0)
  M  138 addis r6, r6, 1
  M  139 add r6, r6, r27
  M  140 add r6, r6, r28
  M  141 sth r3, -0x6faa(r6)
  M  142 lwz r6, 0(0)
  M  143 lhz r9, 0x32(r31)
  M  144 addis r6, r6, 1
  M  145 add r6, r6, r27
  M  146 add r6, r6, r28
  M  147 sth r9, -0x6fac(r6)
  M  148 lwz r6, 0(0)
  M  149 lhz r9, 0x32(r31)
  M  150 addis r6, r6, 1
  M  151 add r6, r6, r27
  M  152 rlwinm r9, r9, 2, 0x1c, 0x1d
  M  153 add r6, r6, r28
  M  154 stb r9, -0x6fb6(r6)
  B  133 add r4, r4, r29
  B  134 li r7, 0
  B  135 add r4, r4, r30
  B  136 stb r3, -0x6fba(r4)
  B  137 li r4, 0
  B  138 lwz r10, 0(0)
  B  139 addis r10, r10, 1
  B  140 add r10, r10, r29
  B  141 add r10, r10, r30
  B  142 sth r3, -0x6faa(r10)
  B  143 lwz r10, 0(0)
  B  144 lhz r11, 0x32(r26)
  B  145 addis r10, r10, 1
  B  146 add r10, r10, r29
  B  147 add r10, r10, r30
  B  148 sth r11, -0x6fac(r10)
  B  149 lwz r10, 0(0)
  B  150 lhz r11, 0x32(r26)
  B  151 addis r10, r10, 1
  B  152 add r10, r10, r29
  B  153 rlwinm r11, r11, 2, 0x1c, 0x1d
  B  154 add r10, r10, r30
  B  155 stb r11, -0x6fb6(r10)
--- replace mine 156:158 base 157:159
  M  156 lhz r6, 0x32(r31)
  M  157 sraw r0, r6, r3
  B  157 lhz r10, 0x32(r26)
  B  158 sraw r0, r10, r3
--- replace mine 160:167 base 161:168
  M  160 lwz r9, 0(0)
  M  161 slwi r6, r0, 2
  M  162 addis r9, r9, 1
  M  163 addi r9, r9, -0x6faa
  M  164 lhax r0, r4, r9
  M  165 add r0, r6, r0
  M  166 sthx r0, r4, r9
  B  161 lwz r10, 0(0)
  B  162 slwi r0, r0, 2
  B  163 addis r10, r10, 1
  B  164 addi r11, r10, -0x6faa
  B  165 lhax r10, r9, r11
  B  166 add r0, r10, r0
  B  167 sthx r0, r9, r11
--- replace mine 169:171 base 170:172
  M  169 addi r0, r5, -1
  M  170 slwi r5, r0, 1
  B  170 addi r0, r4, -1
  B  171 slwi r4, r0, 1
--- replace mine 172:177 base 173:178
  M  172 sraw r3, r6, r5
  M  173 add r0, r0, r27
  M  174 rlwinm r5, r3, 2, 0x1c, 0x1d
  M  175 add r3, r0, r28
  M  176 stb r5, -0x6fb5(r3)
  B  173 sraw r3, r10, r4
  B  174 add r0, r0, r29
  B  175 rlwinm r4, r3, 2, 0x1c, 0x1d
  B  176 add r3, r0, r30
  B  177 stb r4, -0x6fb5(r3)
--- replace mine 178:179 base 179:180
  M  178 addi r5, r5, 1
  B  179 addi r4, r4, 1
--- replace mine 182:183 base 183:184
  M  182 lhz r5, 0x32(r31)
  B  183 lhz r4, 0x32(r26)
--- replace mine 184:189 base 185:190
  M  184 add r0, r0, r27
  M  185 rlwinm r5, r5, 0x14, 0x1c, 0x1d
  M  186 add r3, r0, r28
  M  187 stb r5, -0x6fb5(r3)
  M  188 lhz r0, 0x32(r31)
  B  185 add r0, r0, r29
  B  186 rlwinm r4, r4, 0x14, 0x1c, 0x1d
  B  187 add r3, r0, r30
  B  188 stb r4, -0x6fb5(r3)
  B  189 lhz r0, 0x32(r26)
--- replace mine 191:192 base 192:193
  M  191 lhz r0, 0x30(r31)
  B  192 lhz r0, 0x30(r26)
--- replace mine 193:194 base 194:195
  M  193 bne 32
  B  194 bne 36
--- replace mine 195:196 base 196:198
  M  195 li r8, 0
  B  196 li r4, 0
  B  197 li r7, 0
--- replace mine 197:204 base 199:205
  M  197 add r0, r0, r27
  M  198 add r3, r0, r28
  M  199 stb r8, -0x6fbb(r3)
  M  200 b 440
  M  201 li r10, 8
  M  202 li r9, 0
  M  203 li r6, 0
  B  199 add r0, r0, r29
  B  200 add r3, r0, r30
  B  201 stb r4, -0x6fbb(r3)
  B  202 b 444
  B  203 li r4, 8
  B  204 li r10, 0
--- replace mine 205:206 base 206:207
  M  205 li r5, 0
  B  206 li r12, 0
--- replace mine 208:217 base 209:218
  M  208 mtctr r10
  M  209 lhz r10, 0x32(r31)
  M  210 sraw r10, r10, r5
  M  211 clrlwi. r10, r10, 0x1e
  M  212 beq 256
  M  213 lhz r10, 0x30(r31)
  M  214 sraw r10, r10, r5
  M  215 clrlwi r10, r10, 0x1e
  M  216 cmpwi r10, 1
  B  209 mtctr r4
  B  210 lhz r4, 0x32(r26)
  B  211 sraw r4, r4, r12
  B  212 clrlwi. r4, r4, 0x1e
  B  213 beq 264
  B  214 lhz r4, 0x30(r26)
  B  215 sraw r4, r4, r12
  B  216 clrlwi r4, r4, 0x1e
  B  217 cmpwi r4, 1
--- replace mine 219:220 base 220:221
  M  219 cmpwi r10, 0
  B  220 cmpwi r4, 0
--- replace mine 221:224 base 222:225
  M  221 b 112
  M  222 cmpwi r10, 3
  M  223 bge 104
  B  222 b 108
  B  223 cmpwi r4, 3
  B  224 bge 100
--- replace mine 225:226 base 226:227
  M  225 add r9, r6, r4
  B  226 add r4, r10, r9
--- replace mine 227:234 base 228:235
  M  227 addis r9, r9, 1
  M  228 li r10, 0x400
  M  229 addi r12, r9, -0x6fb4
  M  230 stbx r3, r21, r12
  M  231 li r9, 1
  M  232 b 72
  M  233 add r10, r6, r4
  B  228 addis r4, r4, 1
  B  229 li r6, 0x400
  B  230 addi r4, r4, -0x6fb4
  B  231 li r5, 1
  B  232 stbx r3, r21, r4
  B  233 b 64
  B  234 add r4, r10, r9
--- replace mine 235:259 base 236:262
  M  235 addis r12, r10, 1
  M  236 addi r12, r12, -0x6fb4
  M  237 li r10, 0x800
  M  238 stbx r0, r21, r12
  M  239 b 44
  M  240 lwz r12, 0(0)
  M  241 li r10, 0
  M  242 addis r12, r12, 1
  M  243 add r12, r12, r27
  M  244 add r12, r12, r28
  M  245 add r21, r12, r6
  M  246 lbz r12, -0x6fb5(r21)
  M  247 stb r12, -0x6fb4(r21)
  M  248 b 8
  M  249 li r10, 0
  M  250 cmpwi r6, 7
  M  251 bge 36
  M  252 lwz r12, 0(0)
  M  253 add r12, r4, r12
  M  254 add r12, r11, r12
  M  255 addis r21, r12, 1
  M  256 lwz r12, -0x6fa0(r21)
  M  257 add r12, r10, r12
  M  258 stw r12, -0x6f9c(r21)
  B  236 addis r4, r4, 1
  B  237 li r6, 0x800
  B  238 addi r4, r4, -0x6fb4
  B  239 stbx r0, r21, r4
  B  240 b 36
  B  241 add r4, r10, r9
  B  242 lwz r21, 0(0)
  B  243 addis r4, r4, 1
  B  244 li r6, 0
  B  245 addi r22, r4, -0x6fb4
  B  246 add r22, r21, r22
  B  247 lbz r4, -1(r22)
  B  248 stb r4, 0(r22)
  B  249 cmpwi r10, 7
  B  250 bge 52
  B  251 lwz r4, 0(0)
  B  252 addis r22, r11, 1
  B  253 addi r21, r10, 1
  B  254 add r4, r9, r4
  B  255 addi r22, r22, -0x6fa0
  B  256 slwi r21, r21, 2
  B  257 lwzx r22, r4, r22
  B  258 addis r21, r21, 1
  B  259 add r22, r6, r22
  B  260 addi r21, r21, -0x6fa0
  B  261 stwx r22, r4, r21
--- replace mine 261:275 base 264:278
  M  261 addis r12, r11, 1
  M  262 addi r12, r12, -0x6fa0
  M  263 add r22, r4, r21
  M  264 lwzx r21, r22, r12
  M  265 addis r12, r22, 1
  M  266 add r21, r10, r21
  M  267 stw r21, -0x6f80(r12)
  M  268 lwz r12, 0(0)
  M  269 add r8, r8, r10
  M  270 addis r10, r12, 1
  M  271 addi r12, r10, -0x6fba
  M  272 lbzx r10, r4, r12
  M  273 addi r10, r10, 1
  M  274 stbx r10, r4, r12
  B  264 addis r4, r11, 1
  B  265 addi r4, r4, -0x6fa0
  B  266 add r22, r9, r21
  B  267 lwzx r21, r22, r4
  B  268 addis r4, r22, 1
  B  269 add r21, r6, r21
  B  270 stw r21, -0x6f80(r4)
  B  271 lwz r4, 0(0)
  B  272 add r7, r7, r6
  B  273 addis r4, r4, 1
  B  274 addi r21, r4, -0x6fba
  B  275 lbzx r4, r9, r21
  B  276 addi r4, r4, 1
  B  277 stbx r4, r9, r21
--- replace mine 277:278 base 280:281
  M  277 slwi r0, r6, 2
  B  280 slwi r0, r10, 2
--- replace mine 279:281 base 282:284
  M  279 add r3, r3, r27
  M  280 add r4, r3, r28
  B  282 add r3, r3, r29
  B  283 add r4, r3, r30
--- replace mine 285:286 base 288:289
  M  285 addi r6, r6, 1
  B  288 addi r10, r10, 1
--- replace mine 287:290 base 290:293
  M  287 addi r5, r5, 2
  M  288 bdnz -316
  M  289 cmpwi r9, 0
  B  290 addi r12, r12, 2
  B  291 bdnz -324
  B  292 cmpwi r5, 0
--- replace mine 291:292 base 294:295
  M  291 addi r8, r8, 0x200
  B  294 addi r7, r7, 0x200
--- replace mine 295:297 base 298:300
  M  295 add r0, r0, r27
  M  296 add r3, r0, r28
  B  298 add r0, r0, r29
  B  299 add r3, r0, r30
--- replace mine 299:300 base 302:303
  M  299 lbz r4, 7(r31)
  B  302 lbz r4, 7(r26)
--- replace mine 301:302 base 304:305
  M  301 add r0, r0, r27
  B  304 add r0, r0, r29
--- replace mine 303:304 base 306:307
  M  303 add r3, r0, r28
  B  306 add r3, r0, r30
--- replace mine 307:309 base 310:312
  M  307 add r0, r0, r27
  M  308 add r3, r0, r28
  B  310 add r0, r0, r29
  B  311 add r3, r0, r30
--- replace mine 310:314 base 313:317
  M  310 add r22, r7, r8
  M  311 mr r3, r29
  M  312 add r5, r22, r23
  M  313 addi r4, r1, 0x1c
  B  313 add r21, r8, r7
  B  314 mr r3, r24
  B  315 add r5, r21, r23
  B  316 addi r4, r1, 0xc
--- replace mine 315:316 base 318:319
  M  315 rlwinm r21, r0, 0, 0, 0x16
  B  318 rlwinm r22, r0, 0, 0, 0x16
--- replace mine 318:333 base 321:337
  M  318 bge 52
  M  319 lwz r3, 0(0)
  M  320 li r4, 0
  M  321 addis r0, r3, 1
  M  322 add r0, r0, r27
  M  323 add r3, r0, r28
  M  324 stb r4, -0x6fbc(r3)
  M  325 lwz r3, 0(0)
  M  326 addis r0, r3, 1
  M  327 add r0, r0, r27
  M  328 add r3, r0, r28
  M  329 stb r4, -0x6fbb(r3)
  M  330 b 244
  M  331 lhz r3, 0x38(r31)
  M  332 lwz r0, 0x1c(r1)
  B  321 bge 56
  B  322 lwz r4, 0(0)
  B  323 li r5, 0
  B  324 li r3, 0
  B  325 addis r0, r4, 1
  B  326 add r0, r0, r29
  B  327 add r4, r0, r30
  B  328 stb r5, -0x6fbc(r4)
  B  329 lwz r4, 0(0)
  B  330 addis r0, r4, 1
  B  331 add r0, r0, r29
  B  332 add r4, r0, r30
  B  333 stb r5, -0x6fbb(r4)
  B  334 b 256
  B  335 lhz r3, 0x38(r26)
  B  336 lwz r0, 0xc(r1)
--- replace mine 334:349 base 338:354
  M  334 cmplw r24, r3
  M  335 ble 52
  M  336 lwz r3, 0(0)
  M  337 li r4, 0
  M  338 addis r0, r3, 1
  M  339 add r0, r0, r27
  M  340 add r3, r0, r28
  M  341 stb r4, -0x6fbc(r3)
  M  342 lwz r3, 0(0)
  M  343 addis r0, r3, 1
  M  344 add r0, r0, r27
  M  345 add r3, r0, r28
  M  346 stb r4, -0x6fbb(r3)
  M  347 b 176
  M  348 add r0, r24, r21
  B  338 cmplw r31, r3
  B  339 ble 56
  B  340 lwz r4, 0(0)
  B  341 li r5, 0
  B  342 li r3, 0
  B  343 addis r0, r4, 1
  B  344 add r0, r0, r29
  B  345 add r4, r0, r30
  B  346 stb r5, -0x6fbc(r4)
  B  347 lwz r4, 0(0)
  B  348 addis r0, r4, 1
  B  349 add r0, r0, r29
  B  350 add r4, r0, r30
  B  351 stb r5, -0x6fbb(r4)
  B  352 b 184
  B  353 add r0, r31, r22
--- replace mine 350:364 base 355:370
  M  350 ble 52
  M  351 lwz r3, 0(0)
  M  352 li r4, 0
  M  353 addis r0, r3, 1
  M  354 add r0, r0, r27
  M  355 add r3, r0, r28
  M  356 stb r4, -0x6fbc(r3)
  M  357 lwz r3, 0(0)
  M  358 addis r0, r3, 1
  M  359 add r0, r0, r27
  M  360 add r3, r0, r28
  M  361 stb r4, -0x6fbb(r3)
  M  362 b 116
  M  363 cmpwi r22, 0
  B  355 ble 56
  B  356 lwz r4, 0(0)
  B  357 li r5, 0
  B  358 li r3, 0
  B  359 addis r0, r4, 1
  B  360 add r0, r0, r29
  B  361 add r4, r0, r30
  B  362 stb r5, -0x6fbc(r4)
  B  363 lwz r4, 0(0)
  B  364 addis r0, r4, 1
  B  365 add r0, r0, r29
  B  366 add r4, r0, r30
  B  367 stb r5, -0x6fbb(r4)
  B  368 b 120
  B  369 cmpwi r21, 0
--- replace mine 366:369 base 372:375
  M  366 mr r5, r21
  M  367 mr r6, r24
  M  368 addi r3, r1, 8
  B  372 mr r5, r22
  B  373 mr r6, r31
  B  374 addi r3, r1, 0x10
--- replace mine 373:375 base 379:381
  M  373 mr r24, r3
  M  374 blt 320
  B  379 bge 8
  B  380 b 72
--- replace mine 376:377 base 382:383
  M  376 mr r5, r22
  B  382 mr r5, r21
--- replace mine 378:379 base 384:385
  M  378 add r3, r4, r25
  B  384 add r3, r4, r27
--- replace mine 380:381 base 386:387
  M  380 add r3, r3, r26
  B  386 add r3, r3, r28
--- replace mine 385:386 base 391:392
  M  385 mr r4, r21
  B  391 mr r4, r22
--- replace mine 387:389 base 393:395
  M  387 add r0, r0, r25
  M  388 add r3, r0, r26
  B  393 add r0, r0, r27
  B  394 add r3, r0, r28
--- replace mine 391:394 base 397:404
  M  391 lwz r5, 0x3c(r31)
  M  392 mr r3, r29
  M  393 addi r4, r1, 0x20
  B  397 li r3, 0
  B  398 cmpwi r3, 0
  B  399 bge 8
  B  400 b 424
  B  401 lwz r5, 0x3c(r26)
  B  402 mr r3, r24
  B  403 addi r4, r1, 8
--- replace mine 395:396 base 405:406
  M  395 rlwinm r22, r5, 0, 0, 0x16
  B  405 rlwinm r23, r5, 0, 0, 0x16
--- replace mine 397:399 base 407:409
  M  397 subf r21, r22, r5
  M  398 subf r23, r22, r0
  B  407 subf r21, r23, r5
  B  408 subf r22, r23, r0
--- replace mine 401:407 base 411:417
  M  401 mr r24, r3
  M  402 blt 168
  M  403 cmpwi r22, 0
  M  404 blt 156
  M  405 lhz r3, 0x38(r31)
  M  406 lwz r0, 0x20(r1)
  B  411 mr r29, r3
  B  412 blt 180
  B  413 cmpwi r23, 0
  B  414 blt 24
  B  415 lhz r3, 0x38(r26)
  B  416 lwz r0, 8(r1)
--- replace mine 408:412 base 418:424
  M  408 cmplw r22, r0
  M  409 bgt 136
  M  410 add. r3, r22, r23
  M  411 blt 128
  B  418 cmplw r23, r0
  B  419 ble 12
  B  420 li r29, 0
  B  421 b 144
  B  422 add. r3, r23, r22
  B  423 blt 12
--- replace mine 413:414 base 425:428
  M  413 bgt 120
  B  425 ble 12
  B  426 li r29, 0
  B  427 b 120
--- replace mine 415:418 base 429:432
  M  415 mr r5, r23
  M  416 mr r6, r22
  M  417 addi r3, r1, 8
  B  429 mr r5, r22
  B  430 mr r6, r23
  B  431 addi r3, r1, 0x10
--- replace mine 422:424 base 436:438
  M  422 mr r24, r3
  M  423 blt 84
  B  436 mr r29, r3
  B  437 blt 80
--- replace mine 428:430 base 442:444
  M  428 add r0, r0, r25
  M  429 add r3, r0, r26
  B  442 add r0, r0, r27
  B  443 add r3, r0, r28
--- replace mine 435:437 base 449:451
  M  435 add r0, r4, r25
  M  436 add r3, r0, r26
  B  449 add r0, r4, r27
  B  450 add r3, r0, r28
--- replace mine 441:444 base 455:457
  M  441 li r24, 0
  M  442 b 40
  M  443 li r24, 0
  B  455 li r29, 0
  B  456 b 36
--- replace mine 448:450 base 461:463
  M  448 add r0, r0, r25
  M  449 add r3, r0, r26
  B  461 add r0, r0, r27
  B  462 add r3, r0, r28
--- replace mine 452:453 base 465:466
  M  452 cmpwi r24, 0
  B  465 cmpwi r29, 0
--- replace mine 454:455 base 467:468
  M  454 mr r3, r24
  B  467 mr r3, r29
--- replace mine 456:457 base 469:470
  M  456 addi r3, r1, 8
  B  469 addi r3, r1, 0x10
--- replace mine 461:462 base 474:475
  M  461 mulli r7, r29, 0x5f4
  B  474 mulli r7, r24, 0x5f4
--- replace mine 465:466 base 478:479
  M  465 mulli r6, r30, 0xc
  B  478 mulli r6, r25, 0xc
--- replace mine 470:471 base 483:484
  M  470 lhz r5, 0x38(r31)
  B  483 lhz r5, 0x38(r26)
--- replace mine 475:476 base 488:489
  M  475 lwz r5, 0x28(r31)
  B  488 lwz r5, 0x28(r26)
--- replace mine 479:480 base 492:493
  M  479 lbz r4, 0x34(r31)
  B  492 lbz r4, 0x34(r26)
--- replace mine 486:487 base 499:500
  M  486 lbz r4, 0x34(r31)
  B  499 lbz r4, 0x34(r26)
```

- temporary boundary: retain icon-state record across banner and animation setup: exact False; insns 384/512; differences None; objdiff 63.85547

```text
src 0x600 base 0x800 insns 384/512
--- replace mine 5:8 base 5:8
  M    5 mr r31, r5
  M    6 mr r29, r3
  M    7 mr r30, r4
  B    5 mr r26, r5
  B    6 mr r24, r3
  B    7 mr r25, r4
--- replace mine 12:19 base 12:16
  M   12 b 1464
  M   13 lwz r3, 0(0)
  M   14 mulli r27, r29, 0x1fc0
  M   15 lbz r0, 7(r31)
  M   16 slwi r28, r30, 6
  M   17 addis r3, r3, 1
  M   18 lwz r4, 0x2c(r31)
  B   12 b 1976
  B   13 lbz r0, 7(r26)
  B   14 li r8, 0
  B   15 lwz r3, 0x2c(r26)
--- delete mine 20:23 base 17:17
  M   20 add r3, r3, r27
  M   21 rlwinm r24, r4, 0, 0, 0x16
  M   22 add r3, r3, r28
--- replace mine 24:29 base 18:22
  M   24 addi r6, r3, -0x6fbc
  M   25 subf r23, r24, r4
  M   26 li r7, 0
  M   27 beq 96
  M   28 bge 160
  B   18 rlwinm r31, r3, 0, 0, 0x16
  B   19 subf r23, r31, r3
  B   20 beq 188
  B   21 bge 324
--- replace mine 31:32 base 24:33
  M   31 b 148
  B   24 b 312
  B   25 lwz r3, 0(0)
  B   26 mulli r29, r24, 0x1fc0
  B   27 slwi r30, r25, 6
  B   28 addis r0, r3, 1
  B   29 add r0, r0, r29
  B   30 li r4, 9
  B   31 add r3, r0, r30
  B   32 slwi r28, r25, 2
--- replace mine 33:39 base 34:37
  M   33 slwi r26, r30, 2
  M   34 stb r0, 0(r6)
  M   35 li r0, 9
  M   36 mulli r25, r29, 0x1fc
  M   37 li r7, 0xe00
  M   38 stb r0, 3(r6)
  B   34 li r8, 0xe00
  B   35 stb r0, -0x6fbc(r3)
  B   36 mulli r27, r24, 0x1fc
--- replace mine 41:43 base 39:48
  M   41 add r0, r0, r25
  M   42 add r3, r0, r26
  B   39 add r0, r0, r29
  B   40 add r3, r0, r30
  B   41 stb r4, -0x6fb9(r3)
  B   42 lwz r3, 0(0)
  B   43 addis r3, r3, 1
  B   44 add r4, r3, r29
  B   45 add r0, r3, r27
  B   46 add r3, r0, r28
  B   47 add r4, r4, r30
--- replace mine 44:58 base 49:52
  M   44 subf r3, r6, r0
  M   45 stw r3, 0x14(r6)
  M   46 addi r3, r3, 0xc00
  M   47 addi r0, r3, 0x200
  M   48 stw r3, 0x18(r6)
  M   49 stw r0, 0x1c(r6)
  M   50 b 120
  M   51 li r0, 1
  M   52 slwi r26, r30, 2
  M   53 stb r0, 0(r6)
  M   54 li r0, 5
  M   55 mulli r25, r29, 0x1fc
  M   56 li r7, 0x1800
  M   57 stb r0, 3(r6)
  B   49 addi r3, r4, -0x6fbc
  B   50 subf r0, r3, r0
  B   51 stw r0, -0x6fa8(r4)
--- replace mine 60:73 base 54:59
  M   60 add r0, r0, r25
  M   61 add r3, r0, r26
  M   62 lwz r0, -0x303c(r3)
  M   63 subf r3, r6, r0
  M   64 stw r3, 0x14(r6)
  M   65 addi r0, r3, 0x1800
  M   66 stw r0, 0x1c(r6)
  M   67 b 52
  M   68 li r0, 0
  M   69 slwi r26, r30, 2
  M   70 stb r0, 0(r6)
  M   71 mulli r25, r29, 0x1fc
  M   72 stb r0, 3(r6)
  B   54 add r0, r0, r29
  B   55 add r4, r0, r30
  B   56 lwz r3, -0x6fa8(r4)
  B   57 addi r0, r3, 0xc00
  B   58 stw r0, -0x6fa4(r4)
--- replace mine 75:77 base 61:90
  M   75 add r0, r0, r25
  M   76 add r3, r0, r26
  B   61 add r0, r0, r29
  B   62 add r4, r0, r30
  B   63 lwz r3, -0x6fa4(r4)
  B   64 addi r0, r3, 0x200
  B   65 stw r0, -0x6fa0(r4)
  B   66 b 244
  B   67 lwz r3, 0(0)
  B   68 mulli r29, r24, 0x1fc0
  B   69 slwi r30, r25, 6
  B   70 addis r0, r3, 1
  B   71 add r0, r0, r29
  B   72 li r4, 5
  B   73 add r3, r0, r30
  B   74 slwi r28, r25, 2
  B   75 li r0, 1
  B   76 li r8, 0x1800
  B   77 stb r0, -0x6fbc(r3)
  B   78 mulli r27, r24, 0x1fc
  B   79 lwz r3, 0(0)
  B   80 addis r0, r3, 1
  B   81 add r0, r0, r29
  B   82 add r3, r0, r30
  B   83 stb r4, -0x6fb9(r3)
  B   84 lwz r3, 0(0)
  B   85 addis r3, r3, 1
  B   86 add r4, r3, r29
  B   87 add r0, r3, r27
  B   88 add r3, r0, r28
  B   89 add r4, r4, r30
--- replace mine 78:80 base 91:107
  M   78 subf r0, r6, r0
  M   79 stw r0, 0x1c(r6)
  B   91 addi r3, r4, -0x6fbc
  B   92 subf r0, r3, r0
  B   93 stw r0, -0x6fa8(r4)
  B   94 lwz r3, 0(0)
  B   95 addis r0, r3, 1
  B   96 add r0, r0, r29
  B   97 add r4, r0, r30
  B   98 lwz r3, -0x6fa8(r4)
  B   99 addi r0, r3, 0x1800
  B  100 stw r0, -0x6fa0(r4)
  B  101 b 104
  B  102 lwz r3, 0(0)
  B  103 mulli r29, r24, 0x1fc0
  B  104 slwi r30, r25, 6
  B  105 addis r0, r3, 1
  B  106 add r0, r0, r29
--- insert mine 81:81 base 108:129
  B  108 add r3, r0, r30
  B  109 slwi r28, r25, 2
  B  110 stb r4, -0x6fbc(r3)
  B  111 mulli r27, r24, 0x1fc
  B  112 lwz r3, 0(0)
  B  113 addis r0, r3, 1
  B  114 add r0, r0, r29
  B  115 add r3, r0, r30
  B  116 stb r4, -0x6fb9(r3)
  B  117 lwz r3, 0(0)
  B  118 addis r3, r3, 1
  B  119 add r0, r3, r27
  B  120 add r4, r3, r29
  B  121 add r3, r0, r28
  B  122 add r4, r4, r30
  B  123 lwz r0, -0x303c(r3)
  B  124 addi r3, r4, -0x6fbc
  B  125 subf r0, r3, r0
  B  126 stw r0, -0x6fa0(r4)
  B  127 lwz r4, 0(0)
  B  128 li r3, 0
--- replace mine 82:84 base 130:132
  M   82 stb r4, 2(r6)
  M   83 li r8, 0
  B  130 add r9, r29, r30
  B  131 addis r4, r4, 1
--- replace mine 85:91 base 133:156
  M   85 sth r4, 0x12(r6)
  M   86 lhz r3, 0x32(r31)
  M   87 sth r3, 0x10(r6)
  M   88 lhz r3, 0x32(r31)
  M   89 rlwinm r3, r3, 2, 0x1c, 0x1d
  M   90 stb r3, 6(r6)
  B  133 add r4, r4, r29
  B  134 li r7, 0
  B  135 add r4, r4, r30
  B  136 stb r3, -0x6fba(r4)
  B  137 li r4, 0
  B  138 lwz r10, 0(0)
  B  139 addis r10, r10, 1
  B  140 add r10, r10, r29
  B  141 add r10, r10, r30
  B  142 sth r3, -0x6faa(r10)
  B  143 lwz r10, 0(0)
  B  144 lhz r11, 0x32(r26)
  B  145 addis r10, r10, 1
  B  146 add r10, r10, r29
  B  147 add r10, r10, r30
  B  148 sth r11, -0x6fac(r10)
  B  149 lwz r10, 0(0)
  B  150 lhz r11, 0x32(r26)
  B  151 addis r10, r10, 1
  B  152 add r10, r10, r29
  B  153 rlwinm r11, r11, 2, 0x1c, 0x1d
  B  154 add r10, r10, r30
  B  155 stb r11, -0x6fb6(r10)
--- replace mine 92:94 base 157:159
  M   92 lhz r3, 0x32(r31)
  M   93 sraw r0, r3, r4
  B  157 lhz r10, 0x32(r26)
  B  158 sraw r0, r10, r3
--- replace mine 95:97 base 160:162
  M   95 beq 24
  M   96 lha r3, 0x12(r6)
  B  160 beq 36
  B  161 lwz r10, 0(0)
--- replace mine 98:114 base 163:190
  M   98 add r0, r3, r0
  M   99 sth r0, 0x12(r6)
  M  100 b 28
  M  101 addi r0, r5, -1
  M  102 slwi r0, r0, 1
  M  103 sraw r0, r3, r0
  M  104 rlwinm r0, r0, 2, 0x1c, 0x1d
  M  105 stb r0, 7(r6)
  M  106 b 28
  M  107 addi r5, r5, 1
  M  108 addi r4, r4, 2
  M  109 bdnz -68
  M  110 lhz r0, 0x32(r31)
  M  111 rlwinm r0, r0, 0x14, 0x1c, 0x1d
  M  112 stb r0, 7(r6)
  M  113 lhz r0, 0x32(r31)
  B  163 addis r10, r10, 1
  B  164 addi r11, r10, -0x6faa
  B  165 lhax r10, r9, r11
  B  166 add r0, r10, r0
  B  167 sthx r0, r9, r11
  B  168 b 44
  B  169 lwz r3, 0(0)
  B  170 addi r0, r4, -1
  B  171 slwi r4, r0, 1
  B  172 addis r0, r3, 1
  B  173 sraw r3, r10, r4
  B  174 add r0, r0, r29
  B  175 rlwinm r4, r3, 2, 0x1c, 0x1d
  B  176 add r3, r0, r30
  B  177 stb r4, -0x6fb5(r3)
  B  178 b 44
  B  179 addi r4, r4, 1
  B  180 addi r3, r3, 2
  B  181 bdnz -96
  B  182 lwz r3, 0(0)
  B  183 lhz r4, 0x32(r26)
  B  184 addis r0, r3, 1
  B  185 add r0, r0, r29
  B  186 rlwinm r4, r4, 0x14, 0x1c, 0x1d
  B  187 add r3, r0, r30
  B  188 stb r4, -0x6fb5(r3)
  B  189 lhz r0, 0x32(r26)
--- replace mine 116:117 base 192:193
  M  116 lhz r0, 0x30(r31)
  B  192 lhz r0, 0x30(r26)
--- replace mine 118:125 base 194:205
  M  118 bne 16
  M  119 li r8, 0
  M  120 stb r8, 1(r6)
  M  121 b 296
  M  122 li r10, 8
  M  123 li r9, 0
  M  124 li r5, 0
  B  194 bne 36
  B  195 lwz r3, 0(0)
  B  196 li r4, 0
  B  197 li r7, 0
  B  198 addis r0, r3, 1
  B  199 add r0, r0, r29
  B  200 add r3, r0, r30
  B  201 stb r4, -0x6fbb(r3)
  B  202 b 444
  B  203 li r4, 8
  B  204 li r10, 0
--- replace mine 126:127 base 206:207
  M  126 li r4, 0
  B  206 li r12, 0
--- replace mine 129:138 base 209:218
  M  129 mtctr r10
  M  130 lhz r10, 0x32(r31)
  M  131 sraw r10, r10, r4
  M  132 clrlwi. r10, r10, 0x1e
  M  133 beq 176
  M  134 lhz r10, 0x30(r31)
  M  135 sraw r10, r10, r4
  M  136 clrlwi r10, r10, 0x1e
  M  137 cmpwi r10, 1
  B  209 mtctr r4
  B  210 lhz r4, 0x32(r26)
  B  211 sraw r4, r4, r12
  B  212 clrlwi. r4, r4, 0x1e
  B  213 beq 264
  B  214 lhz r4, 0x30(r26)
  B  215 sraw r4, r4, r12
  B  216 clrlwi r4, r4, 0x1e
  B  217 cmpwi r4, 1
--- replace mine 140:167 base 220:287
  M  140 cmpwi r10, 0
  M  141 bge 56
  M  142 b 72
  M  143 cmpwi r10, 3
  M  144 bge 64
  M  145 b 24
  M  146 add r9, r6, r5
  M  147 li r10, 0x400
  M  148 stb r3, 8(r9)
  M  149 li r9, 1
  M  150 b 44
  M  151 add r12, r6, r5
  M  152 li r10, 0x800
  M  153 stb r0, 8(r12)
  M  154 b 28
  M  155 add r21, r6, r5
  M  156 li r10, 0
  M  157 lbz r12, 7(r21)
  M  158 stb r12, 8(r21)
  M  159 b 8
  M  160 li r10, 0
  M  161 cmpwi r5, 7
  M  162 bge 24
  M  163 add r21, r6, r11
  M  164 lwz r12, 0x1c(r21)
  M  165 add r12, r10, r12
  M  166 stw r12, 0x20(r21)
  B  220 cmpwi r4, 0
  B  221 bge 80
  B  222 b 108
  B  223 cmpwi r4, 3
  B  224 bge 100
  B  225 b 36
  B  226 add r4, r10, r9
  B  227 lwz r21, 0(0)
  B  228 addis r4, r4, 1
  B  229 li r6, 0x400
  B  230 addi r4, r4, -0x6fb4
  B  231 li r5, 1
  B  232 stbx r3, r21, r4
  B  233 b 64
  B  234 add r4, r10, r9
  B  235 lwz r21, 0(0)
  B  236 addis r4, r4, 1
  B  237 li r6, 0x800
  B  238 addi r4, r4, -0x6fb4
  B  239 stbx r0, r21, r4
  B  240 b 36
  B  241 add r4, r10, r9
  B  242 lwz r21, 0(0)
  B  243 addis r4, r4, 1
  B  244 li r6, 0
  B  245 addi r22, r4, -0x6fb4
  B  246 add r22, r21, r22
  B  247 lbz r4, -1(r22)
  B  248 stb r4, 0(r22)
  B  249 cmpwi r10, 7
  B  250 bge 52
  B  251 lwz r4, 0(0)
  B  252 addis r22, r11, 1
  B  253 addi r21, r10, 1
  B  254 add r4, r9, r4
  B  255 addi r22, r22, -0x6fa0
  B  256 slwi r21, r21, 2
  B  257 lwzx r22, r4, r22
  B  258 addis r21, r21, 1
  B  259 add r22, r6, r22
  B  260 addi r21, r21, -0x6fa0
  B  261 stwx r22, r4, r21
  B  262 b 36
  B  263 lwz r21, 0(0)
  B  264 addis r4, r11, 1
  B  265 addi r4, r4, -0x6fa0
  B  266 add r22, r9, r21
  B  267 lwzx r21, r22, r4
  B  268 addis r4, r22, 1
  B  269 add r21, r6, r21
  B  270 stw r21, -0x6f80(r4)
  B  271 lwz r4, 0(0)
  B  272 add r7, r7, r6
  B  273 addis r4, r4, 1
  B  274 addi r21, r4, -0x6fba
  B  275 lbzx r4, r9, r21
  B  276 addi r4, r4, 1
  B  277 stbx r4, r9, r21
  B  278 b 40
  B  279 lwz r3, 0(0)
  B  280 slwi r0, r10, 2
  B  281 addis r3, r3, 1
  B  282 add r3, r3, r29
  B  283 add r4, r3, r30
  B  284 add r3, r4, r0
  B  285 lwz r0, -0x6fa0(r3)
  B  286 stw r0, -0x6f80(r4)
--- replace mine 168:183 base 288:289
  M  168 add r12, r6, r11
  M  169 lwz r12, 0x1c(r12)
  M  170 add r12, r10, r12
  M  171 stw r12, 0x3c(r6)
  M  172 lbz r12, 2(r6)
  M  173 add r8, r8, r10
  M  174 addi r10, r12, 1
  M  175 stb r10, 2(r6)
  M  176 b 24
  M  177 slwi r0, r5, 2
  M  178 add r3, r6, r0
  M  179 lwz r0, 0x1c(r3)
  M  180 stw r0, 0x3c(r6)
  M  181 b 20
  M  182 addi r5, r5, 1
  B  288 addi r10, r10, 1
--- replace mine 184:187 base 290:293
  M  184 addi r4, r4, 2
  M  185 bdnz -220
  M  186 cmpwi r9, 0
  B  290 addi r12, r12, 2
  B  291 bdnz -324
  B  292 cmpwi r5, 0
--- replace mine 188:198 base 294:316
  M  188 addi r8, r8, 0x200
  M  189 li r3, 1
  M  190 stb r3, 1(r6)
  M  191 lbz r0, 7(r31)
  M  192 rlwinm r0, r0, 0, 0x1d, 0x1d
  M  193 stb r0, 5(r6)
  M  194 stb r3, 4(r6)
  M  195 add r22, r7, r8
  M  196 mr r3, r29
  M  197 add r5, r22, r23
  B  294 addi r7, r7, 0x200
  B  295 lwz r3, 0(0)
  B  296 li r5, 1
  B  297 addis r0, r3, 1
  B  298 add r0, r0, r29
  B  299 add r3, r0, r30
  B  300 stb r5, -0x6fbb(r3)
  B  301 lwz r3, 0(0)
  B  302 lbz r4, 7(r26)
  B  303 addis r0, r3, 1
  B  304 add r0, r0, r29
  B  305 rlwinm r4, r4, 0, 0x1d, 0x1d
  B  306 add r3, r0, r30
  B  307 stb r4, -0x6fb7(r3)
  B  308 lwz r3, 0(0)
  B  309 addis r0, r3, 1
  B  310 add r0, r0, r29
  B  311 add r3, r0, r30
  B  312 stb r5, -0x6fb8(r3)
  B  313 add r21, r8, r7
  B  314 mr r3, r24
  B  315 add r5, r21, r23
--- replace mine 200:201 base 318:319
  M  200 rlwinm r21, r0, 0, 0, 0x16
  B  318 rlwinm r22, r0, 0, 0, 0x16
--- replace mine 203:217 base 321:336
  M  203 bge 52
  M  204 lwz r3, 0(0)
  M  205 li r4, 0
  M  206 addis r0, r3, 1
  M  207 add r0, r0, r27
  M  208 add r3, r0, r28
  M  209 stb r4, -0x6fbc(r3)
  M  210 lwz r3, 0(0)
  M  211 addis r0, r3, 1
  M  212 add r0, r0, r27
  M  213 add r3, r0, r28
  M  214 stb r4, -0x6fbb(r3)
  M  215 b 244
  M  216 lhz r3, 0x38(r31)
  B  321 bge 56
  B  322 lwz r4, 0(0)
  B  323 li r5, 0
  B  324 li r3, 0
  B  325 addis r0, r4, 1
  B  326 add r0, r0, r29
  B  327 add r4, r0, r30
  B  328 stb r5, -0x6fbc(r4)
  B  329 lwz r4, 0(0)
  B  330 addis r0, r4, 1
  B  331 add r0, r0, r29
  B  332 add r4, r0, r30
  B  333 stb r5, -0x6fbb(r4)
  B  334 b 256
  B  335 lhz r3, 0x38(r26)
--- replace mine 219:234 base 338:354
  M  219 cmplw r24, r3
  M  220 ble 52
  M  221 lwz r3, 0(0)
  M  222 li r4, 0
  M  223 addis r0, r3, 1
  M  224 add r0, r0, r27
  M  225 add r3, r0, r28
  M  226 stb r4, -0x6fbc(r3)
  M  227 lwz r3, 0(0)
  M  228 addis r0, r3, 1
  M  229 add r0, r0, r27
  M  230 add r3, r0, r28
  M  231 stb r4, -0x6fbb(r3)
  M  232 b 176
  M  233 add r0, r24, r21
  B  338 cmplw r31, r3
  B  339 ble 56
  B  340 lwz r4, 0(0)
  B  341 li r5, 0
  B  342 li r3, 0
  B  343 addis r0, r4, 1
  B  344 add r0, r0, r29
  B  345 add r4, r0, r30
  B  346 stb r5, -0x6fbc(r4)
  B  347 lwz r4, 0(0)
  B  348 addis r0, r4, 1
  B  349 add r0, r0, r29
  B  350 add r4, r0, r30
  B  351 stb r5, -0x6fbb(r4)
  B  352 b 184
  B  353 add r0, r31, r22
--- replace mine 235:249 base 355:370
  M  235 ble 52
  M  236 lwz r3, 0(0)
  M  237 li r4, 0
  M  238 addis r0, r3, 1
  M  239 add r0, r0, r27
  M  240 add r3, r0, r28
  M  241 stb r4, -0x6fbc(r3)
  M  242 lwz r3, 0(0)
  M  243 addis r0, r3, 1
  M  244 add r0, r0, r27
  M  245 add r3, r0, r28
  M  246 stb r4, -0x6fbb(r3)
  M  247 b 116
  M  248 cmpwi r22, 0
  B  355 ble 56
  B  356 lwz r4, 0(0)
  B  357 li r5, 0
  B  358 li r3, 0
  B  359 addis r0, r4, 1
  B  360 add r0, r0, r29
  B  361 add r4, r0, r30
  B  362 stb r5, -0x6fbc(r4)
  B  363 lwz r4, 0(0)
  B  364 addis r0, r4, 1
  B  365 add r0, r0, r29
  B  366 add r4, r0, r30
  B  367 stb r5, -0x6fbb(r4)
  B  368 b 120
  B  369 cmpwi r21, 0
--- replace mine 251:253 base 372:374
  M  251 mr r5, r21
  M  252 mr r6, r24
  B  372 mr r5, r22
  B  373 mr r6, r31
--- replace mine 258:260 base 379:381
  M  258 mr r24, r3
  M  259 blt 320
  B  379 bge 8
  B  380 b 72
--- replace mine 261:262 base 382:383
  M  261 mr r5, r22
  B  382 mr r5, r21
--- replace mine 263:264 base 384:385
  M  263 add r3, r4, r25
  B  384 add r3, r4, r27
--- replace mine 265:266 base 386:387
  M  265 add r3, r3, r26
  B  386 add r3, r3, r28
--- replace mine 270:271 base 391:392
  M  270 mr r4, r21
  B  391 mr r4, r22
--- replace mine 272:274 base 393:395
  M  272 add r0, r0, r25
  M  273 add r3, r0, r26
  B  393 add r0, r0, r27
  B  394 add r3, r0, r28
--- replace mine 276:278 base 397:403
  M  276 lwz r5, 0x3c(r31)
  M  277 mr r3, r29
  B  397 li r3, 0
  B  398 cmpwi r3, 0
  B  399 bge 8
  B  400 b 424
  B  401 lwz r5, 0x3c(r26)
  B  402 mr r3, r24
--- replace mine 280:281 base 405:406
  M  280 rlwinm r22, r5, 0, 0, 0x16
  B  405 rlwinm r23, r5, 0, 0, 0x16
--- replace mine 282:284 base 407:409
  M  282 subf r21, r22, r5
  M  283 subf r23, r22, r0
  B  407 subf r21, r23, r5
  B  408 subf r22, r23, r0
--- replace mine 286:291 base 411:416
  M  286 mr r24, r3
  M  287 blt 168
  M  288 cmpwi r22, 0
  M  289 blt 156
  M  290 lhz r3, 0x38(r31)
  B  411 mr r29, r3
  B  412 blt 180
  B  413 cmpwi r23, 0
  B  414 blt 24
  B  415 lhz r3, 0x38(r26)
--- replace mine 293:297 base 418:424
  M  293 cmplw r22, r0
  M  294 bgt 136
  M  295 add. r3, r22, r23
  M  296 blt 128
  B  418 cmplw r23, r0
  B  419 ble 12
  B  420 li r29, 0
  B  421 b 144
  B  422 add. r3, r23, r22
  B  423 blt 12
--- replace mine 298:299 base 425:428
  M  298 bgt 120
  B  425 ble 12
  B  426 li r29, 0
  B  427 b 120
--- replace mine 300:302 base 429:431
  M  300 mr r5, r23
  M  301 mr r6, r22
  B  429 mr r5, r22
  B  430 mr r6, r23
--- replace mine 307:309 base 436:438
  M  307 mr r24, r3
  M  308 blt 84
  B  436 mr r29, r3
  B  437 blt 80
--- replace mine 313:315 base 442:444
  M  313 add r0, r0, r25
  M  314 add r3, r0, r26
  B  442 add r0, r0, r27
  B  443 add r3, r0, r28
--- replace mine 320:322 base 449:451
  M  320 add r0, r4, r25
  M  321 add r3, r0, r26
  B  449 add r0, r4, r27
  B  450 add r3, r0, r28
--- replace mine 326:329 base 455:457
  M  326 li r24, 0
  M  327 b 40
  M  328 li r24, 0
  B  455 li r29, 0
  B  456 b 36
--- replace mine 333:335 base 461:463
  M  333 add r0, r0, r25
  M  334 add r3, r0, r26
  B  461 add r0, r0, r27
  B  462 add r3, r0, r28
--- replace mine 337:338 base 465:466
  M  337 cmpwi r24, 0
  B  465 cmpwi r29, 0
--- replace mine 339:340 base 467:468
  M  339 mr r3, r24
  B  467 mr r3, r29
--- replace mine 346:347 base 474:475
  M  346 mulli r7, r29, 0x5f4
  B  474 mulli r7, r24, 0x5f4
--- replace mine 350:351 base 478:479
  M  350 mulli r6, r30, 0xc
  B  478 mulli r6, r25, 0xc
--- replace mine 355:356 base 483:484
  M  355 lhz r5, 0x38(r31)
  B  483 lhz r5, 0x38(r26)
--- replace mine 360:361 base 488:489
  M  360 lwz r5, 0x28(r31)
  B  488 lwz r5, 0x28(r26)
--- replace mine 364:365 base 492:493
  M  364 lbz r4, 0x34(r31)
  B  492 lbz r4, 0x34(r26)
--- replace mine 371:372 base 499:500
  M  371 lbz r4, 0x34(r31)
  B  499 lbz r4, 0x34(r26)
```

- operand order and conditions: transfer size first, explicit nonnegative offset limits: exact False; insns 501/512; differences None; objdiff 88.91797

```text
src 0x7d4 base 0x800 insns 501/512
--- replace mine 5:8 base 5:8
  M    5 mr r31, r5
  M    6 mr r29, r3
  M    7 mr r30, r4
  B    5 mr r26, r5
  B    6 mr r24, r3
  B    7 mr r25, r4
--- replace mine 12:16 base 12:16
  M   12 b 1932
  M   13 lbz r0, 7(r31)
  M   14 li r7, 0
  M   15 lwz r3, 0x2c(r31)
  B   12 b 1976
  B   13 lbz r0, 7(r26)
  B   14 li r8, 0
  B   15 lwz r3, 0x2c(r26)
--- replace mine 18:20 base 18:20
  M   18 rlwinm r24, r3, 0, 0, 0x16
  M   19 subf r23, r24, r3
  B   18 rlwinm r31, r3, 0, 0, 0x16
  B   19 subf r23, r31, r3
--- replace mine 26:28 base 26:28
  M   26 mulli r27, r29, 0x1fc0
  M   27 slwi r28, r30, 6
  B   26 mulli r29, r24, 0x1fc0
  B   27 slwi r30, r25, 6
--- replace mine 29:30 base 29:30
  M   29 add r0, r0, r27
  B   29 add r0, r0, r29
--- replace mine 31:33 base 31:33
  M   31 add r3, r0, r28
  M   32 slwi r26, r30, 2
  B   31 add r3, r0, r30
  B   32 slwi r28, r25, 2
--- replace mine 34:35 base 34:35
  M   34 li r7, 0xe00
  B   34 li r8, 0xe00
--- replace mine 36:37 base 36:37
  M   36 mulli r25, r29, 0x1fc
  B   36 mulli r27, r24, 0x1fc
--- replace mine 39:41 base 39:41
  M   39 add r0, r0, r27
  M   40 add r3, r0, r28
  B   39 add r0, r0, r29
  B   40 add r3, r0, r30
--- replace mine 44:48 base 44:48
  M   44 add r4, r3, r27
  M   45 add r0, r3, r25
  M   46 add r3, r0, r26
  M   47 add r4, r4, r28
  B   44 add r4, r3, r29
  B   45 add r0, r3, r27
  B   46 add r3, r0, r28
  B   47 add r4, r4, r30
--- replace mine 54:56 base 54:56
  M   54 add r0, r0, r27
  M   55 add r4, r0, r28
  B   54 add r0, r0, r29
  B   55 add r4, r0, r30
--- replace mine 61:63 base 61:63
  M   61 add r0, r0, r27
  M   62 add r4, r0, r28
  B   61 add r0, r0, r29
  B   62 add r4, r0, r30
--- replace mine 68:70 base 68:70
  M   68 mulli r27, r29, 0x1fc0
  M   69 slwi r28, r30, 6
  B   68 mulli r29, r24, 0x1fc0
  B   69 slwi r30, r25, 6
--- replace mine 71:72 base 71:72
  M   71 add r0, r0, r27
  B   71 add r0, r0, r29
--- replace mine 73:75 base 73:75
  M   73 add r3, r0, r28
  M   74 slwi r26, r30, 2
  B   73 add r3, r0, r30
  B   74 slwi r28, r25, 2
--- replace mine 76:77 base 76:77
  M   76 li r7, 0x1800
  B   76 li r8, 0x1800
--- replace mine 78:79 base 78:79
  M   78 mulli r25, r29, 0x1fc
  B   78 mulli r27, r24, 0x1fc
--- replace mine 81:83 base 81:83
  M   81 add r0, r0, r27
  M   82 add r3, r0, r28
  B   81 add r0, r0, r29
  B   82 add r3, r0, r30
--- replace mine 86:90 base 86:90
  M   86 add r4, r3, r27
  M   87 add r0, r3, r25
  M   88 add r3, r0, r26
  M   89 add r4, r4, r28
  B   86 add r4, r3, r29
  B   87 add r0, r3, r27
  B   88 add r3, r0, r28
  B   89 add r4, r4, r30
--- replace mine 96:98 base 96:98
  M   96 add r0, r0, r27
  M   97 add r4, r0, r28
  B   96 add r0, r0, r29
  B   97 add r4, r0, r30
--- replace mine 103:105 base 103:105
  M  103 mulli r27, r29, 0x1fc0
  M  104 slwi r28, r30, 6
  B  103 mulli r29, r24, 0x1fc0
  B  104 slwi r30, r25, 6
--- replace mine 106:107 base 106:107
  M  106 add r0, r0, r27
  B  106 add r0, r0, r29
--- replace mine 108:110 base 108:110
  M  108 add r3, r0, r28
  M  109 slwi r26, r30, 2
  B  108 add r3, r0, r30
  B  109 slwi r28, r25, 2
--- replace mine 111:112 base 111:112
  M  111 mulli r25, r29, 0x1fc
  B  111 mulli r27, r24, 0x1fc
--- replace mine 114:116 base 114:116
  M  114 add r0, r0, r27
  M  115 add r3, r0, r28
  B  114 add r0, r0, r29
  B  115 add r3, r0, r30
--- replace mine 119:123 base 119:123
  M  119 add r0, r3, r25
  M  120 add r4, r3, r27
  M  121 add r3, r0, r26
  M  122 add r4, r4, r28
  B  119 add r0, r3, r27
  B  120 add r4, r3, r29
  B  121 add r3, r0, r28
  B  122 add r4, r4, r30
--- replace mine 127:128 base 127:128
  M  127 lwz r5, 0(0)
  B  127 lwz r4, 0(0)
--- replace mine 130:135 base 130:132
  M  130 add r4, r27, r28
  M  131 addis r5, r5, 1
  M  132 li r8, 0
  M  133 add r6, r5, r27
  M  134 add r6, r6, r28
  B  130 add r9, r29, r30
  B  131 addis r4, r4, 1
--- replace mine 136:155 base 133:156
  M  136 stb r3, -0x6fba(r6)
  M  137 lwz r6, 0(0)
  M  138 addis r6, r6, 1
  M  139 add r6, r6, r27
  M  140 add r6, r6, r28
  M  141 sth r3, -0x6faa(r6)
  M  142 lwz r6, 0(0)
  M  143 lhz r9, 0x32(r31)
  M  144 addis r6, r6, 1
  M  145 add r6, r6, r27
  M  146 add r6, r6, r28
  M  147 sth r9, -0x6fac(r6)
  M  148 lwz r6, 0(0)
  M  149 lhz r9, 0x32(r31)
  M  150 addis r6, r6, 1
  M  151 add r6, r6, r27
  M  152 rlwinm r9, r9, 2, 0x1c, 0x1d
  M  153 add r6, r6, r28
  M  154 stb r9, -0x6fb6(r6)
  B  133 add r4, r4, r29
  B  134 li r7, 0
  B  135 add r4, r4, r30
  B  136 stb r3, -0x6fba(r4)
  B  137 li r4, 0
  B  138 lwz r10, 0(0)
  B  139 addis r10, r10, 1
  B  140 add r10, r10, r29
  B  141 add r10, r10, r30
  B  142 sth r3, -0x6faa(r10)
  B  143 lwz r10, 0(0)
  B  144 lhz r11, 0x32(r26)
  B  145 addis r10, r10, 1
  B  146 add r10, r10, r29
  B  147 add r10, r10, r30
  B  148 sth r11, -0x6fac(r10)
  B  149 lwz r10, 0(0)
  B  150 lhz r11, 0x32(r26)
  B  151 addis r10, r10, 1
  B  152 add r10, r10, r29
  B  153 rlwinm r11, r11, 2, 0x1c, 0x1d
  B  154 add r10, r10, r30
  B  155 stb r11, -0x6fb6(r10)
--- replace mine 156:158 base 157:159
  M  156 lhz r6, 0x32(r31)
  M  157 sraw r0, r6, r3
  B  157 lhz r10, 0x32(r26)
  B  158 sraw r0, r10, r3
--- replace mine 160:167 base 161:168
  M  160 lwz r9, 0(0)
  M  161 slwi r6, r0, 2
  M  162 addis r9, r9, 1
  M  163 addi r9, r9, -0x6faa
  M  164 lhax r0, r4, r9
  M  165 add r0, r6, r0
  M  166 sthx r0, r4, r9
  B  161 lwz r10, 0(0)
  B  162 slwi r0, r0, 2
  B  163 addis r10, r10, 1
  B  164 addi r11, r10, -0x6faa
  B  165 lhax r10, r9, r11
  B  166 add r0, r10, r0
  B  167 sthx r0, r9, r11
--- replace mine 169:171 base 170:172
  M  169 addi r0, r5, -1
  M  170 slwi r5, r0, 1
  B  170 addi r0, r4, -1
  B  171 slwi r4, r0, 1
--- replace mine 172:177 base 173:178
  M  172 sraw r3, r6, r5
  M  173 add r0, r0, r27
  M  174 rlwinm r5, r3, 2, 0x1c, 0x1d
  M  175 add r3, r0, r28
  M  176 stb r5, -0x6fb5(r3)
  B  173 sraw r3, r10, r4
  B  174 add r0, r0, r29
  B  175 rlwinm r4, r3, 2, 0x1c, 0x1d
  B  176 add r3, r0, r30
  B  177 stb r4, -0x6fb5(r3)
--- replace mine 178:179 base 179:180
  M  178 addi r5, r5, 1
  B  179 addi r4, r4, 1
--- replace mine 182:183 base 183:184
  M  182 lhz r5, 0x32(r31)
  B  183 lhz r4, 0x32(r26)
--- replace mine 184:189 base 185:190
  M  184 add r0, r0, r27
  M  185 rlwinm r5, r5, 0x14, 0x1c, 0x1d
  M  186 add r3, r0, r28
  M  187 stb r5, -0x6fb5(r3)
  M  188 lhz r0, 0x32(r31)
  B  185 add r0, r0, r29
  B  186 rlwinm r4, r4, 0x14, 0x1c, 0x1d
  B  187 add r3, r0, r30
  B  188 stb r4, -0x6fb5(r3)
  B  189 lhz r0, 0x32(r26)
--- replace mine 191:192 base 192:193
  M  191 lhz r0, 0x30(r31)
  B  192 lhz r0, 0x30(r26)
--- replace mine 193:194 base 194:195
  M  193 bne 32
  B  194 bne 36
--- replace mine 195:196 base 196:198
  M  195 li r8, 0
  B  196 li r4, 0
  B  197 li r7, 0
--- replace mine 197:204 base 199:205
  M  197 add r0, r0, r27
  M  198 add r3, r0, r28
  M  199 stb r8, -0x6fbb(r3)
  M  200 b 440
  M  201 li r10, 8
  M  202 li r9, 0
  M  203 li r6, 0
  B  199 add r0, r0, r29
  B  200 add r3, r0, r30
  B  201 stb r4, -0x6fbb(r3)
  B  202 b 444
  B  203 li r4, 8
  B  204 li r10, 0
--- replace mine 205:206 base 206:207
  M  205 li r5, 0
  B  206 li r12, 0
--- replace mine 208:217 base 209:218
  M  208 mtctr r10
  M  209 lhz r10, 0x32(r31)
  M  210 sraw r10, r10, r5
  M  211 clrlwi. r10, r10, 0x1e
  M  212 beq 256
  M  213 lhz r10, 0x30(r31)
  M  214 sraw r10, r10, r5
  M  215 clrlwi r10, r10, 0x1e
  M  216 cmpwi r10, 1
  B  209 mtctr r4
  B  210 lhz r4, 0x32(r26)
  B  211 sraw r4, r4, r12
  B  212 clrlwi. r4, r4, 0x1e
  B  213 beq 264
  B  214 lhz r4, 0x30(r26)
  B  215 sraw r4, r4, r12
  B  216 clrlwi r4, r4, 0x1e
  B  217 cmpwi r4, 1
--- replace mine 219:220 base 220:221
  M  219 cmpwi r10, 0
  B  220 cmpwi r4, 0
--- replace mine 221:224 base 222:225
  M  221 b 112
  M  222 cmpwi r10, 3
  M  223 bge 104
  B  222 b 108
  B  223 cmpwi r4, 3
  B  224 bge 100
--- replace mine 225:226 base 226:227
  M  225 add r9, r6, r4
  B  226 add r4, r10, r9
--- replace mine 227:234 base 228:235
  M  227 addis r9, r9, 1
  M  228 li r10, 0x400
  M  229 addi r12, r9, -0x6fb4
  M  230 stbx r3, r21, r12
  M  231 li r9, 1
  M  232 b 72
  M  233 add r10, r6, r4
  B  228 addis r4, r4, 1
  B  229 li r6, 0x400
  B  230 addi r4, r4, -0x6fb4
  B  231 li r5, 1
  B  232 stbx r3, r21, r4
  B  233 b 64
  B  234 add r4, r10, r9
--- replace mine 235:259 base 236:262
  M  235 addis r12, r10, 1
  M  236 addi r12, r12, -0x6fb4
  M  237 li r10, 0x800
  M  238 stbx r0, r21, r12
  M  239 b 44
  M  240 lwz r12, 0(0)
  M  241 li r10, 0
  M  242 addis r12, r12, 1
  M  243 add r12, r12, r27
  M  244 add r12, r12, r28
  M  245 add r21, r12, r6
  M  246 lbz r12, -0x6fb5(r21)
  M  247 stb r12, -0x6fb4(r21)
  M  248 b 8
  M  249 li r10, 0
  M  250 cmpwi r6, 7
  M  251 bge 36
  M  252 lwz r12, 0(0)
  M  253 add r12, r4, r12
  M  254 add r12, r11, r12
  M  255 addis r21, r12, 1
  M  256 lwz r12, -0x6fa0(r21)
  M  257 add r12, r10, r12
  M  258 stw r12, -0x6f9c(r21)
  B  236 addis r4, r4, 1
  B  237 li r6, 0x800
  B  238 addi r4, r4, -0x6fb4
  B  239 stbx r0, r21, r4
  B  240 b 36
  B  241 add r4, r10, r9
  B  242 lwz r21, 0(0)
  B  243 addis r4, r4, 1
  B  244 li r6, 0
  B  245 addi r22, r4, -0x6fb4
  B  246 add r22, r21, r22
  B  247 lbz r4, -1(r22)
  B  248 stb r4, 0(r22)
  B  249 cmpwi r10, 7
  B  250 bge 52
  B  251 lwz r4, 0(0)
  B  252 addis r22, r11, 1
  B  253 addi r21, r10, 1
  B  254 add r4, r9, r4
  B  255 addi r22, r22, -0x6fa0
  B  256 slwi r21, r21, 2
  B  257 lwzx r22, r4, r22
  B  258 addis r21, r21, 1
  B  259 add r22, r6, r22
  B  260 addi r21, r21, -0x6fa0
  B  261 stwx r22, r4, r21
--- replace mine 261:275 base 264:278
  M  261 addis r12, r11, 1
  M  262 addi r12, r12, -0x6fa0
  M  263 add r22, r4, r21
  M  264 lwzx r21, r22, r12
  M  265 addis r12, r22, 1
  M  266 add r21, r10, r21
  M  267 stw r21, -0x6f80(r12)
  M  268 lwz r12, 0(0)
  M  269 add r8, r8, r10
  M  270 addis r10, r12, 1
  M  271 addi r12, r10, -0x6fba
  M  272 lbzx r10, r4, r12
  M  273 addi r10, r10, 1
  M  274 stbx r10, r4, r12
  B  264 addis r4, r11, 1
  B  265 addi r4, r4, -0x6fa0
  B  266 add r22, r9, r21
  B  267 lwzx r21, r22, r4
  B  268 addis r4, r22, 1
  B  269 add r21, r6, r21
  B  270 stw r21, -0x6f80(r4)
  B  271 lwz r4, 0(0)
  B  272 add r7, r7, r6
  B  273 addis r4, r4, 1
  B  274 addi r21, r4, -0x6fba
  B  275 lbzx r4, r9, r21
  B  276 addi r4, r4, 1
  B  277 stbx r4, r9, r21
--- replace mine 277:278 base 280:281
  M  277 slwi r0, r6, 2
  B  280 slwi r0, r10, 2
--- replace mine 279:281 base 282:284
  M  279 add r3, r3, r27
  M  280 add r4, r3, r28
  B  282 add r3, r3, r29
  B  283 add r4, r3, r30
--- replace mine 285:286 base 288:289
  M  285 addi r6, r6, 1
  B  288 addi r10, r10, 1
--- replace mine 287:290 base 290:293
  M  287 addi r5, r5, 2
  M  288 bdnz -316
  M  289 cmpwi r9, 0
  B  290 addi r12, r12, 2
  B  291 bdnz -324
  B  292 cmpwi r5, 0
--- replace mine 291:292 base 294:295
  M  291 addi r8, r8, 0x200
  B  294 addi r7, r7, 0x200
--- replace mine 295:297 base 298:300
  M  295 add r0, r0, r27
  M  296 add r3, r0, r28
  B  298 add r0, r0, r29
  B  299 add r3, r0, r30
--- replace mine 299:300 base 302:303
  M  299 lbz r4, 7(r31)
  B  302 lbz r4, 7(r26)
--- replace mine 301:302 base 304:305
  M  301 add r0, r0, r27
  B  304 add r0, r0, r29
--- replace mine 303:304 base 306:307
  M  303 add r3, r0, r28
  B  306 add r3, r0, r30
--- replace mine 307:309 base 310:312
  M  307 add r0, r0, r27
  M  308 add r3, r0, r28
  B  310 add r0, r0, r29
  B  311 add r3, r0, r30
--- replace mine 310:313 base 313:316
  M  310 add r22, r7, r8
  M  311 mr r3, r29
  M  312 add r5, r22, r23
  B  313 add r21, r8, r7
  B  314 mr r3, r24
  B  315 add r5, r21, r23
--- replace mine 315:316 base 318:319
  M  315 rlwinm r21, r0, 0, 0, 0x16
  B  318 rlwinm r22, r0, 0, 0, 0x16
--- replace mine 318:332 base 321:336
  M  318 bge 52
  M  319 lwz r3, 0(0)
  M  320 li r4, 0
  M  321 addis r0, r3, 1
  M  322 add r0, r0, r27
  M  323 add r3, r0, r28
  M  324 stb r4, -0x6fbc(r3)
  M  325 lwz r3, 0(0)
  M  326 addis r0, r3, 1
  M  327 add r0, r0, r27
  M  328 add r3, r0, r28
  M  329 stb r4, -0x6fbb(r3)
  M  330 b 244
  M  331 lhz r3, 0x38(r31)
  B  321 bge 56
  B  322 lwz r4, 0(0)
  B  323 li r5, 0
  B  324 li r3, 0
  B  325 addis r0, r4, 1
  B  326 add r0, r0, r29
  B  327 add r4, r0, r30
  B  328 stb r5, -0x6fbc(r4)
  B  329 lwz r4, 0(0)
  B  330 addis r0, r4, 1
  B  331 add r0, r0, r29
  B  332 add r4, r0, r30
  B  333 stb r5, -0x6fbb(r4)
  B  334 b 256
  B  335 lhz r3, 0x38(r26)
--- replace mine 334:349 base 338:354
  M  334 cmplw r24, r3
  M  335 ble 52
  M  336 lwz r3, 0(0)
  M  337 li r4, 0
  M  338 addis r0, r3, 1
  M  339 add r0, r0, r27
  M  340 add r3, r0, r28
  M  341 stb r4, -0x6fbc(r3)
  M  342 lwz r3, 0(0)
  M  343 addis r0, r3, 1
  M  344 add r0, r0, r27
  M  345 add r3, r0, r28
  M  346 stb r4, -0x6fbb(r3)
  M  347 b 176
  M  348 add r0, r21, r24
  B  338 cmplw r31, r3
  B  339 ble 56
  B  340 lwz r4, 0(0)
  B  341 li r5, 0
  B  342 li r3, 0
  B  343 addis r0, r4, 1
  B  344 add r0, r0, r29
  B  345 add r4, r0, r30
  B  346 stb r5, -0x6fbc(r4)
  B  347 lwz r4, 0(0)
  B  348 addis r0, r4, 1
  B  349 add r0, r0, r29
  B  350 add r4, r0, r30
  B  351 stb r5, -0x6fbb(r4)
  B  352 b 184
  B  353 add r0, r31, r22
--- replace mine 350:364 base 355:370
  M  350 ble 52
  M  351 lwz r3, 0(0)
  M  352 li r4, 0
  M  353 addis r0, r3, 1
  M  354 add r0, r0, r27
  M  355 add r3, r0, r28
  M  356 stb r4, -0x6fbc(r3)
  M  357 lwz r3, 0(0)
  M  358 addis r0, r3, 1
  M  359 add r0, r0, r27
  M  360 add r3, r0, r28
  M  361 stb r4, -0x6fbb(r3)
  M  362 b 116
  M  363 cmpwi r22, 0
  B  355 ble 56
  B  356 lwz r4, 0(0)
  B  357 li r5, 0
  B  358 li r3, 0
  B  359 addis r0, r4, 1
  B  360 add r0, r0, r29
  B  361 add r4, r0, r30
  B  362 stb r5, -0x6fbc(r4)
  B  363 lwz r4, 0(0)
  B  364 addis r0, r4, 1
  B  365 add r0, r0, r29
  B  366 add r4, r0, r30
  B  367 stb r5, -0x6fbb(r4)
  B  368 b 120
  B  369 cmpwi r21, 0
--- replace mine 366:368 base 372:374
  M  366 mr r5, r21
  M  367 mr r6, r24
  B  372 mr r5, r22
  B  373 mr r6, r31
--- replace mine 373:375 base 379:381
  M  373 mr r24, r3
  M  374 blt 328
  B  379 bge 8
  B  380 b 72
--- replace mine 376:377 base 382:383
  M  376 mr r5, r22
  B  382 mr r5, r21
--- replace mine 378:379 base 384:385
  M  378 add r3, r4, r25
  B  384 add r3, r4, r27
--- replace mine 380:381 base 386:387
  M  380 add r3, r3, r26
  B  386 add r3, r3, r28
--- replace mine 385:386 base 391:392
  M  385 mr r4, r21
  B  391 mr r4, r22
--- replace mine 387:389 base 393:395
  M  387 add r0, r0, r25
  M  388 add r3, r0, r26
  B  393 add r0, r0, r27
  B  394 add r3, r0, r28
--- replace mine 391:393 base 397:403
  M  391 lwz r5, 0x3c(r31)
  M  392 mr r3, r29
  B  397 li r3, 0
  B  398 cmpwi r3, 0
  B  399 bge 8
  B  400 b 424
  B  401 lwz r5, 0x3c(r26)
  B  402 mr r3, r24
--- replace mine 395:396 base 405:406
  M  395 rlwinm r22, r5, 0, 0, 0x16
  B  405 rlwinm r23, r5, 0, 0, 0x16
--- replace mine 397:399 base 407:409
  M  397 subf r21, r22, r5
  M  398 subf r23, r22, r0
  B  407 subf r21, r23, r5
  B  408 subf r22, r23, r0
--- replace mine 401:407 base 411:416
  M  401 mr r24, r3
  M  402 blt 176
  M  403 lis r4, -0x8000
  M  404 cmplw r22, r4
  M  405 bge 160
  M  406 lhz r3, 0x38(r31)
  B  411 mr r29, r3
  B  412 blt 180
  B  413 cmpwi r23, 0
  B  414 blt 24
  B  415 lhz r3, 0x38(r26)
--- replace mine 409:414 base 418:424
  M  409 cmplw r22, r0
  M  410 bgt 140
  M  411 add r3, r22, r23
  M  412 cmplw r3, r4
  M  413 bge 128
  B  418 cmplw r23, r0
  B  419 ble 12
  B  420 li r29, 0
  B  421 b 144
  B  422 add. r3, r23, r22
  B  423 blt 12
--- replace mine 415:416 base 425:428
  M  415 bgt 120
  B  425 ble 12
  B  426 li r29, 0
  B  427 b 120
--- replace mine 417:419 base 429:431
  M  417 mr r5, r23
  M  418 mr r6, r22
  B  429 mr r5, r22
  B  430 mr r6, r23
--- replace mine 424:426 base 436:438
  M  424 mr r24, r3
  M  425 blt 84
  B  436 mr r29, r3
  B  437 blt 80
--- replace mine 430:432 base 442:444
  M  430 add r0, r0, r25
  M  431 add r3, r0, r26
  B  442 add r0, r0, r27
  B  443 add r3, r0, r28
--- replace mine 437:439 base 449:451
  M  437 add r0, r4, r25
  M  438 add r3, r0, r26
  B  449 add r0, r4, r27
  B  450 add r3, r0, r28
--- replace mine 443:446 base 455:457
  M  443 li r24, 0
  M  444 b 40
  M  445 li r24, 0
  B  455 li r29, 0
  B  456 b 36
--- replace mine 450:452 base 461:463
  M  450 add r0, r0, r25
  M  451 add r3, r0, r26
  B  461 add r0, r0, r27
  B  462 add r3, r0, r28
--- replace mine 454:455 base 465:466
  M  454 cmpwi r24, 0
  B  465 cmpwi r29, 0
--- replace mine 456:457 base 467:468
  M  456 mr r3, r24
  B  467 mr r3, r29
--- replace mine 463:464 base 474:475
  M  463 mulli r7, r29, 0x5f4
  B  474 mulli r7, r24, 0x5f4
--- replace mine 467:468 base 478:479
  M  467 mulli r6, r30, 0xc
  B  478 mulli r6, r25, 0xc
--- replace mine 472:473 base 483:484
  M  472 lhz r5, 0x38(r31)
  B  483 lhz r5, 0x38(r26)
--- replace mine 477:478 base 488:489
  M  477 lwz r5, 0x28(r31)
  B  488 lwz r5, 0x28(r26)
--- replace mine 481:482 base 492:493
  M  481 lbz r4, 0x34(r31)
  B  492 lbz r4, 0x34(r26)
--- replace mine 488:489 base 499:500
  M  488 lbz r4, 0x34(r31)
  B  499 lbz r4, 0x34(r26)
```

## src/scene/address/iplAddressEdit: stt_add_code_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x1bc base 0x1bc insns 111/111
diffs 8: [50, 56, 74, 77, 85, 87, 93, 95]
    50 M mr r30, r3
       B mr r28, r3
    56 M mr r4, r30
       B mr r4, r28
    74 M mr r29, r3
       B mr r28, r3
    77 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- temporary reuse: final fade controller reused for empty and nonempty name branches: exact False; insns 111/111; differences 4; objdiff 99.81982

```text
src 0x1bc base 0x1bc insns 111/111
diffs 4: [85, 87, 93, 95]
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

- branch-local boundaries: independent base name-fade controllers in both branches: exact True; insns 111/111; differences 0; objdiff 100.0; candidate exact without report regressions

```text
src 0x1bc base 0x1bc insns 111/111
diffs 0: []
```

- branch direction: empty-name animation arm first with shared fade controller: exact False; insns 111/111; differences 7; objdiff 99.75676

```text
src 0x1bc base 0x1bc insns 111/111
diffs 7: [80, 82, 85, 87, 90, 93, 95]
    80 M bne 36
       B beq 36
    82 M li r4, 3
       B li r4, 2
    85 M mr r29, r3
       B mr r28, r3
    87 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
    90 M li r4, 2
       B li r4, 3
    93 M mr r29, r3
       B mr r28, r3
    95 M stw r30, 0x14(r29)
       B stw r30, 0x14(r28)
```

## src/scene/address/iplAddress: stt_cover_backward__Q33ipl5scene7AddressFv

```text
src 0xc4 base 0xe4 insns 49/57
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 3:5 base 3:5
  M    3 stw r0, 0x24(r1)
  M    4 stw r31, 0x1c(r1)
  B    3 stw r0, 0x34(r1)
  B    4 stw r31, 0x2c(r1)
--- replace mine 11:12 base 11:12
  M   11 beq 112
  B   11 beq 144
--- replace mine 13:15 base 13:15
  M   13 lfs f1, 0(0)
  M   14 lfs f0, 4(r3)
  B   13 lfs f0, 0(0)
  B   14 lfs f1, 4(r3)
--- insert mine 16:16 base 16:18
  B   16 fneg f0, f0
  B   17 addi r4, r4, 0
--- delete mine 17:19 base 19:19
  M   17 addi r4, r4, 0
  M   18 fneg f0, f0
--- replace mine 20:22 base 20:30
  M   20 stfs f1, 8(r1)
  M   21 stfs f0, 0xc(r1)
  B   20 stfs f0, 8(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
  B   28 stfs f1, 0x18(r1)
  B   29 stfs f0, 0x1c(r1)
--- replace mine 30:31 base 38:39
  M   30 addi r5, r1, 8
  B   38 addi r5, r1, 0x18
--- replace mine 44:46 base 52:54
  M   44 lwz r0, 0x24(r1)
  M   45 lwz r31, 0x1c(r1)
  B   52 lwz r0, 0x34(r1)
  B   53 lwz r31, 0x2c(r1)
--- replace mine 47:48 base 55:56
  M   47 addi r1, r1, 0x20
  B   55 addi r1, r1, 0x30
```

- inline conversion helper with offset declared before two base intermediates: exact False; insns 55/57; differences None; objdiff 82.2807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 18:19 base 18:19
  M   18 fneg f2, f1
  B   18 fneg f1, f1
--- delete mine 20:21 base 20:20
  M   20 frsp f1, f0
--- replace mine 22:24 base 21:28
  M   22 frsp f0, f2
  M   23 stfs f2, 0xc(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x10(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x14(r1)
```

- inline conversion helper with copied vector declared before offset: exact False; insns 55/57; differences None; objdiff 82.22807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 18:19 base 18:19
  M   18 fneg f2, f1
  B   18 fneg f1, f1
--- delete mine 20:21 base 20:20
  M   20 frsp f1, f0
--- replace mine 22:26 base 21:30
  M   22 frsp f0, f2
  M   23 stfs f2, 0xc(r1)
  M   24 stfs f1, 0x10(r1)
  M   25 stfs f0, 0x14(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
  B   28 stfs f1, 0x18(r1)
  B   29 stfs f0, 0x1c(r1)
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x18(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x1c(r1)
--- replace mine 36:37 base 38:39
  M   36 addi r5, r1, 0x10
  B   38 addi r5, r1, 0x18
```

- inline conversion helper with negation initialized by base constructor: exact False; insns 55/57; differences None; objdiff 69.22807

```text
src 0xdc base 0xe4 insns 55/57
--- replace mine 11:12 base 11:12
  M   11 beq 136
  B   11 beq 144
--- replace mine 13:16 base 13:18
  M   13 lfs f1, 0(0)
  M   14 lfs f0, 4(r3)
  M   15 addi r3, r1, 8
  B   13 lfs f0, 0(0)
  B   14 lfs f1, 4(r3)
  B   15 lis r4, 0
  B   16 fneg f0, f0
  B   17 addi r4, r4, 0
--- replace mine 17:23 base 19:28
  M   17 fneg f2, f0
  M   18 bl 0
  M   19 lfs f1, 8(r1)
  M   20 lis r4, 0
  M   21 lfs f0, 0xc(r1)
  M   22 addi r4, r4, 0
  B   19 li r5, 1
  B   20 stfs f0, 8(r1)
  B   21 stfs f1, 0xc(r1)
  B   22 lwz r3, 8(r1)
  B   23 lwz r0, 0xc(r1)
  B   24 stw r3, 0x10(r1)
  B   25 stw r0, 0x14(r1)
  B   26 lfs f1, 0x10(r1)
  B   27 lfs f0, 0x14(r1)
--- delete mine 24:25 base 29:29
  M   24 li r5, 1
--- delete mine 27:28 base 31:31
  M   27 stfs f1, 0x10(r1)
--- delete mine 29:30 base 32:32
  M   29 stfs f0, 0x14(r1)
```

## src/scene/address/iplAddressEdit: stt_wait_decide_anm__Q33ipl5scene11AddressEditFv

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- inline scopes: independent animators for each case-one animation: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- inline scopes and pane lifetimes: unique animators and all three pane locals: exact False; insns 379/379; differences 4; objdiff 99.94723

```text
src 0x5ec base 0x5ec insns 379/379
diffs 4: [148, 156, 179, 185]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
   179 M mr r27, r3
       B mr r28, r3
   185 M mr r4, r27
       B mr r4, r28
```

- local lifetime: question pane declared before case-one animation scopes: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

## src/scene/address/iplAddress: onEvent__Q33ipl5scene12AddressEventFUlUlPv

```text
src 0x284 base 0x284 insns 161/161
diffs 2: [32, 37]
    32 M beq -22047
       B beq -21703
    37 M beq -22067
       B beq -21723
```

- gate discrepancy audit: controller declaration before pane lookup: exact False; insns 161/161; differences 2; objdiff 100.0

```text
src 0x284 base 0x284 insns 161/161
diffs 2: [32, 37]
    32 M beq -22047
       B beq -21703
    37 M beq -22067
       B beq -21723
```

- gate discrepancy audit: unsigned-int event selector local: exact False; insns 161/161; differences 2; objdiff 100.0

```text
src 0x284 base 0x284 insns 161/161
diffs 2: [32, 37]
    32 M beq -22047
       B beq -21703
    37 M beq -22067
       B beq -21723
```

- gate discrepancy audit: positive dragging branch with explicit channel comparison: exact False; insns 161/161; differences 12; objdiff 96.27329

```text
src 0x284 base 0x284 insns 161/161
diffs 12: [32, 37, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59]
    32 M beq -22047
       B beq -21703
    37 M beq -22067
       B beq -21723
    50 M lwz r12, 0(r30)
       B lbz r0, 0(r31)
    51 M mr r3, r30
       B cmpwi r0, 0x42
    52 M lwz r12, 0x10(r12)
       B bne 44
    53 M mtctr r12
       B lwz r12, 0(r30)
    54 M bctrl
       B mr r3, r30
    55 M lwz r0, 0x10(r29)
       B lwz r12, 0x10(r12)
    56 M cmpw r0, r3
       B mtctr r12
    57 M bne 24
       B bctrl
    58 M lbz r0, 0(r31)
       B lwz r0, 0x10(r29)
    59 M cmpwi r0, 0x42
       B cmpw r0, r3
```

## src/scene/address/iplAddressEdit: get_friendinfo__Q33ipl5scene11AddressEditFv

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline helper boundary: named textbox assignment retains name argument: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline helper boundary: named textbox assignment retains display argument: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

- inline helper boundaries: name and display assignments share named-pane helper: exact False; insns 82/84; differences None; objdiff 88.03571

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

## src/scene/address/iplAddressEdit: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0x178 base 0x178 insns 94/94
diffs 5: [20, 29, 41, 82, 86]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
    82 M mr r30, r3
       B mr r29, r3
    86 M stw r3, 0x14(r30)
       B stw r3, 0x14(r29)
```

- distinct normalized completion phases with base controller: exact False; insns 94/94; differences 13; objdiff 89.94681

```text
src 0x178 base 0x178 insns 94/94
diffs 13: [37, 38, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51]
    37 M addi r0, r5, -1
       B addi r5, r5, -1
    38 M cntlzw r0, r0
       B addic r0, r5, -1
    40 M srwi r30, r0, 5
       B subfe r0, r0, r5
    41 M bl 0
       B and r5, r29, r0
    42 M cntlzw r0, r30
       B addic r0, r5, -1
    43 M lwz r3, 0x14(r3)
       B subfe r30, r0, r5
    44 M srwi r0, r0, 5
       B bl 0
    45 M and r4, r29, r0
       B lwz r3, 0x14(r3)
    47 M addic r0, r4, -1
       B addic r0, r3, -1
    48 M subfe r4, r0, r4
       B subfe r0, r0, r3
    49 M addic r0, r3, -1
       B and r3, r30, r0
    50 M subfe r0, r0, r3
       B addic r0, r3, -1
    51 M and. r0, r4, r0
       B subfe. r0, r0, r3
```

- distinct normalized completion phases with BOOL intermediate: exact False; insns 94/94; differences 13; objdiff 89.94681

```text
src 0x178 base 0x178 insns 94/94
diffs 13: [37, 38, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51]
    37 M addi r0, r5, -1
       B addi r5, r5, -1
    38 M cntlzw r0, r0
       B addic r0, r5, -1
    40 M srwi r30, r0, 5
       B subfe r0, r0, r5
    41 M bl 0
       B and r5, r29, r0
    42 M cntlzw r0, r30
       B addic r0, r5, -1
    43 M lwz r3, 0x14(r3)
       B subfe r30, r0, r5
    44 M srwi r0, r0, 5
       B bl 0
    45 M and r4, r29, r0
       B lwz r3, 0x14(r3)
    47 M addic r0, r4, -1
       B addic r0, r3, -1
    48 M subfe r4, r0, r4
       B subfe r0, r0, r3
    49 M addic r0, r3, -1
       B and r3, r30, r0
    50 M subfe r0, r0, r3
       B addic r0, r3, -1
    51 M and. r0, r4, r0
       B subfe. r0, r0, r3
```

- separate initial completion and mutable remaining-animation accumulator: exact False; insns 94/94; differences 3; objdiff 99.84042

```text
src 0x178 base 0x178 insns 94/94
diffs 3: [20, 29, 41]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
```
