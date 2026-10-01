# Round 3 final block map

Target: `build/43U/asm/<unit>.s`, checked against original-object function sizes. Build: `build/43U/src/<unit>.o` disassembled with `tools/decomp-assist/disasm_fn.py`. Basic-block leaders include branch destinations, fallthrough after terminators and jump-table destinations. Direct calls stay inside their basic block.

Offsets are function-relative hexadecimal; counts include real PPC instructions. Target operands are decoded from instruction bytes so `subi` aliases retain their negative immediate. Relocations supply call names, data references and ordinary string literals. Separate target/build columns list each side by block index; the following alignment spans align call sequence, string references and opcode sequence. These are alignment estimates, not proofs that a semantic path is missing.

Call-aligned region bounds are instruction indices with the upper bound excluded. Positive deficit means the target has more instructions in the span; negative means the build has more. Equal counts can still have different branches, loads or operands. Attempts and source review evidence are in `fix-board-r3.attempts.md`.

## AOSS_Init_old

Target 1584; built 1578; signed deficit 6.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 25 / _savegpr_14, memset / ['lbl_81694C78', 0], ['lbl_81694C7A', 0] / - | +0000 / 25 / _savegpr_14, memset / ['s_defaultOptions', 0] / - |
| 1 | +0064 / 2 / - / - / - | +0064 / 2 / - / - / - |
| 2 | +006c / 4 / - / - / - | +006c / 4 / - / - / - |
| 3 | +007c / 2 / - / - / - | +007c / 2 / - / - / - |
| 4 | +0084 / 4 / - / - / - | +0084 / 4 / - / - / - |
| 5 | +0094 / 2 / - / - / - | +0094 / 2 / - / - / - |
| 6 | +009c / 4 / - / - / - | +009c / 4 / - / - / - |
| 7 | +00ac / 2 / - / - / - | +00ac / 2 / - / - / - |
| 8 | +00b4 / 3 / - / - / - | +00b4 / 3 / - / - / - |
| 9 | +00c0 / 1 / - / - / - | +00c0 / 1 / - / - / - |
| 10 | +00c4 / 30 / memset, memset / ['lbl_81698C78', 0], ['AOSS_810BDEF8', 0], ['lbl_81698C84', 0] / - | +00c4 / 31 / memset, memset / ['s_accessPointName', 0], ['s_runtime', 0], ['s_errorCode', 0] / - |
| 11 | +013c / 7 / - / ['lbl_81698C84', 0], ['lbl_81698C74', 0] / - | +0140 / 7 / - / ['s_errorCode', 0], ['s_accessPointConfig', 0] / - |
| 12 | +0158 / 2 / AOSSi_Free / ['lbl_81698C74', 0] / - | +015c / 2 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 13 | +0160 / 3 / - / ['lbl_81698C70', 0] / - | +0164 / 3 / - / ['s_accessPointList', 0] / - |
| 14 | +016c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0170 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 15 | +0178 / 2 / - / - / - | +017c / 2 / - / - / - |
| 16 | +0180 / 4 / - / ['lbl_8169720C', 0] / - | +0184 / 4 / - / ['s_operationState', 0] / - |
| 17 | +0190 / 3 / AOSSi_Status / ['lbl_8169720C', 0] / - | +0194 / 3 / AOSSi_Status / ['s_operationState', 0] / - |
| 18 | +019c / 2 / - / - / - | +01a0 / 2 / - / - / - |
| 19 | +01a4 / 3 / - / ['lbl_81698C70', 0] / - | +01a8 / 3 / - / ['s_accessPointList', 0] / - |
| 20 | +01b0 / 2 / AOSSi_Free / ['lbl_81698C70', 0] / - | +01b4 / 2 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 21 | +01b8 / 4 / AOSSi_WLANGetBSSList / ['lbl_81698C70', 0] / - | +01bc / 4 / AOSSi_WLANGetBSSList / ['s_accessPointList', 0] / - |
| 22 | +01c8 / 5 / - / ['lbl_81698C74', 0] / - | +01cc / 5 / - / ['s_accessPointConfig', 0] / - |
| 23 | +01dc / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +01e0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 24 | +01e8 / 3 / - / ['lbl_81698C70', 0] / - | +01ec / 3 / - / ['s_accessPointList', 0] / - |
| 25 | +01f4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +01f8 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 26 | +0200 / 2 / - / - / - | +0204 / 2 / - / - / - |
| 27 | +0208 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +020c / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 28 | +0214 / 5 / - / ['lbl_81698C74', 0] / - | +0218 / 5 / - / ['s_accessPointConfig', 0] / - |
| 29 | +0228 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +022c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 30 | +0234 / 3 / - / ['lbl_81698C70', 0] / - | +0238 / 3 / - / ['s_accessPointList', 0] / - |
| 31 | +0240 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0244 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 32 | +024c / 2 / - / - / - | +0250 / 2 / - / - / - |
| 33 | +0254 / 4 / AOSS_CheckAP / ['lbl_81698C70', 0] / - | +0258 / 4 / AOSS_CheckAP / ['s_accessPointList', 0] / - |
| 34 | +0264 / 5 / - / ['lbl_81698C74', 0] / - | +0268 / 5 / - / ['s_accessPointConfig', 0] / - |
| 35 | +0278 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +027c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 36 | +0284 / 3 / - / ['lbl_81698C70', 0] / - | +0288 / 3 / - / ['s_accessPointList', 0] / - |
| 37 | +0290 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0294 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 38 | +029c / 2 / - / - / - | +02a0 / 2 / - / - / - |
| 39 | +02a4 / 2 / - / - / - | +02a8 / 2 / - / - / - |
| 40 | +02ac / 3 / - / - / - | +02b0 / 4 / - / - / - |
| 41 | +02b8 / 5 / - / ['lbl_81698C74', 0] / - | +02c0 / 5 / - / ['s_accessPointConfig', 0] / - |
| 42 | +02cc / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +02d4 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 43 | +02d8 / 3 / - / ['lbl_81698C70', 0] / - | +02e0 / 3 / - / ['s_accessPointList', 0] / - |
| 44 | +02e4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +02ec / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 45 | +02f0 / 2 / - / - / - | +02f8 / 2 / - / - / - |
| 46 | +02f8 / 2 / - / - / - | +0300 / 1 / - / - / - |
| 47 | +0300 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +0304 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 48 | +030c / 5 / - / ['lbl_81698C74', 0] / - | +0310 / 5 / - / ['s_accessPointConfig', 0] / - |
| 49 | +0320 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0324 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 50 | +032c / 3 / - / ['lbl_81698C70', 0] / - | +0330 / 3 / - / ['s_accessPointList', 0] / - |
| 51 | +0338 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +033c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 52 | +0344 / 2 / - / - / - | +0348 / 2 / - / - / - |
| 53 | +034c / 2 / - / - / - | +0350 / 3 / - / - / - |
| 54 | +0354 / 2 / - / - / - | +035c / 3 / AOSSi_Sleep / - / - |
| 55 | +035c / 1 / - / - / - | +0368 / 2 / AOSSi_Sleep / - / - |
| 56 | +0360 / 3 / AOSSi_Sleep / - / - | +0370 / 2 / - / - / - |
| 57 | +036c / 2 / - / - / - | +0378 / 2 / - / - / - |
| 58 | +0374 / 1 / - / - / - | +0380 / 1 / - / - / - |
| 59 | +0378 / 2 / - / - / - | +0384 / 2 / - / - / - |
| 60 | +0380 / 2 / - / - / - | +038c / 2 / - / - / - |
| 61 | +0388 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +0394 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 62 | +0394 / 5 / - / ['lbl_81698C74', 0] / - | +03a0 / 5 / - / ['s_accessPointConfig', 0] / - |
| 63 | +03a8 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +03b4 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 64 | +03b4 / 3 / - / ['lbl_81698C70', 0] / - | +03c0 / 3 / - / ['s_accessPointList', 0] / - |
| 65 | +03c0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +03cc / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 66 | +03cc / 2 / - / - / - | +03d8 / 2 / - / - / - |
| 67 | +03d4 / 2 / - / - / - | +03e0 / 2 / - / - / - |
| 68 | +03dc / 3 / - / ['lbl_8169720C', 0] / - | +03e8 / 3 / - / ['s_operationState', 0] / - |
| 69 | +03e8 / 4 / AOSSi_Status / ['lbl_8169720C', 0] / - | +03f4 / 4 / AOSSi_Status / ['s_operationState', 0] / - |
| 70 | +03f8 / 19 / memset, strlen, memcpy, strlen / ['lbl_81657C48', 0], ['lbl_81697204', 0] / 'ESSID-AOSS', 'ESSID-AOSS', 'ESSID-AOSS', 'MELCO' | +0404 / 19 / memset, strlen, memcpy, strlen / ['@2508', 0], ['s_manufacturer', 0] / 'ESSID-AOSS', 'ESSID-AOSS', 'ESSID-AOSS', 'MELCO' |
| 71 | +0444 / 1 / - / - / - | +0450 / 4 / memcpy / ['s_manufacturer', 0] / 'MELCO' |
| 72 | +0448 / 4 / memcpy / ['lbl_81697204', 0] / 'MELCO' | +0460 / 10 / AOSSi_SetNCDIPAddr / - / - |
| 73 | +0458 / 9 / AOSSi_SetNCDIPAddr / - / - | +0488 / 7 / - / ['s_errorCode', 0], ['s_accessPointConfig', 0] / - |
| 74 | +047c / 7 / - / ['lbl_81698C84', 0], ['lbl_81698C74', 0] / - | +04a4 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 75 | +0498 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +04b0 / 3 / - / ['s_accessPointList', 0] / - |
| 76 | +04a4 / 3 / - / ['lbl_81698C70', 0] / - | +04bc / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 77 | +04b0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +04c8 / 2 / - / - / - |
| 78 | +04bc / 2 / - / - / - | +04d0 / 5 / AOSSi_Alloc / ['s_accessPointConfig', 0] / - |
| 79 | +04c4 / 1 / - / - / - | +04e4 / 5 / - / ['s_accessPointConfig', 0] / - |
| 80 | +04c8 / 5 / - / ['lbl_81698C74', 0] / - | +04f8 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 81 | +04dc / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0504 / 3 / - / ['s_accessPointList', 0] / - |
| 82 | +04e8 / 3 / - / ['lbl_81698C70', 0] / - | +0510 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 83 | +04f4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +051c / 2 / - / - / - |
| 84 | +0500 / 2 / - / - / - | +0524 / 6 / memset / - / - |
| 85 | +0508 / 5 / AOSSi_Alloc / ['lbl_81698C74', 0] / - | +053c / 5 / AOSS_814020CC / ['s_accessPointConfig', 0] / - |
| 86 | +051c / 5 / - / ['lbl_81698C74', 0] / - | +0550 / 5 / - / ['s_accessPointConfig', 0] / - |
| 87 | +0530 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0564 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 88 | +053c / 3 / - / ['lbl_81698C70', 0] / - | +0570 / 3 / - / ['s_accessPointList', 0] / - |
| 89 | +0548 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +057c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 90 | +0554 / 2 / - / - / - | +0588 / 2 / - / - / - |
| 91 | +055c / 6 / memset / - / - | +0590 / 3 / - / - / - |
| 92 | +0574 / 5 / AOSS_814020CC / ['lbl_81698C74', 0] / - | +059c / 4 / - / ['s_accessPointConfig', 0] / - |
| 93 | +0588 / 5 / - / ['lbl_81698C74', 0] / - | +05ac / 1 / - / - / - |
| 94 | +059c / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +05b0 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 95 | +05a8 / 3 / - / ['lbl_81698C70', 0] / - | +05bc / 5 / - / ['s_accessPointConfig', 0] / - |
| 96 | +05b4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +05d0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 97 | +05c0 / 2 / - / - / - | +05dc / 3 / - / ['s_accessPointList', 0] / - |
| 98 | +05c8 / 2 / - / - / - | +05e8 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 99 | +05d0 / 1 / - / - / - | +05f4 / 2 / - / - / - |
| 100 | +05d4 / 4 / - / ['lbl_81698C74', 0] / - | +05fc / 2 / - / - / - |
| 101 | +05e4 / 2 / - / - / - | +0604 / 2 / - / - / - |
| 102 | +05ec / 3 / - / ['AOSSi_cancel_flag', 0] / - | +060c / 1 / - / - / - |
| 103 | +05f8 / 5 / - / ['lbl_81698C74', 0] / - | +0610 / 3 / AOSSi_Sleep / - / - |
| 104 | +060c / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +061c / 2 / - / - / - |
| 105 | +0618 / 3 / - / ['lbl_81698C70', 0] / - | +0624 / 1 / - / - / - |
| 106 | +0624 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0628 / 2 / - / - / - |
| 107 | +0630 / 2 / - / - / - | +0630 / 2 / - / - / - |
| 108 | +0638 / 2 / - / - / - | +0638 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 109 | +0640 / 2 / - / - / - | +0644 / 5 / - / ['s_accessPointConfig', 0] / - |
| 110 | +0648 / 1 / - / - / - | +0658 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 111 | +064c / 3 / AOSSi_Sleep / - / - | +0664 / 3 / - / ['s_accessPointList', 0] / - |
| 112 | +0658 / 2 / - / - / - | +0670 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 113 | +0660 / 1 / - / - / - | +067c / 2 / - / - / - |
| 114 | +0664 / 2 / - / - / - | +0684 / 1 / - / - / - |
| 115 | +066c / 2 / - / - / - | +0688 / 3 / - / - / - |
| 116 | +0674 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +0694 / 4 / - / - / - |
| 117 | +0680 / 5 / - / ['lbl_81698C74', 0] / - | +06a4 / 5 / - / ['s_accessPointConfig', 0] / - |
| 118 | +0694 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +06b8 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 119 | +06a0 / 3 / - / ['lbl_81698C70', 0] / - | +06c4 / 3 / - / ['s_accessPointList', 0] / - |
| 120 | +06ac / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +06d0 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 121 | +06b8 / 2 / - / - / - | +06dc / 2 / - / - / - |
| 122 | +06c0 / 1 / - / - / - | +06e4 / 3 / - / ['s_accessPointConfig', 0] / - |
| 123 | +06c4 / 3 / - / - / - | +06f0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 124 | +06d0 / 4 / - / - / - | +06fc / 3 / - / ['s_accessPointList', 0] / - |
| 125 | +06e0 / 5 / - / ['lbl_81698C74', 0] / - | +0708 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 126 | +06f4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0714 / 3 / - / - / - |
| 127 | +0700 / 3 / - / ['lbl_81698C70', 0] / - | +0720 / 18 / memcpy, rand, SOHtoNs / - / - |
| 128 | +070c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0768 / 7 / SOSocket / ['s_socket', 0] / - |
| 129 | +0718 / 2 / - / - / - | +0784 / 5 / - / ['s_accessPointConfig', 0] / - |
| 130 | +0720 / 3 / - / ['lbl_81698C74', 0] / - | +0798 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 131 | +072c / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +07a4 / 3 / - / ['s_accessPointList', 0] / - |
| 132 | +0738 / 3 / - / ['lbl_81698C70', 0] / - | +07b0 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 133 | +0744 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +07bc / 2 / - / - / - |
| 134 | +0750 / 3 / - / - / - | +07c4 / 2 / - / - / - |
| 135 | +075c / 15 / memcpy, rand, SOHtoNs / - / - | +07cc / 7 / - / ['s_errorCode', 0], ['s_accessPointConfig', 0] / - |
| 136 | +0798 / 7 / SOSocket / ['lbl_81697200', 0] / - | +07e8 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 137 | +07b4 / 5 / - / ['lbl_81698C74', 0] / - | +07f4 / 3 / - / ['s_accessPointList', 0] / - |
| 138 | +07c8 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0800 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 139 | +07d4 / 3 / - / ['lbl_81698C70', 0] / - | +080c / 2 / - / - / - |
| 140 | +07e0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0814 / 18 / memset, SOGetHostID, SOHtoNs, SOBind / ['s_socket', 0] / - |
| 141 | +07ec / 2 / - / - / - | +085c / 5 / - / ['s_accessPointConfig', 0] / - |
| 142 | +07f4 / 2 / - / - / - | +0870 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 143 | +07fc / 7 / - / ['lbl_81698C84', 0], ['lbl_81698C74', 0] / - | +087c / 3 / - / ['s_accessPointList', 0] / - |
| 144 | +0818 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0888 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 145 | +0824 / 3 / - / ['lbl_81698C70', 0] / - | +0894 / 2 / - / - / - |
| 146 | +0830 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +089c / 18 / - / ['s_runtime', 0] / - |
| 147 | +083c / 2 / - / - / - | +08e4 / 9 / memset / ['s_responseBuffer', 0] / - |
| 148 | +0844 / 18 / memset, SOGetHostID, SOHtoNs, SOBind / ['lbl_81697200', 0] / - | +0908 / 2 / - / - / - |
| 149 | +088c / 5 / - / ['lbl_81698C74', 0] / - | +0910 / 3 / - / - / - |
| 150 | +08a0 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +091c / 3 / - / ['s_socket', 0] / - |
| 151 | +08ac / 3 / - / ['lbl_81698C70', 0] / - | +0928 / 1 / SOClose / - / - |
| 152 | +08b8 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +092c / 4 / - / ['s_socketStarted', 0], ['s_socket', 0] / - |
| 153 | +08c4 / 2 / - / - / - | +093c / 4 / SOCleanup / ['s_socketStarted', 0] / - |
| 154 | +08cc / 18 / - / ['AOSS_810BDEF8', 0] / - | +094c / 2 / - / - / - |
| 155 | +0914 / 9 / memset / ['lbl_81698C8C', 0] / - | +0954 / 1 / - / - / - |
| 156 | +0938 / 2 / - / - / - | +0958 / 2 / - / - / - |
| 157 | +0940 / 3 / - / - / - | +0960 / 5 / - / ['s_accessPointConfig', 0] / - |
| 158 | +094c / 3 / - / ['lbl_81697200', 0] / - | +0974 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 159 | +0958 / 1 / SOClose / - / - | +0980 / 3 / - / ['s_accessPointList', 0] / - |
| 160 | +095c / 4 / - / ['lbl_81698C88', 0], ['lbl_81697200', 0] / - | +098c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 161 | +096c / 4 / SOCleanup / ['lbl_81698C88', 0] / - | +0998 / 2 / - / - / - |
| 162 | +097c / 2 / - / - / - | +09a0 / 9 / - / - / - |
| 163 | +0984 / 1 / - / - / - | +09c4 / 1 / - / - / - |
| 164 | +0988 / 2 / - / - / - | +09c8 / 8 / AOSSi_SetNCDIPAddr / - / - |
| 165 | +0990 / 5 / - / ['lbl_81698C74', 0] / - | +09e8 / 7 / - / ['s_errorCode', 0], ['s_accessPointConfig', 0] / - |
| 166 | +09a4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0a04 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 167 | +09b0 / 3 / - / ['lbl_81698C70', 0] / - | +0a10 / 3 / - / ['s_accessPointList', 0] / - |
| 168 | +09bc / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0a1c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 169 | +09c8 / 2 / - / - / - | +0a28 / 2 / - / - / - |
| 170 | +09d0 / 9 / - / - / - | +0a30 / 6 / AOSSi_Alloc / ['s_accessPointConfig', 0] / - |
| 171 | +09f4 / 1 / - / - / - | +0a48 / 5 / - / ['s_accessPointConfig', 0] / - |
| 172 | +09f8 / 7 / AOSSi_SetNCDIPAddr / - / - | +0a5c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 173 | +0a14 / 7 / - / ['lbl_81698C84', 0], ['lbl_81698C74', 0] / - | +0a68 / 3 / - / ['s_accessPointList', 0] / - |
| 174 | +0a30 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0a74 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 175 | +0a3c / 3 / - / ['lbl_81698C70', 0] / - | +0a80 / 2 / - / - / - |
| 176 | +0a48 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0a88 / 6 / memset / - / - |
| 177 | +0a54 / 2 / - / - / - | +0aa0 / 5 / AOSS_814020CC / ['s_accessPointConfig', 0] / - |
| 178 | +0a5c / 6 / AOSSi_Alloc / ['lbl_81698C74', 0] / - | +0ab4 / 5 / - / ['s_accessPointConfig', 0] / - |
| 179 | +0a74 / 5 / - / ['lbl_81698C74', 0] / - | +0ac8 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 180 | +0a88 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0ad4 / 3 / - / ['s_accessPointList', 0] / - |
| 181 | +0a94 / 3 / - / ['lbl_81698C70', 0] / - | +0ae0 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 182 | +0aa0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0aec / 2 / - / - / - |
| 183 | +0aac / 2 / - / - / - | +0af4 / 2 / - / - / - |
| 184 | +0ab4 / 6 / memset / - / - | +0afc / 4 / - / ['s_accessPointConfig', 0] / - |
| 185 | +0acc / 5 / AOSS_814020CC / ['lbl_81698C74', 0] / - | +0b0c / 2 / - / - / - |
| 186 | +0ae0 / 5 / - / ['lbl_81698C74', 0] / - | +0b14 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 187 | +0af4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0b20 / 5 / - / ['s_accessPointConfig', 0] / - |
| 188 | +0b00 / 3 / - / ['lbl_81698C70', 0] / - | +0b34 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 189 | +0b0c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0b40 / 3 / - / ['s_accessPointList', 0] / - |
| 190 | +0b18 / 2 / - / - / - | +0b4c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 191 | +0b20 / 2 / - / - / - | +0b58 / 2 / - / - / - |
| 192 | +0b28 / 1 / - / - / - | +0b60 / 3 / - / - / - |
| 193 | +0b2c / 4 / - / ['lbl_81698C74', 0] / - | +0b6c / 2 / - / - / - |
| 194 | +0b3c / 2 / - / - / - | +0b74 / 1 / - / - / - |
| 195 | +0b44 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +0b78 / 3 / AOSSi_Sleep / - / - |
| 196 | +0b50 / 5 / - / ['lbl_81698C74', 0] / - | +0b84 / 2 / - / - / - |
| 197 | +0b64 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0b8c / 1 / - / - / - |
| 198 | +0b70 / 3 / - / ['lbl_81698C70', 0] / - | +0b90 / 2 / - / - / - |
| 199 | +0b7c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0b98 / 2 / - / - / - |
| 200 | +0b88 / 2 / - / - / - | +0ba0 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 201 | +0b90 / 2 / - / - / - | +0bac / 5 / - / ['s_accessPointConfig', 0] / - |
| 202 | +0b98 / 2 / - / - / - | +0bc0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 203 | +0ba0 / 1 / - / - / - | +0bcc / 3 / - / ['s_accessPointList', 0] / - |
| 204 | +0ba4 / 3 / AOSSi_Sleep / - / - | +0bd8 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 205 | +0bb0 / 2 / - / - / - | +0be4 / 2 / - / - / - |
| 206 | +0bb8 / 1 / - / - / - | +0bec / 1 / - / - / - |
| 207 | +0bbc / 2 / - / - / - | +0bf0 / 3 / - / - / - |
| 208 | +0bc4 / 2 / - / - / - | +0bfc / 7 / SOSocket / ['s_socket', 0] / - |
| 209 | +0bcc / 3 / - / ['AOSSi_cancel_flag', 0] / - | +0c18 / 5 / - / ['s_accessPointConfig', 0] / - |
| 210 | +0bd8 / 5 / - / ['lbl_81698C74', 0] / - | +0c2c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 211 | +0bec / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0c38 / 3 / - / ['s_accessPointList', 0] / - |
| 212 | +0bf8 / 3 / - / ['lbl_81698C70', 0] / - | +0c44 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 213 | +0c04 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0c50 / 2 / - / - / - |
| 214 | +0c10 / 2 / - / - / - | +0c58 / 16 / memset, SOGetHostID, SOHtoNs, SOBind / ['s_socket', 0] / - |
| 215 | +0c18 / 1 / - / - / - | +0c98 / 5 / - / ['s_accessPointConfig', 0] / - |
| 216 | +0c1c / 3 / - / - / - | +0cac / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 217 | +0c28 / 7 / SOSocket / ['lbl_81697200', 0] / - | +0cb8 / 3 / - / ['s_accessPointList', 0] / - |
| 218 | +0c44 / 5 / - / ['lbl_81698C74', 0] / - | +0cc4 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 219 | +0c58 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0cd0 / 2 / - / - / - |
| 220 | +0c64 / 3 / - / ['lbl_81698C70', 0] / - | +0cd8 / 3 / - / ['s_socket', 0] / - |
| 221 | +0c70 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0ce4 / 1 / - / - / - |
| 222 | +0c7c / 2 / - / - / - | +0ce8 / 2 / - / - / - |
| 223 | +0c84 / 16 / memset, SOGetHostID, SOHtoNs, SOBind / ['lbl_81697200', 0] / - | +0cf0 / 1 / - / - / - |
| 224 | +0cc4 / 5 / - / ['lbl_81698C74', 0] / - | +0cf4 / 2 / - / - / - |
| 225 | +0cd8 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0cfc / 1 / - / - / - |
| 226 | +0ce4 / 3 / - / ['lbl_81698C70', 0] / - | +0d00 / 3 / - / ['s_operationState', 0] / - |
| 227 | +0cf0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0d0c / 3 / AOSSi_Status / ['s_operationState', 0] / - |
| 228 | +0cfc / 2 / - / - / - | +0d18 / 6 / AOSS_81401574 / - / - |
| 229 | +0d04 / 3 / - / ['lbl_81697200', 0] / - | +0d30 / 3 / - / ['s_operationState', 0] / - |
| 230 | +0d10 / 1 / - / - / - | +0d3c / 3 / AOSSi_Status / ['s_operationState', 0] / - |
| 231 | +0d14 / 2 / - / - / - | +0d48 / 6 / AOSS_81401778 / - / - |
| 232 | +0d1c / 1 / - / - / - | +0d60 / 3 / - / ['s_operationState', 0] / - |
| 233 | +0d20 / 2 / - / - / - | +0d6c / 4 / AOSSi_Status / ['s_operationState', 0] / - |
| 234 | +0d28 / 1 / - / - / - | +0d7c / 52 / memset, memcpy, strlen, AOSS_81401E80, SOHtoNs, SOHtoNs, SOHtoNs, SOHtoNs, memcpy, memset, SOHtoNs, SOHtoNl / ['s_responseBuffer', 0], ['s_manufacturer', 0] / 'MELCO', 'MELCO' |
| 235 | +0d2c / 3 / - / ['lbl_8169720C', 0] / - | +0e4c / 1 / - / - / - |
| 236 | +0d38 / 3 / AOSSi_Status / ['lbl_8169720C', 0] / - | +0e50 / 9 / SOSendTo / - / - |
| 237 | +0d44 / 5 / AOSS_81401574 / - / - | +0e74 / 1 / - / - / - |
| 238 | +0d58 / 3 / - / ['lbl_8169720C', 0] / - | +0e78 / 2 / - / - / - |
| 239 | +0d64 / 4 / AOSSi_Status / ['lbl_8169720C', 0] / - | +0e80 / 7 / - / ['s_errorCode', 0], ['s_accessPointConfig', 0] / - |
| 240 | +0d74 / 5 / AOSS_81401778 / - / - | +0e9c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 241 | +0d88 / 3 / - / ['lbl_8169720C', 0] / - | +0ea8 / 3 / - / ['s_accessPointList', 0] / - |
| 242 | +0d94 / 4 / AOSSi_Status / ['lbl_8169720C', 0] / - | +0eb4 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 243 | +0da4 / 52 / memset, memcpy, strlen, AOSS_81401E80, SOHtoNs, SOHtoNs, SOHtoNs, SOHtoNs, memcpy, memset, SOHtoNs, SOHtoNl / ['lbl_81698C8C', 0], ['lbl_81697204', 0] / 'MELCO', 'MELCO' | +0ec0 / 2 / - / - / - |
| 244 | +0e74 / 1 / - / - / - | +0ec8 / 39 / memset, SOPoll / ['s_socket', 0] / - |
| 245 | +0e78 / 9 / SOSendTo / - / - | +0f64 / 5 / - / - / - |
| 246 | +0e9c / 1 / - / - / - | +0f78 / 2 / - / - / - |
| 247 | +0ea0 / 2 / - / - / - | +0f80 / 1 / - / - / - |
| 248 | +0ea8 / 7 / - / ['lbl_81698C84', 0], ['lbl_81698C74', 0] / - | +0f84 / 2 / - / - / - |
| 249 | +0ec4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +0f8c / 1 / - / - / - |
| 250 | +0ed0 / 3 / - / ['lbl_81698C70', 0] / - | +0f90 / 3 / - / ['s_errorCode', 0] / - |
| 251 | +0edc / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +0f9c / 3 / - / ['s_errorCode', 0] / - |
| 252 | +0ee8 / 2 / - / - / - | +0fa8 / 2 / - / ['s_errorCode', 0] / - |
| 253 | +0ef0 / 39 / memset, SOPoll / ['lbl_81697200', 0] / - | +0fb0 / 2 / - / - / - |
| 254 | +0f8c / 5 / - / - / - | +0fb8 / 2 / - / - / - |
| 255 | +0fa0 / 2 / - / - / - | +0fc0 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 256 | +0fa8 / 3 / - / ['lbl_81698C84', 0] / - | +0fcc / 5 / - / ['s_accessPointConfig', 0] / - |
| 257 | +0fb4 / 2 / - / - / - | +0fe0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 258 | +0fbc / 3 / - / ['lbl_81698C84', 0] / - | +0fec / 3 / - / ['s_accessPointList', 0] / - |
| 259 | +0fc8 / 2 / - / ['lbl_81698C84', 0] / - | +0ff8 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 260 | +0fd0 / 2 / - / - / - | +1004 / 2 / - / - / - |
| 261 | +0fd8 / 2 / - / - / - | +100c / 2 / - / - / - |
| 262 | +0fe0 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +1014 / 2 / - / - / - |
| 263 | +0fec / 5 / - / ['lbl_81698C74', 0] / - | +101c / 1 / - / - / - |
| 264 | +1000 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1020 / 3 / AOSSi_Sleep / - / - |
| 265 | +100c / 3 / - / ['lbl_81698C70', 0] / - | +102c / 2 / - / - / - |
| 266 | +1018 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1034 / 1 / - / - / - |
| 267 | +1024 / 2 / - / - / - | +1038 / 2 / - / - / - |
| 268 | +102c / 2 / - / - / - | +1040 / 2 / - / - / - |
| 269 | +1034 / 2 / - / - / - | +1048 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 270 | +103c / 1 / - / - / - | +1054 / 5 / - / ['s_accessPointConfig', 0] / - |
| 271 | +1040 / 3 / AOSSi_Sleep / - / - | +1068 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 272 | +104c / 2 / - / - / - | +1074 / 3 / - / ['s_accessPointList', 0] / - |
| 273 | +1054 / 1 / - / - / - | +1080 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 274 | +1058 / 2 / - / - / - | +108c / 2 / - / - / - |
| 275 | +1060 / 2 / - / - / - | +1094 / 22 / SORecvFrom, SONtoHs, AOSS_814001B4 / ['s_socket', 0] / - |
| 276 | +1068 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +10ec / 2 / - / - / - |
| 277 | +1074 / 5 / - / ['lbl_81698C74', 0] / - | +10f4 / 2 / - / - / - |
| 278 | +1088 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +10fc / 2 / - / - / - |
| 279 | +1094 / 3 / - / ['lbl_81698C70', 0] / - | +1104 / 2 / - / - / - |
| 280 | +10a0 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +110c / 3 / - / - / - |
| 281 | +10ac / 2 / - / - / - | +1118 / 3 / - / ['s_socket', 0] / - |
| 282 | +10b4 / 23 / SORecvFrom, SONtoHs, AOSS_814001B4 / ['lbl_81697200', 0] / - | +1124 / 1 / SOClose / - / - |
| 283 | +1110 / 2 / - / - / - | +1128 / 4 / - / ['s_socketStarted', 0], ['s_socket', 0] / - |
| 284 | +1118 / 2 / - / - / - | +1138 / 4 / SOCleanup / ['s_socketStarted', 0] / - |
| 285 | +1120 / 2 / - / - / - | +1148 / 2 / - / - / - |
| 286 | +1128 / 2 / - / - / - | +1150 / 1 / - / - / - |
| 287 | +1130 / 2 / - / - / - | +1154 / 2 / - / - / - |
| 288 | +1138 / 3 / - / ['lbl_81697200', 0] / - | +115c / 5 / - / ['s_accessPointConfig', 0] / - |
| 289 | +1144 / 1 / SOClose / - / - | +1170 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 290 | +1148 / 4 / - / ['lbl_81698C88', 0], ['lbl_81697200', 0] / - | +117c / 3 / - / ['s_accessPointList', 0] / - |
| 291 | +1158 / 4 / SOCleanup / ['lbl_81698C88', 0] / - | +1188 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 292 | +1168 / 2 / - / - / - | +1194 / 2 / - / - / - |
| 293 | +1170 / 1 / - / - / - | +119c / 3 / - / ['s_operationState', 0] / - |
| 294 | +1174 / 2 / - / - / - | +11a8 / 4 / AOSSi_Status / ['s_operationState', 0] / - |
| 295 | +117c / 5 / - / ['lbl_81698C74', 0] / - | +11b8 / 3 / - / ['s_accessPointList', 0] / - |
| 296 | +1190 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +11c4 / 2 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 297 | +119c / 3 / - / ['lbl_81698C70', 0] / - | +11cc / 4 / AOSSi_WLANGetBSSList / ['s_accessPointList', 0] / - |
| 298 | +11a8 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +11dc / 5 / - / ['s_accessPointConfig', 0] / - |
| 299 | +11b4 / 2 / - / - / - | +11f0 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 300 | +11bc / 3 / - / ['lbl_8169720C', 0] / - | +11fc / 3 / - / ['s_accessPointList', 0] / - |
| 301 | +11c8 / 4 / AOSSi_Status / ['lbl_8169720C', 0] / - | +1208 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 302 | +11d8 / 3 / - / ['lbl_81698C70', 0] / - | +1214 / 2 / - / - / - |
| 303 | +11e4 / 2 / AOSSi_Free / ['lbl_81698C70', 0] / - | +121c / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 304 | +11ec / 4 / AOSSi_WLANGetBSSList / ['lbl_81698C70', 0] / - | +1228 / 5 / - / ['s_accessPointConfig', 0] / - |
| 305 | +11fc / 5 / - / ['lbl_81698C74', 0] / - | +123c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 306 | +1210 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1248 / 3 / - / ['s_accessPointList', 0] / - |
| 307 | +121c / 3 / - / ['lbl_81698C70', 0] / - | +1254 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 308 | +1228 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1260 / 2 / - / - / - |
| 309 | +1234 / 2 / - / - / - | +1268 / 4 / AOSS_CheckAP / ['s_accessPointList', 0] / - |
| 310 | +123c / 3 / - / ['AOSSi_cancel_flag', 0] / - | +1278 / 5 / - / ['s_accessPointConfig', 0] / - |
| 311 | +1248 / 5 / - / ['lbl_81698C74', 0] / - | +128c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 312 | +125c / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1298 / 3 / - / ['s_accessPointList', 0] / - |
| 313 | +1268 / 3 / - / ['lbl_81698C70', 0] / - | +12a4 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 314 | +1274 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +12b0 / 2 / - / - / - |
| 315 | +1280 / 2 / - / - / - | +12b8 / 2 / - / - / - |
| 316 | +1288 / 4 / AOSS_CheckAP / ['lbl_81698C70', 0] / - | +12c0 / 5 / - / ['s_accessPointConfig', 0] / - |
| 317 | +1298 / 5 / - / ['lbl_81698C74', 0] / - | +12d4 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 318 | +12ac / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +12e0 / 3 / - / ['s_accessPointList', 0] / - |
| 319 | +12b8 / 3 / - / ['lbl_81698C70', 0] / - | +12ec / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 320 | +12c4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +12f8 / 2 / - / - / - |
| 321 | +12d0 / 2 / - / - / - | +1300 / 5 / AOSSi_Alloc / ['s_accessPointConfig', 0] / - |
| 322 | +12d8 / 2 / - / - / - | +1314 / 5 / - / ['s_accessPointConfig', 0] / - |
| 323 | +12e0 / 5 / - / ['lbl_81698C74', 0] / - | +1328 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 324 | +12f4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1334 / 3 / - / ['s_accessPointList', 0] / - |
| 325 | +1300 / 3 / - / ['lbl_81698C70', 0] / - | +1340 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 326 | +130c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +134c / 2 / - / - / - |
| 327 | +1318 / 2 / - / - / - | +1354 / 6 / memset / - / - |
| 328 | +1320 / 5 / AOSSi_Alloc / ['lbl_81698C74', 0] / - | +136c / 5 / AOSS_814020CC / ['s_accessPointConfig', 0] / - |
| 329 | +1334 / 5 / - / ['lbl_81698C74', 0] / - | +1380 / 5 / - / ['s_accessPointConfig', 0] / - |
| 330 | +1348 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1394 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 331 | +1354 / 3 / - / ['lbl_81698C70', 0] / - | +13a0 / 3 / - / ['s_accessPointList', 0] / - |
| 332 | +1360 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +13ac / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 333 | +136c / 2 / - / - / - | +13b8 / 2 / - / - / - |
| 334 | +1374 / 6 / memset / - / - | +13c0 / 2 / - / - / - |
| 335 | +138c / 5 / AOSS_814020CC / ['lbl_81698C74', 0] / - | +13c8 / 4 / - / ['s_accessPointConfig', 0] / - |
| 336 | +13a0 / 5 / - / ['lbl_81698C74', 0] / - | +13d8 / 2 / - / - / - |
| 337 | +13b4 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +13e0 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 338 | +13c0 / 3 / - / ['lbl_81698C70', 0] / - | +13ec / 5 / - / ['s_accessPointConfig', 0] / - |
| 339 | +13cc / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1400 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 340 | +13d8 / 2 / - / - / - | +140c / 3 / - / ['s_accessPointList', 0] / - |
| 341 | +13e0 / 2 / - / - / - | +1418 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 342 | +13e8 / 1 / - / - / - | +1424 / 2 / - / - / - |
| 343 | +13ec / 4 / - / ['lbl_81698C74', 0] / - | +142c / 2 / - / - / - |
| 344 | +13fc / 2 / - / - / - | +1434 / 2 / - / - / - |
| 345 | +1404 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +143c / 1 / - / - / - |
| 346 | +1410 / 5 / - / ['lbl_81698C74', 0] / - | +1440 / 3 / AOSSi_Sleep / - / - |
| 347 | +1424 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +144c / 2 / - / - / - |
| 348 | +1430 / 3 / - / ['lbl_81698C70', 0] / - | +1454 / 1 / - / - / - |
| 349 | +143c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1458 / 2 / - / - / - |
| 350 | +1448 / 2 / - / - / - | +1460 / 2 / - / - / - |
| 351 | +1450 / 2 / - / - / - | +1468 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 352 | +1458 / 2 / - / - / - | +1474 / 5 / - / ['s_accessPointConfig', 0] / - |
| 353 | +1460 / 1 / - / - / - | +1488 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 354 | +1464 / 3 / AOSSi_Sleep / - / - | +1494 / 3 / - / ['s_accessPointList', 0] / - |
| 355 | +1470 / 2 / - / - / - | +14a0 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 356 | +1478 / 1 / - / - / - | +14ac / 2 / - / - / - |
| 357 | +147c / 2 / - / - / - | +14b4 / 1 / - / - / - |
| 358 | +1484 / 2 / - / - / - | +14b8 / 3 / - / - / - |
| 359 | +148c / 3 / - / ['AOSSi_cancel_flag', 0] / - | +14c4 / 3 / - / ['s_accessPointConfig', 0] / - |
| 360 | +1498 / 5 / - / ['lbl_81698C74', 0] / - | +14d0 / 2 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 361 | +14ac / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +14d8 / 3 / - / ['s_accessPointList', 0] / - |
| 362 | +14b8 / 3 / - / ['lbl_81698C70', 0] / - | +14e4 / 2 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 363 | +14c4 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +14ec / 7 / SOSocket / ['s_socket', 0] / - |
| 364 | +14d0 / 2 / - / - / - | +1508 / 5 / - / ['s_accessPointConfig', 0] / - |
| 365 | +14d8 / 1 / - / - / - | +151c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 366 | +14dc / 3 / - / - / - | +1528 / 3 / - / ['s_accessPointList', 0] / - |
| 367 | +14e8 / 3 / - / ['lbl_81698C74', 0] / - | +1534 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 368 | +14f4 / 2 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1540 / 2 / - / - / - |
| 369 | +14fc / 3 / - / ['lbl_81698C70', 0] / - | +1548 / 16 / memset, SOGetHostID, SOHtoNs, SOBind / ['s_socket', 0] / - |
| 370 | +1508 / 2 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1588 / 5 / - / ['s_accessPointConfig', 0] / - |
| 371 | +1510 / 7 / SOSocket / ['lbl_81697200', 0] / - | +159c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 372 | +152c / 5 / - / ['lbl_81698C74', 0] / - | +15a8 / 3 / - / ['s_accessPointList', 0] / - |
| 373 | +1540 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +15b4 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 374 | +154c / 3 / - / ['lbl_81698C70', 0] / - | +15c0 / 2 / - / - / - |
| 375 | +1558 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +15c8 / 2 / - / - / - |
| 376 | +1564 / 2 / - / - / - | +15d0 / 5 / - / - / - |
| 377 | +156c / 16 / memset, SOGetHostID, SOHtoNs, SOBind / ['lbl_81697200', 0] / - | +15e4 / 2 / - / - / - |
| 378 | +15ac / 5 / - / ['lbl_81698C74', 0] / - | +15ec / 1 / - / - / - |
| 379 | +15c0 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +15f0 / 2 / - / - / - |
| 380 | +15cc / 3 / - / ['lbl_81698C70', 0] / - | +15f8 / 1 / - / - / - |
| 381 | +15d8 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +15fc / 3 / - / ['s_errorCode', 0] / - |
| 382 | +15e4 / 2 / - / - / - | +1608 / 3 / - / ['s_errorCode', 0] / - |
| 383 | +15ec / 2 / - / - / - | +1614 / 2 / - / ['s_errorCode', 0] / - |
| 384 | +15f4 / 5 / - / - / - | +161c / 2 / - / - / - |
| 385 | +1608 / 2 / - / - / - | +1624 / 2 / - / - / - |
| 386 | +1610 / 3 / - / ['lbl_81698C84', 0] / - | +162c / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 387 | +161c / 2 / - / - / - | +1638 / 5 / - / ['s_accessPointConfig', 0] / - |
| 388 | +1624 / 3 / - / ['lbl_81698C84', 0] / - | +164c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 389 | +1630 / 2 / - / ['lbl_81698C84', 0] / - | +1658 / 3 / - / ['s_accessPointList', 0] / - |
| 390 | +1638 / 2 / - / - / - | +1664 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 391 | +1640 / 2 / - / - / - | +1670 / 2 / - / - / - |
| 392 | +1648 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +1678 / 2 / - / - / - |
| 393 | +1654 / 5 / - / ['lbl_81698C74', 0] / - | +1680 / 3 / AOSSi_Sleep / - / - |
| 394 | +1668 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +168c / 2 / AOSSi_Sleep / - / - |
| 395 | +1674 / 3 / - / ['lbl_81698C70', 0] / - | +1694 / 2 / - / - / - |
| 396 | +1680 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +169c / 2 / - / - / - |
| 397 | +168c / 2 / - / - / - | +16a4 / 1 / - / - / - |
| 398 | +1694 / 2 / - / - / - | +16a8 / 2 / - / - / - |
| 399 | +169c / 2 / - / - / - | +16b0 / 2 / - / - / - |
| 400 | +16a4 / 1 / - / - / - | +16b8 / 3 / - / ['AOSSi_cancel_flag', 0] / - |
| 401 | +16a8 / 3 / AOSSi_Sleep / - / - | +16c4 / 5 / - / ['s_accessPointConfig', 0] / - |
| 402 | +16b4 / 2 / - / - / - | +16d8 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 403 | +16bc / 1 / - / - / - | +16e4 / 3 / - / ['s_accessPointList', 0] / - |
| 404 | +16c0 / 2 / - / - / - | +16f0 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 405 | +16c8 / 2 / - / - / - | +16fc / 2 / - / - / - |
| 406 | +16d0 / 3 / - / ['AOSSi_cancel_flag', 0] / - | +1704 / 3 / - / ['s_socket', 0] / - |
| 407 | +16dc / 5 / - / ['lbl_81698C74', 0] / - | +1710 / 1 / SOClose / - / - |
| 408 | +16f0 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +1714 / 5 / - / ['s_socketStarted', 0], ['s_socket', 0] / - |
| 409 | +16fc / 3 / - / ['lbl_81698C70', 0] / - | +1728 / 5 / SOCleanup / ['s_socketStarted', 0] / - |
| 410 | +1708 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +173c / 2 / - / - / - |
| 411 | +1714 / 2 / - / - / - | +1744 / 1 / - / - / - |
| 412 | +171c / 3 / - / ['lbl_81697200', 0] / - | +1748 / 2 / - / - / - |
| 413 | +1728 / 1 / SOClose / - / - | +1750 / 5 / - / ['s_accessPointConfig', 0] / - |
| 414 | +172c / 5 / - / ['lbl_81698C88', 0], ['lbl_81697200', 0] / - | +1764 / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 415 | +1740 / 5 / SOCleanup / ['lbl_81698C88', 0] / - | +1770 / 3 / - / ['s_accessPointList', 0] / - |
| 416 | +1754 / 2 / - / - / - | +177c / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 417 | +175c / 1 / - / - / - | +1788 / 2 / - / - / - |
| 418 | +1760 / 2 / - / - / - | +1790 / 2 / - / - / - |
| 419 | +1768 / 5 / - / ['lbl_81698C74', 0] / - | +1798 / 3 / - / ['s_errorCode', 0] / - |
| 420 | +177c / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +17a4 / 1 / - / - / - |
| 421 | +1788 / 3 / - / ['lbl_81698C70', 0] / - | +17a8 / 2 / - / - / - |
| 422 | +1794 / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +17b0 / 1 / - / - / - |
| 423 | +17a0 / 2 / - / - / - | +17b4 / 1 / - / - / - |
| 424 | +17a8 / 2 / - / - / - | +17b8 / 2 / - / - / - |
| 425 | +17b0 / 3 / - / ['lbl_81698C84', 0] / - | +17c0 / 1 / - / - / - |
| 426 | +17bc / 1 / - / - / - | +17c4 / 2 / - / - / - |
| 427 | +17c0 / 2 / - / - / - | +17cc / 1 / - / - / - |
| 428 | +17c8 / 1 / - / - / - | +17d0 / 2 / - / - / - |
| 429 | +17cc / 1 / - / - / - | +17d8 / 2 / - / - / - |
| 430 | +17d0 / 2 / - / - / - | +17e0 / 2 / - / - / - |
| 431 | +17d8 / 1 / - / - / - | +17e8 / 2 / - / - / - |
| 432 | +17dc / 2 / - / - / - | +17f0 / 2 / - / - / - |
| 433 | +17e4 / 1 / - / - / - | +17f8 / 1 / - / - / - |
| 434 | +17e8 / 2 / - / - / - | +17fc / 4 / - / ['s_accessPointConfig', 0] / - |
| 435 | +17f0 / 2 / - / - / - | +180c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 436 | +17f8 / 2 / - / - / - | +1818 / 3 / - / ['s_accessPointList', 0] / - |
| 437 | +1800 / 2 / - / - / - | +1824 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 438 | +1808 / 2 / - / - / - | +1830 / 2 / - / - / - |
| 439 | +1810 / 1 / - / - / - | +1838 / 4 / AOSS_813FFD68 / - / - |
| 440 | +1814 / 4 / - / ['lbl_81698C74', 0] / - | +1848 / 5 / - / ['s_accessPointConfig', 0] / - |
| 441 | +1824 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | +185c / 3 / AOSSi_Free / ['s_accessPointConfig', 0] / - |
| 442 | +1830 / 3 / - / ['lbl_81698C70', 0] / - | +1868 / 3 / - / ['s_accessPointList', 0] / - |
| 443 | +183c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | +1874 / 3 / AOSSi_Free / ['s_accessPointList', 0] / - |
| 444 | +1848 / 2 / - / - / - | +1880 / 2 / - / - / - |
| 445 | +1850 / 4 / AOSS_813FFD68 / - / - | +1888 / 1 / - / - / - |
| 446 | +1860 / 5 / - / ['lbl_81698C74', 0] / - | +188c / 7 / _restgpr_14 / - / - |
| 447 | +1874 / 3 / AOSSi_Free / ['lbl_81698C74', 0] / - | - |
| 448 | +1880 / 3 / - / ['lbl_81698C70', 0] / - | - |
| 449 | +188c / 3 / AOSSi_Free / ['lbl_81698C70', 0] / - | - |
| 450 | +1898 / 2 / - / - / - | - |
| 451 | +18a0 / 1 / - / - / - | - |
| 452 | +18a4 / 7 / _restgpr_14 / - / - | - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |
| replace | 0:1 / 25 | 0:1 / 25 |
| replace | 10:11 / 30 | 10:11 / 31 |
| replace | 21:22 / 4 | 21:22 / 4 |
| replace | 40:41 / 3 | 40:41 / 4 |
| replace | 46:47 / 2 | 46:47 / 1 |
| replace | 53:59 / 11 | 53:59 / 13 |
| replace | 70:74 / 33 | 70:73 / 33 |
| delete | 75:81 / 17 | 74:74 / 0 |
| replace | 98:102 / 9 | 91:94 / 8 |
| replace | 124:125 / 4 | 116:117 / 4 |
| replace | 134:136 / 18 | 126:128 / 21 |
| replace | 154:156 / 27 | 146:148 / 27 |
| replace | 161:162 / 4 | 153:154 / 4 |
| replace | 170:171 / 9 | 162:163 / 9 |
| replace | 172:173 / 7 | 164:165 / 8 |
| replace | 178:179 / 6 | 170:171 / 6 |
| replace | 192:194 / 5 | 184:185 / 4 |
| replace | 201:202 / 2 | 192:193 / 3 |
| replace | 237:238 / 5 | 228:232 / 18 |
| replace | 240:244 / 64 | 234:235 / 52 |
| replace | 253:254 / 39 | 244:245 / 39 |
| replace | 255:256 / 2 | 246:250 / 6 |
| delete | 257:258 / 2 | 251:251 / 0 |
| replace | 282:283 / 23 | 275:276 / 22 |
| replace | 287:288 / 2 | 280:281 / 3 |
| replace | 304:305 / 4 | 297:298 / 4 |
| replace | 328:329 / 5 | 321:322 / 5 |
| replace | 342:344 / 5 | 335:336 / 4 |
| replace | 354:357 / 6 | 346:349 / 6 |
| replace | 385:386 / 2 | 377:381 / 6 |
| delete | 387:388 / 2 | 382:382 / 0 |
| replace | 399:402 / 6 | 393:396 / 7 |
| replace | 415:416 / 5 | 409:410 / 5 |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| R001 | 8:21 | 8:21 | +0 | memset |
| R002 | 21:53 | 21:53 | +0 | memset |
| R004 | 60:87 | 60:88 | -1 | AOSSi_Free |
| R008 | 109:112 | 110:113 | +0 | AOSSi_WLANGetBSSList |
| R016 | 165:180 | 166:182 | -1 | AOSSi_Free |
| R018 | 186:201 | 188:202 | +1 | AOSSi_Free |
| R020 | 207:217 | 208:217 | +1 | AOSSi_Sleep |
| R021 | 217:235 | 217:238 | -3 | AOSSi_Free |
| R027 | 266:270 | 269:273 | +0 | strlen |
| R028 | 270:278 | 273:280 | +1 | memcpy |
| R030 | 285:312 | 287:298 | +16 | AOSSi_Free |
| R039 | 366:388 | 352:373 | +1 | AOSSi_Free |
| R044 | 428:446 | 413:431 | +0 | AOSSi_Free |
| R048 | 466:476 | 451:463 | -2 | memcpy |
| R050 | 477:481 | 464:468 | +0 | SOHtoNs |
| R051 | 481:490 | 468:478 | -1 | SOSocket |
| R062 | 559:586 | 547:574 | +0 | memset |
| R063 | 586:599 | 574:587 | +0 | SOClose |
| R065 | 605:618 | 593:606 | +0 | AOSSi_Free |
| R067 | 624:643 | 612:632 | -1 | AOSSi_SetNCDIPAddr |
| R071 | 666:675 | 655:664 | +0 | AOSSi_Free |
| R077 | 708:730 | 697:718 | +1 | AOSSi_Free |
| R079 | 736:746 | 724:735 | -1 | AOSSi_Sleep |
| R093 | 853:861 | 842:850 | +0 | AOSSi_Status |
| R095 | 865:873 | 854:863 | -1 | AOSSi_Status |
| R098 | 882:884 | 872:874 | +0 | strlen |
| R099 | 884:889 | 874:879 | +0 | AOSS_81401E80 |
| R112 | 960:993 | 950:983 | +0 | SOPoll |
| R113 | 993:1025 | 983:1017 | -2 | AOSSi_Free |
| R118 | 1065:1077 | 1057:1068 | +1 | SORecvFrom |
| R121 | 1089:1106 | 1080:1098 | -1 | SOClose |
| R127 | 1146:1149 | 1138:1141 | +0 | AOSSi_WLANGetBSSList |
| R138 | 1226:1235 | 1218:1227 | +0 | AOSSi_Free |
| R144 | 1268:1290 | 1260:1281 | +1 | AOSSi_Free |
| R147 | 1306:1324 | 1297:1315 | +0 | AOSSi_Free |
| R160 | 1399:1435 | 1390:1428 | -2 | AOSSi_Free |
| R162 | 1441:1451 | 1434:1442 | +2 | AOSSi_Sleep |
| R163 | 1451:1469 | 1442:1463 | -3 | AOSSi_Free |
| R167 | 1491:1504 | 1485:1498 | +0 | AOSSi_Free |

## AOSS_81400830

Target 321; built 321; signed deficit 0.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 20 / _savegpr_26, memcpy, strlen, AOSS_81401E80 / ['lbl_81697204', 0] / 'MELCO', 'MELCO' | +0000 / 20 / _savegpr_26, memcpy, strlen, AOSS_81401E80 / ['s_manufacturer', 0] / 'MELCO', 'MELCO' |
| 1 | +0050 / 4 / - / ['lbl_81698C84', 0] / - | +0050 / 4 / - / ['s_errorCode', 0] / - |
| 2 | +0060 / 7 / SONtoHs, AOSS_81400D34 / - / - | +0060 / 7 / SONtoHs, AOSS_81400D34 / - / - |
| 3 | +007c / 1 / - / - / - | +007c / 1 / - / - / - |
| 4 | +0080 / 5 / SONtoHs / - / - | +0080 / 5 / SONtoHs / - / - |
| 5 | +0094 / 4 / memcpy / ['lbl_81698C78', 0] / - | +0094 / 4 / memcpy / ['s_accessPointName', 0] / - |
| 6 | +00a4 / 4 / SONtoHs / - / - | +00a4 / 4 / SONtoHs / - / - |
| 7 | +00b4 / 2 / - / - / - | +00b4 / 2 / - / - / - |
| 8 | +00bc / 8 / SONtoHs, AOSSi_Alloc / - / - | +00bc / 8 / SONtoHs, AOSSi_Alloc / - / - |
| 9 | +00dc / 4 / - / ['lbl_81698C84', 0] / - | +00dc / 4 / - / ['s_errorCode', 0] / - |
| 10 | +00ec / 6 / AOSSi_Alloc / - / - | +00ec / 6 / AOSSi_Alloc / - / - |
| 11 | +0104 / 4 / - / ['lbl_81698C84', 0] / - | +0104 / 4 / - / ['s_errorCode', 0] / - |
| 12 | +0114 / 20 / memcpy, memcpy, AOSS_81401C9C / ['AOSS_810BE838', 0], ['lbl_81698C78', 0] / - | +0114 / 20 / memcpy, memcpy, AOSS_81401C9C / ['s_packetState', 0], ['s_accessPointName', 0] / - |
| 13 | +0164 / 3 / - / - / - | +0164 / 3 / - / - / - |
| 14 | +0170 / 61 / - / - / - | +0170 / 61 / - / - / - |
| 15 | +0264 / 2 / - / - / - | +0264 / 2 / - / - / - |
| 16 | +026c / 1 / - / - / - | +026c / 1 / - / - / - |
| 17 | +0270 / 32 / - / - / - | +0270 / 32 / - / - / - |
| 18 | +02f0 / 8 / AOSS_81401DC0 / ['AOSS_810BE8A0', 0] / - | +02f0 / 8 / AOSS_81401DC0 / ['s_crcTable', 0] / - |
| 19 | +0310 / 3 / - / - / - | +0310 / 3 / - / - / - |
| 20 | +031c / 2 / - / - / - | +031c / 2 / - / - / - |
| 21 | +0324 / 4 / - / - / - | +0324 / 4 / - / - / - |
| 22 | +0334 / 1 / - / - / - | +0334 / 1 / - / - / - |
| 23 | +0338 / 2 / - / - / - | +0338 / 2 / - / - / - |
| 24 | +0340 / 7 / - / ['AOSS_810BE8A0', 0] / - | +0340 / 7 / - / ['s_crcTable', 0] / - |
| 25 | +035c / 51 / - / - / - | +035c / 51 / - / - / - |
| 26 | +0428 / 7 / - / ['AOSS_810BE8A0', 0] / - | +0428 / 7 / - / ['s_crcTable', 0] / - |
| 27 | +0444 / 8 / - / - / - | +0444 / 8 / - / - / - |
| 28 | +0464 / 5 / - / - / - | +0464 / 5 / - / - / - |
| 29 | +0478 / 6 / AOSSi_Free / ['lbl_81698C84', 0] / - | +0478 / 6 / AOSSi_Free / ['s_errorCode', 0] / - |
| 30 | +0490 / 3 / AOSSi_Free / - / - | +0490 / 3 / AOSSi_Free / - / - |
| 31 | +049c / 2 / - / - / - | +049c / 2 / - / - / - |
| 32 | +04a4 / 6 / AOSSi_Free / ['lbl_81698C84', 0] / - | +04a4 / 6 / AOSSi_Free / ['s_errorCode', 0] / - |
| 33 | +04bc / 2 / - / - / - | +04bc / 2 / - / - / - |
| 34 | +04c4 / 10 / memcpy, SOHtoNs, AOSSi_Free / - / - | +04c4 / 10 / memcpy, SOHtoNs, AOSSi_Free / - / - |
| 35 | +04ec / 6 / _restgpr_26 / - / - | +04ec / 6 / _restgpr_26 / - / - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |
| replace | 0:1 / 20 | 0:1 / 20 |
| replace | 5:6 / 4 | 5:6 / 4 |
| replace | 12:13 / 20 | 12:13 / 20 |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| R002 | 11:13 | 11:13 | +0 | strlen |
| R003 | 13:18 | 13:18 | +0 | AOSS_81401E80 |
| R007 | 34:41 | 34:41 | +0 | memcpy |
| R013 | 74:79 | 74:79 | +0 | memcpy |

## AOSS_814013AC

Target 114; built 114; signed deficit 0.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 12 / _savegpr_24 / - / - | +0000 / 12 / _savegpr_24 / - / - |
| 1 | +0030 / 2 / - / - / - | +0030 / 2 / - / - / - |
| 2 | +0038 / 2 / - / ['lbl_81697210', 0] / - | +0038 / 2 / - / ['s_responseTypeByState', 0] / - |
| 3 | +0040 / 4 / - / - / - | +0040 / 4 / - / - / - |
| 4 | +0050 / 7 / SONtoHs / - / - | +0050 / 7 / SONtoHs / - / - |
| 5 | +006c / 2 / - / - / - | +006c / 2 / - / - / - |
| 6 | +0074 / 13 / SONtoHs / - / - | +0074 / 13 / SONtoHs / - / - |
| 7 | +00a8 / 3 / - / - / - | +00a8 / 3 / - / - / - |
| 8 | +00b4 / 1 / - / - / - | +00b4 / 1 / - / - / - |
| 9 | +00b8 / 2 / - / - / - | +00b8 / 2 / - / - / - |
| 10 | +00c0 / 1 / - / - / - | +00c0 / 1 / - / - / - |
| 11 | +00c4 / 2 / - / - / - | +00c4 / 2 / - / - / - |
| 12 | +00cc / 1 / - / - / - | +00cc / 1 / - / - / - |
| 13 | +00d0 / 2 / - / - / - | +00d0 / 2 / - / - / - |
| 14 | +00d8 / 1 / - / - / - | +00d8 / 1 / - / - / - |
| 15 | +00dc / 5 / AOSS_81401104 / - / - | +00dc / 5 / AOSS_81401104 / - / - |
| 16 | +00f0 / 5 / AOSS_81401104 / - / - | +00f0 / 5 / AOSS_81401104 / - / - |
| 17 | +0104 / 5 / AOSS_81401284 / - / - | +0104 / 5 / AOSS_81401284 / - / - |
| 18 | +0118 / 5 / AOSS_81401284 / - / - | +0118 / 5 / AOSS_81401284 / - / - |
| 19 | +012c / 4 / SONtoHs / - / - | +012c / 4 / SONtoHs / - / - |
| 20 | +013c / 2 / - / - / - | +013c / 2 / - / - / - |
| 21 | +0144 / 3 / - / - / - | +0144 / 3 / - / - / - |
| 22 | +0150 / 2 / - / - / - | +0150 / 2 / - / - / - |
| 23 | +0158 / 5 / memcpy / - / - | +0158 / 5 / memcpy / - / - |
| 24 | +016c / 1 / - / - / - | +016c / 1 / - / - / - |
| 25 | +0170 / 2 / - / - / - | +0170 / 2 / - / - / - |
| 26 | +0178 / 1 / - / - / - | +0178 / 1 / - / - / - |
| 27 | +017c / 7 / SONtoHs / - / - | +017c / 7 / SONtoHs / - / - |
| 28 | +0198 / 6 / - / ['AOSS_810BDEF8', 0] / - | +0198 / 6 / - / ['s_runtime', 0] / - |
| 29 | +01b0 / 6 / _restgpr_24 / - / - | +01b0 / 6 / _restgpr_24 / - / - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |
| replace | 2:3 / 2 | 2:3 / 2 |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| R001 | 5:22 | 5:22 | +0 | SONtoHs |

## AOSS_81401778

Target 273; built 271; signed deficit 2.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 36 / _savegpr_25, memset, memset, SOHtoNs, SOHtoNl / ['lbl_81698C8C', 0], ['AOSS_810BDEF8', 0], ['lbl_81698C80', 0] / - | +0000 / 37 / _savegpr_24, memset, memset, SOHtoNs, SOHtoNl / ['...bss.0', 0], ['s_responseBuffer', 0], ['s_connectionState', 0] / - |
| 1 | +0090 / 63 / AOSS_81401DC0, AOSSi_Alloc / ['AOSS_810BE8A0', 0] / - | +0094 / 62 / AOSS_81401DC0, AOSSi_Alloc / - / - |
| 2 | +018c / 25 / rand, memcpy, memcpy, memcpy, AOSS_81401C9C / ['AOSS_810BE838', 0], ['lbl_81698C78', 0] / - | +018c / 24 / rand, memcpy, memcpy, memcpy, AOSS_81401C9C / ['s_accessPointName', 0] / - |
| 3 | +01f0 / 64 / - / - / - | +01ec / 64 / - / - / - |
| 4 | +02f0 / 2 / AOSSi_Free / - / - | +02ec / 2 / AOSSi_Free / - / - |
| 5 | +02f8 / 5 / SOHtoNs / - / - | +02f4 / 5 / SOHtoNs / - / - |
| 6 | +030c / 4 / memcpy / - / - | +0308 / 4 / memcpy / - / - |
| 7 | +031c / 11 / memcpy, AOSS_81401E80 / ['lbl_81697204', 0] / 'MELCO' | +0318 / 11 / memcpy, AOSS_81401E80 / ['s_manufacturer', 0] / 'MELCO' |
| 8 | +0348 / 4 / - / ['lbl_81698C84', 0] / - | +0344 / 4 / - / ['s_errorCode', 0] / - |
| 9 | +0358 / 42 / SOHtoNs, SOHtoNs, SOHtoNs, SOHtoNs, memcpy, memset, SOHtoNs, SOHtoNl / ['AOSS_810BDEF8', 0] / - | +0354 / 41 / SOHtoNs, SOHtoNs, SOHtoNs, SOHtoNs, memcpy, memset, SOHtoNs, SOHtoNl / - / - |
| 10 | +0400 / 2 / - / - / - | +03f8 / 2 / - / - / - |
| 11 | +0408 / 9 / SOSendTo / - / - | +0400 / 9 / SOSendTo / - / - |
| 12 | +042c / 6 / _restgpr_25 / - / - | +0424 / 6 / _restgpr_24 / - / - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |
| replace | 0:3 / 124 | 0:3 / 123 |
| replace | 7:8 / 11 | 7:8 / 11 |
| replace | 9:10 / 42 | 9:10 / 41 |
| replace | 12:13 / 6 | 12:13 / 6 |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| R000 | 0:14 | 0:16 | -2 | memset |
| R003 | 25:31 | 27:32 | +1 | SOHtoNl |
| R004 | 31:42 | 32:42 | +1 | AOSS_81401DC0 |
| R005 | 42:96 | 42:96 | +0 | AOSSi_Alloc |
| R008 | 105:110 | 105:109 | +1 | memcpy |
| R009 | 110:115 | 109:114 | +0 | memcpy |
| R015 | 203:208 | 202:207 | +0 | AOSS_81401E80 |
| R023 | 247:252 | 246:250 | +1 | SOHtoNl |

## AOSS_81401E80

Target 147; built 147; signed deficit 0.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 17 / _savegpr_21, AOSSi_Alloc / - / - | +0000 / 17 / _savegpr_21, AOSSi_Alloc / - / - |
| 1 | +0044 / 2 / - / - / - | +0044 / 2 / - / - / - |
| 2 | +004c / 5 / AOSSi_Alloc / - / - | +004c / 5 / AOSSi_Alloc / - / - |
| 3 | +0060 / 4 / AOSSi_Free / - / - | +0060 / 4 / AOSSi_Free / - / - |
| 4 | +0070 / 4 / - / - / - | +0070 / 4 / - / - / - |
| 5 | +0080 / 8 / - / - / - | +0080 / 8 / - / - / - |
| 6 | +00a0 / 8 / - / - / - | +00a0 / 8 / - / - / - |
| 7 | +00c0 / 1 / - / - / - | +00c0 / 1 / - / - / - |
| 8 | +00c4 / 3 / - / - / - | +00c4 / 3 / - / - / - |
| 9 | +00d0 / 3 / - / - / - | +00d0 / 3 / - / - / - |
| 10 | +00dc / 3 / - / - / - | +00dc / 3 / - / - / - |
| 11 | +00e8 / 2 / - / - / - | +00e8 / 2 / - / - / - |
| 12 | +00f0 / 3 / - / - / - | +00f0 / 3 / - / - / - |
| 13 | +00fc / 1 / - / - / - | +00fc / 1 / - / - / - |
| 14 | +0100 / 2 / - / - / - | +0100 / 2 / - / - / - |
| 15 | +0108 / 5 / - / - / - | +0108 / 5 / - / - / - |
| 16 | +011c / 36 / - / - / - | +011c / 36 / - / - / - |
| 17 | +01ac / 6 / - / - / - | +01ac / 6 / - / - / - |
| 18 | +01c4 / 8 / - / - / - | +01c4 / 8 / - / - / - |
| 19 | +01e4 / 15 / memcpy, memcpy, memcpy / - / - | +01e4 / 15 / memcpy, memcpy, memcpy / - / - |
| 20 | +0220 / 5 / AOSSi_Free, AOSSi_Free / - / - | +0220 / 5 / AOSSi_Free, AOSSi_Free / - / - |
| 21 | +0234 / 6 / _restgpr_21 / - / - | +0234 / 6 / _restgpr_21 / - / - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| - | Equal counts/opcode sequence | Operand registers still differ | 0 | - |

## Zi8ChangeWordCase

Target 44; built 44; signed deficit 0.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 14 / - / - / - | +0000 / 14 / - / - / - |
| 1 | +0038 / 8 / Zi8ChangeCharCase / - / - | +0038 / 8 / Zi8ChangeCharCase / - / - |
| 2 | +0058 / 3 / - / - / - | +0058 / 3 / - / - / - |
| 3 | +0064 / 2 / - / - / - | +0064 / 2 / - / - / - |
| 4 | +006c / 6 / Zi8ChangeCharCase / - / - | +006c / 6 / Zi8ChangeCharCase / - / - |
| 5 | +0084 / 3 / - / - / - | +0084 / 3 / - / - / - |
| 6 | +0090 / 8 / - / - / - | +0090 / 8 / - / - / - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| - | Equal counts/opcode sequence | Operand registers still differ | 0 | - |

## Zi8AlphaGetCandidates

Target 3946; built 3947; signed deficit -1.

| Block index | Target: offset / count / calls / data refs / strings | Build: offset / count / calls / data refs / strings |
| --- | --- | --- |
| 0 | +0000 / 95 / _savegpr_27 / - / - | +0000 / 94 / _savegpr_27 / - / - |
| 1 | +017c / 3 / - / - / - | +0178 / 3 / - / - / - |
| 2 | +0188 / 3 / - / - / - | +0184 / 3 / - / - / - |
| 3 | +0194 / 3 / - / - / - | +0190 / 3 / - / - / - |
| 4 | +01a0 / 3 / - / - / - | +019c / 3 / - / - / - |
| 5 | +01ac / 3 / - / - / - | +01a8 / 3 / - / - / - |
| 6 | +01b8 / 3 / - / - / - | +01b4 / 3 / - / - / - |
| 7 | +01c4 / 5 / - / - / - | +01c0 / 5 / - / - / - |
| 8 | +01d8 / 16 / - / - / - | +01d4 / 16 / - / - / - |
| 9 | +0218 / 4 / - / - / - | +0214 / 4 / - / - / - |
| 10 | +0228 / 1 / - / - / - | +0224 / 1 / - / - / - |
| 11 | +022c / 7 / - / - / - | +0228 / 7 / - / - / - |
| 12 | +0248 / 3 / - / - / - | +0244 / 3 / - / - / - |
| 13 | +0254 / 3 / - / - / - | +0250 / 3 / - / - / - |
| 14 | +0260 / 7 / - / - / - | +025c / 7 / - / - / - |
| 15 | +027c / 5 / - / - / - | +0278 / 5 / - / - / - |
| 16 | +0290 / 3 / - / - / - | +028c / 3 / - / - / - |
| 17 | +029c / 4 / - / - / - | +0298 / 4 / - / - / - |
| 18 | +02ac / 2 / - / - / - | +02a8 / 2 / - / - / - |
| 19 | +02b4 / 3 / - / - / - | +02b0 / 3 / - / - / - |
| 20 | +02c0 / 2 / - / - / - | +02bc / 2 / - / - / - |
| 21 | +02c8 / 3 / - / - / - | +02c4 / 3 / - / - / - |
| 22 | +02d4 / 3 / - / - / - | +02d0 / 3 / - / - / - |
| 23 | +02e0 / 3 / - / - / - | +02dc / 3 / - / - / - |
| 24 | +02ec / 3 / - / - / - | +02e8 / 3 / - / - / - |
| 25 | +02f8 / 3 / - / - / - | +02f4 / 3 / - / - / - |
| 26 | +0304 / 14 / - / - / - | +0300 / 14 / - / - / - |
| 27 | +033c / 6 / - / - / - | +0338 / 6 / - / - / - |
| 28 | +0354 / 12 / Zi8ChangeCharCase / - / - | +0350 / 12 / Zi8ChangeCharCase / - / - |
| 29 | +0384 / 1 / - / - / - | +0380 / 1 / - / - / - |
| 30 | +0388 / 3 / - / - / - | +0384 / 3 / - / - / - |
| 31 | +0394 / 4 / - / - / - | +0390 / 4 / - / - / - |
| 32 | +03a4 / 2 / - / - / - | +03a0 / 2 / - / - / - |
| 33 | +03ac / 2 / - / - / - | +03a8 / 2 / - / - / - |
| 34 | +03b4 / 3 / - / - / - | +03b0 / 3 / - / - / - |
| 35 | +03c0 / 3 / - / - / - | +03bc / 3 / - / - / - |
| 36 | +03cc / 3 / - / - / - | +03c8 / 3 / - / - / - |
| 37 | +03d8 / 3 / ZiprocessHighlightedW / - / - | +03d4 / 3 / ZiprocessHighlightedW / - / - |
| 38 | +03e4 / 3 / - / - / - | +03e0 / 3 / - / - / - |
| 39 | +03f0 / 3 / - / - / - | +03ec / 3 / - / - / - |
| 40 | +03fc / 3 / - / - / - | +03f8 / 3 / - / - / - |
| 41 | +0408 / 2 / - / - / - | +0404 / 2 / - / - / - |
| 42 | +0410 / 10 / Zi8GetTableCount / - / - | +040c / 9 / Zi8GetTableCount / - / - |
| 43 | +0438 / 3 / - / - / - | +0430 / 3 / - / - / - |
| 44 | +0444 / 2 / - / - / - | +043c / 2 / - / - / - |
| 45 | +044c / 3 / - / - / - | +0444 / 3 / - / - / - |
| 46 | +0458 / 3 / - / - / - | +0450 / 3 / - / - / - |
| 47 | +0464 / 5 / - / - / - | +045c / 5 / - / - / - |
| 48 | +0478 / 3 / - / - / - | +0470 / 3 / - / - / - |
| 49 | +0484 / 3 / - / - / - | +047c / 3 / - / - / - |
| 50 | +0490 / 3 / - / - / - | +0488 / 3 / - / - / - |
| 51 | +049c / 3 / - / - / - | +0494 / 3 / - / - / - |
| 52 | +04a8 / 6 / Zi8LangSupported / - / - | +04a0 / 6 / Zi8LangSupported / - / - |
| 53 | +04c0 / 7 / - / - / - | +04b8 / 7 / - / - / - |
| 54 | +04dc / 3 / - / - / - | +04d4 / 3 / - / - / - |
| 55 | +04e8 / 3 / - / - / - | +04e0 / 3 / - / - / - |
| 56 | +04f4 / 4 / - / - / - | +04ec / 4 / - / - / - |
| 57 | +0504 / 4 / - / - / - | +04fc / 4 / - / - / - |
| 58 | +0514 / 25 / Zi8MatchROMdata / - / - | +050c / 25 / Zi8MatchROMdata / - / - |
| 59 | +0578 / 3 / - / - / - | +0570 / 3 / - / - / - |
| 60 | +0584 / 23 / Zi8MatchROMdata / - / - | +057c / 23 / Zi8MatchROMdata / - / - |
| 61 | +05e0 / 6 / - / - / - | +05d8 / 6 / - / - / - |
| 62 | +05f8 / 2 / - / - / - | +05f0 / 2 / - / - / - |
| 63 | +0600 / 3 / - / - / - | +05f8 / 3 / - / - / - |
| 64 | +060c / 3 / - / - / - | +0604 / 3 / - / - / - |
| 65 | +0618 / 3 / - / - / - | +0610 / 3 / - / - / - |
| 66 | +0624 / 3 / - / - / - | +061c / 3 / - / - / - |
| 67 | +0630 / 7 / - / - / - | +0628 / 7 / - / - / - |
| 68 | +064c / 7 / - / - / - | +0644 / 7 / - / - / - |
| 69 | +0668 / 7 / - / - / - | +0660 / 7 / - / - / - |
| 70 | +0684 / 3 / - / - / - | +067c / 3 / - / - / - |
| 71 | +0690 / 2 / - / - / - | +0688 / 2 / - / - / - |
| 72 | +0698 / 3 / - / - / - | +0690 / 3 / - / - / - |
| 73 | +06a4 / 3 / - / - / - | +069c / 3 / - / - / - |
| 74 | +06b0 / 3 / - / - / - | +06a8 / 3 / - / - / - |
| 75 | +06bc / 9 / Zi8IsAlphaPunct / - / - | +06b4 / 10 / Zi8IsAlphaPunct / - / - |
| 76 | +06e0 / 4 / - / - / - | +06dc / 4 / - / - / - |
| 77 | +06f0 / 4 / - / - / - | +06ec / 4 / - / - / - |
| 78 | +0700 / 4 / - / - / - | +06fc / 4 / - / - / - |
| 79 | +0710 / 3 / - / - / - | +070c / 3 / - / - / - |
| 80 | +071c / 7 / - / - / - | +0718 / 7 / - / - / - |
| 81 | +0738 / 2 / - / - / - | +0734 / 2 / - / - / - |
| 82 | +0740 / 7 / - / - / - | +073c / 7 / - / - / - |
| 83 | +075c / 3 / - / - / - | +0758 / 3 / - / - / - |
| 84 | +0768 / 8 / - / - / - | +0764 / 8 / - / - / - |
| 85 | +0788 / 9 / Zi8GetTableCount / - / - | +0784 / 9 / Zi8GetTableCount / - / - |
| 86 | +07ac / 3 / - / - / - | +07a8 / 3 / - / - / - |
| 87 | +07b8 / 9 / Zi8GetTableCount / - / - | +07b4 / 9 / Zi8GetTableCount / - / - |
| 88 | +07dc / 3 / - / - / - | +07d8 / 3 / - / - / - |
| 89 | +07e8 / 5 / - / - / - | +07e4 / 5 / - / - / - |
| 90 | +07fc / 4 / - / - / - | +07f8 / 4 / - / - / - |
| 91 | +080c / 4 / - / - / - | +0808 / 4 / - / - / - |
| 92 | +081c / 4 / - / - / - | +0818 / 4 / - / - / - |
| 93 | +082c / 7 / - / - / - | +0828 / 7 / - / - / - |
| 94 | +0848 / 4 / - / - / - | +0844 / 4 / - / - / - |
| 95 | +0858 / 3 / - / - / - | +0854 / 3 / - / - / - |
| 96 | +0864 / 2 / - / - / - | +0860 / 2 / - / - / - |
| 97 | +086c / 3 / - / - / - | +0868 / 3 / - / - / - |
| 98 | +0878 / 2 / - / - / - | +0874 / 2 / - / - / - |
| 99 | +0880 / 3 / - / - / - | +087c / 3 / - / - / - |
| 100 | +088c / 9 / Zi8GetTableCount / - / - | +0888 / 9 / Zi8GetTableCount / - / - |
| 101 | +08b0 / 2 / - / - / - | +08ac / 2 / - / - / - |
| 102 | +08b8 / 9 / Zi8GetTableCount / - / - | +08b4 / 9 / Zi8GetTableCount / - / - |
| 103 | +08dc / 3 / - / - / - | +08d8 / 3 / - / - / - |
| 104 | +08e8 / 4 / - / - / - | +08e4 / 4 / - / - / - |
| 105 | +08f8 / 5 / Zi8InitDupWordBuf / - / - | +08f4 / 7 / Zi8InitDupWordBuf / - / - |
| 106 | +090c / 3 / - / - / - | +0910 / 3 / - / - / - |
| 107 | +0918 / 3 / - / - / - | +091c / 3 / - / - / - |
| 108 | +0924 / 4 / - / - / - | +0928 / 4 / - / - / - |
| 109 | +0934 / 3 / - / - / - | +0938 / 3 / - / - / - |
| 110 | +0940 / 7 / - / - / - | +0944 / 7 / - / - / - |
| 111 | +095c / 9 / Zi8IsAlphaPunct / - / - | +0960 / 9 / Zi8IsAlphaPunct / - / - |
| 112 | +0980 / 3 / - / - / - | +0984 / 3 / - / - / - |
| 113 | +098c / 11 / - / - / - | +0990 / 11 / - / - / - |
| 114 | +09b8 / 10 / - / - / - | +09bc / 10 / - / - / - |
| 115 | +09e0 / 5 / - / - / - | +09e4 / 5 / - / - / - |
| 116 | +09f4 / 13 / - / - / - | +09f8 / 13 / - / - / - |
| 117 | +0a28 / 2 / - / - / - | +0a2c / 2 / - / - / - |
| 118 | +0a30 / 4 / - / - / - | +0a34 / 4 / - / - / - |
| 119 | +0a40 / 3 / - / - / - | +0a44 / 3 / - / - / - |
| 120 | +0a4c / 3 / - / - / - | +0a50 / 3 / - / - / - |
| 121 | +0a58 / 2 / - / - / - | +0a5c / 2 / - / - / - |
| 122 | +0a60 / 4 / - / - / - | +0a64 / 4 / - / - / - |
| 123 | +0a70 / 1 / - / - / - | +0a74 / 1 / - / - / - |
| 124 | +0a74 / 2 / - / - / - | +0a78 / 2 / - / - / - |
| 125 | +0a7c / 1 / - / - / - | +0a80 / 1 / - / - / - |
| 126 | +0a80 / 1 / - / - / - | +0a84 / 1 / - / - / - |
| 127 | +0a84 / 3 / - / - / - | +0a88 / 3 / - / - / - |
| 128 | +0a90 / 3 / - / - / - | +0a94 / 3 / - / - / - |
| 129 | +0a9c / 7 / - / - / - | +0aa0 / 7 / - / - / - |
| 130 | +0ab8 / 5 / - / - / - | +0abc / 5 / - / - / - |
| 131 | +0acc / 3 / - / - / - | +0ad0 / 3 / - / - / - |
| 132 | +0ad8 / 2 / - / - / - | +0adc / 2 / - / - / - |
| 133 | +0ae0 / 3 / - / - / - | +0ae4 / 3 / - / - / - |
| 134 | +0aec / 3 / - / - / - | +0af0 / 3 / - / - / - |
| 135 | +0af8 / 8 / Zi8IsDupWordW / - / - | +0afc / 8 / Zi8IsDupWordW / - / - |
| 136 | +0b18 / 3 / - / - / - | +0b1c / 3 / - / - / - |
| 137 | +0b24 / 4 / - / - / - | +0b28 / 4 / - / - / - |
| 138 | +0b34 / 5 / - / - / - | +0b38 / 5 / - / - / - |
| 139 | +0b48 / 3 / - / - / - | +0b4c / 3 / - / - / - |
| 140 | +0b54 / 2 / - / - / - | +0b58 / 2 / - / - / - |
| 141 | +0b5c / 7 / - / - / - | +0b60 / 7 / - / - / - |
| 142 | +0b78 / 5 / - / - / - | +0b7c / 5 / - / - / - |
| 143 | +0b8c / 1 / - / - / - | +0b90 / 1 / - / - / - |
| 144 | +0b90 / 9 / - / - / - | +0b94 / 9 / - / - / - |
| 145 | +0bb4 / 3 / - / - / - | +0bb8 / 3 / - / - / - |
| 146 | +0bc0 / 5 / Zi8ChangeWordCase / - / - | +0bc4 / 5 / Zi8ChangeWordCase / - / - |
| 147 | +0bd4 / 4 / Zi8ChangeWordCase / - / - | +0bd8 / 4 / Zi8ChangeWordCase / - / - |
| 148 | +0be4 / 14 / - / - / - | +0be8 / 14 / - / - / - |
| 149 | +0c1c / 4 / - / - / - | +0c20 / 4 / - / - / - |
| 150 | +0c2c / 3 / - / - / - | +0c30 / 3 / - / - / - |
| 151 | +0c38 / 3 / - / - / - | +0c3c / 3 / - / - / - |
| 152 | +0c44 / 3 / - / - / - | +0c48 / 3 / - / - / - |
| 153 | +0c50 / 22 / - / - / - | +0c54 / 22 / - / - / - |
| 154 | +0ca8 / 3 / - / - / - | +0cac / 3 / - / - / - |
| 155 | +0cb4 / 5 / - / - / - | +0cb8 / 5 / - / - / - |
| 156 | +0cc8 / 10 / ZiIsLetterHyphen / - / - | +0ccc / 10 / ZiIsLetterHyphen / - / - |
| 157 | +0cf0 / 5 / - / - / - | +0cf4 / 5 / - / - / - |
| 158 | +0d04 / 5 / - / - / - | +0d08 / 5 / - / - / - |
| 159 | +0d18 / 2 / - / - / - | +0d1c / 2 / - / - / - |
| 160 | +0d20 / 3 / - / - / - | +0d24 / 3 / - / - / - |
| 161 | +0d2c / 5 / - / - / - | +0d30 / 5 / - / - / - |
| 162 | +0d40 / 10 / ZiIsLetterHyphen / - / - | +0d44 / 10 / ZiIsLetterHyphen / - / - |
| 163 | +0d68 / 5 / - / - / - | +0d6c / 5 / - / - / - |
| 164 | +0d7c / 4 / - / - / - | +0d80 / 4 / - / - / - |
| 165 | +0d8c / 10 / ZiIsLetterHyphen / - / - | +0d90 / 11 / ZiIsLetterHyphen / - / - |
| 166 | +0db4 / 3 / - / - / - | +0dbc / 3 / - / - / - |
| 167 | +0dc0 / 4 / - / - / - | +0dc8 / 4 / - / - / - |
| 168 | +0dd0 / 3 / - / - / - | +0dd8 / 3 / - / - / - |
| 169 | +0ddc / 4 / - / - / - | +0de4 / 4 / - / - / - |
| 170 | +0dec / 3 / - / - / - | +0df4 / 3 / - / - / - |
| 171 | +0df8 / 5 / - / - / - | +0e00 / 5 / - / - / - |
| 172 | +0e0c / 3 / - / - / - | +0e14 / 3 / - / - / - |
| 173 | +0e18 / 16 / Zi8GetTableCount / - / - | +0e20 / 15 / Zi8GetTableCount / - / - |
| 174 | +0e58 / 3 / - / - / - | +0e5c / 3 / - / - / - |
| 175 | +0e64 / 3 / - / - / - | +0e68 / 3 / - / - / - |
| 176 | +0e70 / 3 / - / - / - | +0e74 / 3 / - / - / - |
| 177 | +0e7c / 3 / - / - / - | +0e80 / 3 / - / - / - |
| 178 | +0e88 / 3 / - / - / - | +0e8c / 3 / - / - / - |
| 179 | +0e94 / 3 / - / - / - | +0e98 / 3 / - / - / - |
| 180 | +0ea0 / 3 / - / - / - | +0ea4 / 3 / - / - / - |
| 181 | +0eac / 2 / - / - / - | +0eb0 / 2 / - / - / - |
| 182 | +0eb4 / 3 / - / - / - | +0eb8 / 3 / - / - / - |
| 183 | +0ec0 / 5 / - / - / - | +0ec4 / 5 / - / - / - |
| 184 | +0ed4 / 4 / - / - / - | +0ed8 / 4 / - / - / - |
| 185 | +0ee4 / 3 / - / - / - | +0ee8 / 3 / - / - / - |
| 186 | +0ef0 / 2 / - / - / - | +0ef4 / 2 / - / - / - |
| 187 | +0ef8 / 5 / - / - / - | +0efc / 5 / - / - / - |
| 188 | +0f0c / 2 / - / - / - | +0f10 / 2 / - / - / - |
| 189 | +0f14 / 2 / - / - / - | +0f18 / 2 / - / - / - |
| 190 | +0f1c / 13 / - / - / - | +0f20 / 13 / - / - / - |
| 191 | +0f50 / 11 / Zi8ConvertWC2Key / - / - | +0f54 / 11 / Zi8ConvertWC2Key / - / - |
| 192 | +0f7c / 1 / - / - / - | +0f80 / 1 / - / - / - |
| 193 | +0f80 / 3 / - / - / - | +0f84 / 3 / - / - / - |
| 194 | +0f8c / 21 / - / - / - | +0f90 / 21 / - / - / - |
| 195 | +0fe0 / 2 / - / - / - | +0fe4 / 2 / - / - / - |
| 196 | +0fe8 / 13 / - / - / - | +0fec / 13 / - / - / - |
| 197 | +101c / 11 / Zi8ConvertWC2Key / - / - | +1020 / 11 / Zi8ConvertWC2Key / - / - |
| 198 | +1048 / 1 / - / - / - | +104c / 1 / - / - / - |
| 199 | +104c / 3 / - / - / - | +1050 / 3 / - / - / - |
| 200 | +1058 / 20 / - / - / - | +105c / 20 / - / - / - |
| 201 | +10a8 / 3 / - / - / - | +10ac / 3 / - / - / - |
| 202 | +10b4 / 3 / - / - / - | +10b8 / 3 / - / - / - |
| 203 | +10c0 / 2 / - / - / - | +10c4 / 2 / - / - / - |
| 204 | +10c8 / 12 / Zi8GetTableCount / - / - | +10cc / 12 / Zi8GetTableCount / - / - |
| 205 | +10f8 / 3 / - / - / - | +10fc / 3 / - / - / - |
| 206 | +1104 / 3 / - / - / - | +1108 / 3 / - / - / - |
| 207 | +1110 / 7 / - / - / - | +1114 / 7 / - / - / - |
| 208 | +112c / 7 / - / - / - | +1130 / 7 / - / - / - |
| 209 | +1148 / 12 / Zi8ConvertWC2Key / - / - | +114c / 11 / Zi8ConvertWC2Key / - / - |
| 210 | +1178 / 3 / - / - / - | +1178 / 3 / - / - / - |
| 211 | +1184 / 5 / - / - / - | +1184 / 5 / - / - / - |
| 212 | +1198 / 3 / - / - / - | +1198 / 3 / - / - / - |
| 213 | +11a4 / 4 / - / - / - | +11a4 / 4 / - / - / - |
| 214 | +11b4 / 6 / - / - / - | +11b4 / 6 / - / - / - |
| 215 | +11cc / 1 / - / - / - | +11cc / 1 / - / - / - |
| 216 | +11d0 / 2 / - / - / - | +11d0 / 2 / - / - / - |
| 217 | +11d8 / 1 / - / - / - | +11d8 / 1 / - / - / - |
| 218 | +11dc / 2 / - / - / - | +11dc / 2 / - / - / - |
| 219 | +11e4 / 1 / - / - / - | +11e4 / 1 / - / - / - |
| 220 | +11e8 / 2 / - / - / - | +11e8 / 2 / - / - / - |
| 221 | +11f0 / 1 / - / - / - | +11f0 / 1 / - / - / - |
| 222 | +11f4 / 2 / - / - / - | +11f4 / 2 / - / - / - |
| 223 | +11fc / 2 / - / - / - | +11fc / 2 / - / - / - |
| 224 | +1204 / 3 / - / - / - | +1204 / 3 / - / - / - |
| 225 | +1210 / 3 / - / - / - | +1210 / 3 / - / - / - |
| 226 | +121c / 1 / - / - / - | +121c / 1 / - / - / - |
| 227 | +1220 / 2 / - / - / - | +1220 / 2 / - / - / - |
| 228 | +1228 / 12 / Zi8GetTableCount / - / - | +1228 / 11 / Zi8GetTableCount / - / - |
| 229 | +1258 / 3 / - / - / - | +1254 / 3 / - / - / - |
| 230 | +1264 / 2 / - / - / - | +1260 / 2 / - / - / - |
| 231 | +126c / 5 / - / - / - | +1268 / 5 / - / - / - |
| 232 | +1280 / 3 / - / - / - | +127c / 3 / - / - / - |
| 233 | +128c / 5 / - / - / - | +1288 / 5 / - / - / - |
| 234 | +12a0 / 1 / - / - / - | +129c / 1 / - / - / - |
| 235 | +12a4 / 1 / - / - / - | +12a0 / 1 / - / - / - |
| 236 | +12a8 / 3 / - / - / - | +12a4 / 3 / - / - / - |
| 237 | +12b4 / 5 / - / - / - | +12b0 / 5 / - / - / - |
| 238 | +12c8 / 2 / - / - / - | +12c4 / 2 / - / - / - |
| 239 | +12d0 / 3 / - / - / - | +12cc / 3 / - / - / - |
| 240 | +12dc / 3 / - / - / - | +12d8 / 3 / - / - / - |
| 241 | +12e8 / 3 / - / - / - | +12e4 / 3 / - / - / - |
| 242 | +12f4 / 3 / - / - / - | +12f0 / 3 / - / - / - |
| 243 | +1300 / 3 / - / - / - | +12fc / 3 / - / - / - |
| 244 | +130c / 4 / - / - / - | +1308 / 4 / - / - / - |
| 245 | +131c / 3 / - / - / - | +1318 / 3 / - / - / - |
| 246 | +1328 / 12 / Zi8getKeyLayout / - / - | +1324 / 12 / Zi8getKeyLayout / - / - |
| 247 | +1358 / 3 / - / - / - | +1354 / 3 / - / - / - |
| 248 | +1364 / 2 / - / - / - | +1360 / 2 / - / - / - |
| 249 | +136c / 12 / Zi8GetTableCount / - / - | +1368 / 12 / Zi8GetTableCount / - / - |
| 250 | +139c / 2 / - / - / - | +1398 / 2 / - / - / - |
| 251 | +13a4 / 3 / - / - / - | +13a0 / 3 / - / - / - |
| 252 | +13b0 / 7 / Zi8GetTableAddress / - / - | +13ac / 7 / Zi8GetTableAddress / - / - |
| 253 | +13cc / 3 / - / - / - | +13c8 / 3 / - / - / - |
| 254 | +13d8 / 3 / - / - / - | +13d4 / 3 / - / - / - |
| 255 | +13e4 / 3 / - / - / - | +13e0 / 3 / - / - / - |
| 256 | +13f0 / 7 / - / - / - | +13ec / 7 / - / - / - |
| 257 | +140c / 4 / Zi8Memset / - / - | +1408 / 4 / Zi8Memset / - / - |
| 258 | +141c / 4 / - / - / - | +1418 / 4 / - / - / - |
| 259 | +142c / 7 / - / - / - | +1428 / 7 / - / - / - |
| 260 | +1448 / 3 / - / - / - | +1444 / 3 / - / - / - |
| 261 | +1454 / 1 / - / - / - | +1450 / 1 / - / - / - |
| 262 | +1458 / 3 / - / - / - | +1454 / 3 / - / - / - |
| 263 | +1464 / 2 / - / - / - | +1460 / 2 / - / - / - |
| 264 | +146c / 3 / - / - / - | +1468 / 3 / - / - / - |
| 265 | +1478 / 3 / - / - / - | +1474 / 3 / - / - / - |
| 266 | +1484 / 1 / - / - / - | +1480 / 1 / - / - / - |
| 267 | +1488 / 2 / - / - / - | +1484 / 2 / - / - / - |
| 268 | +1490 / 2 / - / - / - | +148c / 2 / - / - / - |
| 269 | +1498 / 1 / - / - / - | +1494 / 1 / - / - / - |
| 270 | +149c / 5 / - / - / - | +1498 / 5 / - / - / - |
| 271 | +14b0 / 1 / - / - / - | +14ac / 1 / - / - / - |
| 272 | +14b4 / 2 / - / - / - | +14b0 / 2 / - / - / - |
| 273 | +14bc / 2 / - / - / - | +14b8 / 2 / - / - / - |
| 274 | +14c4 / 1 / - / - / - | +14c0 / 1 / - / - / - |
| 275 | +14c8 / 2 / - / - / - | +14c4 / 2 / - / - / - |
| 276 | +14d0 / 1 / - / - / - | +14cc / 1 / - / - / - |
| 277 | +14d4 / 2 / - / - / - | +14d0 / 2 / - / - / - |
| 278 | +14dc / 1 / - / - / - | +14d8 / 1 / - / - / - |
| 279 | +14e0 / 3 / - / - / - | +14dc / 3 / - / - / - |
| 280 | +14ec / 9 / Zi8GetTableCount / - / - | +14e8 / 9 / Zi8GetTableCount / - / - |
| 281 | +1510 / 4 / - / - / - | +150c / 4 / - / - / - |
| 282 | +1520 / 4 / - / - / - | +151c / 4 / - / - / - |
| 283 | +1530 / 10 / Zi8getKeyLayout / - / - | +152c / 10 / Zi8getKeyLayout / - / - |
| 284 | +1558 / 3 / - / - / - | +1554 / 3 / - / - / - |
| 285 | +1564 / 3 / - / - / - | +1560 / 3 / - / - / - |
| 286 | +1570 / 3 / - / - / - | +156c / 3 / - / - / - |
| 287 | +157c / 3 / - / - / - | +1578 / 3 / - / - / - |
| 288 | +1588 / 3 / - / - / - | +1584 / 3 / - / - / - |
| 289 | +1594 / 7 / - / - / - | +1590 / 7 / - / - / - |
| 290 | +15b0 / 3 / - / - / - | +15ac / 3 / - / - / - |
| 291 | +15bc / 3 / - / - / - | +15b8 / 3 / - / - / - |
| 292 | +15c8 / 4 / - / - / - | +15c4 / 4 / - / - / - |
| 293 | +15d8 / 3 / - / - / - | +15d4 / 3 / - / - / - |
| 294 | +15e4 / 3 / - / - / - | +15e0 / 3 / - / - / - |
| 295 | +15f0 / 7 / - / - / - | +15ec / 7 / - / - / - |
| 296 | +160c / 3 / - / - / - | +1608 / 3 / - / - / - |
| 297 | +1618 / 3 / - / - / - | +1614 / 3 / - / - / - |
| 298 | +1624 / 5 / - / - / - | +1620 / 5 / - / - / - |
| 299 | +1638 / 3 / - / - / - | +1634 / 3 / - / - / - |
| 300 | +1644 / 4 / - / - / - | +1640 / 4 / - / - / - |
| 301 | +1654 / 3 / - / - / - | +1650 / 3 / - / - / - |
| 302 | +1660 / 3 / - / - / - | +165c / 3 / - / - / - |
| 303 | +166c / 3 / - / - / - | +1668 / 3 / - / - / - |
| 304 | +1678 / 7 / - / - / - | +1674 / 7 / - / - / - |
| 305 | +1694 / 3 / - / - / - | +1690 / 3 / - / - / - |
| 306 | +16a0 / 4 / - / - / - | +169c / 4 / - / - / - |
| 307 | +16b0 / 2 / - / - / - | +16ac / 2 / - / - / - |
| 308 | +16b8 / 2 / - / - / - | +16b4 / 2 / - / - / - |
| 309 | +16c0 / 3 / - / - / - | +16bc / 3 / - / - / - |
| 310 | +16cc / 4 / - / - / - | +16c8 / 4 / - / - / - |
| 311 | +16dc / 1 / - / - / - | +16d8 / 1 / - / - / - |
| 312 | +16e0 / 4 / - / - / - | +16dc / 4 / - / - / - |
| 313 | +16f0 / 3 / - / - / - | +16ec / 3 / - / - / - |
| 314 | +16fc / 1 / - / - / - | +16f8 / 1 / - / - / - |
| 315 | +1700 / 3 / - / - / - | +16fc / 3 / - / - / - |
| 316 | +170c / 4 / - / - / - | +1708 / 4 / - / - / - |
| 317 | +171c / 4 / - / - / - | +1718 / 4 / - / - / - |
| 318 | +172c / 3 / - / - / - | +1728 / 3 / - / - / - |
| 319 | +1738 / 3 / - / - / - | +1734 / 3 / - / - / - |
| 320 | +1744 / 3 / - / - / - | +1740 / 3 / - / - / - |
| 321 | +1750 / 4 / - / - / - | +174c / 4 / - / - / - |
| 322 | +1760 / 4 / - / - / - | +175c / 4 / - / - / - |
| 323 | +1770 / 3 / - / - / - | +176c / 3 / - / - / - |
| 324 | +177c / 5 / - / - / - | +1778 / 5 / - / - / - |
| 325 | +1790 / 3 / - / - / - | +178c / 3 / - / - / - |
| 326 | +179c / 4 / - / - / - | +1798 / 4 / - / - / - |
| 327 | +17ac / 4 / - / - / - | +17a8 / 4 / - / - / - |
| 328 | +17bc / 4 / - / - / - | +17b8 / 4 / - / - / - |
| 329 | +17cc / 4 / - / - / - | +17c8 / 4 / - / - / - |
| 330 | +17dc / 3 / - / - / - | +17d8 / 3 / - / - / - |
| 331 | +17e8 / 1 / - / - / - | +17e4 / 1 / - / - / - |
| 332 | +17ec / 3 / - / - / - | +17e8 / 3 / - / - / - |
| 333 | +17f8 / 3 / - / - / - | +17f4 / 3 / - / - / - |
| 334 | +1804 / 27 / - / - / - | +1800 / 27 / - / - / - |
| 335 | +1870 / 3 / - / - / - | +186c / 3 / - / - / - |
| 336 | +187c / 6 / - / - / - | +1878 / 6 / - / - / - |
| 337 | +1894 / 7 / - / - / - | +1890 / 7 / - / - / - |
| 338 | +18b0 / 6 / - / ['jumptable_8166AA58', 0] / - | +18ac / 6 / - / ['@1527', 0] / - |
| 339 | +18c8 / 2 / - / - / - | +18c4 / 2 / - / - / - |
| 340 | +18d0 / 3 / - / - / - | +18cc / 3 / - / - / - |
| 341 | +18dc / 3 / - / - / - | +18d8 / 3 / - / - / - |
| 342 | +18e8 / 3 / - / - / - | +18e4 / 3 / - / - / - |
| 343 | +18f4 / 3 / - / - / - | +18f0 / 3 / - / - / - |
| 344 | +1900 / 5 / - / - / - | +18fc / 5 / - / - / - |
| 345 | +1914 / 5 / - / - / - | +1910 / 5 / - / - / - |
| 346 | +1928 / 7 / - / - / - | +1924 / 7 / - / - / - |
| 347 | +1944 / 3 / - / - / - | +1940 / 3 / - / - / - |
| 348 | +1950 / 3 / - / - / - | +194c / 3 / - / - / - |
| 349 | +195c / 23 / Zi8MatchROMdata / - / - | +1958 / 23 / Zi8MatchROMdata / - / - |
| 350 | +19b8 / 3 / - / - / - | +19b4 / 3 / - / - / - |
| 351 | +19c4 / 3 / - / - / - | +19c0 / 3 / - / - / - |
| 352 | +19d0 / 6 / - / - / - | +19cc / 6 / - / - / - |
| 353 | +19e8 / 3 / - / - / - | +19e4 / 3 / - / - / - |
| 354 | +19f4 / 23 / Zi8MatchROMdata / - / - | +19f0 / 23 / Zi8MatchROMdata / - / - |
| 355 | +1a50 / 20 / Zi8MatchROMdata / - / - | +1a4c / 20 / Zi8MatchROMdata / - / - |
| 356 | +1aa0 / 3 / - / - / - | +1a9c / 3 / - / - / - |
| 357 | +1aac / 4 / - / - / - | +1aa8 / 4 / - / - / - |
| 358 | +1abc / 2 / - / - / - | +1ab8 / 2 / - / - / - |
| 359 | +1ac4 / 3 / - / - / - | +1ac0 / 3 / - / - / - |
| 360 | +1ad0 / 4 / - / - / - | +1acc / 4 / - / - / - |
| 361 | +1ae0 / 3 / - / - / - | +1adc / 3 / - / - / - |
| 362 | +1aec / 3 / - / - / - | +1ae8 / 3 / - / - / - |
| 363 | +1af8 / 3 / - / - / - | +1af4 / 3 / - / - / - |
| 364 | +1b04 / 11 / - / - / - | +1b00 / 12 / - / - / - |
| 365 | +1b30 / 3 / - / - / - | +1b30 / 3 / - / - / - |
| 366 | +1b3c / 3 / - / - / - | +1b3c / 3 / - / - / - |
| 367 | +1b48 / 4 / - / - / - | +1b48 / 4 / - / - / - |
| 368 | +1b58 / 3 / - / - / - | +1b58 / 3 / - / - / - |
| 369 | +1b64 / 11 / Zi8ITspecialExclusion / - / - | +1b64 / 11 / Zi8ITspecialExclusion / - / - |
| 370 | +1b90 / 3 / - / - / - | +1b90 / 3 / - / - / - |
| 371 | +1b9c / 3 / - / - / - | +1b9c / 3 / - / - / - |
| 372 | +1ba8 / 12 / Zi8_814659E8 / - / - | +1ba8 / 11 / Zi8_814659E8 / - / - |
| 373 | +1bd8 / 3 / - / - / - | +1bd4 / 3 / - / - / - |
| 374 | +1be4 / 8 / Zi8IsVowel / - / - | +1be0 / 8 / Zi8IsVowel / - / - |
| 375 | +1c04 / 2 / - / - / - | +1c00 / 2 / - / - / - |
| 376 | +1c0c / 3 / - / - / - | +1c08 / 3 / - / - / - |
| 377 | +1c18 / 11 / - / - / - | +1c14 / 11 / - / - / - |
| 378 | +1c44 / 1 / - / - / - | +1c40 / 1 / - / - / - |
| 379 | +1c48 / 3 / - / - / - | +1c44 / 3 / - / - / - |
| 380 | +1c54 / 3 / - / - / - | +1c50 / 3 / - / - / - |
| 381 | +1c60 / 3 / - / - / - | +1c5c / 3 / - / - / - |
| 382 | +1c6c / 3 / - / - / - | +1c68 / 3 / - / - / - |
| 383 | +1c78 / 3 / - / - / - | +1c74 / 3 / - / - / - |
| 384 | +1c84 / 3 / - / - / - | +1c80 / 3 / - / - / - |
| 385 | +1c90 / 3 / - / - / - | +1c8c / 3 / - / - / - |
| 386 | +1c9c / 3 / - / - / - | +1c98 / 3 / - / - / - |
| 387 | +1ca8 / 3 / - / - / - | +1ca4 / 3 / - / - / - |
| 388 | +1cb4 / 3 / - / - / - | +1cb0 / 3 / - / - / - |
| 389 | +1cc0 / 7 / Zi8ITspecialExclusion / - / - | +1cbc / 7 / Zi8ITspecialExclusion / - / - |
| 390 | +1cdc / 3 / - / - / - | +1cd8 / 3 / - / - / - |
| 391 | +1ce8 / 3 / - / - / - | +1ce4 / 3 / - / - / - |
| 392 | +1cf4 / 7 / Zi8_814659E8 / - / - | +1cf0 / 7 / Zi8_814659E8 / - / - |
| 393 | +1d10 / 3 / - / - / - | +1d0c / 3 / - / - / - |
| 394 | +1d1c / 6 / Zi8IsVowel / - / - | +1d18 / 6 / Zi8IsVowel / - / - |
| 395 | +1d34 / 2 / - / - / - | +1d30 / 2 / - / - / - |
| 396 | +1d3c / 3 / - / - / - | +1d38 / 3 / - / - / - |
| 397 | +1d48 / 8 / - / - / - | +1d44 / 8 / - / - / - |
| 398 | +1d68 / 3 / - / - / - | +1d64 / 3 / - / - / - |
| 399 | +1d74 / 5 / - / - / - | +1d70 / 5 / - / - / - |
| 400 | +1d88 / 3 / - / - / - | +1d84 / 3 / - / - / - |
| 401 | +1d94 / 2 / - / - / - | +1d90 / 2 / - / - / - |
| 402 | +1d9c / 6 / Zi8IsZicorpSignature / - / - | +1d98 / 7 / Zi8IsZicorpSignature / - / - |
| 403 | +1db4 / 3 / - / - / - | +1db4 / 3 / - / - / - |
| 404 | +1dc0 / 19 / Zi8MatchPUDdata / - / - | +1dc0 / 19 / Zi8MatchPUDdata / - / - |
| 405 | +1e0c / 26 / Zi8MatchUWDdata / - / - | +1e0c / 25 / Zi8MatchUWDdata / - / - |
| 406 | +1e74 / 3 / - / - / - | +1e70 / 3 / - / - / - |
| 407 | +1e80 / 3 / - / - / - | +1e7c / 3 / - / - / - |
| 408 | +1e8c / 6 / - / - / - | +1e88 / 6 / - / - / - |
| 409 | +1ea4 / 3 / - / - / - | +1ea0 / 3 / - / - / - |
| 410 | +1eb0 / 19 / Zi8MatchOEMdata / - / - | +1eac / 19 / Zi8MatchOEMdata / - / - |
| 411 | +1efc / 6 / - / - / - | +1ef8 / 6 / - / - / - |
| 412 | +1f14 / 6 / - / - / - | +1f10 / 6 / - / - / - |
| 413 | +1f2c / 3 / - / - / - | +1f28 / 3 / - / - / - |
| 414 | +1f38 / 3 / - / - / - | +1f34 / 3 / - / - / - |
| 415 | +1f44 / 3 / - / - / - | +1f40 / 3 / - / - / - |
| 416 | +1f50 / 2 / - / - / - | +1f4c / 2 / - / - / - |
| 417 | +1f58 / 9 / - / - / - | +1f54 / 9 / - / - / - |
| 418 | +1f7c / 1 / - / - / - | +1f78 / 1 / - / - / - |
| 419 | +1f80 / 4 / - / - / - | +1f7c / 4 / - / - / - |
| 420 | +1f90 / 4 / - / - / - | +1f8c / 4 / - / - / - |
| 421 | +1fa0 / 3 / - / - / - | +1f9c / 3 / - / - / - |
| 422 | +1fac / 2 / - / - / - | +1fa8 / 2 / - / - / - |
| 423 | +1fb4 / 9 / - / - / - | +1fb0 / 9 / - / - / - |
| 424 | +1fd8 / 1 / - / - / - | +1fd4 / 1 / - / - / - |
| 425 | +1fdc / 3 / - / - / - | +1fd8 / 3 / - / - / - |
| 426 | +1fe8 / 3 / - / - / - | +1fe4 / 3 / - / - / - |
| 427 | +1ff4 / 3 / - / - / - | +1ff0 / 3 / - / - / - |
| 428 | +2000 / 9 / - / - / - | +1ffc / 9 / - / - / - |
| 429 | +2024 / 5 / - / - / - | +2020 / 5 / - / - / - |
| 430 | +2038 / 2 / - / - / - | +2034 / 2 / - / - / - |
| 431 | +2040 / 8 / - / - / - | +203c / 8 / - / - / - |
| 432 | +2060 / 8 / - / - / - | +205c / 8 / - / - / - |
| 433 | +2080 / 3 / - / - / - | +207c / 3 / - / - / - |
| 434 | +208c / 3 / - / - / - | +2088 / 3 / - / - / - |
| 435 | +2098 / 5 / - / - / - | +2094 / 5 / - / - / - |
| 436 | +20ac / 7 / - / - / - | +20a8 / 7 / - / - / - |
| 437 | +20c8 / 3 / - / - / - | +20c4 / 3 / - / - / - |
| 438 | +20d4 / 5 / - / - / - | +20d0 / 5 / - / - / - |
| 439 | +20e8 / 3 / - / - / - | +20e4 / 3 / - / - / - |
| 440 | +20f4 / 5 / - / - / - | +20f0 / 5 / - / - / - |
| 441 | +2108 / 3 / - / - / - | +2104 / 3 / - / - / - |
| 442 | +2114 / 3 / - / - / - | +2110 / 3 / - / - / - |
| 443 | +2120 / 3 / - / - / - | +211c / 3 / - / - / - |
| 444 | +212c / 3 / - / - / - | +2128 / 3 / - / - / - |
| 445 | +2138 / 4 / - / - / - | +2134 / 4 / - / - / - |
| 446 | +2148 / 3 / - / - / - | +2144 / 3 / - / - / - |
| 447 | +2154 / 6 / - / - / - | +2150 / 6 / - / - / - |
| 448 | +216c / 5 / - / - / - | +2168 / 5 / - / - / - |
| 449 | +2180 / 6 / - / - / - | +217c / 6 / - / - / - |
| 450 | +2198 / 1 / - / - / - | +2194 / 2 / - / - / - |
| 451 | +219c / 2 / - / - / - | +219c / 2 / - / - / - |
| 452 | +21a4 / 2 / - / - / - | +21a4 / 2 / - / - / - |
| 453 | +21ac / 1 / - / - / - | +21ac / 12 / Zi8getKeyLayout / - / - |
| 454 | +21b0 / 13 / Zi8getKeyLayout / - / - | +21dc / 2 / - / - / - |
| 455 | +21e4 / 2 / - / - / - | +21e4 / 7 / - / - / - |
| 456 | +21ec / 7 / - / - / - | +2200 / 3 / - / - / - |
| 457 | +2208 / 3 / - / - / - | +220c / 3 / - / - / - |
| 458 | +2214 / 3 / - / - / - | +2218 / 3 / - / - / - |
| 459 | +2220 / 3 / - / - / - | +2224 / 3 / - / - / - |
| 460 | +222c / 3 / - / - / - | +2230 / 4 / - / - / - |
| 461 | +2238 / 4 / - / - / - | +2240 / 3 / - / - / - |
| 462 | +2248 / 3 / - / - / - | +224c / 3 / - / - / - |
| 463 | +2254 / 3 / - / - / - | +2258 / 7 / - / - / - |
| 464 | +2260 / 7 / - / - / - | +2274 / 5 / - / - / - |
| 465 | +227c / 5 / - / - / - | +2288 / 3 / - / - / - |
| 466 | +2290 / 3 / - / - / - | +2294 / 3 / - / - / - |
| 467 | +229c / 3 / - / - / - | +22a0 / 6 / - / - / - |
| 468 | +22a8 / 6 / - / - / - | +22b8 / 3 / - / - / - |
| 469 | +22c0 / 3 / - / - / - | +22c4 / 6 / - / - / - |
| 470 | +22cc / 6 / - / - / - | +22dc / 2 / - / - / - |
| 471 | +22e4 / 1 / - / - / - | +22e4 / 2 / - / - / - |
| 472 | +22e8 / 2 / - / - / - | +22ec / 2 / - / - / - |
| 473 | +22f0 / 2 / - / - / - | +22f4 / 12 / Zi8getKeyLayout / - / - |
| 474 | +22f8 / 1 / - / - / - | +2324 / 2 / - / - / - |
| 475 | +22fc / 12 / Zi8getKeyLayout / - / - | +232c / 5 / - / - / - |
| 476 | +232c / 2 / - / - / - | +2340 / 4 / - / - / - |
| 477 | +2334 / 5 / - / - / - | +2350 / 3 / - / - / - |
| 478 | +2348 / 4 / - / - / - | +235c / 3 / - / - / - |
| 479 | +2358 / 3 / - / - / - | +2368 / 3 / - / - / - |
| 480 | +2364 / 3 / - / - / - | +2374 / 3 / - / - / - |
| 481 | +2370 / 3 / - / - / - | +2380 / 8 / Zi8ITspecialExclusion / - / - |
| 482 | +237c / 3 / - / - / - | +23a0 / 1 / - / - / - |
| 483 | +2388 / 8 / Zi8ITspecialExclusion / - / - | +23a4 / 3 / - / - / - |
| 484 | +23a8 / 1 / - / - / - | +23b0 / 7 / Zi8_814659E8 / - / - |
| 485 | +23ac / 3 / - / - / - | +23cc / 1 / - / - / - |
| 486 | +23b8 / 7 / Zi8_814659E8 / - / - | +23d0 / 7 / Zi8IsVowel / - / - |
| 487 | +23d4 / 1 / - / - / - | +23ec / 3 / - / - / - |
| 488 | +23d8 / 7 / Zi8IsVowel / - / - | +23f8 / 3 / - / - / - |
| 489 | +23f4 / 3 / - / - / - | +2404 / 3 / - / - / - |
| 490 | +2400 / 3 / - / - / - | +2410 / 3 / - / - / - |
| 491 | +240c / 3 / - / - / - | +241c / 3 / - / - / - |
| 492 | +2418 / 3 / - / - / - | +2428 / 3 / - / - / - |
| 493 | +2424 / 3 / - / - / - | +2434 / 7 / - / - / - |
| 494 | +2430 / 3 / - / - / - | +2450 / 3 / - / - / - |
| 495 | +243c / 7 / - / - / - | +245c / 4 / - / - / - |
| 496 | +2458 / 3 / - / - / - | +246c / 6 / - / - / - |
| 497 | +2464 / 4 / - / - / - | +2484 / 13 / Zi8DeTokenization / - / - |
| 498 | +2474 / 6 / - / - / - | +24b8 / 5 / - / - / - |
| 499 | +248c / 13 / Zi8DeTokenization / - / - | +24cc / 6 / - / - / - |
| 500 | +24c0 / 6 / - / - / - | +24e4 / 6 / - / - / - |
| 501 | +24d8 / 6 / - / - / - | +24fc / 7 / - / - / - |
| 502 | +24f0 / 6 / - / - / - | +2518 / 3 / - / - / - |
| 503 | +2508 / 7 / - / - / - | +2524 / 8 / Zi8ZHCheckSpelling / - / - |
| 504 | +2524 / 3 / - / - / - | +2544 / 3 / - / - / - |
| 505 | +2530 / 8 / Zi8ZHCheckSpelling / - / - | +2550 / 3 / - / - / - |
| 506 | +2550 / 3 / - / - / - | +255c / 3 / - / - / - |
| 507 | +255c / 3 / - / - / - | +2568 / 6 / Zi8ChangeWordCase / - / - |
| 508 | +2568 / 3 / - / - / - | +2580 / 3 / - / - / - |
| 509 | +2574 / 6 / Zi8ChangeWordCase / - / - | +258c / 6 / - / - / - |
| 510 | +258c / 3 / - / - / - | +25a4 / 8 / - / - / - |
| 511 | +2598 / 6 / - / - / - | +25c4 / 6 / - / - / - |
| 512 | +25b0 / 8 / - / - / - | +25dc / 13 / Zi8IsDupWordW / - / - |
| 513 | +25d0 / 6 / - / - / - | +2610 / 3 / - / - / - |
| 514 | +25e8 / 12 / Zi8IsDupWordW / - / - | +261c / 4 / - / - / - |
| 515 | +2618 / 3 / - / - / - | +262c / 1 / - / - / - |
| 516 | +2624 / 4 / - / - / - | +2630 / 3 / - / - / - |
| 517 | +2634 / 1 / - / - / - | +263c / 3 / - / - / - |
| 518 | +2638 / 3 / - / - / - | +2648 / 5 / - / - / - |
| 519 | +2644 / 3 / - / - / - | +265c / 5 / - / - / - |
| 520 | +2650 / 5 / - / - / - | +2670 / 3 / - / - / - |
| 521 | +2664 / 5 / - / - / - | +267c / 1 / - / - / - |
| 522 | +2678 / 3 / - / - / - | +2680 / 2 / - / - / - |
| 523 | +2684 / 1 / - / - / - | +2688 / 1 / - / - / - |
| 524 | +2688 / 2 / - / - / - | +268c / 2 / - / - / - |
| 525 | +2690 / 1 / - / - / - | +2694 / 1 / - / - / - |
| 526 | +2694 / 2 / - / - / - | +2698 / 9 / - / - / - |
| 527 | +269c / 1 / - / - / - | +26bc / 6 / - / - / - |
| 528 | +26a0 / 9 / - / - / - | +26d4 / 9 / - / - / - |
| 529 | +26c4 / 6 / - / - / - | +26f8 / 2 / - / - / - |
| 530 | +26dc / 7 / - / - / - | +2700 / 7 / - / - / - |
| 531 | +26f8 / 9 / - / - / - | +271c / 3 / - / - / - |
| 532 | +271c / 2 / - / - / - | +2728 / 3 / - / - / - |
| 533 | +2724 / 1 / - / - / - | +2734 / 3 / - / - / - |
| 534 | +2728 / 3 / - / - / - | +2740 / 14 / Zi8ConvertWC2UC / - / - |
| 535 | +2734 / 3 / - / - / - | +2778 / 4 / - / - / - |
| 536 | +2740 / 3 / - / - / - | +2788 / 1 / - / - / - |
| 537 | +274c / 14 / Zi8ConvertWC2UC / - / - | +278c / 3 / - / - / - |
| 538 | +2784 / 4 / - / - / - | +2798 / 9 / - / - / - |
| 539 | +2794 / 1 / - / - / - | +27bc / 3 / - / - / - |
| 540 | +2798 / 3 / - / - / - | +27c8 / 4 / - / - / - |
| 541 | +27a4 / 9 / - / - / - | +27d8 / 4 / - / - / - |
| 542 | +27c8 / 3 / - / - / - | +27e8 / 6 / - / - / - |
| 543 | +27d4 / 4 / - / - / - | +2800 / 12 / - / - / - |
| 544 | +27e4 / 4 / - / - / - | +2830 / 1 / - / - / - |
| 545 | +27f4 / 6 / - / - / - | +2834 / 3 / - / - / - |
| 546 | +280c / 12 / - / - / - | +2840 / 3 / - / - / - |
| 547 | +283c / 1 / - / - / - | +284c / 3 / - / - / - |
| 548 | +2840 / 3 / - / - / - | +2858 / 3 / - / - / - |
| 549 | +284c / 3 / - / - / - | +2864 / 6 / - / - / - |
| 550 | +2858 / 4 / - / - / - | +287c / 5 / - / - / - |
| 551 | +2868 / 3 / - / - / - | +2890 / 6 / - / - / - |
| 552 | +2874 / 3 / - / - / - | +28a8 / 5 / - / - / - |
| 553 | +2880 / 6 / - / - / - | +28bc / 7 / - / - / - |
| 554 | +2898 / 5 / - / - / - | +28d8 / 1 / - / - / - |
| 555 | +28ac / 6 / - / - / - | +28dc / 3 / - / - / - |
| 556 | +28c4 / 5 / - / - / - | +28e8 / 2 / - / - / - |
| 557 | +28d8 / 6 / - / - / - | +28f0 / 1 / - / - / - |
| 558 | +28f0 / 1 / - / - / - | +28f4 / 3 / - / - / - |
| 559 | +28f4 / 3 / - / - / - | +2900 / 8 / - / - / - |
| 560 | +2900 / 2 / - / - / - | +2920 / 3 / - / - / - |
| 561 | +2908 / 8 / - / - / - | +292c / 3 / - / - / - |
| 562 | +2928 / 1 / - / - / - | +2938 / 3 / - / - / - |
| 563 | +292c / 3 / - / - / - | +2944 / 3 / - / - / - |
| 564 | +2938 / 3 / - / - / - | +2950 / 6 / Zi8WCharCount / - / - |
| 565 | +2944 / 3 / - / - / - | +2968 / 3 / - / - / - |
| 566 | +2950 / 3 / - / - / - | +2974 / 3 / - / - / - |
| 567 | +295c / 3 / - / - / - | +2980 / 3 / - / - / - |
| 568 | +2968 / 6 / Zi8WCharCount / - / - | +298c / 3 / - / - / - |
| 569 | +2980 / 3 / - / - / - | +2998 / 3 / - / - / - |
| 570 | +298c / 3 / - / - / - | +29a4 / 3 / - / - / - |
| 571 | +2998 / 3 / - / - / - | +29b0 / 3 / - / - / - |
| 572 | +29a4 / 3 / - / - / - | +29bc / 3 / - / - / - |
| 573 | +29b0 / 3 / - / - / - | +29c8 / 3 / - / - / - |
| 574 | +29bc / 3 / - / - / - | +29d4 / 2 / - / - / - |
| 575 | +29c8 / 3 / - / - / - | +29dc / 3 / - / - / - |
| 576 | +29d4 / 3 / - / - / - | +29e8 / 5 / - / - / - |
| 577 | +29e0 / 3 / - / - / - | +29fc / 3 / - / - / - |
| 578 | +29ec / 2 / - / - / - | +2a08 / 3 / - / - / - |
| 579 | +29f4 / 3 / - / - / - | +2a14 / 3 / - / - / - |
| 580 | +2a00 / 5 / - / - / - | +2a20 / 3 / - / - / - |
| 581 | +2a14 / 3 / - / - / - | +2a2c / 5 / - / - / - |
| 582 | +2a20 / 3 / - / - / - | +2a40 / 3 / - / - / - |
| 583 | +2a2c / 3 / - / - / - | +2a4c / 3 / - / - / - |
| 584 | +2a38 / 2 / - / - / - | +2a58 / 3 / - / - / - |
| 585 | +2a40 / 8 / - / - / - | +2a64 / 3 / - / - / - |
| 586 | +2a60 / 3 / - / - / - | +2a70 / 2 / - / - / - |
| 587 | +2a6c / 2 / - / - / - | +2a78 / 8 / - / - / - |
| 588 | +2a74 / 8 / - / - / - | +2a98 / 3 / - / - / - |
| 589 | +2a94 / 3 / - / - / - | +2aa4 / 2 / - / - / - |
| 590 | +2aa0 / 7 / - / - / - | +2aac / 8 / - / - / - |
| 591 | +2abc / 3 / - / - / - | +2acc / 3 / - / - / - |
| 592 | +2ac8 / 5 / - / - / - | +2ad8 / 6 / - / - / - |
| 593 | +2adc / 3 / - / - / - | +2af0 / 3 / - / - / - |
| 594 | +2ae8 / 3 / - / - / - | +2afc / 3 / - / - / - |
| 595 | +2af4 / 3 / - / - / - | +2b08 / 4 / - / - / - |
| 596 | +2b00 / 2 / - / - / - | +2b18 / 3 / - / - / - |
| 597 | +2b08 / 3 / - / - / - | +2b24 / 4 / - / - / - |
| 598 | +2b14 / 3 / - / - / - | +2b34 / 3 / - / - / - |
| 599 | +2b20 / 4 / - / - / - | +2b40 / 4 / - / - / - |
| 600 | +2b30 / 3 / - / - / - | +2b50 / 3 / - / - / - |
| 601 | +2b3c / 4 / - / - / - | +2b5c / 4 / - / - / - |
| 602 | +2b4c / 3 / - / - / - | +2b6c / 3 / - / - / - |
| 603 | +2b58 / 4 / - / - / - | +2b78 / 3 / - / - / - |
| 604 | +2b68 / 3 / - / - / - | +2b84 / 3 / - / - / - |
| 605 | +2b74 / 4 / - / - / - | +2b90 / 2 / - / - / - |
| 606 | +2b84 / 3 / - / - / - | +2b98 / 6 / - / - / - |
| 607 | +2b90 / 3 / - / - / - | +2bb0 / 3 / - / - / - |
| 608 | +2b9c / 3 / - / - / - | +2bbc / 6 / - / - / - |
| 609 | +2ba8 / 2 / - / - / - | +2bd4 / 3 / - / - / - |
| 610 | +2bb0 / 6 / - / - / - | +2be0 / 3 / - / - / - |
| 611 | +2bc8 / 3 / - / - / - | +2bec / 4 / - / - / - |
| 612 | +2bd4 / 6 / - / - / - | +2bfc / 3 / - / - / - |
| 613 | +2bec / 3 / - / - / - | +2c08 / 4 / - / - / - |
| 614 | +2bf8 / 3 / - / - / - | +2c18 / 3 / - / - / - |
| 615 | +2c04 / 4 / - / - / - | +2c24 / 4 / - / - / - |
| 616 | +2c14 / 3 / - / - / - | +2c34 / 3 / - / - / - |
| 617 | +2c20 / 4 / - / - / - | +2c40 / 4 / - / - / - |
| 618 | +2c30 / 3 / - / - / - | +2c50 / 5 / - / - / - |
| 619 | +2c3c / 4 / - / - / - | +2c64 / 3 / - / - / - |
| 620 | +2c4c / 3 / - / - / - | +2c70 / 3 / - / - / - |
| 621 | +2c58 / 4 / - / - / - | +2c7c / 3 / - / - / - |
| 622 | +2c68 / 5 / - / - / - | +2c88 / 4 / - / - / - |
| 623 | +2c7c / 3 / - / - / - | +2c98 / 2 / - / - / - |
| 624 | +2c88 / 3 / - / - / - | +2ca0 / 6 / - / - / - |
| 625 | +2c94 / 3 / - / - / - | +2cb8 / 3 / - / - / - |
| 626 | +2ca0 / 4 / - / - / - | +2cc4 / 4 / - / - / - |
| 627 | +2cb0 / 2 / - / - / - | +2cd4 / 2 / - / - / - |
| 628 | +2cb8 / 6 / - / - / - | +2cdc / 6 / - / - / - |
| 629 | +2cd0 / 3 / - / - / - | +2cf4 / 3 / - / - / - |
| 630 | +2cdc / 4 / - / - / - | +2d00 / 4 / - / - / - |
| 631 | +2cec / 2 / - / - / - | +2d10 / 3 / - / - / - |
| 632 | +2cf4 / 6 / - / - / - | +2d1c / 3 / - / - / - |
| 633 | +2d0c / 3 / - / - / - | +2d28 / 4 / - / - / - |
| 634 | +2d18 / 4 / - / - / - | +2d38 / 3 / - / - / - |
| 635 | +2d28 / 3 / - / - / - | +2d44 / 4 / - / - / - |
| 636 | +2d34 / 3 / - / - / - | +2d54 / 3 / - / - / - |
| 637 | +2d40 / 4 / - / - / - | +2d60 / 4 / - / - / - |
| 638 | +2d50 / 3 / - / - / - | +2d70 / 3 / - / - / - |
| 639 | +2d5c / 4 / - / - / - | +2d7c / 4 / - / - / - |
| 640 | +2d6c / 3 / - / - / - | +2d8c / 5 / - / - / - |
| 641 | +2d78 / 4 / - / - / - | +2da0 / 3 / - / - / - |
| 642 | +2d88 / 3 / - / - / - | +2dac / 3 / - / - / - |
| 643 | +2d94 / 4 / - / - / - | +2db8 / 3 / - / - / - |
| 644 | +2da4 / 5 / - / - / - | +2dc4 / 2 / - / - / - |
| 645 | +2db8 / 3 / - / - / - | +2dcc / 6 / - / - / - |
| 646 | +2dc4 / 3 / - / - / - | +2de4 / 3 / - / - / - |
| 647 | +2dd0 / 3 / - / - / - | +2df0 / 2 / - / - / - |
| 648 | +2ddc / 2 / - / - / - | +2df8 / 7 / - / - / - |
| 649 | +2de4 / 6 / - / - / - | +2e14 / 3 / - / - / - |
| 650 | +2dfc / 3 / - / - / - | +2e20 / 2 / - / - / - |
| 651 | +2e08 / 2 / - / - / - | +2e28 / 2 / - / - / - |
| 652 | +2e10 / 7 / - / - / - | +2e30 / 11 / Zi8ConvertWC2UC / - / - |
| 653 | +2e2c / 3 / - / - / - | +2e5c / 5 / - / - / - |
| 654 | +2e38 / 2 / - / - / - | +2e70 / 7 / - / - / - |
| 655 | +2e40 / 2 / - / - / - | +2e8c / 3 / - / - / - |
| 656 | +2e48 / 10 / Zi8ConvertWC2UC / - / - | +2e98 / 13 / - / - / - |
| 657 | +2e70 / 5 / - / - / - | +2ecc / 7 / - / - / - |
| 658 | +2e84 / 7 / - / - / - | +2ee8 / 5 / - / - / - |
| 659 | +2ea0 / 3 / - / - / - | +2efc / 1 / - / - / - |
| 660 | +2eac / 13 / - / - / - | +2f00 / 11 / - / - / - |
| 661 | +2ee0 / 7 / - / - / - | +2f2c / 7 / - / - / - |
| 662 | +2efc / 5 / - / - / - | +2f48 / 3 / - / - / - |
| 663 | +2f10 / 1 / - / - / - | +2f54 / 8 / - / - / - |
| 664 | +2f14 / 11 / - / - / - | +2f74 / 3 / - / - / - |
| 665 | +2f40 / 6 / - / - / - | +2f80 / 3 / - / - / - |
| 666 | +2f58 / 3 / - / - / - | +2f8c / 3 / - / - / - |
| 667 | +2f64 / 8 / - / - / - | +2f98 / 4 / - / - / - |
| 668 | +2f84 / 3 / - / - / - | +2fa8 / 3 / - / - / - |
| 669 | +2f90 / 3 / - / - / - | +2fb4 / 2 / - / - / - |
| 670 | +2f9c / 3 / - / - / - | +2fbc / 6 / - / - / - |
| 671 | +2fa8 / 4 / - / - / - | +2fd4 / 3 / - / - / - |
| 672 | +2fb8 / 3 / - / - / - | +2fe0 / 10 / - / - / - |
| 673 | +2fc4 / 2 / - / - / - | +3008 / 2 / - / - / - |
| 674 | +2fcc / 6 / - / - / - | +3010 / 6 / - / - / - |
| 675 | +2fe4 / 3 / - / - / - | +3028 / 3 / - / - / - |
| 676 | +2ff0 / 10 / - / - / - | +3034 / 8 / - / - / - |
| 677 | +3018 / 2 / - / - / - | +3054 / 3 / - / - / - |
| 678 | +3020 / 6 / - / - / - | +3060 / 3 / - / - / - |
| 679 | +3038 / 3 / - / - / - | +306c / 3 / - / - / - |
| 680 | +3044 / 7 / - / - / - | +3078 / 4 / - / - / - |
| 681 | +3060 / 3 / - / - / - | +3088 / 3 / - / - / - |
| 682 | +306c / 3 / - / - / - | +3094 / 3 / - / - / - |
| 683 | +3078 / 4 / - / - / - | +30a0 / 3 / - / - / - |
| 684 | +3088 / 3 / - / - / - | +30ac / 3 / - / - / - |
| 685 | +3094 / 3 / - / - / - | +30b8 / 10 / Zi8GetTableCount / - / - |
| 686 | +30a0 / 3 / - / - / - | +30e0 / 4 / - / - / - |
| 687 | +30ac / 3 / - / - / - | +30f0 / 4 / - / - / - |
| 688 | +30b8 / 10 / Zi8GetTableCount / - / - | +3100 / 11 / Zi8getKeyLayout / - / - |
| 689 | +30e0 / 4 / - / - / - | +312c / 2 / - / - / - |
| 690 | +30f0 / 4 / - / - / - | +3134 / 3 / - / - / - |
| 691 | +3100 / 11 / Zi8getKeyLayout / - / - | +3140 / 3 / - / - / - |
| 692 | +312c / 2 / - / - / - | +314c / 3 / - / - / - |
| 693 | +3134 / 3 / - / - / - | +3158 / 5 / - / - / - |
| 694 | +3140 / 3 / - / - / - | +316c / 4 / - / - / - |
| 695 | +314c / 3 / - / - / - | +317c / 10 / - / - / - |
| 696 | +3158 / 5 / - / - / - | +31a4 / 3 / - / - / - |
| 697 | +316c / 4 / - / - / - | +31b0 / 4 / - / - / - |
| 698 | +317c / 3 / - / - / - | +31c0 / 2 / - / - / - |
| 699 | +3188 / 4 / - / - / - | +31c8 / 5 / - / - / - |
| 700 | +3198 / 2 / - / - / - | +31dc / 3 / - / - / - |
| 701 | +31a0 / 5 / - / - / - | +31e8 / 2 / - / - / - |
| 702 | +31b4 / 8 / - / - / - | +31f0 / 3 / - / - / - |
| 703 | +31d4 / 3 / - / - / - | +31fc / 23 / - / - / - |
| 704 | +31e0 / 2 / - / - / - | +3258 / 11 / - / - / - |
| 705 | +31e8 / 3 / - / - / - | +3284 / 5 / - / - / - |
| 706 | +31f4 / 23 / - / - / - | +3298 / 2 / - / - / - |
| 707 | +3250 / 11 / - / - / - | +32a0 / 9 / - / - / - |
| 708 | +327c / 5 / - / - / - | +32c4 / 4 / - / - / - |
| 709 | +3290 / 2 / - / - / - | +32d4 / 3 / - / - / - |
| 710 | +3298 / 5 / - / - / - | +32e0 / 3 / - / - / - |
| 711 | +32ac / 5 / - / - / - | +32ec / 3 / - / - / - |
| 712 | +32c0 / 4 / - / - / - | +32f8 / 3 / - / - / - |
| 713 | +32d0 / 3 / - / - / - | +3304 / 3 / - / - / - |
| 714 | +32dc / 3 / - / - / - | +3310 / 3 / - / - / - |
| 715 | +32e8 / 3 / - / - / - | +331c / 7 / - / - / - |
| 716 | +32f4 / 3 / - / - / - | +3338 / 5 / - / - / - |
| 717 | +3300 / 3 / - / - / - | +334c / 6 / - / - / - |
| 718 | +330c / 3 / - / - / - | +3364 / 3 / - / - / - |
| 719 | +3318 / 7 / - / - / - | +3370 / 3 / - / - / - |
| 720 | +3334 / 5 / - / - / - | +337c / 3 / - / - / - |
| 721 | +3348 / 6 / - / - / - | +3388 / 3 / - / - / - |
| 722 | +3360 / 3 / - / - / - | +3394 / 3 / - / - / - |
| 723 | +336c / 3 / - / - / - | +33a0 / 3 / - / - / - |
| 724 | +3378 / 3 / - / - / - | +33ac / 3 / - / - / - |
| 725 | +3384 / 3 / - / - / - | +33b8 / 7 / - / - / - |
| 726 | +3390 / 3 / - / - / - | +33d4 / 5 / - / - / - |
| 727 | +339c / 3 / - / - / - | +33e8 / 5 / - / - / - |
| 728 | +33a8 / 3 / - / - / - | +33fc / 9 / Zi8IsAlphaPunct / - / - |
| 729 | +33b4 / 7 / - / - / - | +3420 / 3 / - / - / - |
| 730 | +33d0 / 5 / - / - / - | +342c / 3 / - / - / - |
| 731 | +33e4 / 5 / - / - / - | +3438 / 5 / - / - / - |
| 732 | +33f8 / 9 / Zi8IsAlphaPunct / - / - | +344c / 3 / - / - / - |
| 733 | +341c / 3 / - / - / - | +3458 / 3 / - / - / - |
| 734 | +3428 / 7 / - / - / - | +3464 / 3 / - / - / - |
| 735 | +3444 / 3 / - / - / - | +3470 / 2 / - / - / - |
| 736 | +3450 / 3 / - / - / - | +3478 / 3 / - / - / - |
| 737 | +345c / 9 / - / - / - | +3484 / 28 / - / - / - |
| 738 | +3480 / 19 / - / - / - | +34f4 / 7 / - / - / - |
| 739 | +34cc / 3 / - / - / - | +3510 / 3 / - / - / - |
| 740 | +34d8 / 3 / - / - / - | +351c / 7 / - / - / - |
| 741 | +34e4 / 5 / - / - / - | +3538 / 3 / - / - / - |
| 742 | +34f8 / 3 / - / - / - | +3544 / 2 / - / - / - |
| 743 | +3504 / 3 / - / - / - | +354c / 2 / - / - / - |
| 744 | +3510 / 3 / - / - / - | +3554 / 3 / - / - / - |
| 745 | +351c / 2 / - / - / - | +3560 / 3 / - / - / - |
| 746 | +3524 / 3 / - / - / - | +356c / 3 / - / - / - |
| 747 | +3530 / 28 / - / - / - | +3578 / 5 / - / - / - |
| 748 | +35a0 / 7 / - / - / - | +358c / 3 / - / - / - |
| 749 | +35bc / 3 / - / - / - | +3598 / 5 / - / - / - |
| 750 | +35c8 / 7 / - / - / - | +35ac / 3 / - / - / - |
| 751 | +35e4 / 3 / - / - / - | +35b8 / 3 / - / - / - |
| 752 | +35f0 / 2 / - / - / - | +35c4 / 1 / - / - / - |
| 753 | +35f8 / 2 / - / - / - | +35c8 / 3 / - / - / - |
| 754 | +3600 / 3 / - / - / - | +35d4 / 7 / - / - / - |
| 755 | +360c / 3 / - / - / - | +35f0 / 3 / - / - / - |
| 756 | +3618 / 3 / - / - / - | +35fc / 3 / - / - / - |
| 757 | +3624 / 5 / - / - / - | +3608 / 9 / - / - / - |
| 758 | +3638 / 3 / - / - / - | +362c / 19 / - / - / - |
| 759 | +3644 / 5 / - / - / - | +3678 / 3 / - / - / - |
| 760 | +3658 / 3 / - / - / - | +3684 / 7 / - / - / - |
| 761 | +3664 / 3 / - / - / - | +36a0 / 4 / - / - / - |
| 762 | +3670 / 3 / - / - / - | +36b0 / 8 / ZiIsLetterHyphen / - / - |
| 763 | +367c / 7 / - / - / - | +36d0 / 3 / - / - / - |
| 764 | +3698 / 4 / - / - / - | +36dc / 11 / ZiIsLetterHyphen / - / - |
| 765 | +36a8 / 8 / ZiIsLetterHyphen / - / - | +3708 / 3 / - / - / - |
| 766 | +36c8 / 3 / - / - / - | +3714 / 3 / - / - / - |
| 767 | +36d4 / 10 / ZiIsLetterHyphen / - / - | +3720 / 10 / ZiIsLetterHyphen / - / - |
| 768 | +36fc / 3 / - / - / - | +3748 / 10 / Zi8GetTableCount / - / - |
| 769 | +3708 / 3 / - / - / - | +3770 / 7 / - / - / - |
| 770 | +3714 / 10 / ZiIsLetterHyphen / - / - | +378c / 3 / - / - / - |
| 771 | +373c / 10 / Zi8GetTableCount / - / - | +3798 / 18 / - / - / - |
| 772 | +3764 / 7 / - / - / - | +37e0 / 3 / - / - / - |
| 773 | +3780 / 3 / - / - / - | +37ec / 14 / - / - / - |
| 774 | +378c / 18 / - / - / - | +3824 / 9 / Zi8IsAlphaPunct / - / - |
| 775 | +37d4 / 3 / - / - / - | +3848 / 12 / - / - / - |
| 776 | +37e0 / 14 / - / - / - | +3878 / 9 / - / - / - |
| 777 | +3818 / 8 / Zi8IsAlphaPunct / - / - | +389c / 3 / - / - / - |
| 778 | +3838 / 13 / - / - / - | +38a8 / 7 / - / - / - |
| 779 | +386c / 9 / - / - / - | +38c4 / 4 / - / - / - |
| 780 | +3890 / 3 / - / - / - | +38d4 / 3 / - / - / - |
| 781 | +389c / 7 / - / - / - | +38e0 / 3 / - / - / - |
| 782 | +38b8 / 4 / - / - / - | +38ec / 3 / - / - / - |
| 783 | +38c8 / 3 / - / - / - | +38f8 / 3 / - / - / - |
| 784 | +38d4 / 3 / - / - / - | +3904 / 9 / Zi8GetTableCount / - / - |
| 785 | +38e0 / 3 / - / - / - | +3928 / 2 / - / - / - |
| 786 | +38ec / 3 / - / - / - | +3930 / 6 / - / - / - |
| 787 | +38f8 / 10 / Zi8GetTableCount / - / - | +3948 / 8 / Zi8IsAlphaPunct / - / - |
| 788 | +3920 / 2 / - / - / - | +3968 / 12 / - / - / - |
| 789 | +3928 / 6 / - / - / - | +3998 / 9 / - / - / - |
| 790 | +3940 / 8 / Zi8IsAlphaPunct / - / - | +39bc / 3 / - / - / - |
| 791 | +3960 / 13 / - / - / - | +39c8 / 3 / - / - / - |
| 792 | +3994 / 9 / - / - / - | +39d4 / 3 / - / - / - |
| 793 | +39b8 / 3 / - / - / - | +39e0 / 3 / - / - / - |
| 794 | +39c4 / 3 / - / - / - | +39ec / 3 / - / - / - |
| 795 | +39d0 / 3 / - / - / - | +39f8 / 5 / - / - / - |
| 796 | +39dc / 3 / - / - / - | +3a0c / 9 / Zi8IsAlphaPunct / - / - |
| 797 | +39e8 / 3 / - / - / - | +3a30 / 3 / - / - / - |
| 798 | +39f4 / 5 / - / - / - | +3a3c / 3 / - / - / - |
| 799 | +3a08 / 10 / Zi8IsAlphaPunct / - / - | +3a48 / 3 / - / - / - |
| 800 | +3a30 / 3 / - / - / - | +3a54 / 10 / Zi8IsAlphaPunct / - / - |
| 801 | +3a3c / 3 / - / - / - | +3a7c / 7 / - / - / - |
| 802 | +3a48 / 3 / - / - / - | +3a98 / 3 / - / - / - |
| 803 | +3a54 / 9 / Zi8IsAlphaPunct / - / - | +3aa4 / 3 / - / - / - |
| 804 | +3a78 / 7 / - / - / - | +3ab0 / 5 / - / - / - |
| 805 | +3a94 / 3 / - / - / - | +3ac4 / 7 / - / - / - |
| 806 | +3aa0 / 3 / - / - / - | +3ae0 / 7 / - / - / - |
| 807 | +3aac / 5 / - / - / - | +3afc / 5 / - / - / - |
| 808 | +3ac0 / 7 / - / - / - | +3b10 / 4 / - / - / - |
| 809 | +3adc / 7 / - / - / - | +3b20 / 2 / - / - / - |
| 810 | +3af8 / 5 / - / - / - | +3b28 / 8 / - / - / - |
| 811 | +3b0c / 3 / - / - / - | +3b48 / 3 / - / - / - |
| 812 | +3b18 / 3 / - / - / - | +3b54 / 3 / - / - / - |
| 813 | +3b24 / 8 / - / - / - | +3b60 / 6 / - / - / - |
| 814 | +3b44 / 3 / - / - / - | +3b78 / 3 / - / - / - |
| 815 | +3b50 / 3 / - / - / - | +3b84 / 3 / - / - / - |
| 816 | +3b5c / 6 / - / - / - | +3b90 / 6 / - / - / - |
| 817 | +3b74 / 3 / - / - / - | +3ba8 / 2 / - / - / - |
| 818 | +3b80 / 3 / - / - / - | +3bb0 / 6 / - / - / - |
| 819 | +3b8c / 6 / - / - / - | +3bc8 / 4 / - / - / - |
| 820 | +3ba4 / 2 / - / - / - | +3bd8 / 3 / - / - / - |
| 821 | +3bac / 6 / - / - / - | +3be4 / 2 / - / - / - |
| 822 | +3bc4 / 4 / - / - / - | +3bec / 3 / - / - / - |
| 823 | +3bd4 / 3 / - / - / - | +3bf8 / 3 / - / - / - |
| 824 | +3be0 / 2 / - / - / - | +3c04 / 4 / - / - / - |
| 825 | +3be8 / 3 / - / - / - | +3c14 / 2 / - / - / - |
| 826 | +3bf4 / 3 / - / - / - | +3c1c / 3 / - / - / - |
| 827 | +3c00 / 4 / - / - / - | +3c28 / 3 / - / - / - |
| 828 | +3c10 / 2 / - / - / - | +3c34 / 4 / - / - / - |
| 829 | +3c18 / 3 / - / - / - | +3c44 / 2 / - / - / - |
| 830 | +3c24 / 3 / - / - / - | +3c4c / 3 / - / - / - |
| 831 | +3c30 / 4 / - / - / - | +3c58 / 5 / - / - / - |
| 832 | +3c40 / 2 / - / - / - | +3c6c / 9 / Zi8ConvertUC2WC / - / - |
| 833 | +3c48 / 3 / - / - / - | +3c90 / 4 / - / - / - |
| 834 | +3c54 / 5 / - / - / - | +3ca0 / 4 / - / - / - |
| 835 | +3c68 / 9 / Zi8ConvertUC2WC / - / - | +3cb0 / 1 / - / - / - |
| 836 | +3c8c / 4 / - / - / - | +3cb4 / 2 / - / - / - |
| 837 | +3c9c / 4 / - / - / - | +3cbc / 5 / Zi8SetHighlightedWordW / - / - |
| 838 | +3cac / 1 / - / - / - | +3cd0 / 3 / - / - / - |
| 839 | +3cb0 / 2 / - / - / - | +3cdc / 4 / - / - / - |
| 840 | +3cb8 / 5 / Zi8SetHighlightedWordW / - / - | +3cec / 7 / - / - / - |
| 841 | +3ccc / 3 / - / - / - | +3d08 / 5 / - / - / - |
| 842 | +3cd8 / 4 / - / - / - | +3d1c / 6 / - / - / - |
| 843 | +3ce8 / 7 / - / - / - | +3d34 / 4 / - / - / - |
| 844 | +3d04 / 5 / - / - / - | +3d44 / 12 / - / - / - |
| 845 | +3d18 / 6 / - / - / - | +3d74 / 3 / - / - / - |
| 846 | +3d30 / 4 / - / - / - | +3d80 / 11 / Zi8LogError, _restgpr_27 / - / - |
| 847 | +3d40 / 12 / - / - / - | - |
| 848 | +3d70 / 3 / - / - / - | - |
| 849 | +3d7c / 11 / Zi8LogError, _restgpr_27 / - / - | - |

Unequal basic-block alignment spans:

| Kind | Target blocks / instructions | Build blocks / instructions |
| --- | --- | --- |
| replace | 0:1 / 95 | 0:1 / 94 |
| replace | 42:43 / 10 | 42:43 / 9 |
| replace | 75:76 / 9 | 75:76 / 10 |
| replace | 105:106 / 5 | 105:106 / 7 |
| replace | 116:117 / 13 | 116:117 / 13 |
| replace | 165:166 / 10 | 165:166 / 11 |
| replace | 173:174 / 16 | 173:174 / 15 |
| replace | 209:210 / 12 | 209:210 / 11 |
| replace | 228:229 / 12 | 228:229 / 11 |
| replace | 364:365 / 11 | 364:365 / 12 |
| replace | 372:373 / 12 | 372:373 / 11 |
| replace | 402:403 / 6 | 402:403 / 7 |
| replace | 405:406 / 26 | 405:406 / 25 |
| delete | 450:451 / 1 | 450:450 / 0 |
| replace | 453:455 / 14 | 452:454 / 14 |
| replace | 471:475 / 6 | 470:473 / 6 |
| replace | 492:494 / 6 | 490:492 / 6 |
| replace | 497:498 / 4 | 495:496 / 4 |
| replace | 500:501 / 6 | 498:499 / 5 |
| replace | 511:512 / 6 | 509:510 / 6 |
| replace | 514:515 / 12 | 512:513 / 13 |
| replace | 520:521 / 5 | 518:519 / 5 |
| replace | 529:531 / 13 | 527:528 / 6 |
| replace | 533:534 / 1 | 530:531 / 7 |
| replace | 549:551 / 7 | 546:547 / 3 |
| replace | 553:554 / 6 | 549:550 / 6 |
| replace | 557:558 / 6 | 553:554 / 7 |
| delete | 561:562 / 8 | 557:557 / 0 |
| replace | 563:564 / 3 | 558:560 / 11 |
| replace | 565:566 / 3 | 561:562 / 3 |
| replace | 568:569 / 6 | 564:565 / 6 |
| replace | 570:571 / 3 | 566:567 / 3 |
| replace | 576:579 / 8 | 572:575 / 8 |
| insert | 583:583 / 0 | 579:584 / 17 |
| insert | 584:584 / 0 | 585:586 / 3 |
| replace | 590:597 / 26 | 592:593 / 6 |
| replace | 656:657 / 10 | 652:653 / 11 |
| replace | 665:666 / 6 | 661:662 / 7 |
| replace | 680:681 / 7 | 676:678 / 11 |
| replace | 690:691 / 4 | 687:688 / 4 |
| replace | 697:698 / 4 | 694:696 / 14 |
| replace | 701:703 / 13 | 699:700 / 5 |
| replace | 706:707 / 23 | 703:704 / 23 |
| replace | 710:712 / 10 | 707:708 / 9 |
| replace | 732:739 / 53 | 728:729 / 9 |
| replace | 761:762 / 3 | 751:759 / 48 |
| replace | 767:768 / 10 | 764:765 / 11 |
| replace | 777:779 / 21 | 774:776 / 21 |
| replace | 787:788 / 10 | 784:785 / 9 |
| replace | 791:792 / 13 | 788:789 / 12 |
| replace | 799:800 / 10 | 796:797 / 9 |
| replace | 803:804 / 9 | 800:801 / 10 |
| replace | 810:813 / 11 | 807:810 / 11 |
| replace | 818:819 / 3 | 815:816 / 3 |

Unequal call-aligned regions (counts or opcode sequences differ):

| Region | Target instruction span | Build instruction span | Deficit | Ending call |
| --- | --- | --- | --- | --- |
| R001 | 5:222 | 5:221 | +1 | Zi8ChangeCharCase |
| R004 | 265:301 | 264:299 | +1 | Zi8LangSupported |
| R008 | 437:487 | 435:486 | -1 | Zi8GetTableCount |
| R013 | 576:605 | 575:606 | -2 | Zi8IsAlphaPunct |
| R014 | 605:707 | 606:708 | +0 | Zi8IsDupWordW |
| R020 | 874:910 | 875:911 | +0 | Zi8GetTableCount |
| R025 | 1114:1169 | 1115:1169 | +1 | Zi8GetTableCount |
| R026 | 1169:1235 | 1169:1234 | +1 | Zi8getKeyLayout |
| R035 | 1702:1761 | 1701:1761 | -1 | Zi8ITspecialExclusion |
| R037 | 1778:1790 | 1778:1789 | +1 | Zi8IsVowel |
| R042 | 1900:1920 | 1899:1920 | -1 | Zi8MatchPUDdata |
| R044 | 1943:1980 | 1943:1979 | +1 | Zi8MatchOEMdata |
| R045 | 1980:2165 | 1979:2164 | +0 | Zi8getKeyLayout |
| R046 | 2165:2248 | 2164:2246 | +1 | Zi8getKeyLayout |
| R050 | 2297:2347 | 2295:2345 | +0 | Zi8DeTokenization |
| R051 | 2347:2385 | 2345:2382 | +1 | Zi8ZHCheckSpelling |
| R053 | 2403:2435 | 2400:2432 | +0 | Zi8IsDupWordW |
| R054 | 2435:2523 | 2432:2520 | +0 | Zi8ConvertWC2UC |
| R055 | 2523:2653 | 2520:2647 | +3 | Zi8WCharCount |
| R056 | 2653:2969 | 2647:2963 | +0 | Zi8ConvertWC2UC |
| R057 | 2969:3123 | 2963:3123 | -6 | Zi8GetTableCount |
| R058 | 3123:3144 | 3123:3144 | +0 | Zi8getKeyLayout |
| R059 | 3144:3332 | 3144:3333 | -1 | Zi8IsAlphaPunct |
| R060 | 3332:3502 | 3333:3504 | -1 | ZiIsLetterHyphen |
| R062 | 3516:3532 | 3518:3535 | -1 | ZiIsLetterHyphen |
| R065 | 3595:3651 | 3598:3654 | +0 | Zi8GetTableCount |
| R066 | 3651:3669 | 3654:3671 | +1 | Zi8IsAlphaPunct |
| R067 | 3669:3720 | 3671:3721 | +1 | Zi8IsAlphaPunct |
| R068 | 3720:3739 | 3721:3739 | +1 | Zi8IsAlphaPunct |
| R069 | 3739:3871 | 3739:3872 | -1 | Zi8ConvertUC2WC |
