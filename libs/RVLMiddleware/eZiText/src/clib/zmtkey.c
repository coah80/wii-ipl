#include <zi8clib/zconvert.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zmtkey.h>

typedef struct ziUserKeyMap { ziWChar* upper[32]; ziWChar* lower[32]; } ziUserKeyMap;

ziU16 Zi8GetTableCount(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
ziU32 Zi8GetTableAddress(ziU8 language, ziU8 tableIndex, ziPtr __zi8_work_data);
ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data);

ziBool Zi8MapKeyCode(ziWChar character, ziWChar* output, ziPtr __zi8_work_data) {
    if (character == 0xeffa) {
        *output = 0;
    } else if ((character >= 0xeff1) && (character <= 0xeff9)) {
        *output = character - 0xeff0;
    } else if ((character >= 0xeffb) && (character <= 0xf010)) {
        *output = character - 0xeff1;
    } else {
        return 0;
    }
    return 1;
}

static ziU8 ziNumKeysWithChars(ziU8 language, ziPtr __zi8_work_data) {
    ziU16 tableCount;
    ziU8* table;
    ziU32 totalCharacters;
    ziU32 keyIndex;

    tableCount = Zi8GetTableCount(language, 0x1e, __zi8_work_data);
    table = (ziU8*)Zi8GetTableAddress(language, 0x1e, __zi8_work_data);
    if (tableCount == 0) {
        return 0x0c;
    }

    keyIndex = totalCharacters = 0;
    for (; (ziU16)keyIndex < 0x20; keyIndex++) {
        totalCharacters += table[(ziU16)keyIndex];
    }
    if ((ziS32)tableCount >= (((ziS32)(totalCharacters & 0xffff) * 4) + 0x20)) {
        return 0x20;
    }
    return 0x0c;
}

ziBool Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* chars, ziU8 mode, ziPtr __zi8_work_data) {
    ziU16 tableCount;
    ziU8 numKeys;
    ziU8* dataAddress;
    ziUserKeyMap* customTable;
    ziU16 charCount;
    ziU16 keyIndex;
    ziWChar* keyChars;

    dataAddress = 0;
    numKeys = ziNumKeysWithChars(language, __zi8_work_data);
    Zi8LogError(0x64, __zi8_work_data);
    *chars = 0;
    if (ZI_WORK->userKeys[language] != 0) {
        customTable = ZI_WORK->userKeys[language];
        if (!Zi8MapKeyCode(key, &key, __zi8_work_data)) {
            return 0;
        }
        keyChars = customTable->lower[key];
        for (keyIndex = 0; keyChars[(ziU16)keyIndex] != 0; keyIndex++) {
            chars[(ziU16)keyIndex] = keyChars[(ziU16)keyIndex];
        }
        chars[(ziU16)keyIndex] = 0;
        return 1;
    } else {
        if (mode == 1) {
            goto table_1e;
        }
        if ((tableCount = Zi8GetTableCount(language, 0x1d, __zi8_work_data)) == 0) {
            goto table_1e;
        }
        {
            dataAddress = (ziU8*)Zi8GetTableAddress(language, 0x1d, __zi8_work_data);
            goto tables_ready;
        }
table_1e:
        if ((tableCount = Zi8GetTableCount(language, 0x1e, __zi8_work_data)) != 0) {
            dataAddress = (ziU8*)Zi8GetTableAddress(language, 0x1e, __zi8_work_data);
        }
tables_ready:
        if (dataAddress == 0) {
            Zi8ReplaceLastError(0x962, __zi8_work_data);
            return 0;
        }
        if (!Zi8MapKeyCode(key, &key, __zi8_work_data) || (key >= numKeys)) {
            Zi8ReplaceLastError(300, __zi8_work_data);
            return 0;
        }

        keyIndex = tableCount = 0;
        for (; (ziU16)keyIndex < key; keyIndex++) {
            tableCount += dataAddress[(ziU16)keyIndex];
        }
        if ((charCount = (ziU8)dataAddress[key]) == 0) {
            return 0;
        }
        dataAddress = dataAddress + numKeys + (tableCount * 2);
        keyIndex = 0;
        for (; (ziU16)keyIndex < charCount; keyIndex++) {
            chars[(ziU16)keyIndex] = (ziU16)dataAddress[(ziU16)keyIndex * 2] |
                ((ziU16)dataAddress[((ziU16)keyIndex * 2) + 1] << 8);
        }
        chars[(ziU16)keyIndex] = 0;
        return 1;
    }
}

ziBool Zi8ChangeCharCase(ziBool upper, ziWChar* character, ziU8 language ZI_NEED_WORK) {
    ziU8 changed;
    ziU16 total;
    ziU16 tableCount;
    ziU8* dataAddress;
    ziUserKeyMap* customTables;
    ziU8 numKeys;
    ziS16 direction;
    ziU16 result;
    ziS32 keyIndex;
    ziPtr from;
    ziPtr to;
    ziS32 characterIndex;

    customTables = 0;
    dataAddress = 0;
    changed = 0;
    numKeys = 0x20;
    Zi8LogError(0x64, ZI_WORK);
    if (ZI_WORK->userKeys[language] != 0) {
        customTables = (ziUserKeyMap*)ZI_WORK->userKeys[language];
    } else if (ZI_WORK->customKeyMap != 0) {
        customTables = (ziUserKeyMap*)ZI_WORK->customKeyMap;
    } else {
        tableCount = Zi8GetTableCount(language, 0x1e, ZI_WORK);
        if (tableCount != 0) {
            dataAddress = (ziU8*)Zi8GetTableAddress(language, 0x1e, ZI_WORK);
            numKeys = ziNumKeysWithChars(language, ZI_WORK);
        } else {
            Zi8ReplaceLastError(0x138d, ZI_WORK);
            return 0;
        }
    }
    if (customTables != 0) {
        for (keyIndex = 0; (changed == 0) && (keyIndex < (ziS32)(ziU32)numKeys); keyIndex++) {
            if (upper != 0) {
                from = (ziPtr)customTables->lower[keyIndex];
                to = (ziPtr)customTables->upper[keyIndex];
            } else {
                from = (ziPtr)customTables->upper[keyIndex];
                to = (ziPtr)customTables->lower[keyIndex];
            }
            if ((from != 0) && (to != 0)) {
                for (characterIndex = 0; ((ziU16)((ziS16*)from)[characterIndex]) != 0; characterIndex++) {
                    if ((ziU16)((ziS16*)from)[characterIndex] == *character) {
                        *character = (ziU16)((ziWChar*)to)[characterIndex];
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }
    else if (dataAddress != 0) {
        total = 0;
        for (keyIndex = 0; keyIndex < (ziS32)(ziU32)numKeys; keyIndex++) {
            total += dataAddress[keyIndex];
        }
        dataAddress = dataAddress + numKeys;
        direction = 1;
        if (upper == 0) {
            dataAddress = dataAddress + ((ziU32)total * 2);
            direction = -1;
        }
        for (keyIndex = 0; keyIndex < (ziS32)(ziU32)total; keyIndex++) {
            tableCount = (ziU16)(dataAddress[(keyIndex * 2)] |
                ((ziU16)dataAddress[(keyIndex * 2) + 1] << 8));
            if (tableCount == *character) {
                dataAddress = dataAddress + ((ziS32)direction * ((ziU32)total * 2));
                *character = (ziU16)(dataAddress[(keyIndex * 2)] |
                    ((ziU16)dataAddress[(keyIndex * 2) + 1] << 8));
                changed = 1;
                break;
            }
        }
    }
    if (changed == 0) {
        result = 0;
        if (upper != 0) {
            if (((*character >= 0x61) && (*character <= 0x7a)) || ((*character >= 0xf1) && (*character <= 0xf6)) ||
                ((*character >= 0xf8) && (*character <= 0xfe)) || ((*character >= 0xe0) && (*character <= 0xef))) {
                result = *character - 0x20;
            } else if (*character == 0xff) {
                result = 0x178;
            }
        } else {
            if (((*character >= 0x41) && (*character <= 0x5a)) || ((*character >= 0xd1) && (*character <= 0xd6)) ||
                ((*character >= 0xd8) && (*character <= 0xde)) || ((*character >= 0xc0) && (*character <= 0xcf))) {
                result = *character + 0x20;
            } else if (*character == 0x178) {
                result = 0xff;
            }
        }

        if ((result != 0) && Zi8ConvertWC2UC(result, language, ZI_WORK)) {
            *character = result;
            changed = 1;
        }
    }
    return changed;
}
