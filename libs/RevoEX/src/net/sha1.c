#include <revolution/net/NETDigest.h>
#include <string.h>

typedef struct SHA1State {
    u32 state[5];
    u8 buffer[64];
    u32 buffered;
    u32 blocksLow;
    u32 blocksHigh;
} SHA1State;

typedef struct DigestInterface {
    u32 digestSize;
    u32 blockSize;
    u32 contextSize;
    u32 flags;
    void (*init)(NETSHA1Context*);
    void (*update)(NETSHA1Context*, const void*, u32);
    void (*getDigest)(NETSHA1Context*, void*);
} DigestInterface;

void NETSHA1iProcessBlock(NETSHA1Context* context);

void NETSHA1Init(NETSHA1Context* context) {
    SHA1State* work = (SHA1State*)context;
    work->blocksLow = 0;
    work->blocksHigh = 0;
    work->buffered = 0;
    work->state[0] = 0x67452301;
    work->state[1] = 0xefcdab89;
    work->state[2] = 0x98badcfe;
    work->state[3] = 0x10325476;
    work->state[4] = 0xc3d2e1f0;
}

void NETSHA1Update(NETSHA1Context* context, const void* input, u32 length) {
    SHA1State* work = (SHA1State*)context;
    u32 available;
    u32 remaining = length;
    const u8* data = input;
    while (remaining != 0) {
        available = 64 - work->buffered;
        if (available > remaining) available = remaining;
        memcpy(work->buffer + work->buffered, data, available);
        work->buffered += available;
        data += available;
        remaining -= available;
        if (work->buffered >= 64) {
            NETSHA1iProcessBlock(context);
            work->buffered = 0;
            if (++work->blocksLow == 0) ++work->blocksHigh;
        }
    }
}

void NETSHA1GetDigest(NETSHA1Context* context, void* digest) {
    static const u8 endMarker = 0x80;
    static const u8 zeroBytes[8] = {0};
    SHA1State* work = (SHA1State*)context;
    u32 bitLength[2];
    u32 length;
    u32 available;
    u32 endSpace;
    bitLength[1] = (work->blocksLow << 9) + (work->buffered << 3);
    bitLength[0] = (work->blocksHigh << 9) + (work->blocksLow >> 23);
    NETSHA1Update(context, &endMarker, 1);
    endSpace = 64 - work->buffered;
    if (endSpace < 8) NETSHA1Update(context, zeroBytes, endSpace);
    length = 56 - work->buffered;
    while (length != 0) {
        available = 64 - work->buffered;
        if (available > length) available = length;
        memset(work->buffer + work->buffered, 0, available);
        work->buffered += available;
        length -= available;
        if (work->buffered >= 64) {
            NETSHA1iProcessBlock(context);
            work->buffered = 0;
            if (++work->blocksLow == 0) ++work->blocksHigh;
        }
    }
    NETSHA1Update(context, bitLength, 8);
    memcpy(digest, context, 20);
}

const DigestInterface* NETGetSHA1Interface(void) {
    static const DigestInterface interface = {20, 64, 96, 0, NETSHA1Init, NETSHA1Update, NETSHA1GetDigest};
    return &interface;
}

#define ROTATE(x,n) (((x) << (n)) | ((x) >> (32 - (n))))
#define EXPAND() if (round >= 16) words[round & 15] = ROTATE((words[(round-3)&15] ^ words[(round-8)&15]) ^ (words[(round-16)&15] ^ words[(round-14)&15]), 1)
#define ROUND(f,k) { u32 next = (f) + (k); EXPAND(); next = words[round & 15] + (ROTATE(a,5) + (next + e)); e=d; d=c; c=ROTATE(b,30); b=a; a=next; }

void NETSHA1iProcessBlock(NETSHA1Context* context) {
    SHA1State* work = (SHA1State*)context;
    u32 words[16];
    int round=0;
    u32 a=work->state[0], b=work->state[1], c=work->state[2], d=work->state[3], e=work->state[4];
    { int word; for (word=0; word<16; ++word) words[word] = ((u32*)work->buffer)[word]; }
    for (; round < 20; ++round) ROUND((b & c) | (~b & d), 0x5a827999);
    for (; round < 40; ++round) ROUND(b ^ c ^ d, 0x6ed9eba1);
    for (; round < 60; ++round) ROUND((c & d) | (b & (c | d)), 0x8f1bbcdc);
    for (; round < 80; ++round) ROUND(b ^ c ^ d, 0xca62c1d6);
    work->state[0] += a;
    work->state[1] += b;
    work->state[2] += c;
    work->state[3] += d;
    work->state[4] += e;
}
