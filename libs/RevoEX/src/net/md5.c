#include <revolution/net/NETDigest.h>
#include <string.h>

static void ProcessBlock(NETMD5Context* context);

void NETMD5Init(NETMD5Context* context) {
    context->a = 0x67452301;
    context->b = 0xefcdab89;
    context->c = 0x98badcfe;
    context->d = 0x10325476;
    context->length = 0;
}

void NETMD5Update(NETMD5Context* context, const void* input, u32 length) {
    u32 available;
    const u8* data;
    u32 offset;
    int blocks;
    offset = context->length & 63;
    context->length += length;
    available = 64 - offset;
    data = input;
    if (available > length) {
        if (length) memcpy(context->buffer8 + offset, data, length);
    } else {
        memcpy(context->buffer8 + offset, data, available);
        ProcessBlock(context);
        length -= available;
        data += available;
        blocks = length >> 6;
        while (blocks > 0) {
            memcpy(context->buffer8, data, 64);
            data += 64;
            ProcessBlock(context);
            --blocks;
        }
        length &= 63;
        if (length) memcpy(context->buffer8, data, length);
    }
}

#define SWAP32(x) ((((((x) << 24) | ((x) >> 8)) & 0xff000000) | ((((x) << 8) | ((x) >> 24)) & 0x00ff0000)) | (((((x) << 8) | ((x) >> 24)) & 0x000000ff) | ((((x) << 24) | ((x) >> 8)) & 0x0000ff00)))

void NETMD5GetDigest(NETMD5Context* context, void* digest) {
    static u8 endMarker = 0x80;
    u32* output = digest;
    u64 bits = context->length << 3;
    u32 low = bits;
    u32 high = bits >> 32;
    u32 offset, available;
    NETMD5Update(context, &endMarker, 1);
    offset = context->length & 63;
    available = 64 - offset;
    if (available < 8) {
        memset(context->buffer8 + offset, 0, available);
        ProcessBlock(context);
        offset = 0;
        available = 64;
    }
    if (available > 8) memset(context->buffer8 + offset, 0, available - 8);
    context->buffer32[14] = SWAP32(low);
    context->buffer32[15] = SWAP32(high);
    ProcessBlock(context);
    __stwbrx(context->a, digest, 0);
    __stwbrx(context->b, &output[1], 0);
    __stwbrx(context->c, &output[2], 0);
    __stwbrx(context->d, &output[3], 0);
    memset(context, 0, sizeof(*context));
}

static inline u32 ReadMessageWord(const u32* data) {
    return __lwbrx((void*)data, 0);
}

static inline u32 rotateSum(u32 state, const u32* word, u32 constant, int shift) {
    // Each rotation half reads its own byte-reversed message word.
    u32 right = ReadMessageWord(word);
    u32 left = ReadMessageWord(word);
    return ((state + (constant + left)) << shift) | ((constant + (state + right)) >> (32 - shift));
}

static inline u32 rotateNextSum(u32 state, u32** cursor, u32 constant, int shift) {
    u32 right = ReadMessageWord(*cursor);
    u32 left = ReadMessageWord((*cursor)++);
    return ((state + (constant + left)) << shift) | ((constant + (state + right)) >> (32 - shift));
}

#define STEP_NEXT(a, b, c, d, f, word, n) ((a) = (b) + rotateNextSum((a) + (f), &(word), *constant, n))
#define STEP(a, b, c, d, f, word, n) ((a) = (b) + rotateSum((a) + (f), word, *constant, n))

static void ProcessBlock(NETMD5Context* context) {
    static u32 constants[64] = {0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501, 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821, 0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8, 0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A, 0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, 0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665, 0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1, 0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391};
    static u32 indices[48] = {0x00000001, 0x00000006, 0x0000000B, 0x00000000, 0x00000005, 0x0000000A, 0x0000000F, 0x00000004, 0x00000009, 0x0000000E, 0x00000003, 0x00000008, 0x0000000D, 0x00000002, 0x00000007, 0x0000000C, 0x00000005, 0x00000008, 0x0000000B, 0x0000000E, 0x00000001, 0x00000004, 0x00000007, 0x0000000A, 0x0000000D, 0x00000000, 0x00000003, 0x00000006, 0x00000009, 0x0000000C, 0x0000000F, 0x00000002, 0x00000000, 0x00000007, 0x0000000E, 0x00000005, 0x0000000C, 0x00000003, 0x0000000A, 0x00000001, 0x00000008, 0x0000000F, 0x00000006, 0x0000000D, 0x00000004, 0x0000000B, 0x00000002, 0x00000009};
    u32 a = context->a, b = context->b, c = context->c, d = context->d;
    u32* cursor;
    u32* block;
    u32* constant;
    int round;
    block = context->buffer32;
    cursor = block;
    constant = constants;
    for (round = 0; round < 4; ++round) {
        STEP_NEXT(a,b,c,d,(b & c) | (~b & d),cursor,7); ++constant;
        STEP_NEXT(d,a,b,c,(a & b) | (~a & c),cursor,12); ++constant;
        STEP_NEXT(c,d,a,b,(d & a) | (~d & b),cursor,17); ++constant;
        STEP_NEXT(b,c,d,a,(c & d) | (~c & a),cursor,22); ++constant;
    }
    cursor = indices;
    for (round = 0; round < 4; ++round) {
        STEP(a,b,c,d,(b & d) | (c & ~d),block + *cursor,5); ++constant; ++cursor;
        STEP(d,a,b,c,(a & c) | (b & ~c),block + *cursor,9); ++constant; ++cursor;
        STEP(c,d,a,b,(d & b) | (a & ~b),block + *cursor,14); ++constant; ++cursor;
        STEP(b,c,d,a,(c & a) | (d & ~a),block + *cursor,20); ++constant; ++cursor;
    }
    for (round = 0; round < 4; ++round) {
        STEP(a,b,c,d,b ^ c ^ d,block + *cursor,4); ++constant; ++cursor;
        STEP(d,a,b,c,a ^ b ^ c,block + *cursor,11); ++constant; ++cursor;
        STEP(c,d,a,b,d ^ a ^ b,block + *cursor,16); ++constant; ++cursor;
        STEP(b,c,d,a,c ^ d ^ a,block + *cursor,23); ++constant; ++cursor;
    }
    for (round = 0; round < 4; ++round) {
        STEP(a,b,c,d,c ^ (b | ~d),block + *cursor,6); ++constant; ++cursor;
        STEP(d,a,b,c,b ^ (a | ~c),block + *cursor,10); ++constant; ++cursor;
        STEP(c,d,a,b,a ^ (d | ~b),block + *cursor,15); ++constant; ++cursor;
        STEP(b,c,d,a,d ^ (c | ~a),block + *cursor,21); ++constant; ++cursor;
    }
    context->a += a;
    context->b += b;
    context->c += c;
    context->d += d;
}
