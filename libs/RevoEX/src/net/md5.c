#include <revolution/net.h>

#include <string.h>

static void ProcessBlock(NETMD5Context* context);

static u32 t[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static u32 k[48] = {
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9,
};

static u8 padding = 0x80;

#define MD5_ROT(x, s) (((x) << (s)) | ((x) >> (32 - (s))))

void NETMD5Init(NETMD5Context* context) {
    context->a = 0x67452301;
    context->b = 0xefcdab89;
    context->c = 0x98badcfe;
    context->d = 0x10325476;
    context->length = 0;
}

void NETMD5Update(NETMD5Context* context, const void* input, u32 length) {
    const u8* input8 = input;
    u32 used = context->length & 63;
    s32 gap;

    context->length += length;
    gap = 64 - used;

    if (gap > length) {
        if (length != 0) {
            memcpy(&context->buffer8[used], input8, length);
        }
    } else {
        memcpy(&context->buffer8[used], input8, gap);
        ProcessBlock(context);

        input8 += gap;
        length -= gap;

        gap = length >> 6;
        while (gap > 0) {
            memcpy(context->buffer8, input8, 64);
            input8 += 64;
            ProcessBlock(context);
            gap--;
        }

        if ((length &= 63) != 0) {
            memcpy(context->buffer8, input8, length);
        }
    }
}

void NETMD5GetDigest(NETMD5Context* context, void* digest) {
    u64 bits = context->length << 3;
    u32 used;
    u32 gap;

    NETMD5Update(context, &padding, 1);

    used = context->length & 63;
    gap = 64 - used;

    if (gap < 8) {
        memset(&context->buffer8[used], 0, gap);
        ProcessBlock(context);
        used = 0;
        gap = 64;
    }

    if (gap > 8) {
        memset(&context->buffer8[used], 0, gap - 8);
    }

    context->buffer32[14] = ((u32)bits >> 24) | (((u32)bits >> 8) & 0xFF00) |
        (((u32)bits << 8) & 0xFF0000) | ((u32)bits << 24);
    context->buffer32[15] = ((u32)(bits >> 32) >> 24) | (((u32)(bits >> 32) >> 8) & 0xFF00) |
        (((u32)(bits >> 32) << 8) & 0xFF0000) | ((u32)(bits >> 32) << 24);
    ProcessBlock(context);

    __stwbrx(context->a, digest, 0);
    __stwbrx(context->b, (u8*)digest + 4, 0);
    __stwbrx(context->c, (u8*)digest + 8, 0);
    __stwbrx(context->d, (u8*)digest + 0xC, 0);

    memset(context, 0, sizeof(NETMD5Context));
}

#define F(x, y, z) (((x) & (y)) | ((z) & ~(x)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

#define STEP(a, b, c, d, f, xi, ti, s)                                     \
    do {                                                                 \
        u8* xi_ = (u8*)(xi);                                             \
        u32 xt_ = __lwbrx(xi_, 0) + (ti);                                \
        a = (((a) + f(b, c, d) + xt_) << (s) |                           \
             ((a) + f(b, c, d) + __lwbrx(xi_, 0) + (ti)) >> (32 - (s))) + \
            (b);                                                       \
    } while (0)

static void ProcessBlock(NETMD5Context* context) {
    u32 a = context->a;
    u32 b = context->b;
    u32 c = context->c;
    u32 d = context->d;
    const u32* tp = t;
    const u32* kp = k;
    u8* xb = context->buffer8;
    u8* xp = xb;
    int i;

    for (i = 0; i < 4; i++, tp += 4) {
        STEP(a, b, c, d, F, xp, tp[0], 7);
        xp += 4;
        STEP(d, a, b, c, F, xp, tp[1], 12);
        xp += 4;
        STEP(c, d, a, b, F, xp, tp[2], 17);
        xp += 4;
        STEP(b, c, d, a, F, xp, tp[3], 22);
        xp += 4;
    }

    for (i = 0; i < 4; i++, tp += 4, kp += 4) {
        STEP(a, b, c, d, G, xb + kp[0] * 4, tp[0], 5);
        STEP(d, a, b, c, G, xb + kp[1] * 4, tp[1], 9);
        STEP(c, d, a, b, G, xb + kp[2] * 4, tp[2], 14);
        STEP(b, c, d, a, G, xb + kp[3] * 4, tp[3], 20);
    }

    for (i = 0; i < 4; i++, tp += 4, kp += 4) {
        STEP(a, b, c, d, H, xb + kp[0] * 4, tp[0], 4);
        STEP(d, a, b, c, H, xb + kp[1] * 4, tp[1], 11);
        STEP(c, d, a, b, H, xb + kp[2] * 4, tp[2], 16);
        STEP(b, c, d, a, H, xb + kp[3] * 4, tp[3], 23);
    }

    for (i = 0; i < 4; i++, tp += 4, kp += 4) {
        STEP(a, b, c, d, I, xb + kp[0] * 4, tp[0], 6);
        STEP(d, a, b, c, I, xb + kp[1] * 4, tp[1], 10);
        STEP(c, d, a, b, I, xb + kp[2] * 4, tp[2], 15);
        STEP(b, c, d, a, I, xb + kp[3] * 4, tp[3], 21);
    }

    context->a += a;
    context->b += b;
    context->c += c;
    context->d += d;
}
