#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

extern const ziU16 nodeHeaderTable[16];

ziU32 ZiDAWGGetChild(ziU32 node) {
    ziU32 base;
    ziU16 header;
    ziS32 offset;

    base = node;
    header = nodeHeaderTable[*(ziU8*)node >> 4];
    if (((ziU32)header & 1) == 0) {
        node = 0;
    } else {
        if ((*(ziU8*)node & 0xf) == 0xf) {
            offset = 2;
        } else {
            offset = 1;
        }

        node += offset;
        if (((ziU32)header & 2) != 0) {
            if ((*(ziU8*)node & 0x80) != 0) {
                offset = ((*(ziU8*)node & 0x7f) << 16) +
                         ((((ziU32)*((ziU8*)node + 1) & 0xffff) << 8) + *((ziU8*)node + 2)) + 0x8000;
            } else {
                offset = (((ziU32)*(ziU8*)node & 0xffff) << 8) + (ziU32)*((ziU8*)node + 1);
            }
        } else if (((ziU32)header & 8) != 0) {
            if ((*(ziU8*)node & 0x80) != 0) {
                offset += 3;
            } else {
                offset += 2;
            }
        }

        node = base + offset;
    }

    return node;
}

typedef struct ziDawgLongOffset {
    ziU8 flags;
    ziU8 middle;
    ziU8 low;
} ziDawgLongOffset;
typedef char ziDawgLongOffsetSizeCheck[(sizeof(ziDawgLongOffset) == 3) ? 1 : -1];

ziU8* ZiDAWGGetSibling(ziU8* cursor) {
    ziS32 depth;
    ziU8* node;
    ziU16 header;
    ziS32 offset;

    depth = 0;
    node = cursor;
    offset = 0;
    header = nodeHeaderTable[cursor[0] >> 4];
    if ((header & 4) == 0) {
        return 0;
    } else {
        if ((header & 8) != 0) {
            if ((cursor[0] & 0xf) == 0xf) {
                cursor += 2;
            } else {
                cursor += 1;
            }

            if ((header & 2) != 0) {
                if ((*cursor & 0x80) != 0) {
                    cursor += 3;
                } else {
                    cursor += 2;
                }
            }

            if ((*cursor & 0x80) != 0) {
                node += (((const ziDawgLongOffset*)cursor)->flags & 0x7f) * 0x10000 +
                        (((ziU32)(ziU16)cursor[1] << 8) +
                         ((const ziDawgLongOffset*)cursor)->low) + 0x8000;
            } else {
                node = cursor[1] + (node + (ziU16)*cursor * 0x100);
            }
            return node;
        } else {
            do {
                header = nodeHeaderTable[cursor[0] >> 4];
                if ((cursor[0] & 0xf) == 0xf) {
                    cursor += 2;
                    offset += 2;
                } else {
                    cursor++;
                    offset++;
                }

                if ((header & 1) != 0) {
                    if ((header & 2) != 0) {
                        if ((*cursor & 0x80) != 0) {
                            cursor += 3;
                            offset += 3;
                        } else {
                            cursor += 2;
                            offset += 2;
                        }
                    } else {
                        depth++;
                    }
                }

                if ((header & 4) == 0) {
                    depth--;
                } else if ((header & 8) != 0) {
                    if ((*cursor & 0x80) != 0) {
                        cursor += 3;
                        offset += 3;
                    } else {
                        cursor += 2;
                        offset += 2;
                    }
                    depth--;
                }
            } while (0 < depth);

            return node + offset;
        }
    }

}

ziU8 ZiDAWGgetEOWattribute(ziU32 node) {
    return (nodeHeaderTable[*(ziU8*)node >> 4] & 0x10) > 0;
}

ziU32 ZiDAWGgetCHARattribute(zi8DawgCtx* context, ziU32 node, ziPtr __zi8_work_data) {
    ziU8 key;
    ziU32 attribute;

    if ((*(ziU8*)node & 0xf) == 0xf) {
        key = (ziU32)*((ziU8*)node + 1) + 0xf;
    } else {
        key = (ziU32)*(ziU8*)node & 0xf;
    }

    if (key > context->cap) {
        Zi8LogError(0x138b, __zi8_work_data);
        return 0;
    }

    attribute = key << 24;
    attribute |= ((ziU8*)context->characterFlags)[key] << 16;
    attribute |= (((ziU32)((ziU8*)context->characters)[key * 2] & 0xFFFF) << 8) +
                 ((ziU8*)context->characters + key * 2)[1];
    Zi8LogError(0x64, __zi8_work_data);
    return attribute;
}

ziU32 ZiDAWGGetGraph(ziPtr context) {
    return (((ziU32)((zi8DawgCtx*)context)->table[2] & 0xFFFF) << 8) +
           ((zi8DawgCtx*)context)->table[3] +
           ((ziU32)((zi8DawgCtx*)context)->table + 4);
}

ziU32 ZiDAWGGetGraphInfo(zi8DawgCtx* context, ziU8* entry, ziU16* keys) {
    ziU8 depth;
    ziU32 end;
    ziU32 graph;
    ziS32 result;

    graph = ZiDAWGGetGraph(context);
    result = 0;
    if ((((ziU16)entry[0] << 8) + entry[1]) != 0 || (((ziU16)entry[2] << 8) + entry[3]) != 0) {
        return 0;
    }
    end = (ziU32)(entry + (((ziU16)entry[4] << 8) + entry[5] + 1) * 10);
    entry += 10;
    depth = 0;
    while ((depth < 2) && (*keys != 0)) {
        if (*keys >= 0xeff1 && *keys <= 0xf010) {
            goto checkEntry;
            while (1) {
                if (*keys == (ziS32)(((ziU16)entry[2] << 8) + entry[3])) {
                    break;
                }
                entry += (((ziU16)entry[0] << 8) + entry[1]) * 10 + 10;
checkEntry:
                if (((ziU32)entry >= end) ||
                    (*keys == (ziS32)(((ziU16)entry[2] << 8) + entry[3]))) {
                    break;
                }
            }
        } else {
            return 0;
        }

        if ((ziU32)entry >= end) {
            return 0;
        }

        result = graph + (ziU32)entry[4] * 0x10000 + (((ziU16)entry[5] << 8) + entry[6]);
        context->endNode =
            graph + (ziU32)entry[7] * 0x10000 + (((ziU16)entry[8] << 8) + entry[9]);
        if (context->endNode == graph) {
            context->endNode = 0;
        }

        if ((((ziU16)entry[0] << 8) + entry[1]) == 0) {
            break;
        }

        end = (((ziU16)entry[0] << 8) + entry[1]) * 10 + ((ziU32)entry + 10);
        entry += 10;
        depth++;
        keys++;
    }

    return result;
}
