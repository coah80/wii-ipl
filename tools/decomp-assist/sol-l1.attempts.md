# sol-l1: link AddressEdit

Worktree data-d10; branch agent/w1009/ae-link; baseline dc7725eb.
Baseline full 43U build passes; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Live report: functions 94/94, code 27112/27112, data 2560/2560, linked code 0.
Prior logs reviewed: lnkaddr, linkgap, sol-addr, sol-tiny, agg, scene4. AddressEdit body experiments already landed; this task changes definition placement only. lnkaddr proves delayed weak-inline definitions can restore link order. Do not repeat body or compiler-flag trials.

Acceptance: unchanged function bodies, all 94 exact-name scores 100, all ctxdiff equal-sized with zero differences, identical pool and all data sections, Matching enabled, expected DOL hash, final gate PASS.

## obj baseline symbols

### .text

```text
  0 0000 0260 STB_GLOBAL NWC24CheckPublicMailAddr_
  1 0260 00d0 STB_GLOBAL __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi
  2 0330 0098 STB_GLOBAL __dt__Q33ipl5scene11AddressEditFv
  3 03c8 004c STB_GLOBAL prepare__Q33ipl5scene11AddressEditFv
  4 0414 0cd0 STB_GLOBAL create__Q33ipl5scene11AddressEditFv
  5 10e4 0074 STB_GLOBAL calcFadein__Q33ipl5scene11AddressEditFv
  6 1158 0054 STB_GLOBAL initCalcNormal__Q33ipl5scene11AddressEditFv
  7 11ac 0204 STB_GLOBAL calcNormal__Q33ipl5scene11AddressEditFv
  8 13b0 0050 STB_GLOBAL initCalcFadeout__Q33ipl5scene11AddressEditFv
  9 1400 00c0 STB_GLOBAL calcFadeout__Q33ipl5scene11AddressEditFv
 10 14c0 0068 STB_GLOBAL calcCommonAfter__Q33ipl5scene11AddressEditFv
 11 1528 0068 STB_GLOBAL draw__Q33ipl5scene11AddressEditFv
 12 1590 0070 STB_GLOBAL stt_normal__Q33ipl5scene11AddressEditFv
 13 1600 05ec STB_GLOBAL stt_wait_decide_anm__Q33ipl5scene11AddressEditFv
 14 1bec 0014 STB_GLOBAL getDispCodeLong__Q43ipl5scene11AddressEdit6StringCFv
 15 1c00 00f4 STB_GLOBAL stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv
 16 1cf4 0178 STB_GLOBAL stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv
 17 1e6c 004c STB_GLOBAL stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv
 18 1eb8 00f0 STB_GLOBAL stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv
 19 1fa8 00c8 STB_GLOBAL stt_wait_delete__Q33ipl5scene11AddressEditFv
 20 2070 0064 STB_GLOBAL stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv
 21 20d4 009c STB_GLOBAL stt_msg_del_rlt__Q33ipl5scene11AddressEditFv
 22 2170 00a0 STB_GLOBAL stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv
 23 2210 0070 STB_GLOBAL stt_ipt_normal__Q33ipl5scene11AddressEditFv
 24 2280 020c STB_GLOBAL stt_ipt_input__Q33ipl5scene11AddressEditFv
 25 248c 00d8 STB_GLOBAL stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv
 26 2564 00bc STB_GLOBAL stt_add_code_fadein__Q33ipl5scene11AddressEditFv
 27 2620 0070 STB_GLOBAL stt_add_code_normal__Q33ipl5scene11AddressEditFv
 28 2690 0354 STB_GLOBAL stt_add_code_input__Q33ipl5scene11AddressEditFv
 29 29e4 0060 STB_GLOBAL stt_msg_code_invalid__Q33ipl5scene11AddressEditFv
 30 2a44 0060 STB_GLOBAL stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv
 31 2aa4 0060 STB_GLOBAL stt_msg_dup_email__Q33ipl5scene11AddressEditFv
 32 2b04 0060 STB_GLOBAL stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv
 33 2b64 01bc STB_GLOBAL stt_add_code_fadeout__Q33ipl5scene11AddressEditFv
 34 2d20 0084 STB_GLOBAL stt_add_name_fadein__Q33ipl5scene11AddressEditFv
 35 2da4 0070 STB_GLOBAL stt_add_name_normal__Q33ipl5scene11AddressEditFv
 36 2e14 020c STB_GLOBAL stt_add_name_input__Q33ipl5scene11AddressEditFv
 37 3020 035c STB_GLOBAL stt_add_name_fadeout__Q33ipl5scene11AddressEditFv
 38 337c 0084 STB_GLOBAL stt_add_mii_fadein__Q33ipl5scene11AddressEditFv
 39 3400 0070 STB_GLOBAL stt_add_mii_normal__Q33ipl5scene11AddressEditFv
 40 3470 0178 STB_GLOBAL stt_add_mii_input__Q33ipl5scene11AddressEditFv
 41 35e8 0060 STB_GLOBAL stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv
 42 3648 02e8 STB_GLOBAL stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv
 43 3930 004c STB_GLOBAL stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv
 44 397c 0070 STB_GLOBAL stt_add_confirm_normal__Q33ipl5scene11AddressEditFv
 45 39ec 00f8 STB_GLOBAL stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv
 46 3ae4 00d0 STB_GLOBAL stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv
 47 3bb4 0024 STB_GLOBAL stt_msg_code_add__Q33ipl5scene11AddressEditFv
 48 3bd8 0024 STB_GLOBAL stt_msg_code_edit__Q33ipl5scene11AddressEditFv
 49 3bfc 0080 STB_GLOBAL stt_msg_no_mii__Q33ipl5scene11AddressEditFv
 50 3c7c 0190 STB_GLOBAL stt_select_mii__Q33ipl5scene11AddressEditFv
 51 3e0c 0068 STB_GLOBAL stt_msg_add_rlt__Q33ipl5scene11AddressEditFv
 52 3e74 010c STB_GLOBAL stt_msg_net__Q33ipl5scene11AddressEditFv
 53 3f80 0084 STB_GLOBAL stt_wait_parental__Q33ipl5scene11AddressEditFv
 54 4004 00e0 STB_GLOBAL stt_wait_parental_dst__Q33ipl5scene11AddressEditFv
 55 40e4 010c STB_GLOBAL stt_msg_wc__Q33ipl5scene11AddressEditFv
 56 41f0 0084 STB_GLOBAL stt_wait_parental_wc__Q33ipl5scene11AddressEditFv
 57 4274 00e0 STB_GLOBAL stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv
 58 4354 0024 STB_GLOBAL stt_msg_parental__Q33ipl5scene11AddressEditFv
 59 4378 0024 STB_GLOBAL stt_msg_nwc24_error__Q33ipl5scene11AddressEditFv
 60 439c 0050 STB_GLOBAL stt_msg_no_established__Q33ipl5scene11AddressEditFv
 61 43ec 009c STB_GLOBAL set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
 62 4488 00b0 STB_GLOBAL nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 63 4538 003c STB_GLOBAL getName__Q33ipl6nigaoe6ObjectCFv
 64 4574 00ec STB_GLOBAL nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 65 4660 02d8 STB_GLOBAL start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface
 66 4938 0180 STB_GLOBAL start_left_event__Q33ipl5scene11AddressEditFPCc
 67 4ab8 01c0 STB_GLOBAL start_trig_event__Q33ipl5scene11AddressEditFPCc
 68 4c78 04a4 STB_GLOBAL start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci
 69 511c 0014 STB_GLOBAL __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl
 70 5130 0008 STB_GLOBAL getInputForm__Q29textinput7ManagerFv
 71 5138 0164 STB_GLOBAL start_ipt_point_event__Q33ipl5scene11AddressEditFPCci
 72 529c 00f8 STB_GLOBAL start_ipt_left_event__Q33ipl5scene11AddressEditFPCci
 73 5394 0074 STB_GLOBAL get_button_no__Q33ipl5scene11AddressEditFPCc
 74 5408 00ac STB_GLOBAL reset_gui__Q33ipl5scene11AddressEditFv
 75 54b4 0150 STB_GLOBAL add_friendinfo__Q33ipl5scene11AddressEditFv
 76 5604 0150 STB_GLOBAL get_friendinfo__Q33ipl5scene11AddressEditFv
 77 5754 0044 STB_GLOBAL delete_friendinfo__Q33ipl5scene11AddressEditFv
 78 5798 0098 STB_GLOBAL update_friendinfo__Q33ipl5scene11AddressEditFv
 79 5830 0084 STB_GLOBAL utf16_wiiid__Q33ipl5scene11AddressEditFPCw
 80 58b4 00a8 STB_GLOBAL wiiid_utf16__Q33ipl5scene11AddressEditFUxPw
 81 595c 00fc STB_GLOBAL setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
 82 5a58 085c STB_GLOBAL onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
 83 62b4 0064 STB_GLOBAL clear__Q43ipl5scene11AddressEdit6StringFv
 84 6318 00dc STB_GLOBAL setEMail__Q43ipl5scene11AddressEdit6StringFPCw
 85 63f4 0124 STB_GLOBAL setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw
 86 6518 008c STB_GLOBAL setName__Q43ipl5scene11AddressEdit6StringFPCw
 87 65a4 0084 STB_GLOBAL isDupCode__Q43ipl5scene11AddressEdit6StringCFv
 88 6628 0068 STB_GLOBAL isMyCode__Q43ipl5scene11AddressEdit6StringCFv
 89 6690 012c STB_GLOBAL set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err
 90 67bc 00e8 STB_GLOBAL onEvent__Q33ipl5scene16AddressEditEventFUlUlPv
 91 68a4 0134 STB_GLOBAL onEvent__Q33ipl5scene17AddressInputEventFUlUlPv
 92 69d8 0008 STB_GLOBAL @20@__dt__Q33ipl5scene11AddressEditFv
 93 69e0 0008 STB_GLOBAL @88@onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
```

### .data

```text
  0 0000 000d STB_GLOBAL @16959
  1 000d 000d STB_GLOBAL @16960
  2 001a 000d STB_GLOBAL @16961
  3 0027 000e STB_GLOBAL @16962
  4 0035 000c STB_GLOBAL @16963
  5 0044 0014 STB_GLOBAL sButtonPaneNames
  6 0058 000e STB_GLOBAL @16964
  7 0066 000c STB_GLOBAL @23886
  8 0072 0012 STB_GLOBAL @24207
  9 0084 001c STB_GLOBAL @24208
 10 00a0 000f STB_GLOBAL @24209
 11 00af 0019 STB_GLOBAL @24210
 12 00c8 000b STB_GLOBAL @24211
 13 00d3 000b STB_GLOBAL @24212
 14 00de 000b STB_GLOBAL @24213
 15 00e9 000c STB_GLOBAL @24214
 16 00f5 000e STB_GLOBAL @24215
 17 0103 001a STB_GLOBAL @24216
 18 011d 001a STB_GLOBAL @24217
 19 0137 001d STB_GLOBAL @24218
 20 0154 001e STB_GLOBAL @24219
 21 0172 000c STB_GLOBAL @24220
 22 017e 0022 STB_GLOBAL @24221
 23 01a0 0009 STB_GLOBAL @24222
 24 01a9 0023 STB_GLOBAL @24223
 25 01cc 001c STB_GLOBAL @24224
 26 01e8 000d STB_GLOBAL @24225
 27 01f5 000d STB_GLOBAL @24226
 28 0202 000d STB_GLOBAL @24227
 29 020f 000e STB_GLOBAL @24228
 30 021d 000e STB_GLOBAL @24229
 31 022b 000a STB_LOCAL  @24231
 32 0235 0012 STB_LOCAL  @24804
 33 0247 001c STB_LOCAL  @24805
 34 0263 0011 STB_LOCAL  @24806
 35 0274 0022 STB_LOCAL  @24807
 36 0296 000e STB_LOCAL  @24808
 37 02a4 001e STB_LOCAL  @24809
 38 02c2 000a STB_LOCAL  @24810
 39 02cc 001d STB_LOCAL  @24811
 40 02e9 0009 STB_LOCAL  @24812
 41 02f2 001d STB_LOCAL  @24813
 42 030f 0023 STB_LOCAL  @24815
 43 0332 001f STB_LOCAL  @24816
 44 0351 001e STB_LOCAL  @24817
 45 036f 001e STB_LOCAL  @24818
 46 038d 001c STB_LOCAL  @24819
 47 03a9 0010 STB_LOCAL  @24820
 48 03b9 0016 STB_LOCAL  @24821
 49 03cf 000b STB_LOCAL  @24822
 50 03da 0015 STB_LOCAL  @24823
 51 03ef 000e STB_LOCAL  @24824
 52 03fd 0009 STB_LOCAL  @24825
 53 0406 0019 STB_LOCAL  @24829
 54 0420 00c0 STB_LOCAL  @25188
 55 04e0 00c0 STB_LOCAL  @25187
 56 05ad 0016 STB_GLOBAL @25711
 57 05c3 000f STB_GLOBAL @25835
 58 05d4 0044 STB_LOCAL  @25838
 59 0628 0058 STB_LOCAL  @26007
 60 0680 008c STB_LOCAL  @26006
 61 070c 000c STB_GLOBAL @26030
 62 0718 0018 STB_GLOBAL __vt__Q33ipl5scene17AddressInputEvent
 63 0730 0018 STB_GLOBAL __vt__Q33ipl5scene16AddressEditEvent
 64 0748 0088 STB_GLOBAL __vt__Q33ipl5scene11AddressEdit
```

### .rodata

```text
  0 0000 000b STB_GLOBAL specials$18760
  1 000b 000c STB_GLOBAL @19145
  2 0017 000c STB_LOCAL  @19550
```

### .sdata

```text
  0 0000 0004 STB_GLOBAL sInputPaneName
  1 0004 0004 STB_GLOBAL lbl_816965E4
  2 0008 0002 STB_GLOBAL lbl_816965E8
  3 000a 0006 STB_GLOBAL lbl_816965EA
  4 0010 0008 STB_GLOBAL lbl_816965F0
```

### .sdata2

```text
  0 0000 0004 STB_GLOBAL lbl_816947F0
  1 0004 0004 STB_GLOBAL lbl_816947F4
  2 0008 0004 STB_GLOBAL lbl_816947F8
  3 000c 0004 STB_GLOBAL lbl_816947FC
  4 0010 0004 STB_GLOBAL lbl_81694800
  5 0014 0004 STB_GLOBAL lbl_81694804
```

### .bss

```text
  0 0000 0140 STB_GLOBAL sFriendInfo__Q23ipl5scene
```

## src baseline symbols

### .text

```text
  0 0000 0014 STB_GLOBAL __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl
  1 0014 00d0 STB_GLOBAL __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi
  2 00e4 0058 STB_WEAK   __dt__Q33ipl5scene14FaderSceneBaseFv
  3 013c 0098 STB_GLOBAL __dt__Q33ipl5scene11AddressEditFv
  4 01d4 0024 STB_GLOBAL stt_msg_code_add__Q33ipl5scene11AddressEditFv
  5 01f8 0024 STB_GLOBAL stt_msg_code_edit__Q33ipl5scene11AddressEditFv
  6 021c 0024 STB_GLOBAL stt_msg_parental__Q33ipl5scene11AddressEditFv
  7 0240 0024 STB_GLOBAL stt_msg_nwc24_error__Q33ipl5scene11AddressEditFv
  8 0264 00ac STB_GLOBAL reset_gui__Q33ipl5scene11AddressEditFv
  9 0310 0050 STB_GLOBAL stt_msg_no_established__Q33ipl5scene11AddressEditFv
 10 0360 0060 STB_GLOBAL stt_msg_code_invalid__Q33ipl5scene11AddressEditFv
 11 03c0 0060 STB_GLOBAL stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv
 12 0420 0060 STB_GLOBAL stt_msg_dup_email__Q33ipl5scene11AddressEditFv
 13 0480 0060 STB_GLOBAL stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv
 14 04e0 0060 STB_GLOBAL stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv
 15 0540 0068 STB_GLOBAL stt_msg_add_rlt__Q33ipl5scene11AddressEditFv
 16 05a8 0070 STB_GLOBAL stt_add_code_normal__Q33ipl5scene11AddressEditFv
 17 0618 0070 STB_GLOBAL stt_add_name_normal__Q33ipl5scene11AddressEditFv
 18 0688 0014 STB_GLOBAL getDispCodeLong__Q43ipl5scene11AddressEdit6StringCFv
 19 069c 0064 STB_GLOBAL clear__Q43ipl5scene11AddressEdit6StringFv
 20 0700 0124 STB_GLOBAL setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw
 21 0824 0084 STB_GLOBAL isDupCode__Q43ipl5scene11AddressEdit6StringCFv
 22 08a8 0068 STB_GLOBAL isMyCode__Q43ipl5scene11AddressEdit6StringCFv
 23 0910 004c STB_GLOBAL prepare__Q33ipl5scene11AddressEditFv
 24 095c 0cd0 STB_GLOBAL create__Q33ipl5scene11AddressEditFv
 25 162c 00b0 STB_WEAK   __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb
 26 16dc 0040 STB_WEAK   __dt__Q23gui9InterfaceFv
 27 171c 0008 STB_WEAK   setManager__Q23gui12EventHandlerFPQ23gui7Manager
 28 1724 05ec STB_GLOBAL stt_wait_decide_anm__Q33ipl5scene11AddressEditFv
 29 1d10 00c8 STB_GLOBAL stt_wait_delete__Q33ipl5scene11AddressEditFv
 30 1dd8 004c STB_GLOBAL stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv
 31 1e24 0084 STB_GLOBAL stt_add_name_fadein__Q33ipl5scene11AddressEditFv
 32 1ea8 0084 STB_GLOBAL stt_add_mii_fadein__Q33ipl5scene11AddressEditFv
 33 1f2c 00bc STB_GLOBAL stt_add_code_fadein__Q33ipl5scene11AddressEditFv
 34 1fe8 020c STB_GLOBAL stt_add_name_input__Q33ipl5scene11AddressEditFv
 35 21f4 0070 STB_GLOBAL stt_add_mii_normal__Q33ipl5scene11AddressEditFv
 36 2264 0178 STB_GLOBAL stt_add_mii_input__Q33ipl5scene11AddressEditFv
 37 23dc 0008 STB_WEAK   getChild__Q33ipl5scene4BaseFv
 38 23e4 02e8 STB_GLOBAL stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv
 39 26cc 00d8 STB_GLOBAL stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv
 40 27a4 00f0 STB_GLOBAL stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv
 41 2894 0080 STB_GLOBAL stt_msg_no_mii__Q33ipl5scene11AddressEditFv
 42 2914 00f8 STB_GLOBAL stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv
 43 2a0c 00d0 STB_GLOBAL stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv
 44 2adc 0070 STB_GLOBAL stt_add_confirm_normal__Q33ipl5scene11AddressEditFv
 45 2b4c 0084 STB_GLOBAL stt_wait_parental__Q33ipl5scene11AddressEditFv
 46 2bd0 0084 STB_GLOBAL stt_wait_parental_wc__Q33ipl5scene11AddressEditFv
 47 2c54 00e0 STB_GLOBAL stt_wait_parental_dst__Q33ipl5scene11AddressEditFv
 48 2d34 00e0 STB_GLOBAL stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv
 49 2e14 010c STB_GLOBAL stt_msg_net__Q33ipl5scene11AddressEditFv
 50 2f20 010c STB_GLOBAL stt_msg_wc__Q33ipl5scene11AddressEditFv
 51 302c 0190 STB_GLOBAL stt_select_mii__Q33ipl5scene11AddressEditFv
 52 31bc 009c STB_GLOBAL set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
 53 3258 0008 STB_WEAK   GetRuntimeTypeInfo__Q34nw4r3lyt4PaneCFv
 54 3260 00fc STB_GLOBAL setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
 55 335c 00e8 STB_GLOBAL onEvent__Q33ipl5scene16AddressEditEventFUlUlPv
 56 3444 0008 STB_WEAK   getPane__Q23gui13PaneComponentFv
 57 344c 0134 STB_GLOBAL onEvent__Q33ipl5scene17AddressInputEventFUlUlPv
 58 3580 00b0 STB_GLOBAL nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 59 3630 003c STB_WEAK   getName__Q33ipl6nigaoe6ObjectCFv
 60 366c 00ec STB_GLOBAL nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 61 3758 0074 STB_GLOBAL calcFadein__Q33ipl5scene11AddressEditFv
 62 37cc 0054 STB_GLOBAL initCalcNormal__Q33ipl5scene11AddressEditFv
 63 3820 0204 STB_GLOBAL calcNormal__Q33ipl5scene11AddressEditFv
 64 3a24 035c STB_GLOBAL stt_add_name_fadeout__Q33ipl5scene11AddressEditFv
 65 3d80 0050 STB_GLOBAL initCalcFadeout__Q33ipl5scene11AddressEditFv
 66 3dd0 0068 STB_GLOBAL calcCommonAfter__Q33ipl5scene11AddressEditFv
 67 3e38 0070 STB_GLOBAL stt_normal__Q33ipl5scene11AddressEditFv
 68 3ea8 004c STB_GLOBAL stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv
 69 3ef4 0044 STB_GLOBAL delete_friendinfo__Q33ipl5scene11AddressEditFv
 70 3f38 0084 STB_GLOBAL utf16_wiiid__Q33ipl5scene11AddressEditFPCw
 71 3fbc 00a8 STB_GLOBAL wiiid_utf16__Q33ipl5scene11AddressEditFUxPw
 72 4064 008c STB_GLOBAL setName__Q43ipl5scene11AddressEdit6StringFPCw
 73 40f0 00c0 STB_GLOBAL calcFadeout__Q33ipl5scene11AddressEditFv
 74 41b0 0068 STB_GLOBAL draw__Q33ipl5scene11AddressEditFv
 75 4218 00f4 STB_GLOBAL stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv
 76 430c 0178 STB_GLOBAL stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv
 77 4484 0064 STB_GLOBAL stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv
 78 44e8 009c STB_GLOBAL stt_msg_del_rlt__Q33ipl5scene11AddressEditFv
 79 4584 00a0 STB_GLOBAL stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv
 80 4624 0070 STB_GLOBAL stt_ipt_normal__Q33ipl5scene11AddressEditFv
 81 4694 020c STB_GLOBAL stt_ipt_input__Q33ipl5scene11AddressEditFv
 82 48a0 0354 STB_GLOBAL stt_add_code_input__Q33ipl5scene11AddressEditFv
 83 4bf4 01bc STB_GLOBAL stt_add_code_fadeout__Q33ipl5scene11AddressEditFv
 84 4db0 0260 STB_GLOBAL NWC24CheckPublicMailAddr_
 85 5010 02d8 STB_GLOBAL start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface
 86 52e8 0180 STB_GLOBAL start_left_event__Q33ipl5scene11AddressEditFPCc
 87 5468 01c0 STB_GLOBAL start_trig_event__Q33ipl5scene11AddressEditFPCc
 88 5628 04a4 STB_GLOBAL start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci
 89 5acc 0008 STB_WEAK   getInputForm__Q29textinput7ManagerFv
 90 5ad4 0164 STB_GLOBAL start_ipt_point_event__Q33ipl5scene11AddressEditFPCci
 91 5c38 085c STB_GLOBAL onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
 92 6494 00f8 STB_GLOBAL start_ipt_left_event__Q33ipl5scene11AddressEditFPCci
 93 658c 012c STB_GLOBAL set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err
 94 66b8 0074 STB_GLOBAL get_button_no__Q33ipl5scene11AddressEditFPCc
 95 672c 0150 STB_GLOBAL add_friendinfo__Q33ipl5scene11AddressEditFv
 96 687c 0150 STB_GLOBAL get_friendinfo__Q33ipl5scene11AddressEditFv
 97 69cc 0098 STB_GLOBAL update_friendinfo__Q33ipl5scene11AddressEditFv
 98 6a64 00dc STB_GLOBAL setEMail__Q43ipl5scene11AddressEdit6StringFPCw
 99 6b40 0008 STB_WEAK   getLatestEventCtrlNo__Q23gui12EventHandlerFv
100 6b48 0008 STB_WEAK   setLatestEventCtrlNo__Q23gui12EventHandlerFi
101 6b50 0008 STB_WEAK   getPrev__Q33ipl5scene4BaseFv
102 6b58 0008 STB_WEAK   getNext__Q33ipl5scene4BaseFv
103 6b60 0008 STB_WEAK   getParent__Q33ipl5scene4BaseFv
104 6b68 0004 STB_WEAK   destroy__Q33ipl5scene4BaseFv
105 6b6c 0008 STB_WEAK   isResetProcessDone__Q33ipl5scene4BaseFv
106 6b74 0004 STB_WEAK   startResetting__Q33ipl5scene4BaseFv
107 6b78 0008 STB_WEAK   isResetAcceptable__Q33ipl5scene4BaseCFv
108 6b80 0008 STB_WEAK   isReady__Q33ipl5scene4BaseCFv
109 6b88 0004 STB_WEAK   calcCommon__Q33ipl5scene14FaderSceneBaseFv
110 6b8c 0004 STB_WEAK   draw__Q23gui9InterfaceFRA3_A4_f
111 6b90 0004 STB_WEAK   create__Q23gui9InterfaceFv
112 6b94 0054 STB_WEAK   changeEventHandler__Q23gui7ManagerFPQ23gui12EventHandler
113 6be8 002c STB_WEAK   setEventHandler__Q23gui7ManagerFPQ23gui12EventHandler
114 6c14 0080 STB_WEAK   onEvent__Q23gui7ManagerFUlUliPv
115 6c94 0004 STB_WEAK   onEvent__Q23gui12EventHandlerFUlUlPv
116 6c98 0008 STB_WEAK   update__Q23gui7ManagerFiPC10KPADStatusffPv
117 6ca0 0008 STB_WEAK   setDrawInfo__Q23gui11PaneManagerFPCQ34nw4r3lyt8DrawInfo
118 6ca8 0008 STB_WEAK   getDrawInfo__Q23gui11PaneManagerFv
119 6cb0 0058 STB_WEAK   __dt__Q33ipl3gui11PaneManagerFv
120 6d08 0004 STB_WEAK   draw__Q23gui9InterfaceFv
121 6d0c 0004 STB_WEAK   calc__Q23gui9InterfaceFv
122 6d10 0004 STB_WEAK   init__Q23gui9InterfaceFv
123 6d14 0008 STB_WEAK   @20@__dt__Q33ipl5scene11AddressEditFv
124 6d1c 0008 STB_WEAK   @88@onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
```

### .data

```text
  0 0000 0000 STB_LOCAL  ...data.0
  1 0000 000d STB_LOCAL  @17047
  2 000d 000d STB_LOCAL  @17048
  3 001a 000d STB_LOCAL  @17049
  4 0027 000e STB_LOCAL  @17050
  5 0035 000c STB_LOCAL  @17051
  6 0044 0014 STB_LOCAL  sButtonPaneNames
  7 0058 000e STB_LOCAL  @17052
  8 0066 000c STB_LOCAL  @24446
  9 0072 0012 STB_LOCAL  @24755
 10 0084 001c STB_LOCAL  @24756
 11 00a0 000f STB_LOCAL  @24757
 12 00af 0019 STB_LOCAL  @24758
 13 00c8 000b STB_LOCAL  @24759
 14 00d3 000b STB_LOCAL  @24760
 15 00de 000b STB_LOCAL  @24761
 16 00e9 000c STB_LOCAL  @24762
 17 00f5 000e STB_LOCAL  @24763
 18 0103 001a STB_LOCAL  @24764
 19 011d 001a STB_LOCAL  @24765
 20 0137 001d STB_LOCAL  @24766
 21 0154 001e STB_LOCAL  @24767
 22 0172 000c STB_LOCAL  @24768
 23 017e 0022 STB_LOCAL  @24769
 24 01a0 0009 STB_LOCAL  @24770
 25 01a9 0023 STB_LOCAL  @24771
 26 01cc 001c STB_LOCAL  @24772
 27 01e8 000d STB_LOCAL  @24773
 28 01f5 000d STB_LOCAL  @24774
 29 0202 000d STB_LOCAL  @24775
 30 020f 000e STB_LOCAL  @24776
 31 021d 000e STB_LOCAL  @24777
 32 022b 000a STB_LOCAL  @24779
 33 0235 0012 STB_LOCAL  @24780
 34 0247 001c STB_LOCAL  @24781
 35 0263 0011 STB_LOCAL  @24782
 36 0274 0022 STB_LOCAL  @24783
 37 0296 000e STB_LOCAL  @24784
 38 02a4 001e STB_LOCAL  @24785
 39 02c2 000a STB_LOCAL  @24786
 40 02cc 001d STB_LOCAL  @24787
 41 02e9 0009 STB_LOCAL  @24788
 42 02f2 001d STB_LOCAL  @24789
 43 030f 0023 STB_LOCAL  @24791
 44 0332 001f STB_LOCAL  @24792
 45 0351 001e STB_LOCAL  @24793
 46 036f 001e STB_LOCAL  @24794
 47 038d 001c STB_LOCAL  @24795
 48 03a9 0010 STB_LOCAL  @24796
 49 03b9 0016 STB_LOCAL  @24797
 50 03cf 000b STB_LOCAL  @24798
 51 03da 0015 STB_LOCAL  @24799
 52 03ef 000e STB_LOCAL  @24800
 53 03fd 0009 STB_LOCAL  @24801
 54 0406 0019 STB_LOCAL  @24804
 55 0420 00c0 STB_LOCAL  @25770
 56 04e0 00c0 STB_LOCAL  @25769
 57 05a0 000d STB_LOCAL  @25906
 58 05ad 0016 STB_LOCAL  @26437
 59 05c3 000f STB_LOCAL  @26493
 60 05d4 0044 STB_LOCAL  @26572
 61 0618 000f STB_LOCAL  @26733
 62 0628 0058 STB_LOCAL  @26737
 63 0680 008c STB_LOCAL  @26736
 64 070c 000c STB_LOCAL  @26760
 65 0718 0018 STB_GLOBAL __vt__Q33ipl5scene17AddressInputEvent
 66 0730 0018 STB_GLOBAL __vt__Q33ipl5scene16AddressEditEvent
 67 0748 0088 STB_GLOBAL __vt__Q33ipl5scene11AddressEdit
 68 07d0 005c STB_WEAK   __vt__Q33ipl3gui11PaneManager
 69 082c 0018 STB_WEAK   __vt__Q23gui12EventHandler
 70 0844 0020 STB_WEAK   __vt__Q23gui9Interface
```

### .rodata

```text
  0 0000 000b STB_LOCAL  specials$18951
  1 000b 000c STB_LOCAL  @19329
  2 0017 000c STB_LOCAL  @19521
```

### .sdata

```text
  0 0000 0004 STB_LOCAL  sInputPaneName
  1 0004 0004 STB_LOCAL  @24754
  2 0008 0002 STB_LOCAL  @24778
  3 000a 0006 STB_LOCAL  @24790
  4 0010 0008 STB_LOCAL  @26820
```

### .sdata2

```text
  0 0000 0004 STB_LOCAL  @24802
  1 0004 0004 STB_LOCAL  @24803
  2 0008 0004 STB_LOCAL  @24805
  3 000c 0004 STB_LOCAL  @26438
  4 0010 0004 STB_LOCAL  @26439
  5 0014 0004 STB_LOCAL  @26440
```

### .bss

```text
  0 0000 0140 STB_GLOBAL sFriendInfo__Q23ipl5scene
```

## Trial 1: target definition order

Moved the 90 explicit target definitions into target order. Kept the four existing fully inlined helper bodies, the three scoped pragmas, class definitions and global declarations unchanged. Parser verifies the complete multiset of all 95 original function definitions is unchanged. First compile found a namespace global in the old inter-function declarations; retained those declarations before the ordered functions and rebuilt.

Fresh object: 94/94 exact-name functions, code 27112/27112, data 2560/2560, every owned data section 100%. Pool IDENTICAL at 57/57 strings. Read .symtab after the move, including weak functions: retained getInputForm appears immediately before KeyboardSetting constructor, opposite the target. .data positions, string bytes, switch tables and vtable positions remain unchanged; target excludes three deduplicated weak vtables and two embedded string labels. .rodata/.sdata/.sdata2/.bss positions and sizes remain unchanged. Generated label numbers and ELF binding are metadata.

Enabled Matching and ran full build: checksum fails with SHA1 ae060041ddf60a926d5056b589db11fbac35ac21. doldiff finds only 25 differing bytes: swapped constructor/getInputForm bodies, two caller relocations, and two getInputForm vtable slots. Raw evidence /tmp/sol-l1-trial1-doldiff.log.

## Trial 2: delay the existing getter definition

Extend the existing tiManager.h declaration guard to IPL_ADDRESS_EDIT_CPP. Move its unchanged body to an out-of-class inline definition immediately after KeyboardSetting, before start_ipt_point_event. This keeps weak binding, preserves the existing body, and affects only this translation unit. No caller body or instruction edits.

Trial 2 result: target function order now identical, all 94 functions still exact, data 2560/2560, pool IDENTICAL 57/57. All 1027 other source objects retain baseline SHA256. Full link leaves exactly 3 differing bytes, all in get_button_no. The target relocations at function offsets 0x16 HA / 0x1e LO both point to sButtonPaneNames; current source points to smButtonName__Q33ipl5scene6Button. Retail instructions materialize 0x81647F24, current DOL materializes 0x8164BF5C. This predates this task and is invisible to instruction-exact scoring. Reordering cannot correct that relocation identity. Required one-line correction is in /tmp/sol-l1-table-reference.patch. Await task-scope clarification because user explicitly requires no changes inside function bodies.

## Trial 2 symbol placement

### .text

```text
  0 0000 0260 STB_GLOBAL NWC24CheckPublicMailAddr_
  1 0260 00d0 STB_GLOBAL __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi
  2 0330 0058 STB_WEAK   __dt__Q33ipl5scene14FaderSceneBaseFv
  3 0388 0098 STB_GLOBAL __dt__Q33ipl5scene11AddressEditFv
  4 0420 004c STB_GLOBAL prepare__Q33ipl5scene11AddressEditFv
  5 046c 0cd0 STB_GLOBAL create__Q33ipl5scene11AddressEditFv
  6 113c 00b0 STB_WEAK   __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb
  7 11ec 0040 STB_WEAK   __dt__Q23gui9InterfaceFv
  8 122c 0008 STB_WEAK   setManager__Q23gui12EventHandlerFPQ23gui7Manager
  9 1234 0074 STB_GLOBAL calcFadein__Q33ipl5scene11AddressEditFv
 10 12a8 0054 STB_GLOBAL initCalcNormal__Q33ipl5scene11AddressEditFv
 11 12fc 0204 STB_GLOBAL calcNormal__Q33ipl5scene11AddressEditFv
 12 1500 0050 STB_GLOBAL initCalcFadeout__Q33ipl5scene11AddressEditFv
 13 1550 00c0 STB_GLOBAL calcFadeout__Q33ipl5scene11AddressEditFv
 14 1610 0068 STB_GLOBAL calcCommonAfter__Q33ipl5scene11AddressEditFv
 15 1678 0068 STB_GLOBAL draw__Q33ipl5scene11AddressEditFv
 16 16e0 0070 STB_GLOBAL stt_normal__Q33ipl5scene11AddressEditFv
 17 1750 05ec STB_GLOBAL stt_wait_decide_anm__Q33ipl5scene11AddressEditFv
 18 1d3c 0014 STB_GLOBAL getDispCodeLong__Q43ipl5scene11AddressEdit6StringCFv
 19 1d50 00f4 STB_GLOBAL stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv
 20 1e44 0178 STB_GLOBAL stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv
 21 1fbc 004c STB_GLOBAL stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv
 22 2008 00f0 STB_GLOBAL stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv
 23 20f8 00c8 STB_GLOBAL stt_wait_delete__Q33ipl5scene11AddressEditFv
 24 21c0 0064 STB_GLOBAL stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv
 25 2224 009c STB_GLOBAL stt_msg_del_rlt__Q33ipl5scene11AddressEditFv
 26 22c0 00a0 STB_GLOBAL stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv
 27 2360 0070 STB_GLOBAL stt_ipt_normal__Q33ipl5scene11AddressEditFv
 28 23d0 020c STB_GLOBAL stt_ipt_input__Q33ipl5scene11AddressEditFv
 29 25dc 00d8 STB_GLOBAL stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv
 30 26b4 00bc STB_GLOBAL stt_add_code_fadein__Q33ipl5scene11AddressEditFv
 31 2770 0070 STB_GLOBAL stt_add_code_normal__Q33ipl5scene11AddressEditFv
 32 27e0 0354 STB_GLOBAL stt_add_code_input__Q33ipl5scene11AddressEditFv
 33 2b34 0060 STB_GLOBAL stt_msg_code_invalid__Q33ipl5scene11AddressEditFv
 34 2b94 0060 STB_GLOBAL stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv
 35 2bf4 0060 STB_GLOBAL stt_msg_dup_email__Q33ipl5scene11AddressEditFv
 36 2c54 0060 STB_GLOBAL stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv
 37 2cb4 01bc STB_GLOBAL stt_add_code_fadeout__Q33ipl5scene11AddressEditFv
 38 2e70 0084 STB_GLOBAL stt_add_name_fadein__Q33ipl5scene11AddressEditFv
 39 2ef4 0070 STB_GLOBAL stt_add_name_normal__Q33ipl5scene11AddressEditFv
 40 2f64 020c STB_GLOBAL stt_add_name_input__Q33ipl5scene11AddressEditFv
 41 3170 035c STB_GLOBAL stt_add_name_fadeout__Q33ipl5scene11AddressEditFv
 42 34cc 0084 STB_GLOBAL stt_add_mii_fadein__Q33ipl5scene11AddressEditFv
 43 3550 0070 STB_GLOBAL stt_add_mii_normal__Q33ipl5scene11AddressEditFv
 44 35c0 0178 STB_GLOBAL stt_add_mii_input__Q33ipl5scene11AddressEditFv
 45 3738 0008 STB_WEAK   getChild__Q33ipl5scene4BaseFv
 46 3740 0060 STB_GLOBAL stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv
 47 37a0 02e8 STB_GLOBAL stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv
 48 3a88 004c STB_GLOBAL stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv
 49 3ad4 0070 STB_GLOBAL stt_add_confirm_normal__Q33ipl5scene11AddressEditFv
 50 3b44 00f8 STB_GLOBAL stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv
 51 3c3c 00d0 STB_GLOBAL stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv
 52 3d0c 0024 STB_GLOBAL stt_msg_code_add__Q33ipl5scene11AddressEditFv
 53 3d30 0024 STB_GLOBAL stt_msg_code_edit__Q33ipl5scene11AddressEditFv
 54 3d54 0080 STB_GLOBAL stt_msg_no_mii__Q33ipl5scene11AddressEditFv
 55 3dd4 0190 STB_GLOBAL stt_select_mii__Q33ipl5scene11AddressEditFv
 56 3f64 0068 STB_GLOBAL stt_msg_add_rlt__Q33ipl5scene11AddressEditFv
 57 3fcc 010c STB_GLOBAL stt_msg_net__Q33ipl5scene11AddressEditFv
 58 40d8 0084 STB_GLOBAL stt_wait_parental__Q33ipl5scene11AddressEditFv
 59 415c 00e0 STB_GLOBAL stt_wait_parental_dst__Q33ipl5scene11AddressEditFv
 60 423c 010c STB_GLOBAL stt_msg_wc__Q33ipl5scene11AddressEditFv
 61 4348 0084 STB_GLOBAL stt_wait_parental_wc__Q33ipl5scene11AddressEditFv
 62 43cc 00e0 STB_GLOBAL stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv
 63 44ac 0024 STB_GLOBAL stt_msg_parental__Q33ipl5scene11AddressEditFv
 64 44d0 0024 STB_GLOBAL stt_msg_nwc24_error__Q33ipl5scene11AddressEditFv
 65 44f4 0050 STB_GLOBAL stt_msg_no_established__Q33ipl5scene11AddressEditFv
 66 4544 009c STB_GLOBAL set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
 67 45e0 0008 STB_WEAK   GetRuntimeTypeInfo__Q34nw4r3lyt4PaneCFv
 68 45e8 00b0 STB_GLOBAL nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 69 4698 003c STB_WEAK   getName__Q33ipl6nigaoe6ObjectCFv
 70 46d4 00ec STB_GLOBAL nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv
 71 47c0 02d8 STB_GLOBAL start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface
 72 4a98 0180 STB_GLOBAL start_left_event__Q33ipl5scene11AddressEditFPCc
 73 4c18 01c0 STB_GLOBAL start_trig_event__Q33ipl5scene11AddressEditFPCc
 74 4dd8 04a4 STB_GLOBAL start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci
 75 527c 0014 STB_GLOBAL __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl
 76 5290 0008 STB_WEAK   getInputForm__Q29textinput7ManagerFv
 77 5298 0164 STB_GLOBAL start_ipt_point_event__Q33ipl5scene11AddressEditFPCci
 78 53fc 00f8 STB_GLOBAL start_ipt_left_event__Q33ipl5scene11AddressEditFPCci
 79 54f4 0074 STB_GLOBAL get_button_no__Q33ipl5scene11AddressEditFPCc
 80 5568 00ac STB_GLOBAL reset_gui__Q33ipl5scene11AddressEditFv
 81 5614 0150 STB_GLOBAL add_friendinfo__Q33ipl5scene11AddressEditFv
 82 5764 0150 STB_GLOBAL get_friendinfo__Q33ipl5scene11AddressEditFv
 83 58b4 0044 STB_GLOBAL delete_friendinfo__Q33ipl5scene11AddressEditFv
 84 58f8 0098 STB_GLOBAL update_friendinfo__Q33ipl5scene11AddressEditFv
 85 5990 0084 STB_GLOBAL utf16_wiiid__Q33ipl5scene11AddressEditFPCw
 86 5a14 00a8 STB_GLOBAL wiiid_utf16__Q33ipl5scene11AddressEditFUxPw
 87 5abc 00fc STB_GLOBAL setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
 88 5bb8 085c STB_GLOBAL onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
 89 6414 0008 STB_WEAK   getPane__Q23gui13PaneComponentFv
 90 641c 0064 STB_GLOBAL clear__Q43ipl5scene11AddressEdit6StringFv
 91 6480 00dc STB_GLOBAL setEMail__Q43ipl5scene11AddressEdit6StringFPCw
 92 655c 0124 STB_GLOBAL setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw
 93 6680 008c STB_GLOBAL setName__Q43ipl5scene11AddressEdit6StringFPCw
 94 670c 0084 STB_GLOBAL isDupCode__Q43ipl5scene11AddressEdit6StringCFv
 95 6790 0068 STB_GLOBAL isMyCode__Q43ipl5scene11AddressEdit6StringCFv
 96 67f8 012c STB_GLOBAL set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err
 97 6924 00e8 STB_GLOBAL onEvent__Q33ipl5scene16AddressEditEventFUlUlPv
 98 6a0c 0134 STB_GLOBAL onEvent__Q33ipl5scene17AddressInputEventFUlUlPv
 99 6b40 0008 STB_WEAK   getLatestEventCtrlNo__Q23gui12EventHandlerFv
100 6b48 0008 STB_WEAK   setLatestEventCtrlNo__Q23gui12EventHandlerFi
101 6b50 0008 STB_WEAK   getPrev__Q33ipl5scene4BaseFv
102 6b58 0008 STB_WEAK   getNext__Q33ipl5scene4BaseFv
103 6b60 0008 STB_WEAK   getParent__Q33ipl5scene4BaseFv
104 6b68 0004 STB_WEAK   destroy__Q33ipl5scene4BaseFv
105 6b6c 0008 STB_WEAK   isResetProcessDone__Q33ipl5scene4BaseFv
106 6b74 0004 STB_WEAK   startResetting__Q33ipl5scene4BaseFv
107 6b78 0008 STB_WEAK   isResetAcceptable__Q33ipl5scene4BaseCFv
108 6b80 0008 STB_WEAK   isReady__Q33ipl5scene4BaseCFv
109 6b88 0004 STB_WEAK   calcCommon__Q33ipl5scene14FaderSceneBaseFv
110 6b8c 0004 STB_WEAK   draw__Q23gui9InterfaceFRA3_A4_f
111 6b90 0004 STB_WEAK   create__Q23gui9InterfaceFv
112 6b94 0054 STB_WEAK   changeEventHandler__Q23gui7ManagerFPQ23gui12EventHandler
113 6be8 002c STB_WEAK   setEventHandler__Q23gui7ManagerFPQ23gui12EventHandler
114 6c14 0080 STB_WEAK   onEvent__Q23gui7ManagerFUlUliPv
115 6c94 0004 STB_WEAK   onEvent__Q23gui12EventHandlerFUlUlPv
116 6c98 0008 STB_WEAK   update__Q23gui7ManagerFiPC10KPADStatusffPv
117 6ca0 0008 STB_WEAK   setDrawInfo__Q23gui11PaneManagerFPCQ34nw4r3lyt8DrawInfo
118 6ca8 0008 STB_WEAK   getDrawInfo__Q23gui11PaneManagerFv
119 6cb0 0058 STB_WEAK   __dt__Q33ipl3gui11PaneManagerFv
120 6d08 0004 STB_WEAK   draw__Q23gui9InterfaceFv
121 6d0c 0004 STB_WEAK   calc__Q23gui9InterfaceFv
122 6d10 0004 STB_WEAK   init__Q23gui9InterfaceFv
123 6d14 0008 STB_WEAK   @20@__dt__Q33ipl5scene11AddressEditFv
124 6d1c 0008 STB_WEAK   @88@onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface
```

### .data

```text
  0 0000 0000 STB_LOCAL  ...data.0
  1 0000 000d STB_LOCAL  @17043
  2 000d 000d STB_LOCAL  @17044
  3 001a 000d STB_LOCAL  @17045
  4 0027 000e STB_LOCAL  @17046
  5 0035 000c STB_LOCAL  @17047
  6 0044 0014 STB_LOCAL  sButtonPaneNames
  7 0058 000e STB_LOCAL  @17048
  8 0066 000c STB_LOCAL  @23864
  9 0072 0012 STB_LOCAL  @24173
 10 0084 001c STB_LOCAL  @24174
 11 00a0 000f STB_LOCAL  @24175
 12 00af 0019 STB_LOCAL  @24176
 13 00c8 000b STB_LOCAL  @24177
 14 00d3 000b STB_LOCAL  @24178
 15 00de 000b STB_LOCAL  @24179
 16 00e9 000c STB_LOCAL  @24180
 17 00f5 000e STB_LOCAL  @24181
 18 0103 001a STB_LOCAL  @24182
 19 011d 001a STB_LOCAL  @24183
 20 0137 001d STB_LOCAL  @24184
 21 0154 001e STB_LOCAL  @24185
 22 0172 000c STB_LOCAL  @24186
 23 017e 0022 STB_LOCAL  @24187
 24 01a0 0009 STB_LOCAL  @24188
 25 01a9 0023 STB_LOCAL  @24189
 26 01cc 001c STB_LOCAL  @24190
 27 01e8 000d STB_LOCAL  @24191
 28 01f5 000d STB_LOCAL  @24192
 29 0202 000d STB_LOCAL  @24193
 30 020f 000e STB_LOCAL  @24194
 31 021d 000e STB_LOCAL  @24195
 32 022b 000a STB_LOCAL  @24197
 33 0235 0012 STB_LOCAL  @24198
 34 0247 001c STB_LOCAL  @24199
 35 0263 0011 STB_LOCAL  @24200
 36 0274 0022 STB_LOCAL  @24201
 37 0296 000e STB_LOCAL  @24202
 38 02a4 001e STB_LOCAL  @24203
 39 02c2 000a STB_LOCAL  @24204
 40 02cc 001d STB_LOCAL  @24205
 41 02e9 0009 STB_LOCAL  @24206
 42 02f2 001d STB_LOCAL  @24207
 43 030f 0023 STB_LOCAL  @24209
 44 0332 001f STB_LOCAL  @24210
 45 0351 001e STB_LOCAL  @24211
 46 036f 001e STB_LOCAL  @24212
 47 038d 001c STB_LOCAL  @24213
 48 03a9 0010 STB_LOCAL  @24214
 49 03b9 0016 STB_LOCAL  @24215
 50 03cf 000b STB_LOCAL  @24216
 51 03da 0015 STB_LOCAL  @24217
 52 03ef 000e STB_LOCAL  @24218
 53 03fd 0009 STB_LOCAL  @24219
 54 0406 0019 STB_LOCAL  @24222
 55 0420 00c0 STB_LOCAL  @24337
 56 04e0 00c0 STB_LOCAL  @24336
 57 05a0 000d STB_LOCAL  @25300
 58 05ad 0016 STB_LOCAL  @25856
 59 05c3 000f STB_LOCAL  @25912
 60 05d4 0044 STB_LOCAL  @25991
 61 0618 000f STB_LOCAL  @26282
 62 0628 0058 STB_LOCAL  @26286
 63 0680 008c STB_LOCAL  @26285
 64 070c 000c STB_LOCAL  @26342
 65 0718 0018 STB_GLOBAL __vt__Q33ipl5scene17AddressInputEvent
 66 0730 0018 STB_GLOBAL __vt__Q33ipl5scene16AddressEditEvent
 67 0748 0088 STB_GLOBAL __vt__Q33ipl5scene11AddressEdit
 68 07d0 005c STB_WEAK   __vt__Q33ipl3gui11PaneManager
 69 082c 0018 STB_WEAK   __vt__Q23gui12EventHandler
 70 0844 0020 STB_WEAK   __vt__Q23gui9Interface
```

### .rodata

```text
  0 0000 000b STB_LOCAL  specials$17132
  1 000b 000c STB_LOCAL  @19121
  2 0017 000c STB_LOCAL  @19153
```

### .sdata

```text
  0 0000 0004 STB_LOCAL  sInputPaneName
  1 0004 0004 STB_LOCAL  @24172
  2 0008 0002 STB_LOCAL  @24196
  3 000a 0006 STB_LOCAL  @24208
  4 0010 0008 STB_LOCAL  @26294
```

### .sdata2

```text
  0 0000 0004 STB_LOCAL  @24220
  1 0004 0004 STB_LOCAL  @24221
  2 0008 0004 STB_LOCAL  @24223
  3 000c 0004 STB_LOCAL  @25857
  4 0010 0004 STB_LOCAL  @25858
  5 0014 0004 STB_LOCAL  @25859
```

### .bss

```text
  0 0000 0140 STB_GLOBAL sFriendInfo__Q23ipl5scene
```

## Pending-scope safe state

Retain the verified definition-order change and unchanged weak-inline relocation. Restore only the Matching flag while the single required body correction awaits authorization; current DOL must remain valid. The link task remains incomplete until that correction is allowed and the Matching/full-DOL gate passes. Run the requested quick gate on this safe state before local preservation.

## Safe-state verification

All 94 ctxdiff audits have identical sizes and instruction counts with diffs 0; evidence /tmp/sol-l1-ctxdiff.txt. All 95 pre-existing function definition blocks remain byte-identical. The sole added source definition is the existing getter body moved from the header. All 1027 unowned source objects are byte-identical to baseline, and all 1027 unowned live report unit entries are unchanged. Final symbol order includes every target function, including both retained weak functions and the two thunks, in original order.

The required quick gate passes on the safe NonMatching state. This preserves code/data exactness and the original DOL while the link goal awaits the requested scope exception. Do not accept this as a completed link: complete_code remains zero. To finish, authorize/apply /tmp/sol-l1-table-reference.patch, flip only the AddressEdit Object entry to Matching, rerun the full build, pool, exact-name report, ctxdiff and final gate. Expected complete_code 27112 and complete_data 2560. No push, PR, merge, rebase, or other-worktree edit performed.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 27112/27112 data 2560/2560 functions 94/94 fuzzy 100.0000 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 94/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 100.0
[src/scene/address/iplAddressEdit] baseline: code 27112/27112 data 2560 functions 94 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 98.05994 -> 98.05994
global fuzzy_match_percent: 99.91572 -> 99.91572
global complete_code_percent: 89.90470 -> 89.90470
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Round b: approved table correction and link

User approved the get_button_no table correction and explicitly authorized rebase.
Fetched origin under /tmp/wii-git.lock and rebased 6a0c7424 onto ca6529e6.
Replayed definition-order commit is 52efc64f. Resolved the set_textbox conflict
by retaining its earlier definition position. Removed both file-static balloon
margin helpers and retained main's TextBalloon::getDefaultMargin16x9/4x3 calls.
The TextBalloon header is unchanged from origin/main.

Changed get_button_no to sButtonPaneNames. Retained the external Button table
declaration needed by setDefaultTitleText. This corrects the HA/LO relocation
identity recorded in trial 2. Enabled Matching only for iplAddressEdit.
No earlier body, compiler-flag or declaration-order experiments repeated.
Required verification: full 43U build, expected DOL SHA1, identical pool,
94/94 exact-name scores and zero-diff ctxdiff, all owned sections exact,
27112 linked code bytes, 2560 linked data bytes, final requested quick gate.

First full build rejected removal of the external Button table declaration:
setDefaultTitleText still uses index 5. Restored that declaration without
changing its caller. The approved get_button_no correction remains in place.
Build evidence: /tmp/sol-l1-round-b-build.log.

Full build passed on the linked candidate. DOL SHA1 is
26116613f624061ba99c8d1a299aaa6efa85670d. Live report has 94/94 exact-name
functions, 27112/27112 matched and linked code bytes, 2560/2560 matched and
linked data bytes, and 100% for every owned section. Pool is identical at
57/57 strings, including byte offsets. Both object files now reference
sButtonPaneNames at get_button_no offsets 0x16 and 0x1e with zero addends.
Successful build evidence: /tmp/sol-l1-round-b-build2.log.

All 94 target functions passed ctxdiff with equal sizes and instruction
counts and diffs 0. Evidence: /tmp/sol-l1-round-b-ctxdiff.txt.
The requested quick gate passed with zero regressions, forbidden additions
and readability warnings. Final round-b source diff from rebased HEAD is
one table reference and one Matching flag. All rebase changes retain the
previous definition order and main's TextBalloon getter calls.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 27112/27112 data 2560/2560 functions 94/94 fuzzy 100.0000 linked code 27112
[src/scene/address/iplAddressEdit] instruction-exact functions: 94/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 100.0
[src/scene/address/iplAddressEdit] baseline: code 27112/27112 data 2560 functions 94 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 98.09787 -> 98.09787
global fuzzy_match_percent: 99.92176 -> 99.92176
global complete_code_percent: 90.12492 -> 91.03011
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```
