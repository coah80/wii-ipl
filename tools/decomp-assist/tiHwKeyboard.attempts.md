# tiHwKeyboard

Baseline: 7/10 exact, 1676/4596 code bytes, 296/568 data bytes. Three functions were absent. Existing assembly bodies and pinned data were not expanded.

- updateTappingShift_: typed KeySet iteration and inherited keyboard fields reproduce 145/145 instructions exactly on the first implementation.
- updateRepeatKey_ attempt 1: scalar space command produced 182/180 instructions and an extra saved register.
- attempt 2: copying a static NavigationCommand aggregate produced 184/180 and a larger frame.
- attempt 3: initialize the local NavigationCommand with {8, modifierState}; 180/180, one mask difference when using a boolean modifier.
- attempt 4: preserve the masked u32 modifier; 180/180, zero differences.
- updateTriggerKey_ attempt 1: copying the static character-input template was hoisted; 407/405, extra frame space.
- attempt 2: separate aggregate assignment and wider character temporary: 403/405, register and stack differences.
- attempt 3: local navigation aggregate and numeric range simplification: 405/405, 284 differences, mostly allocation/frame offsets.
- attempt 4: initialize the character aggregate locally; 400/405, template copy now occurs inside the loop.
- attempt 5: accurate u32 GetWChar declaration and explicit wchar_t narrowing; restored numeric filter switch. 404/405, quote handling remained.
- attempt 6: quote switch: 405/405, 14 branch differences.
- attempt 7: wchar_t quote-pair ranges: 404/405, missing high-half addition.
- attempt 8: express modular quote distances as character + (0x10000 - quote); 405/405, zero differences.

Data: the first 64 extracted .rodata bytes belong to the preceding letter animation table (documented in MyTiLetterForm.attempts.md). They were not recreated as hardware dummy data. The real hardware key map and character-input template use ordinary typed C++ objects. Moving the key map after its consumer preserves all exact functions; moving country definitions after their assembly consumer failed compilation and was reverted. Target .bss is unreferenced extracted space; .sdata2 includes trailing zeros. No padding or force-active objects were added. Pools remain identical. Shared changes are isolated behind TIHWKEYBOARD_IMPLEMENTATION.
