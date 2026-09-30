# MyTiLetterForm attempts

- Initial reconstruction: 24/26 exact; create had three constructor-store ordering differences, drawBody four literal-offset differences. No source existed at the configured path.
- Pool: the fourth animation group is in the neighboring extracted tiHwKeyboard .rodata range, starting four bytes after 0x81616B88. Its real N_SendMes entry has one animation, animationFiles[5]. Reconstructing all four ordinary groups and correcting drawBody's conditional T_TouchLetter and unconditional N_SendMes references made the 13-string pool identical and drawBody exact.
- create attempt 1: two direct EventHandler members produced three reordered stores (179/179 instructions).
- create attempt 2: memo EventHandler base with the second pointer in letter EventHandler reduced the difference to two stores.
- create attempt 3: both pointers initialized by the memo constructor before the letter vtable store produced zero differences. Restoring the actual inputform EventHandler -> memo EventHandler -> letter EventHandler hierarchy preserves zero differences.
- Vtables: typed shared declarations behind MYTILETTERFORM_IMPLEMENTATION corrected create, scrolling, sound, cursor-cache signatures. Ordering class declarations EventHandler, AnmPane, WholePane, PicPane reproduced the four owned vtable positions without forced data.
- All 26 functions are instruction exact. The owned .data bytes are identical after clearing relocations; the only differing relocation is the malformed concatenated isEnableCursorCache/getStartPos name in the target, plus four relocations in the ordinary weak gui EventHandler vtable, which is zero-filled in the extracted original.
- .rodata is 784 bytes versus extracted 720; all 720 prefix bytes and normalized relocations agree. The remaining 64 bytes are the final null of group three and all of group four, visibly misassigned to tiHwKeyboard in splits.txt. No split, symbol or neighboring source changes were made.
- .sdata is 66 bytes versus extracted 72; every prefix byte agrees. The six trailing target zeros were not recreated with padding. .sdata2 is 32/32 identical. Pool is identical.
