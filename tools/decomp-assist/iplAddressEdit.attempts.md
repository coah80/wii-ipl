
## get_friendinfo keep-vs-remat (88%)
Orig caches mString.mName (this+0x2b4) and mString.mDisplayText (this+0x2cc)
pointers in r29 across the FindPaneByName+set_textbox calls (extra addi + mr
reuse, +2 insns); mine rematerializes the member addresses inline at the call.
Orig this=r28, ptr webs=r29 (reused sequentially for both ptrs). Mine this=r29,
no ptr webs - the callee-reg web rotation differs by one position. Same
documented keep-vs-remat + web-ordering wall family as create/CDBRecordEncrypt.
