# sol-med matching attempts

Baseline and per-attempt instruction differences were measured with ctxdiff. Unaccepted variants were restored.

## Data: AddressEdit String::setEMail source order

Moved the real setEMail definition after the scene functions, matching target object order and moving its ellipsis literal after arc, empty text, and G_mii.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 17384/27112 data 48/2560 functions 81/94 fuzzy 98.6425 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 81/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match None
[src/scene/address/iplAddressEdit]   section .data size 2152 match 71.23057
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 98.591545
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 98.64252
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.44634
[src/scene/address/iplAddressEdit]   below 100: stt_wait_decide_anm__Q33ipl5scene11AddressEditFv 99.97362
[src/scene/address/iplAddressEdit]   below 100: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404
[src/scene/address/iplAddressEdit]   below 100: stt_add_code_fadeout__Q33ipl5scene11AddressEditFv 99.63964
[src/scene/address/iplAddressEdit]   below 100: stt_add_mii_input__Q33ipl5scene11AddressEditFv 70.84042
[src/scene/address/iplAddressEdit]   below 100: stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv 99.83871
[src/scene/address/iplAddressEdit]   below 100: stt_select_mii__Q33ipl5scene11AddressEditFv 99.85
[src/scene/address/iplAddressEdit]   below 100: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066
[src/scene/address/iplAddressEdit]   below 100: start_left_event__Q33ipl5scene11AddressEditFPCc 83.291664
[src/scene/address/iplAddressEdit]   below 100: start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci 95.23569
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit]   below 100: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664
[src/scene/address/iplAddressEdit] baseline: code 17384/27112 data 24 functions 81 fuzzy 98.6425
regressions vs baseline: 0
global matched_code_percent: 83.80901 -> 83.80901
global fuzzy_match_percent: 97.60954 -> 97.60954
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
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

- local lifetime: distinct first question pane, retain subsequent text pane: exact False; insns 379/379; differences 2; objdiff 99.97362

- inline boundary: animation pointers use FrameController base type: exact False; insns 379/379; differences 14; objdiff 99.8153

- loop form: do-while animation completion accumulation: exact False; insns 379/379; differences 2; objdiff 99.97362

## src/scene/address/iplAddressEdit: stt_select_mii__Q33ipl5scene11AddressEditFv

```text
src 0x190 base 0x190 insns 100/100
diffs 3: [71, 73, 76]
    71 M mr r31, r29
       B mr r30, r29
    73 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    76 M mr r4, r31
       B mr r4, r30
```

- stack frame: face metadata declared at function scope: exact False; insns 100/100; differences 3; objdiff 99.85

- condition form: completion flag computed before handler restore: exact False; insns 107/100; differences None; objdiff 92.15

- loop form: walk point counters by pointer after restoring handler: exact False; insns 100/100; differences 9; objdiff 92.98

## src/scene/address/iplAddressEdit: stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv

```text
src 0xf8 base 0xf8 insns 62/62
diffs 2: [33, 37]
    33 M mr r31, r3
       B mr r30, r3
    37 M stw r3, 0x14(r31)
       B stw r3, 0x14(r30)
```

- local lifetime: scene button fetched only in confirming arm: exact False; insns 62/62; differences 27; objdiff 32.258064

- branch form: ordered if-else substate dispatch: exact False; insns 57/62; differences None; objdiff 85.145164

- inline boundary: animator stored through FrameController base: exact True; insns 62/62; differences 0; objdiff 100.0; candidate exact without report regressions

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

- local type and lifetime: completion and label declared at entry: exact False; insns 90/94; differences None; objdiff 95.42553

- branch form: separate non-short-circuit completion operands: exact False; insns 94/94; differences 6; objdiff 99.57447

- inline boundary: base controller plus explicit finished guard: exact False; insns 94/94; differences 3; objdiff 99.84042

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

- local type: animator and pane lifetimes through references: exact False; insns 111/111; differences 6; objdiff 99.72973

- condition form: boolean combined animation completion then body: exact False; insns 111/111; differences 8; objdiff 99.63964

- inline boundary: base controller for retained animation pointer: exact False; insns 111/111; differences 8; objdiff 99.63964

## src/scene/address/iplAddressEdit: update_friendinfo__Q33ipl5scene11AddressEditFv

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

- local lifetime: retain String reference before name clear and copy: exact False; insns 38/38; differences 2; objdiff 99.42105

- temporary boundaries: both copy arguments named in target evaluation order: exact False; insns 38/38; differences 2; objdiff 99.42105

- operand form: name copy through array first-element addresses: exact False; insns 38/38; differences 2; objdiff 99.42105

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

- local construction: field-initialize balloon positions after default construction: exact False; insns 177/182; differences None; objdiff 92.62637

- branch form: direct state if dispatch in place of outer switch: exact False; insns 180/182; differences None; objdiff 98.72527

- operand order: inline offsets and explicit half-height product: exact False; insns 177/182; differences None; objdiff 95.0

## src/scene/address/iplAddressEdit: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err

```text
src 0x130 base 0x12c insns 76/75
--- delete mine 46:47 base 46:46
  M   46 li r4, 0x1c5
```

- stack declaration order: initialized default message at function entry: exact False; insns 77/75; differences None; objdiff 95.92

- branch form: exhaustive if-else with safe fallback: exact False; insns 65/75; differences None; objdiff 80.653336

- temporary boundary: retain resolved message before length calculation: exact False; insns 76/75; differences None; objdiff 98.666664

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

- stack/local declaration: board objects declared together before loading: exact False; insns 820/820; differences 323; objdiff 97.44634

- loop form: walk button pane names through table pointers: exact False; insns 821/820; differences None; objdiff 96.267075

- inline boundary: animation pointers use FrameController base: exact False; insns 820/820; differences 323; objdiff 97.44634

## src/scene/address/iplAddressEdit: start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci

```text
src 0x4b0 base 0x4a4 insns 300/297
--- replace mine 17:18 base 17:18
  M   17 beq 1108
  B   17 beq 1096
--- replace mine 23:24 base 23:24
  M   23 bne 1084
  B   23 bne 1072
--- replace mine 27:29 base 27:30
  M   27 cmpwi r3, 0
  M   28 bne 1064
  B   27 cntlzw r0, r3
  B   28 rlwinm. r0, r0, 0x1b, 5, 0x1f
  B   29 beq 1048
--- replace mine 32:33 base 33:34
  M   32 bgt 1048
  B   33 bgt 1032
--- replace mine 58:59 base 59:60
  M   58 mr r28, r3
  B   59 mr r26, r3
--- replace mine 64:65 base 65:66
  M   64 mr r26, r3
  B   65 mr r28, r3
--- replace mine 67:68 base 68:69
  M   67 mr r5, r28
  B   68 mr r5, r26
--- replace mine 69:70 base 70:71
  M   69 mr r3, r26
  B   70 mr r3, r28
--- replace mine 71:72 base 72:73
  M   71 mr r3, r26
  B   72 mr r3, r28
--- insert mine 76:76 base 77:78
  B   77 li r0, 0xd
--- insert mine 77:77 base 79:80
  B   79 stw r0, 0x38(r1)
--- delete mine 80:82 base 83:83
  M   80 li r0, 0xd
  M   81 stw r0, 0x38(r1)
--- replace mine 116:117 base 117:118
  M  116 b 712
  B  117 b 696
--- replace mine 133:134 base 134:135
  M  133 b 56
  B  134 b 72
--- replace mine 176:177 base 177:178
  M  176 b 472
  B  177 b 456
--- replace mine 192:193 base 193:194
  M  192 mr r27, r3
  B  193 mr r26, r3
--- replace mine 196:197 base 197:198
  M  196 mr r26, r3
  B  197 mr r27, r3
--- replace mine 204:206 base 205:207
  M  204 mr r4, r27
  M  205 mr r5, r26
  B  205 mr r4, r26
  B  206 mr r5, r27
--- insert mine 214:214 base 215:216
  B  215 li r0, 0xd
--- insert mine 215:215 base 217:218
  B  217 stw r0, 8(r1)
--- delete mine 218:220 base 221:221
  M  218 li r0, 0xd
  M  219 stw r0, 8(r1)
--- delete mine 242:246 base 243:243
  M  242 bl 0
  M  243 mr r3, r31
  M  244 li r4, 1
  M  245 li r5, 0x2e
```

- stack declarations: shared keyboard setting scoped before switch: exact False; insns 300/297; differences None; objdiff 95.30303

- condition form: positive equality and early non-input exit: exact False; insns 300/297; differences None; objdiff 95.23569

- temporaries and operand order: dictionary pointers as const local copies: exact False; insns 300/297; differences None; objdiff 97.996635

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

- stack layout: code and mail buffers both declared before cache copy: exact False; insns 82/84; differences None; objdiff 88.03571

- inline boundary: use String getters introduced as local references: exact False; insns 82/84; differences None; objdiff 88.03571

- temporary lifetime: pane lookup evaluated after copying display pointer through argument sequence: exact False; insns 82/84; differences None; objdiff 88.03571

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

- branch fallthrough and local reference: button3 shares ordinary count path: exact False; insns 94/96; differences None; objdiff 97.8125

- branch fallthrough and base animation helper: exact False; insns 94/96; differences None; objdiff 97.8125

- branch fallthrough and if-based state dispatch: exact False; insns 92/96; differences None; objdiff 95.625

## src/scene/address/iplAddressEdit: stt_add_mii_input__Q33ipl5scene11AddressEditFv

```text
src 0x194 base 0x178 insns 101/94
--- replace mine 6:7 base 6:7
  M    6 mr r31, r3
  B    6 mr r29, r3
--- replace mine 11:19 base 11:24
  M   11 beq 232
  M   12 lwz r29, 0x23c(r3)
  M   13 cmpwi r29, 0
  M   14 blt 220
  M   15 lis r30, 0
  M   16 clrlwi r4, r29, 0x10
  M   17 addi r30, r30, 0
  M   18 lwz r3, 0x70(r30)
  B   11 beq 204
  B   12 lwz r12, 0(r29)
  B   13 mr r3, r29
  B   14 lwz r12, 0x10(r12)
  B   15 mtctr r12
  B   16 bctrl 
  B   17 lwz r30, 0x23c(r3)
  B   18 cmpwi r30, 0
  B   19 blt 172
  B   20 lis r31, 0
  B   21 clrlwi r4, r30, 0x10
  B   22 addi r31, r31, 0
  B   23 lwz r3, 0x70(r31)
--- replace mine 21:23 base 26:28
  M   21 beq 192
  M   22 lwz r0, 0x4e8(r31)
  B   26 beq 144
  B   27 lwz r0, 0x4e8(r29)
--- replace mine 24:25 base 29:30
  M   24 bne 180
  B   29 bne 132
--- replace mine 26:27 base 31:32
  M   26 clrlwi r6, r29, 0x10
  B   31 clrlwi r6, r30, 0x10
--- replace mine 30:31 base 35:36
  M   30 addi r3, r31, 0x4e0
  B   35 addi r3, r29, 0x4e0
--- replace mine 34:36 base 39:44
  M   34 bne 140
  M   35 lbz r3, 0x34(r1)
  B   39 bne 92
  B   40 addi r3, r29, 0x4e0
  B   41 addi r4, r1, 0x34
  B   42 li r5, 8
  B   43 bl 0
--- replace mine 37:40 base 45:49
  M   37 lbz r0, 0x35(r1)
  M   38 mr r7, r29
  M   39 mr r9, r31
  B   45 lwz r3, 0x70(r31)
  B   46 lwz r4, 0x28(r31)
  B   47 mr r7, r30
  B   48 mr r9, r29
--- delete mine 41:42 base 50:50
  M   41 stb r3, 0x4e0(r31)
--- delete mine 44:59 base 52:52
  M   44 stb r0, 0x4e1(r31)
  M   45 lbz r3, 0x36(r1)
  M   46 lbz r0, 0x37(r1)
  M   47 stb r3, 0x4e2(r31)
  M   48 stb r0, 0x4e3(r31)
  M   49 lbz r3, 0x38(r1)
  M   50 lbz r0, 0x39(r1)
  M   51 stb r3, 0x4e4(r31)
  M   52 stb r0, 0x4e5(r31)
  M   53 lbz r3, 0x3a(r1)
  M   54 lbz r0, 0x3b(r1)
  M   55 stb r3, 0x4e6(r31)
  M   56 stb r0, 0x4e7(r31)
  M   57 lwz r3, 0x70(r30)
  M   58 lwz r4, 0x28(r30)
--- replace mine 61:63 base 54:56
  M   61 lwz r3, 0x7c(r31)
  M   62 stw r0, 0x4e8(r31)
  B   54 lwz r3, 0x7c(r29)
  B   55 stw r0, 0x4e8(r29)
--- replace mine 67:68 base 60:61
  M   67 lwz r3, 0xa8(r31)
  B   60 lwz r3, 0xa8(r29)
--- replace mine 69:71 base 62:64
  M   69 lwz r12, 0(r31)
  M   70 mr r3, r31
  B   62 lwz r12, 0(r29)
  B   63 mr r3, r29
--- replace mine 82:84 base 75:77
  M   82 cmpwi r31, 0
  M   83 mr r30, r31
  B   75 cmpwi r29, 0
  B   76 mr r30, r29
--- replace mine 85:86 base 78:79
  M   85 addi r30, r31, 0x58
  B   78 addi r30, r29, 0x58
--- replace mine 93:95 base 86:88
  M   93 stw r3, 0x64(r31)
  M   94 stw r0, 0x4e8(r31)
  B   86 stw r3, 0x64(r29)
  B   87 stw r0, 0x4e8(r29)
```

- virtual lookup/copy and stack declaration at entry: exact False; insns 94/94; differences 3; objdiff 99.84042

- virtual lookup/copy and boolean completion flag: exact False; insns 101/94; differences None; objdiff 91.64893

- virtual lookup/copy and child existence expression without retained pointer: exact False; insns 94/94; differences 3; objdiff 99.84042

## Data: real cached friend record definition

The original owns a 320-byte bss friend record, but source had only an extern declaration. Define the real scene namespace record and use its ordinary C++ name.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 17632/27112 data 368/2560 functions 82/94 fuzzy 98.6440 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 82/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 71.23057
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 98.591545
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 98.644
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.44634
[src/scene/address/iplAddressEdit]   below 100: stt_wait_decide_anm__Q33ipl5scene11AddressEditFv 99.97362
[src/scene/address/iplAddressEdit]   below 100: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404
[src/scene/address/iplAddressEdit]   below 100: stt_add_code_fadeout__Q33ipl5scene11AddressEditFv 99.63964
[src/scene/address/iplAddressEdit]   below 100: stt_add_mii_input__Q33ipl5scene11AddressEditFv 70.84042
[src/scene/address/iplAddressEdit]   below 100: stt_select_mii__Q33ipl5scene11AddressEditFv 99.85
[src/scene/address/iplAddressEdit]   below 100: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066
[src/scene/address/iplAddressEdit]   below 100: start_left_event__Q33ipl5scene11AddressEditFPCc 83.291664
[src/scene/address/iplAddressEdit]   below 100: start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci 95.23569
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit]   below 100: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664
[src/scene/address/iplAddressEdit] baseline: code 17384/27112 data 24 functions 81 fuzzy 98.6425
regressions vs baseline: 0
global matched_code_percent: 83.80901 -> 83.81729
global fuzzy_match_percent: 97.60954 -> 97.60954
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.17310
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## src/scene/address/iplAddressEdit: stt_select_mii__Q33ipl5scene11AddressEditFv

```text
src 0x190 base 0x190 insns 100/100
diffs 3: [71, 73, 76]
    71 M mr r31, r29
       B mr r30, r29
    73 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    76 M mr r4, r31
       B mr r4, r30
```

- inline conversion: reference event handler before scene lookup: exact False; insns 96/100; differences None; objdiff 92.8

- inline conversion: event handler reference after scene lookup: exact False; insns 96/100; differences None; objdiff 92.8

- inline conversion: ButtonEventHandlerBase reference with restored scene: exact False; insns 96/100; differences None; objdiff 92.8

## src/scene/address/iplAddressEdit: stt_add_mii_input__Q33ipl5scene11AddressEditFv

```text
src 0x194 base 0x178 insns 101/94
--- replace mine 6:7 base 6:7
  M    6 mr r31, r3
  B    6 mr r29, r3
--- replace mine 11:19 base 11:24
  M   11 beq 232
  M   12 lwz r29, 0x23c(r3)
  M   13 cmpwi r29, 0
  M   14 blt 220
  M   15 lis r30, 0
  M   16 clrlwi r4, r29, 0x10
  M   17 addi r30, r30, 0
  M   18 lwz r3, 0x70(r30)
  B   11 beq 204
  B   12 lwz r12, 0(r29)
  B   13 mr r3, r29
  B   14 lwz r12, 0x10(r12)
  B   15 mtctr r12
  B   16 bctrl 
  B   17 lwz r30, 0x23c(r3)
  B   18 cmpwi r30, 0
  B   19 blt 172
  B   20 lis r31, 0
  B   21 clrlwi r4, r30, 0x10
  B   22 addi r31, r31, 0
  B   23 lwz r3, 0x70(r31)
--- replace mine 21:23 base 26:28
  M   21 beq 192
  M   22 lwz r0, 0x4e8(r31)
  B   26 beq 144
  B   27 lwz r0, 0x4e8(r29)
--- replace mine 24:25 base 29:30
  M   24 bne 180
  B   29 bne 132
--- replace mine 26:27 base 31:32
  M   26 clrlwi r6, r29, 0x10
  B   31 clrlwi r6, r30, 0x10
--- replace mine 30:31 base 35:36
  M   30 addi r3, r31, 0x4e0
  B   35 addi r3, r29, 0x4e0
--- replace mine 34:36 base 39:44
  M   34 bne 140
  M   35 lbz r3, 0x34(r1)
  B   39 bne 92
  B   40 addi r3, r29, 0x4e0
  B   41 addi r4, r1, 0x34
  B   42 li r5, 8
  B   43 bl 0
--- replace mine 37:40 base 45:49
  M   37 lbz r0, 0x35(r1)
  M   38 mr r7, r29
  M   39 mr r9, r31
  B   45 lwz r3, 0x70(r31)
  B   46 lwz r4, 0x28(r31)
  B   47 mr r7, r30
  B   48 mr r9, r29
--- delete mine 41:42 base 50:50
  M   41 stb r3, 0x4e0(r31)
--- delete mine 44:59 base 52:52
  M   44 stb r0, 0x4e1(r31)
  M   45 lbz r3, 0x36(r1)
  M   46 lbz r0, 0x37(r1)
  M   47 stb r3, 0x4e2(r31)
  M   48 stb r0, 0x4e3(r31)
  M   49 lbz r3, 0x38(r1)
  M   50 lbz r0, 0x39(r1)
  M   51 stb r3, 0x4e4(r31)
  M   52 stb r0, 0x4e5(r31)
  M   53 lbz r3, 0x3a(r1)
  M   54 lbz r0, 0x3b(r1)
  M   55 stb r3, 0x4e6(r31)
  M   56 stb r0, 0x4e7(r31)
  M   57 lwz r3, 0x70(r30)
  M   58 lwz r4, 0x28(r30)
--- replace mine 61:63 base 54:56
  M   61 lwz r3, 0x7c(r31)
  M   62 stw r0, 0x4e8(r31)
  B   54 lwz r3, 0x7c(r29)
  B   55 stw r0, 0x4e8(r29)
--- replace mine 67:68 base 60:61
  M   67 lwz r3, 0xa8(r31)
  B   60 lwz r3, 0xa8(r29)
--- replace mine 69:71 base 62:64
  M   69 lwz r12, 0(r31)
  M   70 mr r3, r31
  B   62 lwz r12, 0(r29)
  B   63 mr r3, r29
--- replace mine 82:84 base 75:77
  M   82 cmpwi r31, 0
  M   83 mr r30, r31
  B   75 cmpwi r29, 0
  B   76 mr r30, r29
--- replace mine 85:86 base 78:79
  M   85 addi r30, r31, 0x58
  B   78 addi r30, r29, 0x58
--- replace mine 93:95 base 86:88
  M   93 stw r3, 0x64(r31)
  M   94 stw r0, 0x4e8(r31)
  B   86 stw r3, 0x64(r29)
  B   87 stw r0, 0x4e8(r29)
```

- inline conversion: reference event handler before scene lookup: exact False; insns 90/94; differences None; objdiff 92.34042

- inline conversion: event handler reference after scene lookup: exact False; insns 90/94; differences None; objdiff 92.34042

- inline conversion: ButtonEventHandlerBase reference with restored scene: exact False; insns 90/94; differences None; objdiff 92.34042

## Data: Address decimal digit string terminator

Use the target ordinary wide digit string, including its terminator. Code indexes only the ten digits.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 18068/23988 data 60/1964 functions 90/101 fuzzy 98.9393 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 89/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 99.8935
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match None
[src/scene/address/iplAddress]   section .sdata size 16 match 92.30769
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 98.9393
[src/scene/address/iplAddress]   below 100: draw__Q33ipl5scene7AddressFv 97.276596
[src/scene/address/iplAddress]   below 100: stt_cover_backward__Q33ipl5scene7AddressFv 84.8421
[src/scene/address/iplAddress]   below 100: stt_backward__Q33ipl5scene7AddressFv 89.60674
[src/scene/address/iplAddress]   below 100: stt_loop_forward__Q33ipl5scene7AddressFv 92.72727
[src/scene/address/iplAddress]   below 100: set_page_text__Q33ipl5scene7AddressFPCci 93.13433
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 18336/23988 data 36 functions 91 fuzzy 99.0160
regressions vs baseline: 3
   main/src/scene/address/iplAddress: matched_code 18336 -> 18068
   main/src/scene/address/iplAddress: matched_functions 91 -> 90
   main/src/scene/address/iplAddress: function set_page_text__Q33ipl5scene7AddressFPCci 100 -> 93.13433
global matched_code_percent: 83.80901 -> 83.80834
global fuzzy_match_percent: 97.60954 -> 97.60895
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.17442
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE FAIL: 3 regressions vs main
```

## src/scene/address/iplAddress: set_page_text__Q33ipl5scene7AddressFPCci

```text
src 0x10c base 0x10c insns 67/67
diffs 0: []
```

- data string: explicitly sized digit array excludes terminator at copy boundary: compile failed: clude\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
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
#    1028:             const wchar_t digits[10] = L"0123456789"; 
#   Error:                                                     ^
#   (10147) too many initializers
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


- data string: static digit string indexed directly: exact False; insns 58/67; differences None; objdiff 69.910446

- data string: full literal with explicitly copied ten-digit working array: exact False; insns 77/67; differences None; objdiff 81.537315

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

- local declaration and loop lifetime: retain blank at entry, signed short index: exact False; insns 223/223; differences 130; objdiff 94.699554

- branch form: nested switches for state and mode: exact False; insns 224/223; differences None; objdiff 99.394615

- temporary boundary: cached friend number before presence check: exact False; insns 222/223; differences None; objdiff 99.34978

## src/scene/address/iplAddress: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err

```text
src 0x144 base 0x140 insns 81/80
--- delete mine 26:27 base 26:26
  M   26 li r30, 0x190
```

- stack declaration order: initialized message id before clearing output: exact False; insns 81/80; differences None; objdiff 97.4875

- branch form: fully initialized if/else error choice: exact False; insns 78/80; differences None; objdiff 91.2875

- temporaries: error text before output free-length calculation: exact False; insns 81/80; differences None; objdiff 98.6

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

- local lifetimes: fallthrough plus manager component named before pane: exact False; insns 270/270; differences 82; objdiff 98.40741

- branch form: fallthrough and positive valid-state scope: exact False; insns 270/270; differences 81; objdiff 98.42593

- inline boundaries: fallthrough and base frame-controller play expansion: exact False; insns 270/270; differences 4; objdiff 99.92593

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

- stack copies: base vector product then derived float copy: exact False; insns 241/235; differences None; objdiff 94.817024

- stack copies: raw base aggregate then derived conversion: exact False; insns 231/235; differences None; objdiff 97.106384

- temporary boundary: derived product then explicit base reference conversion: exact False; insns 241/235; differences None; objdiff 94.817024

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

- stack copies: base vector product then derived float copy: exact False; insns 173/165; differences None; objdiff 89.933334

- stack copies: raw aggregate and derived conversion: exact False; insns 163/165; differences None; objdiff 96.181816

- inline boundary: vector product plus base-controller animation helpers: exact False; insns 173/165; differences None; objdiff 89.81212

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

- local declaration lifetime: friend name before text-box lookup: exact False; insns 154/155; differences None; objdiff 84.535484

- branch form: valid-pair bool and ordinary accumulation loop: exact False; insns 159/155; differences None; objdiff 92.870964

- loop form: index characters instead of pointer walk: exact False; insns 155/155; differences 24; objdiff 94.80645

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

- stack copies: negated aggregate then base and derived conversion: exact False; insns 95/99; differences None; objdiff 84.72727

- stack copies: negated derived vector then explicit base-reference conversion: exact False; insns 95/99; differences None; objdiff 86.14141

- inline boundary: field-negated base vector and derived conversion: exact False; insns 95/99; differences None; objdiff 84.72727

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

- stack copies: negated aggregate then base and derived conversion: exact False; insns 89/89; differences 15; objdiff 89.24719

- stack copies: negated derived vector then explicit base-reference conversion: exact False; insns 89/89; differences 21; objdiff 86.146065

- inline boundary: field-negated base vector and derived conversion: exact False; insns 89/89; differences 15; objdiff 89.24719

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

- stack copies: negated aggregate then derived conversion: exact False; insns 53/57; differences None; objdiff 85.070175

- stack copies: negated derived vector then explicit base-reference conversion: exact False; insns 53/57; differences None; objdiff 70.4386

- inline boundary: base vector field-negation then derived conversion: exact False; insns 53/57; differences None; objdiff 85.070175

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

- local lifetime: named friend index before each separate accessor: exact False; insns 38/40; differences None; objdiff 78.625

- inline boundary: named record references at individual operations: exact False; insns 38/40; differences None; objdiff 78.5

- temporary boundary: friend name array reference before update: exact False; insns 37/40; differences None; objdiff 78.475

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

- local lifetime: security buffer reference with indexed loop: exact False; insns 610/609; differences None; objdiff 99.44992

- loop form: bound security pointer at each condition, write in body: exact False; insns 609/609; differences 14; objdiff 99.86043

- loop lifetime: reuse initialized return-value local for country mapping: exact False; insns 609/609; differences 14; objdiff 99.86043

## src/iplwww/www_wiisetting: Setter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue

```text
src 0x50c base 0x50c insns 323/323
diffs 43: [6, 7, 9, 12, 14, 50, 75, 80, 85, 86, 88, 89, 92, 95, 98, 100, 103, 104, 105, 108]
     6 M lis r28, 0
       B lis r31, 0
     7 M mr r30, r5
       B mr r29, r5
     9 M addi r28, r28, 0
       B addi r31, r31, 0
    12 M mr r31, r3
       B mr r30, r3
    14 M lfd f0, 8(r30)
       B lfd f0, 8(r29)
    50 M lfd f0, 8(r30)
       B lfd f0, 8(r29)
    75 M lfd f1, 8(r30)
       B lfd f1, 8(r29)
    80 M lbzx r5, r4, r31
       B lbzx r5, r4, r30
    85 M stbx r3, r4, r31
       B stbx r3, r4, r30
    86 M stb r31, 0(0)
       B stb r30, 0(0)
    88 M lfd f0, 8(r30)
       B lfd f0, 8(r29)
    89 M lis r29, 0
       B lis r28, 0
    92 M addi r29, r29, 0
       B addi r28, r28, 0
    95 M stbx r0, r29, r3
       B stbx r0, r28, r3
    98 M lwz r5, 0(r30)
       B lwz r5, 0(r29)
   100 M addi r3, r28, 0x290
       B addi r3, r31, 0x290
   103 M lbzx r5, r29, r31
       B lbzx r5, r28, r30
   104 M mr r4, r31
       B mr r4, r30
   105 M addi r3, r28, 0x2b5
       B addi r3, r31, 0x2b5
   108 M cmplwi r31, 0x45
       B cmplwi r30, 0x45
   111 M slwi r0, r31, 2
       B slwi r0, r30, 2
   123 M lbzx r3, r4, r31
       B lbzx r3, r4, r30
   129 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   132 M li r31, 0
       B li r30, 0
   133 M lis r30, 0
       B lis r29, 0
   138 M stw r31, 0(0)
       B stw r30, 0(0)
   140 M stw r31, 0(0)
       B stw r30, 0(0)
   143 M addi r4, r30, 0
       B addi r4, r29, 0
   151 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   158 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   165 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   172 M lbzx r3, r4, r31
       B lbzx r3, r4, r30
   180 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   185 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   190 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   195 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   200 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   205 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   209 M lfd f1, 8(r30)
       B lfd f1, 8(r29)
   216 M stbx r3, r4, r31
       B stbx r3, r4, r30
   223 M lbzx r3, r3, r31
       B lbzx r3, r3, r30
   297 M lbzx r0, r3, r31
       B lbzx r0, r3, r30
   301 M addi r3, r28, 0x2c4
       B addi r3, r31, 0x2c4
```

- local type: unsigned property index with explicit negative-result cast: exact False; insns 323/323; differences 47; objdiff 98.54489

- branch form: positive restriction flag selects clear mask first: exact True; insns 323/323; differences 0; objdiff 100.0; candidate exact without report regressions

- loop form: controller callback do-while to while: exact False; insns 323/323; differences 43; objdiff 99.287926

## Data: Wii setting dispatch tables

Relocation audit found five wrong Getter table entries and two wrong startFunc entries despite matching instruction shapes. Correct parental answer/request/version case ids to 18/20/23, and queue id from 0x1b to 0x1d. Bodies remain in source order.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/iplwww/www_wiisetting] pool: IDENTICAL
[src/iplwww/www_wiisetting] objdiff: code 3740/6176 data 3856/3856 functions 20/21 fuzzy 99.9450 linked code 0
[src/iplwww/www_wiisetting] instruction-exact functions: 20/21
[src/iplwww/www_wiisetting]   section .bss size 104 match 100.0
[src/iplwww/www_wiisetting]   section .data size 2576 match 100.0
[src/iplwww/www_wiisetting]   section .rodata size 792 match 100.0
[src/iplwww/www_wiisetting]   section .sbss size 32 match 100.0
[src/iplwww/www_wiisetting]   section .sdata size 320 match 100.0
[src/iplwww/www_wiisetting]   section .sdata2 size 32 match 100.0
[src/iplwww/www_wiisetting]   section .text size 6176 match 99.94495
[src/iplwww/www_wiisetting]   below 100: Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue 99.86043
[src/iplwww/www_wiisetting] baseline: code 2448/6176 data 1280 functions 19 fuzzy 99.7960
regressions vs baseline: 0
global matched_code_percent: 83.80901 -> 83.86043
global fuzzy_match_percent: 97.60954 -> 97.60986
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.31366
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
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

- stack layout: listing and mounting status records exchanged: exact False; insns 301/301; differences 86; objdiff 97.91362

- branch condition: signed validity state and explicit FALSE exit comparison: exact False; insns 301/301; differences 79; objdiff 97.74086

- temporary lifetime: broken-file decision directly used in branch: exact False; insns 296/301; differences None; objdiff 95.95681

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

- stack layout: move and rename status declaration order exchanged: exact False; insns 608/608; differences 222; objdiff 97.73849

- branch form: positive remainder bound chooses short transfer: exact False; insns 609/608; differences None; objdiff 97.6727

- temporary lifetime: copy byte counts typed as unsigned sector sizes: exact False; insns 608/608; differences 186; objdiff 97.804276

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

- stack declaration order: sector sizes declared after file descriptor: exact False; insns 499/512; differences None; objdiff 89.42969

- branch form: combined image bounds check preserves first rejection: exact False; insns 487/512; differences None; objdiff 87.24805

- temporary types: retain banner format as full-width unsigned value: exact False; insns 499/512; differences None; objdiff 89.44531

## src/scene/address/iplAddressEdit: stt_wait_decide_anm__Q33ipl5scene11AddressEditFv

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- inline boundary: base frame controller only in name-edit branch: exact False; insns 379/379; differences 4; objdiff 99.94723

- inline boundary: base controller for first status branch only: exact False; insns 379/379; differences 6; objdiff 99.920845

- inline boundary: base controller for retained code animation only: exact False; insns 379/379; differences 6; objdiff 99.920845

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

- condition type and base frame controller: signed completion with bitwise truth: exact False; insns 90/94; differences None; objdiff 95.42553

- condition type and base controller: unsigned completion with bitwise truth: exact False; insns 90/94; differences None; objdiff 95.42553

- temporary lifetime and base controller: animation stopped flags before accumulation: exact False; insns 94/94; differences 3; objdiff 99.84042

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

- branch target: disallowed state exits interaction body through point handling: exact False; insns 270/270; differences 3; objdiff 99.94444

- temporary scope: mailbox scene declared before interaction button: exact False; insns 270/270; differences 85; objdiff 98.35185

- temporary type: retain mailbox scene as Base then cast only at call: exact False; insns 270/270; differences 85; objdiff 98.35185

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

- near target: valid-state fallthrough with const mailbox pointer: exact False; insns 270/270; differences 3; objdiff 99.94444

- near target: valid-state fallthrough with mailbox lookup in if initializer: exact False; insns 268/270; differences None; objdiff 95.53704

- near target: valid-state fallthrough with mailbox pointer assigned after declaration: exact False; insns 270/270; differences 3; objdiff 99.94444

## src/scene/address/iplAddressEdit: start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci

```text
src 0x4b0 base 0x4a4 insns 300/297
--- replace mine 17:18 base 17:18
  M   17 beq 1108
  B   17 beq 1096
--- replace mine 23:24 base 23:24
  M   23 bne 1084
  B   23 bne 1072
--- replace mine 27:29 base 27:30
  M   27 cmpwi r3, 0
  M   28 bne 1064
  B   27 cntlzw r0, r3
  B   28 rlwinm. r0, r0, 0x1b, 5, 0x1f
  B   29 beq 1048
--- replace mine 32:33 base 33:34
  M   32 bgt 1048
  B   33 bgt 1032
--- replace mine 58:59 base 59:60
  M   58 mr r28, r3
  B   59 mr r26, r3
--- replace mine 64:65 base 65:66
  M   64 mr r26, r3
  B   65 mr r28, r3
--- replace mine 67:68 base 68:69
  M   67 mr r5, r28
  B   68 mr r5, r26
--- replace mine 69:70 base 70:71
  M   69 mr r3, r26
  B   70 mr r3, r28
--- replace mine 71:72 base 72:73
  M   71 mr r3, r26
  B   72 mr r3, r28
--- insert mine 76:76 base 77:78
  B   77 li r0, 0xd
--- insert mine 77:77 base 79:80
  B   79 stw r0, 0x38(r1)
--- delete mine 80:82 base 83:83
  M   80 li r0, 0xd
  M   81 stw r0, 0x38(r1)
--- replace mine 116:117 base 117:118
  M  116 b 712
  B  117 b 696
--- replace mine 133:134 base 134:135
  M  133 b 56
  B  134 b 72
--- replace mine 176:177 base 177:178
  M  176 b 472
  B  177 b 456
--- replace mine 192:193 base 193:194
  M  192 mr r27, r3
  B  193 mr r26, r3
--- replace mine 196:197 base 197:198
  M  196 mr r26, r3
  B  197 mr r27, r3
--- replace mine 204:206 base 205:207
  M  204 mr r4, r27
  M  205 mr r5, r26
  B  205 mr r4, r26
  B  206 mr r5, r27
--- insert mine 214:214 base 215:216
  B  215 li r0, 0xd
--- insert mine 215:215 base 217:218
  B  217 stw r0, 8(r1)
--- delete mine 218:220 base 221:221
  M  218 li r0, 0xd
  M  219 stw r0, 8(r1)
--- delete mine 242:246 base 243:243
  M  242 bl 0
  M  243 mr r3, r31
  M  244 li r4, 1
  M  245 li r5, 0x2e
```

- inline bool helper, omit target-absent name restore text and reorder filter type: exact False; insns 297/297; differences 10; objdiff 99.83165

- inline bool helper with dictionaries declared at first use: exact False; insns 297/297; differences 6; objdiff 99.89899

- inline bool helper with input-form lookup and dictionary call combined: exact False; insns 297/297; differences 9; objdiff 99.84849

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

- loop counter type: signed-long dummy-security index: exact False; insns 609/609; differences 14; objdiff 99.86043

- loop counter type: signed-long European country index: exact False; insns 609/609; differences 14; objdiff 99.86043

- loop counter types: both signed-long security and country indices: exact False; insns 609/609; differences 14; objdiff 99.86043

## src/scene/address/iplAddressEdit: start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci

```text
src 0x4b0 base 0x4a4 insns 300/297
--- replace mine 17:18 base 17:18
  M   17 beq 1108
  B   17 beq 1096
--- replace mine 23:24 base 23:24
  M   23 bne 1084
  B   23 bne 1072
--- replace mine 27:29 base 27:30
  M   27 cmpwi r3, 0
  M   28 bne 1064
  B   27 cntlzw r0, r3
  B   28 rlwinm. r0, r0, 0x1b, 5, 0x1f
  B   29 beq 1048
--- replace mine 32:33 base 33:34
  M   32 bgt 1048
  B   33 bgt 1032
--- replace mine 58:59 base 59:60
  M   58 mr r28, r3
  B   59 mr r26, r3
--- replace mine 64:65 base 65:66
  M   64 mr r26, r3
  B   65 mr r28, r3
--- replace mine 67:68 base 68:69
  M   67 mr r5, r28
  B   68 mr r5, r26
--- replace mine 69:70 base 70:71
  M   69 mr r3, r26
  B   70 mr r3, r28
--- replace mine 71:72 base 72:73
  M   71 mr r3, r26
  B   72 mr r3, r28
--- insert mine 76:76 base 77:78
  B   77 li r0, 0xd
--- insert mine 77:77 base 79:80
  B   79 stw r0, 0x38(r1)
--- delete mine 80:82 base 83:83
  M   80 li r0, 0xd
  M   81 stw r0, 0x38(r1)
--- replace mine 116:117 base 117:118
  M  116 b 712
  B  117 b 696
--- replace mine 133:134 base 134:135
  M  133 b 56
  B  134 b 72
--- replace mine 176:177 base 177:178
  M  176 b 472
  B  177 b 456
--- replace mine 192:193 base 193:194
  M  192 mr r27, r3
  B  193 mr r26, r3
--- replace mine 196:197 base 197:198
  M  196 mr r26, r3
  B  197 mr r27, r3
--- replace mine 204:206 base 205:207
  M  204 mr r4, r27
  M  205 mr r5, r26
  B  205 mr r4, r26
  B  206 mr r5, r27
--- insert mine 214:214 base 215:216
  B  215 li r0, 0xd
--- insert mine 215:215 base 217:218
  B  217 stw r0, 8(r1)
--- delete mine 218:220 base 221:221
  M  218 li r0, 0xd
  M  219 stw r0, 8(r1)
--- delete mine 242:246 base 243:243
  M  242 bl 0
  M  243 mr r3, r31
  M  244 li r4, 1
  M  245 li r5, 0x2e
```

- inline bool helper and first-use dictionaries, title only for email keyboard: exact False; insns 297/297; differences 5; objdiff 99.915825

```text
src 0x4a4 base 0x4a4 insns 297/297
diffs 5: [59, 65, 68, 70, 72]
    59 M mr r28, r3
       B mr r26, r3
    65 M mr r26, r3
       B mr r28, r3
    68 M mr r5, r28
       B mr r5, r26
    70 M mr r3, r26
       B mr r3, r28
    72 M mr r3, r26
       B mr r3, r28
```

- inline helper and email-title boundary, const dictionary pointers: exact False; insns 297/297; differences 5; objdiff 99.915825

```text
src 0x4a4 base 0x4a4 insns 297/297
diffs 5: [59, 65, 68, 70, 72]
    59 M mr r28, r3
       B mr r26, r3
    65 M mr r26, r3
       B mr r28, r3
    68 M mr r5, r28
       B mr r5, r26
    70 M mr r3, r26
       B mr r3, r28
    72 M mr r3, r26
       B mr r3, r28
```

- inline helper and email-title boundary, dictionary arguments through inline form lookup: exact True; insns 297/297; differences 0; objdiff 100.0; candidate exact without report regressions

```text
src 0x4a4 base 0x4a4 insns 297/297
diffs 0: []
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

- near-target local order: mailbox declaration after button lookup: exact False; insns 270/270; differences 3; objdiff 99.94444

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

- near-target local order: mailbox declaration before button-name dispatch: exact False; insns 270/270; differences 3; objdiff 99.94444

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

- near-target inline helper: frame controllers bound as references: exact False; insns 270/270; differences 81; objdiff 98.42593

```text
src 0x438 base 0x438 insns 270/270
diffs 81: [5, 7, 10, 11, 20, 29, 31, 33, 45, 46, 51, 52, 53, 54, 64, 67, 81, 85, 88, 89]
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
    64 M mr r3, r29
       B mr r3, r26
    67 M lwz r0, 0x88(r27)
       B lwz r0, 0x88(r29)
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

## src/scene/address/iplAddressEdit: stt_select_mii__Q33ipl5scene11AddressEditFv

```text
src 0x190 base 0x190 insns 100/100
diffs 3: [71, 73, 76]
    71 M mr r31, r29
       B mr r30, r29
    73 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    76 M mr r4, r31
       B mr r4, r30
```

- near-target local type: face selection held as int rather than long: exact True; insns 100/100; differences 0; objdiff 100.0; candidate exact without report regressions

```text
src 0x190 base 0x190 insns 100/100
diffs 0: []
```

- near-target local type: unsigned face selection with explicit signed validity check: exact False; insns 100/100; differences 3; objdiff 99.85

```text
src 0x190 base 0x190 insns 100/100
diffs 3: [71, 73, 76]
    71 M mr r31, r29
       B mr r30, r29
    73 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    76 M mr r4, r31
       B mr r4, r30
```

- near-target local lifetime: selected-face lookup directly through child expression: exact False; insns 100/100; differences 3; objdiff 99.85

```text
src 0x190 base 0x190 insns 100/100
diffs 3: [71, 73, 76]
    71 M mr r31, r29
       B mr r30, r29
    73 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    76 M mr r4, r31
       B mr r4, r30
```

## src/scene/address/iplAddressEdit: stt_add_mii_input__Q33ipl5scene11AddressEditFv

```text
src 0x194 base 0x178 insns 101/94
--- replace mine 6:7 base 6:7
  M    6 mr r31, r3
  B    6 mr r29, r3
--- replace mine 11:19 base 11:24
  M   11 beq 232
  M   12 lwz r29, 0x23c(r3)
  M   13 cmpwi r29, 0
  M   14 blt 220
  M   15 lis r30, 0
  M   16 clrlwi r4, r29, 0x10
  M   17 addi r30, r30, 0
  M   18 lwz r3, 0x70(r30)
  B   11 beq 204
  B   12 lwz r12, 0(r29)
  B   13 mr r3, r29
  B   14 lwz r12, 0x10(r12)
  B   15 mtctr r12
  B   16 bctrl 
  B   17 lwz r30, 0x23c(r3)
  B   18 cmpwi r30, 0
  B   19 blt 172
  B   20 lis r31, 0
  B   21 clrlwi r4, r30, 0x10
  B   22 addi r31, r31, 0
  B   23 lwz r3, 0x70(r31)
--- replace mine 21:23 base 26:28
  M   21 beq 192
  M   22 lwz r0, 0x4e8(r31)
  B   26 beq 144
  B   27 lwz r0, 0x4e8(r29)
--- replace mine 24:25 base 29:30
  M   24 bne 180
  B   29 bne 132
--- replace mine 26:27 base 31:32
  M   26 clrlwi r6, r29, 0x10
  B   31 clrlwi r6, r30, 0x10
--- replace mine 30:31 base 35:36
  M   30 addi r3, r31, 0x4e0
  B   35 addi r3, r29, 0x4e0
--- replace mine 34:36 base 39:44
  M   34 bne 140
  M   35 lbz r3, 0x34(r1)
  B   39 bne 92
  B   40 addi r3, r29, 0x4e0
  B   41 addi r4, r1, 0x34
  B   42 li r5, 8
  B   43 bl 0
--- replace mine 37:40 base 45:49
  M   37 lbz r0, 0x35(r1)
  M   38 mr r7, r29
  M   39 mr r9, r31
  B   45 lwz r3, 0x70(r31)
  B   46 lwz r4, 0x28(r31)
  B   47 mr r7, r30
  B   48 mr r9, r29
--- delete mine 41:42 base 50:50
  M   41 stb r3, 0x4e0(r31)
--- delete mine 44:59 base 52:52
  M   44 stb r0, 0x4e1(r31)
  M   45 lbz r3, 0x36(r1)
  M   46 lbz r0, 0x37(r1)
  M   47 stb r3, 0x4e2(r31)
  M   48 stb r0, 0x4e3(r31)
  M   49 lbz r3, 0x38(r1)
  M   50 lbz r0, 0x39(r1)
  M   51 stb r3, 0x4e4(r31)
  M   52 stb r0, 0x4e5(r31)
  M   53 lbz r3, 0x3a(r1)
  M   54 lbz r0, 0x3b(r1)
  M   55 stb r3, 0x4e6(r31)
  M   56 stb r0, 0x4e7(r31)
  M   57 lwz r3, 0x70(r30)
  M   58 lwz r4, 0x28(r30)
--- replace mine 61:63 base 54:56
  M   61 lwz r3, 0x7c(r31)
  M   62 stw r0, 0x4e8(r31)
  B   54 lwz r3, 0x7c(r29)
  B   55 stw r0, 0x4e8(r29)
--- replace mine 67:68 base 60:61
  M   67 lwz r3, 0xa8(r31)
  B   60 lwz r3, 0xa8(r29)
--- replace mine 69:71 base 62:64
  M   69 lwz r12, 0(r31)
  M   70 mr r3, r31
  B   62 lwz r12, 0(r29)
  B   63 mr r3, r29
--- replace mine 82:84 base 75:77
  M   82 cmpwi r31, 0
  M   83 mr r30, r31
  B   75 cmpwi r29, 0
  B   76 mr r30, r29
--- replace mine 85:86 base 78:79
  M   85 addi r30, r31, 0x58
  B   78 addi r30, r29, 0x58
--- replace mine 93:95 base 86:88
  M   93 stw r3, 0x64(r31)
  M   94 stw r0, 0x4e8(r31)
  B   86 stw r3, 0x64(r29)
  B   87 stw r0, 0x4e8(r29)
```

- near-target local type: face selection held as int rather than long: exact True; insns 94/94; differences 0; objdiff 100.0; candidate exact without report regressions

```text
src 0x178 base 0x178 insns 94/94
diffs 0: []
```

- near-target local type: unsigned face selection with explicit signed validity check: exact False; insns 94/94; differences 3; objdiff 99.84042

```text
src 0x178 base 0x178 insns 94/94
diffs 3: [76, 78, 81]
    76 M mr r31, r29
       B mr r30, r29
    78 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    81 M mr r4, r31
       B mr r4, r30
```

- near-target local lifetime: selected-face lookup directly through child expression: exact False; insns 94/94; differences 3; objdiff 99.84042

```text
src 0x178 base 0x178 insns 94/94
diffs 3: [76, 78, 81]
    76 M mr r31, r29
       B mr r30, r29
    78 M addi r31, r29, 0x58
       B addi r30, r29, 0x58
    81 M mr r4, r31
       B mr r4, r30
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

- loop counter type: animation completion loop uses int instead of long: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- local type: animation index retained as unsigned int before short conversion: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
   148 M mr r27, r3
       B mr r28, r3
   156 M mr r4, r27
       B mr r4, r28
```

- loop and local types: completion index int, friend check result int: exact False; insns 379/379; differences 2; objdiff 99.97362

```text
src 0x5ec base 0x5ec insns 379/379
diffs 2: [148, 156]
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

- local type: unsigned-byte completion accumulator: exact False; insns 94/94; differences 35; objdiff 91.06383

```text
src 0x178 base 0x178 insns 94/94
diffs 35: [12, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38]
    12 M bne 44
       B bne 40
    20 M subfe r0, r0, r3
       B subfe r29, r0, r3
    21 M clrlwi r30, r0, 0x18
       B b 36
    22 M b 40
       B lwz r3, 0x68(r3)
    23 M lwz r3, 0x68(r3)
       B li r4, 0x1b
    24 M li r4, 0x1b
       B addi r3, r3, 0x28c
    25 M addi r3, r3, 0x28c
       B bl 0
    26 M bl 0
       B lwz r3, 0x14(r3)
    27 M lwz r3, 0x14(r3)
       B addi r3, r3, -1
    28 M addi r3, r3, -1
       B addic r0, r3, -1
    29 M addic r0, r3, -1
       B subfe r29, r0, r3
    30 M subfe r0, r0, r3
       B lwz r3, 0x68(r31)
    31 M clrlwi r30, r0, 0x18
       B li r4, 0x16
    32 M lwz r3, 0x68(r31)
       B addi r3, r3, 0x28c
    33 M li r4, 0x16
       B bl 0
    34 M addi r3, r3, 0x28c
       B lwz r5, 0x14(r3)
    35 M bl 0
       B li r4, 0x17
    36 M lwz r5, 0x14(r3)
       B lwz r3, 0x68(r31)
    37 M li r4, 0x17
       B addi r5, r5, -1
    38 M lwz r3, 0x68(r31)
       B addic r0, r5, -1
    39 M addi r5, r5, -1
       B addi r3, r3, 0x28c
    40 M addic r0, r5, -1
       B subfe r0, r0, r5
    41 M addi r3, r3, 0x28c
       B and r5, r29, r0
    42 M subfe r0, r0, r5
       B addic r0, r5, -1
    43 M clrlwi r0, r0, 0x18
       B subfe r30, r0, r5
    44 M and r30, r30, r0
       B bl 0
    45 M bl 0
       B lwz r3, 0x14(r3)
    46 M lwz r3, 0x14(r3)
       B addi r3, r3, -1
    47 M addi r3, r3, -1
       B addic r0, r3, -1
    48 M addic r0, r3, -1
       B subfe r0, r0, r3
    49 M subfe r0, r0, r3
       B and r3, r30, r0
    50 M clrlwi r0, r0, 0x18
       B addic r0, r3, -1
    51 M and. r30, r30, r0
       B subfe. r0, r0, r3
    82 M mr r30, r3
       B mr r29, r3
    86 M stw r3, 0x14(r30)
       B stw r3, 0x14(r29)
```

- inline boundary: animation completion read through base controller: exact False; insns 94/94; differences 5; objdiff 99.73404

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

- inline boundaries: completion reads and final animation both use base controller: exact False; insns 94/94; differences 3; objdiff 99.84042

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

- local type: first animator held through const base for playing test: exact False; insns 111/111; differences 8; objdiff 99.63964

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

- temporary type: first question pane cast to TextBox before helper call: exact False; insns 111/111; differences 6; objdiff 99.72973

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

- operand form: nonempty name normalized as BOOL before branch: exact False; insns 111/111; differences 8; objdiff 99.63964

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
