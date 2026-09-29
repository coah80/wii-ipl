#include <private/cdb.h>
#include <revolution/cdb.h>

#include <string.h>

typedef struct _CDBIntArray {
    int* records;
    int capacity;
    int size;
    int reverse;
} CDBIntArray;

void CDBIntCopy(int* i1, const int* i2) {
    *i1 = *i2;
}

int CDBIntCompare(int* i1, int* i2) {
    if (*i1 < *i2) {
        return -1;
    }

    return *i1 != *i2;
}

void CDBIntArrayInit(CDBIntArray* recordArray, int* records, int capacity) {
    recordArray->size = 0;
    recordArray->reverse = 1;
    recordArray->capacity = capacity;
    recordArray->records = records;
}

void CDBIntArraySetReverse(CDBIntArray* recordArray) {
    recordArray->reverse = -1;
}

int CDBIntArraySize(CDBIntArray* recordArray) {
    return recordArray->size;
}

int* CDBIntArrayAt(CDBIntArray* recordArray, int index) {
    return recordArray->records + index;
}

BOOL CDBIntArrayEmpty(CDBIntArray* recordArray) {
    return recordArray->size == 0;
}

BOOL CDBIntArrayFull(CDBIntArray* recordArray) {
    return recordArray->capacity <= recordArray->size;
}

int* CDBIntArrayEnd(CDBIntArray* recordArray) {
    return recordArray->records + recordArray->size;
}

int CDBIntArrayDicInsertR(CDBIntArray* recordArray, int* record, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = CDBIntCompare(record, recordArray->records + first);
        if (result < 0) {
            return first;
        }

        result = CDBIntCompare(record, recordArray->records + last);
        if (result >= 0) {
            result = last + 1;
        } else {
            result = last;
        }
        return result;
    }

    index = first + (last - first) / 2;
    result = CDBIntCompare(record, recordArray->records + index);
    if (result < 0) {
        return CDBIntArrayDicInsertR(recordArray, record, first, index);
    }
    if (result > 0) {
        return CDBIntArrayDicInsertR(recordArray, record, index, last);
    }

    return index;
}

int* CDBIntArrayDicInsert(CDBIntArray* recordArray, int* record) {
    register int* elem;
    int size = recordArray->size;
    int index;
    int moveCount;

    if (size == 0) {
        if (size < recordArray->capacity) {
            elem = recordArray->records + size;
            CDBIntCopy(elem, record);
            recordArray->size++;
        }
        return record;
    }

    if (recordArray->capacity <= size) {
        if (recordArray->reverse == 1) {
            if (size != 0) {
                elem = recordArray->records + (size - 1);
            } else {
                elem = recordArray->records;
            }
            if (CDBIntCompare(elem, record) < 0) {
                return elem;
            }

            recordArray->size--;
            index = CDBIntArrayDicInsertR(recordArray, record, 0, recordArray->size - 1);
            moveCount = (recordArray->size - index) * sizeof(int);
            if (recordArray->capacity <= recordArray->size) {
                moveCount -= sizeof(int);
            }
            if (moveCount > 0) {
                memmove(recordArray->records + (index + 1), recordArray->records + index, moveCount);
            }
            CDBIntCopy(recordArray->records + index, record);
            if (recordArray->size < recordArray->capacity) {
                recordArray->size++;
            }
            return recordArray->records + index;
        }

        elem = recordArray->records;
        if (CDBIntCompare(record, elem) < 0) {
            return elem;
        }

        recordArray->size--;
        if (recordArray->size >= 0 && recordArray->capacity - 1 >= 0) {
            memmove(recordArray->records, recordArray->records + 1, recordArray->size * sizeof(int));
        }
        index = CDBIntArrayDicInsertR(recordArray, record, 0, recordArray->size - 1);
        moveCount = (recordArray->size - index) * sizeof(int);
        if (recordArray->capacity <= recordArray->size) {
            moveCount -= sizeof(int);
        }
        if (moveCount > 0) {
            memmove(recordArray->records + (index + 1), recordArray->records + index, moveCount);
        }
        CDBIntCopy(recordArray->records + index, record);
        if (recordArray->size < recordArray->capacity) {
            recordArray->size++;
        }
        return recordArray->records + index;
    }

    index = CDBIntArrayDicInsertR(recordArray, record, 0, recordArray->size - 1);
    moveCount = (recordArray->size - index) * sizeof(int);
    if (recordArray->capacity <= recordArray->size) {
        moveCount -= sizeof(int);
    }
    if (moveCount > 0) {
        memmove(recordArray->records + (index + 1), recordArray->records + index, moveCount);
    }
    CDBIntCopy(recordArray->records + index, record);
    if (recordArray->size < recordArray->capacity) {
        recordArray->size++;
    }
    return recordArray->records + index;
}

int CDBIntArrayDicFindR(CDBIntArray* recordArray, int* record, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = CDBIntCompare(record, recordArray->records + first);
        if (result == 0) {
            return first;
        }

        result = CDBIntCompare(record, recordArray->records + last);
        if (result != 0) {
            result = -1;
        } else {
            result = last;
        }
        return result;
    }

    index = first + (last - first) / 2;
    result = CDBIntCompare(record, recordArray->records + index);
    if (result < 0) {
        return CDBIntArrayDicFindR(recordArray, record, first, index);
    }
    if (result > 0) {
        return CDBIntArrayDicFindR(recordArray, record, index, last);
    }

    return index;
}

int* CDBIntArrayDicFind(CDBIntArray* recordArray, int* record) {
    int size = recordArray->size;
    int index;

    if (size == 0) {
        return recordArray->records + size;
    }

    index = CDBIntArrayDicFindR(recordArray, record, 0, size - 1);
    if (index != -1) {
        return recordArray->records + index;
    }

    return recordArray->records + recordArray->size;
}

static void CDBDeadTest1(void) {
    CDBReportError("TESTSTRING1 static-fn\n");
}

void CDBDeadTest2(void) {
    if (0) {
        CDBReportError("TESTSTRING2 if0\n");
    }
    (void)"TESTSTRING3 voidexpr\n";
}
