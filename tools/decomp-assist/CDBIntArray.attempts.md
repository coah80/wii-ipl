# CDBIntArray attempts

Baseline 0/13, 0/1556 code. No data sections.

Started with scalar copies, ordered comparison, array descriptors and recursive dictionary operations. Explicit full test operand order and unequal return match the nine basic methods. Initial recursive auto-inlining expanded searches to 412 instructions; disabling recursive inlining and using direct scalar comparisons restores tail calls. Adapted the existing sibling record-key array implementation, using the same capacity and reverse-direction behavior. The same ordinary dont_inline pragma as that sibling preserves the recursive searches. No helper retained solely for emission.

CDBIntArrayDicInsertR | return right index plus comparison | (93.548386, -5) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicInsertR | explicit values in comparisons | (98.30645, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicInsertR | middle first local declaration | (98.30645, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicFindR | direct array indexing | (94.19355, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicFindR | inverted leaf comparison | (100.0, -2) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicFindR | comparison first declaration | (94.19355, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicInsertR | leaf early return | (98.30645, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicInsertR | leaf result conditional expression | (93.548386, -3) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicInsertR | comparison variable before index | (93.548386, -3) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicFindR | leaf positive branch first | (94.19355, -9999) | src 0xfc base 0xf8 insns 63/62
CDBIntArrayDicFindR | leaf conditional expression | (100.0, 0) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicInsert | direct scalar copies | (99.60317, -16) | src 0x2f4 base 0x2f4 insns 189/189
CDBIntArrayDicInsert | record pointer before scalar temporaries | (94.89418, -9999) | src 0x300 base 0x2f4 insns 192/189
CDBIntArrayDicInsert | signed move byte counts | (94.89418, -9999) | src 0x300 base 0x2f4 insns 192/189
CDBIntArrayDicInsertR | separate result index | (100.0, 0) | src 0xf8 base 0xf8 insns 62/62
CDBIntArrayDicInsert | local value loaded before ordered comparisons | (99.78836, -5) | src 0x2f4 base 0x2f4 insns 189/189
CDBIntArrayDicInsert | record local first declaration | (99.60317, -14) | src 0x2f4 base 0x2f4 insns 189/189
CDBIntArrayDicInsert | comparison expression evaluates stored value first | (99.49735, -16) | src 0x2f4 base 0x2f4 insns 189/189
CDBIntArrayDicInsert | stored element captured after incoming value | (100.0, 0) | src 0x2f4 base 0x2f4 insns 189/189

Recursion trials additionally included recursive calls, goto iteration, source-level ordered comparisons and separate leaf return index. Find tried empty end return, found-first branch and shared result before adopting the sibling method; it now matches.

Final: all 13 functions instruction-exact, 1556/1556 code bytes, no data sections. Full gate and pool pass.
