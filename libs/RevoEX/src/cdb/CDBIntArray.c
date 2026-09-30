#include <revolution/types.h>
#include <string.h>

typedef struct {
    int* values;
    int capacity;
    int size;
    int direction;
} CDBIntArray;

void CDBIntCopy(int* destination, const int* value) {
    *destination = *value;
}

int CDBIntCompare(const int* left, const int* right) {
    if (*left < *right) {
        return -1;
    }
    return *left != *right;
}

void CDBIntArrayInit(CDBIntArray* array, int* values, int capacity) {
    array->size = 0;
    array->direction = 1;
    array->capacity = capacity;
    array->values = values;
}

void CDBIntArraySetReverse(CDBIntArray* array) {
    array->direction = -1;
}

int CDBIntArraySize(CDBIntArray* array) {
    return array->size;
}

int* CDBIntArrayAt(CDBIntArray* array, int index) {
    return array->values + index;
}

BOOL CDBIntArrayEmpty(CDBIntArray* array) {
    return array->size == 0;
}

BOOL CDBIntArrayFull(CDBIntArray* array) {
    return array->capacity <= array->size;
}

int* CDBIntArrayEnd(CDBIntArray* array) {
    return array->values + array->size;
}

#pragma dont_inline on
int CDBIntArrayDicInsertR(CDBIntArray* array, int* value, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = ((*(value) < *(array->values + first)) ? -1 : (*(value) != *(array->values + first)));
        if (result < 0) {
            return first;
        }

        result = ((*(value) < *(array->values + last)) ? -1 : (*(value) != *(array->values + last)));
        index = last;
        if (result >= 0) {
            index = last + 1;
        }
        return index;
    }

    index = first + (last - first) / 2;
    result = ((*(value) < *(array->values + index)) ? -1 : (*(value) != *(array->values + index)));
    if (result < 0) {
        return CDBIntArrayDicInsertR(array, value, first, index);
    }
    if (result > 0) {
        return CDBIntArrayDicInsertR(array, value, index, last);
    }

    return index;
}

int* CDBIntArrayDicInsert(CDBIntArray* array, int* value) {
    int size = array->size;
    int index;
    int moveCount;
    int* record;
    int number;
    int stored;

    if (size == 0) {
        if (size < array->capacity) {
            record = array->values + size;
            *record = *value;
            array->size++;
        }
        return value;
    }

    if (array->capacity <= size) {
        if (array->direction == 1) {
            if (size != 0) {
                record = array->values + (size - 1);
            } else {
                record = array->values;
            }
            number = *value;
            stored = *record;
            if ((stored < number ? -1 : stored != number) < 0) {
                return record;
            }

            array->size--;
            index = CDBIntArrayDicInsertR(array, value, 0, array->size - 1);
            moveCount = (array->size - index) * sizeof(int);
            if (array->capacity <= array->size) {
                moveCount -= sizeof(int);
            }
            if (moveCount > 0) {
                memmove((array->values + (index + 1)), (array->values + index), moveCount);
            }
            *(array->values + index) = *value;
            if (array->size < array->capacity) {
                array->size++;
            }
            return (array->values + index);
        }

        record = array->values;
        number = *value;
        if ((number < *record ? -1 : number != *record) < 0) {
            return record;
        }

        array->size--;
        if (array->size >= 0 && array->capacity - 1 >= 0) {
            memmove(array->values, array->values + 1, array->size * sizeof(int));
        }
        index = CDBIntArrayDicInsertR(array, value, 0, array->size - 1);
        moveCount = (array->size - index) * sizeof(int);
        if (array->capacity <= array->size) {
            moveCount -= sizeof(int);
        }
        if (moveCount > 0) {
            memmove((array->values + (index + 1)), (array->values + index), moveCount);
        }
        *(array->values + index) = *value;
        if (array->size < array->capacity) {
            array->size++;
        }
        return (array->values + index);
    }

    index = CDBIntArrayDicInsertR(array, value, 0, size - 1);
    moveCount = (array->size - index) * sizeof(int);
    if (array->capacity <= array->size) {
        moveCount -= sizeof(int);
    }
    if (moveCount > 0) {
        memmove((array->values + (index + 1)), (array->values + index), moveCount);
    }
    *(array->values + index) = *value;
    if (array->size < array->capacity) {
        array->size++;
    }
    return (array->values + index);
}

int CDBIntArrayDicFindR(CDBIntArray* array, int* value, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = ((*(value) < *(array->values + first)) ? -1 : (*(value) != *(array->values + first)));
        if (result == 0) {
            return first;
        }

        result = ((*(value) < *(array->values + last)) ? -1 : (*(value) != *(array->values + last)));
        return result != 0 ? -1 : last;
    }

    index = first + (last - first) / 2;
    result = ((*(value) < *(array->values + index)) ? -1 : (*(value) != *(array->values + index)));
    if (result < 0) {
        return CDBIntArrayDicFindR(array, value, first, index);
    }
    if (result > 0) {
        return CDBIntArrayDicFindR(array, value, index, last);
    }

    return index;
}

#pragma dont_inline reset
int* CDBIntArrayDicFind(CDBIntArray* array, int* value) {
    int size = array->size;
    int index;

    if (size == 0) {
        return array->values + size;
    }

    index = CDBIntArrayDicFindR(array, value, 0, size - 1);
    if (index != -1) {
        return array->values + index;
    }

    return array->values + array->size;
}
