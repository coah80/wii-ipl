#include <private/cdb.h>
#include <revolution/cdb.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma push
#pragma section sconst_type ".sdata"
extern const char lbl_816979E8 __attribute__((aligned(8))) = '/';
#pragma pop

void CDBFSConcatenatePath(char* path, const char* concatPath) {
    strcat(path, lbl_816979E8);
    strcat(path, concatPath);
}

BOOL CDBFSIsYearDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 4 + 1) == 4) {
        if (isdigit(dirName[0]) && isdigit(dirName[1]) && isdigit(dirName[2]) && isdigit(dirName[3])) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CDBFSIsMonthDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 2 + 1) == 2) {
        if (isdigit(dirName[0]) && isdigit(dirName[1])) {
            int val = atoi(dirName);
            if (val >= 0 && val <= 11) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL CDBFSIsDayDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 2 + 1) == 2) {
        if (isdigit(dirName[0]) && isdigit(dirName[1])) {
            int val = atoi(dirName);
            if (val >= 1 && val <= 31) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL CDBFSIsHourDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 2 + 1) == 2) {
        if (isdigit(dirName[0]) && isdigit(dirName[1])) {
            int val = atoi(dirName);
            if (val >= 0 && val <= 23) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL CDBFSIsMinuteDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 2 + 1) == 2) {
        if (isdigit(dirName[0]) && isdigit(dirName[1])) {
            int val = atoi(dirName);
            if (val >= 0 && val <= 59) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL CDBFSIsCodeDirName(char* dirName) {
    if (CDBSafeStrLen(dirName, 7 + 1) == 7) {
        if (dirName[4] == '_') {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CDBFSIsTypeDirName(char* dirName) {
    int strLen1 = CDBSafeStrLen(dirName, 5 + 1);
    int strLen2 = CDBSafeStrLen(dirName, 2 + 1);

    BOOL result;

    if (strLen2 == 1 && dirName[0] == '.') {
        result = TRUE;
    } else if (strLen2 == 2 && dirName[0] == '.' && dirName[1] == '.') {
        result = TRUE;
    } else {
        result = FALSE;
    }

    if (!result) {
        if (strLen1 < 6) {
            return TRUE;
        }
    }

    return FALSE;
}

#ifdef __MWERKS__
asm BOOL CDBFSIsCDBFileOnSD(register char* fileName) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0xd
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl CDBSafeStrLen
    cmpwi r3, 0xc
    bne CDBFSIsCDBFileOnSD_invalid
    lis r4, _current_locale@ha
    li r0, 0x4
    addi r4, r4, _current_locale@l
    mr r3, r31
    lwz r6, 0x38(r4)
    li r7, 0
    mtctr r0
CDBFSIsCDBFileOnSD_loop:
    lbz r5, 0(r3)
    li r0, 0
    extsb. r5, r5
    blt CDBFSIsCDBFileOnSD_digit1_invalid
    cmpwi r5, 0x100
    blt CDBFSIsCDBFileOnSD_digit1_check
CDBFSIsCDBFileOnSD_digit1_invalid:
    li r0, 1
CDBFSIsCDBFileOnSD_digit1_check:
    cmpwi r0, 0
    beq CDBFSIsCDBFileOnSD_digit1_map
    li r0, 0
    b CDBFSIsCDBFileOnSD_digit1_done
CDBFSIsCDBFileOnSD_digit1_map:
    lwz r4, 8(r6)
    slwi r0, r5, 1
    lhzx r0, r4, r0
    rlwinm r0, r0, 0, 21, 21
CDBFSIsCDBFileOnSD_digit1_done:
    cmpwi r0, 0
    bne CDBFSIsCDBFileOnSD_first_next
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_first_next:
    lbz r5, 1(r3)
    li r0, 0
    extsb. r5, r5
    blt CDBFSIsCDBFileOnSD_digit2_invalid
    cmpwi r5, 0x100
    blt CDBFSIsCDBFileOnSD_digit2_check
CDBFSIsCDBFileOnSD_digit2_invalid:
    li r0, 1
CDBFSIsCDBFileOnSD_digit2_check:
    cmpwi r0, 0
    beq CDBFSIsCDBFileOnSD_digit2_map
    li r0, 0
    b CDBFSIsCDBFileOnSD_digit2_done
CDBFSIsCDBFileOnSD_digit2_map:
    lwz r4, 8(r6)
    slwi r0, r5, 1
    lhzx r0, r4, r0
    rlwinm r0, r0, 0, 21, 21
CDBFSIsCDBFileOnSD_digit2_done:
    cmpwi r0, 0
    bne CDBFSIsCDBFileOnSD_pair_next
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_pair_next:
    addi r7, r7, 1
    addi r3, r3, 2
    bdnz CDBFSIsCDBFileOnSD_loop
    lbz r0, 8(r31)
    cmpwi r0, 0x2e
    beq CDBFSIsCDBFileOnSD_extension
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_extension:
    lbz r4, 9(r31)
    li r0, 0
    extsb. r4, r4
    blt CDBFSIsCDBFileOnSD_digit3_invalid
    cmpwi r4, 0x100
    blt CDBFSIsCDBFileOnSD_digit3_check
CDBFSIsCDBFileOnSD_digit3_invalid:
    li r0, 1
CDBFSIsCDBFileOnSD_digit3_check:
    cmpwi r0, 0
    beq CDBFSIsCDBFileOnSD_digit3_map
    li r0, 0
    b CDBFSIsCDBFileOnSD_digit3_done
CDBFSIsCDBFileOnSD_digit3_map:
    lwz r3, 8(r6)
    slwi r0, r4, 1
    lhzx r0, r3, r0
    rlwinm r0, r0, 0, 21, 21
CDBFSIsCDBFileOnSD_digit3_done:
    cmpwi r0, 0
    bne CDBFSIsCDBFileOnSD_digit4
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_digit4:
    lbz r4, 0xa(r31)
    li r0, 0
    extsb. r4, r4
    blt CDBFSIsCDBFileOnSD_digit4_invalid
    cmpwi r4, 0x100
    blt CDBFSIsCDBFileOnSD_digit4_check
CDBFSIsCDBFileOnSD_digit4_invalid:
    li r0, 1
CDBFSIsCDBFileOnSD_digit4_check:
    cmpwi r0, 0
    beq CDBFSIsCDBFileOnSD_digit4_map
    li r0, 0
    b CDBFSIsCDBFileOnSD_digit4_done
CDBFSIsCDBFileOnSD_digit4_map:
    lwz r3, 8(r6)
    slwi r0, r4, 1
    lhzx r0, r3, r0
    rlwinm r0, r0, 0, 21, 21
CDBFSIsCDBFileOnSD_digit4_done:
    cmpwi r0, 0
    bne CDBFSIsCDBFileOnSD_digit5
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_digit5:
    lbz r4, 0xb(r31)
    li r0, 0
    extsb. r4, r4
    blt CDBFSIsCDBFileOnSD_digit5_invalid
    cmpwi r4, 0x100
    blt CDBFSIsCDBFileOnSD_digit5_check
CDBFSIsCDBFileOnSD_digit5_invalid:
    li r0, 1
CDBFSIsCDBFileOnSD_digit5_check:
    cmpwi r0, 0
    beq CDBFSIsCDBFileOnSD_digit5_map
    li r0, 0
    b CDBFSIsCDBFileOnSD_digit5_done
CDBFSIsCDBFileOnSD_digit5_map:
    lwz r3, 8(r6)
    slwi r0, r4, 1
    lhzx r0, r3, r0
    rlwinm r0, r0, 0, 21, 21
CDBFSIsCDBFileOnSD_digit5_done:
    cmpwi r0, 0
    bne CDBFSIsCDBFileOnSD_valid
    li r3, 0
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_valid:
    li r3, 1
    b CDBFSIsCDBFileOnSD_return
CDBFSIsCDBFileOnSD_invalid:
    li r3, 0
CDBFSIsCDBFileOnSD_return:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
#else
BOOL CDBFSIsCDBFileOnSD(char* fileName) {
    if (CDBSafeStrLen(fileName, 12 + 1) == 12) {
        char* ptr = fileName;
        char i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                if (!isxdigit(ptr[j])) {
                    return FALSE;
                }
            }
            ptr += 2;
        }

        if (fileName[8] != '.') {
            return FALSE;
        }

        for (i = 9; i < 12; i++) {
            if (!isxdigit(fileName[i])) {
                return FALSE;
            }
        }
        return TRUE;
    }

    return FALSE;
}
#endif

BOOL CDBFSIsMCGCDirNameOnSD(char* dirName) {
    if (CDBSafeStrLen(dirName, 7 + 1) == 7) {
        if (dirName[4] == '_') {
            return TRUE;
        }
    }

    return FALSE;
}

// Duplicate of CDBFSIsTypeDirNameOn
BOOL CDBFSIsTypeDirNameOnSD(char* dirName) {
    int strLen1 = CDBSafeStrLen(dirName, 5 + 1);
    int strLen2 = CDBSafeStrLen(dirName, 2 + 1);

    BOOL result;

    if (strLen2 == 1 && dirName[0] == '.') {
        result = TRUE;
    } else if (strLen2 == 2 && dirName[0] == '.' && dirName[1] == '.') {
        result = TRUE;
    } else {
        result = FALSE;
    }

    if (!result) {
        if (strLen1 < 6) {
            return TRUE;
        }
    }

    return FALSE;
}
