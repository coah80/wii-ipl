#include <revolution/net.h>

#include <string.h>

typedef struct NETSHA1Interface {
    u32 digestSize;
    u32 blockSize;
    u32 contextSize;
    void* unk_0x0C;
    void (*init)(NETSHA1Context* context);
    void (*update)(NETSHA1Context* context, const void* input, u32 length);
    void (*getDigest)(NETSHA1Context* context, void* digest);
    void* unk_0x1C;
} NETSHA1Interface;

typedef struct {
    u32 state[5];
    union {
        u32 buffer32[16];
        u8 buffer8[64];
    };
    u32 used;
    u32 blocksLo;
    u32 blocksHi;
} NETSHA1iContext;

static const u8 padlead = 0x80;
static const u8 padalign[8];

#define SHA1_ROT(x, s) (((x) << (s)) | ((x) >> (32 - (s))))

static void NETSHA1iProcessBlock(NETSHA1Context* context) {
    NETSHA1iContext* ctx = (NETSHA1iContext*)context;
    u32 w[16];
    u32 a;
    u32 b;
    u32 c;
    u32 d;
    u32 e;
    u32 f;
    int i;

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];

    for (i = 0; i < 16; i++) {
        w[i] = ctx->buffer32[i];
    }

    i = 0;

    for (; i < 20; i++) {
            u32* wp = w;
        f = (b & c) | (d & ~b);
        f += 0x5A827999;
        if (i >= 16) {
            wp[i & 15] = SHA1_ROT(
                (wp[(i - 3) & 15] ^ wp[(i - 8) & 15]) ^
                    (wp[(i - 16) & 15] ^ wp[(i - 14) & 15]),
                1);
        }
        f += e;
        f += SHA1_ROT(a, 5);
        f += wp[i & 15];
        e = d;
        d = c;
        c = SHA1_ROT(b, 30);
        b = a;
        a = f;
    }

    for (; i < 40; i++) {
        f = b ^ c ^ d;
        f += 0x6ED9EBA1;
        if (i >= 16) {
            w[i & 15] = SHA1_ROT(
                (w[(i - 3) & 15] ^ w[(i - 8) & 15]) ^
                    (w[(i - 16) & 15] ^ w[(i - 14) & 15]),
                1);
        }
        f += e + SHA1_ROT(a, 5) + w[i & 15];
        e = d;
        d = c;
        c = SHA1_ROT(b, 30);
        b = a;
        a = f;
    }

    for (; i < 60; i++) {
        f = (b & (c | d)) | (c & d);
        f += 0x8F1BBCDC;
        if (i >= 16) {
            w[i & 15] = SHA1_ROT(
                (w[(i - 3) & 15] ^ w[(i - 8) & 15]) ^
                    (w[(i - 16) & 15] ^ w[(i - 14) & 15]),
                1);
        }
        f += e + SHA1_ROT(a, 5) + w[i & 15];
        e = d;
        d = c;
        c = SHA1_ROT(b, 30);
        b = a;
        a = f;
    }

    for (; i < 80; i++) {
        f = b ^ c ^ d;
        f += 0xCA62C1D6;
        if (i >= 16) {
            w[i & 15] = SHA1_ROT(
            (w[(i - 3) & 15] ^ w[(i - 8) & 15]) ^
                (w[(i - 16) & 15] ^ w[(i - 14) & 15]),
            1);
        }
        f += e + SHA1_ROT(a, 5) + w[i & 15];
        e = d;
        d = c;
        c = SHA1_ROT(b, 30);
        b = a;
        a = f;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
}

void NETSHA1Init(NETSHA1Context* context) {
    NETSHA1iContext* ctx = (NETSHA1iContext*)context;

    ctx->blocksLo = 0;
    ctx->blocksHi = 0;
    ctx->used = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
}

void NETSHA1Update(NETSHA1Context* context, const void* input, u32 length) {
    NETSHA1iContext* ctx = (NETSHA1iContext*)context;

    while (length != 0) {
        u32 fill = 64 - ctx->used;

        if (fill > length) {
            fill = length;
        }

        memcpy(&ctx->buffer8[ctx->used], input, fill);
        input = (const u8*)input + fill;
        length -= fill;
        ctx->used += fill;

        if (ctx->used >= 64) {
            NETSHA1iProcessBlock(context);
            ctx->used = 0;
            if (++ctx->blocksLo == 0) {
                ctx->blocksHi++;
            }
        }
    }
}

void NETSHA1GetDigest(NETSHA1Context* context, void* digest) {
    NETSHA1iContext* ctx = (NETSHA1iContext*)context;
    union {
        u64 v;
        u32 w[2];
    } bits;
    u32 remaining;

    bits.w[1] = (ctx->blocksLo << 9) + (ctx->used << 3);
    bits.w[0] = (ctx->blocksHi << 9) + (ctx->blocksLo >> 23);
    NETSHA1Update(context, &padlead, 1);

    if (64 - ctx->used < 8) {
        NETSHA1Update(context, padalign, 64 - ctx->used);
    }

    for (remaining = 56 - ctx->used; remaining != 0;) {
        u32 fill = 64 - ctx->used;

        if (fill > remaining) {
            fill = remaining;
        }

        memset(&ctx->buffer8[ctx->used], 0, fill);
        remaining -= fill;
        ctx->used += fill;

        if (ctx->used >= 64) {
            NETSHA1iProcessBlock(context);
            ctx->used = 0;
            if (++ctx->blocksLo == 0) {
                ctx->blocksHi++;
            }
        }
    }

    NETSHA1Update(context, &bits, sizeof(bits));
    memcpy(digest, ctx->state, 0x14);
}

static const NETSHA1Interface sha1template = {
    0x14,
    0x40,
    0x60,
    NULL,
    NETSHA1Init,
    NETSHA1Update,
    NETSHA1GetDigest,
    NULL,
};

const NETSHA1Interface* NETGetSHA1Interface(void) {
    return &sha1template;
}
