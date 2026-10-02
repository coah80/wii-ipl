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

#define ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define STEP(a, b, c, d, f, word, n) \
    do { \
        u32 _xw = __lwbrx((word), 0); \
        u32 _wc = __lwbrx((word), 0) + *constant; \
        (a) += (f); \
        (a) = (b) + (((a) + _wc) << (n) | (_xw + (*constant + (a))) >> (32 - (n))); \
        ++constant; \
    } while (0)

static void ProcessBlock(NETMD5Context* context) {
    static u32 constants[64] = {0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501, 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821, 0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8, 0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A, 0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, 0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665, 0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1, 0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391};
    static u32 indices[48] = {0x00000001, 0x00000006, 0x0000000B, 0x00000000, 0x00000005, 0x0000000A, 0x0000000F, 0x00000004, 0x00000009, 0x0000000E, 0x00000003, 0x00000008, 0x0000000D, 0x00000002, 0x00000007, 0x0000000C, 0x00000005, 0x00000008, 0x0000000B, 0x0000000E, 0x00000001, 0x00000004, 0x00000007, 0x0000000A, 0x0000000D, 0x00000000, 0x00000003, 0x00000006, 0x00000009, 0x0000000C, 0x0000000F, 0x00000002, 0x00000000, 0x00000007, 0x0000000E, 0x00000005, 0x0000000C, 0x00000003, 0x0000000A, 0x00000001, 0x00000008, 0x0000000F, 0x00000006, 0x0000000D, 0x00000004, 0x0000000B, 0x00000002, 0x00000009};
    u32 a = context->a, b = context->b, c = context->c, d = context->d;
    u32* word;
    u32* constant;
    u32* index;
    u32* wptr;
    int round;
    u32* block;
    block = context->buffer32;
    word = block;
    constant = constants;
    for (round = 0; round < 4; ++round) {
        STEP(a,b,c,d,(b & c) | (~b & d),word,7); ++word;
        STEP(d,a,b,c,(a & b) | (~a & c),word,12); ++word;
        STEP(c,d,a,b,(d & a) | (~d & b),word,17); ++word;
        STEP(b,c,d,a,(c & d) | (~c & a),word,22); ++word;
    }
    index = indices;
    for (round = 0; round < 4; ++round) {
        wptr = block + *index; STEP(a,b,c,d,(b & d) | (c & ~d),wptr,5); ++index;
        wptr = block + *index; STEP(d,a,b,c,(a & c) | (b & ~c),wptr,9); ++index;
        wptr = block + *index; STEP(c,d,a,b,(d & b) | (a & ~b),wptr,14); ++index;
        wptr = block + *index; STEP(b,c,d,a,(c & a) | (d & ~a),wptr,20); ++index;
    }
    for (round = 0; round < 4; ++round) {
        wptr = block + *index; STEP(a,b,c,d,d ^ b ^ c,wptr,4); ++index;
        wptr = block + *index; STEP(d,a,b,c,c ^ a ^ b,wptr,11); ++index;
        wptr = block + *index; STEP(c,d,a,b,b ^ d ^ a,wptr,16); ++index;
        wptr = block + *index; STEP(b,c,d,a,a ^ c ^ d,wptr,23); ++index;
    }
    for (round = 0; round < 4; ++round) {
        wptr = block + *index; STEP(a,b,c,d,c ^ (b | ~d),wptr,6); ++index;
        wptr = block + *index; STEP(d,a,b,c,b ^ (a | ~c),wptr,10); ++index;
        wptr = block + *index; STEP(c,d,a,b,a ^ (d | ~b),wptr,15); ++index;
        wptr = block + *index; STEP(b,c,d,a,d ^ (c | ~a),wptr,21); ++index;
    }
    context->a += a;
    context->b += b;
    context->c += c;
    context->d += d;
}
