#include <zi8clib/zconvert.h>
#include <zi8clib/zierror.h>

typedef struct ziConversionRange {
    ziU16 first, last;
    union { ziPtr table; ziU32 character; } result;
} ziConversionRange;
typedef struct ziConversionRangeTable {
    ziU16 count, flags;
    ziConversionRange* entries;
} ziConversionRangeTable;
typedef struct ziConversionTables {
    ziU16 first, last;
    ziWChar* unicode;
    ziConversionRangeTable reverse, keys, cases;
} ziConversionTables;
typedef struct ziConversionEntry {
    ziU8 first[2], last[2], flags[2], value[2];
} ziConversionEntry;
typedef struct ziConversionTable {
    ziU8 count[2], flags[2], minimum[2], maximum[2];
    ziConversionEntry entries[1];
} ziConversionTable;
const ziConversionTables Zi8CvrtTables = {0};
ziU16 Zi8GetTableCount(ziU8, ziU8 ZI_NEED_WORK);
ziPtr Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
ziWChar Zi8ConvertUC2UserKey(ziChar, ziU8 ZI_NEED_WORK);

ziWChar Zi8ConvertUC2WC(ziChar character, ziU8 language ZI_NEED_WORK) {
    ziU8* table;
    ziWChar* mapped;
    ziU8* cursor;
    ziU16 first, last;
    const ziConversionTables* defaults;
    if (character == 0) {
        Zi8LogError(0x133, __zi8_work_data);
        return 0;
    }
    if (Zi8GetTableCount(language, 6, __zi8_work_data) != 0) {
        table = Zi8GetTableAddress(language, 6, __zi8_work_data);
        if (table == 0) {
            Zi8LogError(0x6A4, __zi8_work_data);
            return 0;
        }
        cursor = table;
        first = (ziU16)cursor[0] << 8 | cursor[1];
        last = (ziU16)cursor[2] << 8 | cursor[3];
        if (character < first || character > last) {
            Zi8LogError(0x132, __zi8_work_data);
            return 0;
        }
        cursor += (character - first) * 2 + 8;
        Zi8LogError(100, __zi8_work_data);
        return (ziU16)cursor[0] << 8 | cursor[1];
    }
    defaults = &Zi8CvrtTables;
    if (defaults == 0) {
        Zi8LogError(0x6A4, __zi8_work_data);
        return 0;
    }
    if (character < defaults->first || character > defaults->last) {
        Zi8LogError(0x132, __zi8_work_data);
        return 0;
    }
    mapped = defaults->unicode;
    Zi8LogError(100, __zi8_work_data);
    return mapped[character - defaults->first];
}
ziChar Zi8ConvertWC2UC(ziWChar character, ziU8 language ZI_NEED_WORK) {
    ziU16 index, count, first, last, value;
    ziConversionTable* table;
    const ziConversionRangeTable* defaults;
    ziConversionRange* ranges;
    ziConversionEntry* entry;
    ziU8* cursor;
    if (character == 0) {
        Zi8LogError(0x133, __zi8_work_data);
        return 0;
    }
    if (Zi8GetTableCount(language, 7, __zi8_work_data) != 0) {
        table = Zi8GetTableAddress(language, 7, __zi8_work_data);
        if (table == 0) {
            Zi8LogError(0x6AE, __zi8_work_data);
            return 0;
        }
        entry = table->entries;
        count = (ziU16)table->count[0] << 8 | table->count[1];
        for (index = 0; index < count; index++) {
            first = ((ziU16)entry->first[0] << 8 | entry->first[1]);
            last = (ziU16)entry->last[0] << 8 | entry->last[1];
            if (first <= character && character <= last) {
                value = ((ziU16)entry->value[0] << 8 | entry->value[1]);
                if (first == last) {
                    Zi8LogError(100, __zi8_work_data);
                    return value & 0xFF;
                }
                Zi8LogError(100, __zi8_work_data);
                return ((ziU8*)table->entries)[character + value - first];
            }
            entry++;
        }
    } else {
        defaults = &Zi8CvrtTables.reverse;
        if (defaults == 0) {
            Zi8LogError(0x6AE, __zi8_work_data);
            return 0;
        }
        ranges = defaults->entries;
        for (index = 0; index < defaults->count; index++) {
            if (ranges[index].first <= character && character <= ranges[index].last) {
                Zi8LogError(100, __zi8_work_data);
                if (ranges[index].first == ranges[index].last) return ranges[index].result.character & 0xFF;
                return ((ziU8*)ranges[index].result.table)[character - ranges[index].first];
            }
        }
    }
    Zi8LogError(0x6C2, __zi8_work_data);
    return 0;
}
ziWChar Zi8ConvertUC2Key(ziChar character, ziU8 language ZI_NEED_WORK) {
    ziU16 count, index, first, last;
    ziU32 key = 0;
    ziConversionTable* table;
    const ziConversionRangeTable* defaults;
    ziConversionRange* ranges;
    ziConversionEntry* entry;
    ziU8* cursor;
    if (character == 0) {
        Zi8LogError(0x133, __zi8_work_data);
        return 0;
    }
    if (ZI_WORK->userKeys[language] != 0) return Zi8ConvertUC2UserKey(character, language, __zi8_work_data);
    if (Zi8GetTableCount(language, 8, __zi8_work_data) != 0) {
        table = Zi8GetTableAddress(language, 8, __zi8_work_data);
        if (table == 0) {
            Zi8LogError(0x6B8, __zi8_work_data);
            return 0;
        }
        entry = table->entries;
        count = (ziU16)table->count[0] << 8 | table->count[1];
        for (index = 0; index < count; index++) {
            first = ((ziU16)entry->first[0] << 8 | entry->first[1]);
            last = (ziU16)entry->last[0] << 8 | entry->last[1];
            if (first <= character && character <= last) {
                key = ((ziU16)entry->value[0] << 8 | entry->value[1]);
                if (first != last) {
                    cursor = (ziU8*)table->entries + key + (character - first) * 2;
                    key = (ziU16)cursor[0] << 8 | cursor[1];
                }
                break;
            }
            entry++;
        }
    } else {
        defaults = &Zi8CvrtTables.keys;
        if (defaults == 0) {
            Zi8LogError(0x6B8, __zi8_work_data);
            return 0;
        }
        ranges = defaults->entries;
        for (index = 0; index < defaults->count; index++) {
            if (ranges[index].first <= character && character <= ranges[index].last) {
                if (ranges[index].first == ranges[index].last) key = ranges[index].result.character & 0xFF;
                else key = ((ziWChar*)ranges[index].result.table)[character - ranges[index].first];
                break;
            }
        }
    }
    if (key == 0) {
        Zi8LogError(0x6C2, __zi8_work_data);
        key = 0xEFF1;
    } else Zi8LogError(100, __zi8_work_data);
    return key;
}
ziWChar Zi8ConvertWC2Key(ziWChar character, ziU8 language ZI_NEED_WORK) {
    return Zi8ConvertUC2Key(Zi8ConvertWC2UC(character, language, __zi8_work_data), language, __zi8_work_data);
}
