#include <revolution.h>
#include <revolution/net.h>

#include <string.h>

// TODO: Not yet in the SDK
typedef struct {
    u32 digestSize;    // 0x00
    u32 blockSize;     // 0x04
    u32 contextSize;   // 0x08
    void* unk_0x0C;    // 0x0C
    void (*init)(void* context);                                    // 0x10
    void (*update)(void* context, const void* input, u32 length);   // 0x14
    void (*getDigest)(void* context, void* digest);                 // 0x18
} NETHASHInterface;

// TODO: Not yet in the SDK
typedef struct NETHMACContext {
    NETHASHInterface hash;  // 0x00
    u32 keyLen;             // 0x1C
    u8 hashCtx[0x60];       // 0x20
    u8 keyBuf[0x40];        // 0x80
} NETHMACContext;           // 0xC0

void NETHMACInit(NETHMACContext* ctx, const NETHASHInterface* template, const void* key,
                 u32 keyLen) {
    u8 ipad[64];
    u8* hctx = ctx->hashCtx;
    u32 i;

    ctx->hash.digestSize = template->digestSize;
    ctx->hash.blockSize = template->blockSize;
    ctx->hash.contextSize = template->contextSize;
    ctx->hash.unk_0x0C = template->unk_0x0C;
    ctx->hash.init = template->init;
    ctx->hash.update = template->update;
    ctx->hash.getDigest = template->getDigest;

    if (ctx->hash.contextSize > 0x60 || ctx->hash.blockSize > 0x40) {
        OSReport("%s(%d):[warning in %s]", "hmac.c", 100, __FUNCTION__);
        OSReport("specified interface needs too large workmemory.");
        OSReport("\n");
        return;
    }

    if (keyLen <= ctx->hash.blockSize) {
        memcpy(ctx->keyBuf, key, keyLen);
        ctx->keyLen = keyLen;
    } else {
        ctx->hash.init(hctx);
        ctx->hash.update(hctx, key, keyLen);
        ctx->hash.getDigest(hctx, ctx->keyBuf);
        ctx->keyLen = ctx->hash.digestSize;
    }

    keyLen = ctx->keyLen;
    for (i = 0; i < keyLen; i++) {
        ipad[i] = ctx->keyBuf[i] ^ 0x36;
    }
    memset(ipad + keyLen, 0x36, ctx->hash.blockSize - keyLen);

    ctx->hash.init(ctx->hashCtx);
    ctx->hash.update(ctx->hashCtx, ipad, ctx->hash.blockSize);
}

void NETHMACUpdate(NETHMACContext* ctx, const void* data, u32 len) {
    ctx->hash.update(ctx->hashCtx, data, len);
}

void NETHMACGetDigest(NETHMACContext* ctx, void* digest) {
    u8* hctx = ctx->hashCtx;
    u8 inner[64];
    u8 opad[64];
    u32 i;

    ctx->hash.getDigest(hctx, inner);

    {
        u32 keyLen = ctx->keyLen;
        for (i = 0; i < keyLen; i++) {
            opad[i] = ctx->keyBuf[i] ^ 0x5c;
        }
        memset(opad + keyLen, 0x5c, ctx->hash.blockSize - keyLen);
    }

    hctx = ctx->hashCtx;

    ctx->hash.init(hctx);
    ctx->hash.update(hctx, opad, ctx->hash.blockSize);
    ctx->hash.update(hctx, inner, ctx->hash.digestSize);
    ctx->hash.getDigest(hctx, digest);
}
