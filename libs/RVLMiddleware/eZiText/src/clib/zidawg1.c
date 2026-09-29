#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 nodeHeaderTable[0x10];

ziU8* ZiDAWGGetChild(ziU8* node) {
    ziU8* orig = node;
    ziU16 hdr;
    ziU32 off;

    hdr = (ziU16)nodeHeaderTable[node[0] >> 4];
    if (!(hdr & 1)) {
        return ZI8_NULL;
    }
    if ((node[0] & 0xF) == 0xF) {
        off = 2;
    } else {
        off = 1;
    }
    node += off;
    if ((hdr & 2) != 0) {
        if ((node[0] & 0x80) != 0) {
            off = node[2] + (((ziU32)(node[0] & 0x7F) << 16) +
                              ((ziU16)node[1] << 8) + 0x8000);
        } else {
            off = ((ziU16)node[0] << 8) + node[1];
        }
    } else if ((hdr & 8) != 0) {
        if ((node[0] & 0x80) != 0) {
            off += 3;
        } else {
            off += 2;
        }
    }
    return orig + off;
}

ziU8* ZiDAWGGetSibling(ziU8* node) {
    ziU8* orig = node;
    ziS32 count = 0;
    ziU16 hdr;
    ziS32 off = 0;

    hdr = (ziU16)nodeHeaderTable[node[0] >> 4];
    if (!(hdr & 4)) {
        return ZI8_NULL;
    }
    if ((hdr & 8) != 0) {
        if ((node[0] & 0xF) == 0xF) {
            node += 2;
        } else {
            node += 1;
        }
        if ((hdr & 2) != 0) {
            if ((node[0] & 0x80) != 0) {
                node += 3;
            } else {
                node += 2;
            }
        }
        if ((node[0] & 0x80) != 0) {
            orig = (((ziU32)(node[0] & 0x7F) << 16) +
                     ((ziU16)node[1] << 8)) + 0x8000 + (orig + node[2]);
        } else {
            orig = orig + ((ziU16)node[0] << 8) + node[1];
        }
        return orig;
    }
    do {
        hdr = (ziU16)nodeHeaderTable[node[0] >> 4];
        if ((node[0] & 0xF) == 0xF) {
            node += 2;
            off += 2;
        } else {
            node += 1;
            off += 1;
        }
        if ((hdr & 1) != 0) {
            if ((hdr & 2) != 0) {
                if ((node[0] & 0x80) != 0) {
                    node += 3;
                    off += 3;
                } else {
                    node += 2;
                    off += 2;
                }
            } else {
                count++;
            }
        }
        if (!(hdr & 4)) {
            count--;
        } else if ((hdr & 8) != 0) {
            if ((node[0] & 0x80) != 0) {
                node += 3;
                off += 3;
            } else {
                node += 2;
                off += 2;
            }
            count--;
        }
    } while (count > 0);
    return orig + off;
}

ziU8 ZiDAWGgetEOWattribute(ziU8* node) {
    return (ziU8)(!!(nodeHeaderTable[node[0] >> 4] & 0x10));
}

ziU32 ZiDAWGgetCHARattribute(ziU8* graph, ziU8* node ZI_NEED_WORK) {
    ziU32 res;
    ziU8 idx;

    idx = ((node[0] & 0xF) == 0xF) ? (ziU8)(node[1] + 0xF)
                                    : (ziU8)(node[0] & 0xF);
    if (idx > *(ziU16*)(graph + 4)) {
        Zi8LogError(0x138B, __zi8_work_data);
        return 0;
    }
    res = (ziU32)idx << 0x18;
    res |= (ziU32)(*(ziU8**)(graph + 0xC))[idx] << 0x10;
    res |= (ziU16)(*(ziU8**)(graph + 8))[idx * 2] * 0x100 +
           (*(ziU8**)(graph + 8))[idx * 2 + 1];
    Zi8LogError(0x64, __zi8_work_data);
    return res;
}

ziU8* ZiDAWGGetGraph(ziU8* arg) {
    return ((ziU16)(*(ziU8**)(arg + 0x10))[2] << 8) +
           (*(ziU8**)(arg + 0x10))[3] +
           *(ziU8**)(arg + 0x10) + 4;
}

ziU32 ZiDAWGGetGraphInfo(ziPtr work, ziU8* hdr, ziWChar* key) {
    ziU8* graph;
    ziU32 res;
    ziU8* end;
    ziU8 i;

    graph = ZiDAWGGetGraph((ziU8*)work);
    res = 0;
    if (((ziU16)hdr[0] << 8) + hdr[1] != 0 ||
        ((ziU16)hdr[2] << 8) + hdr[3] != 0) {
        return 0;
    }
    end = hdr + ((((ziU16)hdr[4] << 8) + hdr[5]) + 1) * 0xA;
    hdr += 0xA;
    i = 0;
    goto check;
body:
    if (*key < 0xEFF1) {
        goto ret0;
    }
    if (*key > 0xF010) {
        goto ret0;
    }
    goto scan;
advance:
    if (*key == ((ziU16)hdr[2] << 8) + hdr[3]) {
        goto found;
    }
    hdr += (((ziU16)hdr[0] << 8) + hdr[1]) * 0xA + 0xA;
scan:
    if (hdr >= end) {
        goto found;
    }
    if (*key != ((ziU16)hdr[2] << 8) + hdr[3]) {
        goto advance;
    }
    goto found;
ret0:
    return 0;
found:
    if (hdr >= end) {
        return 0;
    }
    res = (ziU32)(graph + ((ziU32)hdr[4] << 0x10) +
                  (((ziU16)hdr[5] << 8) + hdr[6]));
    ((struct __zi8_work_data_s*)work)->unk_0x338 =
        (ziU32)(graph + ((ziU32)hdr[7] << 0x10) +
                (((ziU16)hdr[8] << 8) + hdr[9]));
    if (((struct __zi8_work_data_s*)work)->unk_0x338 == (ziU32)graph) {
        ((struct __zi8_work_data_s*)work)->unk_0x338 = ZI8_NULL;
    }
    if ((((ziU16)hdr[0] << 8) + hdr[1]) == 0) {
        goto done;
    }
    end = hdr + (((ziU16)hdr[0] << 8) + hdr[1]) * 0xA;
    end += 0xA;
    hdr += 0xA;
    i++;
    key++;
check:
    if (i >= 2) {
        goto done;
    }
    if (*key != 0) {
        goto body;
    }
done:
    return res;
}
