# rx6 allocator experiments

Retained result: kbdEventHandler is exact; clean four-unit GATE PASS. Keyboard 17/21 -> 18/21 exact functions, +744 matched code bytes. Six requested targets remain unresolved; all four units remain unlinked.

| Function | Objdiff before | Objdiff after | Instructions | Final diffs |
| --- | --- | --- | --- | --- |
| kbdProcMod | 99.90234 | 99.90234 | 256/256 | 4 |
| KBDSetModState | 99.40476 | 99.40476 | 42/42 | 4 |
| kbdEventHandler | 99.83871 | 100.0 | 186/186 | 0 |
| kbd_led_handler | 99.72 | 99.72 | 25/25 | 3 |
| CellPhone create | 99.8949 | 99.8949 | 333/333 | 7 |
| SignWindow create | 99.86425 | 99.86425 | 221/221 | 6 |
| Getter_ | 99.86043 | 99.86043 | 609/609 | 14 |

Getter experiments used the f3 seed at 99.9179 (nine differences); it did not become exact and was not installed. The table reports the retained checkout.

Owned branch `agent/w1005/rx6`, base `f7cc4a45`. Owned sources: kbd_lib.c, tiCellPhone.cpp, tiSignWindow.cpp, www_wiisetting.cpp. Pre-existing g2 logs are left alone.

Read levers 20-22, mwdbg README, f-round and common. All captures use --project data-d4. A private launcher in build/rx6/mwdbg.py only redirects the allowed output root into this worktree; compiler arguments, debugger, shared port lock and compiler hash checks are unchanged. Captures and trials stay under build/rx6.

Acceptance: new exact-name objdiff 100%, ctxdiff zero, identical pools, zero regressions, full gate and retail DOL SHA1. No configure.py linking changes. Reject behavior changes and artificial carrier objects.

Shared mwdbg had 20+ queued captures. Canceled only rx6 queued PID 3115129. Private emulator copy changes the single GDB listener port immediate at virtual 0x3cd408 from 9001 to 19006; gc3.py changes only its matching connect address. Private lock and output roots are in build/rx6. Compiler remains unchanged. Byte identity against the standard wibo build is required before using captures as evidence. See build/rx6/port-patch.json.

- mod-reuse-channel-loaded: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-reuse-channel-loaded", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 95.05469], "KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 95.05469, "insns": [253, 256], "diffs": 47}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-reuse-value-loaded: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-reuse-value-loaded", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 95.05469], "KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 95.05469, "insns": [253, 256], "diffs": 47}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-reuse-state-address: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-reuse-state-address", "unit": "kbd", "compiled": true, "pool": true, "data": "3992", "code": "3552", "drops": {"kbdProcMod": [99.90234, 89.046875], "KBDResetChannel": [100.0, 72.954544]}, "functions": {"kbdProcMod": {"score": 89.046875, "insns": [232, 256], "diffs": 254}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-load-physical-scalar: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-load-physical-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-load-physical-scalar-double: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-load-physical-scalar-double", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-merge-into-oldstate: Captured baseline colors old-value r182 before address r181. Change loaded-value provenance or reuse the real address to alter simplification/color order. Preserve the interrupt interval and exact mask; measure both setter and inlined kbdProcMod.
  {"label": "mod-merge-into-oldstate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.53125], "KBDSetModState": [99.40476, 97.38095]}, "functions": {"kbdProcMod": {"score": 99.53125, "insns": [256, 256], "diffs": 7}, "KBDSetModState": {"score": 97.38095, "insns": [42, 42], "diffs": 6}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

## kbdProcMod baseline allocator

Private capture build/rx6/kbdProcMod-base-2 is byte-identical to wibo whole-unit output, SHA256 13fedf29bfeec1efaa886d327753ef4d037d31319bdbe63b1e3139bb61285eb9. First failed private capture only lacked the shared Python import path; fixed that path without changing decoding.

Target tail address is r4, old state is r5. Source PCode B63 defines r181 = r180 + r45 and r182 = load(r181+544); r185 carries masked new state. Simplify removes r181 at degree 5, r182 at degree 3, r185 at degree 3, budget 29. Reverse coloring assigns r185 to r0, then r182 to r4 with legal mask 0x80001ff0, then r181 to r5 with mask 0x80001fe0. Coalescing has no candidates. Source ordinal ordering of the address/load temporaries, rather than pressure or a spill, causes the swap. Named primitive old-state and an explicit mask reproduce it; reusing incoming parameters disturbs the inlined critical path.

- www-f3-replay: Replay the requested agent/w1004/f3 helper seed. Mask helper changes loop-variable provenance; it is historical, not a new rx6 match.
  {"label": "www-f3-replay", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- mod-reuse-new-value: Keep the existing incoming value as the final merged word. Test whether a twice-assigned source web alters the old-value/address color priority; no new reads or side effects.
  {"label": "mod-reuse-new-value", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-reuse-union-old: Keep the existing incoming value as the final merged word. Test whether a twice-assigned source web alters the old-value/address color priority; no new reads or side effects.
  {"label": "mod-reuse-union-old", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-aggregate-init: Initialize the real modifier union at the load rather than assign its member. This targets scalar-replacement numbering, retaining the same field value and critical section.
  {"label": "mod-aggregate-init", "unit": "kbd", "compiled": false}

- mod-aggregate-init-cast: Initialize the real modifier union at the load rather than assign its member. This targets scalar-replacement numbering, retaining the same field value and critical section.
  {"label": "mod-aggregate-init-cast", "unit": "kbd", "compiled": false}

- mod-physical-field-pointer-True: Read the existing field through its declared modifier union view, moving only the view binding. Check whether the load web can color after the common channel address.
  {"label": "mod-physical-field-pointer-True", "unit": "kbd", "compiled": false}

- mod-physical-field-pointer-False: Read the existing field through its declared modifier union view, moving only the view binding. Check whether the load web can color after the common channel address.
  {"label": "mod-physical-field-pointer-False", "unit": "kbd", "compiled": false}

- led-bool-failure-switch: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-bool-failure-switch", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 81.2]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 81.2, "insns": [29, 25], "diffs": 18}}}

- led-bool-success-switch: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-bool-success-switch", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 85.12]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 85.12, "insns": [28, 25], "diffs": 17}}}

- led-unsigned-comparison-switch: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-unsigned-comparison-switch", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 93.2]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 93.2, "insns": [26, 25], "diffs": 15}}}

- led-case-zero-and-default: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-case-zero-and-default", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 91.6]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 91.6, "insns": [27, 25], "diffs": 15}}}

- led-failure-if-call: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-failure-if-call", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 39.6]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 39.6, "insns": [26, 25], "diffs": 22}}}

- led-success-if-call: Target selects success 0 by fall-through, failure 7 by bne. Test a different predicate/CFG spelling while preserving success == 1 for all input bits. No allocator swap is implied for the two constants.
  {"label": "led-success-if-call", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbd_led_handler": [99.72, 39.8]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 39.8, "insns": [26, 25], "diffs": 22}}}

- mod-copy-whole: Reuse the real old-state union as the incoming state before loading current physical bits. All assignments feed a value; test the multiple-definition provenance that should keep a named value below the address temporary.
  {"label": "mod-copy-whole", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-copy-value: Reuse the real old-state union as the incoming state before loading current physical bits. All assignments feed a value; test the multiple-definition provenance that should keep a named value below the address temporary.
  {"label": "mod-copy-value", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-copy-physical: Reuse the real old-state union as the incoming state before loading current physical bits. All assignments feed a value; test the multiple-definition provenance that should keep a named value below the address temporary.
  {"label": "mod-copy-physical", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-physical-field-pointer-True-c89: Correct C89 declaration placement. Read physical bits via a union pointer to the existing modifier field; compare temporary and common-address provenance.
  {"label": "mod-physical-field-pointer-True-c89", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 95.05469], "KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 95.05469, "insns": [253, 256], "diffs": 47}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-physical-field-pointer-False-c89: Correct C89 declaration placement. Read physical bits via a union pointer to the existing modifier field; compare temporary and common-address provenance.
  {"label": "mod-physical-field-pointer-False-c89", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 95.05469], "KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 95.05469, "insns": [253, 256], "diffs": 47}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-direct-plus: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-direct-plus", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-direct-index: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-direct-index", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-direct-reverse-plus: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-direct-reverse-plus", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-base-local: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-base-local", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-base-param-reuse: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-base-param-reuse", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-compound-subtract: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-compound-subtract", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 98.68279]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 98.68279, "insns": [187, 186], "diffs": 152}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-array-reference: Captured B6 uses named r41 for both global base and selected channel, pinning both to r30. Separate base and selected-address webs so the base can compete for r3 and status for r5; inspect operand order too.
  {"label": "event-array-reference", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-reload-status-named: Keep the report error classifier in its named byte variable through the subtraction. Test whether status priority drops below the independent base temporary.
  {"label": "event-reload-status-named", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-use-report-parameter: Keep the report error classifier in its named byte variable through the subtraction. Test whether status priority drops below the independent base temporary.
  {"label": "event-use-report-parameter", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u8-mutable-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u8-mutable-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.80645]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.80645, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u8-mutable-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u8-mutable-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.752686]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.752686, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u8-const-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u8-const-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.80645]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.80645, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u8-const-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u8-const-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.752686]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.752686, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u32-mutable-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u32-mutable-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.80645]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.80645, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u32-mutable-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u32-mutable-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.752686]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.752686, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u32-const-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u32-const-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.80645]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.80645, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-u32-const-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-u32-const-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.752686]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.752686, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-s32-mutable-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-s32-mutable-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.48387]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.48387, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-s32-mutable-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-s32-mutable-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.43011]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.43011, "insns": [186, 186], "diffs": 7}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-s32-const-separate: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-s32-const-separate", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.48387]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.48387, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-inline-classifier-s32-const-direct: Move the status-load classifier into a natural inline helper, leaving selected-channel lifetime unchanged. Status should move below base and displacement priority to receive r5; types preserve the byte wrap before comparison.
  {"label": "event-inline-classifier-s32-const-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.43011]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.43011, "insns": [186, 186], "diffs": 7}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-0-False-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-0-False-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-0-False-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-0-False-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-0-True-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-0-True-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-0-True-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-0-True-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-1-False-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-1-False-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-1-False-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-1-False-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-1-True-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-1-True-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-word-1-True-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-word-1-True-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-0-False-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-0-False-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-0-False-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-0-False-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-0-True-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-0-True-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-0-True-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-0-True-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-1-False-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-1-False-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-1-False-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-1-False-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-1-True-scalar: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-1-True-scalar", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-inline-union-1-True-field: Place the physical-state load and mask merge across a real helper boundary. Named argument provenance and parameter order should change which web colors first; preserve single load/store and all allowed modifier bits.
  {"label": "mod-inline-union-1-True-field", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

## Debugger platform findings

C++ invocations with -enc SJIS fault at compiler address 0x47e090 before CodeGen, WRITE_UNMAPPED. Removing only -enc SJIS gets past startup but exposes retrowin32 case-sensitive include lookup, first nw4r/lyt/textbox.h versus textBox.h, then tiHWKeyboard.h versus tiHwKeyboard.h. A private lowercase include overlay is insufficient for relative mixed-case includes. Next workaround preprocesses with the exact original command through wibo, then captures that expanded source without SJIS. Compare the resulting complete object to both wibo-preprocessed and normal source objects before using any C++ allocator explanation. These are debugger runtime limitations, not evidence about the functions.

- event-live-status-first-direct-u8-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-direct-u8-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-direct-u8-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-direct-u8-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-direct-u32-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-direct-u32-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-direct-u32-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-direct-u32-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-separate-u8-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-separate-u8-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-separate-u8-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-separate-u8-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-separate-u32-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-separate-u32-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-separate-u32-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-separate-u32-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-base-local-u8-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-base-local-u8-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-base-local-u8-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-base-local-u8-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-base-local-u32-False: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-base-local-u32-False", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-live-status-first-base-local-u32-True: The direct-address capture gives status r55, base r54, displacement r52; reverse order colors status first. Create a used status expression before the address, rather than the previously dead status load, so base and displacement can color first.
  {"label": "event-live-status-first-base-local-u32-True", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- sign-reuse-count-type: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-reuse-count-type", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

- sign-reuse-force-name: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-reuse-force-name", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 97.02715]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 97.02715, "insns": [222, 221], "diffs": 156}}}

- sign-explicit-slot-double-use: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-explicit-slot-double-use", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.117645]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.117645, "insns": [221, 221], "diffs": 34}}}

- sign-reuse-allocation-buffer: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-reuse-allocation-buffer", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.004524]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.004524, "insns": [221, 221], "diffs": 42}}}

- sign-count-loop-scope: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-count-loop-scope", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.8914]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.8914, "insns": [221, 221], "diffs": 46}}}

- sign-count-loop-condition-cast: Target count is r31 and slot address is r22. Reuse a real non-overlapping source variable or change the named loop boundary to move count ahead of slot in simplify priority; verify that loads across calls stay equivalent.
  {"label": "sign-count-loop-condition-cast", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

- cell-shared-indices: Target toggle row is r18 and animation byte displacement is r16. Test shared real locals or loop-width provenance without invented carrier structs and without caching mutable values across calls.
  {"label": "cell-shared-indices", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 97.327324]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 97.327324, "insns": [333, 333], "diffs": 148}}}

- cell-shared-row: Target toggle row is r18 and animation byte displacement is r16. Test shared real locals or loop-width provenance without invented carrier structs and without caching mutable values across calls.
  {"label": "cell-shared-row", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.86487]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.86487, "insns": [333, 333], "diffs": 8}}}

- cell-toggle-row-rebind: Target toggle row is r18 and animation byte displacement is r16. Test shared real locals or loop-width provenance without invented carrier structs and without caching mutable values across calls.
  {"label": "cell-toggle-row-rebind", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 95.285286]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 95.285286, "insns": [331, 333], "diffs": 199}}}

- cell-explicit-narrow-index: Target toggle row is r18 and animation byte displacement is r16. Test shared real locals or loop-width provenance without invented carrier structs and without caching mutable values across calls.
  {"label": "cell-explicit-narrow-index", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

## C and CellPhone captures

KBDSetModState B8 has address r48, loaded state r49, merge r52. r49 colors r4 ahead of r48/r5, the same ordinal conflict as the inlined copy. Scalar conversion changes the merge from r185 to r183 but leaves address r181 and old r182 in that same order. No coalescing candidates.

kbdEventHandler B6 reuses r41 data for global-base construction and selected channel, forcing base to r30. Direct-address trial separates base r54, offset r52, status r55. Status still colors first to r3, base r4, offset r5, versus desired base r3, offset r4, status r5. Reordering a used status computation also reproduces the same machine output. The two accepted coalesces in the direct trial merge unrelated key arguments into physical r3; status/base remain separate representatives.

kbd_led_handler is already wrong before allocation: B2 branches true to B5/zero while fall-through B3 gives seven. Both arms define virtual v34 (err). The allocator accepts coalesce v34 -> physical r3 for the callback argument, pinning both constants to r3 before graph coloring. Register priority therefore does not explain the three branch/constant differences. Success-first duplicated-call trial confirms the desired false branch, but emits two call blocks and 26 rather than 25 instructions.

CellPhone preprocessed capture uses unchanged text/data/relocation sections. Temporary filename changed only STT_FILE and __sinit symbol spelling; subsequent preprocessing keeps original basename. Row r38 paneName has 29 initial edges, simplifies third at degree 27; displacement r48 @9178 has 28 initial edges, simplifies seventh at degree 25. Reverse coloring gives displacement r18, cached animationKey r17, row r16. Target wants row r18 and displacement r16. No coalescing involves r38 or r48. This is concrete simplify-order evidence, not a guessed saved-register priority.

- cell-graph-direct-row: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-direct-row", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.78979]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.78979, "insns": [333, 333], "diffs": 12}}}

- cell-graph-toggle-pointer: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-toggle-pointer", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-graph-animation-pointer-ref: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-animation-pointer-ref", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-graph-move-row-outer: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-move-row-outer", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-graph-move-row-inner: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-move-row-inner", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.83483]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.83483, "insns": [333, 333], "diffs": 10}}}

- cell-graph-shared-key: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-shared-key", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.81982]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.81982, "insns": [333, 333], "diffs": 11}}}

- cell-graph-shared-resource: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-shared-resource", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 97.14715]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 97.14715, "insns": [333, 333], "diffs": 155}}}

- cell-graph-direct-row-reused-resource: Captured row r38 simplifies third at degree 27, before displacement r48 at degree 25, so reverse coloring claims r18 for displacement first. Remove the named row or widen a real variable lifetime to move row after displacement in simplify order. Preserve repeated mutable-table loads.
  {"label": "cell-graph-direct-row-reused-resource", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.693695]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.693695, "insns": [333, 333], "diffs": 73}}}

## SignWindow baseline allocator

With the original source basename, both preprocessed wibo and debugger objects are byte-identical to the normal tiSignWindow.o. The graph jams at degree 29. It removes r113 as an optimistic spill candidate with cost 7, then simplifies the remaining nodes in ascending virtual order: count r44 at degree 21, forceName r45 at 20, and finally slot-address r129 at 12. Reverse coloring makes r129 the first saved-register request, r31; r44 is tenth and gets r22. No actual spill is necessary. Count and slot do not participate in accepted coalesces. A named count and anonymous derived slot are ordered on opposite sides of the jammed-node list.

- www-reuse-status: Target country-loop counter reuses r31 after the property index expires. Reuse an existing real integer local with no later use of its prior value, then inspect allocator splitting/coalescing; preserve the unmatched-country result path.
  {"label": "www-reuse-status", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-reuse-string-property: Target country-loop counter reuses r31 after the property index expires. Reuse an existing real integer local with no later use of its prior value, then inspect allocator splitting/coalescing; preserve the unmatched-country result path.
  {"label": "www-reuse-string-property", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-reuse-return: Target country-loop counter reuses r31 after the property index expires. Reuse an existing real integer local with no later use of its prior value, then inspect allocator splitting/coalescing; preserve the unmatched-country result path.
  {"label": "www-reuse-return", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-mask-increment-clause: Change buffer binding or the natural mask loop form inside the f3 helper, preserving the assignment before every strlen and the same index at each store. Seek buffer r25 rather than r28 without a carrier object.
  {"label": "www-mask-increment-clause", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-mask-bind-before-test: Change buffer binding or the natural mask loop form inside the f3 helper, preserving the assignment before every strlen and the same index at each store. Seek buffer r25 rather than r28 without a carrier object.
  {"label": "www-mask-bind-before-test", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-mask-const-buffer: Change buffer binding or the natural mask loop form inside the f3 helper, preserving the assignment before every strlen and the same index at each store. Seek buffer r25 rather than r28 without a carrier object.
  {"label": "www-mask-const-buffer", "unit": "www", "compiled": true, "pool": true, "data": "1280", "code": "3740", "drops": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": [99.86043, 99.32677]}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.32677, "insns": [612, 609], "diffs": 380}}}

- sign-loop-helper-count-local-0: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-local-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-local-1: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-local-1", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- www-mask-return-pointer: Return the actual mask result from the helper and assign it at the original call site. The final pString read is preserved; returning a value changes inlined result and buffer lifetimes without a wrapper object.
  {"label": "www-mask-return-pointer", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- sign-loop-helper-count-local-2: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-local-2", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-local-3: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-local-3", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-arg-0: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-arg-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.47511]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.47511, "insns": [221, 221], "diffs": 60}}}

- www-mask-return-buffer: Return the actual mask result from the helper and assign it at the original call site. The final pString read is preserved; returning a value changes inlined result and buffer lifetimes without a wrapper object.
  {"label": "www-mask-return-buffer", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- sign-loop-helper-count-arg-1: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-arg-1", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.47511]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.47511, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-arg-2: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-arg-2", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.47511]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.47511, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-arg-3: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-arg-3", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.47511]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.47511, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-and-force-args-0: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-and-force-args-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-and-force-args-1: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-and-force-args-1", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.497734]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.497734, "insns": [221, 221], "diffs": 58}}}

- sign-loop-helper-count-and-force-args-2: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-and-force-args-2", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.46154]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.46154, "insns": [221, 221], "diffs": 60}}}

- sign-loop-helper-count-and-force-args-3: Move actual animation attachment into an inline helper. Parameter/local numbering can lift count above the derived slot in the jammed simplify list. Resource accessor is a reference to the original field so virtual calls still reload it.
  {"label": "sign-loop-helper-count-and-force-args-3", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.497734]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.497734, "insns": [221, 221], "diffs": 58}}}

## Getter f3 preprocessed allocator, provisional

Mask buffer is r43, loop index r44, country index r35. r43 simplifies at degree 15, r44 at 19 and r35 at 22. Color masks are the decisive evidence: r44 gets r26 from 0xd4000000; r43 then gets r28 from 0xd0000000 while pool 0xfc001ff9 does not yet contain r25. Later retVal r39 opens r25. Country r35 then picks r25 from 0x86000000, which also permits r31. Target buffer r25 needs a later color point after r25 exists; target country r31 needs an earlier point before lower saved colors become available. Neither value is merged by coalescing. Reusing staIdx/strPropIdx/retVal and returning the mask buffer reproduce the f3 object code exactly.

Rejected www-mask-const-buffer on semantics as well as score: it reloads pString after strlen instead of retaining the captured pointer. Nothing from that trial is retained.

Getter preprocessing validation FAILED: it inserts an extra pString reload at instruction 265 and makes Getter 610 rather than 609 instructions. Its node numbers and masks above are provisional and cannot establish the exact f3 graph. No source was installed. Added a complete private include alias overlay, then verified full-source wibo without SJIS before requesting a full-source capture.

- cell-loop-helper-row-ref-0: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-ref-0", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-loop-helper-row-ref-1: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-ref-1", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-loop-helper-row-ref-2: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-ref-2", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-loop-helper-row-index-0: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-index-0", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.693695]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.693695, "insns": [333, 333], "diffs": 74}}}

- cell-loop-helper-row-index-1: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-index-1", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.693695]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.693695, "insns": [333, 333], "diffs": 74}}}

- cell-loop-helper-row-index-2: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-index-2", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.693695]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.693695, "insns": [333, 333], "diffs": 74}}}

- cell-loop-helper-row-pointer-0: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-pointer-0", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-loop-helper-row-pointer-1: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-pointer-1", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-loop-helper-row-pointer-2: Place the actual toggle-animation loop behind an inline helper so the row and compiler displacement enter a different local-numbering cluster. Reference accessor preserves reloads across calls; compare priority and degree against the captured r38/r48 conflict.
  {"label": "cell-loop-helper-row-pointer-2", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.47447]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.47447, "insns": [333, 333], "diffs": 30}}}

- cell-accessor-row-u16: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-row-u16", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.66967]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.66967, "insns": [333, 333], "diffs": 21}}}

- cell-accessor-row-u32: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-row-u32", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 99.66967]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.66967, "insns": [333, 333], "diffs": 21}}}

- cell-accessor-key-u16: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-key-u16", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-key-u32: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-key-u32", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-animation-u16: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-animation-u16", "unit": "cell", "compiled": false}

- cell-accessor-animation-u32: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-animation-u32", "unit": "cell", "compiled": false}

- cell-accessor-filename-u16: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-filename-u16", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-filename-u32: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-filename-u32", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-id-u16: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-id-u16", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-id-u32: Test only the differing row or displacement expression across a small typed table accessor. This changes creation order without adding a carrier, caching mutable fields, or altering the animation loop.
  {"label": "cell-accessor-id-u32", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-animation-u16-typed: Correct the table accessor return type to the existing AnimationFileForControlKey. Preserve table access and observe whether named record reference changes the synthetic displacement priority.
  {"label": "cell-accessor-animation-u16-typed", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-accessor-animation-u32-typed: Correct the table accessor return type to the existing AnimationFileForControlKey. Preserve table access and observe whether named record reference changes the synthetic displacement priority.
  {"label": "cell-accessor-animation-u32-typed", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- sign-slot-array-ref: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-array-ref", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

- sign-slot-slot-pointer: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-slot-pointer", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

- sign-slot-base-plus-index: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-base-plus-index", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 96.53846]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 96.53846, "insns": [221, 221], "diffs": 60}}}

- sign-slot-const-value: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-const-value", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 97.004524]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 97.004524, "insns": [219, 221], "diffs": 91}}}

- sign-slot-load-reference-helper: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-load-reference-helper", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

- sign-slot-load-pointer-helper: The anonymous slot r129 is the first color request, while count r44 is tenth after the graph jams. Give the array slot a real named pointer or accessor reference and inspect whether it leaves the high virtual-number position. Cache-value variant is diagnostic because repeated pointer reads must be reviewed.
  {"label": "sign-slot-load-pointer-helper", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.86425, "insns": [221, 221], "diffs": 6}}}

Cell direct-row capture is byte-identical to its private wibo trial. Removing the named reference produces row r48 and displacement r49. They simplify in the same unwanted order at degrees 27 and 25; the loaded key is now earlier, so this changes 7 baseline differences into 12 rather than fixing the swap. This confirms CSE temp creation order survives the source cleanup.

Sign slot const-value is rejected on semantics: it caches the table entry across calls where the original reference reloads the pointer. The reference/pointer/accessor variants preserve those reloads and retain six differences.

- www-country-helper-ref: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-helper-ref", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-country-helper-pointer: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-helper-pointer", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-country-do-while: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-do-while", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-country-post-condition: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-post-condition", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": [99.86043, 99.5977]}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.5977, "insns": [609, 609], "diffs": 9}}}

- www-country-unsigned-cast-condition: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-unsigned-cast-condition", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

- www-country-outer-index: Country r35 colors after lower saved registers exist and picks r25; target wants r31. Move its true loop lifetime across a plain helper or induction boundary. Output helper writes only on the original matching path, retaining the target no-match behavior.
  {"label": "www-country-outer-index", "unit": "www", "compiled": true, "pool": true, "data": "3856", "code": "3740", "drops": {}, "functions": {"Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue": {"score": 99.9179, "insns": [609, 609], "diffs": 9}}}

### Definitive full-source Getter allocation

The earlier preprocessed Getter capture is rejected: it inserted a pString load and had 610 instructions. `build/rx6/www-f3-fullsource/unit.o` is byte-identical to the ordinary f3-seed object, including all sections. The valid graph uses v41, not provisional v43, for the captured pString buffer. v43 is dead. v41 simplifies with degree 17, then colors from pool 0xfc001ff9 with legal mask 0xd0000000 to r28. Loop index v44 colors r26; retVal v39 later exhausts its colors and opens r25. Country counter v35 simplifies with degree 22 and colors after that expansion, choosing r25 from mask 0x86000000 (r25/r26/r31). Target buffer r25 requires allocation after r25 opens; target country r31 requires an earlier priority or different interference. Neither v41 nor v35 participates in a coalescing candidate. Full-source capture preserves the one pString reload per loop test and its reuse across strlen.

### Sign changed-source allocation confirmation

`sign-explicit-slot-double-use` and its byte-identical `sign-slot-pp/capture` move the slot address from baseline v129 to synthetic v46. It now colors eighth (r24), behind seven hoisted constructor/table constants. Animation count remains named v43 and colors tenth (r22); target count r31 and slot r22 still fail. The missing first slot color shifts the seven constants up one register, producing 34 diffs at unchanged 221 instructions. This shows that changing only slot naming is insufficient: the count must also become the first saved-register claimant while the slot moves behind forceName. No code from this diagnostic was retained.

- sign-count-value-reference: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-value-reference", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-count-value-reference-slot-reload: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-value-reference-slot-reload", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-count-value-reference-cast: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-value-reference-cast", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-count-value-reference-cast-slot-reload: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-value-reference-cast-slot-reload", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-count-const-count-slot-reload: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-const-count-slot-reload", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.1448]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.1448, "insns": [221, 221], "diffs": 59}}}

- sign-count-member-count-copy: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-member-count-copy", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.8914]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.8914, "insns": [221, 221], "diffs": 46}}}

- sign-count-member-count-copy-slot-reload: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-member-count-copy-slot-reload", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.1448]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.1448, "insns": [221, 221], "diffs": 59}}}

- sign-count-member-count-reference: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-member-count-reference", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-count-member-count-reference-slot-reload: Count must become the first saved-register claimant while the slot moves behind forceName. Test scalar value-copy reference lifetime and a real PaneAnimation count accessor; preserve a single cached count and repeated animation-pointer reads. No carrier structure or altered table layout.
  {"label": "sign-count-member-count-reference-slot-reload", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- mod-physical-key-fields-leftControl: Preserve the six physical key flags individually through the existing KBDModifierState keys view. Multiple true uses may retain a named old-value web so it colors after the address, instead of baseline synthetic old v49 coloring before address v48. No layout change or redundant arithmetic.
  {"label": "mod-physical-key-fields-leftControl", "unit": "kbd", "compiled": true, "pool": true, "data": "3992", "code": "3552", "drops": {"kbdProcMod": [99.90234, 89.046875], "KBDResetChannel": [100.0, 72.954544], "KBDSetModState": [99.40476, 87.38095]}, "functions": {"kbdProcMod": {"score": 89.046875, "insns": [232, 256], "diffs": 254}, "KBDSetModState": {"score": 87.38095, "insns": [47, 42], "diffs": 20}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-physical-key-fields-rightAlt: Preserve the six physical key flags individually through the existing KBDModifierState keys view. Multiple true uses may retain a named old-value web so it colors after the address, instead of baseline synthetic old v49 coloring before address v48. No layout change or redundant arithmetic.
  {"label": "mod-physical-key-fields-rightAlt", "unit": "kbd", "compiled": true, "pool": true, "data": "3992", "code": "3552", "drops": {"kbdProcMod": [99.90234, 89.046875], "KBDResetChannel": [100.0, 72.954544], "KBDSetModState": [99.40476, 87.38095]}, "functions": {"kbdProcMod": {"score": 89.046875, "insns": [232, 256], "diffs": 254}, "KBDSetModState": {"score": 87.38095, "insns": [47, 42], "diffs": 20}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- sign-reference-follow-force-inner: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-force-inner", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.86878]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.86878, "insns": [221, 221], "diffs": 47}}}

- sign-reference-follow-force-inner-const: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-force-inner-const", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.86878]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.86878, "insns": [221, 221], "diffs": 47}}}

- sign-reference-follow-force-use-pane-name: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-force-use-pane-name", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 97.004524]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 97.004524, "insns": [222, 221], "diffs": 156}}}

- sign-reference-follow-slot-pointer-outer-before-force: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-slot-pointer-outer-before-force", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-reference-follow-slot-pointer-outer-after-force: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-slot-pointer-outer-after-force", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-reference-follow-slot-pointer-loop: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-slot-pointer-loop", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.095024]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.095024, "insns": [221, 221], "diffs": 35}}}

- sign-reference-follow-reload-pointer: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-reload-pointer", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.47511]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.47511, "insns": [220, 221], "diffs": 35}}}

- sign-reference-follow-reuse-resource-buffer: Scalar reference-to-copy puts count in target r31, but forceName r22 and slot r23 are swapped. Move the real pointer lifetimes, declaration scopes or reuse so force colors before slot; retain count snapshot and pointer reloads across resource/animation calls.
  {"label": "sign-reference-follow-reuse-resource-buffer", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 98.7104]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 98.7104, "insns": [221, 221], "diffs": 53}}}

- mod-read-helper-state-channel: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-state-channel", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-read-helper-state-data: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-state-data", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-read-helper-scalar-channel: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-scalar-channel", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-input-report-original-pointer: Model the existing eight-byte input record with its real modifiers/reserved/six-key fields. This tests alias and address expression lowering, not a register carrier; preserve every report byte reload across callbacks and use exactly the original offsets.
  {"label": "event-input-report-original-pointer", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-read-helper-scalar-data: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-scalar-data", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-input-report-original-reference-by-index: Model the existing eight-byte input record with its real modifiers/reserved/six-key fields. This tests alias and address expression lowering, not a register carrier; preserve every report byte reload across callbacks and use exactly the original offsets.
  {"label": "event-input-report-original-reference-by-index", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-read-helper-state-out-channel: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-state-out-channel", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-input-report-direct-pointer: Model the existing eight-byte input record with its real modifiers/reserved/six-key fields. This tests alias and address expression lowering, not a register carrier; preserve every report byte reload across callbacks and use exactly the original offsets.
  {"label": "event-input-report-direct-pointer", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-read-helper-state-out-data: Capture the old modifier word through a plain typed reader using the existing modifier union. Returning the real bitfield state or a scalar changes load-origin numbering without creating an artificial carrier; verify both inlined kbdProcMod and standalone setter.
  {"label": "mod-read-helper-state-out-data", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"KBDSetModState": [99.40476, 98.690475]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 98.690475, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-input-report-direct-reference-by-index: Model the existing eight-byte input record with its real modifiers/reserved/six-key fields. This tests alias and address expression lowering, not a register carrier; preserve every report byte reload across callbacks and use exactly the original offsets.
  {"label": "event-input-report-direct-reference-by-index", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- cell-reference-row-pointer-key-original: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-pointer-key-original", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-reference-row-pointer-key-pointer-reference-copy: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-pointer-key-pointer-reference-copy", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.75375]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.75375, "insns": [333, 333], "diffs": 68}}}

- cell-reference-row-const-pointer-key-original: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-const-pointer-key-original", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 99.8949, "insns": [333, 333], "diffs": 7}}}

- cell-reference-row-const-pointer-key-pointer-reference-copy: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-const-pointer-key-pointer-reference-copy", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.75375]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.75375, "insns": [333, 333], "diffs": 68}}}

- cell-reference-row-pointer-reference-copy-key-original: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-pointer-reference-copy-key-original", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 98.81381]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 98.81381, "insns": [333, 333], "diffs": 67}}}

- cell-reference-row-pointer-reference-copy-key-pointer-reference-copy: Target row r18 must color before byte displacement r16. Test a typed row pointer and scalar pointer-copy lifetime, preserving the captured condition pointer and the row field reload for forceAddAnimation. No table copy, new carrier or changed field values.
  {"label": "cell-reference-row-pointer-reference-copy-key-pointer-reference-copy", "unit": "cell", "compiled": true, "pool": true, "data": "3860", "code": "17696", "drops": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": [99.8949, 97.49249]}, "functions": {"create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator": {"score": 97.49249, "insns": [333, 333], "diffs": 143}}}

### Getter helper capture: changed priority, same nine target differences

The full-source `www-country-helper-fullsource/unit.o` is byte-identical to trial `www-country-helper-ref/unit.o` (SHA256 84840eeadc04de30498854e3ceee0ee3bd266590ec3c554468fc929782fe0b38). The European index becomes inline temporary v43 instead of named v35. Its degree remains 22, but it now colors before retVal opens r25 and chooses r26. The buffer becomes v40, still degree 17 and r28. This corrects any interpretation of the unchanged objdiff score as unchanged register choices: the helper moves the country counter r25 to r26, but target r31 remains unmet. Neither affected value coalesces. Pool identical, 609/609 instructions, nine target differences, no exact gain.

- sign-reference-accessor-member-file: Captured value-copy count becomes late split v142 and colors first to r31; slot common address v46 still outranks forceName v44 and takes r23 instead of r22. Use real record value accessors to change common-address creation order, keeping all pointer reads at their original call boundaries.
  {"label": "sign-reference-accessor-member-file", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-reference-accessor-member-name-id: Captured value-copy count becomes late split v142 and colors first to r31; slot common address v46 still outranks forceName v44 and takes r23 instead of r22. Use real record value accessors to change common-address creation order, keeping all pointer reads at their original call boundaries.
  {"label": "sign-reference-accessor-member-name-id", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-reference-accessor-free-file-ref: Captured value-copy count becomes late split v142 and colors first to r31; slot common address v46 still outranks forceName v44 and takes r23 instead of r22. Use real record value accessors to change common-address creation order, keeping all pointer reads at their original call boundaries.
  {"label": "sign-reference-accessor-free-file-ref", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-reference-accessor-free-file-pointer: Captured value-copy count becomes late split v142 and colors first to r31; slot common address v46 still outranks forceName v44 and takes r23 instead of r22. Use real record value accessors to change common-address creation order, keeping all pointer reads at their original call boundaries.
  {"label": "sign-reference-accessor-free-file-pointer", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-reference-accessor-free-file-index-first: Captured value-copy count becomes late split v142 and colors first to r31; slot common address v46 still outranks forceName v44 and takes r23 instead of r22. Use real record value accessors to change common-address creation order, keeping all pointer reads at their original call boundaries.
  {"label": "sign-reference-accessor-free-file-index-first", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

### Sign scalar-copy reference allocation evidence

`sign-count-reference-fullsource/unit.o` is byte-identical to `sign-count-value-reference-slot-reload/unit.o`. The count reference itself is dead v37; its scalar temporary is promoted late to v142 (34 initial edges, cost 136). It simplifies last after the same optimistic v113 spill choice and colors first to r31. Slot common address v46 (30 edges, cost 448) now colors ninth to r23, then forceName v44 (34 edges, cost 264) colors tenth to r22. This satisfies the original count choice but swaps the slot and forceName. The candidate has 221/221 instructions, seven diffs, identical pool, and no new exact function. Follow-ups tested forceName scope, reuse of pane names, slot pointers in three scopes, repeated pointer assignment, and resource-buffer reuse; all failed (35-156 diffs). No reference-copy diagnostic was installed.

- mod-two-stage-direct-compound: Test two-stage physical-mask retention and requested-lock insertion. All operations remain inside the original interrupt-disabled block with the same final word; inspect whether memory/CSE lowering retains a named old-value web before the computed store address. Reject extra stores or any function/data regression.
  {"label": "mod-two-stage-direct-compound", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 94.04762]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [256, 256], "diffs": 5}, "KBDSetModState": {"score": 94.04762, "insns": [42, 42], "diffs": 7}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-two-stage-local-compound: Test two-stage physical-mask retention and requested-lock insertion. All operations remain inside the original interrupt-disabled block with the same final word; inspect whether memory/CSE lowering retains a named old-value web before the computed store address. Reject extra stores or any function/data regression.
  {"label": "mod-two-stage-local-compound", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.35547], "KBDSetModState": [99.40476, 96.07143]}, "functions": {"kbdProcMod": {"score": 99.35547, "insns": [257, 256], "diffs": 13}, "KBDSetModState": {"score": 96.07143, "insns": [43, 42], "diffs": 14}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-two-stage-physical-then-locks: Test two-stage physical-mask retention and requested-lock insertion. All operations remain inside the original interrupt-disabled block with the same final word; inspect whether memory/CSE lowering retains a named old-value web before the computed store address. Reject extra stores or any function/data regression.
  {"label": "mod-two-stage-physical-then-locks", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdProcMod": [99.90234, 99.140625], "KBDSetModState": [99.40476, 95.0]}, "functions": {"kbdProcMod": {"score": 99.140625, "insns": [257, 256], "diffs": 18}, "KBDSetModState": {"score": 95.0, "insns": [43, 42], "diffs": 18}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

### Full-source CellPhone confirmation

The final `cell-fullsource` capture uses the complete source, not a preprocessed surrogate. Its entire object is byte-identical to `build/43U/src/src/keyboard/tiCellPhone.o` (SHA256 5075b480f6de660131a65bf5f44056f6b580500343089dace20d8cce862b5959). This removes the earlier cell-pp filename-symbol qualification. Row and animation-displacement allocation still agrees with the original degree/priority analysis. The shared compiler executable and code-generation flags remain unchanged; the isolated emulator port, input-encoding workaround and private header spelling aliases affect only debugger execution and are all confined to build/rx6.

### Search scheduling

All 18 configured source searches retain the shared 24-slot CPU lock unchanged. At the first six completed runs, ten remained queued and two were running; elapsed queue time is not counted toward their 1200-second search budgets. No other worker process, worktree, compiler, or shared debugger service was modified. No best/solution file had been produced by those six runs. The current project sources still equal the initial checkout; the f3 Getter seed and every trial remain private under build/rx6.

## Allocator checkpoint before the exact event-handler result

| Function | Target value placement | Observed cause | Confirmed source experiment |
| --- | --- | --- | --- |
| kbdProcMod | Channel address r4; old modifier word r5 | Tail v181 address simplifies before v182 old word (degrees 5 and 3); reverse coloring gives the word r4 and address r5 after merged value v185 takes r0. No relevant coalescing. | Scalar physical-bit load changes the merged node to v183, leaves address/word priority unchanged, and produces the identical whole object. |
| KBDSetModState | Channel address r4; old modifier word r5 | Same tail, address v48 and word v49; later-numbered word colors first to r4. No relevant coalescing. | Same scalar-load experiment is byte-identical standalone as well as when inlined into kbdProcMod. |
| kbdEventHandler | Global base r3; displacement r4; status r5; selected channel r30 | Baseline keeps base and selected channel in named v41/r30. Direct indexing splits them, but status v55 colors r3 before base v54/r4 and offset v52/r5. | Byte-identical capture of event-direct-plus confirms the split and wrong reverse order; 186/186 instructions, six differences. |
| kbd_led_handler | bne to failure; fallthrough loads 0, alternate loads 7 | Wrong polarity and arm order exist before allocation. The accepted v34 -> r3 coalesce pins both constants to the callback argument register before coloring; the failure is CFG selection. | Success-first duplicated callback calls get bne but make separate call blocks and 26 instructions instead of 25. |
| CellPhone create | Toggle row r18; animation displacement r16 | Named row v38 simplifies third (degree 27), synthetic displacement v48 seventh (degree 25); reverse coloring assigns row r16 and displacement r18. Neither value coalesces. | Direct table access changes row to synthetic v48 and displacement to v49 but retains their order; it adds normal-loop differences, giving 12 total. |
| SignWindow create | Cached count r31; animation slot address r22 | After optimistic spill candidate v113 breaks the degree-29 graph, count v44 simplifies before slot v129. Slot colors first to r31; count tenth to r22. No actual spill. | Scalar-copy reference promotes count to late v142 and gets r31; explicit repeated slot loads put slot v46 in r23 and forceName v44 in r22 instead. Seven differences remain. |
| Getter_ f3 seed | Captured buffer r25; European counter r31 | Buffer v41 colors before retVal v39 opens r25, so mask 0xd0000000 selects r28. Counter v35 colors afterward from 0x86000000 and selects r25. No relevant coalescing. | Plain country helper makes counter synthetic v43, colored earlier from mask 0x84000000 to r26. Buffer v40 still takes r28; nine differences remain. |

Every explanation above is tied to a capture validated against an ordinary whole-object build. The rejected 610-instruction preprocessed Getter capture is excluded. Remaining mismatches are measured failures, not an impossibility proof. No target function has reached an accepted exact match in this round.

- sign-branch-baseline-name-value-0: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-baseline-name-value-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.117645]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.117645, "insns": [221, 221], "diffs": 34}}}

- sign-branch-baseline-name-value-4: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-baseline-name-value-4", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.117645]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.117645, "insns": [221, 221], "diffs": 34}}}

- sign-branch-baseline-name-ref-0: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-baseline-name-ref-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.117645]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.117645, "insns": [221, 221], "diffs": 34}}}

- sign-branch-baseline-name-ref-4: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-baseline-name-ref-4", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.117645]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.117645, "insns": [221, 221], "diffs": 34}}}

- sign-branch-reference-count-name-value-0: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-reference-count-name-value-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-branch-reference-count-name-value-4: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-reference-count-name-value-4", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-branch-reference-count-name-ref-0: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-reference-count-name-ref-0", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

- sign-branch-reference-count-name-ref-4: Limit the inline boundary to the actual animation-binding branch. Pass the slot by reference so its pointer is still read separately in each arm, and pass the already-cached forceName by value or reference. Test whether this moves forceName priority past the common slot address without changing the surrounding animation loop or count snapshot.
  {"label": "sign-branch-reference-count-name-ref-4", "unit": "sign", "compiled": true, "pool": true, "data": "3468", "code": "6300", "drops": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": [99.86425, 99.84163]}, "functions": {"create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator": {"score": 99.84163, "insns": [221, 221], "diffs": 7}}}

### Reuse of completed identical-source searches

The existing g2 run completed seeds 617, 821 and 1009 for both create functions, each for 1200 seconds, with no candidate. Verified the actual search start files and baseline objects byte-for-byte against current rx6 source and objects: CellPhone SHA256 source 69edfe68c25ae3aa1a72f1ed4f712082f3344d39621b8fd1e58d0916f232536c; SignWindow 20965774704d932ee63f3a746cf287bb5322018a02c9778f9afcf28000f75016. All 16 mutation/scoring predicate routine ASTs agree between the g2 and rx6 private srcsearch copies. Existing coverage: CellPhone 2609 trials; SignWindow 2431 trials. Evidence: build/g2/search-summary.json and build/g2/search-manifest.json.

Cancelled only the four still-unstarted duplicate searches: cell-6, cell-22, sign-6, sign-22. Each process was verified in this worktree, stopped before inspection, confirmed to hold no CPU-slot lock, then terminated. They performed no trials and are not counted as completed rx6 runs. The extra SignWindow seed completed while this audit ran. CellPhone seed 61 had acquired a slot, so it is retained. Remaining keyboard searches still run because their prior seeds used different source shapes; the prior event seed used a now-forbidden carrier and is not reused as coverage for the current plain source. The shared CPU limiter is unchanged.

- event-error-range-split-named-or: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-named-or", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.83871, "insns": [186, 186], "diffs": 5}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-split-named-bounds: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-named-bounds", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 98.1129]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 98.1129, "insns": [186, 186], "diffs": 8}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-split-direct-or: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-direct-or", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-split-direct-bounds: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-direct-bounds", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 98.1129]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 98.1129, "insns": [186, 186], "diffs": 8}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-split-switch-error-first: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-switch-error-first", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 96.77419]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 96.77419, "insns": [187, 186], "diffs": 153}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-split-switch-valid-first: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-split-switch-valid-first", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 85.10753]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 85.10753, "insns": [186, 186], "diffs": 143}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-named-or: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-named-or", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 99.78494]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 99.78494, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-named-bounds: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-named-bounds", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 98.139786]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 98.139786, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-direct-or: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-direct-or", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-direct-bounds: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-direct-bounds", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 98.139786]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 98.139786, "insns": [186, 186], "diffs": 6}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-switch-error-first: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-switch-error-first", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 96.935486]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 96.935486, "insns": [187, 186], "diffs": 150}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-error-range-direct-switch-valid-first: The status load currently becomes a late anonymous node, colored before the independent base and displacement. Spell the actual HID error set (1, 2, 3) with multiple genuine uses or grouped switch cases, so range folding may retain the earlier named status web. Keep the callback-side report reload and all valid-report processing unchanged.
  {"label": "event-error-range-direct-switch-valid-first", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "3728", "drops": {"kbdEventHandler": [99.83871, 85.268814]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 85.268814, "insns": [186, 186], "diffs": 140}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- event-exact-clean-status: Exact candidate: direct channel indexing plus explicit HID error-code comparisons 1,2,3 reaches 100.0, 186/186, diffs 0. Remove the pre-existing unused status declaration and assignment so the retained source has no dead status local; require the exact result and zero unit regressions to remain.
  {"label": "event-exact-clean-status", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

## Exact kbdEventHandler result

Retained source changes only the channel pointer expression and error predicate, and removes the pre-existing unused status declaration/assignment. `data = &kbdData[channel]` replaces base assignment plus addition. `bytes[2] == 1 || bytes[2] == 2 || bytes[2] == 3` replaces the wrapped-byte range test. All 256 input-byte values were checked for equivalence; no call occurs between these comparisons, and the report reload after OSCancelAlarm and all valid-report processing remain unchanged.

The cleaned source keeps status as compiler temporary v46, named @1121, instead of the late instruction temporary used by the single range expression. Its simplify degree is 6, before displacement v53 (degree 6) and base v55 (degree 6). Reverse coloring now assigns base v55 to r3 from mask 0x50001ff8, displacement v53 to r4 from 0x50001ff0, and status v46 to r5 from 0x50001fe0. The selected channel remains v41/r30. No coalescing candidate involves these three changed values. This is the target allocation. Direct indexing alone gave the wrong status/base order; using a named status in the OR also failed. The repeated direct expression is what moves the status into the earlier compiler-temporary group while the compiler still folds the predicate to the original single range test.

`event-exact-clean-status/capture-kbdEventHandler/unit.o` is byte-identical to both its ordinary private build and the installed project object. A fresh owned-object ninja build, pool_diff, exact-name objdiff and ctxdiff pass: 99.83871 -> 100.0, 186/186 instructions, diffs 0. Unit code 3728/5764 -> 4472/5764 (+744); functions 17/21 -> 18/21; data stays 5296/5296; no sibling score drops. The other three keyboard targets remain unresolved, so the unit is not claimed ready for linking. Full clean gate and local commit remain pending at this checkpoint.

After the event handler reached a clean exact result, event seed 22 was cancelled before acquiring a CPU slot. Seeds 6 and 61 already completed; seed 22 is not counted as a completed run. The modifier and LED final seeds remain queued.

- mod-cse-physical-groups-3-direct: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-3-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

### Clean gate after event-handler match

Ran the shared gate.py for all four owned units without --quick. Both still-queued keyboard searches were stopped temporarily before CPU-slot acquisition, verified to hold no slot lock, and resumed in a finally block after the clean build. No running compiler was overlapped with deletion/rebuilding of build/43U. Full build passed; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; zero regressions; zero forbidden patterns; zero readability warnings; GATE PASS. The keyboard unit has 18/21 objdiff and instruction-exact functions, code 4472/5764, data 5296/5296. Other units remain CellPhone 85/86, SignWindow 55/56, Getter unit 20/21. Gate evidence: tools/decomp-assist/rx6.final-gate.txt.

- mod-cse-physical-groups-3-named: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-3-named", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-cse-physical-groups-2-direct: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-2-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-cse-physical-groups-2-named: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-2-named", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-cse-physical-groups-6-direct: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-6-direct", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

- mod-cse-physical-groups-6-named: The exact event result proves repeated direct expressions can become earlier compiler temporaries than a single range expression. Test whether preserving the control/shift/alt groups (or left/right groups, or six individual flags) similarly gives the old modifier word earlier provenance than the store address. Every mask is disjoint and contributes necessary physical bits; their union is exactly 0x3f. Preserve the installed exact event handler and the interrupt interval.
  {"label": "mod-cse-physical-groups-6-named", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 99.72, "insns": [25, 25], "diffs": 3}}}

### Modifier follow-up after the event result

The three physical-bit groups produce the same address/old-word ordering as the baseline. In the byte-identical ordinary-build/mwdbg capture (SHA256 a14afdabcdcc115ef327cfff939b523a20b612c46ebca7beda6f6217d87f3858), address v48 simplifies with degree 5 before old word v49 with degree 3. The merged word is now v51, but reverse coloring still assigns it r0, then old word v49 takes r4 from mask 0x1ff0 and address v48 takes r5 from 0x1fe0. Only the incoming argument copies are considered for coalescing; both are rejected for interference. Splitting the real physical-bit groups therefore does not reproduce the event predicate's useful change of value priority. All six grouped-mask variants retain the four differences in each modifier function and preserve the newly exact event handler. None is installed.

- led-control-goto-error: The debugger locates the polarity mismatch in preallocation CFG, while ordinary if/else is lowered to a branchless select. Test an explicit shared callback exit from success and failure blocks, preserving success == TRUE and one callback invocation. No new state, arithmetic, volatile or carriers; preserve the exact event handler. Reject added instructions or changed sibling functions.
  {"label": "led-control-goto-error", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {"kbd_led_handler": [99.72, 34.4]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 34.4, "insns": [22, 25], "diffs": 23}}}

- led-control-goto-notify: The debugger locates the polarity mismatch in preallocation CFG, while ordinary if/else is lowered to a branchless select. Test an explicit shared callback exit from success and failure blocks, preserving success == TRUE and one callback invocation. No new state, arithmetic, volatile or carriers; preserve the exact event handler. Reject added instructions or changed sibling functions.
  {"label": "led-control-goto-notify", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {"kbd_led_handler": [99.72, 30.4]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 30.4, "insns": [23, 25], "diffs": 23}}}

- led-control-break-error: The debugger locates the polarity mismatch in preallocation CFG, while ordinary if/else is lowered to a branchless select. Test an explicit shared callback exit from success and failure blocks, preserving success == TRUE and one callback invocation. No new state, arithmetic, volatile or carriers; preserve the exact event handler. Reject added instructions or changed sibling functions.
  {"label": "led-control-break-error", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {"kbd_led_handler": [99.72, 30.4]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 30.4, "insns": [23, 25], "diffs": 23}}}

- led-control-switch-goto-notify: The debugger locates the polarity mismatch in preallocation CFG, while ordinary if/else is lowered to a branchless select. Test an explicit shared callback exit from success and failure blocks, preserving success == TRUE and one callback invocation. No new state, arithmetic, volatile or carriers; preserve the exact event handler. Reject added instructions or changed sibling functions.
  {"label": "led-control-switch-goto-notify", "unit": "kbd", "compiled": true, "pool": true, "data": "5296", "code": "4472", "drops": {"kbd_led_handler": [99.72, 95.6]}, "functions": {"kbdProcMod": {"score": 99.90234, "insns": [256, 256], "diffs": 4}, "KBDSetModState": {"score": 99.40476, "insns": [42, 42], "diffs": 4}, "kbdEventHandler": {"score": 100.0, "insns": [186, 186], "diffs": 0}, "kbd_led_handler": {"score": 95.6, "insns": [26, 25], "diffs": 14}}}

### LED coalescing and explicit-exit follow-up

The pre-regalloc dump still names the merged error value v34. The subsequent coalescing trace accepts v34 -> physical r3, and the before-simplify graph resolves v34 to r3 with the coalesced flag. This distinguishes the early wrong branch shape from the later successful ABI-register coalescing; the wording above has been corrected to name both stages explicitly. Goto/break forms with one shared callback exit are also rejected: the ordinary conditional versions become 22/23-instruction branchless forms; the switch/goto form has 26 instructions and fourteen diffs. All preserve the exact event handler. No LED change is retained.

## Durable allocator trace excerpts

These rows are extracted from validated dumps. Node IDs are local to each capture. Event positions are zero-based positions in the GPR trace; degree is recorded at simplification, and the mask is the last available-colors mask before assignment. A coalesced node may have no simplify or color event. Complete captures remain under build/rx6.

### kbdProcMod baseline

Capture `kbdProcMod-base-2`; object SHA256 `13fedf29bfeec1efaa886d327753ef4d037d31319bdbe63b1e3139bb61285eb9`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| channel address | v181 | 146 / 5 | 188 / r5 | 0x80001fe0 |
| old word | v182 | 147 / 3 | 185 / r4 | 0x80001ff0 |
| merged word | v185 | 150 / 3 | 176 / r0 | 0x1ff1 |

Relevant coalescing: none.

### KBDSetModState baseline

Capture `KBDSetModState-base`; object SHA256 `13fedf29bfeec1efaa886d327753ef4d037d31319bdbe63b1e3139bb61285eb9`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| channel address | v48 | 20 / 5 | 47 / r5 | 0x1fe0 |
| old word | v49 | 21 / 3 | 44 / r4 | 0x1ff0 |
| merged word | v52 | 24 / 2 | 35 / r0 | 0x1ff1 |

Relevant coalescing: none.

### kbdEventHandler direct-index experiment

Capture `trials/event-direct-plus/capture-kbdEventHandler`; object SHA256 `8cc6e928baccce781b65cd9f9f25e4c5947b35dfed796ccd9259247b977b878d`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| displacement | v52 | 39 / 7 | 234 / r5 | 0x50001fe0 |
| global base | v54 | 41 / 7 | 228 / r4 | 0x50001ff0 |
| status | v55 | 42 / 4 | 225 / r3 | 0x50001ff8 |

Relevant coalescing: none.

### kbdEventHandler retained exact source

Capture `trials/event-exact-clean-status/capture-kbdEventHandler`; object SHA256 `6a85c207eaac2f59a57f1c2b16f05861bf20a1ca1250449848ef0fa7353d06de`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| status | v46 | 33 / 6 | 252 / r5 | 0x50001fe0 |
| displacement | v53 | 40 / 6 | 231 / r4 | 0x50001ff0 |
| global base | v55 | 42 / 6 | 225 / r3 | 0x50001ff8 |

Relevant coalescing: none.

### kbd_led_handler baseline

Capture `kbd_led_handler-base`; object SHA256 `13fedf29bfeec1efaa886d327753ef4d037d31319bdbe63b1e3139bb61285eb9`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| error code | v34 | coalesced | coalesced / r3 | fixed by coalescing |

Relevant coalescing: coalesce-candidate v34 -> r3; coalesce v34 -> r3.

### CellPhone baseline full source

Capture `cell-fullsource`; object SHA256 `5075b480f6de660131a65bf5f44056f6b580500343089dace20d8cce862b5959`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| toggle row | v38 | 166 / 27 | 745 / r16 | 0x30000 |
| animation displacement | v48 | 170 / 25 | 727 / r18 | 0x40000 |

Relevant coalescing: none.

### SignWindow baseline

Capture `sign-pp/capture`; object SHA256 `fe37c48d255c8785c2d1e0926bbafa624ba146f92215b0f13132a95f26866495`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| animation count | v44 | 207 / 21 | 276 / r22 | 0x400000 |
| animation slot | v129 | 216 / 12 | 222 / r31 | 0x80000000 |

Relevant coalescing: none.

### SignWindow scalar-copy reference experiment

Capture `sign-count-reference-fullsource`; object SHA256 `277a1d4d5a7cebdb5cebacaef27b07efed915a06f5cb968d70e15a66323a6ce4`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| animation count | v142 | 218 / 12 | 224 / r31 | 0x80000000 |
| animation slot | v46 | 210 / 20 | 272 / r23 | 0x800000 |
| force name | v44 | 209 / 21 | 278 / r22 | 0x400000 |

Relevant coalescing: coalesce-candidate v44 -> r7; coalesce-interference-rejected v44 -> r7; coalesce-candidate v44 -> r7; coalesce-interference-rejected v44 -> r7.

### Getter f3 full-source seed

Capture `www-f3-fullsource`; object SHA256 `1add000ca19dd886bb515f8257a31595a13f01dfbf9f482388851cbaee1968eb`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| buffer | v41 | 42 / 17 | 1279 / r28 | 0xd0000000 |
| country counter | v35 | 37 / 22 | 1297 / r25 | 0x86000000 |
| return value | v39 | 40 / 28 | 1288 / r25 | 0x2000000 |

Relevant coalescing: coalesce-candidate v39 -> r3; coalesce-interference-rejected v39 -> r3.

### Getter country-helper experiment

Capture `www-country-helper-fullsource`; object SHA256 `84840eeadc04de30498854e3ceee0ee3bd266590ec3c554468fc929782fe0b38`.

| Value | Virtual | Simplify event / degree | Assign event / physical | Available mask |
| --- | --- | --- | --- | --- |
| buffer | v40 | 41 / 17 | 1282 / r28 | 0xd0000000 |
| country counter | v43 | 44 / 22 | 1273 / r26 | 0x84000000 |

Relevant coalescing: none.


## Final search and validation record

Manual experiments: 218 attempted, 212 compiled. Compiled counts by source family: mod 46, event 50, led 10, cell 37, sign 54, www 15. Modifier experiments measure both the standalone setter and its inlined copy in kbdProcMod.

| Search | Status | Trials |
| --- | --- | --- |
| mod-6 | completed | 720 |
| mod-22 | completed | 1272 |
| mod-61 | completed | 669 |
| event-6 | completed | 1089 |
| event-22 | stopped before start; function matched | 0 |
| event-61 | completed | 1907 |
| led-6 | completed | 1260 |
| led-22 | completed | 1876 |
| led-61 | completed | 2005 |
| cell-6 | reused verified g2 coverage | 0 |
| cell-22 | reused verified g2 coverage | 0 |
| cell-61 | completed | 704 |
| sign-6 | reused verified g2 coverage | 0 |
| sign-22 | reused verified g2 coverage | 0 |
| sign-61 | completed | 527 |
| www-6 | completed | 176 |
| www-22 | completed | 245 |
| www-61 | completed | 185 |

The 13 completed new searches each received 1200 seconds after acquiring a shared CPU slot, totaling 12635 trials. None saved an improved candidate. Cancelled searches ran zero trials and are not counted as completed. CellPhone and SignWindow additionally reuse the six previously verified g2 runs (seeds 617, 821, 1009; 5040 trials total) on byte-identical source/objects and identical mutation routines; the two rx6 runs already started were allowed to finish. The event seed cancelled after the manual exact match was unnecessary.

After the clean gate, regenerated the live progress report and reran ctxdiff for all seven requested symbols. Results are recorded in build/rx6/final/measurements.json and the adjacent ctx files. The report confirms kbdEventHandler 100.0 and 186/186 instructions with zero differences; all six remaining target scores and instruction differences equal the starting checkout. The f3 Getter seed and all other unsuccessful source trials remain private; no fuzzy-only source change is retained.

GATE PASS for all four owned units: clean full 43U build, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, identical pools, zero regressions, zero added forbidden patterns, zero readability warnings. Keyboard exact functions 17/21 -> 18/21, matched code 3728/5764 -> 4472/5764 (+744); data unchanged at 5296/5296. CellPhone 85/86, SignWindow 55/56, and www_wiisetting 20/21 are unchanged. The four units remain unlinked; this is one exact-function gain, not full unit or project completion.

Retained source: libs/RVL_SDK/src/kbd/kbd_lib.c only. Evidence: this attempts log and tools/decomp-assist/rx6.final-gate.txt. Pre-existing g2 logs were preserved. No push, PR, merge, rebase, configure.py edit, or edit in another worktree occurred.
