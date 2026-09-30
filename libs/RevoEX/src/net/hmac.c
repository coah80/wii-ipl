#include <revolution/types.h>
#include <revolution/os.h>
#include <string.h>

typedef struct DigestInterface {
    u32 digestSize;
    u32 blockSize;
    u32 contextSize;
    u32 flags;
    void (*init)(void*);
    void (*update)(void*, const void*, u32);
    void (*getDigest)(void*, void*);
} DigestInterface;

typedef struct HMACContext {
    DigestInterface interface;
    s32 keyLength;
    u8 digestContext[96];
    u8 key[64];
} HMACContext;

void NETHMACInit(HMACContext* context, const DigestInterface* interface, const void* key, u32 length) {
    u8 innerKey[64];
    u32 i;
    u32 keyLength;
    void* work = context->digestContext;
    const char* function = "NETHMACInit";
    context->interface = *interface;
    if (context->interface.contextSize > 96 || context->interface.blockSize > 64) {
        OSReport("%s(%d):[warning in %s]", "hmac.c", 100, function);
        OSReport("specified interface needs too large workmemory.");
        OSReport("\n");
        return;
    }
    if (length <= context->interface.blockSize) {
        memcpy(context->key, key, length);
        context->keyLength = length;
    } else {
        context->interface.init(work);
        context->interface.update(work, key, length);
        context->interface.getDigest(work, context->key);
        context->keyLength = context->interface.digestSize;
    }
    keyLength = context->keyLength;
    for (i=0; i<keyLength; ++i) innerKey[i] = context->key[i] ^ 0x36;
    memset(innerKey + keyLength, 0x36, context->interface.blockSize - keyLength);
    context->interface.init(context->digestContext);
    context->interface.update(context->digestContext, innerKey, context->interface.blockSize);
}

void NETHMACUpdate(HMACContext* context, const void* data, u32 length) {
    context->interface.update(context->digestContext, data, length);
}

void NETHMACGetDigest(HMACContext* context, void* digest) {
    u8 innerDigest[64];
    u8 outerKey[64];
    u32 i;
    u32 keyLength;
    void* work = context->digestContext;
    context->interface.getDigest(work, innerDigest);
    keyLength = context->keyLength;
    for (i=0; i<keyLength; ++i) outerKey[i] = context->key[i] ^ 0x5c;
    memset(outerKey + keyLength, 0x5c, context->interface.blockSize - keyLength);
    context->interface.init(context->digestContext);
    context->interface.update(context->digestContext, outerKey, context->interface.blockSize);
    context->interface.update(work, innerDigest, context->interface.digestSize);
    context->interface.getDigest(work, digest);
}
