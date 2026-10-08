#include <private/nwc24.h>
#include <revolution/nwc24.h>

static const u8 TtableInv[] = {13, 5, 9, 7, 0, 15, 10, 2, 12, 3, 14, 1, 8, 6, 11, 4};
static const u8 ExcTable[] = {1, 5, 0, 4, 2, 3, 6, 7};
extern void _savegpr_27(void);
extern void _restgpr_27(void);
extern void __shr2u(void);
extern void __shl2i(void);

static NWC24UserId getUnScrambleId(NWC24UserId id);
NWC24Err NWC24CheckUserId(NWC24UserId id) {
    NWC24UserId myId;
    u64 value;
    int i;
    u32 area;
    u32 myArea;

    NWC24GetMyUserId(&myId);
    if (myId == id) {
        return NWC24_ERR_ID_GENERATED;
    }
    myArea = (getUnScrambleId(myId) >> 47) & 7;
    value = getUnScrambleId(id);
    area = (value >> 47) & 7;
    for (i = 0; i < 0x2B; i++) {
        if ((value >> (0x35 - (i + 1))) & 1) {
            value ^= (u64)0x635 << (0x2A - i);
        }
    }
    if (value != 0) {
        return NWC24_ERR_ID_CRC;
    }
    if (myArea == 0 && area != 0) {
        return NWC24_ERR_PROTECTED;
    }
    return NWC24_OK;
}


NWC24Err NWC24iCheckUserIdCRC(NWC24UserId id) {
    u64 value = getUnScrambleId(id);
    int i;

    for (i = 0; i < 0x2B; i++) {
        if ((value >> (0x35 - (i + 1))) & 1) {
            value ^= (u64)0x635 << (0x2A - i);
        }
    }

    if (value != 0) {
        return NWC24_ERR_ID_CRC;
    }
    return NWC24_OK;
}

static u8 getByte(u64 value, u8 index) {
    return (value >> (index * 8)) & 0xFF;
}

static u64 setByte(u64 value, u8 index, u8 byte) {
    return (value & ~(0xFFULL << ((u64)8 * index))) | ((u64)byte << ((u64)8 * index));
}

static NWC24UserId getUnScrambleId(NWC24UserId id) {
    u64 copy;
    u8 i;

    id &= 0x001FFFFFFFFFFFFFULL;
    id ^= 0x00005E5E5E5E5E5EULL;
    id &= 0x001FFFFFFFFFFFFFULL;
    id |= (((id & 0xFF) << 5) & 0x20) << 48;
    id >>= 1;

    copy = id;
    for (i = 0; i < 6; ++i) {
        id = setByte(id, i, getByte(copy, ExcTable[i]));
    }

    for (i = 0; i < 6; ++i) {
        id = setByte(id, i, (TtableInv[(getByte(id, i) >> 4) & 0xF] << 4) | TtableInv[getByte(id, i) & 0xF]);
    }

    id = ((id & 0x7FFFFFFFFFFULL) << 10) | ((id >> 43) & 0x3FF);
    id ^= 0x0000B3B3B3B3B3B3ULL;
    return id;
}
